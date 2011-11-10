/*

Copyright (C) 1996, 1997, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
              2007, 2008 John W. Eaton

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

#include "mx-fcm-fm.h"
#include "mx-fm-fcm.h"
#include "mx-fcnda-fnda.h"
#include "mx-fnda-fcnda.h"

#include "gripes.h"
#include "oct-obj.h"
#include "ov.h"
#include "ov-cx-mat.h"
#include "ov-flt-cx-mat.h"
#include "ov-flt-re-mat.h"
#include "ov-re-mat.h"
#include "ov-typeinfo.h"
#include "ops.h"
#include "xdiv.h"
#include "xpow.h"

// complex matrix by matrix ops.

DEFNDBINOP_OP (add, float_complex_matrix, float_matrix, float_complex_array, float_array, +)
DEFNDBINOP_OP (sub, float_complex_matrix, float_matrix, float_complex_array, float_array, -)

DEFBINOP_OP (mul, float_complex_matrix, float_matrix, *)

DEFBINOP (div, float_complex_matrix, float_matrix)
{
  CAST_BINOP_ARGS (const octave_float_complex_matrix&, 
		   const octave_float_matrix&);
  MatrixType typ = v2.matrix_type ();
  
  FloatComplexMatrix ret = xdiv (v1.float_complex_matrix_value (), 
				 v2.float_matrix_value (), typ);

  v2.matrix_type (typ);
  return ret;
}


DEFBINOPX (pow, float_complex_matrix, float_matrix)
{
  error ("can't do A ^ B for A and B both matrices");
  return octave_value ();
}

DEFBINOP (ldiv, float_complex_matrix, float_matrix)
{
  CAST_BINOP_ARGS (const octave_float_complex_matrix&, 
		   const octave_float_matrix&);
  MatrixType typ = v1.matrix_type ();
  
  FloatComplexMatrix ret = xleftdiv (v1.float_complex_matrix_value (), 
				     v2.float_matrix_value (), typ);

  v1.matrix_type (typ);
  return ret;
}

DEFNDBINOP_FN (lt, float_complex_matrix, float_matrix, 
	       float_complex_array, float_array, mx_el_lt)
DEFNDBINOP_FN (le, float_complex_matrix, float_matrix, 
	       float_complex_array, float_array, mx_el_le)
DEFNDBINOP_FN (eq, float_complex_matrix, float_matrix, 
	       float_complex_array, float_array, mx_el_eq)
DEFNDBINOP_FN (ge, float_complex_matrix, float_matrix, 
	       float_complex_array, float_array, mx_el_ge)
DEFNDBINOP_FN (gt, float_complex_matrix, float_matrix, 
	       float_complex_array, float_array, mx_el_gt)
DEFNDBINOP_FN (ne, float_complex_matrix, float_matrix, 
	       float_complex_array, float_array, mx_el_ne)

DEFNDBINOP_FN (el_mul, float_complex_matrix, float_matrix, 
	       float_complex_array, float_array, product)
DEFNDBINOP_FN (el_div, float_complex_matrix, float_matrix, 
	       float_complex_array, float_array, quotient)
DEFNDBINOP_FN (el_pow, float_complex_matrix, float_matrix, 
	       float_complex_array, float_array, elem_xpow)

DEFBINOP (el_ldiv, float_complex_matrix, float_matrix)
{
  CAST_BINOP_ARGS (const octave_float_complex_matrix&, 
		   const octave_float_matrix&);

  return quotient (v2.float_array_value (), v1.float_complex_array_value ());
}

DEFNDBINOP_FN (el_and, float_complex_matrix, float_matrix, 
	       float_complex_array, float_array, mx_el_and)
DEFNDBINOP_FN (el_or,  float_complex_matrix, float_matrix, 
	       float_complex_array, float_array, mx_el_or)

DEFNDCATOP_FN (fcm_fm, float_complex_matrix, float_matrix, 
	       float_complex_array, float_array, concat)

DEFNDCATOP_FN (cm_fm, complex_matrix, float_matrix, 
	       float_complex_array, float_array, concat)

DEFNDCATOP_FN (fcm_m, float_complex_matrix, matrix, 
	       float_complex_array, float_array, concat)

DEFNDASSIGNOP_FN (assign, float_complex_matrix, float_matrix, 
		  float_complex_array, assign)
DEFNDASSIGNOP_FN (dbl_assign, complex_matrix, float_matrix, 
		  complex_array, assign)

void
install_fcm_fm_ops (void)
{
  INSTALL_BINOP (op_add, octave_float_complex_matrix, octave_float_matrix, add);
  INSTALL_BINOP (op_sub, octave_float_complex_matrix, octave_float_matrix, sub);
  INSTALL_BINOP (op_mul, octave_float_complex_matrix, octave_float_matrix, mul);
  INSTALL_BINOP (op_div, octave_float_complex_matrix, octave_float_matrix, div);
  INSTALL_BINOP (op_pow, octave_float_complex_matrix, octave_float_matrix, pow);
  INSTALL_BINOP (op_ldiv, octave_float_complex_matrix, 
		 octave_float_matrix, ldiv);
  INSTALL_BINOP (op_lt, octave_float_complex_matrix, octave_float_matrix, lt);
  INSTALL_BINOP (op_le, octave_float_complex_matrix, octave_float_matrix, le);
  INSTALL_BINOP (op_eq, octave_float_complex_matrix, octave_float_matrix, eq);
  INSTALL_BINOP (op_ge, octave_float_complex_matrix, octave_float_matrix, ge);
  INSTALL_BINOP (op_gt, octave_float_complex_matrix, octave_float_matrix, gt);
  INSTALL_BINOP (op_ne, octave_float_complex_matrix, octave_float_matrix, ne);
  INSTALL_BINOP (op_el_mul, octave_float_complex_matrix, 
		 octave_float_matrix, el_mul);
  INSTALL_BINOP (op_el_div, octave_float_complex_matrix, 
		 octave_float_matrix, el_div);
  INSTALL_BINOP (op_el_pow, octave_float_complex_matrix, 
		 octave_float_matrix, el_pow);
  INSTALL_BINOP (op_el_ldiv, octave_float_complex_matrix, 
		 octave_float_matrix, el_ldiv);
  INSTALL_BINOP (op_el_and, octave_float_complex_matrix, 
		 octave_float_matrix, el_and);
  INSTALL_BINOP (op_el_or, octave_float_complex_matrix, 
		 octave_float_matrix, el_or);

  INSTALL_CATOP (octave_float_complex_matrix, octave_float_matrix, fcm_fm);
  INSTALL_CATOP (octave_complex_matrix, octave_float_matrix, cm_fm);
  INSTALL_CATOP (octave_float_complex_matrix, octave_matrix, fcm_m);

  INSTALL_ASSIGNOP (op_asn_eq, octave_float_complex_matrix, 
		    octave_float_matrix, assign);
  INSTALL_ASSIGNOP (op_asn_eq, octave_complex_matrix, 
		    octave_float_matrix, dbl_assign);
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
