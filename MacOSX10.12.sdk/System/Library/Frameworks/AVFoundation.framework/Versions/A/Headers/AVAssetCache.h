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

/*!
	@class		AVAssetCache

	@abstract
		AVAssetCache is a class vended by an AVAsset used for the inspection of locally available media data.

	@discussion
		AVAssetCaches are vended by AVURLAsset's assetCache property.

*/
NS_CLASS_AVAILABLE(10_12, 10_0)
@interface AVAssetCache : NSObject

/*
	@property	playableOffline
	@abstract
		Returns YES if a complete rendition of an AVAsset is available to be played without a network connection.
	@discussion
		An answer of YES does not indicate that any given media selection is available for offline playback. To determine if a specific media selection is available offline, see mediaSelectionOptionsInMediaSelectionGroup:.
*/
@property (nonatomic, readonly, getter=isPlayableOffline) BOOL playableOffline;

/*
	@method		mediaSelectionOptionsInMediaSelectionGroup:
	@abstract
		Returns an array of AVMediaSelectionOptions in an AVMediaSelectionGroup that are available for offline operations, e.g. playback.
*/
- (NSArray<AVMediaSelectionOption *> *)mediaSelectionOptionsInMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup;

AV_INIT_UNAVAILABLE

@end

NS_ASSUME_NONNULL_END
