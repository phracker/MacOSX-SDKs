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
    UISplitViewControllerDisplayModeSecondaryOnly,
    UISplitViewControllerDisplayModeOneBesideSecondary, // Two tiled columns. Leading will be UISplitViewControllerColumnSupplementary for UISplitViewControllerStyleTripleColumn, Primary otherwise
    UISplitViewControllerDisplayModeOneOverSecondary, // Supplementary column overlaid on Secondary column for UISplitViewControllerStyleTripleColumn, Primary overlaid otherwise
    
    // For triple-column style only. Three different ways to lay out primary, supplementary, and secondary columns with the secondary more or less visible, and an additional layout that hides the secondary.
    UISplitViewControllerDisplayModeTwoBesideSecondary NS_ENUM_AVAILABLE_IOS(14_0), // All three columns fully displayed side-by-side and interactive
    UISplitViewControllerDisplayModeTwoOverSecondary NS_ENUM_AVAILABLE_IOS(14_0), // primary and supplementary columns side-by-side in overlay on top of partially visible detail column (detail column has dimming view). For widths too narrow to see much of the detail when the primary and supplementary columns are tiled.
    UISplitViewControllerDisplayModeTwoDisplaceSecondary NS_ENUM_AVAILABLE_IOS(14_0), // primary, supplementary and detail columns side-by-side, but the dimmed, noninteractive detail has been displaced toward and cropped on the trailing edge. For wider widths than in TwoOverSecondary but still too narrow for TwoBesideSecondary

    UISplitViewControllerDisplayModePrimaryHidden API_DEPRECATED_WITH_REPLACEMENT("UISplitViewControllerDisplayModeSecondaryOnly", ios(8.0, 14.0)) = UISplitViewControllerDisplayModeSecondaryOnly,
    UISplitViewControllerDisplayModeAllVisible API_DEPRECATED_WITH_REPLACEMENT("UISplitViewControllerDisplayModeOneBesideSecondary", ios(8.0, 14.0)) = UISplitViewControllerDisplayModeOneBesideSecondary,
    UISplitViewControllerDisplayModePrimaryOverlay API_DEPRECATED_WITH_REPLACEMENT("UISplitViewControllerDisplayModeOneOverSecondary", ios(8.0, 14.0)) = UISplitViewControllerDisplayModeOneOverSecondary,
} API_AVAILABLE(ios(8.0));

typedef NS_ENUM(NSInteger, UISplitViewControllerPrimaryEdge) {
    UISplitViewControllerPrimaryEdgeLeading,
    UISplitViewControllerPrimaryEdgeTrailing,
} API_AVAILABLE(ios(11.0), tvos(11.0));

typedef NS_ENUM(NSInteger, UISplitViewControllerBackgroundStyle) {
    UISplitViewControllerBackgroundStyleNone,
    UISplitViewControllerBackgroundStyleSidebar,
} API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos);

typedef NS_ENUM(NSInteger, UISplitViewControllerStyle) {
    UISplitViewControllerStyleUnspecified,
    UISplitViewControllerStyleDoubleColumn,
    UISplitViewControllerStyleTripleColumn,
} API_AVAILABLE(ios(14.0));

typedef NS_ENUM(NSInteger, UISplitViewControllerColumn) {
    UISplitViewControllerColumnPrimary,
    UISplitViewControllerColumnSupplementary, // Valid for UISplitViewControllerStyleTripleColumn only
    UISplitViewControllerColumnSecondary,
    UISplitViewControllerColumnCompact, // If a vc is set for this column, it will be used when the UISVC is collapsed, instead of stacking the vc’s for the Primary, Supplementary, and Secondary columns
} API_AVAILABLE(ios(14.0));

// Allowed displayModes depend on the splitBehavior
// Tile behavior allows SecondaryOnly, OneBesideSecondary, and TwoBesideSecondary display modes
// Overlay behavior allows SecondaryOnly, OneOverSecondary, and TwoOverSecondary display modes
// Displace behavior allows SecondaryOnly, OneBesideSecondary, and TwoDisplaceSecondary display modes
typedef NS_ENUM(NSInteger, UISplitViewControllerSplitBehavior) {
    UISplitViewControllerSplitBehaviorAutomatic,
    UISplitViewControllerSplitBehaviorTile,
    UISplitViewControllerSplitBehaviorOverlay,
    UISplitViewControllerSplitBehaviorDisplace,
} API_AVAILABLE(ios(14.0));

