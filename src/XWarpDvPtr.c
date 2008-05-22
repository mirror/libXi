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
 * XWarpDevicePointer - Warp the pointer of an extension input device.
 *
 */

#include <X11/extensions/XI.h>
#include <X11/extensions/XIproto.h>
#include <X11/Xlibint.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/extutil.h>
#include "XIint.h"

int
XWarpDevicePointer(Display      *dpy,
                   XDevice      *dev,
                   Window       src_win,
                   Window       dst_win,
                   int          src_x,
                   int          src_y,
                   unsigned int src_width,
                   unsigned int src_height,
                   int          dst_x,
                   int          dst_y)
{
    register xWarpDevicePointerReq *req;

    XExtDisplayInfo *info = XInput_find_display(dpy);

    LockDisplay(dpy);
    if (_XiCheckExtInit(dpy, XInput_Initial_Release, info) == -1)
	return (NoSuchExtension);

    GetReq(WarpDevicePointer, req);
    req->reqType = info->codes->major_opcode;
    req->ReqType = X_WarpDevicePointer;
    req->deviceid = dev->device_id;
    req->src_win = src_win;
    req->dst_win = dst_win;
    req->src_x = src_x;
    req->src_y = src_y;
    req->src_width = src_width;
    req->src_height = src_height;
    req->dst_x = dst_x;
    req->dst_y = dst_y;


    UnlockDisplay(dpy);
    SyncHandle();
    return Success;
}
