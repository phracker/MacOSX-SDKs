/*
    File:  AVPlayerItem.h

	Framework:  AVFoundation
 
	Copyright 2010-2012 Apple Inc. All rights reserved.

*/

/*!
	@class			AVPlayerItem

	@abstract
	  An AVPlayerItem carries a reference to an AVAsset as well as presentation settings for that asset.

	@discussion
	  Note that inspection of media assets is provided by AVAsset.
	  This class is intended to represent presentation state for an asset that's played by an AVPlayer and to permit observation of that state.

	  To allow clients to add and remove their objects as key-value observers safely, AVPlayerItem serializes notifications of
	  changes that occur dynamically during playback on the same dispatch queue on which notifications of playback state changes
	  are serialized by its associated AVPlayer. By default, this queue is the main queue. See dispatch_get_main_queue().
	  
	  To ensure safe access to AVPlayerItem's nonatomic properties while dynamic changes in playback state may be reported, clients must
	  serialize their access with the associated AVPlayer's notification queue. In the common case, such serialization is naturally
	  achieved by invoking AVPlayerItem's various methods on the main thread or queue.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>
#import <CoreMedia/CMSync.h>
#if TARGET_OS_IPHONE
#import <CoreGraphics/CGGeometry.h>
#else // ! TARGET_OS_IPHONE
#import <ApplicationServices/../Frameworks/CoreGraphics.framework/Headers/CGGeometry.h>
#endif  // ! TARGET_OS_IPHONE

/* Note that NSNotifications posted by AVPlayerItem may be posted on a different thread from the one on which the observer was registered. */

// notifications                                                                                description
AVF_EXPORT NSString *const AVPlayerItemTimeJumpedNotification			 NS_AVAILABLE(10_7, 5_0);	// the item's current time has changed discontinuously
AVF_EXPORT NSString *const AVPlayerItemDidPlayToEndTimeNotification      NS_AVAILABLE(10_7, 4_0);   // item has played to its end time
AVF_EXPORT NSString *const AVPlayerItemFailedToPlayToEndTimeNotification NS_AVAILABLE(10_7, 4_3);   // item has failed to play to its end time

// notification userInfo key                                                                    type
AVF_EXPORT NSString *const AVPlayerItemFailedToPlayToEndTimeErrorKey     NS_AVAILABLE(10_7, 4_3);   // NSError

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
enum {
	AVPlayerItemStatusUnknown,
	AVPlayerItemStatusReadyToPlay,
	AVPlayerItemStatusFailed
};
typedef NSInteger AVPlayerItemStatus;

@class AVPlayer;
@class AVAsset;
@class AVAssetTrack;
@class AVAudioMix;
@class AVVideoComposition;
@class AVMediaSelectionGroup;
@class AVMediaSelectionOption;
@class AVPlayerItemInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVPlayerItem : NSObject <NSCopying>
{
@private
	AVPlayerItemInternal* _playerItem;
}

/*!
 @method			playerItemWithURL:
 @abstract		Returns an instance of AVPlayerItem for playing a resource at the specified location.
 @param			URL
 @result			An instance of AVPlayerItem.
 @discussion	
 */
+ (AVPlayerItem *)playerItemWithURL:(NSURL *)URL;

/*!
 @method			playerItemWithAsset:
 @abstract		Returns an instance of AVPlayerItem for playing an AVAsset.
 @param			asset
 @result			An instance of AVPlayerItem.
 @discussion	
 */
+ (AVPlayerItem *)playerItemWithAsset:(AVAsset *)asset;

/*!
 @method			initWithURL:
 @abstract		Initializes an AVPlayerItem with an NSURL.
 @param			URL
 @result			An instance of AVPlayerItem
 @discussion	
 */
- (id)initWithURL:(NSURL *)URL;

/*!
 @method			initWithAsset:
 @abstract		Initializes an AVPlayerItem with an AVAsset.
 @param			asset
 @result			An instance of AVPlayerItem
 @discussion	
 */
