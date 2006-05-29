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

SUBDIRS = http xmlParser

src_LTLIBRARIES = libmusicbrainz.la
INCLUDES = -I$(top_srcdir)/include -DMB_API_EXPORTS

libmusicbrainz_la_SOURCES = \
	artist.cpp artistalias.cpp disc.cpp entity.cpp filters.cpp \
	includes.cpp mbxmlparser.cpp metadata.cpp relation.cpp release.cpp \
	releaseevent.cpp results.cpp track.cpp user.cpp utils.cpp \
	webservice.cpp

# Here are a set of rules to help you update your library version information:
#  Scheme: current:revsion:age
#  1. Start with version information of `0:0:0' for each libtool library.
#  2. Update the version information only immediately before a public release 
#     of your software. More frequent updates are unnecessary, and only 
#     guarantee that the current interface number gets larger faster.
#  3. If the library source code has changed at all since the last update, 
#     then increment revision (`c:r:a' becomes `c:r+1:a').
#  4. If any interfaces have been added, removed, or changed since the last 
#     update, increment current, and set revision to 0.
#  5. If any interfaces have been added since the last public release, then 
#     increment age.
#  6. If any interfaces have been removed since the last public release, then 
#     set age to 0. 
#libmusicbrainz_la_LDFLAGS = -version-info 5:0:0 -no-undefined
libmusicbrainz_la_LDFLAGS = -version-info 4:0:0 -no-undefined
libmusicbrainz_la_LIBADD = -lstdc++ -lm \
	http/libhttp.la xmlParser/libxmlParser.la

EXTRA_DIST = types.h SConscript
