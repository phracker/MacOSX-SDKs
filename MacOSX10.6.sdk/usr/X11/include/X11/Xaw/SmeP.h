/*
 * $Xorg: SmeP.h,v 1.4 2001/02/09 02:03:46 xorgcvs Exp $
 *
Copyright 1989, 1994, 1998  The Open Group

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
/* $XFree86: xc/lib/Xaw/SmeP.h,v 1.8 2001/12/14 19:54:43 dawes Exp $ */

/*
 * This is the private header file for the Athena Sme object.
 * This object is intended to be used with the simple menu widget.  
 *
 * Date:    April 3, 1989
 *
 * By:      Chris D. Peterson
 *          MIT X Consortium 
 *          kit@expo.lcs.mit.edu
 */

#ifndef _XawSmeP_h
#define _XawSmeP_h

/*
 * Sme Widget Private Data
 */
#include <X11/Xfuncproto.h>

#include <X11/Xaw/Sme.h>

_XFUNCPROTOBEGIN

/* New fields for the Sme widget class */
typedef struct _SmeClassPart {
    XtWidgetProc highlight;
    XtWidgetProc unhighlight;
    XtWidgetProc notify;
    XtPointer	 extension;
} SmeClassPart;

/* Full class record */
typedef struct _SmeClassRec {
    RectObjClassPart    rect_class;
    SmeClassPart	sme_class;
} SmeClassRec;

extern SmeClassRec smeClassRec;

/* New fields for the Sme widget */
typedef struct {
    /* resources */
    XtCallbackList callbacks;
    Boolean international;
#ifndef OLDXAW
    XtPointer pad[4];	/* for future use and keep binary compatability */
#endif
} SmePart;

/* Full instance record */
typedef struct _SmeRec {
    ObjectPart	object;
    RectObjPart	rectangle;
    SmePart	sme;
} SmeRec;

#define XtInheritHighlight	((XtWidgetProc)_XtInherit)
#define XtInheritUnhighlight XtInheritHighlight
#define XtInheritNotify      XtInheritHighlight

_XFUNCPROTOEND

#endif /* _XawSmeP_h */
