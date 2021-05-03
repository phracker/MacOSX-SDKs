#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIView.h>)
//
//  UIView.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIResponder.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIAppearance.h>
#import <UIKit/UIDynamicBehavior.h>
#import <UIKit/NSLayoutConstraint.h>
#import <UIKit/UITraitCollection.h>
#import <UIKit/UIFocus.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIViewAnimationCurve) {
    UIViewAnimationCurveEaseInOut,         // slow at beginning and end
    UIViewAnimationCurveEaseIn,            // slow at beginning
    UIViewAnimationCurveEaseOut,           // slow at end
    UIViewAnimationCurveLinear,
};

typedef NS_ENUM(NSInteger, UIViewContentMode) {
    UIViewContentModeScaleToFill,
    UIViewContentModeScaleAspectFit,      // contents scaled to fit with fixed aspect. remainder is transparent
    UIViewContentModeScaleAspectFill,     // contents scaled to fill with fixed aspect. some portion of content may be clipped.
    UIViewContentModeRedraw,              // redraw on bounds change (calls -setNeedsDisplay)
    UIViewContentModeCenter,              // contents remain same size. positioned adjusted.
    UIViewContentModeTop,
    UIViewContentModeBottom,
    UIViewContentModeLeft,
    UIViewContentModeRight,
    UIViewContentModeTopLeft,
    UIViewContentModeTopRight,
    UIViewContentModeBottomLeft,
    UIViewContentModeBottomRight,
};

typedef NS_ENUM(NSInteger, UIViewAnimationTransition) {
    UIViewAnimationTransitionNone,
    UIViewAnimationTransitionFlipFromLeft,
    UIViewAnimationTransitionFlipFromRight,
    UIViewAnimationTransitionCurlUp,
    UIViewAnimationTransitionCurlDown,
};

typedef NS_OPTIONS(NSUInteger, UIViewAutoresizing) {
    UIViewAutoresizingNone                 = 0,
    UIViewAutoresizingFlexibleLeftMargin   = 1 << 0,
    UIViewAutoresizingFlexibleWidth        = 1 << 1,
    UIViewAutoresizingFlexibleRightMargin  = 1 << 2,
    UIViewAutoresizingFlexibleTopMargin    = 1 << 3,
    UIViewAutoresizingFlexibleHeight       = 1 << 4,
    UIViewAutoresizingFlexibleBottomMargin = 1 << 5
};

typedef NS_OPTIONS(NSUInteger, UIViewAnimationOptions) {
    UIViewAnimationOptionLayoutSubviews            = 1 <<  0,
    UIViewAnimationOptionAllowUserInteraction      = 1 <<  1, // turn on user interaction while animating
    UIViewAnimationOptionBeginFromCurrentState     = 1 <<  2, // start all views from current value, not initial value
    UIViewAnimationOptionRepeat                    = 1 <<  3, // repeat animation indefinitely
    UIViewAnimationOptionAutoreverse               = 1 <<  4, // if repeat, run animation back and forth
    UIViewAnimationOptionOverrideInheritedDuration = 1 <<  5, // ignore nested duration
    UIViewAnimationOptionOverrideInheritedCurve    = 1 <<  6, // ignore nested curve
    UIViewAnimationOptionAllowAnimatedContent      = 1 <<  7, // animate contents (applies to transitions only)
    UIViewAnimationOptionShowHideTransitionViews   = 1 <<  8, // flip to/from hidden state instead of adding/removing
    UIViewAnimationOptionOverrideInheritedOptions  = 1 <<  9, // do not inherit any options or animation type
    
    UIViewAnimationOptionCurveEaseInOut            = 0 << 16, // default
    UIViewAnimationOptionCurveEaseIn               = 1 << 16,
    UIViewAnimationOptionCurveEaseOut              = 2 << 16,
    UIViewAnimationOptionCurveLinear               = 3 << 16,
    
    UIViewAnimationOptionTransitionNone            = 0 << 20, // default
    UIViewAnimationOptionTransitionFlipFromLeft    = 1 << 20,
    UIViewAnimationOptionTransitionFlipFromRight   = 2 << 20,
    UIViewAnimationOptionTransitionCurlUp          = 3 << 20,
    UIViewAnimationOptionTransitionCurlDown        = 4 << 20,
    UIViewAnimationOptionTransitionCrossDissolve   = 5 << 20,
    UIViewAnimationOptionTransitionFlipFromTop     = 6 << 20,
    UIViewAnimationOptionTransitionFlipFromBottom  = 7 << 20,

    UIViewAnimationOptionPreferredFramesPerSecondDefault     = 0 << 24,
    UIViewAnimationOptionPreferredFramesPerSecond60          = 3 << 24,
    UIViewAnimationOptionPreferredFramesPerSecond30          = 7 << 24,
    
} API_AVAILABLE(ios(4.0));

typedef NS_OPTIONS(NSUInteger, UIViewKeyframeAnimationOptions) {
    UIViewKeyframeAnimationOptionLayoutSubviews            = UIViewAnimationOptionLayoutSubviews,
    UIViewKeyframeAnimationOptionAllowUserInteraction      = UIViewAnimationOptionAllowUserInteraction, // turn on user interaction while animating
    UIViewKeyframeAnimationOptionBeginFromCurrentState     = UIViewAnimationOptionBeginFromCurrentState, // start all views from current value, not initial value
    UIViewKeyframeAnimationOptionRepeat                    = UIViewAnimationOptionRepeat, // repeat animation indefinitely
    UIViewKeyframeAnimationOptionAutoreverse               = UIViewAnimationOptionAutoreverse, // if repeat, run animation back and forth
    UIViewKeyframeAnimationOptionOverrideInheritedDuration = UIViewAnimationOptionOverrideInheritedDuration, // ignore nested duration
    UIViewKeyframeAnimationOptionOverrideInheritedOptions  = UIViewAnimationOptionOverrideInheritedOptions, // do not inherit any options or animation type
    
    UIViewKeyframeAnimationOptionCalculationModeLinear     = 0 << 10, // default
    UIViewKeyframeAnimationOptionCalculationModeDiscrete   = 1 << 10,
    UIViewKeyframeAnimationOptionCalculationModePaced      = 2 << 10,
    UIViewKeyframeAnimationOptionCalculationModeCubic      = 3 << 10,
    UIViewKeyframeAnimationOptionCalculationModeCubicPaced = 4 << 10
} API_AVAILABLE(ios(7.0));
    
