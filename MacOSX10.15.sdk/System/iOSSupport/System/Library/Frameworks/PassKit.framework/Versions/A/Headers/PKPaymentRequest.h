//
//  PKPaymentRequest.h
//
//  Copyright (c) 2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PassKit/PKConstants.h>

#if TARGET_OS_IOS && !TARGET_OS_MACCATALYST
#import <AddressBook/ABRecord.h>
#endif // TARGET_OS_IOS

#import <PassKit/PKConstants.h>

#ifndef __PKPAYMENTREQUEST_H__
#define __PKPAYMENTREQUEST_H__

@class PKContact;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, PKMerchantCapability) {
    PKMerchantCapability3DS                                  = 1UL << 0,   // Merchant supports 3DS
    PKMerchantCapabilityEMV                                  = 1UL << 1,   // Merchant supports EMV
    PKMerchantCapabilityCredit NS_ENUM_AVAILABLE_IOS(9_0) = 1UL << 2,   // Merchant supports credit
    PKMerchantCapabilityDebit  NS_ENUM_AVAILABLE_IOS(9_0) = 1UL << 3    // Merchant supports debit
} API_AVAILABLE(ios(8.0), watchos(3.0));

typedef NS_OPTIONS(NSUInteger, PKAddressField) {
    PKAddressFieldNone                               = 0UL,      // No address fields required.
    PKAddressFieldPostalAddress                      = 1UL << 0, // Full street address including name, street, city, state/province, postal code, country.
    PKAddressFieldPhone                              = 1UL << 1,
    PKAddressFieldEmail                              = 1UL << 2,
    PKAddressFieldName NS_ENUM_AVAILABLE_IOS(8_3) = 1UL << 3,
    PKAddressFieldAll                                = (PKAddressFieldPostalAddress|PKAddressFieldPhone|PKAddressFieldEmail|PKAddressFieldName)
} API_DEPRECATED("Use PKContactField and -requiredShippingContactFields / -requiredBillingContactFields", ios(8.0, 11.0), watchos(3.0, 4.0));

typedef NS_ENUM(NSUInteger, PKShippingType) {
    PKShippingTypeShipping,
    PKShippingTypeDelivery,
    PKShippingTypeStorePickup,
    PKShippingTypeServicePickup
}  API_AVAILABLE(ios(8.3), watchos(3.0));

typedef NS_ENUM(NSUInteger, PKPaymentSummaryItemType) {
    PKPaymentSummaryItemTypeFinal,      // The payment summary item's amount is known to be correct
    PKPaymentSummaryItemTypePending     // The payment summary item's amount is estimated or unknown - e.g, a taxi fare
}  API_AVAILABLE(ios(9.0), watchos(3.0));

// PKPaymentSummaryItem Defines a line-item for a payment such as tax, shipping, or discount.
API_AVAILABLE(ios(8.0), watchos(3.0))
@interface PKPaymentSummaryItem : NSObject

+ (instancetype)summaryItemWithLabel:(NSString *)label amount:(NSDecimalNumber *)amount;
+ (instancetype)summaryItemWithLabel:(NSString *)label amount:(NSDecimalNumber *)amount type:(PKPaymentSummaryItemType)type API_AVAILABLE(ios(9.0), watchos(3.0));

// A short localized description of the item, e.g. "Tax" or "Gift Card".
@property (nonatomic, copy) NSString *label;

// Same currency as the enclosing PKPaymentRequest.  Negative values are permitted, for example when
// redeeming a coupon. An amount is always required unless the summary item's type is set to pending
@property (nonatomic, copy) NSDecimalNumber *amount;

// Defaults to PKPaymentSummaryItemTypeFinal
// Set to PKPaymentSummaryItemTypePending if the amount of the item is not known at this time
@property (nonatomic, assign) PKPaymentSummaryItemType type API_AVAILABLE(ios(9.0), watchos(3.0));

@end

// Defines a shipping method for delivering physical goods.
API_AVAILABLE(ios(8.0), watchos(3.0))
@interface PKShippingMethod : PKPaymentSummaryItem

// Application-defined unique identifier for this shipping method.  The application will receive this
// in paymentAuthorizationViewController:didAuthorizePayment:completion:.
@property (nonatomic, copy, nullable) NSString *identifier;

// Additional localized information about the shipping method, e.g. "Ships in 24 hours" or
// "Arrives Friday April 4."
@property (nonatomic, copy, nullable) NSString *detail;

@end

// PKPaymentRequest defines an application's request to produce a payment instrument for the
// purchase of goods and services. It encapsulates information about the selling party's payment
// processing capabilities, an amount to pay, and the currency code.
API_AVAILABLE(ios(8.0), watchos(3.0))
@interface PKPaymentRequest : NSObject

// The payment networks and platforms supported for in-app payment
+ (NSArray<PKPaymentNetwork> *)availableNetworks API_AVAILABLE(ios(10.0), watchos(3.0));

