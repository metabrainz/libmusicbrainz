#
# Makefile for libmusicbrainz' test suite.
#
# Run `make check' from the top level directory to build and run it.
#
TESTS = test_runner

check_PROGRAMS = test_runner

test_runner_SOURCES = \
	main.cpp test_first.cpp test_model.cpp test_parser.cpp \
	test_parser_artist.cpp test_parser_release.cpp test_parser_track.cpp \
	test_parser_user.cpp test_utils.cpp test_ws_filters.cpp \
	test_ws_includes.cpp

INCLUDES = -I$(top_srcdir)/include @CPPUNIT_CFLAGS@

test_runner_LDFLAGS = @CPPUNIT_LIBS@
test_runner_LDADD = $(top_srcdir)/lib/libmusicbrainz.la

EXTRA_DIST = SConscript
