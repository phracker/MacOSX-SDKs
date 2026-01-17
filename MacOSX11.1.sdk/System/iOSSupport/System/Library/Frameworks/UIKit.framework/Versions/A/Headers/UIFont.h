#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFont.h>)
//
//  UIFont.h
//  UIKit
//
//  Copyright (c) 2007-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIFontDescriptor.h>

@class UITraitCollection;

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) @interface UIFont : NSObject <NSCopying>

// Returns an instance of the font associated with the text style and scaled appropriately for the user's selected content size category. See UIFontDescriptor.h for the complete list.
+ (UIFont *)preferredFontForTextStyle:(UIFontTextStyle)style API_AVAILABLE(ios(7.0));
// Returns an instance of the font associated with the text style and scaled appropriately for the content size category defined in the trait collection.
+ (UIFont *)preferredFontForTextStyle:(UIFontTextStyle)style compatibleWithTraitCollection:(nullable UITraitCollection *)traitCollection API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);

// Returns a font using CSS name matching semantics.
+ (nullable UIFont *)fontWithName:(NSString *)fontName size:(CGFloat)fontSize;

// Returns an array of font family names for all installed fonts
@property(class, nonatomic, readonly) NSArray<NSString *> *familyNames;

// Returns an array of font names for the specified family name
+ (NSArray<NSString *> *)fontNamesForFamilyName:(NSString *)familyName;


// Some convenience methods to create system fonts

// Think carefully before using these methods. In most cases, a font returned by +preferredFontForTextStyle: will be more appropriate, and will respect the user's selected content size category.
+ (UIFont *)systemFontOfSize:(CGFloat)fontSize;
+ (UIFont *)boldSystemFontOfSize:(CGFloat)fontSize;
+ (UIFont *)italicSystemFontOfSize:(CGFloat)fontSize;

// Weights used here are analogous to those used with UIFontDescriptor's UIFontWeightTrait.
// See the UIFontWeight... constants in UIFontDescriptor.h for suggested values.
// The caveat above about the use of ...systemFont... methods applies to these methods too.
+ (UIFont *)systemFontOfSize:(CGFloat)fontSize weight:(UIFontWeight)weight API_AVAILABLE(ios(8.2));
+ (UIFont *)monospacedDigitSystemFontOfSize:(CGFloat)fontSize weight:(UIFontWeight)weight API_AVAILABLE(ios(9.0));

/* Returns current default monospaced font for system UI. Clients of this API should be aware that the monospaced system font has a similar coverage of default system UI font, which includes Latin and common symbols used for displaying text like source code. For the characters it does not cover, the subtituted fonts are usually not the same width as the monospaced system font, they can be wider, narrower, or variable. To ensure fixed advances in text layout, clients can consider using string attributes like UIFontDescriptorFixedAdvanceAttribute. */
+ (UIFont *)monospacedSystemFontOfSize:(CGFloat)fontSize weight:(UIFontWeight)weight API_AVAILABLE(ios(13.0));


// Font attributes
@property(nonatomic,readonly,strong) NSString *familyName;
@property(nonatomic,readonly,strong) NSString *fontName;
@property(nonatomic,readonly)        CGFloat   pointSize;
@property(nonatomic,readonly)        CGFloat   ascender;
@property(nonatomic,readonly)        CGFloat   descender;
@property(nonatomic,readonly)        CGFloat   capHeight;
@property(nonatomic,readonly)        CGFloat   xHeight;
@property(nonatomic,readonly)        CGFloat   lineHeight API_AVAILABLE(ios(4.0));
@property(nonatomic,readonly)        CGFloat   leading;

// Create a new font that is identical to the current font except the specified size
- (UIFont *)fontWithSize:(CGFloat)fontSize;

// Returns a font matching the font descriptor. If fontSize is greater than 0.0, it has precedence over UIFontDescriptorSizeAttribute in fontDescriptor.
+ (UIFont *)fontWithDescriptor:(UIFontDescriptor *)descriptor size:(CGFloat)pointSize API_AVAILABLE(ios(7.0));

// Returns a font descriptor which describes the font.
@property(nonatomic, readonly) UIFontDescriptor *fontDescriptor API_AVAILABLE(ios(7.0));

@end

NS_ASSUME_NONNULL_END

 

#else
#import <UIKitCore/UIFont.h>
#endif
