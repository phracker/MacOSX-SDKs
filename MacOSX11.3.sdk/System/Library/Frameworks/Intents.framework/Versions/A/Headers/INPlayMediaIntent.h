//
//  INPlayMediaIntent.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INPlaybackQueueLocation.h>
#import <Intents/INPlaybackRepeatMode.h>

@class INBooleanResolutionResult;
@class INMediaItem;
@class INMediaItemResolutionResult;
@class INMediaSearch;
@class INPlayMediaMediaItemResolutionResult;
@class INPlayMediaPlaybackSpeedResolutionResult;
@class INPlaybackQueueLocationResolutionResult;
@class INPlaybackRepeatModeResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0), tvos(14.0))
API_UNAVAILABLE(macos)
@interface INPlayMediaIntent : INIntent

- (instancetype)initWithMediaItems:(nullable NSArray<INMediaItem *> *)mediaItems
                    mediaContainer:(nullable INMediaItem *)mediaContainer
                      playShuffled:(nullable NSNumber *)playShuffled
                playbackRepeatMode:(INPlaybackRepeatMode)playbackRepeatMode
                    resumePlayback:(nullable NSNumber *)resumePlayback
             playbackQueueLocation:(INPlaybackQueueLocation)playbackQueueLocation
                     playbackSpeed:(nullable NSNumber *)playbackSpeed
                       mediaSearch:(nullable INMediaSearch *)mediaSearch NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(13.0), watchos(6.0), macosx(10.15));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INMediaItem *> *mediaItems;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INMediaItem *mediaContainer;

// An NSNumber representing a boolean value where true indicates that the media should be shuffled.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *playShuffled NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPlaybackRepeatMode playbackRepeatMode;

// An NSNumber representing a boolean value where true indicates that the media should be resumed.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *resumePlayback NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPlaybackQueueLocation playbackQueueLocation API_AVAILABLE(ios(13.0), watchos(6.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *playbackSpeed NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(13.0), watchos(6.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INMediaSearch *mediaSearch API_AVAILABLE(ios(13.0), watchos(6.0));

@end

@class INPlayMediaIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INPlayMediaIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(12.0), watchos(5.0), tvos(14.0))
API_UNAVAILABLE(macos)
@protocol INPlayMediaIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INPlayMediaIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INPlayMediaIntentResponse containing the details of the result of having executed the intent

 @see  INPlayMediaIntentResponse
 */

- (void)handlePlayMedia:(INPlayMediaIntent *)intent
             completion:(void (^)(INPlayMediaIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INPlayMediaIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INPlayMediaIntentResponse
 */

- (void)confirmPlayMedia:(INPlayMediaIntent *)intent
              completion:(void (^)(INPlayMediaIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveMediaItemsForPlayMedia:(INPlayMediaIntent *)intent
                    withCompletion:(void (^)(NSArray<INPlayMediaMediaItemResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveMediaItems(for:with:)) API_AVAILABLE(ios(13.0), watchos(6.0));

- (void)resolvePlayShuffledForPlayMedia:(INPlayMediaIntent *)intent
                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePlayShuffled(for:with:)) API_AVAILABLE(ios(13.0), watchos(6.0));

- (void)resolvePlaybackRepeatModeForPlayMedia:(INPlayMediaIntent *)intent
                    withCompletion:(void (^)(INPlaybackRepeatModeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePlaybackRepeatMode(for:with:)) API_AVAILABLE(ios(13.0), watchos(6.0));

- (void)resolveResumePlaybackForPlayMedia:(INPlayMediaIntent *)intent
                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveResumePlayback(for:with:)) API_AVAILABLE(ios(13.0), watchos(6.0));

- (void)resolvePlaybackQueueLocationForPlayMedia:(INPlayMediaIntent *)intent
                    withCompletion:(void (^)(INPlaybackQueueLocationResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePlaybackQueueLocation(for:with:)) API_AVAILABLE(ios(13.0), watchos(6.0));

- (void)resolvePlaybackSpeedForPlayMedia:(INPlayMediaIntent *)intent
                    withCompletion:(void (^)(INPlayMediaPlaybackSpeedResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePlaybackSpeed(for:with:)) API_AVAILABLE(ios(13.0), watchos(6.0));

@end

NS_ASSUME_NONNULL_END
