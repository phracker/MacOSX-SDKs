#if !__has_include(<AVFCore/AVPlayer.h>)
/*
    File:  AVPlayer.h

	Framework:  AVFoundation
 
	Copyright 2010-2019 Apple Inc. All rights reserved.

*/

/*!
	@class			AVPlayer
 
	@abstract
      AVPlayer offers a playback interface for single-item playback that's sufficient for
      the implementation of playback controllers and playback user interfaces.
 
	@discussion
      AVPlayer works equally well with local and remote media files, providing clients with appropriate
      information about readiness to play or about the need to await additional data before continuing.

      Visual content of items played by an instance of AVPlayer can be displayed in a CoreAnimation layer
      of class AVPlayerLayer.

	  To allow clients to add and remove their objects as key-value observers safely, AVPlayer serializes notifications of
	  changes that occur dynamically during playback on a dispatch queue. By default, this queue is the main queue. See dispatch_get_main_queue().
	  
	  To ensure safe access to AVPlayer's nonatomic properties while dynamic changes in playback state may be reported, clients must
	  serialize their access with the receiver's notification queue. In the common case, such serialization is naturally achieved
	  by invoking AVPlayer's various methods on the main thread or queue.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVAnimation.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>
#import <CoreMedia/CMSync.h>
#import <Foundation/Foundation.h>

@class AVPlayerItem;
@class AVPlayerInternal;

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum AVPlayerStatus
 @abstract
	These constants are returned by the AVPlayer status property to indicate whether it can successfully play items.
 
 @constant	 AVPlayerStatusUnknown
	Indicates that the status of the player is not yet known because it has not tried to load new media resources for
	playback.
 @constant	 AVPlayerStatusReadyToPlay
	Indicates that the player is ready to play AVPlayerItem instances.
 @constant	 AVPlayerStatusFailed
	Indicates that the player can no longer play AVPlayerItem instances because of an error. The error is described by
	the value of the player's error property.
 */
typedef NS_ENUM(NSInteger, AVPlayerStatus) {
	AVPlayerStatusUnknown = 0,
	AVPlayerStatusReadyToPlay = 1,
	AVPlayerStatusFailed = 2
};

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0))
@interface AVPlayer : NSObject 
{
@private
	AVPlayerInternal     *_player;
}

/*!
	@method			playerWithURL:
	@abstract		Returns an instance of AVPlayer that plays a single audiovisual resource referenced by URL.
	@param			URL
	@result			An instance of AVPlayer
	@discussion		Implicitly creates an AVPlayerItem. Clients can obtain the AVPlayerItem as it becomes the player's currentItem.
*/
+ (instancetype)playerWithURL:(NSURL *)URL;

/*!
	@method			playerWithPlayerItem:
	@abstract		Create an AVPlayer that plays a single audiovisual item.
	@param			item
	@result			An instance of AVPlayer
	@discussion		Useful in order to play items for which an AVAsset has previously been created. See -[AVPlayerItem initWithAsset:].
*/
+ (instancetype)playerWithPlayerItem:(nullable AVPlayerItem *)item;

/*!
	@method			initWithURL:
	@abstract		Initializes an AVPlayer that plays a single audiovisual resource referenced by URL.
	@param			URL
	@result			An instance of AVPlayer
	@discussion		Implicitly creates an AVPlayerItem. Clients can obtain the AVPlayerItem as it becomes the player's currentItem.
*/
- (instancetype)initWithURL:(NSURL *)URL;

/*!
	@method			initWithPlayerItem:
	@abstract		Create an AVPlayer that plays a single audiovisual item.
	@param			item
	@result			An instance of AVPlayer
	@discussion		Useful in order to play items for which an AVAsset has previously been created. See -[AVPlayerItem initWithAsset:].
*/
- (instancetype)initWithPlayerItem:(nullable AVPlayerItem *)item;

/*!
 @property status
 @abstract
	The ability of the receiver to be used for playback.
 
 @discussion
	The value of this property is an AVPlayerStatus that indicates whether the receiver can be used for playback. When
	the value of this property is AVPlayerStatusFailed, the receiver can no longer be used for playback and a new
	instance needs to be created in its place. When this happens, clients can check the value of the error property to
	determine the nature of the failure. This property is key value observable.
 */
@property (nonatomic, readonly) AVPlayerStatus status;

/*!
 @property error
 @abstract
	If the receiver's status is AVPlayerStatusFailed, this describes the error that caused the failure.
 
 @discussion
	The value of this property is an NSError that describes what caused the receiver to no longer be able to play items.
	If the receiver's status is not AVPlayerStatusFailed, the value of this property is nil.
 */
@property (nonatomic, readonly, nullable) NSError *error;

@end


@interface AVPlayer (AVPlayerPlaybackControl)

/*!
 @property		rate
 @abstract		Indicates the desired rate of playback; 0.0 means "paused", 1.0 indicates a desire to play at the natural rate of the current item.
 @discussion
 Setting the value of rate to 0.0 pauses playback, causing the value of timeControlStatus to change to AVPlayerTimeControlStatusPaused.
 Setting the rate to a non-zero value causes the value of timeControlStatus to become either AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate or AVPlayerTimeControlStatusPlaying, depending on whether sufficient media data has been buffered for playback to occur and whether the player's default behavior of waiting in order to minimize stalling is permitted. See discussion of AVPlayerTimeControlStatus for more details.
 
 AVPlayer can reset the desired rate to 0.0 when a change in overall state requires playback to be halted, such as when an interruption occurs on iOS, as announced by AVAudioSession, or when the playback buffer becomes empty and playback stalls while automaticallyWaitsToMinimizeStalling is NO.

 The effective rate of playback may differ from the desired rate even while timeControlStatus is AVPlayerTimeControlStatusPlaying, if the processing algorithm in use for managing audio pitch requires quantization of playback rate. For information about quantization of rates for audio processing, see AVAudioProcessingSettings.h. You can always obtain the effective rate of playback from the currentItem's timebase; see the timebase property of AVPlayerItem.
 */
