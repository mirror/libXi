# $XdotOrg: $

lib_LTLIBRARIES = libXi.la

libXi_la_SOURCES = \
		  XAllowDv.c \
		  XChgDCtl.c \
		  XChgFCtl.c \
		  XChgKbd.c \
		  XChgKMap.c \
		  XChgPnt.c \
		  XChgProp.c \
		  XCloseDev.c \
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
		  XGrabDev.c \
		  XGrDvBut.c \
		  XGrDvKey.c \
		  XGtFocus.c \
		  XGtSelect.c \
		  XListDev.c \
		  XOpenDev.c \
		  XQueryDv.c \
		  XSelect.c \
		  XSetBMap.c \
		  XSetDVal.c \
		  XSetMMap.c \
		  XSetMode.c \
		  XSndExEv.c \
		  XStFocus.c \
		  XUngrDev.c \
		  XUngrDvB.c \
		  XUngrDvK.c \
		  XExtInt.c 

libXi_la_LIBADD = $(XI_LIBS)

libXi_la_CFLAGS = $(XI_CFLAGS)

#INCLUDES = -I$(top_srcdir)/include/X11/extensions

#
# Library version info.  Check the libtool docs for
# instructions on when and how to change this value
#
# bump when the ABI changes
XI_CURRENT=1
# bump for non-ABI changes, reset to zero when CURRENT changes
XI_REVISION=0
# bump when the ABI changes in backward-compatible fashion
XI_AGE=0

libXi_la_LDFLAGS = -version-info ${XI_CURRENT}:${XI_REVISION}:${XI_AGE}

#libXiincludedir = $(includedir)/X11/extensions
#libXiinclude_HEADERS = $(top_srcdir)/include/X11/extensions/Xi.h 
