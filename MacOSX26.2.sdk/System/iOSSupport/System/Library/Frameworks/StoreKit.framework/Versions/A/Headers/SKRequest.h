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
SK_EXTERN_CLASS
API_DEPRECATED("No longer supported.", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0))
NS_SWIFT_NONSENDABLE
@interface SKRequest : NSObject {
@private
    id _requestInternal;
}

@property(nonatomic, weak, nullable) id <SKRequestDelegate> delegate;

// Cancel the request if it has started.
- (void)cancel;

// Start the request if it has not already been started.
- (void)start;

@end


API_DEPRECATED("No longer supported.", ios(3.0, 18.0), macos(10.7, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0))
@protocol SKRequestDelegate <NSObject>

@optional
- (void)requestDidFinish:(SKRequest *)request;
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