@property (nonatomic) float rate;

/*!
 @method		play
 @abstract		Signals the desire to begin playback at the current item's natural rate.
 @discussion	Equivalent to setting the value of rate to 1.0.
 */
- (void)play;

/*!
 @method		pause
 @abstract		Pauses playback.
 @discussion	Equivalent to setting the value of rate to 0.0.
 */
- (void)pause;

/*!
 @enum AVPlayerTimeControlStatus
 @abstract
	These constants are the allowable values of AVPlayer's timeControlStatus property. This discussion pertains when automaticallyWaitsToMinimizeStalling is YES, the default setting, and exceptions are discussed in connection with automaticallyWaitsToMinimizeStalling.
 
 @constant	 AVPlayerTimeControlStatusPaused
	This state is entered upon receipt of a -pause message, an invocation of -setRate: with a value of 0.0, when a change in overall state requires playback to be halted, such as when an interruption occurs on iOS, as announced by AVAudioSession.
    In this state, playback is paused indefinitely and will not resume until 1) a subsequent -play message is received or 2) a -setRate: or -playImmediatelyAtRate: message with a non-zero value for rate is received and sufficient media data has been buffered for playback to proceed.
 @constant	 AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate
    This state is entered when 1) the playback buffer becomes empty and playback stalls in AVPlayerTimeControlStatusPlaying, 2) when rate is set from zero to non-zero in AVPlayerTimeControlStatusPaused and insufficient media data has been buffered for playback to occur, or 3) when the player has no item to play, i.e. when the receiver's currentItem is nil.
    In this state, the value of the rate property is not currently effective but instead indicates the rate at which playback will start or resume. Refer to the value of reasonForWaitingToPlay for details about why the receiver is waiting and the conditions that allow waitStatus to change to AVPlayerWaitStatusPlaying.
	While waiting for buffering, you can attempt to start playback of any available media data via -playImmediatelyAtRate:.
 @constant	 AVPlayerTimeControlStatusPlaying
	In this state, playback is currently progressing and rate changes will take effect immediately. Should playback stall because of insufficient media data, timeControlStatus will change to AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate.
 */
typedef NS_ENUM(NSInteger, AVPlayerTimeControlStatus) {
	AVPlayerTimeControlStatusPaused = 0,
	AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate = 1,
	AVPlayerTimeControlStatusPlaying = 2
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));


/*!
 @property		timeControlStatus
 @abstract		Indicates whether playback is currently paused indefinitely, suspended while waiting for appropriate conditions, or in progress.
 @discussion    For possible values and discussion, see AVPlayerTimeControlStatus.
 
When automaticallyWaitsToMinimizeStalling is YES, absent intervention in the form of invocations of -setRate: or -pause or, on iOS, an interruption that requires user intervention before playback can resume, the value of the property timeControlStatus automatically changes between AVPlayerTimeControlStatusPlaying and AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate depending on whether sufficient media data is available to continue playback. This property is key value observable.
*/
@property (nonatomic, readonly) AVPlayerTimeControlStatus timeControlStatus API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*!
 @typedef AVPlayerWaitingReason
 @abstract
    The type of reason that a player is waiting for playback.
*/
typedef NSString * AVPlayerWaitingReason NS_STRING_ENUM;

/*!
 @constant AVPlayerWaitingToMinimizeStallsReason
 @abstract Indicates that the player is waiting for appropriate playback buffer conditions before starting playback
 @discussion
	The player is waiting for playback because automaticallyWaitToMinimizeStalling is YES and playback at the specified rate would likely cause the playback buffer to become empty before playback completes. Playback will resume when 1) playback at the specified rate will likely complete without a stall or 2) the playback buffer becomes full, meaning no forther buffering of media data is possible.
	When the value of automaticallyWaitsToMinimizeStalling is NO, timeControlStatus cannot become AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate for this reason.
 */
AVF_EXPORT AVPlayerWaitingReason const AVPlayerWaitingToMinimizeStallsReason API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*!
 @constant AVPlayerWaitingWhileEvaluatingBufferingRateReason
 @abstract Indicates that the player is monitoring the playback buffer fill rate to determine if playback is likely to complete without interruptions.
 @discussion
	The player is waiting for playback because automaticallyWaitToMinimizeStalling is YES and it has not yet determined if starting playback at the specified rate would likely cause the buffer to become empty. When the brief initial monitoring period is over, either playback will begin or the value of reasonForWaitingToPlayAtSpecifiedRate will switch to AVPlayerWaitingToMinimizeStallsReason.
	Recommended practice is not to show UI indicating the waiting state to the user while the value of reasonForWaitingToPlayAtSpecifiedRate is AVPlayerWaitingWhileEvaluatingBufferingRateReason.
 */
AVF_EXPORT AVPlayerWaitingReason const AVPlayerWaitingWhileEvaluatingBufferingRateReason API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*!
 @constant AVPlayerWaitingWithNoItemToPlayReason
 @abstract Indicates that the AVPlayer is waiting because its currentItem is nil
 @discussion
	The player is waiting for playback because automaticallyWaitToMinimizeStalling is YES and the value of currentItem is nil. When an item becomes available, either because of a call to -replaceCurrentItemWithPlayerItem: or  -insertItem: afterItem:, playback will begin or the value of reasonForWaitingToPlay will change.
 */
AVF_EXPORT AVPlayerWaitingReason const AVPlayerWaitingWithNoItemToPlayReason API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));


/*!
 @property		reasonForWaitingToPlay
 @abstract		Indicates the reason for waiting when the value of timeControlStatus is AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate
 @discussion
    When the value of timeControlStatus is AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate, this property describes why the player is currently waiting. It is nil otherwise.
    You can use the value of reasonForWaitingToPlay to show UI indicating the player's waiting state conditionally.
    This property is key value observable.
    Possible values are AVPlayerWaitingWithNoItemToPlayReason, AVPlayerWaitingWhileEvaluatingBufferingRateReason, and AVPlayerWaitingToMinimizeStallsReason.
*/

