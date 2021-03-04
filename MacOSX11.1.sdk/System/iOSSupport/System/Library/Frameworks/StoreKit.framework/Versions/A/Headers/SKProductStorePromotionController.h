//
//  SKProductStorePromotionController.h
//  StoreKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class SKProduct;

typedef NS_CLOSED_ENUM(NSInteger, SKProductStorePromotionVisibility) {
    SKProductStorePromotionVisibilityDefault,
    SKProductStorePromotionVisibilityShow,
    SKProductStorePromotionVisibilityHide,
} API_AVAILABLE(ios(11.0), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos);

SK_EXTERN_CLASS API_AVAILABLE(ios(11.0), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos) @interface SKProductStorePromotionController : NSObject

+ (instancetype)defaultController API_AVAILABLE(ios(11.0), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos);

- (void)fetchStorePromotionVisibilityForProduct:(SKProduct *)product completionHandler:(nullable void (^)(SKProductStorePromotionVisibility storePromotionVisibility, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos);
- (void)updateStorePromotionVisibility:(SKProductStorePromotionVisibility)promotionVisibility forProduct:(SKProduct *)product completionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(update(storePromotionVisibility:for:completionHandler:)) API_AVAILABLE(ios(11.0), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos);

- (void)fetchStorePromotionOrderWithCompletionHandler:(nullable void (^)(NSArray<SKProduct *> *storePromotionOrder, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos);
- (void)updateStorePromotionOrder:(NSArray<SKProduct *> *)storePromotionOrder completionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(update(storePromotionOrder:completionHandler:)) API_AVAILABLE(ios(11.0), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END