// Convenience method to create a payment contact error with the supplied field
// You may optionally provide a localized description to be displayed to the user.
// Available display space for descriptions may be limited, so you should keep your messages concise
+ (NSError *)paymentContactInvalidErrorWithContactField:(PKContactField)field
                                   localizedDescription:(nullable NSString *)localizedDescription API_AVAILABLE(ios(11.0), watchos(4.0));

// Convenience method to create a payment shipping address error with the supplied CNPostalAddressKey and description
+ (NSError *)paymentShippingAddressInvalidErrorWithKey:(NSString *)postalAddressKey
                                  localizedDescription:(nullable NSString *)localizedDescription API_AVAILABLE(ios(11.0), watchos(4.0));

// Convenience method to create a payment billing address error with the supplied CNPostalAddressKey and description
+ (NSError *)paymentBillingAddressInvalidErrorWithKey:(NSString *)postalAddressKey
                                 localizedDescription:(nullable NSString *)localizedDescription API_AVAILABLE(ios(11.0), watchos(4.0));

// Convenience method to create a payment shipping address service error with the supplied description
+ (NSError *)paymentShippingAddressUnserviceableErrorWithLocalizedDescription:(nullable NSString *)localizedDescription API_AVAILABLE(ios(11.0), watchos(4.0));

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

// Array of PKPaymentSummaryItem objects which should be presented to the user.
// The last item should be the total you wish to charge, and should not be pending
@property (nonatomic, copy) NSArray<PKPaymentSummaryItem *> *paymentSummaryItems;

// Currency code for this payment.
@property (nonatomic, copy) NSString *currencyCode;

// Indicates which billing contact fields the merchant requires in order to process a transaction.
// Currently only postal address may be requested for billing contact. For all other fields use -requiredShippingContactFields
@property (nonatomic, strong) NSSet<PKContactField> *requiredBillingContactFields API_AVAILABLE(ios(11.0), watchos(4.0));

// Indicates which billing address fields are required. The default is PKAddressFieldNone.
// This property is deprecated and should not be used.
@property (nonatomic, assign) PKAddressField requiredBillingAddressFields API_DEPRECATED_WITH_REPLACEMENT("requiredBillingContactFields", ios(8.0, 11.0), watchos(2.0, 4.0));

// If the merchant already has a billing address on file, set it here.
@property (nonatomic, strong, nullable) PKContact *billingContact API_AVAILABLE(ios(9.0), watchos(3.0));

// Indicates which shipping contact fields the merchant requires in order to process a transactions
//
@property (nonatomic, strong) NSSet<PKContactField> *requiredShippingContactFields API_AVAILABLE(ios(11.0), watchos(4.0));

// Indicates which shipping address fields are required. The default is PKAddressFieldNone.
// This property is deprecated and should not be used
@property (nonatomic, assign) PKAddressField requiredShippingAddressFields API_DEPRECATED_WITH_REPLACEMENT("requiredShippingContactFields", ios(8.0, 11.0), watchos(2.0, 4.0));

// If the merchant already has a shipping address on file, set it here.
@property (nonatomic, strong, nullable) PKContact *shippingContact API_AVAILABLE(ios(9.0), watchos(3.0));

// Shipping methods supported by the merchant.
@property (nonatomic, copy, nullable) NSArray<PKShippingMethod *> *shippingMethods;

// Indicates the display mode for the shipping (e.g, "Pick Up", "Ship To", "Deliver To"). Localized.
// The default is PKShippingTypeShipping
@property (nonatomic, assign) PKShippingType shippingType API_AVAILABLE(ios(8.3), watchos(3.0));

// Optional merchant-supplied information about the payment request.  Examples of this are an order
// or cart identifier.  It will be signed and included in the resulting PKPaymentToken.
@property (nonatomic, copy, nullable) NSData *applicationData;

// Set of two-letter ISO 3166 country codes. When provided will filter the selectable payment passes to those
// issued in the supported countries.
@property (nonatomic, copy, nullable) NSSet<NSString *> *supportedCountries API_AVAILABLE(ios(11.0), watchos(4.0));

#if TARGET_OS_IOS && !TARGET_OS_MACCATALYST
// These properties have been deprecated and should not be used.
@property (nonatomic, assign, nullable) ABRecordRef shippingAddress __WATCHOS_PROHIBITED API_DEPRECATED("ABRecordRef has been deprecated, and does not support all available address properties. You should migrate to shippingContact.", ios(8.0, 9.0));

@property (nonatomic, assign, nullable) ABRecordRef billingAddress __WATCHOS_PROHIBITED API_DEPRECATED("ABRecordRef has been deprecated, and does not support all available address properties. You should migrate to billingContact.", ios(8.0, 9.0));
#endif

@end

NS_ASSUME_NONNULL_END

#endif // __PKPAYMENTREQUEST_H__
