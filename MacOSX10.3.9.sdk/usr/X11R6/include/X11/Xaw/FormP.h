/* $Xorg: FormP.h,v 1.4 2001/02/09 02:03:43 xorgcvs Exp $ */

/***********************************************************

Copyright 1987, 1988, 1994, 1998  The Open Group

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


Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/
/* $XFree86: xc/lib/Xaw/FormP.h,v 1.14 2001/12/19 21:37:30 dawes Exp $ */

/* Form widget private definitions */

#ifndef _XawFormP_h
#define _XawFormP_h

#include <X11/Xfuncproto.h>

#include <X11/Xaw/Form.h>
#include <X11/Xaw/XawInit.h>

_XFUNCPROTOBEGIN

#define XtREdgeType "EdgeType"

typedef enum {
    LayoutPending,
    LayoutInProgress,
    LayoutDone
} LayoutState;

#define XtInheritLayout							\
((Boolean (*)(FormWidget, unsigned int, unsigned int, Bool))_XtInherit)

typedef struct {
    Boolean(*layout)(FormWidget, unsigned int, unsigned int, Bool);
#ifndef OLDXAW
    XtPointer extension;
#endif
} FormClassPart;

typedef struct _FormClassRec {
    CoreClassPart	core_class;
    CompositeClassPart	composite_class;
    ConstraintClassPart	constraint_class;
    FormClassPart	form_class;
} FormClassRec;

extern FormClassRec formClassRec;

typedef struct _FormPart {
    /* resources */
    int		default_spacing;    /* default distance between children */

    /* private */
    Dimension	old_width, old_height; /* reference value for *_virtual  */
    int		no_refigure;	    /* no re-layout while > 0		 */
    Boolean	needs_relayout;	    /* next time no_refigure == 0	 */
    Boolean	resize_in_layout;   /* should layout() do geom request?  */
    Dimension	preferred_width, preferred_height; /* cached from layout */
    Boolean	resize_is_no_op;    /* Causes resize to take not action  */
#ifndef OLDXAW
    XawDisplayList *display_list;
    XtPointer pad[4];	/* for future use and keep binary compatability */
#endif
} FormPart;

typedef struct _FormRec {
    CorePart		core;
    CompositePart	composite;
    ConstraintPart	constraint;
    FormPart		form;
} FormRec;

typedef struct _FormConstraintsPart {
    /* resources */
    XtEdgeType top, bottom, left, right;/* where to drag edge on resize */
    int		dx;		/* desired horiz offset			*/
    int		dy;		/* desired vertical offset		*/
    Widget	horiz_base;	/* measure dx from here if non-null	*/
    Widget	vert_base;	/* measure dy from here if non-null	*/
    Boolean	allow_resize;	/* True if child may request resize	*/

    /* private */
    short	virtual_width, virtual_height;
    Position	new_x, new_y;
    LayoutState	layout_state;	/* temporary layout state		*/
    Boolean	deferred_resize;/* was resized while no_refigure is set */
#ifndef OLDXAW
    short	virtual_x, virtual_y;
    XtPointer	pad[2];		/* leave some space for further optimizations
				 * in the form widget geometry
				 */
#endif
} FormConstraintsPart;

typedef struct _FormConstraintsRec {
    FormConstraintsPart	form;
} FormConstraintsRec, *FormConstraints;

_XFUNCPROTOEND

#endif /* _XawFormP_h */
