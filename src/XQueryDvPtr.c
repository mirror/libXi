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
 * XIQueryDevicePointer - Query the pointer of an extension input device.
 *
 */

#include <stdint.h>
#include <X11/extensions/XI.h>
#include <X11/extensions/XI2proto.h>
#include <X11/Xlibint.h>
#include <X11/extensions/XInput2.h>
#include <X11/extensions/extutil.h>
#include "XIint.h"

#define FP1616toDBL(x) ((x) * 1.0 / (1 << 16))

Bool
XIQueryDevicePointer(Display     *dpy,
                    int         deviceid,
                    Window      w,
                    Window      *root,
                    Window      *child,
                    int         *root_x,
                    int         *root_y,
                    int         *win_x,
                    int         *win_y,
                    unsigned int *mask)
{
    xXIQueryDevicePointerReq *req;
    xXIQueryDevicePointerReply rep;

    XExtDisplayInfo *info = XInput_find_display(dpy);

    LockDisplay(dpy);
    if (_XiCheckExtInit(dpy, XInput_Initial_Release, info) == -1)
	return False;

    GetReq(XIQueryDevicePointer, req);
    req->reqType = info->codes->major_opcode;
    req->ReqType = X_XIQueryDevicePointer;
    req->deviceid = deviceid;
    req->win = w;

    if (!_XReply(dpy, (xReply *) & rep, 0, xFalse)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return False;
    }

    *root = rep.root;
    *child = rep.child;
    *root_x = FP1616toDBL(cvtINT16toInt(rep.root_x));
    *root_y = FP1616toDBL(cvtINT16toInt(rep.root_y));
    *win_x = FP1616toDBL(cvtINT16toInt(rep.win_x));
    *win_y = FP1616toDBL(cvtINT16toInt(rep.win_y));
    *mask = rep.mask;
    UnlockDisplay(dpy);
    SyncHandle();
    return rep.same_screen;
}
