/*

Copyright (C) 1996, 1997, 1998, 2000, 2001, 2002, 2003, 2004, 2005,
              2006, 2007, 2008 John W. Eaton

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

#include <iostream>

#include "lo-ieee.h"
#include "lo-specfun.h"
#include "lo-mappers.h"

#include "oct-obj.h"
#include "oct-stream.h"
#include "ops.h"
#include "ov-complex.h"
#include "ov-flt-complex.h"
#include "ov-base.h"
#include "ov-base-scalar.h"
#include "ov-base-scalar.cc"
#include "ov-cx-mat.h"
#include "ov-scalar.h"
#include "gripes.h"
#include "pr-output.h"
#include "ops.h"

#include "ls-oct-ascii.h"
#include "ls-hdf5.h"

template class octave_base_scalar<Complex>;

DEFINE_OCTAVE_ALLOCATOR (octave_complex);

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_complex,
				     "complex scalar", "double");

static octave_base_value *
default_numeric_demotion_function (const octave_base_value& a)
{
  CAST_CONV_ARG (const octave_complex&);

  return new octave_float_complex (v.float_complex_value ());
}

octave_base_value::type_conv_info
octave_complex::numeric_demotion_function (void) const
{
  return octave_base_value::type_conv_info(default_numeric_demotion_function,
                                           octave_float_complex::static_type_id ());
}

octave_base_value *
octave_complex::try_narrowing_conversion (void)
{
  octave_base_value *retval = 0;

  double im = std::imag (scalar);

  if (im == 0.0 && ! lo_ieee_signbit (im))
    retval = new octave_scalar (std::real (scalar));

  return retval;
}

octave_value
octave_complex::do_index_op (const octave_value_list& idx, bool resize_ok)
{
  // FIXME -- this doesn't solve the problem of
  //
  //   a = i; a([1,1], [1,1], [1,1])
  //
  // and similar constructions.  Hmm...

  // FIXME -- using this constructor avoids narrowing the
  // 1x1 matrix back to a scalar value.  Need a better solution
  // to this problem.

  octave_value tmp (new octave_complex_matrix (complex_matrix_value ()));

  return tmp.do_index_op (idx, resize_ok);
}

double
octave_complex::double_value (bool force_conversion) const
{
  double retval = lo_ieee_nan_value ();

  if (! force_conversion)
    gripe_implicit_conversion ("Octave:imag-to-real",
			       "complex scalar", "real scalar");

  retval = std::real (scalar);

  return retval;
}

float
octave_complex::float_value (bool force_conversion) const
{
  float retval = lo_ieee_float_nan_value ();

  if (! force_conversion)
    gripe_implicit_conversion ("Octave:imag-to-real",
			       "complex scalar", "real scalar");

  retval = std::real (scalar);

  return retval;
}

Matrix
octave_complex::matrix_value (bool force_conversion) const
{
  Matrix retval;

  if (! force_conversion)
    gripe_implicit_conversion ("Octave:imag-to-real",
			       "complex scalar", "real matrix");

  retval = Matrix (1, 1, std::real (scalar));

  return retval;
}

FloatMatrix
octave_complex::float_matrix_value (bool force_conversion) const
{
  FloatMatrix retval;

  if (! force_conversion)
    gripe_implicit_conversion ("Octave:imag-to-real",
			       "complex scalar", "real matrix");

  retval = FloatMatrix (1, 1, std::real (scalar));

  return retval;
}

NDArray
octave_complex::array_value (bool force_conversion) const
{
  NDArray retval;

  if (! force_conversion)
    gripe_implicit_conversion ("Octave:imag-to-real",
			       "complex scalar", "real matrix");

  retval = NDArray (dim_vector (1, 1), std::real (scalar));

  return retval;
}

FloatNDArray
octave_complex::float_array_value (bool force_conversion) const
{
  FloatNDArray retval;

  if (! force_conversion)
    gripe_implicit_conversion ("Octave:imag-to-real",
			       "complex scalar", "real matrix");

  retval = FloatNDArray (dim_vector (1, 1), std::real (scalar));

  return retval;
}

Complex
octave_complex::complex_value (bool) const
{
  return scalar;
}

FloatComplex
octave_complex::float_complex_value (bool) const
{
  return static_cast<FloatComplex> (scalar);
}

ComplexMatrix
octave_complex::complex_matrix_value (bool) const
{
  return ComplexMatrix (1, 1, scalar);
}

FloatComplexMatrix
octave_complex::float_complex_matrix_value (bool) const
{
  return FloatComplexMatrix (1, 1, static_cast<FloatComplex> (scalar));
}

ComplexNDArray
octave_complex::complex_array_value (bool /* force_conversion */) const
{
  return ComplexNDArray (dim_vector (1, 1), scalar);
}

