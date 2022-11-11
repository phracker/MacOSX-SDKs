#if !__has_include(<AVFCore/AVSampleBufferRenderSynchronizer.h>)
/*
	File:  AVSampleBufferRenderSynchronizer.h

	Framework:  AVFoundation
 
	Copyright 2013-2021 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMSync.h>

@protocol AVQueuedSampleBufferRendering;
@class AVSampleBufferRenderSynchronizerInternal;

NS_ASSUME_NONNULL_BEGIN

/*!
  @class		AVSampleBufferRenderSynchronizer
  @abstract		AVSampleBufferRenderSynchronizer can synchronize multiple objects conforming to AVQueuedSampleBufferRendering to a single timebase.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface AVSampleBufferRenderSynchronizer : NSObject
{
@private
	AVSampleBufferRenderSynchronizerInternal *_synchronizerInternal;
}

/*!
	@property		timebase
	@abstract		The synchronizer's rendering timebase, which governs how time stamps are interpreted.
	@discussion
		By default, this timebase will be driven by the clock of an added AVSampleBufferAudioRenderer.
	
		If no AVSampleBufferAudioRenderer has been added, the source clock will be the host time clock (mach_absolute_time with the appropriate timescale conversion; this is the same as Core Animation's CACurrentMediaTime).
					
		The timebase is a read-only timebase.  Use the rate property and corresponding methods to adjust the timebase.
*/
@property (retain, readonly) __attribute__((NSObject)) CMTimebaseRef timebase;

/*!
	@property		rate
	@abstract		Playback rate.
	@discussion
		Indicates the current rate of rendering.  A value of 0.0 means "stopped"; a value of 1.0 means "play at the natural rate of the media".  Must be greater than or equal to 0.0.
*/
@property (nonatomic, readwrite) float rate;

/*!
	@constant		AVSampleBufferRenderSynchronizerRateDidChangeNotification
	@abstract		A notification that fires whenever the value of the "rate" property changes.
	@discussion
		The rate can change as a result of setting the rate property, either by directly setting the property or calling -setRate:time:.  The rate can also change at any time, without any action by the client of the render synchronizer.  For example, on iOS if the app's playback is interrupted (e.g. by a phone call or another non-mixable app starting playback), the rate will automatically be set to zero.  This notification will be sent in all of those cases.
 */
AVF_EXPORT NSNotificationName const AVSampleBufferRenderSynchronizerRateDidChangeNotification API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

/*!
	@method			currentTime
	@abstract		Returns the current time of the synchronizer.
	@result			A CMTime
	@discussion		Returns the current time of the synchronizer. Not key-value observable; use -addPeriodicTimeObserverForInterval:queue:usingBlock: instead.
*/
- (CMTime)currentTime API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

/*!
	@method			setRate:time:
	@abstract		Sets the timebase's time and rate.
	@param			rate
		A new timebase rate to set.  Must be greater than or equal to 0.0
	@param			time
		A new time to set.  Must be greater than or equal to kCMTimeZero, or kCMTimeInvalid
	@discussion
		Sets the timebase's time to time and then sets the rendering rate to rate.  A rate value of 0.0 means "stopped"; a rate value of 1.0 means "play at the natural rate of the media".  Use kCMTimeInvalid for time to not modify the timebase's time.
*/
- (void)setRate:(float)rate time:(CMTime)time;

