#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIScrollView.h>)
//
//  UIScrollView.h
//  UIKit
//
//  Copyright (c) 2007-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIRefreshControl.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UIScrollViewIndicatorStyle) {
    UIScrollViewIndicatorStyleDefault,     // Automatically switches appearance based on the user interface style
    UIScrollViewIndicatorStyleBlack,       // Dark indicator, for use on light backgrounds
    UIScrollViewIndicatorStyleWhite        // Light indicator, for use on dark backgrounds
} API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIScrollViewKeyboardDismissMode) {
    UIScrollViewKeyboardDismissModeNone,
    UIScrollViewKeyboardDismissModeOnDrag,      // dismisses the keyboard when a drag begins
    UIScrollViewKeyboardDismissModeInteractive, // the keyboard follows the dragging touch off screen, and may be pulled upward again to cancel the dismiss
    UIScrollViewKeyboardDismissModeOnDragWithAccessory,       // dismisses both keyboard and accessory in the style of UIScrollViewKeyboardDismissModeOnDrag
    UIScrollViewKeyboardDismissModeInteractiveWithAccessory   // dismisses both keyboard and accessory in the style of UIScrollViewKeyboardDismissModeInteractive
} API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(visionos, watchos);

typedef NS_ENUM(NSInteger, UIScrollViewIndexDisplayMode) {
    UIScrollViewIndexDisplayModeAutomatic,    // the index will show or hide automatically as needed
    UIScrollViewIndexDisplayModeAlwaysHidden, // the index will never be displayed
} API_AVAILABLE(tvos(10.2)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIScrollViewContentInsetAdjustmentBehavior) {
    UIScrollViewContentInsetAdjustmentAutomatic, // Similar to .scrollableAxes, but for backward compatibility will also adjust the top & bottom contentInset when the scroll view is owned by a view controller with automaticallyAdjustsScrollViewInsets = YES inside a navigation controller, regardless of whether the scroll view is scrollable
    UIScrollViewContentInsetAdjustmentScrollableAxes, // Edges for scrollable axes are adjusted (i.e., contentSize.width/height > frame.size.width/height or alwaysBounceHorizontal/Vertical = YES)
    UIScrollViewContentInsetAdjustmentNever, // contentInset is not adjusted
    UIScrollViewContentInsetAdjustmentAlways, // contentInset is always adjusted by the scroll view's safeAreaInsets
} API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

typedef CGFloat UIScrollViewDecelerationRate NS_TYPED_ENUM API_UNAVAILABLE(watchos);

UIKIT_EXTERN const UIScrollViewDecelerationRate UIScrollViewDecelerationRateNormal API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(watchos);
UIKIT_EXTERN const UIScrollViewDecelerationRate UIScrollViewDecelerationRateFast API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(watchos);

/// Styles for a scroll view's edge effect.
UIKIT_FINAL UIKIT_EXTERN NS_SWIFT_UI_ACTOR API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(UIScrollEdgeEffect.Style)
@interface UIScrollEdgeEffectStyle : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The automatic scroll edge effect style.
@property (nonatomic, readonly, class) UIScrollEdgeEffectStyle *automaticStyle;

/// A soft-edged scroll edge effect.
@property (nonatomic, readonly, class) UIScrollEdgeEffectStyle *softStyle;

/// A scroll edge effect with a hard cutoff and dividing line.
@property (nonatomic, readonly, class) UIScrollEdgeEffectStyle *hardStyle;

@end

/// Properties of the effect on a particular edge of the scroll view.
UIKIT_FINAL UIKIT_EXTERN NS_SWIFT_UI_ACTOR API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
@interface UIScrollEdgeEffect : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The style of this edge effect.
@property (nonatomic, strong) UIScrollEdgeEffectStyle *style;

/// Whether this edge effect is hidden.
/// Default: false
@property (nonatomic, getter=isHidden) BOOL hidden;

@end

@class UIEvent, UIImageView, UIPanGestureRecognizer, UIPinchGestureRecognizer;
@protocol UIScrollViewDelegate;

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIScrollView : UIView <NSCoding, UIFocusItemScrollableContainer>

