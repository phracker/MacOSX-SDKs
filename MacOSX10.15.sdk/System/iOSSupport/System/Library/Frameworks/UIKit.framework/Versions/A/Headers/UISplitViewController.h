#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISplitViewController.h>)
//
//  UISplitViewController.h
//  UIKit
//
//  Copyright (c) 2009-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIViewController.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@protocol UISplitViewControllerDelegate;

typedef NS_ENUM(NSInteger, UISplitViewControllerDisplayMode) {
    UISplitViewControllerDisplayModeAutomatic,
    UISplitViewControllerDisplayModePrimaryHidden,
    UISplitViewControllerDisplayModeAllVisible,
    UISplitViewControllerDisplayModePrimaryOverlay,
} API_AVAILABLE(ios(8.0));

typedef NS_ENUM(NSInteger, UISplitViewControllerPrimaryEdge) {
    UISplitViewControllerPrimaryEdgeLeading,
    UISplitViewControllerPrimaryEdgeTrailing,
} API_AVAILABLE(ios(11.0), tvos(11.0));

typedef NS_ENUM(NSInteger, UISplitViewControllerBackgroundStyle) {
    UISplitViewControllerBackgroundStyleNone,
    UISplitViewControllerBackgroundStyleSidebar,
} API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos);

// This constant can be used with any sizing-related `UISplitViewController` properties to get the default system behavior.
UIKIT_EXTERN CGFloat const UISplitViewControllerAutomaticDimension API_AVAILABLE(ios(8.0));

UIKIT_EXTERN API_AVAILABLE(ios(3.2)) @interface UISplitViewController : UIViewController

@property (nonatomic, copy) NSArray<__kindof UIViewController *> *viewControllers;
@property (nullable, nonatomic, weak) id <UISplitViewControllerDelegate> delegate;

// If 'YES', hidden view can be presented and dismissed via a swipe gesture. Defaults to 'YES'.
@property (nonatomic) BOOL presentsWithGesture API_AVAILABLE(ios(5.1));

// Specifies whether the split view controller has collapsed its primary and secondary view controllers together
@property(nonatomic, readonly, getter=isCollapsed) BOOL collapsed  API_AVAILABLE(ios(8.0));

// An animatable property that controls how the primary view controller is hidden and displayed. A value of `UISplitViewControllerDisplayModeAutomatic` specifies the default behavior split view controller, which on an iPad, corresponds to an overlay mode in portrait and a side-by-side mode in landscape.
@property (nonatomic) UISplitViewControllerDisplayMode preferredDisplayMode API_AVAILABLE(ios(8.0));

// The actual current displayMode of the split view controller. This will never return `UISplitViewControllerDisplayModeAutomatic`.
@property (nonatomic, readonly) UISplitViewControllerDisplayMode displayMode API_AVAILABLE(ios(8.0));

// A system bar button item whose action will change the displayMode property depending on the result of targetDisplayModeForActionInSplitViewController:. When inserted into the navigation bar of the secondary view controller it will change its appearance to match its target display mode. When the target displayMode is PrimaryHidden, this will appear as a fullscreen button, for AllVisible or PrimaryOverlay it will appear as a Back button, and when it won't cause any action it will become hidden.
@property (nonatomic, readonly) UIBarButtonItem *displayModeButtonItem API_AVAILABLE(ios(8.0));

// An animatable property that can be used to adjust the relative width of the primary view controller in the split view controller. This preferred width will be limited by the maximum and minimum properties (and potentially other system heuristics).
@property(nonatomic, assign) CGFloat preferredPrimaryColumnWidthFraction API_AVAILABLE(ios(8.0)); // default: UISplitViewControllerAutomaticDimension

// An animatable property that can be used to adjust the minimum absolute width of the primary view controller in the split view controller.
@property(nonatomic, assign) CGFloat minimumPrimaryColumnWidth API_AVAILABLE(ios(8.0)); // default: UISplitViewControllerAutomaticDimension

