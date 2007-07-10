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
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/

/***********************************************************************
 *
 * XPermitDevices - Change list of devices allowed to access a window.
 *
 */

#include <X11/extensions/XI.h>
#include <X11/extensions/XIproto.h>
#include <X11/Xlibint.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/extutil.h>
#include "XIint.h"

Status
XPermitDevices(Display* dpy, Window win, XID* devices, int count)
{
    xChangeWindowAccessReq* req;

    XExtDisplayInfo *info = XInput_find_display(dpy);

    LockDisplay(dpy);
    if (_XiCheckExtInit(dpy, XInput_Initial_Release, info) == -1)
	return (NoSuchExtension);

    GetReq(ChangeWindowAccess, req);
    req->reqType = info->codes->major_opcode;
    req->ReqType = X_ChangeWindowAccess;
    req->win = win;
    /* If list is empty, clear all devices */
    if (! count)
	req->clear = WindowAccessClearPerm;
    else
        req->clear = WindowAccessClearNone;
    req->defaultRule = WindowAccessKeepRule;
    req->npermit = count;
    req->length += (count * sizeof(XID) + 3) >> 2;
    req->ndeny = 0;
    Data(dpy, (char*)devices, count * sizeof(XID));

    UnlockDisplay(dpy);
    SyncHandle();
    return Success;
}
