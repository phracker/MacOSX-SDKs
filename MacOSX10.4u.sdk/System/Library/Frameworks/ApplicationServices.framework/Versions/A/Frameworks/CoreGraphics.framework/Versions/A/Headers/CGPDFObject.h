/* CoreGraphics - CGPDFObject.h
 * Copyright (c) 2002-2004 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGPDFOBJECT_H_
#define CGPDFOBJECT_H_

#include <CoreGraphics/CGBase.h>

/* A type for boolean values. */

typedef unsigned char CGPDFBoolean;

/* A type for integer values. */

typedef long int CGPDFInteger;

/* A type for real values. */

typedef float CGPDFReal;

/* A type to hold any object. */

typedef union CGPDFObject *CGPDFObjectRef;

/* An identifier to describe an object's type. */

enum CGPDFObjectType {
    kCGPDFObjectTypeNull = 1,
    kCGPDFObjectTypeBoolean,
    kCGPDFObjectTypeInteger,
    kCGPDFObjectTypeReal,
    kCGPDFObjectTypeName,
    kCGPDFObjectTypeString,
    kCGPDFObjectTypeArray,
    kCGPDFObjectTypeDictionary,
    kCGPDFObjectTypeStream
};
typedef enum CGPDFObjectType CGPDFObjectType;

CG_EXTERN_C_BEGIN

/* Return the type of `object'. */

CG_EXTERN CGPDFObjectType CGPDFObjectGetType(CGPDFObjectRef object) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Get the value of `object'.  If the type of `object' is equal to `type',
 * then copy the value of `object' to `value' (if it's non-NULL) and return
 * true.  Otherwise, if the type of `object' is `kCGPDFObjectTypeInteger'
 * and `type' is equal to `kCGPDFObjectTypeReal', then convert the value of
 * `object' to floating point and copy the result to `value' (if it's
 * non-NULL) and return true. Otherwise, return false. */

CG_EXTERN bool CGPDFObjectGetValue(CGPDFObjectRef object, CGPDFObjectType type, void *value) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGPDFOBJECT_H_ */
