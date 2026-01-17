#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIContentUnavailableTextProperties.h>)
//
//  UIContentUnavailableTextProperties.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/NSParagraphStyle.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIFont;
@class UIColor;

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIContentUnavailableTextProperties : NSObject <NSCopying, NSSecureCoding>

/// The font used for the text.
@property (nonatomic, strong) UIFont *font;

/// The color of the text.
@property (nonatomic, strong) UIColor *color;

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

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIContentUnavailableTextProperties.h>
#endif
