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
} NS_SWIFT_NAME(SKProduct.PeriodUnit) NS_AVAILABLE(10_13_2, 11_2);

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS_AVAILABLE(10_13_2, 11_2) @interface SKProductSubscriptionPeriod : NSObject {
@private
    id _internal;
}

@property(nonatomic, readonly) NSUInteger numberOfUnits;

@property(nonatomic, readonly) SKProductPeriodUnit unit;

@end

SK_EXTERN_CLASS_AVAILABLE(10_7, 3_0) @interface SKProduct : NSObject {
@private
    id _internal;
}

@property(nonatomic, readonly) NSString *localizedDescription NS_AVAILABLE(10_7, 3_0);

@property(nonatomic, readonly) NSString *localizedTitle NS_AVAILABLE(10_7, 3_0);

@property(nonatomic, readonly) NSDecimalNumber *price NS_AVAILABLE(10_7, 3_0);

@property(nonatomic, readonly) NSLocale *priceLocale NS_AVAILABLE(10_7, 3_0);

@property(nonatomic, readonly) NSString *productIdentifier NS_AVAILABLE(10_7, 3_0);

// YES if this product has content downloadable using SKDownload
#if TARGET_OS_OSX
@property(nonatomic, readonly) BOOL downloadable NS_AVAILABLE_MAC(10_8);
#else
@property(nonatomic, readonly, getter=isDownloadable) BOOL downloadable NS_AVAILABLE_IOS(6_0);
#endif

// Sizes in bytes (NSNumber [long long]) of the downloads available for this product
@property(nonatomic, readonly) NSArray<NSNumber *> *contentLengths NS_DEPRECATED_MAC(10_8, 10_14, "Use [SKProduct downloadContentLengths] instead");
@property(nonatomic, readonly) NSArray<NSNumber *> *downloadContentLengths NS_AVAILABLE(10_14, 6_0);

// Version of the downloadable content
@property(nonatomic, readonly) NSString *contentVersion NS_DEPRECATED_MAC(10_8, 10_14, "Use [SKProduct downloadContentVersion] instead");
@property(nonatomic, readonly) NSString *downloadContentVersion NS_AVAILABLE(10_14, 6_0);

@property(nonatomic, readonly, nullable) SKProductSubscriptionPeriod *subscriptionPeriod NS_AVAILABLE(10_13_2, 11_2);

@property(nonatomic, readonly, nullable) SKProductDiscount *introductoryPrice NS_AVAILABLE(10_13_2, 11_2);

@property(nonatomic, readonly, nullable) NSString *subscriptionGroupIdentifier NS_AVAILABLE(10_14, 12_0);

@end

NS_ASSUME_NONNULL_END
