#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextFormattingViewControllerChangeValue.h>)
//
//  UITextFormattingViewControllerChangeValue.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITextFormattingViewControllerFormattingDescriptor.h>
#import <UIKit/NSText.h>

@class UIColor;
@class UIFont;
@class NSNumber;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#pragma mark - UITextFormattingViewControllerChangeType

/// Enumeration of text formatting actions.
typedef NSString * UITextFormattingViewControllerChangeType NS_TYPED_ENUM NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerUndefinedChangeType             NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerSetBoldChangeType               NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerRemoveBoldChangeType            NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerSetItalicChangeType             NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerRemoveItalicChangeType          NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerSetUnderlineChangeType          NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerRemoveUnderlineChangeType       NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerSetStrikethroughChangeType      NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerRemoveStrikethroughChangeType   NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerFontChangeType                  NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerFontSizeChangeType              NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerIncreaseFontSizeChangeType      NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerDecreaseFontSizeChangeType      NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerTextColorChangeType             NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerLineHeightPointSizeChangeType   NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerIncreaseIndentationChangeType   NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerDecreaseIndentationChangeType   NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerFormattingStyleChangeType       NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerTextListChangeType              NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerTextAlignmentChangeType         NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerChangeType const UITextFormattingViewControllerHighlightChangeType             NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);

#pragma mark - UITextFormattingViewControllerChangeValue

UIKIT_EXTERN API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT
/// Describes text formatting change that is a result of user action.
/// Contains type of change, any associated value that may be applicable to that change.
@interface UITextFormattingViewControllerChangeValue : NSObject <NSCopying, NSSecureCoding>

/// Type of change.
@property (nonatomic, readonly) UITextFormattingViewControllerChangeType changeType;

/// On formatting style change, use this property to determine selected style.
@property (nullable, nonatomic, readonly, copy) NSString *formattingStyleKey;

/// Any font that may be associated with the change.
/// For example, this property will be available in case of font typography settings change or new font selection.
@property (nullable, nonatomic, readonly, copy) UIFont *font;

/// Any color value that may be associated with the change.
/// For example, this property will be available if user has changed text color.
@property (nullable, nonatomic, readonly, copy) UIColor *color;

/// Any number value that may be associated with the change.
/// For example, if case of font point size change, this property will reflect new point size.
@property (nullable, nonatomic, readonly, copy) NSNumber *numberValue;

/// Text list style associated with the `UITextFormattingViewControllerTextListChangeType`.
/// If property is nil for `UITextFormattingViewControllerTextListChangeType`, it indicates text list has been removed.
@property (nullable, nonatomic, readonly, copy) UITextFormattingViewControllerTextList textList;

/// Text alignment associated with the `UITextFormattingViewControllerTextAlignmentChangeType`.
@property (nonatomic, readonly) NSTextAlignment textAlignment;

/// Text highlight associated with the `UITextFormattingViewControllerHighlightChangeType`.
/// If property is nil for `UITextFormattingViewControllerHighlightChangeType`, it indicates highlight has been removed.
@property (nullable, nonatomic, readonly, copy) UITextFormattingViewControllerHighlight highlight;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextFormattingViewControllerChangeValue.h>
#endif
