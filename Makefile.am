#
#  MusicBrainz -- The Internet music metadatabase
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

SYM_LINKS = \
	mb.cpp \
	mb.h

FEATHERS = $(filter-out $(SYM_LINKS), $(mbndex_SOURCES) $(DOCS) $(OTHERFILES))

snapshot: $(FEATHERS)
	tar -cf - $(FEATHERS) | gzip > $(PACKAGE)-$(VERSION).tar.gz

cvsclean: distclean
	@echo "additonal cleanup for cvs commits"
	rm -f *~ *.exe
	rm -f mb.h cdi.cpp
	rm -f $(PACKAGE)-$(VERSION).tar.gz

$(OBJECTS): libtool
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck

install-data-local:
	mkdir -p $(DESTDIR)$(includedir)/musicbrainz
	$(INSTALL) -m 0644 lib/musicbrainz.h lib/queries.h lib/errors.h lib/mb_c.h $(DESTDIR)$(includedir)/musicbrainz

