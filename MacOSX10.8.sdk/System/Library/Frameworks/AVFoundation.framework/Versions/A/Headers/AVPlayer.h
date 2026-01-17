/*
    File:  AVPlayer.h

	Framework:  AVFoundation
 
	Copyright 2010-2012 Apple Inc. All rights reserved.

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
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>
#import <CoreMedia/CMSync.h>
#import <Foundation/Foundation.h>

@class AVPlayerItem;
@class AVPlayerInternal;

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
enum {
	AVPlayerStatusUnknown,
	AVPlayerStatusReadyToPlay,
	AVPlayerStatusFailed
};
typedef NSInteger AVPlayerStatus;

NS_CLASS_AVAILABLE(10_7, 4_0)
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
+ (id)playerWithURL:(NSURL *)URL;

/*!
	@method			playerWithPlayerItem:
	@abstract		Create an AVPlayer that plays a single audiovisual item.
	@param			item
	@result			An instance of AVPlayer
	@discussion		Useful in order to play items for which an AVAsset has previously been created. See -[AVPlayerItem initWithAsset:].
*/
+ (id)playerWithPlayerItem:(AVPlayerItem *)item;

/*!
	@method			initWithURL:
	@abstract		Initializes an AVPlayer that plays a single audiovisual resource referenced by URL.
	@param			URL
	@result			An instance of AVPlayer
	@discussion		Implicitly creates an AVPlayerItem. Clients can obtain the AVPlayerItem as it becomes the player's currentItem.
*/
- (id)initWithURL:(NSURL *)URL;

/*!
	@method			initWithPlayerItem:
	@abstract		Create an AVPlayer that plays a single audiovisual item.
	@param			item
	@result			An instance of AVPlayer
	@discussion		Useful in order to play items for which an AVAsset has previously been created. See -[AVPlayerItem initWithAsset:].
*/
- (id)initWithPlayerItem:(AVPlayerItem *)item;

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
	If the receiver's status is not AVPlayerItemStatusFailed, the value of this property is nil.
 */
@property (nonatomic, readonly) NSError *error;

@end


@interface AVPlayer (AVPlayerPlaybackControl)

/* indicates the current rate of playback; 0.0 means "stopped", 1.0 means "play at the natural rate of the current item" */
@property (nonatomic) float rate;

/*!
	@method			play
	@abstract		Begins playback of the current item.
	@discussion		Same as setting rate to 1.0.
*/
- (void)play;

/*!
	@method			pause
	@abstract		Pauses playback.
	@discussion		Same as setting rate to 0.0.
*/
- (void)pause;

@end


@interface AVPlayer (AVPlayerItemControl)

/* indicates the current item of the player */
@property (nonatomic, readonly) AVPlayerItem *currentItem;

/*!
	@method			replaceCurrentItemWithPlayerItem:
	@abstract		Replaces the player's current item with the specified player item.
	@param			item
	  The AVPlayerItem that will become the player's current item.
	@discussion
	  For best results ensure that the tracks property of an AVPlayerItem's AVAsset, if there is one,
	  has reached the status AVKeyValueStatusLoaded before attempting to replace the current item with it.
	  See -[AVAsset loadValuesAsynchronouslyForKeys:completionHandler:].
	  
	  In all releases of iOS 4, invoking replaceCurrentItemWithPlayerItem: with an AVPlayerItem that's already the receiver's currentItem results in an exception being raised. Starting with iOS 5, it's a no-op.
*/
- (void)replaceCurrentItemWithPlayerItem:(AVPlayerItem *)item;

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
enum
{
    AVPlayerActionAtItemEndAdvance	= 0,
	AVPlayerActionAtItemEndPause	= 1,
	AVPlayerActionAtItemEndNone		= 2,
};
typedef NSInteger AVPlayerActionAtItemEnd;

/* indicates the action that the player should perform when playback of an item reaches its end time */
@property (nonatomic) AVPlayerActionAtItemEnd actionAtItemEnd;

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
- (void)seekToTime:(CMTime)time completionHandler:(void (^)(BOOL finished))completionHandler NS_AVAILABLE(10_7, 5_0);

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
- (void)seekToTime:(CMTime)time toleranceBefore:(CMTime)toleranceBefore toleranceAfter:(CMTime)toleranceAfter completionHandler:(void (^)(BOOL finished))completionHandler NS_AVAILABLE(10_7, 5_0);

@end


@interface AVPlayer (AVPlayerAdvancedRateControl)

/*!
	@method			setRate:time:atHostTime:
	@abstract		Simultaneously sets the playback rate and the relationship between the current item's current time and host time.
	@discussion		You can use this function to synchronize playback with an external activity.
	
					The current item's timebase is adjusted so that its time will be (or was) itemTime when host time is (or was) hostClockTime.
					In other words: if hostClockTime is in the past, the timebase's time will be interpolated as though the timebase has been running at the requested rate since that time.  If hostClockTime is in the future, the timebase will immediately start running at the requested rate from an earlier time so that it will reach the requested itemTime at the requested hostClockTime.  (Note that the item's time will not jump backwards, but instead will sit at itemTime until the timebase reaches that time.)
	@param itemTime	The time to start playback from, specified precisely (i.e., with zero tolerance).
					Pass kCMTimeInvalid to use the current item's current time.
	@param hostClockTime
					The host time at which to start playback.
					If hostClockTime is specified, the player will not ensure that media data is loaded before the timebase starts moving.
					If hostClockTime is kCMTimeInvalid, the rate and time will be set together, but without external synchronization;
					a host time in the near future will be used, allowing some time for data media loading.
*/
- (void)setRate:(float)rate time:(CMTime)itemTime atHostTime:(CMTime)hostClockTime NS_AVAILABLE(10_8, TBD);

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
- (void)prerollAtRate:(float)rate completionHandler:(void (^)(BOOL finished))completionHandler NS_AVAILABLE(10_8, TBD);