- (id)initWithAsset:(AVAsset *)asset;

/*!
 @property status
 @abstract
	The ability of the receiver to be used for playback.
 
 @discussion
	The value of this property is an AVPlayerItemStatus that indicates whether the receiver can be used for playback.
	When the value of this property is AVPlayerItemStatusFailed, the receiver can no longer be used for playback and
	a new instance needs to be created in its place. When this happens, clients can check the value of the error
	property to determine the nature of the failure. This property is key value observable.
 */
@property (nonatomic, readonly) AVPlayerItemStatus status;

/*!
 @property error
 @abstract
	If the receiver's status is AVPlayerItemStatusFailed, this describes the error that caused the failure.
 
 @discussion
	The value of this property is an NSError that describes what caused the receiver to no longer be able to be played.
	If the receiver's status is not AVPlayerItemStatusFailed, the value of this property is nil.
 */
@property (nonatomic, readonly) NSError *error;

@end


@interface AVPlayerItem (AVPlayerItemInspection)

/*!
 @property asset
 @abstract Accessor for underlying AVAsset.
 */
@property (nonatomic, readonly) AVAsset *asset;

/*!
 @property tracks
 @abstract Provides array of AVPlayerItem tracks. Observable (can change dynamically during playback).
 */
@property (nonatomic, readonly) NSArray *tracks;

/*!
 @property duration
 @abstract Indicates the duration of the item, not considering either its forwardPlaybackEndTime or reversePlaybackEndTime.
 
 @discussion
	This property is observable. The duration of an item can change dynamically during playback.
 */
@property (nonatomic, readonly) CMTime duration NS_AVAILABLE(10_7, 4_3);

/*!
 @property presentationSize
 @abstract The size of the receiver as presented by the player.
 
 @discussion 
	Indicates the size at which the visual portion of the item is presented by the player; can be scaled from this 
	size to fit within the bounds of an AVPlayerLayer via its videoGravity property. Can be scaled arbitarily for presentation
	via the frame property of an AVPlayerLayer.
 */
@property (nonatomic, readonly) CGSize presentationSize;

/*!
 @property timedMetadata
 @abstract Provides an NSArray of AVMetadataItems representing the timed metadata encountered most recently within the media as it plays. May be nil.
 @discussion
   Notifications of changes are available via key-value observation.
   As an optimization for playback, AVPlayerItem may omit the processing of timed metadata when no observer of this property is registered. Therefore, when no such observer is registered, the value of the timedMetadata property may remain nil regardless of the contents of the underlying media.
 */
@property (nonatomic, readonly) NSArray *timedMetadata;

@end


@interface AVPlayerItem (AVPlayerItemRateAndSteppingSupport)

/* indicates whether the item can be played at rates greater than 1.0 */
@property (nonatomic, readonly) BOOL canPlayFastForward NS_AVAILABLE(10_8, 5_0);

/* indicates whether the item can be played at rates between 0.0 and 1.0 */
@property (nonatomic, readonly) BOOL canPlaySlowForward NS_AVAILABLE(10_8, TBD);

/* indicates whether the item can be played at rate -1.0 */
@property (nonatomic, readonly) BOOL canPlayReverse NS_AVAILABLE(10_8, TBD);

/* indicates whether the item can be played at rates less between 0.0 and -1.0 */
@property (nonatomic, readonly) BOOL canPlaySlowReverse NS_AVAILABLE(10_8, TBD);

/* indicates whether the item can be played at rates less than -1.0 */
@property (nonatomic, readonly) BOOL canPlayFastReverse NS_AVAILABLE(10_8, 5_0);

/* Indicates whether the item supports stepping forward; see -stepByCount:. Once the item has become ready to play, the value of canStepForward does not change even when boundary conditions are reached, such as when the item's currentTime is its end time. */
@property (nonatomic, readonly) BOOL canStepForward NS_AVAILABLE(10_8, TBD);

