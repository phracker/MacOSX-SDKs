/* $Xorg: WidgetNode.h,v 1.5 2001/02/09 02:03:53 xorgcvs Exp $ */

/*

Copyright 1990, 1998  The Open Group

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
/* $XFree86: xc/lib/Xmu/WidgetNode.h,v 1.5 2001/01/17 19:42:57 dawes Exp $ */

/*
 * Author:  Jim Fulton, MIT X Consortium
 */

#ifndef _XmuWidgetNode_h
#define _XmuWidgetNode_h

#include <X11/Intrinsic.h>
#include <X11/Xfuncproto.h>

/*
 * This is usually initialized by setting the first two fields and letting
 * rest be implicitly nulled (by genlist.sh, for example)
 */
typedef struct _XmuWidgetNode {
    char *label;			/* mixed case name */
    WidgetClass *widget_class_ptr;	/* addr of widget class */
    struct _XmuWidgetNode *superclass;	/* superclass of widget_class */
    struct _XmuWidgetNode *children, *siblings;	/* subclass links */
    char *lowered_label;		/* lowercase version of label */
    char *lowered_classname;		/* lowercase version of class_name */
    Bool have_resources;		/* resources have been fetched */
    XtResourceList resources;		/* extracted resource database */
    struct _XmuWidgetNode **resourcewn;	/* where resources come from */
    Cardinal nresources;		/* number of resources */
    XtResourceList constraints;		/* extracted constraint resources */
    struct _XmuWidgetNode **constraintwn;  /* where constraints come from */
    Cardinal nconstraints;		/* number of constraint resources */
    XtPointer data;			/* extra data */
} XmuWidgetNode;

#define XmuWnClass(wn) ((wn)->widget_class_ptr[0])
#define XmuWnClassname(wn) (XmuWnClass(wn)->core_class.class_name)
#define XmuWnSuperclass(wn) ((XmuWnClass(wn))->core_class.superclass)

					/* external interfaces */
_XFUNCPROTOBEGIN

void XmuWnInitializeNodes
(
 XmuWidgetNode		*nodearray,
 int			nnodes
 );

void XmuWnFetchResources
(
 XmuWidgetNode		*node,
 Widget			toplevel,
 XmuWidgetNode		*topnode
 );

int XmuWnCountOwnedResources
(
 XmuWidgetNode		*node,
 XmuWidgetNode		*ownernode,
 Bool			constraints
 );

XmuWidgetNode *XmuWnNameToNode
(
 XmuWidgetNode		*nodelist,
 int			nnodes,
 _Xconst char		*name
 );

_XFUNCPROTOEND

#endif /* _XmuWidgetNode_h */

