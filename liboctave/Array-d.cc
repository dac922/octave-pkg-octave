/*

Copyright (C) 1994, 1995, 1996, 1997, 1998, 2000, 2001, 2003, 2004,
              2005, 2006, 2007, 2008, 2009 John W. Eaton

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

// Instantiate Arrays of double values.

#include "lo-mappers.h"
#include "Array.h"
#include "Array.cc"
#include "oct-locbuf.h"

#define INLINE_ASCENDING_SORT
#define INLINE_DESCENDING_SORT
#include "oct-sort.cc"

template <>
inline bool
sort_isnan<double> (double x)
{
  return xisnan (x);
}

static bool
nan_ascending_compare (double x, double y)
{
  return xisnan (y) ? ! xisnan (x) : x < y;
}

static bool
nan_descending_compare (double x, double y)
{
  return xisnan (x) ? ! xisnan (y) : x > y;
}

Array<double>::compare_fcn_type
sortrows_comparator (sortmode mode, const Array<double>& a , bool allow_chk)
{
  Array<double>::compare_fcn_type result = 0;

  if (allow_chk)
    {
      octave_idx_type k = 0;
      for (; k < a.numel () && ! xisnan (a(k)); k++) ;
      if (k == a.numel ())
        {
          if (mode == ASCENDING)
            result = octave_sort<double>::ascending_compare;
          else if (mode == DESCENDING)
            result = octave_sort<double>::descending_compare;
        }
    }

  if (! result)
    {
      if (mode == ASCENDING)
        result = nan_ascending_compare;
      else if (mode == DESCENDING)
        result = nan_descending_compare;
    }

  return result;
}

INSTANTIATE_ARRAY_SORT (double);

INSTANTIATE_ARRAY (double, OCTAVE_API);

#include "Array2.h"

template class OCTAVE_API Array2<double>;

#include "ArrayN.h"
#include "ArrayN.cc"

template class OCTAVE_API ArrayN<double>;

template OCTAVE_API std::ostream& operator << (std::ostream&, const ArrayN<double>&);

#include "DiagArray2.h"
#include "DiagArray2.cc"

#ifdef _MSC_VER
template class OCTAVE_API DiagArray2<double>::Proxy;
#endif
template class OCTAVE_API DiagArray2<double>;

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
