//
//  WCError.h
//  WatchConnectivity
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchConnectivity/WCDefines.h>

NS_ASSUME_NONNULL_BEGIN

WC_EXTERN NSString * const WCErrorDomain NS_AVAILABLE_IOS(9.0);

/** These are the possible error codes that can be returned from the WatchConnectivity APIs. */
typedef NS_ENUM(NSInteger, WCErrorCode) {
	WCErrorCodeGenericError                         = 7001,
	WCErrorCodeSessionNotSupported                  = 7002,
	WCErrorCodeSessionMissingDelegate               = 7003,
	WCErrorCodeSessionNotActivated                  = 7004,
	WCErrorCodeDeviceNotPaired                      = 7005,
	WCErrorCodeWatchAppNotInstalled                 = 7006,
	WCErrorCodeNotReachable                         = 7007,
	WCErrorCodeInvalidParameter                     = 7008,
	WCErrorCodePayloadTooLarge                      = 7009,
	WCErrorCodePayloadUnsupportedTypes              = 7010,
	WCErrorCodeMessageReplyFailed                   = 7011,
	WCErrorCodeMessageReplyTimedOut                 = 7012,
	WCErrorCodeFileAccessDenied                     = 7013,
	WCErrorCodeDeliveryFailed                       = 7014,
	WCErrorCodeInsufficientSpace                    = 7015,
	WCErrorCodeSessionInactive                      __IOS_AVAILABLE(9.3) __WATCHOS_AVAILABLE(2.2) = 7016,
	WCErrorCodeTransferTimedOut                     __IOS_AVAILABLE(9.3) __WATCHOS_AVAILABLE(2.2) = 7017,
	WCErrorCodeCompanionAppNotInstalled             __IOS_AVAILABLE(13.0) __WATCHOS_AVAILABLE(6.0) = 7018,
	WCErrorCodeWatchOnlyApp                         __IOS_AVAILABLE(13.0) __WATCHOS_AVAILABLE(6.0) = 7019,
} NS_ENUM_AVAILABLE_IOS(9.0);

NS_ASSUME_NONNULL_END
