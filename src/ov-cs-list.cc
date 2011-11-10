/*

Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 John W. Eaton

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
#include <sstream>

#include "lo-utils.h"

#include "defun.h"
#include "error.h"
#include "ov-cs-list.h"
#include "unwind-prot.h"

DEFINE_OCTAVE_ALLOCATOR (octave_cs_list);

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_cs_list, "cs-list", "cs-list");

octave_cs_list::octave_cs_list (const Cell& c)
  : octave_base_value (), lst (c)
{
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
