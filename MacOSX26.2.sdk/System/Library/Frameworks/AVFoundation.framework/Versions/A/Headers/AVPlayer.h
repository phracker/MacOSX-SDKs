#if !__has_include(<AVFCore/AVPlayer.h>)
/*
    File:  AVPlayer.h

	Framework:  AVFoundation
 
	Copyright 2010-2024 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVAnimation.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>
#import <CoreMedia/CMSync.h>
#import <Foundation/Foundation.h>
#if TARGET_OS_IOS || TARGET_OS_TV
#import <AVRouting/AVRoutingPlaybackArbiter.h>
#endif

@class AVPlayerItem;
@class AVPlayerInternal;
@class AVPlayerPlaybackCoordinator;
@class AVPlayerVideoOutput;
@class CASpatialAudioExperience;

NS_ASSUME_NONNULL_BEGIN

/// These constants are returned by the AVPlayer status property to indicate whether it can successfully play items.
typedef NS_ENUM(NSInteger, AVPlayerStatus) {
	/// Indicates that the status of the player is not yet known because it has not tried to load new media resources for playback.
	AVPlayerStatusUnknown = 0,
	/// Indicates that the player is ready to play AVPlayerItem instances.
	AVPlayerStatusReadyToPlay = 1,
	/// Indicates that the player can no longer play AVPlayerItem instances because of an error. The error is described by the value of the player's error property.
	AVPlayerStatusFailed = 2
};

/// AVPlayer offers a playback interface for single-item playback that's sufficient for the implementation of playback controllers and playback user interfaces.
/// 
/// AVPlayer works equally well with local and remote media files, providing clients with appropriate
/// information about readiness to play or about the need to await additional data before continuing.
/// 
/// Visual content of items played by an instance of AVPlayer can be displayed in a CoreAnimation layer
/// of class AVPlayerLayer.
/// 
/// To allow clients to add and remove their objects as key-value observers safely, AVPlayer serializes notifications of
/// changes that occur dynamically during playback on a dispatch queue. By default, this queue is the main queue. See dispatch_get_main_queue().
NS_SWIFT_UI_ACTOR
API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0))
@interface AVPlayer : NSObject
{
@private
	AVPlayerInternal     *_player;
}

/// Initializes an AVPlayer with no player items.
- (instancetype)init NS_SWIFT_NONISOLATED;

/// Returns an instance of AVPlayer that plays a single audiovisual resource referenced by URL.
/// 
/// Implicitly creates an AVPlayerItem. Clients can obtain the AVPlayerItem as it becomes the player's currentItem.
/// 
/// - Parameter URL:
/// 
/// - Returns: An instance of AVPlayer
+ (instancetype)playerWithURL:(NSURL *)URL NS_SWIFT_NONISOLATED;

/// Create an AVPlayer that plays a single audiovisual item.
/// 
/// Useful in order to play items for which an AVAsset has previously been created. See -[AVPlayerItem initWithAsset:].
/// 
/// - Parameter item:
/// 
/// - Returns: An instance of AVPlayer
+ (instancetype)playerWithPlayerItem:(nullable AVPlayerItem *)item NS_SWIFT_NONISOLATED;

/// Initializes an AVPlayer that plays a single audiovisual resource referenced by URL.
/// 
/// Implicitly creates an AVPlayerItem. Clients can obtain the AVPlayerItem as it becomes the player's currentItem.
/// 
/// - Parameter URL:
/// 
/// - Returns: An instance of AVPlayer
- (instancetype)initWithURL:(NSURL *)URL NS_SWIFT_NONISOLATED;

/// Create an AVPlayer that plays a single audiovisual item.
/// 
/// Useful in order to play items for which an AVAsset has previously been created. See -[AVPlayerItem initWithAsset:].
/// This method throws an exception if the item is not an AVPlayerItem, or if the item is
/// associated with another AVPlayer.
/// 
/// - Parameter item:
/// 
/// - Returns: An instance of AVPlayer
- (instancetype)initWithPlayerItem:(nullable AVPlayerItem *)item NS_SWIFT_NONISOLATED;

/// The ability of the receiver to be used for playback.
/// 
/// The value of this property is an AVPlayerStatus that indicates whether the receiver can be used for playback. When
/// the value of this property is AVPlayerStatusFailed, the receiver can no longer be used for playback and a new
/// instance needs to be created in its place. When this happens, clients can check the value of the error property to
/// determine the nature of the failure. This property is key value observable.
@property (readonly) AVPlayerStatus status NS_SWIFT_NONISOLATED;

/// If the receiver's status is AVPlayerStatusFailed, this describes the error that caused the failure.
/// 
/// The value of this property is an NSError that describes what caused the receiver to no longer be able to play items.
/// If the receiver's status is not AVPlayerStatusFailed, the value of this property is nil.
@property (readonly, nullable) NSError *error NS_SWIFT_NONISOLATED;

@end

/// Indicates a player rate change.
/// 
/// Posted by the player when its rate changes. Similar to KVO of AVPlayer.rate, but providing additional information about the rate change in the userInfo. See keys below.
AVF_EXPORT NSNotificationName const AVPlayerRateDidChangeNotification API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/// Indicates a reason for the rate change notification.
/// 
/// The value corresponding to this key is of type AVPlayerRateDidChangeReason.
AVF_EXPORT NSString *const AVPlayerRateDidChangeReasonKey API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Indicates a rate change was caused by another participant connected through AVPlayerPlaybackCoordinator.
/// 
/// Informs the receiver of an AVPlayerRateDidChangeNotification about a rate change originated from another AVCoordinatedPlaybackParticipant connected through AVPlayerPlaybackCoordinator. This can be used to inform UI showing why the playback rate changed. The type of the value for this key is an AVCoordinatedPlaybackParticipant, which is part of the AVPlayerPlaybackCoordinator.otherParticipants array.
AVF_EXPORT NSString *const AVPlayerRateDidChangeOriginatingParticipantKey API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

typedef NSString * AVPlayerRateDidChangeReason NS_STRING_ENUM;
AVF_EXPORT AVPlayerRateDidChangeReason const AVPlayerRateDidChangeReasonSetRateCalled API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT AVPlayerRateDidChangeReason const AVPlayerRateDidChangeReasonSetRateFailed API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT AVPlayerRateDidChangeReason const AVPlayerRateDidChangeReasonAudioSessionInterrupted API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT AVPlayerRateDidChangeReason const AVPlayerRateDidChangeReasonAppBackgrounded API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

@interface AVPlayer (AVPlayerPlaybackControl)

/// Indicates the desired rate of playback; 0.0 means "paused", 1.0 indicates a desire to play at the natural rate of the current item.
/// 
/// Setting the value of rate to 0.0 pauses playback, causing the value of timeControlStatus to change to AVPlayerTimeControlStatusPaused.
/// Setting the rate to a non-zero value causes the value of timeControlStatus to become either AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate or AVPlayerTimeControlStatusPlaying, depending on whether sufficient media data has been buffered for playback to occur and whether the player's default behavior of waiting in order to minimize stalling is permitted. See discussion of AVPlayerTimeControlStatus for more details.
/// 
/// AVPlayer can reset the desired rate to 0.0 when a change in overall state requires playback to be halted, such as when an interruption occurs on iOS, as announced by AVAudioSession, or when the playback buffer becomes empty and playback stalls while automaticallyWaitsToMinimizeStalling is NO.
/// 
/// The effective rate of playback may differ from the desired rate even while timeControlStatus is AVPlayerTimeControlStatusPlaying, if the processing algorithm in use for managing audio pitch requires quantization of playback rate. For information about quantization of rates for audio processing, see AVAudioProcessingSettings.h. You can always obtain the effective rate of playback from the currentItem's timebase; see the timebase property of AVPlayerItem.
/// 
/// Before macOS 13, iOS 16, tvOS 16, and watchOS 9, this property must be accessed on the main thread/queue.
@property float rate
#if AVF_DEPLOYING_TO_2022_RELEASES_AND_LATER
NS_SWIFT_NONISOLATED
#endif
;

/// Indicates the rate at which to start playback when play is called; defaults to 1.0.
/// 
/// Setting this property does not imply playback starts automatically at this rate. Clients still have to kick off playback using `play`. Note that using setRate to start playback will skip using the value in this property nor would it update this property. Therefore, `setRate:1.0` is no longer recommended as a means to start playback. Use `play` instead. Use `setRate` for operations like scanning where the rate is to be updated instantaneously. Invoking `play` again would restore playback at the rate set in this property.
/// 
/// The effective rate of playback may still differ from the default rate subject to restrictions imposed by the system. See documentation for the rate property for a discussion on when the desired rate does not translate to effective rate.
@property (nonatomic) float defaultRate NS_SWIFT_NONISOLATED API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/// Signals the desire to begin playback at the rate set in the defaultRate.
/// 
/// For releases up to iOS version 16.0, macOS versions 13.0, tvOS 16.0 and watchOS 9.0, this is equivalent to setting the value of rate to `1.0`. Starting from iOS version 16.0, macOS versions 13.0, tvOS 16.0 and watchOS 9.0, this will attempt to use the rate set in the `defaultRate` property. The effective rate of playback may differ from the `defaultRate` due to the reasons mentioned in the documentation of the `rate` property. Clients interested in knowing the effective rate can listen for `AVPlayerRateDidChangeNotification` notification.
/// 
/// Before macOS 13, iOS 16, tvOS 16, and watchOS 9, this method must be invoked on the main thread/queue.
- (void)play
#if AVF_DEPLOYING_TO_2022_RELEASES_AND_LATER
NS_SWIFT_NONISOLATED
#endif
;

/// Pauses playback.
/// 
/// Equivalent to setting the value of rate to 0.0.
/// 
/// Before macOS 13, iOS 16, tvOS 16, and watchOS 9, this method must be invoked on the main thread/queue.
- (void)pause
#if AVF_DEPLOYING_TO_2022_RELEASES_AND_LATER
NS_SWIFT_NONISOLATED
#endif
;

/// These constants are the allowable values of AVPlayer's timeControlStatus property. This discussion pertains when automaticallyWaitsToMinimizeStalling is YES, the default setting, and exceptions are discussed in connection with automaticallyWaitsToMinimizeStalling.
typedef NS_ENUM(NSInteger, AVPlayerTimeControlStatus) {
	/// This state is entered upon receipt of a -pause message, an invocation of -setRate: with a value of 0.0, when a change in overall state requires playback to be halted, such as when an interruption occurs on iOS, as announced by AVAudioSession. In this state, playback is paused indefinitely and will not resume until 1) a subsequent -play message is received or 2) a -setRate: or -playImmediatelyAtRate: message with a non-zero value for rate is received and sufficient media data has been buffered for playback to proceed.
	AVPlayerTimeControlStatusPaused = 0,
	/// This state is entered when 1) the playback buffer becomes empty and playback stalls in AVPlayerTimeControlStatusPlaying, 2) when rate is set from zero to non-zero in AVPlayerTimeControlStatusPaused and insufficient media data has been buffered for playback to occur, or 3) when the player has no item to play, i.e. when the receiver's currentItem is nil. In this state, the value of the rate property is not currently effective but instead indicates the rate at which playback will start or resume. Refer to the value of reasonForWaitingToPlay for details about why the receiver is waiting and the conditions that allow waitStatus to change to AVPlayerWaitStatusPlaying. While waiting for buffering, you can attempt to start playback of any available media data via -playImmediatelyAtRate:.
	AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate = 1,
	/// In this state, playback is currently progressing and rate changes will take effect immediately. Should playback stall because of insufficient media data, timeControlStatus will change to AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate.
	AVPlayerTimeControlStatusPlaying = 2
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0), visionos(1.0));

/// Indicates whether playback is currently paused indefinitely, suspended while waiting for appropriate conditions, or in progress.
/// 
/// For possible values and discussion, see AVPlayerTimeControlStatus.
/// 
/// When automaticallyWaitsToMinimizeStalling is YES, absent intervention in the form of invocations of -setRate: or -pause or, on iOS, an interruption that requires user intervention before playback can resume, the value of the property timeControlStatus automatically changes between AVPlayerTimeControlStatusPlaying and AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate depending on whether sufficient media data is available to continue playback. This property is key value observable.
@property (readonly) AVPlayerTimeControlStatus timeControlStatus NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0), visionos(1.0));

/// The type of reason that a player is waiting for playback.
typedef NSString * AVPlayerWaitingReason NS_STRING_ENUM;

/// Indicates that the player is waiting for appropriate playback buffer conditions before starting playback
/// 
/// The player is waiting for playback because automaticallyWaitToMinimizeStalling is YES and playback at the specified rate would likely cause the playback buffer to become empty before playback completes. Playback will resume when 1) playback at the specified rate will likely complete without a stall or 2) the playback buffer becomes full, meaning no forther buffering of media data is possible.
/// When the value of automaticallyWaitsToMinimizeStalling is NO, timeControlStatus cannot become AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate for this reason.
AVF_EXPORT AVPlayerWaitingReason const AVPlayerWaitingToMinimizeStallsReason API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0), visionos(1.0));

/// Indicates that the player is monitoring the playback buffer fill rate to determine if playback is likely to complete without interruptions.
/// 
/// The player is waiting for playback because automaticallyWaitToMinimizeStalling is YES and it has not yet determined if starting playback at the specified rate would likely cause the buffer to become empty. When the brief initial monitoring period is over, either playback will begin or the value of reasonForWaitingToPlayAtSpecifiedRate will switch to AVPlayerWaitingToMinimizeStallsReason.
/// Recommended practice is not to show UI indicating the waiting state to the user while the value of reasonForWaitingToPlayAtSpecifiedRate is AVPlayerWaitingWhileEvaluatingBufferingRateReason.
AVF_EXPORT AVPlayerWaitingReason const AVPlayerWaitingWhileEvaluatingBufferingRateReason API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0), visionos(1.0));

/// Indicates that the AVPlayer is waiting because its currentItem is nil
/// 
/// The player is waiting for playback because automaticallyWaitToMinimizeStalling is YES and the value of currentItem is nil. When an item becomes available, either because of a call to -replaceCurrentItemWithPlayerItem: or -insertItem: afterItem:, playback will begin or the value of reasonForWaitingToPlay will change.
AVF_EXPORT AVPlayerWaitingReason const AVPlayerWaitingWithNoItemToPlayReason API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0), visionos(1.0));

/// Indicates that the player is waiting for another participant connected through its AVPlayerPlaybackCoordinator.
/// 
/// The player is waiting for playback because its connected AVPlayerPlaybackCoordinator requires information from one of the other participants before playback can start.
AVF_EXPORT AVPlayerWaitingReason const AVPlayerWaitingForCoordinatedPlaybackReason API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Indicates the reason for waiting when the value of timeControlStatus is AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate
/// 
/// When the value of timeControlStatus is AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate, this property describes why the player is currently waiting. It is nil otherwise.
/// You can use the value of reasonForWaitingToPlay to show UI indicating the player's waiting state conditionally.
/// This property is key value observable.
/// Possible values are AVPlayerWaitingWithNoItemToPlayReason, AVPlayerWaitingWhileEvaluatingBufferingRateReason, and AVPlayerWaitingToMinimizeStallsReason.
@property (readonly, nullable) AVPlayerWaitingReason reasonForWaitingToPlay NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0), visionos(1.0));

/// Immediately plays the available media data at the specified rate.
/// 
/// When the player's currentItem has a value of NO for playbackBufferEmpty, this method causes the value of rate to change to the specified rate, the value of timeControlStatus to change to AVPlayerTimeControlStatusPlaying, and the receiver to play the available media immediately, whether or not prior buffering of media data is sufficient to ensure smooth playback.
/// If insufficient media data is buffered for playback to start (e.g. if the current item has a value of YES for playbackBufferEmpty), the receiver will act as if the buffer became empty during playback, except that no AVPlayerItemPlaybackStalledNotification will be posted.
/// 
/// Before macOS 13, iOS 16, tvOS 16, and watchOS 9, this method must be invoked on the main thread/queue.
- (void)playImmediatelyAtRate:(float)rate
#if AVF_DEPLOYING_TO_2022_RELEASES_AND_LATER
NS_SWIFT_NONISOLATED
#endif
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0), visionos(1.0));

@end


@interface AVPlayer (AVPlayerItemControl)

/// Indicates the current item of the player
@property (readonly, nullable) AVPlayerItem *currentItem NS_SWIFT_NONISOLATED;

/// Replaces the player's current item with the specified player item.
/// 
/// In all releases of iOS 4, invoking replaceCurrentItemWithPlayerItem: with an AVPlayerItem that's already the receiver's currentItem results in an exception being raised. Starting with iOS 5, it's a no-op.
/// This method throws an exception if the item already exists in the play queue.
/// 
/// - Parameter item: The AVPlayerItem that will become the player's current item.
- (void)replaceCurrentItemWithPlayerItem:(nullable AVPlayerItem *)item NS_SWIFT_NONISOLATED;

/// These constants are the allowable values of AVPlayer's actionAtItemEnd property.
typedef NS_ENUM(NSInteger, AVPlayerActionAtItemEnd)
{
    /// Indicates that when an AVPlayerItem reaches its end time the player will automatically advance to the next item in its queue. This value is supported only for players of class AVQueuePlayer. An AVPlayer that's not an AVQueuePlayer will raise an NSInvalidArgumentException if an attempt is made to set its actionAtItemEnd to AVPlayerActionAtItemEndAdvance.
    AVPlayerActionAtItemEndAdvance	= 0,
	/// Indicates that when an AVPlayerItem reaches its end time the player will automatically pause (which is to say, the player's rate will automatically be set to 0).
	AVPlayerActionAtItemEndPause	= 1,
	/// Indicates that when an AVPlayerItem reaches its end time the player will take no action (which is to say, the player's rate will not change, its currentItem will not change, and its currentTime will continue to be incremented or decremented as time elapses, according to its rate). After this, if the player's actionAtItemEnd is set to a value other than AVPlayerActionAtItemEndNone, the player will immediately take the action appropriate to that value.
	AVPlayerActionAtItemEndNone		= 2,
};

/// Indicates the action that the player should perform when playback of an item reaches its end time.
/// 
/// This property throws an exception if set to AVPlayerActionAtItemEndAdvance on an AVPlayer which is not an AVQueuePlayer.
@property AVPlayerActionAtItemEnd actionAtItemEnd NS_SWIFT_NONISOLATED;

@end


@interface AVPlayer (AVPlayerTimeControl)

/// Returns the current time of the current item.
/// 
/// Returns the current time of the current item. Not key-value observable; use -addPeriodicTimeObserverForInterval:queue:usingBlock: instead.
/// 
/// - Returns: A CMTime
- (CMTime)currentTime NS_SWIFT_NONISOLATED;

/// Moves the playback cursor.
/// 
/// Use this method to seek to a specified time for the current player item.
/// The time seeked to may differ from the specified time for efficiency. For sample accurate seeking see seekToTime:toleranceBefore:toleranceAfter:.
/// 
/// - Parameter date:
- (void)seekToDate:(NSDate *)date NS_SWIFT_NONISOLATED;

/// Moves the playback cursor and invokes the specified block when the seek operation has either been completed or been interrupted.
/// 
/// Use this method to seek to a specified time for the current player item and to be notified when the seek operation is complete.
/// The completion handler for any prior seek request that is still in process will be invoked immediately with the finished parameter 
/// set to NO. If the new request completes without being interrupted by another seek request or by any other operation the specified 
/// completion handler will be invoked with the finished parameter set to YES. If no item is attached, the completion handler will be
/// invoked immediately with the finished parameter set to NO.
/// 
/// - Parameter date:
/// - Parameter completionHandler:
- (void)seekToDate:(NSDate *)date completionHandler:(void (^ NS_SWIFT_SENDABLE)(BOOL finished))completionHandler NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// Moves the playback cursor.
/// 
/// Use this method to seek to a specified time for the current player item.
/// The time seeked to may differ from the specified time for efficiency. For sample accurate seeking see seekToTime:toleranceBefore:toleranceAfter:.
/// 
/// - Parameter time:
- (void)seekToTime:(CMTime)time NS_SWIFT_NONISOLATED;

/// Moves the playback cursor within a specified time bound.
/// 
/// Use this method to seek to a specified time for the current player item.
/// The time seeked to will be within the range [time-toleranceBefore, time+toleranceAfter] and may differ from the specified time for efficiency.
/// Pass kCMTimeZero for both toleranceBefore and toleranceAfter to request sample accurate seeking which may incur additional decoding delay. 
/// Messaging this method with beforeTolerance:kCMTimePositiveInfinity and afterTolerance:kCMTimePositiveInfinity is the same as messaging seekToTime: directly.
/// 
/// - Parameter time:
/// - Parameter toleranceBefore:
/// - Parameter toleranceAfter:
- (void)seekToTime:(CMTime)time toleranceBefore:(CMTime)toleranceBefore toleranceAfter:(CMTime)toleranceAfter NS_SWIFT_NONISOLATED;

/// Moves the playback cursor and invokes the specified block when the seek operation has either been completed or been interrupted.
/// 
/// Use this method to seek to a specified time for the current player item and to be notified when the seek operation is complete.
/// The completion handler for any prior seek request that is still in process will be invoked immediately with the finished parameter 
/// set to NO. If the new request completes without being interrupted by another seek request or by any other operation the specified 
/// completion handler will be invoked with the finished parameter set to YES. If no item is attached, the completion handler will be
/// invoked immediately with the finished parameter set to NO.
/// 
/// - Parameter time:
/// - Parameter completionHandler:
- (void)seekToTime:(CMTime)time completionHandler:(void (^ NS_SWIFT_SENDABLE)(BOOL finished))completionHandler NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// Moves the playback cursor within a specified time bound and invokes the specified block when the seek operation has either been completed or been interrupted.
/// 
/// Use this method to seek to a specified time for the current player item and to be notified when the seek operation is complete.
/// The time seeked to will be within the range [time-toleranceBefore, time+toleranceAfter] and may differ from the specified time for efficiency.
/// Pass kCMTimeZero for both toleranceBefore and toleranceAfter to request sample accurate seeking which may incur additional decoding delay. 
/// Messaging this method with beforeTolerance:kCMTimePositiveInfinity and afterTolerance:kCMTimePositiveInfinity is the same as messaging seekToTime: directly.
/// The completion handler for any prior seek request that is still in process will be invoked immediately with the finished parameter set to NO. If the new 
/// request completes without being interrupted by another seek request or by any other operation the specified completion handler will be invoked with the 
/// finished parameter set to YES. If no item is attached, the completion handler will be invoked immediately with the finished parameter set to NO.
/// 
/// - Parameter time:
/// - Parameter toleranceBefore:
/// - Parameter toleranceAfter:
- (void)seekToTime:(CMTime)time toleranceBefore:(CMTime)toleranceBefore toleranceAfter:(CMTime)toleranceAfter completionHandler:(void (^ NS_SWIFT_SENDABLE)(BOOL finished))completionHandler NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0), watchos(1.0), visionos(1.0));

@end


@interface AVPlayer (AVPlayerAdvancedRateControl)

/// Indicates that the player is allowed to delay playback at the specified rate in order to minimize stalling
/// 
/// When this property is YES, whenever 1) the rate is set from zero to non-zero or 2) the playback buffer becomes empty and playback stalls, the player will attempt to determine if, at the specified rate, its currentItem will play to the end without interruptions. Should it determine that such interruptions would occur and these interruptions can be avoided by delaying the start or resumption of playback, the value of timeControlStatus will become AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate and playback will start automatically when the likelihood of stalling has been minimized.
/// 
/// You may want to set this property to NO when you need precise control over playback start times, e.g., when synchronizing multiple instances of AVPlayer, and you should set it to NO if you use an AVAssetResourceLoader delegate to load media data (more on this below). If the value of this property is NO, reasonForWaitingToPlay cannot assume a value of AVPlayerWaitingToMinimizeStallsReason.
/// This implies that setting rate to a non-zero value in AVPlayerTimeControlStatusPaused will cause playback to start immediately as long as the playback buffer is not empty. When the playback buffer becomes empty during AVPlayerTimeControlStatusPlaying and playback stalls, playback state will switch to AVPlayerTimeControlStatusPaused and the rate will become 0.0.
/// 
/// Changing the value of this property to NO while the value of timeControlStatus is AVPlayerTimeControlStatusWaitingToPlayAtSpecifiedRate with a reasonForWaitingToPlay of AVPlayerWaitingToMinimizeStallsReason will cause the player to attempt playback at the specified rate immediately.
/// 
/// For clients linked against iOS 10.0 and running on that version or later or linked against macOS 10.12 and running on that version or later, the default value of this property is YES.
/// In versions of iOS prior to iOS 10.0 and versions of macOS prior to 10.12, this property is unavailable, and the behavior of the AVPlayer corresponds to the type of content being played. For streaming content, including HTTP Live Streaming, the AVPlayer acts as if automaticallyWaitsToMinimizeStalling is YES. For file-based content, including file-based content accessed via progressive http download, the AVPlayer acts as if automaticallyWaitsToMinimizeStalling is NO.
/// 
/// If you employ an AVAssetResourceLoader delegate that loads media data for playback, you should set the value of your AVPlayer’s automaticallyWaitsToMinimizeStalling property to NO. Allowing the value of automaticallyWaitsToMinimizeStalling to remain YES when an AVAssetResourceLoader delegate is used for the loading of media data can result in poor start-up times for playback and poor recovery from stalls, because the behaviors provided by AVPlayer when automaticallyWaitsToMinimizeStalling has a value of YES depend on predictions of the future availability of media data that that do not function as expected when data is loaded via a client-controlled means, using the AVAssetResourceLoader delegate interface.
/// 
/// You can allow the value of automaticallyWaitsToMinimizeStalling to remain YES if you use an AVAssetResourceLoader delegate to manage content keys for FairPlay Streaming, to provide dynamically-generated master playlists for HTTP Live Streaming, or to respond to authentication challenges, but not to load media data for playback.
/// 
/// Before macOS 13, iOS 16, tvOS 16, and watchOS 9, this property must be accessed on the main thread/queue.
@property (nonatomic) BOOL automaticallyWaitsToMinimizeStalling
#if AVF_DEPLOYING_TO_2022_RELEASES_AND_LATER
NS_SWIFT_NONISOLATED
#endif
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0), visionos(1.0));

/// Simultaneously sets the playback rate and the relationship between the current item's current time and host time.
/// 
/// You can use this function to synchronize playback with an external activity.
/// 
/// The current item's timebase is adjusted so that its time will be (or was) itemTime when host time is (or was) hostClockTime.
/// In other words: if hostClockTime is in the past, the timebase's time will be interpolated as though the timebase has been running at the requested rate since that time. If hostClockTime is in the future, the timebase will immediately start running at the requested rate from an earlier time so that it will reach the requested itemTime at the requested hostClockTime. (Note that the item's time will not jump backwards, but instead will sit at itemTime until the timebase reaches that time.)
/// 
/// Note that setRate:time:atHostTime: is not supported when automaticallyWaitsToMinimizeStalling is YES. For clients linked against iOS 10.0 and later or macOS 12.0 and later, invoking setRate:time:atHostTime: when automaticallyWaitsToMinimizeStalling is YES will raise an NSInvalidArgument exception. Support for HTTP Live Streaming content requires iOS 11, tvOS 11, macOS 10.13 or later.
/// 
/// Before macOS 13, iOS 16, tvOS 16, and watchOS 9, this method must be invoked on the main thread/queue.
/// 
/// - Parameter itemTime: The time to start playback from, specified precisely (i.e., with zero tolerance). Pass kCMTimeInvalid to use the current item's current time.
/// - Parameter hostClockTime: The host time at which to start playback. If hostClockTime is specified, the player will not ensure that media data is loaded before the timebase starts moving. If hostClockTime is kCMTimeInvalid, the rate and time will be set together, but without external synchronization; a host time in the near future will be used, allowing some time for media data loading.
- (void)setRate:(float)rate time:(CMTime)itemTime atHostTime:(CMTime)hostClockTime
#if AVF_DEPLOYING_TO_2022_RELEASES_AND_LATER
NS_SWIFT_NONISOLATED
#endif
API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// Begins loading media data to prime the render pipelines for playback from the current time with the given rate.
/// 
/// Once the completion handler is called with YES, the player's rate can be set with minimal latency.
/// The completion handler will be called with NO if the preroll is interrupted by a time change or incompatible rate change, or if preroll is not possible for some other reason.
/// Call this method only when the rate is currently zero and only after the AVPlayer's status has become AVPlayerStatusReadyToPlay.
/// This method throws an exception if the status is not AVPlayerStatusReadyToPlay.
/// 
/// - Parameter rate: The intended rate for subsequent playback.
/// - Parameter completionHandler: The block that will be called when the preroll is either completed or is interrupted.
- (void)prerollAtRate:(float)rate completionHandler:(nullable void (^ NS_SWIFT_SENDABLE)(BOOL finished))completionHandler NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// Cancel any pending preroll requests and invoke the corresponding completion handlers if present.
/// 
/// Use this method to cancel and release the completion handlers for pending prerolls. The finished parameter of the completion handlers will be set to NO.
- (void)cancelPendingPrerolls NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// Set to override the automatic choice of source clock for item timebases.
/// 
/// NULL by default. This is most useful for synchronizing video-only movies with audio played via other means. IMPORTANT NOTE: If you specify a source clock other than the appropriate audio device clock, audio may drift out of sync.
@property (nonatomic, retain, nullable) __attribute__((NSObject)) CMClockRef sourceClock NS_SWIFT_NONISOLATED API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

@end


@interface AVPlayer (AVPlayerTimeObservation)

/// Requests invocation of a block during playback to report changing time.
/// 
/// The block is invoked periodically at the interval specified, interpreted according to the timeline of the current item.
/// The block is also invoked whenever time jumps and whenever playback starts or stops.
/// If the interval corresponds to a very short interval in real time, the player may invoke the block less frequently
/// than requested. Even so, the player will invoke the block sufficiently often for the client to update indications
/// of the current time appropriately in its end-user interface.
/// Each call to -addPeriodicTimeObserverForInterval:queue:usingBlock: should be paired with a corresponding call to -removeTimeObserver:.
/// Releasing the observer object without a call to -removeTimeObserver: will result in undefined behavior.
/// 
/// - Parameter interval: The interval of invocation of the block during normal playback, according to progress of the current time of the player.
/// - Parameter queue: The serial queue onto which block should be enqueued. If you pass NULL, the main queue (obtained using dispatch_get_main_queue()) will be used. Passing a concurrent queue to this method will result in undefined behavior.
/// - Parameter block: The block to be invoked periodically.
/// 
/// - Returns: An object conforming to the NSObject protocol.  You must retain this returned value as long as you want the time observer to be invoked by the player.
/// 	  Pass this object to -removeTimeObserver: to cancel time observation.
- (id)addPeriodicTimeObserverForInterval:(CMTime)interval queue:(nullable dispatch_queue_t)queue usingBlock:(void (^ NS_SWIFT_SENDABLE)(CMTime time))block NS_SWIFT_NONISOLATED;

/// Requests invocation of a block when specified times are traversed during normal playback.
/// 
/// Each call to -addPeriodicTimeObserverForInterval:queue:usingBlock: should be paired with a corresponding call to -removeTimeObserver:.
/// Releasing the observer object without a call to -removeTimeObserver: will result in undefined behavior.
/// 
/// - Parameter times: The times for which the observer requests notification, supplied as an array of NSValues carrying CMTimes.
/// - Parameter queue: The serial queue onto which block should be enqueued. If you pass NULL, the main queue (obtained using dispatch_get_main_queue()) will be used. Passing a concurrent queue to this method will result in undefined behavior.
/// - Parameter block: The block to be invoked when any of the specified times is crossed during normal playback.
/// 
/// - Returns: An object conforming to the NSObject protocol.  You must retain this returned value as long as you want the time observer to be invoked by the player.
/// 	  Pass this object to -removeTimeObserver: to cancel time observation.
- (id)addBoundaryTimeObserverForTimes:(NSArray<NSValue *> *)times queue:(nullable dispatch_queue_t)queue usingBlock:(void (^ NS_SWIFT_SENDABLE)(void))block NS_SWIFT_NONISOLATED;

/// Cancels a previously registered time observer.
/// 
/// Upon return, the caller is guaranteed that no new time observer blocks will begin executing. Depending on the calling thread and the queue
/// used to add the time observer, an in-flight block may continue to execute after this method returns. You can guarantee synchronous time 
/// observer removal by enqueuing the call to -removeTimeObserver: on that queue. Alternatively, call dispatch_sync(queue, ^{}) after
/// -removeTimeObserver: to wait for any in-flight blocks to finish executing.
/// -removeTimeObserver: should be used to explicitly cancel each time observer added using -addPeriodicTimeObserverForInterval:queue:usingBlock:
/// and -addBoundaryTimeObserverForTimes:queue:usingBlock:.
/// 
/// This method throws an exception for any of the following reasons:
/// - observer was added by a different instance of AVPlayer
/// - observer was not returned by -addPeriodicTimeObserverForInterval:queue:usingBlock:
/// - observer was not returned by -addBoundaryTimeObserverForTimes:queue:usingBlock:
/// 
/// - Parameter observer: An object returned by a previous call to -addPeriodicTimeObserverForInterval:queue:usingBlock: or -addBoundaryTimeObserverForTimes:queue:usingBlock:.
- (void)removeTimeObserver:(id)observer NS_SWIFT_NONISOLATED;

@end


@interface AVPlayer (AVPlayerMediaControl)

/// Indicates the current audio volume of the player; 0.0 means "silence all audio", 1.0 means "play at the full volume of the current item".
///
/// iOS note: Do not use this property to implement a volume slider for media playback. For that purpose, use MPVolumeView, which is customizable in appearance and provides standard media playback behaviors that users expect.
/// This property is most useful on iOS to control the volume of the AVPlayer relative to other audio output, not for volume control by end users.
@property float volume NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.7), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// Indicates whether or not audio output of the player is muted. Only affects audio muting for the player instance and not for the device.
@property (getter=isMuted) BOOL muted NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.7), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));

@end


@class AVPlayerMediaSelectionCriteria;

@interface AVPlayer (AVPlayerAutomaticMediaSelection)

/// Indicates whether the receiver should apply the current selection criteria automatically to AVPlayerItems.
///
/// For clients linked against the iOS 7 SDK or later or against the macOS 10.9 SDK or later, the default is YES. For all others, the default is NO.
///
/// By default, AVPlayer applies selection criteria based on system preferences. To override the default criteria for any media selection group, use -[AVPlayer setMediaSelectionCriteria:forMediaCharacteristic:].
@property BOOL appliesMediaSelectionCriteriaAutomatically NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// Applies automatic selection criteria for media that has the specified media characteristic.
/// 
/// Criteria will be applied to an AVPlayerItem when:
/// a) It is made ready to play
/// b) Specific media selections are made by -[AVPlayerItem selectMediaOption:inMediaSelectionGroup:] in a different group. The automatic choice in one group may be influenced by a specific selection in another group.
/// c) Underlying system preferences change, e.g. system language, accessibility captions.
/// 
/// Specific selections made by -[AVPlayerItem selectMediaOption:inMediaSelectionGroup:] within any group will override automatic selection in that group until -[AVPlayerItem selectMediaOptionAutomaticallyInMediaSelectionGroup:] is received.
/// 
/// Before macOS 13, iOS 16, tvOS 16, and watchOS 9, this method must be invoked on the main thread/queue.
/// 
/// - Parameter criteria: An instance of AVPlayerMediaSelectionCriteria.
/// - Parameter mediaCharacteristic: The media characteristic for which the selection criteria are to be applied. Supported values include AVMediaCharacteristicAudible, AVMediaCharacteristicLegible, and AVMediaCharacteristicVisual.
- (void)setMediaSelectionCriteria:(nullable AVPlayerMediaSelectionCriteria *)criteria forMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic
#if AVF_DEPLOYING_TO_2022_RELEASES_AND_LATER
NS_SWIFT_NONISOLATED
#endif
API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// Returns the automatic selection criteria for media that has the specified media characteristic.
/// 
/// - Parameter mediaCharacteristic: The media characteristic for which the selection criteria is to be returned. Supported values include AVMediaCharacteristicAudible, AVMediaCharacteristicLegible, and AVMediaCharacteristicVisual. Before macOS 13, iOS 16, tvOS 16, and watchOS 9, this method must be invoked on the main thread/queue.
- (nullable AVPlayerMediaSelectionCriteria *)mediaSelectionCriteriaForMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic
#if AVF_DEPLOYING_TO_2022_RELEASES_AND_LATER
NS_SWIFT_NONISOLATED
#endif
API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));

@end


@interface AVPlayer (AVPlayerAudioDeviceSupport)

/// Specifies the unique ID of the Core Audio output device used to play audio.
/// 
/// By default, the value of this property is nil, indicating that the default audio output device is used. Otherwise the value of this property is an NSString containing the unique ID of the Core Audio output device to be used for audio output.
/// 
/// Core Audio's kAudioDevicePropertyDeviceUID is a suitable source of audio output device unique IDs.
@property (copy, nullable) NSString *audioOutputDeviceUniqueID NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

@end

/// Methods for supporting "external playback" of video
/// 
/// "External playback" is a mode where video data is sent to an external device for full screen playback at its original fidelity.
/// AirPlay Video playback is considered as an "external playback" mode.
/// 
/// In "external screen" mode (also known as mirroring and second display), video data is rendered on the host 
/// device (e.g. Mac and iPhone), rendered video is recompressed and transferred to the external device, and the
/// external device decompresses and displays the video.
/// 
/// AVPlayerExternalPlaybackSupport properties affect AirPlay Video playback and are the replacement for the 
/// deprecated AVPlayerAirPlaySupport properties.
/// 
/// Additional note for iOS: AVPlayerExternalPlaybackSupport properties apply to the Lightning-based
/// video adapters but do not apply to 30-pin-connector-based video output cables and adapters.
@interface AVPlayer (AVPlayerExternalPlaybackSupport)

/// Indicates whether the player allows switching to "external playback" mode. The default value is YES.
@property BOOL allowsExternalPlayback NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.11), ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, visionos);

/// Indicates whether the player is currently playing video in "external playback" mode.
@property (readonly, getter=isExternalPlaybackActive) BOOL externalPlaybackActive NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.11), ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, visionos);

/// Indicates whether the player should automatically switch to "external playback" mode while the "external screen" mode is active in order to play video content and switching back to "external screen" mode as soon as playback is done. Brief transition may be visible on the external display when automatically switching between the two modes. The default value is NO. Has no effect if allowsExternalPlayback is NO.
@property BOOL usesExternalPlaybackWhileExternalScreenIsActive NS_SWIFT_NONISOLATED API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(macos, watchos, visionos);

/// Video gravity strictly for "external playback" mode, one of AVLayerVideoGravity* defined in AVAnimation.h
@property (nonatomic, copy) AVLayerVideoGravity externalPlaybackVideoGravity NS_SWIFT_NONISOLATED API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(macos, watchos, visionos);

@end

#if TARGET_OS_IPHONE

@interface AVPlayer (AVPlayerAirPlaySupport)

/// Indicates whether the player allows AirPlay Video playback. The default value is YES.  This property is deprecated. Use AVPlayer's -allowsExternalPlayback instead.
@property BOOL allowsAirPlayVideo API_DEPRECATED_WITH_REPLACEMENT("allowsExternalPlayback", ios(5.0, 6.0), tvos(9.0, 9.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(macos);

/// Indicates whether the player is currently playing video via AirPlay. This property is deprecated. Use AVPlayer's -externalPlaybackActive instead.
@property (readonly, getter=isAirPlayVideoActive) BOOL airPlayVideoActive API_DEPRECATED_WITH_REPLACEMENT("externalPlaybackActive", ios(5.0, 6.0), tvos(9.0, 9.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(macos);

/// Indicates whether the player should automatically switch to AirPlay Video while AirPlay Screen is active in order to play video content, switching back to AirPlay Screen as soon as playback is done.
///
/// The default value is NO. Has no effect if allowsAirPlayVideo is NO.
/// This property is deprecated. Use AVPlayer's -usesExternalPlaybackWhileExternalScreenIsActive instead.
@property BOOL usesAirPlayVideoWhileAirPlayScreenIsActive API_DEPRECATED_WITH_REPLACEMENT("usesExternalPlaybackWhileExternalScreenIsActive", ios(5.0, 6.0), tvos(9.0, 9.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(macos);

@end

#endif // TARGET_OS_IPHONE

/// Methods supporting protected content.
@interface AVPlayer (AVPlayerProtectedContent)

/// Whether or not decoded output is being obscured due to insufficient external protection.
/// 
/// The value of this property indicates whether the player is purposefully obscuring the visual output
/// of the current item because the requirement for an external protection mechanism is not met by the
/// current device configuration. It is highly recommended that clients whose content requires external
/// protection observe this property and set the playback rate to zero and display an appropriate user
/// interface when the value changes to YES. This property is key value observable.
/// 
/// Note that the value of this property is dependent on the external protection requirements of the
/// current item. These requirements are inherent to the content itself and cannot be externally specified.
/// If the current item does not require external protection, the value of this property will be NO.
@property (readonly) BOOL outputObscuredDueToInsufficientExternalProtection NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.12), ios(6.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

@end

/// A bitfield type that specifies an HDR mode.
typedef NS_OPTIONS(NSInteger, AVPlayerHDRMode) {
	/// Indicates that HLG (Hybrid Log-Gamma) HDR mode is available.
	AVPlayerHDRModeHLG				= 0x1,
	/// Indicates that HDR10 HDR mode is available.
	AVPlayerHDRModeHDR10				= 0x2,
	/// Indicates that Dolby Vision HDR mode is available.
	AVPlayerHDRModeDolbyVision		= 0x4,
} API_DEPRECATED("The deprecated availableHDRModes uses this enum. Use eligibleForHDRPlayback instead", ios(11.2, 26.0), tvos(11.2, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos);

@interface AVPlayer (AVPlayerPlaybackCapabilities)

/// An AVPlayerHDRMode value that indicates the HDR modes the device can play to an appropriate display. A value of 0 indicates that no HDR modes are supported.
/// 
/// This property indicates all of the HDR modes that the device can play. Each value indicates that an appropriate HDR display is available for the specified HDR mode. Additionally, the device must be capable of playing the specified HDR type. This property does not indicate whether video contains HDR content, whether HDR video is currently playing, or whether video is playing on an HDR display.
@property (class, readonly) AVPlayerHDRMode availableHDRModes NS_SWIFT_NONISOLATED API_DEPRECATED("Use eligibleForHDRPlayback instead", ios(11.2, 26.0), tvos(11.2, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos);

/// A notification that fires whenever availableHDRModes changes.
/// 
/// This notification fires when a value is added or removed from the list of availableHDRModes. This can be caused by display connection/disconnection or resource changes.
API_DEPRECATED_WITH_REPLACEMENT("AVPlayerEligibleForHDRPlaybackDidChangeNotification", ios(11.2, 26.0), tvos(11.2, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos)
AVF_EXPORT NSNotificationName const AVPlayerAvailableHDRModesDidChangeNotification;

/// Indicates whether HDR content can be played to an appropriate display.
/// 
/// This property is YES if an HDR display is available and the device is capable of playing HDR content from an appropriate AVAsset, NO otherwise. This property does not indicate whether video contains HDR content, whether HDR video is currently playing, or whether video is playing on an HDR display. This property is not KVO observable.
@property (class, readonly) BOOL eligibleForHDRPlayback NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.15), ios(13.4), tvos(13.4), visionos(1.0)) API_UNAVAILABLE(watchos);

/// A notification that fires whenever eligibleForHDRPlayback changes.
/// 
/// This notification fires when eligibleForHDRPlayback changes. This can be caused by display connection/disconnection or resource changes.
API_AVAILABLE(macos(10.15), ios(13.4), tvos(13.4), visionos(1.0)) API_UNAVAILABLE(watchos)
AVF_EXPORT NSNotificationName const AVPlayerEligibleForHDRPlaybackDidChangeNotification;

@end

@interface AVPlayer (AVPlayerVideoDecoderGPUSupport)

/// Specifies a registryID associated with a GPU that should be used for video decode.
/// 
/// By default, whenever possible, video decode will be performed on the GPU associated with the display on which the presenting CALayer is located. Decode will be transitioned to a new GPU if appropriate when the CALayer moves to a new display. This property overrides this default behavior, forcing decode to prefer an affinity to the GPU specified regardless of which GPU is being used to display the associated CALayer.
/// 
/// The GPU registryID can be obtained from the GPU MTLDevice using [MTLDevice registryID] or can be obtained from OpenGL or OpenCL.
@property (nonatomic) uint64_t preferredVideoDecoderGPURegistryID NS_SWIFT_NONISOLATED API_AVAILABLE(macos(10.13)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

@end

@interface AVPlayer (AVPlayerVideoDisplaySleepPrevention)

/// Indicates whether video playback prevents display and device sleep.
/// 
/// Default is YES on iOS, tvOS and in Mac Catalyst apps. Default is NO on macOS.
/// Setting this property to NO does not force the display to sleep, it simply stops preventing display sleep. Other apps or frameworks within your app may still be preventing display sleep for various reasons.
/// 
/// Before macOS 13, iOS 16, tvOS 16, and watchOS 9, this property must be accessed on the main thread/queue.
@property (nonatomic) BOOL preventsDisplaySleepDuringVideoPlayback
#if AVF_DEPLOYING_TO_2022_RELEASES_AND_LATER
NS_SWIFT_NONISOLATED
#endif
API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0)) API_UNAVAILABLE(watchos, visionos);

@end

@interface AVPlayer (AVPlayerAutomaticBackgroundPrevention)

/// Indicates whether video playback prevents the app from automatically getting backgrounded.
/// 
/// Default value is YES.
/// Setting this property to YES prevents an application that is playing video from automatically getting backgrounded. This property does not prevent the user from backgrounding the application.
@property (nonatomic) BOOL preventsAutomaticBackgroundingDuringVideoPlayback NS_SWIFT_NONISOLATED API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(macos, ios, tvos, watchos);
@end

@interface AVPlayer (AVPlayerBackgroundSupport)

/// This policy describes how AVPlayer behaves when the application transitions to UIApplicationStateBackground while playing video.
typedef NS_ENUM(NSInteger, AVPlayerAudiovisualBackgroundPlaybackPolicy) {
	/// Indicates that the system is free to decide. This is the default policy.
	AVPlayerAudiovisualBackgroundPlaybackPolicyAutomatic = 1,
	/// Indicates that the player must be paused on going to background.
	AVPlayerAudiovisualBackgroundPlaybackPolicyPauses = 2,
	/// Indicates that the player continues to play if possible in background.
	AVPlayerAudiovisualBackgroundPlaybackPolicyContinuesIfPossible = 3,
} API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/// Controls the policy to be used in deciding how playback of audiovisual content should continue while the application transitions to background.
/// 
/// By default, the system is free to decide the background playback policy (AVPlayerAudiovisualBackgroundPlaybackPolicyAutomatic).
/// If set to AVPlayerAudiovisualBackgroundPlaybackPolicyPauses, player will be paused on entering background.
/// If set to AVPlayerAudiovisualBackgroundPlaybackPolicyContinuesIfPossible, the system makes the best effort to continue playback but the app also needs appropriate UIBackgroundModes for the system to let it continue running in the background. Note that this policy only applies to items with enabled video.
@property (nonatomic) AVPlayerAudiovisualBackgroundPlaybackPolicy audiovisualBackgroundPlaybackPolicy NS_SWIFT_NONISOLATED API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

@end

@interface AVPlayer (PlaybackCoordination)

/// The playback coordinator for this player.
/// 
/// If the playback coordinator is connected to other participants, rate changes and seeks on the current item will be automatically mirrored to all connected participants.
/// Depending on policies, the coordinator may also intercept rate changes to non-zero to coordinate playback start with the rest of the group.
/// Use [AVPlayer playImmediatelyAtRate:] to override the coordinated startup behavior and start playback immediately. This is useful to give users an opportunity to override waiting caused by other participants' suspensions.
/// Player configuration other than rate and seeks are not communicated to other participants and can be configured independently by each participant.
/// A player with a connected playbackCoordinator will change behavior in situations that require the player to pause for internal reasons, such as a route change or a stall.
/// When resuming after these events, the player will not resume at the stop time. Instead, it will attempt to rejoin the group, potentially seeking to match the other participant's progress.
/// It is left to the owner of the AVPlayer to ensure that all participants are playing the same item. See the discussion of AVPlaybackCoordinator for considerations about item transitions.
@property (readonly, strong) AVPlayerPlaybackCoordinator *playbackCoordinator
#if AVF_DEPLOYING_TO_2024_RELEASES_AND_LATER
NS_SWIFT_NONISOLATED
#endif
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

@end

API_AVAILABLE(macos(14.2), ios(17.2), tvos(17.2), watchos(10.2), visionos(1.1))
@interface AVPlayer (AVPlayerOutputSupport)

/// The video output for this player, if one was set.
/// 
/// When an AVPlayerVideoOutput is associated with an AVPlayer, the AVPlayerVideoOutput can then be used to receive video-related samples during playback.
/// 
/// - NOTE: If an output is set while AVPlayer has a current item it may cause different data channels to be selected for that item, which can have a performance impact.
///  				As a result, when possible, it is best to set an output before setting items on an AVPlayer.
@property (nonatomic, nullable, readwrite) AVPlayerVideoOutput *videoOutput NS_SWIFT_NONISOLATED;

@end

/// This defines the network resource priority for a player.
typedef NS_ENUM(NSInteger, AVPlayerNetworkResourcePriority) {
	/// The default priority level given to a player for loading network resources. Use this when the player requires an optimal level of network resources and streaming in high-quality resolution is ideal. Players with AVPlayerNetworkResourcePriorityHigh will take precedence over this player. This player will take precedence over players with AVPlayerNetworkResourcePriorityLow.
	AVPlayerNetworkResourcePriorityDefault = 0,
	/// Indicates a low priority level for loading network resources. Use this when the player requires minimal network bandwidth and streaming in high-quality resolution is not crucial. Other players with higher priority will take precedence over this player.
	AVPlayerNetworkResourcePriorityLow = 1,
	/// Indicates a high priority level for loading network resources. Use this when the player requires a high level of network resources and streaming in high-quality resolution is crucial. This player will take precedence over other lower priority players.
	AVPlayerNetworkResourcePriorityHigh = 2,
} NS_SWIFT_NAME(AVPlayer.NetworkResourcePriority) API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
@interface AVPlayer (AVPlayerResourceArbitrationSupport)

/// Indicates the priority of this player for network bandwidth resource distribution.
/// 
/// This value determines the priority of the player during network resource allocation among all other players within the same application process. The default value for this is AVPlayerNetworkResourcePriorityDefault.
@property (nonatomic) AVPlayerNetworkResourcePriority networkResourcePriority API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

@end

API_AVAILABLE(visionos(26.0)) API_UNAVAILABLE(macos, ios, tvos, watchos)
@interface AVPlayer (AVPlayerSpatialAudioExperience)

/// The AVPlayer's intended spatial audio experience.
/// 
/// The default value of CAAutomaticSpatialAudio means the player uses its AVAudioSession's intended spatial experience. If the anchoring strategy is impossible (e.g. it uses a destroyed UIScene's identifier), the player follows a "front" anchoring strategy instead.
@property (nonatomic, copy) CASpatialAudioExperience *intendedSpatialAudioExperience NS_SWIFT_NONISOLATED NS_REFINED_FOR_SWIFT;

@end

#if TARGET_OS_IOS || TARGET_OS_TV

/// AVPlayer conforms to the AVRoutingPlaybackParticipant protocol
/// 
/// An AVPlayer can be used as a participant in an AVRoutingPlaybackArbiter. Participants to the AVRoutingPlaybackArbiter must conform to the AVRoutingPlaybackParticipant protocol.
API_AVAILABLE(ios(26.0), tvos(26.0)) API_UNAVAILABLE(macos, watchos, visionos)
@interface AVPlayer (AVRoutingPlaybackArbitrationEligibility) <AVRoutingPlaybackParticipant>

@end
#endif

@interface AVPlayer (AVPlayerRoutingPlaybackArbitrationSupport)

/// Whether the player's audio output is suppressed due to being on a non-mixable audio route.
/// 
/// If YES, the player's audio output is suppressed. The player is muted while on a non-mixable audio route and cannot play audio. The player's mute property does not reflect the true mute status.
/// If NO, the player's audio output is not suppressed. The player may be muted or unmuted while on a non-mixable audio route and can play audio. The player's mute property reflects the true mute status.
/// In a non-mixable audio route, only one player can play audio. To play audio in non-mixable states, the player must be specified as the priority participant in AVRoutingPlaybackArbiter.preferredParticipantForNonMixableAudioRoutes. If this player becomes the preferred player, it will gain audio priority and suppress the audio of all other players. If another participant becomes the preferred participant, this player will lose audio priority and have their audio suppressed. This property is key-value observed.
@property (nonatomic, readonly) BOOL audioOutputSuppressedDueToNonMixableAudioRoute API_AVAILABLE(ios(26.0), tvos(26.0)) API_UNAVAILABLE(macos, watchos, visionos);

@end

@interface AVPlayer (AVPlayerObservation)

/// AVPlayer and other AVFoundation types can optionally be observed using Swift Observation.
///
/// When set to YES, new instances of AVPlayer, AVQueuePlayer, AVPlayerItem, and AVPlayerItemTrack are observable with Swift Observation. The default value is NO (not observable).  An exception is thrown if this property is set YES after initializing any objects of these types, or if it is set to NO after any observable objects are initialized.  In other words, all objects of these types must either be observable or not observable in an application instance.
///
/// For more information regarding management of class objects in SwiftUI, please refer to https://developer.apple.com/documentation/swiftui/state.
@property (class, readwrite, getter=isObservationEnabled) BOOL observationEnabled NS_SWIFT_NONISOLATED API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
@end

@interface AVPlayer (AVPlayerDeprecated)

/// Indicates whether display of closed captions is enabled.
/// 
/// This property is deprecated.
/// 
/// When the value of appliesMediaSelectionCriteriaAutomatically is YES, the receiver will enable closed captions automatically either according to user preferences or, if you provide them, according to AVPlayerMediaSelectionCriteria for the media characteristic AVMediaCharacteristicLegible.
/// 
/// If you want to determine whether closed captions may be available for a given AVPlayerItem, you can examine the AVMediaSelectionOptions in the AVMediaSelectionGroup for the characteristic AVMediaCharacteristicLegible, as vended by -[AVAsset mediaSelectionGroupForMediaCharacteristic:]. See AVMediaCharacteristicTranscribesSpokenDialogForAccessibility and AVMediaCharacteristicDescribesMusicAndSoundForAccessibility as documented in AVMediaFormat.h for information about how to identify legible media selection options that offer the features of closed captions for accessibility purposes.
/// 
/// You can select or deselect a specific AVMediaSelectionOption via -[AVPlayerItem selectMediaOption:inMediaSelectionGroup:].
/// 
/// For further information about Media Accessibility preferences, see MediaAccessibility framework documentation.
@property (getter=isClosedCaptionDisplayEnabled) BOOL closedCaptionDisplayEnabled API_DEPRECATED("Allow AVPlayer to enable closed captions automatically according to user preferences by ensuring that the value of appliesMediaSelectionCriteriaAutomatically is YES.", macos(10.7, 10.13), ios(4.0, 11.0), tvos(9.0, 11.0)) API_UNAVAILABLE(watchos, visionos);

/// Use sourceClock instead.
@property (nonatomic, retain, nullable) __attribute__((NSObject)) CMClockRef masterClock NS_SWIFT_NONISOLATED API_DEPRECATED_WITH_REPLACEMENT( "sourceClock", macos(10.8, 15.0), ios(6.0, 18.0), tvos(9.0, 18.0), watchos(1.0, 11.0)) API_UNAVAILABLE(visionos);

@end

@class AVQueuePlayerInternal;

/// AVQueuePlayer is a subclass of AVPlayer that offers an interface for multiple-item playback.
/// 
/// AVQueuePlayer extends AVPlayer with methods for managing a queue of items to be played in sequence.
/// It plays these items as gaplessly as possible in the current runtime environment, depending on 
/// the timely availability of media data for the enqueued items.
/// 
/// For best performance clients should typically enqueue only as many AVPlayerItems as are necessary
/// to ensure smooth playback. Note that once an item is enqueued it becomes eligible to be loaded and
/// made ready for playback, with whatever I/O and processing overhead that entails.
API_AVAILABLE(macos(10.7), ios(4.1), tvos(9.0), watchos(1.0), visionos(1.0))
@interface AVQueuePlayer : AVPlayer 
{
@private
    AVQueuePlayerInternal   *_queuePlayer;
}

/// Creates an instance of AVQueuePlayer and enqueues the AVPlayerItems from the specified array.
/// 
/// - Parameter items: An NSArray of AVPlayerItems with which to populate the player's queue initially.
/// 
/// - Returns: An instance of AVQueuePlayer.
+ (instancetype)queuePlayerWithItems:(NSArray<AVPlayerItem *> *)items NS_SWIFT_NONISOLATED;

/// Initializes an instance of AVQueuePlayer by enqueueing the AVPlayerItems from the specified array.
/// 
/// This method throws an exception if items contains duplicated values or values associated with another AVPlayer.
/// 
/// - Parameter items: An NSArray of AVPlayerItems with which to populate the player's queue initially.
/// 
/// - Returns: An instance of AVQueuePlayer.
- (instancetype)initWithItems:(NSArray<AVPlayerItem *> *)items NS_SWIFT_NONISOLATED;

/// Provides an array of the currently enqueued items.
/// 
/// - Returns: An NSArray containing the enqueued AVPlayerItems.
- (NSArray<AVPlayerItem *> *)items NS_SWIFT_NONISOLATED;

/// Ends playback of the current item and initiates playback of the next item in the player's queue.
/// 
/// Removes the current item from the play queue.
- (void)advanceToNextItem NS_SWIFT_NONISOLATED;

/// Tests whether an AVPlayerItem can be inserted into the player's queue.
/// 
/// Note that adding the same AVPlayerItem to an AVQueuePlayer at more than one position in the queue is not supported.
/// 
/// - Parameter item: The AVPlayerItem to be tested.
/// - Parameter afterItem: The item that the item to be tested is to follow in the queue. Pass nil to test whether the item can be appended to the queue.
/// 
/// - Returns: An indication of whether the item can be inserted into the queue after the specified item.
- (BOOL)canInsertItem:(AVPlayerItem *)item afterItem:(nullable AVPlayerItem *)afterItem NS_SWIFT_NONISOLATED;

/// Places an AVPlayerItem after the specified item in the queue.
/// 
/// This method throws an exception if item already exists in the queue.
/// 
/// - Parameter item: The item to be inserted.
/// - Parameter afterItem: The item that the newly inserted item should follow in the queue. Pass nil to append the item to the queue.
- (void)insertItem:(AVPlayerItem *)item afterItem:(nullable AVPlayerItem *)afterItem NS_SWIFT_NONISOLATED;

/// Removes an AVPlayerItem from the queue.
/// 
/// If the item to be removed is currently playing, has the same effect as -advanceToNextItem.
/// 
/// - Parameter item: The item to be removed.
- (void)removeItem:(AVPlayerItem *)item NS_SWIFT_NONISOLATED;

/// Removes all items from the queue.
/// 
/// Stops playback by the target.
- (void)removeAllItems NS_SWIFT_NONISOLATED;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVPlayer.h>
#endif