/* indicates whether the item supports stepping backward; see -stepByCount:. Once the item has become ready to play, the value of canStepBackward does not change even when boundary conditions are reached, such as when the item's currentTime is equal to kCMTimeZero. */
@property (nonatomic, readonly) BOOL canStepBackward NS_AVAILABLE(10_8, TBD);

@end


@interface AVPlayerItem (AVPlayerItemTimeControl)

/*!
 @method			currentTime
 @abstract			Returns the current time of the item.
 @result			A CMTime
 @discussion		Returns the current time of the item.
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
@property (nonatomic) CMTime forwardPlaybackEndTime;

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
@property (nonatomic) CMTime reversePlaybackEndTime;

/*!
 @property seekableTimeRanges
 @abstract This property provides a collection of time ranges that the player item can seek to. The ranges provided might be discontinous.
 @discussion Returns an NSArray of NSValues containing CMTimeRanges.
 */
@property (nonatomic, readonly) NSArray *seekableTimeRanges;

/*!
 @method			seekToTime:
 @abstract			Moves the playback cursor.
 @param				time
 @discussion		Use this method to seek to a specified time for the item.
					The time seeked to may differ from the specified time for efficiency. For sample accurate seeking see seekToTime:toleranceBefore:toleranceAfter:.
 */
- (void)seekToTime:(CMTime)time;

/*!
 @method			seekToTime:completionHandler:
 @abstract			Moves the playback cursor and invokes the specified block when the seek operation has either been completed or been interrupted.
 @param				time
 @param				completionHandler
 @discussion		Use this method to seek to a specified time for the item and to be notified when the seek operation is complete.
 					The completion handler for any prior seek request that is still in process will be invoked immediately with the finished parameter 
 					set to NO. If the new request completes without being interrupted by another seek request or by any other operation the specified 
 					completion handler will be invoked with the finished parameter set to YES. 
 */
- (void)seekToTime:(CMTime)time completionHandler:(void (^)(BOOL finished))completionHandler NS_AVAILABLE(10_7, 5_0);

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
 */
- (void)seekToTime:(CMTime)time toleranceBefore:(CMTime)toleranceBefore toleranceAfter:(CMTime)toleranceAfter;

/*!
 @method			seekToTime:toleranceBefore:toleranceAfter:completionHandler:
 @abstract			Moves the playback cursor within a specified time bound and invokes the specified block when the seek operation has either been completed or been interrupted.
 @param				time
 @param				toleranceBefore
 @param				toleranceAfter
 @discussion		Use this method to seek to a specified time for the item and to be notified when the seek operation is complete.
					The time seeked to will be within the range [time-toleranceBefore, time+toleranceAfter] and may differ from the specified time for efficiency.
					Pass kCMTimeZero for both toleranceBefore and toleranceAfter to request sample accurate seeking which may incur additional decoding delay. 
					Messaging this method with beforeTolerance:kCMTimePositiveInfinity and afterTolerance:kCMTimePositiveInfinity is the same as messaging seekToTime: directly.
					The completion handler for any prior seek request that is still in process will be invoked immediately with the finished parameter set to NO. If the new 
					request completes without being interrupted by another seek request or by any other operation the specified completion handler will be invoked with the 
					finished parameter set to YES.
 */
- (void)seekToTime:(CMTime)time toleranceBefore:(CMTime)toleranceBefore toleranceAfter:(CMTime)toleranceAfter completionHandler:(void (^)(BOOL finished))completionHandler NS_AVAILABLE(10_7, 5_0);

/*!
 @method			cancelPendingSeeks
 @abstract			Cancel any pending seek requests and invoke the corresponding completion handlers if present.
 @discussion		Use this method to cancel and release the completion handlers of pending seeks. The finished parameter of the completion handlers will
 					be set to NO.
 */
- (void)cancelPendingSeeks NS_AVAILABLE(10_7, 5_0);

