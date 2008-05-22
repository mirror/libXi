/************************************************************

Copyright 2006 Peter Hutterer <peter@cs.unisa.edu.au>

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
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/

/***********************************************************************
 *
 * XQueryDevicePointer - Query the pointer of an extension input device.
 *
 */

#include <X11/extensions/XI.h>
#include <X11/extensions/XIproto.h>
#include <X11/Xlibint.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/extutil.h>
#include "XIint.h"

Bool
XQueryDevicePointer(Display     *dpy,
                    XDevice     *dev,
                    Window      w,
                    Window      *root,
                    Window      *child,
                    int         *root_x,
                    int         *root_y,
                    int         *win_x,
                    int         *win_y,
                    unsigned int *mask)
{
    xQueryDevicePointerReq *req;
    xQueryDevicePointerReply rep;

    XExtDisplayInfo *info = XInput_find_display(dpy);

    LockDisplay(dpy);
    if (_XiCheckExtInit(dpy, XInput_Initial_Release, info) == -1)
	return False;

    GetReq(QueryDevicePointer, req);
    req->reqType = info->codes->major_opcode;
    req->ReqType = X_QueryDevicePointer;
    req->deviceid = dev->device_id;
    req->win = w;

    if (!_XReply(dpy, (xReply *) & rep, 0, xFalse)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return False;
    }

    *root = rep.root;
    *child = rep.child;
    *root_x = cvtINT16toInt(rep.rootX);
    *root_y = cvtINT16toInt(rep.rootY);
    *win_x = cvtINT16toInt(rep.winX);
    *win_y = cvtINT16toInt(rep.winY);
    *mask = rep.mask;
    UnlockDisplay(dpy);
    SyncHandle();
    return rep.sameScreen;
}
