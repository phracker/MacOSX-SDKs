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
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response NS_AVAILABLE_MAC(10_7);

@end


// request information about products for your application
SK_EXTERN_CLASS_AVAILABLE(10_7)
@interface SKProductsRequest : SKRequest
{
@private
    id _productsRequestInternal;
}

// Set of string product identifiers
- (instancetype)initWithProductIdentifiers:(NSSet<NSString *> *)productIdentifiers NS_AVAILABLE_MAC(10_7);

@property(nonatomic, weak, nullable) id <SKProductsRequestDelegate> delegate NS_AVAILABLE_MAC(10_7);

@end


SK_EXTERN_CLASS_AVAILABLE(10_7)
@interface SKProductsResponse : NSObject
{
@private
    id _internal;
}

// Array of SKProduct instances.
@property(nonatomic, readonly) NSArray<SKProduct *> *products NS_AVAILABLE_MAC(10_7);

// Array of invalid product identifiers.
@property(nonatomic, readonly) NSArray<NSString *> *invalidProductIdentifiers NS_AVAILABLE_MAC(10_7);

@end

NS_ASSUME_NONNULL_END
