/*
	File:  AVPlayerItemTrack.h

	Framework:  AVFoundation
 
	Copyright 2010 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

@class AVPlayerImageProvider;
@class AVAssetTrack;
@class AVPlayerItemTrackInternal;

/*!
	@class			AVPlayerItemTrack

	@abstract
		An AVPlayerItemTrack carries a reference to an AVAssetTrack as well as presentation settings for that track.

	@discussion
		Note that inspection of assets tracks is provided by AVAssetTrack.
		This class is intended to represent presentation state for a track of an asset that's played by an AVPlayer and AVPlayerItem.

		To ensure safe access to AVPlayerItemTrack's nonatomic properties while dynamic changes in playback state may be reported,
		clients must serialize their access with the associated AVPlayer's notification queue. In the common case, such serialization
		is naturally achieved by invoking AVPlayerItemTrack's various methods on the main thread or queue.
*/
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVPlayerItemTrack : NSObject
{
@private
	AVPlayerItemTrackInternal	*_playerItemTrack;
}

/*!
 @property		assetTrack
 @abstract		Indicates the AVAssetTrack for which the AVPlayerItemTrack represents presentation state.
 @discussion	This property is not observable.
	Clients must serialize their access to the resulting AVAssetTrack and related objects on the associated AVPlayer's
	notification queue.  By default, this queue is the main queue.
 */
@property (nonatomic, readonly) AVAssetTrack *assetTrack;

/*!
 @property		enabled
 @abstract		Indicates whether the track is enabled for presentation during playback.
 */
@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

@end
