/* $Xorg: Print.h,v 1.1 2003/07/11 19:46:06 gisburn Exp $ */
/******************************************************************************
 ******************************************************************************
 **
 ** (c) Copyright 2003 Danny Backx <danny.backx@skynet.be>
 ** (c) Copyright 2003-2004 Roland Mainz <roland.mainz@nrubsig.org>
 ** 
 ** Permission is hereby granted, free of charge, to any person obtaining a copy
 ** of this software and associated documentation files (the "Software"), to deal
 ** in the Software without restriction, including without limitation the rights
 ** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 ** copies of the Software, and to permit persons to whom the Software is
 ** furnished to do so, subject to the following conditions:
 **
 ** The above copyright notice and this permission notice shall be included in
 ** all copies or substantial portions of the Software.
 **
 ** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 ** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 ** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 ** COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 ** IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 ** CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **
 ** Except as contained in this notice, the names of the copyright holders shall
 ** not be used in advertising or otherwise to promote the sale, use or other
 ** dealings in this Software without prior written authorization from said
 ** copyright holders.
 **
 ******************************************************************************
 *****************************************************************************/
 

#ifndef _XAW_PRINT_H
#define _XAW_PRINT_H 1

#include <X11/extensions/Print.h>

/* Resources:
   NOT WRITTEN YET
*/

/* XawPrintConfigureLayoutMode - define how the shell resizes/moves itself
 * to match the paper size
 * Values:
 * - XawPrintLAYOUTMODE_NONE
 *   do nothing
 * - XawPrintLAYOUTMODE_PAGESIZE
 *   set width/height to page size
 *   (this is the default (mainly for compatibilty to XmPrintShell))
 * - XawPrintLAYOUTMODE_DRAWABLEAREA
 *   set x/y/width/height to drawable area of pag
 */
typedef
enum
{
  XawPrintLAYOUTMODE_NONE,
  XawPrintLAYOUTMODE_PAGESIZE,
  XawPrintLAYOUTMODE_DRAWABLEAREA
} XawPrintConfigureLayoutMode;


#define XawNstartJobCallback             "startJobCallback"
#define XawNendJobCallback               "endJobCallback"
#define XawNdocSetupCallback             "docSetupCallback"
#define XawNpageSetupCallback            "pageSetupCallback"
#define XawNlayoutMode                   "layoutMode"
#define XawCLayoutMode                   "LayoutMode"
#define XawNminX                         "minX"
#define XawCMinX                         "MinX"
#define XawNminY                         "minY"
#define XawCMinY                         "MinY"
#define XawNmaxX                         "maxX"
#define XawCMaxX                         "MaxX"
#define XawNmaxY                         "maxY"
#define XawCMaxY                         "MaxY"
#define XawNcurrDocNumInJob              "currDocNumInJob"
#define XawCCurrDocNumInJob              "CurrDocNumInJob"
#define XawNcurrPageNumInDoc             "currPageNumInDoc"
#define XawCCurrPageNumInDoc             "CurrPageNumInDoc"
#define XawNcurrPageNumInJob             "currPageNumInJob"
#define XawCCurrPageNumInJob             "CurrPageNumInJob"
#define XawNdefaultPixmapResolution      "defaultPixmapResolution"
#define XawCDefaultPixmapResolution      "DefaultPixmapResolution"

#define XawCR_START_JOB         70
#define XawCR_END_JOB           71
#define XawCR_DOC_SETUP         72
#define XawCR_PAGE_SETUP        73

typedef struct
{
    int            reason;
    XEvent        *event;
    XPContext      context;
    Boolean        last_page_in_doc;
    Boolean        last_page_in_job;
    XtPointer      detail;
} XawPrintShellCallbackStruct;

extern WidgetClass xawPrintShellWidgetClass;
typedef struct XawPrintShellRec *XawPrintShellWidget;

/************************************************************
 *
 * Public Functions.
 *
 ************************************************************/

_XFUNCPROTOBEGIN

/* Returns whether the widget passed in is a print shell or "print shell"-like
 * widget (e.g. print preview).
 * Note that this will return |True| for more classes than |XawPrintShell| in
 * the future (like for |XmPrintShell| etc.)
 */
extern Boolean XawIsPrintShell(
#if NeedFunctionPrototypes
    Widget w
#endif
);

extern void   XawPrintRedisplayWidget(
#if NeedFunctionPrototypes
    Widget w /* Widget */
#endif
);
          
_XFUNCPROTOEND

#endif /* !_XAW_PRINT_H */

