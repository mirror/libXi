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

/* Definitions used by the library and client */

#ifndef _XINPUT2_H_
#define _XINPUT2_H_

#include <X11/Xlib.h>
#include <X11/extensions/XI2.h>
#include <X11/extensions/Xge.h>

/*******************************************************************
 *
 */
typedef struct {
    int                 type;
    char*               name;
    Bool                sendCore;
    Bool                enable;
} XICreateMasterInfo;

typedef struct {
    int                 type;
    XDevice*            device;
    int                 returnMode; /* AttachToMaster, Floating */
    XDevice*            returnPointer;
    XDevice*            returnKeyboard;
} XIRemoveMasterInfo;

typedef struct {
    int                 type;
    XDevice*            device;
    XDevice*            newMaster;
} XIAttachSlaveInfo;

typedef struct {
    int                 type;
    XDevice*            device;
} XIDetachSlaveInfo;

typedef union {
    int                   type; /* must be first element */
    XICreateMasterInfo    create;
    XIRemoveMasterInfo    remove;
    XIAttachSlaveInfo     attach;
    XIDetachSlaveInfo     detach;
} XIAnyHierarchyChangeInfo;

_XFUNCPROTOBEGIN

extern Bool     XIQueryDevicePointer(
    Display*            /* display */,
    XDevice*            /* device */,
    Window              /* win */,
    Window*             /* root */,
    Window*             /* child */,
    int*                /* root_x */,
    int*                /* root_y */,
    int*                /* win_x */,
    int*                /* win_y */,
    unsigned int*       /* mask */
);

extern Bool     XIWarpDevicePointer(
    Display*            /* display */,
    XDevice*            /* device */,
    Window              /* src_win */,
    Window              /* dst_win */,
    int                 /* src_x */,
    int                 /* src_y */,
    unsigned int        /* src_width */,
    unsigned int        /* src_height */,
    int                 /* dst_x */,
    int                 /* dst_y */
);

extern Status   XIDefineDeviceCursor(
    Display*            /* display */,
    XDevice*            /* device */,
    Window              /* win */,
    Cursor              /* cursor */
);

extern Status   XIUndefineDeviceCursor(
    Display*            /* display */,
    XDevice*            /* device */,
    Window              /* win */
);

extern Status   XIChangeDeviceHierarchy(
    Display*            /* display */,
    XIAnyHierarchyChangeInfo*  /* changes*/,
    int                 /* num_changes */
);

extern Status   XISetClientPointer(
    Display*            /* dpy */,
    Window              /* win */,
    XDevice*            /* device */
);

extern Bool     XIGetClientPointer(
    Display*            /* dpy */,
    Window              /* win */,
    int*                /* deviceid */
);

typedef CARD16 XIEventType;

typedef struct
{
    int         deviceid;
    int         num_types;
    XIEventType *types;
} XIDeviceEventMask;

extern int
XISelectEvent(
     Display*           /* dpy */,
     Window             /* win */,
     XIDeviceEventMask** /* masks*/,
     int                 /* nmasks */
);

_XFUNCPROTOEND

/*
 * Notifies the client that the device hierarchy has been changed. The client
 * is expected to re-query the server for the device hierarchy.
 */
typedef struct {
    int           type;         /* GenericEvent */
    unsigned long serial;       /* # of last request processed by server */
    Bool          send_event;   /* true if this came from a SendEvent request */
    Display       *display;     /* Display the event was read from */
    int           extension;    /* XI extension offset */
    int           evtype;       /* XI_DeviceHierarchyChangedNotify */
    Time          time;
} XDeviceHierarchyChangedEvent;

/*
 * Notifies the client that the classes have been changed. This happens when
 * the slave device that sends through the master changes.
 */
typedef struct {
    int           type;         /* GenericEvent */
    unsigned long serial;       /* # of last request processed by server */
    Bool          send_event;   /* true if this came from a SendEvent request */
    Display       *display;     /* Display the event was read from */
    int           extension;    /* XI extension offset */
    int           evtype;       /* XI_DeviceHierarchyChangedNotify */
    Time          time;
    XID           deviceid;     /* id of the device that changed */
    XID           slaveid;      /* id of the slave device that caused the
                                   change */
    int           num_classes;
    XIAnyClassInfo *inputclassinfo; /* same as in XDeviceInfo */
} XDeviceClassesChangedEvent;

#endif /* XINPUT2_H */
