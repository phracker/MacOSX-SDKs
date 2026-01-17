#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITabGroup.h>)
//
//  UITabGroup.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <UIKit/UITab.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSUInteger, UITabGroupSidebarAppearance) {
    /// The default appearance showing the group and its children appropriately depending
    /// on the group level it is in.
    UITabGroupSidebarAppearanceAutomatic   = 0,
    /// Displays only the children alongside the group's siblings.
    UITabGroupSidebarAppearanceInline      = 1,
    /// Displays the group and its children as a top-level group of the sidebar.
    UITabGroupSidebarAppearanceRootSection = 2,
} NS_SWIFT_NAME(UITabGroup.SidebarAppearance) API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

@class UINavigationController, UIAction;

UIKIT_EXTERN NS_SWIFT_UI_ACTOR
API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos)
@interface UITabGroup: UITab

/// The currently selected tab. The tab must be part of `children`.
@property (nonatomic, strong, nullable) UITab *selectedChild;

/// The default child tab to select for when a selection is required and `selectedChild` is nil.
/// If this is nil, then the default selected element is the first element of `children`. Default is nil.
@property (nonatomic, copy, nullable) NSString *defaultChildIdentifier;

/// Child tabs of the tab group. Default is an empty array.
@property (nonatomic, copy) NSArray<UITab *> *children;

/// The display order of the children, represented by the identifiers. Default is empty.
/// Any tab in `children` not contained in `displayOrderIdentifiers` will be appended after
/// sorted items. Identifiers that do not match tabs in `children` will be ignored.
@property (nonatomic, copy) NSArray<NSString *> *displayOrderIdentifiers;

/// Determines if elements in `children` can be reordered from the sidebar. Default is NO.
/// Changes in the display order are notified via `tabBarController:displayOrderDidChangeForGroup:`
/// in `UITabBarControllerDelegate`.
@property (nonatomic, assign) BOOL allowsReordering;

/// Returns the `children` array sorted by `displayOrderIdentifiers` if it is specified.
/// Any tab in `children` not contained in the identifiers will be appended after
/// sorted items. Identifiers that do not match tabs in `children` will be ignored.
@property (nonatomic, strong, readonly) NSArray<UITab *> *displayOrder;

/// Returns the `tab` matching the specified `identifier` in the group's children and its descendants.
/// Returns nil if no tab is found matching the `identifier`.
- (nullable UITab *)tabForIdentifier:(NSString *)identifier;

#pragma mark Managed Navigation

/// A navigation controller used to automatically manage the view controller hierarchy of the group.
/// Set a `UINavigationController` to allow the tab group to manage the hierarchy automatically.
/// The navigation stack of the managing navigation controller will be managed by the tab group based on
/// the selected tab of the group. When multiple navigation controllers are set on nested groups, the root-most
/// controller is used. Default is nil.
///
/// By default, the navigation stack is represented by the view controller of each tab of the selected tree, if a
/// view controller is provided for that level. If no view controller is provided for that level, then it will be ignored.
///
/// To customize the displayed view controllers per tab level of selection, implement the delegate method
/// `tabBarController:displayedViewControllersForTab:proposedViewControllers:`
/// on `UITabBarControllerDelegate`, which will propose a set of view controllers per level.
@property (nonatomic, strong, nullable) UINavigationController *managingNavigationController;

#pragma mark Sidebar

/// Actions to display in the sidebar, after all tabs. Default is nil.
@property (nonatomic, copy) NSArray<UIAction *> *sidebarActions API_UNAVAILABLE(tvos, watchos);

/// The preferred appearance of the group and its children in the sidebar. Default is `automatic`
@property (nonatomic, assign) UITabGroupSidebarAppearance sidebarAppearance API_UNAVAILABLE(tvos, watchos);

/// Determines if the tab group itself can be selected as a destination in the sidebar.
///
/// By default, tab groups are not destinations when displayed in the sidebar, and cannot be selected directly
/// by users. When enabled, the tab group becomes a selectable item in the sidebar, and will no longer perform
/// automatic selection for a default child if no child is currently selected. The default value is NO.
@property (nonatomic, assign) BOOL isSidebarDestination API_AVAILABLE(ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);

/// Creates a `UITabGroup` using the specified parameters.
- (instancetype)initWithTitle:(NSString *)title
                        image:(nullable UIImage *)image
                   identifier:(NSString *)identifier
                     children:(NSArray<UITab *> *)children
       viewControllerProvider:(UIViewController *(^_Nullable)(__kindof UITab *))viewControllerProvider;

@end

NS_HEADER_AUDIT_END(nullability, sendability)


#else
#import <UIKitCore/UITabGroup.h>
#endif
