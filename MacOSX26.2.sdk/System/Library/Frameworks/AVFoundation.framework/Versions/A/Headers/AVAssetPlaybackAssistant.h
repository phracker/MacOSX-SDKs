#if !__has_include(<AVFCore/AVAssetPlaybackAssistant.h>)
/*
	File:  AVAssetPlaybackAssistant.h

	Framework:  AVFoundation
 
	Copyright 2021-2025 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

@class AVAsset;

NS_ASSUME_NONNULL_BEGIN

typedef NSString *AVAssetPlaybackConfigurationOption NS_STRING_ENUM API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/// Indicates whether or not the asset can be rendered as stereo video.
/// 
/// Clients may use this property to determine whether to configure stereo video rendering.
AVF_EXPORT AVAssetPlaybackConfigurationOption const AVAssetPlaybackConfigurationOptionStereoVideo API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/// Indicates whether or not the asset can rendered as stereo video and is also in a multiview compression format.
/// 
/// Clients may use this property to determine whether to configure stereo video rendering.
AVF_EXPORT AVAssetPlaybackConfigurationOption const AVAssetPlaybackConfigurationOptionStereoMultiviewVideo API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/// Indicates whether or not the asset can be rendered as spatial video.
/// 
/// Clients may use this property to determine whether to configure spatial video rendering.
AVF_EXPORT AVAssetPlaybackConfigurationOption const AVAssetPlaybackConfigurationOptionSpatialVideo API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/// Indicates whether the asset calls for the use of a non-rectilinear projection for rendering video.
/// 
/// Clients may use this property to determine whether to configure a non-rectilinear projection when displaying video.
AVF_EXPORT AVAssetPlaybackConfigurationOption const AVAssetPlaybackConfigurationOptionNonRectilinearProjection API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);

/// Indicates whether the asset is Apple Immersive Video.
/// 
/// Clients may use this property to switch into specific display and control modes for Apple Immersive Video playback.
AVF_EXPORT AVAssetPlaybackConfigurationOption const AVAssetPlaybackConfigurationOptionAppleImmersiveVideo API_AVAILABLE(macos(26.0), visionos(26.0)) API_UNAVAILABLE(ios, tvos, watchos);

/// AVAssetPlaybackAssistant provides playback information for an asset.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0))
@interface AVAssetPlaybackAssistant : NSObject

AV_INIT_UNAVAILABLE

/// Returns an instance of AVAssetPlaybackAssistant for inspection of an AVAsset object.
/// 
/// - Parameter asset: An instance of AVAsset.
/// 
/// - Returns: An instance of AVAssetPlaybackAssistant.
+ (instancetype)assetPlaybackAssistantWithAsset:(AVAsset *)asset;

/// Calls the completionHandler with information about the asset.
/// 
/// completionHandler is called when all of the AVAssetPlaybackConfigurationOption values have been loaded. If AVAssetPlaybackAssistant encounters failures when inspecting the contents of the asset, it will return no AVAssetPlaybackConfigurationOptions associated with those contents.
/// 
/// - Parameter completionHandler: Called with an array of AVAssetPlaybackConfigurationOption values describing capabilities of the asset.
- (void)loadPlaybackConfigurationOptionsWithCompletionHandler:(void (^ NS_SWIFT_SENDABLE)(NSArray<AVAssetPlaybackConfigurationOption> *playbackConfigurationOptions))completionHandler NS_SWIFT_ASYNC_NAME(getter:playbackConfigurationOptions());

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVAssetPlaybackAssistant.h>
#endif
