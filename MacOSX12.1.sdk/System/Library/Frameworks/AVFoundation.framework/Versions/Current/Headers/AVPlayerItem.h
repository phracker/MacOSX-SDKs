#if !__has_include(<AVFCore/AVPlayerItem.h>)
/*
    File:  AVPlayerItem.h

	Framework:  AVFoundation
 
	Copyright 2010-2021 Apple Inc. All rights reserved.

*/

/*!
	@class			AVPlayerItem

	@abstract
	  An AVPlayerItem carries a reference to an AVAsset as well as presentation settings for that asset.

	@discussion
	  Note that inspection of media assets is provided by AVAsset.
	  This class is intended to represent presentation state for an asset that's played by an AVPlayer and to permit observation of that state.
 
  	  It is important to avoid key-value observation with a key path containing the asset's property.  Observe the AVPlayerItem's property instead.  For example, use the "duration" key path instead of the "asset.duration" key path.
 
	  To allow clients to add and remove their objects as key-value observers safely, AVPlayerItem serializes notifications of
	  changes that occur dynamically during playback on the same dispatch queue on which notifications of playback state changes
	  are serialized by its associated AVPlayer. By default, this queue is the main queue. See dispatch_get_main_queue().
	  
	  To ensure safe access to AVPlayerItem's nonatomic properties while dynamic changes in playback state may be reported, clients must
	  serialize their access with the associated AVPlayer's notification queue. In the common case, such serialization is naturally
	  achieved by invoking AVPlayerItem's various methods on the main thread or queue.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAudioProcessingSettings.h>
#import <AVFoundation/AVVideoSettings.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>
#import <CoreMedia/CMSync.h>
#import <CoreGraphics/CGGeometry.h>

NS_ASSUME_NONNULL_BEGIN

/* Note that NSNotifications posted by AVPlayerItem may be posted on a different thread from the one on which the observer was registered. */

// notifications                                                                                description
AVF_EXPORT NSNotificationName const AVPlayerItemTimeJumpedNotification	 API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0), watchos(1.0));	// the item's current time has changed discontinuously
AVF_EXPORT NSString *const AVPlayerItemDidPlayToEndTimeNotification      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));   // item has played to its end time
AVF_EXPORT NSString *const AVPlayerItemFailedToPlayToEndTimeNotification API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0));   // item has failed to play to its end time
AVF_EXPORT NSString *const AVPlayerItemPlaybackStalledNotification       API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0), watchos(1.0));    // media did not arrive in time to continue playback
AVF_EXPORT NSString *const AVPlayerItemNewAccessLogEntryNotification	 API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0), watchos(1.0));	// a new access log entry has been added
AVF_EXPORT NSString *const AVPlayerItemNewErrorLogEntryNotification		 API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0), watchos(1.0));	// a new error log entry has been added
AVF_EXPORT NSNotificationName const AVPlayerItemRecommendedTimeOffsetFromLiveDidChangeNotification		 API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));	// the value of recommendedTimeOffsetFromLive has changed
AVF_EXPORT NSNotificationName const AVPlayerItemMediaSelectionDidChangeNotification		API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0)); // a media selection group changed its selected option


// notification userInfo key                                                                    type
AVF_EXPORT NSString *const AVPlayerItemFailedToPlayToEndTimeErrorKey     API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0));   // NSError
/**
 @constant AVPlayerItemTimeJumpedOriginatingParticipantKey
 @abstract Indicates a time jump was caused by another participant connected through AVPlayerPlaybackCoordinator.
 @discussion Informs the receiver of an AVPlayerItemTimeJumpedNotification that a time jump originated from another AVCoordinatedPlaybackParticipant connected through AVPlayerPlaybackCoordinator. This can be used to inform UI showing why the current time changed. The type of the value for this key is an AVCoordinatedPlaybackParticipant, which is part of the AVPlayerPlaybackCoordinator.otherParticipants array.
 */
AVF_EXPORT NSString *const AVPlayerItemTimeJumpedOriginatingParticipantKey API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/*!
 @enum AVPlayerItemStatus
 @abstract
	These constants are returned by the AVPlayerItem status property to indicate whether it can successfully be played.
 
 @constant	 AVPlayerItemStatusUnknown
	Indicates that the status of the player item is not yet known because it has not tried to load new media resources
	for playback.
 @constant	 AVPlayerItemStatusReadyToPlay
	Indicates that the player item is ready to be played.
 @constant	 AVPlayerItemStatusFailed
	Indicates that the player item can no longer be played because of an error. The error is described by the value of
	the player item's error property.
 */
typedef NS_ENUM(NSInteger, AVPlayerItemStatus) {
	AVPlayerItemStatusUnknown = 0,
	AVPlayerItemStatusReadyToPlay = 1,
	AVPlayerItemStatusFailed = 2
};

@class AVPlayer;
@class AVAsset;
@class AVAssetTrack;
@class AVAudioMix;
@class AVVideoComposition;
@class AVMediaSelection;
@class AVMediaSelectionGroup;
@class AVMediaSelectionOption;
@class AVPlayerItemInternal;
@protocol AVVideoCompositing;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0))
@interface AVPlayerItem : NSObject <NSCopying>
{
@private
	AVPlayerItemInternal* _playerItem;
}
AV_INIT_UNAVAILABLE

/*!
 @method		playerItemWithURL:
 @abstract		Returns an instance of AVPlayerItem for playing a resource at the specified location.
 @param			URL
 @result		An instance of AVPlayerItem.
 @discussion	Equivalent to +playerItemWithAsset:, passing [AVAsset assetWithURL:URL] as the value of asset.
 */
+ (instancetype)playerItemWithURL:(NSURL *)URL;

/*!
 @method		playerItemWithAsset:
 @abstract		Returns an instance of AVPlayerItem for playing an AVAsset.
 @param			asset
 @result		An instance of AVPlayerItem.
 @discussion	Equivalent to +playerItemWithAsset:automaticallyLoadedAssetKeys:, passing @[ @"duration" ] as the value of automaticallyLoadedAssetKeys.
  */
+ (instancetype)playerItemWithAsset:(AVAsset *)asset;

/*!
 @method		playerItemWithAsset:automaticallyLoadedAssetKeys:
 @abstract		Returns an instance of AVPlayerItem for playing an AVAsset.
 @param			asset
 @param			automaticallyLoadedAssetKeys
 				An NSArray of NSStrings, each representing a property key defined by AVAsset. See AVAsset.h for property keys, e.g. duration.
 @result		An instance of AVPlayerItem.
 @discussion	The value of each key in automaticallyLoadedAssetKeys will be automatically be loaded by the underlying AVAsset before the receiver achieves the status AVPlayerItemStatusReadyToPlay; i.e. when the item is ready to play, the value of -[[AVPlayerItem asset] statusOfValueForKey:error:] will be one of the terminal status values greater than AVKeyValueStatusLoading.
 */
+ (instancetype)playerItemWithAsset:(AVAsset *)asset automaticallyLoadedAssetKeys:(nullable NSArray<NSString *> *)automaticallyLoadedAssetKeys API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
 @method		initWithURL:
 @abstract		Initializes an AVPlayerItem with an NSURL.
 @param			URL
 @result		An instance of AVPlayerItem
 @discussion	Equivalent to -initWithAsset:, passing [AVAsset assetWithURL:URL] as the value of asset.
 */
- (instancetype)initWithURL:(NSURL *)URL;

/*!
 @method		initWithAsset:
 @abstract		Initializes an AVPlayerItem with an AVAsset.
 @param			asset
 @result		An instance of AVPlayerItem
 @discussion	Equivalent to -initWithAsset:automaticallyLoadedAssetKeys:, passing @[ @"duration" ] as the value of automaticallyLoadedAssetKeys.
 */
- (instancetype)initWithAsset:(AVAsset *)asset;

