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
} API_DEPRECATED("Use Product.PromotionInfo.Visibility.", ios(11.0, 18.0), macos(11.0, 15.0), macCatalyst(14.0, 18.0)) API_UNAVAILABLE(watchos, visionos);

SK_EXTERN_CLASS
API_DEPRECATED("Use Product.PromotionInfo.", ios(11.0, 18.0), macos(11.0, 15.0), macCatalyst(14.0, 18.0))
API_UNAVAILABLE(watchos, visionos)
@interface SKProductStorePromotionController : NSObject

+ (instancetype)defaultController;

- (void)fetchStorePromotionVisibilityForProduct:(SKProduct *)product completionHandler:(nullable void (^)(SKProductStorePromotionVisibility storePromotionVisibility, NSError * _Nullable error))completionHandler
NS_SWIFT_ASYNC_NAME(promotionVisibility(for:))
API_DEPRECATED("Get visibility from Product.PromotionInfo.currentOrder.", ios(11.0, 18.0), macos(11.0, 15.0), macCatalyst(14.0, 18.0))
API_UNAVAILABLE(watchos, visionos);

- (void)updateStorePromotionVisibility:(SKProductStorePromotionVisibility)promotionVisibility forProduct:(SKProduct *)product completionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler
NS_SWIFT_NAME(update(storePromotionVisibility:for:completionHandler:))
NS_SWIFT_ASYNC_NAME(update(promotionVisibility:for:))
API_DEPRECATED("Use Product.PromotionInfo.updateProductVisibility(_:for:).", ios(11.0, 18.0), macos(11.0, 15.0), macCatalyst(14.0, 18.0))
API_UNAVAILABLE(watchos, visionos);

- (void)fetchStorePromotionOrderWithCompletionHandler:(nullable void (^)(NSArray<SKProduct *> *promotionOrder, NSError * _Nullable error))completionHandler
NS_SWIFT_ASYNC_NAME(promotionOrder())
API_DEPRECATED("Use Product.PromotionInfo.currentOrder.", ios(11.0, 18.0), macos(11.0, 15.0), macCatalyst(14.0, 18.0))
API_UNAVAILABLE(watchos, visionos);

- (void)updateStorePromotionOrder:(NSArray<SKProduct *> *)promotionOrder completionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler
NS_SWIFT_NAME(update(storePromotionOrder:completionHandler:))
NS_SWIFT_ASYNC_NAME(update(promotionOrder:))
API_DEPRECATED("Use Product.PromotionInfo.updateProductOrder(byID:).", ios(11.0, 18.0), macos(11.0, 15.0), macCatalyst(14.0, 18.0))
API_UNAVAILABLE(watchos, visionos);

@end

NS_ASSUME_NONNULL_END
