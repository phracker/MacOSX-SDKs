/*
 *  GKSessionError.h
 *  GameKit
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

// domain
GK_EXTERN_WEAK NSString * __nonnull const GKSessionErrorDomain;

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
}  NS_ENUM_DEPRECATED_IOS(3_0, 7_0);

