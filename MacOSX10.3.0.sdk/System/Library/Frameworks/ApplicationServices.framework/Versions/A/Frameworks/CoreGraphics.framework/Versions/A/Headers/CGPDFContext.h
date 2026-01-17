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
 * `auxiliaryInfo' are described below. */

CG_EXTERN CGContextRef CGPDFContextCreate(CGDataConsumerRef consumer, const CGRect *mediaBox, CFDictionaryRef auxiliaryInfo);

/* Convenience function: create a PDF context, writing to `url'. */

CG_EXTERN CGContextRef CGPDFContextCreateWithURL(CFURLRef url, const CGRect *mediaBox, CFDictionaryRef auxiliaryInfo);

/*** Keys for auxiliary info dictionary. ***/

/* The document's title. Optional; if present, the value must be a
 * CFString. */

#define kCGPDFContextTitle CFSTR("kCGPDFContextTitle")

/* The name of the person who created this document. Optional; if present,
 * the value must be a CFString. */

#define kCGPDFContextAuthor CFSTR("kCGPDFContextAuthor")

/* The name of the application that created the original data used to
 * create this document. Optional; if present, the value must be a
 * CFString. */

#define kCGPDFContextCreator CFSTR("kCGPDFContextCreator")

/* The document's output intent. Optional; if present, the value must be a
 * CFDictionaryRef. The dictionary is added to the PDF document in the
 * /OutputIntents entry in the PDF file's document catalog. The keys and
 * values contained in the dictionary must match those specified in section
 * 9.10.4 of the PDF 1.4 specification, ISO/DIS 15930-3 document published
 * by ISO/TC 130, and Adobe Technical Note #5413.
 *
 * The following keys are supported:
 *
 * "S" - The output intent subtype.  This key is required; the value must
 *    be a CFString equal to "GTS_PDFX"; otherwise, the dictionary is
 *    ignored.
 *
 * "OutputConditionIdentifier" - A string identifying the intended output
 *    device or production condition in a human- or machine-readable form.
 *    This key is required; the value must be a CFString.  For best
 *    results, the string should be representable losslessly in ASCII
 *    encoding.
 *
 * "OutputCondition" - A text string identifying the intended output device
 *    or production condition in a human-readable form.  This key is
 *    optional; if present, the value must be a CFString.
 *
 * "RegistryName" - A string identifying the registry in which the
 *    condition designated by "OutputConditionIdentifier" is defined.  This
 *    key is optional; if present, the value must be a CFString.  For best
 *    results, the string should be representable losslessly in ASCII
 *    encoding.
 *
 * "Info" - A human-readable text string containing additional information
 *    or comments about the intended target device or production condition.
 *    This key is required if "OutputConditionIdentifier" does not specify
 *    a standard production condition; it is optional otherwise.  If
 *    present, the value must be a CFString.
 *
 * "DestOutputProfile" - An ICC profile stream defined the transformation
 *    from the PDF document's source colors to output device colorants.
 *    This key is required if "OutputConditionIdentifier" does not specify
 *    a standard production condition; it is optional otherwise.  If
 *    present, the value must be a ICC-based CGColorSpaceRef. */

#define kCGPDFContextOutputIntent CFSTR("kCGPDFContextOutputIntent")

/* The document's output intents. Optional; if present, the value must be a
 * CFArrayRef containing one or more CFDictionaryRefs. The array is added
 * to the PDF document in the /OutputIntents entry in the PDF file's
 * document catalog.  Each dictionary in the array must be of form
 * specified above for the "kCGPDFContextOutputIntent" key, except that
 * only the first dictionary in the array is required to contain the "S"
 * key with a value of "GTS_PDFX". If both the "kCGPDFContextOutputIntent"
 * and "kCGPDFContextOutputIntents" keys are specified, the former will be
 * ignored. */

#define kCGPDFContextOutputIntents CFSTR("kCGPDFContextOutputIntents")

CG_EXTERN_C_END

#endif	/* CGPDFCONTEXT_H_ */