/*!
	@method			setRate:time:atHostTime:
	@abstract		Simultaneously sets the playback rate and the relationship between the current time and host time.
	@param			rate
		A new timebase rate to set.  Must be greater than or equal to 0.0
	@param			time
		A new timebase time to set.  Must be greater than or equal to kCMTimeZero, or kCMTimeInvalid
	@param			hostTime
		A new hostTime to set.  Must be greater than or equal to kCMTimeZero, or kCMTimeInvalid
	@discussion
		You can use this function to synchronize playback with an external activity.
 
		The timebase is adjusted so that its time will be (or was) time when host time is (or was) hostTime.
		In other words: if hostTime is in the past, the timebase's time will be interpolated as though the timebase has been running at the requested rate since that time.  If hostTime is in the future, the timebase will immediately start running at the requested rate from an earlier time so that it will reach the requested time at the requested hostTime.
		It is a responsibility of the client to ensure that proper time and hostTime is set.  This method will not attempt to validate improper time, hostTime values.
		In addition, it is also the caller’s responsibility to enqueue samples in the connected renderers that match the timeline defined here.
		Note that any buffers that are in the past of the defined timeline will still be processed by the renderers.

		The recommended approach is to use the output presentation time of the first buffer enqueued in the renderers as time and and an associated hostTime in the future.
		Example use:
		CMTime startTime = …;
		__block CMTime nextBufferTime = startTime;
		[renderer requestMediaDataWhenReadyOnQueue:queue usingBlock:^{
			…
			CMSampleBufferRef sampleBuffer = [self generateSampleBufferFor: nextBufferTime];
			[renderer enqueueSampleBuffer:sampleBuffer];
			...
		}];
		CMTime inOneSecond = CMTimeAdd(CMClockGetTime(CMClockGetHostTimeClock()), CMTimeMake(1, 1));
		[synchronizer setRate:rate time:startTime atHostTime:inOneSecond];
*/
- (void)setRate:(float)rate time:(CMTime)time atHostTime:(CMTime)hostTime API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5), watchos(7.4));

/*!
    @property	delaysRateChangeUntilHasSufficientMediaData
    @abstract	Indicates whether the playback should be started immediately on rate change request.
    @discussion	If set to YES, playback will be delayed if the value of hasSufficientMediaDataForReliablePlaybackStart of any added renderer is NO. If set to NO, playback will attempt to start immediately regardless of the value of hasSufficientMediaDataForReliablePlaybackStart of added renderers. Default is YES.
 */
@property (nonatomic) BOOL delaysRateChangeUntilHasSufficientMediaData API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5), watchos(7.4));

@end

@interface AVSampleBufferRenderSynchronizer (AVSampleBufferRenderSynchronizerRendererManagement)

/*!
	@property		renderers
	@abstract		Array of id<AVQueuedSampleBufferRendering> currently attached to the synchronizer.
	@discussion
		A list of renderers added to and not removed from the synchronizer.  The list also includes renderers that have been scheduled to be removed but have not yet been removed.
	
		This property is not KVO observable.
*/
@property (atomic, readonly) NSArray<__kindof id <AVQueuedSampleBufferRendering>> *renderers;

/*!
	@method			addRenderer:
	@abstract		Adds a renderer to the list of renderers under the synchronizer's control.
	@param			renderer
		An object conforming to AVQueuedSampleBufferRendering to be synchronized by this synchronizer.
	@discussion
		Adds a renderer to begin operating with the synchronizer's timebase.

		This method can be called while rate is non-0.0.
*/
- (void)addRenderer:(id <AVQueuedSampleBufferRendering>)renderer;

/*!
	@method			removeRenderer:atTime:completionHandler:
	@abstract		Removes a renderer from the list of renderers under the synchronizer's control.
	@param			renderer
		An object conforming to AVQueuedSampleBufferRendering currently synchronized by this synchronizer to no longer be synchronized by the synchronizer.
	@param			time
		The time on the timebase's timeline at which the renderer should be removed.
	@param			completionHandler
		Optional.  A block called when the renderer is removed from the synchronizer.  If provided, this block will always be called with didRemoveRenderer indicating whether the renderer was removed by this scheduled removal.
	@discussion
		This method can be called while rate is non-0.0.

		time is used to schedule future removals.  If the time is in the past, the renderer will be removed immediately.  kCMTimeInvalid can also be used to force immediate removal.
	
		This method removes the renderer asynchronously.  The method can be called more than once, with a subsequent scheduled removal replacing a previously scheduled removal.
					
		Clients may provide an optional completionHandler block to be notified when the scheduled removal completes.  If provided, completionHandler will always be called with the following values for didRemoveRenderer:
			
			- If the renderer has not been added to this synchronizer, completionHandler will be called and didRemoveRenderer will be NO.
			- If a removal of a particular renderer is scheduled after another removal of that same renderer has already been scheduled but not yet occurred, the previously-scheduled removal's completionHandler will be called and didRemoveRenderer will be NO.  The new scheduled removal's completionHandler will not be called until it is replaced by another scheduled removal or the renderer is actually removed.
			- When the renderer is removed due to a scheduled removal, the completionHandler provided when that removal was scheduled will be called and didRemoveRenderer will be YES.
*/
- (void)removeRenderer:(id <AVQueuedSampleBufferRendering>)renderer atTime:(CMTime)time completionHandler:(nullable void (^)(BOOL didRemoveRenderer))completionHandler;

