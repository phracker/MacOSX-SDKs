/************************************************************

Copyright (c) 2003, Oracle and/or its affiliates. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice (including the next
paragraph) shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

************************************************************/

#ifndef _XEVIE_H_
#define _XEVIE_H_

#include <X11/Xfuncproto.h>

#define XEVIE_UNMODIFIED    0
#define XEVIE_MODIFIED   1

#ifndef _XEVIE_SERVER_

_XFUNCPROTOBEGIN

Bool XevieQueryVersion(
    Display*			/* dpy */,
    int*			/* major_version */,
    int*			/* minor_version */
);

extern Status XevieStart(
    Display*			/* dpy */
);

Status XevieEnd(
    Display*			/* dpy */
);

Status XevieSendEvent(
    Display*                    /* dpy */,
    XEvent*			/* event */,
    int				/* data type */
);

Status XevieSelectInput(
    Display*                    /* dpy */,
    long
);


_XFUNCPROTOEND

#endif /* _XEVIE_SERVER_ */

#endif /* _XEVIE_H_ */

