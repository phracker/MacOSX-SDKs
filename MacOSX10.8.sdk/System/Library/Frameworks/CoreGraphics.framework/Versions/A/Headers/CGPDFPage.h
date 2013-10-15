/* CoreGraphics - CGPDFPage.h
   Copyright (c) 2001-2011 Apple Inc.
   All rights reserved. */

#ifndef CGPDFPAGE_H_
#define CGPDFPAGE_H_

typedef struct CGPDFPage *CGPDFPageRef;

#include <CoreGraphics/CGAffineTransform.h> 
#include <CoreGraphics/CGPDFDictionary.h> 
#include <CoreGraphics/CGPDFDocument.h> 

enum CGPDFBox {
  kCGPDFMediaBox = 0,
  kCGPDFCropBox = 1,
  kCGPDFBleedBox = 2,
  kCGPDFTrimBox = 3,
  kCGPDFArtBox = 4
};
typedef enum CGPDFBox CGPDFBox;

/* Equivalent to `CFRetain(page)', except it doesn't crash (as CFRetain
   does) if `page' is NULL. */

CG_EXTERN CGPDFPageRef CGPDFPageRetain(CGPDFPageRef page)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Equivalent to `CFRelease(page)', except it doesn't crash (as CFRelease
   does) if `page' is NULL. */

CG_EXTERN void CGPDFPageRelease(CGPDFPageRef page)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the document of `page'. */

CG_EXTERN CGPDFDocumentRef CGPDFPageGetDocument(CGPDFPageRef page)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the page number of `page'. */

CG_EXTERN size_t CGPDFPageGetPageNumber(CGPDFPageRef page)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the rectangle associated with `box' in `page'. This is the value
   of the corresponding entry (such as /MediaBox, /ArtBox, and so on) in the
   page's dictionary. */

CG_EXTERN CGRect CGPDFPageGetBoxRect(CGPDFPageRef page, CGPDFBox box)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the rotation angle (in degrees) of `page'. This is the value of
   the /Rotate entry in the page's dictionary. */

CG_EXTERN int CGPDFPageGetRotationAngle(CGPDFPageRef page)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return a transform mapping the box specified by `box' to `rect' as
   follows:
     - Compute the effective rect by intersecting the rect associated with
       `box' and the /MediaBox entry of the page.
     - Rotate the effective rect according to the page's /Rotate entry.
     - Center the resulting rect on `rect'. If `rotation' is non-zero, then
       the rect will rotated clockwise by `rotation' degrees. `rotation'
       must be a multiple of 90.
     - Scale the rect down, if necessary, so that it coincides with the
       edges of `rect'. If `preserveAspectRatio' is true, then the final
       rect will coincide with the edges of `rect' only in the more
       restrictive dimension. */

CG_EXTERN CGAffineTransform CGPDFPageGetDrawingTransform(CGPDFPageRef page,
  CGPDFBox box, CGRect rect, int rotate, bool preserveAspectRatio)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the dictionary of `page'. */

CG_EXTERN CGPDFDictionaryRef CGPDFPageGetDictionary(CGPDFPageRef page)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the CFTypeID for CGPDFPageRefs. */

CG_EXTERN CFTypeID CGPDFPageGetTypeID(void)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

#endif /* CGPDFPAGE_H_ */
