//
//  SKProductDiscount.h
//  StoreKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKProductSubscriptionPeriod;

typedef NS_ENUM(NSUInteger, SKProductDiscountPaymentMode) {
    SKProductDiscountPaymentModePayAsYouGo,
    SKProductDiscountPaymentModePayUpFront,
    SKProductDiscountPaymentModeFreeTrial
}
NS_SWIFT_NAME(SKProductDiscount.PaymentMode)
API_DEPRECATED("Use Product.SubscriptionOffer.PaymentMode.", ios(11.2, 18.0), macos(10.13.2, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

typedef NS_ENUM(NSUInteger, SKProductDiscountType) {
    SKProductDiscountTypeIntroductory,
    SKProductDiscountTypeSubscription,
}
NS_SWIFT_NAME(SKProductDiscount.Type)
API_DEPRECATED("Use Product.SubscriptionOffer.OfferType.", ios(12.2, 18.0), macos(10.14.4, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS
API_DEPRECATED("Use Product.SubscriptionOffer.", ios(11.2, 18.0), macos(10.13.2, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0))
NS_SWIFT_SENDABLE
@interface SKProductDiscount : NSObject {
@private
    id _internal;
}

@property(nonatomic, readonly) NSDecimalNumber *price API_DEPRECATED("Use Product.SubscriptionOffer.displayPrice.", ios(11.2, 18.0), macos(10.13.2, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@property(nonatomic, readonly) NSLocale *priceLocale API_DEPRECATED("Use Product.SubscriptionOffer.displayPrice.", ios(11.2, 18.0), macos(10.13.2, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@property(nonatomic, readonly, nullable) NSString *identifier API_DEPRECATED("Use Product.SubscriptionOffer.id.", ios(12.2, 18.0), macos(10.14.4, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@property(nonatomic, readonly) SKProductSubscriptionPeriod *subscriptionPeriod API_DEPRECATED("Use Product.SubscriptionOffer.period.", ios(11.2, 18.0), macos(10.13.2, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@property(nonatomic, readonly) NSUInteger numberOfPeriods API_DEPRECATED("Use Product.SubscriptionOffer.periodCount.", ios(11.2, 18.0), macos(10.13.2, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@property(nonatomic, readonly) SKProductDiscountPaymentMode paymentMode API_DEPRECATED("Use Product.SubscriptionOffer.paymentMode.", ios(11.2, 18.0), macos(10.13.2, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@property(nonatomic, readonly) SKProductDiscountType type API_DEPRECATED("Use Product.SubscriptionOffer.type.", ios(12.2, 18.0), macos(10.14.4, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@end

NS_ASSUME_NONNULL_END
