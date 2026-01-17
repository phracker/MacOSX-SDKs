//
//  BAAppExtensionInfo.h
//  BackgroundAssets
//
//  Copyright (c) 2022, Apple Inc.
//  All rights reserved.
//

#import <BackgroundAssets/BackgroundAssets.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos)
NS_SWIFT_SENDABLE
@interface BAAppExtensionInfo : NSObject <NSSecureCoding>

/// @brief The number of bytes remaining that can be scheduled if the total download size is restricted.
/// @discussion When a download is restricted, your extension can only schedule up to its `BADownloadAllowance`
/// defined in your app's `Info.plist`. This result tells you the number of bytes remaining that can be scheduled
/// before the application is launched. Once the application is launched, this restriction is removed.
/// @result The result is `nil` if downloads are not restricted. It returns a valid number with the remaining available download size otherwise.
@property (readonly, strong, nullable) NSNumber *restrictedDownloadSizeRemaining
NS_REFINED_FOR_SWIFT;

/// @brief The number of bytes remaining that can be scheduled if the total download size of optional assets is restricted.
/// @discussion When a download is restricted, your extension can only schedule up to its `BAEssentialDownloadAllowance`
/// defined in your app's `Info.plist`. This result tells you the number of bytes remaining that can be scheduled
/// before the application is launched. Once the application is launched, this restriction is removed.
/// @result The result is `nil` if downloads are not restricted. It returns a valid number with the remaining available download size otherwise.
@property (readonly, strong, nullable) NSNumber *restrictedEssentialDownloadSizeRemaining
API_AVAILABLE(macos(13.3), ios(16.4), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT;

- (instancetype)init
NS_UNAVAILABLE;

+ (instancetype)new
NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
