#if !__has_include(<AVFCore/AVPlayerItemTrack.h>)
/*
	File:  AVPlayerItemTrack.h

	Framework:  AVFoundation
 
	Copyright 2010-2021 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

@class AVPlayerImageProvider;
@class AVAssetTrack;
@class AVPlayerItemTrackInternal;

NS_ASSUME_NONNULL_BEGIN

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
API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0))
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
@property (nonatomic, readonly, nullable) AVAssetTrack *assetTrack;

/*!
 @property		enabled
 @abstract		Indicates whether the track is enabled for presentation during playback.
 @discussion	This property must be accessed on the main thread/queue.
*/
@property (nonatomic, assign, getter=isEnabled) BOOL enabled NS_SWIFT_UI_ACTOR;

/*!
 @property		currentVideoFrameRate
 @abstract		If the media type of the assetTrack is AVMediaTypeVideo, indicates the current frame rate of the track as it plays, in units of frames per second. If the item is not playing, or if the media type of the track is not video, the value of this property is 0.
 @discussion	This property is not observable.

 This property must be accessed on the main thread/queue.
*/
@property (nonatomic, readonly) float currentVideoFrameRate NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/*!
 @constant		AVPlayerItemTrackVideoFieldModeDeinterlaceFields
 @abstract		Use with videoFieldMode property to request deinterlacing of video fields.
*/
AVF_EXPORT NSString *const AVPlayerItemTrackVideoFieldModeDeinterlaceFields API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
 @property		videoFieldMode
 @abstract		If the media type of the assetTrack is AVMediaTypeVideo, specifies the handling of video frames that contain multiple fields.
 @discussion	A value of nil indicates default processing of video frames. If you want video fields to be deinterlaced, set videoFieldMode to AVPlayerItemTrackVideoFieldModeDeinterlaceFields.
 				You can test whether video being played has multiple fields by examining the underlying AVAssetTrack's format descriptions. See -[AVAssetTrack formatDescriptions] and, for video format descriptions, kCMFormatDescriptionExtension_FieldCount.
 
 This property must be accessed on the main thread/queue.
*/
@property (nonatomic, copy, nullable) NSString *videoFieldMode NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos);

#endif

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVPlayerItemTrack.h>
#endif
