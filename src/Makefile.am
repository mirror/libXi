# $XdotOrg: lib/Xi/src/Makefile.am,v 1.6 2005/12/03 04:41:49 kem Exp $

lib_LTLIBRARIES = libXi.la

libXi_la_SOURCES = \
		  XAllowDv.c \
		  XChDevHier.c \
		  XChDProp.c \
		  XChgDCtl.c \
		  XChgFCtl.c \
		  XChgKbd.c \
		  XChgKMap.c \
		  XChgPnt.c \
		  XChgProp.c \
		  XCloseDev.c \
		  XDefDevCur.c \
		  XDelDProp.c \
		  XDevBell.c \
		  XExtGrabDev.c \
		  XExtToWire.c \
		  XGetBMap.c \
		  XGetCPtr.c \
		  XGetDCtl.c \
		  XGetDProp.c \
		  XGetFCtl.c \
		  XGetKMap.c \
		  XGetMMap.c \
		  XGetProp.c \
		  XGetVers.c \
		  XGMotion.c \
		  XGrabDev.c \
		  XGrDvBut.c \
		  XGrDvKey.c \
		  XGtFocus.c \
		  XGtSelect.c \
		  XListDev.c \
		  XListDProp.c \
		  XOpenDev.c \
		  XQueryDv.c \
                  XQueryDvPtr.c \
		  XSelect.c \
		  XSetBMap.c \
		  XSetCPtr.c \
		  XSetDVal.c \
		  XSetMMap.c \
		  XSetMode.c \
		  XSndExEv.c \
		  XStFocus.c \
		  XUndefDevCur.c \
		  XUngrDev.c \
		  XUngrDvB.c \
		  XUngrDvK.c \
                  XWarpDvPtr.c \
		  XExtInt.c  \
                  XiSelEv.c \
		  XIint.h

libXi_la_LIBADD = $(XI_LIBS)

AM_CFLAGS = -I$(top_srcdir)/include \
            -I$(top_srcdir)/include/X11 \
            -I$(top_srcdir)/include/X11/extensions \
            $(XI_CFLAGS) \
            $(MALLOC_ZERO_CFLAGS)


libXi_la_LDFLAGS = -version-number 6:0:0 -no-undefined

libXiincludedir = $(includedir)/X11/extensions
libXiinclude_HEADERS = $(top_srcdir)/include/X11/extensions/XInput.h

EXTRA_DIST = XFreeLst.c
