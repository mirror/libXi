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

libman_PRE = \
	      XAllowDeviceEvents.man \
	      XChangeKeyboardDevice.man \
	      XChangePointerDevice.man \
	      XDeviceBell.man \
	      XQueryDeviceState.man \
	      XSendExtensionEvent.man \
	      XSetDeviceMode.man \
	      XSetDeviceValuators.man \
	      XChangeDeviceDontPropagateList.man \
	      XGetDeviceDontPropagateList.man \
	      XChangeDeviceHierarchy.man \
	      XDefineDeviceCursor.man \
	      XUndefineDeviceCursor.man \
	      XExtendedGrabDevice.man \
	      XGetDeviceControl.man \
	      XChangeDeviceControl.man \
	      XGetDeviceKeyMapping.man \
	      XChangeDeviceKeyMapping.man \
	      XGetDeviceModifierMapping.man \
	      XSetDeviceModifierMapping.man \
	      XGetDeviceMotionEvents.man \
	      XDeviceTimeCoord.man \
	      XGetFeedbackControl.man \
	      XChangeFeedbackControl.man \
	      XGrabDeviceButton.man \
	      XUngrabDeviceButton.man \
	      XGrabDeviceKey.man \
	      XUngrabDeviceKey.man \
	      XGrabDevice.man \
	      XUngrabDevice.man \
	      XiSelectEvent.man \
	      XListInputDevices.man \
	      XFreeDeviceList.man \
	      XOpenDevice.man \
	      XCloseDevice.man \
	      XQueryDevicePointer.man \
	      XQueryInputVersion.man \
	      XGetExtensionVersion.man \
	      XSelectExtensionEvent.man \
	      XGetSelectedExtensionEvents.man \
	      XSetClientPointer.man \
	      XGetClientPointer.man \
	      XSetDeviceButtonMapping.man \
	      XGetDeviceButtonMapping.man \
	      XSetDeviceFocus.man \
	      XGetDeviceFocus.man \
	      XWarpDevicePointer.man \
	      XListDeviceProperties.man \
	      XGetDeviceProperty.man \
	      XChangeDeviceProperty.man \
	      XDeleteDeviceProperty.man

EXTRA_DIST = $(libman_PRE) $(libman_xml) xi.stamp

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

# This is ugly, but handling of tools with multiple outputs in make is a
# huge PITA. The commands below are taken from the automake manual:
# http://www.gnu.org/software/automake/manual/automake.html#Multiple-Outputs
if HAVE_XMLTO
xi.stamp: $(libman_xml)
	@rm -f xi.tmp
	@touch xi.tmp
	$(XMLTO) man $^
	@for man in $(libman_PRE); do \
	  out=`echo $$man | sed 's/\.man/.__libmansuffix__/'`; \
	  echo mv -f $$out $$man; \
	  mv -f $$out $$man || exit 1; \
	done
	@mv -f xi.tmp $@
$(libman_PRE): xi.stamp
	@if test -f $@; then :; else \
	  rm -f $<; \
	  $(MAKE) $(AM_MAKEFLAGS) $<; \
	fi
CLEANFILES += xi.tmp
MAINTAINERCLEANFILES += xi.stamp
endif # HAVE_XMLTO
