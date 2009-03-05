/************************************************************

Copyright 2009 Red Hat, Inc.

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
 *
 * XISelectEvent - Select for XI2 events.
 *
 */


#include <stdint.h>
#include <X11/Xlibint.h>
#include <X11/extensions/XI.h>
#include <X11/extensions/XI2proto.h>
#include <X11/extensions/XInput2.h>
#include <X11/extensions/extutil.h>
#include <X11/extensions/ge.h>
#include <X11/extensions/geproto.h>
#include "XIint.h"

int
XISelectEvent(Display* dpy, Window win, XIDeviceEventMask* masks, int num_masks)
{
    XIDeviceEventMask  *current;
    xXISelectEventsReq  *req;
    xXIDeviceEventMask mask;
    int i;
    int len = 0;

    XExtDisplayInfo *info = XInput_find_display(dpy);
    LockDisplay(dpy);
    if (_XiCheckExtInit(dpy, XInput_Initial_Release, info) == -1)
	return (NoSuchExtension);
    GetReq(XISelectEvents, req);

    req->reqType = info->codes->major_opcode;
    req->ReqType = X_XISelectEvents;
    req->window = win;
    req->num_masks = num_masks;

    /* get the right length */
    for (i = 0; i < num_masks; i++)
    {
        len++;
        current = &masks[i];
        len += (current->mask_len + 3)/4;
    }

    SetReqLen(req, len, len);

    for (i = 0; i < num_masks; i++)
    {
        char *buff;
        current = &masks[i];
        mask.deviceid = current->deviceid;
        mask.mask_len = (current->mask_len + 3)/4;
        /* masks.mask_len is in bytes, but we need 4-byte units on the wire,
         * and they need to be padded with 0 */
        buff = calloc(1, mask.mask_len * 4);
        memcpy(buff, current->mask, current->mask_len);
        Data32(dpy, &mask, sizeof(xXIDeviceEventMask));
        Data(dpy, buff, mask.mask_len * 4);
        free(buff);
    }

    UnlockDisplay(dpy);
    SyncHandle();
    return Success;

}