@property (nonatomic, readonly, nullable) AVPlayerWaitingReason reasonForWaitingToPlay API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));


/*!
 @method		playImmediatelyAtRate:
 @abstract		Immediately plays the available media data at the specified rate.
 @discussion
 When the player's currentItem has a value of NO for playbackBufferEmpty, this method causes the value of rate to change to the specified rate, the value of timeControlStatus to change to AVPlayerTimeControlStatusPlaying, and the receiver to play the available media immediately, whether or not prior buffering of media data is sufficient to ensure smooth playback.
 If insufficient media data is buffered for playback to start (e.g. if the current item has a value of YES for playbackBufferEmpty), the receiver will act as if the buffer became empty during playback, except that no AVPlayerItemPlaybackStalledNotification will be posted.
 */
- (void)playImmediatelyAtRate:(float)rate API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

@end


@interface AVPlayer (AVPlayerItemControl)

/* indicates the current item of the player */
@property (nonatomic, readonly, nullable) AVPlayerItem *currentItem;

/*!
	@method			replaceCurrentItemWithPlayerItem:
	@abstract		Replaces the player's current item with the specified player item.
	@param			item
	  The AVPlayerItem that will become the player's current item.
	@discussion
	  In all releases of iOS 4, invoking replaceCurrentItemWithPlayerItem: with an AVPlayerItem that's already the receiver's currentItem results in an exception being raised. Starting with iOS 5, it's a no-op.
*/
- (void)replaceCurrentItemWithPlayerItem:(nullable AVPlayerItem *)item;

/*!
 @enum AVPlayerActionAtItemEnd
 @abstract
	These constants are the allowable values of AVPlayer's actionAtItemEnd property.
 
 @constant	 AVPlayerActionAtItemEndAdvance
	Indicates that when an AVPlayerItem reaches its end time the player will automatically advance to the next item in its queue.
	This value is supported only for players of class AVQueuePlayer. An AVPlayer that's not an AVQueuePlayer will raise an NSInvalidArgumentException if an attempt is made to set its actionAtItemEnd to AVPlayerActionAtItemEndAdvance.
 @constant	 AVPlayerActionAtItemEndPause
	Indicates that when an AVPlayerItem reaches its end time the player will automatically pause (which is to say, the player's
	rate will automatically be set to 0).
 @constant	 AVPlayerActionAtItemEndNone
	Indicates that when an AVPlayerItem reaches its end time the player will take no action (which is to say, the player's rate
	will not change, its currentItem will not change, and its currentTime will continue to be incremented or decremented as time
	elapses, according to its rate). After this, if the player's actionAtItemEnd is set to a value other than AVPlayerActionAtItemEndNone,
	the player will immediately take the action appropriate to that value.
*/
typedef NS_ENUM(NSInteger, AVPlayerActionAtItemEnd)
{
    AVPlayerActionAtItemEndAdvance	= 0,
	AVPlayerActionAtItemEndPause	= 1,
	AVPlayerActionAtItemEndNone		= 2,
};

/* indicates the action that the player should perform when playback of an item reaches its end time */
@property AVPlayerActionAtItemEnd actionAtItemEnd;

@end


@interface AVPlayer (AVPlayerTimeControl)
/*!
 @method			currentTime
 @abstract			Returns the current time of the current item.
 @result			A CMTime
 @discussion		Returns the current time of the current item. Not key-value observable; use -addPeriodicTimeObserverForInterval:queue:usingBlock: instead.
 */
- (CMTime)currentTime;

/*!
 @method			seekToDate:
 @abstract			Moves the playback cursor.
 @param				date
 @discussion		Use this method to seek to a specified time for the current player item.
					The time seeked to may differ from the specified time for efficiency. For sample accurate seeking see seekToTime:toleranceBefore:toleranceAfter:.
 */
- (void)seekToDate:(NSDate *)date;

/*!
 @method			seekToDate:completionHandler:
 @abstract			Moves the playback cursor and invokes the specified block when the seek operation has either been completed or been interrupted.
 @param				date
 @param				completionHandler
 @discussion		Use this method to seek to a specified time for the current player item and to be notified when the seek operation is complete.
					The completion handler for any prior seek request that is still in process will be invoked immediately with the finished parameter 
					set to NO. If the new request completes without being interrupted by another seek request or by any other operation the specified 
					completion handler will be invoked with the finished parameter set to YES. 
 */
- (void)seekToDate:(NSDate *)date completionHandler:(void (^)(BOOL finished))completionHandler API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0), watchos(1.0));

/*!
 @method			seekToTime:
 @abstract			Moves the playback cursor.
 @param				time
 @discussion		Use this method to seek to a specified time for the current player item.
					The time seeked to may differ from the specified time for efficiency. For sample accurate seeking see seekToTime:toleranceBefore:toleranceAfter:.
 */
- (void)seekToTime:(CMTime)time;

/*!
 @method			seekToTime:toleranceBefore:toleranceAfter:
 @abstract			Moves the playback cursor within a specified time bound.
 @param				time
 @param				toleranceBefore
 @param				toleranceAfter
 @discussion		Use this method to seek to a specified time for the current player item.
					The time seeked to will be within the range [time-toleranceBefore, time+toleranceAfter] and may differ from the specified time for efficiency.
					Pass kCMTimeZero for both toleranceBefore and toleranceAfter to request sample accurate seeking which may incur additional decoding delay. 
					Messaging this method with beforeTolerance:kCMTimePositiveInfinity and afterTolerance:kCMTimePositiveInfinity is the same as messaging seekToTime: directly.
 */
- (void)seekToTime:(CMTime)time toleranceBefore:(CMTime)toleranceBefore toleranceAfter:(CMTime)toleranceAfter;

