/*

Copyright (C) 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001,
              2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 John W. Eaton
  
This file is part of Octave.

Octave is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

Octave is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with Octave; see the file COPYING.  If not, see
<http://www.gnu.org/licenses/>.

*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "oct-env.h"
#include "oct-time.h"
#include "file-ops.h"
#include "file-stat.h"

#include "defun.h"
#include "dirfns.h"
#include "input.h"
#include "load-path.h"
#include "symtab.h"
#include "ov-fcn.h"
#include "ov-usr-fcn.h"
#include "pager.h"
#include "parse.h"
#include "pt-arg-list.h"
#include "toplev.h"
#include "unwind-prot.h"
#include "utils.h"
#include "debug.h"

symbol_table *symbol_table::instance = 0;

symbol_table::scope_id_cache *symbol_table::scope_id_cache::instance = 0;

std::map<symbol_table::scope_id, symbol_table*> symbol_table::all_instances;

std::map<std::string, octave_value> symbol_table::global_table;

std::map<std::string, symbol_table::fcn_info> symbol_table::fcn_table;

std::map<std::string, std::set<std::string> > symbol_table::class_precedence_table;

const symbol_table::scope_id symbol_table::xglobal_scope = 0;
const symbol_table::scope_id symbol_table::xtop_scope = 1;

symbol_table::scope_id symbol_table::xcurrent_scope = 1;

symbol_table::scope_id symbol_table::xparent_scope = -1;

symbol_table::context_id symbol_table::xcurrent_context = 0;

// Should Octave always check to see if function files have changed
// since they were last compiled?
static int Vignore_function_time_stamp = 1;

void
symbol_table::symbol_record::symbol_record_rep::dump
  (std::ostream& os, const std::string& prefix) const
{
  octave_value val = varval (xcurrent_context);

  os << prefix << name;

  if (val.is_defined ())
    {
      os << " ["
	 << (is_local () ? "l" : "")
	 << (is_automatic () ? "a" : "")
	 << (is_formal () ? "f" : "")
	 << (is_hidden () ? "h" : "")
	 << (is_inherited () ? "i" : "")
	 << (is_global () ? "g" : "")
	 << (is_persistent () ? "p" : "")
	 << "] ";
      val.dump (os);
    }

  os << "\n";
}

octave_value
symbol_table::symbol_record::find (tree_argument_list *args,
				   const string_vector& arg_names,
				   octave_value_list& evaluated_args,
				   bool& args_evaluated) const
{
  octave_value retval;

  if (is_global ())
    return symbol_table::global_varref (name ());
  else
    {
      octave_value val = varval ();

      if (val.is_defined ())
	return val;
    }

  return symbol_table::find_function (name (), args, arg_names,
				      evaluated_args, args_evaluated);
}

// Check the load path to see if file that defined this is still
// visible.  If the file is no longer visible, then erase the
// definition and move on.  If the file is visible, then we also
// need to check to see whether the file has changed since the the
// function was loaded/parsed.  However, this check should only
// happen once per prompt (for files found from relative path
// elements, we also check if the working directory has changed
// since the last time the function was loaded/parsed).
//
// FIXME -- perhaps this should be done for all loaded functions when
// the prompt is printed or the directory has changed, and then we
// would not check for it when finding symbol definitions.

static inline bool
load_out_of_date_fcn (const std::string& ff, const std::string& dir_name,
		      octave_value& function,
		      const std::string& dispatch_type = std::string ())
{
  bool retval = false;

  octave_function *fcn = load_fcn_from_file (ff, dir_name, dispatch_type);

  if (fcn)
    {
      retval = true;

      function = octave_value (fcn);
    }
  else
    function = octave_value ();

  return retval;
}

static inline bool
out_of_date_check_internal (octave_function *fcn, octave_value& function,
			    const std::string& dispatch_type = std::string ())
{
  bool retval = false;

  if (fcn)
    {
      // FIXME -- we need to handle nested functions properly here.

      if (! fcn->is_nested_function ())
	{
	  std::string ff = fcn->fcn_file_name ();

	  if (! ff.empty ())
	    {
	      octave_time tc = fcn->time_checked ();

	      bool relative = fcn->is_relative ();

	      if (tc < Vlast_prompt_time
		  || (relative && tc < Vlast_chdir_time))
		{
		  bool clear_breakpoints = false;
		  std::string nm = fcn->name ();

		  int nm_len = nm.length ();

		  std::string file;
		  std::string dir_name;

		  if (octave_env::absolute_pathname (nm)
		      && ((nm_len > 4 && (nm.substr (nm_len-4) == ".oct"
					  || nm.substr (nm_len-4) == ".mex"))
			  || (nm_len > 2 && nm.substr (nm_len-2) == ".m")))
		    file = nm;
		  else
		    {
		      // We don't want to make this an absolute name,
		      // because load_fcn_file looks at the name to
		      // decide whether it came from a relative lookup.

		      if (! dispatch_type.empty ())
			file = load_path::find_method (dispatch_type, nm,
						       dir_name);

		      if (file.empty ())
			file = load_path::find_fcn (nm, dir_name);
		    }

		  if (file.empty ())
		    {
		      // Can't see this function from current
		      // directory, so we should clear it.

		      function = octave_value ();

		      clear_breakpoints = true;
		    }
		  else if (same_file (file, ff))
		    {
		      // Same file.  If it is out of date, then reload it.

		      octave_time ottp = fcn->time_parsed ();
		      time_t tp = ottp.unix_time ();

		      fcn->mark_fcn_file_up_to_date (octave_time ());

		      if (! (Vignore_function_time_stamp == 2
			     || (Vignore_function_time_stamp
				 && fcn->is_system_fcn_file ())))
			{
			  file_stat fs (ff);

			  if (fs)
			    {
			      if (fs.is_newer (tp))
				{
				  retval = load_out_of_date_fcn (ff, dir_name,
								 function,
								 dispatch_type);

				  clear_breakpoints = true;
				}
			    }
			  else
			    {
			      function = octave_value ();

			      clear_breakpoints = true;
			    }
			}
		    }
		  else
		    {
		      // Not the same file, so load the new file in
		      // place of the old.

		      retval = load_out_of_date_fcn (file, dir_name, function,
						     dispatch_type);

		      clear_breakpoints = true;
		    }

		  // If the function has been replaced then clear any 
		  // breakpoints associated with it
		  if (clear_breakpoints)
		    bp_table::remove_all_breakpoints_in_file (nm, true);
		}
	    }
	}
    }

  return retval;
}

static inline bool
out_of_date_check_internal (octave_value& function,
			    const std::string& dispatch_type = std::string ())
{
  return out_of_date_check_internal (function.function_value (true),
				     function, dispatch_type);
}

bool
out_of_date_check (octave_value& function)
{
  return out_of_date_check_internal (function);
}

bool
out_of_date_check (octave_function* fcn)
{
  octave_value function;
  return out_of_date_check_internal (fcn, function);
}

octave_value
symbol_table::fcn_info::fcn_info_rep::load_private_function
  (const std::string& dir_name)
{
  octave_value retval;

  std::string file_name = load_path::find_private_fcn (dir_name, name);

  if (! file_name.empty ())
    {
      octave_function *fcn = load_fcn_from_file (file_name, dir_name);

      if (fcn)
	{
	  std::string class_name;

	  size_t pos = dir_name.find_last_of (file_ops::dir_sep_chars ());

	  if (pos != std::string::npos)
	    {
	      std::string tmp = dir_name.substr (pos+1);

	      if (tmp[0] == '@')
		class_name = tmp.substr (1);
	    }

	  fcn->mark_as_private_function (class_name);

	  retval = octave_value (fcn);

	  private_functions[dir_name] = retval;
	}
    }

  return retval;
}

octave_value
symbol_table::fcn_info::fcn_info_rep::load_class_constructor (void)
{
  octave_value retval;

  std::string dir_name;

  std::string file_name = load_path::find_method (name, name, dir_name);

  if (! file_name.empty ())
    {
      octave_function *fcn = load_fcn_from_file (file_name, dir_name, name);

      if (fcn)
	{
	  retval = octave_value (fcn);

	  class_constructors[name] = retval;
	}
    }

  return retval;
}

octave_value
symbol_table::fcn_info::fcn_info_rep::load_class_method
  (const std::string& dispatch_type)
{
  octave_value retval;

  if (name == dispatch_type)
    retval = load_class_constructor ();
  else
    {
      std::string dir_name;

      std::string file_name = load_path::find_method (dispatch_type, name,
						      dir_name);

      if (! file_name.empty ())
	{
	  octave_function *fcn = load_fcn_from_file (file_name, dir_name,
						     dispatch_type);

	  if (fcn)
	    {
	      retval = octave_value (fcn);

	      class_methods[dispatch_type] = retval;
	    }
	}
    }

  return retval;
}

void
symbol_table::fcn_info::fcn_info_rep::print_dispatch (std::ostream& os) const
{
  if (dispatch_map.empty ())
    os << "dispatch: " << name << " is not overloaded" << std::endl;
  else
    {
      os << "Overloaded function " << name << ":\n\n";

      for (dispatch_map_const_iterator p = dispatch_map.begin ();
	   p != dispatch_map.end (); p++)
	os << "  " << name << " (" << p->first << ", ...) -> " 
	   << p->second << " (" << p->first << ", ...)\n";

      os << std::endl;
    }
}

std::string
symbol_table::fcn_info::fcn_info_rep::help_for_dispatch (void) const
{
  std::string retval;

  if (! dispatch_map.empty ())
    {
      retval = "Overloaded function:\n\n";

      for (dispatch_map_const_iterator p = dispatch_map.begin ();
	   p != dispatch_map.end (); p++)
	retval += "  " + p->second + " (" + p->first + ", ...)\n\n";
    }

  return retval;
}

static std::string
get_dispatch_type (const octave_value_list& evaluated_args)
{
  std::string dispatch_type;

  int n = evaluated_args.length ();

  if (n > 0)
    {
      // Find first object, if any.

      int i;

      for (i = 0; i < n; i++)
	{
	  octave_value arg = evaluated_args(i);

	  if (arg.is_object ())
	    {
	      dispatch_type = arg.class_name ();
	      break;
	    }
	}

      for (int j = i+1; j < n; j++)
	{
	  octave_value arg = evaluated_args(j);

	  if (arg.is_object ())
	    {
	      std::string cname = arg.class_name ();

	      // Only switch to type of ARG if it is marked superior
	      // to the current DISPATCH_TYPE.
	      if (! symbol_table::is_superiorto (dispatch_type, cname)
		  && symbol_table::is_superiorto (cname, dispatch_type))
		dispatch_type = cname;
	    }
	}

      if (dispatch_type.empty ())
	{
	  // No object found, so use class of first argument.

	  dispatch_type = evaluated_args(0).class_name ();
	}
    }

  return dispatch_type;
}

// Find the definition of NAME according to the following precedence
// list:
//
//   variable
//   subfunction
//   private function
//   class constructor
//   class method
//   legacy dispatch
//   command-line function
//   autoload function
//   function on the path
//   built-in function

// Notes:
//
// FIXME -- we need to evaluate the argument list to determine the
// dispatch type.  The method used here works (pass in the args, pass
// out the evaluated args and a flag saying whether the evaluation was
// needed), but it seems a bit inelegant.  We do need to save the
// evaluated args in some way to avoid evaluating them multiple times.
//  Maybe evaluated args could be attached to the tree_argument_list
// object?  Then the argument list could be evaluated outside of this
// function and we could elimnate the arg_names, evaluated_args, and
// args_evaluated arguments.  We would still want to avoid computing
// the dispatch type unless it is needed, so the args should be passed
// rather than the dispatch type.  But the arguments will need to be
// evaluated no matter what, so evaluating them beforehand should be
// OK.  If the evaluated arguments are attached to args, then we would
// need to determine the appropriate place(s) to clear them (for
// example, before returning from tree_index_expression::rvalue).

octave_value
symbol_table::fcn_info::fcn_info_rep::find
  (tree_argument_list *args, const string_vector& arg_names,
   octave_value_list& evaluated_args, bool& args_evaluated)
{
  octave_value retval = xfind (args, arg_names, evaluated_args, args_evaluated);

  if (! retval.is_defined ())
    {
      // It is possible that the user created a file on the fly since
      // the last prompt or chdir, so try updating the load path and
      // searching again.

      load_path::update ();

      retval = xfind (args, arg_names, evaluated_args, args_evaluated);
    }

  return retval;
}

octave_value
symbol_table::fcn_info::fcn_info_rep::xfind
  (tree_argument_list *args, const string_vector& arg_names,
   octave_value_list& evaluated_args, bool& args_evaluated)
{
  // Subfunction.  I think it only makes sense to check for
  // subfunctions if we are currently executing a function defined
  // from a .m file.

  scope_val_iterator r = subfunctions.find (xcurrent_scope);

  octave_function *curr_fcn = 0;

  if (r != subfunctions.end ())
    {
      // FIXME -- out-of-date check here.

      return r->second;
    }
  else
    {
      curr_fcn = octave_call_stack::current ();

      if (curr_fcn)
	{
	  scope_id pscope = curr_fcn->parent_fcn_scope ();

	  if (pscope > 0)
	    {
	      r = subfunctions.find (pscope);

	      if (r != subfunctions.end ())
		{
		  // FIXME -- out-of-date check here.

		  return r->second;
		}
	    }
	}
    }

  // Private function.

  if (! curr_fcn)
    curr_fcn = octave_call_stack::current ();

  if (curr_fcn)
    {
      std::string dir_name = curr_fcn->dir_name ();

      if (! dir_name.empty ())
	{
	  str_val_iterator q = private_functions.find (dir_name);

	  if (q == private_functions.end ())
	    {
	      octave_value val = load_private_function (dir_name);

	      if (val.is_defined ())
		return val;
	    }
	  else
	    {
	      octave_value& fval = q->second;

	      if (fval.is_defined ())
		out_of_date_check_internal (fval);

	      if (fval.is_defined ())
		return fval;
	      else
		{
		  octave_value val = load_private_function (dir_name);

		  if (val.is_defined ())
		    return val;
		}
	    }
	}
    }

  // Class constructors.  The class name and function name are the same.

  str_val_iterator q = class_constructors.find (name);

  if (q == class_constructors.end ())
    {
      octave_value val = load_class_constructor ();

      if (val.is_defined ())
	return val;
    }
  else
    {
      octave_value& fval = q->second;

      if (fval.is_defined ())
	out_of_date_check_internal (fval, name);

      if (fval.is_defined ())
	return fval;
      else
	{
	  octave_value val = load_class_constructor ();

	  if (val.is_defined ())
	    return val;
	}
    }

  // Class methods.

  if (args_evaluated || (args && args->length () > 0))
    {
      if (! args_evaluated)
	evaluated_args = args->convert_to_const_vector ();

      if (! error_state)
	{
	  int n = evaluated_args.length ();

	  if (n > 0 && ! args_evaluated)
	    evaluated_args.stash_name_tags (arg_names);

	  args_evaluated = true;

	  if (n > 0)
	    {
	      std::string dispatch_type = get_dispatch_type (evaluated_args);

	      octave_value fcn = find_method (dispatch_type);

	      if (fcn.is_defined ())
		return fcn;
	    }
	}
      else
	return octave_value ();
    }

  // Legacy dispatch.  We just check args_evaluated here because the
  // actual evaluation will have happened already when searching for
  // class methods.

  if (args_evaluated && ! dispatch_map.empty ())
    {
      std::string dispatch_type = 
        const_cast<const octave_value_list&>(evaluated_args)(0).type_name ();

      std::string fname;

      dispatch_map_iterator p = dispatch_map.find (dispatch_type);

      if (p == dispatch_map.end ())
	p = dispatch_map.find ("any");

      if (p != dispatch_map.end ())
	{
	  fname = p->second;

	  octave_value fcn
	    = symbol_table::find_function (fname, evaluated_args);

	  if (fcn.is_defined ())
	    return fcn;
	}
    }

  // Command-line function.

  if (cmdline_function.is_defined ())
    return cmdline_function;

  // Autoload?

  octave_value fcn = find_autoload ();

  if (fcn.is_defined ())
    return fcn;

  // Function on the path.

  fcn = find_user_function ();

  if (fcn.is_defined ())
    return fcn;

  // Built-in function (might be undefined).

  return built_in_function;
}

octave_value
symbol_table::fcn_info::fcn_info_rep::find_method (const std::string& dispatch_type)
{
  octave_value retval;

  str_val_iterator q = class_methods.find (dispatch_type);

  if (q == class_methods.end ())
    {
      octave_value val = load_class_method (dispatch_type);

      if (val.is_defined ())
	return val;
    }
  else
    {
      octave_value& fval = q->second;

      if (fval.is_defined ())
	out_of_date_check_internal (fval, dispatch_type);

      if (fval.is_defined ())
	return fval;
      else
	{
	  octave_value val = load_class_method (dispatch_type);

	  if (val.is_defined ())
	    return val;
	}
    }

  return retval;
}

octave_value
symbol_table::fcn_info::fcn_info_rep::find_autoload (void)
{
  octave_value retval;

  // Autoloaded function.

  if (autoload_function.is_defined ())
    out_of_date_check_internal (autoload_function);

  if (! autoload_function.is_defined ())
    {
      std::string file_name = lookup_autoload (name);

      if (! file_name.empty ())
	{
	  size_t pos = file_name.find_last_of (file_ops::dir_sep_chars ());

	  std::string dir_name = file_name.substr (0, pos);

	  octave_function *fcn = load_fcn_from_file (file_name, dir_name,
						     "", name, true);

	  if (fcn)
	    autoload_function = octave_value (fcn);
	}
    }

  return autoload_function;
}

octave_value
symbol_table::fcn_info::fcn_info_rep::find_user_function (void)
{
  // Function on the path.

  if (function_on_path.is_defined ())
    out_of_date_check_internal (function_on_path);

  if (! function_on_path.is_defined ())
    {
      std::string dir_name;

      std::string file_name = load_path::find_fcn (name, dir_name);

      if (! file_name.empty ())
	{
	  octave_function *fcn = load_fcn_from_file (file_name, dir_name);

	  if (fcn)
	    function_on_path = octave_value (fcn);
	}
    }

  return function_on_path;
}

// Insert INF_CLASS in the set of class names that are considered
// inferior to SUP_CLASS.  Return FALSE if INF_CLASS is currently
// marked as superior to  SUP_CLASS.

bool
symbol_table::set_class_relationship (const std::string& sup_class,
				      const std::string& inf_class)
{
  class_precedence_table_const_iterator p
    = class_precedence_table.find (inf_class);

  if (p != class_precedence_table.end ())
    {
      const std::set<std::string>& inferior_classes = p->second;

      std::set<std::string>::const_iterator q
	= inferior_classes.find (sup_class);

      if (q != inferior_classes.end ())
	return false;
    }

  class_precedence_table[sup_class].insert (inf_class);

  return true;
}

// Has class A been marked as superior to class B?  Also returns
// TRUE if B has been marked as inferior to A, since we only keep
// one table, and convert inferiort information to a superiorto
// relationship.  Two calls are required to determine whether there
// is no relationship between two classes:
//
//  if (symbol_table::is_superiorto (a, b))
//    // A is superior to B, or B has been marked inferior to A.
//  else if (symbol_table::is_superiorto (b, a))
//    // B is superior to A, or A has been marked inferior to B.
//  else
//    // No relation.

bool
symbol_table::is_superiorto (const std::string& a, const std::string& b)
{
  bool retval = false;

  class_precedence_table_const_iterator p = class_precedence_table.find (a);

  if (p != class_precedence_table.end ())
    {
      const std::set<std::string>& inferior_classes = p->second;
      std::set<std::string>::const_iterator q = inferior_classes.find (b);

      if (q != inferior_classes.end ())
	retval = true;
    }

  return retval;
}

static std::string
fcn_file_name (const octave_value& fcn)
{
  const octave_function *f = fcn.function_value ();

  return f ? f->fcn_file_name () : std::string ();
}

void
symbol_table::fcn_info::fcn_info_rep::dump
  (std::ostream& os, const std::string& prefix) const
{
  os << prefix << name
     << " ["
     << (cmdline_function.is_defined () ? "c" : "")
     << (built_in_function.is_defined () ? "b" : "")
     << "]\n";

  std::string tprefix = prefix + "  ";

  if (autoload_function.is_defined ())
    os << tprefix << "autoload: "
       << fcn_file_name (autoload_function) << "\n";

  if (function_on_path.is_defined ())
    os << tprefix << "function from path: "
       << fcn_file_name (function_on_path) << "\n";

  if (! subfunctions.empty ())
    {
      for (scope_val_const_iterator p = subfunctions.begin ();
	   p != subfunctions.end (); p++)
	os << tprefix << "subfunction: " << fcn_file_name (p->second)
	   << " [" << p->first << "]\n";
    }

  if (! private_functions.empty ())
    {
      for (str_val_const_iterator p = private_functions.begin ();
	   p != private_functions.end (); p++)
	os << tprefix << "private: " << fcn_file_name (p->second)
	   << " [" << p->first << "]\n";
    }

  if (! class_constructors.empty ())
    {
      for (str_val_const_iterator p = class_constructors.begin ();
	   p != class_constructors.end (); p++)
	os << tprefix << "constructor: " << fcn_file_name (p->second)
	   << " [" << p->first << "]\n";
    }

  if (! class_methods.empty ())
    {
      for (str_val_const_iterator p = class_methods.begin ();
	   p != class_methods.end (); p++)
	os << tprefix << "method: " << fcn_file_name (p->second)
	   << " [" << p->first << "]\n";
    }

  if (! dispatch_map.empty ())
    {
      for (dispatch_map_const_iterator p = dispatch_map.begin ();
	   p != dispatch_map.end (); p++)
	os << tprefix << "dispatch: " << fcn_file_name (p->second)
	   << " [" << p->first << "]\n";
    }
}

octave_value
symbol_table::fcn_info::find (tree_argument_list *args,
			      const string_vector& arg_names,
			      octave_value_list& evaluated_args,
			      bool& args_evaluated)
{
  return rep->find (args, arg_names, evaluated_args, args_evaluated);
}

octave_value
symbol_table::find (const std::string& name, tree_argument_list *args,
		    const string_vector& arg_names,
		    octave_value_list& evaluated_args, bool& args_evaluated,
		    bool skip_variables)
{
  symbol_table *inst = get_instance (xcurrent_scope);

  return inst
    ? inst->do_find (name, args, arg_names, evaluated_args,
		     args_evaluated, skip_variables)
    : octave_value ();
}

octave_value
symbol_table::find_function (const std::string& name, tree_argument_list *args,
			     const string_vector& arg_names,
			     octave_value_list& evaluated_args,
			     bool& args_evaluated)
{
  octave_value retval;

  if (! name.empty () && name[0] == '@')
    {
      // Look for a class specific function.
      std::string dispatch_type = 
	name.substr (1, name.find_first_of (file_ops::dir_sep_str ()) - 1);

      std::string method = 
	name.substr (name.find_last_of (file_ops::dir_sep_str ()) + 1, 
		     std::string::npos);

      retval = find_method (method, dispatch_type);
    }
  else
    {
      size_t pos = name.find_first_of (Vfilemarker);

      if (pos == std::string::npos)
	retval = find (name, args, arg_names, evaluated_args,
		       args_evaluated, true);
      else
	{
	  std::string fcn_scope = name.substr (0, pos);
	  scope_id stored_scope = xcurrent_scope;
	  xcurrent_scope = xtop_scope;
	  octave_value parent = find_function (name.substr(0, pos));

	  if (parent.is_defined ())
	    {
	      octave_function *parent_fcn = parent.function_value ();

	      if (parent_fcn)
		{
		  xcurrent_scope = parent_fcn->scope ();

		  if (xcurrent_scope > 1)
		    retval = find_function (name.substr (pos + 1), args,
					    arg_names, evaluated_args, 
					    args_evaluated);
		}
	    }

	  xcurrent_scope = stored_scope;
	}
    }

  return retval;
}

void
symbol_table::dump (std::ostream& os, scope_id scope)
{
  if (scope == xglobal_scope)
    dump_global (os);
  else
    {
      symbol_table *inst = get_instance (scope, false);

      if (inst)
	{
	  os << "*** dumping symbol table scope " << scope
	     << " (" << inst->table_name << ")\n\n";

	  std::map<std::string, octave_value> sfuns
	    = symbol_table::subfunctions_defined_in_scope (scope);

	  if (! sfuns.empty ())
	    {
	      os << "  subfunctions defined in this scope:\n";

	      for (std::map<std::string, octave_value>::const_iterator p = sfuns.begin ();
		   p != sfuns.end (); p++)
		os << "    " << p->first << "\n";

	      os << "\n";
	    }

	  inst->do_dump (os);
	}
    }
}

void
symbol_table::dump_global (std::ostream& os)
{
  if (! global_table.empty ())
    {
      os << "*** dumping global symbol table\n\n";

      for (global_table_const_iterator p = global_table.begin ();
	   p != global_table.end (); p++)
	{
	  std::string nm = p->first;
	  octave_value val = p->second;

	  os << "  " << nm << " ";
	  val.dump (os);
	  os << "\n";
	}
    }
}

void
symbol_table::dump_functions (std::ostream& os)
{
  if (! fcn_table.empty ())
    {
      os << "*** dumping globally visible functions from symbol table\n"
	 << "    (c=commandline, b=built-in)\n\n";

      for (fcn_table_const_iterator p = fcn_table.begin ();
	   p != fcn_table.end (); p++)
	p->second.dump (os, "  ");

      os << "\n";
    }
}

void
symbol_table::stash_dir_name_for_subfunctions (scope_id scope,
					       const std::string& dir_name)
{
  // FIXME -- is this the best way to do this?  Maybe it would be
  // better if we had a map from scope to list of subfunctions
  // stored with the function.  Do we?

  for (fcn_table_const_iterator p = fcn_table.begin ();
       p != fcn_table.end (); p++)
    {
      std::pair<std::string, octave_value> tmp
	= p->second.subfunction_defined_in_scope (scope);

      std::string nm = tmp.first;

      if (! nm.empty ())
	{
	  octave_value& fcn = tmp.second;

	  octave_user_function *f = fcn.user_function_value ();

	  if (f)
	    f->stash_dir_name (dir_name);
	}
    }
}

octave_value
symbol_table::do_find (const std::string& name, tree_argument_list *args,
		       const string_vector& arg_names,
		       octave_value_list& evaluated_args,
		       bool& args_evaluated, bool skip_variables)
{
  octave_value retval;

  // Variable.

  if (! skip_variables)
    {
      table_iterator p = table.find (name);

      if (p != table.end ())
	{
	  symbol_record sr = p->second;

	  // FIXME -- should we be using something other than varref here?

	  if (sr.is_global ())
	    return symbol_table::global_varref (name);
	  else
	    {
	      octave_value& val = sr.varref ();

	      if (val.is_defined ())
		return val;
	    }
	}
    }

  fcn_table_iterator p = fcn_table.find (name);

  if (p != fcn_table.end ())
    return p->second.find (args, arg_names, evaluated_args, args_evaluated);
  else
    {
      fcn_info finfo (name);

      octave_value fcn = finfo.find (args, arg_names, evaluated_args,
				     args_evaluated);

      if (fcn.is_defined ())
	fcn_table[name] = finfo;

      return fcn;
    }

  return retval;
}

void
symbol_table::do_dump (std::ostream& os)
{
  if (! persistent_table.empty ())
    {
      os << "  persistent variables in this scope:\n\n";

      for (persistent_table_const_iterator p = persistent_table.begin ();
	   p != persistent_table.end (); p++)
	{
	  std::string nm = p->first;
	  octave_value val = p->second;

	  os << "    " << nm << " ";
	  val.dump (os);
	  os << "\n";
	}

      os << "\n";
    }

  if (! table.empty ())
    {
      os << "  other symbols in this scope (l=local; a=auto; f=formal\n"
	 << "    h=hidden; i=inherited; g=global; p=persistent)\n\n";

      for (table_const_iterator p = table.begin (); p != table.end (); p++)
	p->second.dump (os, "    ");

      os << "\n";
    }
}

DEFUN (ignore_function_time_stamp, args, nargout,
    "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {@var{val} =} ignore_function_time_stamp ()\n\
@deftypefnx {Built-in Function} {@var{old_val} =} ignore_function_time_stamp (@var{new_val})\n\
Query or set the internal variable that controls whether Octave checks\n\
the time stamp on files each time it looks up functions defined in\n\
function files.  If the internal variable is set to @code{\"system\"},\n\
Octave will not automatically recompile function files in subdirectories of\n\
@file{@var{octave-home}/lib/@var{version}} if they have changed since\n\
they were last compiled, but will recompile other function files in the\n\
search path if they change.  If set to @code{\"all\"}, Octave will not\n\
recompile any function files unless their definitions are removed with\n\
@code{clear}.  If set to \"none\", Octave will always check time stamps\n\
on files to determine whether functions defined in function files\n\
need to recompiled.\n\
@end deftypefn")
{
  octave_value retval;

  if (nargout > 0)
    {
      switch (Vignore_function_time_stamp)
	{
	case 1:
	  retval = "system";
	  break;

	case 2:
	  retval = "all";
	  break;

	default:
	  retval = "none";
	  break;
	}
    }

  int nargin = args.length ();

  if (nargin == 1)
    {
      std::string sval = args(0).string_value ();

      if (! error_state)
	{
	  if (sval == "all")
	    Vignore_function_time_stamp = 2;
	  else if (sval == "system")
	    Vignore_function_time_stamp = 1;
	  else if (sval == "none")
	    Vignore_function_time_stamp = 0;
	  else
	    error ("ignore_function_time_stamp: expecting argument to be \"all\", \"system\", or \"none\"");
	}
      else
	error ("ignore_function_time_stamp: expecting argument to be character string");
    }
  else if (nargin > 1)
    print_usage ();

  return retval;
}

DEFUN (__current_scope__, , ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {[@var{scope}, @var{context}]} __dump_symtab_info__ ()\n\
Undocumented internal function.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(1) = symbol_table::current_context ();
  retval(0) = symbol_table::current_scope ();

  return retval;
}

DEFUN (__dump_symtab_info__, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} __dump_symtab_info__ ()\n\
@deftypefnx {Built-in Function} {} __dump_symtab_info__ (@var{scope})\n\
@deftypefnx {Built-in Function} {} __dump_symtab_info__ (\"scopes\")\n\
@deftypefnx {Built-in Function} {} __dump_symtab_info__ (\"functions\")\n\
Undocumented internal function.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 0)
    {
      symbol_table::dump_functions (octave_stdout);

      symbol_table::dump_global (octave_stdout);

      std::list<symbol_table::scope_id> lst = symbol_table::scopes ();

      for (std::list<symbol_table::scope_id>::const_iterator p = lst.begin ();
	   p != lst.end (); p++)
	symbol_table::dump (octave_stdout, *p);
    }
  else if (nargin == 1)
    {
      octave_value arg = args(0);

      if (arg.is_string ())
	{
	  std::string s_arg = arg.string_value ();

	  if (s_arg == "scopes")
	    {
	      std::list<symbol_table::scope_id> lst = symbol_table::scopes ();

	      RowVector v (lst.size ());

	      octave_idx_type k = 0;

	      for (std::list<symbol_table::scope_id>::const_iterator p = lst.begin ();
		   p != lst.end (); p++)
		v.xelem (k++) = *p;

	      retval = v;
	    }
	  else if (s_arg == "functions")
	    {
	      symbol_table::dump_functions (octave_stdout);
	    }
	  else
	    error ("__dump_symtab_info__: expecting \"functions\" or \"scopes\"");
	}
      else
	{
	  int s = arg.int_value ();

	  if (! error_state)
	    symbol_table::dump (octave_stdout, s);
	  else
	    error ("__dump_symtab_info__: expecting string or scope id");
	}
    }
  else
    print_usage ();

  return retval;
}

#if 0

// FIXME -- should we have functions like this in Octave?

DEFUN (set_variable, args, , "set_variable (NAME, VALUE)")
{
  octave_value retval;

  if (args.length () == 2)
    {
      std::string name = args(0).string_value ();

      if (! error_state)
	symbol_table::varref (name) = args(1);
      else
	error ("set_variable: expecting variable name as first argument");
    }
  else
    print_usage ();

  return retval;
}

DEFUN (variable_value, args, , "VALUE = variable_value (NAME)")
{
  octave_value retval;

  if (args.length () == 1)
    {
      std::string name = args(0).string_value ();

      if (! error_state)
	{
	  retval = symbol_table::varval (name);

	  if (retval.is_undefined ())
	    error ("variable_value: `%s' is not a variable in the current scope",
		   name.c_str ());
	}
      else
	error ("variable_value: expecting variable name as first argument");
    }
  else
    print_usage ();

  return retval;
}
#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
