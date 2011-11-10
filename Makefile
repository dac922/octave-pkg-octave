# Makefile for octave's src directory
#
# Copyright (C) 1994, 1995, 1996, 1997, 1998, 2000, 2001, 2003, 2004,
#               2005, 2006, 2007, 2009 John W. Eaton
#
# This file is part of Octave.
# 
# Octave is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 3 of the License, or (at
# your option) any later version.
# 
# Octave is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Octave; see the file COPYING.  If not, see
# <http://www.gnu.org/licenses/>.

TARGETS = octave-bug octave-config mkoctfile libcruft liboctave \
	dlfcn readline src scripts doc check octave.info \
	INSTALL.OCTAVE BUGS install install-strip uninstall \
	tags TAGS dist conf-dist snapshot snapshot-version \
	.gdbinit run-octave

NO_DEP_TARGETS = clean mostlyclean distclean maintainer-clean

all: header-msg config-check
	$(MAKE) -f octMakefile all

configfiles: FORCE
	$(MAKE) -f octMakefile configfiles

$(TARGETS): FORCE
	$(MAKE) -f octMakefile $@

$(NO_DEP_TARGETS): FORCE
	$(MAKE) -f octMakefile omit_deps=true $@

# Maybe this message will prevent people from asking why the
# Makefiles don't work for them.  Maybe not.

header-msg: FORCE
	@echo ""
	@echo "***********************************************************"
	@echo "*"
	@echo "*  To compile Octave, you will need a recent versions of"
	@echo "*  the following software:"
	@echo "*"
	@echo "*    GNU Make (a recent version)"
	@echo "*"
	@echo "*    g++ (preferably a recent 4.x version)"
	@echo "*"
	@echo "*    flex (2.5.4 or a more recent version) -- required if"
	@echo "*    you need to recreate lex.cc from lex.l"
	@echo "*"
	@echo "*    bison (1.31 or a more recent version) -- required if"
	@echo "*    you need to recreate parse.cc from parse.y"
	@echo "*"
	@echo "*    gperf (3.0.1 or a more recent version) -- required if"
	@echo "*    you need to recreate oct-gperf.h from octave.gperf"
	@echo "*"
	@echo "*  Now would be a good time to read INSTALL.OCTAVE if"
	@echo "*  you have not done so already."
	@echo "*"
	@echo "***********************************************************"
	@echo ""

help: header-msg
	@echo ""
	@echo "For more information, please read the files INSTALL,"
	@echo "INSTALL.OCTAVE, and any other system-specific README"
	@echo "files that apply (e.g., README.Linux)."
	@echo ""
	@echo "The following targets are available:"
	@echo ""
	@echo "  all                  build everything"
	@echo "  check                run self tests"
	@echo "  install              install files"
	@echo "  install-strip        same as install but strip binaries"
	@echo "  uninstall            delete installed files"
	@echo ""
	@echo "  dist                 create a source distribution"
	@echo "  conf-dist            create a config files distribution"
	@echo ""
	@echo "  clean                remove files created by make all"
	@echo "  mostlyclean          remove most files created by make all"
	@echo "  distclean            remove all files not in distribution"
	@echo "  maintainer-clean     clean up everything"
	@echo ""
	@echo "  octave-bug           create octave-bug script"
	@echo "  octave-config        create octave-config script"
	@echo "  mkoctfile            create mkoctfile script"
	@echo "  INSTALL.OCTAVE       create INSTALL.OCTAVE doc file"
	@echo "  BUGS                 create BUGS doc file"
	@echo "  tags                 create tags files"
	@echo "  TAGS                 create TAGS files"
	@echo ""
	@echo "  dlfcn                make all in subdirectory dlfcn"
	@echo "  doc                  make all in subdirectory doc"
	@echo "  libcruft             make all in subdirectory libcruft"
	@echo "  liboctave            make all in subdirectory liboctave"
	@echo "  scripts              make all in subdirectory scripts"
	@echo "  src                  make all in subdirectory src"
	@echo ""
	@echo "  configfiles          update the configuration files"
	@echo ""
	@echo "  help                 print this message"
	@echo ""

config-check:
	@if test -f octMakefile; then \
	  true; \
	else \
	  echo ""; \
	  echo "*** You must run configure before running make."; \
	  echo "***"; \
	  echo "*** Please read the INSTALL and INSTALL.OCTAVE files"; \
	  echo "*** for more information about how to configure and"; \
	  echo "*** compile Octave."; \
	  echo ""; \
	  exit 1; \
	fi

FORCE:

.NOTPARALLEL:
