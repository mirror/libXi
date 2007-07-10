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
 * XQueryAccess - Query access restrictions on given window.
 *
 */

#include <X11/extensions/XI.h>
#include <X11/extensions/XIproto.h>
#include <X11/Xlibint.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/extutil.h>
#include "XIint.h"

Status
XQueryWindowAccess(Display* dpy, 
             Window win, 
             int* rule,
             XID** permdevs, 
             int* nperm, 
             XID** denydevs,
             int* ndeny)
{
    xQueryWindowAccessReq* req;
    xQueryWindowAccessReply rep;

    XExtDisplayInfo *info = XInput_find_display(dpy);

    LockDisplay(dpy);
    if (_XiCheckExtInit(dpy, XInput_Initial_Release, info) == -1)
	return (NoSuchExtension);

    GetReq(QueryWindowAccess, req);
    req->reqType = info->codes->major_opcode;
    req->ReqType = X_QueryWindowAccess;
    req->win = win;

    if (!_XReply(dpy, (xReply *) & rep, 0, xFalse)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return BadImplementation;
    }

    *rule = rep.defaultRule;
    *nperm = rep.npermit;
    *ndeny = rep.ndeny;
    *permdevs = (XID *)Xmalloc(*nperm * sizeof(XID));
    if (!*permdevs)
    {
        _XEatData(dpy, (unsigned long)rep.length << 2);
        UnlockDisplay(dpy);
        SyncHandle();
	return BadImplementation;
    }

    *denydevs = (XID*)Xmalloc(*ndeny * sizeof(XID));
    if (!*denydevs)
    {
        _XEatData(dpy, (unsigned long)rep.length << 2);
        UnlockDisplay(dpy);
        SyncHandle();
	return BadImplementation;
    }
    _XRead(dpy, (char*)*permdevs, *nperm * sizeof(XID));
    _XRead(dpy, (char*)*denydevs, *ndeny * sizeof(XID));

    /* discard padding */
    _XEatData(dpy, (rep.length << 2) - (*ndeny * sizeof(XID)) - (*nperm * sizeof(XID)));

    UnlockDisplay(dpy);
    SyncHandle();
    return Success;

}