/*!
	@method			cancelPendingPrerolls
	@abstract		Cancel any pending preroll requests and invoke the corresponding completion handlers if present.
	@discussion		Use this method to cancel and release the completion handlers for pending prerolls. The finished parameter of the completion handlers will be set to NO.
*/
- (void)cancelPendingPrerolls NS_AVAILABLE(10_8, TBD);

/* NULL by default.  if not NULL, overrides the automatic choice of master clock for item timebases. This is most useful for synchronizing video-only movies with audio played via other means. IMPORTANT: If you specify a master clock other than the appropriate audio device clock, audio may drift out of sync. */
@property (nonatomic, retain) __attribute__((NSObject)) CMClockRef masterClock NS_AVAILABLE(10_8, NA);

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
					Releasing the observer object without a call to -removeTimeObserver will result in undefined behavior.
*/
- (id)addPeriodicTimeObserverForInterval:(CMTime)interval queue:(dispatch_queue_t)queue usingBlock:(void (^)(CMTime time))block;

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
					Releasing the observer object without a call to -removeTimeObserver will result in undefined behavior.
*/
- (id)addBoundaryTimeObserverForTimes:(NSArray *)times queue:(dispatch_queue_t)queue usingBlock:(void (^)(void))block;

/*!
	@method			removeTimeObserver:
	@abstract		Cancels a previously registered time observer.
	@param			observer
	  An object returned by a previous call to -addPeriodicTimeObserverForInterval:queue:usingBlock: or -addBoundaryTimeObserverForTimes:queue:usingBlock:.
	@discussion		Upon return, the caller is guaranteed that no new time observer blocks will begin executing.  Depending on the calling thread and the queue
					used to add the time observer, an in-flight block may continue to execute after this method returns.  You can guarantee synchronous time 
					observer removal by enqueuing the call to -removeTimeObserver on that queue.  Alternatively, call dispatch_sync(queue, ^{}) after 
					-removeTimeObserver to wait for any in-flight blocks to finish executing.
					-removeTimeObserver should be used to explicitly cancel each time observer added using -addPeriodicTimeObserverForInterval:queue:usingBlock:
					and -addBoundaryTimeObserverForTimes:queue:usingBlock:.
*/
- (void)removeTimeObserver:(id)observer;

@end


@interface AVPlayer (AVPlayerMediaControl)

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/* indicates the current audio volume of the player; 0.0 means "silence all audio", 1.0 means "play at the full volume of the current item" */
@property (nonatomic) float volume NS_AVAILABLE(10_7, NA);

/* indicates whether or not audio output of the player is muted */
@property (nonatomic, getter=isMuted) BOOL muted NS_AVAILABLE(10_7, NA);

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/* indicates whether display of closed captions is enabled */
@property (nonatomic, getter=isClosedCaptionDisplayEnabled) BOOL closedCaptionDisplayEnabled;

@end


#if TARGET_OS_IPHONE

@interface AVPlayer (AVPlayerAirPlaySupport)

/* Indicates whether the player allows AirPlay video playback. The default value is YES. */
@property (nonatomic) BOOL allowsAirPlayVideo NS_AVAILABLE_IOS(5_0);

/* Indicates whether the player is currently playing video via AirPlay. */
@property (nonatomic, readonly, getter=isAirPlayVideoActive) BOOL airPlayVideoActive NS_AVAILABLE_IOS(5_0);

/* Indicates whether the player should automatically switch to AirPlay Video while AirPlay Screen is active in order to play video content, switching back to AirPlay Screen as soon as playback is done. 
   The default value is NO. Has no effect if allowsAirPlayVideo is NO. */
@property (nonatomic) BOOL usesAirPlayVideoWhileAirPlayScreenIsActive NS_AVAILABLE_IOS(5_0);

@end

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
@property (nonatomic, readonly) BOOL outputObscuredDueToInsufficientExternalProtection NS_AVAILABLE_IOS(TBD);

@end

#endif // TARGET_OS_IPHONE


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

NS_CLASS_AVAILABLE(10_7, 4_1)
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
+ (id)queuePlayerWithItems:(NSArray *)items;

/*!
    @method     initWithItems:
    @abstract   Initializes an instance of AVQueuePlayer by enqueueing the AVPlayerItems from the specified array.
    @param      items
      An NSArray of AVPlayerItems with which to populate the player's queue initially.
    @result
      An instance of AVQueuePlayer.
*/
- (id)initWithItems:(NSArray *)items;

/*!
    @method     items
    @abstract   Provides an array of the currently enqueued items.
    @result     An NSArray containing the enqueued AVPlayerItems.
*/
- (NSArray *)items;

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
- (BOOL)canInsertItem:(AVPlayerItem *)item afterItem:(AVPlayerItem *)afterItem;

/*!
    @method     insertItem:afterItem:
    @abstract   Places an AVPlayerItem after the specified item in the queue.
    @param      item
      The item to be inserted.
    @param      afterItem
      The item that the newly inserted item should follow in the queue. Pass nil to append the item to the queue.
*/
- (void)insertItem:(AVPlayerItem *)item afterItem:(AVPlayerItem *)afterItem;

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
