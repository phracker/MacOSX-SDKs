#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPageViewController.h>)
//
//  UIPageViewController.h
//  UIKit
//
//  Copyright 2011-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIViewController.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UIPageViewControllerNavigationOrientation) {
    UIPageViewControllerNavigationOrientationHorizontal = 0,
    UIPageViewControllerNavigationOrientationVertical = 1
} API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIPageViewControllerSpineLocation) {
    UIPageViewControllerSpineLocationNone = 0, // Returned if 'spineLocation' is queried when 'transitionStyle' is not 'UIPageViewControllerTransitionStylePageCurl'.
    UIPageViewControllerSpineLocationMin = 1,  // Requires one view controller.
    UIPageViewControllerSpineLocationMid = 2,  // Requires two view controllers.
    UIPageViewControllerSpineLocationMax = 3   // Requires one view controller.
} API_UNAVAILABLE(watchos);   // Only pertains to 'UIPageViewControllerTransitionStylePageCurl'.

typedef NS_ENUM(NSInteger, UIPageViewControllerNavigationDirection) {
    UIPageViewControllerNavigationDirectionForward,
    UIPageViewControllerNavigationDirectionReverse
} API_UNAVAILABLE(watchos);  // For 'UIPageViewControllerNavigationOrientationHorizontal', 'forward' is right-to-left, like pages in a book. For 'UIPageViewControllerNavigationOrientationVertical', bottom-to-top, like pages in a wall calendar.

typedef NS_ENUM(NSInteger, UIPageViewControllerTransitionStyle) {
    UIPageViewControllerTransitionStylePageCurl = 0, // Navigate between views via a page curl transition.
    UIPageViewControllerTransitionStyleScroll = 1 // Navigate between views by scrolling.
} API_UNAVAILABLE(watchos);

typedef NSString * UIPageViewControllerOptionsKey NS_TYPED_ENUM API_UNAVAILABLE(watchos);

// Key for specifying spine location in options dictionary argument to initWithTransitionStyle:navigationOrientation:options:.
// Value should be a 'UIPageViewControllerSpineLocation' wrapped in an NSNumber.
// Only valid for use with page view controllers with transition style 'UIPageViewControllerTransitionStylePageCurl'.
UIKIT_EXTERN UIPageViewControllerOptionsKey const UIPageViewControllerOptionSpineLocationKey API_UNAVAILABLE(watchos);

// Key for specifying spacing between pages in options dictionary argument to initWithTransitionStyle:navigationOrientation:options:.
// Value should be a CGFloat wrapped in an NSNumber. Default is '0'.
// Only valid for use with page view controllers with transition style 'UIPageViewControllerTransitionStyleScroll'.
UIKIT_EXTERN UIPageViewControllerOptionsKey const UIPageViewControllerOptionInterPageSpacingKey API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(watchos);

@protocol UIPageViewControllerDelegate, UIPageViewControllerDataSource;

UIKIT_EXTERN API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIPageViewController : UIViewController {
}

- (instancetype)initWithTransitionStyle:(UIPageViewControllerTransitionStyle)style navigationOrientation:(UIPageViewControllerNavigationOrientation)navigationOrientation options:(nullable NSDictionary<UIPageViewControllerOptionsKey, id> *)options NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (nullable, nonatomic, weak) id <UIPageViewControllerDelegate> delegate;
@property (nullable, nonatomic, weak) id <UIPageViewControllerDataSource> dataSource; // If nil, user gesture-driven navigation will be disabled.
@property (nonatomic, readonly) UIPageViewControllerTransitionStyle transitionStyle;
@property (nonatomic, readonly) UIPageViewControllerNavigationOrientation navigationOrientation;
@property (nonatomic, readonly) UIPageViewControllerSpineLocation spineLocation; // If transition style is 'UIPageViewControllerTransitionStylePageCurl', default is 'UIPageViewControllerSpineLocationMin', otherwise 'UIPageViewControllerSpineLocationNone'.