/*!
 @method		initWithAsset:automaticallyLoadedAssetKeys:
 @abstract		Initializes an AVPlayerItem with an AVAsset.
 @param			asset
 				An instance of AVAsset.
 @param			automaticallyLoadedAssetKeys
 				An NSArray of NSStrings, each representing a property key defined by AVAsset. See AVAsset.h for property keys, e.g. duration.
 @result		An instance of AVPlayerItem
 @discussion	The value of each key in automaticallyLoadedAssetKeys will be automatically be loaded by the underlying AVAsset before the receiver achieves the status AVPlayerItemStatusReadyToPlay; i.e. when the item is ready to play, the value of -[[AVPlayerItem asset] statusOfValueForKey:error:] will be one of the terminal status values greater than AVKeyValueStatusLoading.
 */
- (instancetype)initWithAsset:(AVAsset *)asset automaticallyLoadedAssetKeys:(nullable NSArray<NSString *> *)automaticallyLoadedAssetKeys NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

- (id)copyWithZone:(nullable NSZone *)zone NS_SWIFT_UI_ACTOR;
- (id)copy NS_SWIFT_UI_ACTOR;

/*!
 @property status
 @abstract
	The ability of the receiver to be used for playback.
 
 @discussion
	The value of this property is an AVPlayerItemStatus that indicates whether the receiver can be used for playback.
	When the value of this property is AVPlayerItemStatusFailed, the receiver can no longer be used for playback and
	a new instance needs to be created in its place. When this happens, clients can check the value of the error
	property to determine the nature of the failure. The value of this property will not be updated after the receiver
	is removed from an AVPlayer. This property is key value observable.
 */
@property (readonly) AVPlayerItemStatus status;

/*!
 @property error
 @abstract
	If the receiver's status is AVPlayerItemStatusFailed, this describes the error that caused the failure.
 
 @discussion
	The value of this property is an NSError that describes what caused the receiver to no longer be able to be played.
	If the receiver's status is not AVPlayerItemStatusFailed, the value of this property is nil.
 */
@property (readonly, nullable) NSError *error;

@end


@class AVPlayerItemTrack;
@class AVMetadataItem;

@interface AVPlayerItem (AVPlayerItemInspection)

/*!
 @property asset
 @abstract Accessor for underlying AVAsset.
 */
@property (nonatomic, readonly) AVAsset *asset;

/*!
 @property tracks
 @abstract Provides array of AVPlayerItem tracks. Observable (can change dynamically during playback).
	
 @discussion
	The value of this property will accord with the properties of the underlying media resource when the receiver becomes ready to play.
	Before the underlying media resource has been sufficiently loaded, its value is an empty NSArray. Use key-value observation to obtain
	a valid array of tracks as soon as it becomes available.
 */
@property (readonly) NSArray<AVPlayerItemTrack *> *tracks;

/*!
 @property duration
 @abstract Indicates the duration of the item, not considering either its forwardPlaybackEndTime or reversePlaybackEndTime.
 
 @discussion
	This property is observable. The duration of an item can change dynamically during playback.
	
	Unless you omit @"duration" from the array of asset keys you pass to +playerItemWithAsset:automaticallyLoadedAssetKeys: or
	-initWithAsset:automaticallyLoadedAssetKeys:, the value of this property will accord with the properties of the underlying
	AVAsset and the current state of playback once the receiver becomes ready to play.

	Before the underlying duration has been loaded, the value of this property is kCMTimeIndefinite. Use key-value observation to
	obtain a valid duration as soon as it becomes available. (Note that the value of duration may remain kCMTimeIndefinite,
	e.g. for live streams.)
 */
@property (readonly) CMTime duration API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0));

/*!
 @property presentationSize
 @abstract The size of the receiver as presented by the player.
 
 @discussion 
	Indicates the size at which the visual portion of the item is presented by the player; can be scaled from this 
	size to fit within the bounds of an AVPlayerLayer via its videoGravity property. Can be scaled arbitarily for presentation
	via the frame property of an AVPlayerLayer.
	
	The value of this property will accord with the properties of the underlying media resource when the receiver becomes ready to play.
	Before the underlying media resource is sufficiently loaded, its value is CGSizeZero. Use key-value observation to obtain a valid
	presentationSize as soon as it becomes available. (Note that the value of presentationSize may remain CGSizeZero, e.g. for audio-only items.)
 */
@property (readonly) CGSize presentationSize;

/*!
 @property timedMetadata
 @abstract Provides an NSArray of AVMetadataItems representing the timed metadata encountered most recently within the media as it plays. May be nil.
 @discussion
   Notifications of changes are available via key-value observation.
   As an optimization for playback, AVPlayerItem may omit the processing of timed metadata when no observer of this property is registered. Therefore, when no such observer is registered, the value of the timedMetadata property may remain nil regardless of the contents of the underlying media.
 
   This property must be accessed on the main thread/queue.
 */
@property (nonatomic, readonly, nullable) NSArray<AVMetadataItem *> *timedMetadata NS_SWIFT_UI_ACTOR API_DEPRECATED("Use AVPlayerItemMetadataOutput to obtain timed metadata", macos(10.7, 10.15), ios(4.0, 13.0), tvos(9.0, 13.0)) API_UNAVAILABLE(watchos);

/*!
 @property automaticallyLoadedAssetKeys
 @abstract An array of property keys defined on AVAsset. The value of each key in the array is automatically loaded while the receiver is being made ready to play.
 @discussion
   The value of each key in automaticallyLoadedAssetKeys will be automatically be loaded by the underlying AVAsset before the receiver achieves the status AVPlayerItemStatusReadyToPlay; i.e. when the item is ready to play, the value of -[[AVPlayerItem asset] statusOfValueForKey:error:] will be AVKeyValueStatusLoaded. If loading of any of the values fails, the status of the AVPlayerItem will change instead to AVPlayerItemStatusFailed..
 */
@property (nonatomic, readonly) NSArray<NSString *> *automaticallyLoadedAssetKeys API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

@end


@interface AVPlayerItem (AVPlayerItemRateAndSteppingSupport)

/* For releases of OS X prior to 10.9 and releases of iOS prior to 7.0, indicates whether the item can be played at rates greater than 1.0.
   Starting with OS X 10.9 and iOS 7.0, all AVPlayerItems with status AVPlayerItemReadyToPlay can be played at rates between 1.0 and 2.0, inclusive, even if canPlayFastForward is NO; for those releases canPlayFastForward indicates whether the item can be played at rates greater than 2.0.
*/
@property (readonly) BOOL canPlayFastForward API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0));

/* indicates whether the item can be played at rates between 0.0 and 1.0 */
@property (readonly) BOOL canPlaySlowForward API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));

/* indicates whether the item can be played at rate -1.0 */
@property (readonly) BOOL canPlayReverse API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));

/* indicates whether the item can be played at rates less between 0.0 and -1.0 */
@property (readonly) BOOL canPlaySlowReverse API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));

/* indicates whether the item can be played at rates less than -1.0 */
@property (readonly) BOOL canPlayFastReverse API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0));

/* Indicates whether the item supports stepping forward; see -stepByCount:. Once the item has become ready to play, the value of canStepForward does not change even when boundary conditions are reached, such as when the item's currentTime is its end time. */
@property (readonly) BOOL canStepForward API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));

/* indicates whether the item supports stepping backward; see -stepByCount:. Once the item has become ready to play, the value of canStepBackward does not change even when boundary conditions are reached, such as when the item's currentTime is equal to kCMTimeZero. */
@property (readonly) BOOL canStepBackward API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));

/*!
 @property		configuredTimeOffsetFromLive
 @abstract		Indicates how close to the latest content in a live stream playback will begin after a live start or a seek to kCMTimePositiveInfinity.
 @discussion	For non-live assets this value is kCMTimeInvalid.
 */
