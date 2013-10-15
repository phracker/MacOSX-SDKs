/*
 * $Xorg: Toggle.h,v 1.4 2001/02/09 02:03:47 xorgcvs Exp $
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
/* $XFree86: xc/lib/Xaw/Toggle.h,v 1.5 2001/01/17 19:42:35 dawes Exp $ */

/*
 * ToggleP.h - Private definitions for Toggle widget
 *
 * Author: Chris D. Peterson
 *         MIT X Consortium
 *         kit@expo.lcs.mit.edu
 *  
 * Date:   January 12, 1989
 */

#ifndef _XawToggle_h
#define _XawToggle_h

#include <X11/Xaw/Command.h>

/* Resources:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 radioGroup          RadioGroup         Widget          NULL              +
 radioData           RadioData          Pointer         (XPointer) Widget  ++
 state               State              Boolean         Off

 background	     Background		Pixel		XtDefaultBackground
 bitmap		     Pixmap		Pixmap		None
 border		     BorderColor	Pixel		XtDefaultForeground
 borderWidth	     BorderWidth	Dimension	1
 callback	     Callback		Pointer		NULL
 cursor		     Cursor		Cursor		None
 destroyCallback     Callback		Pointer		NULL
 displayList	     DisplayList	XawDisplayList*	NULL
 font		     Font		XFontStructx*	XtDefaultFont
 foreground	     Foreground		Pixel		XtDefaultForeground
 height		     Height		Dimension	text height
 highlightThickness  Thickness		Dimension	2
 insensitiveBorder   Insensitive	Pixmap		Gray
 internalHeight	     Height		Dimension	2
 internalWidth	     Width		Dimension	4
 justify	     Justify		XtJustify	XtJustifyCenter
 label		     Label		String		NULL
 mappedWhenManaged   MappedWhenManaged	Boolean		True
 resize		     Resize		Boolean		True
 sensitive	     Sensitive		Boolean		True
 width		     Width		Dimension	text width
 x		     Position		Position	0
 y		     Position		Position	0

+ To use the toggle as a radio toggle button, set this resource to point to
  any other widget in the radio group.

++ This is the data returned from a call to XtToggleGetCurrent, by default
   this is set to the name of toggle widget.

*/

/*
 * These should be in StringDefs.h but aren't so we will define
 * them here if they are needed
 */
#define XtCWidget "Widget"
#define XtCState "State"
#define XtCRadioGroup "RadioGroup"
#define XtCRadioData "RadioData"

#ifndef _XtStringDefs_h_
#define XtRWidget "Widget"
#endif

#define XtNstate "state"
#define XtNradioGroup "radioGroup"
#define XtNradioData "radioData"

extern WidgetClass               toggleWidgetClass;

typedef struct _ToggleClassRec   *ToggleWidgetClass;
typedef struct _ToggleRec        *ToggleWidget;

/*
 * Public Functions
 */

_XFUNCPROTOBEGIN
   
/*
 * Function:
 *	XawToggleChangeRadioGroup
 *
 * Parameters:
 *	w	    - toggle widget to change lists
 *	radio_group - any widget in the new list
 *
 * Description:
 *	Allows a toggle widget to change radio lists.
 */
void XawToggleChangeRadioGroup
(
 Widget		w,
 Widget		radio_group
 );

/*
 * Function:
 *	XawToggleGetCurrent
 *
 * Parameters:
 *	radio_group - any toggle widget in the toggle list
 *
 * Description:
 *	  Returns the RadioData associated with the toggle
 *                   widget that is currently active in a toggle list.
 * Returns:
 *	The XtNradioData associated with the toggle widget
 */

XtPointer XawToggleGetCurrent
(
 Widget		radio_group
 );

/*
 * Function:
 *	XawToggleSetCurrent
 *
 * Parameters:
 *	radio_group - any toggle widget in the toggle list
 *	radio_data - radio data of the toggle widget to set
 *
 * Description:
 *	Sets the Toggle widget associated with the radio_data specified.
 */
void XawToggleSetCurrent
(
 Widget		radio_group,
 XtPointer	radio_data
 );

/*
 * Function:
 *	XawToggleUnsetCurrent
 *
 * Parameters:
 *	radio_group - any toggle widget in the toggle list
 *
 * Description:
 *	Unsets all Toggles in the radio_group specified.
 */
void XawToggleUnsetCurrent
(
 Widget		radio_group
 );

_XFUNCPROTOEND

#endif /* _XawToggle_h */