// An animatable property that can be used to adjust the maximum absolute width of the primary view controller in the split view controller.
@property(nonatomic, assign) CGFloat maximumPrimaryColumnWidth API_AVAILABLE(ios(8.0)); // default: UISplitViewControllerAutomaticDimension

// The current primary view controller's column width.
@property(nonatomic,readonly) CGFloat primaryColumnWidth API_AVAILABLE(ios(8.0));

// The edge of the UISplitViewController where the primary view controller should be positioned
@property(nonatomic) UISplitViewControllerPrimaryEdge primaryEdge API_AVAILABLE(ios(11.0), tvos(11.0)); // default: UISplitViewControllerPrimaryEdgeLeading

// In a horizontally-regular environment this will set either the master or detail view controller depending on the original target. In a compact environment this defaults to a full screen presentation. In general the master or detail view controller will have implemented showViewController:sender: so this method would not be invoked.
- (void)showViewController:(UIViewController *)vc sender:(nullable id)sender API_AVAILABLE(ios(8.0));

// In a horizontally-regular environment this will set the detail view controller unless it provided an implementation for showViewController:sender: in which case it will be called. In a horizontally-compact environment the master view controller or detail view controller is sent the showViewController:sender: message. If neither one of them provide an implementation for this method then it will fall back to a full screen presentation.
- (void)showDetailViewController:(UIViewController *)vc sender:(nullable id)sender API_AVAILABLE(ios(8.0));

// The background style of the primary view controller.
@property (nonatomic) UISplitViewControllerBackgroundStyle primaryBackgroundStyle API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos);

@end

@protocol UISplitViewControllerDelegate

@optional

// This method allows a client to update any bar button items etc.
- (void)splitViewController:(UISplitViewController *)svc willChangeToDisplayMode:(UISplitViewControllerDisplayMode)displayMode API_AVAILABLE(ios(8.0));

// Called by the gesture AND barButtonItem to determine what they will set the display mode to (and what the displayModeButtonItem's appearance will be.) Return UISplitViewControllerDisplayModeAutomatic to get the default behavior.
- (UISplitViewControllerDisplayMode)targetDisplayModeForActionInSplitViewController:(UISplitViewController *)svc API_AVAILABLE(ios(8.0));

// Override this method to customize the behavior of `showViewController:` on a split view controller. Return YES to indicate that you've handled
// the action yourself; return NO to cause the default behavior to be executed.
- (BOOL)splitViewController:(UISplitViewController *)splitViewController showViewController:(UIViewController *)vc sender:(nullable id)sender API_AVAILABLE(ios(8.0));

// Override this method to customize the behavior of `showDetailViewController:` on a split view controller. Return YES to indicate that you've
// handled the action yourself; return NO to cause the default behavior to be executed.
- (BOOL)splitViewController:(UISplitViewController *)splitViewController showDetailViewController:(UIViewController *)vc sender:(nullable id)sender API_AVAILABLE(ios(8.0));

// Return the view controller which is to become the primary view controller after `splitViewController` is collapsed due to a transition to
// the horizontally-compact size class. If you return `nil`, then the argument will perform its default behavior (i.e. to use its current primary view
// controller).
- (nullable UIViewController *)primaryViewControllerForCollapsingSplitViewController:(UISplitViewController *)splitViewController API_AVAILABLE(ios(8.0));

// Return the view controller which is to become the primary view controller after the `splitViewController` is expanded due to a transition
// to the horizontally-regular size class. If you return `nil`, then the argument will perform its default behavior (i.e. to use its current
// primary view controller.)
- (nullable UIViewController *)primaryViewControllerForExpandingSplitViewController:(UISplitViewController *)splitViewController API_AVAILABLE(ios(8.0));

// This method is called when a split view controller is collapsing its children for a transition to a compact-width size class. Override this
// method to perform custom adjustments to the view controller hierarchy of the target controller.  When you return from this method, you're
// expected to have modified the `primaryViewController` so as to be suitable for display in a compact-width split view controller, potentially
// using `secondaryViewController` to do so.  Return YES to prevent UIKit from applying its default behavior; return NO to request that UIKit
// perform its default collapsing behavior.
- (BOOL)splitViewController:(UISplitViewController *)splitViewController collapseSecondaryViewController:(UIViewController *)secondaryViewController ontoPrimaryViewController:(UIViewController *)primaryViewController API_AVAILABLE(ios(8.0));

