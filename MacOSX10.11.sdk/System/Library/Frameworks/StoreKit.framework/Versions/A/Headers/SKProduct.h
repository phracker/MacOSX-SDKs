//
//  SKProduct.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_CLASS_AVAILABLE(10_7, NA)
@interface SKProduct : NSObject {
@private
    id _internal;
}

@property(nullable, readonly) NSString *localizedDescription;

@property(nullable, readonly) NSString *localizedTitle;

@property(nullable, readonly) NSDecimalNumber *price;

@property(nullable, readonly) NSLocale *priceLocale;

@property(nullable, readonly) NSString *productIdentifier;

// YES if the product's assets are hosted by the App Store. NO otherwise. 
@property(readonly) BOOL downloadable;

// Version string of the product
@property(nullable, readonly) NSString* contentVersion;

// An array of filesizes of the assets associated with the product
@property(nullable, readonly) NSArray<NSNumber *> *contentLengths;

@end
