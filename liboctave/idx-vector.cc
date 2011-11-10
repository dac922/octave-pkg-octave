/*

Copyright (C) 2008, 2009 Jaroslav Hajek
Copyright (C) 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2002,
              2003, 2004, 2005, 2006, 2007 John W. Eaton

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

#include <cstdlib>

#include <iostream>

#include "idx-vector.h"
#include "Array.h"
#include "Sparse.h"
#include "Range.h"

#include "oct-locbuf.h"
#include "lo-error.h"
#include "lo-mappers.h"

static void
gripe_invalid_index (void)
{
  (*current_liboctave_error_handler)
    ("subscript indices must be either positive integers or logicals.");
}

static void
gripe_invalid_range (void)
{
  (*current_liboctave_error_handler)
    ("invalid range used as index.");
}

static void
gripe_index_out_of_range (void)
{
  (*current_liboctave_error_handler)
    ("internal error: idx_vector index out of range.");
}

DEFINE_OCTAVE_ALLOCATOR(idx_vector::idx_colon_rep);

idx_vector::idx_colon_rep::idx_colon_rep (char c)
{
  if (c != ':')
    {
      (*current_liboctave_error_handler)
        ("internal error: invalid character converted to idx_vector. Must be ':'.");
      err = true;
    }
}

octave_idx_type
idx_vector::idx_colon_rep::checkelem (octave_idx_type i) const
{
  if (i < 0)
    {
      gripe_index_out_of_range ();
      return 0;
    }
  else
    return i;
}

std::ostream& 
idx_vector::idx_colon_rep::print (std::ostream& os) const
{
  return os << ":";
}

DEFINE_OCTAVE_ALLOCATOR(idx_vector::idx_range_rep);

idx_vector::idx_range_rep::idx_range_rep (octave_idx_type _start, octave_idx_type _limit,
                                          octave_idx_type _step)
 : start(_start), len (_step ? (_limit - _start) / _step : -1), step (_step)
{
  if (len < 0)
    {
      gripe_invalid_range ();
      err = true;
    }
  else if (start < 0)
    {
      gripe_invalid_index ();
      err = true;
    }
}

idx_vector::idx_range_rep::idx_range_rep (const Range& r)
  : start (0), len (r.nelem ()), step (1)
{
  if (len < 0)
    {
      gripe_invalid_range ();
      err = true;
    }
  else if (len > 0)
    {
      if (r.all_elements_are_ints ())
        {    
          start = static_cast<octave_idx_type> (r.base ()) - 1;
          step = static_cast<octave_idx_type> (r.inc ());
          if (start < 0 || (step < 0 && start + (len-1)*step < 0))
            {
              gripe_invalid_index ();
              err = true;
            }
        }
      else
        {
          gripe_invalid_index ();
          err = true;
        }
    }
}

octave_idx_type
idx_vector::idx_range_rep::checkelem (octave_idx_type i) const
{
  if (i < 0 || i >= len)
    {
      gripe_index_out_of_range ();
      return 0;
    }
  else
    return start + i*step;
}

idx_vector::idx_base_rep *
idx_vector::idx_range_rep::sort_uniq_clone (bool)
{
  if (step < 0)
    return new idx_range_rep (start + (len - 1)*step, len, -step, DIRECT);
  else
    {
      count++;
      return this;
    }
}

std::ostream& 
idx_vector::idx_range_rep::print (std::ostream& os) const
{
  os << start << ':' << step << ':' << start + len*step;
  return os;
}

inline octave_idx_type
convert_index (octave_idx_type i, bool& conv_error, 
               octave_idx_type& ext)
{
  if (i <= 0) 
    conv_error = true;
  if (ext < i) ext = i;
  return i - 1;
}

inline octave_idx_type
convert_index (double x, bool& conv_error, octave_idx_type& ext)
{
  octave_idx_type i = static_cast<octave_idx_type> (x);
  if (static_cast<double> (i) != x)
    conv_error = true;

  return convert_index (i, conv_error, ext);
}

inline octave_idx_type
convert_index (float x, bool& conv_error, octave_idx_type& ext)
{
  return convert_index (static_cast<double> (x), conv_error, ext);
}

template <class T>
inline octave_idx_type
convert_index (octave_int<T> x, bool& conv_error, 
               octave_idx_type& ext)
{
  octave_idx_type i = octave_int<octave_idx_type> (x).value ();
  return convert_index (i, conv_error, ext);
}

DEFINE_OCTAVE_ALLOCATOR(idx_vector::idx_scalar_rep);

template <class T>
idx_vector::idx_scalar_rep::idx_scalar_rep (T x)
{
  octave_idx_type dummy;
  data = convert_index (x, err, dummy);
  if (err) gripe_invalid_index ();
}

idx_vector::idx_scalar_rep::idx_scalar_rep (octave_idx_type i) 
  : data (i)
{
  if (data < 0) 
    {
      gripe_invalid_index ();
      err = true;
    }
}

octave_idx_type
idx_vector::idx_scalar_rep::checkelem (octave_idx_type i) const
{
  if (i != 0) gripe_index_out_of_range ();
  return data;
}

std::ostream& idx_vector::idx_scalar_rep::print (std::ostream& os) const
{
  return os << data;
}

DEFINE_OCTAVE_ALLOCATOR(idx_vector::idx_vector_rep);

template <class T>
idx_vector::idx_vector_rep::idx_vector_rep (const Array<T>& nda)
  : data (0), len (nda.numel ()), ext (0), aowner (0), orig_dims (nda.dims ())
{
  if (len != 0)
    {
      octave_idx_type *d = new octave_idx_type[len];
      for (octave_idx_type i = 0; i < len; i++)
        d[i] = convert_index (nda.xelem (i), err, ext);
      data = d;

      if (err) gripe_invalid_index ();
    }
}

// Note that this makes a shallow copy of the index array.

idx_vector::idx_vector_rep::idx_vector_rep (const Array<octave_idx_type>& inda)
  : data (inda.data ()), len (inda.numel ()), ext (0), 
  aowner (new Array<octave_idx_type> (inda)), orig_dims (inda.dims ())
{
  if (len != 0)
    {
      octave_idx_type max = -1;
      for (octave_idx_type i = 0; i < len; i++)
        {
          octave_idx_type k = inda.xelem (i);
          if (k < 0) 
            err = true;
          else if (k > max) 
            max = k;
        }

      ext = max + 1;

      if (err) gripe_invalid_index ();
    }
}

idx_vector::idx_vector_rep::idx_vector_rep (bool b)
  : data (0), len (b ? 1 : 0), ext (0), aowner (0), orig_dims (len, len)
{
  if (len != 0)
    {
      octave_idx_type *d = new octave_idx_type [1];
      d[0] = 0;
      data = d;
      ext = 1;
    }
}

idx_vector::idx_vector_rep::idx_vector_rep (const Array<bool>& bnda)
  : data (0), len (0), ext (0), aowner (0), orig_dims ()
{
  for (octave_idx_type i = 0, l = bnda.numel (); i < l; i++)
    if (bnda.xelem (i)) len++;

  const dim_vector dv = bnda.dims ();

  if (! dv.all_zero ())
    orig_dims = ((dv.length () == 2 && dv(0) == 1) 
                 ? dim_vector (1, len) : dim_vector (len, 1));

  if (len != 0)
    {
      octave_idx_type *d = new octave_idx_type [len];

      octave_idx_type ntot = bnda.length ();

      octave_idx_type k = 0;
      for (octave_idx_type i = 0; i < ntot; i++)
	if (bnda.xelem (i)) d[k++] = i;

      data = d;

      ext = d[k-1] + 1;
    }
}

idx_vector::idx_vector_rep::idx_vector_rep (const Sparse<bool>& bnda)
  : data (0), len (0), ext (0), aowner (0), orig_dims ()
{
  for (octave_idx_type i = 0, l = bnda.nnz (); i < l; i++)
    if (bnda.data (i)) len++;

  dim_vector dv = bnda.dims ();

  orig_dims = ((dv.length () == 2 && dv(0) == 1)
	       ? dim_vector (1, len) : orig_dims = dim_vector (len, 1));

  if (len != 0)
    {
      octave_idx_type *d = new octave_idx_type [len];

      octave_idx_type nnz = bnda.nnz ();

      octave_idx_type k = 0;
      // FIXME: I hope this is OK, i.e. the element iterated this way are correctly ordered.
      for (octave_idx_type i = 0; i < nnz; i++)
        {
          if (bnda.data (i)) 
            d[k++] = bnda.cidx (i) + bnda.rows () * bnda.ridx (i);
        }

      data = d;

      ext = d[k-1] + 1;
    }
}

idx_vector::idx_vector_rep::~idx_vector_rep (void)
{ 
  if (aowner) 
    delete aowner;
  else
    delete [] data; 
}

octave_idx_type
idx_vector::idx_vector_rep::checkelem (octave_idx_type n) const
{
  if (n < 0 || n >= len)
    {
      gripe_invalid_index ();
      return 0;
    }

  return xelem (n);
}

idx_vector::idx_base_rep *
idx_vector::idx_vector_rep::sort_uniq_clone (bool uniq)
{
  octave_idx_type *new_data = new octave_idx_type[len];
  std::copy (data, data + len, new_data);
  std::sort (new_data, new_data + len);
  octave_idx_type new_len;
  if (uniq)
    new_len = std::unique (new_data, new_data + len) - new_data;
  else 
    new_len = len;

  return new idx_vector_rep (new_data, new_len, ext, orig_dims, DIRECT);
}

std::ostream& 
idx_vector::idx_vector_rep::print (std::ostream& os) const
{
  os << '[';
  for (octave_idx_type ii = 0; ii < len - 1; ii++)
    os << data[ii] << ',' << ' ';
  if (len > 0) os << data[len-1]; os << ']';

  return os;
}

const idx_vector idx_vector::colon (new idx_vector::idx_colon_rep ());

bool idx_vector::maybe_reduce (octave_idx_type n, const idx_vector& j,
                               octave_idx_type nj)
{
  bool reduced = false;

  // Empty index always reduces.
  if (rep->length (n) == 0)
    {
      *this = idx_vector ();
      return true;
    }

  // Possibly skip singleton dims.
  if (n == 1 && rep->is_colon_equiv (n))
    {
      *this = j;
      return true;
    }

  if (nj == 1 && j.is_colon_equiv (nj))
    return true;

  switch (j.idx_class ())
    {
    case class_colon:
      if (rep->is_colon_equiv (n))
        {
          // (:,:) reduces to (:)
          *this = colon;
          reduced = true;
        }
      else if (rep->idx_class () == class_scalar)
        {
          // (i,:) reduces to a range.
          idx_scalar_rep * r = dynamic_cast<idx_scalar_rep *> (rep);
          octave_idx_type k = r->get_data ();
          *this = new idx_range_rep (k, nj, n, DIRECT);
          reduced = true;
        }
      break;
    case class_range:
      if (rep->is_colon_equiv (n))
        {
          // (:,i:j) reduces to a range (the step must be 1)
          idx_range_rep * rj = dynamic_cast<idx_range_rep *> (j.rep);
          if (rj->get_step () == 1)
            {
              octave_idx_type s = rj->get_start (), l = rj->length (nj);
              *this = new idx_range_rep (s * n, l * n, 1, DIRECT);
              reduced = true;
            }
        }
      else if (rep->idx_class () == class_scalar)
        {
          // (k,i:d:j) reduces to a range.
          idx_scalar_rep * r = dynamic_cast<idx_scalar_rep *> (rep);
          idx_range_rep * rj = dynamic_cast<idx_range_rep *> (j.rep);
          octave_idx_type k = r->get_data ();
          octave_idx_type s = rj->get_start (), l = rj->length (nj);
          octave_idx_type t = rj->get_step ();
          *this = new idx_range_rep (n * s + k, l, n * t, DIRECT);
          reduced = true;
        }
      break;
    case class_scalar:
      switch (rep->idx_class ())
        {
        case class_scalar:
          {
            // (i,j) reduces to a single index.
            idx_scalar_rep * r = dynamic_cast<idx_scalar_rep *> (rep);
            idx_scalar_rep * rj = dynamic_cast<idx_scalar_rep *> (j.rep);
            octave_idx_type k = r->get_data () + n * rj->get_data ();
            *this = new idx_scalar_rep (k, DIRECT);
            reduced = true;
          }
          break;
        case class_range:
          {
            // (i:d:j,k) reduces to a range.
            idx_range_rep * r = dynamic_cast<idx_range_rep *> (rep);
            idx_scalar_rep * rj = dynamic_cast<idx_scalar_rep *> (j.rep);
            octave_idx_type s = r->get_start (), l = r->length (nj);
            octave_idx_type t = r->get_step ();
            octave_idx_type k = rj->get_data ();
            *this = new idx_range_rep (n * k + s, l, t, DIRECT);
            reduced = true;
          }
          break;
        case class_colon:
          {
            // (:,k) reduces to a range.
            idx_scalar_rep * rj = dynamic_cast<idx_scalar_rep *> (j.rep);
            octave_idx_type k = rj->get_data ();
            *this = new idx_range_rep (n * k, n, 1, DIRECT);
            reduced = true;
          }
          break;
        default:
          break;
        }
      break;
    default:
      break;
    }

  return reduced;
}

bool
idx_vector::is_cont_range (octave_idx_type n,
			   octave_idx_type& l, octave_idx_type& u) const
{
  bool res = false;
  switch (rep->idx_class ())
    {
    case class_colon:
      l = 0; u = n;
      res = true;
      break;
    case class_range:
      {
        idx_range_rep * r = dynamic_cast<idx_range_rep *> (rep);
        if (r->get_step () == 1)
          {
            l = r->get_start ();
            u = l + r->length (n);
            res = true;
          }
      }
      break;
    case class_scalar:
      {
        idx_scalar_rep * r = dynamic_cast<idx_scalar_rep *> (rep);
        l = r->get_data ();
        u = l + 1;
        res = true;
      }
      break;
    default:
      break;
    }

  return res;
}

idx_vector
idx_vector::complement (octave_idx_type n) const
{
  OCTAVE_LOCAL_BUFFER_INIT (bool, left, n, true);

  octave_idx_type cnt = n;

  for (octave_idx_type i = 0, len = length (); i < len; i++)
    { 
      octave_idx_type k = xelem (i);
      if (k < n && left[k])
        {
          left[k] = false;
          cnt--;
        }
    }

  octave_idx_type len = cnt, *data = new octave_idx_type[len];
  for (octave_idx_type i = 0, j = 0; i < n; i++)
    if (left[i]) data[j++] = i;

  return new idx_vector_rep (data, len, 
                             len ? data[len-1]+1 : 0, 
                             dim_vector (1, len), DIRECT);
}

bool
idx_vector::is_permutation (octave_idx_type n) const
{
  bool retval = false;

  if (is_colon_equiv (n))
    retval = true;
  else if (length (n) == n && extent(n) == n)
    {
      OCTAVE_LOCAL_BUFFER_INIT (bool, left, n, true);

      retval = true;

      for (octave_idx_type i = 0, len = length (); i < len; i++)
        { 
          octave_idx_type k = xelem (i);
          if (left[k])
              left[k] = false;
          else
            {
              retval = false;
              break;
            }
        }

    }

  return retval;
}

octave_idx_type 
idx_vector::freeze (octave_idx_type z_len, const char *, bool resize_ok)
{
  if (! resize_ok && extent (z_len) > z_len)
    {
      (*current_liboctave_error_handler)
        ("invalid matrix index = %d", extent (z_len));
      rep->err = true;
      chkerr ();
    }

  return length (z_len);
}

octave_idx_type 
idx_vector::ones_count () const
{
  octave_idx_type n = 0;
  if (is_colon ())
    n = 1;
  else
    for (octave_idx_type i = 0; i < length (1); i++)
      if (xelem (i) == 0) n++;
  return n;
}

// Instantiate the octave_int constructors we want.
#define INSTANTIATE_SCALAR_VECTOR_REP_CONST(T) \
  template OCTAVE_API idx_vector::idx_scalar_rep::idx_scalar_rep (T); \
  template OCTAVE_API idx_vector::idx_vector_rep::idx_vector_rep (const Array<T>&);

INSTANTIATE_SCALAR_VECTOR_REP_CONST (float)
INSTANTIATE_SCALAR_VECTOR_REP_CONST (double)
INSTANTIATE_SCALAR_VECTOR_REP_CONST (octave_int8)
INSTANTIATE_SCALAR_VECTOR_REP_CONST (octave_int16)
INSTANTIATE_SCALAR_VECTOR_REP_CONST (octave_int32)
INSTANTIATE_SCALAR_VECTOR_REP_CONST (octave_int64)
INSTANTIATE_SCALAR_VECTOR_REP_CONST (octave_uint8)
INSTANTIATE_SCALAR_VECTOR_REP_CONST (octave_uint16)
INSTANTIATE_SCALAR_VECTOR_REP_CONST (octave_uint32)
INSTANTIATE_SCALAR_VECTOR_REP_CONST (octave_uint64)

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
