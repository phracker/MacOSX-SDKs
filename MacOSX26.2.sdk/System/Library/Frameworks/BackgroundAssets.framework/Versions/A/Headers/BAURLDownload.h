//
//  BAURLDownload.h
//  BackgroundAssets
//
//  Copyright (c) 2022, Apple Inc.
//  All rights reserved.
//

#import <BackgroundAssets/BackgroundAssets.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_SENDABLE
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos)
@interface BAURLDownload : BADownload<NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// @abstract Constructs a download object to represent the download of a asset located inside of the provided @c request.
/// @param identifier A unique identifier that is used to track the download across the app and extension.
/// @param request The request used to perform the download. The URL provided inside of the request must be a https scheme.
/// @param fileSize The size of the file to download. This field must be accurate in order to show the user accurate progress during app installation.
/// If the size does not match the file being downloaded, then the download will fail.
/// @param applicationGroupIdentifier The identifier of the application group that should used to store the finished download.
- (instancetype)initWithIdentifier:(NSString *)identifier
                           request:(NSURLRequest *)request
                          fileSize:(NSUInteger)fileSize
        applicationGroupIdentifier:(NSString *)applicationGroupIdentifier
API_AVAILABLE(macos(13.3), ios(16.4), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

/// @abstract Constructs a download object to represent the download of a asset located inside of the provided @c request.
/// @param identifier A unique identifier that is used to track the download across the app and extension.
/// @param request The request used to perform the download. The URL provided inside of the request must be a https scheme.
/// @param essential Whether the download is essential. See @c BADownload.isEssential. Default is false.
/// @param fileSize The size of the file to download. This field must be accurate in order to show the user accurate progress during app installation.
/// If the size does not match the file being downloaded, then the download will fail.
/// @param applicationGroupIdentifier The identifier of the application group that should used to store the finished download.
/// @param priority A priority between @c BADownloaderPriorityMin - @c BADownloaderPriorityMax which is used to order the downloads for this process.
/// It is recommended to use  @c BADownloaderPriorityDefault if download priority does not matter.
- (instancetype)initWithIdentifier:(NSString *)identifier
                           request:(NSURLRequest *)request
                         essential:(BOOL)essential
                          fileSize:(NSUInteger)fileSize
        applicationGroupIdentifier:(NSString *)applicationGroupIdentifier
                          priority:(BADownloaderPriority)priority
NS_DESIGNATED_INITIALIZER
API_AVAILABLE(macos(13.3), ios(16.4), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

#pragma mark -
#pragma mark Deprecated APIs

/// @abstract Constructs a download object to represent the download of a asset located inside of the provided @c request.
/// @param identifier A unique identifier that is used to track the download across the app and extension.
/// @param request The request used to perform the download. The URL provided inside of the request must be a https scheme.
/// @param applicationGroupIdentifier The identifier of the application group that should used to store the finished download.
- (instancetype)initWithIdentifier:(NSString *)identifier
                           request:(NSURLRequest *)request
        applicationGroupIdentifier:(NSString *)applicationGroupIdentifier
API_DEPRECATED_WITH_REPLACEMENT("initWithIdentifier:request:fileSize:applicationGroupIdentifier:", ios(16.1, 16.4), macos(13.0, 13.3))
API_UNAVAILABLE(tvos, watchos, visionos);

/// @abstract Constructs a download object to represent the download of a asset located inside of the provided @c request.
/// @param identifier A unique identifier that is used to track the download across the app and extension.
/// @param request The request used to perform the download. The URL provided inside of the request must be a https scheme.
/// @param applicationGroupIdentifier The identifier of the application group that should used to store the finished download.
/// @param priority A priority between @c BADownloaderPriorityMin - @c BADownloaderPriorityMax which is used to order the downloads for this process.
/// It is recommended to use  @c BADownloaderPriorityDefault if download priority does not matter.
- (instancetype)initWithIdentifier:(NSString *)identifier
                           request:(NSURLRequest *)request
        applicationGroupIdentifier:(NSString *)applicationGroupIdentifier
                          priority:(BADownloaderPriority)priority
API_DEPRECATED_WITH_REPLACEMENT("initWithIdentifier:request:essential:fileSize:applicationGroupIdentifier:priority:", ios(16.1, 16.4), macos(13.0, 13.3))
API_UNAVAILABLE(tvos, watchos, visionos);

@end

NS_ASSUME_NONNULL_END
