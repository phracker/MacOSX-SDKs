/* $Xorg: PrintSP.h,v 1.1 2003/07/11 19:46:06 gisburn Exp $ */
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

#ifndef _XAW_PRINTSP_H
#define _XAW_PRINTSP_H 1

#include <X11/CoreP.h>
#include <X11/ShellP.h>

_XFUNCPROTOBEGIN

/* New fields for the XawPrintShell widget class record */

typedef struct {
    XtPointer       extension;          /* pointer to extension record      */
} XawPrintShellClassPart;

typedef struct XawPrintShellClassRec {
    CoreClassPart              core_class;
    CompositeClassPart         composite_class;
    ShellClassPart             shell_class;
    WMShellClassPart           wm_shell_class;
    VendorShellClassPart       vendor_shell_class;
    TopLevelShellClassPart     top_level_shell_class;
    ApplicationShellClassPart  application_shell_class;
    XawPrintShellClassPart     print_shell_class;
} XawPrintShellClassRec;

extern XawPrintShellClassRec xawPrintShellClassRec;

/* New fields for the XawPrint shell widget */

typedef struct {
    XtCallbackList               start_job_callback,
                                 end_job_callback,
                                 doc_setup_callback,
                                 page_setup_callback;
    XtEnum                       layoutmode; /* see XawPrintConfigureLayoutMode */
    unsigned short               page_width,
                                 page_height;
    Dimension                    min_x,
                                 min_y,
                                 max_x,
                                 max_y;
    unsigned int                 curr_doc_num_in_job,  /* Current document number in job */
                                 curr_page_num_in_doc, /* Current page number in doc */
                                 curr_page_num_in_job; /* Current page number in job */
    unsigned short               default_pixmap_resolution;
    long                         print_resolution;
    Boolean                      last_page_in_doc;
    Boolean                      last_page_in_job;
} XawPrintShellPart;

typedef struct XawPrintShellRec {
    CorePart              core;
    CompositePart         composite;
    ShellPart             shell;
    WMShellPart           wm;
    VendorShellPart       vendor;
    TopLevelShellPart     topLevel;
    ApplicationShellPart  application;
    XawPrintShellPart     print;
} XawPrintShellRec;
extern WidgetClass xawPrintShellWidgetClass;

#define PS_StartJobCallback(w) \
    (((XawPrintShellWidget) (w))->print.start_job_callback)
#define PS_EndJobCallback(w) \
    (((XawPrintShellWidget) (w))->print.end_job_callback)
#define PS_DocSetupCallback(w) \
    (((XawPrintShellWidget) (w))->print.doc_setup_callback)
#define PS_PageSetupCallback(w) \
    (((XawPrintShellWidget) (w))->print.page_setup_callback)
#define PS_LayoutMode(w) \
    (((XawPrintShellWidget) (w))->print.layoutmode)
#define PS_PageWidth(w) \
    (((XawPrintShellWidget) (w))->print.page_width)
#define PS_PageHeight(w) \
    (((XawPrintShellWidget) (w))->print.page_height)
#define PS_MinX(w) \
    (((XawPrintShellWidget) (w))->print.min_x)
#define PS_MinY(w) \
    (((XawPrintShellWidget) (w))->print.min_y)
#define PS_MaxX(w) \
    (((XawPrintShellWidget) (w))->print.max_x)
#define PS_MaxY(w) \
    (((XawPrintShellWidget) (w))->print.max_y)
#define PS_CurrDocNumInJob(w) \
    (((XawPrintShellWidget) (w))->print.curr_doc_num_in_job)
#define PS_CurrPageNumInDoc(w) \
    (((XawPrintShellWidget) (w))->print.curr_page_num_in_doc)
#define PS_CurrPageNumInJob(w) \
    (((XawPrintShellWidget) (w))->print.curr_page_num_in_job)
#define PS_DefaultPixmapResolution(w) \
    (((XawPrintShellWidget) (w))->print.default_pixmap_resolution)
#define PS_PrintResolution(w) \
    (((XawPrintShellWidget) (w))->print.print_resolution)
#define PS_LastPageInDoc(w) \
    (((XawPrintShellWidget) (w))->print.last_page_in_doc)
#define PS_LastPageInJob(w) \
    (((XawPrintShellWidget) (w))->print.last_page_in_job)

_XFUNCPROTOEND

#endif /* !_XAW_PRINTSP_H */

