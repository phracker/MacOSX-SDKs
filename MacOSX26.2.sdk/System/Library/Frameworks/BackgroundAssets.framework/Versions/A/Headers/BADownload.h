//
//  BADownload.h
//  BackgroundAssets
//
//  Copyright (c) 2022, Apple Inc.
//  All rights reserved.
//

#import <BackgroundAssets/BackgroundAssets.h>

NS_ASSUME_NONNULL_BEGIN

/// @typedef Download state
typedef NS_ENUM(NSInteger, BADownloadState) {
    BADownloadStateFailed = -1,
    BADownloadStateCreated = 0,
    BADownloadStateWaiting,
    BADownloadStateDownloading,
    BADownloadStateFinished,
}
NS_SWIFT_NAME(BADownload.State);

/// @brief A download's priority
/// @discussion The priority applied to a given download or group of downloads. This is a range from `BADownloaderPriorityMin` to `BADownloaderPriorityMax`.
/// The priority only applies to how downloads are ordered for your application. Higher priority items will be enqued for download before lower priority items regardless of order in which they are scheduled.
typedef NSInteger BADownloaderPriority NS_TYPED_EXTENSIBLE_ENUM
NS_SWIFT_NAME(BADownload.Priority);

/// @brief A value that represents the lowest priority for a download.
FOUNDATION_EXPORT const BADownloaderPriority BADownloaderPriorityMin
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

/// @brief A value that represents average priority for a download.
FOUNDATION_EXPORT const BADownloaderPriority BADownloaderPriorityDefault
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

/// @brief A value that represents the highest priority for a download.
FOUNDATION_EXPORT const BADownloaderPriority BADownloaderPriorityMax
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

NS_SWIFT_SENDABLE
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos)
@interface BADownload : NSObject<NSCoding, NSSecureCoding, NSCopying>

/// @brief The current state of the respresented download.
@property (readonly, nonatomic) BADownloadState state
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

/// @brief A client defined identifier that uniquely identifies this asset.
@property (readonly, nonatomic) NSString *identifier
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

/// @brief A UUID that uniquely identifies the download object.
@property (readonly, nonatomic) NSString *uniqueIdentifier
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

/// @brief A client set priority to try to order downloads in order of importance
@property (readonly) BADownloaderPriority priority
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

/// @brief Whether this download is essential.
/// Essential downloads will occur while the app is being installed. Users cannot launch the app while these downloads are occurring.
/// Essential downloads cannot be scheduled with `BADownloadManager`, they may only be scheduled from the extension with
/// a `BAContentRequest` type of `Update` or `Install`.
/// Essential downloads must have an accurate `fileSize` or they will fail.
@property (readonly) BOOL isEssential
API_AVAILABLE(macos(13.3), ios(16.4), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

/// @brief Copies an existing download ensuring that it has `isEssential == false`.
/// @discussion This serves as a convenience method for constructing a non-essential representation of an existing
/// download. It is important to note that essential downloads can only be enqueued by
/// the app extension during a content request. If an essential download fails, `copyAsNonEssential`
/// can be used to create a copy with `isEssential == false` that can be re-queued with `BADownloadManager`.
- (instancetype)copyAsNonEssential
API_AVAILABLE(macos(13.3), ios(16.4), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(removingEssential());

- (instancetype)init
NS_UNAVAILABLE;

+ (instancetype)new
NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
