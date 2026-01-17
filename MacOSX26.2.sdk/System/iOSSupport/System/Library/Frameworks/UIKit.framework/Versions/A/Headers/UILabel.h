#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UILabel.h>)
//
//  UILabel.h
//  UIKit
//
//  Copyright (c) 2006-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIContentSizeCategoryAdjusting.h>
#import <UIKit/UILetterformAwareAdjusting.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIColor, UIFont;

typedef NS_ENUM(NSInteger, UILabelVibrancy) {
    // No vibrancy will be applied automatically in this mode.
    UILabelVibrancyNone,
    
    // Vibrancy gets applied automatically to labels if the context allows it.
    // The kind of vibrancy effects depends on the labels text color.
    // labelColor becomes UIVibrancyEffectStyleLabel,
    // secondaryLabelColor becomes UIVibrancyEffectStyleSecondaryLabel etc.
    UILabelVibrancyAutomatic,
} API_AVAILABLE(visionos(1.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UILabel : UIView <NSCoding, UIContentSizeCategoryAdjusting, UILetterformAwareAdjusting>

@property(nullable, nonatomic,copy)   NSString           *text; // default is nil
@property(null_resettable, nonatomic,strong) UIFont      *font UI_APPEARANCE_SELECTOR; // default is nil (system font 17 plain)
@property(null_resettable, nonatomic,strong) UIColor     *textColor UI_APPEARANCE_SELECTOR; // default is labelColor

// Controls whether a label becomes vibrant automatically.
//
// If a label has a vibrancy mode other than `None` set, the system tries
// to apply vibrancy automatically to that label. This will only succeed if
// the label is in a context that allows vibrancy, which in general means the
// the label needs to be on top of a blurred material.
//
// This property can only be used to opt-in to automatic vibrancy. It is not
// a way to opt-out of vibrancy that is enabled by other means. A label
// placed in a vibrant `UIVisualEffectView` with preferred vibrancy `None` will
// still be vibrant.
//
// The default is `automatic` on xrOS and `none` on all other platforms.
@property (nonatomic) UILabelVibrancy preferredVibrancy UI_APPEARANCE_SELECTOR API_AVAILABLE(visionos(1.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@property(nullable, nonatomic,strong) UIColor            *shadowColor UI_APPEARANCE_SELECTOR; // default is nil (no shadow)
@property(nonatomic)        CGSize             shadowOffset UI_APPEARANCE_SELECTOR; // default is CGSizeMake(0, -1) -- a top shadow
@property(nonatomic)        NSTextAlignment    textAlignment;   // default is NSTextAlignmentNatural (before iOS 9, the default was NSTextAlignmentLeft)
@property(nonatomic)        NSLineBreakMode    lineBreakMode;   // default is NSLineBreakByTruncatingTail. used for single and multiple lines of text

// the underlying attributed string drawn by the label, if set, the label ignores the properties above.
@property(nullable, nonatomic,copy)   NSAttributedString *attributedText API_AVAILABLE(ios(6.0));  // default is nil

// the 'highlight' property is used by subclasses for such things as pressed states. it's useful to make it part of the base class as a user property

@property(nullable, nonatomic,strong)               UIColor *highlightedTextColor UI_APPEARANCE_SELECTOR; // default is nil
@property(nonatomic,getter=isHighlighted) BOOL     highlighted;          // default is NO

@property(nonatomic,getter=isUserInteractionEnabled) BOOL userInteractionEnabled;  // default is NO
@property(nonatomic,getter=isEnabled)                BOOL enabled;                 // default is YES. changes how the label is drawn

// this determines the number of lines to draw and what to do when sizeToFit is called. default value is 1 (single line). A value of 0 means no limit
// if the height of the text reaches the # of lines or the height of the view is less than the # of lines allowed, the text will be
// truncated using the line break mode.

@property(nonatomic) NSInteger numberOfLines;

// these next 3 properties allow the label to be autosized to fit a certain width by scaling the font size(s) by a scaling factor >= the minimum scaling factor
// and to specify how the text baseline moves when it needs to shrink the font.

@property(nonatomic) BOOL adjustsFontSizeToFitWidth;         // default is NO
@property(nonatomic) UIBaselineAdjustment baselineAdjustment; // default is UIBaselineAdjustmentAlignBaselines
@property(nonatomic) CGFloat minimumScaleFactor API_AVAILABLE(ios(6.0)); // default is 0.0


// Tightens inter-character spacing in attempt to fit lines wider than the available space if the line break mode is one of the truncation modes before starting to truncate.
// The maximum amount of tightening performed is determined by the system based on contexts such as font, line width, etc.
@property(nonatomic) BOOL allowsDefaultTighteningForTruncation API_AVAILABLE(ios(9.0)); // default is NO

// Specifies the line break strategies that may be used for laying out the text in this label.
// If this property is not set, the default value is NSLineBreakStrategyStandard.
// If the label contains an attributed text with paragraph style(s) that specify a set of line break strategies, the set of strategies in the paragraph style(s) will be used instead of the set of strategies defined by this property.
@property(nonatomic) NSLineBreakStrategy lineBreakStrategy API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

// override points. can adjust rect before calling super.
// label has default content mode of UIViewContentModeRedraw

- (CGRect)textRectForBounds:(CGRect)bounds limitedToNumberOfLines:(NSInteger)numberOfLines;
- (void)drawTextInRect:(CGRect)rect;


// Support for constraint-based layout (auto layout)
// If nonzero, this is used when determining -intrinsicContentSize for multiline labels
@property(nonatomic) CGFloat preferredMaxLayoutWidth API_AVAILABLE(ios(6.0));


// If YES, the UILabel will scroll its text while any of its immediate or distant superviews become focused. Also, lineBreakMode, adjustsFontSizeToFitWidth, and allowsDefaultTighteningForTruncation are ignored.
@property (nonatomic) BOOL enablesMarqueeWhenAncestorFocused API_AVAILABLE(tvos(12.0)) API_UNAVAILABLE(ios, watchos);

/// Indicates whether expansion text will be shown when the view is too small to show all the contents. Defaults to NO.
@property (nonatomic) BOOL showsExpansionTextWhenTruncated API_AVAILABLE(macCatalyst(15.0)) API_UNAVAILABLE(watchos);

// deprecated:

@property(nonatomic) CGFloat minimumFontSize API_DEPRECATED("", ios(2.0, 6.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos); // deprecated - use minimumScaleFactor. default is 0.0

// Non-functional.  Hand tune by using NSKernAttributeName to affect tracking, or consider using the allowsDefaultTighteningForTruncation property.
@property(nonatomic) BOOL adjustsLetterSpacingToFitWidth API_DEPRECATED("", ios(6.0, 7.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UILabel.h>
#endif
