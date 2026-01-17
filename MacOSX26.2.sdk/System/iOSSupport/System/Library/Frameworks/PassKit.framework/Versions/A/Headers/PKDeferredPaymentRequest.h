#if !__has_include(<PassKitCore/PKDeferredPaymentRequest.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKDeferredPaymentRequest.h
//    PassKit
//  Copyright © 2022 Apple, Inc. All rights reserved.
//


#import <Foundation/Foundation.h>

@class PKDeferredPaymentSummaryItem;

NS_ASSUME_NONNULL_BEGIN

// Represents a request to set up a deferred payment, such as a hotel booking or a pre-order.
// This request will receive a merchant-specific payment token, if the
// payment network supports merchant-specific payment tokens.
API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(watchos)
@interface PKDeferredPaymentRequest : NSObject

// A description of the deferred payment, for example "Hotel Stay, 2 nights".
@property (nonatomic, copy) NSString *paymentDescription;

// Details about the deferred payment, for example "Pay $2.99 on January 9, 2022".
@property (nonatomic, strong) PKDeferredPaymentSummaryItem *deferredBilling;

// Optional, localized billing agreement to be displayed to the user prior to payment authorization.
// This may include further details about the cancellation period or penalties for late cancellation.
@property (nonatomic, copy, nullable) NSString *billingAgreement;

// A URL that links to a page on your web site where the user can manage the payment method for this
// deferred payment, including deleting it.
@property (nonatomic, strong) NSURL *managementURL;

// Optional URL to receive lifecycle notifications for the merchant-specific payment token issued
// for this request, if applicable. If this property is not set, notifications will not be sent when
// lifecycle changes occur for the token, for example when the token is deleted.
@property (nonatomic, strong, nullable) NSURL *tokenNotificationURL;

// Optional, the last date before which cancellation charges don't apply. If `freeCancellationDate` is set, `freeCancellationDateTimeZone` must be set as well.
@property (nonatomic, strong, nullable) NSDate *freeCancellationDate;

// Optional, the timezone of the "destination" of the payment. As an example, for a hotel booking, this refers to the local timezone of the hotel. On the payment sheet, this timezone will be used to format the cancellation date.  If `freeCancellationDateTimeZone` date is set, `freeCancellationDate` must be set as well
@property (nonatomic, strong, nullable) NSTimeZone *freeCancellationDateTimeZone;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithPaymentDescription:(NSString *)paymentDescription
                           deferredBilling:(PKDeferredPaymentSummaryItem *)deferredBilling
                             managementURL:(NSURL *)managementURL NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END


#else
#import <TargetConditionals.h>
#import <PassKitCore/PKDeferredPaymentRequest.h>
#endif