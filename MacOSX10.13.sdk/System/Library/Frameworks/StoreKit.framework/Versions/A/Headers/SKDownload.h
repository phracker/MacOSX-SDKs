//
//  SKDownload.h
//  StoreKit
//
//  Copyright 2012 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKPaymentTransaction;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SKDownloadState)
{
	SKDownloadStateWaiting,
	SKDownloadStateActive,
	SKDownloadStatePaused,
	SKDownloadStateFinished,
	SKDownloadStateFailed,
	SKDownloadStateCancelled
} NS_AVAILABLE_MAC(10_8);


// Model class to define a download for a particular product
SK_EXTERN_CLASS_AVAILABLE(10_8)
@interface SKDownload : NSObject
{
@private
    id _internal;
}

// Product identifier entered in iTunesConnect
@property(nonatomic, readonly) NSString *contentIdentifier NS_AVAILABLE_MAC(10_8);

// Download state
@property(nonatomic, readonly) SKDownloadState state NS_AVAILABLE_MAC(10_8);

// Content URL
@property(nonatomic, readonly, nullable) NSURL *contentURL NS_AVAILABLE_MAC(10_8);

// Download progress 
@property(nonatomic, readonly) float progress NS_AVAILABLE_MAC(10_8);

// Last error, can be NULL
@property(nonatomic, copy, readonly, nullable) NSError *error NS_AVAILABLE_MAC(10_8);

// Estimated number of seconds remaining in the download
@property(nonatomic, readonly) NSTimeInterval timeRemaining NS_AVAILABLE_MAC(10_8);

// Filesize of the asset
@property(nonatomic, copy, readonly) NSNumber *contentLength NS_AVAILABLE_MAC(10_8);

// Version string of the product
@property(nonatomic, copy, readonly) NSString *contentVersion NS_AVAILABLE_MAC(10_8);

// The transaction associated with the downloadable file
@property(nonatomic, readonly) SKPaymentTransaction *transaction NS_AVAILABLE_MAC(10_11);

//
+ (nullable NSURL *) contentURLForProductID:(NSString *)productID NS_AVAILABLE_MAC(10_8);

// Deletes the content for that identifier from disk
+ (void) deleteContentForProductID:(NSString *)productID NS_AVAILABLE_MAC(10_8);

@end

NS_ASSUME_NONNULL_END
