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
INCLUDES = -I$(srcdir)/bitzi
lib_LTLIBRARIES = libmusicbrainz.la

libmusicbrainz_la_SOURCES = base64.c base64.h musicbrainz.cpp musicbrainz.h diskid.cpp diskid.h errors.h http.cpp http.h sha1.h sha1.c types.h mb.cpp signature.cpp signature.h comhttpsocket.cpp comhttpsocket.h comsocket.cpp comsocket.h haar.cpp haar.h sigxdr.cpp sigxdr.h sigclient.cpp sigclient.h sigfft.cpp audiosig.h sigcomplex.h sigfft.h mb.h c_wrapper.cpp mb_c.h uuid.cpp rdfparse.c rdfparse.h rdfextract.cpp rdfextract.h browser.c browser.h
libmusicbrainz_la_LDFLAGS = -version-info 2:1:0
if DARWIN
libmusicbrainz_la_LIBADD = ../expat/xmlparse/hashtable.lo ../expat/xmlparse/xmlparse.lo ../expat/xmltok/xmlrole.lo ../expat/xmltok/xmltok.lo bitzi/bitprint.lo bitzi/id3.lo bitzi/md5.lo bitzi/sboxes.lo bitzi/browser.lo bitzi/list.lo bitzi/mp3.lo bitzi/tiger.lo bitzi/dirsearch.lo bitzi/main.lo bitzi/plugin_man.lo bitzi/tigertree.lo 
else
libmusicbrainz_la_LIBADD = ../expat/xmlparse/libxmlparse.la ../expat/xmltok/libxmltok.la bitzi/libbitzi.la 
endif

noinst_HEADERS = audiosig.h base64.h diskid.h http.h sha1.h sigfft.h sigcomplex.h types.h parse.h uuid.h 

EXTRA_DIST = wincomsocket.cpp wincomsocket.h
