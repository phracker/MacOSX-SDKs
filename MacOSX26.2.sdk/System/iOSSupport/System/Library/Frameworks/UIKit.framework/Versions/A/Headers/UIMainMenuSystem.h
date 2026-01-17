#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIMainMenuSystem.h>)
//
//  UIMainMenuSystem.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <UIKit/UIMenuSystem.h>

@class UIMainMenuSystemConfiguration;
@protocol UIMenuBuilder;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The main menu system.
UIKIT_EXTERN API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIMainMenuSystem : UIMenuSystem

/// The shared main menu system.
@property (class, nonatomic, readonly) UIMainMenuSystem *sharedSystem;

/// Specifies that the main menu system should be built using the specified configuration.
/// A build handler can be optionally provided, which the main menu system will use instead of calling `-buildMenuWithBuilder:`.
/// Setting this will invalidate and rebuild the main menu system. Ideally it should be set once, and as early as possible, preferably in `-application:didFinishLaunchingWithOptions:`.
/// Subsequent rebuilds of the main menu system will continue to use this `configuration` and `buildHandler`.
/// It is a developer error to set the `configuration` while the main menu system is building. Doing so will assert.
- (void)setBuildConfiguration:(UIMainMenuSystemConfiguration *)configuration buildHandler:(void(^ _Nullable)(id<UIMenuBuilder> builder))buildHandler NS_REFINED_FOR_SWIFT;

@property (class, nonatomic, readonly) UIMenuSystem *mainSystem NS_UNAVAILABLE;
@property (class, nonatomic, readonly) UIMenuSystem *contextSystem NS_UNAVAILABLE;

@end

/// A configuration for the main menu system.
/// You can specify whether or not certain elements are present in the initial main menu, as well as a block to build the menu using a UIMenuBuilder.
UIKIT_EXTERN API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(UIMainMenuSystem.Configuration) NS_SWIFT_UI_ACTOR
@interface UIMainMenuSystemConfiguration : NSObject <NSCopying>

/// Specifies a preference for new scene elements in the main menu.
@property (nonatomic, assign) UIMenuSystemElementGroupPreference newScenePreference;

/// Specifies a preference for document elements in the main menu.
@property (nonatomic, assign) UIMenuSystemElementGroupPreference documentPreference;

/// Specifies a preference for printing elements in the main menu.
@property (nonatomic, assign) UIMenuSystemElementGroupPreference printingPreference;

/// Specifies a preference for finding elements in the main menu.
@property (nonatomic, assign) UIMenuSystemElementGroupPreference findingPreference;

/// Configuration for the find elements should they be present in the main menu.
@property (nonatomic, strong, readonly) UIMenuSystemFindElementGroupConfiguration *findingConfiguration;

/// Specifies a preference for toolbar elements in the main menu.
@property (nonatomic, assign) UIMenuSystemElementGroupPreference toolbarPreference;

/// Specifies a preference for sidebar elements in the main menu.
@property (nonatomic, assign) UIMenuSystemElementGroupPreference sidebarPreference;

/// Specifies a preference for inspector elements in the main menu.
@property (nonatomic, assign) UIMenuSystemElementGroupPreference inspectorPreference;

/// Specifies a preference for text formatting elements in the main menu.
@property (nonatomic, assign) UIMenuSystemElementGroupPreference textFormattingPreference;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIMainMenuSystem.h>
#endif