FloatComplexNDArray
octave_complex::float_complex_array_value (bool /* force_conversion */) const
{
  return FloatComplexNDArray (dim_vector (1, 1), static_cast<FloatComplex> (scalar));
}

octave_value 
octave_complex::resize (const dim_vector& dv, bool fill) const
{
  if (fill)
    {
      ComplexNDArray retval (dv, ComplexNDArray::resize_fill_value ());

      if (dv.numel ())
	retval(0) = scalar;

      return retval;
    }
  else
    {
      ComplexNDArray retval (dv);

      if (dv.numel ())
	retval(0) = scalar;

      return retval;
    }
}

bool 
octave_complex::save_ascii (std::ostream& os)
{
  Complex c = complex_value ();

  octave_write_complex (os, c);

  os << "\n";

  return true;
}

bool 
octave_complex::load_ascii (std::istream& is)
{
  scalar = octave_read_complex (is);

  if (!is) 
    {
      error ("load: failed to load complex scalar constant");
      return false;
    }

  return true;
}


bool 
octave_complex::save_binary (std::ostream& os, bool& /* save_as_floats */)
{
  char tmp = static_cast<char> (LS_DOUBLE);
  os.write (reinterpret_cast<char *> (&tmp), 1);
  Complex ctmp = complex_value ();
  os.write (reinterpret_cast<char *> (&ctmp), 16);

  return true;
}

bool 
octave_complex::load_binary (std::istream& is, bool swap,
			     oct_mach_info::float_format fmt)
{
  char tmp;
  if (! is.read (reinterpret_cast<char *> (&tmp), 1))
    return false;

  Complex ctmp;
  read_doubles (is, reinterpret_cast<double *> (&ctmp),
		static_cast<save_type> (tmp), 2, swap, fmt);
  if (error_state || ! is)
    return false;

  scalar = ctmp;
  return true;
}

#if defined (HAVE_HDF5)

bool
octave_complex::save_hdf5 (hid_t loc_id, const char *name,
			   bool /* save_as_floats */)
{
  hsize_t dimens[3];
  hid_t space_hid = -1, type_hid = -1, data_hid = -1;
  bool retval = true;

  space_hid = H5Screate_simple (0, dimens, 0);
  if (space_hid < 0)
    return false;

  type_hid = hdf5_make_complex_type (H5T_NATIVE_DOUBLE);
  if (type_hid < 0) 
    {
      H5Sclose (space_hid);
      return false;
    }

  data_hid = H5Dcreate (loc_id, name, type_hid, space_hid, H5P_DEFAULT);
  if (data_hid < 0) 
    {
      H5Sclose (space_hid);
      H5Tclose (type_hid);
      return false;
    }

  Complex tmp = complex_value ();
  retval = H5Dwrite (data_hid, type_hid, H5S_ALL, H5S_ALL, H5P_DEFAULT, 
		     &tmp) >= 0;

  H5Dclose (data_hid);
  H5Tclose (type_hid);
  H5Sclose (space_hid);

  return retval;
}

bool
octave_complex::load_hdf5 (hid_t loc_id, const char *name,
			   bool /* have_h5giterate_bug */)
{
  bool retval = false;
  hid_t data_hid = H5Dopen (loc_id, name);
  hid_t type_hid = H5Dget_type (data_hid);

  hid_t complex_type = hdf5_make_complex_type (H5T_NATIVE_DOUBLE);

  if (! hdf5_types_compatible (type_hid, complex_type))
    {
      H5Tclose (complex_type);
      H5Dclose (data_hid);
      return false;
    }

  hid_t space_id = H5Dget_space (data_hid);
  hsize_t rank = H5Sget_simple_extent_ndims (space_id);

  if (rank != 0) 
    {
      H5Tclose (complex_type);
      H5Sclose (space_id);
      H5Dclose (data_hid);
      return false;
    }

  // complex scalar:
  Complex ctmp;
  if (H5Dread (data_hid, complex_type, H5S_ALL, H5S_ALL, H5P_DEFAULT,
	       &ctmp) >= 0)
    {
      retval = true;
      scalar = ctmp;
    }

  H5Tclose (complex_type);
  H5Sclose (space_id);
  H5Dclose (data_hid);

  return retval;
}

