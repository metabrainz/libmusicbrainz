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

lib_LTLIBRARIES = libmusicbrainz.la
libmusicbrainz_la_SOURCES = base64.c base64.h musicbrainz.cpp musicbrainz.h diskid.cpp diskid.h errors.h http.cpp http.h sha.h sha_func.c types.h xd3.h parse.cpp parse.h xql.cpp xql.h mb.cpp signature.cpp signature.h comsocket.cpp comsocket.h sigxdr.cpp sigxdr.h sigclient.cpp sigclient.h sigfft.cpp audiosig.h sigcomplex.h sigfft.h mb.h c_wrapper.cpp mb_c.h uuid.cpp
libmusicbrainz_la_LDFLAGS = -version-info 1:0:0
libmusicbrainz_la_LIBADD = ../expat/xmlparse/libxmlparse.la ../expat/xmltok/libxmltok.la

noinst_HEADERS = audiosig.h base64.h musicbrainz.h diskid.h errors.h http.h sha.h sigfft.h sigcomplex.h types.h parse.h xql.h mb_c.h uuid.h

EXTRA_DIST = wincomsocket.cpp wincomsocket.h
