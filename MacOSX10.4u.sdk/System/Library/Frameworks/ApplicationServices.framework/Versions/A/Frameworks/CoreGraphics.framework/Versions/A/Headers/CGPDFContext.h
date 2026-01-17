/* CoreGraphics - CGPDFContext.h
 * Copyright (c) 2000-2004 Apple Computer, Inc.
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
 * used. `auxiliaryInfo' specifies additional information used by the PDF
 * context when generating the PDF file.  The keys and values in
 * `auxiliaryInfo' are described below. If `mediaBox' is non-NULL, then its
 * value overrides the value of `kCGPDFContextMediaBox' if specified in the
 * `auxiliaryInfo' dictionary. */

CG_EXTERN CGContextRef CGPDFContextCreate(CGDataConsumerRef consumer, const CGRect *mediaBox, CFDictionaryRef auxiliaryInfo);

/* Create a PDF context for writing to `url'. This function behaves in the
 * same manner as the above function, except that the output data will be
 * written to `url'. */

CG_EXTERN CGContextRef CGPDFContextCreateWithURL(CFURLRef url, const CGRect *mediaBox, CFDictionaryRef auxiliaryInfo);

/* Begin a new page in the PDF context `context'. */

CG_EXTERN void CGPDFContextBeginPage(CGContextRef context, CFDictionaryRef pageInfo) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* End the current page in the PDF context `context'. */

CG_EXTERN void CGPDFContextEndPage(CGContextRef context) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set the URL associated with `rect' to `url' in the PDF context
 * `context'. */

CG_EXTERN void CGPDFContextSetURLForRect(CGContextRef context, CFURLRef url, CGRect rect) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Create a PDF destination named `name' at `point' in the current page of
 * the PDF context `context'. */

void CGPDFContextAddDestinationAtPoint(CGContextRef context, CFStringRef name, CGPoint point) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Specify a destination named `name' to jump to when clicking in `rect' of
 * the current page of the PDF context `context'. */

CG_EXTERN void CGPDFContextSetDestinationForRect(CGContextRef context, CFStringRef name, CGRect rect) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*** Keys for the auxiliary info dictionary or the page info dictionary. ***/ 

/* The media box for the document or for a given page. Optional; if
 * present, the value of this key must be a CFData containing a CGRect
 * (stored by value, not by reference). */

CG_EXTERN CFStringRef kCGPDFContextMediaBox AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The crop box for the document or for a given page. Optional; if present,
 * the value of this key must be a CFData containing a CGRect (stored by
 * value, not by reference). */

CG_EXTERN CFStringRef kCGPDFContextCropBox AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The bleed box for the document or for a given page. Optional; if
 * present, the value of this key must be a CFData containing a CGRect
 * (stored by value, not by reference). */

CG_EXTERN CFStringRef kCGPDFContextBleedBox AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The trim box for the document or for a given page. Optional; if present,
 * the value of this key must be a CFData containing a CGRect (stored by
 * value, not by reference). */

CG_EXTERN CFStringRef kCGPDFContextTrimBox AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The art box for the document or for a given page. Optional; if present,
 * the value of this key must be a CFData containing a CGRect (stored by
 * value, not by reference). */

CG_EXTERN CFStringRef kCGPDFContextArtBox AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*** Keys for auxiliary info dictionary. ***/

/* The document's title. Optional; if present, the value of this key must
 * be a CFString. */

CG_EXTERN CFStringRef kCGPDFContextTitle AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The name of the person who created this document. Optional; if present,
 * the value of this key must be a CFString. */

CG_EXTERN CFStringRef kCGPDFContextAuthor AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The name of the application that created the original data used to
 * create this document. Optional; if present, the value of this key must
 * be a CFString. */

CG_EXTERN CFStringRef kCGPDFContextCreator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The "owner password" of the PDF document. If this key is specified, the
 * document will be encrypted using the value as the owner password;
 * otherwise, the document will not be encrypted. The value of this key
 * must be a CFStringRef which can be represented in ASCII encoding; only
 * the first 32 bytes will be used for the password. There is no default
 * value for this key.
 *
 * If the value of this key cannot be represented in ASCII, the document
 * will not be created and the creation function will return NULL. */

CG_EXTERN CFStringRef kCGPDFContextOwnerPassword AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The "user password" of the PDF document. If the document is encrypted,
 * then the value of this key will be the user password for the document;
 * if unspecified, the user password will be the empty string. The value of
 * this key must be a CFStringRef which can be represented in ASCII
 * encoding; only the first 32 bytes will be used for the password.
 *
 * If the value of this key cannot be represented in ASCII, the document
 * will not be created and the creation function will return NULL. */

CG_EXTERN CFStringRef kCGPDFContextUserPassword AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Used to specify whether the document allows printing when unlocked with
 * the user password.  The value of this key must be a CFBooleanRef.  The
 * default value of this key is "kCFBooleanTrue". */

CG_EXTERN CFStringRef kCGPDFContextAllowsPrinting AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Used to specify whether the document allows copying when unlocked with
 * the user password.  The value of this key must be a CFBooleanRef.  The
 * default value of this key is "kCFBooleanTrue". */

CG_EXTERN CFStringRef kCGPDFContextAllowsCopying AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The document's PDF/X output intent. Optional; if present, the value of
 * this key must be a CFDictionaryRef. The dictionary is added to the
 * /OutputIntents entry in the PDF file's document catalog. The keys and
 * values contained in the dictionary must match those specified in section
 * 9.10.4 of the PDF 1.4 specification, ISO/DIS 15930-3 document published
 * by ISO/TC 130, and Adobe Technical Note #5413. */

CG_EXTERN CFStringRef kCGPDFContextOutputIntent AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The following keys are supported in the output intent dictionary:
 *
 * kCGPDFXOutputIntentSubtype ("S") - The output intent subtype.  This key
 *    is required; the value of this key must be a CFString equal to
 *    "GTS_PDFX"; otherwise, the dictionary is ignored. */

CG_EXTERN CFStringRef kCGPDFXOutputIntentSubtype AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* kCGPDFXOutputConditionIdentifier ("OutputConditionIdentifier") - A
 *    string identifying the intended output device or production condition
 *    in a human- or machine-readable form.  This key is required; the
 *    value of this key must be a CFString.  For best results, the string
 *    should be representable losslessly in ASCII encoding. */

CG_EXTERN CFStringRef kCGPDFXOutputConditionIdentifier AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* kCGPDFXOutputCondition ("OutputCondition") - A text string identifying
 *    the intended output device or production condition in a human-
 *    readable form.  This key is optional; if present, the value of this
 *    key must be a CFString. */

CG_EXTERN CFStringRef kCGPDFXOutputCondition AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* kCGPDFXRegistryName ("RegistryName") - A string identifying the registry
 *   in which the condition designated by kCGPDFXOutputConditionIdentifier
 *   is defined.  This key is optional; if present, the value of this key
 *   must be a CFString.  For best results, the string should be
 *   representable losslessly in ASCII encoding. */

CG_EXTERN CFStringRef kCGPDFXRegistryName AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* kCGPDFXInfo ("Info") - A human-readable text string containing
 *    additional information or comments about the intended target device
 *    or production condition.  This key is required if the value of
 *    kCGPDFXOutputConditionIdentifier does not specify a standard
 *    production condition; it is optional otherwise.  If present, the
 *    value of this key must be a CFString. */

CG_EXTERN CFStringRef kCGPDFXInfo AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* kCGPDFXDestinationOutputProfile ("DestOutputProfile") - An ICC profile
 *    stream defining the transformation from the PDF document's source
 *    colors to output device colorants.  This key is required if the value
 *    of kCGPDFXOutputConditionIdentifier does not specify a standard
 *    production condition; it is optional otherwise.  If present, the
 *    value of this key must be a ICC-based CGColorSpaceRef. */

CG_EXTERN CFStringRef kCGPDFXDestinationOutputProfile AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The document's output intents. Optional; if present, the value must be a
 * CFArrayRef containing one or more CFDictionaryRefs. The array is added
 * to the PDF document in the /OutputIntents entry in the PDF file's
 * document catalog.  Each dictionary in the array must be of form
 * specified above for the "kCGPDFContextOutputIntent" key, except that
 * only the first dictionary in the array may contain the
 * kCGPDFXOutputIntentSubtype ("S") key with a value of "GTS_PDFX". If both
 * the "kCGPDFContextOutputIntent" and "kCGPDFContextOutputIntents" keys
 * are specified, the former is ignored. */

CG_EXTERN CFStringRef kCGPDFContextOutputIntents AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN_C_END

/* Compatibility with earlier versions of Mac OS X. */

#if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_4

#define kCGPDFContextTitle CFSTR("kCGPDFContextTitle")
#define kCGPDFContextAuthor CFSTR("kCGPDFContextAuthor")
#define kCGPDFContextCreator CFSTR("kCGPDFContextCreator")
#define kCGPDFContextOutputIntent CFSTR("kCGPDFContextOutputIntent")
#define kCGPDFContextOutputIntents CFSTR("kCGPDFContextOutputIntents")

#endif	/* MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_4 */

#endif	/* CGPDFCONTEXT_H_ */