@property CMTime configuredTimeOffsetFromLive API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property		recommendedTimeOffsetFromLive
 @abstract		A recommended value for configuredTimeOffsetFromLive, based on observed network conditions.
 @discussion	For non-live assets this value is kCMTimeInvalid.
 */
@property (nonatomic, readonly) CMTime recommendedTimeOffsetFromLive API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property		automaticallyPreservesTimeOffsetFromLive
 @abstract		Indicates that after the player spends a period of time buffering media, it will skip forward if necessary to restore the playhead's distance from the live edge of the presentation to what it was when buffering began.
 @discussion
  If the value of this property is YES and the player must buffer media from the network in order to resume playback, the player will seek forward if necessary before resuming playback to restore the position that the playhead had when rebuffering began, relative to the end of the current AVPlayerItem's seekableTimeRange. 

  This behavior applies to media buffering that occurs as a consequence of starting playback, seeking, and recovering from a playback stall.

  Note that if the network cannot deliver media quickly enough to maintain the playback rate, playback may stall interminably.
 
 This property value has no effect if the asset is not a live stream. The default value of this property is NO.
 */

@property (nonatomic) BOOL automaticallyPreservesTimeOffsetFromLive API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0),watchos(6.0));

@end

@interface AVPlayerItem (AVPlayerItemTimeControl)

/*!
 @method			currentTime
 @abstract			Returns the current time of the item.
 @result			A CMTime
 @discussion		Returns the current time of the item. Not key-value observable; use -[AVPlayer addPeriodicTimeObserverForInterval:queue:usingBlock:] instead.
 */
- (CMTime)currentTime;

/*!
 @property forwardPlaybackEndTime
 @abstract
	The end time for forward playback.
 
 @discussion
	Specifies the time at which playback should end when the playback rate is positive (see AVPlayer's rate property).
	The default value is kCMTimeInvalid, which indicates that no end time for forward playback is specified.
	In this case, the effective end time for forward playback is the receiver's duration.
	
	When the end time is reached, the receiver will post AVPlayerItemDidPlayToEndTimeNotification and the AVPlayer will take
	the action indicated by the value of its actionAtItemEnd property (see AVPlayerActionAtItemEnd in AVPlayer.h). 

	The value of this property has no effect on playback when the rate is negative.
 */
@property CMTime forwardPlaybackEndTime;

/*!
 @property reversePlaybackEndTime
 @abstract
	The end time for reverse playback.
 
 @discussion
	Specifies the time at which playback should end when the playback rate is negative (see AVPlayer's rate property).
	The default value is kCMTimeInvalid, which indicates that no end time for reverse playback is specified.
	In this case, the effective end time for reverse playback is kCMTimeZero.

	When the end time is reached, the receiver will post AVPlayerItemDidPlayToEndTimeNotification and the AVPlayer will take
	the action indicated by the value of its actionAtItemEnd property (see AVPlayerActionAtItemEnd in AVPlayer.h). 

	The value of this property has no effect on playback when the rate is positive.
 */
@property CMTime reversePlaybackEndTime;

/*!
 @property seekableTimeRanges
 @abstract This property provides a collection of time ranges that the player item can seek to. The ranges provided might be discontinous.
 @discussion Returns an NSArray of NSValues containing CMTimeRanges.
 */
@property (readonly) NSArray<NSValue *> *seekableTimeRanges;

/*!
 @method			seekToTime:completionHandler:
 @abstract			Moves the playback cursor and invokes the specified block when the seek operation has either been completed or been interrupted.
 @param				time
 @param				completionHandler
 @discussion		Use this method to seek to a specified time for the item and to be notified when the seek operation is complete.
 					The completion handler for any prior seek request that is still in process will be invoked immediately with the finished parameter 
 					set to NO. If the new request completes without being interrupted by another seek request or by any other operation the specified 
 					completion handler will be invoked with the finished parameter set to YES. 
					If the seek time is outside of seekable time ranges as indicated by seekableTimeRanges property, the seek request will be cancelled and the completion handler will be invoked with the finished parameter set to NO.
 */
- (void)seekToTime:(CMTime)time completionHandler:(void (^_Nullable)(BOOL finished))completionHandler API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0), watchos(1.0));

/*!
 @method			seekToTime:toleranceBefore:toleranceAfter:completionHandler:
 @abstract			Moves the playback cursor within a specified time bound and invokes the specified block when the seek operation has either been completed or been interrupted.
 @param				time
 @param				toleranceBefore
 @param				toleranceAfter
 @param				completionHandler
 @discussion		Use this method to seek to a specified time for the item and to be notified when the seek operation is complete.
					The time seeked to will be within the range [time-toleranceBefore, time+toleranceAfter] and may differ from the specified time for efficiency.
					Pass kCMTimeZero for both toleranceBefore and toleranceAfter to request sample accurate seeking which may incur additional decoding delay. 
					Messaging this method with beforeTolerance:kCMTimePositiveInfinity and afterTolerance:kCMTimePositiveInfinity is the same as messaging seekToTime: directly.
					The completion handler for any prior seek request that is still in process will be invoked immediately with the finished parameter set to NO. If the new 
					request completes without being interrupted by another seek request or by any other operation the specified completion handler will be invoked with the 
					finished parameter set to YES.
					If the seek time is outside of seekable time ranges as indicated by seekableTimeRanges property, the seek request will be cancelled and the completion handler will be invoked with the finished parameter set to NO.
 */
- (void)seekToTime:(CMTime)time toleranceBefore:(CMTime)toleranceBefore toleranceAfter:(CMTime)toleranceAfter completionHandler:(void (^_Nullable)(BOOL finished))completionHandler API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0), watchos(1.0));

/*!
 @method			cancelPendingSeeks
 @abstract			Cancel any pending seek requests and invoke the corresponding completion handlers if present.
 @discussion		Use this method to cancel and release the completion handlers of pending seeks. The finished parameter of the completion handlers will
 					be set to NO.
 */
- (void)cancelPendingSeeks API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0), watchos(1.0));

/*!
	@method	currentDate
	@abstract	If currentTime is mapped to a particular (real-time) date, return that date.
	@result		Returns the date of current playback, or nil if playback is not mapped to any date.
*/
- (nullable NSDate *)currentDate;

/*!
 @method		seekToDate:completionHandler:
 @abstract		move playhead to a point corresponding to a particular date, and invokes the specified block when the seek operation has either been completed or been interrupted.
 @discussion
   For playback content that is associated with a range of dates, move the
   playhead to point within that range and invokes the completion handler when the seek operation is complete. 
   Will fail if the supplied date is outside the range or if the content is not associated with a range of dates.  
   The completion handler for any prior seek request that is still in process will be invoked immediately with the finished parameter 
   set to NO. If the new request completes without being interrupted by another seek request or by any other operation, the specified 
   completion handler will be invoked with the finished parameter set to YES. 
 @param			date				The new position for the playhead.
 @param			completionHandler	The block to invoke when seek operation is complete
 @result		Returns true if the playhead was moved to the supplied date.
 */
- (BOOL)seekToDate:(NSDate *)date completionHandler:(void (^_Nullable)(BOOL finished))completionHandler API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0), watchos(1.0));

/*!
 @method		stepByCount:
 @abstract		Moves player's current item's current time forward or backward by the specified number of steps.
 @param 		stepCount
   The number of steps by which to move. A positive number results in stepping forward, a negative number in stepping backward.
 @discussion
   The size of each step depends on the enabled AVPlayerItemTracks of the AVPlayerItem. 

   This method must be invoked on the main thread/queue.
 */
- (void)stepByCount:(NSInteger)stepCount NS_SWIFT_UI_ACTOR;

/*!
 @property		timebase
 @abstract		The item's timebase.
 @discussion 
   You can examine the timebase to discover the relationship between the item's time and the source clock used for drift synchronization.
   This timebase is read-only; you cannot set its time or rate to affect playback.  The value of this property may change during playback.
 */
