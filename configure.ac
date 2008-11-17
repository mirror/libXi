dnl $XdotOrg: lib/Xi/configure.ac,v 1.9 2005/12/15 00:24:30 kem Exp $
dnl
dnl Process this file with autoconf to create configure.

AC_PREREQ([2.57])

AC_INIT(libXi, 1.2.99.1, [https://bugs.freedesktop.org/enter_bug.cgi?product=xorg], libXi)
AM_INIT_AUTOMAKE([dist-bzip2])
AM_MAINTAINER_MODE

AM_CONFIG_HEADER(src/config.h)

# Check for progs
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for pkg-config packages
PKG_CHECK_MODULES(XI, [xproto >= 7.0.13] [x11 >= 1.1.99.1] [xextproto >= 7.0.3] [xext >= 1.0.99.1] [inputproto >= 1.9.99.6])
AC_SUBST(XI_CFLAGS)
AC_SUBST(XI_LIBS)

# Check for xmlto for man page conversion 
# (only needed by people building tarballs)
AC_ARG_VAR([XMLTO], [Path to xmlto command])
AC_PATH_PROG([XMLTO], [xmlto])
AM_CONDITIONAL([HAVE_XMLTO], [test "x$XMLTO" != "x"])
if test "x$XMLTO" = "x"; then
	AC_MSG_WARN([xmlto not found - cannot create man pages without it])
fi

XORG_CHECK_MALLOC_ZERO
XORG_MANPAGE_SECTIONS
XORG_RELEASE_VERSION

AC_OUTPUT([Makefile
	   src/Makefile
	   man/Makefile
           xi.pc])

