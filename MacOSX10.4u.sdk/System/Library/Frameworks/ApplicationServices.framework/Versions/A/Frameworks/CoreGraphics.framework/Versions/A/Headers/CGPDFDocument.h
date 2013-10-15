/* CoreGraphics - CGPDFDocument.h
 * Copyright (c) 2000-2003 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGPDFDOCUMENT_H_
#define CGPDFDOCUMENT_H_

typedef struct CGPDFDocument *CGPDFDocumentRef;

#include <CoreGraphics/CGDataProvider.h> 
#include <CoreGraphics/CGGeometry.h> 
#include <CoreGraphics/CGPDFPage.h> 
#include <CoreFoundation/CFURL.h>

CG_EXTERN_C_BEGIN

/* Create a PDF document, using `provider' to obtain the document's
 * data. */

CG_EXTERN CGPDFDocumentRef CGPDFDocumentCreateWithProvider(CGDataProviderRef provider);

/* Create a PDF document from `url'. */

CG_EXTERN CGPDFDocumentRef CGPDFDocumentCreateWithURL(CFURLRef url);

/* Equivalent to `CFRetain(document)', except it doesn't crash (as CFRetain
 * does) if `document' is NULL. */

CG_EXTERN CGPDFDocumentRef CGPDFDocumentRetain(CGPDFDocumentRef document);

/* Equivalent to `CFRelease(document)', except it doesn't crash (as
 * CFRelease does) if `document' is NULL. */

CG_EXTERN void CGPDFDocumentRelease(CGPDFDocumentRef document);

/* Return the major and minor version numbers of `document'. */

CG_EXTERN void CGPDFDocumentGetVersion(CGPDFDocumentRef document, int *majorVersion, int *minorVersion) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return true if the PDF file associated with `document' is encrypted;
 * false otherwise.  If the PDF file is encrypted, then a password must be
 * supplied before certain operations are enabled; different passwords may
 * enable different operations. */

CG_EXTERN bool CGPDFDocumentIsEncrypted(CGPDFDocumentRef document) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Use `password' to decrypt `document' and grant permission for certain
 * operations.  Returns true if `password' is a valid password; false
 * otherwise. */

CG_EXTERN bool CGPDFDocumentUnlockWithPassword(CGPDFDocumentRef document, const char *password) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Return true if `document' is unlocked; false otherwise.  A document is
 * unlocked if it isn't encrypted, or if it is encrypted and a valid password
 * was previously specified with CGPDFDocumentUnlockWithPassword. */

CG_EXTERN bool CGPDFDocumentIsUnlocked(CGPDFDocumentRef document) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Return true if `document' allows printing; false otherwise.  Typically,
 * this function returns false only if the document is encrypted and the
 * document's current password doesn't grant permission to perform
 * printing. */

CG_EXTERN bool CGPDFDocumentAllowsPrinting(CGPDFDocumentRef document) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Return true if `document' allows copying; false otherwise.  Typically,
 * this function returns false only if the document is encrypted and the
 * document's current password doesn't grant permission to perform
 * copying. */

CG_EXTERN bool CGPDFDocumentAllowsCopying(CGPDFDocumentRef document) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Return the number of pages in `document'. */

CG_EXTERN size_t CGPDFDocumentGetNumberOfPages(CGPDFDocumentRef document);

/* Return the page corresponding to `pageNumber', or NULL if no such page
 * exists in the document.  Pages are numbered starting at 1. */

CG_EXTERN CGPDFPageRef CGPDFDocumentGetPage(CGPDFDocumentRef document, size_t pageNumber) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return the document catalog of `document'. */

CG_EXTERN CGPDFDictionaryRef CGPDFDocumentGetCatalog(CGPDFDocumentRef document) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return the info dictionary of `document'. */

CG_EXTERN CGPDFDictionaryRef CGPDFDocumentGetInfo(CGPDFDocumentRef document) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the "file identifier" of `document'. */

CG_EXTERN CGPDFArrayRef CGPDFDocumentGetID(CGPDFDocumentRef document) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the CFTypeID for CGPDFDocumentRefs. */

CG_EXTERN CFTypeID CGPDFDocumentGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* The following functions are deprecated in favor of the CGPDFPage API. */

/* DEPRECATED; return the media box of page number `page' in `document'. */

CG_EXTERN CGRect CGPDFDocumentGetMediaBox(CGPDFDocumentRef document, int page);

/* DEPRECATED; return the crop box of page number `page' in `document'. */

CG_EXTERN CGRect CGPDFDocumentGetCropBox(CGPDFDocumentRef document, int page);

/* DEPRECATED; return the bleed box of page number `page' in `document'. */

CG_EXTERN CGRect CGPDFDocumentGetBleedBox(CGPDFDocumentRef document, int page);

/* DEPRECATED; return the trim box of page number `page' in `document'. */

CG_EXTERN CGRect CGPDFDocumentGetTrimBox(CGPDFDocumentRef document, int page);

/* DEPRECATED; return the art box of page number `page' in `document'. */

CG_EXTERN CGRect CGPDFDocumentGetArtBox(CGPDFDocumentRef document, int page);

/* DEPRECATED; return the rotation angle (in degrees) of page number `page'
 * in `document'. */

CG_EXTERN int CGPDFDocumentGetRotationAngle(CGPDFDocumentRef document, int page);

CG_EXTERN_C_END

#endif	/* CGPDFDOCUMENT_H_ */
