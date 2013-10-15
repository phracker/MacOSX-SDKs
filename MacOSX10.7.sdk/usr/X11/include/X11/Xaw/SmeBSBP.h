/*
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
 *
 * Author:  Chris D. Peterson, MIT X Consortium
 */

#ifndef _XawSmeBSBP_h
#define _XawSmeBSBP_h

/*
 * Sme Object Private Data
 */
#include <X11/Xaw/SmeP.h>
#include <X11/Xaw/SmeBSB.h>

typedef struct _SmeBSBClassPart {
    XtPointer extension;
} SmeBSBClassPart;

/* Full class record declaration */
typedef struct _SmeBSBClassRec {
    RectObjClassPart	rect_class;
    SmeClassPart	sme_class;
    SmeBSBClassPart	sme_bsb_class;
} SmeBSBClassRec;

extern SmeBSBClassRec smeBSBClassRec;

/* New fields for the Sme Object record */
typedef struct {
    /* resources */
    String label;			/* The entry label */
    int vert_space;			/* extra vert space to leave, as a
					   percentage of the font height of
					   the label */
    Pixmap left_bitmap, right_bitmap;	/* bitmaps to show */
    Dimension left_margin, right_margin;/* left and right margins */
    Pixel foreground;			/* foreground color */
    XFontStruct *font;			/* The font to show label in */
    XFontSet fontset;			/* or fontset */
    XtJustify justify;			/* Justification for the label. */

    /* private */
    Boolean set_values_area_cleared;	/* do we need to unhighlight? */
    GC norm_gc;				/* noral color gc */
    GC rev_gc;				/* reverse color gc */
    GC norm_gray_gc;			/* Normal color (grayed out) gc */
    GC invert_gc;			/* gc for flipping colors */
    Dimension left_bitmap_width;	/* size of each bitmap */
    Dimension left_bitmap_height;
    Dimension right_bitmap_width;
    Dimension right_bitmap_height;

#ifndef OLDXAW
    /* new resources */
    String menu_name;			/* name of nested sub menu or NULL */
    XtPointer pad[4];	/* for future use and keep binary compatability */
#endif
} SmeBSBPart;

/*
 * Full instance record declaration
 */
typedef struct _SmeBSBRec {
    ObjectPart	object;
    RectObjPart	rectangle;
    SmePart	sme;
    SmeBSBPart	sme_bsb;
} SmeBSBRec;

#endif /* _XawSmeBSBP_h */
