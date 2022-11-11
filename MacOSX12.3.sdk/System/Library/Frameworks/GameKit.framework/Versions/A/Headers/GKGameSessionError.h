//
//  GKGameSessionError.h
//  Game Center
//
//  Copyright 2016-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString * __nonnull GKGameSessionErrorDomain API_DEPRECATED("GKGameSession is deprecated, use real-time and turn-based matchmaking APIs instead.", ios(10.0, 12.0), tvos(10.0, 12.0), macosx(10.12, 10.14)) API_UNAVAILABLE(watchos);

typedef  NS_ENUM(NSInteger, GKGameSessionErrorCode) {
    GKGameSessionErrorUnknown = 1,
    GKGameSessionErrorNotAuthenticated = 2,
    GKGameSessionErrorSessionConflict = 3,
    GKGameSessionErrorSessionNotShared = 4,
    GKGameSessionErrorConnectionCancelledByUser = 5,
    GKGameSessionErrorConnectionFailed = 6,
    GKGameSessionErrorSessionHasMaxConnectedPlayers = 7,
    GKGameSessionErrorSendDataNotConnected = 8,
    GKGameSessionErrorSendDataNoRecipients = 9,
    GKGameSessionErrorSendDataNotReachable = 10,
    GKGameSessionErrorSendRateLimitReached = 11,
    GKGameSessionErrorBadContainer = 12,
    GKGameSessionErrorCloudQuotaExceeded = 13,
    GKGameSessionErrorNetworkFailure = 14,
    GKGameSessionErrorCloudDriveDisabled = 15,
    GKGameSessionErrorInvalidSession = 16,
} API_DEPRECATED("GKGameSession is deprecated, use real-time and turn-based matchmaking APIs instead.", ios(10.0, 12.0), tvos(10.0, 12.0), macosx(10.12, 10.14)) API_UNAVAILABLE(watchos);
