//
//  SKError.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>



extern NSString * const SKErrorDomain NS_AVAILABLE(10_7, NA);

// error codes for the SKErrorDomain
enum {
    SKErrorUnknown,
    SKErrorClientInvalid,       // client is not allowed to issue the request, etc.
    SKErrorPaymentCancelled,    // user cancelled the request, etc.
    SKErrorPaymentInvalid,      // purchase identifier was invalid, etc.
    SKErrorPaymentNotAllowed    // this machine is not allowed to make the payment
};

