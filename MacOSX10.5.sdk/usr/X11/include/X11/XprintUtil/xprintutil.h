/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
#ifndef XPRINTUTIL_H
#define XPRINTUTIL_H 1
/******************************************************************************
 ******************************************************************************
 **
 ** (c) Copyright 2001-2004 Roland Mainz <roland.mainz@nrubsig.org>
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

/* Force ANSI C prototypes from X11 headers */
#ifndef FUNCPROTO 
#define FUNCPROTO 15
#endif /* !FUNCPROTO */

#include <X11/Xlibint.h>
#include <X11/extensions/Print.h>
#include <X11/Intrinsic.h>

/* I don't know how to make this "better" yet... ;-( */
#ifdef USE_MOZILLA_TYPES
#include <prtypes.h>
#include <prmem.h>
#include <prthread.h>
#define XPU_USE_NSPR 1
/*
 * Disabled for now - Threaded codepath does not work properly always.
 * See bug 134570 ("Print-to-file not working with threaded XprintUtil")
 * #define XPU_USE_THREADS 1
 */
#endif /* USE_MOZILLA_TYPES */

#ifdef DEBUG
/* trace function calls */
#define XPU_TRACE(EX)  (puts(#EX),EX)
/* trace function calls in child */
#define XPU_TRACE_CHILD(EX)  (puts("child: " #EX),EX)
/* execute function EX only in debug mode */
#define XPU_DEBUG_ONLY(EX)  (EX)
#else
#define XPU_TRACE(EX) (EX)
#define XPU_TRACE_CHILD(EX) (EX)
#define XPU_DEBUG_ONLY(EX)
#endif /* DEBUG */

/* debug/logging: replace NULLptrs with "<NULL>" string */
#define XPU_NULLXSTR(s) (((s)!=NULL)?(s):("<NULL>"))

/*
 * Struct for XpuGetMediumSourceSizeList(), XpuFreeMediumSourceSizeList(),
 * XpuSetDocMediumSourceSize(), XpuSetPageMediumSourceSize(),
 * XpuFindMediumSourceSizeBy*()
 */
typedef struct {
  const char *tray_name;
  const char *medium_name;
  int         mbool;
  float       ma1; 
  float       ma2; 
  float       ma3; 
  float       ma4;
} XpuMediumSourceSizeRec, *XpuMediumSourceSizeList;

/*
 * Struct for XpuGetResolutionList(), XpuFreeResolutionList(),
 * XpuGetResolution(), XpuSetPageResolution(), XpuSetDocResolution(),
 * XpuFindResolutionByName()
 */
typedef struct {
  const char *name;
  long        x_dpi;
  long        y_dpi;
} XpuResolutionRec, *XpuResolutionList;

/*
 * Struct for XpuGetOrientationList(), XpuFreeOrientationList(),
 * XpuFindOrientationBy*(), XpuSetPageResolution(), 
 * XpuSetDocOrientation()
 */
typedef struct {
  const char *orientation;
} XpuOrientationRec, *XpuOrientationList;

/*
 * Struct for XpuGetPlexList(), XpuFreePlexList(), XpuFindPlexBy*(),
 * XpuSetDocPlex(), XpuSetPagePlex()
 */
typedef struct {
  const char *plex;
} XpuPlexRec, *XpuPlexList;

/*
 * Struct for XpuGetColorspaceList(), XpuFreeColorspaceList()
 */
typedef struct
{
  const char  *name;
  XVisualInfo  visualinfo;
} XpuColorspaceRec, *XpuColorspaceList;

/* XPUATTRIBUTESUPPORTED_*:
 * Flags which indicate whether it is allowed to set/change a specific attribute
 */
