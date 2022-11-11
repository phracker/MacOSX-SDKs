#if !__has_include(<AVFCore/AVPlayerLooper.h>)
/*
 File:  AVPlayerLooper.h

	Framework:  AVFoundation

	Copyright 2016-2018 Apple Inc. All rights reserved.

 */

/*!
 @class AVPlayerLooper

 @abstract
    AVPlayerLooper is a helper object that repeatedly plays an AVPlayerItem with an AVQueuePlayer

 @discussion
    The same result can be accomplished with AVQueuePlayer directly, but AVPlayerLooper provides a simpler interface to loop a single AVPlayerItem with an option to specify a time range. AVPlayerLooper only supports looping for forward playback (positive player rate). Behavior is undefined for negative player rate.

	Note that the transition at the loop point is not guaranteed to be gapless.

    Sample usage code:
    // Create player and configure
    AVQueuePlayer *player = [[AVQueuePlayer alloc] init];
    AVPlayerLayer *playerLayer = [AVPlayerLayer playerLayerWithPlayer:player];
    [player pause];
    // Create looping item
    AVPlayerItem* itemToLoop = [AVPlayerItem playerItemWithURL:@“loop.mov”];
    // Create looping helper object. Loop item segment from 5sec to 7sec
    AVPlayerLooper* looper = [AVPlayerLooper playerLooperWithPlayer:player templateItem:itemToLoop timeRange:CMTimeRangeMake(CMTimeMake(5000,1000), CMTimeMake(2000,1000))];
    // Perform any other set up operations like setting AVPlayerItemDataOutputs on the looping item replicas
    // Start playback
    [player play];
    // itemToLoop between 5s and 7s plays repeatedly
    ....
    // To end the looping
    [looper disableLooping];
    // Player will play through the end of the current looping item
 */


#import <AVFoundation/AVBase.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVPlayer.h>
#import <AVFoundation/AVPlayerItem.h>

@class AVPlayerLooperInternal;

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum AVPlayerLooperStatus
 @abstract
    These constants are returned by the AVPlayerLooper status property to indicate whether it can successfully accomplish looping playback.
 @constant AVPlayerLooperStatusUnknown
    Indicates that the status of the looper is not yet known.
 @constant AVPlayerLooperStatusReady
    Indicates that the looper is ready for looping playback.
 @constant AVPlayerLooperStatusFailed
    Indicates that the looper is not able to perform looping playback because of an error. The error is described by the value of the error property.
 @constant AVPlayerLooperStatusCancelled
    Indicates that the looper is no longer looping because -disableLooping was invoked.
 */
typedef NS_ENUM(NSInteger, AVPlayerLooperStatus) {
    AVPlayerLooperStatusUnknown = 0,
    AVPlayerLooperStatusReady = 1,
    AVPlayerLooperStatusFailed = 2,
    AVPlayerLooperStatusCancelled = 3
};

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos)
@interface AVPlayerLooper : NSObject
{
@private
    AVPlayerLooperInternal *_looper;
}
AV_INIT_UNAVAILABLE

/*!
 @method playerLooperWithPlayer:templateItem:timeRange:
 @abstract
    Returns an instance of AVPlayerLooper to loop specified AVPlayerItem within the specified time range with specified AVQueuePlayer.
 @param player
    Must not be nil
 @param itemToLoop
    Must not be nil
 @param loopRange
    Playback time range in [0, itemToLoop's duration]. kCMTimeRangeInvalid means [0, itemToLoop's duration].
 @result
    An instance of AVPlayerLooper.
 @discussion
    The specified AVPlayerItem will be used as a template to generate at least 3 AVPlayerItem replicas and the replicas will be inserted into specified AVQueuePlayer's play queue to accomplish the looping playback. The specified AVPlayerItem should have its asset's duration property loaded beforehand so looping setup work would not be blocked until the duration value is known. Otherwise, AVPlayerLooper's status property is  AVPlayerLooperStatusUnknown until the duration property is loaded. The specified AVPlayerItem will not be used in the actual looping playback. Furthermore, AVPlayerItem replicas will be generated at initialization time so any changes made to the specified AVPlayerItem's property afterwards will not be reflected in the replicas used for looping playback. Specified CMTimeRange will limit each item loop iteration to playing within the specified time range. To play from beginning and the whole duration of the item, specify kCMTimeRangeInvalid for the range parameter. Time range will be accomplished by seeking to range start time and setting AVPlayerItem's forwardPlaybackEndTime property on the looping item replicas. Client should not modify AVQueuePlayer's play queue while AVPlayerLooper is performing the looping. AVPlayerLooper will insert the replica items before any existing items in the specified AVQueuePlayer's play queue and change the actionAtItemEnd to AVPlayerActionAtItemEndAdvance if required. AVQueuePlayer's play queue and actionAtItemEnd will be restored when -disableLooping method is called and then current looping item replicas completes playback or when AVPlayerLooper is destroyed. While AVPlayerLooper is being initialized, the specified AVQueuePlayer will be paused (rate of 0.0) if necessary and the original player rate will be restored after initialization completes. The client shall set the specified AVQueuePlayer's rate to 0 beforehand if additional set-up work needs to be performed after AVPlayerLooper initialization and before starting looping playback. An NSInvalidArgumentException will be raised if the player and template item are not specified or the template item has a 0 duration. An NSInvalidArgumentException will be raised if a valid time range has a duration of 0 or is not contained within time 0 and duration of the templateItem.
*/
+ (instancetype)playerLooperWithPlayer:(AVQueuePlayer *)player templateItem:(AVPlayerItem *)itemToLoop timeRange:(CMTimeRange)loopRange;

