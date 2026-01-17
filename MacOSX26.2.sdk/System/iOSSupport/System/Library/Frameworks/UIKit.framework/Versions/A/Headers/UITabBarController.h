#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITabBarController.h>)
//
//  UITabBarController.h
//  UIKit
//
//  Copyright (c) 2007-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIViewControllerTransitioning.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITabBar.h>
#import <UIKit/UIDropInteraction.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UITabBarControllerMode) {
    /// The default tab bar controller mode.
    /// Resolves to `tabSidebar` if any of the tab elements of the tab bar controller is a group, and
    /// if the platform supports displaying a sidebar mode. Otherwise, resolves to `tabBar`.
    UITabBarControllerModeAutomatic = 0,

    /// Displays tabs in a tab bar.
    UITabBarControllerModeTabBar = 1,

    /// Displays tabs in a tab bar and sidebar.
    UITabBarControllerModeTabSidebar API_UNAVAILABLE(tvos) = 2,

} NS_SWIFT_NAME(UITabBarController.Mode) API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UITabBarMinimizeBehavior) {
    /// Resolves to the system default minimize behavior.
    UITabBarMinimizeBehaviorAutomatic = 0,

    /// The tab bar does not minimize.
    UITabBarMinimizeBehaviorNever API_UNAVAILABLE(tvos, visionos),

    /// The tab bar minimizes when scrolling down, and expands when scrolling back up.
    UITabBarMinimizeBehaviorOnScrollDown API_UNAVAILABLE(tvos, visionos),

    /// The tab bar minimizes when scrolling up, and expands when scrolling back down.
    /// Recommended if the scroll view content is aligned to the bottom.
    UITabBarMinimizeBehaviorOnScrollUp API_UNAVAILABLE(tvos, visionos),

} NS_SWIFT_NAME(UITabBarController.MinimizeBehavior) API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

@class UIView, UIImage, UINavigationController, UITabBarItem, UITabBarControllerSidebar, UITab, UITabGroup, UITabAccessory;
@protocol UITabBarControllerDelegate;

/*!
 UITabBarController manages a button bar and transition view, for an application with multiple top-level modes.
 
 To use in your application, add its view to the view hierarchy, then add top-level view controllers in order.
 Most clients will not need to subclass UITabBarController.

 If more than five view controllers are added to a tab bar controller, only the first four will display.
 The rest will be accessible under an automatically generated More item.
 
 UITabBarController is rotatable if all of its view controllers are rotatable.
 */

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UITabBarController : UIViewController <UITabBarDelegate, NSCoding>

/// The object managing the delegate of the tab bar controller.
///
/// The default value for this property is `nil`.
@property(nonatomic, weak, nullable) id<UITabBarControllerDelegate> delegate;

/// The object managing the tab sidebar for the tab bar controller.
///
/// The default value for this property is `UITabBarControllerModeAutomatic`.
@property (nonatomic, assign) UITabBarControllerMode mode API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// The object managing the tab sidebar for the tab bar controller.
@property (nonatomic, strong, readonly) UITabBarControllerSidebar *sidebar API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/// The customization identifier for the tab bar and sidebar for persistence.
///
/// The identifier is useful for when an app has multiple tab bar controllers, each with their own customizations.
/// If the customization identifier is `nil`, a system default is used. Default is `nil`.
@property (nonatomic, copy, nullable) NSString *customizationIdentifier API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// An optional filter to display only select root-level tabs when in a compact appearance.
///
/// The default value is is `nil`, which would make all tabs available.
@property (nonatomic, copy, nullable) NSArray<NSString *> *compactTabIdentifiers API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// The currently selected tab, which can be a root tab or any of their descendants.
///
/// The default value for this property is `nil`.
@property (nonatomic, strong, nullable) UITab *selectedTab API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// An array of root tabs representing view controllers to display by the tab bar interface.
///
/// Once set, `UITabBarController.viewControllers` and related properties and methods will not be called.
@property (nonatomic, copy) NSArray<__kindof UITab *> *tabs API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// Sets the root tabs of the tab bar controller, with an option to animate the change.
- (void)setTabs:(NSArray<UITab *> *)tabs animated:(BOOL)animated API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// Returns the `tab` matching the specified `identifier` in the tab bar controller's tabs. Returns nil if no tab is found matching the `identifier`.
- (nullable UITab *)tabForIdentifier:(NSString *)identifier API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// Creates a tab bar controller with the specified tabs.
- (instancetype)initWithTabs:(NSArray<UITab *> *)tabs API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// Defines the minimize behavior for the tab bar, if it is supported.
///
/// The default value for this property is `UITabBarMinimizeBehaviorAutomatic`.
@property (nonatomic, assign) UITabBarMinimizeBehavior tabBarMinimizeBehavior API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// Determines if the active tab bar is currently hidden.
///
/// The default value for this property is `NO`.
@property (nonatomic, assign, getter=isTabBarHidden) BOOL tabBarHidden API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// Changes the active tab bar's visibility with an option to animate the change.
- (void)setTabBarHidden:(BOOL)hidden animated:(BOOL)animated API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// The content layout guide provides the layout area for the UITabBarController unobscured by the tab bar or sidebar.
@property (nonatomic, strong, readonly) UILayoutGuide *contentLayoutGuide API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// An optional bottom accessory of the tab bar controller.
///
/// The default value for this property is `nil`.
@property (nonatomic, strong, nullable) UITabAccessory *bottomAccessory API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos);

