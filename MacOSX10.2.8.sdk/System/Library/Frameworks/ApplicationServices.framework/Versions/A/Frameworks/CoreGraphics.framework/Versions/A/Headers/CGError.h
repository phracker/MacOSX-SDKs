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
    kCGErrorIllegalArgument = 1001,
    kCGErrorInvalidConnection = 1002,
    kCGErrorInvalidContext = 1003,
    kCGErrorCannotComplete = 1004,
    kCGErrorNameTooLong = 1005,
    kCGErrorNotImplemented = 1006,
    kCGErrorRangeCheck = 1007,
    kCGErrorTypeCheck = 1008,
    kCGErrorNoCurrentPoint = 1009,
    kCGErrorInvalidOperation = 1010,
    kCGErrorNoneAvailable = 1011,
    //	internal errors have taken 1012, 1013, and 1014

	kCGErrorApplicationRequiresNewerSystem = 1015,
		//	the application being launched says in it's bundle info that it requires a
		//	newer version of the system than is currently running.
	
	kCGErrorApplicationNotPermittedToExecute = 1016,
		//	Macintosh Manager is active, and this application is not permitted to run
	
    kCGErrorLast = kCGErrorApplicationRequiresNewerSystem    
};
typedef int32_t  CGError;

CG_EXTERN_C_END

#endif /* __CGERROR_H__ */
