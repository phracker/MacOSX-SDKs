//
//  SKProduct.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS_AVAILABLE(10_7)
@interface SKProduct : NSObject
{
@private
    id _internal;
}

@property(nonatomic, readonly) NSString *localizedDescription NS_AVAILABLE_MAC(10_7);

@property(nonatomic, readonly) NSString *localizedTitle NS_AVAILABLE_MAC(10_7);

@property(nonatomic, readonly) NSDecimalNumber *price NS_AVAILABLE_MAC(10_7);

@property(nonatomic, readonly) NSLocale *priceLocale NS_AVAILABLE_MAC(10_7);

@property(nonatomic, readonly) NSString *productIdentifier NS_AVAILABLE_MAC(10_7);

// YES if the product's assets are hosted by the App Store. NO otherwise. 
@property(nonatomic, readonly) BOOL downloadable NS_AVAILABLE_MAC(10_8);

// Version string of the product
@property(nonatomic, readonly) NSString *contentVersion NS_AVAILABLE_MAC(10_8);

// An array of filesizes of the assets associated with the product
@property(nonatomic, readonly) NSArray<NSNumber *> *contentLengths NS_AVAILABLE_MAC(10_8);

@end

NS_ASSUME_NONNULL_END
