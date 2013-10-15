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

@property(readonly) NSString *localizedDescription;

@property(readonly) NSString *localizedTitle;

@property(readonly) NSDecimalNumber *price;

@property(readonly) NSLocale *priceLocale;

@property(readonly) NSString *productIdentifier;

@end
