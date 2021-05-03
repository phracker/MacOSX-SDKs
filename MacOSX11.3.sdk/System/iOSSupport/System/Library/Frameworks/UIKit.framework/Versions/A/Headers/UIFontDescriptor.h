#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFontDescriptor.h>)
//
//  UIFontDescriptor.h
//  UIKit
//
//  Copyright (c) 2013-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>


NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(uint32_t, UIFontDescriptorSymbolicTraits) {
    /* Symbolic Font Traits (Typeface info - lower 16 bits of UIFontDescriptorSymbolicTraits) */
    /*
     UIFontDescriptorSymbolicTraits symbolically describes stylistic aspects of a font. The upper 16 bits is used to describe appearance of the font whereas the lower 16 bits for typeface. The font appearance information represented by the upper 16 bits can be used for stylistic font matching.
     */
    UIFontDescriptorTraitItalic = 1u << 0,
    UIFontDescriptorTraitBold = 1u << 1,
    UIFontDescriptorTraitExpanded = 1u << 5, // expanded and condensed traits are mutually exclusive
    UIFontDescriptorTraitCondensed = 1u << 6,
    UIFontDescriptorTraitMonoSpace = 1u << 10, // Use fixed-pitch glyphs if available. May have multiple glyph advances (most CJK glyphs may contain two spaces)
    UIFontDescriptorTraitVertical = 1u << 11, // Use vertical glyph variants and metrics
    UIFontDescriptorTraitUIOptimized = 1u << 12, // Synthesize appropriate attributes for UI rendering such as control titles if necessary
    UIFontDescriptorTraitTightLeading = 1u << 15, // Use tighter leading values
    UIFontDescriptorTraitLooseLeading = 1u << 16, // Use looser leading values
    
    /* Font appearance info (upper 16 bits of NSFontSymbolicTraits */
    /* UIFontDescriptorClassFamily classifies certain stylistic qualities of the font. These values correspond closely to the font class values in the OpenType 'OS/2' table. The class values are bundled in the upper four bits of the UIFontDescriptorSymbolicTraits and can be accessed via UIFontDescriptorClassMask. For specific meaning of each identifier, refer to the OpenType specification.
     */
    UIFontDescriptorClassMask = 0xF0000000,
    
    UIFontDescriptorClassUnknown = 0u << 28,
    UIFontDescriptorClassOldStyleSerifs = 1u << 28,
    UIFontDescriptorClassTransitionalSerifs = 2u << 28,
    UIFontDescriptorClassModernSerifs = 3u << 28,
    UIFontDescriptorClassClarendonSerifs = 4u << 28,
    UIFontDescriptorClassSlabSerifs = 5u << 28,
    UIFontDescriptorClassFreeformSerifs = 7u << 28,
    UIFontDescriptorClassSansSerif = 8u << 28,
    UIFontDescriptorClassOrnamentals = 9u << 28,
    UIFontDescriptorClassScripts = 10u << 28,
    UIFontDescriptorClassSymbolic = 12u << 28
} API_AVAILABLE(ios(7.0));

typedef NSUInteger UIFontDescriptorClass;
typedef NSString * UIFontTextStyle NS_TYPED_ENUM;
typedef NSString * UIFontDescriptorAttributeName NS_TYPED_ENUM;
typedef NSString * UIFontDescriptorTraitKey NS_TYPED_ENUM;
typedef NSString * UIFontDescriptorFeatureKey NS_TYPED_EXTENSIBLE_ENUM;
typedef CGFloat UIFontWeight NS_TYPED_EXTENSIBLE_ENUM;

typedef NSString * UIFontDescriptorSystemDesign NS_TYPED_ENUM;
UIKIT_EXTERN UIFontDescriptorSystemDesign const UIFontDescriptorSystemDesignDefault API_AVAILABLE(ios(13.0), watchos(5.2), tvos(13.0));
UIKIT_EXTERN UIFontDescriptorSystemDesign const UIFontDescriptorSystemDesignRounded API_AVAILABLE(ios(13.0), watchos(5.2), tvos(13.0));
UIKIT_EXTERN UIFontDescriptorSystemDesign const UIFontDescriptorSystemDesignSerif API_AVAILABLE(ios(13.0), watchos(7.0), tvos(13.0));
UIKIT_EXTERN UIFontDescriptorSystemDesign const UIFontDescriptorSystemDesignMonospaced API_AVAILABLE(ios(13.0), watchos(7.0), tvos(13.0));

@class NSMutableDictionary, NSDictionary, NSArray, NSSet, UITraitCollection;

UIKIT_EXTERN API_AVAILABLE(ios(7.0)) @interface UIFontDescriptor : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

// Core attribute access
@property(nonatomic, readonly) NSString *postscriptName;
@property(nonatomic, readonly) CGFloat   pointSize;
@property(nonatomic, readonly) CGAffineTransform matrix API_UNAVAILABLE(macCatalyst);
@property(nonatomic, readonly) UIFontDescriptorSymbolicTraits symbolicTraits;

