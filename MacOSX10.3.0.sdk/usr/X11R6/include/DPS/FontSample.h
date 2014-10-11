/*
 * FontSample.h
 *
 * (c) Copyright 1991-1994 Adobe Systems Incorporated.
 * All rights reserved.
 * 
 * Permission to use, copy, modify, distribute, and sublicense this software
 * and its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notices appear in all copies and that
 * both those copyright notices and this permission notice appear in
 * supporting documentation and that the name of Adobe Systems Incorporated
 * not be used in advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.  No trademark license
 * to use the Adobe trademarks is hereby granted.  If the Adobe trademark
 * "Display PostScript"(tm) is used to describe this software, its
 * functionality or for any other purpose, such use shall be limited to a
 * statement that this software works in conjunction with the Display
 * PostScript system.  Proper trademark attribution to reflect Adobe's
 * ownership of the trademark shall be given whenever any such reference to
 * the Display PostScript system is made.
 * 
 * ADOBE MAKES NO REPRESENTATIONS ABOUT THE SUITABILITY OF THE SOFTWARE FOR
 * ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 * ADOBE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON- INFRINGEMENT OF THIRD PARTY RIGHTS.  IN NO EVENT SHALL ADOBE BE LIABLE
 * TO YOU OR ANY OTHER PARTY FOR ANY SPECIAL, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE, STRICT LIABILITY OR ANY OTHER ACTION ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.  ADOBE WILL NOT
 * PROVIDE ANY TRAINING OR OTHER SUPPORT FOR THE SOFTWARE.
 * 
 * Adobe, PostScript, and Display PostScript are trademarks of Adobe Systems
 * Incorporated which may be registered in certain jurisdictions
 * 
 * Author:  Adobe Systems Incorporated
 */
/* $XFree86: xc/include/DPS/FontSample.h,v 1.2 2000/06/07 22:02:55 tsi Exp $ */

#ifndef _FontSampler_h
#define _FontSampler_h

/* New resouce names and classes */

#define XtNdismissCallback "dismissCallback"
#define XtNsizes "sizes"
#define XtCSizes "Sizes"
#define XtNsizeCount "sizeCount"
#define XtCSizeCount "SizeCount"
#define XtNfontSelectionBox "fontSelectionBox"
#define XtCFontSelectionBox "FontSelectionBox"
#define XtNminimumWidth "minimumWidth"
#define XtCMinimumWidth "MinimumWidth"
#define XtNminimumHeight "minimumHeight"
#define XtCMinimumHeight "MinimumHeight"
#define XtNnoRoomMessage "noRoomMessage"
#define XtNnoFontMessage "noFontMessage"
#define XtNnoSelectedFontMessage "noSelectedFontMessage"
#define XtNnoSelectedFamilyMessage "noSelectedFamilyMessage"
#define XtNnoFamilyFontMessage "noFamilyFontMessage"
#define XtNnoMatchMessage "noMatchMessage"
#define XtCMessage "Message"

/* Read-only resources for all the subwidgets */

#define XtNpanelChild "panelChild"
#define XtNareaChild "areaChild"
#define XtNtextChild "textChild"
#define XtNfontLabelChild "fontLabelChild"
#define XtNscrolledWindowChild "scrolledWindowChild"
#define XtNdisplayButtonChild "displayButtonChild"
#define XtNdismissButtonChild "dismissButtonChild"
#define XtNstopButtonChild "stopButtonChild"
#define XtNclearButtonChild "clearButtonChild"
#define XtNradioFrameChild "radioFrameChild"
#define XtNradioBoxChild "radioBoxChild"
#define XtNallToggleChild "allToggleChild"
#define XtNselectedToggleChild "selectedToggleChild"
#define XtNselectedFamilyToggleChild "selectedFamilyToggleChild"
#define XtNfilterToggleChild "filterToggleChild"
#define XtNfilterTextChild "filterTextChild"
#define XtNfilterBoxChild "filterBoxChild"
#define XtNfilterFrameChild "filterFrameChild"
#define XtNsizeOptionMenuChild "sizeOptionMenuChild"
#define XtNsizeTextFieldChild "sizeTextFieldChild"
#define XtNsizeLabelChild "sizeLabelChild"

/* Class record constants */

extern WidgetClass fontSamplerWidgetClass;

typedef struct _FontSamplerRec *FontSamplerWidget;

extern void FSBCancelSampler(Widget w);

#endif /* _FontSampler_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
