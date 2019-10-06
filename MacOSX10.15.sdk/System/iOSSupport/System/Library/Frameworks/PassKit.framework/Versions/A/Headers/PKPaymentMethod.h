//
//  PKPaymentMethod.h
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#ifndef __PKPAYMENTMETHOD_H
#define __PKPAYMENTMETHOD_H

#import <Foundation/Foundation.h>
#import <PassKit/PKConstants.h>

@class CNContact;
@class PKPaymentPass;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(ios(9.0), watchos(3.0))
@interface PKPaymentMethod : NSObject

typedef NS_ENUM(NSUInteger, PKPaymentMethodType) {
    PKPaymentMethodTypeUnknown = 0,
    PKPaymentMethodTypeDebit,
    PKPaymentMethodTypeCredit,
    PKPaymentMethodTypePrepaid,
    PKPaymentMethodTypeStore
} API_AVAILABLE(ios(9.0), watchos(3.0));

// A string describing the instrument that's suitable for display
// This property will be nil prior to the user authorizing the payment
@property (nonatomic, copy, readonly, nullable) NSString *displayName;

// The payment network that backs the instrument. Suitable for display.
// This property will be nil prior to the user authorizing the payment
@property (nonatomic, copy, readonly, nullable) PKPaymentNetwork network;

// The underlying instrument type (Credit, Debit, etc)
@property (nonatomic, readonly) PKPaymentMethodType type;

// The payment pass - will only be provided if your app is entitled to view the pass in question
@property (nonatomic, copy, readonly, nullable) PKPaymentPass *paymentPass;

// A partially redacted billing address. Only available if no shipping address info was requested.
@property (nonatomic, copy, readonly, nullable) CNContact *billingAddress API_AVAILABLE(ios(13.0), watchos(6.0));

@end

NS_ASSUME_NONNULL_END

#endif // End __PKPAYMENTMETHOD_H

