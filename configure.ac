dnl Process this file with autoconf to produce a configure script.
dnl
dnl NOTE: Each time a release is made, the version number below and the
dnl       libtool version number in src/Makefile.am have to be incremented.
dnl       The libtool version number has to be changed ALWAYS, no matter how
dnl       small the change to the source code was!
dnl
AC_INIT(libmusicbrainz, 3.0.0dev)
AC_CONFIG_SRCDIR(src/artist.cpp)
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS(config.h)

AM_MAINTAINER_MODE

dnl set the host_cpu, host_vendor, and host_os variables
AC_CANONICAL_HOST

case "${host_cpu}-${host_os}" in
  *-beos*)    os=beos; LIBS='-lbe -lroot' ;;
  *-cygwin*)  os=cygwin; LIBS='-lwinmm' ;;
  *-freebsd*) os=freebsd ;;
  *-darwin*)  os=darwin ;;
  *-irix*)    os=irix; CXXFLAGS="$CFLAGS -fsquangle"; 
                       LIBS='-lcdaudio -lmediad -lds' ;; 
  *-linux*)   os=linux ;;
  *-netbsd*)  os=netbsd ;;
  *-openbsd*) os=openbsd ;;
  *-os2_emx*) os=os2 ;;
  *-solaris*) os=solaris; LIBS='-lsocket -lnsl' ;;
  *-qnx*)     os=qnx; LIBS='-lsocket' ;;
  *)          AC_MSG_RESULT([WARNING: unknown system]) ;;
esac
AM_CONDITIONAL(DARWIN, test x$os = xdarwin)

dnl Checks for programs.
AC_PROG_CC
AM_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)  
AC_PROG_CXX
AC_PROG_INSTALL


dnl Checks for libraries

dnl Check for cppunit. This is only necessary for building the test suite.
dnl If found, this sets CPPUNIT_CFLAGS and CPPUNIT_LIBS.
AM_PATH_CPPUNIT(1.10.0, , 
	AC_MSG_WARN([[No recent cppunit found, test suite will not work.]])
)

dnl Check for neon.
NE_REQUIRE_VERSIONS([0], [25 26])
NEON_LIBRARY

if test "$GCC" = yes; then
  CFLAGS="$CFLAGS -Wall -O2 -DNDEBUG"
fi
if test "$GXX" = yes; then
  CXXFLAGS="$CXXFLAGS -Wall -O2 -DNDEBUG"
fi


AC_OUTPUT([
Makefile 
src/Makefile 
src/xmlParser/Makefile
include/Makefile
include/musicbrainz3/Makefile
test/Makefile
examples/Makefile 
libmusicbrainz3.pc
Doxyfile], 
echo timestamp > stamp-h)