@property (nonatomic, readonly, nullable) __attribute__((NSObject)) CMTimebaseRef timebase API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));

@end


@class AVTextStyleRule;

@interface AVPlayerItem (AVPlayerItemVisualPresentation)

/*!
 @property 		videoComposition
 @abstract 		Indicates the video composition settings to be applied during playback.
 @discussion	This property must be accessed on the main thread/queue.

 */
@property (nonatomic, copy, nullable) AVVideoComposition *videoComposition NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @property customVideoCompositor
 @abstract Indicates the custom video compositor instance.
 @discussion
 	This property is nil if there is no video compositor, or if the internal video compositor is in use. This reference can be used to provide
	extra context to the custom video compositor instance if required.
 
	This property must be accessed on the main thread/queue.
 */
@property (nonatomic, readonly, nullable) id<AVVideoCompositing> customVideoCompositor NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @property seekingWaitsForVideoCompositionRendering
 @abstract Indicates whether the item's timing follows the displayed video frame when seeking with a video composition
 @discussion
   By default, item timing is updated as quickly as possible, not waiting for media at new times to be rendered when seeking or 
   during normal playback. The latency that occurs, for example, between the completion of a seek operation and the display of a 
   video frame at a new time is negligible in most situations. However, when video compositions are in use, the processing of 
   video for any particular time may introduce noticeable latency. Therefore it may be desirable when a video composition is in 
   use for the item's timing be updated only after the video frame for a time has been displayed. This allows, for instance, an 
   AVSynchronizedLayer associated with an AVPlayerItem to remain in synchronization with the displayed video and for the 
   currentTime property to return the time of the displayed video.

   This property has no effect on items for which videoComposition is nil.

 */
@property BOOL seekingWaitsForVideoCompositionRendering API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @property textStyleRules
 @abstract An array of AVTextStyleRules representing text styling that can be applied to subtitles and other legible media.
 @discussion
	The styling information contained in each AVTextStyleRule object in the array is used only when no equivalent styling information is provided by the media resource being played.  For example, if the text style rules specify Courier font but the media resource specifies Helvetica font, the text will be drawn using Helvetica font.
 
	This property has an effect only for tracks with media subtype kCMSubtitleFormatType_WebVTT.
*/
@property (copy, nullable) NSArray<AVTextStyleRule *> *textStyleRules API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @property	videoApertureMode
 @abstract	Specifies the video aperture mode to apply during playback.
 @discussion
	See AVVideoApertureMode constants defined in AVVideoSettings.h. Default is AVVideoApertureModeCleanAperture.
 */
@property (copy) AVVideoApertureMode videoApertureMode API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

/*!
@property	appliesPerFrameHDRDisplayMetadata
@abstract	Controls whether or not to apply the per frame HDR display metadata of the source during playback.
@discussion
*/
@property (nonatomic) BOOL appliesPerFrameHDRDisplayMetadata API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);  // default is YES

@end


@interface AVPlayerItem (AVPlayerItemAudioProcessing)

/*!
 @property	audioTimePitchAlgorithm
 @abstract	Indicates the processing algorithm used to manage audio pitch at varying rates and for scaled audio edits.
 @discussion
   Constants for various time pitch algorithms, e.g. AVAudioTimePitchSpectral, are defined in AVAudioProcessingSettings.h.
   The default value for applications linked on or after iOS 15.0 or macOS 12.0 is AVAudioTimePitchAlgorithmTimeDomain. For iOS versions prior to 15.0 the default value is AVAudioTimePitchAlgorithmLowQualityZeroLatency.
   For macOS versions prior to 12.0 the default value is AVAudioTimePitchAlgorithmSpectral.
*/
@property (copy) AVAudioTimePitchAlgorithm audioTimePitchAlgorithm API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
 @property audioSpatializationAllowed
 @abstract Indicates whether audio spatialization is allowed
 @discussion
   When audio spatialization is allowed for an AVPlayerItem, the AVPlayer may render multichannel audio if available even if the output device doesn't support multichannel audio on its own, via use of a synthetic channel layout. When audio spatialization is not allowed, the AVPlayer must render audio with a channel layout that best matches the capabilities of the output device. This property is not observable. Defaults to YES.
 */
@property (nonatomic, assign, getter=isAudioSpatializationAllowed) BOOL audioSpatializationAllowed API_DEPRECATED_WITH_REPLACEMENT("allowedAudioSpatializationFormats", macos(10.15, API_TO_BE_DEPRECATED), ios(13.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(tvos, watchos);

/*!
 @property allowedAudioSpatializationFormats
 @abstract Indicates the source audio channel layouts allowed by the receiver for spatialization.
 @discussion
   Spatialization uses psychoacoustic methods to create a more immersive audio rendering when the content is played on specialized headphones and speaker arrangements. When an AVPlayerItem's allowedAudioSpatializationFormats property is set to AVAudioSpatializationFormatMonoAndStereo the AVPlayer will attempt to spatialize content tagged with a stereo channel layout, two-channel content with no layout specified as well as mono. It is considered incorrect to render a binaural recording with spatialization. A binaural recording is captured using two carefully placed microphones at each ear where the intent, when played on headphones, is to reproduce a naturally occurring spatial effect. Content tagged with a binaural channel layout will ignore this property value. When an AVPlayerItem's allowedAudioSpatializationFormats property is set to AVAudioSpatializationFormatMultichannel the AVPlayer will attempt to spatialize any decodable multichannel layout. Setting this property to AVAudioSpatializationFormatMonoStereoAndMultichannel indicates that the sender allows the AVPlayer to spatialize any decodable mono, stereo or multichannel layout. This property is not observable. The default value for this property with video content is AVAudioSpatializationFormatMonoStereoAndMultichannel. Otherwise, audio only content default value is AVAudioSpatializationFormatMultichannel.
 */
@property (nonatomic, assign) AVAudioSpatializationFormats allowedAudioSpatializationFormats API_AVAILABLE(macos(11.0), ios(14.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/*!
 @property audioMix
 @abstract Indicates the audio mix parameters to be applied during playback
 @discussion
   The inputParameters of the AVAudioMix must have trackIDs that correspond to a track of the receiver's asset. Otherwise they will be ignored. (See AVAudioMix.h for the declaration of AVAudioMixInputParameters and AVPlayerItem's asset property.)
 */
@property (nonatomic, copy, nullable) AVAudioMix *audioMix;

@end


@interface AVPlayerItem (AVPlayerItemPlayability)

/*!
 @property loadedTimeRanges
 @abstract This property provides a collection of time ranges for which the player has the media data readily available. The ranges provided might be discontinuous.
 @discussion Returns an NSArray of NSValues containing CMTimeRanges.
 */
@property (readonly) NSArray<NSValue *> *loadedTimeRanges;

/*!
 @property playbackLikelyToKeepUp
 @abstract Indicates whether the item will likely play through without stalling.
 @discussion This property communicates a prediction of playability. Factors considered in this prediction
	include I/O throughput and media decode performance. It is possible for playbackLikelyToKeepUp to
	indicate NO while the property playbackBufferFull indicates YES. In this event the playback buffer has
	reached capacity but there isn't the statistical data to support a prediction that playback is likely to 
	keep up. It is left to the application programmer to decide to continue media playback or not. 
	See playbackBufferFull below.
  */
@property (readonly, getter=isPlaybackLikelyToKeepUp) BOOL playbackLikelyToKeepUp;

/*! 
 @property playbackBufferFull
 @abstract Indicates that the internal media buffer is full and that further I/O is suspended.
 @discussion This property reports that the data buffer used for playback has reach capacity.
	Despite the playback buffer reaching capacity there might not exist sufficient statistical 
	data to support a playbackLikelyToKeepUp prediction of YES. See playbackLikelyToKeepUp above.
 */
@property (readonly, getter=isPlaybackBufferFull) BOOL playbackBufferFull;

/* indicates that playback has consumed all buffered media and that playback will stall or end */
@property (readonly, getter=isPlaybackBufferEmpty) BOOL playbackBufferEmpty;

/*!
 @property canUseNetworkResourcesForLiveStreamingWhilePaused
 @abstract Indicates whether the player item can use network resources to keep playback state up to date while paused
 @discussion
	For live streaming content, the player item may need to use extra networking and power resources to keep playback state up to date when paused.  For example, when this property is set to YES, the seekableTimeRanges property will be periodically updated to reflect the current state of the live stream.
 
	For clients linked on or after OS X 10.11 or iOS 9.0, the default value is NO.  To minimize power usage, avoid setting this property to YES when you do not need playback state to stay up to date while paused.
 */
@property (assign) BOOL canUseNetworkResourcesForLiveStreamingWhilePaused API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));

/*!
@property	preferredForwardBufferDuration
@abstract	Indicates the media duration the caller prefers the player to buffer from the network ahead of the playhead to guard against playback disruption. 
@discussion	The value is in seconds. If it is set to 0, the player will choose an appropriate level of buffering for most use cases.
			Note that setting this property to a low value will increase the chance that playback will stall and re-buffer, while setting it to a high value will increase demand on system resources.
			Note that the system may buffer less than the value of this property in order to manage resource consumption.
*/
@property NSTimeInterval preferredForwardBufferDuration API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

@end


@interface AVPlayerItem (AVPlayerItemVariantControl)

/*!
 @property preferredPeakBitRate
 @abstract Indicates the desired limit of network bandwidth consumption for this item.

 @discussion
	Set preferredPeakBitRate to non-zero to indicate that the player should attempt to limit item playback to that bit rate, expressed in bits per second.

	If network bandwidth consumption cannot be lowered to meet the preferredPeakBitRate, it will be reduced as much as possible while continuing to play the item.
*/
@property double preferredPeakBitRate API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));

