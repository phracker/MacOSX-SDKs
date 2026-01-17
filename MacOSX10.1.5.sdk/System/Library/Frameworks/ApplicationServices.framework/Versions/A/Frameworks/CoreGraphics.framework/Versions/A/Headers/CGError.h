/*
 *  CGError.h
 *  CoreGraphics
 *
 *  Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 */
#ifndef __CGERROR_H__
#define __CGERROR_H__ 1

#include <CoreGraphics/CGBase.h>
#include <stdint.h>

CG_EXTERN_C_BEGIN

/* Types used for error and error handler */
enum _CGError {
    kCGErrorSuccess = 0,
    kCGErrorFirst = 1000,
    kCGErrorFailure = kCGErrorFirst,
    kCGErrorIllegalArgument,
    kCGErrorInvalidConnection,
    kCGErrorInvalidContext,
    kCGErrorCannotComplete,
    kCGErrorNameTooLong,
    kCGErrorNotImplemented,
    kCGErrorRangeCheck,
    kCGErrorTypeCheck,
    kCGErrorNoCurrentPoint,
    kCGErrorInvalidOperation,
    kCGErrorNoneAvailable,
    kCGErrorLast = kCGErrorNoneAvailable
};
typedef int32_t  CGError;

CG_EXTERN_C_END

#endif /* __CGERROR_H__ */