// Whether client content appears on both sides of each page. If 'NO', content on page front will partially show through back.
// If 'UIPageViewControllerSpineLocationMid' is set, 'doubleSided' is set to 'YES'. Setting 'NO' when spine location is mid results in an exception.
@property (nonatomic, getter=isDoubleSided) BOOL doubleSided; // Default is 'NO'.

// An array of UIGestureRecognizers pre-configured to handle user interaction. Initially attached to a view in the UIPageViewController's hierarchy, they can be placed on an arbitrary view to change the region in which the page view controller will respond to user gestures.
// Only populated if transition style is 'UIPageViewControllerTransitionStylePageCurl'.

@property(nonatomic, readonly) NSArray<__kindof UIGestureRecognizer *> *gestureRecognizers;
@property (nullable, nonatomic, readonly) NSArray<__kindof UIViewController *> *viewControllers;

// Set visible view controllers, optionally with animation. Array should only include view controllers that will be visible after the animation has completed.
// For transition style 'UIPageViewControllerTransitionStylePageCurl', if 'doubleSided' is 'YES' and the spine location is not 'UIPageViewControllerSpineLocationMid', two view controllers must be included, as the latter view controller is used as the back.
- (void)setViewControllers:(nullable NSArray<UIViewController *> *)viewControllers direction:(UIPageViewControllerNavigationDirection)direction animated:(BOOL)animated completion:(void (^ __nullable)(BOOL finished))completion NS_SWIFT_DISABLE_ASYNC;

@end

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIPageViewControllerDelegate <NSObject>

@optional

// Sent when a gesture-initiated transition begins.
- (void)pageViewController:(UIPageViewController *)pageViewController willTransitionToViewControllers:(NSArray<UIViewController *> *)pendingViewControllers API_AVAILABLE(ios(6.0));

// Sent when a gesture-initiated transition ends. The 'finished' parameter indicates whether the animation finished, while the 'completed' parameter indicates whether the transition completed or bailed out (if the user let go early).
- (void)pageViewController:(UIPageViewController *)pageViewController didFinishAnimating:(BOOL)finished previousViewControllers:(NSArray<UIViewController *> *)previousViewControllers transitionCompleted:(BOOL)completed;

// Delegate may specify a different spine location for after the interface orientation change. Only sent for transition style 'UIPageViewControllerTransitionStylePageCurl'.
// Delegate may set new view controllers or update double-sided state within this method's implementation as well.
- (UIPageViewControllerSpineLocation)pageViewController:(UIPageViewController *)pageViewController spineLocationForInterfaceOrientation:(UIInterfaceOrientation)orientation API_UNAVAILABLE(tvos);

- (UIInterfaceOrientationMask)pageViewControllerSupportedInterfaceOrientations:(UIPageViewController *)pageViewController API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(tvos);
- (UIInterfaceOrientation)pageViewControllerPreferredInterfaceOrientationForPresentation:(UIPageViewController *)pageViewController API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(tvos);

@end

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIPageViewControllerDataSource <NSObject>

@required

// In terms of navigation direction. For example, for 'UIPageViewControllerNavigationOrientationHorizontal', view controllers coming 'before' would be to the left of the argument view controller, those coming 'after' would be to the right.
// Return 'nil' to indicate that no more progress can be made in the given direction.
// For gesture-initiated transitions, the page view controller obtains view controllers via these methods, so use of setViewControllers:direction:animated:completion: is not required.
- (nullable UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerBeforeViewController:(UIViewController *)viewController;
- (nullable UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerAfterViewController:(UIViewController *)viewController;

@optional

// A page indicator will be visible if both methods are implemented, transition style is 'UIPageViewControllerTransitionStyleScroll', and navigation orientation is 'UIPageViewControllerNavigationOrientationHorizontal'.
// Both methods are called in response to a 'setViewControllers:...' call, but the presentation index is updated automatically in the case of gesture-driven navigation.
- (NSInteger)presentationCountForPageViewController:(UIPageViewController *)pageViewController API_AVAILABLE(ios(6.0)); // The number of items reflected in the page indicator.
- (NSInteger)presentationIndexForPageViewController:(UIPageViewController *)pageViewController API_AVAILABLE(ios(6.0)); // The selected item reflected in the page indicator.

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIPageViewController.h>
#endif