// Control the displayModeButtonItem visibility for column-style UISplitViewController
typedef NS_ENUM(NSInteger, UISplitViewControllerDisplayModeButtonVisibility) {
    UISplitViewControllerDisplayModeButtonVisibilityAutomatic,
    UISplitViewControllerDisplayModeButtonVisibilityNever,
    UISplitViewControllerDisplayModeButtonVisibilityAlways
} API_AVAILABLE(ios(14.5));

// This constant can be used with any sizing-related `UISplitViewController` properties to get the default system behavior.
UIKIT_EXTERN CGFloat const UISplitViewControllerAutomaticDimension API_AVAILABLE(ios(8.0));

UIKIT_EXTERN API_AVAILABLE(ios(3.2)) @interface UISplitViewController : UIViewController

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithStyle:(UISplitViewControllerStyle)style NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(14.0));
@property(nonatomic, readonly) UISplitViewControllerStyle style API_AVAILABLE(ios(14.0)); // For information only, will not be called from UIKit code
@property (nullable, nonatomic, weak) id <UISplitViewControllerDelegate> delegate;

// Default NO. The secondary-only shortcut button is applicable only for UISplitViewControllerStyleTripleColumn
@property(nonatomic) BOOL showsSecondaryOnlyButton API_AVAILABLE(ios(14.0));

// Controls allowed display modes
@property(nonatomic) UISplitViewControllerSplitBehavior preferredSplitBehavior API_AVAILABLE(ios(14.0)); // default Automatic, actual behavior will be determined by width buckets and view aspect ration
@property(nonatomic, readonly) UISplitViewControllerSplitBehavior splitBehavior API_AVAILABLE(ios(14.0));

- (void)setViewController:(nullable UIViewController *)vc forColumn:(UISplitViewControllerColumn)column API_AVAILABLE(ios(14.0)); // If the vc is not a UINavigationController, one will be created, except for UISplitViewControllerColumnCompact.
- (nullable __kindof UIViewController *)viewControllerForColumn:(UISplitViewControllerColumn)column API_AVAILABLE(ios(14.0));

/*
-hideColumn: and -showColumn: do not accept the Compact column
Collapsed:
   -hideColumn:
       always ignored for the Primary column, or if the requested column is not on top;
       otherwise the column is popped
   -showColumn:
       pushes the column (and any intervening columns) if the column is not in the stack;
       does nothing if the column is on top;
       pops any covering columns if the column is in the stack but not on top
Expanded:
   -hideColumn:
       ignored for the Secondary column;
       ignored when the column is not visible in the current displayMode;
       otherwise animates to the nearest displayMode where the column is not visible
   -showColumn:
       ignored for the Secondary column;
       ignored when the column is already visible in the current displayMode;
       otherwise animates to the nearest displayMode where the column is visible

If an animation is started due to -show/hideColumn:, the transitionCoordinator for the UISplitViewController is available following the -show/hideColumn: message.
*/
- (void)hideColumn:(UISplitViewControllerColumn)column API_AVAILABLE(ios(14.0));
- (void)showColumn:(UISplitViewControllerColumn)column API_AVAILABLE(ios(14.0));

@property (nonatomic, copy) NSArray<__kindof UIViewController *> *viewControllers; // -setViewController:forColumn:/-viewControllerForColumn: recommended for column-style UISplitViewController

// If 'YES', hidden view can be presented and dismissed via a swipe gesture. Defaults to 'YES'.
@property (nonatomic) BOOL presentsWithGesture API_AVAILABLE(ios(5.1));

// Specifies whether the split view controller has collapsed its primary and secondary view controllers together
@property(nonatomic, readonly, getter=isCollapsed) BOOL collapsed  API_AVAILABLE(ios(8.0));

// An animatable property that controls how the primary view controller is hidden and displayed. A value of `UISplitViewControllerDisplayModeAutomatic` specifies the default behavior split view controller, which on an iPad, corresponds to an overlay mode in portrait and a side-by-side mode in landscape.
@property (nonatomic) UISplitViewControllerDisplayMode preferredDisplayMode API_AVAILABLE(ios(8.0));

// The actual current displayMode of the split view controller. This will never return `UISplitViewControllerDisplayModeAutomatic`.
@property (nonatomic, readonly) UISplitViewControllerDisplayMode displayMode API_AVAILABLE(ios(8.0));

// A system bar button item whose action will change the displayMode property depending on the result of targetDisplayModeForActionInSplitViewController:. When inserted into the navigation bar of the secondary view controller it will change its appearance to match its target display mode. When the target displayMode is PrimaryHidden, this will appear as a fullscreen button, for AllVisible or PrimaryOverlay it will appear as a Back button, and when it won't cause any action it will become hidden.
// Not supported for column-style UISplitViewController
@property (nonatomic, readonly) UIBarButtonItem *displayModeButtonItem API_AVAILABLE(ios(8.0));

