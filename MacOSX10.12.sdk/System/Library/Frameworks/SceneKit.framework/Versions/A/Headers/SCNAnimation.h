//
//  SCNAnimation.h
//
//  Copyright (c) 2012-2016 Apple Inc. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @typedef SCNAnimationEventBlock
 @discussion Signature for the block executed when the animation event is triggered.
 */
typedef void (^SCNAnimationEventBlock)(CAAnimation *animation, id animatedObject, BOOL playingBackward);

/*!
 @class SCNAnimationEvent
 @abstract SCNAnimationEvent encapsulate a block to trigger at a specific time.
 */

API_AVAILABLE(macosx(10.9))
@interface SCNAnimationEvent : NSObject

/*!
 @method animationEventWithKeyTime:block:
 @abstract Returns an animation event instance
 @param time The relative time to trigger the event.
 @param eventBlock The block to call when the event is triggered.
 @discussion "time" is relative to animation duration and therefor it has to be a value in the range [0,1].
 */
+ (instancetype)animationEventWithKeyTime:(CGFloat)time block:(SCNAnimationEventBlock)eventBlock;

@end

/*!
 @protocol SCNAnimatable
 @abstract The SCNAnimatable protocol defines an animatable property. Objects that implement this protocol can be animated through these methods.
*/
@protocol SCNAnimatable <NSObject>

/*!
 @method addAnimation:forKey:
 @abstract Add an animation.
 @param animation Added animation.
 @param key May be any string such that only one animation per unique key is added per animatable object.
 */
- (void)addAnimation:(CAAnimation *)animation forKey:(nullable NSString *)key;

/*!
 @method removeAllAnimations
 @abstract Remove all animations.
 */
- (void)removeAllAnimations;

/*!
 @method removeAnimationForKey
 @abstract Remove the animation with the given identifier.
 @param key The identifier for the animation to remove.
 */
- (void)removeAnimationForKey:(NSString *)key;

/*!
 @method animationKeys
 @abstract Returns an array containing the keys of all animations currently attached to the receiver.
 */
@property(readonly) NSArray<NSString *> *animationKeys;

/*!
 @method animationForKey:
 @abstract Returns the animation with the given identifier
 @param key The identifier for the animation to retrieve.
 @discussion This will return nil if no such animation exists.
			 Attempting to modify any properties of the returned object will result in undefined behavior.
 */
- (nullable CAAnimation *)animationForKey:(NSString *)key;

/*!
 @method pauseAnimationForKey:
 @abstract Pause the animation with the given identifier.
 @param key The identifier for the animation to pause.
 */
- (void)pauseAnimationForKey:(NSString *)key API_AVAILABLE(macosx(10.9));

/*!
 @method resumeAnimationForKey:
 @abstract Resume the animation with the given identifier.
 @param key The identifier for the animation to resume.
 */
- (void)resumeAnimationForKey:(NSString *)key API_AVAILABLE(macosx(10.9));

/*!
 @method isAnimationForKeyPaused:
 @abstract Returns whether the animation for the specified identifier is paused.
 @param key The identifier for the animation to query.
 */
- (BOOL)isAnimationForKeyPaused:(NSString *)key API_AVAILABLE(macosx(10.9));

/*!
 @method removeAnimationForKey:fadeOutDuration:
 @abstract Smoothly remove the animation with the given identifier.
 @param key The identifier for the animation to remove.
 @param duration The fade out duration used to remove the animation.
 */
- (void)removeAnimationForKey:(NSString *)key fadeOutDuration:(CGFloat)duration API_AVAILABLE(macosx(10.10));

/*!
 @method setSpeed:forAnimationKey:
 @abstract Update the animation speed of the animation with the given identifier.
 @param speed The new speed of the animation.
 @param key The identifier for the animation to update.
 */
- (void)setSpeed:(CGFloat)speed forAnimationKey:(NSString *)key API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

@end

/*!
 @category CAAnimation (CAAnimation)
 @abstract Extends the CAAnimation class for SceneKit explicit animations.
 */
@interface CAAnimation (SceneKitAdditions)

/*!
 @property usesSceneTimeBase
 @abstract Determines whether the receiver is evaluated using the scene time or the system time. Defaults to NO.
 @discussion A scene-time based animation is evaluated using the "sceneTime" value of the renderer that renders the scene.
 */
@property BOOL usesSceneTimeBase;

/*!
 @property fadeInDuration
 @abstract Determines the receiver's fade-in duration.
 @discussion When the fadeInDuration is greater than zero, the effect of the animation progressively increase from 0% to 100% during the specified duration.
 */
@property CGFloat fadeInDuration API_AVAILABLE(macosx(10.9));
 
/*!
 @property fadeOutDuration
 @abstract Determines the receiver's fade-out duration.
 @discussion When the fadeOutDuration is greater than zero, the effect of the animation progressively decrease from 100% to 0% at the end of the animation duration.
 */
@property CGFloat fadeOutDuration API_AVAILABLE(macosx(10.9));

/*!
 @property animationEvents
 @abstract Specifies the animation events attached to the receiver.
 */
@property(nonatomic, copy, nullable) NSArray<SCNAnimationEvent *> *animationEvents API_AVAILABLE(macosx(10.9));

@end

NS_ASSUME_NONNULL_END
