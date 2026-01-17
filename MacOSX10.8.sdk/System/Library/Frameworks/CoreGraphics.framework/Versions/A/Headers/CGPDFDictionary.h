/* CoreGraphics - CGPDFDictionary.h
 * Copyright (c) 2002-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGPDFDICTIONARY_H_
#define CGPDFDICTIONARY_H_

typedef struct CGPDFDictionary *CGPDFDictionaryRef;

#include <CoreGraphics/CGPDFArray.h>
#include <CoreGraphics/CGPDFObject.h>
#include <CoreGraphics/CGPDFStream.h>
#include <CoreGraphics/CGPDFString.h>

/* Return the number of entries in `dictionary'. */

CG_EXTERN size_t CGPDFDictionaryGetCount(CGPDFDictionaryRef dict)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and return the result
   in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFDictionaryGetObject(CGPDFDictionaryRef dict,
    const char *key, CGPDFObjectRef *value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's a
   boolean, return the result in `value'. Return true on success; false
   otherwise. */

CG_EXTERN bool CGPDFDictionaryGetBoolean(CGPDFDictionaryRef dict,
    const char *key, CGPDFBoolean *value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's an
   integer, return the result in `value'. Return true on success; false
   otherwise. */

CG_EXTERN bool CGPDFDictionaryGetInteger(CGPDFDictionaryRef dict,
    const char *key, CGPDFInteger *value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's a number
   (real or integer), return the result in `value'. Return true on success;
   false otherwise. */

CG_EXTERN bool CGPDFDictionaryGetNumber(CGPDFDictionaryRef dict,
    const char *key, CGPDFReal *value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's a name,
   return the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFDictionaryGetName(CGPDFDictionaryRef dict, const char *key,
    const char **value) CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's a string,
   return the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFDictionaryGetString(CGPDFDictionaryRef dict,
    const char *key, CGPDFStringRef *value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's an array,
   return the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFDictionaryGetArray(CGPDFDictionaryRef dict,
    const char *key, CGPDFArrayRef *value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's a
   dictionary, return the result in `value'. Return true on success; false
   otherwise. */

CG_EXTERN bool CGPDFDictionaryGetDictionary(CGPDFDictionaryRef dict,
    const char *key, CGPDFDictionaryRef *value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Look up the object associated with `key' in `dict' and, if it's a stream,
   return the result in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFDictionaryGetStream(CGPDFDictionaryRef dict,
    const char *key, CGPDFStreamRef *value)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* The callback for `CGPDFDictionaryApplyFunction'. `key' is the current
   key, `value' is the value for `key', and `info' is the parameter passed
   to `CGPDFDictionaryApplyFunction'. */

typedef void (*CGPDFDictionaryApplierFunction)(const char *key,
    CGPDFObjectRef value, void *info);

/* Enumerate all of the keys in `dict', calling `function' once for each
   key/value pair. Passes the current key, the associated value, and `info'
   to `function'. */

CG_EXTERN void CGPDFDictionaryApplyFunction(CGPDFDictionaryRef dict,
    CGPDFDictionaryApplierFunction function, void *info)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

#endif /* CGPDFDICTIONARY_H_ */
