//
//  SKPayment.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKProduct;
@class SKPaymentDiscount;

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS
API_DEPRECATED("Use Product.purchase(confirmIn:options:).", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0))
NS_SWIFT_NONSENDABLE
@interface SKPayment : NSObject <NSCopying, NSMutableCopying> {
@private
    id _internal;
}

+ (instancetype)paymentWithProduct:(SKProduct *)product;

+ (id)paymentWithProductIdentifier:(NSString *)identifier API_DEPRECATED_WITH_REPLACEMENT("+[SKPayment paymentWithProduct:]", ios(3.0, 5.0), macCatalyst(13.0, 13.0)) API_UNAVAILABLE(tvos, macos, watchos) API_UNAVAILABLE(visionos);

// Identifier agreed upon with the store.  Required.
@property(nonatomic, copy, readonly) NSString *productIdentifier;

// Payment request data agreed upon with the store.  Optional.
@property(nonatomic, copy, readonly, nullable) NSData *requestData API_DEPRECATED("Create Product.PurchaseOption.custom values to use in Product.purchase(confirmIn:options:).", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

// default: 1.  Must be at least 1.
@property(nonatomic, readonly) NSInteger quantity API_DEPRECATED("Create a Product.PurchaseOption.quantity to use in Product.purchase(confirmIn:options:).", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

// Application-specific user identifier.  Optional.
@property(nonatomic, copy, readonly, nullable) NSString *applicationUsername API_DEPRECATED("Create a Product.PurchaseOption.appAccountToken to use in Product.purchase(confirmIn:options:).", ios(7.0, 18.0), macos(10.9, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

// Force an "ask to buy" flow for this payment, in the sandbox
@property(nonatomic, readonly) BOOL simulatesAskToBuyInSandbox API_DEPRECATED("Create a Product.PurchaseOption.simulatesAskToBuyInSandbox to use in Product.purchase(confirmIn:options:).", ios(8.3, 18.0), macos(10.14, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

// The relevant data for specifying a discount to be applied to this payment. Optional.
@property(nonatomic, copy, readonly, nullable) SKPaymentDiscount *paymentDiscount API_DEPRECATED("Create a Product.PurchaseOption.promotionalOffer to use in Product.purchase(confirmIn:options:).", ios(12.2, 18.0), macos(10.14.4, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@end


SK_EXTERN_CLASS
API_DEPRECATED("Use Product.purchase(confirmIn:options:).", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0))
NS_SWIFT_NONSENDABLE
@interface SKMutablePayment : SKPayment

@property(nonatomic, copy, readwrite, nullable) NSString *applicationUsername API_DEPRECATED("Create a Product.PurchaseOption.appAccountToken to use in Product.purchase(confirmIn:options:).", ios(7.0, 18.0), macos(10.9, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));
@property(nonatomic, copy, readwrite, nullable) SKPaymentDiscount *paymentDiscount API_DEPRECATED("Create a Product.PurchaseOption.promotionalOffer to use in Product.purchase(confirmIn:options:).", ios(12.2, 18.0), macos(10.14.4, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));
@property(nonatomic, copy, readwrite) NSString *productIdentifier;
@property(nonatomic, readwrite) NSInteger quantity API_DEPRECATED("Create a Product.PurchaseOption.quantity to use in Product.purchase(confirmIn:options:).", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));
@property(nonatomic, copy, readwrite, nullable) NSData *requestData API_DEPRECATED("Create Product.PurchaseOption.custom values to use in Product.purchase(confirmIn:options:).", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));
@property(nonatomic, readwrite) BOOL simulatesAskToBuyInSandbox API_DEPRECATED("Create a Product.PurchaseOption.simulatesAskToBuyInSandbox to use in Product.purchase(confirmIn:options:).", ios(8.3, 18.0), macos(10.14, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@end

NS_ASSUME_NONNULL_END