/*!
 @method			seekToTime:completionHandler:
 @abstract			Moves the playback cursor and invokes the specified block when the seek operation has either been completed or been interrupted.
 @param				time
 @param				completionHandler
 @discussion		Use this method to seek to a specified time for the current player item and to be notified when the seek operation is complete.
					The completion handler for any prior seek request that is still in process will be invoked immediately with the finished parameter 
					set to NO. If the new request completes without being interrupted by another seek request or by any other operation the specified 
					completion handler will be invoked with the finished parameter set to YES. 
 */
- (void)seekToTime:(CMTime)time completionHandler:(void (^)(BOOL finished))completionHandler API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0), watchos(1.0));

/*!
 @method			seekToTime:toleranceBefore:toleranceAfter:completionHandler:
 @abstract			Moves the playback cursor within a specified time bound and invokes the specified block when the seek operation has either been completed or been interrupted.
 @param				time
 @param				toleranceBefore
 @param				toleranceAfter
 @discussion		Use this method to seek to a specified time for the current player item and to be notified when the seek operation is complete.
					The time seeked to will be within the range [time-toleranceBefore, time+toleranceAfter] and may differ from the specified time for efficiency.
					Pass kCMTimeZero for both toleranceBefore and toleranceAfter to request sample accurate seeking which may incur additional decoding delay. 
					Messaging this method with beforeTolerance:kCMTimePositiveInfinity and afterTolerance:kCMTimePositiveInfinity is the same as messaging seekToTime: directly.
					The completion handler for any prior seek request that is still in process will be invoked immediately with the finished parameter set to NO. If the new 
					request completes without being interrupted by another seek request or by any other operation the specified completion handler will be invoked with the 
					finished parameter set to YES.
 */
- (void)seekToTime:(CMTime)time toleranceBefore:(CMTime)toleranceBefore toleranceAfter:(CMTime)toleranceAfter completionHandler:(void (^)(BOOL finished))completionHandler API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0), watchos(1.0));

@end


@interface AVPlayer (AVPlayerAdvancedRateControl)


/*!
 @property		automaticallyWaitsToMinimizeStalling
 @abstract		Indicates that the player is allowed to delay playback at the specified rate in order to minimize stalling
 @discussion
 
 When this property is YES, whenever 1) the rate is set from zero to non-zero or 2) the playback buffer becomes empty and playback stalls, the player will attempt to determine if, at the specified rate, its currentItem will play to the end without interruptions. Should it determine that such interruptions would occur and these interruptions can be avoided by delaying the start or resumption of playback, the value of timeControlStatus will become AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate and playback will start automatically when the likelihood of stalling has been minimized.
 
 You may want to set this property to NO when you need precise control over playback start times, e.g., when synchronizing multiple instances of AVPlayer, and you should set it to NO if you use an AVAssetResourceLoader delegate to load media data (more on this below). If the value of this property is NO, reasonForWaitingToPlay cannot assume a value of AVPlayerWaitingToMinimizeStallsReason.
 This implies that setting rate to a non-zero value in AVPlayerTimeControlStatusPaused will cause playback to start immediately as long as the playback buffer is not empty. When the playback buffer becomes empty during AVPlayerTimeControlStatusPlaying and playback stalls, playback state will switch to AVPlayerTimeControlStatusPaused and the rate will become 0.0.
 
 Changing the value of this property to NO while the value of timeControlStatus is AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate with a reasonForWaitingToPlay of AVPlayerWaitingToMinimizeStallsReason will cause the player to attempt playback at the specified rate immediately.
 
 For clients linked against iOS 10.0 and running on that version or later or linked against OS X 10.12 and running on that version or later, the default value of this property is YES.
 In versions of iOS prior to iOS 10.0 and versions of OS X prior to 10.12, this property is unavailable, and the behavior of the AVPlayer corresponds to the type of content being played. For streaming content, including HTTP Live Streaming, the AVPlayer acts as if automaticallyWaitsToMinimizeStalling is YES. For file-based content, including file-based content accessed via progressive http download, the AVPlayer acts as if automaticallyWaitsToMinimizeStalling is NO.

 If you employ an AVAssetResourceLoader delegate that loads media data for playback, you should set the value of your AVPlayer’s automaticallyWaitsToMinimizeStalling property to NO. Allowing the value of automaticallyWaitsToMinimizeStalling to remain YES when an AVAssetResourceLoader delegate is used for the loading of media data can result in poor start-up times for playback and poor recovery from stalls, because the behaviors provided by AVPlayer when automaticallyWaitsToMinimizeStalling has a value of YES depend on predictions of the future availability of media data that that do not function as expected when data is loaded via a client-controlled means, using the AVAssetResourceLoader delegate interface.

 You can allow the value of automaticallyWaitsToMinimizeStalling to remain YES if you use an AVAssetResourceLoader delegate to manage content keys for FairPlay Streaming, to provide dynamically-generated master playlists for HTTP Live Streaming, or to respond to authentication challenges, but not to load media data for playback.
*/

@property (nonatomic) BOOL automaticallyWaitsToMinimizeStalling API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));



/*!
	@method			setRate:time:atHostTime:
	@abstract		Simultaneously sets the playback rate and the relationship between the current item's current time and host time.
	@discussion		You can use this function to synchronize playback with an external activity.
	
					The current item's timebase is adjusted so that its time will be (or was) itemTime when host time is (or was) hostClockTime.
					In other words: if hostClockTime is in the past, the timebase's time will be interpolated as though the timebase has been running at the requested rate since that time.  If hostClockTime is in the future, the timebase will immediately start running at the requested rate from an earlier time so that it will reach the requested itemTime at the requested hostClockTime.  (Note that the item's time will not jump backwards, but instead will sit at itemTime until the timebase reaches that time.)

					Note that setRate:time:atHostTime: is not supported when automaticallyWaitsToMinimizeStalling is YES. For clients linked against iOS 10.0 and later or OS X 12.0 and later, invoking setRate:time:atHostTime: when automaticallyWaitsToMinimizeStalling is YES will raise an NSInvalidArgument exception. Support for HTTP Live Streaming content requires iOS 11, tvOS 11, macOS 10.13 or later.
	@param itemTime	The time to start playback from, specified precisely (i.e., with zero tolerance).
					Pass kCMTimeInvalid to use the current item's current time.
	@param hostClockTime
					The host time at which to start playback.
					If hostClockTime is specified, the player will not ensure that media data is loaded before the timebase starts moving.
					If hostClockTime is kCMTimeInvalid, the rate and time will be set together, but without external synchronization;
					a host time in the near future will be used, allowing some time for media data loading.
*/
- (void)setRate:(float)rate time:(CMTime)itemTime atHostTime:(CMTime)hostClockTime API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));

