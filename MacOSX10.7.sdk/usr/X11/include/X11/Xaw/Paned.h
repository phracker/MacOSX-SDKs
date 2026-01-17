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

/*
 * Paned.h - Paned Composite Widget's public header file.
 *
 * Updated and significantly modifided from the Athena VPaned Widget.
 *
 * Date:    March 1, 1989
 *
 * By:      Chris D. Peterson
 *          MIT X Consortium
 *          kit@expo.lcs.mit.edu
 */

#ifndef _XawPaned_h
#define _XawPaned_h

#include <X11/Intrinsic.h>
#include <X11/Xmu/Converters.h>

/* RESOURCES:

 Name		         Class		   RepType	    Default Value
 ----		         -----		   -------	    -------------
 background	         Background	   Pixel	    XtDefaultBackground
 betweenCursor	         Cursor	           Cursor	    **
 border		         BorderColor       Pixel	    XtDefaultForeground
 borderWidth	         BorderWidth       Dimension	    1
 cursor		         Cursor	           Cursor	    None
 destroyCallback         Callback	   Pointer	    NULL
 height		         Height	           Dimension	    0
 gripIndent	         GripIndent	   Position	    16
 gripCursor	         Cursor	           Cursor	    **
 horizontalGripCursol    Cursor	           Cursor	    sb_h_double_arrow
 horizontalBetweencursor Cursor	           Cursor	    sb_up_arrow
 internalBorderColor     BorderColor	   Pixel	    XtDefaultForeground
 internalBorderWidth     BorderWidth	   Position	    1
 leftCursor	         Cursor	           Cursor	    sb_left_arrow
 lowerCursor	         Cursor	           Cursor	    sb_down_arrow
 mappedWhenManaged       MappedWhenManaged Boolean	    True
 orientation             Orientation       XtOrientation    XtorientVertical
 refigureMode	         Boolean	   Boolean	    On
 rightCursor	         Cursor	           Cursor           sb_right_arrow
 sensitive	         Sensitive	   Boolean	    True
 upperCursor	         Cursor	           Cursor	    sb_up_arrow
 verticalBetweenCursor   Cursor	           Cursor           sb_left_arrow
 verticalGripCursor      Cursor	           Cursor           sb_v_double_arrow
 width		         Width	           Dimension	    0
 x		         Position	   Position	    0
 y		         Position	   Position    	    0

** These resources now are set to the vertical or horizontal cursor
   depending upon orientation, by default.  If a value is specified here
   then that cursor will be used reguardless of orientation.


CONSTRAINT RESOURCES:

 Name		      Class		RepType		Default Value
 ----		      -----		-------		-------------
 allowResize	      Boolean	        Boolean         False
 max		      Max	        Dimension	unlimited
 min		      Min		Dimension	Grip Size
 preferredPaneSize    PreferredPaneSize Dimension	PANED_ASK_CHILD
 resizeToPreferred    Boolean		Boolean	 	False
 showGrip	      ShowGrip		Boolean		True
 skipAdjust	      Boolean	        Boolean         False

*/

#define PANED_ASK_CHILD 0
#define PANED_GRIP_SIZE 0

#define XtNallowResize "allowResize"
#define XtNbetweenCursor "betweenCursor"
#define XtNverticalBetweenCursor "verticalBetweenCursor"
#define XtNhorizontalBetweenCursor "horizontalBetweenCursor"
#define XtNgripCursor "gripCursor"
#define XtNgripIndent "gripIndent"
#define XtNhorizontalGripCursor "horizontalGripCursor"
#define XtNinternalBorderColor "internalBorderColor"
#define XtNinternalBorderWidth "internalBorderWidth"
#define XtNleftCursor "leftCursor"
#define XtNlowerCursor "lowerCursor"
#define XtNrefigureMode "refigureMode"
#define XtNposition "position"
#define XtNmin "min"
#define XtNmax "max"
#define XtNpreferredPaneSize "preferredPaneSize"
#define XtNresizeToPreferred "resizeToPreferred"
#define XtNrightCursor "rightCursor"
#define XtNshowGrip "showGrip"
#define XtNskipAdjust "skipAdjust"
#define XtNupperCursor "upperCursor"
#define XtNverticalGripCursor "verticalGripCursor"

#define XtCGripIndent "GripIndent"
#define XtCMin "Min"
#define XtCMax "Max"
#define XtCPreferredPaneSize "PreferredPaneSize"
#define XtCShowGrip "ShowGrip"

/* Class record constant */
extern WidgetClass panedWidgetClass;

typedef struct _PanedClassRec	*PanedWidgetClass;
typedef struct _PanedRec	*PanedWidget;

/*
 *  Public Procedures 
 */

_XFUNCPROTOBEGIN

/*
 * Function:
 *	XawPanedSetMinMax
 *
 * Parameters:
 *	widget - widget that is a child of the Paned widget
 *	min    - new min and max size for the pane
 *	max    - ""
 *
 * Description:
 *	Sets the min and max size for a pane.
 */
void XawPanedSetMinMax
(
 Widget			w,
 int			min,
 int			max
 );

/*
 * Function:
 *	XawPanedGetMinMax
 *
 * Parameters:
 *	widget - widget that is a child of the Paned widget
 *	min    - return the current min and max size for the pane
 *	max    - ""
 *
 * Description:
 *	Gets the min and max size for a pane.
 */
void XawPanedGetMinMax
(
 Widget			w,
 int			*min_return,
 int			*max_return
 );

/*
 * Function:
 *	XawPanedSetRefigureMode
 *
 * Parameters:
 *	w    - paned widget
 *	mode - if False then inhibit refigure
 *
 * Description:
 *	  Allows a flag to be set the will inhibit  the paned widgets
 *	relayout routine.
 */
void XawPanedSetRefigureMode
(
 Widget			w,
#if NeedWidePrototypes
 int			mode
#else
 Boolean		mode
#endif
 );

/*
 * Function:
 *	XawPanedGetNumSub
 *
 * Parameters:
 *	w - paned widget
 *
 * Returns:
 *	Number of panes in the paned widget.
 */
int XawPanedGetNumSub
(
 Widget			w
 );

/*
 * Function:
 *	XawPanedAllowResize
 *
 * Parameters:
 *	widget - child of the paned widget
 *
 * Description:
 *	  Allows a flag to be set that determines if the paned widget will
 *	allow geometry requests from this child
 */
void XawPanedAllowResize
(
 Widget			w,
#if NeedWidePrototypes
 int			allow_resize
#else
 Boolean		allow_resize
#endif
 );

_XFUNCPROTOEND

#endif /* _XawPaned_h */
