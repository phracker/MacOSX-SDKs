/*
 * $Xorg: Panner.h,v 1.5 2001/02/09 02:03:45 xorgcvs Exp $
 *
Copyright 1989, 1998  The Open Group

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
/* $XFree86: xc/lib/Xaw/Panner.h,v 1.5 2001/01/17 19:42:28 dawes Exp $ */

#ifndef _XawPanner_h
#define _XawPanner_h

#include <X11/Intrinsic.h>
#include <X11/Xaw/Reports.h>

/*****************************************************************************
 * 
 * Panner Widget (subclass of Simple)
 * 
 * This widget is used to represent navigation in a 2d coordinate system
 * 
 * Resources:
 * 
 *  Name		Class		Type		Default
 *  ----		-----		----		-------
 * 
 *  allowOff		AllowOff	Boolean		FALSE
 *  background		Background	Pixel		XtDefaultBackground
 *  backgroundStipple	BackgroundStipple	String	NULL
 *  canvasWidth		CanvasWidth	Dimension	0
 *  canvasHeight	CanvasHeight	Dimension	0
 *  defaultScale	DefaultScale	Dimension	8 percent
 *  foreground		Foreground	Pixel		XtDefaultBackground
 *  internalSpace	InternalSpace	Dimension	4
 *  lineWidth		LineWidth	Dimension	0
 *  reportCallback	ReportCallback	XtCallbackList	NULL
 *  resize		Resize		Boolean		TRUE
 *  rubberBand		RubberBand	Boolean		FALSE
 *  shadowColor		ShadowColor	Pixel		XtDefaultForeground
 *  shadowThickness	ShadowThickness	Dimension	2
 *  sliderX		SliderX		Position	0
 *  sliderY		SliderY		Position	0
 *  sliderWidth		SliderWidth	Dimension	0
 *  sliderHeight	SliderHeight	Dimension	0
 * 
 *****************************************************************************/

#ifndef _XtStringDefs_h_
#define XtNresize "resize"
#define XtCResize "Resize"
#endif

#define XtNallowOff "allowOff"
#define XtCAllowOff "AllowOff"
#define XtNbackgroundStipple "backgroundStipple"
#define XtCBackgroundStipple "BackgroundStipple"
#define XtNdefaultScale "defaultScale"
#define XtCDefaultScale "DefaultScale"
#define XtNcanvasWidth "canvasWidth"
#define XtCCanvasWidth "CanvasWidth"
#define XtNcanvasHeight "canvasHeight"
#define XtCCanvasHeight "CanvasHeight"
#define XtNinternalSpace "internalSpace"
#define XtCInternalSpace "InternalSpace"
#define XtNlineWidth "lineWidth"
#define XtCLineWidth "LineWidth"
#define XtNrubberBand "rubberBand"
#define XtCRubberBand "RubberBand"
#define XtNshadowThickness "shadowThickness"
#define XtCShadowThickness "ShadowThickness"
#define XtNshadowColor "shadowColor"
#define XtCShadowColor "ShadowColor"
#define XtNsliderX "sliderX"
#define XtCSliderX "SliderX"
#define XtNsliderY "sliderY"
#define XtCSliderY "SliderY"
#define XtNsliderWidth "sliderWidth"
#define XtCSliderWidth "SliderWidth"
#define XtNsliderHeight "sliderHeight"
#define XtCSliderHeight "SliderHeight"

extern WidgetClass pannerWidgetClass;

typedef struct _PannerClassRec *PannerWidgetClass;
typedef struct _PannerRec      *PannerWidget;

#endif /* _XawPanner_h */
