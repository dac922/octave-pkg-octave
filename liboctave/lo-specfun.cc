/*

Copyright (C) 1996, 1998, 2002, 2003, 2004, 2005, 2006, 2007, 2008
              John W. Eaton

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

#include "Range.h"
#include "CColVector.h"
#include "CMatrix.h"
#include "dRowVector.h"
#include "dMatrix.h"
#include "dNDArray.h"
#include "CNDArray.h"
#include "fCColVector.h"
#include "fCMatrix.h"
#include "fRowVector.h"
#include "fMatrix.h"
#include "fNDArray.h"
#include "fCNDArray.h"
#include "f77-fcn.h"
#include "lo-error.h"
#include "lo-ieee.h"
#include "lo-specfun.h"
#include "mx-inlines.cc"
#include "lo-mappers.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

extern "C"
{
  F77_RET_T
  F77_FUNC (zbesj, ZBESJ) (const double&, const double&, const double&,
			   const octave_idx_type&, const octave_idx_type&, double*, double*,
			   octave_idx_type&, octave_idx_type&);

  F77_RET_T
  F77_FUNC (zbesy, ZBESY) (const double&, const double&, const double&,
			   const octave_idx_type&, const octave_idx_type&, double*, double*,
			   octave_idx_type&, double*, double*, octave_idx_type&);

  F77_RET_T
  F77_FUNC (zbesi, ZBESI) (const double&, const double&, const double&,
			   const octave_idx_type&, const octave_idx_type&, double*, double*,
			   octave_idx_type&, octave_idx_type&);

  F77_RET_T
  F77_FUNC (zbesk, ZBESK) (const double&, const double&, const double&,
			   const octave_idx_type&, const octave_idx_type&, double*, double*,
			   octave_idx_type&, octave_idx_type&);

  F77_RET_T
  F77_FUNC (zbesh, ZBESH) (const double&, const double&, const double&,
			   const octave_idx_type&, const octave_idx_type&, const octave_idx_type&, double*,
			   double*, octave_idx_type&, octave_idx_type&);

  F77_RET_T
  F77_FUNC (cbesj, cBESJ) (const FloatComplex&, const float&,
			   const octave_idx_type&, const octave_idx_type&,
			   FloatComplex*, octave_idx_type&, octave_idx_type&);

  F77_RET_T
  F77_FUNC (cbesy, CBESY) (const FloatComplex&, const float&,
			   const octave_idx_type&, const octave_idx_type&,
			   FloatComplex*, octave_idx_type&,
			   FloatComplex*, octave_idx_type&);

  F77_RET_T
  F77_FUNC (cbesi, CBESI) (const FloatComplex&, const float&,
			   const octave_idx_type&, const octave_idx_type&,
			   FloatComplex*, octave_idx_type&, octave_idx_type&);

  F77_RET_T
  F77_FUNC (cbesk, CBESK) (const FloatComplex&, const float&,
			   const octave_idx_type&, const octave_idx_type&,
			   FloatComplex*, octave_idx_type&, octave_idx_type&);

  F77_RET_T
  F77_FUNC (cbesh, CBESH) (const FloatComplex&, const float&,
			   const octave_idx_type&, const octave_idx_type&,
			   const octave_idx_type&, FloatComplex*,
			   octave_idx_type&, octave_idx_type&);

  F77_RET_T
  F77_FUNC (zairy, ZAIRY) (const double&, const double&, const octave_idx_type&,
			   const octave_idx_type&, double&, double&, octave_idx_type&, octave_idx_type&);

  F77_RET_T
  F77_FUNC (cairy, CAIRY) (const float&, const float&, const octave_idx_type&,
			   const octave_idx_type&, float&, float&, octave_idx_type&, octave_idx_type&);

  F77_RET_T
  F77_FUNC (zbiry, ZBIRY) (const double&, const double&, const octave_idx_type&,
			   const octave_idx_type&, double&, double&, octave_idx_type&);

  F77_RET_T
  F77_FUNC (cbiry, CBIRY) (const float&, const float&, const octave_idx_type&,
			   const octave_idx_type&, float&, float&, octave_idx_type&);

  F77_RET_T
  F77_FUNC (xdacosh, XDACOSH) (const double&, double&);

  F77_RET_T
  F77_FUNC (xacosh, XACOSH) (const float&, float&);

  F77_RET_T
  F77_FUNC (xdasinh, XDASINH) (const double&, double&);

  F77_RET_T
  F77_FUNC (xasinh, XASINH) (const float&, float&);

  F77_RET_T
  F77_FUNC (xdatanh, XDATANH) (const double&, double&);

  F77_RET_T
  F77_FUNC (xatanh, XATANH) (const float&, float&);

  F77_RET_T
  F77_FUNC (xderf, XDERF) (const double&, double&);

  F77_RET_T
  F77_FUNC (xerf, XERF) (const float&, float&);

  F77_RET_T
  F77_FUNC (xderfc, XDERFC) (const double&, double&);

  F77_RET_T
  F77_FUNC (xerfc, XERFC) (const float&, float&);

  F77_RET_T
  F77_FUNC (xdbetai, XDBETAI) (const double&, const double&,
			       const double&, double&);

  F77_RET_T
  F77_FUNC (xbetai, XBETAI) (const float&, const float&,
			     const float&, float&);

  F77_RET_T
  F77_FUNC (xdgamma, XDGAMMA) (const double&, double&);

  F77_RET_T
  F77_FUNC (xgamma, XGAMMA) (const float&, float&);

  F77_RET_T
  F77_FUNC (xgammainc, XGAMMAINC) (const double&, const double&, double&);

  F77_RET_T
  F77_FUNC (xsgammainc, XSGAMMAINC) (const float&, const float&, float&);

  F77_RET_T
  F77_FUNC (dlgams, DLGAMS) (const double&, double&, double&);

  F77_RET_T
  F77_FUNC (algams, ALGAMS) (const float&, float&, float&);
}

#if !defined (HAVE_ACOSH)
double
acosh (double x)
{
  double retval;
  F77_XFCN (xdacosh, XDACOSH, (x, retval));
  return retval;
}
#endif

#if !defined (HAVE_ACOSHF)
float
acoshf (float x)
{
  float retval;
  F77_XFCN (xacosh, XACOSH, (x, retval));
  return retval;
}
#endif

#if !defined (HAVE_ASINH)
double
asinh (double x)
{
  double retval;
  F77_XFCN (xdasinh, XDASINH, (x, retval));
  return retval;
}
#endif

#if !defined (HAVE_ASINHF)
float
asinhf (float x)
{
  float retval;
  F77_XFCN (xasinh, XASINH, (x, retval));
  return retval;
}
#endif

#if !defined (HAVE_ATANH)
double
atanh (double x)
{
  double retval;
  F77_XFCN (xdatanh, XDATANH, (x, retval));
  return retval;
}
#endif

#if !defined (HAVE_ATANHF)
float
atanhf (float x)
{
  float retval;
  F77_XFCN (xatanh, XATANH, (x, retval));
  return retval;
}
#endif

#if !defined (HAVE_ERF)
double
erf (double x)
{
  double retval;
  F77_XFCN (xderf, XDERF, (x, retval));
  return retval;
}
#endif

#if !defined (HAVE_ERFF)
float
erff (float x)
{
  float retval;
  F77_XFCN (xerf, XERF, (x, retval));
  return retval;
}
#endif

#if !defined (HAVE_ERFC)
double
erfc (double x)
{
  double retval;
  F77_XFCN (xderfc, XDERFC, (x, retval));
  return retval;
}
#endif

#if !defined (HAVE_ERFCF)
float
erfcf (float x)
{
  float retval;
  F77_XFCN (xerfc, XERFC, (x, retval));
  return retval;
}
#endif

double
xgamma (double x)
{
#if defined (HAVE_TGAMMA)
  return tgamma (x);
#else
  double result;

  if (xisnan (x))
    result = x;
  else if ((x <= 0 && D_NINT (x) == x) || xisinf (x))
    result = octave_Inf;
  else
    F77_XFCN (xdgamma, XDGAMMA, (x, result));

  return result;
#endif
}

double
xlgamma (double x)
{
#if defined (HAVE_LGAMMA)
  return lgamma (x);
#else
  double result;
  double sgngam;

  if (xisnan (x))
    result = x;
  else if (xisinf (x))
    result = octave_Inf;
  else
    F77_XFCN (dlgams, DLGAMS, (x, result, sgngam));

  return result;
#endif
}

Complex
xlgamma (const Complex& xc)
{
  // Can only be called with a real value of x.
  double x = xc.real ();
  double result;

#if defined (HAVE_LGAMMA_R)
  int sgngam;
  result = lgamma_r (x, &sgngam);    
#else
  double sgngam;

  if (xisnan (x))
    result = x;
  else if (xisinf (x))
    result = octave_Inf;
  else
    F77_XFCN (dlgams, DLGAMS, (x, result, sgngam));

#endif

  if (sgngam < 0)
    return result + Complex (0., M_PI);
  else
    return result;
}

float
xgamma (float x)
{
#if defined (HAVE_TGAMMAF)
  return tgammaf (x);
#else
  float result;

  if (xisnan (x))
    result = x;
  else if ((x <= 0 && D_NINT (x) == x) || xisinf (x))
    result = octave_Float_Inf;
  else
    F77_XFCN (xgamma, XGAMMA, (x, result));

  return result;
#endif
}

float
xlgamma (float x)
{
#if defined (HAVE_LGAMMAF)
  return lgammaf (x);
#else
  float result;
  float sgngam;

  if (xisnan (x))
    result = x;
  else if (xisinf (x))
    result = octave_Float_Inf;
  else
    F77_XFCN (algams, ALGAMS, (x, result, sgngam));

  return result;
#endif
}

FloatComplex
xlgamma (const FloatComplex& xc)
{
  // Can only be called with a real value of x.
  float x = xc.real ();
  float result;

#if defined (HAVE_LGAMMAF_R)
  int sgngam;
  result = lgammaf_r (x, &sgngam);    
#else
  float sgngam;

  if (xisnan (x))
    result = x;
  else if (xisinf (x))
    result = octave_Float_Inf;
  else
    F77_XFCN (algams, ALGAMS, (x, result, sgngam));

#endif

  if (sgngam < 0)
    return result + FloatComplex (0., M_PI);
  else
    return result;
}

#if !defined (HAVE_EXPM1)
double
expm1 (double x)
{
  double retval;

  double ax = fabs (x);

  if (ax < 0.1)
    {
      ax /= 16;

      // use Taylor series to calculate exp(x)-1.
      double t = ax;
      double s = 0; 
      for (int i = 2; i < 7; i++)
        s += (t *= ax/i);
      s += ax;

      // use the identity (a+1)^2-1 = a*(a+2)
      double e = s;
      for (int i = 0; i < 4; i++)
        {
          s *= e + 2;
          e *= e + 2;
        }

      retval = (x > 0) ? s : -s / (1+s);
    }
  else
    retval = exp (x) - 1;

  return retval;
}
#endif

Complex 
expm1(const Complex& x)
{
  Complex retval;

  if (std:: abs (x) < 1)
    {
      double im = x.imag();
      double u = expm1 (x.real ());
      double v = sin (im/2);
      v = -2*v*v;
      retval = Complex (u*v + u + v, (u+1) * sin (im));
    }
  else
    retval = std::exp (x) - Complex (1);

  return retval;
}

#if !defined (HAVE_EXPM1F)
float
expm1f (float x)
{
  float retval;

  float ax = fabs (x);

  if (ax < 0.1)
    {
      ax /= 16;

      // use Taylor series to calculate exp(x)-1.
      float t = ax;
      float s = 0; 
      for (int i = 2; i < 7; i++)
        s += (t *= ax/i);
      s += ax;

      // use the identity (a+1)^2-1 = a*(a+2)
      float e = s;
      for (int i = 0; i < 4; i++)
        {
          s *= e + 2;
          e *= e + 2;
        }

      retval = (x > 0) ? s : -s / (1+s);
    }
  else
    retval = exp (x) - 1;

  return retval;
}
#endif

FloatComplex 
expm1f(const FloatComplex& x)
{
  FloatComplex retval;

  if (std:: abs (x) < 1)
    {
      float im = x.imag();
      float u = expm1 (x.real ());
      float v = sin (im/2);
      v = -2*v*v;
      retval = FloatComplex (u*v + u + v, (u+1) * sin (im));
    }
  else
    retval = std::exp (x) - FloatComplex (1);

  return retval;
}

#if !defined (HAVE_LOG1P)
double
log1p (double x)
{
  double retval;

  double ax = fabs (x);

  if (ax < 0.2)
    {
      // use approximation log (1+x) ~ 2*sum ((x/(2+x)).^ii ./ ii), ii = 1:2:2n+1
      double u = x / (2 + x), t = 1, s = 0;
      for (int i = 2; i < 12; i += 2)
        s += (t *= u*u) / (i+1);

      retval = 2 * (s + 1) * u;
    }
  else
    retval = log (1 + x);

  return retval;
}
#endif

Complex 
log1p (const Complex& x)
{
  Complex retval;

  double r = x.real (), i = x.imag();

  if (fabs (r) < 0.5 && fabs (i) < 0.5)
    {
      double u = 2*r + r*r + i*i;
      retval = Complex (log1p (u / (1+sqrt (u+1))),
			atan2 (1 + r, i));
    }
  else
    retval = std::log (Complex(1) + x);

  return retval;
}

#if !defined (HAVE_LOG1PF)
float
log1pf (float x)
{
  float retval;

  float ax = fabs (x);

  if (ax < 0.2)
    {
      // use approximation log (1+x) ~ 2*sum ((x/(2+x)).^ii ./ ii), ii = 1:2:2n+1
      float u = x / (2 + x), t = 1, s = 0;
      for (int i = 2; i < 12; i += 2)
        s += (t *= u*u) / (i+1);

      retval = 2 * (s + 1) * u;
    }
  else
    retval = log (1 + x);

  return retval;
}
#endif

FloatComplex 
log1pf (const FloatComplex& x)
{
  FloatComplex retval;

  float r = x.real (), i = x.imag();

  if (fabs (r) < 0.5 && fabs (i) < 0.5)
    {
      float u = 2*r + r*r + i*i;
      retval = FloatComplex (log1p (u / (1+sqrt (u+1))),
			atan2 (1 + r, i));
    }
  else
    retval = std::log (FloatComplex(1) + x);

  return retval;
}

static inline Complex
zbesj (const Complex& z, double alpha, int kode, octave_idx_type& ierr);

static inline Complex
zbesy (const Complex& z, double alpha, int kode, octave_idx_type& ierr);

static inline Complex
zbesi (const Complex& z, double alpha, int kode, octave_idx_type& ierr);

static inline Complex
zbesk (const Complex& z, double alpha, int kode, octave_idx_type& ierr);

static inline Complex
zbesh1 (const Complex& z, double alpha, int kode, octave_idx_type& ierr);

static inline Complex
zbesh2 (const Complex& z, double alpha, int kode, octave_idx_type& ierr);

static inline Complex
bessel_return_value (const Complex& val, octave_idx_type ierr)
{
  static const Complex inf_val = Complex (octave_Inf, octave_Inf);
  static const Complex nan_val = Complex (octave_NaN, octave_NaN);

  Complex retval;

  switch (ierr)
    {
    case 0:
    case 3:
      retval = val;
      break;

    case 2:
      retval = inf_val;
      break;

    default:
      retval = nan_val;
      break;
    }

  return retval;
}

static inline bool
is_integer_value (double x)
{
  return x == static_cast<double> (static_cast<long> (x));
}

static inline Complex
zbesj (const Complex& z, double alpha, int kode, octave_idx_type& ierr)
{
  Complex retval;

  if (alpha >= 0.0)
    {
      double yr = 0.0;
      double yi = 0.0;

      octave_idx_type nz;

      double zr = z.real ();
      double zi = z.imag ();

      F77_FUNC (zbesj, ZBESJ) (zr, zi, alpha, 2, 1, &yr, &yi, nz, ierr);

      if (kode != 2)
	{
	  double expz = exp (std::abs (zi)); 
	  yr *= expz;
	  yi *= expz;
	}

      if (zi == 0.0 && zr >= 0.0)
	yi = 0.0;

      retval = bessel_return_value (Complex (yr, yi), ierr);
    }
  else if (is_integer_value (alpha))
    {
      // zbesy can overflow as z->0, and cause troubles for generic case below
      alpha = -alpha;
      Complex tmp = zbesj (z, alpha, kode, ierr);
      if ((static_cast <long> (alpha)) & 1) 
	tmp = - tmp;
      retval = bessel_return_value (tmp, ierr);
    }
  else
    {
      alpha = -alpha;

      Complex tmp = cos (M_PI * alpha) * zbesj (z, alpha, kode, ierr);

      if (ierr == 0 || ierr == 3)
	{
	  tmp -= sin (M_PI * alpha) * zbesy (z, alpha, kode, ierr);

	  retval = bessel_return_value (tmp, ierr);
	}
      else
	retval = Complex (octave_NaN, octave_NaN);
    }

  return retval;
}

static inline Complex
zbesy (const Complex& z, double alpha, int kode, octave_idx_type& ierr)
{
  Complex retval;

  if (alpha >= 0.0)
    {
      double yr = 0.0;
      double yi = 0.0;

      octave_idx_type nz;

      double wr, wi;

      double zr = z.real ();
      double zi = z.imag ();

      ierr = 0;

      if (zr == 0.0 && zi == 0.0)
	{
	  yr = -octave_Inf;
	  yi = 0.0;
	}
      else
	{
	  F77_FUNC (zbesy, ZBESY) (zr, zi, alpha, 2, 1, &yr, &yi, nz,
				   &wr, &wi, ierr);

	  if (kode != 2)
	    {
	      double expz = exp (std::abs (zi));
	      yr *= expz;
	      yi *= expz;
	    }

	  if (zi == 0.0 && zr >= 0.0)
	    yi = 0.0;
	}

      return bessel_return_value (Complex (yr, yi), ierr);
    }
  else if (is_integer_value (alpha - 0.5))
    {
      // zbesy can overflow as z->0, and cause troubles for generic case below
      alpha = -alpha;
      Complex tmp = zbesj (z, alpha, kode, ierr);
      if ((static_cast <long> (alpha - 0.5)) & 1) 
	tmp = - tmp;
      retval = bessel_return_value (tmp, ierr);
    }
  else
    {
      alpha = -alpha;

      Complex tmp = cos (M_PI * alpha) * zbesy (z, alpha, kode, ierr);

      if (ierr == 0 || ierr == 3)
	{
	  tmp += sin (M_PI * alpha) * zbesj (z, alpha, kode, ierr);

	  retval = bessel_return_value (tmp, ierr);
	}
      else
	retval = Complex (octave_NaN, octave_NaN);
    }

  return retval;
}

static inline Complex
zbesi (const Complex& z, double alpha, int kode, octave_idx_type& ierr)
{
  Complex retval;

  if (alpha >= 0.0)
    {
      double yr = 0.0;
      double yi = 0.0;

      octave_idx_type nz;

      double zr = z.real ();
      double zi = z.imag ();

      F77_FUNC (zbesi, ZBESI) (zr, zi, alpha, 2, 1, &yr, &yi, nz, ierr);

      if (kode != 2)
	{
	  double expz = exp (std::abs (zr));
	  yr *= expz;
	  yi *= expz;
	}

      if (zi == 0.0 && zr >= 0.0)
	yi = 0.0;

      retval = bessel_return_value (Complex (yr, yi), ierr);
    }
  else
    {
      alpha = -alpha;

      Complex tmp = zbesi (z, alpha, kode, ierr);

      if (ierr == 0 || ierr == 3)
	{
	  Complex tmp2 = (2.0 / M_PI) * sin (M_PI * alpha)
	    * zbesk (z, alpha, kode, ierr);
	
	  if (kode == 2) 
	    {
	      // Compensate for different scaling factor of besk.
	      tmp2 *= exp(-z - std::abs(z.real()));
	    }
	  
	  tmp += tmp2;

	  retval = bessel_return_value (tmp, ierr);
	}
      else
	retval = Complex (octave_NaN, octave_NaN);
    }

  return retval;
}

static inline Complex
zbesk (const Complex& z, double alpha, int kode, octave_idx_type& ierr)
{
  Complex retval;

  if (alpha >= 0.0)
    {
      double yr = 0.0;
      double yi = 0.0;

      octave_idx_type nz;

      double zr = z.real ();
      double zi = z.imag ();

      ierr = 0;

      if (zr == 0.0 && zi == 0.0)
	{
	  yr = octave_Inf;
	  yi = 0.0;
	}
      else
	{
	  F77_FUNC (zbesk, ZBESK) (zr, zi, alpha, 2, 1, &yr, &yi, nz, ierr);

	  if (kode != 2)
	    {
	      Complex expz = exp (-z);

	      double rexpz = real (expz);
	      double iexpz = imag (expz);

	      double tmp = yr*rexpz - yi*iexpz;

	      yi = yr*iexpz + yi*rexpz;
	      yr = tmp;
	    }

	  if (zi == 0.0 && zr >= 0.0)
	    yi = 0.0;
	}

      retval = bessel_return_value (Complex (yr, yi), ierr);
    }
  else
    {
      Complex tmp = zbesk (z, -alpha, kode, ierr);

      retval = bessel_return_value (tmp, ierr);
    }

  return retval;
}

static inline Complex
zbesh1 (const Complex& z, double alpha, int kode, octave_idx_type& ierr)
{
  Complex retval;

  if (alpha >= 0.0)
    {
      double yr = 0.0;
      double yi = 0.0;

      octave_idx_type nz;

      double zr = z.real ();
      double zi = z.imag ();

      F77_FUNC (zbesh, ZBESH) (zr, zi, alpha, 2, 1, 1, &yr, &yi, nz, ierr);

      if (kode != 2)
	{
	  Complex expz = exp (Complex (0.0, 1.0) * z);

	  double rexpz = real (expz);
	  double iexpz = imag (expz);

	  double tmp = yr*rexpz - yi*iexpz;

	  yi = yr*iexpz + yi*rexpz;
	  yr = tmp;
	}

      retval = bessel_return_value (Complex (yr, yi), ierr);
    }
  else
    {
      alpha = -alpha;

      static const Complex eye = Complex (0.0, 1.0);

      Complex tmp = exp (M_PI * alpha * eye) * zbesh1 (z, alpha, kode, ierr);

      retval = bessel_return_value (tmp, ierr);
    }

  return retval;
}

static inline Complex
zbesh2 (const Complex& z, double alpha, int kode, octave_idx_type& ierr)
{
  Complex retval;

  if (alpha >= 0.0)
    {
      double yr = 0.0;
      double yi = 0.0;

      octave_idx_type nz;

      double zr = z.real ();
      double zi = z.imag ();

      F77_FUNC (zbesh, ZBESH) (zr, zi, alpha, 2, 2, 1, &yr, &yi, nz, ierr);

      if (kode != 2)
	{
	  Complex expz = exp (-Complex (0.0, 1.0) * z);

	  double rexpz = real (expz);
	  double iexpz = imag (expz);

	  double tmp = yr*rexpz - yi*iexpz;

	  yi = yr*iexpz + yi*rexpz;
	  yr = tmp;
	}

      retval = bessel_return_value (Complex (yr, yi), ierr);
    }
  else
    {
      alpha = -alpha;

      static const Complex eye = Complex (0.0, 1.0);

      Complex tmp = exp (-M_PI * alpha * eye) * zbesh2 (z, alpha, kode, ierr);

      retval = bessel_return_value (tmp, ierr);
    }

  return retval;
}

typedef Complex (*dptr) (const Complex&, double, int, octave_idx_type&);

static inline Complex
do_bessel (dptr f, const char *, double alpha, const Complex& x,
	   bool scaled, octave_idx_type& ierr)
{
  Complex retval;

  retval = f (x, alpha, (scaled ? 2 : 1), ierr);

  return retval;
}

static inline ComplexMatrix
do_bessel (dptr f, const char *, double alpha, const ComplexMatrix& x,
	   bool scaled, Array2<octave_idx_type>& ierr)
{
  octave_idx_type nr = x.rows ();
  octave_idx_type nc = x.cols ();

  ComplexMatrix retval (nr, nc);

  ierr.resize (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = f (x(i,j), alpha, (scaled ? 2 : 1), ierr(i,j));

  return retval;
}

static inline ComplexMatrix
do_bessel (dptr f, const char *, const Matrix& alpha, const Complex& x,
	   bool scaled, Array2<octave_idx_type>& ierr)
{
  octave_idx_type nr = alpha.rows ();
  octave_idx_type nc = alpha.cols ();

  ComplexMatrix retval (nr, nc);

  ierr.resize (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = f (x, alpha(i,j), (scaled ? 2 : 1), ierr(i,j));

  return retval;
}

static inline ComplexMatrix
do_bessel (dptr f, const char *fn, const Matrix& alpha,
	   const ComplexMatrix& x, bool scaled, Array2<octave_idx_type>& ierr)
{
  ComplexMatrix retval;

  octave_idx_type x_nr = x.rows ();
  octave_idx_type x_nc = x.cols ();

  octave_idx_type alpha_nr = alpha.rows ();
  octave_idx_type alpha_nc = alpha.cols ();

  if (x_nr == alpha_nr && x_nc == alpha_nc)
    {
      octave_idx_type nr = x_nr;
      octave_idx_type nc = x_nc;

      retval.resize (nr, nc);

      ierr.resize (nr, nc);

      for (octave_idx_type j = 0; j < nc; j++)
	for (octave_idx_type i = 0; i < nr; i++)
	  retval(i,j) = f (x(i,j), alpha(i,j), (scaled ? 2 : 1), ierr(i,j));
    }
  else
    (*current_liboctave_error_handler)
      ("%s: the sizes of alpha and x must conform", fn);

  return retval;
}

static inline ComplexNDArray
do_bessel (dptr f, const char *, double alpha, const ComplexNDArray& x,
	   bool scaled, ArrayN<octave_idx_type>& ierr)
{
  dim_vector dv = x.dims ();
  octave_idx_type nel = dv.numel ();
  ComplexNDArray retval (dv);

  ierr.resize (dv);

  for (octave_idx_type i = 0; i < nel; i++)
      retval(i) = f (x(i), alpha, (scaled ? 2 : 1), ierr(i));

  return retval;
}

static inline ComplexNDArray
do_bessel (dptr f, const char *, const NDArray& alpha, const Complex& x,
	   bool scaled, ArrayN<octave_idx_type>& ierr)
{
  dim_vector dv = alpha.dims ();
  octave_idx_type nel = dv.numel ();
  ComplexNDArray retval (dv);

  ierr.resize (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    retval(i) = f (x, alpha(i), (scaled ? 2 : 1), ierr(i));

  return retval;
}

static inline ComplexNDArray
do_bessel (dptr f, const char *fn, const NDArray& alpha,
	   const ComplexNDArray& x, bool scaled, ArrayN<octave_idx_type>& ierr)
{
  dim_vector dv = x.dims ();
  ComplexNDArray retval;

  if (dv == alpha.dims ())
    {
      octave_idx_type nel = dv.numel ();

      retval.resize (dv);
      ierr.resize (dv);

      for (octave_idx_type i = 0; i < nel; i++)
	retval(i) = f (x(i), alpha(i), (scaled ? 2 : 1), ierr(i));
    }
  else
    (*current_liboctave_error_handler)
      ("%s: the sizes of alpha and x must conform", fn);

  return retval;
}

static inline ComplexMatrix
do_bessel (dptr f, const char *, const RowVector& alpha,
	   const ComplexColumnVector& x, bool scaled, Array2<octave_idx_type>& ierr)
{
  octave_idx_type nr = x.length ();
  octave_idx_type nc = alpha.length ();

  ComplexMatrix retval (nr, nc);

  ierr.resize (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = f (x(i), alpha(j), (scaled ? 2 : 1), ierr(i,j));

  return retval;
}

#define SS_BESSEL(name, fcn) \
  Complex \
  name (double alpha, const Complex& x, bool scaled, octave_idx_type& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define SM_BESSEL(name, fcn) \
  ComplexMatrix \
  name (double alpha, const ComplexMatrix& x, bool scaled, \
	Array2<octave_idx_type>& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define MS_BESSEL(name, fcn) \
  ComplexMatrix \
  name (const Matrix& alpha, const Complex& x, bool scaled, \
	Array2<octave_idx_type>& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define MM_BESSEL(name, fcn) \
  ComplexMatrix \
  name (const Matrix& alpha, const ComplexMatrix& x, bool scaled, \
	Array2<octave_idx_type>& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define SN_BESSEL(name, fcn) \
  ComplexNDArray \
  name (double alpha, const ComplexNDArray& x, bool scaled, \
	ArrayN<octave_idx_type>& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define NS_BESSEL(name, fcn) \
  ComplexNDArray \
  name (const NDArray& alpha, const Complex& x, bool scaled, \
	ArrayN<octave_idx_type>& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define NN_BESSEL(name, fcn) \
  ComplexNDArray \
  name (const NDArray& alpha, const ComplexNDArray& x, bool scaled, \
	ArrayN<octave_idx_type>& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define RC_BESSEL(name, fcn) \
  ComplexMatrix \
  name (const RowVector& alpha, const ComplexColumnVector& x, bool scaled, \
        Array2<octave_idx_type>& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define ALL_BESSEL(name, fcn) \
  SS_BESSEL (name, fcn) \
  SM_BESSEL (name, fcn) \
  MS_BESSEL (name, fcn) \
  MM_BESSEL (name, fcn) \
  SN_BESSEL (name, fcn) \
  NS_BESSEL (name, fcn) \
  NN_BESSEL (name, fcn) \
  RC_BESSEL (name, fcn)

ALL_BESSEL (besselj, zbesj)
ALL_BESSEL (bessely, zbesy)
ALL_BESSEL (besseli, zbesi)
ALL_BESSEL (besselk, zbesk)
ALL_BESSEL (besselh1, zbesh1)
ALL_BESSEL (besselh2, zbesh2)

#undef ALL_BESSEL
#undef SS_BESSEL
#undef SM_BESSEL
#undef MS_BESSEL
#undef MM_BESSEL
#undef SN_BESSEL
#undef NS_BESSEL
#undef NN_BESSEL
#undef RC_BESSEL

static inline FloatComplex
cbesj (const FloatComplex& z, float alpha, int kode, octave_idx_type& ierr);

static inline FloatComplex
cbesy (const FloatComplex& z, float alpha, int kode, octave_idx_type& ierr);

static inline FloatComplex
cbesi (const FloatComplex& z, float alpha, int kode, octave_idx_type& ierr);

static inline FloatComplex
cbesk (const FloatComplex& z, float alpha, int kode, octave_idx_type& ierr);

static inline FloatComplex
cbesh1 (const FloatComplex& z, float alpha, int kode, octave_idx_type& ierr);

static inline FloatComplex
cbesh2 (const FloatComplex& z, float alpha, int kode, octave_idx_type& ierr);

static inline FloatComplex
bessel_return_value (const FloatComplex& val, octave_idx_type ierr)
{
  static const FloatComplex inf_val = FloatComplex (octave_Float_Inf, octave_Float_Inf);
  static const FloatComplex nan_val = FloatComplex (octave_Float_NaN, octave_Float_NaN);

  FloatComplex retval;

  switch (ierr)
    {
    case 0:
    case 3:
      retval = val;
      break;

    case 2:
      retval = inf_val;
      break;

    default:
      retval = nan_val;
      break;
    }

  return retval;
}

static inline bool
is_integer_value (float x)
{
  return x == static_cast<float> (static_cast<long> (x));
}

static inline FloatComplex
cbesj (const FloatComplex& z, float alpha, int kode, octave_idx_type& ierr)
{
  FloatComplex retval;

  if (alpha >= 0.0)
    {
      FloatComplex y = 0.0;

      octave_idx_type nz;

      F77_FUNC (cbesj, CBESJ) (z, alpha, 2, 1, &y, nz, ierr);

      if (kode != 2)
	{
	  float expz = exp (std::abs (imag (z)));
	  y *= expz;
	}

      if (imag (z) == 0.0 && real (z) >= 0.0)
	y = FloatComplex (y.real (), 0.0);

      retval = bessel_return_value (y, ierr);
    }
  else if (is_integer_value (alpha))
    {
      // zbesy can overflow as z->0, and cause troubles for generic case below
      alpha = -alpha;
      FloatComplex tmp = cbesj (z, alpha, kode, ierr);
      if ((static_cast <long> (alpha)) & 1) 
	tmp = - tmp;
      retval = bessel_return_value (tmp, ierr);
    }
  else
    {
      alpha = -alpha;

      FloatComplex tmp = cosf (static_cast<float> (M_PI) * alpha) * cbesj (z, alpha, kode, ierr);

      if (ierr == 0 || ierr == 3)
	{
	  tmp -= sinf (static_cast<float> (M_PI) * alpha) * cbesy (z, alpha, kode, ierr);

	  retval = bessel_return_value (tmp, ierr);
	}
      else
	retval = FloatComplex (octave_Float_NaN, octave_Float_NaN);
    }

  return retval;
}

static inline FloatComplex
cbesy (const FloatComplex& z, float alpha, int kode, octave_idx_type& ierr)
{
  FloatComplex retval;

  if (alpha >= 0.0)
    {
      FloatComplex y = 0.0;

      octave_idx_type nz;

      FloatComplex w;

      ierr = 0;

      if (real (z) == 0.0 && imag (z) == 0.0)
	{
	  y = FloatComplex (-octave_Float_Inf, 0.0);
	}
      else
	{
	  F77_FUNC (cbesy, CBESY) (z, alpha, 2, 1, &y, nz, &w, ierr);

	  if (kode != 2)
	    {
	      float expz = exp (std::abs (imag (z)));
	      y *= expz;
	    }

	  if (imag (z) == 0.0 && real (z) >= 0.0)
	    y = FloatComplex (y.real (), 0.0);
	}

      return bessel_return_value (y, ierr);
    }
  else if (is_integer_value (alpha - 0.5))
    {
      // zbesy can overflow as z->0, and cause troubles for generic case below
      alpha = -alpha;
      FloatComplex tmp = cbesj (z, alpha, kode, ierr);
      if ((static_cast <long> (alpha - 0.5)) & 1) 
	tmp = - tmp;
      retval = bessel_return_value (tmp, ierr);
    }
  else
    {
      alpha = -alpha;

      FloatComplex tmp = cosf (static_cast<float> (M_PI) * alpha) * cbesy (z, alpha, kode, ierr);

      if (ierr == 0 || ierr == 3)
	{
	  tmp += sinf (static_cast<float> (M_PI) * alpha) * cbesj (z, alpha, kode, ierr);

	  retval = bessel_return_value (tmp, ierr);
	}
      else
	retval = FloatComplex (octave_Float_NaN, octave_Float_NaN);
    }

  return retval;
}

static inline FloatComplex
cbesi (const FloatComplex& z, float alpha, int kode, octave_idx_type& ierr)
{
  FloatComplex retval;

  if (alpha >= 0.0)
    {
      FloatComplex y = 0.0;

      octave_idx_type nz;

      F77_FUNC (cbesi, CBESI) (z, alpha, 2, 1, &y, nz, ierr);

      if (kode != 2)
	{
	  float expz = exp (std::abs (real (z)));
	  y *= expz;
	}

      if (imag (z) == 0.0 && real (z) >= 0.0)
	y = FloatComplex (y.real (), 0.0);

      retval = bessel_return_value (y, ierr);
    }
  else
    {
      alpha = -alpha;

      FloatComplex tmp = cbesi (z, alpha, kode, ierr);

      if (ierr == 0 || ierr == 3)
	{
	  FloatComplex tmp2 = static_cast<float> (2.0 / M_PI) * sinf (static_cast<float> (M_PI) * alpha)
	    * cbesk (z, alpha, kode, ierr);
	  
	  if (kode == 2) 
	    {
	      // Compensate for different scaling factor of besk.
	      tmp2 *= exp(-z - std::abs(z.real()));
	    }

	  tmp += tmp2;

	  retval = bessel_return_value (tmp, ierr);
	}
      else
	retval = FloatComplex (octave_Float_NaN, octave_Float_NaN);
    }

  return retval;
}

static inline FloatComplex
cbesk (const FloatComplex& z, float alpha, int kode, octave_idx_type& ierr)
{
  FloatComplex retval;

  if (alpha >= 0.0)
    {
      FloatComplex y = 0.0;

      octave_idx_type nz;

      ierr = 0;

      if (real (z) == 0.0 && imag (z) == 0.0)
	{
	  y = FloatComplex (octave_Float_Inf, 0.0);
	}
      else
	{
	  F77_FUNC (cbesk, CBESK) (z, alpha, 2, 1, &y, nz, ierr);

	  if (kode != 2)
	    {
	      FloatComplex expz = exp (-z);

	      float rexpz = real (expz);
	      float iexpz = imag (expz);

	      float tmp_r = real (y) * rexpz - imag (y) * iexpz;
	      float tmp_i = real (y) * iexpz + imag (y) * rexpz;

	      y = FloatComplex (tmp_r, tmp_i);
	    }

	  if (imag (z) == 0.0 && real (z) >= 0.0)
	    y = FloatComplex (y.real (), 0.0);
	}

      retval = bessel_return_value (y, ierr);
    }
  else
    {
      FloatComplex tmp = cbesk (z, -alpha, kode, ierr);

      retval = bessel_return_value (tmp, ierr);
    }

  return retval;
}

static inline FloatComplex
cbesh1 (const FloatComplex& z, float alpha, int kode, octave_idx_type& ierr)
{
  FloatComplex retval;

  if (alpha >= 0.0)
    {
      FloatComplex y = 0.0;

      octave_idx_type nz;

      F77_FUNC (cbesh, CBESH) (z, alpha, 2, 1, 1, &y, nz, ierr);

      if (kode != 2)
	{
	  FloatComplex expz = exp (FloatComplex (0.0, 1.0) * z);

	  float rexpz = real (expz);
	  float iexpz = imag (expz);

	  float tmp_r = real (y) * rexpz - imag (y) * iexpz;
	  float tmp_i = real (y) * iexpz + imag (y) * rexpz;

	  y = FloatComplex (tmp_r, tmp_i);
	}

      retval = bessel_return_value (y, ierr);
    }
  else
    {
      alpha = -alpha;

      static const FloatComplex eye = FloatComplex (0.0, 1.0);

      FloatComplex tmp = exp (static_cast<float> (M_PI) * alpha * eye) * cbesh1 (z, alpha, kode, ierr);

      retval = bessel_return_value (tmp, ierr);
    }

  return retval;
}

static inline FloatComplex
cbesh2 (const FloatComplex& z, float alpha, int kode, octave_idx_type& ierr)
{
  FloatComplex retval;

  if (alpha >= 0.0)
    {
      FloatComplex y = 0.0;

      octave_idx_type nz;

      F77_FUNC (cbesh, CBESH) (z, alpha, 2, 2, 1, &y, nz, ierr);

      if (kode != 2)
	{
	  FloatComplex expz = exp (-FloatComplex (0.0, 1.0) * z);

	  float rexpz = real (expz);
	  float iexpz = imag (expz);

	  float tmp_r = real (y) * rexpz - imag (y) * iexpz;
	  float tmp_i = real (y) * iexpz + imag (y) * rexpz;

	  y = FloatComplex (tmp_r, tmp_i);
	}

      retval = bessel_return_value (y, ierr);
    }
  else
    {
      alpha = -alpha;

      static const FloatComplex eye = FloatComplex (0.0, 1.0);

      FloatComplex tmp = exp (-static_cast<float> (M_PI) * alpha * eye) * cbesh2 (z, alpha, kode, ierr);

      retval = bessel_return_value (tmp, ierr);
    }

  return retval;
}

typedef FloatComplex (*fptr) (const FloatComplex&, float, int, octave_idx_type&);

static inline FloatComplex
do_bessel (fptr f, const char *, float alpha, const FloatComplex& x,
	   bool scaled, octave_idx_type& ierr)
{
  FloatComplex retval;

  retval = f (x, alpha, (scaled ? 2 : 1), ierr);

  return retval;
}

static inline FloatComplexMatrix
do_bessel (fptr f, const char *, float alpha, const FloatComplexMatrix& x,
	   bool scaled, Array2<octave_idx_type>& ierr)
{
  octave_idx_type nr = x.rows ();
  octave_idx_type nc = x.cols ();

  FloatComplexMatrix retval (nr, nc);

  ierr.resize (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = f (x(i,j), alpha, (scaled ? 2 : 1), ierr(i,j));

  return retval;
}

static inline FloatComplexMatrix
do_bessel (fptr f, const char *, const FloatMatrix& alpha, const FloatComplex& x,
	   bool scaled, Array2<octave_idx_type>& ierr)
{
  octave_idx_type nr = alpha.rows ();
  octave_idx_type nc = alpha.cols ();

  FloatComplexMatrix retval (nr, nc);

  ierr.resize (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = f (x, alpha(i,j), (scaled ? 2 : 1), ierr(i,j));

  return retval;
}

static inline FloatComplexMatrix
do_bessel (fptr f, const char *fn, const FloatMatrix& alpha,
	   const FloatComplexMatrix& x, bool scaled, Array2<octave_idx_type>& ierr)
{
  FloatComplexMatrix retval;

  octave_idx_type x_nr = x.rows ();
  octave_idx_type x_nc = x.cols ();

  octave_idx_type alpha_nr = alpha.rows ();
  octave_idx_type alpha_nc = alpha.cols ();

  if (x_nr == alpha_nr && x_nc == alpha_nc)
    {
      octave_idx_type nr = x_nr;
      octave_idx_type nc = x_nc;

      retval.resize (nr, nc);

      ierr.resize (nr, nc);

      for (octave_idx_type j = 0; j < nc; j++)
	for (octave_idx_type i = 0; i < nr; i++)
	  retval(i,j) = f (x(i,j), alpha(i,j), (scaled ? 2 : 1), ierr(i,j));
    }
  else
    (*current_liboctave_error_handler)
      ("%s: the sizes of alpha and x must conform", fn);

  return retval;
}

static inline FloatComplexNDArray
do_bessel (fptr f, const char *, float alpha, const FloatComplexNDArray& x,
	   bool scaled, ArrayN<octave_idx_type>& ierr)
{
  dim_vector dv = x.dims ();
  octave_idx_type nel = dv.numel ();
  FloatComplexNDArray retval (dv);

  ierr.resize (dv);

  for (octave_idx_type i = 0; i < nel; i++)
      retval(i) = f (x(i), alpha, (scaled ? 2 : 1), ierr(i));

  return retval;
}

static inline FloatComplexNDArray
do_bessel (fptr f, const char *, const FloatNDArray& alpha, const FloatComplex& x,
	   bool scaled, ArrayN<octave_idx_type>& ierr)
{
  dim_vector dv = alpha.dims ();
  octave_idx_type nel = dv.numel ();
  FloatComplexNDArray retval (dv);

  ierr.resize (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    retval(i) = f (x, alpha(i), (scaled ? 2 : 1), ierr(i));

  return retval;
}

static inline FloatComplexNDArray
do_bessel (fptr f, const char *fn, const FloatNDArray& alpha,
	   const FloatComplexNDArray& x, bool scaled, ArrayN<octave_idx_type>& ierr)
{
  dim_vector dv = x.dims ();
  FloatComplexNDArray retval;

  if (dv == alpha.dims ())
    {
      octave_idx_type nel = dv.numel ();

      retval.resize (dv);
      ierr.resize (dv);

      for (octave_idx_type i = 0; i < nel; i++)
	retval(i) = f (x(i), alpha(i), (scaled ? 2 : 1), ierr(i));
    }
  else
    (*current_liboctave_error_handler)
      ("%s: the sizes of alpha and x must conform", fn);

  return retval;
}

static inline FloatComplexMatrix
do_bessel (fptr f, const char *, const FloatRowVector& alpha,
	   const FloatComplexColumnVector& x, bool scaled, Array2<octave_idx_type>& ierr)
{
  octave_idx_type nr = x.length ();
  octave_idx_type nc = alpha.length ();

  FloatComplexMatrix retval (nr, nc);

  ierr.resize (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = f (x(i), alpha(j), (scaled ? 2 : 1), ierr(i,j));

  return retval;
}

#define SS_BESSEL(name, fcn) \
  FloatComplex \
  name (float alpha, const FloatComplex& x, bool scaled, octave_idx_type& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define SM_BESSEL(name, fcn) \
  FloatComplexMatrix \
  name (float alpha, const FloatComplexMatrix& x, bool scaled, \
	Array2<octave_idx_type>& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define MS_BESSEL(name, fcn) \
  FloatComplexMatrix \
  name (const FloatMatrix& alpha, const FloatComplex& x, bool scaled, \
	Array2<octave_idx_type>& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define MM_BESSEL(name, fcn) \
  FloatComplexMatrix \
  name (const FloatMatrix& alpha, const FloatComplexMatrix& x, bool scaled, \
	Array2<octave_idx_type>& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define SN_BESSEL(name, fcn) \
  FloatComplexNDArray \
  name (float alpha, const FloatComplexNDArray& x, bool scaled, \
	ArrayN<octave_idx_type>& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define NS_BESSEL(name, fcn) \
  FloatComplexNDArray \
  name (const FloatNDArray& alpha, const FloatComplex& x, bool scaled, \
	ArrayN<octave_idx_type>& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define NN_BESSEL(name, fcn) \
  FloatComplexNDArray \
  name (const FloatNDArray& alpha, const FloatComplexNDArray& x, bool scaled, \
	ArrayN<octave_idx_type>& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define RC_BESSEL(name, fcn) \
  FloatComplexMatrix \
  name (const FloatRowVector& alpha, const FloatComplexColumnVector& x, bool scaled, \
        Array2<octave_idx_type>& ierr) \
  { \
    return do_bessel (fcn, #name, alpha, x, scaled, ierr); \
  }

#define ALL_BESSEL(name, fcn) \
  SS_BESSEL (name, fcn) \
  SM_BESSEL (name, fcn) \
  MS_BESSEL (name, fcn) \
  MM_BESSEL (name, fcn) \
  SN_BESSEL (name, fcn) \
  NS_BESSEL (name, fcn) \
  NN_BESSEL (name, fcn) \
  RC_BESSEL (name, fcn)

ALL_BESSEL (besselj, cbesj)
ALL_BESSEL (bessely, cbesy)
ALL_BESSEL (besseli, cbesi)
ALL_BESSEL (besselk, cbesk)
ALL_BESSEL (besselh1, cbesh1)
ALL_BESSEL (besselh2, cbesh2)

#undef ALL_BESSEL
#undef SS_BESSEL
#undef SM_BESSEL
#undef MS_BESSEL
#undef MM_BESSEL
#undef SN_BESSEL
#undef NS_BESSEL
#undef NN_BESSEL
#undef RC_BESSEL

Complex
airy (const Complex& z, bool deriv, bool scaled, octave_idx_type& ierr)
{
  double ar = 0.0;
  double ai = 0.0;

  octave_idx_type nz;

  double zr = z.real ();
  double zi = z.imag ();

  octave_idx_type id = deriv ? 1 : 0;

  F77_FUNC (zairy, ZAIRY) (zr, zi, id, 2, ar, ai, nz, ierr);

  if (! scaled)
    {
      Complex expz = exp (- 2.0 / 3.0 * z * sqrt(z));

      double rexpz = real (expz);
      double iexpz = imag (expz);

      double tmp = ar*rexpz - ai*iexpz;

      ai = ar*iexpz + ai*rexpz;
      ar = tmp;
    }

  if (zi == 0.0 && (! scaled || zr >= 0.0))
    ai = 0.0;

  return bessel_return_value (Complex (ar, ai), ierr);
}

Complex
biry (const Complex& z, bool deriv, bool scaled, octave_idx_type& ierr)
{
  double ar = 0.0;
  double ai = 0.0;

  double zr = z.real ();
  double zi = z.imag ();

  octave_idx_type id = deriv ? 1 : 0;

  F77_FUNC (zbiry, ZBIRY) (zr, zi, id, 2, ar, ai, ierr);

  if (! scaled)
    {
      Complex expz = exp (std::abs (real (2.0 / 3.0 * z * sqrt (z))));

      double rexpz = real (expz);
      double iexpz = imag (expz);

      double tmp = ar*rexpz - ai*iexpz;

      ai = ar*iexpz + ai*rexpz;
      ar = tmp;
    }

  if (zi == 0.0 && (! scaled || zr >= 0.0))
    ai = 0.0;

  return bessel_return_value (Complex (ar, ai), ierr);
}

ComplexMatrix
airy (const ComplexMatrix& z, bool deriv, bool scaled, Array2<octave_idx_type>& ierr)
{
  octave_idx_type nr = z.rows ();
  octave_idx_type nc = z.cols ();

  ComplexMatrix retval (nr, nc);

  ierr.resize (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = airy (z(i,j), deriv, scaled, ierr(i,j));

  return retval;
}

ComplexMatrix
biry (const ComplexMatrix& z, bool deriv, bool scaled, Array2<octave_idx_type>& ierr)
{
  octave_idx_type nr = z.rows ();
  octave_idx_type nc = z.cols ();

  ComplexMatrix retval (nr, nc);

  ierr.resize (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = biry (z(i,j), deriv, scaled, ierr(i,j));

  return retval;
}

ComplexNDArray
airy (const ComplexNDArray& z, bool deriv, bool scaled, ArrayN<octave_idx_type>& ierr)
{
  dim_vector dv = z.dims ();
  octave_idx_type nel = dv.numel ();
  ComplexNDArray retval (dv);

  ierr.resize (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    retval (i) = airy (z(i), deriv, scaled, ierr(i));

  return retval;
}

ComplexNDArray
biry (const ComplexNDArray& z, bool deriv, bool scaled, ArrayN<octave_idx_type>& ierr)
{
  dim_vector dv = z.dims ();
  octave_idx_type nel = dv.numel ();
  ComplexNDArray retval (dv);

  ierr.resize (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    retval (i) = biry (z(i), deriv, scaled, ierr(i));

  return retval;
}

FloatComplex
airy (const FloatComplex& z, bool deriv, bool scaled, octave_idx_type& ierr)
{
  float ar = 0.0;
  float ai = 0.0;

  octave_idx_type nz;

  float zr = z.real ();
  float zi = z.imag ();

  octave_idx_type id = deriv ? 1 : 0;

  F77_FUNC (cairy, CAIRY) (zr, zi, id, 2, ar, ai, nz, ierr);

  if (! scaled)
    {
      FloatComplex expz = exp (- static_cast<float> (2.0 / 3.0) * z * sqrt(z));

      float rexpz = real (expz);
      float iexpz = imag (expz);

      float tmp = ar*rexpz - ai*iexpz;

      ai = ar*iexpz + ai*rexpz;
      ar = tmp;
    }

  if (zi == 0.0 && (! scaled || zr >= 0.0))
    ai = 0.0;

  return bessel_return_value (FloatComplex (ar, ai), ierr);
}

FloatComplex
biry (const FloatComplex& z, bool deriv, bool scaled, octave_idx_type& ierr)
{
  float ar = 0.0;
  float ai = 0.0;

  float zr = z.real ();
  float zi = z.imag ();

  octave_idx_type id = deriv ? 1 : 0;

  F77_FUNC (cbiry, CBIRY) (zr, zi, id, 2, ar, ai, ierr);

  if (! scaled)
    {
      FloatComplex expz = exp (std::abs (real (static_cast<float> (2.0 / 3.0) * z * sqrt (z))));

      float rexpz = real (expz);
      float iexpz = imag (expz);

      float tmp = ar*rexpz - ai*iexpz;

      ai = ar*iexpz + ai*rexpz;
      ar = tmp;
    }

  if (zi == 0.0 && (! scaled || zr >= 0.0))
    ai = 0.0;

  return bessel_return_value (FloatComplex (ar, ai), ierr);
}

FloatComplexMatrix
airy (const FloatComplexMatrix& z, bool deriv, bool scaled, Array2<octave_idx_type>& ierr)
{
  octave_idx_type nr = z.rows ();
  octave_idx_type nc = z.cols ();

  FloatComplexMatrix retval (nr, nc);

  ierr.resize (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = airy (z(i,j), deriv, scaled, ierr(i,j));

  return retval;
}

FloatComplexMatrix
biry (const FloatComplexMatrix& z, bool deriv, bool scaled, Array2<octave_idx_type>& ierr)
{
  octave_idx_type nr = z.rows ();
  octave_idx_type nc = z.cols ();

  FloatComplexMatrix retval (nr, nc);

  ierr.resize (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = biry (z(i,j), deriv, scaled, ierr(i,j));

  return retval;
}

FloatComplexNDArray
airy (const FloatComplexNDArray& z, bool deriv, bool scaled, ArrayN<octave_idx_type>& ierr)
{
  dim_vector dv = z.dims ();
  octave_idx_type nel = dv.numel ();
  FloatComplexNDArray retval (dv);

  ierr.resize (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    retval (i) = airy (z(i), deriv, scaled, ierr(i));

  return retval;
}

FloatComplexNDArray
biry (const FloatComplexNDArray& z, bool deriv, bool scaled, ArrayN<octave_idx_type>& ierr)
{
  dim_vector dv = z.dims ();
  octave_idx_type nel = dv.numel ();
  FloatComplexNDArray retval (dv);

  ierr.resize (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    retval (i) = biry (z(i), deriv, scaled, ierr(i));

  return retval;
}

static void
gripe_betainc_nonconformant (octave_idx_type r1, octave_idx_type c1, octave_idx_type r2, octave_idx_type c2, octave_idx_type r3,
			     octave_idx_type c3)
{
  (*current_liboctave_error_handler)
   ("betainc: nonconformant arguments (x is %dx%d, a is %dx%d, b is %dx%d)",
     r1, c1, r2, c2, r3, c3);
}

static dim_vector null_dims (0);

static void
gripe_betainc_nonconformant (const dim_vector& d1, const dim_vector& d2,
			     const dim_vector& d3)
{
  std::string d1_str = d1.str ();
  std::string d2_str = d2.str ();
  std::string d3_str = d3.str ();

  (*current_liboctave_error_handler)
  ("betainc: nonconformant arguments (x is %s, a is %s, b is %s)",
   d1_str.c_str (), d2_str.c_str (), d3_str.c_str ());
}

double
betainc (double x, double a, double b)
{
  double retval;
  F77_XFCN (xdbetai, XDBETAI, (x, a, b, retval));
  return retval;
}

Matrix
betainc (double x, double a, const Matrix& b)
{
  octave_idx_type nr = b.rows ();
  octave_idx_type nc = b.cols ();

  Matrix retval (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = betainc (x, a, b(i,j));

  return retval;
}

Matrix
betainc (double x, const Matrix& a, double b)
{
  octave_idx_type nr = a.rows ();
  octave_idx_type nc = a.cols ();

  Matrix retval (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = betainc (x, a(i,j), b);

  return retval;
}

Matrix
betainc (double x, const Matrix& a, const Matrix& b)
{
  Matrix retval;

  octave_idx_type a_nr = a.rows ();
  octave_idx_type a_nc = a.cols ();

  octave_idx_type b_nr = b.rows ();
  octave_idx_type b_nc = b.cols ();

  if (a_nr == b_nr && a_nc == b_nc)
    {
      retval.resize (a_nr, a_nc);

      for (octave_idx_type j = 0; j < a_nc; j++)
	for (octave_idx_type i = 0; i < a_nr; i++)
	  retval(i,j) = betainc (x, a(i,j), b(i,j));
    }
  else
    gripe_betainc_nonconformant (1, 1, a_nr, a_nc, b_nr, b_nc);

  return retval;
}

NDArray
betainc (double x, double a, const NDArray& b)
{
  dim_vector dv = b.dims ();
  octave_idx_type nel = dv.numel ();

  NDArray retval (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    retval (i) = betainc (x, a, b(i));

  return retval;
}

NDArray
betainc (double x, const NDArray& a, double b)
{
  dim_vector dv = a.dims ();
  octave_idx_type nel = dv.numel ();

  NDArray retval (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    retval (i) = betainc (x, a(i), b);

  return retval;
}

NDArray
betainc (double x, const NDArray& a, const NDArray& b)
{
  NDArray retval;
  dim_vector dv = a.dims ();

  if (dv == b.dims ())
    {
      octave_idx_type nel = dv.numel ();

      retval.resize (dv);

      for (octave_idx_type i = 0; i < nel; i++)
	retval (i) = betainc (x, a(i), b(i));
    }
  else
    gripe_betainc_nonconformant (dim_vector (0), dv, b.dims ());
  
  return retval;
}


Matrix
betainc (const Matrix& x, double a, double b)
{
  octave_idx_type nr = x.rows ();
  octave_idx_type nc = x.cols ();

  Matrix retval (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = betainc (x(i,j), a, b);

  return retval;
}

Matrix
betainc (const Matrix& x, double a, const Matrix& b)
{
  Matrix retval;

  octave_idx_type nr = x.rows ();
  octave_idx_type nc = x.cols ();

  octave_idx_type b_nr = b.rows ();
  octave_idx_type b_nc = b.cols ();

  if (nr == b_nr && nc == b_nc)
    {
      retval.resize (nr, nc);

      for (octave_idx_type j = 0; j < nc; j++)
	for (octave_idx_type i = 0; i < nr; i++)
	  retval(i,j) = betainc (x(i,j), a, b(i,j));
    }
  else
    gripe_betainc_nonconformant (nr, nc, 1, 1, b_nr, b_nc);

  return retval;
}

Matrix
betainc (const Matrix& x, const Matrix& a, double b)
{
  Matrix retval;

  octave_idx_type nr = x.rows ();
  octave_idx_type nc = x.cols ();

  octave_idx_type a_nr = a.rows ();
  octave_idx_type a_nc = a.cols ();

  if (nr == a_nr && nc == a_nc)
    {
      retval.resize (nr, nc);

      for (octave_idx_type j = 0; j < nc; j++)
	for (octave_idx_type i = 0; i < nr; i++)
	  retval(i,j) = betainc (x(i,j), a(i,j), b);
    }
  else
    gripe_betainc_nonconformant (nr, nc, a_nr, a_nc, 1, 1);

  return retval;
}

Matrix
betainc (const Matrix& x, const Matrix& a, const Matrix& b)
{
  Matrix retval;

  octave_idx_type nr = x.rows ();
  octave_idx_type nc = x.cols ();

  octave_idx_type a_nr = a.rows ();
  octave_idx_type a_nc = a.cols ();

  octave_idx_type b_nr = b.rows ();
  octave_idx_type b_nc = b.cols ();

  if (nr == a_nr && nr == b_nr && nc == a_nc && nc == b_nc)
    {
      retval.resize (nr, nc);

      for (octave_idx_type j = 0; j < nc; j++)
	for (octave_idx_type i = 0; i < nr; i++)
	  retval(i,j) = betainc (x(i,j), a(i,j), b(i,j));
    }
  else
    gripe_betainc_nonconformant (nr, nc, a_nr, a_nc, b_nr, b_nc);

  return retval;
}

NDArray
betainc (const NDArray& x, double a, double b)
{
  dim_vector dv = x.dims ();
  octave_idx_type nel = dv.numel ();

  NDArray retval (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    retval (i) = betainc (x(i), a, b);

  return retval;
}

NDArray
betainc (const NDArray& x, double a, const NDArray& b)
{
  NDArray retval;
  dim_vector dv = x.dims ();

  if (dv == b.dims ())
    {
      octave_idx_type nel = dv.numel ();

      retval.resize (dv);

      for (octave_idx_type i = 0; i < nel; i++)
	retval (i) = betainc (x(i), a, b(i));
    }
  else
    gripe_betainc_nonconformant (dv, dim_vector (0), b.dims ());
  
  return retval;
}

NDArray
betainc (const NDArray& x, const NDArray& a, double b)
{
  NDArray retval;
  dim_vector dv = x.dims ();

  if (dv == a.dims ())
    {
      octave_idx_type nel = dv.numel ();

      retval.resize (dv);

      for (octave_idx_type i = 0; i < nel; i++)
	retval (i) = betainc (x(i), a(i), b);
    }
  else
    gripe_betainc_nonconformant (dv, a.dims (), dim_vector (0));
  
  return retval;
}

NDArray
betainc (const NDArray& x, const NDArray& a, const NDArray& b)
{
  NDArray retval;
  dim_vector dv = x.dims ();

  if (dv == a.dims () && dv == b.dims ())
    {
      octave_idx_type nel = dv.numel ();

      retval.resize (dv);

      for (octave_idx_type i = 0; i < nel; i++)
	retval (i) = betainc (x(i), a(i), b(i));
    }
  else
    gripe_betainc_nonconformant (dv, a.dims (), b.dims ());

  return retval;
}

float
betainc (float x, float a, float b)
{
  float retval;
  F77_XFCN (xbetai, XBETAI, (x, a, b, retval));
  return retval;
}

FloatMatrix
betainc (float x, float a, const FloatMatrix& b)
{
  octave_idx_type nr = b.rows ();
  octave_idx_type nc = b.cols ();

  FloatMatrix retval (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = betainc (x, a, b(i,j));

  return retval;
}

FloatMatrix
betainc (float x, const FloatMatrix& a, float b)
{
  octave_idx_type nr = a.rows ();
  octave_idx_type nc = a.cols ();

  FloatMatrix retval (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = betainc (x, a(i,j), b);

  return retval;
}

FloatMatrix
betainc (float x, const FloatMatrix& a, const FloatMatrix& b)
{
  FloatMatrix retval;

  octave_idx_type a_nr = a.rows ();
  octave_idx_type a_nc = a.cols ();

  octave_idx_type b_nr = b.rows ();
  octave_idx_type b_nc = b.cols ();

  if (a_nr == b_nr && a_nc == b_nc)
    {
      retval.resize (a_nr, a_nc);

      for (octave_idx_type j = 0; j < a_nc; j++)
	for (octave_idx_type i = 0; i < a_nr; i++)
	  retval(i,j) = betainc (x, a(i,j), b(i,j));
    }
  else
    gripe_betainc_nonconformant (1, 1, a_nr, a_nc, b_nr, b_nc);

  return retval;
}

FloatNDArray
betainc (float x, float a, const FloatNDArray& b)
{
  dim_vector dv = b.dims ();
  octave_idx_type nel = dv.numel ();

  FloatNDArray retval (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    retval (i) = betainc (x, a, b(i));

  return retval;
}

FloatNDArray
betainc (float x, const FloatNDArray& a, float b)
{
  dim_vector dv = a.dims ();
  octave_idx_type nel = dv.numel ();

  FloatNDArray retval (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    retval (i) = betainc (x, a(i), b);

  return retval;
}

FloatNDArray
betainc (float x, const FloatNDArray& a, const FloatNDArray& b)
{
  FloatNDArray retval;
  dim_vector dv = a.dims ();

  if (dv == b.dims ())
    {
      octave_idx_type nel = dv.numel ();

      retval.resize (dv);

      for (octave_idx_type i = 0; i < nel; i++)
	retval (i) = betainc (x, a(i), b(i));
    }
  else
    gripe_betainc_nonconformant (dim_vector (0), dv, b.dims ());
  
  return retval;
}


FloatMatrix
betainc (const FloatMatrix& x, float a, float b)
{
  octave_idx_type nr = x.rows ();
  octave_idx_type nc = x.cols ();

  FloatMatrix retval (nr, nc);

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      retval(i,j) = betainc (x(i,j), a, b);

  return retval;
}

FloatMatrix
betainc (const FloatMatrix& x, float a, const FloatMatrix& b)
{
  FloatMatrix retval;

  octave_idx_type nr = x.rows ();
  octave_idx_type nc = x.cols ();

  octave_idx_type b_nr = b.rows ();
  octave_idx_type b_nc = b.cols ();

  if (nr == b_nr && nc == b_nc)
    {
      retval.resize (nr, nc);

      for (octave_idx_type j = 0; j < nc; j++)
	for (octave_idx_type i = 0; i < nr; i++)
	  retval(i,j) = betainc (x(i,j), a, b(i,j));
    }
  else
    gripe_betainc_nonconformant (nr, nc, 1, 1, b_nr, b_nc);

  return retval;
}

FloatMatrix
betainc (const FloatMatrix& x, const FloatMatrix& a, float b)
{
  FloatMatrix retval;

  octave_idx_type nr = x.rows ();
  octave_idx_type nc = x.cols ();

  octave_idx_type a_nr = a.rows ();
  octave_idx_type a_nc = a.cols ();

  if (nr == a_nr && nc == a_nc)
    {
      retval.resize (nr, nc);

      for (octave_idx_type j = 0; j < nc; j++)
	for (octave_idx_type i = 0; i < nr; i++)
	  retval(i,j) = betainc (x(i,j), a(i,j), b);
    }
  else
    gripe_betainc_nonconformant (nr, nc, a_nr, a_nc, 1, 1);

  return retval;
}

FloatMatrix
betainc (const FloatMatrix& x, const FloatMatrix& a, const FloatMatrix& b)
{
  FloatMatrix retval;

  octave_idx_type nr = x.rows ();
  octave_idx_type nc = x.cols ();

  octave_idx_type a_nr = a.rows ();
  octave_idx_type a_nc = a.cols ();

  octave_idx_type b_nr = b.rows ();
  octave_idx_type b_nc = b.cols ();

  if (nr == a_nr && nr == b_nr && nc == a_nc && nc == b_nc)
    {
      retval.resize (nr, nc);

      for (octave_idx_type j = 0; j < nc; j++)
	for (octave_idx_type i = 0; i < nr; i++)
	  retval(i,j) = betainc (x(i,j), a(i,j), b(i,j));
    }
  else
    gripe_betainc_nonconformant (nr, nc, a_nr, a_nc, b_nr, b_nc);

  return retval;
}

FloatNDArray
betainc (const FloatNDArray& x, float a, float b)
{
  dim_vector dv = x.dims ();
  octave_idx_type nel = dv.numel ();

  FloatNDArray retval (dv);

  for (octave_idx_type i = 0; i < nel; i++)
    retval (i) = betainc (x(i), a, b);

  return retval;
}

FloatNDArray
betainc (const FloatNDArray& x, float a, const FloatNDArray& b)
{
  FloatNDArray retval;
  dim_vector dv = x.dims ();

  if (dv == b.dims ())
    {
      octave_idx_type nel = dv.numel ();

      retval.resize (dv);

      for (octave_idx_type i = 0; i < nel; i++)
	retval (i) = betainc (x(i), a, b(i));
    }
  else
    gripe_betainc_nonconformant (dv, dim_vector (0), b.dims ());
  
  return retval;
}

FloatNDArray
betainc (const FloatNDArray& x, const FloatNDArray& a, float b)
{
  FloatNDArray retval;
  dim_vector dv = x.dims ();

  if (dv == a.dims ())
    {
      octave_idx_type nel = dv.numel ();

      retval.resize (dv);

      for (octave_idx_type i = 0; i < nel; i++)
	retval (i) = betainc (x(i), a(i), b);
    }
  else
    gripe_betainc_nonconformant (dv, a.dims (), dim_vector (0));
  
  return retval;
}

FloatNDArray
betainc (const FloatNDArray& x, const FloatNDArray& a, const FloatNDArray& b)
{
  FloatNDArray retval;
  dim_vector dv = x.dims ();

  if (dv == a.dims () && dv == b.dims ())
    {
      octave_idx_type nel = dv.numel ();

      retval.resize (dv);

      for (octave_idx_type i = 0; i < nel; i++)
	retval (i) = betainc (x(i), a(i), b(i));
    }
  else
    gripe_betainc_nonconformant (dv, a.dims (), b.dims ());

  return retval;
}

// FIXME -- there is still room for improvement here...

double
gammainc (double x, double a, bool& err)
{
  double retval;

  err = false;

  if (a < 0.0 || x < 0.0)
    {
      (*current_liboctave_error_handler)
	("gammainc: A and X must be non-negative");

      err = true;
    }
  else
    F77_XFCN (xgammainc, XGAMMAINC, (a, x, retval));

  return retval;
}

Matrix
gammainc (double x, const Matrix& a)
{
  octave_idx_type nr = a.rows ();
  octave_idx_type nc = a.cols ();

  Matrix result (nr, nc);
  Matrix retval;

  bool err;

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      {
	result(i,j) = gammainc (x, a(i,j), err);

	if (err)
	  goto done;
      }

  retval = result;

 done:

  return retval;
}

Matrix
gammainc (const Matrix& x, double a)
{
  octave_idx_type nr = x.rows ();
  octave_idx_type nc = x.cols ();

  Matrix result (nr, nc);
  Matrix retval;

  bool err;

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      {
	result(i,j) = gammainc (x(i,j), a, err);

	if (err)
	  goto done;
      }

  retval = result;

 done:

  return retval;
}

Matrix
gammainc (const Matrix& x, const Matrix& a)
{
  Matrix result;
  Matrix retval;

  octave_idx_type nr = x.rows ();
  octave_idx_type nc = x.cols ();

  octave_idx_type a_nr = a.rows ();
  octave_idx_type a_nc = a.cols ();

  if (nr == a_nr && nc == a_nc)
    {
      result.resize (nr, nc);

      bool err;

      for (octave_idx_type j = 0; j < nc; j++)
	for (octave_idx_type i = 0; i < nr; i++)
	  {
	    result(i,j) = gammainc (x(i,j), a(i,j), err);

	    if (err)
	      goto done;
	  }

      retval = result;
    }
  else
    (*current_liboctave_error_handler)
      ("gammainc: nonconformant arguments (arg 1 is %dx%d, arg 2 is %dx%d)",
       nr, nc, a_nr, a_nc);

 done:

  return retval;
}

NDArray
gammainc (double x, const NDArray& a)
{
  dim_vector dv = a.dims ();
  octave_idx_type nel = dv.numel ();

  NDArray retval;
  NDArray result (dv);

  bool err;

  for (octave_idx_type i = 0; i < nel; i++)
    {
      result (i) = gammainc (x, a(i), err);

      if (err)
	goto done;
    }

  retval = result;

 done:

  return retval;
}

NDArray
gammainc (const NDArray& x, double a)
{
  dim_vector dv = x.dims ();
  octave_idx_type nel = dv.numel ();

  NDArray retval;
  NDArray result (dv);

  bool err;

  for (octave_idx_type i = 0; i < nel; i++)
    {
      result (i) = gammainc (x(i), a, err);

      if (err)
	goto done;
    }

  retval = result;

 done:

  return retval;
}

NDArray
gammainc (const NDArray& x, const NDArray& a)
{
  dim_vector dv = x.dims ();
  octave_idx_type nel = dv.numel ();

  NDArray retval;
  NDArray result;

  if (dv == a.dims ())
    {
      result.resize (dv);

      bool err;

      for (octave_idx_type i = 0; i < nel; i++)
	{
	  result (i) = gammainc (x(i), a(i), err);
	  
	  if (err)
	    goto done;
	}

      retval = result;
    }
  else
    {
      std::string x_str = dv.str ();
      std::string a_str = a.dims ().str ();

      (*current_liboctave_error_handler)
	("gammainc: nonconformant arguments (arg 1 is %s, arg 2 is %s)",
	 x_str.c_str (), a_str. c_str ());
    }

 done:

  return retval;
}

float
gammainc (float x, float a, bool& err)
{
  float retval;

  err = false;

  if (a < 0.0 || x < 0.0)
    {
      (*current_liboctave_error_handler)
	("gammainc: A and X must be non-negative");

      err = true;
    }
  else
    F77_XFCN (xsgammainc, XSGAMMAINC, (a, x, retval));

  return retval;
}

FloatMatrix
gammainc (float x, const FloatMatrix& a)
{
  octave_idx_type nr = a.rows ();
  octave_idx_type nc = a.cols ();

  FloatMatrix result (nr, nc);
  FloatMatrix retval;

  bool err;

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      {
	result(i,j) = gammainc (x, a(i,j), err);

	if (err)
	  goto done;
      }

  retval = result;

 done:

  return retval;
}

FloatMatrix
gammainc (const FloatMatrix& x, float a)
{
  octave_idx_type nr = x.rows ();
  octave_idx_type nc = x.cols ();

  FloatMatrix result (nr, nc);
  FloatMatrix retval;

  bool err;

  for (octave_idx_type j = 0; j < nc; j++)
    for (octave_idx_type i = 0; i < nr; i++)
      {
	result(i,j) = gammainc (x(i,j), a, err);

	if (err)
	  goto done;
      }

  retval = result;

 done:

  return retval;
}

FloatMatrix
gammainc (const FloatMatrix& x, const FloatMatrix& a)
{
  FloatMatrix result;
  FloatMatrix retval;

  octave_idx_type nr = x.rows ();
  octave_idx_type nc = x.cols ();

  octave_idx_type a_nr = a.rows ();
  octave_idx_type a_nc = a.cols ();

  if (nr == a_nr && nc == a_nc)
    {
      result.resize (nr, nc);

      bool err;

      for (octave_idx_type j = 0; j < nc; j++)
	for (octave_idx_type i = 0; i < nr; i++)
	  {
	    result(i,j) = gammainc (x(i,j), a(i,j), err);

	    if (err)
	      goto done;
	  }

      retval = result;
    }
  else
    (*current_liboctave_error_handler)
      ("gammainc: nonconformant arguments (arg 1 is %dx%d, arg 2 is %dx%d)",
       nr, nc, a_nr, a_nc);

 done:

  return retval;
}

FloatNDArray
gammainc (float x, const FloatNDArray& a)
{
  dim_vector dv = a.dims ();
  octave_idx_type nel = dv.numel ();

  FloatNDArray retval;
  FloatNDArray result (dv);

  bool err;

  for (octave_idx_type i = 0; i < nel; i++)
    {
      result (i) = gammainc (x, a(i), err);

      if (err)
	goto done;
    }

  retval = result;

 done:

  return retval;
}

FloatNDArray
gammainc (const FloatNDArray& x, float a)
{
  dim_vector dv = x.dims ();
  octave_idx_type nel = dv.numel ();

  FloatNDArray retval;
  FloatNDArray result (dv);

  bool err;

  for (octave_idx_type i = 0; i < nel; i++)
    {
      result (i) = gammainc (x(i), a, err);

      if (err)
	goto done;
    }

  retval = result;

 done:

  return retval;
}

FloatNDArray
gammainc (const FloatNDArray& x, const FloatNDArray& a)
{
  dim_vector dv = x.dims ();
  octave_idx_type nel = dv.numel ();

  FloatNDArray retval;
  FloatNDArray result;

  if (dv == a.dims ())
    {
      result.resize (dv);

      bool err;

      for (octave_idx_type i = 0; i < nel; i++)
	{
	  result (i) = gammainc (x(i), a(i), err);
	  
	  if (err)
	    goto done;
	}

      retval = result;
    }
  else
    {
      std::string x_str = dv.str ();
      std::string a_str = a.dims ().str ();

      (*current_liboctave_error_handler)
	("gammainc: nonconformant arguments (arg 1 is %s, arg 2 is %s)",
	 x_str.c_str (), a_str. c_str ());
    }

 done:

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
