#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIViewControllerTransitionCoordinator.h>)
//
//  UIViewControllerTransitionCoordinator.h
//  UIKit
//
//  Copyright (c) 2013-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>

// An object that conforms to this protocol provides descriptive information about an active
// view controller transition.
NS_ASSUME_NONNULL_BEGIN

typedef NSString * UITransitionContextViewControllerKey NS_TYPED_ENUM;
typedef NSString * UITransitionContextViewKey NS_TYPED_ENUM;

@protocol UIViewControllerTransitionCoordinatorContext <NSObject>

// Most of the time isAnimated will be YES. For custom transitions that use the
// new UIModalPresentationCustom presentation type we invoke the
// animateTransition: even though the transition is not animated. (This allows
// the custom transition to add or remove subviews to the container view.)
@property(nonatomic, readonly, getter=isAnimated) BOOL animated;

// A modal presentation style whose transition is being customized or UIModaPresentationNone if this is not a modal presentation
// or dismissal.
@property(nonatomic, readonly) UIModalPresentationStyle presentationStyle;

/// initiallyInteractive indicates whether the transition was initiated as an interactive transition.
/// It never changes during the course of a transition.
/// It can only be YES if isAnimated is YES.
///If it is NO, then isInteractive can only be YES if isInterruptible is YES
@property(nonatomic, readonly) BOOL initiallyInteractive;
@property(nonatomic,readonly) BOOL isInterruptible API_AVAILABLE(ios(10.0));

// Interactive transitions have non-interactive segments. For example, they all complete non-interactively. Some interactive transitions may have
// intermediate segments that are not interactive.
@property(nonatomic, readonly, getter=isInteractive) BOOL interactive;

// isCancelled is usually NO. It is only set to YES for an interactive transition that was cancelled.
@property(nonatomic, readonly, getter=isCancelled) BOOL cancelled;

// The full expected duration of the transition if it is run non-interactively. 
@property(nonatomic, readonly) NSTimeInterval transitionDuration;

// These three methods are potentially meaningful for interactive transitions that are
// completing. It reports the percent complete of the transition when it moves
// to the non-interactive completion phase of the transition.
@property(nonatomic, readonly) CGFloat percentComplete;
@property(nonatomic, readonly) CGFloat completionVelocity;
@property(nonatomic, readonly) UIViewAnimationCurve completionCurve;

// Currently only two keys are defined by the system:
//   UITransitionContextToViewControllerKey
//   UITransitionContextFromViewControllerKey
- (nullable __kindof UIViewController *)viewControllerForKey:(UITransitionContextViewControllerKey)key;

// Currently only two keys are defined by the system:
//   UITransitionContextToViewKey
//   UITransitionContextFromViewKey
- (nullable __kindof UIView *)viewForKey:(UITransitionContextViewKey)key API_AVAILABLE(ios(8.0));

// The view in which the animated transition is taking place.
@property(nonatomic, readonly) UIView *containerView;

// This is either CGAffineTransformIdentity (indicating no rotation), or a rotation transform of +90, -90, or 180.
@property(nonatomic, readonly) CGAffineTransform targetTransform API_AVAILABLE(ios(8.0));

@end

// An object conforming to this protocol is returned by -[UIViewController
// transitionCoordinator] when an active transition or presentation/dismissal is
// in flight. A container controller may not vend such an object. This is an
// ephemeral object that is released after the transition completes and the
// last callback has been made.

@protocol UIViewControllerTransitionCoordinator <UIViewControllerTransitionCoordinatorContext>


// Any animations specified will be run in the same animation context as the
// transition. If the animations are occurring in a view that is a not
// descendent of the containerView, then an ancestor view in which all of the
// animations are occuring should be specified.  The completionBlock is invoked
// after the transition completes. (Note that this may not be after all the
// animations specified by to call complete if the duration is not inherited.)
// It is perfectly legitimate to only specify a completion block. This method
// returns YES if the animations are successfully queued to run. The completions
// may be run even if the animations are not. Note that for transitioning
// animators that are not implemented with UIView animations, the alongside
// animations will be run just after their animateTransition: method returns.
//
- (BOOL)animateAlongsideTransition:(void (^ __nullable)(id <UIViewControllerTransitionCoordinatorContext>context))animation
                        completion:(void (^ __nullable)(id <UIViewControllerTransitionCoordinatorContext>context))completion;

// This alternative API is needed if the view is not a descendent of the container view AND you require this animation
// to be driven by a UIPercentDrivenInteractiveTransition interaction controller.
- (BOOL)animateAlongsideTransitionInView:(nullable UIView *)view
                               animation:(void (^ __nullable)(id <UIViewControllerTransitionCoordinatorContext>context))animation
                              completion:(void (^ __nullable)(id <UIViewControllerTransitionCoordinatorContext>context))completion;

// When a transition changes from interactive to non-interactive then handler is
// invoked. The handler will typically then do something depending on whether or
// not the transition isCancelled. Note that only interactive transitions can
// be cancelled and all interactive transitions complete as non-interactive
// ones. In general, when a transition is cancelled the view controller that was
// appearing will receive a viewWillDisappear: call, and the view controller
// that was disappearing will receive a viewWillAppear: call.  This handler is
// invoked BEFORE the "will" method calls are made.
- (void)notifyWhenInteractionEndsUsingBlock: (void (^)(id <UIViewControllerTransitionCoordinatorContext>context))handler API_DEPRECATED_WITH_REPLACEMENT("notifyWhenInteractionChangesUsingBlock", ios(7.0, 10.0));

// This method behavior is identical to the method above. On 10.0, however, the behavior has
// changed slightly to account for the fact that transitions can be interruptible. For interruptible transitions
// The block may be called multiple times. It is called each time the transition moves from an interactive to a 
// non-interactive state and vice-versa. The block is now also retained until the transition has completed.
- (void)notifyWhenInteractionChangesUsingBlock: (void (^)(id <UIViewControllerTransitionCoordinatorContext>context))handler API_AVAILABLE(ios(10.0));

@end

@interface UIViewController(UIViewControllerTransitionCoordinator)

// The default implementation will return a transition coordinator if called during
// an active presentation or dismissal. Otherwise it will ask the parent view
// controller. This method, if overridden, can first check if there is an
// appropriate transition coordinator to return, otherwise it should call
// super. Only custom container view controllers should ever need to override
// this method.
@property(nonatomic, readonly, nullable) id <UIViewControllerTransitionCoordinator> transitionCoordinator API_AVAILABLE(ios(7.0));
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIViewControllerTransitionCoordinator.h>
#endif