typedef NS_ENUM(NSUInteger, UISystemAnimation) {
    UISystemAnimationDelete,    // removes the views from the hierarchy when complete
} API_AVAILABLE(ios(7.0));

typedef NS_ENUM(NSInteger, UIViewTintAdjustmentMode) {
    UIViewTintAdjustmentModeAutomatic,
    
    UIViewTintAdjustmentModeNormal,
    UIViewTintAdjustmentModeDimmed,
} API_AVAILABLE(ios(7.0));

typedef NS_ENUM(NSInteger, UISemanticContentAttribute) {
    UISemanticContentAttributeUnspecified = 0,
    UISemanticContentAttributePlayback, // for playback controls such as Play/RW/FF buttons and playhead scrubbers
    UISemanticContentAttributeSpatial, // for controls that result in some sort of directional change in the UI, e.g. a segmented control for text alignment or a D-pad in a game
    UISemanticContentAttributeForceLeftToRight,
    UISemanticContentAttributeForceRightToLeft
} API_AVAILABLE(ios(9.0));

@protocol UICoordinateSpace <NSObject>

- (CGPoint)convertPoint:(CGPoint)point toCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace API_AVAILABLE(ios(8.0));
- (CGPoint)convertPoint:(CGPoint)point fromCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace API_AVAILABLE(ios(8.0));
- (CGRect)convertRect:(CGRect)rect toCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace API_AVAILABLE(ios(8.0));
- (CGRect)convertRect:(CGRect)rect fromCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace API_AVAILABLE(ios(8.0));

@property (readonly, nonatomic) CGRect bounds API_AVAILABLE(ios(8.0));

@end

@class UIBezierPath, UIEvent, UIWindow, UIViewController, UIColor, UIGestureRecognizer, UIMotionEffect, CALayer, UILayoutGuide;

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) @interface UIView : UIResponder <NSCoding, UIAppearance, UIAppearanceContainer, UIDynamicItem, UITraitEnvironment, UICoordinateSpace, UIFocusItem, UIFocusItemContainer, CALayerDelegate>

@property(class, nonatomic, readonly) Class layerClass;                        // default is [CALayer class]. Used when creating the underlying layer for the view.

- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property(nonatomic,getter=isUserInteractionEnabled) BOOL userInteractionEnabled;  // default is YES. if set to NO, user events (touch, keys) are ignored and removed from the event queue.
@property(nonatomic)                                 NSInteger tag;                // default is 0
@property(nonatomic,readonly,strong)                 CALayer  *layer;              // returns view's layer. Will always return a non-nil value. view is layer's delegate

@property(nonatomic,readonly) BOOL canBecomeFocused API_AVAILABLE(ios(9.0)); // NO by default
@property (readonly, nonatomic, getter=isFocused) BOOL focused API_AVAILABLE(ios(9.0));

/// The identifier of the focus group that this view belongs to. If this is nil, subviews inherit their superview's focus group.
@property (nonatomic, readwrite, nullable, copy) NSString *focusGroupIdentifier API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos);

@property (nonatomic) UISemanticContentAttribute semanticContentAttribute API_AVAILABLE(ios(9.0));

// This method returns the layout direction implied by the provided semantic content attribute relative to the application-wide layout direction (as returned by UIApplication.sharedApplication.userInterfaceLayoutDirection).
+ (UIUserInterfaceLayoutDirection)userInterfaceLayoutDirectionForSemanticContentAttribute:(UISemanticContentAttribute)attribute API_AVAILABLE(ios(9.0));

// This method returns the layout direction implied by the provided semantic content attribute relative to the provided layout direction. For example, when provided a layout direction of RightToLeft and a semantic content attribute of Playback, this method returns LeftToRight. Layout and drawing code can use this method to determine how to arrange elements, but might find it easier to query the container view’s effectiveUserInterfaceLayoutDirection property instead.
+ (UIUserInterfaceLayoutDirection)userInterfaceLayoutDirectionForSemanticContentAttribute:(UISemanticContentAttribute)semanticContentAttribute relativeToLayoutDirection:(UIUserInterfaceLayoutDirection)layoutDirection API_AVAILABLE(ios(10.0));

// Returns the user interface layout direction appropriate for arranging the immediate content of this view. Always consult the effectiveUserInterfaceLayoutDirection of the view whose immediate content is being arranged or drawn. Do not assume that the value propagates through the view’s subtree.
@property (readonly, nonatomic) UIUserInterfaceLayoutDirection effectiveUserInterfaceLayoutDirection API_AVAILABLE(ios(10.0));

@end

@interface UIView(UIViewGeometry)

// animatable. do not use frame if view is transformed since it will not correctly reflect the actual location of the view. use bounds + center instead.
@property(nonatomic) CGRect            frame;

// use bounds/center and not frame if non-identity transform. if bounds dimension is odd, center may be have fractional part
@property(nonatomic) CGRect            bounds;      // default bounds is zero origin, frame size. animatable
@property(nonatomic) CGPoint           center;      // center is center of frame. animatable
@property(nonatomic) CGAffineTransform transform;   // default is CGAffineTransformIdentity. animatable. Please use this property instead of the affineTransform property on the layer
@property(nonatomic) CATransform3D     transform3D API_AVAILABLE(ios(13.0),tvos(13.0)); // default is CATransform3DIdentity. animatable. Please use this property instead of the transform property on the layer
@property(nonatomic) CGFloat           contentScaleFactor API_AVAILABLE(ios(4.0));

@property(nonatomic,getter=isMultipleTouchEnabled) BOOL multipleTouchEnabled API_UNAVAILABLE(tvos);   // default is NO
@property(nonatomic,getter=isExclusiveTouch) BOOL       exclusiveTouch API_UNAVAILABLE(tvos);         // default is NO