- (nullable id)objectForKey:(UIFontDescriptorAttributeName)anAttribute;

@property(nonatomic, readonly) NSDictionary<UIFontDescriptorAttributeName, id> *fontAttributes;

// Instance conversion
// Returns "normalized" font descriptors matching the receiver. mandatoryKeys is an NSSet instance containing keys that are required to be identical in order to be matched. mandatoryKeys can be nil.
- (NSArray<UIFontDescriptor *> *)matchingFontDescriptorsWithMandatoryKeys:(nullable NSSet<UIFontDescriptorAttributeName> *)mandatoryKeys;

// Instantiation
+ (UIFontDescriptor *)fontDescriptorWithFontAttributes:(NSDictionary<UIFontDescriptorAttributeName, id> *)attributes;
+ (UIFontDescriptor *)fontDescriptorWithName:(NSString *)fontName size:(CGFloat)size;
+ (UIFontDescriptor *)fontDescriptorWithName:(NSString *)fontName matrix:(CGAffineTransform)matrix;

// Returns a font descriptor containing the text style and containing the user's selected content size category.
+ (UIFontDescriptor *)preferredFontDescriptorWithTextStyle:(UIFontTextStyle)style;
// Returns a font descriptor containing the text style and containing the content size category defined in the trait collection.
+ (UIFontDescriptor *)preferredFontDescriptorWithTextStyle:(UIFontTextStyle)style compatibleWithTraitCollection:(nullable UITraitCollection *)traitCollection API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);

- (instancetype)initWithFontAttributes:(NSDictionary<UIFontDescriptorAttributeName, id> *)attributes NS_DESIGNATED_INITIALIZER;

- (UIFontDescriptor *)fontDescriptorByAddingAttributes:(NSDictionary<UIFontDescriptorAttributeName, id> *)attributes; // the new attributes take precedence over the existing ones in the receiver
- (UIFontDescriptor *)fontDescriptorWithSize:(CGFloat)newPointSize;
- (UIFontDescriptor *)fontDescriptorWithMatrix:(CGAffineTransform)matrix API_UNAVAILABLE(macCatalyst);
- (UIFontDescriptor *)fontDescriptorWithFace:(NSString *)newFace;
- (UIFontDescriptor *)fontDescriptorWithFamily:(NSString *)newFamily;

- (nullable UIFontDescriptor *)fontDescriptorWithSymbolicTraits:(UIFontDescriptorSymbolicTraits)symbolicTraits; // Returns a new font descriptor reference in the same family with the given symbolic traits, or nil if none found in the system.
- (nullable UIFontDescriptor *)fontDescriptorWithDesign:(UIFontDescriptorSystemDesign)design API_AVAILABLE(ios(13.0), watchos(5.2), tvos(13.0)); // Returns a new font descriptor reference with the given design, or nil if no match is found in the system.


@end

// Predefined font attributes not defined in NSAttributedString.h

UIKIT_EXTERN UIFontDescriptorAttributeName const UIFontDescriptorFamilyAttribute API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIFontDescriptorAttributeName const UIFontDescriptorNameAttribute API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIFontDescriptorAttributeName const UIFontDescriptorFaceAttribute API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIFontDescriptorAttributeName const UIFontDescriptorSizeAttribute API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIFontDescriptorAttributeName const UIFontDescriptorVisibleNameAttribute API_AVAILABLE(ios(7.0));

UIKIT_EXTERN UIFontDescriptorAttributeName const UIFontDescriptorMatrixAttribute API_AVAILABLE(ios(7.0)); // An NSValue containing a CGAffineTransform. (default: identity matrix)
UIKIT_EXTERN UIFontDescriptorAttributeName const UIFontDescriptorCharacterSetAttribute API_AVAILABLE(ios(7.0)); // An NSCharacterSet instance representing a set of Unicode characters covered by the font. (default: supplied by font)
UIKIT_EXTERN UIFontDescriptorAttributeName const UIFontDescriptorCascadeListAttribute API_AVAILABLE(ios(7.0)); // An NSArray instance. Each member of the array is a sub-descriptor. (default: the system default cascading list for user's locale)
UIKIT_EXTERN UIFontDescriptorAttributeName const UIFontDescriptorTraitsAttribute API_AVAILABLE(ios(7.0)); // An NSDictionary instance fully describing font traits. (default: supplied by font)
UIKIT_EXTERN UIFontDescriptorAttributeName const UIFontDescriptorFixedAdvanceAttribute API_AVAILABLE(ios(7.0)); // A float represented as an NSNumber. The value overrides glyph advancement specified by the font. (default: supplied by each glyph)
UIKIT_EXTERN UIFontDescriptorAttributeName const UIFontDescriptorFeatureSettingsAttribute API_AVAILABLE(ios(7.0)); // An array of dictionaries representing non-default font feature settings. Each dictionary contains UIFontFeatureTypeIdentifierKey and UIFontFeatureSelectorIdentifierKey.

