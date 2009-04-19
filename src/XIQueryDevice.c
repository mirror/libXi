/*
 * Copyright © 2009 Red Hat, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include <stdint.h>
#include <X11/Xlibint.h>
#include <X11/extensions/XI2proto.h>
#include <X11/extensions/XInput2.h>
#include <X11/extensions/extutil.h>
#include "XIint.h"

/* Copy classes from any into to->classes and return the number of bytes
 * copied. Memory layout of to->classes is
 * [clsptr][clsptr][clsptr][classinfo][classinfo]...
 *    |________|___________^
 *             |______________________^
 */
int
copy_classes(XIDeviceInfo* to, xXIAnyInfo* from, int nclasses)
{
    XIAnyClassInfo *any_lib;
    xXIAnyInfo *any_wire;
    char *ptr_wire, *ptr_lib;
    int i, len;

    /* size them up first */
    len = nclasses * sizeof(XIAnyClassInfo*); /* len for to->classes */
    ptr_wire = (char*)from;
    for (i = 0; i < nclasses; i++)
    {
        int l = 0;
        any_wire = (xXIAnyInfo*)ptr_wire;
        switch(any_wire->type)
        {
            case ButtonClass:
                l = sizeof(XIButtonClassInfo);
                l += ((xXIButtonInfo*)any_wire)->num_buttons * sizeof(Atom);
                break;
            case KeyClass:
                l = sizeof(XIKeyClassInfo);
                l += ((xXIKeyInfo*)any_wire)->num_keycodes * sizeof(int);
                break;
            case ValuatorClass:
                l = sizeof(XIValuatorClassInfo);
                break;
        }

        len += l;
        ptr_wire += any_wire->length * 4;
    }

    to->classes = Xmalloc(len);
    if (!to->classes)
        return -1;

    ptr_wire = (char*)from;
    ptr_lib = (char*)&to->classes[nclasses];
    len = 0; /* count wire length */

    for (i = 0; i < nclasses; i++)
    {
        any_lib = (XIAnyClassInfo*)ptr_lib;
        any_wire = (xXIAnyInfo*)ptr_wire;

        to->classes[i] = any_lib;
        any_lib->type = any_wire->type;
        switch(any_wire->type)
        {
            case ButtonClass:
                {
                    XIButtonClassInfo *cls_lib;
                    xXIButtonInfo *cls_wire;

                    cls_lib = (XIButtonClassInfo*)any_lib;
                    cls_wire = (xXIButtonInfo*)any_wire;

                    cls_lib->num_buttons = cls_wire->num_buttons;
                    cls_lib->buttons = (Atom*)&cls_lib[1];
                    memcpy(cls_lib->buttons, &cls_wire[1],
                            cls_lib->num_buttons);

                    ptr_lib += sizeof(XIButtonClassInfo);
                    ptr_lib += cls_lib->num_buttons * sizeof(Atom);
                    break;
                }
            case KeyClass:
                {
                    XIKeyClassInfo *cls_lib;
                    xXIKeyInfo *cls_wire;

                    cls_lib = (XIKeyClassInfo*)any_lib;
                    cls_wire = (xXIKeyInfo*)any_wire;

                    cls_lib->num_keycodes = cls_wire->num_keycodes;
                    cls_lib->keycodes = (int*)&cls_lib[1];
                    memcpy(cls_lib->keycodes, &cls_wire[1],
                            cls_lib->num_keycodes);

                    ptr_lib += sizeof(XIKeyClassInfo);
                    ptr_lib += cls_lib->num_keycodes * sizeof(int);
                    break;
                }
            case ValuatorClass:
                {
                    XIValuatorClassInfo *cls_lib;
                    xXIValuatorInfo *cls_wire;

                    cls_lib = (XIValuatorClassInfo*)any_lib;
                    cls_wire = (xXIValuatorInfo*)any_wire;

                    cls_lib->number = cls_wire->number;
                    cls_lib->name   = cls_wire->name;
                    cls_lib->resolution = cls_wire->resolution;
                    cls_lib->min        = cls_wire->min.integral;
                    cls_lib->max        = cls_wire->max.integral;
                    /* FIXME: fractional parts */
                    cls_lib->mode       = cls_wire->mode;

                }
                ptr_lib += sizeof(XIValuatorClassInfo);
                break;
        }
        len += any_wire->length * 4;
        ptr_wire += any_wire->length * 4;
    }
    return len;
}

XIDeviceInfo*
XIQueryDevice(Display *dpy, int deviceid, int *ndevices_return)
{
    XIDeviceInfo        *info = NULL;
    xXIQueryDeviceReq   *req;
    xXIQueryDeviceReply reply;
    char                *ptr;
    int                 i;
    char                *buf;

    XExtDisplayInfo *extinfo = XInput_find_display(dpy);

    LockDisplay(dpy);
    if (_XiCheckExtInit(dpy, Dont_Check, extinfo) == -1)
	goto error;

    GetReq(XIQueryDevice, req);
    req->reqType  = extinfo->codes->major_opcode;
    req->ReqType  = X_XIQueryDevice;
    req->deviceid = deviceid;

    if (!_XReply(dpy, (xReply*) &reply, 0, xFalse))
        goto error;

    *ndevices_return = reply.num_devices;
    info = Xmalloc((reply.num_devices + 1) * sizeof(XIDeviceInfo));
    if (!info)
        goto error;

    buf = Xmalloc(reply.length * 4);
    _XRead(dpy, buf, reply.length * 4);
    ptr = buf;

    /* info is a null-terminated array */
    info[reply.num_devices].name = NULL;

    for (i = 0; i < reply.num_devices; i++)
    {
        XIDeviceInfo    *lib = &info[i];
        xXIDeviceInfo   *wire = (xXIDeviceInfo*)ptr;

        lib->deviceid    = wire->deviceid;
        lib->use         = wire->use;
        lib->attachment  = wire->attachment;
        lib->enabled     = wire->enabled;
        lib->num_classes = wire->num_classes;
        lib->classes     = (XIAnyClassInfo**)&lib[1];

        ptr += sizeof(xXIDeviceInfo);

        lib->name = Xcalloc(wire->name_len + 1, 1);
        strncpy(lib->name, ptr, wire->name_len);
        ptr += ((wire->name_len + 3)/4) * 4;

        ptr += copy_classes(lib, (xXIAnyInfo*)ptr, lib->num_classes);
    }

    Xfree(buf);
    UnlockDisplay(dpy);
    SyncHandle();
    return info;

error:
    UnlockDisplay(dpy);
    SyncHandle();
    *ndevices_return = -1;
    return NULL;
}

void
XIFreeDeviceInfo(XIDeviceInfo* info)
{
    XIDeviceInfo *ptr = info;
    while(ptr->name)
    {
        Xfree(ptr->classes);
        Xfree(ptr->name);
        ptr++;
    }
    Xfree(info);
}
