//
//  SKRequest.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>



@protocol SKRequestDelegate;

// Base class used to fetch data from the store.  Should not be used directly.
NS_CLASS_AVAILABLE(10_7, NA)
@interface SKRequest : NSObject {
@private
    id _requestInternal;
    NSValue* _serverConnection; //if request uses sustained connection
}

@property(assign) id <SKRequestDelegate> delegate;

// Cancel the request if it has started.
- (void)cancel;

// Start the request if it has not already been started.
- (void)start;

@end

@protocol SKRequestDelegate <NSObject>

@optional
- (void)requestDidFinish:(SKRequest *)request;
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error;

@end