/// Sets a bottom accessory with an option to animate the change.
- (void)setBottomAccessory:(nullable UITabAccessory *)bottomAccessory animated:(BOOL)animated API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos);

@property(nullable, nonatomic,copy) NSArray<__kindof UIViewController *> *viewControllers;

// If the number of view controllers is greater than the number displayable by a tab bar, a "More" navigation controller will automatically be shown.
// The "More" navigation controller will not be returned by -viewControllers, but it may be returned by -selectedViewController.
- (void)setViewControllers:(NSArray<__kindof UIViewController *> * __nullable)viewControllers animated:(BOOL)animated;

@property(nullable, nonatomic, assign) __kindof UIViewController *selectedViewController; // This may return the "More" navigation controller if it exists.
@property(nonatomic) NSUInteger selectedIndex;

@property(nonatomic, readonly) UINavigationController *moreNavigationController API_UNAVAILABLE(tvos, visionos); // Returns the "More" navigation controller, creating it if it does not already exist.
@property(nullable, nonatomic, copy) NSArray<__kindof UIViewController *> *customizableViewControllers API_UNAVAILABLE(tvos, visionos); // If non-nil, then the "More" view will include an "Edit" button that displays customization UI for the specified controllers. By default, all view controllers are customizable.

@property(nonatomic,readonly) UITabBar *tabBar API_AVAILABLE(ios(3.0)); // Provided for -[UIActionSheet showFromTabBar:]. Attempting to modify the contents of the tab bar directly will throw an exception.

@end

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UITabBarControllerDelegate <NSObject>

@optional

/// Asks the delegate whether the specified tab should be made active.
///
/// Return @c YES if the specified @c tab can be selected by the user. Otherwise, return @c NO
- (BOOL)tabBarController:(UITabBarController *)tabBarController shouldSelectTab:(UITab *)tab NS_SWIFT_NAME(tabBarController(_:shouldSelectTab:)) API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// Tells the delegate that the user selected the specified @c selectedTab in the tab bar controller.
///
/// This specified @c selectedTab is either a root tab or any of their descendants.
- (void)tabBarController:(UITabBarController *)tabBarController didSelectTab:(UITab *)selectedTab previousTab:(nullable UITab *)previousTab NS_SWIFT_NAME(tabBarController(_:didSelectTab:previousTab:)) API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// Asks the delegate for a drop operation to determine if drag items can be dropped into the specified @c tab
///
/// If the operation is either a `.move` or `.copy`, then the drop will proceed and `tabBarController:tab:acceptItemsFromDropSession:`
/// is called. By default, the drop will be treated as a cancel operation if this is not implemented.
- (UIDropOperation)tabBarController:(UITabBarController *)tabBarController tab:(UITab *)tab operationForAcceptingItemsFromDropSession:(id<UIDropSession>)session API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

/// Notifies the delegate to perform a drop into the specified @c tab from the specified session.
///
/// This is only called if the operation returned from `tabBarController:tab:operationForAcceptingItemsFromDropSession` is valid for a drop.
- (void)tabBarController:(UITabBarController *)tabBarController tab:(UITab *)tab acceptItemsFromDropSession:(id<UIDropSession>)session API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

/// Notifies the delegate when the tab bar controller is about to begin editing.
- (void)tabBarControllerWillBeginEditing:(UITabBarController *)tabBarController API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

