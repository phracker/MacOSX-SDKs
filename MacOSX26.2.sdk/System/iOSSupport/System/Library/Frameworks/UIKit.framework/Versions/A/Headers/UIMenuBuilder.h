#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIMenuBuilder.h>)
//
//  UIMenuBuilder.h
//  UIKit
//
//  Copyright (c) 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIAction.h>
#import <UIKit/UIMenu.h>

@class UICommand;
@class UIMenuSystem;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Encapsulates access and mutation for a menu hierarchy.
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIMenuBuilder

/// Which system we are building for.
@property (nonatomic, readonly) UIMenuSystem *system;

/// Fetch the identified menu.
///
/// @param identifier The identifier of the menu to fetch.
/// @return The menu with the given identifier, or `nil` if no such menu.
- (nullable UIMenu *)menuForIdentifier:(UIMenuIdentifier)identifier NS_SWIFT_NAME(menu(for:));

/// Fetch the identified action.
///
/// @param identifier The identifier of the action to fetch.
/// @return The action with the given identifier, or `nil` if no such action.
- (nullable UIAction *)actionForIdentifier:(UIActionIdentifier)identifier NS_SWIFT_NAME(action(for:));

/// Fetch the identified command.
///
/// @param action The action of the command to fetch.
/// @param propertyList Property list object to distinguish commands, if needed.
/// @return The command with the given action and property list, or `nil` if no such command.
- (nullable UICommand *)commandForAction:(SEL)action propertyList:(nullable id)propertyList NS_REFINED_FOR_SWIFT;

/// Replace an identified menu with a menu.
///
/// @param replacedIdentifier The identifier of the menu to be replaced.
/// @param replacementGroup The replacement menu.
- (void)replaceMenuForIdentifier:(UIMenuIdentifier)replacedIdentifier withMenu:(UIMenu *)replacementMenu NS_SWIFT_NAME(replace(menu:with:));

/// Replace the children of an identified parent menu.
///
/// @param parentIdentifier The identifier of the parent menu.
/// @param childrenBlock A block that returns the new children, given the old children.
- (void)replaceChildrenOfMenuForIdentifier:(UIMenuIdentifier)parentIdentifier
                         fromChildrenBlock:(NSArray<UIMenuElement *> *(NS_NOESCAPE ^)(NSArray<UIMenuElement *> *))childrenBlock NS_SWIFT_NAME(replaceChildren(ofMenu:from:));

/// Replace an identified menu with menu elements.
///
/// @param replacedIdentifier The identifier of the menu to be replaced.
/// @param replacementElements The replacement elements.
- (void)replaceMenuForIdentifier:(UIMenuIdentifier)replacedIdentifier withElements:(NSArray<UIMenuElement *> *)replacementElements API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(replace(menu:with:));

/// Replace an identified action with menu elements.
///
/// @param replacedIdentifier The identifier of the action to be replaced.
/// @param replacementElements The replacement elements.
- (void)replaceActionForIdentifier:(UIActionIdentifier)replacedIdentifier withElements:(NSArray<UIMenuElement *> *)replacementElements API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(replace(action:with:));

/// Replace an identified command with menu elements.
///
/// @param replacedAction The action of the command to be replaced.
/// @param replacedPropertyList Property list object to distinguish commands, if needed.
/// @param replacementElements The replacement elements.
- (void)replaceCommandForAction:(SEL)replacedAction propertyList:(nullable id)replacedPropertyList withElements:(NSArray<UIMenuElement *> *)replacementElements API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

/// Insert a sibling menu before an identified sibling menu.
///
/// @param siblingGroup The sibling menu to insert.
/// @param siblingIdentifier The identifier of the sibling menu to insert before.
- (void)insertSiblingMenu:(UIMenu *)siblingMenu beforeMenuForIdentifier:(UIMenuIdentifier)siblingIdentifier NS_SWIFT_NAME(insertSibling(_:beforeMenu:));

/// Insert elements before an identified menu.
///
/// @param insertedElements The elements to insert.
/// @param siblingIdentifier The identifier of the menu to insert elements before.
- (void)insertElements:(NSArray<UIMenuElement *> *)insertedElements beforeMenuForIdentifier:(UIMenuIdentifier)siblingIdentifier API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(insertElements(_:beforeMenu:));