/*!
	@method			prerollAtRate:completionHandler:
	@abstract		Begins loading media data to prime the render pipelines for playback from the current time with the given rate.
	@discussion		Once the completion handler is called with YES, the player's rate can be set with minimal latency.
					The completion handler will be called with NO if the preroll is interrupted by a time change or incompatible rate change, or if preroll is not possible for some other reason.
					Call this method only when the rate is currently zero and only after the AVPlayer's status has become AVPlayerStatusReadyToPlay.
	@param rate		The intended rate for subsequent playback.
	@param completionHandler
					The block that will be called when the preroll is either completed or is interrupted.
*/
- (void)prerollAtRate:(float)rate completionHandler:(nullable void (^)(BOOL finished))completionHandler API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));

/*!
	@method			cancelPendingPrerolls
	@abstract		Cancel any pending preroll requests and invoke the corresponding completion handlers if present.
	@discussion		Use this method to cancel and release the completion handlers for pending prerolls. The finished parameter of the completion handlers will be set to NO.
*/
- (void)cancelPendingPrerolls API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));

/* NULL by default.  if not NULL, overrides the automatic choice of master clock for item timebases. This is most useful for synchronizing video-only movies with audio played via other means. IMPORTANT: If you specify a master clock other than the appropriate audio device clock, audio may drift out of sync. */
@property (nonatomic, retain, nullable) __attribute__((NSObject)) CMClockRef masterClock API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));

@end


@interface AVPlayer (AVPlayerTimeObservation)

/*!
	@method			addPeriodicTimeObserverForInterval:queue:usingBlock:
	@abstract		Requests invocation of a block during playback to report changing time.
	@param			interval
	  The interval of invocation of the block during normal playback, according to progress of the current time of the player.
	@param			queue
	  The serial queue onto which block should be enqueued.  If you pass NULL, the main queue (obtained using dispatch_get_main_queue()) will be used.  Passing a
	  concurrent queue to this method will result in undefined behavior.
	@param			block
	  The block to be invoked periodically.
	@result
	  An object conforming to the NSObject protocol.  You must retain this returned value as long as you want the time observer to be invoked by the player.
	  Pass this object to -removeTimeObserver: to cancel time observation.
	@discussion		The block is invoked periodically at the interval specified, interpreted according to the timeline of the current item.
					The block is also invoked whenever time jumps and whenever playback starts or stops.
					If the interval corresponds to a very short interval in real time, the player may invoke the block less frequently
					than requested. Even so, the player will invoke the block sufficiently often for the client to update indications
					of the current time appropriately in its end-user interface.
					Each call to -addPeriodicTimeObserverForInterval:queue:usingBlock: should be paired with a corresponding call to -removeTimeObserver:.
					Releasing the observer object without a call to -removeTimeObserver: will result in undefined behavior.
*/
- (id)addPeriodicTimeObserverForInterval:(CMTime)interval queue:(nullable dispatch_queue_t)queue usingBlock:(void (^)(CMTime time))block;

/*!
	@method			addBoundaryTimeObserverForTimes:queue:usingBlock:
	@abstract		Requests invocation of a block when specified times are traversed during normal playback.
	@param			times
	  The times for which the observer requests notification, supplied as an array of NSValues carrying CMTimes.
	@param			queue
	  The serial queue onto which block should be enqueued.  If you pass NULL, the main queue (obtained using dispatch_get_main_queue()) will be used.  Passing a
	  concurrent queue to this method will result in undefined behavior.
	@param			block
	  The block to be invoked when any of the specified times is crossed during normal playback.
	@result
	  An object conforming to the NSObject protocol.  You must retain this returned value as long as you want the time observer to be invoked by the player.
	  Pass this object to -removeTimeObserver: to cancel time observation.
	@discussion		Each call to -addPeriodicTimeObserverForInterval:queue:usingBlock: should be paired with a corresponding call to -removeTimeObserver:.
					Releasing the observer object without a call to -removeTimeObserver: will result in undefined behavior.
*/
- (id)addBoundaryTimeObserverForTimes:(NSArray<NSValue *> *)times queue:(nullable dispatch_queue_t)queue usingBlock:(void (^)(void))block;

/*!
	@method			removeTimeObserver:
	@abstract		Cancels a previously registered time observer.
	@param			observer
	  An object returned by a previous call to -addPeriodicTimeObserverForInterval:queue:usingBlock: or -addBoundaryTimeObserverForTimes:queue:usingBlock:.
	@discussion		Upon return, the caller is guaranteed that no new time observer blocks will begin executing.  Depending on the calling thread and the queue
					used to add the time observer, an in-flight block may continue to execute after this method returns.  You can guarantee synchronous time 
					observer removal by enqueuing the call to -removeTimeObserver: on that queue.  Alternatively, call dispatch_sync(queue, ^{}) after
					-removeTimeObserver: to wait for any in-flight blocks to finish executing.
					-removeTimeObserver: should be used to explicitly cancel each time observer added using -addPeriodicTimeObserverForInterval:queue:usingBlock:
					and -addBoundaryTimeObserverForTimes:queue:usingBlock:.
*/
- (void)removeTimeObserver:(id)observer;

@end


@interface AVPlayer (AVPlayerMediaControl)

