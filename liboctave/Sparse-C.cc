/*

Copyright (C) 2004, 2005, 2007, 2008, 2009 David Bateman
Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003, 2004 Andy Adler

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

// Instantiate Sparse matrix of complex values.

#include "oct-cmplx.h"
#include "lo-mappers.h"
#include "lo-ieee.h"
#include "Sparse.h"
#include "Sparse.cc"


static double
xabs (const Complex& x)
{
  return (xisinf (x.real ()) || xisinf (x.imag ())) ? octave_Inf : abs (x);
}


template <>
bool
sparse_ascending_compare<Complex> (const Complex& a, const Complex& b)
{
  return (xisnan (b) || (xabs (a) < xabs (b))
	  || ((xabs (a) == xabs (b)) && (arg (a) < arg (b))));
}

template <>
bool
sparse_descending_compare<Complex> (const Complex& a, const Complex& b)
{
  return (xisnan (a) || (xabs (a) > xabs (b))
	  || ((xabs (a) == xabs (b)) && (arg (a) > arg (b))));
}

INSTANTIATE_SPARSE_AND_ASSIGN (Complex, OCTAVE_API);

INSTANTIATE_SPARSE_ASSIGN (Complex, double, OCTAVE_API);

#if 0
template std::ostream& operator << (std::ostream&, const Sparse<Complex>&);
#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
