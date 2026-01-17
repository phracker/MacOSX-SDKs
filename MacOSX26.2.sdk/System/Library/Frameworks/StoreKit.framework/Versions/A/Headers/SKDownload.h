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

typedef NS_CLOSED_ENUM(NSInteger, SKDownloadState) {
    SKDownloadStateWaiting,     // Download is inactive, waiting to be downloaded
    SKDownloadStateActive,      // Download is actively downloading
    SKDownloadStatePaused,      // Download was paused by the user
    SKDownloadStateFinished,    // Download is finished, content is available
    SKDownloadStateFailed,      // Download failed
    SKDownloadStateCancelled,   // Download was cancelled
} API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.8, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);

SK_EXTERN NSTimeInterval SKDownloadTimeRemainingUnknown API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.14, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);

SK_EXTERN_CLASS API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.8, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos) @interface SKDownload : NSObject {
@private
    id _internal;
}

// State of the download
@property(nonatomic, readonly) SKDownloadState state API_DEPRECATED("Hosted content is no longer supported.", ios(12.0, 16.0), macos(10.8, 13.0), tvos(12.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);
@property(nonatomic, readonly) SKDownloadState downloadState API_DEPRECATED_WITH_REPLACEMENT("-[SKDownload state]", ios(6.0, 12.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(macos, watchos);

// Total size of the content, in bytes
#if TARGET_OS_OSX
@property(nonatomic, copy, readonly) NSNumber *contentLength API_DEPRECATED_WITH_REPLACEMENT("-[SKDownload expectedContentLength]", macos(10.8, 10.15)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(ios, watchos, tvos);
#else
@property(nonatomic, readonly) long long contentLength API_DEPRECATED_WITH_REPLACEMENT("-[SKDownload expectedContentLength]", ios(6.0, 13.0), tvos(9.0, 13.0), macCatalyst(13.0, 13.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(macos, watchos);
#endif

// Total size of the content, in bytes
@property(nonatomic, readonly) long long expectedContentLength API_DEPRECATED("Hosted content is no longer supported.", ios(13.0, 16.0), macos(10.15, 13.0), tvos(13.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);

// Identifier for this content
@property(nonatomic, readonly) NSString *contentIdentifier API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.8, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);

// Location of the content data, if state is SKDownloadStateFinished
@property(nonatomic, readonly, nullable) NSURL *contentURL API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.8, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);

// Content version
@property(nonatomic, readonly) NSString *contentVersion API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.8, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);

// Failure error, if state is SKDownloadStateFailed
@property(nonatomic, readonly, nullable) NSError *error API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.8, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);

// Overall progress for the download [0..1]
@property(nonatomic, readonly) float progress API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.8, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);

// Estimated time remaining to complete the download, in seconds.  Value is SKDownloadTimeRemainingUnknown if estimate is unknownxx.
@property(nonatomic, readonly) NSTimeInterval timeRemaining API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.8, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);

// Transaction for this download
@property(nonatomic, readonly) SKPaymentTransaction *transaction API_DEPRECATED("Hosted content is no longer supported.", ios(6.0, 16.0), macos(10.11, 13.0), tvos(9.0, 16.0), watchos(6.2, 9.0)) API_UNAVAILABLE(visionos);


+ (nullable NSURL *)contentURLForProductID:(NSString *)productID API_DEPRECATED("Hosted content is no longer supported.", macos(10.8, 13.0), macCatalyst(13.0, 16.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(ios, tvos, watchos);

// Deletes the content for that identifier from disk
+ (void)deleteContentForProductID:(NSString *)productID API_DEPRECATED("Hosted content is no longer supported.", macos(10.8, 13.0), macCatalyst(13.0, 16.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(ios, tvos, watchos);
@end

NS_ASSUME_NONNULL_END