@property(nonatomic)         CGPoint                      contentOffset;                  // default CGPointZero
@property(nonatomic)         CGSize                       contentSize;                    // default CGSizeZero
@property(nonatomic)         UIEdgeInsets                 contentInset;                   // default UIEdgeInsetsZero. add additional scroll area around content

// A unit point that describes how to align the scroll view content when the content size is smaller than the scroll view bounds.
// For example, (0, 0) aligns the content to the top left, (0.5, 0.5) centers the content, and (0.5, 1.0) would align the content to the bottom center.
// Default: CGPointZero
@property (nonatomic) CGPoint contentAlignmentPoint API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos);

/* When contentInsetAdjustmentBehavior allows, UIScrollView may incorporate
 its safeAreaInsets into the adjustedContentInset.
 */
@property(nonatomic, readonly) UIEdgeInsets adjustedContentInset API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

/* Also see -scrollViewDidChangeAdjustedContentInset: in the UIScrollViewDelegate protocol.
 */
- (void)adjustedContentInsetDidChange API_AVAILABLE(ios(11.0),tvos(11.0)) NS_REQUIRES_SUPER API_UNAVAILABLE(watchos);

/* Configure the behavior of adjustedContentInset.
 Default is UIScrollViewContentInsetAdjustmentAutomatic.
 */
@property(nonatomic) UIScrollViewContentInsetAdjustmentBehavior contentInsetAdjustmentBehavior API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

/* Configures whether the scroll indicator insets are automatically adjusted by the system.
 Default is YES.
 */
@property(nonatomic) BOOL automaticallyAdjustsScrollIndicatorInsets API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

/* contentLayoutGuide anchors (e.g., contentLayoutGuide.centerXAnchor, etc.) refer to
 the untranslated content area of the scroll view.
 */
@property(nonatomic,readonly,strong) UILayoutGuide *contentLayoutGuide API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

/* frameLayoutGuide anchors (e.g., frameLayoutGuide.centerXAnchor) refer to
 the untransformed frame of the scroll view.
 */
@property(nonatomic,readonly,strong) UILayoutGuide *frameLayoutGuide API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

@property(nullable,nonatomic,weak) id<UIScrollViewDelegate>        delegate;                       // default nil. weak reference
@property(nonatomic,getter=isDirectionalLockEnabled) BOOL directionalLockEnabled;         // default NO. if YES, try to lock vertical or horizontal scrolling while dragging

// If YES, bounces past the edge of the content and back again.
// Setting this property is a convenience for setting both `bouncesHorizontally` and `bouncesVertically`.
// Only returns YES if both `bouncesHorizontally` and `bouncesVertically` are YES.
// Default: YES
@property (nonatomic) BOOL bounces;

// If YES, bounces past the left and right edges of the content and back again.
// Setting the `bounces` property will set this axis-specific value.
// Default: YES
@property (nonatomic) BOOL bouncesHorizontally API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos);

// If YES, bounces past the top and bottom edges of the content and back again.
// Setting the `bounces` property will set this axis-specific value.
// Default: YES
@property (nonatomic) BOOL bouncesVertically API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos);

@property(nonatomic)         BOOL                         alwaysBounceVertical;           // default NO. if YES and bounces is YES, even if content is smaller than bounds, allow drag vertically
@property(nonatomic)         BOOL                         alwaysBounceHorizontal;         // default NO. if YES and bounces is YES, even if content is smaller than bounds, allow drag horizontally
@property(nonatomic,getter=isPagingEnabled) BOOL          pagingEnabled API_UNAVAILABLE(tvos);// default NO. if YES, stop on multiples of view bounds
@property(nonatomic,getter=isScrollEnabled) BOOL          scrollEnabled;                  // default YES. turn off any dragging temporarily

// If YES, scrolling horizontally past the left and right edges of the content will start scrolling parent scroll views.
// Default: YES
@property (nonatomic) BOOL transfersHorizontalScrollingToParent API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos);

// If YES, scrolling vertically past the top and bottom edges of the content will start scrolling parent scroll views.
// Default: YES
@property (nonatomic) BOOL transfersVerticalScrollingToParent API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos);

