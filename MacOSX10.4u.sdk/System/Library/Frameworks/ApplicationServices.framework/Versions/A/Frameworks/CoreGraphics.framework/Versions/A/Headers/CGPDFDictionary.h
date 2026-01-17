/* CoreGraphics - CGPDFDictionary.h
 * Copyright (c) 2002-2004 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGPDFDICTIONARY_H_
#define CGPDFDICTIONARY_H_

typedef struct CGPDFDictionary *CGPDFDictionaryRef;

#include <CoreGraphics/CGPDFArray.h>
#include <CoreGraphics/CGPDFObject.h>
#include <CoreGraphics/CGPDFStream.h>
#include <CoreGraphics/CGPDFString.h>

CG_EXTERN_C_BEGIN

/* Return the number of entries in `dictionary'. */

CG_EXTERN size_t CGPDFDictionaryGetCount(CGPDFDictionaryRef dict) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Look up the object associated with `key' in `dict' and return the result
 * in `value'. Return true on success; false otherwise. */

CG_EXTERN bool CGPDFDictionaryGetObject(CGPDFDictionaryRef dict, const char *key, CGPDFObjectRef *value) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Look up the object associated with `key' in `dict' and, if it's a
 * boolean, return the result in `value'.  Return true on success; false
 * otherwise. */

CG_EXTERN bool CGPDFDictionaryGetBoolean(CGPDFDictionaryRef dict, const char *key, CGPDFBoolean *value) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Look up the object associated with `key' in `dict' and, if it's an
 * integer, return the result in `value'.  Return true on success; false
 * otherwise. */

CG_EXTERN bool CGPDFDictionaryGetInteger(CGPDFDictionaryRef dict, const char *key, CGPDFInteger *value) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Look up the object associated with `key' in `dict' and, if it's a number
 * (real or integer), return the result in `value'.  Return true on
 * success; false otherwise. */

CG_EXTERN bool CGPDFDictionaryGetNumber(CGPDFDictionaryRef dict, const char *key, CGPDFReal *value) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Look up the object associated with `key' in `dict' and, if it's a name,
 * return the result in `value'.  Return true on success; false
 * otherwise. */

CG_EXTERN bool CGPDFDictionaryGetName(CGPDFDictionaryRef dict, const char *key, const char **value) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Look up the object associated with `key' in `dict' and, if it's a
 * string, return the result in `value'.  Return true on success; false
 * otherwise. */

CG_EXTERN bool CGPDFDictionaryGetString(CGPDFDictionaryRef dict, const char *key, CGPDFStringRef *value) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Look up the object associated with `key' in `dict' and, if it's an
 * array, return the result in `value'.  Return true on success; false
 * otherwise. */

CG_EXTERN bool CGPDFDictionaryGetArray(CGPDFDictionaryRef dict, const char *key, CGPDFArrayRef *value) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Look up the object associated with `key' in `dict' and, if it's a
 * dictionary, return the result in `value'.  Return true on success; false
 * otherwise. */

CG_EXTERN bool CGPDFDictionaryGetDictionary(CGPDFDictionaryRef dict, const char *key, CGPDFDictionaryRef *value) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Look up the object associated with `key' in `dict' and, if it's a
 * stream, return the result in `value'. Return true on success; false
 * otherwise. */

CG_EXTERN bool CGPDFDictionaryGetStream(CGPDFDictionaryRef dict, const char *key, CGPDFStreamRef *value) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* The callback for `CGPDFDictionaryApplyFunction'.  `key' is the current
 * key, `value' is the value for `key', and `info' is the parameter passed
 * to `CGPDFDictionaryApplyFunction'. */

typedef void (*CGPDFDictionaryApplierFunction)(const char *key, CGPDFObjectRef value, void *info);

/* Enumerate all of the keys in `dict', calling `function' once for each
 * key/value pair.  Passes the current key, the associated value, and
 * `info' to `function'. */

void CGPDFDictionaryApplyFunction(CGPDFDictionaryRef dict, CGPDFDictionaryApplierFunction function, void *info) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGPDFDICTIONARY_H_ */
