/* CoreGraphics - CGPDFString.h
 * Copyright (c) 2002-2004 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGPDFSTRING_H_
#define CGPDFSTRING_H_

typedef struct CGPDFString *CGPDFStringRef;

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFDate.h>
#include <CoreFoundation/CFString.h>

CG_EXTERN_C_BEGIN

/* Return the length of `string'. */

CG_EXTERN size_t CGPDFStringGetLength(CGPDFStringRef string) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return a pointer to the bytes of `string'. */

CG_EXTERN const unsigned char *CGPDFStringGetBytePtr(CGPDFStringRef string) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return a CFString representing `string' as a "text string".  See Section
 * 3.8.1 "Text Strings", PDF Reference: Adobe PDF version 1.4 (3rd ed.)
 * for more information. */

CG_EXTERN CFStringRef CGPDFStringCopyTextString(CGPDFStringRef string) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Convert `string' to a CFDate.  See Section 3.8.3 "Dates", PDF Reference:
 * Adobe PDF version 1.4 (3rd ed.)  for more information. */

CG_EXTERN CFDateRef CGPDFStringCopyDate(CGPDFStringRef string) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGPDFSTRING_H_ */
