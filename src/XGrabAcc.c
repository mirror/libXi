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
 * XGrabAccessControl - Register a client as allowed to control access to
 * windows. 
 * Returns True on success or false otherwise.
 *
 */

#include <X11/extensions/XI.h>
#include <X11/extensions/XIproto.h>
#include <X11/Xlibint.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/extutil.h>
#include "XIint.h"

Bool 
XGrabAccessControl(Display* dpy)
{
    xGrabAccessControlReq* req;
    xGrabAccessControlReply rep;

    XExtDisplayInfo *info = XInput_find_display(dpy);

    LockDisplay(dpy);
    if (_XiCheckExtInit(dpy, XInput_Initial_Release, info) == -1)
	return (NoSuchExtension);

    GetReq(GrabAccessControl, req);

    req->reqType = info->codes->major_opcode;
    req->ReqType = X_GrabAccessControl;
    req->ungrab = False;

    if (!_XReply(dpy, (xReply *) & rep, 0, xFalse)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return False;
    }

    UnlockDisplay(dpy);
    SyncHandle();
    return rep.success;
}
