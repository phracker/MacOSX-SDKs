/*
 *  CMError.h
 *  CoreMotion
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */

/*
 *  CMError
 *
 *  Discussion:
 *    Error returned as code to NSError from CoreMotion.
 */
typedef enum {
	CMErrorNULL = 100,
	CMErrorDeviceRequiresMovement,
	CMErrorTrueNorthNotAvailable,
	CMErrorUnknown,
	CMErrorMotionActivityNotAvailable,
	CMErrorMotionActivityNotAuthorized,
	CMErrorMotionActivityNotEntitled,
	CMErrorInvalidParameter,
	CMErrorInvalidAction,
	CMErrorNotAvailable,
	CMErrorNotEntitled,
	CMErrorNotAuthorized,
	CMErrorNilData,
	CMErrorSize
} CMError;
