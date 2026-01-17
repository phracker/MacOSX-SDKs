#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITabAccessory.h>)
//
//  UITabAccessory.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <UIKit/UITrait.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIView;

UIKIT_EXTERN NS_SWIFT_UI_ACTOR
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos, tvos, watchos)
@interface UITabAccessory: NSObject

/// The content view of the accessory.
@property (nonatomic, strong, nonnull, readonly) UIView *contentView;

/// Creates a new accessory with the specified content view.
- (instancetype)initWithContentView:(UIView *)contentView NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - UITabAccessoryEnvironment

typedef NS_ENUM(NSInteger, UITabAccessoryEnvironment) {
    /// Indicates the absence of any information about whether or not the trait collection is
    /// from a view that is in a tab accessory.
    UITabAccessoryEnvironmentUnspecified,

    /// The trait collection is from a view that is not in an active tab accessory environment.
    UITabAccessoryEnvironmentNone,

    /// The environment for when the accessory is laid out either:
    ///   - above the bottom tab bar when it is visible; or,
    ///   - at the bottom of the UITabBarController's view.
    UITabAccessoryEnvironmentRegular,

    /// The environment for when the accessory is laid out inline with
    /// the collapsed bottom tab bar.
    UITabAccessoryEnvironmentInline,
} API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos, tvos, watchos) NS_SWIFT_NAME(UITabAccessory.Environment);

#pragma mark UITraitTabAccessoryEnvironment

/// A trait that specifies the UITabAccessoryEnvironment, if any, that a view is in. It is set on views inside
/// UITabBarController.bottomAccessory. Defaults to UITabAccessoryEnvironmentUnspecified.
UIKIT_EXTERN NS_SWIFT_UI_ACTOR NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos, tvos, watchos)
@interface UITraitTabAccessoryEnvironment : NSObject <UINSIntegerTraitDefinition>

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITabAccessory.h>
#endif