- (nullable UIView *)hitTest:(CGPoint)point withEvent:(nullable UIEvent *)event;   // recursively calls -pointInside:withEvent:. point is in the receiver's coordinate system
- (BOOL)pointInside:(CGPoint)point withEvent:(nullable UIEvent *)event;   // default returns YES if point is in bounds

- (CGPoint)convertPoint:(CGPoint)point toView:(nullable UIView *)view;
- (CGPoint)convertPoint:(CGPoint)point fromView:(nullable UIView *)view;
- (CGRect)convertRect:(CGRect)rect toView:(nullable UIView *)view;
- (CGRect)convertRect:(CGRect)rect fromView:(nullable UIView *)view;

@property(nonatomic) BOOL               autoresizesSubviews; // default is YES. if set, subviews are adjusted according to their autoresizingMask if self.bounds changes
@property(nonatomic) UIViewAutoresizing autoresizingMask;    // simple resize. default is UIViewAutoresizingNone

- (CGSize)sizeThatFits:(CGSize)size;     // return 'best' size to fit given size. does not actually resize view. Default is return existing view size
- (void)sizeToFit;                       // calls sizeThatFits: with current view bounds and changes bounds size.

@end

@interface UIView(UIViewHierarchy)

@property(nullable, nonatomic,readonly) UIView       *superview;
@property(nonatomic,readonly,copy) NSArray<__kindof UIView *> *subviews;
@property(nullable, nonatomic,readonly) UIWindow     *window;

- (void)removeFromSuperview;
- (void)insertSubview:(UIView *)view atIndex:(NSInteger)index;
- (void)exchangeSubviewAtIndex:(NSInteger)index1 withSubviewAtIndex:(NSInteger)index2;

- (void)addSubview:(UIView *)view;
- (void)insertSubview:(UIView *)view belowSubview:(UIView *)siblingSubview;
- (void)insertSubview:(UIView *)view aboveSubview:(UIView *)siblingSubview;

- (void)bringSubviewToFront:(UIView *)view;
- (void)sendSubviewToBack:(UIView *)view;

- (void)didAddSubview:(UIView *)subview;
- (void)willRemoveSubview:(UIView *)subview;

- (void)willMoveToSuperview:(nullable UIView *)newSuperview;
- (void)didMoveToSuperview;
- (void)willMoveToWindow:(nullable UIWindow *)newWindow;
- (void)didMoveToWindow;

- (BOOL)isDescendantOfView:(UIView *)view;  // returns YES for self.
- (nullable __kindof UIView *)viewWithTag:(NSInteger)tag; // recursive search. includes self

// Allows you to perform layout before the drawing cycle happens. -layoutIfNeeded forces layout early
- (void)setNeedsLayout;
- (void)layoutIfNeeded;

- (void)layoutSubviews;    // override point. called by layoutIfNeeded automatically. As of iOS 6.0, when constraints-based layout is used the base implementation applies the constraints-based layout, otherwise it does nothing.

/* -layoutMargins returns a set of insets from the edge of the view's bounds that denote a default spacing for laying out content.
 If preservesSuperviewLayoutMargins is YES, margins cascade down the view tree, adjusting for geometry offsets, so that setting
 the left value of layoutMargins on a superview will affect the left value of layoutMargins for subviews positioned close to the
 left edge of their superview's bounds
   If your view subclass uses layoutMargins in its layout or drawing, override -layoutMarginsDidChange in order to refresh your 
 view if the margins change.
   On iOS 11.0 and later, please support both user interface layout directions by setting the directionalLayoutMargins property
 instead of the layoutMargins property. After setting the directionalLayoutMargins property, the values in the left and right
 fields of the layoutMargins property will depend on the user interface layout direction.
 */
@property (nonatomic) UIEdgeInsets layoutMargins API_AVAILABLE(ios(8.0));

/* directionalLayoutMargins.leading is used on the left when the user interface direction is LTR and on the right for RTL.
 Vice versa for directionalLayoutMargins.trailing.
 */
@property (nonatomic) NSDirectionalEdgeInsets directionalLayoutMargins API_AVAILABLE(ios(11.0),tvos(11.0));

@property (nonatomic) BOOL preservesSuperviewLayoutMargins API_AVAILABLE(ios(8.0)); // default is NO - set to enable pass-through or cascading behavior of margins from this view’s parent to its children
@property (nonatomic) BOOL insetsLayoutMarginsFromSafeArea API_AVAILABLE(ios(11.0),tvos(11.0));  // Default: YES

- (void)layoutMarginsDidChange API_AVAILABLE(ios(8.0));

@property (nonatomic,readonly) UIEdgeInsets safeAreaInsets API_AVAILABLE(ios(11.0),tvos(11.0));
- (void)safeAreaInsetsDidChange API_AVAILABLE(ios(11.0),tvos(11.0));

/* The edges of this guide are constrained to equal the edges of the view inset by the layoutMargins
 */
@property(readonly,strong) UILayoutGuide *layoutMarginsGuide API_AVAILABLE(ios(9.0));

/// This content guide provides a layout area that you can use to place text and related content whose width should generally be constrained to a size that is easy for the user to read. This guide provides a centered region that you can place content within to get this behavior for this view.
@property (nonatomic, readonly, strong) UILayoutGuide *readableContentGuide  API_AVAILABLE(ios(9.0));

/* The top of the safeAreaLayoutGuide indicates the unobscured top edge of the view (e.g, not behind
 the status bar or navigation bar, if present). Similarly for the other edges.
 */
@property(nonatomic,readonly,strong) UILayoutGuide *safeAreaLayoutGuide API_AVAILABLE(ios(11.0),tvos(11.0));
@end

@interface UIView(UIViewRendering)

- (void)drawRect:(CGRect)rect;

- (void)setNeedsDisplay;
- (void)setNeedsDisplayInRect:(CGRect)rect;

