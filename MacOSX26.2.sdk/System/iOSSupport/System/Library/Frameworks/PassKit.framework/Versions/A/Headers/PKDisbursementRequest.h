#if !__has_include(<PassKitCore/PKDisbursementRequest.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKDisbursementRequest.h
//    PassKit
//  Copyright © 2019 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PassKit/PKPaymentRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class PKPaymentSummaryItem;

API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos, tvos)
@interface PKDisbursementRequest : NSObject

// Identifies the merchant, as previously agreed with Apple. Must match one of the merchant
// identifiers in the application's entitlement.
@property (nonatomic, copy) NSString *merchantIdentifier;

// The merchant's ISO 3166 region code.
@property (nonatomic, copy) NSString *regionCode NS_REFINED_FOR_SWIFT;

// The payment networks supported by the merchant, for example `@[ PKPaymentNetworkVisa,
// PKPaymentNetworkMasterCard ]`.  This property constrains payment cards that may receive the funds.
@property (nonatomic, copy) NSArray<PKPaymentNetwork> *supportedNetworks;

// The payment processing capabilities of the merchant.
@property (nonatomic, assign) PKMerchantCapability merchantCapabilities;

// Array of PKPaymentSummaryItem objects which should be presented to the user.
// The last item should be the total you wish to disburse, and should not be pending.
@property (nonatomic, copy) NSArray<PKPaymentSummaryItem *> *summaryItems;

// Currency code for this disbursement.
@property (nonatomic, copy) NSString *currencyCode NS_REFINED_FOR_SWIFT;

// Indicates which of the recipient's contact details the merchant requires in order to process a disbursement.
// The order of the elements is ignored.
@property (nonatomic, strong) NSArray<PKContactField> *requiredRecipientContactFields;

// If the merchant already has recipient contact information on file, set it here.
@property (nonatomic, strong, nullable) PKContact *recipientContact;

// Set of two-letter ISO 3166 region codes. When provided, it will filter the selectable payment passes to those
// issued in the supported regions. The order of the elements is ignored.
@property (nonatomic, copy, nullable) NSArray<NSString *> *supportedRegions NS_REFINED_FOR_SWIFT;

// Optional merchant-supplied information about the disbursement request.
// It will be signed and included in the resulting PKPaymentToken.
@property (nonatomic, copy, nullable) NSData *applicationData;

// Initialise a disbursement request with all required fields.
- (instancetype)initWithMerchantIdentifier:(NSString *)merchantIdentifier
                              currencyCode:(NSString *)currencyCode
                                regionCode:(NSString *)regionCode
                         supportedNetworks:(NSArray<PKPaymentNetwork> *)supportedNetworks
                      merchantCapabilities:(PKMerchantCapability)merchantCapabilities
                              summaryItems:(NSArray<PKPaymentSummaryItem *> *)summaryItems NS_REFINED_FOR_SWIFT;

// Convenience method to create a receipient contact error with the supplied field
// You may optionally provide a localized description to be displayed to the user.
// Available display space for descriptions may be limited, so you should keep your messages concise
+ (NSError *)disbursementContactInvalidErrorWithContactField:(PKContactField)field
                                        localizedDescription:(nullable NSString *)localizedDescription;

// Convenience method to create an error indicating that the selected card does not support receiving
// funds via disbursements.
+ (NSError *)disbursementCardUnsupportedError;

@end

NS_ASSUME_NONNULL_END

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKDisbursementRequest.h>
#endif