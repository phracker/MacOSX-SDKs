/*
 * $Xorg: PortholeP.h,v 1.4 2001/02/09 02:03:45 xorgcvs Exp $
 *
Copyright 1990, 1994, 1998  The Open Group

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
 *
 * Author:  Jim Fulton, MIT X Consortium
 */
/* $XFree86: xc/lib/Xaw/PortholeP.h,v 1.7 2001/01/17 19:42:29 dawes Exp $ */

#ifndef _XawPortholeP_h
#define _XawPortholeP_h

#include <X11/Xaw/Porthole.h>

/* new fields in widget class */
typedef struct {
    XtPointer extension;
} PortholeClassPart;

/* widget class */
typedef struct _PortholeClassRec {
    CoreClassPart core_class;
    CompositeClassPart composite_class;
    PortholeClassPart porthole_class;
} PortholeClassRec;

/* new fields in widget */
typedef struct {
    /* resources */
    XtCallbackList report_callbacks;	/* callback/Callback */
#ifndef OLDXAW
    XtPointer pad[4];	/* for future use and keep binary compatability */
#endif
} PortholePart;

typedef struct _PortholeRec {
    CorePart core;
    CompositePart composite;
    PortholePart porthole;
} PortholeRec;

extern PortholeClassRec portholeClassRec;

#endif /* _XawPortholeP_h */
