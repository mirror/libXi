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

#include <X11/Xlibint.h>
#include <X11/extensions/XInput2.h>

/**
 * Free memory associated with the given event, but not the event itself.
 */
void
XIFreeEventData(XIEvent *event)
{
    if (event->type != GenericEvent)
        return;

    switch(event->evtype)
    {
        case XI_Motion:
        case XI_ButtonPress:
        case XI_ButtonRelease:
        case XI_KeyPress:
        case XI_KeyRelease:
            {
                XIDeviceEvent *ev = (XIDeviceEvent*)event;
                free(ev->buttons);
                free(ev->valuators);
                free(ev->mods);
                free(ev->group);
            }
            break;
        case XI_DeviceChanged:
            free(((XIDeviceChangedEvent*)event)->classes);
            break;
        case XI_HierarchyChanged:
            free(((XIDeviceHierarchyEvent*)event)->info);
            break;
        case XI_RawEvent:
            free(((XIRawDeviceEvent*)event)->valuators->values);
            free(((XIRawDeviceEvent*)event)->valuators);
            free(((XIRawDeviceEvent*)event)->raw_values);
            break;
    }
}
