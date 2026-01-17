#if !__has_include(<PassKitCore/PKAutomaticReloadPaymentRequest.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKAutomaticReloadPaymentRequest.h
//    PassKit
//  Copyright © 2021 Apple, Inc. All rights reserved.
//

#ifndef PKAutomaticReloadPaymentRequest_h
#define PKAutomaticReloadPaymentRequest_h

#import <Foundation/Foundation.h>

@class PKAutomaticReloadPaymentSummaryItem;

NS_ASSUME_NONNULL_BEGIN

// Represents a request to set up an automatic reload or refill payment, such as a store card top-up.
// This request will receive a merchant-specific payment token, if the payment network supports
// merchant-specific payment tokens.
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos)
@interface PKAutomaticReloadPaymentRequest : NSObject

// A description of the automatic reload, for example "Gift Card Reload".
@property (nonatomic, copy) NSString *paymentDescription;

// Details about the automatic reload payment, for example "top-up with $20 when account reaches $5".
@property (nonatomic, strong) PKAutomaticReloadPaymentSummaryItem *automaticReloadBilling;

// Optional, localized billing agreement to be displayed to the user prior to payment authorization.
// This may include further details about the threshold amount or reload conditions.
@property (nonatomic, copy, nullable) NSString *billingAgreement;

// A URL that links to a page on your web site where the user can manage the payment method for this
// automatic reload payment, including deleting it.
@property (nonatomic, strong) NSURL *managementURL;

// Optional URL to receive lifecycle notifications for the merchant-specific payment token issued
// for this request, if applicable. If this property is not set, notifications will not be sent when
// lifecycle changes occur for the token, for example when the token is deleted.
@property (nonatomic, strong, nullable) NSURL *tokenNotificationURL;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithPaymentDescription:(NSString *)paymentDescription
                    automaticReloadBilling:(PKAutomaticReloadPaymentSummaryItem *)automaticReloadBilling
                             managementURL:(NSURL *)managementURL NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

#endif /* PKAutomaticReloadPaymentRequest_h */

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKAutomaticReloadPaymentRequest.h>
#endif