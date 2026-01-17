#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextFormattingViewControllerComponent.h>)
//
//  UITextFormattingViewControllerComponent.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#pragma mark - UITextFormattingViewControllerComponentKey

/// Predefined text formatting view controller components.
typedef NSString * UITextFormattingViewControllerComponentKey NS_TYPED_ENUM NS_SWIFT_NAME(UITextFormattingViewController.ComponentKey) API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);

UIKIT_EXTERN UITextFormattingViewControllerComponentKey const UITextFormattingViewControllerFormattingStylesComponentKey                NS_SWIFT_NAME(formattingStyles)                 API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerComponentKey const UITextFormattingViewControllerFontAttributesComponentKey                  NS_SWIFT_NAME(fontAttributes)                   API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerComponentKey const UITextFormattingViewControllerFontPickerComponentKey                      NS_SWIFT_NAME(fontPicker)                       API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerComponentKey const UITextFormattingViewControllerFontSizeComponentKey                        NS_SWIFT_NAME(fontSize)                         API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerComponentKey const UITextFormattingViewControllerFontPointSizeComponentKey                   NS_SWIFT_NAME(fontPointSize)                    API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerComponentKey const UITextFormattingViewControllerTextAlignmentComponentKey                   NS_SWIFT_NAME(textAlignment)                    API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerComponentKey const UITextFormattingViewControllerTextAlignmentAndJustificationComponentKey   NS_SWIFT_NAME(textAlignmentAndJustification)    API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerComponentKey const UITextFormattingViewControllerTextIndentationComponentKey                 NS_SWIFT_NAME(textIndentation)                  API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerComponentKey const UITextFormattingViewControllerLineHeightComponentKey                      NS_SWIFT_NAME(lineHeight)                       API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerComponentKey const UITextFormattingViewControllerListStylesComponentKey                      NS_SWIFT_NAME(listStyles)                       API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerComponentKey const UITextFormattingViewControllerTextColorComponentKey                       NS_SWIFT_NAME(textColor)                        API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerComponentKey const UITextFormattingViewControllerHighlightComponentKey                       NS_SWIFT_NAME(highlight)                        API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerComponentKey const UITextFormattingViewControllerHighlightPickerComponentKey                 NS_SWIFT_NAME(highlightPicker)                  API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);

#pragma mark - _UITextFormattingViewControllerComponentSize

/// Sizes of text formatting view controller components.
typedef NS_ENUM(NSInteger, UITextFormattingViewControllerComponentSize) {
    UITextFormattingViewControllerComponentSizeAutomatic = 0,
    UITextFormattingViewControllerComponentSizeMini = 1,
    UITextFormattingViewControllerComponentSizeSmall = 2,
    UITextFormattingViewControllerComponentSizeRegular = 3,
    UITextFormattingViewControllerComponentSizeLarge = 4,
    UITextFormattingViewControllerComponentSizeExtraLarge = 5,
} NS_SWIFT_NAME(UITextFormattingViewController.ComponentSize) API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);

#pragma mark - UITextFormattingViewControllerComponent

UIKIT_EXTERN API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NAME(UITextFormattingViewController.Component)
/// Defines text formatting view component.
@interface UITextFormattingViewControllerComponent : NSObject <NSCopying, NSSecureCoding>

/// Unique key that identifies text formatting view component.
@property (nonatomic, readonly) UITextFormattingViewControllerComponentKey componentKey;

/// Specifies preferred size of the component in text formatting view.
@property (nonatomic, readonly) UITextFormattingViewControllerComponentSize preferredSize;

/// Creates a text formatting view component configuration with component key and preferred size.
///
/// - Parameters:
///   - componentKey: Component key.
///   - preferredSize: Preferred size of component in text formatting view.
- (instancetype)initWithComponentKey:(UITextFormattingViewControllerComponentKey)componentKey
                       preferredSize:(UITextFormattingViewControllerComponentSize)preferredSize NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - UITextFormattingViewControllerComponentGroup

UIKIT_EXTERN API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NAME(UITextFormattingViewController.ComponentGroup)
/// Defines grouping of text formatting components in view.
@interface UITextFormattingViewControllerComponentGroup : NSObject <NSCopying, NSSecureCoding>

/// Components in group.
@property (nonatomic, readonly, copy) NSArray<UITextFormattingViewControllerComponent *> *components;

/// Creates a group of components.
/// - Parameter components: Components to be included in the group.
- (instancetype)initWithComponents:(NSArray<UITextFormattingViewControllerComponent *> *)components NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextFormattingViewControllerComponent.h>
#endif
