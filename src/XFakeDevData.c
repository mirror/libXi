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
AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the author shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the author.

*/

/***********************************************************************
 *
 * XFakeDeviceData - fake device data for a given device. The data will appear
 * as if would come from the device driver.
 *
 */

#include <X11/extensions/XI.h>
#include <X11/extensions/XIproto.h>
#include <X11/Xlibint.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/extutil.h>
#include "XIint.h"

int XFakeDeviceData(Display* dpy, 
                    XDevice* dev, 
                    int type,
                    int buttons, 
                    int num_valuators, 
                    int first_valuator,
                    ValuatorData* valuators)
{
    xFakeDeviceDataReq *req;

    XExtDisplayInfo *info = XInput_find_display(dpy);
    LockDisplay(dpy);

    if (_XiCheckExtInit(dpy, XInput_Initial_Release, info) == -1)
	return (NoSuchExtension);

    GetReq(FakeDeviceData, req);

    req->reqType = info->codes->major_opcode;
    req->ReqType = X_FakeDeviceData;
    req->type = type;
    req->deviceid = dev->device_id;
    req->buttons = buttons;
    req->num_valuators = num_valuators;
    req->first_valuator = first_valuator;
    req->length += num_valuators;

    if (num_valuators)
    {
        /* note: Data is a macro that uses its arguments multiple
         * times, so "nvalues" is changed in a separate assignment
         * statement */
        num_valuators <<= 2;
        Data32(dpy, (long*)valuators, num_valuators);
    }

    UnlockDisplay(dpy);
    SyncHandle();
    return Success;
}

