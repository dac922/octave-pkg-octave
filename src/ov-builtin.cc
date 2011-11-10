/*

Copyright (C) 1996, 1997, 1998, 1999, 2000, 2002, 2003, 2004, 2005,
              2006, 2007, 2008, 2009 John W. Eaton

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

#include "error.h"
#include "gripes.h"
#include "oct-obj.h"
#include "ov-builtin.h"
#include "ov.h"
#include "toplev.h"
#include "unwind-prot.h"

DEFINE_OCTAVE_ALLOCATOR (octave_builtin);

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_builtin,
				     "built-in function",
				     "built-in function");

octave_value_list
octave_builtin::subsref (const std::string& type,
			 const std::list<octave_value_list>& idx,
			 int nargout)
{
  octave_value_list retval;

  switch (type[0])
    {
    case '(':
      {
	int tmp_nargout = (type.length () > 1 && nargout == 0) ? 1 : nargout;

	retval = do_multi_index_op (tmp_nargout, idx.front ());
      }
      break;

    case '{':
    case '.':
      {
	std::string nm = type_name ();
	error ("%s cannot be indexed with %c", nm.c_str (), type[0]);
      }
      break;

    default:
      panic_impossible ();
    }

  // FIXME -- perhaps there should be an
  // octave_value_list::next_subsref member function?  See also
  // octave_user_function::subsref.
  //
  // FIXME -- Note that if a function call returns multiple
  // values, and there is further indexing to perform, then we are
  // ignoring all but the first value.  Is this really what we want to
  // do?  If it is not, then what should happen for stat("file").size,
  // for exmaple?

  if (idx.size () > 1)
    retval = retval(0).next_subsref (nargout, type, idx);

  return retval;
}

octave_value_list
octave_builtin::do_multi_index_op (int nargout, const octave_value_list& args)
{
  octave_value_list retval;

  if (error_state)
    return retval;

  if (args.has_magic_colon ())
    ::error ("invalid use of colon in function argument list");
  else
    {
      unwind_protect::begin_frame ("builtin_func_eval");

      octave_call_stack::push (this);

      unwind_protect::add (octave_call_stack::unwind_pop, 0);

      try
	{
	  retval = (*f) (args, nargout);
          // Do not allow null values to be returned from functions.
          // FIXME -- perhaps true builtins should be allowed?
          retval.make_storable_values ();
	}
      catch (octave_execution_exception)
	{
	  gripe_library_execution_error ();
	}

      unwind_protect::run_frame ("builtin_func_eval");
    }

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
