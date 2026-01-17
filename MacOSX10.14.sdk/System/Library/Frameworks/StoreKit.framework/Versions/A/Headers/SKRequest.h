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
SK_EXTERN_CLASS_AVAILABLE(10_7, 3_0) @interface SKRequest : NSObject {
@private
    id _requestInternal;
}

@property(nonatomic, weak, nullable) id <SKRequestDelegate> delegate NS_AVAILABLE(10_7, 3_0);

// Cancel the request if it has started.
- (void)cancel NS_AVAILABLE(10_7, 3_0);

// Start the request if it has not already been started.
- (void)start NS_AVAILABLE(10_7, 3_0);

@end


@protocol SKRequestDelegate <NSObject>

@optional
- (void)requestDidFinish:(SKRequest *)request NS_AVAILABLE(10_7, 3_0);
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error NS_AVAILABLE(10_7, 3_0);

@end

NS_ASSUME_NONNULL_END
