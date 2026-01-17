#if !__has_include(<PassKitCore/PKIdentityError.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKIdentityError.h
//    PassKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//


#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Error domain for identity errors.
extern NSErrorDomain const PKIdentityErrorDomain API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, tvos);

/// Identity error codes.
typedef NS_ERROR_ENUM(PKIdentityErrorDomain, PKIdentityError) {
    /// Catch-all for all errors without a specific error code.
    PKIdentityErrorUnknown = 0,

    /// Returned if the request originates from an unsupported device.
    PKIdentityErrorNotSupported = 1,

    /// Returned if the sheet was cancelled.
    PKIdentityErrorCancelled = 2,

    /// Returned if a request cannot be processed because
    /// the network is not available.
    PKIdentityErrorNetworkUnavailable = 3,

    /// Returned if no supported elements were requested.
    PKIdentityErrorNoElementsRequested = 4,

    /// Returned if a request is made but another request is already
    /// in progress.
    PKIdentityErrorRequestAlreadyInProgress = 5,

    /// Returned if the caller-supplied nonce is too large or otherwise unsuitable.
    PKIdentityErrorInvalidNonce = 6,

    /// Returned if an element requested by the caller is invalid.
    PKIdentityErrorInvalidElement = 7,

    /// Returned if the document descriptor region is not supported.
    PKIdentityErrorRegionNotSupported API_AVAILABLE(ios(18.0)) = 8,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_END

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKIdentityError.h>
#endif