/************************************************************

Copyright 2007 Peter Hutterer <peter@cs.unisa.edu.au>

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
AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the author shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the author.

*/

/***********************************************************************
 *
 * XExtendedGrabDevice - grab an input device.
 *
 */

#include <X11/extensions/XI.h>
#include <X11/extensions/XIproto.h>
#include <X11/Xlibint.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/extutil.h>
#include "XIint.h"

int
XExtendedGrabDevice(Display*      dpy,
                    XDevice*      dev,
                    Window        grab_window,
                    int           device_mode,
                    Bool          ownerEvents,
                    Window        confineTo,
                    Cursor        cursor,
                    int           event_count,
                    XEventClass*  event_list,
                    int           generic_event_count,
                    XGenericEventMask* generic_events)        
{
    xExtendedGrabDeviceReply rep;
    xExtendedGrabDeviceReq *req;

    XExtDisplayInfo *info = XInput_find_display(dpy);

    LockDisplay(dpy);
    if (_XiCheckExtInit(dpy, XInput_Initial_Release, info) == -1)
	return (NoSuchExtension);

    GetReq(ExtendedGrabDevice, req);
    req->reqType = info->codes->major_opcode;
    req->ReqType = X_ExtendedGrabDevice;
    req->deviceid = dev->device_id;
    req->grab_window = grab_window;
    req->ungrab = False;
    req->device_mode = device_mode;
    req->owner_events = ownerEvents;
    req->confine_to = confineTo;
    req->cursor = cursor;
    req->event_count = event_count;
    req->generic_event_count = generic_event_count;
    req->time = CurrentTime;

    if (event_count)
    {
        req->length += event_count;
        event_count <<= 2;
        Data32(dpy, (long *)event_list, event_count);
    }

    if (generic_event_count)
    {
        req->length += (generic_event_count * sizeof(XGenericEventMask)) >> 2;
        Data(dpy, (char *)generic_events, generic_event_count * sizeof(XGenericEventMask));
    }

    if (_XReply(dpy, (xReply *) & rep, 0, xTrue) == 0)
	rep.status = GrabSuccess;
    UnlockDisplay(dpy);
    SyncHandle();
    return (rep.status);
}