/*!
 @property preferredPeakBitRateForExpensiveNetworks
 @abstract Indicates the desired limit of network bandwidth consumption for this item over expensive networks.

 @discussion
	When preferredPeakBitRateForExpensiveNetworks is set to non-zero, the player will attempt to limit item playback to that bit rate 
	when streaming over an expensive network, such as when using a cellular data plan.  (See -[NWPath isExpensive])

	If network bandwidth consumption cannot be lowered to meet the preferredPeakBitRateForExpensiveNetworks, it will be reduced as much as possible while continuing to play the item.
	
	Note that preferredPeakBitRate still applies unconditionally.  If preferredPeakBitRateForExpensiveNetworks is less restrictive (greater) than preferredPeakBitRate,
	preferredPeakBitRateForExpensiveNetworks has no practical effect.
*/
@property double preferredPeakBitRateForExpensiveNetworks API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/*!
 @property preferredMaximumResolution
 @abstract Indicates a preferred upper limit on the resolution of the video to be downloaded (or otherwise transferred) and rendered by the player.
 @discussion
	The default value is CGSizeZero, which indicates that the client enforces no limit on video resolution. Other values indicate a preferred maximum video resolution.
	It only applies to HTTP Live Streaming asset.
 */
@property CGSize preferredMaximumResolution API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

/*!
 @property preferredMaximumResolutionForExpensiveNetworks
 @abstract Indicates a preferred upper limit on the resolution of the video to be downloaded that applies only when the download occurs over expensive networks.
 @discussion
	The default value is CGSizeZero, which indicates that the client enforces no limit on video resolution. Other values indicate a preferred maximum video resolution.
	This limit applies only when streaming over an expensive network, such as when using a cellular data plan.  (See -[NWPath isExpensive])

	It only applies to HTTP Live Streaming asset.
 
	Note that preferredMaximumResolution still applies unconditionally.  If preferredMaximumResolutionForExpensiveNetworks is less restrictive (higher resolution)
	than preferredMaximumResolution, preferredMaximumResolutionForExpensiveNetworks has no practical effect.
 */
@property CGSize preferredMaximumResolutionForExpensiveNetworks API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/*!
 @property		startsOnFirstEligibleVariant
 @abstract		Directs the player to start playback with the first eligible variant  that appears in the stream's master playlist.
 @discussion
   This property influences AVPlayer's algorithm for selecting which of the eligible variant streams in an HTTP Live Streaming master playlist is selected when playback first begins.
	In all cases, AVPlayer may switch to other variants during playback.
 
	On releases prior to macOS 10.15, iOS 13, tvOS 13 and watchOS 6, AVPlayer starts HLS playback with the first eligible variant in the master playlist.
	On releases starting with macOS 10.15, iOS 13, tvOS 13 and watchOS 6, AVPlayer starts HLS playback by choosing an initial variant that optimizes the startup experience.
	On releases starting with macOS 11.0, iOS 14, tvOS 14 and watchOS 7, applications may set this property to YES to request that AVPlayer use the previous behaviour of using the first eligible variant in the master playlist. This would be appropriate, for example, for applications which wish to control initial variant selection by ordering the variants in the master playlist.
	
	Note that changing this property may impact stream startup performance and quality. In order to be effective this property must be set before initial variant selection occurs.
	This property only applies to HTTP Live Streaming assets. The default value of this property is NO.
 */
@property (nonatomic) BOOL startsOnFirstEligibleVariant API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0));

/*!
  @enum			AVVariantPreferences
  @abstract		These constants can be used in any combination as the value of variantPreferences.

  @constant		AVVariantPreferenceNone
	Indicates that only the basic behaviors of the player for choosing among variants should be applied, including considerations of available bandwidth, compatibility of the indicated codec or codecs, the dimensions of visual output, and the number of available audio output channels.
  @constant		AVVariantPreferenceScalabilityToLosslessAudio
	Directs the item to permit the use of variants with lossless audio encodings, if sufficient bandwidth is available for their use.
*/
typedef NS_OPTIONS(NSUInteger, AVVariantPreferences) {
	AVVariantPreferenceNone							= 0,
	AVVariantPreferenceScalabilityToLosslessAudio	= 1U << 0,
} API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5), watchos(7.4));

/*!
	@property		variantPreferences
	@abstract		Indicates preferences for variant switching.
	@discussion
		Changing variant preferences during playback may result in a variant switch.
		The default value is AVVariantPreferenceNone.
*/
@property AVVariantPreferences variantPreferences API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5), watchos(7.4));

@end


@interface AVPlayerItem (AVPlayerItemMediaSelection) 

/*!
 @method		selectMediaOption:inMediaSelectionGroup:
 @abstract
   Selects the media option described by the specified instance of AVMediaSelectionOption in the specified AVMediaSelectionGroup and deselects all other options in that group.
 @param 		mediaSelectionOption	The option to select.
 @param 		mediaSelectionGroup		The media selection group, obtained from the receiver's asset, that contains the specified option.
 @discussion
   If the specified media selection option isn't a member of the specified media selection group, no change in presentation state will result.
   If the value of the property allowsEmptySelection of the AVMediaSelectionGroup is YES, you can pass nil for mediaSelectionOption to deselect
   all media selection options in the group.
   Note that if multiple options within a group meet your criteria for selection according to locale or other considerations, and if these options are otherwise indistinguishable to you according to media characteristics that are meaningful for your application, content is typically authored so that the first available option that meets your criteria is appropriate for selection.
 
   This method must be invoked on the main thread/queue.
 */
- (void)selectMediaOption:(nullable AVMediaSelectionOption *)mediaSelectionOption inMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0));

