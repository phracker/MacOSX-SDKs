//
//  TKError.h
//  Copyright (c) 2013 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CryptoTokenKit/TKBase.h>

NS_ASSUME_NONNULL_BEGIN

TK_EXTERN NSString *const TKErrorDomain;

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

    TKErrorAuthenticationFailed NS_ENUM_DEPRECATED(10_10, 10_11, 9_0, 9_0, "Use TKErrorCodeAuthenticationFailed")
      = TKErrorCodeAuthenticationFailed,
    TKErrorObjectNotFound NS_ENUM_DEPRECATED(10_10, 10_11, 9_0, 9_0, "Use TKErrorCodeObjectNotFound")
      = TKErrorCodeObjectNotFound,
    TKErrorTokenNotFound NS_ENUM_DEPRECATED(10_10, 10_11, 9_0, 9_0, "Use TKErrorCodeTokenNotFound")
      = TKErrorCodeTokenNotFound,
};

NS_ASSUME_NONNULL_END
