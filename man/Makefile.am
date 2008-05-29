#
# Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
# 
# Permission to use, copy, modify, distribute, and sell this software and its
# documentation for any purpose is hereby granted without fee, provided that
# the above copyright notice appear in all copies and that both that
# copyright notice and this permission notice appear in supporting
# documentation.
# 
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
# 
# Except as contained in this notice, the name of the copyright holders shall
# not be used in advertising or otherwise to promote the sale, use or
# other dealings in this Software without prior written authorization
# from the copyright holders.
# 

libmandir = $(LIB_MAN_DIR)

LIB_MAN_DIR_SUFFIX = $(LIB_MAN_DIR:@mandir@/man%=%)

libman_xml = XI.xml

if HAVE_XMLTO
XI_manpages = \
	      XAllowDeviceEvents \
	      XChangeKeyboardDevice \
	      XChangePointerDevice \
	      XDeviceBell \
	      XQueryDeviceState \
	      XSendExtensionEvent \
	      XSetDeviceMode \
	      XSetDeviceValuators \
	      XChangeDeviceDontPropagateList \
	      XGetDeviceDontPropagateList \
	      XChangeDeviceHierarchy \
	      XDefineDeviceCursor \
	      XUndefineDeviceCursor \
	      XExtendedGrabDevice \
	      XGetDeviceControl \
	      XChangeDeviceControl \
	      XGetDeviceKeyMapping \
	      XChangeDeviceKeyMapping \
	      XGetDeviceModifierMapping \
	      XSetDeviceModifierMapping \
	      XGetDeviceMotionEvents \
	      XDeviceTimeCoord \
	      XGetFeedbackControl \
	      XChangeFeedbackControl \
	      XGrabDeviceButton \
	      XUngrabDeviceButton \
	      XGrabDeviceKey \
	      XUngrabDeviceKey \
	      XGrabDevice \
	      XUngrabDevice \
	      XiSelectEvent \
	      XListInputDevices \
	      XFreeDeviceList \
	      XOpenDevice \
	      XCloseDevice \
	      XPermitDevices \
	      XDenyDevices \
	      XChangeAccessRule \
	      XQueryDevicePointer \
	      XQueryInputVersion \
	      XGetExtensionVersion \
	      XQueryWindowAccess \
	      XSelectExtensionEvent \
	      XGetSelectedExtensionEvents \
	      XSetClientPointer \
	      XGetClientPointer \
	      XSetDeviceButtonMapping \
	      XGetDeviceButtonMapping \
	      XSetDeviceFocus \
	      XGetDeviceFocus \
	      XWarpDevicePointer \
	      XWindowClearAccess 
endif # HAVE_XMLTO

libman_PRE = $(XI_manpages:%=%.man)

EXTRA_DIST = $(libman_PRE) $(libman_xml)

CLEANFILES = $(libman_DATA) $(BUILT_SOURCES)

MAINTAINERCLEANFILES = $(libman_PRE)

libman_DATA = $(libman_PRE:man=@LIB_MAN_SUFFIX@)

SED = sed

# Strings to replace in man pages
XORGRELSTRING = @PACKAGE_STRING@
  XORGMANNAME = X Version 11

MAN_SUBSTS = \
	-e 's/__xorgversion__/"$(XORGRELSTRING)" "$(XORGMANNAME)"/' \
	-e 's/__xservername__/Xorg/g' \
	-e 's/__xconfigfile__/xorg.conf/g' \
	-e 's/__appmansuffix__/$(APP_MAN_SUFFIX)/g' \
	-e 's/__libmansuffix__/$(LIB_MAN_SUFFIX)/g' \
	-e 's/__filemansuffix__/$(FILE_MAN_SUFFIX)/g'

SUFFIXES = .$(LIB_MAN_SUFFIX) .man

.man.$(LIB_MAN_SUFFIX):
	sed $(MAN_SUBSTS) < $< > $@

dist-hook: $(libman_PRE)

.PHONY: do_xmlto_stage

$(libman_PRE): do_xmlto_stage

do_xmlto_stage: $(libman_xml)
	$(XMLTO) man $(libman_xml)
	for m in $(XI_manpages); do \
	  mv -f $$m.__libmansuffix__ $$m.man ; \
	done
