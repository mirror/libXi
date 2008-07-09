/************************************************************

Copyright 2008 Peter Hutterer

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the author shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the author.

*/

/***********************************************************************
 * XQueryDeviceProperties - query an input device's properties.
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <X11/Xlibint.h>
#include <X11/extensions/XI.h>
#include <X11/extensions/XIproto.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/extutil.h>
#include "XIint.h"

XIPropertyInfo*
XQueryDeviceProperty(Display* dpy, XDevice* dev, Atom property)
{
    xQueryDevicePropertyReq   *req;
    xQueryDevicePropertyReply rep;
    int                       len;
    int                       rbytes, nbytes;
    XIPropertyInfo            *prop_info;

    XExtDisplayInfo *info = XInput_find_display(dpy);

    LockDisplay(dpy);
    if (_XiCheckExtInit(dpy, XInput_Initial_Release, info) == -1)
	return NULL;

    GetReq(QueryDeviceProperty, req);
    req->reqType    = info->codes->major_opcode;
    req->ReqType    = X_QueryDeviceProperty;
    req->deviceid   = dev->device_id;
    req->property   = property;

    if (!_XReply(dpy, (xReply*)&rep, 0, xFalse)) {
        UnlockDisplay(dpy);
        SyncHandle();
        return NULL;
    }

    rbytes = sizeof (XIPropertyInfo) + rep.length * sizeof (long);
    nbytes = rep.length << 2;

    prop_info = (XIPropertyInfo*) Xmalloc (rbytes);
    if (prop_info == NULL) {
	_XEatData (dpy, nbytes);
	UnlockDisplay (dpy);
	SyncHandle ();
	return NULL;
    }

    prop_info->pending = rep.pending;
    prop_info->range = rep.range;
    prop_info->immutable = rep.immutable;
    prop_info->fromClient = rep.fromClient;
    prop_info->num_values = rep.length;
    if (rep.length != 0) {
	prop_info->values = (long *) (prop_info + 1);
	_XRead32 (dpy, prop_info->values, nbytes);
    } else {
	prop_info->values = NULL;
    }

    UnlockDisplay(dpy);
    SyncHandle();
    return prop_info;
}

