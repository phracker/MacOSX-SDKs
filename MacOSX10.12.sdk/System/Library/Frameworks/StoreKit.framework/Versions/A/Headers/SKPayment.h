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

//Model class to define a payment for a particular product
SK_EXTERN_CLASS_AVAILABLE(10_7)
@interface SKPayment : NSObject <NSCopying, NSMutableCopying>
{
@protected
    id _internal;
}

+ (instancetype)paymentWithProduct:(SKProduct *)product NS_AVAILABLE_MAC(10_7);

// Identifier agreed upon with the store.  Required.
@property(nonatomic, copy, readonly) NSString *productIdentifier NS_AVAILABLE_MAC(10_7);

// Payment request data agreed upon with the store.  Optional.
@property(nonatomic, copy, readonly, nullable) NSData *requestData NS_AVAILABLE_MAC(10_7);

// default: 1.  Must be at least 1.
@property(nonatomic, readonly) NSInteger quantity NS_AVAILABLE_MAC(10_7);

// Application-specific user identifier.  Optional.
@property(nonatomic, copy, readonly, nullable) NSString *applicationUsername NS_AVAILABLE_MAC(10_9);

@end


SK_EXTERN_CLASS_AVAILABLE(10_7)
@interface SKMutablePayment : SKPayment

@property(nonatomic, copy) NSString *productIdentifier NS_AVAILABLE_MAC(10_7);
@property(nonatomic) NSInteger quantity NS_AVAILABLE_MAC(10_7);
@property(nonatomic, copy, nullable) NSData *requestData NS_AVAILABLE_MAC(10_7);
@property(nonatomic, copy, nullable) NSString *applicationUsername NS_AVAILABLE_MAC(10_9);

@end

NS_ASSUME_NONNULL_END
