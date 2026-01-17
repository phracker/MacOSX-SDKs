/* CoreGraphics - CGPDFDocument.h
 * Copyright (c) 2000 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGPDFDOCUMENT_H_
#define CGPDFDOCUMENT_H_

typedef struct CGPDFDocument *CGPDFDocumentRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGDataProvider.h> 
#include <CoreGraphics/CGGeometry.h> 
#include <CoreFoundation/CFURL.h>

CG_EXTERN_C_BEGIN

/* Create a PDF document, using `provider' to obtain the document's
 * data. */

CG_EXTERN CGPDFDocumentRef CGPDFDocumentCreateWithProvider(CGDataProviderRef provider);

/* Create a PDF document from `url'. */

CG_EXTERN CGPDFDocumentRef CGPDFDocumentCreateWithURL(CFURLRef url);

/* Increment the retain count of `document' and return it.  All PDF
 * documents are created with an initial retain count of 1. */

CG_EXTERN CGPDFDocumentRef CGPDFDocumentRetain(CGPDFDocumentRef document);

/* Decrement the retain count of `document'.  If the retain count reaches 0,
 * then free it and any associated resources. */

CG_EXTERN void CGPDFDocumentRelease(CGPDFDocumentRef document);

/* Return the number of pages in `document'. */

CG_EXTERN int CGPDFDocumentGetNumberOfPages(CGPDFDocumentRef document);

/* Return the media box of page number `page' in `document'. */

CG_EXTERN CGRect CGPDFDocumentGetMediaBox(CGPDFDocumentRef document, int page);

/* Return the crop box of page number `page' in `document'. */

CG_EXTERN CGRect CGPDFDocumentGetCropBox(CGPDFDocumentRef document, int page);

/* Return the bleed box of page number `page' in `document'. */

CG_EXTERN CGRect CGPDFDocumentGetBleedBox(CGPDFDocumentRef document, int page);

/* Return the trim box of page number `page' in `document'. */

CG_EXTERN CGRect CGPDFDocumentGetTrimBox(CGPDFDocumentRef document, int page);

/* Return the art box of page number `page' in `document'. */

CG_EXTERN CGRect CGPDFDocumentGetArtBox(CGPDFDocumentRef document, int page);

/* Return the rotation angle (in degrees) of page number `page' in
 * `document'. */

CG_EXTERN int CGPDFDocumentGetRotationAngle(CGPDFDocumentRef document, int page);

CG_EXTERN_C_END

#endif	/* CGPDFDOCUMENT_H_ */
