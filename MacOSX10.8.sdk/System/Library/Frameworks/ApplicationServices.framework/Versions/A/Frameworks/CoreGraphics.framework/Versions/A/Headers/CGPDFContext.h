/* CoreGraphics - CGPDFContext.h
   Copyright (c) 2000-2011 Apple Inc.
   All rights reserved. */

#ifndef CGPDFCONTEXT_H_
#define CGPDFCONTEXT_H_

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGContext.h>
#include <CoreGraphics/CGDataConsumer.h>
#include <CoreFoundation/CFDictionary.h>

/* Create a PDF context, using `consumer' for output. `mediaBox' is the
   default page media bounding box; if NULL, then a default page size is
   used. `auxiliaryInfo' specifies additional information used by the PDF
   context when generating the PDF file. The keys and values in
   `auxiliaryInfo' are described below. If `mediaBox' is non-NULL, then its
   value overrides the value of `kCGPDFContextMediaBox' if specified in the
   `auxiliaryInfo' dictionary. */

CG_EXTERN CGContextRef CGPDFContextCreate(CGDataConsumerRef consumer,
  const CGRect *mediaBox, CFDictionaryRef auxiliaryInfo)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a PDF context for writing to `url'. This function behaves in the
   same manner as the above function, except that the output data will be
   written to `url'. */

CG_EXTERN CGContextRef CGPDFContextCreateWithURL(CFURLRef url,
  const CGRect *mediaBox, CFDictionaryRef auxiliaryInfo)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Close a PDF context. After closing the context, all pending data is
   written to the context's destination, and the PDF file is completed. No
   additional data will be written to the context's destionation after
   closing. */

CG_EXTERN void CGPDFContextClose(CGContextRef context)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Begin a new page in the PDF context `context'. */

CG_EXTERN void CGPDFContextBeginPage(CGContextRef context,
  CFDictionaryRef pageInfo)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* End the current page in the PDF context `context'. */

CG_EXTERN void CGPDFContextEndPage(CGContextRef context)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Add the metadata stream specified by `metadata' to the document catalog
   of `context', as described in Table 3.25, "Entries in the catalog
   dictionary", of the PDF 1.7 specification. The contents of metadata must
   be XML formatted according to the Extensible Metadata Platform, as
   described in section 10.2.2, "Metadata Streams", of the PDF 1.7
   specification. */

CG_EXTERN void CGPDFContextAddDocumentMetadata(CGContextRef context,
  CFDataRef metadata) CG_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_4_0);

/* Set the URL associated with `rect' to `url' in the PDF context
   `context'. */

