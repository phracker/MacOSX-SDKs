/* =============================================================================
 *
 *	File:		QDPictToCGContext.h
 *
 *  Written By:	David Gelphman (gelphman@apple.com, Ext. 4-6106)
 *
 *	Copyright © 2001, Apple Computer Inc., all rights reserved
 *	All rights reserved.
 *
 *  Description:
 *		This module implements QuickDraw picture drawing into 
 *		CG contexts.
 *
 *	$Revision: 1.2 $
 *	$Date: 2001/06/22 20:45:02 $
 *
 * ========================================================================== */


/* --- Change History: ---------------------------------------------------------

$Log: QDPictToCGContext.h,v $
Revision 1.2  2001/06/22 20:45:02  velocio
remove  directive from header comment

Revision 1.1  2001/04/16 20:34:14  velocio
#2679365: Need to draw PICTs into CG context

Revision 1.3  2001/03/29 23:44:33  gelphman
DMG825 complete changes to conform to agreed upon .h.

Revision 1.2  2001/03/29 20:30:31  gelphman
DMG825 fix to support auto CVS revision updating.


----------------------------------------------------------------------------- */
#ifndef _QDPICTTOCGCONTEXT_H_
#define _QDPICTTOCGCONTEXT_H_

typedef struct QDPict *QDPictRef;

#ifndef __CGCONTEXT__
#include <CoreGraphics/CGContext.h>
#endif

/*
    Note: QuickDraw picture data typically comes in two forms: a PICT resource
    that begins the picture header data at the beginning of the resource and PICT
    files that begin with 512 bytes of arbitrary data, followed by
    the picture header data. For this reason, the routines that create a QDPictRef
    attempt to find the picture header data beginning at either the first byte
    of the data provided or at byte 513 of the data provided.
    
    Additionally the Picture Bounds must not be an empty rect.
*/

/* Create a QDPict reference, using `provider' to obtain the QDPict's data. 
 * It is assumed that either the first byte or the 513th byte of data
 * in the file referenced by the URL is the first byte of the
 * picture header. If the URL does not begin PICT data at one
 * of these places in the data fork then the QDPictRef returned will be NULL.
*/
extern QDPictRef QDPictCreateWithProvider(CGDataProviderRef provider);

/* Create a QDPict reference from `url'. 
 * It is assumed that either the first byte or the 513th byte of data
 * in the file referenced by the URL is the first byte of the
 * picture header. If the URL does not begin PICT data at one
 * of these places in the data fork then the QDPictRef returned will be NULL.
*/
extern QDPictRef QDPictCreateWithURL(CFURLRef url);

/* Increment the retain count of `pictRef' and return it.  All 
 * pictRefs are created with an initial retain count of 1. */
extern QDPictRef QDPictRetain(QDPictRef pictRef);

/* Decrement the retain count of `pictRef'.  If the retain count reaches 0,
 * then free it and any associated resources. */
extern void QDPictRelease(QDPictRef pictRef);

/* Return the Picture Bounds of the QuickDraw picture represented by `pictRef'. This
    rectangle is in the default user space with one unit = 1/72 inch.
*/
extern CGRect QDPictGetBounds(QDPictRef pictRef);

/* Return the resolution of the QuickDraw picture represented by `pictRef'.
    This data, together with the CGRect returned by QDPictGetBounds, can be
    used to compute the size of the picture in pixels, which is what QuickDraw
    really records into pictures.
*/
extern void QDPictGetResolution(QDPictRef pictRef, float *xRes, float *yRes);

/* Draw `pictRef' in the rectangular area specified by `rect'.
 * The PICT bounds of the page is scaled, if necessary, to fit into
 * `rect'. To get unscaled results, supply a rect the size of the rect
 * returned by QDPictGetBounds.
*/
extern OSStatus QDPictDrawToCGContext(CGContextRef ctx, CGRect rect, QDPictRef pictRef);

#endif	/* _QDPICTTOCGCONTEXT_H_ */
