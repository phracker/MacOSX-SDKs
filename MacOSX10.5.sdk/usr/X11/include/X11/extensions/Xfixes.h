/*
 * $XFree86: xc/lib/Xfixes/Xfixes.h,v 1.1 2002/11/30 06:21:45 keithp Exp $
 *
 * Copyright © 2006 Sun Microsystems
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Sun Microsystems not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Sun Microsystems makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * Copyright © 2002 Keith Packard, member of The XFree86 Project, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Keith Packard not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Keith Packard makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * KEITH PACKARD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL KEITH PACKARD BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _XFIXES_H_
#define _XFIXES_H_

#include <X11/extensions/xfixeswire.h>

#include <X11/Xfuncproto.h>
#include <X11/Xlib.h>

/*
 * This revision number also appears in configure.ac, they have
 * to be manually synchronized
 */
#define XFIXES_REVISION	1
#define XFIXES_VERSION	((XFIXES_MAJOR * 10000) + (XFIXES_MINOR * 100) + (XFIXES_REVISION))

typedef struct {
    int type;			/* event base */
    unsigned long serial;
    Bool send_event;
    Display *display;
    Window window;
    int subtype;
    Window owner;
    Atom selection;
    Time timestamp;
    Time selection_timestamp;
} XFixesSelectionNotifyEvent;

typedef struct {
    int type;			/* event base */
    unsigned long serial;
    Bool send_event;
    Display *display;
    Window window;
    int subtype;
    unsigned long cursor_serial;
    Time timestamp;
    Atom cursor_name;
} XFixesCursorNotifyEvent;

typedef struct {
    short	    x, y;
    unsigned short  width, height;
    unsigned short  xhot, yhot;
    unsigned long   cursor_serial;
    unsigned long   *pixels;
#if XFIXES_MAJOR >= 2
    Atom	    atom;		    /* Version >= 2 only */
    const char	    *name;		    /* Version >= 2 only */
#endif
} XFixesCursorImage;

#if XFIXES_MAJOR >= 2
/* Version 2 types */

typedef XID XserverRegion;

typedef struct {
    short	    x, y;
    unsigned short  width, height;
    unsigned short  xhot, yhot;
    unsigned long   cursor_serial;
    unsigned long   *pixels;
    Atom	    atom;
    const char	    *name;
} XFixesCursorImageAndName;

#endif

_XFUNCPROTOBEGIN

Bool XFixesQueryExtension (Display *dpy, int *event_basep, int *error_basep);
Status XFixesQueryVersion (Display *dpy,
			    int     *major_versionp,
			    int     *minor_versionp);

int XFixesVersion (void);

void
XFixesChangeSaveSet (Display	*dpy,
		     Window	win,
		     int	mode,
		     int	target,
		     int	map);

void
XFixesSelectSelectionInput (Display	    *dpy,
			    Window	    win,
			    Atom	    selection, 
			    unsigned long   eventMask);

void
XFixesSelectCursorInput (Display	*dpy,
			 Window		win,
			 unsigned long	eventMask);

XFixesCursorImage *
XFixesGetCursorImage (Display *dpy);

#if XFIXES_MAJOR >= 2
/* Version 2 functions */

XserverRegion
XFixesCreateRegion (Display *dpy, XRectangle *rectangles, int nrectangles);

XserverRegion
XFixesCreateRegionFromBitmap (Display *dpy, Pixmap bitmap);

XserverRegion
XFixesCreateRegionFromWindow (Display *dpy, Window window, int kind);

XserverRegion
XFixesCreateRegionFromGC (Display *dpy, GC gc);

XserverRegion
XFixesCreateRegionFromPicture (Display *dpy, XID picture);

void
XFixesDestroyRegion (Display *dpy, XserverRegion region);

void
XFixesSetRegion (Display *dpy, XserverRegion region,
		 XRectangle *rectangles, int nrectangles);

void
XFixesCopyRegion (Display *dpy, XserverRegion dst, XserverRegion src);

void
XFixesUnionRegion (Display *dpy, XserverRegion dst,
		   XserverRegion src1, XserverRegion src2);

void
XFixesIntersectRegion (Display *dpy, XserverRegion dst,
		       XserverRegion src1, XserverRegion src2);

void
XFixesSubtractRegion (Display *dpy, XserverRegion dst,
		      XserverRegion src1, XserverRegion src2);

void
XFixesInvertRegion (Display *dpy, XserverRegion dst,
		    XRectangle *rect, XserverRegion src);

void
XFixesTranslateRegion (Display *dpy, XserverRegion region, int dx, int dy);

void
XFixesRegionExtents (Display *dpy, XserverRegion dst, XserverRegion src);

XRectangle *
XFixesFetchRegion (Display *dpy, XserverRegion region, int *nrectanglesRet);

XRectangle *
XFixesFetchRegionAndBounds (Display *dpy, XserverRegion region, 
			    int *nrectanglesRet,
			    XRectangle *bounds);

void
XFixesSetGCClipRegion (Display *dpy, GC gc, 
		       int clip_x_origin, int clip_y_origin,
		       XserverRegion region);

void
XFixesSetWindowShapeRegion (Display *dpy, Window win, int shape_kind,
			    int x_off, int y_off, XserverRegion region);

void
XFixesSetPictureClipRegion (Display *dpy, XID picture,
			    int clip_x_origin, int clip_y_origin,
			    XserverRegion region);

void
XFixesSetCursorName (Display *dpy, Cursor cursor, const char *name);

const char *
XFixesGetCursorName (Display *dpy, Cursor cursor, Atom *atom);

void
XFixesChangeCursor (Display *dpy, Cursor source, Cursor destination);

void
XFixesChangeCursorByName (Display *dpy, Cursor source, const char *name);

#endif	/* XFIXES_MAJOR >= 2 */

#if XFIXES_MAJOR >= 3

void
XFixesExpandRegion (Display *dpy, XserverRegion dst, XserverRegion src,
		    unsigned left, unsigned right,
		    unsigned top, unsigned bottom);

#endif	/* XFIXES_MAJOR >= 3 */

#if XFIXES_MAJOR >= 4
/* Version 4.0 externs */

void
XFixesHideCursor (Display *dpy, Window win);

void
XFixesShowCursor (Display *dpy, Window win);

#endif /* XFIXES_MAJOR >= 4 */

_XFUNCPROTOEND

#endif /* _XFIXES_H_ */
