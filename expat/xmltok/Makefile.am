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
noinst_LTLIBRARIES = libxmltok.la
libxmltok_la_SOURCES = asciitab.h iasciitab.h latin1tab.h \
		       nametab.h utf8tab.h xmldef.h xmlrole.c xmlrole.h \
		       xmltok.c xmltok.h xmltok_impl.h 

EXTRA_DIST = xmltok_impl.c xmltok_ns.c 

AM_CPPFLAGS = -I$(srcdir)/../xmlparse -DXML_NS