/*!
	@method	currentDate
	@abstract	If currentTime is mapped to a particular (real-time) date, return that date.
	@result		Returns the date of current playback, or nil if playback is not mapped to any date.
*/
- (NSDate*)currentDate;

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
- (BOOL)seekToDate:(NSDate *)date;

/*!
 @method		stepByCount:
 @abstract     Moves player's current item's current time forward or backward by the specified number of steps.
 @param 		stepCount
   The number of steps by which to move. A positive number results in stepping forward, a negative number in stepping backward.
 @discussion
   The size of each step depends on the enabled AVPlayerItemTracks of the AVPlayerItem. 
 */
- (void)stepByCount:(NSInteger)stepCount;

/*!
 @property		timebase
 @abstract		The item's timebase.
 @discussion 
   You can examine the timebase to discover the relationship between the item's time and the master clock used for drift synchronization.
   This timebase is read-only; you cannot set its time or rate to affect playback.
 */
@property (nonatomic, readonly) __attribute__((NSObject)) CMTimebaseRef timebase NS_AVAILABLE(10_8, TBD);

@end


@interface AVPlayerItem (AVPlayerItemPresentation)

/*!
 @property audioMix
 @abstract Indicates the audio mix parameters to be applied during playback
 */
@property (nonatomic, copy) AVAudioMix *audioMix;

/*!
 @property videoComposition
 @abstract Indicates the video composition settings to be applied during playback.
 */
@property (nonatomic, copy) AVVideoComposition *videoComposition;

@end


@interface AVPlayerItem (AVPlayerItemPlayability)

/*!
 @property loadedTimeRanges
 @abstract This property provides a collection of time ranges for which the player has the media data readily available. The ranges provided might be discontinous.
 @discussion Returns an NSArray of NSValues containing CMTimeRanges.
 */
@property (nonatomic, readonly) NSArray *loadedTimeRanges;

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
@property (nonatomic, readonly, getter=isPlaybackLikelyToKeepUp) BOOL playbackLikelyToKeepUp;

/*! 
 @property playbackBufferFull
 @abstract Indicates that the internal media buffer is full and that further I/O is suspended.
 @discussion This property reports that the data buffer used for playback has reach capacity.
	Despite the playback buffer reaching capacity there might not exist sufficient statistical 
	data to support a playbackLikelyToKeepUp prediction of YES. See playbackLikelyToKeepUp above.
 */
@property (nonatomic, readonly, getter=isPlaybackBufferFull) BOOL playbackBufferFull;

/* indicates that playback has consumed all buffered media and that playback will stall or end */
@property (nonatomic, readonly, getter=isPlaybackBufferEmpty) BOOL playbackBufferEmpty;

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
 */
- (void)selectMediaOption:(AVMediaSelectionOption *)mediaSelectionOption inMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup NS_AVAILABLE(10_8, 5_0);

/*!
 @method		selectedMediaOptionInMediaSelectionGroup:
 @abstract		Indicates the media selection option that's currently selected from the specified group. May be nil.
 @param 		mediaSelectionGroup		A media selection group obtained from the receiver's asset.
 @result		An instance of AVMediaSelectionOption that describes the currently selection option in the group.
 @discussion
   If the value of the property allowsEmptySelection of the AVMediaSelectionGroup is YES, the currently selected option in the group may be nil.
 */
- (AVMediaSelectionOption *)selectedMediaOptionInMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup NS_AVAILABLE(10_8, 5_0);

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
 @result		An autoreleased AVPlayerItemAccessLog instance.
 */
- (AVPlayerItemAccessLog *)accessLog NS_AVAILABLE(10_7, 4_3);

/*!
 @method		errorLog
 @abstract		Returns an object that represents a snapshot of the error log. Can be nil.
 @discussion	An AVPlayerItemErrorLog provides methods to retrieve the error log in a format suitable for serialization.
 				If nil is returned then there is no logging information currently available for this AVPlayerItem.
 @result		An autoreleased AVPlayerItemErrorLog instance.
 */