#endif

mxArray *
octave_complex::as_mxArray (void) const
{
  mxArray *retval = new mxArray (mxDOUBLE_CLASS, 1, 1, mxCOMPLEX);

  double *pr = static_cast<double *> (retval->get_data ());
  double *pi = static_cast<double *> (retval->get_imag_data ());

  pr[0] = std::real (scalar);
  pi[0] = std::imag (scalar);

  return retval;
}

static double
xabs (const Complex& x)
{
  return (xisinf (x.real ()) || xisinf (x.imag ())) ? octave_Inf : abs (x);
}

static double
ximag (const Complex& x)
{
  return x.imag ();
}

static double
xreal (const Complex& x)
{
  return x.real ();
}

#define COMPLEX_MAPPER(MAP, FCN)	\
  octave_value \
  octave_complex::MAP (void) const \
  { \
    return octave_value (FCN (scalar)); \
  }

#define SCALAR_MAPPER(MAP, FCN)	\
  octave_value \
  octave_complex::MAP (void) const \
  { \
    if (scalar.imag () == 0) \
      return octave_value (FCN (scalar.real ())); \
    else \
      { \
        error ("%s: not defined for complex arguments", #MAP); \
        return octave_value (); \
      } \
  }

#define CD_SCALAR_MAPPER(MAP, RFCN, CFCN, L1, L2) \
  octave_value \
  octave_complex::MAP (void) const \
  { \
    if (scalar.imag () == 0) \
      { \
	double re = scalar.real (); \
	return (re < L1 || re > L2 \
            ? octave_value (CFCN (scalar)) \
	    : octave_value (RFCN (re))); \
      } \
    else \
      { \
        error ("%s: not defined for complex arguments", #MAP); \
        return octave_value (); \
      } \
  }

SCALAR_MAPPER (erf, ::erf)
SCALAR_MAPPER (erfc, ::erfc)
SCALAR_MAPPER (gamma, xgamma)
CD_SCALAR_MAPPER (lgamma, xlgamma, xlgamma, 0.0, octave_Inf)

COMPLEX_MAPPER (abs, xabs)
COMPLEX_MAPPER (acos, ::acos)
COMPLEX_MAPPER (acosh, ::acosh)
COMPLEX_MAPPER (angle, std::arg)
COMPLEX_MAPPER (arg, std::arg)
COMPLEX_MAPPER (asin, ::asin)
COMPLEX_MAPPER (asinh, ::asinh)
COMPLEX_MAPPER (atan, ::atan)
COMPLEX_MAPPER (atanh, ::atanh)
COMPLEX_MAPPER (ceil, ::ceil)
COMPLEX_MAPPER (conj, std::conj)
COMPLEX_MAPPER (cos, std::cos)
COMPLEX_MAPPER (cosh, std::cosh)
COMPLEX_MAPPER (exp, std::exp)
COMPLEX_MAPPER (expm1, ::expm1)
COMPLEX_MAPPER (fix, ::fix)
COMPLEX_MAPPER (floor, ::floor)
COMPLEX_MAPPER (imag, ximag)
COMPLEX_MAPPER (log, std::log)
COMPLEX_MAPPER (log2, xlog2)
COMPLEX_MAPPER (log10, std::log10)
COMPLEX_MAPPER (log1p, ::log1p)
COMPLEX_MAPPER (real, xreal)
COMPLEX_MAPPER (round, xround)
COMPLEX_MAPPER (roundb, xroundb)
COMPLEX_MAPPER (signum, ::signum)
COMPLEX_MAPPER (sin, std::sin)
COMPLEX_MAPPER (sinh, std::sinh)
COMPLEX_MAPPER (sqrt, std::sqrt)
COMPLEX_MAPPER (tan, std::tan)
COMPLEX_MAPPER (tanh, std::tanh)
COMPLEX_MAPPER (finite, xfinite)
COMPLEX_MAPPER (isinf, xisinf)
COMPLEX_MAPPER (isna, octave_is_NA)
COMPLEX_MAPPER (isnan, xisnan)

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
