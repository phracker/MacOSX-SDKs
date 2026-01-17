/* CoreGraphics - CGPDFString.h
 * Copyright (c) 2002-2003 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGPDFSTRING_H_
#define CGPDFSTRING_H_

typedef struct CGPDFString *CGPDFStringRef;

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFString.h>

CG_EXTERN_C_BEGIN

/* Return the length of `string'. */

size_t CGPDFStringGetLength(CGPDFStringRef string);

/* Return a pointer to the bytes of `string'. */

const unsigned char *CGPDFStringGetBytePtr(CGPDFStringRef string);

/* Return a CFString representing `string' as a "text string".  See Section
 * 3.8.1 "Text Strings", PDF Reference: Adobe PDF version 1.4 (3rd ed.)
 * for more information. */

CFStringRef CGPDFStringCopyTextString(CGPDFStringRef string);

CG_EXTERN_C_END

#endif	/* CGPDFSTRING_H_ */
