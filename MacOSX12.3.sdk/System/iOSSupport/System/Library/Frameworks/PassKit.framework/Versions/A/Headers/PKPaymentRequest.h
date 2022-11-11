//
//  PKPaymentRequest.h
//
//  Copyright (c) 2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PassKit/PKConstants.h>
#import <PassKit/PKDeferredPaymentSummaryItem.h>
#import <PassKit/PKRecurringPaymentSummaryItem.h>
#import <PassKit/PKPaymentSummaryItem.h>
#import <PassKit/PKShippingMethod.h>

#if TARGET_OS_IOS && !TARGET_OS_MACCATALYST
#import <AddressBook/ABRecord.h>
#endif // TARGET_OS_IOS

#ifndef __PKPAYMENTREQUEST_H__
#define __PKPAYMENTREQUEST_H__

@class PKContact;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, PKMerchantCapability) {
    PKMerchantCapability3DS                                  = 1UL << 0,   // Merchant supports 3DS
    PKMerchantCapabilityEMV                                  = 1UL << 1,   // Merchant supports EMV
    PKMerchantCapabilityCredit NS_ENUM_AVAILABLE(11_0, 9_0) = 1UL << 2,   // Merchant supports credit
    PKMerchantCapabilityDebit  NS_ENUM_AVAILABLE(11_0, 9_0) = 1UL << 3    // Merchant supports debit
} API_AVAILABLE(macos(11.0), ios(8.0), watchos(3.0));

typedef NS_OPTIONS(NSUInteger, PKAddressField) {
    PKAddressFieldNone                               = 0UL,      // No address fields required.
    PKAddressFieldPostalAddress                      = 1UL << 0, // Full street address including name, street, city, state/province, postal code, country.
    PKAddressFieldPhone                              = 1UL << 1,
    PKAddressFieldEmail                              = 1UL << 2,
    PKAddressFieldName NS_ENUM_AVAILABLE(11_0, 8_3) = 1UL << 3,
    PKAddressFieldAll                                = (PKAddressFieldPostalAddress|PKAddressFieldPhone|PKAddressFieldEmail|PKAddressFieldName)
} API_DEPRECATED("Use PKContactField and -requiredShippingContactFields / -requiredBillingContactFields", ios(8.0, 11.0), watchos(3.0, 4.0));

typedef NS_ENUM(NSUInteger, PKShippingType) {
    PKShippingTypeShipping,
    PKShippingTypeDelivery,
    PKShippingTypeStorePickup,
    PKShippingTypeServicePickup
}  API_AVAILABLE(macos(11.0), ios(8.3), watchos(3.0));

typedef NS_ENUM(NSUInteger, PKShippingContactEditingMode) {
    PKShippingContactEditingModeEnabled = 1,
    PKShippingContactEditingModeStorePickup
}  API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0));

// PKPaymentRequest defines an application's request to produce a payment instrument for the
// purchase of goods and services. It encapsulates information about the selling party's payment
// processing capabilities, an amount to pay, and the currency code.
API_AVAILABLE(macos(11.0), ios(8.0), watchos(3.0))
@interface PKPaymentRequest : NSObject

// The payment networks and platforms supported for in-app payment
+ (NSArray<PKPaymentNetwork> *)availableNetworks API_AVAILABLE(macos(11.0), ios(10.0), watchos(3.0));

// Convenience method to create a payment contact error with the supplied field
// You may optionally provide a localized description to be displayed to the user.
// Available display space for descriptions may be limited, so you should keep your messages concise
+ (NSError *)paymentContactInvalidErrorWithContactField:(PKContactField)field
                                   localizedDescription:(nullable NSString *)localizedDescription API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0));

// Convenience method to create a payment shipping address error with the supplied CNPostalAddressKey and description
+ (NSError *)paymentShippingAddressInvalidErrorWithKey:(NSString *)postalAddressKey
                                  localizedDescription:(nullable NSString *)localizedDescription API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0));

// Convenience method to create a payment billing address error with the supplied CNPostalAddressKey and description
+ (NSError *)paymentBillingAddressInvalidErrorWithKey:(NSString *)postalAddressKey
                                 localizedDescription:(nullable NSString *)localizedDescription API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0));

// Convenience method to create a payment shipping address service error with the supplied description
+ (NSError *)paymentShippingAddressUnserviceableErrorWithLocalizedDescription:(nullable NSString *)localizedDescription API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0));

// Convenience method to create a payment coupon code invalid error with the supplied description.
+ (NSError *)paymentCouponCodeInvalidErrorWithLocalizedDescription:(nullable NSString *)localizedDescription API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