/// Insert elements after an identified menu.
///
/// @param insertedElements The elements to insert.
/// @param siblingIdentifier The identifier of the menu to insert elements after.
- (void)insertElements:(NSArray<UIMenuElement *> *)insertedElements afterMenuForIdentifier:(UIMenuIdentifier)siblingIdentifier API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(insertElements(_:afterMenu:));

/// Insert a sibling menu after an identified sibling menu.
///
/// @param siblingGroup The sibling menu to insert.
/// @param siblingIdentifier The identifier of the sibling menu to insert after.
- (void)insertSiblingMenu:(UIMenu *)siblingMenu afterMenuForIdentifier:(UIMenuIdentifier)siblingIdentifier NS_SWIFT_NAME(insertSibling(_:afterMenu:));

/// Insert a child menu at the start of an identified parent menu.
///
/// @param childGroup The child menu to insert.
/// @param parentIdentifier The identifier of the parent menu to insert at the start of.
- (void)insertChildMenu:(UIMenu *)childMenu atStartOfMenuForIdentifier:(UIMenuIdentifier)parentIdentifier NS_SWIFT_NAME(insertChild(_:atStartOfMenu:));

/// Insert elements before an identified action.
///
/// @param insertedElements The elements to insert.
/// @param siblingIdentifier The identifier of the action to insert elements before.
- (void)insertElements:(NSArray<UIMenuElement *> *)insertedElements beforeActionForIdentifier:(UIActionIdentifier)siblingIdentifier API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(insertElements(_:beforeAction:));

/// Insert elements after an identified action.
///
/// @param insertedElements The elements to insert.
/// @param siblingIdentifier The identifier of the action to insert elements after.
- (void)insertElements:(NSArray<UIMenuElement *> *)insertedElements afterActionForIdentifier:(UIActionIdentifier)siblingIdentifier API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(insertElements(_:afterAction:));

/// Insert elements before an identified command.
///
/// @param insertedElements The elements to insert.
/// @param siblingAction The action of the command to insert elements before.
/// @param siblingPropertyList Property list object to distinguish commands, if needed.
- (void)insertElements:(NSArray<UIMenuElement *> *)insertedElements beforeCommandForAction:(SEL)siblingAction propertyList:(nullable id)siblingPropertyList API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

/// Insert elements after an identified command.
///
/// @param insertedElements The elements to insert.
/// @param siblingAction The action of the command to insert elements after.
/// @param siblingPropertyList Property list object to distinguish commands, if needed.
- (void)insertElements:(NSArray<UIMenuElement *> *)insertedElements afterCommandForAction:(SEL)siblingAction propertyList:(nullable id)siblingPropertyList API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

/// Insert elements at the start of an identified parent menu.
///
/// @param childElements The child elements to insert.
/// @param parentIdentifier The identifier of the parent menu to insert elements at the start of.
- (void)insertElements:(NSArray<UIMenuElement *> *)childElements atStartOfMenuForIdentifier:(UIMenuIdentifier)parentIdentifier API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(insertElements(_:atStartOfMenu:));

/// Insert a child menu at the end of an identified parent menu.
///
/// @param childGroup The child menu to insert.
/// @param parentIdentifier The identifier of the parent menu to insert at the end of.
- (void)insertChildMenu:(UIMenu *)childMenu atEndOfMenuForIdentifier:(UIMenuIdentifier)parentIdentifier NS_SWIFT_NAME(insertChild(_:atEndOfMenu:));

/// Insert elements at the end of an identified parent menu.
///
/// @param childElements The child elements to insert.
/// @param parentIdentifier The identifier of the parent menu to insert elements at the end of.
- (void)insertElements:(NSArray<UIMenuElement *> *)childElements atEndOfMenuForIdentifier:(UIMenuIdentifier)parentIdentifier API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(insertElements(_:atEndOfMenu:));

/// Remove an identified menu.
///
/// @param removedIdentifier The menu to remove.
- (void)removeMenuForIdentifier:(UIMenuIdentifier)removedIdentifier NS_SWIFT_NAME(remove(menu:));

/// Remove an identified action.
///
/// @param removedIdentifier The identifier of the action to remove.
- (void)removeActionForIdentifier:(UIActionIdentifier)removedIdentifier API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(remove(action:));

/// Remove an identified command.
///
/// @param removedAction The action of the command to remove.
/// @param removedPropertyList Property list object to distinguish commands, if needed.
- (void)removeCommandForAction:(SEL)removedAction propertyList:(nullable id)removedPropertyList API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIMenuBuilder.h>
#endif