typedef long XpuSupportedFlags;
/* Job attributes */
#define XPUATTRIBUTESUPPORTED_JOB_NAME                     (1L<<0)
#define XPUATTRIBUTESUPPORTED_JOB_OWNER                    (1L<<1)
#define XPUATTRIBUTESUPPORTED_NOTIFICATION_PROFILE         (1L<<2)
/* Document/Page attributes */
#define XPUATTRIBUTESUPPORTED_COPY_COUNT                   (1L<<3)
#define XPUATTRIBUTESUPPORTED_DOCUMENT_FORMAT              (1L<<4)
#define XPUATTRIBUTESUPPORTED_CONTENT_ORIENTATION          (1L<<5)
#define XPUATTRIBUTESUPPORTED_DEFAULT_PRINTER_RESOLUTION   (1L<<6)
#define XPUATTRIBUTESUPPORTED_DEFAULT_INPUT_TRAY           (1L<<7)
#define XPUATTRIBUTESUPPORTED_DEFAULT_MEDIUM               (1L<<8)
#define XPUATTRIBUTESUPPORTED_PLEX                         (1L<<9)
#define XPUATTRIBUTESUPPORTED_LISTFONTS_MODES              (1L<<10)

/* prototypes */
_XFUNCPROTOBEGIN

int XpuCheckExtension( Display *pdpy );

/* Create/destroy connection to printer */
Bool XpuXprintServersAvailable( void );
int XpuGetPrinter( const char *printername, Display **pdpyptr, XPContext *pcontextptr );
void XpuClosePrinterDisplay(Display *pdpy, XPContext pcontext);

/* Misc. functions */
void XpuSetOneAttribute( Display *pdpy, XPContext pcontext, 
                         XPAttributes type, const char *attribute_name, const char *value, XPAttrReplacement replacement_rule );
void XpuSetOneLongAttribute( Display *pdpy, XPContext pcontext, 
                         XPAttributes type, const char *attribute_name, long value, XPAttrReplacement replacement_rule );
int XpuCheckSupported( Display *pdpy, XPContext pcontext, XPAttributes type, const char *attribute_name, const char *query );
int XpuSetJobTitle( Display *pdpy, XPContext pcontext, const char *title );
int XpuGetOneLongAttribute( Display *pdpy, XPContext pcontext, XPAttributes type, const char *attribute_name, long *result );
#ifdef DEBUG
void dumpXpAttributes( Display *pdpy, XPContext pcontext );
#endif /* DEBUG */
void XpuWaitForPrintNotify( Display *pdpy, int xp_event_base, int detail );

/* Get list of printers */
XPPrinterList XpuGetPrinterList( const char *printer, int *res_list_count );
void XpuFreePrinterList( XPPrinterList list );

/* Set number of document copies */
int XpuSetDocumentCopies( Display *pdpy, XPContext pcontext, long num_copies );

/* Get/Set/Query supported mediums (paper sizes) */
XpuMediumSourceSizeList XpuGetMediumSourceSizeList( Display *pdpy, XPContext pcontext, int *numEntriesPtr );
void XpuFreeMediumSourceSizeList( XpuMediumSourceSizeList list );
int XpuSetDocMediumSourceSize( Display *pdpy, XPContext pcontext, XpuMediumSourceSizeRec *medium_spec );
int XpuSetPageMediumSourceSize( Display *pdpy, XPContext pcontext, XpuMediumSourceSizeRec *medium_spec );
XpuMediumSourceSizeRec *
XpuFindMediumSourceSizeBySize( XpuMediumSourceSizeList mlist, int mlist_count,
                               float page_width_mm, float page_height_mm, float tolerance );
XpuMediumSourceSizeRec *
XpuFindMediumSourceSizeByBounds( XpuMediumSourceSizeList mlist, int mlist_count, 
                                 float m1, float m2, float m3, float m4, float tolerance );
XpuMediumSourceSizeRec *
XpuFindMediumSourceSizeByName( XpuMediumSourceSizeList mlist, int mlist_count, 
                               const char *tray_name, const char *medium_name );

