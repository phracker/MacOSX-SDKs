#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIViewPropertyAnimator.h>)
//
//  UIViewPropertyAnimator.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewAnimating.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITimingParameters.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(10.0)) NS_SWIFT_UI_ACTOR
@interface UIViewPropertyAnimator : NSObject <UIViewImplicitlyAnimating, NSCopying>

@property(nullable, nonatomic, copy, readonly) id <UITimingCurveProvider> timingParameters;

@property(nonatomic, readonly) NSTimeInterval duration;

/// Defaults to 0. This property is set when calling -[UIView startAnimationAfterDelay:].
@property(nonatomic, readonly) NSTimeInterval delay;

/// Defaults to YES. Raises if set on an active animator.
@property(nonatomic, getter=isUserInteractionEnabled) BOOL userInteractionEnabled;

/// Defaults to NO. Set if you need to manage the the hit-testing of animating view hierarchies
@property(nonatomic, getter=isManualHitTestingEnabled) BOOL manualHitTestingEnabled;

/// Defaults to YES. Raises if set on an active animator.
@property(nonatomic, getter=isInterruptible) BOOL interruptible;

/// Defaults to YES. Provides the ability for an animator to pause and scrub either linearly or using the animator’s current timing.
@property(nonatomic) BOOL scrubsLinearly API_AVAILABLE(ios(11.0));

/// Defaults to NO. Provides the ability for an animator to pause on completion instead of transitioning to the .inactive state.
@property(nonatomic) BOOL pausesOnCompletion API_AVAILABLE(ios(11.0));

- (instancetype)initWithDuration:(NSTimeInterval)duration timingParameters:(id <UITimingCurveProvider>)parameters NS_DESIGNATED_INITIALIZER;

/// All convenience initializers return an animator which is not running.
- (instancetype)initWithDuration:(NSTimeInterval)duration curve:(UIViewAnimationCurve)curve animations:(void (^ __nullable)(void))animations;
- (instancetype)initWithDuration:(NSTimeInterval)duration controlPoint1:(CGPoint)point1 controlPoint2:(CGPoint)point2 animations:(void (^ __nullable)(void))animations;
- (instancetype)initWithDuration:(NSTimeInterval)duration dampingRatio:(CGFloat)ratio animations:(void (^ __nullable)(void))animations;

/// @abstract This method provides compatibility with the old style [UIView
/// animationWithDuration:...]  method. It is also useful for controlling
/// how animations options are inherited.
/// @discussion Creates a UIViewPropertyAnimator, sets the duration, options, etc. And starts the
/// animation with the associated animation and completion blocks. The animator
/// returned is interruptible only if it is not called from within the execution
/// block of another animation (animator or legacy). Note that if it is called
/// within the execution block of another animation it will inherit the duration
/// and other characteristics of that animation UNLESS the appropriate override
/// options have been specified. Also note that if is called within the execution
/// block of another propertyAnimator that is interruptible, the implicit
/// animations defined by this call will be tracked by the outer
/// propertyAnimator.
+ (instancetype)runningPropertyAnimatorWithDuration:(NSTimeInterval)duration
                                              delay:(NSTimeInterval)delay
                                            options:(UIViewAnimationOptions)options
                                         animations:(void (^)(void))animations
                                         completion:(void (^ __nullable)(UIViewAnimatingPosition finalPosition))completion;

/// Animatable view properties that are set by the animation block will be
/// animated to their new values. The animations will commence at delayFactor *
/// animator.duration seconds into the animation. The duration of the animation
/// will be (1 - delayFactor) * animator.duration seconds.
- (void)addAnimations:(void (^)(void))animation delayFactor:(CGFloat)delayFactor;

/// Animatable view properties that are set by the animation block will be
/// animated to their new values. Starting an animator that does not contain any animation blocks
/// will start the animator in a transient paused state. While in this state, submitting an animation
/// block will automatically start animating any animatable view properties set therein. When the
/// animator is stopped, either naturally completing or explicitly, any animation blocks and completion
/// handlers are invalidated. Immediately calling `startAnimation` again on the animator, since there
/// are no animation blocks, will start the animator in a transient paused state.
- (void)addAnimations:(void (^)(void))animation;

- (void)addCompletion:(void (^)(UIViewAnimatingPosition finalPosition))completion;

/// Provides a means to continue an animation in either the forward or reversed
/// directions with new timing parameters and duration.  The durationFactor is in
/// terms of a unit duration defined by the originally specified duration of the
/// animator. It is used to specify the remaining time for the animation. When
/// called, it behaves as if the animation was started from its current position
/// with a new duration and timing parameters.
- (void)continueAnimationWithTimingParameters:(nullable id <UITimingCurveProvider>)parameters durationFactor:(CGFloat)durationFactor;


@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIViewPropertyAnimator.h>
#endif
