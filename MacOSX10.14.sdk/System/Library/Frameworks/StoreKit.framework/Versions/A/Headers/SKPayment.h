//
//  SKPayment.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKProduct;

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS_AVAILABLE(10_7, 3_0) @interface SKPayment : NSObject <NSCopying, NSMutableCopying> {
@private
    id _internal;
}

+ (instancetype)paymentWithProduct:(SKProduct *)product NS_AVAILABLE(10_7, 3_0);

+ (id)paymentWithProductIdentifier:(NSString *)identifier NS_DEPRECATED_IOS(3_0, 5_0, "Use +paymentWithProduct: after fetching the available products using SKProductsRequest");

// Identifier agreed upon with the store.  Required.
@property(nonatomic, copy, readonly) NSString *productIdentifier NS_AVAILABLE(10_7, 3_0);

// Payment request data agreed upon with the store.  Optional.
@property(nonatomic, copy, readonly, nullable) NSData *requestData NS_AVAILABLE(10_7, 3_0);

// default: 1.  Must be at least 1.
@property(nonatomic, readonly) NSInteger quantity NS_AVAILABLE(10_7, 3_0);

// Application-specific user identifier.  Optional.
@property(nonatomic, copy, readonly, nullable) NSString *applicationUsername NS_AVAILABLE(10_9, 7_0);

// Force an "ask to buy" flow for this payment, in the sandbox
@property(nonatomic, readonly) BOOL simulatesAskToBuyInSandbox NS_AVAILABLE(10_14, 8_3);

@end


SK_EXTERN_CLASS_AVAILABLE(10_7, 3_0) @interface SKMutablePayment : SKPayment

@property(nonatomic, copy, readwrite, nullable) NSString *applicationUsername NS_AVAILABLE(10_9, 7_0);
@property(nonatomic, copy, readwrite) NSString *productIdentifier NS_AVAILABLE(10_7, 3_0);
@property(nonatomic, readwrite) NSInteger quantity NS_AVAILABLE(10_7, 3_0);
@property(nonatomic, copy, readwrite, nullable) NSData *requestData NS_AVAILABLE(10_7, 3_0);
@property(nonatomic, readwrite) BOOL simulatesAskToBuyInSandbox NS_AVAILABLE(10_14, 8_3);

@end

NS_ASSUME_NONNULL_END