@end

@interface AVSampleBufferRenderSynchronizer (AVSampleBufferRenderSynchronizerTimeObservation)

/*!
	@method			addPeriodicTimeObserverForInterval:queue:usingBlock:
	@abstract		Requests invocation of a block during rendering to report changing time.
	@param			interval
		The interval of invocation of the block during normal rendering, according to progress of the current time of the timebase.
	@param			queue
		The serial queue onto which block should be enqueued.  If you pass NULL, the main queue (obtained using dispatch_get_main_queue()) will be used.  Passing a concurrent queue to this method will result in undefined behavior.
	@param			block
		The block to be invoked periodically.
	@result
		An object conforming to the NSObject protocol.  You must retain this returned value as long as you want the time observer to be invoked by the synchronizer.  Pass this object to -removeTimeObserver: to cancel time observation.
	@discussion
		The block is invoked periodically at the interval specified, interpreted according to the timeline of the timebase.  The block is also invoked whenever time jumps and whenever rendering starts or stops.
 
		If the interval corresponds to a very short interval in real time, the synchronizer may invoke the block less frequently than requested. Even so, the synchronizer will invoke the block sufficiently often for the client to update indications of the current time appropriately in its end-user interface.
 
		Each call to -addPeriodicTimeObserverForInterval:queue:usingBlock: should be paired with a corresponding call to -removeTimeObserver:.  Releasing the observer object without a call to -removeTimeObserver: will result in undefined behavior.
*/
- (id)addPeriodicTimeObserverForInterval:(CMTime)interval queue:(nullable dispatch_queue_t)queue usingBlock:(void (^)(CMTime time))block;

/*!
	@method			addBoundaryTimeObserverForTimes:queue:usingBlock:
	@abstract		Requests invocation of a block when specified times are traversed during normal rendering.
	@param			times
		The times for which the observer requests notification, supplied as an array of NSValues carrying CMTimes.
	@param			queue
		The serial queue onto which block should be enqueued.  If you pass NULL, the main queue (obtained using dispatch_get_main_queue()) will be used.  Passing a
	  concurrent queue to this method will result in undefined behavior.
	@param			block
		The block to be invoked when any of the specified times is crossed during normal rendering.
	@result
		An object conforming to the NSObject protocol.  You must retain this returned value as long as you want the time observer to be invoked by the synchronizer.  Pass this object to -removeTimeObserver: to cancel time observation.
	@discussion
		Each call to -addPeriodicTimeObserverForInterval:queue:usingBlock: should be paired with a corresponding call to -removeTimeObserver:.  Releasing the observer object without a call to -removeTimeObserver: will result in undefined behavior.
*/
- (id)addBoundaryTimeObserverForTimes:(NSArray<NSValue *> *)times queue:(nullable dispatch_queue_t)queue usingBlock:(void (^)(void))block;

/*!
	@method			removeTimeObserver:
	@abstract		Cancels a previously registered time observer.
	@param			observer
		An object returned by a previous call to -addPeriodicTimeObserverForInterval:queue:usingBlock: or -addBoundaryTimeObserverForTimes:queue:usingBlock:.
	@discussion
		Upon return, the caller is guaranteed that no new time observer blocks will begin executing.  Depending on the calling thread and the queue used to add the time observer, an in-flight block may continue to execute after this method returns.  You can guarantee synchronous time observer removal by enqueuing the call to -removeTimeObserver: on that queue.  Alternatively, call dispatch_sync(queue, ^{}) after -removeTimeObserver: to wait for any in-flight blocks to finish executing.  -removeTimeObserver: should be used to explicitly cancel each time observer added using -addPeriodicTimeObserverForInterval:queue:usingBlock: and -addBoundaryTimeObserverForTimes:queue:usingBlock:.
*/
- (void)removeTimeObserver:(id)observer;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVSampleBufferRenderSynchronizer.h>
#endif
