## Copyright (C) 2005-2012 John W. Eaton
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
## @deftypefn  {Function File} {} line ()
## @deftypefnx {Function File} {} line (@var{x}, @var{y})
## @deftypefnx {Function File} {} line (@var{x}, @var{y}, @var{z})
## @deftypefnx {Function File} {} line (@var{x}, @var{y}, @var{z}, @var{property}, @var{value}, @dots{})
## Create line object from @var{x} and @var{y} and insert in current
## axes object.  Return a handle (or vector of handles) to the line
## objects created.
##
## Multiple property-value pairs may be specified for the line, but they
## must appear in pairs.
## @end deftypefn

## Author: jwe

function h = line (varargin)

  ## make a default line object, and make it the current axes for
  ## the current figure.
  tmp = __line__ (gca (), varargin{:});

  if (nargout > 0)
    h = tmp;
  endif

endfunction

%!demo
%! clf
%! x = 0:0.3:10;
%! y1 = cos (x);
%! y2 = sin (x);
%! subplot (3,1,1);
%! args = {"color", "b", "marker", "s"};
%! line ([x(:), x(:)], [y1(:), y2(:)], args{:})
%! title ("Test broadcasting for line()")
%! subplot (3,1,2);
%! line (x(:), [y1(:), y2(:)], args{:})
%! subplot (3,1,3);
%! line ([x(:), x(:)+pi/2], y1(:), args{:})
%! xlim ([0 10])

%!test
%! hf = figure ("visible", "off");
%! unwind_protect
%!   h = line;
%!   assert (findobj (hf, "type", "line"), h);
%!   assert (get (h, "xdata"), [0 1], eps);
%!   assert (get (h, "ydata"), [0 1], eps);
%!   assert (get (h, "type"), "line");
%!   assert (get (h, "color"), get (0, "defaultlinecolor"));
%!   assert (get (h, "linestyle"), get (0, "defaultlinelinestyle"));
%!   assert (get (h, "linewidth"), get (0, "defaultlinelinewidth"), eps);
%! unwind_protect_cleanup
%!   close (hf);
%! end_unwind_protect

