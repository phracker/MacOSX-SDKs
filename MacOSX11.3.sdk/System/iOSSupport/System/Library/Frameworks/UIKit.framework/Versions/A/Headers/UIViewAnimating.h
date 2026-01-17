#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIViewAnimating.h>)
//
//  UIViewAnimating.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

typedef NS_ENUM(NSInteger, UIViewAnimatingState)
{
    UIViewAnimatingStateInactive, // The animation is not executing.
    UIViewAnimatingStateActive,   // The animation is executing.
    UIViewAnimatingStateStopped,  // The animation has been stopped and has not transitioned to inactive.
} API_AVAILABLE(ios(10.0)) ;

typedef NS_ENUM(NSInteger, UIViewAnimatingPosition) {
    UIViewAnimatingPositionEnd,
    UIViewAnimatingPositionStart,
    UIViewAnimatingPositionCurrent,
} API_AVAILABLE(ios(10.0));


NS_ASSUME_NONNULL_BEGIN

@protocol UIViewAnimating <NSObject>

@property(nonatomic, readonly) UIViewAnimatingState state;

// Running indicates that the animation is running either in the forward or the reversed direction.
// The state of a running animation is always active.
@property(nonatomic, readonly, getter=isRunning) BOOL running;

// Reversed indicates that the animation is running in the reversed direction when running is YES.
// If running is NO, it indicates that it will run in the reversed direction when it is started.
@property(nonatomic, getter=isReversed) BOOL reversed;

// fractionComplete values are typically between 0 and 1. Some adopters may choose to give
// meaning to values less than zero and greater than 1 to facilitate over and
// undershooting.  The setter is usually a no-op when the animation is
// running. Adopters are free to change this if it makes sense. An adopter
// may also choose to only return a meaningful result for this property if it 
// is read while the animation is not running.
@property(nonatomic) CGFloat fractionComplete;  

// Starts the animation either from an inactive state, or if the animation has been paused.
- (void)startAnimation;

// Starts the animation after the given delay.
- (void)startAnimationAfterDelay:(NSTimeInterval)delay;

// Pauses an active, running animation, or start the animation as paused. This is different
// than stopping an animation.
- (void)pauseAnimation;

// Stops the animation.  The values of a view's animated property values are
// updated to correspond to the values that were last rendered. If
// withoutFinishing == YES, then the animator immediately becomes
// inactive. Otherwise it enters the stopped state and it is incumbent on the
// client to explicitly finish the animation by calling finishAnimationAtPosition:. Note
// when an animation finishes naturally this method is not called.
- (void)stopAnimation:(BOOL) withoutFinishing;

// This method may only be called if the animator is in the stopped state.
// The finalPosition argument should indicate the final values of the animated properties.
- (void)finishAnimationAtPosition:(UIViewAnimatingPosition)finalPosition;

@end

@protocol UITimingCurveProvider;

@protocol UIViewImplicitlyAnimating <UIViewAnimating>

@optional

- (void)addAnimations:(void (^)(void))animation delayFactor:(CGFloat)delayFactor;
- (void)addAnimations:(void (^)(void))animation;
- (void)addCompletion:(void (^)(UIViewAnimatingPosition finalPosition))completion;
- (void)continueAnimationWithTimingParameters:(nullable id <UITimingCurveProvider>)parameters durationFactor:(CGFloat)durationFactor;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIViewAnimating.h>
#endif
