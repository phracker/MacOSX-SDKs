/* CoreGraphics - CGPDFContext.h
 * Copyright (c) 2000 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGPDFCONTEXT_H_
#define CGPDFCONTEXT_H_

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGContext.h>
#include <CoreGraphics/CGDataConsumer.h>
#include <CoreFoundation/CFDictionary.h>

CG_EXTERN_C_BEGIN

/* Create a PDF context, using `consumer' for output. `mediaBox' is the
 * default page media bounding box; if NULL, then a default page size is
 * used.  `auxiliaryInfo' specifies additional information used by the PDF
 * context when generating the PDF file.  The keys and values in
 * `auxiliaryInfo' must be CFStrings.  The following keys are recognized:
 *   Key       Value
 *   --------  --------
 *   Title     The document's title.
 *   Author    The name of the person who created the document.
 *   Creator   If the document was converted to PDF from another format,
 *             the name of the application that created the original
 *             document from which it was converted. */

CG_EXTERN CGContextRef CGPDFContextCreate(CGDataConsumerRef consumer, const CGRect *mediaBox, CFDictionaryRef auxiliaryInfo);

/* Convenience function: create a PDF context, writing to `url'. */

CG_EXTERN CGContextRef CGPDFContextCreateWithURL(CFURLRef url, const CGRect *mediaBox, CFDictionaryRef auxiliaryInfo);

CG_EXTERN_C_END

#endif	/* CGPDFCONTEXT_H_ */