/*!
 @method		selectMediaOptionAutomaticallyInMediaSelectionGroup:
 @abstract
    Selects the media option in the specified media selection group that best matches the AVPlayer's current automatic selection criteria. Also allows automatic selection to be re-applied to the specified group subsequently if the relevant criteria are changed.
 @param 		mediaSelectionGroup		The media selection group, obtained from the receiver's asset, that contains the specified option.
 @discussion
   Has no effect unless the appliesMediaSelectionCriteriaAutomatically property of the associated AVPlayer is YES and unless automatic media selection has previously been overridden via -[AVPlayerItem selectMediaOption:inMediaSelectionGroup:].
 
   This method must be invoked on the main thread/queue.
 */
- (void)selectMediaOptionAutomaticallyInMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
  @property		currentMediaSelection
  @abstract		Provides an instance of AVMediaSelection carrying current selections for each of the receiver's media selection groups.
*/
@property (nonatomic, readonly) AVMediaSelection *currentMediaSelection API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));

@end


@class AVPlayerItemAccessLog;
@class AVPlayerItemErrorLog;
@class AVPlayerItemAccessLogInternal;
@class AVPlayerItemErrorLogInternal;
@class AVPlayerItemAccessLogEventInternal;
@class AVPlayerItemErrorLogEventInternal;

@interface AVPlayerItem (AVPlayerItemLogging)

/*!
 @method		accessLog
 @abstract		Returns an object that represents a snapshot of the network access log. Can be nil.
 @discussion	An AVPlayerItemAccessLog provides methods to retrieve the network access log in a format suitable for serialization.
 				If nil is returned then there is no logging information currently available for this AVPlayerItem.
				An AVPlayerItemNewAccessLogEntryNotification will be posted when new logging information becomes available. However, accessLog might already return a non-nil value even before the first notification is posted.
 @result		An autoreleased AVPlayerItemAccessLog instance.
 */
- (nullable AVPlayerItemAccessLog *)accessLog API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0));

/*!
 @method		errorLog
 @abstract		Returns an object that represents a snapshot of the error log. Can be nil.
 @discussion	An AVPlayerItemErrorLog provides methods to retrieve the error log in a format suitable for serialization.
 				If nil is returned then there is no logging information currently available for this AVPlayerItem.
 @result		An autoreleased AVPlayerItemErrorLog instance.
 */
- (nullable AVPlayerItemErrorLog *)errorLog API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0));

@end

@class AVPlayerItemOutput;

@interface AVPlayerItem (AVPlayerItemOutputs)

/*!
 @method		addOutput:
 @abstract		Adds the specified instance of AVPlayerItemOutput to the receiver's collection of outputs.
 @discussion	
	The class of AVPlayerItemOutput provided dictates the data structure that decoded samples are vended in. 
 
 	When an AVPlayerItemOutput is associated with an AVPlayerItem, samples are provided for a media type in accordance with the rules for mixing, composition, or exclusion that the AVPlayer honors among multiple enabled tracks of that media type for its own rendering purposes. For example, video media will be composed according to the instructions provided via AVPlayerItem.videoComposition, if present. Audio media will be mixed according to the parameters provided via AVPlayerItem.audioMix, if present.
 @param			output
				An instance of AVPlayerItemOutput
 */

- (void)addOutput:(AVPlayerItemOutput *)output API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));

/*!
 @method		removeOutput:
 @abstract		Removes the specified instance of AVPlayerItemOutput from the receiver's collection of outputs.
 @param			output
				An instance of AVPlayerItemOutput
 */

- (void)removeOutput:(AVPlayerItemOutput *)output API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));

/*!
 @property		outputs
 @abstract		The collection of associated outputs.
 */

@property (nonatomic, readonly) NSArray<AVPlayerItemOutput *> *outputs API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));

@end

@class AVPlayerItemMediaDataCollector;

@interface AVPlayerItem (AVPlayerItemMediaDataCollectors)

/*!
 @method		addMediaDataCollector:
 @abstract		Adds the specified instance of AVPlayerItemMediaDataCollector to the receiver's collection of mediaDataCollectors.
 @discussion
	This method may incur additional I/O to collect the requested media data asynchronously.
 @param			collector
				An instance of AVPlayerItemMediaDataCollector
*/
- (void)addMediaDataCollector:(AVPlayerItemMediaDataCollector *)collector API_AVAILABLE(macos(10.11.3), ios(9.3), tvos(9.3), watchos(2.3));

/*!
 @method		removeMediaDataCollector:
 @abstract		Removes the specified instance of AVPlayerItemMediaDataCollector from the receiver's collection of mediaDataCollectors.
 @param			collector
				An instance of AVPlayerItemMediaDataCollector
*/
- (void)removeMediaDataCollector:(AVPlayerItemMediaDataCollector *)collector API_AVAILABLE(macos(10.11.3), ios(9.3), tvos(9.3), watchos(2.3));

/*!
 @property		mediaDataCollectors
 @abstract		The collection of associated mediaDataCollectors.
*/
@property (nonatomic, readonly) NSArray<AVPlayerItemMediaDataCollector *> *mediaDataCollectors API_AVAILABLE(macos(10.11.3), ios(9.3), tvos(9.3), watchos(2.3));

@end

@interface AVPlayerItem (AVPlayerItemDeprecated)

/*!
 @method			seekToTime:
 @abstract			Moves the playback cursor.
 @param				time
 @discussion		Use this method to seek to a specified time for the item.
					The time seeked to may differ from the specified time for efficiency. For sample accurate seeking see seekToTime:toleranceBefore:toleranceAfter:.
					If the seek time is outside of seekable time ranges as indicated by seekableTimeRanges property, the seek request will be cancelled.
 */
- (void)seekToTime:(CMTime)time API_DEPRECATED("Use -seekToTime:completionHandler:, passing nil for the completionHandler if you don't require notification of completion", macos(10.7, 10.13), ios(4.0, 11.0), tvos(9.0, 11.0)) API_UNAVAILABLE(watchos);

/*!
 @method			seekToTime:toleranceBefore:toleranceAfter:
 @abstract			Moves the playback cursor within a specified time bound.
 @param				time
 @param				toleranceBefore
 @param				toleranceAfter
 @discussion		Use this method to seek to a specified time for the item.
					The time seeked to will be within the range [time-toleranceBefore, time+toleranceAfter] and may differ from the specified time for efficiency.
					Pass kCMTimeZero for both toleranceBefore and toleranceAfter to request sample accurate seeking which may incur additional decoding delay. 
					Messaging this method with beforeTolerance:kCMTimePositiveInfinity and afterTolerance:kCMTimePositiveInfinity is the same as messaging seekToTime: directly.
					Seeking is constrained by the collection of seekable time ranges. If you seek to a time outside all of the seekable ranges the seek will result in a currentTime
					within the seekable ranges.
					If the seek time is outside of seekable time ranges as indicated by seekableTimeRanges property, the seek request will be cancelled.
 */
- (void)seekToTime:(CMTime)time toleranceBefore:(CMTime)toleranceBefore toleranceAfter:(CMTime)toleranceAfter API_DEPRECATED("Use -seekToTime:toleranceBefore:toleranceAfter:completionHandler:, passing nil for the completionHandler if you don't require notification of completion", macos(10.7, 10.13), ios(4.0, 11.0), tvos(9.0, 11.0)) API_UNAVAILABLE(watchos);

/*!
 @method		seekToDate
 @abstract		move playhead to a point corresponding to a particular date.
 @discussion
   For playback content that is associated with a range of dates, move the
   playhead to point within that range. Will fail if the supplied date is outside
   the range or if the content is not associated with a range of dates.
 @param			date	The new position for the playhead.
 @result		Returns true if the playhead was moved to the supplied date.
 */
- (BOOL)seekToDate:(NSDate *)date API_DEPRECATED("Use -seekToDate:completionHandler:, passing nil for the completionHandler if you don't require notification of completion", macos(10.7, 10.13), ios(4.0, 11.0), tvos(9.0, 11.0)) API_UNAVAILABLE(watchos);

