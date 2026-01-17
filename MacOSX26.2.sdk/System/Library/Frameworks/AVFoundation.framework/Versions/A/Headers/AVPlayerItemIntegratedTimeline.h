#if !__has_include(<AVFCore/AVPlayerItemIntegratedTimeline.h>)
/*
	File:  AVPlayerItemIntegratedTimeline.h

	Framework:  AVFoundation
 
   Copyright:  2023 by Apple Inc., all rights reserved.

*/

#import <Foundation/Foundation.h>
#import <AVFoundation/AVPlayer.h>
#import <AVFoundation/AVPlayerItem.h>
#import <AVFoundation/AVPlayerInterstitialEventController.h>

NS_ASSUME_NONNULL_BEGIN

/*!
@enum		AVPlayerItemSegmentType
@abstract	These constants specify the type of segment

@constant	AVPlayerItemSegmentTypePrimary
			Indicates segment represent playback of a primary item.
@constant	AVPlayerItemSegmentTypeInterstitial
			Indicates segment represents playback of an interstitial event.
*/
typedef NS_ENUM(NSInteger, AVPlayerItemSegmentType) {
AVPlayerItemSegmentTypePrimary = 0,
AVPlayerItemSegmentTypeInterstitial = 1
} NS_SWIFT_NAME(AVPlayerItemSegment.SegmentType) API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/*!
@class			AVPlayerItemSegment

@abstract 		Representing a segment of time on the integrated timeline. Segments are immutable objects.
@discussion		Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0))
@interface AVPlayerItemSegment : NSObject
 
AV_INIT_UNAVAILABLE

/*!
@property		segmentType
@abstract		The type of content this segment represents.
*/
@property (nonatomic, readonly) AVPlayerItemSegmentType segmentType;

/*!
@property		timeMapping
@abstract		The timeMapping for this segment.
@discussion
	The timeMapping source timeRange represents the start and duration in the segment source's timeline (ie: primary item timeline or interstitial event). The target timeRange represents the start point and duration in the integrated timeline. For interstitial events which occupy a single point, the target's duration will be kCMTimeZero.
*/
@property (nonatomic, readonly) CMTimeMapping timeMapping;

/*!
@property	loadedTimeRanges
@abstract	This property provides a collection of time ranges for the segment if media data is readily available. The ranges provided might be discontinuous.
@discussion
	Returns an NSArray of NSValues containing CMTimeRanges. Loaded time ranges will be within the timeMapping's target timeRange. Loaded time ranges will be empty for interstitial events that occupy a single point in time.
*/
@property (readonly) NSArray<NSValue *> *loadedTimeRanges NS_REFINED_FOR_SWIFT;

/*!
@property		startDate
@abstract		The date this segment starts at.
@discussion
	The date this segment starts at. This value will be nil if the primary item does not contain dates.
*/
@property (nonatomic, readonly, nullable) NSDate *startDate;

/*!
@property		interstitialEvent
@abstract		The associated interstitial event for this segment.
@discussion
	The associated interstitial event for this segment. This value will be nil for segments representing playback of the primary itme.
*/
@property (nonatomic, readonly, nullable) AVPlayerInterstitialEvent* interstitialEvent;

@end

/*!
@class			AVPlayerItemIntegratedTimelineSnapshot
@abstract		AVPlayerItemIntegratedTimelineSnapshot provides an immutable representation of inspectable details from an AVPlayerItemIntegratedTimeline.
@discussion
	An instance of AVPlayerItemIntegratedTimelineSnapshot is an immutable snapshot representation of inspectable details from an AVPlayerItemIntegratedTimeline. As playback progresses,
AVPlayerItemIntegratedTimelineSnapshot will not reflect the new timeline state. One can request a new snapshot instance from an AVPlayerItemIntegratedTimeline to reflect the latest timeline state.
	Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.

*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0))
@interface AVPlayerItemIntegratedTimelineSnapshot : NSObject

AV_INIT_UNAVAILABLE

/*!
@property	duration
@abstract	Returns the duration totaling the primary item and scheduled interstitial events.
@discussion
	This property returns the duration totaling the primary item and scheduled interstitial events and taking into account the interstitial event's playoutLimit and resumption offset.
	Before loading the duration of the primary item, the value of this property is kCMTimeInvalid. For livestreams, this value will be kCMTimeIndefinite.
*/
@property (nonatomic, readonly) CMTime duration;

/*!
@property	currentSegment
@abstract	Returns the current AVPlayerItemSegment playback is traversing.
*/
@property (readonly, nullable) AVPlayerItemSegment *currentSegment;

/*!
@property	segments
@abstract	Returns an array of AVPlayerItemSegment for the snapshot.
@discussion
	Returns an array of AVPlayerItemSegment. The segments are presented in chronological order, contiguous from the previous element, and non-overlapping.
*/
@property (readonly) NSArray<AVPlayerItemSegment *>*segments;

