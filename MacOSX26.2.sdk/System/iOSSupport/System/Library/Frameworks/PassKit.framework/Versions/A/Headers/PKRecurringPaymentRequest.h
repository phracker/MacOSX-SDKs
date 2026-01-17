#if !__has_include(<PassKitCore/PKRecurringPaymentRequest.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKRecurringPaymentRequest.h
//    PassKit
//
//  Copyright © 2021 Apple, Inc. All rights reserved.
//

#ifndef PKRecurringPaymentRequest_h
#define PKRecurringPaymentRequest_h

#import <Foundation/Foundation.h>

@class PKRecurringPaymentSummaryItem;

NS_ASSUME_NONNULL_BEGIN

// Represents a request to set up a recurring payment, typically a subscription. This request will
// receive a merchant-specific payment token, if the payment network supports merchant-specific
// payment tokens.
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos)
@interface PKRecurringPaymentRequest : NSObject

// A description of the recurring payment, for example "Apple News+".
@property (nonatomic, copy) NSString *paymentDescription;

// The regular billing cycle, for example "$9.99 monthly".
@property (nonatomic, strong) PKRecurringPaymentSummaryItem *regularBilling;

// Optional, trial billing cycle, for example "$1.99 for the first six months".
@property (nonatomic, strong, nullable) PKRecurringPaymentSummaryItem *trialBilling;

// Optional, localized billing agreement to be displayed to the user prior to payment authorization.
@property (nonatomic, copy, nullable) NSString *billingAgreement;

// A URL that links to a page on your web site where the user can manage the payment method for this
// recurring payment, including deleting it.
@property (nonatomic, strong) NSURL *managementURL;

// Optional URL to receive lifecycle notifications for the merchant-specific payment token issued
// for this request, if applicable. If this property is not set, notifications will not be sent when
// lifecycle changes occur for the token, for example when the token is deleted.
@property (nonatomic, strong, nullable) NSURL *tokenNotificationURL;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithPaymentDescription:(NSString *)paymentDescription
                            regularBilling:(PKRecurringPaymentSummaryItem *)regularBilling
                             managementURL:(NSURL *)managementURL NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

#endif /* PKRecurringPaymentRequest_h */

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKRecurringPaymentRequest.h>
#endif