/*!
 @method		selectedMediaOptionInMediaSelectionGroup:
 @abstract		Indicates the media selection option that's currently selected from the specified group. May be nil.
 @param 		mediaSelectionGroup		A media selection group obtained from the receiver's asset.
 @result		An instance of AVMediaSelectionOption that describes the currently selection option in the group.
 @discussion
   If the value of the property allowsEmptySelection of the AVMediaSelectionGroup is YES, the currently selected option in the group may be nil.
 */
- (nullable AVMediaSelectionOption *)selectedMediaOptionInMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup API_DEPRECATED("Use currentMediaSelection to obtain an instance of AVMediaSelection, which encompasses the currently selected AVMediaSelectionOption in each of the available AVMediaSelectionGroups", macos(10.8, 10.13), ios(5.0, 11.0), tvos(9.0, 11.0)) API_UNAVAILABLE(watchos);

@end

@class AVPlayerItemAccessLogEvent;

/*!
 @class			AVPlayerItemAccessLog
 @abstract		An AVPlayerItemAccessLog provides methods to retrieve the access log in a format suitable for serialization.
 @discussion	An AVPlayerItemAccessLog acculumulates key metrics about network playback and presents them as a collection 
 				of AVPlayerItemAccessLogEvent instances. Each AVPlayerItemAccessLogEvent instance collates the data 
 				that relates to each uninterrupted period of playback.
*/
API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0))
@interface AVPlayerItemAccessLog : NSObject <NSCopying>
{
@private
	AVPlayerItemAccessLogInternal	*_playerItemAccessLog;
}
AV_INIT_UNAVAILABLE

/*!
 @method		extendedLogData
 @abstract		Serializes an AVPlayerItemAccessLog in the Extended Log File Format.
 @discussion	This method converts the webserver access log into a textual format that conforms to the
				W3C Extended Log File Format for web server log files.
				For more information see: http://www.w3.org/pub/WWW/TR/WD-logfile.html
 @result		An autoreleased NSData instance.
 */
- (nullable NSData *)extendedLogData;

/*!
 @property		extendedLogDataStringEncoding
 @abstract		Returns the NSStringEncoding for extendedLogData, see above.
 @discussion	A string suitable for console output is obtainable by: 
 				[[NSString alloc] initWithData:[myLog extendedLogData] encoding:[myLog extendedLogDataStringEncoding]]
 */
 @property (nonatomic, readonly) NSStringEncoding extendedLogDataStringEncoding;

/*!
 @property		events
 @abstract		An ordered collection of AVPlayerItemAccessLogEvent instances.
 @discussion	An ordered collection of AVPlayerItemAccessLogEvent instances that represent the chronological
 				sequence of events contained in the access log.
 				This property is not observable.
 */
@property (nonatomic, readonly) NSArray<AVPlayerItemAccessLogEvent *> *events;

@end

@class AVPlayerItemErrorLogEvent;
/*!
 @class			AVPlayerItemErrorLog
 @abstract		An AVPlayerItemErrorLog provides methods to retrieve the error log in a format suitable for serialization.
 @discussion	An AVPlayerItemErrorLog provides data to identify if, and when, network resource playback failures occured.
*/
API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0))
@interface AVPlayerItemErrorLog : NSObject <NSCopying>
{
@private
	AVPlayerItemErrorLogInternal	*_playerItemErrorLog;
}
AV_INIT_UNAVAILABLE

/*!
 @method		extendedLogData
 @abstract		Serializes an AVPlayerItemErrorLog in the Extended Log File Format.
 @discussion	This method converts the webserver error log into a textual format that conforms to the
				W3C Extended Log File Format for web server log files.
				For more information see: http://www.w3.org/pub/WWW/TR/WD-logfile.html
 @result		An autoreleased NSData instance.
 */
- (nullable NSData *)extendedLogData;

/*!
 @property		extendedLogDataStringEncoding
 @abstract		Returns the NSStringEncoding for extendedLogData, see above.
 @discussion	A string suitable for console output is obtainable by: 
 				[[NSString alloc] initWithData:[myLog extendedLogData] encoding:[myLog extendedLogDataStringEncoding]]
 */
 @property (nonatomic, readonly) NSStringEncoding extendedLogDataStringEncoding;

/*!
 @property		events
 @abstract		An ordered collection of AVPlayerItemErrorLogEvent instances.
 @discussion	An ordered collection of AVPlayerItemErrorLogEvent instances that represent the chronological
 				sequence of events contained in the error log.
 				This property is not observable.
 */
@property (nonatomic, readonly) NSArray<AVPlayerItemErrorLogEvent *> *events;

@end

/*!
 @class			AVPlayerItemAccessLogEvent
 @abstract		An AVPlayerItemAccessLogEvent represents a single log entry.
 @discussion	An AVPlayerItemAccessLogEvent provides named properties for accessing the data
				fields of each log event. None of the properties of this class are observable.
*/

API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0))
@interface AVPlayerItemAccessLogEvent : NSObject <NSCopying>
{
@private
	AVPlayerItemAccessLogEventInternal	*_playerItemAccessLogEvent;
}
AV_INIT_UNAVAILABLE

/*!
 @property		numberOfSegmentsDownloaded
 @abstract		A count of media segments downloaded.
 @discussion	Value is negative if unknown. A count of media segments downloaded from the server to this client. Corresponds to "sc-count".
 				This property is not observable.
 				This property is deprecated. Use numberOfMediaRequests instead.
 */
@property (nonatomic, readonly) NSInteger numberOfSegmentsDownloaded API_DEPRECATED_WITH_REPLACEMENT("numberOfMediaRequests", macos(10.7, 10.9), ios(4.3, 7.0), tvos(9.0, 9.0)) API_UNAVAILABLE(watchos);

/*!
 @property		numberOfMediaRequests
 @abstract		A count of media read requests.
 @discussion	Value is negative if unknown. A count of media read requests from the server to this client. Corresponds to "sc-count".
				For HTTP live Streaming, a count of media segments downloaded from the server to this client.
				For progressive-style HTTP media downloads, a count of HTTP GET (byte-range) requests for the resource.
 				This property is not observable. 
 */
@property (nonatomic, readonly) NSInteger numberOfMediaRequests API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0), watchos(1.0));

/*!
 @property		playbackStartDate
 @abstract		The date/time at which playback began for this event. Can be nil.
 @discussion	If nil is returned the date is unknown. Corresponds to "date".
 				This property is not observable.
 */
@property (nonatomic, readonly, nullable) NSDate *playbackStartDate;

/*!
 @property		URI
 @abstract		The URI of the playback item. Can be nil.
 @discussion	If nil is returned the URI is unknown. Corresponds to "uri".
 				This property is not observable.
 */
@property (nonatomic, readonly, nullable) NSString *URI;

/*!
 @property		serverAddress
 @abstract		The IP address of the server that was the source of the last delivered media segment. Can be nil.
 @discussion	If nil is returned the address is unknown. Can be either an IPv4 or IPv6 address. Corresponds to "s-ip".
 				This property is not observable.
 */
@property (nonatomic, readonly, nullable) NSString *serverAddress;

/*!
 @property		numberOfServerAddressChanges
 @abstract		A count of changes to the property serverAddress, see above, over the last uninterrupted period of playback.
 @discussion	Value is negative if unknown. Corresponds to "s-ip-changes".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSInteger numberOfServerAddressChanges;

/*!
 @property		playbackSessionID
 @abstract		A GUID that identifies the playback session. This value is used in HTTP requests. Can be nil.
 @discussion	If nil is returned the GUID is unknown. Corresponds to "cs-guid".
 				This property is not observable.
 */
@property (nonatomic, readonly, nullable) NSString *playbackSessionID;

