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

SUBDIRS = bitzi

AM_CPPFLAGS = -I$(srcdir)/bitzi

lib_LTLIBRARIES = libmusicbrainz.la

dist_libmusicbrainz_la_SOURCES = \
  base64.c browser.c c_wrapper.cpp comhttpsocket.cpp comsocket.cpp \
  diskid.cpp haar.cpp http.cpp \
  musicbrainz.cpp sha1.c signature.cpp \
  sigxdr.cpp sigclient.cpp sigfft.cpp \
  rdfparse.c rdfextract.cpp uuid.cpp 
nodist_libmusicbrainz_la_SOURCES = mb.cpp
libmusicbrainz_la_LDFLAGS = -version-info 2:1:0

if DARWIN
libmusicbrainz_la_LIBADD = ../expat/xmlparse/hashtable.lo ../expat/xmlparse/xmlparse.lo ../expat/xmltok/xmlrole.lo ../expat/xmltok/xmltok.lo bitzi/bitprint.lo bitzi/id3.lo bitzi/md5.lo bitzi/sboxes.lo bitzi/browser.lo bitzi/list.lo bitzi/mp3.lo bitzi/tiger.lo bitzi/dirsearch.lo bitzi/main.lo bitzi/plugin_man.lo bitzi/tigertree.lo 
else
libmusicbrainz_la_LIBADD = @EXPAT_LIBS@ bitzi/libbitzi.la 
endif


mb_incdir = $(includedir)/musicbrainz

mb_inc_HEADERS = bitprintinfo.h browser.h errors.h mb_c.h musicbrainz.h \
		 queries.h 

noinst_HEADERS = \
  audiosig.h base64.h comhttpsocket.h comsocket.h \
  diskid.h haar.h http.h parse.h \
  sha1.h sigfft.h sigclient.h sigcomplex.h sigxdr.h \
  rdfparse.h rdfextract.h types.h trm.h uuid.h 

EXTRA_DIST = wincomsocket.cpp wincomsocket.h apsmetadata.h apsutility.h