- (AVPlayerItemErrorLog *)errorLog NS_AVAILABLE(10_7, 4_3); 

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

- (void)addOutput:(AVPlayerItemOutput *)output NS_AVAILABLE(10_8, TBD);

/*!
 @method		removeOutput:
 @abstract		Removes the specified instance of AVPlayerItemOutput from the receiver's collection of outputs.
 @param			output
				An instance of AVPlayerItemOutput
 */

- (void)removeOutput:(AVPlayerItemOutput *)output NS_AVAILABLE(10_8, TBD);

/*!
 @property		outputs
 @abstract		The collection of associated outputs.
 */

@property (nonatomic, readonly) NSArray *outputs NS_AVAILABLE(10_8, TBD);

@end

/*!
 @class			AVPlayerItemAccessLog
 @abstract		An AVPlayerItemAccessLog provides methods to retrieve the access log in a format suitable for serialization.
 @discussion	An AVPlayerItemAccessLog acculumulates key metrics about network playback and presents them as a collection 
 				of AVPlayerItemAccessLogEvent instances. Each AVPlayerItemAccessLogEvent instance collates the data 
 				that relates to each uninterrupted period of playback.
*/
NS_CLASS_AVAILABLE(10_7, 4_3)
@interface AVPlayerItemAccessLog : NSObject <NSCopying>
{
@private
	AVPlayerItemAccessLogInternal	*_playerItemAccessLog;
}

/*!
 @method		extendedLogData
 @abstract		Serializes an AVPlayerItemAccessLog in the Extended Log File Format.
 @discussion	This method converts the webserver access log into a textual format that conforms to the
				W3C Extended Log File Format for web server log files.
				For more information see: http://www.w3.org/pub/WWW/TR/WD-logfile.html
 @result		An autoreleased NSData instance.
 */
- (NSData *)extendedLogData;

/*!
 @method		extendedLogDataStringEncoding
 @abstract		Returns the NSStringEncoding for extendedLogData, see above.
 @discussion	A string suitable for console output is obtainable by: 
 				[[NSString alloc] initWithData:[myLog extendedLogData] encoding:[myLog extendedLogDataStringEncoding]]
 @result		An NSStringEncoding.
 */
 - (NSStringEncoding)extendedLogDataStringEncoding;

/*!
 @property		events
 @abstract		An ordered collection of AVPlayerItemAccessLogEvent instances.
 @discussion	An ordered collection of AVPlayerItemAccessLogEvent instances that represent the chronological
 				sequence of events contained in the access log.
 				This property is not observable.
 */
@property (nonatomic, readonly) NSArray *events;

@end

/*!
 @class			AVPlayerItemErrorLog
 @abstract		An AVPlayerItemErrorLog provides methods to retrieve the error log in a format suitable for serialization.
 @discussion	An AVPlayerItemErrorLog provides data to identify if, and when, network resource playback failures occured.
*/
NS_CLASS_AVAILABLE(10_7, 4_3)
@interface AVPlayerItemErrorLog : NSObject <NSCopying>
{
@private
	AVPlayerItemErrorLogInternal	*_playerItemErrorLog;
}

/*!
 @method		extendedLogData
 @abstract		Serializes an AVPlayerItemErrorLog in the Extended Log File Format.
 @discussion	This method converts the webserver error log into a textual format that conforms to the
				W3C Extended Log File Format for web server log files.
				For more information see: http://www.w3.org/pub/WWW/TR/WD-logfile.html
 @result		An autoreleased NSData instance.
 */
- (NSData *)extendedLogData;

