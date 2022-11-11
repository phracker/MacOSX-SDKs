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

SK_EXTERN_CLASS API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2)) @interface SKPayment : NSObject <NSCopying, NSMutableCopying> {
@private
    id _internal;
}

+ (instancetype)paymentWithProduct:(SKProduct *)product API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));

+ (id)paymentWithProductIdentifier:(NSString *)identifier API_DEPRECATED_WITH_REPLACEMENT("+[SKPayment paymentWithProduct:]", ios(3.0, 5.0), macCatalyst(13.0, 13.0)) API_UNAVAILABLE(tvos, macos, watchos);

// Identifier agreed upon with the store.  Required.
@property(nonatomic, copy, readonly) NSString *productIdentifier API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));

// Payment request data agreed upon with the store.  Optional.
@property(nonatomic, copy, readonly, nullable) NSData *requestData API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));

// default: 1.  Must be at least 1.
@property(nonatomic, readonly) NSInteger quantity API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));

// Application-specific user identifier.  Optional.
@property(nonatomic, copy, readonly, nullable) NSString *applicationUsername API_AVAILABLE(ios(7.0), macos(10.9), watchos(6.2));

// Force an "ask to buy" flow for this payment, in the sandbox
@property(nonatomic, readonly) BOOL simulatesAskToBuyInSandbox API_AVAILABLE(ios(8.3), macos(10.14), watchos(6.2));

// The relevant data for specifying a discount to be applied to this payment. Optional.
@property(nonatomic, copy, readonly, nullable) SKPaymentDiscount *paymentDiscount API_AVAILABLE(ios(12.2), macos(10.14.4), watchos(6.2));

@end


SK_EXTERN_CLASS API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2)) @interface SKMutablePayment : SKPayment

@property(nonatomic, copy, readwrite, nullable) NSString *applicationUsername API_AVAILABLE(ios(7.0), macos(10.9), watchos(6.2));
@property(nonatomic, copy, readwrite, nullable) SKPaymentDiscount *paymentDiscount API_AVAILABLE(ios(12.2), macos(10.14.4), watchos(6.2));
@property(nonatomic, copy, readwrite) NSString *productIdentifier API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));
@property(nonatomic, readwrite) NSInteger quantity API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));
@property(nonatomic, copy, readwrite, nullable) NSData *requestData API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2));
@property(nonatomic, readwrite) BOOL simulatesAskToBuyInSandbox API_AVAILABLE(ios(8.3), macos(10.14), watchos(6.2));

@end

NS_ASSUME_NONNULL_END
