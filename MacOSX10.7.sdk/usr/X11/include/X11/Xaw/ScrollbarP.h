/***********************************************************

Copyright 1987, 1988, 1998  The Open Group

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

#ifndef _ScrollbarP_h
#define _ScrollbarP_h

#include <X11/Xaw/Scrollbar.h>
#include <X11/Xaw/SimpleP.h>

typedef struct {
    /* resources */
    Pixel	   foreground;	/* thumb foreground color */
    XtOrientation  orientation;	/* horizontal or vertical */
    XtCallbackList scrollProc;	/* proportional scroll */
    XtCallbackList thumbProc;	/* jump (to position) scroll */
    XtCallbackList jumpProc;	/* same as thumbProc but pass data by ref */
    Pixmap	   thumb;			/* thumb pixmap */
    Cursor	   upCursor;	/* scroll up cursor */
    Cursor	   downCursor;	/* scroll down cursor */
    Cursor	   leftCursor;	/* scroll left cursor */
    Cursor	   rightCursor;	/* scroll right cursor */
    Cursor	   verCursor;	/* scroll vertical cursor */
    Cursor	   horCursor;	/* scroll horizontal cursor */
    float	   top;
    float	   shown;
    Dimension	   length;	/* either height or width */
    Dimension	   thickness;	/* either width or height */
    Dimension	   min_thumb;	/* minium size for the thumb */

     /* private */
    Cursor	   inactiveCursor; /* The normal cursor for scrollbar */
    char	   direction;	/* a scroll has started; which direction */
    GC		   gc;		/* a (shared) gc */
    Position	   topLoc;	/* Pixel that corresponds to top */
    Dimension	   shownLength;	/* Num pixels corresponding to shown */
#ifndef OLDXAW
    XtPointer pad[4];	/* for future use and keep binary compatability */
#endif
} ScrollbarPart;

typedef struct _ScrollbarRec {
    CorePart		core;
    SimplePart		simple;
    ScrollbarPart	scrollbar;
} ScrollbarRec;

typedef struct {
  XtPointer extension;
} ScrollbarClassPart;

typedef struct _ScrollbarClassRec {
    CoreClassPart		core_class;
    SimpleClassPart		simple_class;
    ScrollbarClassPart		scrollbar_class;
} ScrollbarClassRec;

extern ScrollbarClassRec scrollbarClassRec;

#endif /* _ScrollbarP_h */
