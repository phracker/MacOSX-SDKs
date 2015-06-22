//
//  TKError.h
//  Copyright (c) 2013 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString *const TKErrorDomain;

typedef NS_ENUM(NSInteger, TKErrorCode) {
    TKErrorCodeNotImplemented        = -1,
    TKErrorCodeCommunicationError    = -2,
    TKErrorCodeCorruptedData         = -3,
    TKErrorCodeCanceledByUser        = -4,
    TKErrorAuthenticationFailed      = -5,
    TKErrorObjectNotFound            = -6,
    TKErrorTokenNotFound             = -7,
    TKErrorCodeBadParameter          = -8,
};

NS_ASSUME_NONNULL_END