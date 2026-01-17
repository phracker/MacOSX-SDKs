
/*
 * $Xorg:xpapputil.h,v 1.1 2002/06/10 02:54:18 gisburn Exp $
 * 
 * xpapputil - Application level utility library for Xprint
 *
 * 
Copyright 2002-2004 Roland Mainz <roland.mainz@nrubsig.org>

All Rights Reserved.

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
 * Author:  Roland Mainz <roland.mainz@nrubsig.org>
 */

#ifndef XPAPPUTILS_H
#define XPAPPUTILS_H 1
 
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XprintUtil/xprintutil.h>

#ifdef DEBUG
#define XPAU_RETURN_IF_FAIL(expr, return_code) \
    if( !(expr) ) { \
      printf("XPAU_RETURN_IF_FAIL(file %s, line %d): " #expr ", returning " #return_code "\n", __FILE__, __LINE__); \
      return (return_code); \
    }

#define XPAU_DEBUG(x) x

#else

#define XPAU_RETURN_IF_FAIL(expr, return_code) \
    if( !(expr) ) { \
      return (return_code); \
    }

#define XPAU_DEBUG(x)
#endif /* DEBUG */

/*
 * Struct for XpauGetContext(), XpauReleaseContext()
 * 
 */
typedef struct
{
    Display                 *pdpy;
    XPContext                pcontext;
    int                      xp_event_base,
                             xp_error_base;

    Bool                     inJob;
    Bool                     inDocument;
    Bool                     inPage;

    void                    *print_to_filehandle;
    Screen                  *pscreen;
    int                      pscreennumber;
    long                     document_dpi_x,
                             document_dpi_y;
    
    XpuSupportedFlags        supported_job_attributes;
    XpuSupportedFlags        supported_doc_attributes;
    XpuSupportedFlags        supported_page_attributes;
    
    XpuMediumSourceSizeList  medium_list;
    int                      medium_num_list_entries;
    XpuResolutionList        resolution_list;
    int                      resolution_num_list_entries;
    XpuOrientationList       orientation_list;
    int                      orientation_num_list_entries;
    XpuPlexList              plex_list;
    int                      plex_num_list_entries;
} XpauContext;


#define XpauVFilename      (1L<<0)
#define XpauVMedium        (1L<<1)
#define XpauVResolution    (1L<<2)
#define XpauVOrientation   (1L<<3)
#define XpauVPlex          (1L<<4)
#define XpauVCopies        (1L<<5)
#define XpauVTitle         (1L<<6)
#define XpauVAll (XpauVFilename    | \
                  XpauVMedium      | \
                  XpauVResolution  | \
                  XpauVOrientation | \
                  XpauVPlex        | \
                  XpauVCopies      | \
                  XpauVTitle)

typedef unsigned long XpauFlags;

typedef struct
{
  const char              *title;
  long                     copies;
} XpauJobValues;

typedef struct
{
  XpuMediumSourceSizeRec  *medium;
  XpuResolutionRec        *resolution;
  XpuOrientationRec       *orientation;
  XpuPlexRec              *plex;
  long                     copies;
} XpauDocValues;

typedef struct
{
  XpuMediumSourceSizeRec  *medium;
  XpuResolutionRec        *resolution;
  XpuOrientationRec       *orientation;
  XpuPlexRec              *plex;
} XpauPageValues;

typedef enum {
  XpAuError_success = 0, 
  XpAuError_unspecified_error, 
  XpAuError_errno,      /* check |errno| for error */
  XpAuError_error_no_memory, 
  XpAuError_unexpected_eos, 
  XpAuError_unknown_argument, 
  XpAuError_unsupported_medium, 
  XpAuError_unsupported_resolution, 
  XpAuError_unsupported_orientation, 
  XpAuError_unsupported_plex,
  XpAuError_unsupported_copy_count,
  XpAuError_unsupported_job_name,
  XpAuError_no_dpi_set,
  XpAuError_not_inside_job,
  XpAuError_not_inside_document,
  XpAuError_not_inside_page,
  XpAuError_inside_job,
  XpAuError_inside_document,
  XpAuError_inside_page
} XpAuErrorValue;

/* Prototypes */
XpauContext *  XpauGetContext( const char *printername );
void           XpauReleaseContext( XpauContext *context );
XpAuErrorValue XpauParseArgs( XpauContext *context,
                              XpauFlags *jobvaluemask, XpauJobValues *jobvalues,
                              XpauFlags *docvaluemask, XpauDocValues *docvalues,
                              char **jobfilename,
                              const char *argument_string );
XpAuErrorValue XpauSetJobValues( XpauContext *context, XpauFlags valuemask, XpauJobValues *Xpaujobvalues );
XpAuErrorValue XpauSetDocValues( XpauContext *context, XpauFlags valuemask, XpauDocValues *Xpaudocvalues );
XpAuErrorValue XpauSetPageValues( XpauContext *context, XpauFlags valuemask, XpauPageValues *Xpaupagevalues );
XpAuErrorValue XpauStartJob( XpauContext *context, const char *printerfile );
XpAuErrorValue XpauEndJob( XpauContext *context );
XpAuErrorValue XpauStartDocument( XpauContext *context, XPDocumentType type );
XpAuErrorValue XpauEndDocument( XpauContext *context );
XpAuErrorValue XpauStartPage( XpauContext *context, Window pwin );
XpAuErrorValue XpauEndPage( XpauContext *context );
void           XpauWaitForPrintNotify(XpauContext *context, int type);
const char    *XpAuErrorValueToString(XpAuErrorValue value);
#endif /* !XPAPPUTILS_H */


