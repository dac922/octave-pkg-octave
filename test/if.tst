## Copyright (C) 2006-2012 John W. Eaton
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

%% test/octave.test/if/if-1.m
%!test
%! i = 0;
%! if (i == 0)
%!   i++;
%!   __printf_assert__ ("%d\n", i);
%! endif
%! assert (__prog_output_assert__ ("1"));

%% test/octave.test/if/if-2.m
%!test
%! if (eye (2))
%!   __printf_assert__ ("fail\n");
%! else
%!   __printf_assert__ ("pass\n");
%! end
%! assert (__prog_output_assert__ ("pass"));

%% test/octave.test/if/if-3.m
%!test
%! x = 2;
%! if (eye (2))
%!   __printf_assert__ ("fail\n");
%! elseif (x)
%!   __printf_assert__ ("pass\n");
%! endif
%! assert (__prog_output_assert__ ("pass"));

%% test/octave.test/if/if-4.m
%!test
%! x = 0;
%! y = -2;
%! if (eye (2))
%!   __printf_assert__ ("fail\n");
%! elseif (x)
%!   __printf_assert__ ("fail\n");
%! elseif (y)
%!   __printf_assert__ ("pass\n");
%! end
%! assert (__prog_output_assert__ ("pass"));

%% test/octave.test/if/if-5.m
%!test
%! x = 0;
%! y = -2;
%! if (eye (2))
%!   __printf_assert__ ("fail\n");
%! elseif (x)
%!   __printf_assert__ ("fail\n");
%! elseif (x)
%!   __printf_assert__ ("fail\n");
%! else
%!   __printf_assert__ ("pass\n");
%! endif
%! assert (__prog_output_assert__ ("pass"));

%% test/octave.test/if/if-6.m
%!test
%! x = 0;
%! y = -2;
%! if (y)
%!   __printf_assert__ ("pass\n");
%! elseif (x)
%!   __printf_assert__ ("fail\n");
%! elseif (x)
%!   __printf_assert__ ("fail\n");
%! end
%! assert (__prog_output_assert__ ("pass"));