/*!
@property	currentTime
@abstract	Returns the current time on the integrated timeline when the snapshot was taken.
@discussion
	Returns the current time on the integrated timeline when the snapshot was taken. CurrentTime will not change as playback progresses.
*/
@property (readonly) CMTime currentTime;

/*!
@property	currentDate
@abstract	Returns the  current date when the snapshot was taken, or nil if playback is not mapped to any date.
*/
@property (readonly, nullable) NSDate *currentDate;

/*!
@method 	mapTime
@abstract	Provides mapping from time to AVPlayerItemSegment and offset in segment.
@param		time
			Time represented in the integrated time domain.
@param		timeSegmentOut
			Output parameter for segment.
@param		segmentOffsetOut
			Output parameter for offset in segment.
@discussion
	Provides mapping from time to segment and offset in the segment's timeMapping target. For time that correlates to the start of multiple segments, this will return the first one.
*/
- (void)mapTime:(CMTime)time toSegment:(AVPlayerItemSegment * CM_NONNULL * CM_NULLABLE)timeSegmentOut atSegmentOffset:(CMTime*)segmentOffsetOut NS_REFINED_FOR_SWIFT;

@end

/*!
@class		AVPlayerItemIntegratedTimeline

@abstract
	An AVPlayerItemIntegratedTimeline provides detailed timing information and control for the sequence of playback of a primary AVPlayerItem and scheduled AVPlayerInterstitialEvents.

@discussion
	An object that models the timeline and sequence of playback of primary AVPlayerItem and scheduled AVPlayerInterstitialEvents. The timeline models all regions expected to be traversed during playback. Notably portions of the primary item may not be presented when exiting an interstitial event with a positive resumption offset.
	Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0))
@interface AVPlayerItemIntegratedTimeline : NSObject

AV_INIT_UNAVAILABLE

/*!
@property	currentSnapshot
@abstract	This property provides an immutable representation of the timeline state at time of request.
@discussion
	Returns an immutable representation of the timeline state at time of request. A timeline snapshot provides accessors for obtaining inspectable details of the timeline.  Because a snapshot is immutable, the snapshot's properties will not update as playback continues.
*/
@property (readonly) AVPlayerItemIntegratedTimelineSnapshot *currentSnapshot;

/*!
@property	currentTime
@abstract	Returns the current time on the integrated timeline.
@discussion
	Returns the current time on the integrated timeline. During playback of interstitial events that occupy a single point, currentTime will not change.
*/
@property (readonly) CMTime currentTime;

/*!
@property	currentDate
@abstract	Returns the date of current playback, or nil if playback is not mapped to any date.
*/
@property (readonly, nullable) NSDate *currentDate;

@end

API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0))
@interface AVPlayerItemIntegratedTimeline(AVPlayerItemIntegratedTimelineControl)

/*!
@method       seekToTime
@abstract     Seeks to a particular time in the integrated time domain and invokes the completionHandler
@param        time
			  Time represented in the integrated time domain.
@param        toleranceBefore
			  Tolerance before target time allowed to seek to.
@param        toleranceAfter
			  Tolerance after target time allowed to seek to.
@param        completionHandler
			  CompletionHandler callback after seek completes. Success will be true if the playhead moved to the new time.
@discussion
The integrated timeline seeks to the the range of [time-beforeTolerance, time+afterTolerance] will be attributed to a segment and AVPlayerItem that falls in that range. You can request sample accurate seeking by passing a time value of kCMTimeZero for both toleranceBefore and toleranceAfter.
*/
- (void)seekToTime:(CMTime)time toleranceBefore:(CMTime)toleranceBefore toleranceAfter:(CMTime)toleranceAfter completionHandler:(void (^ NS_SWIFT_SENDABLE _Nullable)(BOOL success))completionHandler;

/*!
@method		seekToDate
@abstract	Seeks playhead to corresponding date and invokes the completionHandler.
@param		date
			The new position for the playhead.
@param		completionHandler
			CompletionHandler callback after seek completes. Success will be true if the playhead moved to the new date.
@discussion
	The integrated timeline will seek playhead to the coresponding date.
*/
- (void)seekToDate:(NSDate *)date completionHandler:(void (^ NS_SWIFT_SENDABLE _Nullable)(BOOL success))completionHandler;

@end

/*!
	@protocol       AVPlayerItemIntegratedTimelineObserver
	@abstract       Defines protocol for objects returned from timeline observer routines.
*/
@protocol AVPlayerItemIntegratedTimelineObserver <NSObject>

@end

API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0))
@interface AVPlayerItemIntegratedTimeline(AVPlayerItemIntegratedTimelineObserver)

