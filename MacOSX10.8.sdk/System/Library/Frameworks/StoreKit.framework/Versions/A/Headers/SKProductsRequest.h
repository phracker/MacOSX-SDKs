//
//  SKProductsRequest.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <StoreKit/SKRequest.h>



@class SKProductsRequest, SKProductsResponse;

@protocol SKProductsRequestDelegate <SKRequestDelegate>

@required
// Sent immediately before -requestDidFinish:
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response;

@end


// request information about products for your application
NS_CLASS_AVAILABLE(10_7, NA)
@interface SKProductsRequest : SKRequest {
@private
    id _productsRequestInternal;
}

// Set of string product identifiers
- (id)initWithProductIdentifiers:(NSSet *)productIdentifiers;

@property(assign) id <SKProductsRequestDelegate> delegate;

@end


NS_CLASS_AVAILABLE(10_7, NA)
@interface SKProductsResponse : NSObject {
@private
    id _internal;
}

// Array of SKProduct instances.
@property(readonly) NSArray *products;

// Array of invalid product identifiers.
@property(readonly) NSArray *invalidProductIdentifiers;

@end


