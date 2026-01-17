/*
	NSFontDescriptor.h
	Application Kit
	Copyright (c) 2003-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/AppKitDefines.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* Symbolic Font Traits */
/*!
    @enum NSFontSymbolicTraits
    @abstract Symbolic representation of stylistic font attributes.
    @discussion NSFontSymbolicTraits symbolically describes stylistic aspects of a font. The upper 16 bits is used to describe appearance of the font whereas the lower 16 bits for typeface. The font appearance information represented by the upper 16 bits can be used for stylistic font matching. The symbolic traits supersedes the existing NSFontTraitMask type used by NSFontManager. The corresponding values are kept compatible between NSFontTraitMask and NSFontSymbolicTraits.
*/
typedef uint32_t NSFontSymbolicTraits;

/* Font appearance info (upper 16 bits of NSFontSymbolicTraits */
/*!
    @enum NSFontFamilyClass
    @abstract Stylistic class values.
    @discussion NSFontFamilyClass classifies certain stylistic qualities of the font. These values correspond closely to the font class values in the OpenType 'OS/2' table. The class values are bundled in the upper four bits of the NSFontSymbolicTraits and can be accessed via NSFontFamilyClassMask. For specific meaning of each identifier, refer to the OpenType specification.
 */
typedef enum {
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
} NSFontFamilyClass;	

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
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

@class NSMutableDictionary, NSDictionary, NSArray, NSSet, NSAffineTransform;

@interface NSFontDescriptor: NSObject <NSCopying, NSCoding> {
/* All instance variables are private */
    NSMutableDictionary *_attributes;
    id _reserved1;
    id _reserved2;
    id _reserved3;
    id _reserved4;
    id _reserved5;
}

/* Core attribute access */
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSString *)postscriptName;
- (float)pointSize;
- (NSAffineTransform *)matrix;
- (NSFontSymbolicTraits)symbolicTraits;

- (id)objectForKey:(NSString *)anAttribute;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

- (NSDictionary *)fontAttributes;

/* Instantiation */
+ (NSFontDescriptor *)fontDescriptorWithFontAttributes:(NSDictionary *)attributes;
+ (NSFontDescriptor *)fontDescriptorWithName:(NSString *)fontName size:(float)size;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
+ (NSFontDescriptor *)fontDescriptorWithName:(NSString *)fontName matrix:(NSAffineTransform *)matrix;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

- (id)initWithFontAttributes:(NSDictionary *)attributes;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* Instance conversion */
/* Returns "normalized" font descriptors matching the receiver. mandatoryKeys is an NSSet instance containing keys that are required to be identical in order to be matched. mandatoryKeys can be nil.
*/
- (NSArray *)matchingFontDescriptorsWithMandatoryKeys:(NSSet *)mandatoryKeys;

- (NSFontDescriptor *)fontDescriptorByAddingAttributes:(NSDictionary *)attributes; // the new attributes take precedence over the existing ones in the receiver
- (NSFontDescriptor *)fontDescriptorWithSymbolicTraits:(NSFontSymbolicTraits)symbolicTraits;
- (NSFontDescriptor *)fontDescriptorWithSize:(float)newPointSize;
- (NSFontDescriptor *)fontDescriptorWithMatrix:(NSAffineTransform *)matrix;
- (NSFontDescriptor *)fontDescriptorWithFace:(NSString *)newFace;
- (NSFontDescriptor *)fontDescriptorWithFamily:(NSString *)newFamily;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */
@end
#endif

/* Predefined font attributes not defined in NSAttributedString.h */

APPKIT_EXTERN NSString *NSFontFamilyAttribute			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSFontNameAttribute			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSFontFaceAttribute			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSFontSizeAttribute			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER; 
APPKIT_EXTERN NSString *NSFontVisibleNameAttribute 		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER; 

APPKIT_EXTERN NSString *NSFontMatrixAttribute                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // An NSAffineTransform instance. (default: identity matrix)
APPKIT_EXTERN NSString *NSFontVariationAttribute                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // An NSDictionary instance describing variation axis (default: supplied by font)
APPKIT_EXTERN NSString *NSFontCharacterSetAttribute             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // An NSCharacterSet instance representing a set of Unicode characters covered by the font. (default: supplied by font)
APPKIT_EXTERN NSString *NSFontCascadeListAttribute              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // An NSArray instance. Each member of the array is a sub-descriptor. (default: the system default cascading list for user's locale)
APPKIT_EXTERN NSString *NSFontTraitsAttribute                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // An NSDictionary instance fully describing font traits. (default: supplied by font)
APPKIT_EXTERN NSString *NSFontFixedAdvanceAttribute             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // A float represented as an NSNumber. The value overrides glyph advancement specified by the font. (default: 0.0)

APPKIT_EXTERN NSString *NSFontColorAttribute 			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4; // This attribute is obsolete. Use NSForegroundColorAttributeName instead.

/* Font traits keys */
/* This key is used with a trait dictionary to get the symbolic traits value as an NSNumber.
*/
APPKIT_EXTERN NSString *NSFontSymbolicTrait AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* This key is used with a trait dictionary to get the normalized weight value as an NSNumber. The valid value range is from -1.0 to 1.0. The value of 0.0 corresponds to the regular or medium font weight.
*/
APPKIT_EXTERN NSString *NSFontWeightTrait AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* This key is used with a trait dictionary to get the relative inter-glyph spacing value as an NSNumber. The valid value range is from -1.0 to 1.0. The value of 0.0 corresponds to the regular glyph spacing.
*/
APPKIT_EXTERN NSString *NSFontWidthTrait AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* This key is used with a trait dictionary to get the relative slant angle value as an NSNumber. The valid value range is from -1.0 to 1.0. The value or 0.0 corresponds to 0 degree clockwise rotation from the vertical and 1.0 corresponds to 30 degrees clockwise rotation.
*/
APPKIT_EXTERN NSString *NSFontSlantTrait AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Font variation keys */
/* This key is used with a variation axis dictionary to get the axis identifier value as an NSNumber.
*/
APPKIT_EXTERN NSString *NSFontVariationAxisIdentifierKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* This key is used with a variation axis dictionary to get the  minimum axis value as an NSNumber.
*/
APPKIT_EXTERN NSString *NSFontVariationAxisMinimumValueKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* This key is used with a variation axis dictionary to get the maximum axis value as an NSNumber.
*/
APPKIT_EXTERN NSString *NSFontVariationAxisMaximumValueKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* This key is used with a variation axis dictionary to get the default axis value as an NSNumber.
*/
APPKIT_EXTERN NSString *NSFontVariationAxisDefaultValueKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* This key is used with a variation axis dictionary to get the localized variation axis name.
*/
APPKIT_EXTERN NSString *NSFontVariationAxisNameKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