CG_EXTERN void CGPDFContextSetURLForRect(CGContextRef context, CFURLRef url,
  CGRect rect) CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Create a PDF destination named `name' at `point' in the current page of
   the PDF context `context'. */

CG_EXTERN void CGPDFContextAddDestinationAtPoint(CGContextRef context,
  CFStringRef name, CGPoint point)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Specify a destination named `name' to jump to when clicking in `rect' of
   the current page of the PDF context `context'. */

CG_EXTERN void CGPDFContextSetDestinationForRect(CGContextRef context,
  CFStringRef name, CGRect rect)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/*** Keys for the auxiliary info dictionary or the page info dictionary. ***/ 

/* The media box for the document or for a given page. Optional; if present,
   the value of this key must be a CFData containing a CGRect (stored by
   value, not by reference). */

CG_EXTERN const CFStringRef kCGPDFContextMediaBox
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The crop box for the document or for a given page. Optional; if present,
   the value of this key must be a CFData containing a CGRect (stored by
   value, not by reference). */

CG_EXTERN const CFStringRef kCGPDFContextCropBox
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The bleed box for the document or for a given page. Optional; if present,
   the value of this key must be a CFData containing a CGRect (stored by
   value, not by reference). */

CG_EXTERN const CFStringRef kCGPDFContextBleedBox
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The trim box for the document or for a given page. Optional; if present,
   the value of this key must be a CFData containing a CGRect (stored by
   value, not by reference). */

CG_EXTERN const CFStringRef kCGPDFContextTrimBox
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The art box for the document or for a given page. Optional; if present,
   the value of this key must be a CFData containing a CGRect (stored by
   value, not by reference). */

CG_EXTERN const CFStringRef kCGPDFContextArtBox
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/*** Keys for auxiliary info dictionary. ***/

/* The document's title. Optional; if present, the value of this key must be
   a CFString. */

CG_EXTERN const CFStringRef kCGPDFContextTitle
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The name of the person who created this document. Optional; if present,
   the value of this key must be a CFString. */

CG_EXTERN const CFStringRef kCGPDFContextAuthor
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The subject of a document. Optional; if present, the value of this key
   must be a CFString. */

CG_EXTERN const CFStringRef kCGPDFContextSubject
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* The keywords for this document. This key is optional. If the value of
   this key is a CFString, the /Keywords entry will be the specified string.
   If the value of this key is a CFArray, then it must be an array of
   CFStrings. The /Keywords entry will in this case be the concatenation of
   the specified strings separated by commas (","). In addition, an entry
   with the key "/AAPL:Keywords" will be stored in the document information
   dictionary; its value is an array consisting of each of the specified
   strings. The value of this key must be in one of the above forms;
   otherwise, this key is ignored. */

CG_EXTERN const CFStringRef kCGPDFContextKeywords
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* The name of the application that created the original data used to create
   this document. Optional; if present, the value of this key must be a
   CFString. */

CG_EXTERN const CFStringRef kCGPDFContextCreator
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The "owner password" of the PDF document. If this key is specified, the
   document will be encrypted using the value as the owner password;
   otherwise, the document will not be encrypted. The value of this key must
   be a CFStringRef which can be represented in ASCII encoding; only the
   first 32 bytes will be used for the password. There is no default value
   for this key.

   If the value of this key cannot be represented in ASCII, the document
   will not be created and the creation function will return NULL. */

CG_EXTERN const CFStringRef kCGPDFContextOwnerPassword
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The "user password" of the PDF document. If the document is encrypted,
   then the value of this key will be the user password for the document; if
   unspecified, the user password will be the empty string. The value of
   this key must be a CFStringRef which can be represented in ASCII
   encoding; only the first 32 bytes will be used for the password.

   If the value of this key cannot be represented in ASCII, the document
   will not be created and the creation function will return NULL. */

CG_EXTERN const CFStringRef kCGPDFContextUserPassword
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Specifies the encryption key length in bits; see Table 3.18 "Entries
   common to all encryption dictionaries", PDF Reference: Adobe PDF version
   1.5 (4th ed.) for more info. Optional; if present, the value of this key
   must be a CFNumber with value which is a multiple of 8 between 40 and
   128, inclusive. If this key is absent or invalid, the encryption key
   length defaults to 40 bits. */

CG_EXTERN const CFStringRef kCGPDFContextEncryptionKeyLength
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Used to specify whether the document allows printing when unlocked with
   the user password. The value of this key must be a CFBooleanRef. The
   default value of this key is "kCFBooleanTrue". */

CG_EXTERN const CFStringRef kCGPDFContextAllowsPrinting
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Used to specify whether the document allows copying when unlocked with
   the user password. The value of this key must be a CFBooleanRef. The
   default value of this key is "kCFBooleanTrue". */

CG_EXTERN const CFStringRef kCGPDFContextAllowsCopying
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* The document's PDF/X output intent. Optional; if present, the value of
   this key must be a CFDictionaryRef. The dictionary is added to the
   /OutputIntents entry in the PDF file's document catalog. The keys and
   values contained in the dictionary must match those specified in section
   9.10.4 of the PDF 1.4 specification, ISO/DIS 15930-3 document published
   by ISO/TC 130, and Adobe Technical Note #5413. */

CG_EXTERN const CFStringRef kCGPDFContextOutputIntent
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* The following keys are supported in the output intent dictionary:

   kCGPDFXOutputIntentSubtype ("S"): The output intent subtype. This key is
   required; the value of this key must be a CFString equal to "GTS_PDFX";
   otherwise, the dictionary is ignored. */

CG_EXTERN const CFStringRef kCGPDFXOutputIntentSubtype
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* kCGPDFXOutputConditionIdentifier ("OutputConditionIdentifier"): A string
   identifying the intended output device or production condition in a
   human- or machine-readable form. This key is required; the value of this
   key must be a CFString. For best results, the string should be
   representable losslessly in ASCII encoding. */

CG_EXTERN const CFStringRef kCGPDFXOutputConditionIdentifier
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* kCGPDFXOutputCondition ("OutputCondition"): A text string identifying the
   intended output device or production condition in a human-readable form.
   This key is optional; if present, the value of this key must be a
   CFString. */

CG_EXTERN const CFStringRef kCGPDFXOutputCondition
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* kCGPDFXRegistryName ("RegistryName"): A string identifying the registry
   in which the condition designated by `kCGPDFXOutputConditionIdentifier'
   is defined. This key is optional; if present, the value of this key must
   be a CFString. For best results, the string should be representable
   losslessly in ASCII encoding. */

CG_EXTERN const CFStringRef kCGPDFXRegistryName
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* kCGPDFXInfo ("Info"): A human-readable text string containing additional
   information about the intended target device or production condition.
   This key is required if the value of `kCGPDFXOutputConditionIdentifier'
   does not specify a standard production condition; it is optional
   otherwise. If present, the value of this key must be a CFString. */

CG_EXTERN const CFStringRef kCGPDFXInfo
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* kCGPDFXDestinationOutputProfile ("DestOutputProfile"): An ICC profile
   stream defining the transformation from the PDF document's source colors
   to output device colorants. This key is required if the value of
   `kCGPDFXOutputConditionIdentifier' does not specify a standard production
   condition; it is optional otherwise. If present, the value of this key
   must be a ICC-based CGColorSpaceRef. */

CG_EXTERN const CFStringRef kCGPDFXDestinationOutputProfile
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* The document's output intents. Optional; if present, the value must be a
   CFArrayRef containing one or more CFDictionaryRefs. The array is added to
   the PDF document in the /OutputIntents entry in the PDF file's document
   catalog. Each dictionary in the array must be of form specified above for
   the `kCGPDFContextOutputIntent' key, except that only the first
   dictionary in the array may contain the `kCGPDFXOutputIntentSubtype'
   ("S") key with a value of "GTS_PDFX". If both `kCGPDFContextOutputIntent'
   and `kCGPDFContextOutputIntents' keys are specified, the former is
   ignored. */

CG_EXTERN const CFStringRef kCGPDFContextOutputIntents
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

#endif /* CGPDFCONTEXT_H_ */
