//
//  PKPayment.h
//
//  Copyright (c) 2014 Apple, Inc. All rights reserved.
//

#if TARGET_OS_IOS && !TARGET_OS_MACCATALYST
#import <AddressBook/ABRecord.h>
#endif // TARGET_OS_IOS && !TARGET_OS_MACCATALYST
#import <PassKit/PKPaymentToken.h>

@class PKShippingMethod;
@class PKContact;

// PKPayment represents the result of a payment request.  Successful payments
// have a PKPaymentToken which contains a payment credential encrypted to the merchant
// identifier specified in the request, and when requested, the user's shipping address
// and chosen shipping method.
API_AVAILABLE(ios(8.0), watchos(3.0))
@interface PKPayment : NSObject

// A PKPaymentToken which contains an encrypted payment credential.
@property (nonatomic, strong, readonly, nonnull) PKPaymentToken *token;

// The full billing address that the user selected for this transaction.  Fields are
// constrained to those specified in the requiredBillingAddressFields property of the original
// PKPaymentRequest object.  This property is only set when the application has set
// the requiredBillingAddressFields property of the PKPaymentRequest.
@property (nonatomic, strong, readonly, nullable) PKContact *billingContact API_AVAILABLE(ios(9.0), watchos(3.0));

#if TARGET_OS_IOS && !TARGET_OS_MACCATALYST
@property (nonatomic, assign, readonly, nullable) ABRecordRef billingAddress API_DEPRECATED("Use billingContact instead", ios(8.0, 9.0)) __WATCHOS_PROHIBITED;
#endif // TARGET_OS_IOS && !TARGET_OS_MACCATALYST

// The full shipping address that the user selected for this transaction.  Fields are
// constrained to those specified in the requiredShippingAddressFields property of the original
// PKPaymentRequest object.  This property is only set when the application has set
// the requiredShippingAddressFields property of the PKPaymentRequest.
@property (nonatomic, strong, readonly, nullable) PKContact *shippingContact API_AVAILABLE(ios(9.0), watchos(3.0));

#if TARGET_OS_IOS && !TARGET_OS_MACCATALYST
@property (nonatomic, assign, readonly, nullable) ABRecordRef shippingAddress API_DEPRECATED("Use shippingContact instead", ios(8.0, 9.0)) __WATCHOS_PROHIBITED;
#endif // TARGET_OS_IOS && !TARGET_OS_MACCATALYST

// The shipping method that the user chose.  This property is only set when the
// application has set the shippingMethods property of the PKPaymentRequest.
@property (nonatomic, strong, readonly, nullable) PKShippingMethod *shippingMethod;

@end

