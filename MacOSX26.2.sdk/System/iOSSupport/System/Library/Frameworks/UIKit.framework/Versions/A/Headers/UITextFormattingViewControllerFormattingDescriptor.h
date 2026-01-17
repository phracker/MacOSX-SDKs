#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextFormattingViewControllerFormattingDescriptor.h>)
//
//  UITextFormattingViewControllerFormattingDescriptor.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class UIFont;
@class UIColor;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#pragma mark - UITextFormattingViewControllerTextAlignment

/// Text formatting horizontal alignment state.
typedef NSString * UITextFormattingViewControllerTextAlignment NS_TYPED_ENUM NS_SWIFT_NAME(UITextFormattingViewController.TextAlignment) API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);

UIKIT_EXTERN UITextFormattingViewControllerTextAlignment const UITextFormattingViewControllerTextAlignmentLeft      NS_SWIFT_NAME(left)         API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerTextAlignment const UITextFormattingViewControllerTextAlignmentCenter    NS_SWIFT_NAME(center)       API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerTextAlignment const UITextFormattingViewControllerTextAlignmentRight     NS_SWIFT_NAME(right)        API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerTextAlignment const UITextFormattingViewControllerTextAlignmentJustified NS_SWIFT_NAME(justified)    API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerTextAlignment const UITextFormattingViewControllerTextAlignmentNatural   NS_SWIFT_NAME(natural)      API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);

#pragma mark - UITextFormattingViewControllerTextList

/// Text formatting text list state.
typedef NSString * UITextFormattingViewControllerTextList NS_TYPED_ENUM NS_SWIFT_NAME(UITextFormattingViewController.TextList) API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);

UIKIT_EXTERN UITextFormattingViewControllerTextList const UITextFormattingViewControllerTextListDisc                NS_SWIFT_NAME(disc)         API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerTextList const UITextFormattingViewControllerTextListHyphen              NS_SWIFT_NAME(hyphen)       API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerTextList const UITextFormattingViewControllerTextListDecimal             NS_SWIFT_NAME(decimal)      API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerTextList const UITextFormattingViewControllerTextListOther               NS_SWIFT_NAME(other)        API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);

#pragma mark - UITextFormattingViewControllerHighlight

/// Text formatting highlight state.
typedef NSString * UITextFormattingViewControllerHighlight NS_TYPED_ENUM NS_SWIFT_NAME(UITextFormattingViewController.Highlight) API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);

UIKIT_EXTERN UITextFormattingViewControllerHighlight const UITextFormattingViewControllerHighlightDefault           NS_SWIFT_NAME(default)      API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerHighlight const UITextFormattingViewControllerHighlightPurple            NS_SWIFT_NAME(purple)       API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerHighlight const UITextFormattingViewControllerHighlightPink              NS_SWIFT_NAME(pink)         API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerHighlight const UITextFormattingViewControllerHighlightOrange            NS_SWIFT_NAME(orange)       API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerHighlight const UITextFormattingViewControllerHighlightMint              NS_SWIFT_NAME(mint)         API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
UIKIT_EXTERN UITextFormattingViewControllerHighlight const UITextFormattingViewControllerHighlightBlue              NS_SWIFT_NAME(blue)         API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);

#pragma mark - UITextFormattingViewControllerFormattingDescriptor

UIKIT_EXTERN API_AVAILABLE(ios(18.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT
/// Object that represents current text formatting state.
/// This can apply to formatting state of some selected range of text or currently applicable input formatting.
@interface UITextFormattingViewControllerFormattingDescriptor : NSObject <NSCopying, NSSecureCoding>

/// Initializes formatting descriptor with default property values.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Initializes formatting descriptor with a string and selected range of string.
/// - Parameters:
///   - string: Attributed string for which we are creating formatting descriptor.
///   - range: Range of string that is being represented by descriptor
- (instancetype)initWithString:(NSAttributedString *)string range:(NSRange)range;

/// Initializes formatting descriptor with attribute dictionary.
/// - Parameter attributes: Attribute dictionary that is being represented by descriptor.
- (instancetype)initWithAttributes:(NSDictionary<NSAttributedStringKey, id> *)attributes;

@property (nonatomic, nullable, copy) NSArray<UIFont *> *fonts;

@property (nonatomic, nullable, copy) NSArray<UIColor *> *textColors;

@property (nonatomic) CGFloat lineHeight;

@property (nonatomic) BOOL underlinePresent;

@property (nonatomic) BOOL strikethroughPresent;

@property (nonatomic, copy) NSSet<UITextFormattingViewControllerTextAlignment> *textAlignments;

@property (nonatomic, copy) NSSet<UITextFormattingViewControllerTextList> *textLists;

@property (nonatomic, copy) NSSet<UITextFormattingViewControllerHighlight> *highlights;

@property (nonatomic, nullable, copy) NSString *formattingStyleKey;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextFormattingViewControllerFormattingDescriptor.h>
#endif
