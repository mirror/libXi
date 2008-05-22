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
 * XChangeDeviceHierarch - change the device hierarchy, i.e. which slave
 * device is attached to which master, etc.
 */

#include <X11/extensions/XI.h>
#include <X11/extensions/XIproto.h>
#include <X11/Xlibint.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/extutil.h>
#include "XIint.h"

int
XChangeDeviceHierarchy(Display* dpy,
                       XAnyHierarchyChangeInfo* changes,
                       int num_changes)
{
    XAnyHierarchyChangeInfo* any;
    xChangeDeviceHierarchyReq *req;
    XExtDisplayInfo *info = XInput_find_display(dpy);
    char *data = NULL, *dptr;
    int dlen = 0, i;

    LockDisplay(dpy);
    if (_XiCheckExtInit(dpy, XInput_2, info) == -1)
	return (NoSuchExtension);

    GetReq(ChangeDeviceHierarchy, req);
    req->reqType = info->codes->major_opcode;
    req->ReqType = X_ChangeDeviceHierarchy;
    req->num_changes = num_changes;

    /* alloc required memory */
    for (i = 0, any = changes; i < num_changes; i++, any++)
    {
        switch(any->type)
        {
            case CH_CreateMasterDevice:
                {
                    int slen = (strlen(any->create.name));
                    dlen += sizeof(xCreateMasterInfo) + 
                        slen + (4 - (slen % 4));
                }
                break;
            case CH_RemoveMasterDevice:
                dlen += sizeof(xRemoveMasterInfo);
                break;
            case CH_ChangeAttachment:
                dlen += sizeof(xChangeAttachmentInfo);
                break;
            default:
                return BadValue;
        }
    }

    req->length += dlen / 4; /* dlen is 4-byte aligned */
    data = Xmalloc(dlen);
    if (!data)
        return BadAlloc;

    dptr = data;
    for (i = 0, any = changes; i < num_changes; i++, any++)
    {
        switch(any->type)
        {
                case CH_CreateMasterDevice:
                {
                    XCreateMasterInfo* C = &any->create;
                    xCreateMasterInfo* c = (xCreateMasterInfo*)dptr;
                    c->type = C->type;
                    c->sendCore = C->sendCore;
                    c->enable = C->enable;
                    c->namelen = strlen(C->name);
                    c->length = sizeof(xCreateMasterInfo) + c->namelen + 
                        (4 - (c->namelen % 4));
                    strncpy((char*)&c[1], C->name, c->namelen);
                    dptr += c->length;
                }
                break;
            case CH_RemoveMasterDevice:
                {
                    XRemoveMasterInfo* R = &any->remove;
                    xRemoveMasterInfo* r = (xRemoveMasterInfo*)dptr;
                    r->type = R->type;
                    r->returnMode = R->returnMode;
                    r->deviceid = R->device->device_id;
                    r->length = sizeof(xRemoveMasterInfo);
                    if (r->returnMode == AttachToMaster)
                    {
                        r->returnPointer = R->returnPointer->device_id;
                        r->returnKeyboard = R->returnKeyboard->device_id;
                    }
                    dptr += sizeof(xRemoveMasterInfo);
                }
                break;
            case CH_ChangeAttachment:
                {
                    XChangeAttachmentInfo* C = &any->change;
                    xChangeAttachmentInfo* c = (xChangeAttachmentInfo*)dptr;

                    c->type = C->type;
                    c->deviceid = C->device->device_id;
                    c->changeMode = C->changeMode;
                    c->length = sizeof(xChangeAttachmentInfo);
                    if (c->changeMode == AttachToMaster)
                        c->newMaster = C->newMaster->device_id;

                    dptr += sizeof(xChangeAttachmentInfo);
                }
                break;
        }
    }

    Data(dpy, data, dlen);
    Xfree(data);
    UnlockDisplay(dpy);
    SyncHandle();
    return Success;
}
