/*
	NSFontDescriptor.h
	Application Kit
	Copyright (c) 2003-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSSet.h>
#import <AppKit/AppKitDefines.h>


/* Symbolic Font Traits */
/*!
    @enum NSFontSymbolicTraits
    @abstract Symbolic representation of stylistic font attributes.
    @discussion NSFontSymbolicTraits symbolically describes stylistic aspects of a font. The upper 16 bits is used to describe appearance of the font whereas the lower 16 bits for typeface. The font appearance information represented by the upper 16 bits can be used for stylistic font matching. The symbolic traits supersedes the existing NSFontTraitMask type used by NSFontManager. The corresponding values are kept compatible between NSFontTraitMask and NSFontSymbolicTraits.
*/
NS_ASSUME_NONNULL_BEGIN

typedef uint32_t NSFontSymbolicTraits;

/* Font appearance info (upper 16 bits of NSFontSymbolicTraits */
/*!
    @enum NSFontFamilyClass
    @abstract Stylistic class values.
    @discussion NSFontFamilyClass classifies certain stylistic qualities of the font. These values correspond closely to the font class values in the OpenType 'OS/2' table. The class values are bundled in the upper four bits of the NSFontSymbolicTraits and can be accessed via NSFontFamilyClassMask. For specific meaning of each identifier, refer to the OpenType specification.
 */
enum {
    NSFontUnknownClass = 0 << 28,
    NSFontOldStyleSerifsClass = 1 << 28,
    NSFontTransitionalSerifsClass = 2 << 28,
    NSFontModernSerifsClass = 3 << 28,
    NSFontClarendonSerifsClass = 4 << 28,
    NSFontSlabSerifsClass = 5 << 28,
    NSFontFreeformSerifsClass = 7 << 28,
    NSFontSansSerifClass = 8 << 28,
    NSFontOrnamentalsClass = 9 << 28,
    NSFontScriptsClass = 10 << 28,
    NSFontSymbolicClass = 12 << 28
};	
typedef uint32_t NSFontFamilyClass;

enum {
    NSFontFamilyClassMask = 0xF0000000
};

/* Typeface info (lower 16 bits of NSFontSymbolicTraits */
enum {
    NSFontItalicTrait = (1 << 0),
    NSFontBoldTrait = (1 << 1),
    NSFontExpandedTrait = (1 << 5), // expanded and condensed traits are mutually exclusive
    NSFontCondensedTrait = (1 << 6),
    NSFontMonoSpaceTrait = (1 << 10), // Use fixed-pitch glyphs if available. May have multiple glyph advances (most CJK glyphs may contain two spaces)
    NSFontVerticalTrait = (1 << 11), // Use vertical glyph variants and metrics
    NSFontUIOptimizedTrait = (1 << 12) // Synthesize appropriate attributes for UI rendering such as control titles if necessary
};

@class NSAffineTransform;

@interface NSFontDescriptor: NSObject <NSCopying, NSSecureCoding> {
/* All instance variables are private */
    NSMutableDictionary *_attributes;
    id _reserved1;
    id _reserved2;
    id _reserved3;
    id _reserved4;
    id _reserved5;
}

/* Core attribute access */
@property (nullable, readonly, copy) NSString *postscriptName;
@property (readonly) CGFloat pointSize;
@property (nullable, readonly, copy) NSAffineTransform *matrix;
@property (readonly) NSFontSymbolicTraits symbolicTraits;

- (nullable id)objectForKey:(NSString *)anAttribute;

@property (readonly, copy) NSDictionary<NSString *, id> *fontAttributes;

/* Instantiation */
+ (NSFontDescriptor *)fontDescriptorWithFontAttributes:(nullable NSDictionary<NSString *, id> *)attributes;
+ (NSFontDescriptor *)fontDescriptorWithName:(NSString *)fontName size:(CGFloat)size;
+ (NSFontDescriptor *)fontDescriptorWithName:(NSString *)fontName matrix:(NSAffineTransform *)matrix;

- (instancetype)initWithFontAttributes:(nullable NSDictionary<NSString *, id> *)attributes;
/* Instance conversion */
/* Returns "normalized" font descriptors matching the receiver. mandatoryKeys is an NSSet instance containing keys that are required to be identical in order to be matched. mandatoryKeys can be nil.
*/
- (NSArray<NSFontDescriptor *> *)matchingFontDescriptorsWithMandatoryKeys:(nullable NSSet<NSString *> *)mandatoryKeys;

/* Returns a "normalized" font descriptor matching the receiver. It is the first element returned from -matchingFontDescriptorsWithMandatoryKeys:. mandatoryKeys is an NSSet instance containing keys that are required to be identical in order to be matched. mandatoryKeys can be nil.
 */
- (nullable NSFontDescriptor *)matchingFontDescriptorWithMandatoryKeys:(nullable NSSet<NSString *> *)mandatoryKeys NS_AVAILABLE_MAC(10_5);

- (NSFontDescriptor *)fontDescriptorByAddingAttributes:(NSDictionary<NSString *, id> *)attributes; // the new attributes take precedence over the existing ones in the receiver
- (NSFontDescriptor *)fontDescriptorWithSymbolicTraits:(NSFontSymbolicTraits)symbolicTraits;
- (NSFontDescriptor *)fontDescriptorWithSize:(CGFloat)newPointSize;
- (NSFontDescriptor *)fontDescriptorWithMatrix:(NSAffineTransform *)matrix;
- (NSFontDescriptor *)fontDescriptorWithFace:(NSString *)newFace;
- (NSFontDescriptor *)fontDescriptorWithFamily:(NSString *)newFamily;
@end

/* Predefined font attributes not defined in NSAttributedString.h */

