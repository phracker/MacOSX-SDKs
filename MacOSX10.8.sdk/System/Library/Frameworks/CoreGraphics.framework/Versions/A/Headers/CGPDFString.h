/* CoreGraphics - CGPDFString.h
 * Copyright (c) 2002-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGPDFSTRING_H_
#define CGPDFSTRING_H_

typedef struct CGPDFString *CGPDFStringRef;

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFDate.h>
#include <CoreFoundation/CFString.h>

/* Return the length of `string'. */

CG_EXTERN size_t CGPDFStringGetLength(CGPDFStringRef string)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return a pointer to the bytes of `string'. */

CG_EXTERN const unsigned char *CGPDFStringGetBytePtr(CGPDFStringRef string)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return a CFString representing `string' as a "text string". See Section
   3.8.1 "Text Strings", PDF Reference: Adobe PDF version 1.6 (5th ed.) for
   more information. */

CG_EXTERN CFStringRef CGPDFStringCopyTextString(CGPDFStringRef string)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Convert `string' to a CFDate. See Section 3.8.3 "Dates", PDF Reference:
   Adobe PDF version 1.6 (5th ed.) for more information. */

CG_EXTERN CFDateRef CGPDFStringCopyDate(CGPDFStringRef string)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

#endif /* CGPDFSTRING_H_ */
