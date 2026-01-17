//
//  TKError.h
//  Copyright (c) 2013 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CryptoTokenKit/TKBase.h>

NS_ASSUME_NONNULL_BEGIN

TK_EXTERN NSString *const TKErrorDomain
API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0), watchos(2.0));

API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0), watchos(2.0))
typedef NS_ENUM(NSInteger, TKErrorCode) {
    TKErrorCodeNotImplemented        = -1,
    TKErrorCodeCommunicationError    = -2,
    TKErrorCodeCorruptedData         = -3,
    TKErrorCodeCanceledByUser        = -4,
    TKErrorCodeAuthenticationFailed  = -5,
    TKErrorCodeObjectNotFound        = -6,
    TKErrorCodeTokenNotFound         = -7,
    TKErrorCodeBadParameter          = -8,
    TKErrorCodeAuthenticationNeeded  = -9,

    TKErrorAuthenticationFailed API_DEPRECATED_WITH_REPLACEMENT("TKErrorCodeAuthenticationFailed", macos(10.10, 10.11), ios(9.0, 9.0), tvos(9.0, 9.0), watchos(2.0, 2.0)) = TKErrorCodeAuthenticationFailed,
    TKErrorObjectNotFound API_DEPRECATED_WITH_REPLACEMENT("TKErrorCodeObjectNotFound", macos(10.10, 10.11), ios(9.0, 9.0), tvos(9.0, 9.0), watchos(2.0, 2.0)) = TKErrorCodeObjectNotFound,
    TKErrorTokenNotFound API_DEPRECATED_WITH_REPLACEMENT("TKErrorCodeTokenNotFound", macos(10.10, 10.11), ios(9.0, 9.0), tvos(9.0, 9.0), watchos(2.0, 2.0)) = TKErrorCodeTokenNotFound,
};

NS_ASSUME_NONNULL_END