APPKIT_EXTERN NSString * NSFontFamilyAttribute;
APPKIT_EXTERN NSString * NSFontNameAttribute;
APPKIT_EXTERN NSString * NSFontFaceAttribute;
APPKIT_EXTERN NSString * NSFontSizeAttribute; 
APPKIT_EXTERN NSString * NSFontVisibleNameAttribute; 

APPKIT_EXTERN NSString * NSFontMatrixAttribute                  ; // An NSAffineTransform instance. (default: identity matrix)
APPKIT_EXTERN NSString * NSFontVariationAttribute               ; // An NSDictionary instance describing variation axis (default: supplied by font)
APPKIT_EXTERN NSString * NSFontCharacterSetAttribute            ; // An NSCharacterSet instance representing a set of Unicode characters covered by the font. (default: supplied by font)
APPKIT_EXTERN NSString * NSFontCascadeListAttribute             ; // An NSArray instance. Each member of the array is a sub-descriptor. (default: the system default cascading list for user's locale)
APPKIT_EXTERN NSString * NSFontTraitsAttribute                  ; // An NSDictionary instance fully describing font traits. (default: supplied by font)
APPKIT_EXTERN NSString * NSFontFixedAdvanceAttribute            ; // A float represented as an NSNumber. The value overrides glyph advancement specified by the font. (default: 0.0)
APPKIT_EXTERN NSString * NSFontFeatureSettingsAttribute          NS_AVAILABLE_MAC(10_5); // An array of dictionaries representing non-default font feature settings. Each dictionary contains NSFontFeatureTypeIdentifierKey and NSFontFeatureSelectorIdentifierKey.

APPKIT_EXTERN NSString * NSFontColorAttribute 			NS_DEPRECATED_MAC(10_3, 10_4); // This attribute is obsolete. Use NSForegroundColorAttributeName instead.

/* Font traits keys */
/* This key is used with a trait dictionary to get the symbolic traits value as an NSNumber.
*/
APPKIT_EXTERN NSString * NSFontSymbolicTrait;

/* This key is used with a trait dictionary to get the normalized weight value as an NSNumber. The valid value range is from -1.0 to 1.0. The value of 0.0 corresponds to the regular or medium font weight.
*/
APPKIT_EXTERN NSString * NSFontWeightTrait;

/* This key is used with a trait dictionary to get the relative inter-glyph spacing value as an NSNumber. The valid value range is from -1.0 to 1.0. The value of 0.0 corresponds to the regular glyph spacing.
*/
APPKIT_EXTERN NSString * NSFontWidthTrait;

/* This key is used with a trait dictionary to get the relative slant angle value as an NSNumber. The valid value range is from -1.0 to 1.0. The value or 0.0 corresponds to 0 degree clockwise rotation from the vertical and 1.0 corresponds to 30 degrees clockwise rotation.
*/
APPKIT_EXTERN NSString * NSFontSlantTrait;

/* Font variation keys */
/* This key is used with a variation axis dictionary to get the axis identifier value as an NSNumber.
*/
APPKIT_EXTERN NSString * NSFontVariationAxisIdentifierKey;

/* This key is used with a variation axis dictionary to get the  minimum axis value as an NSNumber.
*/
APPKIT_EXTERN NSString * NSFontVariationAxisMinimumValueKey;

/* This key is used with a variation axis dictionary to get the maximum axis value as an NSNumber.
*/
APPKIT_EXTERN NSString * NSFontVariationAxisMaximumValueKey;

/* This key is used with a variation axis dictionary to get the default axis value as an NSNumber.
*/
APPKIT_EXTERN NSString * NSFontVariationAxisDefaultValueKey;

/* This key is used with a variation axis dictionary to get the localized variation axis name.
*/
APPKIT_EXTERN NSString * NSFontVariationAxisNameKey;

/* Font feature keys */
/* A number object specifying font feature type such as ligature, character shape, etc. Refer to ATS/SFNTLayoutTypes.h for predefined feature types.
 */
APPKIT_EXTERN NSString * NSFontFeatureTypeIdentifierKey NS_AVAILABLE_MAC(10_5);

/* A number object specifying font feature selector such as common ligature off, traditional character shape, etc. Refer to ATS/SFNTLayoutTypes.h for predefined feature selectors.
 */
APPKIT_EXTERN NSString * NSFontFeatureSelectorIdentifierKey NS_AVAILABLE_MAC(10_5);

/* Font weight trait */
/* Predefined symbolic weight values used for NSFontWeightTrait and +[NSFont systemFontOfSize:weight:].
 */
APPKIT_EXTERN const CGFloat NSFontWeightUltraLight NS_AVAILABLE_MAC(10_11);
APPKIT_EXTERN const CGFloat NSFontWeightThin NS_AVAILABLE_MAC(10_11);
APPKIT_EXTERN const CGFloat NSFontWeightLight NS_AVAILABLE_MAC(10_11);
APPKIT_EXTERN const CGFloat NSFontWeightRegular NS_AVAILABLE_MAC(10_11);
APPKIT_EXTERN const CGFloat NSFontWeightMedium NS_AVAILABLE_MAC(10_11);
APPKIT_EXTERN const CGFloat NSFontWeightSemibold NS_AVAILABLE_MAC(10_11);
APPKIT_EXTERN const CGFloat NSFontWeightBold NS_AVAILABLE_MAC(10_11);
APPKIT_EXTERN const CGFloat NSFontWeightHeavy NS_AVAILABLE_MAC(10_11);
APPKIT_EXTERN const CGFloat NSFontWeightBlack NS_AVAILABLE_MAC(10_11);

NS_ASSUME_NONNULL_END