/* Indicates the current audio volume of the player; 0.0 means "silence all audio", 1.0 means "play at the full volume of the current item".

   iOS note: Do not use this property to implement a volume slider for media playback. For that purpose, use MPVolumeView, which is customizable in appearance and provides standard media playback behaviors that users expect.
   This property is most useful on iOS to control the volume of the AVPlayer relative to other audio output, not for volume control by end users. */
@property float volume API_AVAILABLE(macos(10.7), ios(7.0), tvos(9.0), watchos(1.0));

/* indicates whether or not audio output of the player is muted. Only affects audio muting for the player instance and not for the device. */
@property (getter=isMuted) BOOL muted API_AVAILABLE(macos(10.7), ios(7.0), tvos(9.0), watchos(1.0));

@end


@class AVPlayerMediaSelectionCriteria;

@interface AVPlayer (AVPlayerAutomaticMediaSelection)

/* Indicates whether the receiver should apply the current selection criteria automatically to AVPlayerItems.
 For clients linked against the iOS 7 SDK or later or against the OS X 10.9 SDK or later, the default is YES. For all others, the default is NO.

 By default, AVPlayer applies selection criteria based on system preferences. To override the default criteria for any media selection group, use -[AVPlayer setMediaSelectionCriteria:forMediaCharacteristic:].
*/
@property BOOL appliesMediaSelectionCriteriaAutomatically API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
 @method     setMediaSelectionCriteria:forMediaCharacteristic:
 @abstract   Applies automatic selection criteria for media that has the specified media characteristic.
 @param      criteria
   An instance of AVPlayerMediaSelectionCriteria.
 @param      mediaCharacteristic
   The media characteristic for which the selection criteria are to be applied. Supported values include AVMediaCharacteristicAudible, AVMediaCharacteristicLegible, and AVMediaCharacteristicVisual.
 @discussion
	Criteria will be applied to an AVPlayerItem when:
		a) It is made ready to play
		b) Specific media selections are made by -[AVPlayerItem selectMediaOption:inMediaSelectionGroup:] in a different group. The automatic choice in one group may be influenced by a specific selection in another group.
		c) Underlying system preferences change, e.g. system language, accessibility captions.

   Specific selections made by -[AVPlayerItem selectMediaOption:inMediaSelectionGroup:] within any group will override automatic selection in that group until -[AVPlayerItem selectMediaOptionAutomaticallyInMediaSelectionGroup:] is received.
*/
- (void)setMediaSelectionCriteria:(nullable AVPlayerMediaSelectionCriteria *)criteria forMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
 @method     mediaSelectionCriteriaForMediaCharacteristic:
 @abstract   Returns the automatic selection criteria for media that has the specified media characteristic.
 @param      mediaCharacteristic
  The media characteristic for which the selection criteria is to be returned. Supported values include AVMediaCharacteristicAudible, AVMediaCharacteristicLegible, and AVMediaCharacteristicVisual.
*/
- (nullable AVPlayerMediaSelectionCriteria *)mediaSelectionCriteriaForMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

@end


@interface AVPlayer (AVPlayerAudioDeviceSupport)

/*!
 @property audioOutputDeviceUniqueID
 @abstract
	Specifies the unique ID of the Core Audio output device used to play audio.
 @discussion
	By default, the value of this property is nil, indicating that the default audio output device is used. Otherwise the value of this property is an NSString containing the unique ID of the Core Audio output device to be used for audio output.

	Core Audio's kAudioDevicePropertyDeviceUID is a suitable source of audio output device unique IDs.
*/
@property (copy, nullable) NSString *audioOutputDeviceUniqueID API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, tvos, watchos);

@end

/*
 @category		
	AVPlayer (AVPlayerExternalPlaybackSupport)
 
 @abstract
	Methods for supporting "external playback" of video 
 
 @discussion
	"External playback" is a mode where video data is sent to an external device for full screen playback at its original fidelity.
	AirPlay Video playback is considered as an "external playback" mode.
 
	In "external screen" mode (also known as mirroring and second display), video data is rendered on the host 
	device (e.g. Mac and iPhone), rendered video is recompressed and transferred to the external device, and the
	external device decompresses and displays the video.
 
	AVPlayerExternalPlaybackSupport properties affect AirPlay Video playback and are the replacement for the 
	deprecated AVPlayerAirPlaySupport properties.
 
	Additional note for iOS: AVPlayerExternalPlaybackSupport properties apply to the Lightning-based
	video adapters but do not apply to 30-pin-connector-based video output cables and adapters.
 */

@interface AVPlayer (AVPlayerExternalPlaybackSupport)

