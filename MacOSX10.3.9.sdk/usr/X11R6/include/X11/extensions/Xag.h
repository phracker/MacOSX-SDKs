/* $XFree86: xc/include/extensions/Xag.h,v 1.5 2001/12/17 20:52:24 dawes Exp $ */
/*
Copyright 1996, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.
*/
/* $Xorg: Xag.h,v 1.5 2001/02/09 02:03:24 xorgcvs Exp $ */

#ifndef _XAG_H_
#define _XAG_H_

#include <X11/Xfuncproto.h>

#define X_XagQueryVersion		0
#define X_XagCreate			1
#define X_XagDestroy			2
#define X_XagGetAttr			3
#define X_XagQuery			4
#define X_XagCreateAssoc		5
#define X_XagDestroyAssoc		6

#define XagBadAppGroup			0
#define XagNumberErrors			(XagBadAppGroup + 1)

#define XagNsingleScreen		7
#define XagNdefaultRoot			1
#define XagNrootVisual			2
#define XagNdefaultColormap		3
#define XagNblackPixel			4
#define XagNwhitePixel			5
#define XagNappGroupLeader		6

#ifndef _XAG_SERVER_

#include <stdarg.h>

_XFUNCPROTOBEGIN

typedef XID XAppGroup;

Bool XagQueryVersion(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    int*			/* major_version */,
    int*			/* minor_version */
#endif
);

Status XagCreateEmbeddedApplicationGroup(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    VisualID			/* root_visual */,
    Colormap			/* default_colormap */,
    unsigned long		/* black_pixel */,
    unsigned long		/* white_pixel */,
    XAppGroup*			/* app_group_return */
#endif
);

Status XagCreateNonembeddedApplicationGroup(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    XAppGroup*			/* app_group_return */
#endif
);

Status XagDestroyApplicationGroup(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    XAppGroup			/* app_group */
#endif
);

Status XagGetApplicationGroupAttributes(
#if NeedVarargsPrototypes
    Display*			/* dpy */,
    XAppGroup			/* app_group */,
    ...
#endif
);

Status XagQueryApplicationGroup(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    XID				/* resource_base */,
    XAppGroup*			/* app_group_ret */
#endif
);

Status XagCreateAssociation(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    Window*			/* window_ret */,
    void*			/* system_window */
#endif
);

Status XagDestroyAssociation(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    Window			/* window */
#endif
);

_XFUNCPROTOEND

#endif /* _XAG_SERVER_ */

#endif /* _XAG_H_ */

