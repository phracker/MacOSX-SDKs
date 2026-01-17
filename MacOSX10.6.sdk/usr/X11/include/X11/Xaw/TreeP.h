/*
 * $Xorg: TreeP.h,v 1.4 2001/02/09 02:03:47 xorgcvs Exp $
 *

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

 * Copyright 1989 Prentice Hall
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation.
 * 
 * Prentice Hall and the authors disclaim all warranties with regard
 * to this software, including all implied warranties of merchantability and
 * fitness.  In no event shall Prentice Hall or the authors be liable
 * for any special, indirect or cosequential damages or any damages whatsoever
 * resulting from loss of use, data or profits, whether in an action of
 * contract, negligence or other tortious action, arising out of or in
 * connection with the use or performance of this software.
 * 
 * Authors:  Jim Fulton, MIT X Consortium,
 *           based on a version by Douglas Young, Prentice Hall
 * 
 * This widget is based on the Tree widget described on pages 397-419 of
 * Douglas Young's book "The X Window System, Programming and Applications 
 * with Xt OSF/Motif Edition."  The layout code has been rewritten to use
 * additional blank space to make the structure of the graph easier to see
 * as well as to support vertical trees.
 */
/* $XFree86: xc/lib/Xaw/TreeP.h,v 1.6 2001/01/17 19:42:35 dawes Exp $ */


#ifndef _XawTreeP_h
#define _XawTreeP_h

#include <X11/Xaw/Tree.h>

typedef struct _TreeClassPart {
    XtPointer extension;
} TreeClassPart;

typedef struct _TreeClassRec {
    CoreClassPart core_class;
    CompositeClassPart composite_class;
    ConstraintClassPart constraint_class;
    TreeClassPart tree_class;
} TreeClassRec;

extern TreeClassRec treeClassRec;

typedef struct {
    /* fields available through resources */
    Dimension hpad;			/* hSpace/HSpace */
    Dimension vpad;			/* vSpace/VSpace */
    Dimension line_width;		/* lineWidth/LineWidth */
    Pixel foreground;			/* foreground/Foreground */
    XtGravity gravity;			/* gravity/Gravity */
    Boolean auto_reconfigure;		/* autoReconfigure/AutoReconfigure */
    /* private fields */
    GC gc;				/* used to draw lines */
    Widget tree_root;			/* hidden root off all children */
    Dimension *largest;			/* list of largest per depth */
    int n_largest;			/* number of elements in largest */
    Dimension maxwidth, maxheight;	/* for shrink wrapping */
#ifndef OLDXAW
    XawDisplayList *display_list;
    XtPointer pad[4];	/* for future use and keep binary compatability */
#endif
} TreePart;


typedef struct _TreeRec {
    CorePart core;
    CompositePart composite;
    ConstraintPart constraint;
    TreePart tree;
}  TreeRec;


/*
 * structure attached to all children
 */
typedef struct _TreeConstraintsPart {
    /* resources */
    Widget parent;			/* treeParent/TreeParent */
    GC gc;				/* treeGC/TreeGC */
    /* private data */
    Widget *children;
    int n_children;
    int max_children;
    Dimension bbsubwidth, bbsubheight;	/* bounding box of sub tree */
    Dimension bbwidth, bbheight;	/* bounding box including node */
    Position x, y;
#ifndef OLDXAW
    XtPointer pad[2];	/* leave some space for future optimizations, and
			 * keep binary compatability
			 */
#endif
} TreeConstraintsPart;

typedef struct _TreeConstraintsRec {
   TreeConstraintsPart tree;
} TreeConstraintsRec, *TreeConstraints;


/*
 * useful macros
 */

#define TREE_CONSTRAINT(w) \
                   ((TreeConstraints)((w)->core.constraints))

#define TREE_INITIAL_DEPTH 10		/* for allocating largest array */
#define TREE_HORIZONTAL_DEFAULT_SPACING 20
#define TREE_VERTICAL_DEFAULT_SPACING 6

#endif /* _XawTreeP_h */