@property(nonatomic)                 BOOL              clipsToBounds;              // When YES, content and subviews are clipped to the bounds of the view. Default is NO.
@property(nullable, nonatomic,copy)            UIColor          *backgroundColor UI_APPEARANCE_SELECTOR; // default is nil. Can be useful with the appearance proxy on custom UIView subclasses.
@property(nonatomic)                 CGFloat           alpha;                      // animatable. default is 1.0
@property(nonatomic,getter=isOpaque) BOOL              opaque;                     // default is YES. opaque views must fill their entire bounds or the results are undefined. the active CGContext in drawRect: will not have been cleared and may have non-zeroed pixels
@property(nonatomic)                 BOOL              clearsContextBeforeDrawing; // default is YES. ignored for opaque views. for non-opaque views causes the active CGContext in drawRect: to be pre-filled with transparent pixels
@property(nonatomic,getter=isHidden) BOOL              hidden;                     // default is NO. doesn't check superviews
@property(nonatomic)                 UIViewContentMode contentMode;                // default is UIViewContentModeScaleToFill
@property(nonatomic)                 CGRect            contentStretch API_DEPRECATED("", ios(3.0, 6.0)) API_UNAVAILABLE(tvos); // animatable. default is unit rectangle {{0,0} {1,1}}. Now deprecated: please use -[UIImage resizableImageWithCapInsets:] to achieve the same effect.

@property(nullable, nonatomic,strong)          UIView           *maskView API_AVAILABLE(ios(8.0));

/*
 -tintColor always returns a color. The color returned is the first non-default value in the receiver's superview chain (starting with itself).
 If no non-default value is found, a system-defined color is returned.
 If this view's -tintAdjustmentMode returns Dimmed, then the color that is returned for -tintColor will automatically be dimmed.
 If your view subclass uses tintColor in its rendering, override -tintColorDidChange in order to refresh the rendering if the color changes.
 */
@property(null_resettable, nonatomic, strong) UIColor *tintColor API_AVAILABLE(ios(7.0));

/*
 -tintAdjustmentMode always returns either UIViewTintAdjustmentModeNormal or UIViewTintAdjustmentModeDimmed. The value returned is the first non-default value in the receiver's superview chain (starting with itself).
 If no non-default value is found, UIViewTintAdjustmentModeNormal is returned.
 When tintAdjustmentMode has a value of UIViewTintAdjustmentModeDimmed for a view, the color it returns from tintColor will be modified to give a dimmed appearance.
 When the tintAdjustmentMode of a view changes (either the view's value changing or by one of its superview's values changing), -tintColorDidChange will be called to allow the view to refresh its rendering.
 */
@property(nonatomic) UIViewTintAdjustmentMode tintAdjustmentMode API_AVAILABLE(ios(7.0));

/*
 The -tintColorDidChange message is sent to appropriate subviews of a view when its tintColor is changed by client code or to subviews in the view hierarchy of a view whose tintColor is implicitly changed when its superview or tintAdjustmentMode changes.
 */
- (void)tintColorDidChange API_AVAILABLE(ios(7.0));

@end

@interface UIView(UIViewAnimation)

+ (void)setAnimationsEnabled:(BOOL)enabled;                         // ignore any attribute changes while set.
@property(class, nonatomic, readonly) BOOL areAnimationsEnabled;
+ (void)performWithoutAnimation:(void (NS_NOESCAPE ^)(void))actionsWithoutAnimation API_AVAILABLE(ios(7.0));

@property(class, nonatomic, readonly) NSTimeInterval inheritedAnimationDuration API_AVAILABLE(ios(9.0));

@end

@interface UIView(UIViewAnimationWithBlocks)

+ (void)animateWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay options:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(void (^ __nullable)(BOOL finished))completion API_AVAILABLE(ios(4.0));

+ (void)animateWithDuration:(NSTimeInterval)duration animations:(void (^)(void))animations completion:(void (^ __nullable)(BOOL finished))completion API_AVAILABLE(ios(4.0)); // delay = 0.0, options = 0

+ (void)animateWithDuration:(NSTimeInterval)duration animations:(void (^)(void))animations API_AVAILABLE(ios(4.0)); // delay = 0.0, options = 0, completion = NULL

/* Performs `animations` using a timing curve described by the motion of a spring. When `dampingRatio` is 1, the animation will smoothly decelerate to its final model values without oscillating. Damping ratios less than 1 will oscillate more and more before coming to a complete stop. You can use the initial spring velocity to specify how fast the object at the end of the simulated spring was moving before it was attached. It's a unit coordinate system, where 1 is defined as traveling the total animation distance in a second. So if you're changing an object's position by 200pt in this animation, and you want the animation to behave as if the object was moving at 100pt/s before the animation started, you'd pass 0.5. You'll typically want to pass 0 for the velocity. */
+ (void)animateWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay usingSpringWithDamping:(CGFloat)dampingRatio initialSpringVelocity:(CGFloat)velocity options:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(void (^ __nullable)(BOOL finished))completion API_AVAILABLE(ios(7.0));

+ (void)transitionWithView:(UIView *)view duration:(NSTimeInterval)duration options:(UIViewAnimationOptions)options animations:(void (^ __nullable)(void))animations completion:(void (^ __nullable)(BOOL finished))completion API_AVAILABLE(ios(4.0));

+ (void)transitionFromView:(UIView *)fromView toView:(UIView *)toView duration:(NSTimeInterval)duration options:(UIViewAnimationOptions)options completion:(void (^ __nullable)(BOOL finished))completion API_AVAILABLE(ios(4.0)); // toView added to fromView.superview, fromView removed from its superview

/* Performs the requested system-provided animation on one or more views. Specify additional animations in the parallelAnimations block. These additional animations will run alongside the system animation with the same timing and duration that the system animation defines/inherits. Additional animations should not modify properties of the view on which the system animation is being performed. Not all system animations honor all available options.
 */
+ (void)performSystemAnimation:(UISystemAnimation)animation onViews:(NSArray<__kindof UIView *> *)views options:(UIViewAnimationOptions)options animations:(void (^ __nullable)(void))parallelAnimations completion:(void (^ __nullable)(BOOL finished))completion API_AVAILABLE(ios(7.0));