/*!
 @method		extendedLogDataStringEncoding
 @abstract		Returns the NSStringEncoding for extendedLogData, see above.
 @discussion	A string suitable for console output is obtainable by: 
 				[[NSString alloc] initWithData:[myLog extendedLogData] encoding:[myLog extendedLogDataStringEncoding]]
 @result		An NSStringEncoding.
 */
 - (NSStringEncoding)extendedLogDataStringEncoding;

/*!
 @property		events
 @abstract		An ordered collection of AVPlayerItemErrorLogEvent instances.
 @discussion	An ordered collection of AVPlayerItemErrorLogEvent instances that represent the chronological
 				sequence of events contained in the error log.
 				This property is not observable.
 */
@property (nonatomic, readonly) NSArray *events;

@end

/*!
 @class			AVPlayerItemAccessLogEvent
 @abstract		An AVPlayerItemAccessLogEvent represents a single log entry.
 @discussion	An AVPlayerItemAccessLogEvent provides named properties for accessing the data
				fields of each log event. None of the properties of this class are observable.
*/

NS_CLASS_AVAILABLE(10_7, 4_3)
@interface AVPlayerItemAccessLogEvent : NSObject <NSCopying>
{
@private
	AVPlayerItemAccessLogEventInternal	*_playerItemAccessLogEvent;
}

/*!
 @property		numberOfSegmentsDownloaded
 @abstract		A count of media segments downloaded.
 @discussion	Value is negative if unknown. A count of media segments downloaded from the server to this client. Corresponds to "sc-count".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSInteger numberOfSegmentsDownloaded;

/*!
 @property		playbackStartDate
 @abstract		The date/time at which playback began for this event. Can be nil.
 @discussion	If nil is returned the date is unknown. Corresponds to "date".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSDate *playbackStartDate;

/*!
 @property		URI
 @abstract		The URI of the playback item. Can be nil.
 @discussion	If nil is returned the URI is unknown. Corresponds to "uri".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSString *URI;

/*!
 @property		serverAddress
 @abstract		The IP address of the server that was the source of the last delivered media segment. Can be nil.
 @discussion	If nil is returned the address is unknown. Can be either an IPv4 or IPv6 address. Corresponds to "s-ip".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSString *serverAddress;

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
@property (nonatomic, readonly) NSString *playbackSessionID;

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
 @property		numberOfDroppedVideoFrames
 @abstract		The total number of dropped video frames.
 @discussion	Value is negative if unknown. Corresponds to "c-frames-dropped".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSInteger numberOfDroppedVideoFrames;

@end

/*!
 @class			AVPlayerItemErrorLogEvent
 @abstract		An AVPlayerItemErrorLogEvent represents a single log entry.
 @discussion	An AVPlayerItemErrorLogEvent provides named properties for accessing the data
				fields of each log event. None of the properties of this class are observable.
*/
NS_CLASS_AVAILABLE(10_7, 4_3)
@interface AVPlayerItemErrorLogEvent : NSObject <NSCopying>
{
@private
	AVPlayerItemErrorLogEventInternal	*_playerItemErrorLogEvent;
}

/*!
 @property		date
 @abstract		The date and time when the error occured. Can be nil.
 @discussion	If nil is returned the date is unknown. Corresponds to "date".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSDate *date;

/*!
 @property		URI
 @abstract		The URI of the playback item. Can be nil.
 @discussion	If nil is returned the URI is unknown. Corresponds to "uri".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSString *URI;

/*!
 @property		serverAddress
 @abstract		The IP address of the server that was the source of the error. Can be nil.
 @discussion	If nil is returned the address is unknown. Can be either an IPv4 or IPv6 address. Corresponds to "s-ip".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSString *serverAddress;

/*!
 @property		playbackSessionID
 @abstract		A GUID that identifies the playback session. This value is used in HTTP requests. Can be nil.
 @discussion	If nil is returned the GUID is unknown. Corresponds to "cs-guid".
 				This property is not observable.
 */
@property (nonatomic, readonly) NSString *playbackSessionID;

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
@property (nonatomic, readonly) NSString *errorComment;

@end
