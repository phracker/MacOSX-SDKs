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

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIScrollViewIndicatorStyle) {
    UIScrollViewIndicatorStyleDefault,     // Automatically switches appearance based on the user interface style
    UIScrollViewIndicatorStyleBlack,       // Dark indicator, for use on light backgrounds
    UIScrollViewIndicatorStyleWhite        // Light indicator, for use on dark backgrounds
};

typedef NS_ENUM(NSInteger, UIScrollViewKeyboardDismissMode) {
    UIScrollViewKeyboardDismissModeNone,
    UIScrollViewKeyboardDismissModeOnDrag,      // dismisses the keyboard when a drag begins
    UIScrollViewKeyboardDismissModeInteractive, // the keyboard follows the dragging touch off screen, and may be pulled upward again to cancel the dismiss
} API_AVAILABLE(ios(7.0));

typedef NS_ENUM(NSInteger, UIScrollViewIndexDisplayMode) {
    UIScrollViewIndexDisplayModeAutomatic,    // the index will show or hide automatically as needed
    UIScrollViewIndexDisplayModeAlwaysHidden, // the index will never be displayed
} API_AVAILABLE(tvos(10.2));

typedef NS_ENUM(NSInteger, UIScrollViewContentInsetAdjustmentBehavior) {
    UIScrollViewContentInsetAdjustmentAutomatic, // Similar to .scrollableAxes, but for backward compatibility will also adjust the top & bottom contentInset when the scroll view is owned by a view controller with automaticallyAdjustsScrollViewInsets = YES inside a navigation controller, regardless of whether the scroll view is scrollable
    UIScrollViewContentInsetAdjustmentScrollableAxes, // Edges for scrollable axes are adjusted (i.e., contentSize.width/height > frame.size.width/height or alwaysBounceHorizontal/Vertical = YES)
    UIScrollViewContentInsetAdjustmentNever, // contentInset is not adjusted
    UIScrollViewContentInsetAdjustmentAlways, // contentInset is always adjusted by the scroll view's safeAreaInsets
} API_AVAILABLE(ios(11.0),tvos(11.0));

typedef CGFloat UIScrollViewDecelerationRate NS_TYPED_ENUM;

UIKIT_EXTERN const UIScrollViewDecelerationRate UIScrollViewDecelerationRateNormal API_AVAILABLE(ios(3.0));
UIKIT_EXTERN const UIScrollViewDecelerationRate UIScrollViewDecelerationRateFast API_AVAILABLE(ios(3.0));

@class UIEvent, UIImageView, UIPanGestureRecognizer, UIPinchGestureRecognizer;
@protocol UIScrollViewDelegate;

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) NS_SWIFT_UI_ACTOR
@interface UIScrollView : UIView <NSCoding, UIFocusItemScrollableContainer>

@property(nonatomic)         CGPoint                      contentOffset;                  // default CGPointZero
@property(nonatomic)         CGSize                       contentSize;                    // default CGSizeZero
@property(nonatomic)         UIEdgeInsets                 contentInset;                   // default UIEdgeInsetsZero. add additional scroll area around content

/* When contentInsetAdjustmentBehavior allows, UIScrollView may incorporate
 its safeAreaInsets into the adjustedContentInset.
 */
@property(nonatomic, readonly) UIEdgeInsets adjustedContentInset API_AVAILABLE(ios(11.0),tvos(11.0));

/* Also see -scrollViewDidChangeAdjustedContentInset: in the UIScrollViewDelegate protocol.
 */
- (void)adjustedContentInsetDidChange API_AVAILABLE(ios(11.0),tvos(11.0)) NS_REQUIRES_SUPER;

/* Configure the behavior of adjustedContentInset.
 Default is UIScrollViewContentInsetAdjustmentAutomatic.
 */
@property(nonatomic) UIScrollViewContentInsetAdjustmentBehavior contentInsetAdjustmentBehavior API_AVAILABLE(ios(11.0),tvos(11.0));

/* Configures whether the scroll indicator insets are automatically adjusted by the system.
 Default is YES.
 */
@property(nonatomic) BOOL automaticallyAdjustsScrollIndicatorInsets API_AVAILABLE(ios(13.0), tvos(13.0));

/* contentLayoutGuide anchors (e.g., contentLayoutGuide.centerXAnchor, etc.) refer to
 the untranslated content area of the scroll view.
 */
@property(nonatomic,readonly,strong) UILayoutGuide *contentLayoutGuide API_AVAILABLE(ios(11.0),tvos(11.0));

/* frameLayoutGuide anchors (e.g., frameLayoutGuide.centerXAnchor) refer to
 the untransformed frame of the scroll view.
 */
@property(nonatomic,readonly,strong) UILayoutGuide *frameLayoutGuide API_AVAILABLE(ios(11.0),tvos(11.0));

@property(nullable,nonatomic,weak) id<UIScrollViewDelegate>        delegate;                       // default nil. weak reference
@property(nonatomic,getter=isDirectionalLockEnabled) BOOL directionalLockEnabled;         // default NO. if YES, try to lock vertical or horizontal scrolling while dragging
@property(nonatomic)         BOOL                         bounces;                        // default YES. if YES, bounces past edge of content and back again
@property(nonatomic)         BOOL                         alwaysBounceVertical;           // default NO. if YES and bounces is YES, even if content is smaller than bounds, allow drag vertically
@property(nonatomic)         BOOL                         alwaysBounceHorizontal;         // default NO. if YES and bounces is YES, even if content is smaller than bounds, allow drag horizontally
@property(nonatomic,getter=isPagingEnabled) BOOL          pagingEnabled API_UNAVAILABLE(tvos);// default NO. if YES, stop on multiples of view bounds
@property(nonatomic,getter=isScrollEnabled) BOOL          scrollEnabled;                  // default YES. turn off any dragging temporarily