@property(nonatomic)         BOOL                         showsVerticalScrollIndicator;   // default YES. show indicator while we are tracking. fades out after tracking
@property(nonatomic)         BOOL                         showsHorizontalScrollIndicator; // default YES. show indicator while we are tracking. fades out after tracking
@property(nonatomic)         UIScrollViewIndicatorStyle   indicatorStyle;                 // default is UIScrollViewIndicatorStyleDefault

@property(nonatomic)         UIEdgeInsets                 verticalScrollIndicatorInsets API_AVAILABLE(ios(11.1), tvos(11.1)) API_UNAVAILABLE(watchos); // default is UIEdgeInsetsZero.
@property(nonatomic)         UIEdgeInsets                 horizontalScrollIndicatorInsets API_AVAILABLE(ios(11.1), tvos(11.1)) API_UNAVAILABLE(watchos); // default is UIEdgeInsetsZero.
@property(nonatomic)         UIEdgeInsets                 scrollIndicatorInsets; // use the setter only, as a convenience for setting both verticalScrollIndicatorInsets and horizontalScrollIndicatorInsets to the same value. if those properties have been set to different values, the return value of this getter (deprecated) is undefined.
- (UIEdgeInsets)scrollIndicatorInsets API_DEPRECATED("The scrollIndicatorInsets getter is deprecated, use the verticalScrollIndicatorInsets and horizontalScrollIndicatorInsets getters instead.", ios(2.0, 13.0), tvos(9.0, 13.0)) API_UNAVAILABLE(visionos);
@property(nonatomic)         UIScrollViewDecelerationRate decelerationRate API_AVAILABLE(ios(3.0));
@property(nonatomic)         UIScrollViewIndexDisplayMode indexDisplayMode API_AVAILABLE(tvos(10.2)) API_UNAVAILABLE(watchos);

- (void)setContentOffset:(CGPoint)contentOffset animated:(BOOL)animated;  // animate at constant velocity to new offset
- (void)scrollRectToVisible:(CGRect)rect animated:(BOOL)animated;         // scroll so rect is just visible (nearest edges). nothing if rect completely visible

// Displays the scroll indicators for a short time. This should be done whenever you bring the scroll view to front.
- (void)flashScrollIndicators;

// Shows scroll indicators immediately as a result of any contentOffset changes performed within the block.
// Scroll indicators are only shown on axes where the contentOffset changes.
// If contentOffset is set without animation, the scroll indicators will fade out after a delay.
// If contentOffset is set with animation, the scroll indicators will fade out when the animation completes.
- (void)withScrollIndicatorsShownForContentOffsetChanges:(void (NS_NOESCAPE ^)(void))changes API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos);

/// The following properties can be used to access and modify the effect on a particular edge.
///
/// In the following example, the hard style is set for the top edge.
///
///     scrollView.topEdgeEffect.style = .hard
///

/// The effect for the top edge of the scroll view.
@property (nonatomic, readonly) UIScrollEdgeEffect *topEdgeEffect API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// The effect for the left edge of the scroll view.
@property (nonatomic, readonly) UIScrollEdgeEffect *leftEdgeEffect API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// The effect for the bottom edge of the scroll view.
@property (nonatomic, readonly) UIScrollEdgeEffect *bottomEdgeEffect API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// The effect for the right edge of the scroll view.
@property (nonatomic, readonly) UIScrollEdgeEffect *rightEdgeEffect API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/*
 Scrolling with no scroll bars is a bit complex. on touch down, we don't know if the user will want to scroll or track a subview like a control.
 on touch down, we start a timer and also look at any movement. if the time elapses without sufficient change in position, we start sending events to
 the hit view in the content subview. if the user then drags far enough, we switch back to dragging and cancel any tracking in the subview.
 the methods below are called by the scroll view and give subclasses override points to add in custom behavior.
 you can remove the delay in delivery of touchesBegan:withEvent: to subviews by setting delaysContentTouches to NO.
 */

// Returns YES if user has touched. May not yet have started dragging
@property(nonatomic, readonly, getter=isTracking) BOOL tracking;