// An NSString containing the desired Text Style
UIKIT_EXTERN UIFontDescriptorAttributeName const UIFontDescriptorTextStyleAttribute API_AVAILABLE(ios(7.0));
    
// Font traits keys
// This key is used with a trait dictionary to get the symbolic traits value as an NSNumber.
UIKIT_EXTERN UIFontDescriptorTraitKey const UIFontSymbolicTrait API_AVAILABLE(ios(7.0));

// This key is used with a trait dictionary to get the normalized weight value as an NSNumber. The valid value range is from -1.0 to 1.0. The value of 0.0 corresponds to the regular or medium font weight.
UIKIT_EXTERN UIFontDescriptorTraitKey const UIFontWeightTrait API_AVAILABLE(ios(7.0));

// This key is used with a trait dictionary to get the relative inter-glyph spacing value as an NSNumber. The valid value range is from -1.0 to 1.0. The value of 0.0 corresponds to the regular glyph spacing.
UIKIT_EXTERN UIFontDescriptorTraitKey const UIFontWidthTrait API_AVAILABLE(ios(7.0));

// This key is used with a trait dictionary to get the relative slant angle value as an NSNumber. The valid value range is from -1.0 to 1.0. The value or 0.0 corresponds to 0 degree clockwise rotation from the vertical and 1.0 corresponds to 30 degrees clockwise rotation.
UIKIT_EXTERN UIFontDescriptorTraitKey const UIFontSlantTrait API_AVAILABLE(ios(7.0));

// Suggested values for use with UIFontWeightTrait, and UIFont's systemFontOfSize:weight:
// Beware that most fonts will _not_ have variants available in all these weights!
UIKIT_EXTERN const UIFontWeight UIFontWeightUltraLight API_AVAILABLE(ios(8.2));
UIKIT_EXTERN const UIFontWeight UIFontWeightThin API_AVAILABLE(ios(8.2));
UIKIT_EXTERN const UIFontWeight UIFontWeightLight API_AVAILABLE(ios(8.2));
UIKIT_EXTERN const UIFontWeight UIFontWeightRegular API_AVAILABLE(ios(8.2));
UIKIT_EXTERN const UIFontWeight UIFontWeightMedium API_AVAILABLE(ios(8.2));
UIKIT_EXTERN const UIFontWeight UIFontWeightSemibold API_AVAILABLE(ios(8.2));
UIKIT_EXTERN const UIFontWeight UIFontWeightBold API_AVAILABLE(ios(8.2));
UIKIT_EXTERN const UIFontWeight UIFontWeightHeavy API_AVAILABLE(ios(8.2));
UIKIT_EXTERN const UIFontWeight UIFontWeightBlack API_AVAILABLE(ios(8.2));

// Font feature keys
// A number object specifying font feature type such as ligature, character shape, etc.
UIKIT_EXTERN UIFontDescriptorFeatureKey const UIFontFeatureTypeIdentifierKey API_AVAILABLE(ios(7.0));

// A number object specifying font feature selector such as common ligature off, traditional character shape, etc.
UIKIT_EXTERN UIFontDescriptorFeatureKey const UIFontFeatureSelectorIdentifierKey API_AVAILABLE(ios(7.0));

// Font text styles, semantic descriptions of the intended use for a font returned by +[UIFont preferredFontForTextStyle:]
UIKIT_EXTERN UIFontTextStyle const UIFontTextStyleLargeTitle API_AVAILABLE(ios(11.0), watchos(5.0)) API_UNAVAILABLE(tvos);
UIKIT_EXTERN UIFontTextStyle const UIFontTextStyleTitle1 API_AVAILABLE(ios(9.0));
UIKIT_EXTERN UIFontTextStyle const UIFontTextStyleTitle2 API_AVAILABLE(ios(9.0));
UIKIT_EXTERN UIFontTextStyle const UIFontTextStyleTitle3 API_AVAILABLE(ios(9.0));
UIKIT_EXTERN UIFontTextStyle const UIFontTextStyleHeadline API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIFontTextStyle const UIFontTextStyleSubheadline API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIFontTextStyle const UIFontTextStyleBody API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIFontTextStyle const UIFontTextStyleCallout API_AVAILABLE(ios(9.0));
UIKIT_EXTERN UIFontTextStyle const UIFontTextStyleFootnote API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIFontTextStyle const UIFontTextStyleCaption1 API_AVAILABLE(ios(7.0));
UIKIT_EXTERN UIFontTextStyle const UIFontTextStyleCaption2 API_AVAILABLE(ios(7.0));

NS_ASSUME_NONNULL_END


#else
#import <UIKitCore/UIFontDescriptor.h>
#endif