/// Notifies the delegate when the tab bar controller's current editing state has ended.
- (void)tabBarControllerDidEndEditing:(UITabBarController *)tabBarController API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

/// Notifies the delegate when editing has ended and the specified tabs have had their `isHidden` values changed by the user.
- (void)tabBarController:(UITabBarController *)tabBarController visibilityDidChangeForTabs:(NSArray<UITab *> *)tabs API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

/// Notifies the delegate that the display order for the specified tab has been changed by the user.
- (void)tabBarController:(UITabBarController *)tabBarController displayOrderDidChangeForGroup:(UITabGroup *)group API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

/// Used with `UITabGroup.managingNavigationController`, this method allows the delegate to customize the displayed view controllers
/// within the navigation stack for each level of selected tab. This method is called by the system if the selected tab in the `UITabBarController`
/// belongs to or is in the hierarchy of a managing tab group (i.e. a `UITabGroup` with a non-nil `managingNavigationController`). By default,
/// if this method is not implemented, the system will build the navigation stack by adding each tab's `viewController` into the hierarchy, if one exists.
/// This is especially useful to hide certain view controllers when transitioning between compact and regular size classes.
///
/// @param tabBarController The tab bar controller managed by the delegate.
/// @param tab The tab for which the displayed view controllers is being requested for by its `managingTabGroup`. Each tab in the selection hierarchy will be called once.
/// @param proposedViewControllers The proposed view controllers for the given tab. In general, the proposed view controller is a single-item array of the tab's viewController. If other view controllers are pushed onto the navigation stack, they will be part of the last (leaf-most) tab's `proposedViewControllers` such that they are preserved between updates.
///
/// @return A list of view controllers represented by the tab in the navigation stack.
- (NSArray<UIViewController *> *)tabBarController:(UITabBarController *)tabBarController
                   displayedViewControllersForTab:(UITab *)tab
                          proposedViewControllers:(NSArray<UIViewController *> *)proposedViewControllers API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

- (BOOL)tabBarController:(UITabBarController *)tabBarController shouldSelectViewController:(UIViewController *)viewController API_AVAILABLE(ios(3.0));
- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)viewController;

- (void)tabBarController:(UITabBarController *)tabBarController willBeginCustomizingViewControllers:(NSArray<__kindof UIViewController *> *)viewControllers API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos);
- (void)tabBarController:(UITabBarController *)tabBarController willEndCustomizingViewControllers:(NSArray<__kindof UIViewController *> *)viewControllers changed:(BOOL)changed API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos);
- (void)tabBarController:(UITabBarController *)tabBarController didEndCustomizingViewControllers:(NSArray<__kindof UIViewController *> *)viewControllers changed:(BOOL)changed API_UNAVAILABLE(tvos);

- (UIInterfaceOrientationMask)tabBarControllerSupportedInterfaceOrientations:(UITabBarController *)tabBarController API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos);
- (UIInterfaceOrientation)tabBarControllerPreferredInterfaceOrientationForPresentation:(UITabBarController *)tabBarController API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos);

- (nullable id <UIViewControllerInteractiveTransitioning>)tabBarController:(UITabBarController *)tabBarController
                      interactionControllerForAnimationController: (id <UIViewControllerAnimatedTransitioning>)animationController API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(visionos);

- (nullable id <UIViewControllerAnimatedTransitioning>)tabBarController:(UITabBarController *)tabBarController
            animationControllerForTransitionFromViewController:(UIViewController *)fromVC
                                              toViewController:(UIViewController *)toVC  API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(visionos);

@end

@interface UIViewController (UITabBarControllerItem)

@property(null_resettable, nonatomic, strong) UITabBarItem *tabBarItem; // Automatically created lazily with the view controller's title if it's not set explicitly.

@property(nullable, nonatomic, readonly, strong) UITabBarController *tabBarController; // If the view controller has a tab bar controller as its ancestor, return it. Returns nil otherwise.

/* Deprecated on tvOS 15.0 in favor of -[UIViewController setContentScrollView:forEdge:].
 */
@property(nullable, nonatomic, strong) UIScrollView *tabBarObservedScrollView API_DEPRECATED("Use -setContentScrollView:forEdge: instead.", tvos(13.0,API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, visionos); // Set this property to the full screen scroll view on the tab's top-level view controller, if one exists.

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITabBarController.h>
#endif
