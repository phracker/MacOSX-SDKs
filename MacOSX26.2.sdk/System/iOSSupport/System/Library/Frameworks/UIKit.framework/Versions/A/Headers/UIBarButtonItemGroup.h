#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIBarButtonItemGroup.h>)
//
//  UIBarButtonItemGroup.h
//  UIKit
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIBarButtonItem.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIBarButtonItemGroup : NSObject<NSCoding>

/// Create a new bar button item group with the given items. When bar button item layout is done, either the group's barButtonItems or its representativeItem is displayed (if it exists).
- (instancetype)initWithBarButtonItems:(NSArray<UIBarButtonItem *> *)barButtonItems representativeItem:(nullable UIBarButtonItem *)representativeItem NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Construct a UIBarButtonItemGroup that cannot be moved or removed under UINavigationBar customization.
+ (UIBarButtonItemGroup *)fixedGroupWithRepresentativeItem:(nullable UIBarButtonItem *)representativeItem items:(NSArray<UIBarButtonItem *> *)items API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// Construct a UIBarButtonItemGroup that can be moved but cannot be removed under UINavigationBar customization.
+ (UIBarButtonItemGroup *)movableGroupWithCustomizationIdentifier:(NSString *)customizationIdentifier representativeItem:(nullable UIBarButtonItem *)representativeItem items:(NSArray<UIBarButtonItem *> *)items API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// Construct a UIBarButtonItemGroup that can be moved or added/removed under UINavigationBar customization.
+ (UIBarButtonItemGroup *)optionalGroupWithCustomizationIdentifier:(NSString *)customizationIdentifier inDefaultCustomization:(BOOL)inDefaultCustomization representativeItem:(nullable UIBarButtonItem *)representativeItem items:(NSArray<UIBarButtonItem *> *)items API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// Returns a new group that contains a single zero-width fixed space item inside it.
///
/// If you specify a group with a single zero-width fixed space,
/// the navigation bar to visually separate the following groups.
+ (UIBarButtonItemGroup *)groupWithFixedSpace API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NAME(fixedSpace());

/// The bar button items associated with this group. Changing these items will affect the bar displaying these items without needing to re-set the groups that are in that bar. Any UIBarButtonItems that are already in group will be removed from that group.
@property (nonatomic, readwrite, copy) NSArray<UIBarButtonItem *> *barButtonItems;

/// In order to display as many items as possible, bars that support UIBarButtonItemGroup may choose to collapse items associated with groups to the representativeItem specified by the group.
/// A bar will only collapse groups that have a representativeItem set, but may still choose to use an alternate presentation of these items.
/// A UIBarButtonItem may only be either the representativeItem or a member of the barButtonItems of a single UIBarButtonItemGroup and may only represent a single group.
/// If the representativeItem has an action, then that action will be invoked, otherwise the bar will present a standard UI to allow selection of the barButtonItems in the representedItem's group.
@property (nonatomic, readwrite, strong, nullable) UIBarButtonItem *representativeItem;

/// Returns YES if the representativeItem of this group is currently being displayed, rather than its barButtonItems.
@property (nonatomic, readonly, assign, getter = isDisplayingRepresentativeItem) BOOL displayingRepresentativeItem;

/// Instructs UIKit to ensure that the functionality in this group is made available to the user regardless of customization status. On iPhone and iPad idioms, UIKit currently places these items in the overflow menu; this property has no effect on macOS idiom.
@property (nonatomic, readwrite, assign) BOOL alwaysAvailable API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// A UIMenuElement that should substitute for the UIBarButtonItemGroup when displayed in a menu.
@property (nonatomic, readwrite, copy, nullable) UIMenuElement *menuRepresentation API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// If the group should be hidden from display.
@property (nonatomic, readwrite, assign, getter = isHidden) BOOL hidden API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

@end

@interface UIBarButtonItem (UIBarButtonItemGroup)

/// The group that the UIBarButtonItem is currently associated with, either as a member of the barButtonItems array or as that group's representativeItem.
@property (nonatomic, readonly, weak, nullable) UIBarButtonItemGroup *buttonGroup API_AVAILABLE(ios(9.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIBarButtonItemGroup.h>
#endif