// Returns YES if user has started scrolling. It may require some time and/or distance to move to initiate dragging
@property(nonatomic, readonly, getter=isDragging) BOOL dragging;

// Returns YES if user isn't dragging (touch up) but scroll view is still moving
@property(nonatomic, readonly, getter=isDecelerating) BOOL decelerating;

// Returns YES if the scroll view is currently animating a `contentOffset` change
// For example, this could be from a `setContentOffset:animated:` call
// Note that deceleration will *not* cause this property to be YES
@property (nonatomic, readonly, getter=isScrollAnimating) BOOL scrollAnimating API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos);

@property(nonatomic) BOOL delaysContentTouches;       // default is YES. if NO, we immediately call -touchesShouldBegin:withEvent:inContentView:. this has no effect on presses
@property(nonatomic) BOOL canCancelContentTouches;    // default is YES. if NO, then once we start tracking, we don't try to drag if the touch moves. this has no effect on presses

// override points for subclasses to control delivery of touch events to subviews of the scroll view
// called before touches are delivered to a subview of the scroll view. if it returns NO the touches will not be delivered to the subview
// this has no effect on presses
// default returns YES
- (BOOL)touchesShouldBegin:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event inContentView:(UIView *)view;
// called before scrolling begins if touches have already been delivered to a subview of the scroll view. if it returns NO the touches will continue to be delivered to the subview and scrolling will not occur
// not called if canCancelContentTouches is NO. default returns YES if view isn't a UIControl
// this has no effect on presses
- (BOOL)touchesShouldCancelInContentView:(UIView *)view;

/*
 the following properties and methods are for zooming. as the user tracks with two fingers, we adjust the offset and the scale of the content. When the gesture ends, you should update the content
 as necessary. Note that the gesture can end and a finger could still be down. While the gesture is in progress, we do not send any tracking calls to the subview.
 the delegate must implement both viewForZoomingInScrollView: and scrollViewDidEndZooming:withView:atScale: in order for zooming to work and the max/min zoom scale must be different
 note that we are not scaling the actual scroll view but the 'content view' returned by the delegate. the delegate must return a subview, not the scroll view itself, from viewForZoomingInScrollview:
 */

@property(nonatomic) CGFloat minimumZoomScale;     // default is 1.0
@property(nonatomic) CGFloat maximumZoomScale;     // default is 1.0. must be > minimum zoom scale to enable zooming

@property(nonatomic) CGFloat zoomScale API_AVAILABLE(ios(3.0));            // default is 1.0
- (void)setZoomScale:(CGFloat)scale animated:(BOOL)animated API_AVAILABLE(ios(3.0));
- (void)zoomToRect:(CGRect)rect animated:(BOOL)animated API_AVAILABLE(ios(3.0));

// If set, the user can zoom past the min/max scale while gesturing and the scale will animate to the min/max value when the gesture ends
// Default: YES
@property (nonatomic) BOOL bouncesZoom;

// Returns YES if the user is performing a zoom gesture
@property (nonatomic, readonly, getter=isZooming) BOOL zooming;

// Returns YES if ths scroll view is in the middle of zooming back to the min/max zoom scale
@property (nonatomic, readonly, getter=isZoomBouncing) BOOL zoomBouncing;

// Returns YES if the scroll view is currently animating a `zoomScale` change
// For example, this could be from a `setZoomScale:animated:` call
@property (nonatomic, readonly, getter=isZoomAnimating) BOOL zoomAnimating API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos);

// When the user taps the status bar, the scroll view beneath the touch which is closest to the status bar will be scrolled to top, but only if its `scrollsToTop` property is YES, its delegate does not return NO from `-scrollViewShouldScrollToTop:`, and it is not already at the top.
// On iPhone, we execute this gesture only if there's one on-screen scroll view with `scrollsToTop` == YES. If more than one is found, none will be scrolled.
// Default: YES
@property (nonatomic) BOOL scrollsToTop API_UNAVAILABLE(tvos);

