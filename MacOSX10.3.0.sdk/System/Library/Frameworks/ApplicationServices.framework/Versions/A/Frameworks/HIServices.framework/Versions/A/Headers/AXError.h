/*
 *  AXError.h
 *
 *  Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __AXERROR__
#define __AXERROR__

#ifdef __cplusplus
extern "C" {
#endif

#include <CoreFoundation/CoreFoundation.h>

enum {
    kAXErrorSuccess 				= 0,
    kAXErrorFailure				= -25200,
    kAXErrorIllegalArgument			= -25201,
    kAXErrorInvalidUIElement			= -25202,
    kAXErrorInvalidUIElementObserver		= -25203,
    kAXErrorCannotComplete			= -25204,
    kAXErrorAttributeUnsupported		= -25205,
    kAXErrorActionUnsupported			= -25206,
    kAXErrorNotificationUnsupported		= -25207,
    kAXErrorNotImplemented			= -25208,
    kAXErrorNotificationAlreadyRegistered	= -25209,
    kAXErrorNotificationNotRegistered		= -25210,
    kAXErrorAPIDisabled				= -25211,
    kAXErrorNoValue				= -25212,
    kAXErrorParameterizedAttributeUnsupported	= -25213
};
typedef SInt32 AXError;


#ifdef __cplusplus
}
#endif

#endif // __AXERROR__
