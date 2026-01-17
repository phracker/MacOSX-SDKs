#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIMenuSystem.h>)
//
//  UIMenuSystem.h
//  UIKit
//
//  Copyright (c) 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The command system to build or rebuild.
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIMenuSystem : NSObject

/// The main menu system. This is identical to `UIMainMenuSystem.sharedSystem`.
@property (class, nonatomic, readonly) __kindof UIMenuSystem *mainSystem;

/// The context menu system. This is identical to `UIContextMenuSystem.sharedSystem`.
@property (class, nonatomic, readonly) __kindof UIMenuSystem *contextSystem;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Trigger a rebuild of this system at a suitable time.
- (void)setNeedsRebuild;

/// Trigger a revalidate of this system at a suitable time.
- (void)setNeedsRevalidate;

@end

typedef NS_ENUM(NSInteger, UIMenuSystemElementGroupPreference) {
    /// The default preference. The element group is automatically included based on the platform and other system behaviors.
    UIMenuSystemElementGroupPreferenceAutomatic = 0,
    /// Prefer that the element group is removed.
    UIMenuSystemElementGroupPreferenceRemoved,
    /// Prefer that the element group is included.
    UIMenuSystemElementGroupPreferenceIncluded,
} API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(UIMenuSystem.ElementGroupPreference) NS_SWIFT_SENDABLE;

/// Represents a preference for the structure of Find elements in the main menu.
typedef NS_ENUM(NSInteger, UIMenuSystemFindElementGroupConfigurationStyle) {
    /// The default preference. Find elements are automatically included based on the platform and other system behaviors.
    UIMenuSystemFindElementGroupConfigurationStyleAutomatic = 0,
    /// Prefer a minimal set of find elements, only consisting of elements to search content in the app.
    UIMenuSystemFindElementGroupConfigurationStyleSearch,
    /// Prefer a set of elements for finding within a non-editable text area
    UIMenuSystemFindElementGroupConfigurationStyleNonEditableText,
    /// Prefer a full set of elements for finding and replacing text, such as Find, Find and Replace, Find Navigation, and so on.
    UIMenuSystemFindElementGroupConfigurationStyleEditableText,
} API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(UIMenuSystemFindElementGroupConfiguration.Style) NS_SWIFT_SENDABLE;

/// Represents a configuration for find elements, should they be present.
/// You don't create one of these directly. A configuration is provided as part of a `UIMainMenuSystemConfiguration`.
UIKIT_EXTERN API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(UIMenuSystem.FindElementGroupConfiguration) NS_SWIFT_UI_ACTOR
@interface UIMenuSystemFindElementGroupConfiguration : NSObject

/// Specifies a preference for the style of Find elements in the main menu.
@property (nonatomic, assign) UIMenuSystemFindElementGroupConfigurationStyle style;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIMenuSystem.h>
#endif
