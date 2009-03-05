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
    int                 device;
    int                 returnMode; /* AttachToMaster, Floating */
    int                 returnPointer;
    int                 returnKeyboard;
} XIRemoveMasterInfo;

typedef struct {
    int                 type;
    int                 device;
    int                 newMaster;
} XIAttachSlaveInfo;

typedef struct {
    int                 type;
    int                 device;
} XIDetachSlaveInfo;

typedef union {
    int                   type; /* must be first element */
    XICreateMasterInfo    create;
    XIRemoveMasterInfo    remove;
    XIAttachSlaveInfo     attach;
    XIDetachSlaveInfo     detach;
} XIAnyHierarchyChangeInfo;

typedef struct
{
    int                 deviceid;
    int                 mask_len;
    unsigned char*      mask;
} XIDeviceEventMask;

typedef struct
{
    int         type;
} XIAnyClassInfo;

typedef struct
{
    int         type;
    int         num_buttons;
    Atom        *buttons;
} XIButtonClassInfo;

typedef struct
{
    int         type;
    int         num_keycodes;
    int         *keycodes;
} XIKeyClassInfo;

typedef struct
{
    int         type;
    int         number;
    Atom        name;
    double      min;
    double      max;
    int         resolution;
    int         mode;
} XIValuatorClassInfo;

typedef struct
{
    int                 deviceid;
    char*               name;
    int                 use;
    int                 attachment;
    Bool                enabled;
    int                 num_classes;
    XIAnyClassInfo      **classes;
} XIDeviceInfo;

/**
 * Generic XI2 event. All XI2 events have the same header.
 * Note: this event is padded to be the same size as libX11's XEvent.
 */
typedef struct {
    int           type;         /* GenericEvent */
    unsigned long serial;       /* # of last request processed by server */
    Bool          send_event;   /* true if this came from a SendEvent request */
    Display       *display;     /* Display the event was read from */
    int           extension;    /* XI extension offset */
    int           evtype;
    Time          time;
    char          pad[68];      /* force same size as XEvent */
} XIEvent;

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

typedef struct
{
    int    base;
    int    latched;
    int    locked;
} XIModifierState;

typedef XIModifierState XIGroupState;

typedef struct {
    int           mask_len;
    unsigned char *mask;
} XIButtonState;

typedef struct {
    int           mask_len;
    unsigned char *mask;
    double        *values;
} XIValuatorState;

typedef struct {
    int           type;         /* GenericEvent */
    unsigned long serial;       /* # of last request processed by server */
    Bool          send_event;   /* true if this came from a SendEvent request */
    Display       *display;     /* Display the event was read from */
    int           extension;    /* XI extension offset */
    int           evtype;
    Time          time;
    int           detail;
    Window        root;
    Window        event;
    Window        child;
    int           deviceid;
    int           sourceid;
    float         root_x;
    float         root_y;
    float         event_x;
    float         event_y;
    XIButtonState       *buttons;
    XIValuatorState     *valuators;
    XIModifierState      *mods;
    XIGroupState         *group;
} XIDeviceEvent;

_XFUNCPROTOBEGIN

extern Bool     XIQueryDevicePointer(
    Display*            display,
    int                 deviceid,
    Window              win,
    Window*             root,
    Window*             child,
    int*                root_x,
    int*                root_y,
    int*                win_x,
    int*                win_y,
    unsigned int*       mask
);

extern Bool     XIWarpDevicePointer(
    Display*            display,
    int                 deviceid,
    Window              src_win,
    Window              dst_win,
    int                 src_x,
    int                 src_y,
    unsigned int        src_width,
    unsigned int        src_height,
    int                 dst_x,
    int                 dst_y
);

extern Status   XIDefineDeviceCursor(
    Display*            display,
    int                 deviceid,
    Window              win,
    Cursor              cursor
);

extern Status   XIUndefineDeviceCursor(
    Display*            display,
    int                 deviceid,
    Window              win
);

extern Status   XIChangeDeviceHierarchy(
    Display*            display,
    XIAnyHierarchyChangeInfo*  changes,
    int                 num_changes
);

extern Status   XISetClientPointer(
    Display*            dpy,
    Window              win,
    int                 deviceid
);

extern Bool     XIGetClientPointer(
    Display*            dpy,
    Window              win,
    int*                deviceid
);

extern int      XISelectEvent(
     Display*            dpy,
     Window              win,
     XIDeviceEventMask*  masks,
     int                 nmasks
);

extern Status XIQueryVersion(
     Display*           dpy,
     int*               major_version_return,
     int*               minor_version_return
);

extern XIDeviceInfo* XIQueryDevice(
     Display*           dpy,
     int                deviceid,
     int*               ndevices_return
);

extern void XIFreeDeviceInfo(XIDeviceInfo       *info);

_XFUNCPROTOEND

#endif /* XINPUT2_H */
