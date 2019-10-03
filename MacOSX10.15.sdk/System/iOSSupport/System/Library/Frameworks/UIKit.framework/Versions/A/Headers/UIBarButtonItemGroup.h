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

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(9.0)) @interface UIBarButtonItemGroup : NSObject<NSCoding>

/// Create a new bar button item group with the given items. When bar button item layout is done, either the group's barButtonItems or its representativeItem is displayed (if it exists).
- (instancetype)initWithBarButtonItems:(NSArray<UIBarButtonItem *> *)barButtonItems representativeItem:(nullable UIBarButtonItem *)representativeItem NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// The bar button items associated with this group. Changing these items will affect the bar displaying these items without needing to re-set the groups that are in that bar. Any UIBarButtonItems that are already in group will be removed from that group.
@property (nonatomic, readwrite, copy) NSArray<UIBarButtonItem *> *barButtonItems;

/// In order to display as many items as possible, bars that support UIBarButtonItemGroup may choose to collapse items associated with groups to the representativeItem specified by the group.
/// A bar will only collapse groups that have a representativeItem set, but may still choose to use an alternate presentation of these items.
/// A UIBarButtonItem may only be either the representativeItem or a member of the barbuttonItems of a single UIBarButtonItemGroup and may only represent a single group.
/// If the representativeItem has an action, then that action will be invoked, otherwise the bar will present a standard UI to allow selection of the barButtonItems in the representedItem's group.
@property (nonatomic, readwrite, strong, nullable) UIBarButtonItem *representativeItem;

/// Returns YES if the representativeItem of this group is currently being displayed, rather than its barButtonItems.
@property (nonatomic, readonly, assign, getter = isDisplayingRepresentativeItem) BOOL displayingRepresentativeItem;

@end

@interface UIBarButtonItem (UIBarButtonItemGroup)

/// The group that the UIBarButtonItem is currently associated with, either as a member of the barButtonItems array or as that group's representativeItem.
@property (nonatomic, readonly, weak, nullable) UIBarButtonItemGroup *buttonGroup API_AVAILABLE(ios(9.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIBarButtonItemGroup.h>
#endif
