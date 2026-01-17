/*
 * dosXpreview.h
 *
 * (c) Copyright 1990-1994 Adobe Systems Incorporated.
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
/* $XFree86: xc/include/DPS/dpsXpreview.h,v 1.2 2000/06/07 22:02:55 tsi Exp $ */

#ifndef DPS_X_PREVIEW_H
#define DPS_X_PREVIEW_H

#include <DPS/dpsXcommon.h>

typedef struct {
	long startPos;
	int nestingLevel;
	unsigned long binaryCount;
	Bool continuedLine;
} XDPSPosition;

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* The rewind function should set the file pointer to the beginning of an
   area of interest.
*/

typedef void (*XDPSRewindFunction)(FILE *f,
				   DPSPointer clientData);

/* The gets function should duplicate the behavior of the fgets function,
   but it may return NULL to indicate that the area of interest is over
   even if the end of file is not yet reached.
*/

typedef char *(*XDPSGetsFunction)(char *buf,
				  int n,
				  FILE *f,
				  DPSPointer clientData);

/* XDPSSetFileFunctions defines the functions XDPSCreatePixmapForEPSF and
   XDPSImageFileIntoDrawable will use to reset the file to its beginning
   and to read the next line of the file.
*/

extern int XDPSSetFileFunctions(XDPSRewindFunction rewindFunction,
				DPSPointer rewindClientData,
				XDPSGetsFunction getsFunction,
				DPSPointer getsClientData);

/* The following two functions expect NULL as client data and are appropriate
   for dealing with a separate EPSF file.  They are the default rewind and
   gets functions, and may be used to reset the functions after changing them.
*/

extern void XDPSFileRewindFunc(FILE *f,
			       DPSPointer data);

extern char *XDPSFileGetsFunc(char *buf,
			      int n,
			      FILE *f,
			      DPSPointer data);

/* The following two functions expect the address of an XDPSPosition
   structure as client data and are appropriate for dealing with an ESPF
   file embedded in another file.  The 2.0 document structuring conventions
   %%BeginDocument and %%EndDocument are used to detect the end of the
   included file and to identify any embedded files.  The startPos
   in the XDPSPosition structure should be the first character of the
   embedded file (as found by, for example, ftell).  It must *not* include
   the initial %%BeginDocument comment for this document.  The nestingLevel,
   continuedLine, and binaryCount fields are used internally by the functions
   and should not be modified.  After calling XDPSImageFileIntoDrawable,
   startPos will be modified to be the first character after the complete
   EPSF file, or -1 if the EPSF ended with end-of-file.
*/

extern void XDPSEmbeddedEPSFRewindFunc(FILE *f,
				       DPSPointer data);

extern char *XDPSEmbeddedGetsFunc(char *buf, int n, FILE *f, DPSPointer data);

extern char *XDPSEmbeddedEPSFGetsFunc(char *buf,
				      int n,
				      FILE *f,
				      DPSPointer data);

/* XDPSCreatePixmapForEPSF creates a pixmap for use on the specified screen.
   The size of the pixmap is determined by reading the %%BoundingBox comment
   in the file, scaled by the pixelsPerPoint value.  The size of the
   pixmap is returned in pixelSize (x and y will be zero) and the bounding
   box (in points) is returned in bbox.  The context parameter may be NULL,
   in which case the shared context for the display will be used.  If a real
   context is passed, it must be registered with XDPSRegisterContext.
*/

extern int XDPSCreatePixmapForEPSF(DPSContext context,
				   Screen *screen,
				   FILE *epsf,
				   int depth,
				   double pixelsPerPoint,
				   Pixmap *p,
				   XRectangle *pixelSize,
				   XRectangle *bbox);

/* XDPSPixelsPerPoint returns the number of pixels in one point on the given
   screen.  Note that if the server lies about the resolution of the screen
   (as it often does) the lie will be repeated here. */

extern double XDPSPixelsPerPoint(Screen *screen);

/* XDPSImageFileIntoDrawable images a PostScript file into a drawable.
   The imaging will be offset by the xOffset and yOffset values, these
   must be in points.  If the clear parameter is True, the area defined
   by the bbox will be cleared to white before imaging.  If createMask is
   True, the drawable must be 1 bit deep and it will end up containing a
   1 bit everywhere that the PostScript file images, if clear is also True
   any untouched bits will be 0.  If the drawable is a pixmap, the result
   is suitable for use as a mask in X drawing call.  The context parameter
   may be NULL, in which case the shared context for the display will
   be used.  If a real context is passed, it must be registered with
   XDPSRegisterContext.  

   If waitForCompletion is True, XDPSImageFileIntoDrawable
   will wait for the imaging to be finished before returning.  If
   waitForCompletion parameter is False, XDPSImageFileIntoDrawable will wait
   for a time as specified by the XDPSSetImagingTimeout before returning
   dps_status_imaging_incomplete.  The caller checks for the completion of
   the imaging by calling XDPSCheckImagingResults periodically.

   Partial imaging may be stopped by destroying the context with
   XDPSDestroySharedContext or both DPSDestroyContext and
   XDPSUnregisterContext.  Doing anything with a context between the time
   XDPSImageFileIntoDrawable returns dps_status_imaging_incomplete and the
   time XDPSCheckImagingResults returns other than
   dps_status_imaging_incomplete will yield incorrect imaging
   results and leave the context in an undefined state, don't do it.

   If the display does not support the DPS extension, the image area as
   determined by the bbox parameter will be filled with a 50% gray stipple
   pattern, or set to solid 1's if createMask is True.

   The context parameter may be NULL, in which case the shared context
   for the display will be used.  If a real context is passed, it must
   be registered with XDPSRegisterContext.
*/

extern int XDPSImageFileIntoDrawable(DPSContext context,
				     Screen *screen,
				     Drawable dest,
				     FILE *file,
				     int drawableHeight,
				     int drawableDepth,
				     XRectangle *bbox,
				     int xOffset,
				     int yOffset,
				     double pixelsPerPoint,
				     Bool clear,
				     Bool createMask,
				     Bool waitForCompletion,
				     Bool *doneFlag);

/* XDPSCheckImagingResults checks the status of the imaging on the context.
   If the imaging is not done, it returns dps_status_imaging_incomplete, if
   it is done, it returns dps_status_success or dps_status_postscript_error,
   if the context is not currently involved in imaging it returns
   dps_status_illegal_value.

   The context parameter may be NULL, in which case the shared context
   for the display will be used.  If a real context is passed, it must
   be registered with XDPSRegisterContext.
*/

extern int XDPSCheckImagingResults(DPSContext context,
				   Screen *screen);

/* XDPSSetImagingTimeout determines how long XDPSImageFileIntoDrawable will
   wait before returning after an incomplete imaging, in milliseconds.
   XDPSImageFileIntoDrawable will start by waiting the timeout and will
   repeatedly double the wait until the imaging is complete or until
   maxDoublings have occurred.  */

extern void XDPSSetImagingTimeout(int timeout,
				  int maxDoublings);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* DPS_X_PREVIEW_H */
