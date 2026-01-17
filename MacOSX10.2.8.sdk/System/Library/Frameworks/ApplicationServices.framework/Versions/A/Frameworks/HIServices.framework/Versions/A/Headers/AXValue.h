/*
 *  AXValue.h
 *  Accessibility
 *
 *  Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __AXVALUE__
#define __AXVALUE__

#ifdef __cplusplus
extern "C" {
#endif

#include <HIServices/HIServices.h>
#include <CoreFoundation/CoreFoundation.h>

typedef enum {
    /* Types from CoreGraphics.h */
    kAXValueCGPointType = 1,
    kAXValueCGSizeType = 2,
    kAXValueCGRectType = 3,

    /* Types from CFBase.h */
    kAXValueCFRangeType = 4,

    /* Other */
    kAXValueIllegalType = 0

} AXValueType;


extern CFTypeRef 	AXValueCreate (AXValueType theType, const void *valuePtr);
extern AXValueType 	AXValueGetType(CFTypeRef value);

extern Boolean 		AXValueGetValue(CFTypeRef value, AXValueType theType, void *valuePtr);


#ifdef __cplusplus
}
#endif

#endif // __AXVALUE__