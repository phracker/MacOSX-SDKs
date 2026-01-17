// Copyright © Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

// domain
GK_EXTERN_WEAK NSString * __nonnull const GKSessionErrorDomain API_DEPRECATED("No longer supported", ios(3.0, 18.4), macos(10.10,15.4), tvos(9.0, 18.4), visionos(1.0, 2.4), watchos(3.0, 11.4));

// code
typedef NS_ENUM(int, GKSessionError)
{
    GKSessionInvalidParameterError = 30500,
    GKSessionPeerNotFoundError = 30501,
    GKSessionDeclinedError = 30502,
    GKSessionTimedOutError = 30503,
    GKSessionCancelledError = 30504,
    GKSessionConnectionFailedError = 30505,
    GKSessionConnectionClosedError = 30506,
    GKSessionDataTooBigError = 30507,
    GKSessionNotConnectedError = 30508,
    GKSessionCannotEnableError = 30509,
    GKSessionInProgressError = 30510,

    GKSessionConnectivityError = 30201,
    GKSessionTransportError = 30202,
    GKSessionInternalError = 30203,
    GKSessionUnknownError = 30204,
    GKSessionSystemError = 30205
} API_DEPRECATED("No longer supported", ios(3.0, 7.0), tvos(9.0, 18.4), visionos(1.0, 1.0), watchos(3.0, 3.0)) API_UNAVAILABLE(macos);

