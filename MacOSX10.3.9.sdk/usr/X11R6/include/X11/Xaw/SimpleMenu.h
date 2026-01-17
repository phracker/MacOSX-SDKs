/*
 * $Xorg: SimpleMenu.h,v 1.4 2001/02/09 02:03:45 xorgcvs Exp $
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
/* $XFree86: xc/lib/Xaw/SimpleMenu.h,v 1.8 2001/12/14 19:54:43 dawes Exp $ */

/*
 * SimpleMenu.h - Public Header file for SimpleMenu widget.
 *
 * This is the public header file for the Athena SimpleMenu widget.
 * It is intended to provide one pane pulldown and popup menus within
 * the framework of the X Toolkit.  As the name implies it is a first and
 * by no means complete implementation of menu code. It does not attempt to
 * fill the needs of all applications, but does allow a resource oriented
 * interface to menus.
 *
 * Date:    April 3, 1989
 *
 * By:      Chris D. Peterson
 *          MIT X Consortium 
 *          kit@expo.lcs.mit.edu
 */

#ifndef _SimpleMenu_h
#define _SimpleMenu_h

#include <X11/Shell.h>
#include <X11/Xmu/Converters.h>

/*
 * SimpleMenu widget
 */

/* Resources:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 background	     Background		Pixel		XtDefaultBackground
 backgroundPixmap    BackgroundPixmap	Pixmap          None
 borderColor	     BorderColor	Pixel		XtDefaultForeground
 borderPixmap	     BorderPixmap	Pixmap		None
 borderWidth	     BorderWidth	Dimension	1
 bottomMargin        VerticalMargins    Dimension       VerticalSpace
 columnWidth         ColumnWidth        Dimension       Width of widest text
 cursor              Cursor             Cursor          None
 destroyCallback     Callback		Pointer		NULL
 displayList	     DisplayList	XawDisplayList*	NULL
 height		     Height		Dimension	0
 label               Label              String          NULL (No label)
 labelClass          LabelClass         Pointer         smeBSBObjectClass
 leftMargin	     HorizontalMargins	Dimension	0
 mappedWhenManaged   MappedWhenManaged	Boolean		True
 rightMargin	     HorizontalMargins	Dimension	0
 rowHeight           RowHeight          Dimension       Height of Font
 sensitive	     Sensitive		Boolean		True
 topMargin           VerticalMargins    Dimension       VerticalSpace
 width		     Width		Dimension	0
 x		     Position		Position	0
 y		     Position		Position	0

*/

typedef struct _SimpleMenuClassRec*	SimpleMenuWidgetClass;
typedef struct _SimpleMenuRec*		SimpleMenuWidget;

extern WidgetClass simpleMenuWidgetClass;

#define XtNcursor "cursor"
#define XtNbottomMargin "bottomMargin"
#define XtNcolumnWidth "columnWidth"
#define XtNlabelClass "labelClass"
#define XtNmenuOnScreen "menuOnScreen"
#define XtNpopupOnEntry "popupOnEntry"
#define XtNrowHeight "rowHeight"
#define XtNtopMargin "topMargin"
#define XtNleftMargin "leftMargin"
#define XtNrightMargin "rightMargin"

#define XtCColumnWidth "ColumnWidth"
#define XtCLabelClass "LabelClass"
#define XtCMenuOnScreen "MenuOnScreen"
#define XtCPopupOnEntry "PopupOnEntry"
#define XtCRowHeight "RowHeight"

#define XtCVerticalMargins "VerticalMargins"

#ifndef OLDXAW
#define XtCHorizontalMargins "HorizontalMargins"
#define XawNdisplayList "displayList"
#define XawCDisplayList "DisplayList"
#define XawRDisplayList "XawDisplayList"
#endif

/*
 * Public Functions
 */

_XFUNCPROTOBEGIN

/*
 * Function:
 *	XawSimpleMenuAddGlobalActions
 *
 * Parameters:
 *	app_con - appcontext
 *
 * Description:
 *	Adds the global actions to the simple menu widget.
 */
void XawSimpleMenuAddGlobalActions
(
 XtAppContext		app_con
 );

/*
 * Function:
 *	XawSimpleMenuGetActiveEntry
 *
 * Parameters:
 *	w - smw widget
 *
 * Description:
 *	Gets the currently active (set) entry.
 *
 * Returns:
 *	The currently set entry or NULL if none is set
 */
Widget XawSimpleMenuGetActiveEntry
(
 Widget			w
 );

/*
 * Function:
 *	XawSimpleMenuClearActiveEntry
 *
 * Parameters:
 *	w - smw widget
 *
 * Description:
 *	Unsets the currently active (set) entry.
 */
void XawSimpleMenuClearActiveEntry
(
 Widget			w
);

_XFUNCPROTOEND

#endif /* _SimpleMenu_h */
