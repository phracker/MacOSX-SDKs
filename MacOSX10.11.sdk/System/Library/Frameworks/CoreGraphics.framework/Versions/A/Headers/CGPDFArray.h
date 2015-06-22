/* CoreGraphics - CGPDFArray.h
 * Copyright (c) 2002-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGPDFARRAY_H_
#define CGPDFARRAY_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CGPDFArray *CGPDFArrayRef;

#include <CoreGraphics/CGPDFDictionary.h>
#include <CoreGraphics/CGPDFObject.h>
#include <CoreGraphics/CGPDFStream.h>
#include <CoreGraphics/CGPDFString.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

#/* Return the number of items in `array'. */

CG_EXTERN size_t CGPDFArrayGetCount(CGPDFArrayRef __nullable array)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and return the result in
   `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetObject(CGPDFArrayRef __nullable array, size_t index,
    CGPDFObjectRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a null, return
   true; otherwise, return false. */

CG_EXTERN bool CGPDFArrayGetNull(CGPDFArrayRef __nullable array, size_t index)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a boolean, return
   the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetBoolean(CGPDFArrayRef __nullable array,
    size_t index, CGPDFBoolean * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's an integer, return
   the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetInteger(CGPDFArrayRef __nullable array,
    size_t index, CGPDFInteger * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a number (real or
   integer), return the result in `value'. Return true on success; false
   otherwise. */

CG_EXTERN bool CGPDFArrayGetNumber(CGPDFArrayRef __nullable array,
    size_t index, CGPDFReal * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a name, return the
   result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetName(CGPDFArrayRef __nullable array,
    size_t index, const char * __nullable *  __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a string, return
   the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetString(CGPDFArrayRef __nullable array,
    size_t index, CGPDFStringRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's an array, return it
   in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetArray(CGPDFArrayRef __nullable array,
    size_t index, CGPDFArrayRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a dictionary,
   return it in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetDictionary(CGPDFArrayRef __nullable array,
    size_t index, CGPDFDictionaryRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object at `index' in `array' and, if it's a stream, return it
   in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFArrayGetStream(CGPDFArrayRef __nullable array,
    size_t index, CGPDFStreamRef __nullable * __nullable value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGPDFARRAY_H_ */