// Stops any scrolling or zooming, whether initiated programmatically or by the user
// Stops scrolling at the current `contentOffset` during deceleration unless bouncing, in which case the `contentOffset` is moved within the valid range
// If paging is enabled, aligns `contentOffset` with a page boundary
- (void)stopScrollingAndZooming API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos);

// Use these accessors to configure the scroll view's built-in gesture recognizers.
// Do not change the gestures' delegates or override the getters for these properties.

// Change `panGestureRecognizer.allowedTouchTypes` to limit scrolling to a particular set of touch types.
@property(nonatomic, readonly) UIPanGestureRecognizer *panGestureRecognizer API_AVAILABLE(ios(5.0));
// `pinchGestureRecognizer` will return nil when zooming is disabled.
@property(nullable, nonatomic, readonly) UIPinchGestureRecognizer *pinchGestureRecognizer API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos);
// `directionalPressGestureRecognizer` is disabled by default, but can be enabled to perform scrolling in response to up / down / left / right arrow button presses directly, instead of scrolling indirectly in response to focus updates.
@property(nonatomic, readonly) UIGestureRecognizer *directionalPressGestureRecognizer API_DEPRECATED("Configuring the panGestureRecognizer for indirect scrolling automatically supports directional presses now, so this property is no longer useful.", tvos(9.0, 11.0)) API_UNAVAILABLE(watchos);

@property(nonatomic) UIScrollViewKeyboardDismissMode keyboardDismissMode API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(visionos); // default is UIScrollViewKeyboardDismissModeNone

@property (nonatomic, strong, nullable) UIRefreshControl *refreshControl API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(tvos, watchos);

/// Set this to YES to make the scroll view animate its content offset in response to keys like Page Up/Down, Home/End, and the arrow keys.
/// The scroll view must be focused or first responder in order to receive these key events. Default is YES for apps linked after iOS 17.0.
@property (nonatomic, assign) BOOL allowsKeyboardScrolling API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

/// Defines which axes are considered for Look to Scroll.
/// Does not affect when isPagingEnabled is true.
@property (nonatomic) UIAxis lookToScrollAxes API_AVAILABLE(visionos(26.0)) API_UNAVAILABLE(ios, watchos, tvos);

@end

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIScrollViewDelegate<NSObject>

@optional

- (void)scrollViewDidScroll:(UIScrollView *)scrollView;                                               // any offset changes
- (void)scrollViewDidZoom:(UIScrollView *)scrollView API_AVAILABLE(ios(3.2)); // any zoom scale changes

// called on start of dragging (may require some time and or distance to move)
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView;
// called on finger up if the user dragged. velocity is in points/millisecond. targetContentOffset may be changed to adjust where the scroll view comes to rest
- (void)scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset API_AVAILABLE(ios(5.0));
// called on finger up if the user dragged. decelerate is true if it will continue moving afterwards
- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate;

- (void)scrollViewWillBeginDecelerating:(UIScrollView *)scrollView;   // called on finger up as we are moving
- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView;      // called when scroll view grinds to a halt

- (void)scrollViewDidEndScrollingAnimation:(UIScrollView *)scrollView; // called when setContentOffset/scrollRectVisible:animated: finishes. not called if not animating

- (nullable UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView;     // return a view that will be scaled. if delegate returns nil, nothing happens
- (void)scrollViewWillBeginZooming:(UIScrollView *)scrollView withView:(nullable UIView *)view API_AVAILABLE(ios(3.2)); // called before the scroll view begins zooming its content
- (void)scrollViewDidEndZooming:(UIScrollView *)scrollView withView:(nullable UIView *)view atScale:(CGFloat)scale; // scale between minimum and maximum. called after any 'bounce' animations

- (BOOL)scrollViewShouldScrollToTop:(UIScrollView *)scrollView;   // return a yes if you want to scroll to the top. if not defined, assumes YES
- (void)scrollViewDidScrollToTop:(UIScrollView *)scrollView;      // called when scrolling animation finished. may be called immediately if already at top

/* Also see -[UIScrollView adjustedContentInsetDidChange]
 */
- (void)scrollViewDidChangeAdjustedContentInset:(UIScrollView *)scrollView API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIScrollView.h>
#endif
