//
//  SKPayment.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKProduct;

//Model class to define a payment for a particular product
NS_CLASS_AVAILABLE(10_7, NA) 
NS_ASSUME_NONNULL_BEGIN
@interface SKPayment : NSObject <NSCopying, NSMutableCopying> {
@private
    id _internal;
}

+ (id)paymentWithProduct:(SKProduct *)product;

// Identifier agreed upon with the store.  Required.
@property(copy, readonly) NSString *productIdentifier;

// Payment request data agreed upon with the store.  Optional.
@property(nullable, copy, readonly) NSData *requestData;

// default: 1.  Must be at least 1.
@property(readonly) NSInteger quantity;

// Application-specific user identifier.  Optional.
@property(nullable, nonatomic, copy, readonly) NSString *applicationUsername;

@end
NS_ASSUME_NONNULL_END


NS_CLASS_AVAILABLE(10_7, NA)
NS_ASSUME_NONNULL_BEGIN
@interface SKMutablePayment : SKPayment {
}

@property(copy, readwrite) NSString *productIdentifier;
@property(readwrite) NSInteger quantity;
@property(nullable, copy, readwrite) NSData *requestData;
@property(nullable, nonatomic, copy, readwrite) NSString *applicationUsername;

@end
NS_ASSUME_NONNULL_END

