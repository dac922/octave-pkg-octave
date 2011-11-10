// N-D Array  manipulations.
/*

Copyright (C) 2004, 2005, 2006, 2007, 2009 John W. Eaton

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

#include "int8NDArray.h"
#include "mx-op-defs.h"
#include "intNDArray.cc"

template class OCTAVE_API intNDArray<octave_int8>;

template OCTAVE_API
std::ostream&
operator << (std::ostream& os, const intNDArray<octave_int8>& a);

template OCTAVE_API
std::istream&
operator >> (std::istream& is, intNDArray<octave_int8>& a);

NDS_CMP_OPS (int8NDArray, , octave_int8, )
NDS_BOOL_OPS (int8NDArray, octave_int8, octave_int8 (0))

SND_CMP_OPS (octave_int8, , int8NDArray, )
SND_BOOL_OPS (octave_int8, int8NDArray, octave_int8 (0))

NDND_CMP_OPS (int8NDArray, , int8NDArray, )
NDND_BOOL_OPS (int8NDArray, int8NDArray, octave_int8 (0))

MINMAX_FCNS (int8)

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
