/* CoreGraphics - CGError.h
   Copyright (c) 2000-2009 Apple Inc.
   All rights reserved. */

#ifndef CGERROR_H_
#define CGERROR_H_

#include <CoreGraphics/CGBase.h>
#include <stdint.h>

/* Types used for errors and error handlers. */

enum _CGError {
  kCGErrorSuccess = 0,
  kCGErrorFailure = 1000,
  kCGErrorIllegalArgument = 1001,
  kCGErrorInvalidConnection = 1002,
  kCGErrorInvalidContext = 1003,
  kCGErrorCannotComplete = 1004,
  kCGErrorNotImplemented = 1006,
  kCGErrorRangeCheck = 1007,
  kCGErrorTypeCheck = 1008,
  kCGErrorInvalidOperation = 1010,
  kCGErrorNoneAvailable = 1011,

  /* Obsolete errors. */
  kCGErrorNameTooLong = 1005,
  kCGErrorNoCurrentPoint = 1009,
  kCGErrorApplicationRequiresNewerSystem = 1015,
  kCGErrorApplicationNotPermittedToExecute = 1016,
  kCGErrorApplicationIncorrectExecutableFormatFound = 1023,
  kCGErrorApplicationIsLaunching = 1024,
  kCGErrorApplicationAlreadyRunning = 1025,
  kCGErrorApplicationCanOnlyBeRunInOneSessionAtATime = 1026,
  kCGErrorClassicApplicationsMustBeLaunchedByClassic = 1027,
  kCGErrorForkFailed = 1028,
  kCGErrorRetryRegistration = 1029,
  kCGErrorFirst = 1000,
  kCGErrorLast = 1029
};
typedef int32_t CGError;

#endif /* CGERROR_H_ */
