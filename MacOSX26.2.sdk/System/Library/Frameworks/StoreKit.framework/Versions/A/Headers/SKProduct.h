//
//  SKProduct.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKProductDiscount;

typedef NS_ENUM(NSUInteger, SKProductPeriodUnit) {
    SKProductPeriodUnitDay,
    SKProductPeriodUnitWeek,
    SKProductPeriodUnitMonth,
    SKProductPeriodUnitYear
}
NS_SWIFT_NAME(SKProduct.PeriodUnit)
API_DEPRECATED("Use Product.SubscriptionPeriod.Unit.", ios(11.2, 18.0), macos(10.13.2, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS
API_DEPRECATED("Use Product.SubscriptionPeriod.", ios(11.2, 18.0), macos(10.13.2, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0))
NS_SWIFT_SENDABLE
@interface SKProductSubscriptionPeriod : NSObject {
@private
    id _internal;
}

@property(nonatomic, readonly) NSUInteger numberOfUnits;

@property(nonatomic, readonly) SKProductPeriodUnit unit;

@end

SK_EXTERN_CLASS
API_DEPRECATED("Use Product.", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0))
NS_SWIFT_SENDABLE
@interface SKProduct : NSObject {
@private
    id _internal;
}

@property(nonatomic, readonly) NSString *localizedDescription API_DEPRECATED("Use Product.description.", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@property(nonatomic, readonly) NSString *localizedTitle API_DEPRECATED("Use Product.displayName.", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@property(nonatomic, readonly) NSDecimalNumber *price API_DEPRECATED("Use Product.displayPrice.", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@property(nonatomic, readonly) NSLocale *priceLocale API_DEPRECATED("Use Product.displayPrice.", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@property(nonatomic, readonly) NSString *productIdentifier API_DEPRECATED("Use Product.id.", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

// YES if this product has content downloadable using SKDownload
@property(nonatomic, readonly) BOOL isDownloadable API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.15, 13.0), watchos(6.2, 9.0), visionos(1.0, 2.0));
@property(nonatomic, readonly) BOOL downloadable API_DEPRECATED_WITH_REPLACEMENT("-[SKProduct isDownloadable]", macos(10.8, 10.15)) API_UNAVAILABLE(ios, watchos, visionos);

// YES if this product allows for sharing among family members
@property(nonatomic, readonly) BOOL isFamilyShareable API_DEPRECATED("Use Product.isFamilyShareable.", ios(14.0, 18.0), macos(11.0, 15.0), watchos(7.0, 11.0), visionos(1.0, 2.0));

// Sizes in bytes (NSNumber [long long]) of the downloads available for this product
@property(nonatomic, readonly) NSArray<NSNumber *> *contentLengths API_DEPRECATED_WITH_REPLACEMENT("-[SKProduct downloadContentLengths]", macos(10.8, 10.14)) API_UNAVAILABLE(ios, tvos, watchos, visionos);
@property(nonatomic, readonly) NSArray<NSNumber *> *downloadContentLengths API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.14, 13.0), watchos(6.2, 9.0), visionos(1.0, 2.0));

// Version of the downloadable content
@property(nonatomic, readonly) NSString *contentVersion API_DEPRECATED_WITH_REPLACEMENT("-[SKProduct downloadContentVersion]", macos(10.8, 10.14)) API_UNAVAILABLE(visionos);
@property(nonatomic, readonly) NSString *downloadContentVersion API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.14, 13.0), watchos(6.2, 9.0), visionos(1.0, 2.0));

@property(nonatomic, readonly, nullable) SKProductSubscriptionPeriod *subscriptionPeriod API_DEPRECATED("Use Product.subscription.subscriptionPeriod.", ios(11.2, 18.0), macos(10.13.2, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@property(nonatomic, readonly, nullable) SKProductDiscount *introductoryPrice API_DEPRECATED("Use Product.subscription.introductionaryOffer.", ios(11.2, 18.0), macos(10.13.2, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@property(nonatomic, readonly, nullable) NSString *subscriptionGroupIdentifier API_DEPRECATED("Use Product.subscription.subscriptionGroupID.", ios(12.0, 18.0), macos(10.14, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@property(nonatomic, readonly) NSArray<SKProductDiscount *> *discounts API_DEPRECATED("Use Product.subscription.promotionalOffers.", ios(12.2, 18.0), macos(10.14.4, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@end

NS_ASSUME_NONNULL_END
