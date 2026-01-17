//
//  TKError.h
//  Copyright (c) 2013 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *const TKErrorDomain;

typedef NS_ENUM(NSInteger, TKErrorCode) {
    TKErrorCodeNotImplemented        = -1,
    TKErrorCodeCommunicationError    = -2,
    TKErrorCodeCorruptedData         = -3,
    TKErrorCodeCanceledByUser        = -4,
    TKErrorAuthenticationFailed      = -5,
    TKErrorObjectNotFound            = -6,
    TKErrorTokenNotFound             = -7,
};
