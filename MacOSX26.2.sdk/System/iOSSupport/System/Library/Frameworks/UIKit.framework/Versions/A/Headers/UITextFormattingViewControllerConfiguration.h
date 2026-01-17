#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextFormattingViewControllerConfiguration.h>)
//
//  UITextFormattingViewControllerConfiguration.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class UIColor;
@class UIFont;
@class UITextFormattingViewControllerFormattingStyle;
@class UITextFormattingViewControllerComponentGroup;
@class UIFontPickerViewControllerConfiguration;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#pragma mark - UITextFormattingViewControllerConfiguration

UIKIT_EXTERN API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NAME(UITextFormattingViewController.Configuration)
/// Text formatting view controller configuration object.
@interface UITextFormattingViewControllerConfiguration : NSObject <NSCopying, NSSecureCoding>

/// Component groups displayed by text formatting view.
@property (nonatomic, readonly, copy) NSArray<UITextFormattingViewControllerComponentGroup *> *groups;

/// Configurations of formatting styles available in text formatting view.
@property (nonatomic, nullable, copy) NSArray<UITextFormattingViewControllerFormattingStyle *> *formattingStyles NS_REFINED_FOR_SWIFT;

/// Configuration object that will be used to customize `UIFontPickerViewController` if presented by `UITextFormattingViewController`.
@property (nonatomic, nullable, copy) UIFontPickerViewControllerConfiguration *fontPickerConfiguration;

/// Creates a default configuration with most common text formatting options.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates a configuration object with provided component groups.
/// - Parameter groups: Component groups displayed in text formatting view.
- (instancetype)initWithGroups:(NSArray<UITextFormattingViewControllerComponentGroup *> *)groups;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextFormattingViewControllerConfiguration.h>
#endif
