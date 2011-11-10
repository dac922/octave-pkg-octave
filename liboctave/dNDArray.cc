// N-D Array  manipulations.
/*

Copyright (C) 1996, 1997, 2003, 2004, 2005, 2006, 2007, 2008,
              2009 John W. Eaton

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

#include <cfloat>

#include <vector>

#include "Array-util.h"
#include "dNDArray.h"
#include "functor.h"
#include "mx-base.h"
#include "f77-fcn.h"
#include "lo-error.h"
#include "lo-ieee.h"
#include "lo-mappers.h"
#include "oct-locbuf.h"
#include "mx-op-defs.h"

#if defined (HAVE_FFTW3)
#include "oct-fftw.h"
#endif

NDArray::NDArray (const Array<octave_idx_type>& a, bool zero_based,
		  bool negative_to_nan)
{
  const octave_idx_type *pa = a.fortran_vec ();
  resize (a.dims ());
  double *ptmp = fortran_vec ();
  if (negative_to_nan)
    {
      double nan_val = lo_ieee_nan_value ();

      if (zero_based)
	for (octave_idx_type i = 0; i < a.numel (); i++)
	  {
	    double val = static_cast<double> 
	      (pa[i] + static_cast<octave_idx_type> (1));
	    if (val <= 0)
	      ptmp[i] = nan_val;
	    else
	      ptmp[i] = val;
	  }
      else
	for (octave_idx_type i = 0; i < a.numel (); i++)
	  {
	    double val = static_cast<double> (pa[i]);
	    if (val <= 0)
	      ptmp[i] = nan_val;
	    else
	      ptmp[i] = val;
	  }
    }
  else
    {
      if (zero_based)
	for (octave_idx_type i = 0; i < a.numel (); i++)
	  ptmp[i] = static_cast<double> 
	    (pa[i] + static_cast<octave_idx_type> (1));
      else
	for (octave_idx_type i = 0; i < a.numel (); i++)
	  ptmp[i] = static_cast<double> (pa[i]);
    }
}

NDArray::NDArray (const charNDArray& a)
  : MArrayN<double> (a.dims ())
{
  octave_idx_type n = a.numel ();
  for (octave_idx_type i = 0; i < n; i++)
    xelem (i) = static_cast<unsigned char> (a(i));
}

#if defined (HAVE_FFTW3)

ComplexNDArray
NDArray::fourier (int dim) const
{
  dim_vector dv = dims ();

  if (dim > dv.length () || dim < 0)
    return ComplexNDArray ();

  octave_idx_type stride = 1;
  octave_idx_type n = dv(dim);

  for (int i = 0; i < dim; i++)
    stride *= dv(i);

  octave_idx_type howmany = numel () / dv (dim);
  howmany = (stride == 1 ? howmany : (howmany > stride ? stride : howmany));
  octave_idx_type nloop = (stride == 1 ? 1 : numel () / dv (dim) / stride);
  octave_idx_type dist = (stride == 1 ? n : 1);

  const double *in (fortran_vec ());
  ComplexNDArray retval (dv);
  Complex *out (retval.fortran_vec ());

  // Need to be careful here about the distance between fft's
  for (octave_idx_type k = 0; k < nloop; k++)
    octave_fftw::fft (in + k * stride * n, out + k * stride * n, 
		      n, howmany, stride, dist);

  return retval;
}

ComplexNDArray
NDArray::ifourier (int dim) const
{
  dim_vector dv = dims ();

  if (dim > dv.length () || dim < 0)
    return ComplexNDArray ();

  octave_idx_type stride = 1;
  octave_idx_type n = dv(dim);

  for (int i = 0; i < dim; i++)
    stride *= dv(i);

  octave_idx_type howmany = numel () / dv (dim);
  howmany = (stride == 1 ? howmany : (howmany > stride ? stride : howmany));
  octave_idx_type nloop = (stride == 1 ? 1 : numel () / dv (dim) / stride);
  octave_idx_type dist = (stride == 1 ? n : 1);

  ComplexNDArray retval (*this);
  Complex *out (retval.fortran_vec ());

  // Need to be careful here about the distance between fft's
  for (octave_idx_type k = 0; k < nloop; k++)
    octave_fftw::ifft (out + k * stride * n, out + k * stride * n, 
		      n, howmany, stride, dist);

  return retval;
}

ComplexNDArray
NDArray::fourier2d (void) const
{
  dim_vector dv = dims();
  if (dv.length () < 2)
    return ComplexNDArray ();

  dim_vector dv2(dv(0), dv(1));
  const double *in = fortran_vec ();
  ComplexNDArray retval (dv);
  Complex *out = retval.fortran_vec ();
  octave_idx_type howmany = numel() / dv(0) / dv(1);
  octave_idx_type dist = dv(0) * dv(1);

  for (octave_idx_type i=0; i < howmany; i++)
    octave_fftw::fftNd (in + i*dist, out + i*dist, 2, dv2);

  return retval;
}

ComplexNDArray
NDArray::ifourier2d (void) const
{
  dim_vector dv = dims();
  if (dv.length () < 2)
    return ComplexNDArray ();

  dim_vector dv2(dv(0), dv(1));
  ComplexNDArray retval (*this);
  Complex *out = retval.fortran_vec ();
  octave_idx_type howmany = numel() / dv(0) / dv(1);
  octave_idx_type dist = dv(0) * dv(1);

  for (octave_idx_type i=0; i < howmany; i++)
    octave_fftw::ifftNd (out + i*dist, out + i*dist, 2, dv2);

  return retval;
}

ComplexNDArray
NDArray::fourierNd (void) const
{
  dim_vector dv = dims ();
  int rank = dv.length ();

  const double *in (fortran_vec ());
  ComplexNDArray retval (dv);
  Complex *out (retval.fortran_vec ());

  octave_fftw::fftNd (in, out, rank, dv);

  return retval;
}

ComplexNDArray
NDArray::ifourierNd (void) const
{
  dim_vector dv = dims ();
  int rank = dv.length ();

  ComplexNDArray tmp (*this);
  Complex *in (tmp.fortran_vec ());
  ComplexNDArray retval (dv);
  Complex *out (retval.fortran_vec ());

  octave_fftw::ifftNd (in, out, rank, dv);

  return retval;
}

#else

extern "C"
{
  // Note that the original complex fft routines were not written for
  // double complex arguments.  They have been modified by adding an
  // implicit double precision (a-h,o-z) statement at the beginning of
  // each subroutine.

  F77_RET_T
  F77_FUNC (zffti, ZFFTI) (const octave_idx_type&, Complex*);

  F77_RET_T
  F77_FUNC (zfftf, ZFFTF) (const octave_idx_type&, Complex*, Complex*);

  F77_RET_T
  F77_FUNC (zfftb, ZFFTB) (const octave_idx_type&, Complex*, Complex*);
}

ComplexNDArray
NDArray::fourier (int dim) const
{
  dim_vector dv = dims ();

  if (dim > dv.length () || dim < 0)
    return ComplexNDArray ();

  ComplexNDArray retval (dv);
  octave_idx_type npts = dv(dim);
  octave_idx_type nn = 4*npts+15;
  Array<Complex> wsave (nn);
  Complex *pwsave = wsave.fortran_vec ();

  OCTAVE_LOCAL_BUFFER (Complex, tmp, npts);

  octave_idx_type stride = 1;

  for (int i = 0; i < dim; i++)
    stride *= dv(i);

  octave_idx_type howmany = numel () / npts;
  howmany = (stride == 1 ? howmany : (howmany > stride ? stride : howmany));
  octave_idx_type nloop = (stride == 1 ? 1 : numel () / npts / stride);
  octave_idx_type dist = (stride == 1 ? npts : 1);

  F77_FUNC (zffti, ZFFTI) (npts, pwsave);

  for (octave_idx_type k = 0; k < nloop; k++)
    {
      for (octave_idx_type j = 0; j < howmany; j++)
	{
	  OCTAVE_QUIT;

	  for (octave_idx_type i = 0; i < npts; i++)
	    tmp[i] = elem((i + k*npts)*stride + j*dist);

	  F77_FUNC (zfftf, ZFFTF) (npts, tmp, pwsave);

	  for (octave_idx_type i = 0; i < npts; i++)
	    retval ((i + k*npts)*stride + j*dist) = tmp[i];
	}
    }

  return retval;
}

ComplexNDArray
NDArray::ifourier (int dim) const
{
  dim_vector dv = dims ();

  if (dim > dv.length () || dim < 0)
    return ComplexNDArray ();

  ComplexNDArray retval (dv);
  octave_idx_type npts = dv(dim);
  octave_idx_type nn = 4*npts+15;
  Array<Complex> wsave (nn);
  Complex *pwsave = wsave.fortran_vec ();

  OCTAVE_LOCAL_BUFFER (Complex, tmp, npts);

  octave_idx_type stride = 1;

  for (int i = 0; i < dim; i++)
    stride *= dv(i);

  octave_idx_type howmany = numel () / npts;
  howmany = (stride == 1 ? howmany : (howmany > stride ? stride : howmany));
  octave_idx_type nloop = (stride == 1 ? 1 : numel () / npts / stride);
  octave_idx_type dist = (stride == 1 ? npts : 1);

  F77_FUNC (zffti, ZFFTI) (npts, pwsave);

  for (octave_idx_type k = 0; k < nloop; k++)
    {
      for (octave_idx_type j = 0; j < howmany; j++)
	{
	  OCTAVE_QUIT;

	  for (octave_idx_type i = 0; i < npts; i++)
	    tmp[i] = elem((i + k*npts)*stride + j*dist);

	  F77_FUNC (zfftb, ZFFTB) (npts, tmp, pwsave);

	  for (octave_idx_type i = 0; i < npts; i++)
	    retval ((i + k*npts)*stride + j*dist) = tmp[i] / 
	      static_cast<double> (npts);
	}
    }

  return retval;
}

ComplexNDArray
NDArray::fourier2d (void) const
{
  dim_vector dv = dims();
  dim_vector dv2 (dv(0), dv(1));
  int rank = 2;
  ComplexNDArray retval (*this);
  octave_idx_type stride = 1;

  for (int i = 0; i < rank; i++)
    {
      octave_idx_type npts = dv2(i);
      octave_idx_type nn = 4*npts+15;
      Array<Complex> wsave (nn);
      Complex *pwsave = wsave.fortran_vec ();
      Array<Complex> row (npts);
      Complex *prow = row.fortran_vec ();

      octave_idx_type howmany = numel () / npts;
      howmany = (stride == 1 ? howmany : 
		 (howmany > stride ? stride : howmany));
      octave_idx_type nloop = (stride == 1 ? 1 : numel () / npts / stride);
      octave_idx_type dist = (stride == 1 ? npts : 1);

      F77_FUNC (zffti, ZFFTI) (npts, pwsave);

      for (octave_idx_type k = 0; k < nloop; k++)
	{
	  for (octave_idx_type j = 0; j < howmany; j++)
	    {
	      OCTAVE_QUIT;

	      for (octave_idx_type l = 0; l < npts; l++)
		prow[l] = retval ((l + k*npts)*stride + j*dist);

	      F77_FUNC (zfftf, ZFFTF) (npts, prow, pwsave);

	      for (octave_idx_type l = 0; l < npts; l++)
		retval ((l + k*npts)*stride + j*dist) = prow[l];
	    }
	}

      stride *= dv2(i);
    }

  return retval;
}

ComplexNDArray
NDArray::ifourier2d (void) const
{
  dim_vector dv = dims();
  dim_vector dv2 (dv(0), dv(1));
  int rank = 2;
  ComplexNDArray retval (*this);
  octave_idx_type stride = 1;

  for (int i = 0; i < rank; i++)
    {
      octave_idx_type npts = dv2(i);
      octave_idx_type nn = 4*npts+15;
      Array<Complex> wsave (nn);
      Complex *pwsave = wsave.fortran_vec ();
      Array<Complex> row (npts);
      Complex *prow = row.fortran_vec ();

      octave_idx_type howmany = numel () / npts;
      howmany = (stride == 1 ? howmany : 
		 (howmany > stride ? stride : howmany));
      octave_idx_type nloop = (stride == 1 ? 1 : numel () / npts / stride);
      octave_idx_type dist = (stride == 1 ? npts : 1);

      F77_FUNC (zffti, ZFFTI) (npts, pwsave);

      for (octave_idx_type k = 0; k < nloop; k++)
	{
	  for (octave_idx_type j = 0; j < howmany; j++)
	    {
	      OCTAVE_QUIT;

	      for (octave_idx_type l = 0; l < npts; l++)
		prow[l] = retval ((l + k*npts)*stride + j*dist);

	      F77_FUNC (zfftb, ZFFTB) (npts, prow, pwsave);

	      for (octave_idx_type l = 0; l < npts; l++)
		retval ((l + k*npts)*stride + j*dist) = prow[l] / 
		  static_cast<double> (npts);
	    }
	}

      stride *= dv2(i);
    }

  return retval;
}

ComplexNDArray
NDArray::fourierNd (void) const
{
  dim_vector dv = dims ();
  int rank = dv.length ();
  ComplexNDArray retval (*this);
  octave_idx_type stride = 1;

  for (int i = 0; i < rank; i++)
    {
      octave_idx_type npts = dv(i);
      octave_idx_type nn = 4*npts+15;
      Array<Complex> wsave (nn);
      Complex *pwsave = wsave.fortran_vec ();
      Array<Complex> row (npts);
      Complex *prow = row.fortran_vec ();

      octave_idx_type howmany = numel () / npts;
      howmany = (stride == 1 ? howmany : 
		 (howmany > stride ? stride : howmany));
      octave_idx_type nloop = (stride == 1 ? 1 : numel () / npts / stride);
      octave_idx_type dist = (stride == 1 ? npts : 1);

      F77_FUNC (zffti, ZFFTI) (npts, pwsave);

      for (octave_idx_type k = 0; k < nloop; k++)
	{
	  for (octave_idx_type j = 0; j < howmany; j++)
	    {
	      OCTAVE_QUIT;

	      for (octave_idx_type l = 0; l < npts; l++)
		prow[l] = retval ((l + k*npts)*stride + j*dist);

	      F77_FUNC (zfftf, ZFFTF) (npts, prow, pwsave);

	      for (octave_idx_type l = 0; l < npts; l++)
		retval ((l + k*npts)*stride + j*dist) = prow[l];
	    }
	}

      stride *= dv(i);
    }

  return retval;
}

ComplexNDArray
NDArray::ifourierNd (void) const
{
  dim_vector dv = dims ();
  int rank = dv.length ();
  ComplexNDArray retval (*this);
  octave_idx_type stride = 1;

  for (int i = 0; i < rank; i++)
    {
      octave_idx_type npts = dv(i);
      octave_idx_type nn = 4*npts+15;
      Array<Complex> wsave (nn);
      Complex *pwsave = wsave.fortran_vec ();
      Array<Complex> row (npts);
      Complex *prow = row.fortran_vec ();

      octave_idx_type howmany = numel () / npts;
      howmany = (stride == 1 ? howmany : 
		 (howmany > stride ? stride : howmany));
      octave_idx_type nloop = (stride == 1 ? 1 : numel () / npts / stride);
      octave_idx_type dist = (stride == 1 ? npts : 1);

      F77_FUNC (zffti, ZFFTI) (npts, pwsave);

      for (octave_idx_type k = 0; k < nloop; k++)
	{
	  for (octave_idx_type j = 0; j < howmany; j++)
	    {
	      OCTAVE_QUIT;

	      for (octave_idx_type l = 0; l < npts; l++)
		prow[l] = retval ((l + k*npts)*stride + j*dist);

	      F77_FUNC (zfftb, ZFFTB) (npts, prow, pwsave);

	      for (octave_idx_type l = 0; l < npts; l++)
		retval ((l + k*npts)*stride + j*dist) = prow[l] /
		  static_cast<double> (npts);
	    }
	}

      stride *= dv(i);
    }

  return retval;
}

#endif

// unary operations

boolNDArray
NDArray::operator ! (void) const
{
  boolNDArray b (dims ());

  for (octave_idx_type i = 0; i < length (); i++)
    b.elem (i) = ! elem (i);

  return b;
}

bool
NDArray::any_element_is_negative (bool neg_zero) const
{
  octave_idx_type nel = nelem ();

  if (neg_zero)
    {
      for (octave_idx_type i = 0; i < nel; i++)
	if (lo_ieee_signbit (elem (i)))
	  return true;
    }
  else
    {
      for (octave_idx_type i = 0; i < nel; i++)
	if (elem (i) < 0)
	  return true;
    }

  return false;
}

bool
NDArray::any_element_is_nan (void) const
{
  octave_idx_type nel = nelem ();

  for (octave_idx_type i = 0; i < nel; i++)
    {
      double val = elem (i);
      if (xisnan (val))
	return true;
    }

  return false;
}

bool
NDArray::any_element_is_inf_or_nan (void) const
{
  octave_idx_type nel = nelem ();

  for (octave_idx_type i = 0; i < nel; i++)
    {
      double val = elem (i);
      if (xisinf (val) || xisnan (val))
	return true;
    }

  return false;
}

bool
NDArray::any_element_not_one_or_zero (void) const
{
  octave_idx_type nel = nelem ();

  for (octave_idx_type i = 0; i < nel; i++)
    {
      double val = elem (i);
      if (val != 0 && val != 1)
	return true;
    }

  return false;
}

bool
NDArray::all_elements_are_zero (void) const
{
  octave_idx_type nel = nelem ();

  for (octave_idx_type i = 0; i < nel; i++)
    if (elem (i) != 0)
      return false;

  return true;
}

bool
NDArray::all_elements_are_int_or_inf_or_nan (void) const
{
  octave_idx_type nel = nelem ();

  for (octave_idx_type i = 0; i < nel; i++)
    {
      double val = elem (i);
      if (xisnan (val) || D_NINT (val) == val)
	continue;
      else
	return false;
    }

  return true;
}

// Return nonzero if any element of M is not an integer.  Also extract
// the largest and smallest values and return them in MAX_VAL and MIN_VAL.

bool
NDArray::all_integers (double& max_val, double& min_val) const
{
  octave_idx_type nel = nelem ();

  if (nel > 0)
    {
      max_val = elem (0);
      min_val = elem (0);
    }
  else
    return false;

  for (octave_idx_type i = 0; i < nel; i++)
    {
      double val = elem (i);

      if (val > max_val)
	max_val = val;

      if (val < min_val)
	min_val = val;

      if (D_NINT (val) != val)
	return false;
    }

  return true;
}

bool
NDArray::too_large_for_float (void) const
{
  octave_idx_type nel = nelem ();

  for (octave_idx_type i = 0; i < nel; i++)
    {
      double val = elem (i);

      if (! (xisnan (val) || xisinf (val))
	  && fabs (val) > FLT_MAX)
	return true;
    }

  return false;
}

// FIXME -- this is not quite the right thing.

boolNDArray
NDArray::all (int dim) const
{
  return do_mx_red_op<boolNDArray, double> (*this, dim, mx_inline_all);
}

boolNDArray
NDArray::any (int dim) const
{
  return do_mx_red_op<boolNDArray, double> (*this, dim, mx_inline_any);
}

NDArray
NDArray::cumprod (int dim) const
{
  return do_mx_cum_op<NDArray, double> (*this, dim, mx_inline_cumprod);
}

NDArray
NDArray::cumsum (int dim) const
{
  return do_mx_cum_op<NDArray, double> (*this, dim, mx_inline_cumsum);
}

NDArray
NDArray::prod (int dim) const
{
  return do_mx_red_op<NDArray, double> (*this, dim, mx_inline_prod);
}

NDArray
NDArray::sum (int dim) const
{
  return do_mx_red_op<NDArray, double> (*this, dim, mx_inline_sum);
}

NDArray
NDArray::sumsq (int dim) const
{
  return do_mx_red_op<NDArray, double> (*this, dim, mx_inline_sumsq);
}

NDArray
NDArray::max (int dim) const
{
  return do_mx_minmax_op<NDArray> (*this, dim, mx_inline_max);
}

NDArray
NDArray::max (ArrayN<octave_idx_type>& idx_arg, int dim) const
{
  return do_mx_minmax_op<NDArray> (*this, idx_arg, dim, mx_inline_max);
}

NDArray
NDArray::min (int dim) const
{
  return do_mx_minmax_op<NDArray> (*this, dim, mx_inline_min);
}

NDArray
NDArray::min (ArrayN<octave_idx_type>& idx_arg, int dim) const
{
  return do_mx_minmax_op<NDArray> (*this, idx_arg, dim, mx_inline_min);
}

NDArray
NDArray::cummax (int dim) const
{
  return do_mx_cumminmax_op<NDArray> (*this, dim, mx_inline_cummax);
}

NDArray
NDArray::cummax (ArrayN<octave_idx_type>& idx_arg, int dim) const
{
  return do_mx_cumminmax_op<NDArray> (*this, idx_arg, dim, mx_inline_cummax);
}

NDArray
NDArray::cummin (int dim) const
{
  return do_mx_cumminmax_op<NDArray> (*this, dim, mx_inline_cummin);
}

NDArray
NDArray::cummin (ArrayN<octave_idx_type>& idx_arg, int dim) const
{
  return do_mx_cumminmax_op<NDArray> (*this, idx_arg, dim, mx_inline_cummin);
}

NDArray
NDArray::concat (const NDArray& rb, const Array<octave_idx_type>& ra_idx)
{
  if (rb.numel () > 0)
    insert (rb, ra_idx);
  return *this;
}

ComplexNDArray
NDArray::concat (const ComplexNDArray& rb, const Array<octave_idx_type>& ra_idx)
{
  ComplexNDArray retval (*this);
  if (rb.numel () > 0)
    retval.insert (rb, ra_idx);
  return retval;
}

charNDArray
NDArray::concat (const charNDArray& rb, const Array<octave_idx_type>& ra_idx)
{
  charNDArray retval (dims ());
  octave_idx_type nel = numel ();

  for (octave_idx_type i = 0; i < nel; i++)
    {
      double d = elem (i);

      if (xisnan (d))
	{
	  (*current_liboctave_error_handler)
	    ("invalid conversion from NaN to character");
	  return retval;
	}
      else
	{
	  octave_idx_type ival = NINTbig (d);

	  if (ival < 0 || ival > UCHAR_MAX)
	    // FIXME -- is there something
	    // better we could do? Should we warn the user?
	    ival = 0;

	  retval.elem (i) = static_cast<char>(ival);
	}
    }

  if (rb.numel () == 0)
    return retval;

  retval.insert (rb, ra_idx);
  return retval;
}

NDArray
real (const ComplexNDArray& a)
{
  return NDArray (mx_inline_real_dup (a.data (), a.length ()),
                  a.dims ());
}

NDArray
imag (const ComplexNDArray& a)
{
  return NDArray (mx_inline_imag_dup (a.data (), a.length ()),
                  a.dims ());
}

NDArray&
NDArray::insert (const NDArray& a, octave_idx_type r, octave_idx_type c)
{
  Array<double>::insert (a, r, c);
  return *this;
}

NDArray&
NDArray::insert (const NDArray& a, const Array<octave_idx_type>& ra_idx)
{
  Array<double>::insert (a, ra_idx);
  return *this;
}

NDArray
NDArray::abs (void) const
{
  return NDArray (mx_inline_fabs_dup (data (), length ()),
                  dims ());
}

boolNDArray
NDArray::isnan (void) const
{
  return ArrayN<bool> (fastmap<bool> (xisnan));
}

boolNDArray
NDArray::isinf (void) const
{
  return ArrayN<bool> (fastmap<bool> (xisinf));
}

boolNDArray
NDArray::isfinite (void) const
{
  return ArrayN<bool> (fastmap<bool> (xfinite));
}

Matrix
NDArray::matrix_value (void) const
{
  Matrix retval;

  if (ndims () == 2)
      retval = Matrix (Array2<double> (*this));
  else
    (*current_liboctave_error_handler)
      ("invalid conversion of NDArray to Matrix");

  return retval;
}

void
NDArray::increment_index (Array<octave_idx_type>& ra_idx,
			  const dim_vector& dimensions,
			  int start_dimension)
{
  ::increment_index (ra_idx, dimensions, start_dimension);
}

octave_idx_type
NDArray::compute_index (Array<octave_idx_type>& ra_idx,
			const dim_vector& dimensions)
{
  return ::compute_index (ra_idx, dimensions);
}

NDArray
NDArray::diag (octave_idx_type k) const
{
  return MArrayN<double>::diag (k);
}

NDArray
NDArray::map (dmapper fcn) const
{
  return MArrayN<double>::map<double> (func_ptr (fcn));
}

ComplexNDArray
NDArray::map (cmapper fcn) const
{
  return MArrayN<double>::map<Complex> (func_ptr (fcn));
}

boolNDArray
NDArray::map (bmapper fcn) const
{
  return MArrayN<double>::map<bool> (func_ptr (fcn));
}

// This contains no information on the array structure !!!
std::ostream&
operator << (std::ostream& os, const NDArray& a)
{
  octave_idx_type nel = a.nelem ();

  for (octave_idx_type i = 0; i < nel; i++)
    {
      os << " ";
      octave_write_double (os, a.elem (i));
      os << "\n";
    }
  return os;
}

std::istream&
operator >> (std::istream& is, NDArray& a)
{
  octave_idx_type nel = a.nelem ();

  if (nel > 0)
    {
      double tmp;
      for (octave_idx_type i = 0; i < nel; i++)
	  {
	    tmp = octave_read_double (is);
	    if (is)
	      a.elem (i) = tmp;
	    else
	      goto done;
	  }
    }

 done:

  return is;
}

// FIXME -- it would be nice to share code among the min/max
// functions below.

#define EMPTY_RETURN_CHECK(T) \
  if (nel == 0)	\
    return T (dv);

NDArray
min (double d, const NDArray& m)
{
  dim_vector dv = m.dims ();
  octave_idx_type nel = dv.numel ();

  EMPTY_RETURN_CHECK (NDArray);

  NDArray result (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    {
      OCTAVE_QUIT;
      result (i) = xmin (d, m (i));
    }

  return result;
}

NDArray
min (const NDArray& m, double d)
{
  dim_vector dv = m.dims ();
  octave_idx_type nel = dv.numel ();

  EMPTY_RETURN_CHECK (NDArray);

  NDArray result (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    {
      OCTAVE_QUIT;
      result (i) = xmin (d, m (i));
    }

  return result;
}

NDArray
min (const NDArray& a, const NDArray& b)
{
  dim_vector dv = a.dims ();
  octave_idx_type nel = dv.numel ();

  if (dv != b.dims ())
    {
      (*current_liboctave_error_handler)
	("two-arg min expecting args of same size");
      return NDArray ();
    }

  EMPTY_RETURN_CHECK (NDArray);

  NDArray result (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    {
      OCTAVE_QUIT;
      result (i) = xmin (a (i), b (i));
    }

  return result;
}

NDArray
max (double d, const NDArray& m)
{
  dim_vector dv = m.dims ();
  octave_idx_type nel = dv.numel ();

  EMPTY_RETURN_CHECK (NDArray);

  NDArray result (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    {
      OCTAVE_QUIT;
      result (i) = xmax (d, m (i));
    }

  return result;
}

NDArray
max (const NDArray& m, double d)
{
  dim_vector dv = m.dims ();
  octave_idx_type nel = dv.numel ();

  EMPTY_RETURN_CHECK (NDArray);

  NDArray result (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    {
      OCTAVE_QUIT;
      result (i) = xmax (d, m (i));
    }

  return result;
}

NDArray
max (const NDArray& a, const NDArray& b)
{
  dim_vector dv = a.dims ();
  octave_idx_type nel = dv.numel ();

  if (dv != b.dims ())
    {
      (*current_liboctave_error_handler)
	("two-arg max expecting args of same size");
      return NDArray ();
    }

  EMPTY_RETURN_CHECK (NDArray);

  NDArray result (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    {
      OCTAVE_QUIT;
      result (i) = xmax (a (i), b (i));
    }

  return result;
}

NDS_CMP_OPS(NDArray, , double, )
NDS_BOOL_OPS(NDArray, double, 0.0)

SND_CMP_OPS(double, , NDArray, )
SND_BOOL_OPS(double, NDArray, 0.0)

NDND_CMP_OPS(NDArray, , NDArray, )
NDND_BOOL_OPS(NDArray, NDArray, 0.0)

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
