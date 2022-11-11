//
//  SCNAnimation.h
//  SceneKit
//
//  Copyright © 2012-2021 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

#import <QuartzCore/QuartzCore.h>

@class SCNAnimation, SCNAnimationEvent, SCNAnimationPlayer;
@protocol SCNAnimatable;

@protocol SCNAnimation <NSObject>
@end

#import <SceneKit/SCNCAAnimationExtensions.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^SCNAnimationDidStartBlock)(SCNAnimation *animation, id <SCNAnimatable> receiver);
typedef void (^SCNAnimationDidStopBlock)(SCNAnimation *animation, id <SCNAnimatable> receiver, BOOL completed);

SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNTimingFunction : NSObject <NSSecureCoding>
+ (SCNTimingFunction *)functionWithTimingMode:(SCNActionTimingMode)timingMode;
+ (SCNTimingFunction *)functionWithCAMediaTimingFunction:(CAMediaTimingFunction *)caTimingFunction;
@end

/*!
 @protocol SCNAnimatable
 @abstract The SCNAnimatable protocol defines an animatable property. Objects that implement this protocol can be animated through these methods.
 */
@protocol SCNAnimatable <NSObject>

/*!
 @method addAnimation:forKey:
 @abstract Adds and runs an animation
 @param animation Added animation.
 @param key May be any string such that only one animation per unique key is added per animatable object.
 @discussion Only SCNAnimation (preferred), CABasicAnimation, CAKeyframeAnimation and CAAnimationGroup are supported.
 The animation starts playing right away. The animation is automatically removed on completion unless if removedOnCompletion is explicitly set to NO. 
 @seealso -[id <SCNAnimation> removedOnCompletion]
 */
- (void)addAnimation:(id <SCNAnimation>)animation forKey:(nullable NSString *)key;

/*!
 @method addAnimationPlayer:forKey:
 @abstract Add an animation player.
 @param player Added animation player.
 @param key May be any string such that only one animation per unique key is added per animatable object.
 @discussion The animation player is not removed automatically on completion.
 The animation doesn't start playing immediatelly. Call "play" on the player to start playing it.
 @seealso -[SCNAnimationPlayer play]
 */
- (void)addAnimationPlayer:(SCNAnimationPlayer *)player forKey:(nullable NSString *)key API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @method removeAllAnimations
 @abstract Remove all animations.
 */
- (void)removeAllAnimations;

/*!
 @method removeAllAnimationsWithBlendOutDuration
 @abstract Smoothly remove all animations.
 @param duration The blend out duration used to remove the animation.
 */
- (void)removeAllAnimationsWithBlendOutDuration:(CGFloat)duration API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/*!
 @method removeAnimationForKey
 @abstract Remove the animation with the given identifier.
 @param key The identifier for the animation to remove.
 */
- (void)removeAnimationForKey:(NSString *)key;

/*!
 @method removeAnimationForKey:blendOutDuration:
 @abstract Smoothly remove the animation with the given identifier.
 @param key The identifier for the animation to remove.
 @param duration The blend out duration used to remove the animation.
 */
- (void)removeAnimationForKey:(NSString *)key blendOutDuration:(CGFloat)duration API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property animationKeys
 @abstract Returns an array containing the keys of all animations currently attached to the receiver.
 */
@property(readonly) NSArray<NSString *> *animationKeys;

/*!
 @method animationPlayerForKey:
 @abstract Returns the animation player with the given identifier
 @param key The identifier for the animation player to retrieve.
 @discussion This will return nil if no such animation player exists.
 */
- (nullable SCNAnimationPlayer *)animationPlayerForKey:(NSString *)key API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));


// Deprecated

/*!
 @method removeAnimationForKey:fadeOutDuration:
 @abstract Smoothly remove the animation with the given identifier.
 @param key The identifier for the animation to remove.
 @param duration The fade out duration used to remove the animation.
 */
