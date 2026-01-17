//
//  SKError.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>


NS_ASSUME_NONNULL_BEGIN

SK_EXTERN NSString * const SKErrorDomain NS_AVAILABLE_MAC(10_7);

// error codes for the SKErrorDomain
typedef NS_ENUM(NSInteger, SKErrorCode) {
    SKErrorUnknown,
    SKErrorClientInvalid,       // client is not allowed to issue the request, etc.
    SKErrorPaymentCancelled,    // user cancelled the request, etc.
    SKErrorPaymentInvalid,      // purchase identifier was invalid, etc.
    SKErrorPaymentNotAllowed    // this machine is not allowed to make the payment
};

NS_ASSUME_NONNULL_END
