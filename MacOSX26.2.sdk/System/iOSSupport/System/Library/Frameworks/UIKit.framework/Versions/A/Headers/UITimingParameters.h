#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITimingParameters.h>)
//
//  UITimingParameters.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITimingCurveProvider.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UICubicTimingParameters : NSObject  <UITimingCurveProvider>

@property(nonatomic, readonly) UIViewAnimationCurve animationCurve;
@property(nonatomic, readonly) CGPoint controlPoint1;
@property(nonatomic, readonly) CGPoint controlPoint2;

- (instancetype)init NS_DESIGNATED_INITIALIZER; // initializes with the default CA timing curve
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithAnimationCurve:(UIViewAnimationCurve)curve NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithControlPoint1:(CGPoint)point1 controlPoint2:(CGPoint)point2 NS_DESIGNATED_INITIALIZER;

@end


UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UISpringTimingParameters : NSObject  <UITimingCurveProvider>

@property(nonatomic, readonly) CGVector initialVelocity;

- (instancetype)init NS_DESIGNATED_INITIALIZER; // Initializes with the default system spring parameters

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

// Performs `animations` using a timing curve described by the motion of a
// spring. When `dampingRatio` is 1, the animation will smoothly decelerate to
// its final model values without oscillating. Damping ratios less than 1 will
// oscillate more and more before coming to a complete stop. You can use the
// initial spring velocity to specify how fast the object at the end of the
// simulated spring was moving before it was attached. It's a unit coordinate
// system, where 1 is defined as traveling the total animation distance in a
// second. So if you're changing an object's position by 200pt in this
// animation, and you want the animation to behave as if the object was moving
// at 100pt/s before the animation started, you'd pass 0.5. You'll typically
// want to pass 0 for the velocity. Velocity is specified as a vector for the
// convenience of animating position changes. For 1-dimensional properties
// the x-coordinate of the velocity vector is used.
- (instancetype)initWithDampingRatio:(CGFloat)ratio initialVelocity:(CGVector)velocity NS_DESIGNATED_INITIALIZER;

// Similar to initWithDampingRatio:initialVelocity: except this allows you to specify the spring constants for the underlying
// CASpringAnimation directly. The duration is computed assuming a small settling oscillation.
- (instancetype)initWithMass:(CGFloat)mass stiffness:(CGFloat)stiffness damping:(CGFloat)damping initialVelocity:(CGVector)velocity NS_DESIGNATED_INITIALIZER;

// Equivalent to initWithDampingRatio:initialVelocity: where the velocity is the zero-vector.
- (instancetype)initWithDampingRatio:(CGFloat)ratio;

// Similar to initWithMass:stiffness:damping:initialVelocity: except this
// creates a set of parameters that is specified by perceptual duration and
// bounce. The `duration` specified here is a perceptual duration that
// defines the pace of the spring. This is approximately equal to the settling
// duration, but for very bouncy springs, will be the duration of the period of
// oscillation for the spring. When `bounce` is 0, there are no bounces,
// positive values indicate increasing amounts of bounciness up to a maximum of
// 1.0 (corresponding to undamped oscillation), and negative values indicate
// overdamped springs with a minimum value of -1.0.
- (instancetype)initWithDuration:(NSTimeInterval)duration bounce:(CGFloat)bounce initialVelocity:(CGVector)velocity NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos);

// Equivalent to initWithDuration:bounce:initialVelocity: where the velocity
// is the zero-vector.
- (instancetype)initWithDuration:(NSTimeInterval)duration bounce:(CGFloat)bounce API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos);

@end


NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITimingParameters.h>
#endif
