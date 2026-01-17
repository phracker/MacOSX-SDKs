#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITabSidebarItem.h>)
//
//  UITabSidebarItem.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <Foundation/Foundation.h>
#import <UIKit/UITab.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIAction;
@class UITabSidebarItemRequest, UICellConfigurationState, UIBackgroundConfiguration, UICellAccessory, UIListContentConfiguration;
@protocol UIContentConfiguration;

#pragma mark - UITabSidebarItem

UIKIT_EXTERN NS_SWIFT_UI_ACTOR
API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface UITabSidebarItem : NSObject <NSCopying>

/// The tab that the receiver represents. Only one of `tab` or `action` will be valid for an item.
@property (nonatomic, strong, nullable, readonly) UITab *tab NS_REFINED_FOR_SWIFT;

/// The action that the receiver represents. Only one of `tab` or `action` will be valid for an item.
@property (nonatomic, strong, nullable, readonly) UIAction *action NS_REFINED_FOR_SWIFT;

/// The current configuration state of the sidebar item.
@property (nonatomic, strong, readonly) UICellConfigurationState *configurationState NS_REFINED_FOR_SWIFT;

/// The content configuration to use when displaying this item.
@property (nonatomic, copy) id<UIContentConfiguration> contentConfiguration NS_REFINED_FOR_SWIFT;

/// The background configuration to use when displaying this item.
@property (nonatomic, copy) UIBackgroundConfiguration *backgroundConfiguration NS_REFINED_FOR_SWIFT;

/// Cell accessories to use when displaying this item. Some accessories may not be shown if it conflicts with system default accessories.
@property (nonatomic, copy) NSArray<UICellAccessory *> *accessories NS_REFINED_FOR_SWIFT;

/// Returns the default content configuration for this item and the configuration state.
- (UIListContentConfiguration *)defaultContentConfiguration NS_REFINED_FOR_SWIFT;

/// Returns the default background configuration for this item and the configuration state.
- (UIBackgroundConfiguration *)defaultBackgroundConfiguration NS_REFINED_FOR_SWIFT;

/// Creates a sidebar item from the specified request. The sidebar item will be preconfigured with the appropriate defaults for its content.
+ (instancetype)itemFromRequest:(UITabSidebarItemRequest *)request NS_SWIFT_NAME(init(request:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - UITabSidebarItemRequest

UIKIT_EXTERN NS_SWIFT_UI_ACTOR
API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos)
NS_SWIFT_NAME(UITabSidebarItem.Request)
@interface UITabSidebarItemRequest : NSObject

/// The tab that the receiver represents. Only one of `tab` or `action` will be valid for an item.
@property (nonatomic, readonly, nullable) UITab *tab NS_REFINED_FOR_SWIFT;

/// The action that the receiver represents. Only one of `tab` or `action` will be valid for an item.
@property (nonatomic, readonly, nullable) UIAction *action NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITabSidebarItem.h>
#endif
