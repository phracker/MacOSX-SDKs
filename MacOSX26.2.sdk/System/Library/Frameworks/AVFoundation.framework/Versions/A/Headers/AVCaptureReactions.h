#if !__has_include(<AVFCapture/AVCaptureReactions.h>)
/*
	File:  AVCaptureReactions.h
 
	Framework:  AVFoundation
 
	Copyright 2022-2023 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <CoreMedia/CoreMedia.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @group AVCaptureReactionType string constants
 
 @discussion
    Constants indicating the type of reaction that can be performed in an effect.
 */
typedef NSString *AVCaptureReactionType NS_TYPED_ENUM API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureReactionTypeThumbsUp
 @abstract
    Indicates a reaction which features a thumbs-up symbol.
 */
AVF_EXPORT AVCaptureReactionType AVCaptureReactionTypeThumbsUp API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureReactionTypeThumbsDown
 @abstract
 Indicates a reaction which features a thumbs-down symbol.
 */
AVF_EXPORT AVCaptureReactionType AVCaptureReactionTypeThumbsDown API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureReactionTypeBalloons
 @abstract
 Indicates a reaction which features balloons rising through the scene.
 */
AVF_EXPORT AVCaptureReactionType AVCaptureReactionTypeBalloons API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureReactionTypeHeart
 @abstract
 Indicates a reaction which features one or more heart symbols.
 */
AVF_EXPORT AVCaptureReactionType AVCaptureReactionTypeHeart API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureReactionTypeFireworks
 @abstract
 Indicates a reaction which features fireworks bursting in the background.
 */
AVF_EXPORT AVCaptureReactionType AVCaptureReactionTypeFireworks API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureReactionTypeRain
 @abstract
 Indicates a reaction which features a dark and stormy night.
 */
AVF_EXPORT AVCaptureReactionType AVCaptureReactionTypeRain API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureReactionTypeConfetti
 @abstract
 Indicates a reaction which features festive spots of color falling through the scene.
 */
AVF_EXPORT AVCaptureReactionType AVCaptureReactionTypeConfetti API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @constant AVCaptureReactionTypeLasers
 @abstract
 Indicates a reaction which features a bright laser display projecting into the scene.
 */
AVF_EXPORT AVCaptureReactionType AVCaptureReactionTypeLasers API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @function	AVCaptureReactionSystemImageNameForType
 @abstract
    Returns the name for UIImage or NSImage systemImageNamed: method to obtain the recommended iconography for a specified reaction type.
*/
AVF_EXPORT NSString *AVCaptureReactionSystemImageNameForType(AVCaptureReactionType reactionType) NS_SWIFT_NAME(getter:AVCaptureReactionType.systemImageName(self:)) API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @class AVCaptureReactionEffectState
 @abstract
    Reports the state of a reaction performed on an AVCaptureDevice.
 
 @discussion
    AVCaptureReactionEffectState may be obtained by calling -[AVCaptureDevice reactionEffectsInProgress].  When -[AVCaptureDevice canPerformReactionEffects] returns YES, new entries are added either by calling -[AVCaptureDevice performEffectForReaction:], or by gesture detection in the capture stream when AVCaptureDevice.reactionEffectGesturesEnabled.  The effect rendering is done before frames are given to the capture client, and these status objects let you know when these effects are performed.
 */
API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureReactionEffectState : NSObject

/*!
 @property reactionType
 @abstract
    Indicates the reaction which is running.
 
 @discussion
    There may be multiple reactions of the same type at a given time.  Some may come from gesture detection, some may come from calls to -[AVCaptureDevice performReactionEffect:]
 */
@property(nonatomic, readonly) AVCaptureReactionType reactionType API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property startTime
 @abstract
    Provides the presentation time of the first frame where the effect is being rendered.
 */
@property(nonatomic, readonly) CMTime startTime API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property endTime
 @abstract
    Provides the presentation time of the frame following the last frame where the effect is seen.
 
 @discussion
    Will be kCMTimeInvalid while the effect is in progress, but will be updated to a valid time when the reaction effect completes and the AVCaptureReactionEffectState is removed from -[AVCaptureDevice reactionEffectsInProgress]. (If using NSKeyValueObservingOptionOld, you can access completed effects with valid end times via NSKeyValueChangeOldKey.)
 */
@property(nonatomic, readonly) CMTime endTime API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureReactions.h>
#endif
