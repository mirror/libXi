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
 * XConfigureDeviceProperties - delete an input device's properties.
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

void
XConfigureDeviceProperty(Display* dpy, XDevice* dev, Atom property,
                         Bool pending, Bool range,
                         int num_values, long* values)
{
    xConfigureDevicePropertyReq   *req;
    int                            len;

    XExtDisplayInfo *info = XInput_find_display(dpy);

    LockDisplay(dpy);
    if (_XiCheckExtInit(dpy, XInput_Initial_Release, info) == -1)
	return;

    GetReq(ConfigureDeviceProperty, req);
    req->reqType    = info->codes->major_opcode;
    req->ReqType    = X_ConfigureDeviceProperty;
    req->deviceid   = dev->device_id;
    req->property   = property;
    req->range      = range;
    req->pending    = pending;

    len = num_values;
    if (dpy->bigreq_size || req->length + len <= (unsigned) 65535) {
	SetReqLen(req, len, len);
	len = (long)num_values << 2;
	Data32 (dpy, values, len);
    } /* else force BadLength */

    UnlockDisplay(dpy);
    SyncHandle();
    return;
}