// Convenience method to create a payment coupon code expired error with the supplied description.
+ (NSError *)paymentCouponCodeExpiredErrorWithLocalizedDescription:(nullable NSString *)localizedDescription API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

// Identifies the merchant, as previously agreed with Apple.  Must match one of the merchant
// identifiers in the application's entitlement.
@property (nonatomic, copy) NSString *merchantIdentifier;

// The merchant's ISO country code.
@property (nonatomic, copy) NSString *countryCode;

// The payment networks supported by the merchant, for example @[ PKPaymentNetworkVisa,
// PKPaymentNetworkMasterCard ].  This property constrains payment cards that may fund the payment.
@property (nonatomic, copy) NSArray<PKPaymentNetwork> *supportedNetworks;

// The payment processing capabilities of the merchant.
@property (nonatomic, assign) PKMerchantCapability merchantCapabilities;

// Indicates whether the merchant supports coupon code entry and validation. Defaults to NO.
@property (nonatomic, assign) BOOL supportsCouponCode API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos);

// An optional coupon code that is valid and has been applied to the payment request already.
@property (nonatomic, copy, nullable) NSString *couponCode API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos);

// Array of PKPaymentSummaryItem objects which should be presented to the user.
// The last item should be the total you wish to charge, and should not be pending
@property (nonatomic, copy) NSArray<PKPaymentSummaryItem *> *paymentSummaryItems;

// Currency code for this payment.
@property (nonatomic, copy) NSString *currencyCode;

// Indicates which billing contact fields the merchant requires in order to process a transaction.
// Currently only postal address may be requested for billing contact. For all other fields use -requiredShippingContactFields
@property (nonatomic, strong) NSSet<PKContactField> *requiredBillingContactFields API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0));

// Indicates which billing address fields are required. The default is PKAddressFieldNone.
// This property is deprecated and should not be used.
@property (nonatomic, assign) PKAddressField requiredBillingAddressFields API_DEPRECATED_WITH_REPLACEMENT("requiredBillingContactFields", ios(8.0, 11.0), watchos(2.0, 4.0));

// If the merchant already has a billing address on file, set it here.
@property (nonatomic, strong, nullable) PKContact *billingContact API_AVAILABLE(macos(11.0), ios(9.0), watchos(3.0));

// Indicates which shipping contact fields the merchant requires in order to process a transactions
//
@property (nonatomic, strong) NSSet<PKContactField> *requiredShippingContactFields API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0));

// Indicates which shipping address fields are required. The default is PKAddressFieldNone.
// This property is deprecated and should not be used
@property (nonatomic, assign) PKAddressField requiredShippingAddressFields API_DEPRECATED_WITH_REPLACEMENT("requiredShippingContactFields", ios(8.0, 11.0), watchos(2.0, 4.0));

// If the merchant already has a shipping address on file, set it here.
@property (nonatomic, strong, nullable) PKContact *shippingContact API_AVAILABLE(macos(11.0), ios(9.0), watchos(3.0));

// Shipping methods supported by the merchant.
@property (nonatomic, copy, nullable) NSArray<PKShippingMethod *> *shippingMethods;

// Indicates the display mode for the shipping (e.g, "Pick Up", "Ship To", "Deliver To"). Localized.
// The default is PKShippingTypeShipping
@property (nonatomic, assign) PKShippingType shippingType API_AVAILABLE(macos(11.0), ios(8.3), watchos(3.0));

// Indicates the editing mode for the shipping contact. The default is PKShippingContactEditingModeEnabled.
@property (nonatomic, assign) PKShippingContactEditingMode shippingContactEditingMode API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0));

// Optional merchant-supplied information about the payment request.  Examples of this are an order
// or cart identifier.  It will be signed and included in the resulting PKPaymentToken.
@property (nonatomic, copy, nullable) NSData *applicationData;

// Set of two-letter ISO 3166 country codes. When provided will filter the selectable payment passes to those
// issued in the supported countries.
@property (nonatomic, copy, nullable) NSSet<NSString *> *supportedCountries API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0));

#if TARGET_OS_IOS && !TARGET_OS_MACCATALYST
// These properties have been deprecated and should not be used.
@property (nonatomic, assign, nullable) ABRecordRef shippingAddress __WATCHOS_PROHIBITED API_DEPRECATED("ABRecordRef has been deprecated, and does not support all available address properties. You should migrate to shippingContact.", ios(8.0, 9.0));

@property (nonatomic, assign, nullable) ABRecordRef billingAddress __WATCHOS_PROHIBITED API_DEPRECATED("ABRecordRef has been deprecated, and does not support all available address properties. You should migrate to billingContact.", ios(8.0, 9.0));
#endif



@end

NS_ASSUME_NONNULL_END

#endif // __PKPAYMENTREQUEST_H__
