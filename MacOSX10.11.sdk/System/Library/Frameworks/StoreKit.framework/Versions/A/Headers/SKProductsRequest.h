//
//  SKProductsRequest.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <StoreKit/SKRequest.h>



@class SKProductsRequest, SKProductsResponse, SKProduct;

NS_ASSUME_NONNULL_BEGIN
@protocol SKProductsRequestDelegate <SKRequestDelegate>

@required
// Sent immediately before -requestDidFinish:
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response;

@end
NS_ASSUME_NONNULL_END


// request information about products for your application
NS_CLASS_AVAILABLE(10_7, NA)
NS_ASSUME_NONNULL_BEGIN
@interface SKProductsRequest : SKRequest {
@private
    id _productsRequestInternal;
}

// Set of string product identifiers
- (id)initWithProductIdentifiers:(NSSet *)productIdentifiers;

@property(nullable, assign) id <SKProductsRequestDelegate> delegate;

@end
NS_ASSUME_NONNULL_END


NS_CLASS_AVAILABLE(10_7, NA)
NS_ASSUME_NONNULL_BEGIN
@interface SKProductsResponse : NSObject {
@private
    id _internal;
}

// Array of SKProduct instances.
@property(nullable, readonly) NSArray<SKProduct *> *products;

// Array of invalid product identifiers.
@property(nullable, readonly) NSArray<NSString *> *invalidProductIdentifiers;

@end
NS_ASSUME_NONNULL_END


