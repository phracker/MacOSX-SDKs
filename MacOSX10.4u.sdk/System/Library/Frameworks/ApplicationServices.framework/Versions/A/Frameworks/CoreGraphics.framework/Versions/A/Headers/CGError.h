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
    /*	internal errors have taken 1012, 1013, and 1014 */

	kCGErrorApplicationRequiresNewerSystem = 1015,
		/*	the application being launched says in it's bundle info that it requires a */
		/*	newer version of the system than is currently running. */
	
	kCGErrorApplicationNotPermittedToExecute = 1016,
		/*	Macintosh Manager is active, and this application is not permitted to run */
	
	kCGErrorApplicationIncorrectExecutableFormatFound = 1023,
		/*	the application being launched does not have any executable code for the */
		/*	current system. */
	
	kCGErrorApplicationIsLaunching = 1024,
		/* The application is in the process of launching, but hasn't checked in yet.
		   Any launch data provided will be given to the application when it does
		   check in. */
	
	kCGErrorApplicationAlreadyRunning = 1025,
		/*	The application being launched was already running ( and had already checked
		    in ) and so any launch data provided can not be delivered to in by CPS */

	kCGErrorApplicationCanOnlyBeRunInOneSessionAtATime = 1026,
		/*	The application being launched is incompatible with multiple user sessions,
			and is already running in another session by another user. */
			
	kCGErrorClassicApplicationsMustBeLaunchedByClassic = 1027,
		/*	To avoid deadlock, Classic can't launch another Classic application by going
			thru CPS.  This error gets returned in that case, and it signals TruBlueEnvironment
			that it must handle this launch on its own. */

	kCGErrorForkFailed = 1028,
		/*	CPS was unable to fork a new process in order to launch an application. */

    kCGErrorLast = kCGErrorForkFailed
};
typedef int32_t  CGError;

CG_EXTERN_C_END

#endif /* __CGERROR_H__ */
