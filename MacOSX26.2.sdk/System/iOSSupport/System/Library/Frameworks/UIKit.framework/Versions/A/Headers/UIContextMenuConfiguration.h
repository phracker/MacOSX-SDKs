#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIContextMenuConfiguration.h>)
//
//  UIContextMenuConfiguration.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIAction.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UIContextMenuConfigurationElementOrder) {
    UIContextMenuConfigurationElementOrderAutomatic = 0,  /// Allows the system to choose the appropriate ordering strategy for the current context.
    UIContextMenuConfigurationElementOrderPriority,       /// Order menu elements according to priority. Keeping the first element in the UIMenu closest to user's interaction point.
    UIContextMenuConfigurationElementOrderFixed,          /// Display menu elements using their order in the UIMenu's children array.
} NS_SWIFT_NAME(UIContextMenuConfiguration.ElementOrder) API_AVAILABLE(ios(16.0), tvos(17.0)) API_UNAVAILABLE(watchos);


@class UIViewController;

/*!
 * @abstract Return a UIAction-based UIMenu describing the desired action hierarchy.
 *
 * @param suggestedActions  An array of suggested actions gathered from the UIResponder chain. You may choose to include
 *                          some of these actions in the hierarchy returned from this block to display them in the resulting menu.
 */
typedef UIMenu * _Nullable (^UIContextMenuActionProvider)(NSArray<UIMenuElement *> *suggestedActions) API_UNAVAILABLE(watchos);

/*!
 * @abstract Return a UIViewController to be displayed as this menu's preview component.
 */
typedef UIViewController * _Nullable (^UIContextMenuContentPreviewProvider)(void) API_UNAVAILABLE(watchos);


UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIContextMenuConfiguration : NSObject

/// This configuration's identifier. When representing multiple items in your app, this identifier
/// corresponds to the primary item (i.e. the one with which the user interacted when invoking the menu).
@property (nonatomic, readonly) id<NSCopying> identifier;

/// When this menu acts on multiple items, you may include the identifiers of secondary items to display a multi-item menu.
@property (nonatomic, copy) NSSet<id<NSCopying>> *secondaryItemIdentifiers API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos);

/// Number of items on which this menu acts. Used to badge a multi-item menu's preview stack.
/// When unset, this value is determined automatically by the system. Values lower than 2 hide the badge.
@property (nonatomic) NSInteger badgeCount API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos);

/// Preferred menu element ordering strategy for this menu.
@property (nonatomic) UIContextMenuConfigurationElementOrder preferredMenuElementOrder API_AVAILABLE(ios(16.0), tvos(17.0));

/*!
 * @abstract Returns a UIContextMenuConfiguration.
 *
 * @param identifier       Optional unique identifier. If omitted, an NSUUID will be generated. May be used to
 *                         identify this configuration throughout the interaction's lifecycle.
 * @param previewProvider  Optional preview view controller provider block, called when the menu is about to be presented.
 * @param actionProvider   Optional action provider block, called when the menu is about to be presented.
 */
+ (instancetype)configurationWithIdentifier:(nullable id<NSCopying>)identifier
                            previewProvider:(nullable UIContextMenuContentPreviewProvider)previewProvider
                             actionProvider:(nullable UIContextMenuActionProvider)actionProvider;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIContextMenuConfiguration.h>
#endif
