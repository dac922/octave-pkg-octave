## Copyright (C) 2001-2012 Teemu Ikonen
##
## This file is part of Octave.
##
## Octave is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or (at
## your option) any later version.
##
## Octave is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with Octave; see the file COPYING.  If not, see
## <http://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn {Function File} {} __errcomm__ (@var{caller}, @var{hax}, @dots{})
## Undocumented internal function.
## @end deftypefn

## Created: 20.02.2001
## Author: Teemu Ikonen <tpikonen@pcu.helsinki.fi>
## Keywords: errorbar, plotting

function retval = __errcomm__ (caller, hax, varargin)

  if (nargin < 4)
    print_usage (caller);
  endif

  nargs = length (varargin);
  retval = [];
  k = 1;
  data = cell (6,1);
  while (k <= nargs)
    a = varargin{k++};
    if (isvector (a))
      a = a(:);
    elseif (ismatrix (a))
      ;
    else
      usage ("%s (...)", caller);
    endif
    sz = size (a);
    ndata = 1;
    data{ndata} = a;
    while (k <= nargs)
      a = varargin{k++};
      if (ischar (a) || iscellstr (a))
        retval = [retval; __errplot__(a, hax, data{1:ndata})];
        break;
      elseif (isvector (a))
        a = a(:);
      elseif (ismatrix (a))
        ;
      else
        error ("%s: wrong argument types", caller);
      endif
      if (size (a) != sz)
        error ("%s: argument sizes do not match", caller);
      endif
      data{++ndata} = a;
      if (ndata > 6)
        error ("%s: too many arguments to plot", caller);
      endif
    endwhile
  endwhile

  if (! (ischar (a) || iscellstr (a)))
    retval = [retval; __errplot__("~", hax, data{1:ndata})];
  endif

  drawnow ();

endfunction