/* For column-style UISplitViewController only.
    UISplitViewControllerDisplayModeButtonVisibilityAutomatic is the default behavior where setting presentsWithGesture to NO hides the displayModeButton.
    Set to UISplitViewControllerDisplayModeButtonVisibilityNever to prevent the displayModeButton from showing.
    Set to UISplitViewControllerDisplayModeButtonVisibilityAlways to allow the displayModeButton to show when presentsWithGesture is NO. Note that in displayModes that would not be expected to show the button when presentsWithGesture is YES (e.g., UISplitViewControllerDisplayModeTwoOverSecondary), a value of Always will not force the button to show.
 */
@property(nonatomic) UISplitViewControllerDisplayModeButtonVisibility displayModeButtonVisibility API_AVAILABLE(ios(14.5)); // default: automatic


// An animatable property that can be used to adjust the relative width of the primary view controller in the split view controller. This preferred width will be limited by the maximum and minimum properties (and potentially other system heuristics).
@property(nonatomic, assign) CGFloat preferredPrimaryColumnWidthFraction API_AVAILABLE(ios(8.0)); // default: UISplitViewControllerAutomaticDimension

// Allow setting the primary column width with point values. This is especially useful in Catalyst where the window may be resized more often.
// If set to non-Automatic, takes precedence over preferredPrimaryColumnWidthFraction.
@property(nonatomic, assign) CGFloat preferredPrimaryColumnWidth API_AVAILABLE(ios(14.0)); // default: UISplitViewControllerAutomaticDimension

// An animatable property that can be used to adjust the minimum absolute width of the primary view controller in the split view controller.
@property(nonatomic, assign) CGFloat minimumPrimaryColumnWidth API_AVAILABLE(ios(8.0)); // default: UISplitViewControllerAutomaticDimension

// An animatable property that can be used to adjust the maximum absolute width of the primary view controller in the split view controller.
@property(nonatomic, assign) CGFloat maximumPrimaryColumnWidth API_AVAILABLE(ios(8.0)); // default: UISplitViewControllerAutomaticDimension

// The current primary view controller's column width.
@property(nonatomic,readonly) CGFloat primaryColumnWidth API_AVAILABLE(ios(8.0));

// Same as the "Primary" versions but applying to the Supplementary column for the triple-column style UISplitViewController
@property(nonatomic, assign) CGFloat preferredSupplementaryColumnWidthFraction API_AVAILABLE(ios(14.0));
@property(nonatomic, assign) CGFloat preferredSupplementaryColumnWidth API_AVAILABLE(ios(14.0));
@property(nonatomic, assign) CGFloat minimumSupplementaryColumnWidth API_AVAILABLE(ios(14.0));
@property(nonatomic, assign) CGFloat maximumSupplementaryColumnWidth API_AVAILABLE(ios(14.0));

@property(nonatomic, readonly) CGFloat supplementaryColumnWidth API_AVAILABLE(ios(14.0));

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

- (UISplitViewControllerColumn)splitViewController:(UISplitViewController *)svc topColumnForCollapsingToProposedTopColumn:(UISplitViewControllerColumn)proposedTopColumn API_AVAILABLE(ios(14.0));
- (UISplitViewControllerDisplayMode)splitViewController:(UISplitViewController *)svc displayModeForExpandingToProposedDisplayMode:(UISplitViewControllerDisplayMode)proposedDisplayMode API_AVAILABLE(ios(14.0));
- (void)splitViewControllerDidCollapse:(UISplitViewController *)svc API_AVAILABLE(ios(14.0));
- (void)splitViewControllerDidExpand:(UISplitViewController *)svc API_AVAILABLE(ios(14.0));
- (void)splitViewController:(UISplitViewController *)svc willShowColumn:(UISplitViewControllerColumn)column API_AVAILABLE(ios(14.0));
- (void)splitViewController:(UISplitViewController *)svc willHideColumn:(UISplitViewControllerColumn)column API_AVAILABLE(ios(14.0));
- (void)splitViewControllerInteractivePresentationGestureWillBegin:(UISplitViewController *)svc API_AVAILABLE(ios(14.0));
- (void)splitViewControllerInteractivePresentationGestureDidEnd:(UISplitViewController *)svc API_AVAILABLE(ios(14.0));

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