/* Call this method from within an animation block to repeat animations, otherwise has no effect. The total duration of a repeating animation can be computed via (outerAnimationDuration * repeatCount * autoreverses ? 2 : 1). */
+ (void)modifyAnimationsWithRepeatCount:(CGFloat)count autoreverses:(BOOL)autoreverses animations:(void(NS_NOESCAPE ^)(void))animations API_AVAILABLE(ios(12.0),tvos(12.0));

@end

@interface UIView (UIViewKeyframeAnimations)

+ (void)animateKeyframesWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay options:(UIViewKeyframeAnimationOptions)options animations:(void (^)(void))animations completion:(void (^ __nullable)(BOOL finished))completion API_AVAILABLE(ios(7.0));
+ (void)addKeyframeWithRelativeStartTime:(double)frameStartTime relativeDuration:(double)frameDuration animations:(void (^)(void))animations API_AVAILABLE(ios(7.0)); // start time and duration are values between 0.0 and 1.0 specifying time and duration relative to the overall time of the keyframe animation

@end

@interface UIView (UIViewGestureRecognizers)

@property(nullable, nonatomic,copy) NSArray<__kindof UIGestureRecognizer *> *gestureRecognizers API_AVAILABLE(ios(3.2));

- (void)addGestureRecognizer:(UIGestureRecognizer*)gestureRecognizer API_AVAILABLE(ios(3.2));
- (void)removeGestureRecognizer:(UIGestureRecognizer*)gestureRecognizer API_AVAILABLE(ios(3.2));

// called when the recognizer attempts to transition out of UIGestureRecognizerStatePossible if a touch hit-tested to this view will be cancelled as a result of gesture recognition
// returns YES by default. return NO to cause the gesture recognizer to transition to UIGestureRecognizerStateFailed
// subclasses may override to prevent recognition of particular gestures. for example, UISlider prevents swipes parallel to the slider that start in the thumb
- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer API_AVAILABLE(ios(6.0));

@end
    
@interface UIView (UIViewMotionEffects)

/*! Begins applying `effect` to the receiver. The effect's emitted keyPath/value pairs will be
    applied to the view's presentation layer.
 
    Animates the transition to the motion effect's values using the present UIView animation
    context. */
- (void)addMotionEffect:(UIMotionEffect *)effect API_AVAILABLE(ios(7.0));

/*! Stops applying `effect` to the receiver. Any affected presentation values will animate to
    their post-removal values using the present UIView animation context. */
- (void)removeMotionEffect:(UIMotionEffect *)effect API_AVAILABLE(ios(7.0));

@property (copy, nonatomic) NSArray<__kindof UIMotionEffect *> *motionEffects API_AVAILABLE(ios(7.0));

@end


//
// UIView Constraint-based Layout Support
//

typedef NS_ENUM(NSInteger, UILayoutConstraintAxis) {
    UILayoutConstraintAxisHorizontal = 0,
    UILayoutConstraintAxisVertical = 1
};

// Installing Constraints

/* A constraint is typically installed on the closest common ancestor of the views involved in the constraint. 
 It is required that a constraint be installed on _a_ common ancestor of every view involved.  The numbers in a constraint are interpreted in the coordinate system of the view it is installed on.  A view is considered to be an ancestor of itself.
 */
@interface UIView (UIConstraintBasedLayoutInstallingConstraints)

@property(nonatomic,readonly) NSArray<__kindof NSLayoutConstraint *> *constraints API_AVAILABLE(ios(6.0));

- (void)addConstraint:(NSLayoutConstraint *)constraint API_AVAILABLE(ios(6.0)); // This method will be deprecated in a future release and should be avoided.  Instead, set NSLayoutConstraint's active property to YES.
- (void)addConstraints:(NSArray<__kindof NSLayoutConstraint *> *)constraints API_AVAILABLE(ios(6.0)); // This method will be deprecated in a future release and should be avoided.  Instead use +[NSLayoutConstraint activateConstraints:].
- (void)removeConstraint:(NSLayoutConstraint *)constraint API_AVAILABLE(ios(6.0)); // This method will be deprecated in a future release and should be avoided.  Instead set NSLayoutConstraint's active property to NO.
- (void)removeConstraints:(NSArray<__kindof NSLayoutConstraint *> *)constraints API_AVAILABLE(ios(6.0)); // This method will be deprecated in a future release and should be avoided.  Instead use +[NSLayoutConstraint deactivateConstraints:].
@end

// Core Layout Methods

/* To render a window, the following passes will occur, if necessary.  
 
 update constraints
 layout
 display
 
 Please see the conceptual documentation for a discussion of these methods.
 */

@interface UIView (UIConstraintBasedLayoutCoreMethods) 
- (void)updateConstraintsIfNeeded API_AVAILABLE(ios(6.0)); // Updates the constraints from the bottom up for the view hierarchy rooted at the receiver. UIWindow's implementation creates a layout engine if necessary first.
- (void)updateConstraints API_AVAILABLE(ios(6.0)) NS_REQUIRES_SUPER; // Override this to adjust your special constraints during a constraints update pass
- (BOOL)needsUpdateConstraints API_AVAILABLE(ios(6.0));
- (void)setNeedsUpdateConstraints API_AVAILABLE(ios(6.0));
@end

// Compatibility and Adoption

@interface UIView (UIConstraintBasedCompatibility) 

/* By default, the autoresizing mask on a view gives rise to constraints that fully determine 
 the view's position. This allows the auto layout system to track the frames of views whose 
 layout is controlled manually (through -setFrame:, for example).
 When you elect to position the view using auto layout by adding your own constraints, 
 you must set this property to NO. IB will do this for you.
 */
@property(nonatomic) BOOL translatesAutoresizingMaskIntoConstraints API_AVAILABLE(ios(6.0)); // Default YES

/* constraint-based layout engages lazily when someone tries to use it (e.g., adds a constraint to a view).  If you do all of your constraint set up in -updateConstraints, you might never even receive updateConstraints if no one makes a constraint.  To fix this chicken and egg problem, override this method to return YES if your view needs the window to use constraint-based layout.  
 */
@property(class, nonatomic, readonly) BOOL requiresConstraintBasedLayout API_AVAILABLE(ios(6.0));

@end

