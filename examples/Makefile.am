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
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#
#    $Id$
#

AM_CPPFLAGS = -I$(top_srcdir)/include

noinst_PROGRAMS = findartist findtrack getartist_c getartist getuser

findartist_SOURCES = findartist.cpp
findartist_LDADD = $(top_builddir)/src/libmusicbrainz3.la -lstdc++ -lm

findtrack_SOURCES = findtrack.cpp
findtrack_LDADD = $(top_builddir)/src/libmusicbrainz3.la -lstdc++ -lm

getartist_c_SOURCES = getartist_c.c
getartist_c_LDADD = $(top_builddir)/src/libmusicbrainz3.la -lstdc++ -lm

getartist_SOURCES = getartist.cpp
getartist_LDADD = $(top_builddir)/src/libmusicbrainz3.la -lstdc++ -lm

getuser_SOURCES = getuser.cpp
getuser_LDADD = $(top_builddir)/src/libmusicbrainz3.la -lstdc++ -lm

EXTRA_DIST = SConscript
