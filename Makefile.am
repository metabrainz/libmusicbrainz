#
#  MusicBrainz -- The Intenet music metadatabase
#
#  Copyright (C) 2000 Robert Kaye
#  
#  This library is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation; either
#  version 2.1 of the License, or (at your option) any later version.
#  
#  This library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#  
#  You should have received a copy of the GNU Lesser General Public
#  License along with this library; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
#    $Id$
#
AUTOMAKE_OPTIONS = foreign

SUBDIRS = expat lib examples

EXTRA_DIST = \
	AUTHORS \
	BUGS \
	COPYING \
	ChangeLog \
	INSTALL \
	NEWS \
	README

OTHERFILES = \
   osdep/cdi_beos.cpp \
   osdep/cdi_beos.h \
   osdep/cdi_cygwin.cpp \
   osdep/cdi_cygwin.h \
   osdep/cdi_freebsd.cpp \
   osdep/cdi_freebsd.h \
   osdep/cdi_irix.cpp \
   osdep/cdi_irix.h \
   osdep/cdi_linux.cpp \
   osdep/cdi_linux.h \
   osdep/cdi_netbsd.cpp \
   osdep/cdi_netbsd.h \
   osdep/cdi_openbsd.cpp \
   osdep/cdi_openbsd.h \
   osdep/cdi_os2.cpp \
   osdep/cdi_os2.h \
   osdep/cdi_solaris.cpp \
   osdep/cdi_solaris.h \
   osdep/cdi_win32.cpp \
	osdep/cdi_win32.h \
	Makefile.am \
	Makefile.in \
	acconfig.h \
	aclocal.m4 \
	lib/cdindex.dsp \
	lib/cdindex.dsw \
   config.guess \
	config.h.in \
	config.sub \
	configure \
	configure.in \
	install-sh \
	missing \
	mkinstalldirs \
	stamp-h.in

SYM_LINKS = \
	cdi.cpp \
	cdi.h

FEATHERS = $(filter-out $(SYM_LINKS), $(cdindex_SOURCES) $(DOCS) $(OTHERFILES))

snapshot: $(FEATHERS)
	tar -cf - $(FEATHERS) | gzip > $(PACKAGE)-$(VERSION).tar.gz

cvsclean: distclean
	@echo "additonal cleanup for cvs commits"
	rm -f *~ *.exe
	rm -f cdi.h cdi.cpp
	rm -f $(PACKAGE)-$(VERSION).tar.gz

$(OBJECTS): libtool
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck

install-data-local:
	mkdir -p $(DESTDIR)$(includedir)/musicbrainz
	$(INSTALL) -m 0644 lib/musicbrainz.h lib/queries.h lib/errors.h lib/mb_c.h $(DESTDIR)$(includedir)/musicbrainz

