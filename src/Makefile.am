# $XdotOrg: lib/Xi/src/Makefile.am,v 1.6 2005/12/03 04:41:49 kem Exp $

lib_LTLIBRARIES = libXi.la

libXi_la_SOURCES = \
		  XAllowDv.c \
                  XChAccRl.c \
		  XChgDCtl.c \
		  XChgFCtl.c \
		  XChgKbd.c \
		  XChgKMap.c \
		  XChgPnt.c \
		  XChgProp.c \
		  XChPKPair.c \
                  XClrAcc.c \
		  XCloseDev.c \
		  XDefDevCur.c \
                  XDenyDev.c \
		  XDevBell.c \
		  XExtToWire.c \
		  XGetBMap.c \
		  XGetDCtl.c \
		  XGetFCtl.c \
		  XGetKMap.c \
		  XGetMMap.c \
		  XGetProp.c \
		  XGetVers.c \
		  XGMotion.c \
		  XGrabAcc.c \
		  XGrabDev.c \
		  XGrDvBut.c \
		  XGrDvKey.c \
		  XGtFocus.c \
		  XGtSelect.c \
		  XListDev.c \
		  XOpenDev.c \
                  XPermDev.c \
		  XQryAccRl.c \
		  XQueryDv.c \
                  XQueryDvPtr.c \
		  XRegPair.c \
		  XSelect.c \
		  XSetBMap.c \
		  XSetDVal.c \
		  XSetMMap.c \
		  XSetMode.c \
		  XSndExEv.c \
		  XStFocus.c \
		  XUndefDevCur.c \
		  XUngrabAcc.c \
		  XUngrDev.c \
		  XUngrDvB.c \
		  XUngrDvK.c \
		  XUnregPair.c \
                  XWarpDvPtr.c \
		  XExtInt.c  \
		  XIint.h

libXi_la_LIBADD = $(XI_LIBS)

AM_CFLAGS = $(XI_CFLAGS) $(MALLOC_ZERO_CFLAGS)

#INCLUDES = -I$(top_srcdir)/include/X11/extensions

libXi_la_LDFLAGS = -version-number 6:0:0 -no-undefined

#libXiincludedir = $(includedir)/X11/extensions
#libXiinclude_HEADERS = $(top_srcdir)/include/X11/extensions/Xi.h 

EXTRA_DIST = XFreeLst.c
