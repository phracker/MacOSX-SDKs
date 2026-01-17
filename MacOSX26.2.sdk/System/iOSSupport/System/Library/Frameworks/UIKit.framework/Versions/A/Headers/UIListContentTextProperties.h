#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIListContentTextProperties.h>)
//
//  UIListContentTextProperties.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIConfigurationColorTransformer.h>
#import <UIKit/NSParagraphStyle.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIFont;
@class UIColor;

typedef NS_ENUM(NSInteger, UIListContentTextAlignment) {
    UIListContentTextAlignmentNatural,
    UIListContentTextAlignmentCenter,
    UIListContentTextAlignmentJustified
} API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIListContentTextTransform) {
    UIListContentTextTransformNone,
    UIListContentTextTransformUppercase,
    UIListContentTextTransformLowercase,
    UIListContentTextTransformCapitalized
} API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIListContentTextProperties : NSObject <NSCopying, NSSecureCoding>

/// The font used for the text.
@property (nonatomic, strong) UIFont *font;

/// The color of the text.
@property (nonatomic, strong) UIColor *color;
/// Optional color transformer that is used to resolve the color. A nil value means the `color` is used as-is.
@property (nonatomic, copy, nullable) UIConfigurationColorTransformer colorTransformer;
/// Returns the resolved color, based on the `color` and `colorTransformer`.
- (UIColor *)resolvedColor;

/// The alignment for the text.
@property (nonatomic) UIListContentTextAlignment alignment;
/// The line break mode to use for the text.
@property (nonatomic) NSLineBreakMode lineBreakMode;

/// The maximum number of lines for the text. 0 indicates the number of lines is unlimited.
@property (nonatomic) NSInteger numberOfLines;
/// Whether the font size of the text is automatically adjusted when necessary to fit in the available width.
@property (nonatomic) BOOL adjustsFontSizeToFitWidth;
/// When `adjustsFontSizeToFitWidth` is enabled, the smallest multiplier for the font size used to make the text fit.
@property (nonatomic) CGFloat minimumScaleFactor;
/// Whether the text is tightened before truncating.
@property (nonatomic) BOOL allowsDefaultTighteningForTruncation;
/// Whether the font is automatically updated when the content size category changes.
@property (nonatomic) BOOL adjustsFontForContentSizeCategory;
/// Whether the full text will be shown when a pointer hovers over truncated text.
@property (nonatomic) BOOL showsExpansionTextWhenTruncated API_AVAILABLE(macCatalyst(16.0));

/// A transform that is applied to the text before it is displayed.
@property (nonatomic) UIListContentTextTransform transform;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIListContentTextProperties.h>
#endif