/* Indicates whether the player allows switching to "external playback" mode. The default value is YES. */
@property BOOL allowsExternalPlayback API_AVAILABLE(macos(10.11), ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/* Indicates whether the player is currently playing video in "external playback" mode. */
@property (nonatomic, readonly, getter=isExternalPlaybackActive) BOOL externalPlaybackActive API_AVAILABLE(macos(10.11), ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/* Indicates whether the player should automatically switch to "external playback" mode while the "external 
	screen" mode is active in order to play video content and switching back to "external screen" mode as soon 
	as playback is done. Brief transition may be visible on the external display when automatically switching 
	between the two modes. The default value is NO. Has no effect if allowsExternalPlayback is NO. */
@property BOOL usesExternalPlaybackWhileExternalScreenIsActive API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(macos, watchos);

/* Video gravity strictly for "external playback" mode, one of AVLayerVideoGravity* defined in AVAnimation.h */
@property (nonatomic, copy) AVLayerVideoGravity externalPlaybackVideoGravity API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(macos, watchos);

@end

#if TARGET_OS_IPHONE

@interface AVPlayer (AVPlayerAirPlaySupport)

/* Indicates whether the player allows AirPlay Video playback. The default value is YES. 
	This property is deprecated. Use AVPlayer's -allowsExternalPlayback instead. */
@property BOOL allowsAirPlayVideo API_DEPRECATED("No longer supported", ios(5.0, 6.0), tvos(9.0, 9.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos);

/* Indicates whether the player is currently playing video via AirPlay. 
	This property is deprecated. Use AVPlayer's -externalPlaybackActive instead.*/
@property (nonatomic, readonly, getter=isAirPlayVideoActive) BOOL airPlayVideoActive API_DEPRECATED("No longer supported", ios(5.0, 6.0), tvos(9.0, 9.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos);

/* Indicates whether the player should automatically switch to AirPlay Video while AirPlay Screen is active in order to play video content, switching back to AirPlay Screen as soon as playback is done. 
	The default value is NO. Has no effect if allowsAirPlayVideo is NO.
	This property is deprecated. Use AVPlayer's -usesExternalPlaybackWhileExternalScreenIsActive instead. */
@property BOOL usesAirPlayVideoWhileAirPlayScreenIsActive API_DEPRECATED("No longer supported", ios(5.0, 6.0), tvos(9.0, 9.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos);

@end

#endif // TARGET_OS_IPHONE

/*
	@category		AVPlayer (AVPlayerProtectedContent)
	@abstract		Methods supporting protected content.
*/

@interface AVPlayer (AVPlayerProtectedContent)

/*!
	@property outputObscuredDueToInsufficientExternalProtection
	@abstract
		Whether or not decoded output is being obscured due to insufficient external protection.
 
	@discussion
		The value of this property indicates whether the player is purposefully obscuring the visual output
		of the current item because the requirement for an external protection mechanism is not met by the
		current device configuration. It is highly recommended that clients whose content requires external
		protection observe this property and set the playback rate to zero and display an appropriate user
		interface when the value changes to YES. This property is key value observable.

		Note that the value of this property is dependent on the external protection requirements of the
		current item. These requirements are inherent to the content itself and cannot be externally specified.
		If the current item does not require external protection, the value of this property will be NO.
 */
@property (nonatomic, readonly) BOOL outputObscuredDueToInsufficientExternalProtection API_AVAILABLE(macos(10.12), ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos);

@end

/*!
 @typedef AVPlayerHDRMode
 @abstract  A bitfield type that specifies an HDR mode.
 
 @constant	AVPlayerHDRModeHLG
 @abstract	Indicates that HLG (Hybrid Log-Gamma) HDR mode is available.
 @constant	AVPlayerHDRModeHDR10
 @abstract	Indicates that HDR10 HDR mode is available.
 @constant	AVPlayerHDRModeDolbyVision
 @abstract	Indicates that Dolby Vision HDR mode is available.
 */
typedef NS_OPTIONS(NSInteger, AVPlayerHDRMode) {
	AVPlayerHDRModeHLG				= 0x1,
	AVPlayerHDRModeHDR10				= 0x2,
	AVPlayerHDRModeDolbyVision		= 0x4,
} API_AVAILABLE(ios(11.2), tvos(11.2)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos);

@interface AVPlayer (AVPlayerPlaybackCapabilities)

/*!
	 @property		availableHDRModes
	 @abstract		An AVPlayerHDRMode value that indicates the HDR modes the device can play to an appropriate display.   A value of 0 indicates that no HDR modes are supported.
 
	 @discussion
		 This property indicates all of the HDR modes that the device can play.  Each value indicates that an appropriate HDR display is available for the specified HDR mode.  Additionally, the device must be capable of playing the specified HDR type.  This property does not indicate whether video contains HDR content, whether HDR video is currently playing, or whether video is playing on an HDR display.
*/
@property (class, nonatomic, readonly) AVPlayerHDRMode availableHDRModes API_AVAILABLE(ios(11.2), tvos(11.2)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos);

/*!
	 @constant		AVPlayerAvailableHDRModesDidChangeNotification
	 @abstract		A notification that fires whenever availableHDRModes changes.
 
	 @discussion
		 This notification fires when a value is added or removed from the list of availableHDRModes.  This can be caused by display connection/disconnection or resource changes.
*/
API_AVAILABLE(ios(11.2), tvos(11.2)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos)
AVF_EXPORT NSNotificationName const AVPlayerAvailableHDRModesDidChangeNotification;

/*!
 @property		eligibleForHDRPlayback
 @abstract		Indicates whether HDR content can be played to an appropriate display.
 
 @discussion
 This property is YES if an HDR display is available and the device is capable of playing HDR content from an appropriate AVAsset, NO otherwise.  This property does not indicate whether video contains HDR content, whether HDR video is currently playing, or whether video is playing on an HDR display.  This property is not KVO observable.
 */
@property (class, nonatomic, readonly) BOOL eligibleForHDRPlayback API_AVAILABLE(macos(10.15), ios(13.4), tvos(13.4)) API_UNAVAILABLE(watchos);

/*!
 @constant		eligibleForHDRPlaybackDidChangeNotification
 @abstract		A notification that fires whenever eligibleForHDRPlayback changes.
 
 @discussion
 This notification fires when eligibleForHDRPlayback changes.  This can be caused by display connection/disconnection or resource changes.
 */
API_AVAILABLE(macos(10.15), ios(13.4), tvos(13.4)) API_UNAVAILABLE(watchos)
AVF_EXPORT NSNotificationName const AVPlayerEligibleForHDRPlaybackDidChangeNotification;

@end

@interface AVPlayer (AVPlayerVideoDecoderGPUSupport)

/*!
	@property		preferredVideoDecoderGPURegistryID
	@abstract		Specifies a registryID associated with a GPU that should be used for video decode.

	@discussion
		By default, whenever possible, video decode will be performed on the GPU associated with the display on which the presenting CALayer is located.  Decode will be transitioned to a new GPU if appropriate when the CALayer moves to a new display.  This property overrides this default behavior, forcing decode to prefer an affinity to the GPU specified regardless of which GPU is being used to display the associated CALayer.

		The GPU registryID can be obtained from the GPU MTLDevice using [MTLDevice registryID] or can be obtained from OpenGL or OpenCL.
*/
@property (nonatomic) uint64_t preferredVideoDecoderGPURegistryID API_AVAILABLE(macos(10.13)) API_UNAVAILABLE(ios, tvos, watchos);

@end

@interface AVPlayer (AVPlayerVideoDisplaySleepPrevention)

/*!
 @property   preventsDisplaySleepDuringVideoPlayback
 @abstract   Indicates whether video playback prevents display and device sleep.
 @discussion
	 Default is YES on iOS, tvOS and in Mac Catalyst apps.  Default is NO on macOS.
	 Setting this property to NO does not force the display to sleep, it simply stops preventing display sleep.  Other apps or frameworks within your app may still be preventing display sleep for various reasons.
 */
@property (nonatomic) BOOL preventsDisplaySleepDuringVideoPlayback API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0)) API_UNAVAILABLE(watchos);

@end

@interface AVPlayer (AVPlayerDeprecated)

/*!
	@property closedCaptionDisplayEnabled
	@abstract
		Indicates whether display of closed captions is enabled.

	@discussion
		This property is deprecated.

		When the value of appliesMediaSelectionCriteriaAutomatically is YES, the receiver will enable closed captions automatically either according to user preferences or, if you provide them, according to AVPlayerMediaSelectionCriteria for the media characteristic AVMediaCharacteristicLegible.

		If you want to determine whether closed captions may be available for a given AVPlayerItem, you can examine the AVMediaSelectionOptions in the AVMediaSelectionGroup for the characteristic AVMediaCharacteristicLegible, as vended by -[AVAsset mediaSelectionGroupForMediaCharacteristic:]. See AVMediaCharacteristicTranscribesSpokenDialogForAccessibility and AVMediaCharacteristicDescribesMusicAndSoundForAccessibility as documented in AVMediaFormat.h for information about how to identify legible media selection options that offer the features of closed captions for accessibility purposes.

		You can select or deselect a specific AVMediaSelectionOption via -[AVPlayerItem selectMediaOption:inMediaSelectionGroup:].

		For further information about Media Accessibility preferences, see MediaAccessibility framework documentation.
 */
@property (getter=isClosedCaptionDisplayEnabled) BOOL closedCaptionDisplayEnabled API_DEPRECATED("Allow AVPlayer to enable closed captions automatically according to user preferences by ensuring that the value of appliesMediaSelectionCriteriaAutomatically is YES.", macos(10.7, 10.13), ios(4.0, 11.0), tvos(9.0, 11.0)) API_UNAVAILABLE(watchos);

@end

/*!
	@class			AVQueuePlayer
 
	@abstract
      AVQueuePlayer is a subclass of AVPlayer that offers an interface for multiple-item playback.
 
	@discussion
      AVQueuePlayer extends AVPlayer with methods for managing a queue of items to be played in sequence.
      It plays these items as gaplessly as possible in the current runtime environment, depending on 
      the timely availability of media data for the enqueued items.
      
      For best performance clients should typically enqueue only as many AVPlayerItems as are necessary
      to ensure smooth playback. Note that once an item is enqueued it becomes eligible to be loaded and
      made ready for playback, with whatever I/O and processing overhead that entails.

*/

@class AVQueuePlayerInternal;

API_AVAILABLE(macos(10.7), ios(4.1), tvos(9.0), watchos(1.0))
@interface AVQueuePlayer : AVPlayer 
{
@private
    AVQueuePlayerInternal   *_queuePlayer;
}

/*!
    @method     queuePlayerWithItems:
    @abstract   Creates an instance of AVQueuePlayer and enqueues the AVPlayerItems from the specified array.
    @param      items
      An NSArray of AVPlayerItems with which to populate the player's queue initially.
    @result
      An instance of AVQueuePlayer.
*/
+ (instancetype)queuePlayerWithItems:(NSArray<AVPlayerItem *> *)items;

/*!
    @method     initWithItems:
    @abstract   Initializes an instance of AVQueuePlayer by enqueueing the AVPlayerItems from the specified array.
    @param      items
      An NSArray of AVPlayerItems with which to populate the player's queue initially.
    @result
      An instance of AVQueuePlayer.
*/
- (AVQueuePlayer *)initWithItems:(NSArray<AVPlayerItem *> *)items;

/*!
    @method     items
    @abstract   Provides an array of the currently enqueued items.
    @result     An NSArray containing the enqueued AVPlayerItems.
*/
- (NSArray<AVPlayerItem *> *)items;

/*!
    @method     advanceToNextItem
    @abstract   Ends playback of the current item and initiates playback of the next item in the player's queue.
    @discussion Removes the current item from the play queue.
*/
- (void)advanceToNextItem;

/*!
    @method     canInsertItem:afterItem:
    @abstract   Tests whether an AVPlayerItem can be inserted into the player's queue.
    @param      item
      The AVPlayerItem to be tested.
    @param      afterItem
      The item that the item to be tested is to follow in the queue. Pass nil to test whether the item can be appended to the queue.
    @result
      An indication of whether the item can be inserted into the queue after the specified item.
    @discussion
      Note that adding the same AVPlayerItem to an AVQueuePlayer at more than one position in the queue is not supported.
*/
- (BOOL)canInsertItem:(AVPlayerItem *)item afterItem:(nullable AVPlayerItem *)afterItem;

/*!
    @method     insertItem:afterItem:
    @abstract   Places an AVPlayerItem after the specified item in the queue.
    @param      item
      The item to be inserted.
    @param      afterItem
      The item that the newly inserted item should follow in the queue. Pass nil to append the item to the queue.
*/
- (void)insertItem:(AVPlayerItem *)item afterItem:(nullable AVPlayerItem *)afterItem;

/*!
    @method     removeItem:
    @abstract   Removes an AVPlayerItem from the queue.
    @param      item
      The item to be removed.
    @discussion
      If the item to be removed is currently playing, has the same effect as -advanceToNextItem.
*/
- (void)removeItem:(AVPlayerItem *)item;

/*!
    @method     removeAllItems
    @abstract   Removes all items from the queue.
    @discussion Stops playback by the target.
*/
- (void)removeAllItems;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVPlayer.h>
#endif