@property(nonatomic)         BOOL                         showsVerticalScrollIndicator;   // default YES. show indicator while we are tracking. fades out after tracking
@property(nonatomic)         BOOL                         showsHorizontalScrollIndicator; // default YES. show indicator while we are tracking. fades out after tracking
@property(nonatomic)         UIScrollViewIndicatorStyle   indicatorStyle;                 // default is UIScrollViewIndicatorStyleDefault

@property(nonatomic)         UIEdgeInsets                 verticalScrollIndicatorInsets API_AVAILABLE(ios(11.1), tvos(11.1)); // default is UIEdgeInsetsZero.
@property(nonatomic)         UIEdgeInsets                 horizontalScrollIndicatorInsets API_AVAILABLE(ios(11.1), tvos(11.1)); // default is UIEdgeInsetsZero.
@property(nonatomic)         UIEdgeInsets                 scrollIndicatorInsets; // use the setter only, as a convenience for setting both verticalScrollIndicatorInsets and horizontalScrollIndicatorInsets to the same value. if those properties have been set to different values, the return value of this getter (deprecated) is undefined.
- (UIEdgeInsets)scrollIndicatorInsets API_DEPRECATED("The scrollIndicatorInsets getter is deprecated, use the verticalScrollIndicatorInsets and horizontalScrollIndicatorInsets getters instead.", ios(2.0, 13.0), tvos(9.0, 13.0));
@property(nonatomic)         UIScrollViewDecelerationRate decelerationRate API_AVAILABLE(ios(3.0));
@property(nonatomic)         UIScrollViewIndexDisplayMode indexDisplayMode API_AVAILABLE(tvos(10.2));

- (void)setContentOffset:(CGPoint)contentOffset animated:(BOOL)animated;  // animate at constant velocity to new offset
- (void)scrollRectToVisible:(CGRect)rect animated:(BOOL)animated;         // scroll so rect is just visible (nearest edges). nothing if rect completely visible

- (void)flashScrollIndicators;             // displays the scroll indicators for a short time. This should be done whenever you bring the scroll view to front.

/*
 Scrolling with no scroll bars is a bit complex. on touch down, we don't know if the user will want to scroll or track a subview like a control.
 on touch down, we start a timer and also look at any movement. if the time elapses without sufficient change in position, we start sending events to
 the hit view in the content subview. if the user then drags far enough, we switch back to dragging and cancel any tracking in the subview.
 the methods below are called by the scroll view and give subclasses override points to add in custom behavior.
 you can remove the delay in delivery of touchesBegan:withEvent: to subviews by setting delaysContentTouches to NO.
 */

@property(nonatomic,readonly,getter=isTracking)     BOOL tracking;        // returns YES if user has touched. may not yet have started dragging
@property(nonatomic,readonly,getter=isDragging)     BOOL dragging;        // returns YES if user has started scrolling. this may require some time and or distance to move to initiate dragging
@property(nonatomic,readonly,getter=isDecelerating) BOOL decelerating;    // returns YES if user isn't dragging (touch up) but scroll view is still moving

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

@property(nonatomic) BOOL  bouncesZoom;          // default is YES. if set, user can go past min/max zoom while gesturing and the zoom will animate to the min/max value at gesture end

@property(nonatomic,readonly,getter=isZooming)       BOOL zooming;       // returns YES if user in zoom gesture
@property(nonatomic,readonly,getter=isZoomBouncing)  BOOL zoomBouncing;  // returns YES if we are in the middle of zooming back to the min/max value

// When the user taps the status bar, the scroll view beneath the touch which is closest to the status bar will be scrolled to top, but only if its `scrollsToTop` property is YES, its delegate does not return NO from `-scrollViewShouldScrollToTop:`, and it is not already at the top.
// On iPhone, we execute this gesture only if there's one on-screen scroll view with `scrollsToTop` == YES. If more than one is found, none will be scrolled.
@property(nonatomic) BOOL  scrollsToTop API_UNAVAILABLE(tvos);          // default is YES.

// Use these accessors to configure the scroll view's built-in gesture recognizers.
// Do not change the gestures' delegates or override the getters for these properties.

// Change `panGestureRecognizer.allowedTouchTypes` to limit scrolling to a particular set of touch types.
@property(nonatomic, readonly) UIPanGestureRecognizer *panGestureRecognizer API_AVAILABLE(ios(5.0));
// `pinchGestureRecognizer` will return nil when zooming is disabled.
@property(nullable, nonatomic, readonly) UIPinchGestureRecognizer *pinchGestureRecognizer API_AVAILABLE(ios(5.0));
// `directionalPressGestureRecognizer` is disabled by default, but can be enabled to perform scrolling in response to up / down / left / right arrow button presses directly, instead of scrolling indirectly in response to focus updates.
@property(nonatomic, readonly) UIGestureRecognizer *directionalPressGestureRecognizer API_DEPRECATED("Configuring the panGestureRecognizer for indirect scrolling automatically supports directional presses now, so this property is no longer useful.", tvos(9.0, 11.0));

@property(nonatomic) UIScrollViewKeyboardDismissMode keyboardDismissMode API_AVAILABLE(ios(7.0)); // default is UIScrollViewKeyboardDismissModeNone

@property (nonatomic, strong, nullable) UIRefreshControl *refreshControl API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(tvos);

@end

NS_SWIFT_UI_ACTOR
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
- (void)scrollViewDidChangeAdjustedContentInset:(UIScrollView *)scrollView API_AVAILABLE(ios(11.0), tvos(11.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIScrollView.h>
#endif