- (void)removeAnimationForKey:(NSString *)key fadeOutDuration:(CGFloat)duration API_DEPRECATED_WITH_REPLACEMENT("-removeAnimationForKey:blendOutDuration:", macos(10.10, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @method animationForKey:
 @abstract Returns the animation with the given identifier
 @param key The identifier for the animation to retrieve.
 @discussion This will return nil if no such animation exists.
 Attempting to modify any properties of the returned object will result in undefined behavior.
 */
- (nullable CAAnimation *)animationForKey:(NSString *)key API_DEPRECATED_WITH_REPLACEMENT("-animationPlayerForKey:", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0));

/*!
 @method pauseAnimationForKey:
 @abstract Pause the animation with the given identifier.
 @param key The identifier for the animation to pause.
 */
- (void)pauseAnimationForKey:(NSString *)key API_DEPRECATED("Use -[SCNAnimationPlayer setPaused:] instead", macos(10.9, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @method resumeAnimationForKey:
 @abstract Resume the animation with the given identifier.
 @param key The identifier for the animation to resume.
 */
- (void)resumeAnimationForKey:(NSString *)key API_DEPRECATED("Use -[SCNAnimationPlayer setPaused:] instead", macos(10.9, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @method setSpeed:forAnimationKey:
 @abstract Update the animation speed of the animation with the given identifier.
 @param speed The new speed of the animation.
 @param key The identifier for the animation to update.
 */
- (void)setSpeed:(CGFloat)speed forAnimationKey:(NSString *)key API_DEPRECATED("Use -[SCNAnimationPlayer setSpeed:] instead", macos(10.12, 10.13), ios(10.0, 11.0), tvos(10.0, 11.0), watchos(3.0, 4.0));

/*!
 @method isAnimationForKeyPaused:
 @abstract Returns whether the animation for the specified identifier is paused.
 @param key The identifier for the animation to query.
 */
- (BOOL)isAnimationForKeyPaused:(NSString *)key API_DEPRECATED("Use -[SCNAnimationPlayer paused] instead", macos(10.9, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

@end



/**
 SCNAnimation represents an animation that targets a specific key path.
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNAnimation : NSObject <SCNAnimation, NSCopying, NSSecureCoding>


/*!
 Initializers
 */

/**
 Loads and returns an animation loaded from the specified URL.
 
 @param animationUrl The url to load.
 */
+ (SCNAnimation *)animationWithContentsOfURL:(NSURL *)animationUrl;

/**
 Loads and returns the animation with the specified name in the current application bundle.

 @param animationName The name of the animation to load.
 */
+ (SCNAnimation *)animationNamed:(NSString *)animationName;

// bridge with Core Animation
/**
 Returns a SCNAnimation initialized from a CAAnimation.

 @param caAnimation The CAAnimation to initialize from.
 @discussion Only CABasicAnimation, CAKeyframeAnimation and CAAnimationGroup are currently supported.
 */
+ (SCNAnimation *)animationWithCAAnimation:(CAAnimation *)caAnimation;



/*!
 Basic properties
 */

/**
 The duration of the animation in seconds. Defaults to 0.
 */
@property(nonatomic) NSTimeInterval duration;

/**
 The key-path describing the property to be animated for single-property animations, nil for animations targetting multiple nodes. defaults to nil.
 The key-path uses the KVC syntax. It's also possible to target a specific sub-node with the following syntax:
    /<node-name>.property1.property2.field    (field is optional, <node-name> is the name of the targeted node).
 */
@property(nonatomic, copy, nullable) NSString *keyPath;

/**
 A timing function defining the pacing of the animation. Defaults to nil indicating linear pacing.
 */
@property(nonatomic, retain) SCNTimingFunction *timingFunction;



/*!
 Blending
 */

/**
 Determines the receiver's blend-in duration.
 @discussion When the blendInDuration is greater than zero, the effect of the animation progressively increase from 0% to 100% during the specified duration.
 */
@property(nonatomic) NSTimeInterval blendInDuration;

/**
 Determines the receiver's blend-out duration.
 @discussion When the blendOutDuration is greater than zero, the effect of the animation progressively decrease from 100% to 0% at the end of the animation duration.
 */
@property(nonatomic) NSTimeInterval blendOutDuration;



/*!
 Animation behaviors
 */

/**
 When true, the animation is removed from the render tree once its active duration has passed. Defaults to YES. 
 */
@property(nonatomic, getter=isRemovedOnCompletion) BOOL removedOnCompletion;

/**
 When true, the animation is applied to the model tree once its active duration has passed. Defaults to NO.
 */
@property(nonatomic, getter=isAppliedOnCompletion) BOOL appliedOnCompletion;



/*!
 Repeat
 */

/**
 The repeat count of the object. May be fractional. Defaults to 0.
 */
@property(nonatomic) CGFloat repeatCount;
/**
 When true, the object plays backwards after playing forwards. Defaults to NO.
 */
@property(nonatomic) BOOL autoreverses;



/*!
 Delay and offset
 */

/**
 The relative delay to start the animation, in relation to its parent animation if applicable. Defaults to 0.
 @discussion This property is bridged with CoreAnimations's beginTime. However, for top level animations, startDelay is relative to the current time (unlike CAAnimation's beginTime that is absolute). So if a CAAnimation has a non-zero beginTime, startDelay is initialized as caAnimation.beginTime - CACurrentMediaTime().
 */
@property(nonatomic) NSTimeInterval startDelay;

/**
 Additional offset in active local time. i.e. to convert from parent
 time tp to active local time t: t = (tp - begin) * speed + offset.
 Defaults to 0.
 */
@property(nonatomic) NSTimeInterval timeOffset;



/*!
 Fill mode
 */

/**
 When true, the animation remains active after its active duration and evaluates to its end value. Defaults to NO.
 */
@property(nonatomic) BOOL fillsForward;

/**
 When true, the animation is active before its active duration and evaluates to its start value. Defaults to NO.
 */
@property(nonatomic) BOOL fillsBackward;

/**
 Determines whether the receiver is evaluated using the scene time or the system time. Defaults to NO.
 @discussion A scene-time based animation is evaluated using the "sceneTime" value of the renderer that renders the scene.
 The "sceneTime" base is typically used by players or editors that need to preview, edit and being able to change the evaluation time.
 @see SCNSceneSourceAnimationImportPolicyKey
 */
@property(nonatomic) BOOL usesSceneTimeBase;


/*!
 Notifications & events
 */

/**
 Called when the animation starts.
 */
@property(nonatomic, copy, nullable) SCNAnimationDidStartBlock animationDidStart;

/**
 Called when the animation either completes its active duration or
 is removed from the object it is attached to (i.e. the layer). The 'completed' argument of SCNAnimationDidStopBlock
 is true if the animation reached the end of its active duration without being removed.
 */
@property(nonatomic, copy, nullable) SCNAnimationDidStopBlock animationDidStop;

/**
 Specifies the animation events attached to the receiver.
 @see SCNAnimationEvent
 */
@property(nonatomic, copy, nullable) NSArray<SCNAnimationEvent *> *animationEvents;

/*!
 Additive and cumulative
 */

/**
 When true the value specified by the animation will be "added" to
 the current presentation value of the property to produce the new
 presentation value. The addition function is type-dependent, e.g.
 for affine transforms the two matrices are concatenated. Defaults to
 NO. */
@property(nonatomic, getter=isAdditive) BOOL additive;

/**
 The `cumulative' property affects how repeating animations produce
 their result. If true then the current value of the animation is the
 value at the end of the previous repeat cycle, plus the value of the
 current repeat cycle. If false, the value is simply the value
 calculated for the current repeat cycle. Defaults to NO. 
 */
@property(nonatomic, getter=isCumulative) BOOL cumulative;

@end



/**
 SCNAnimationPlayer let you control when and how to play and blend an animation
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNAnimationPlayer : NSObject  <SCNAnimatable, NSCopying, NSSecureCoding>

/**
 Initialize an animation player with an animation
 @param animation The animation to play
 */
+ (SCNAnimationPlayer *)animationPlayerWithAnimation:(SCNAnimation *)animation;

/**
 The played animation
 */
@property(nonatomic, readonly) SCNAnimation *animation;

/**
 The speed to play the animation at. Defaults to 1.0. Animatable
 */
@property(nonatomic) CGFloat speed;

/**
 Controls the influence of the played animation. When set to 1 the animation is applied without any blending. When set to less than 1, the animation value is blent with the current presentation value of the animated property. Defaults to 1.0. Animatable.
 */
@property(nonatomic) CGFloat blendFactor;

/**
 Specifies if the animation is paused. Defaults to NO.
 */
@property(nonatomic) BOOL paused;

/*!
 Actions
 */

/**
 Set paused to NO and restart playing from the beginning of the animation.
 */
- (void)play;

/**
 Stop the animation.
 */
- (void)stop;

/**
 Stop the animation and smoothly blend out the animation over the specified duration.
 */
- (void)stopWithBlendOutDuration:(NSTimeInterval)duration;

@end


/**
 Signature for the block executed when the animation event is triggered.
 */
typedef void (^SCNAnimationEventBlock)(id <SCNAnimation> animation, id animatedObject, BOOL playingBackward);


/**
 SCNAnimationEvent encapsulates a block to trigger at a specific time.
 */
SCN_EXPORT API_AVAILABLE(macos(10.9))
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

NS_ASSUME_NONNULL_END
