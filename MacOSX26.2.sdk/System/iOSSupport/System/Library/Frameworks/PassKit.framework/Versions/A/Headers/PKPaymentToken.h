#if !__has_include(<PassKitCore/PKPaymentToken.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKPaymentToken.h
//    PassKit
//  Copyright (c) 2014, Apple Inc. All rights reserved.
//

#ifndef __PKPAYMENTTOKEN_H
#define __PKPAYMENTTOKEN_H

#import <Foundation/Foundation.h>

@class PKPaymentMethod;

NS_ASSUME_NONNULL_BEGIN

// Contains the user's payment credentials, encrypted to the merchant.
API_AVAILABLE(macos(11.0), ios(8.0), watchos(3.0))
@interface PKPaymentToken : NSObject

// Describes the properties of the underlying payment instrument selected to fund the payment
@property (nonatomic, strong, readonly) PKPaymentMethod *paymentMethod API_AVAILABLE(macos(11.0), ios(9.0), watchos(3.0));

// A string that describes the payment instrument the user has selected to fund the payment.
// Suitable for display, e.g. "Amex 1234".
@property (nonatomic, copy, readonly) NSString *paymentInstrumentName API_DEPRECATED("Use paymentMethod instead", ios(8.0, 9.0)) __WATCHOS_PROHIBITED;

// Payment network for the card that funds the payment.
@property (nonatomic, copy, readonly) NSString *paymentNetwork API_DEPRECATED("Use paymentMethod instead", ios(8.0, 9.0)) __WATCHOS_PROHIBITED;

// A string that describes a globally unique identifier for this transaction that can be used
// for receipt purposes.
@property (nonatomic, copy, readonly) NSString *transactionIdentifier;

// UTF-8 encoded JSON dictionary of encrypted payment data.  Ready for transmission to
// merchant's e-commerce backend for decryption and submission to a payment processor's
// gateway.
@property (nonatomic, copy, readonly) NSData *paymentData;

@end

NS_ASSUME_NONNULL_END

#endif

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKPaymentToken.h>
#endif