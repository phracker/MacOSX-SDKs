/*
 *  AXValue.h
 *  Accessibility
 *
 *  Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __AXVALUE__
#define __AXVALUE__

#include <AvailabilityMacros.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <CoreServices/CoreServices.h>
#include <CoreFoundation/CoreFoundation.h>

typedef enum {
    /* Types from CoreGraphics.h */
    kAXValueCGPointType = 1,
    kAXValueCGSizeType = 2,
    kAXValueCGRectType = 3,

    /* Types from CFBase.h */
    kAXValueCFRangeType = 4,
    
    /* Types from AXError.h */
    kAXValueAXErrorType = 5,

    /* Other */
    kAXValueIllegalType = 0

} AXValueType;

typedef const struct __AXValue *AXValueRef;

extern CFTypeID		AXValueGetTypeID() AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


extern AXValueRef 	AXValueCreate (AXValueType theType, const void *valuePtr);
extern AXValueType 	AXValueGetType(AXValueRef value);

extern Boolean 		AXValueGetValue(AXValueRef value, AXValueType theType, void *valuePtr);


#ifdef __cplusplus
}
#endif

#endif // __AXVALUE__
