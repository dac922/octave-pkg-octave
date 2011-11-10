/*

Copyright (C) 2005, 2006, 2007, 2008, 2009 David Bateman

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

#include <algorithm>

#include "ov.h"
#include "defun-dld.h"
#include "error.h"
#include "ov-re-mat.h"
#include "ov-cx-mat.h"
#include "ov-re-sparse.h"
#include "ov-cx-sparse.h"
#include "MatrixType.h"
#include "oct-locbuf.h"

DEFUN_DLD (matrix_type, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{type} =} matrix_type (@var{a})\n\
@deftypefnx {Loadable Function} {@var{a} =} matrix_type (@var{a}, @var{type})\n\
@deftypefnx {Loadable Function} {@var{a} =} matrix_type (@var{a}, 'upper', @var{perm})\n\
@deftypefnx {Loadable Function} {@var{a} =} matrix_type (@var{a}, 'lower', @var{perm})\n\
@deftypefnx {Loadable Function} {@var{a} =} matrix_type (@var{a}, 'banded', @var{nl}, @var{nu})\n\
Identify the matrix type or mark a matrix as a particular type.  This allows rapid\n\
for solutions of linear equations involving @var{a} to be performed.  Called with a\n\
single argument, @code{matrix_type} returns the type of the matrix and caches it for\n\
future use.  Called with more than one argument, @code{matrix_type} allows the type\n\
of the matrix to be defined.\n\
\n\
The possible matrix types depend on whether the matrix is full or sparse, and can be\n\
one of the following\n\
\n\
@table @asis\n\
@item 'unknown'\n\
Remove any previously cached matrix type, and mark type as unknown\n\
\n\
@item 'full'\n\
Mark the matrix as full.\n\
\n\
@item 'positive definite'\n\
Probable full positive definite matrix.\n\
\n\
@item 'diagonal'\n\
Diagonal Matrix.  (Sparse matrices only)\n\
\n\
@item 'permuted diagonal'\n\
Permuted Diagonal matrix.  The permutation does not need to be specifically\n\
indicated, as the structure of the matrix explicitly gives this.  (Sparse matrices\n\
only)\n\
\n\
@item 'upper'\n\
Upper triangular.  If the optional third argument @var{perm} is given, the matrix is\n\
assumed to be a permuted upper triangular with the permutations defined by the\n\
vector @var{perm}.\n\
\n\
@item 'lower'\n\
Lower triangular.  If the optional third argument @var{perm} is given, the matrix is\n\
assumed to be a permuted lower triangular with the permutations defined by the\n\
vector @var{perm}.\n\
\n\
@item 'banded'\n\
@itemx 'banded positive definite'\n\
Banded matrix with the band size of @var{nl} below the diagonal and @var{nu} above\n\
it.  If @var{nl} and @var{nu} are 1, then the matrix is tridiagonal and treated\n\
with specialized code.  In addition the matrix can be marked as probably a\n\
positive definite (Sparse matrices only)\n\
\n\
@item 'singular'\n\
The matrix is assumed to be singular and will be treated with a minimum norm solution\n\
\n\
@end table\n\
\n\
Note that the matrix type will be discovered automatically on the first attempt to\n\
solve a linear equation involving @var{a}.  Therefore @code{matrix_type} is only\n\
useful to give Octave hints of the matrix type.  Incorrectly defining the\n\
matrix type will result in incorrect results from solutions of linear equations,\n\
and so it is entirely the responsibility of the user to correctly identify the\n\
matrix type.\n\
\n\
Also the test for positive definiteness is a low-cost test for a hermitian\n\
matrix with a real positive diagonal.  This does not guarantee that the matrix\n\
is positive definite, but only that it is a probable candidate.  When such a\n\
matrix is factorized, a Cholesky factorization is first attempted, and if\n\
that fails the matrix is then treated with an LU factorization.  Once the\n\
matrix has been factorized, @code{matrix_type} will return the correct\n\
classification of the matrix.\n\
@end deftypefn")
{
  int nargin = args.length ();
  octave_value retval;

  if (nargin == 0)
    print_usage ();
  else if (nargin > 4)
    error ("matrix_type: incorrect number of arguments");
  else
    {
      if (args(0).is_scalar_type())
	{
	  if (nargin == 1)
	    retval = octave_value ("Full");
	  else
	    retval = args(0);
	}
      else if (args(0).is_sparse_type ())
	{
	  if (nargin == 1)
	    {
	      MatrixType mattyp;

	      if (args(0).is_complex_type ()) 
		{
		  mattyp = args(0).matrix_type ();

		  if (mattyp.is_unknown ())
		    {
		      SparseComplexMatrix m = 
			args(0).sparse_complex_matrix_value ();
		      if (!error_state)
			{
			  mattyp = MatrixType (m);
			  args(0).matrix_type (mattyp);
			}
		    }
		}
	      else
		{
		  mattyp = args(0).matrix_type ();

		  if (mattyp.is_unknown ())
		    {
		      SparseMatrix m = args(0).sparse_matrix_value ();
		      if (!error_state)
			{
			  mattyp = MatrixType (m);
			  args(0).matrix_type (mattyp);
			}
		    }
		}

	      int typ = mattyp.type ();

	      if (typ == MatrixType::Diagonal)
		retval = octave_value ("Diagonal");
	      else if (typ == MatrixType::Permuted_Diagonal)
		retval = octave_value ("Permuted Diagonal");
	      else if (typ == MatrixType::Upper)
		retval = octave_value ("Upper");
	      else if (typ == MatrixType::Permuted_Upper)
		retval = octave_value ("Permuted Upper");
	      else if (typ == MatrixType::Lower)
		retval = octave_value ("Lower");
	      else if (typ == MatrixType::Permuted_Lower)
		retval = octave_value ("Permuted Lower");
	      else if (typ == MatrixType::Banded)
		retval = octave_value ("Banded");
	      else if (typ == MatrixType::Banded_Hermitian)
		retval = octave_value ("Banded Positive Definite");
	      else if (typ == MatrixType::Tridiagonal)
		retval = octave_value ("Tridiagonal");
	      else if (typ == MatrixType::Tridiagonal_Hermitian)
		retval = octave_value ("Tridiagonal Positive Definite");
	      else if (typ == MatrixType::Hermitian)
		retval = octave_value ("Positive Definite");
	      else if (typ == MatrixType::Rectangular)
		{
		  if (args(0).rows() == args(0).columns())
		    retval = octave_value ("Singular");
		  else
		    retval = octave_value ("Rectangular");
		}
	      else if (typ == MatrixType::Full)
		retval = octave_value ("Full");
	      else
		// This should never happen!!!
		retval = octave_value ("Unknown");
	    }
	  else
	    {
	      // Ok, we're changing the matrix type
	      std::string str_typ = args(1).string_value ();

	      // FIXME -- why do I have to explicitly call the constructor?
	      MatrixType mattyp = MatrixType ();

	      octave_idx_type nl = 0;
	      octave_idx_type nu = 0;
	      
	      if (error_state)
		error ("Matrix type must be a string");
	      else
		{
		  // Use STL function to convert to lower case
		  std::transform (str_typ.begin (), str_typ.end (),
				  str_typ.begin (), tolower);

		  if (str_typ == "diagonal")
		    mattyp.mark_as_diagonal ();
		  if (str_typ == "permuted diagonal")
		    mattyp.mark_as_permuted_diagonal ();
		  else if (str_typ == "upper")
		    mattyp.mark_as_upper_triangular ();
		  else if (str_typ == "lower")
		    mattyp.mark_as_lower_triangular ();
		  else if (str_typ == "banded" || str_typ == "banded positive definite")
		    {
		      if (nargin != 4)
			error ("matrix_type: banded matrix type requires 4 arguments");
		      else
			{
			  nl = args(2).nint_value ();
			  nu = args(3).nint_value ();

			  if (error_state)
			    error ("matrix_type: band size must be integer");
			  else
			    {
			      if (nl == 1 && nu == 1)
				mattyp.mark_as_tridiagonal ();
			      else
				mattyp.mark_as_banded (nu, nl);
			      
			      if (str_typ == "banded positive definite")
				mattyp.mark_as_symmetric ();
			    }
			}
		    }
		  else if (str_typ == "positive definite")
		    {
		      mattyp.mark_as_full ();
		      mattyp.mark_as_symmetric ();
		    }
		  else if (str_typ == "singular")
		    mattyp.mark_as_rectangular ();
		  else if (str_typ == "full")
		    mattyp.mark_as_full ();
		  else if (str_typ == "unknown")
		    mattyp.invalidate_type ();
		  else
		    error ("matrix_type: Unknown matrix type %s", str_typ.c_str());

		  if (! error_state)
		    {
		      if (nargin == 3 && (str_typ == "upper" || str_typ == "lower"))
			{
			  const ColumnVector perm = 
			    ColumnVector (args (2).vector_value ());

			  if (error_state)
			    error ("matrix_type: Invalid permutation vector");
			  else
			    {
			      octave_idx_type len = perm.length ();
			      dim_vector dv = args(0).dims ();
			      
			      if (len != dv(0))
				error ("matrix_type: Invalid permutation vector");
			      else
				{
				  OCTAVE_LOCAL_BUFFER (octave_idx_type, p, len);

				  for (octave_idx_type i = 0; i < len; i++)
				    p[i] = static_cast<octave_idx_type> (perm (i)) - 1; 

				  if (str_typ == "upper")
				    mattyp.mark_as_permuted (len, p);
				  else
				    mattyp.mark_as_permuted (len, p);
				}
			    }
			}
		      else if (nargin != 2 && str_typ != "banded positive definite" &&
			       str_typ != "banded")
			error ("matrix_type: Invalid number of arguments");

		      if (! error_state)
			{
			  // Set the matrix type
			  if (args(0).is_complex_type ())
			    retval = 
			      octave_value (args(0).sparse_complex_matrix_value (), 
					    mattyp);
			  else
			    retval = octave_value (args(0).sparse_matrix_value (), 
						   mattyp);
			}
		    }
		}
	    }
	}
      else
	{
	  if (nargin == 1)
	    {
	      MatrixType mattyp;

	      if (args(0).is_complex_type ())
		{
		  mattyp = args(0).matrix_type ();

		  if (mattyp.is_unknown ())
		    {
		      if (args(0).is_single_type ())
			{
			  FloatComplexMatrix m = args(0).float_complex_matrix_value ();
			  if (!error_state)
			    {
			      mattyp = MatrixType (m);
			      args(0).matrix_type (mattyp);
			    }
			}
		      else
			{
			  ComplexMatrix m = args(0).complex_matrix_value ();
			  if (!error_state)
			    {
			      mattyp = MatrixType (m);
			      args(0).matrix_type (mattyp);
			    }
			}
		    }
		}
	      else
		{
		  mattyp = args(0).matrix_type ();

		  if (mattyp.is_unknown ())
		    {
		      if (args(0).is_single_type ())
			{
			  FloatMatrix m = args(0).float_matrix_value ();
			  if (!error_state)
			    {
			      mattyp = MatrixType (m);
			      args(0).matrix_type (mattyp);
			    }
			}
		      else
			{
			  Matrix m = args(0).matrix_value ();
			  if (!error_state)
			    {
			      mattyp = MatrixType (m);
			      args(0).matrix_type (mattyp);
			    }
			}
		    }
		}

	      int typ = mattyp.type ();

	      if (typ == MatrixType::Upper)
		retval = octave_value ("Upper");
	      else if (typ == MatrixType::Permuted_Upper)
		retval = octave_value ("Permuted Upper");
	      else if (typ == MatrixType::Lower)
		retval = octave_value ("Lower");
	      else if (typ == MatrixType::Permuted_Lower)
		retval = octave_value ("Permuted Lower");
	      else if (typ == MatrixType::Hermitian)
		retval = octave_value ("Positive Definite");
	      else if (typ == MatrixType::Rectangular)
		{
		  if (args(0).rows() == args(0).columns())
		    retval = octave_value ("Singular");
		  else
		    retval = octave_value ("Rectangular");
		}
	      else if (typ == MatrixType::Full)
		retval = octave_value ("Full");
	      else
		// This should never happen!!!
		retval = octave_value ("Unknown");
	    }
	  else
	    {
	      // Ok, we're changing the matrix type
	      std::string str_typ = args(1).string_value ();

	      // FIXME -- why do I have to explicitly call the constructor?
	      MatrixType mattyp = MatrixType (MatrixType::Unknown, true);

	      if (error_state)
		error ("Matrix type must be a string");
	      else
		{
		  // Use STL function to convert to lower case
		  std::transform (str_typ.begin (), str_typ.end (),
				  str_typ.begin (), tolower);

		  if (str_typ == "upper")
		    mattyp.mark_as_upper_triangular ();
		  else if (str_typ == "lower")
		    mattyp.mark_as_lower_triangular ();
		  else if (str_typ == "positive definite")
		    {
		      mattyp.mark_as_full ();
		      mattyp.mark_as_symmetric ();
		    }
		  else if (str_typ == "singular")
		    mattyp.mark_as_rectangular ();
		  else if (str_typ == "full")
		    mattyp.mark_as_full ();
		  else if (str_typ == "unknown")
		    mattyp.invalidate_type ();
		  else
		    error ("matrix_type: Unknown matrix type %s", str_typ.c_str());

		  if (! error_state)
		    {
		      if (nargin == 3 && (str_typ == "upper" 
					  || str_typ == "lower"))
			{
			  const ColumnVector perm = 
			    ColumnVector (args (2).vector_value ());

			  if (error_state)
			    error ("matrix_type: Invalid permutation vector");
			  else
			    {
			      octave_idx_type len = perm.length ();
			      dim_vector dv = args(0).dims ();
			      
			      if (len != dv(0))
				error ("matrix_type: Invalid permutation vector");
			      else
				{
				  OCTAVE_LOCAL_BUFFER (octave_idx_type, p, len);

				  for (octave_idx_type i = 0; i < len; i++)
				    p[i] = static_cast<octave_idx_type> (perm (i)) - 1; 

				  if (str_typ == "upper")
				    mattyp.mark_as_permuted (len, p);
				  else
				    mattyp.mark_as_permuted (len, p);
				}
			    }
			}
		      else if (nargin != 2)
			error ("matrix_type: Invalid number of arguments");

		      if (! error_state)
			{
			  // Set the matrix type
			  if (args(0).is_single_type ())
			    {
			      if (args(0).is_complex_type())
				retval = octave_value 
				  (args(0).float_complex_matrix_value (), 
				   mattyp);
			      else
				retval = octave_value 
				  (args(0).float_matrix_value (), 
				   mattyp);
			    }
			  else
			    {
			      if (args(0).is_complex_type())
				retval = octave_value 
				  (args(0).complex_matrix_value (), 
				   mattyp);
			      else
				retval = octave_value 
				  (args(0).matrix_value (), 
				   mattyp);
			    }
			}
		    }
		}
	    }
	}
    }

  return retval;
}

/*

## FIXME
## Disable tests for lower under-determined and upper over-determined 
## matrices as this detection is disabled in MatrixType due to issues
## of non minimum norm solution being found.
 
%!assert(matrix_type(speye(10,10)),"Diagonal");
%!assert(matrix_type(speye(10,10)([2:10,1],:)),"Permuted Diagonal");
%!assert(matrix_type([[speye(10,10);sparse(1,10)],[1;sparse(9,1);1]]),"Upper");
%!assert(matrix_type([[speye(10,10);sparse(1,10)],[1;sparse(9,1);1]](:,[2,1,3:11])),"Permuted Upper");
%!assert(matrix_type([speye(10,10),sparse(10,1);1,sparse(1,9),1]),"Lower");
%!assert(matrix_type([speye(10,10),sparse(10,1);1,sparse(1,9),1]([2,1,3:11],:)),"Permuted Lower");
%!test
%! bnd=spparms("bandden");
%! spparms("bandden",0.5);
%! a = spdiags(rand(10,3)-0.5,[-1,0,1],10,10);
%! assert(matrix_type(a),"Tridiagonal");
%! assert(matrix_type(a'+a+2*speye(10)),"Tridiagonal Positive Definite");
%! spparms("bandden",bnd);
%!test
%! bnd=spparms("bandden");
%! spparms("bandden",0.5);
%! a = spdiags(randn(10,4),[-2:1],10,10);
%! assert(matrix_type(a),"Banded");
%! assert(matrix_type(a'*a),"Banded Positive Definite");
%! spparms("bandden",bnd);
%!test
%! a=[speye(10,10),[sparse(9,1);1];-1,sparse(1,9),1];
%! assert(matrix_type(a),"Full");
%! assert(matrix_type(a'*a),"Positive Definite");
%!assert(matrix_type(speye(10,11)),"Diagonal");
%!assert(matrix_type(speye(10,11)([2:10,1],:)),"Permuted Diagonal");
%!assert(matrix_type(speye(11,10)),"Diagonal");
%!assert(matrix_type(speye(11,10)([2:11,1],:)),"Permuted Diagonal");
%#!assert(matrix_type([[speye(10,10);sparse(1,10)],[[1,1];sparse(9,2);[1,1]]]),"Upper");
%#!assert(matrix_type([[speye(10,10);sparse(1,10)],[[1,1];sparse(9,2);[1,1]]](:,[2,1,3:12])),"Permuted Upper");
%!assert(matrix_type([speye(11,9),[1;sparse(8,1);1;0]]),"Upper");
%!assert(matrix_type([speye(11,9),[1;sparse(8,1);1;0]](:,[2,1,3:10])),"Permuted Upper");
%#!assert(matrix_type([speye(10,10),sparse(10,1);[1;1],sparse(2,9),[1;1]]),"Lower");
%#!assert(matrix_type([speye(10,10),sparse(10,1);[1;1],sparse(2,9),[1;1]]([2,1,3:12],:)),"Permuted Lower");
%!assert(matrix_type([speye(9,11);[1,sparse(1,8),1,0]]),"Lower");
%!assert(matrix_type([speye(9,11);[1,sparse(1,8),1,0]]([2,1,3:10],:)),"Permuted Lower");
%!assert(matrix_type(spdiags(randn(10,4),[-2:1],10,9)),"Rectangular")

%!assert(matrix_type(1i*speye(10,10)),"Diagonal");
%!assert(matrix_type(1i*speye(10,10)([2:10,1],:)),"Permuted Diagonal");
%!assert(matrix_type([[speye(10,10);sparse(1,10)],[1i;sparse(9,1);1]]),"Upper");
%!assert(matrix_type([[speye(10,10);sparse(1,10)],[1i;sparse(9,1);1]](:,[2,1,3:11])),"Permuted Upper");
%!assert(matrix_type([speye(10,10),sparse(10,1);1i,sparse(1,9),1]),"Lower");
%!assert(matrix_type([speye(10,10),sparse(10,1);1i,sparse(1,9),1]([2,1,3:11],:)),"Permuted Lower");
%!test
%! bnd=spparms("bandden");
%! spparms("bandden",0.5);
%! assert(matrix_type(spdiags(1i*randn(10,3),[-1,0,1],10,10)),"Tridiagonal");
%! a = 1i*(rand(9,1)-0.5);a=[[a;0],ones(10,1),[0;-a]];
%! assert(matrix_type(spdiags(a,[-1,0,1],10,10)),"Tridiagonal Positive Definite");
%! spparms("bandden",bnd);
%!test
%! bnd=spparms("bandden");
%! spparms("bandden",0.5);
%! assert(matrix_type(spdiags(1i*randn(10,4),[-2:1],10,10)),"Banded");
%! a = 1i*(rand(9,2)-0.5);a=[[a;[0,0]],ones(10,1),[[0;-a(:,2)],[0;0;-a(1:8,1)]]];
%! assert(matrix_type(spdiags(a,[-2:2],10,10)),"Banded Positive Definite");
%! spparms("bandden",bnd);
%!test
%! a=[speye(10,10),[sparse(9,1);1i];-1,sparse(1,9),1];
%! assert(matrix_type(a),"Full");
%! assert(matrix_type(a'*a),"Positive Definite");
%!assert(matrix_type(1i*speye(10,11)),"Diagonal");
%!assert(matrix_type(1i*speye(10,11)([2:10,1],:)),"Permuted Diagonal");
%!assert(matrix_type(1i*speye(11,10)),"Diagonal");
%!assert(matrix_type(1i*speye(11,10)([2:11,1],:)),"Permuted Diagonal");
%#!assert(matrix_type([[speye(10,10);sparse(1,10)],[[1i,1i];sparse(9,2);[1i,1i]]]),"Upper");
%#!assert(matrix_type([[speye(10,10);sparse(1,10)],[[1i,1i];sparse(9,2);[1i,1i]]](:,[2,1,3:12])),"Permuted Upper");
%!assert(matrix_type([speye(11,9),[1i;sparse(8,1);1i;0]]),"Upper");
%!assert(matrix_type([speye(11,9),[1i;sparse(8,1);1i;0]](:,[2,1,3:10])),"Permuted Upper");
%#!assert(matrix_type([speye(10,10),sparse(10,1);[1i;1i],sparse(2,9),[1i;1i]]),"Lower");
%#!assert(matrix_type([speye(10,10),sparse(10,1);[1i;1i],sparse(2,9),[1i;1i]]([2,1,3:12],:)),"Permuted Lower");
%!assert(matrix_type([speye(9,11);[1i,sparse(1,8),1i,0]]),"Lower");
%!assert(matrix_type([speye(9,11);[1i,sparse(1,8),1i,0]]([2,1,3:10],:)),"Permuted Lower");
%!assert(matrix_type(1i*spdiags(randn(10,4),[-2:1],10,9)),"Rectangular")

%!test
%! a = matrix_type(spdiags(randn(10,3),[-1,0,1],10,10),"Singular");
%! assert(matrix_type(a),"Singular");

%!assert(matrix_type(triu(ones(10,10))),"Upper");
%!assert(matrix_type(triu(ones(10,10),-1)),"Full");
%!assert(matrix_type(tril(ones(10,10))),"Lower");
%!assert(matrix_type(tril(ones(10,10),1)),"Full");
%!assert(matrix_type(10*eye(10,10) + ones(10,10)), "Positive Definite"); 
%!assert(matrix_type(ones(11,10)),"Rectangular")
%!test
%! a = matrix_type(ones(10,10),"Singular");
%! assert(matrix_type(a),"Singular");

%!assert(matrix_type(triu(1i*ones(10,10))),"Upper");
%!assert(matrix_type(triu(1i*ones(10,10),-1)),"Full");
%!assert(matrix_type(tril(1i*ones(10,10))),"Lower");
%!assert(matrix_type(tril(1i*ones(10,10),1)),"Full");
%!assert(matrix_type(10*eye(10,10) + 1i*triu(ones(10,10),1) -1i*tril(ones(10,10),-1)), "Positive Definite"); 
%!assert(matrix_type(ones(11,10)),"Rectangular")
%!test
%! a = matrix_type(ones(10,10),"Singular");
%! assert(matrix_type(a),"Singular");

*/

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