// Separation of Concerns

@interface UIView (UIConstraintBasedLayoutLayering)

/* Constraints do not actually relate the frames of the views, rather they relate the "alignment rects" of views.  This is the same as the frame unless overridden by a subclass of UIView.  Alignment rects are the same as the "layout rects" shown in Interface Builder 3.  Typically the alignment rect of a view is what the end user would think of as the bounding rect around a control, omitting ornamentation like shadows and engraving lines.  The edges of the alignment rect are what is interesting to align, not the shadows and such.  
 */

/* These two methods should be inverses of each other.  UIKit will call both as part of layout computation.
 They may be overridden to provide arbitrary transforms between frame and alignment rect, though the two methods must be inverses of each other.
 However, the default implementation uses -alignmentRectInsets, so just override that if it's applicable.  It's easier to get right. 
 A view that displayed an image with some ornament would typically override these, because the ornamental part of an image would scale up with the size of the frame.  
 Set the NSUserDefault UIViewShowAlignmentRects to YES to see alignment rects drawn.
 */
- (CGRect)alignmentRectForFrame:(CGRect)frame API_AVAILABLE(ios(6.0));
- (CGRect)frameForAlignmentRect:(CGRect)alignmentRect API_AVAILABLE(ios(6.0));

/* override this if the alignment rect is obtained from the frame by insetting each edge by a fixed amount.  This is only called by alignmentRectForFrame: and frameForAlignmentRect:.
 */
@property(nonatomic, readonly) UIEdgeInsets alignmentRectInsets API_AVAILABLE(ios(6.0));

- (UIView *)viewForBaselineLayout API_DEPRECATED("Override -viewForFirstBaselineLayout or -viewForLastBaselineLayout as appropriate, instead", ios(6.0, 9.0)) API_UNAVAILABLE(tvos);

/* -viewForFirstBaselineLayout is called by the constraints system when interpreting
 the firstBaseline attribute for a view.
    For complex custom UIView subclasses, override this method to return the text-based
 (i.e., UILabel or non-scrollable UITextView) descendant of the receiver whose first baseline
 is appropriate for alignment.
    UIView's implementation returns [self viewForLastBaselineLayout], so if the same 
 descendant is appropriate for both first- and last-baseline layout you may override
 just -viewForLastBaselineLayout.
 */
@property(readonly,strong) UIView *viewForFirstBaselineLayout API_AVAILABLE(ios(9.0));

/* -viewForLastBaselineLayout is called by the constraints system when interpreting
 the lastBaseline attribute for a view.
    For complex custom UIView subclasses, override this method to return the text-based
 (i.e., UILabel or non-scrollable UITextView) descendant of the receiver whose last baseline
 is appropriate for alignment.
    UIView's implementation returns self.
 */
@property(readonly,strong) UIView *viewForLastBaselineLayout API_AVAILABLE(ios(9.0));

/* Override this method to tell the layout system that there is something it doesn't natively understand in this view, and this is how large it intrinsically is.  A typical example would be a single line text field.  The layout system does not understand text - it must just be told that there's something in the view, and that that something will take a certain amount of space if not clipped.  
 
 In response, UIKit will set up constraints that specify (1) that the opaque content should not be compressed or clipped, (2) that the view prefers to hug tightly to its content. 
 
 A user of a view may need to specify the priority of these constraints.  For example, by default, a push button 
 -strongly wants to hug its content in the vertical direction (buttons really ought to be their natural height)
 -weakly hugs its content horizontally (extra side padding between the title and the edge of the bezel is acceptable)
 -strongly resists compressing or clipping content in both directions. 
 
 However, you might have a case where you'd prefer to show all the available buttons with truncated text rather than losing some of the buttons. The truncation might only happen in portrait orientation but not in landscape, for example. In that case you'd want to setContentCompressionResistancePriority:forAxis: to (say) UILayoutPriorityDefaultLow for the horizontal axis.
 
 The default 'strong' and 'weak' priorities referred to above are UILayoutPriorityDefaultHigh and UILayoutPriorityDefaultLow.  
 
 Note that not all views have an intrinsicContentSize.  UIView's default implementation is to return (UIViewNoIntrinsicMetric, UIViewNoIntrinsicMetric).  The _intrinsic_ content size is concerned only with data that is in the view itself, not in other views. Remember that you can also set constant width or height constraints on any view, and you don't need to override intrinsicContentSize if these dimensions won't be changing with changing view content.
 */
UIKIT_EXTERN const CGFloat UIViewNoIntrinsicMetric API_AVAILABLE(ios(6.0)); // -1
@property(nonatomic, readonly) CGSize intrinsicContentSize API_AVAILABLE(ios(6.0));
- (void)invalidateIntrinsicContentSize API_AVAILABLE(ios(6.0)); // call this when something changes that affects the intrinsicContentSize.  Otherwise UIKit won't notice that it changed.

- (UILayoutPriority)contentHuggingPriorityForAxis:(UILayoutConstraintAxis)axis API_AVAILABLE(ios(6.0));
- (void)setContentHuggingPriority:(UILayoutPriority)priority forAxis:(UILayoutConstraintAxis)axis API_AVAILABLE(ios(6.0));

- (UILayoutPriority)contentCompressionResistancePriorityForAxis:(UILayoutConstraintAxis)axis API_AVAILABLE(ios(6.0));
- (void)setContentCompressionResistancePriority:(UILayoutPriority)priority forAxis:(UILayoutConstraintAxis)axis API_AVAILABLE(ios(6.0));
@end

// Size To Fit

UIKIT_EXTERN const CGSize UILayoutFittingCompressedSize API_AVAILABLE(ios(6.0));
UIKIT_EXTERN const CGSize UILayoutFittingExpandedSize API_AVAILABLE(ios(6.0));

@interface UIView (UIConstraintBasedLayoutFittingSize)
/* The size fitting most closely to targetSize in which the receiver's subtree can be laid out while optimally satisfying the constraints. If you want the smallest possible size, pass UILayoutFittingCompressedSize; for the largest possible size, pass UILayoutFittingExpandedSize.
 Also see the comment for UILayoutPriorityFittingSizeLevel.
 */
