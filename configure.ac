dnl Process this file with autoconf to produce a configure script.
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


AC_PROTOTYPE_ACCEPT

AC_DEFINE_UNQUOTED([ACCEPT_ARG2],,"Argument 2 to accept()")
AC_DEFINE_UNQUOTED([ACCEPT_ARG3],,"Argument 3 to accept()")


if test "$GCC" = yes; then
  CFLAGS="$CFLAGS -Wall -O2"
fi
if test "$GXX" = yes; then
  CXXFLAGS="$CXXFLAGS -Wall -O2"
fi


AC_OUTPUT([
Makefile 
src/Makefile 
src/http/Makefile
src/xmlParser/Makefile
include/Makefile
include/musicbrainz3/Makefile
test/Makefile
libmusicbrainz.pc
Doxyfile], 
echo timestamp > stamp-h)
