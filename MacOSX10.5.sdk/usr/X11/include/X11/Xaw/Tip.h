/*
 * Copyright (c) 1999 by The XFree86 Project, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE XFREE86 PROJECT BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of the XFree86 Project shall
 * not be used in advertising or otherwise to promote the sale, use or other
 * dealings in this Software without prior written authorization from the
 * XFree86 Project.
 *
 * Author: Paulo César Pereira de Andrade
 */

/* $XFree86$ */

#ifndef _XawTip_h
#define _XawTip_h

/*
 * Tip Widget
 */

#include <X11/Xaw/Simple.h>

/* Resources:

  Name		    Class		RepType		Default Value
  ----		    -----		-------		-------------
  background	    Background		Pixel		XtDefaultBackground
  backgroundPixmap  BackgroundPixmap	Pixmap		XtUnspecifiedPixmap
  border	    BorderColor		Pixel		XtDefaultForeground
  borderWidth	    BorderWidth		Dimension	1
  bottomMargin	    VerticalMargins	Dimension	2
  destroyCallback   Callback		XtCallbackList	NULL
  displayList	    DisplayList		XawDisplayList*	NULL
  font		    Font		XFontStruct*	XtDefaultFont
  foreground	    Foreground		Pixel		XtDefaultForeground
  height	    Height		Dimension	text height
  leftMargin	    HorizontalMargins	Dimension	6
  rightMargin	    HorizontalMargins	Dimension	6
  timeout	    Timeout		Int		500
  topMargin	    VerticalMargins	Dimension	2
  width		    Width		Dimension	text width
  x		    Position		Position	0
  y		    Position		Position	0

*/

typedef struct _TipClassRec *TipWidgetClass;
typedef struct _TipRec *TipWidget;

extern WidgetClass tipWidgetClass;

#define XtNbottomMargin		"bottomMargin"
#define XawNdisplayList		"displayList"
#define XtNencoding		"encoding"
#define XtNleftMargin		"leftMargin"
#define XtNrightMargin		"rightMargin"
#define XtNtimeout		"timeout"
#define XtNtopMargin		"topMargin"
#define XtNtip			"tip"

#define XawCDisplayList		"DisplayList"
#define XtCHorizontalMargins	"HorizontalMargins"
#define XtCTimeout		"Timeout"
#define XtCVerticalMargins	"VerticalMargins"
#define XtCTip			"Tip"

#define XawRDisplayList		"XawDisplayList"

/*
 * Public Functions
 */
/*
 * Function:
 *	XawTipEnable
 *
 * Parameters:
 *	w - widget
 *
 * Description:
 *	Enables the tip event handler for this widget.
 */
void XawTipEnable
(
 Widget		w
 );

/*
 * Function:
 *	XawTipEnable
 *
 * Parameters:
 *	w - widget
 *
 * Description:
 *	Disables the tip event handler for this widget.
 */
void XawTipDisable
(
 Widget		w
 );

#endif /* _XawTip_h */