- (CGSize)systemLayoutSizeFittingSize:(CGSize)targetSize API_AVAILABLE(ios(6.0)); // Equivalent to sending -systemLayoutSizeFittingSize:withHorizontalFittingPriority:verticalFittingPriority: with UILayoutPriorityFittingSizeLevel for both priorities.
- (CGSize)systemLayoutSizeFittingSize:(CGSize)targetSize withHorizontalFittingPriority:(UILayoutPriority)horizontalFittingPriority verticalFittingPriority:(UILayoutPriority)verticalFittingPriority API_AVAILABLE(ios(8.0));
@end

@interface UIView (UILayoutGuideSupport)

/* UILayoutGuide objects owned by the receiver.
 */
@property(nonatomic,readonly,copy) NSArray<__kindof UILayoutGuide *> *layoutGuides API_AVAILABLE(ios(9.0));

/* Adds layoutGuide to the receiver, passing the receiver in -setOwningView: to layoutGuide.
 */
- (void)addLayoutGuide:(UILayoutGuide *)layoutGuide API_AVAILABLE(ios(9.0));

/* Removes layoutGuide from the receiver, passing nil in -setOwningView: to layoutGuide.
 */
- (void)removeLayoutGuide:(UILayoutGuide *)layoutGuide API_AVAILABLE(ios(9.0));
@end

@class NSLayoutXAxisAnchor,NSLayoutYAxisAnchor,NSLayoutDimension;
@interface UIView (UIViewLayoutConstraintCreation)
/* Constraint creation conveniences. See NSLayoutAnchor.h for details.
 */
@property(nonatomic,readonly,strong) NSLayoutXAxisAnchor *leadingAnchor API_AVAILABLE(ios(9.0));
@property(nonatomic,readonly,strong) NSLayoutXAxisAnchor *trailingAnchor API_AVAILABLE(ios(9.0));
@property(nonatomic,readonly,strong) NSLayoutXAxisAnchor *leftAnchor API_AVAILABLE(ios(9.0));
@property(nonatomic,readonly,strong) NSLayoutXAxisAnchor *rightAnchor API_AVAILABLE(ios(9.0));
@property(nonatomic,readonly,strong) NSLayoutYAxisAnchor *topAnchor API_AVAILABLE(ios(9.0));
@property(nonatomic,readonly,strong) NSLayoutYAxisAnchor *bottomAnchor API_AVAILABLE(ios(9.0));
@property(nonatomic,readonly,strong) NSLayoutDimension *widthAnchor API_AVAILABLE(ios(9.0));
@property(nonatomic,readonly,strong) NSLayoutDimension *heightAnchor API_AVAILABLE(ios(9.0));
@property(nonatomic,readonly,strong) NSLayoutXAxisAnchor *centerXAnchor API_AVAILABLE(ios(9.0));
@property(nonatomic,readonly,strong) NSLayoutYAxisAnchor *centerYAnchor API_AVAILABLE(ios(9.0));
@property(nonatomic,readonly,strong) NSLayoutYAxisAnchor *firstBaselineAnchor API_AVAILABLE(ios(9.0));
@property(nonatomic,readonly,strong) NSLayoutYAxisAnchor *lastBaselineAnchor API_AVAILABLE(ios(9.0));

@end

// Debugging

/* Everything in this section should be used in debugging only, never in shipping code.  These methods may not exist in the future - no promises.  
 */
@interface UIView (UIConstraintBasedLayoutDebugging)

/* This returns a list of all the constraints that are affecting the current location of the receiver.  The constraints do not necessarily involve the receiver, they may affect the frame indirectly.
 Pass UILayoutConstraintAxisHorizontal for the constraints affecting [self center].x and CGRectGetWidth([self bounds]), and UILayoutConstraintAxisVertical for the constraints affecting[self center].y and CGRectGetHeight([self bounds]).
 */
- (NSArray<__kindof NSLayoutConstraint *> *)constraintsAffectingLayoutForAxis:(UILayoutConstraintAxis)axis API_AVAILABLE(ios(6.0));

/* If there aren't enough constraints in the system to uniquely determine layout, we say the layout is ambiguous.  For example, if the only constraint in the system was x = y + 100, then there are lots of different possible values for x and y.  This situation is not automatically detected by UIKit, due to performance considerations and details of the algorithm used for layout.  
 The symptom of ambiguity is that views sometimes jump from place to place, or possibly are just in the wrong place.
 -hasAmbiguousLayout runs a check for whether there is another center and bounds the receiver could have that could also satisfy the constraints.
 -exerciseAmbiguousLayout does more.  It randomly changes the view layout to a different valid layout.  Making the UI jump back and forth can be helpful for figuring out where you're missing a constraint.  
 */
@property(nonatomic, readonly) BOOL hasAmbiguousLayout API_AVAILABLE(ios(6.0));

- (void)exerciseAmbiguityInLayout API_AVAILABLE(ios(6.0)); 
@end

/* Everything in this section should be used in debugging only, never in shipping code.  These methods may not exist in the future - no promises.
 */
@interface UILayoutGuide (UIConstraintBasedLayoutDebugging)

/* This returns a list of all the constraints that are affecting the current location of the receiver.  The constraints do not necessarily involve the receiver, they may affect the frame indirectly.
 Pass UILayoutConstraintAxisHorizontal for the constraints affecting [self center].x and CGRectGetWidth([self bounds]), and UILayoutConstraintAxisVertical for the constraints affecting[self center].y and CGRectGetHeight([self bounds]).
 */
- (NSArray<__kindof NSLayoutConstraint *> *)constraintsAffectingLayoutForAxis:(UILayoutConstraintAxis)axis API_AVAILABLE(ios(10.0));

/* If there aren't enough constraints in the system to uniquely determine layout, we say the layout is ambiguous.  For example, if the only constraint in the system was x = y + 100, then there are lots of different possible values for x and y.  This situation is not automatically detected by UIKit, due to performance considerations and details of the algorithm used for layout.
 The symptom of ambiguity is that views sometimes jump from place to place, or possibly are just in the wrong place.
 -hasAmbiguousLayout runs a check for whether there is another center and bounds the receiver could have that could also satisfy the constraints.
 */
