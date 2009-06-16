dnl $XdotOrg: lib/Xi/configure.ac,v 1.9 2005/12/15 00:24:30 kem Exp $
dnl
dnl Process this file with autoconf to create configure.

AC_PREREQ([2.57])

AC_INIT(libXi, 1.2.99.1, [https://bugs.freedesktop.org/enter_bug.cgi?product=xorg], libXi)
AM_INIT_AUTOMAKE([dist-bzip2])
AM_MAINTAINER_MODE

# Require xorg-macros: XORG_CWARNFLAGS, XORG_CHANGELOG
m4_ifndef([XORG_MACROS_VERSION], [AC_FATAL([must install xorg-macros 1.2 or later before running autoconf/autogen])])
XORG_MACROS_VERSION(1.2)
AM_CONFIG_HEADER(src/config.h)

# Check for progs
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_SED
XORG_CWARNFLAGS

# Checks for pkg-config packages
PKG_CHECK_MODULES(XI, [xproto >= 7.0.13] [x11 >= 1.1.99.1] [xextproto >= 7.0.3] [xext >= 1.0.99.1] [inputproto >= 1.9.99.12])
XI_CFLAGS="$CWARNFLAGS $XI_CFLAGS"
AC_SUBST(XI_CFLAGS)
AC_SUBST(XI_LIBS)

# Check for xmlto and asciidoc for man page conversion
# (only needed by people building tarballs)
AC_ARG_VAR([XMLTO], [Path to xmlto command])
AC_PATH_PROG([XMLTO], [xmlto])
AC_ARG_VAR([ASCIIDOC], [Path to asciidoc command])
AC_PATH_PROG([ASCIIDOC], [asciidoc])
AM_CONDITIONAL([HAVE_DOCTOOLS], [test "x$XMLTO" != "x" && test "x$ASCIIDOC" != "x"])
if test "x$XMLTO" = "x" || test "x$ASCIIDOC" = "x"; then
	AC_MSG_WARN([xmlto or asciidoc not found - cannot create man pages without it])
else
        AC_MSG_WARN([
                     *********************************************************
                     xmlto and asciidoc found. I will be building man
                     pages. Your asciidoc may not support multiple docbook 
                     targets and building the man pages may fail. See
                     http://hg.sharesource.org/asciidoc/raw-rev/fc5a653a30a3
                     *********************************************************])
fi

XORG_CHECK_MALLOC_ZERO
XORG_MANPAGE_SECTIONS
XORG_RELEASE_VERSION
XORG_CHANGELOG

AC_OUTPUT([Makefile
	   src/Makefile
	   man/Makefile
           xi.pc])

