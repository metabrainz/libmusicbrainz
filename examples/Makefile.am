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

INCLUDES = -I$(top_srcdir)/lib

noinst_PROGRAMS = c_example cpp_example cmd findartist
c_example_SOURCES = c_example.c
c_example_LDADD = $(top_builddir)/lib/.libs/libmusicbrainz.a -lstdc++ -ldl

cpp_example_SOURCES = cpp_example.cpp
cpp_example_LDADD = $(top_builddir)/lib/.libs/libmusicbrainz.a -ldl

cmd_SOURCES = cmd.cpp
cmd_LDADD = $(top_builddir)/lib/libmusicbrainz.la -ldl

findartist_SOURCES = findartist.c
findartist_LDADD = $(top_builddir)/lib/libmusicbrainz.la -ldl -lstdc++