@property(nonatomic, readonly) BOOL hasAmbiguousLayout API_AVAILABLE(ios(10.0));
@end

@interface UIView (UIStateRestoration)
@property (nullable, nonatomic, copy) NSString *restorationIdentifier API_AVAILABLE(ios(6.0));
- (void) encodeRestorableStateWithCoder:(NSCoder *)coder API_AVAILABLE(ios(6.0));
- (void) decodeRestorableStateWithCoder:(NSCoder *)coder API_AVAILABLE(ios(6.0));
@end

@interface UIView (UISnapshotting)
/* 
* When requesting a snapshot, 'afterUpdates' defines whether the snapshot is representative of what's currently on screen or if you wish to include any recent changes before taking the snapshot. 
 
 If called during layout from a committing transaction, snapshots occurring after the screen updates will include all changes made, regardless of when the snapshot is taken and the changes are made. For example:
 
     - (void)layoutSubviews {
         UIView *snapshot = [self snapshotViewAfterScreenUpdates:YES];
         self.alpha = 0.0;
     }
 
 The snapshot will appear to be empty since the change in alpha will be captured by the snapshot. If you need to animate the view during layout, animate the snapshot instead.

* Creating snapshots from existing snapshots (as a method to duplicate, crop or create a resizable variant) is supported. In cases where many snapshots are needed, creating a snapshot from a common superview and making subsequent snapshots from it can be more performant. Please keep in mind that if 'afterUpdates' is YES, the original snapshot is committed and any changes made to it, not the view originally snapshotted, will be included.
 */
- (nullable UIView *)snapshotViewAfterScreenUpdates:(BOOL)afterUpdates API_AVAILABLE(ios(7.0));
- (nullable UIView *)resizableSnapshotViewFromRect:(CGRect)rect afterScreenUpdates:(BOOL)afterUpdates withCapInsets:(UIEdgeInsets)capInsets API_AVAILABLE(ios(7.0));  // Resizable snapshots will default to stretching the center
// Use this method to render a snapshot of the view hierarchy into the current context. Returns NO if the snapshot is missing image data, YES if the snapshot is complete. Calling this method from layoutSubviews while the current transaction is committing will capture what is currently displayed regardless if afterUpdates is YES.
- (BOOL)drawViewHierarchyInRect:(CGRect)rect afterScreenUpdates:(BOOL)afterUpdates API_AVAILABLE(ios(7.0));
@end

@interface UIView (DeprecatedAnimations)

/* Deprecated in iOS 13.0. Please use the block-based animation API instead. */

+ (void)beginAnimations:(nullable NSString *)animationID context:(nullable void *)context                       API_DEPRECATED("Use the block-based animation API instead", ios(2.0, 13.0));
+ (void)commitAnimations                                                                                        API_DEPRECATED("Use the block-based animation API instead", ios(2.0, 13.0));
+ (void)setAnimationDelegate:(nullable id)delegate                                                              API_DEPRECATED("Use the block-based animation API instead", ios(2.0, 13.0));
+ (void)setAnimationWillStartSelector:(nullable SEL)selector                                                    API_DEPRECATED("Use the block-based animation API instead", ios(2.0, 13.0));
+ (void)setAnimationDidStopSelector:(nullable SEL)selector                                                      API_DEPRECATED("Use the block-based animation API instead", ios(2.0, 13.0));
+ (void)setAnimationDuration:(NSTimeInterval)duration                                                           API_DEPRECATED("Use the block-based animation API instead", ios(2.0, 13.0));
+ (void)setAnimationDelay:(NSTimeInterval)delay                                                                 API_DEPRECATED("Use the block-based animation API instead", ios(2.0, 13.0));
+ (void)setAnimationStartDate:(NSDate *)startDate                                                               API_DEPRECATED("Use the block-based animation API instead", ios(2.0, 13.0));
+ (void)setAnimationCurve:(UIViewAnimationCurve)curve                                                           API_DEPRECATED("Use the block-based animation API instead", ios(2.0, 13.0));
+ (void)setAnimationRepeatCount:(float)repeatCount                                                              API_DEPRECATED("Use the block-based animation API instead", ios(2.0, 13.0));
+ (void)setAnimationRepeatAutoreverses:(BOOL)repeatAutoreverses                                                 API_DEPRECATED("Use the block-based animation API instead", ios(2.0, 13.0));
+ (void)setAnimationBeginsFromCurrentState:(BOOL)fromCurrentState                                               API_DEPRECATED("Use the block-based animation API instead", ios(2.0, 13.0));
+ (void)setAnimationTransition:(UIViewAnimationTransition)transition forView:(UIView *)view cache:(BOOL)cache   API_DEPRECATED("Use the block-based animation API instead", ios(2.0, 13.0));

@end

@interface UIView (UserInterfaceStyle)

/* Set `overrideUserInterfaceStyle` to cause this view and its subviews to have a specific `UIUserInterfaceStyle`.
 * Reading this property does not return the current `UIUserInterfaceStyle`. Use `traitCollection.userInterfaceStyle` instead.
 *
 * Whenever possible, use the `overrideUserInterfaceStyle` property on `UIViewController` instead.
 *
 * Use this property only when:
 * - You want a particular style on a single view or small view hierarchy.
 * - You want a particular style on an entire `UIWindow` and its view controllers and presentations,
 *   but don't want to force your entire application to have that style.
 *
 *  (If you do want your entire application to have a certain style, don't use this, but instead
 *   set the `UIUserInterfaceStyle" key in your Info.plist.)
 *
 * When set on an ordinary `UIView`:
 * - This property affects only the traits of this view and its subviews.
 * - It does not affect any view controllers, or any subviews that are owned by different view controllers.
 *
 * When set on a `UIWindow`:
 * - This property affects the `rootViewController` and thus the entire view controller and view hierarchy.
 * - It also affects presentations that happen inside the window.
 */
@property (nonatomic) UIUserInterfaceStyle overrideUserInterfaceStyle API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIView.h>
#endif
