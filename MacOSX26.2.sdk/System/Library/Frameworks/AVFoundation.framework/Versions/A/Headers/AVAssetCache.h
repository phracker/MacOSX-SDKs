#if !__has_include(<AVFCore/AVAssetCache.h>)
/*
	File:  AVAssetCache.h
 
	Framework:  AVFoundation
 
	Copyright 2016 Apple Inc. All rights reserved.
 
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVMediaSelectionGroup;
@class AVMediaSelectionOption;
@class AVMediaPresentationSelector;
@class AVMediaPresentationSetting;

/// AVAssetCache is a class vended by an AVAsset used for the inspection of locally available media data.
/// 
/// AVAssetCaches are vended by AVURLAsset's assetCache property.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(10.0), visionos(1.0))
@interface AVAssetCache : NSObject

/// Returns YES if a complete rendition of an AVAsset is available to be played without a network connection.
/// 
/// An answer of YES does not indicate that any given media selection is available for offline playback. To determine if a specific media selection is available offline, see mediaSelectionOptionsInMediaSelectionGroup:.
@property (nonatomic, readonly, getter=isPlayableOffline) BOOL playableOffline;

/// Returns an array of AVMediaSelectionOptions in an AVMediaSelectionGroup that are available for offline operations, e.g. playback.
- (NSArray<AVMediaSelectionOption *> *)mediaSelectionOptionsInMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup;

AV_INIT_UNAVAILABLE

@end

@interface AVAssetCache (AVAssetCacheCustomMediaSelectionScheme)

/// For each AVMediaPresentationSelector defined by the AVCustomMediaSelectionScheme of an AVMediaSelectionGroup, returns the AVMediaPresentationSettings that can be satisfied for offline operations, e.g. playback.
- (NSDictionary <AVMediaPresentationSelector *, NSArray<AVMediaPresentationSetting *> *> *)mediaPresentationSettingsForMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// Returns an array of extended language tags for languages that can be selected for offline operations via use of the AVMediaSelectionGroup's AVCustomMediaSelectionScheme.
- (NSArray <NSString *> *)mediaPresentationLanguagesForMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVAssetCache.h>
#endif