/* Get/Set resolution */
XpuResolutionList XpuGetResolutionList( Display *pdpy, XPContext pcontext, int *numEntriesPtr );
void XpuFreeResolutionList( XpuResolutionList list );
Bool XpuGetResolution( Display *pdpy, XPContext pcontext, long *x_dpi, long *y_dpi );
Bool XpuSetPageResolution( Display *pdpy, XPContext pcontext, XpuResolutionRec * );
Bool XpuSetDocResolution( Display *pdpy, XPContext pcontext, XpuResolutionRec * );
XpuResolutionRec *XpuFindResolutionByName( XpuResolutionList list, int list_count, const char *resolution_name);

/* Get/Set orientation */
XpuOrientationList XpuGetOrientationList( Display *pdpy, XPContext pcontext, int *numEntriesPtr );
void XpuFreeOrientationList( XpuOrientationList list );
XpuOrientationRec *
XpuFindOrientationByName( XpuOrientationList list, int list_count, const char *orientation );
int XpuSetDocOrientation( Display *pdpy, XPContext pcontext, XpuOrientationRec *rec );
int XpuSetPageOrientation( Display *pdpy, XPContext pcontext, XpuOrientationRec *rec );

/* Get/set plex modes */
XpuPlexList XpuGetPlexList( Display *pdpy, XPContext pcontext, int *numEntriesPtr );
void XpuFreePlexList( XpuPlexList list );
XpuPlexRec *XpuFindPlexByName( XpuPlexList list, int list_count, const char *plex );
int XpuSetDocPlex( Display *pdpy, XPContext pcontext, XpuPlexRec *rec );
int XpuSetPagePlex( Display *pdpy, XPContext pcontext, XpuPlexRec *rec );

/* Set/get usage of fonts */
Bool XpuGetEnableFontDownload( Display *pdpy, XPContext pcontext );
int XpuSetEnableFontDownload( Display *pdpy, XPContext pcontext, Bool enableFontDownload );

/* Get per-printer colorspace information */
XpuColorspaceList XpuGetColorspaceList( Display *pdpy, XPContext pcontext, int *numEntriesPtr );
void XpuFreeColorspaceList( XpuColorspaceList list );
XpuColorspaceRec *XpuFindColorspaceByName( XpuColorspaceList list, int list_count, const char *colorspace );

/* Start job to printer (spooler) or file */
void XpuStartJobToSpooler(Display *pdpy);
void *XpuStartJobToFile( Display *pdpy, XPContext pcontext, const char *filename );
XPGetDocStatus XpuWaitForPrintFileChild( void *handle );

/* Get flags which indicate whether it is allowed to set/change a specific attribute */
XpuSupportedFlags XpuGetSupportedJobAttributes(Display *pdpy, XPContext pcontext);
XpuSupportedFlags XpuGetSupportedDocAttributes(Display *pdpy, XPContext pcontext);
XpuSupportedFlags XpuGetSupportedPageAttributes(Display *pdpy, XPContext pcontext);

/* Encode/decode resource strings */
char *XpuResourceEncode( const char *str );
char *XpuResourceDecode( const char *str );
void XpuResourceFreeString( char *s );

/* COMPOUND_TEXT <----> local encoding string converters */
const char *XpuXmbToCompoundText(Display *dpy, const char *xmbtext);
void XpuFreeCompundTextString( const char *s );
const char *XpuCompoundTextToXmb(Display *dpy, const char *ct);
void XpuFreeXmbString( const char *s );


_XFUNCPROTOEND

#define XpuGetJobAttributes( pdpy, pcontext )     XpGetAttributes( (pdpy), (pcontext), XPJobAttr )
#define XpuGetDocAttributes( pdpy, pcontext )     XpGetAttributes( (pdpy), (pcontext), XPDocAttr )
#define XpuGetPageAttributes( pdpy, pcontext )    XpGetAttributes( (pdpy), (pcontext), XPPageAttr )
#define XpuGetPrinterAttributes( pdpy, pcontext ) XpGetAttributes( (pdpy), (pcontext), XPPrinterAttr )
#define XpuGetServerAttributes( pdpy, pcontext )  XpGetAttributes( (pdpy), (pcontext), XPServerAttr )

#endif /* !XPRINTUTIL_H */
/* EOF. */