/*!
 @property		playbackStartOffset
 @abstract		An offset into the playlist where the last uninterrupted period of playback began. Measured in seconds.
 @discussion	Value is negative if unknown. Corresponds to "c-start-time".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSTimeInterval playbackStartOffset;

/*!
 @property		segmentsDownloadedDuration
 @abstract		The accumulated duration of the media downloaded. Measured in seconds.
 @discussion	Value is negative if unknown. Corresponds to "c-duration-downloaded".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSTimeInterval segmentsDownloadedDuration;

/*!
 @property		durationWatched
 @abstract		The accumulated duration of the media played. Measured in seconds.
 @discussion	Value is negative if unknown. Corresponds to "c-duration-watched".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSTimeInterval durationWatched;

/*!
 @property		numberOfStalls
 @abstract		The total number of playback stalls encountered.
 @discussion	Value is negative if unknown. Corresponds to "c-stalls".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSInteger numberOfStalls;

/*!
 @property		numberOfBytesTransferred
 @abstract		The accumulated number of bytes transferred.
 @discussion	Value is negative if unknown. Corresponds to "bytes".
 				This property is not observable.
 */
@property (nonatomic, readonly) long long numberOfBytesTransferred;

/*!
 @property		transferDuration
 @abstract		The accumulated duration of active network transfer of bytes. Measured in seconds.
 @discussion	Value is negative if unknown. Corresponds to "c-transfer-duration".
				This property is not observable.
 */
@property (nonatomic, readonly) NSTimeInterval transferDuration API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
 @property		observedBitrate
 @abstract		The empirical throughput across all media downloaded. Measured in bits per second.
 @discussion	Value is negative if unknown. Corresponds to "c-observed-bitrate".
 				This property is not observable.
 */
@property (nonatomic, readonly) double observedBitrate;

/*!
 @property		indicatedBitrate
 @abstract		The throughput required to play the stream, as advertised by the server. Measured in bits per second.
 @discussion	Value is negative if unknown. Corresponds to "sc-indicated-bitrate".
 				This property is not observable.
 */
@property (nonatomic, readonly) double indicatedBitrate;

/*!
 @property		indicatedAverageBitrate
 @abstract		Average throughput required to play the stream, as advertised by the server. Measured in bits per second.
 @discussion	Value is negative if unknown. Corresponds to "sc-indicated-avg-bitrate".
 This property is not observable.
 */
@property (nonatomic, readonly) double indicatedAverageBitrate API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*!
 @property		averageVideoBitrate
 @abstract		The average bitrate of video track if it is unmuxed. Average bitrate of combined content if muxed. Measured in bits per second.
 @discussion	Value is negative if unknown. Corresponds to "c-avg-video-bitrate".
 This property is not observable.
 */
@property (nonatomic, readonly) double averageVideoBitrate API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos);

/*!
 @property		averageAudioBitrate
 @abstract		The average bitrate of audio track. This is not available if audio is muxed with video. Measured in bits per second.
 @discussion	Value is negative if unknown. Corresponds to "c-avg-audio-bitrate".
 This property is not observable.
 */
@property (nonatomic, readonly) double averageAudioBitrate API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*!
 @property		numberOfDroppedVideoFrames
 @abstract		The total number of dropped video frames.
 @discussion	Value is negative if unknown. Corresponds to "c-frames-dropped".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSInteger numberOfDroppedVideoFrames;

/*!
 @property		startupTime
 @abstract		The accumulated duration until player item is ready to play. Measured in seconds.
 @discussion	Value is negative if unknown. Corresponds to "c-startup-time".
				This property is not observable.
 */
@property (nonatomic, readonly) NSTimeInterval startupTime API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
 @property		downloadOverdue
 @abstract		The total number of times the download of the segments took too long.
 @discussion	Value is negative if unknown. Corresponds to "c-overdue".
				This property is not observable.
 */
@property (nonatomic, readonly) NSInteger downloadOverdue API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
 @property		observedMaxBitrate
 @abstract		Maximum observed segment download bit rate.
 @discussion	Value is negative if unknown. Corresponds to "c-observed-max-bitrate".
				This property is not observable.
 */
@property (nonatomic, readonly) double observedMaxBitrate API_DEPRECATED("Use observedBitrateStandardDeviation to monitor variance in network bitrate.", macos(10.9, 12), ios(7.0, 15.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

/*!
 @property		observedMinBitrate
 @abstract		Minimum observed segment download bit rate.
 @discussion	Value is negative if unknown. Corresponds to "c-observed-min-bitrate".
				This property is not observable.
 */
@property (nonatomic, readonly) double observedMinBitrate API_DEPRECATED("Use observedBitrateStandardDeviation to monitor variance in network bitrate.", macos(10.9, 12), ios(7.0, 15.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

/*!
 @property		observedBitrateStandardDeviation
 @abstract		Standard deviation of observed segment download bit rates.
 @discussion	Value is negative if unknown. Corresponds to "c-observed-bitrate-sd".
				This property is not observable.
 */
@property (nonatomic, readonly) double observedBitrateStandardDeviation API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
 @property		playbackType
 @abstract		Playback type (LIVE, VOD, FILE).
 @discussion	If nil is returned the playback type is unknown. Corresponds to "s-playback-type".
				This property is not observable.
 */
@property (nonatomic, readonly, nullable) NSString *playbackType API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
 @property		mediaRequestsWWAN
 @abstract		Number of network read requests over WWAN.
 @discussion	Value is negative if unknown. Corresponds to "sc-wwan-count".
				This property is not observable.
 */
@property (nonatomic, readonly) NSInteger mediaRequestsWWAN API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
 @property		switchBitrate
 @abstract		Bandwidth that caused us to switch (up or down).
 @discussion	Value is negative if unknown. Corresponds to "c-switch-bitrate".
				This property is not observable.
 */
@property (nonatomic, readonly) double switchBitrate API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

@end

/*!
 @class			AVPlayerItemErrorLogEvent
 @abstract		An AVPlayerItemErrorLogEvent represents a single log entry.
 @discussion	An AVPlayerItemErrorLogEvent provides named properties for accessing the data
				fields of each log event. None of the properties of this class are observable.
*/
API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0))
@interface AVPlayerItemErrorLogEvent : NSObject <NSCopying>
{
@private
	AVPlayerItemErrorLogEventInternal	*_playerItemErrorLogEvent;
}
AV_INIT_UNAVAILABLE

/*!
 @property		date
 @abstract		The date and time when the error occured. Can be nil.
 @discussion	If nil is returned the date is unknown. Corresponds to "date".
 				This property is not observable.
 */
@property (nonatomic, readonly, nullable) NSDate *date;

/*!
 @property		URI
 @abstract		The URI of the playback item. Can be nil.
 @discussion	If nil is returned the URI is unknown. Corresponds to "uri".
 				This property is not observable.
 */
@property (nonatomic, readonly, nullable) NSString *URI;

/*!
 @property		serverAddress
 @abstract		The IP address of the server that was the source of the error. Can be nil.
 @discussion	If nil is returned the address is unknown. Can be either an IPv4 or IPv6 address. Corresponds to "s-ip".
 				This property is not observable.
 */
@property (nonatomic, readonly, nullable) NSString *serverAddress;

/*!
 @property		playbackSessionID
 @abstract		A GUID that identifies the playback session. This value is used in HTTP requests. Can be nil.
 @discussion	If nil is returned the GUID is unknown. Corresponds to "cs-guid".
 				This property is not observable.
 */
@property (nonatomic, readonly, nullable) NSString *playbackSessionID;

/*!
 @property		errorStatusCode
 @abstract		A unique error code identifier.
 @discussion	Corresponds to "status".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSInteger errorStatusCode;

/*!
 @property		errorDomain
 @abstract		The domain of the error.
 @discussion	Corresponds to "domain".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSString *errorDomain;

/*!
 @property		errorComment
 @abstract		A description of the error encountered. Can be nil.
 @discussion	If nil is returned further information is not available. Corresponds to "comment".
 				This property is not observable.
 */
@property (nonatomic, readonly, nullable) NSString *errorComment;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVPlayerItem.h>
#endif
