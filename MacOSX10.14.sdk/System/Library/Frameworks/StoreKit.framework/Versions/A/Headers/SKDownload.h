//
//  SKDownload.h
//  StoreKit
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class SKPaymentTransaction;

typedef NS_ENUM(NSInteger, SKDownloadState) {
    SKDownloadStateWaiting,     // Download is inactive, waiting to be downloaded
    SKDownloadStateActive,      // Download is actively downloading
    SKDownloadStatePaused,      // Download was paused by the user
    SKDownloadStateFinished,    // Download is finished, content is available
    SKDownloadStateFailed,      // Download failed
    SKDownloadStateCancelled,   // Download was cancelled
} NS_AVAILABLE(10_8, 6_0);

SK_EXTERN NSTimeInterval SKDownloadTimeRemainingUnknown NS_AVAILABLE(10_14, 6_0);

SK_EXTERN_CLASS_AVAILABLE(10_8, 6_0) @interface SKDownload : NSObject {
@private
    id _internal;
}

// State of the download
@property(nonatomic, readonly) SKDownloadState state NS_AVAILABLE(10_8, 12_0);
@property(nonatomic, readonly) SKDownloadState downloadState NS_DEPRECATED_IOS(6_0, 12_0, "Use [SKDownload state] instead");

// Total size of the content, in bytes
#if TARGET_OS_OSX
@property(nonatomic, copy, readonly) NSNumber *contentLength NS_AVAILABLE_MAC(10_8);
#else
@property(nonatomic, readonly) long long contentLength NS_AVAILABLE_IOS(6_0);
#endif

// Identifier for this content
@property(nonatomic, readonly) NSString *contentIdentifier NS_AVAILABLE(10_8, 6_0);

// Location of the content data, if state is SKDownloadStateFinished
@property(nonatomic, readonly, nullable) NSURL *contentURL NS_AVAILABLE(10_8, 6_0);

// Content version
@property(nonatomic, readonly) NSString *contentVersion NS_AVAILABLE(10_8, 6_0);

// Failure error, if state is SKDownloadStateFailed
@property(nonatomic, readonly, nullable) NSError *error NS_AVAILABLE(10_8, 6_0);

// Overall progress for the download [0..1]
@property(nonatomic, readonly) float progress NS_AVAILABLE(10_8, 6_0);

// Estimated time remaining to complete the download, in seconds.  Value is SKDownloadTimeRemainingUnknown if estimate is unknownxx.
@property(nonatomic, readonly) NSTimeInterval timeRemaining NS_AVAILABLE(10_8, 6_0);

// Transaction for this download
@property(nonatomic, readonly) SKPaymentTransaction *transaction NS_AVAILABLE(10_11, 6_0);


+ (nullable NSURL *)contentURLForProductID:(NSString *)productID NS_AVAILABLE_MAC(10_8);

// Deletes the content for that identifier from disk
+ (void)deleteContentForProductID:(NSString *)productID NS_AVAILABLE_MAC(10_8);
@end

NS_ASSUME_NONNULL_END
