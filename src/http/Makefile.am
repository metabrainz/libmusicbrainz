#
# Builds a convenience library (one that is never installed) for inclusion
# in libmusicbrainz.
#

noinst_LTLIBRARIES = libhttp.la

libhttp_la_SOURCES = comhttpsocket.cpp comsocket.cpp http.cpp
AM_CPPFLAGS = -I.. -DMB_API_EXPORTS

EXTRA_DIST = wincomsocket.cpp comhttpsocket.h comsocket.h errors.h http.h \
	wincomsocket.h