/*!
@method     addPeriodicTimeObserverForInterval
@abstract   Requests invocation of a block during playback to report changing time.
@param      interval
			The interval of invocation of the block during normal playback, according to progress of the current time in the integrated timeline.
@param      queue
			The serial queue onto which block should be enqueued. If you pass NULL, the main queue (obtained using dispatch_get_main_queue()) will be used. Passing a concurrent queue to this method will result in undefined behavior.
@param      block
			The block to be invoked periodically.
@result
	An object conforming to the AVPlayerItemIntegratedTimelineObserver protocol. You must retain this returned value as long as you want the time observer to be invoked by the timeline. The block is invoked periodically at the interval specified, interpreted according to the integrated timeline. The block is also invoked across AVPlayerItemSegment and AVPlayerItem boundaries, whenever time jumps, and whenever playback starts or stops. Each call to -addPeriodicTimeObserverForInterval:queue:usingBlock: should be paired with a corresponding call to -removeTimeObserver:. Releasing the observer object without a call to -removeTimeObserver: will result in undefined behavior
*/
- (id<AVPlayerItemIntegratedTimelineObserver>)addPeriodicTimeObserverForInterval:(CMTime)interval queue:(nullable dispatch_queue_t)queue usingBlock:(void (^ NS_SWIFT_SENDABLE)(CMTime time))block NS_REFINED_FOR_SWIFT;

/*!
@method     addBoundaryTimeObserverForSegment
@abstract   Requests invocation of a block when an offset in a segment is traversed during playback.
@param      segment
			AVPlayerItemSegment to monitor playback traversal of.
@param      offsetsIntoSegment
			Offsets in the segment for which the observer requests notification, supplied as an array of NSValues carrying CMTimes.
@param      queue
			The serial queue onto which block should be enqueued. If you pass NULL, the main queue (obtained using dispatch_get_main_queue()) will be used. Passing a concurrent queue to this method will result in undefined behavior.
@param      block
			The block to be invoked when the offset is crossed during playback of a segment.
@result
	An object conforming to the AVPlayerItemIntegratedTimelineObserver protocol. You must retain this returned value as long as you want the time observer to be invoked by the timeline. Pass this object to -removeTimeObserver: to cancel time observation. One can also configure single point segments with segmentTimes to trigger during traversal of the segment's playback. As the timeline duration and segments change, the installed time observer will be automatically adjusted to fire at the desired offset in the segment. A segment that is removed from the timeline will trigger the invocation of the block immediately with success set as false.
 Each call to -addBoundaryTimeObserverForSegment:segment:offsetsInSegment:queue:usingBlock: should be paired with a corresponding call to -removeTimeObserver:. Releasing the observer object without a call to -removeTimeObserver: will result in undefined behavior
*/
- (id<AVPlayerItemIntegratedTimelineObserver>)addBoundaryTimeObserverForSegment:(AVPlayerItemSegment *)segment offsetsIntoSegment:(NSArray *)offsetsIntoSegment queue:(nullable dispatch_queue_t)queue usingBlock:(void (^ NS_SWIFT_SENDABLE)(BOOL success))block NS_REFINED_FOR_SWIFT;

/*!
@method     removeTimeObserver:
@abstract   Cancels a previously registered time observer.
@param      observer
			An object returned by a previous call to -addPeriodicTimeObserverForInterval or -addBoundaryTimeObserverForSegment.
*/
- (void)removeTimeObserver:(id<AVPlayerItemIntegratedTimelineObserver>)observer NS_REFINED_FOR_SWIFT;

@end

/**
 @constant	AVPlayerIntegratedTimelineSnapshotsOutOfSyncNotification
 @abstract	A notification which is posted when the snapshot objects provided by this timeline would be out of sync with the current timeline state. See keys below.
*/
AVF_EXPORT NSNotificationName const AVPlayerIntegratedTimelineSnapshotsOutOfSyncNotification
	API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/**
 @constant AVPlayerIntegratedTimelineSnapshotsOutOfSyncReasonKey
 @abstract Indicates the reason for the snapshot out of sync notification.
 */
AVF_EXPORT NSString *const AVPlayerIntegratedTimelineSnapshotsOutOfSyncReasonKey API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

typedef NSString * AVPlayerIntegratedTimelineSnapshotsOutOfSyncReason NS_STRING_ENUM;
AVF_EXPORT AVPlayerIntegratedTimelineSnapshotsOutOfSyncReason const AVPlayerIntegratedTimelineSnapshotsOutOfSyncReasonSegmentsChanged API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));
AVF_EXPORT AVPlayerIntegratedTimelineSnapshotsOutOfSyncReason const AVPlayerIntegratedTimelineSnapshotsOutOfSyncReasonCurrentSegmentChanged API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));
AVF_EXPORT AVPlayerIntegratedTimelineSnapshotsOutOfSyncReason const AVPlayerIntegratedTimelineSnapshotsOutOfSyncReasonLoadedTimeRangesChanged API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

@interface AVPlayerItem (AVPlayerItemIntegratedTimelineSupport)

/*!
@property		integratedTimeline
@abstract		Obtain an instance of AVPlayerItemIntegratedTimeline representing the timing and control of playback of the item with its scheduled AVPlayerInterstitialEvents. This value will return nil for AVPlayerItems in an interstitial player.
*/
@property (readonly) AVPlayerItemIntegratedTimeline *integratedTimeline NS_SWIFT_NONISOLATED API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVPlayerItemIntegratedTimeline.h>
#endif
