/* CoreGraphics - CGPDFArray.h
 * Copyright (c) 2002-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGPDFARRAY_H_
#define CGPDFARRAY_H_

typedef struct CGPDFArray *CGPDFArrayRef;

#include <CoreGraphics/CGPDFDictionary.h>
#include <CoreGraphics/CGPDFObject.h>
#include <CoreGraphics/CGPDFStream.h>
#include <CoreGraphics/CGPDFString.h>

/* Return the number of items in `array'. */

CG_EXTERN size_t CGPDFArrayGetCount(CGPDFArrayRef array)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and return the result in
   `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetObject(CGPDFArrayRef array, size_t index,
    CGPDFObjectRef *value) CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a null, return
   true; otherwise, return false. */

CG_EXTERN bool CGPDFArrayGetNull(CGPDFArrayRef array, size_t index)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a boolean, return
   the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetBoolean(CGPDFArrayRef array, size_t index,
    CGPDFBoolean *value) CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's an integer, return
   the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetInteger(CGPDFArrayRef array, size_t index,
    CGPDFInteger *value) CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a number (real or
   integer), return the result in `value'. Return true on success; false
   otherwise. */

CG_EXTERN bool CGPDFArrayGetNumber(CGPDFArrayRef array, size_t index,
    CGPDFReal *value) CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a name, return the
   result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetName(CGPDFArrayRef array, size_t index,
    const char **value) CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a string, return
   the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetString(CGPDFArrayRef array, size_t index,
    CGPDFStringRef *value) CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's an array, return it
   in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetArray(CGPDFArrayRef array, size_t index,
    CGPDFArrayRef *value) CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a dictionary,
   return it in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetDictionary(CGPDFArrayRef array, size_t index,
    CGPDFDictionaryRef *value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a stream, return it
   in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetStream(CGPDFArrayRef array, size_t index,
    CGPDFStreamRef *value) CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

#endif /* CGPDFARRAY_H_ */
