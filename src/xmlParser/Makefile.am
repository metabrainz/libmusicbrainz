#
# Builds a convenience library (one that is never installed) for inclusion
# in libmusicbrainz.
#

noinst_LTLIBRARIES = libxmlParser.la

libxmlParser_la_SOURCES = xmlParser.cpp
AM_CPPFLAGS = -DMB_API_EXPORTS

EXTRA_DIST = xmlParser.h