/*!
 @method playerLooperWithPlayer:templateItem:
 @abstract
    Returns an instance of AVPlayerLooper to loop specified AVPlayerItem with specified AVQueuePlayer.
 @param player
    Must not be nil
 @param itemToLoop
    Must not be nil
 @result
    An instance of AVPlayerLooper.
 @discussion
    Equivalent to +playerLooperWithPlayer:templateItem:timeRange: and passing in kCMTimeRangeInvalid for timeRange parameter.
*/
+ (instancetype)playerLooperWithPlayer:(AVQueuePlayer *)player templateItem:(AVPlayerItem *)itemToLoop;

/*!
 @method initWithPlayer:templateItem:timeRange:
 @abstract
    Initializes an instance of AVPlayerLooper to loop specified AVPlayerItem within the specified time range with specified AVQueuePlayer.
 @param player
    Must not be nil
 @param itemToLoop
    Must not be nil
 @param loopRange
    Playback time range in [0, itemToLoop's duration]. kCMTimeRangeInvalid means [0, itemToLoop's duration].
 @result
    An initialized AVPlayerLooper.
 @discussion
    The specified AVPlayerItem will be used as a template to generate at least 3 AVPlayerItem replicas and the replicas will be inserted into specified AVQueuePlayer's play queue to accomplish the looping playback. The specified AVPlayerItem should have its asset's duration property loaded beforehand so looping setup work would not be blocked until the duration value is known. Otherwise, AVPlayerLooper's status property is  AVPlayerLooperStatusUnknown until the duration property is loaded. The specified AVPlayerItem will not be used in the actual looping playback. Furthermore, AVPlayerItem replicas will be generated at initialization time so any changes made to the specified AVPlayerItem's property afterwards will not be reflected in the replicas used for looping playback. Specified CMTimeRange will limit each item loop iteration to playing within the specified time range. To play from beginning and the whole duration of the item, specify kCMTimeRangeInvalid for the range parameter. Time range will be accomplished by seeking to range start time and setting AVPlayerItem's forwardPlaybackEndTime property on the looping item replicas. Client should not modify AVQueuePlayer's play queue while AVPlayerLooper is performing the looping. AVPlayerLooper will insert the replica items before any existing items in the specified AVQueuePlayer's play queue and change the actionAtItemEnd to AVPlayerActionAtItemEndAdvance if required. AVQueuePlayer's play queue and actionAtItemEnd will be restored when -disableLooping method is called and then current looping item replicas completes playback or when AVPlayerLooper is destroyed. While AVPlayerLooper is being initialized, the specified AVQueuePlayer will be paused (rate of 0.0) if necessary and the original player rate will be restored after initialization completes. The client shall set the specified AVQueuePlayer's rate to 0 beforehand if additional set-up work needs to be performed after AVPlayerLooper initialization and before starting looping playback. An NSInvalidArgumentException will be raised if the player and template item are not specified or the template item has a 0 duration. An NSInvalidArgumentException will be raised if a valid time range has a duration of 0 or is not contained within time 0 and duration of the templateItem.
 */
- (instancetype)initWithPlayer:(AVQueuePlayer *)player templateItem:(AVPlayerItem *)itemToLoop timeRange:(CMTimeRange)loopRange NS_DESIGNATED_INITIALIZER;

/*!
 @property status
 @abstract
    The ability of the receiver to be used for looping playback.
 @discussion
    The value of this property is an AVPlayerLooperStatus that indicates whether the receiver is ready for looping playback. When the value of this property is AVPlayerStatusFailed, the receiver can no longer be used for playback and a new instance needs to be created in its place. When this happens, clients can check the value of the error property to determine the nature of the failure. This property is key value observable.
 */
@property (readonly) AVPlayerLooperStatus status;

/*!
 @property error
 @abstract
    If the receiver's status is AVPlayerLooperStatusFailed, this describes the error that caused the failure.
 @discussion
    The value of this property is a NSError that describes what caused the receiver to not be able to perform looping playback. If the receiver's status is not AVPlayerLooperStatusFailed, the value of this property is nil.
 */
@property (readonly, nullable) NSError *error;

/*!
 @method disableLooping
 @abstract
    Disables the item looping
 @discussion
    AVPlayerLooper will stop performing player queue operations for looping and let the current looping item replica play to the end. The player's original actionAtItemEnd property will be restored afterwards. After this method is called, the value of the receiver's status property will be AVPlayerLooperStatusCancelled.
 */
- (void)disableLooping;

/*!
 @property loopCount
 @abstract
    Number of times the specified AVPlayerItem has been played
 @discussion
    Starts at 0 and increments when the player starts playback of the AVPlayerItem again. This property is key value observable.
 */
@property (readonly) NSInteger loopCount;

/*!
 @property loopingPlayerItems
 @abstract
    Returns an array containing replicas of specified AVPlayerItem used to accomplish the looping
 @discussion
    AVPlayerLooper creates replicas of the template AVPlayerItem using -copyWithZone: and inserts the replicas in the specified AVQueuePlayer to accomplish the looping. The AVPlayerItem replicas are for informational purposes and to allow the client to apply properties that are not transferred from the template AVPlayerItem to the replicas. The client can determine the number of replicas created and can listen for notifications and property changes from the replicas if desired. AVPlayerItemOutputs and AVPlayerItemMediaDataCollectors are not transferred to the replicas so the client should add them to each replica if desired. The client shall not modify the properties on the replicas that would disrupt looping playback. Examples of such properties are playhead time/date, selected media option, and forward playback end time. This property is key value observable.
 @result
    Array containing replicas of specified AVPlayerItem
 */
@property (nonatomic, readonly) NSArray<AVPlayerItem *> *loopingPlayerItems;

@end

NS_ASSUME_NONNULL_END


#else
#import <AVFCore/AVPlayerLooper.h>
#endif
