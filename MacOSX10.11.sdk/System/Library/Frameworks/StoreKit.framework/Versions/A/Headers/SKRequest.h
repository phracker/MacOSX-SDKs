//
//  SKRequest.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>



NS_ASSUME_NONNULL_BEGIN
@protocol SKRequestDelegate;

// Base class used to fetch data from the store.  Should not be used directly.
NS_CLASS_AVAILABLE(10_7, NA)
@interface SKRequest : NSObject {
@private
    id _requestInternal;
}

@property(nullable, assign) id <SKRequestDelegate> delegate;

// Cancel the request if it has started.
- (void)cancel;

// Start the request if it has not already been started.
- (void)start;

@end
NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN
@protocol SKRequestDelegate <NSObject>

@optional
- (void)requestDidFinish:(SKRequest *)request;
- (void)request:(SKRequest *)request didFailWithError:(nullable NSError *)error;

@end
NS_ASSUME_NONNULL_END


