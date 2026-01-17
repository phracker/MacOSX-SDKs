//
//  SKDownload.h
//  StoreKit
//
//  Copyright 2012 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKPaymentTransaction;

typedef enum : NSInteger
{
	SKDownloadStateWaiting,
	SKDownloadStateActive,
	SKDownloadStatePaused,
	SKDownloadStateFinished,
	SKDownloadStateFailed,
	SKDownloadStateCancelled
}
SKDownloadState;


// Model class to define a download for a particular product
NS_CLASS_AVAILABLE(10_8, NA) 
NS_ASSUME_NONNULL_BEGIN
@interface SKDownload : NSObject {
@private
    id _internal;
}

// Product identifier entered in iTunesConnect
@property(readonly) NSString *contentIdentifier;

// Download state
@property(readonly) SKDownloadState state;

// Content URL
@property(nullable, copy, readonly) NSURL *contentURL;

// Download progress 
@property(readonly) float progress;

// Last error, can be NULL
@property(nullable, copy, readonly) NSError *error;

// Estimated number of seconds remaining in the download
@property(readonly) NSTimeInterval timeRemaining;

// Filesize of the asset
@property(copy, readonly) NSNumber *contentLength;

// Version string of the product
@property(nullable, copy, readonly) NSString* contentVersion;

// The transaction associated with the downloadable file
@property(nullable, nonatomic, readonly) SKPaymentTransaction *transaction;

//
+ (nullable NSURL *) contentURLForProductID:(NSString *)productID;

// Deletes the content for that identifier from disk
+ (void) deleteContentForProductID:(NSString *)productID;

@end
NS_ASSUME_NONNULL_END