// This method is called when a split view controller is separating its child into two children for a transition from a compact-width size
// class to a regular-width size class. Override this method to perform custom separation behavior.  The controller returned from this method
// will be set as the secondary view controller of the split view controller.  When you return from this method, `primaryViewController` should
// have been configured for display in a regular-width split view controller. If you return `nil`, then `UISplitViewController` will perform
// its default behavior.
- (nullable UIViewController *)splitViewController:(UISplitViewController *)splitViewController separateSecondaryViewControllerFromPrimaryViewController:(UIViewController *)primaryViewController API_AVAILABLE(ios(8.0));

- (UIInterfaceOrientationMask)splitViewControllerSupportedInterfaceOrientations:(UISplitViewController *)splitViewController API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(tvos);
- (UIInterfaceOrientation)splitViewControllerPreferredInterfaceOrientationForPresentation:(UISplitViewController *)splitViewController API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(tvos);

// Called when a button should be added to a toolbar for a hidden view controller.
// Implementing this method allows the hidden view controller to be presented via a swipe gesture if 'presentsWithGesture' is 'YES' (the default).
- (void)splitViewController:(UISplitViewController *)svc willHideViewController:(UIViewController *)aViewController withBarButtonItem:(UIBarButtonItem *)barButtonItem forPopoverController:(UIPopoverController *)pc API_DEPRECATED("Use splitViewController:willChangeToDisplayMode: and displayModeButtonItem instead", ios(2.0, 8.0)) API_UNAVAILABLE(tvos);

// Called when the view is shown again in the split view, invalidating the button and popover controller.
- (void)splitViewController:(UISplitViewController *)svc willShowViewController:(UIViewController *)aViewController invalidatingBarButtonItem:(UIBarButtonItem *)barButtonItem API_DEPRECATED("Use splitViewController:willChangeToDisplayMode: and displayModeButtonItem instead", ios(2.0, 8.0)) API_UNAVAILABLE(tvos);

// Called when the view controller is shown in a popover so the delegate can take action like hiding other popovers.
- (void)splitViewController:(UISplitViewController *)svc popoverController:(UIPopoverController *)pc willPresentViewController:(UIViewController *)aViewController API_DEPRECATED_WITH_REPLACEMENT("splitViewController:willChangeToDisplayMode:", ios(2.0, 8.0)) API_UNAVAILABLE(tvos);

// Returns YES if a view controller should be hidden by the split view controller in a given orientation.
// (This method is only called on the leftmost view controller and only discriminates portrait from landscape.)
- (BOOL)splitViewController:(UISplitViewController *)svc shouldHideViewController:(UIViewController *)vc inOrientation:(UIInterfaceOrientation)orientation  API_DEPRECATED_WITH_REPLACEMENT("preferredDisplayMode", ios(5.0, 8.0)) API_UNAVAILABLE(tvos);


@end

@interface UIViewController (UISplitViewController)

@property (nullable, nonatomic, readonly, strong) UISplitViewController *splitViewController; // If the view controller has a split view controller as its ancestor, return it. Returns nil otherwise.


/* Called on the primary view controller when a split view controller is collapsing its children for a transition to a compact-width size class, if its delegate does not provide overridden behavior. The default implementation simply shows the primary (the secondary controller disappears.) */
- (void)collapseSecondaryViewController:(UIViewController *)secondaryViewController forSplitViewController:(UISplitViewController *)splitViewController API_AVAILABLE(ios(8.0));

/* Called on the primary view controller when a split view controller is separating its children for a transition to a regular-width size class, if its delegate does not provide overridden behavior. The default implementation restores the previous secondary controller. */
- (nullable UIViewController *)separateSecondaryViewControllerForSplitViewController:(UISplitViewController *)splitViewController API_AVAILABLE(ios(8.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UISplitViewController.h>
#endif
