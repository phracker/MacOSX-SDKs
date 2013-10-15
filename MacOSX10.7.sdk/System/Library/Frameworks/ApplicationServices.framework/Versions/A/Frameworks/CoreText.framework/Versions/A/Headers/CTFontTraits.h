/*
 *  CTFontTraits.h
 *  CoreText
 *
 *  Copyright (c) 2006-2011 Apple Inc. All rights reserved.
 *
 */

#ifndef __CTFONTTRAITS__
#define __CTFONTTRAITS__

#include <CoreText/CTDefines.h>
#include <CoreFoundation/CFNumber.h>
#include <CoreFoundation/CFString.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
    @defined    kCTFontSymbolicTrait
    @abstract   Dictionary key to access the symbolic traits value.
    @discussion Use this key to access the symbolic traits value from the font traits dictionary. The value is returned as a CFNumberRef.
*/
extern const CFStringRef kCTFontSymbolicTrait CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontWeightTrait
    @abstract   Dictionary key to access the weight trait value.
    @discussion Use this key to access the normalized weigth trait from the font traits dictionary. The value returned is a CFNumberRef representing a float value between -1.0 and 1.0 for normalized weight. The value of 0.0 corresponds to the regular or medium font weight.
*/
extern const CFStringRef kCTFontWeightTrait CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontWidthTrait
    @abstract   Dictionary key to access the width (condense/expand) trait value.
    @discussion Use this key to access the normalized proportion trait from the font traits dictionary. This value corresponds to the relative inter-glyph spacing for a given font. The value returned is a CFNumberRef representing a float between -1.0 and 1.0. The value of 0.0 corresponds to regular glyph spacing while negative values represent condensed glyph spacing.
*/
extern const CFStringRef kCTFontWidthTrait CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontSlantTrait
    @abstract   Dictionary key to access the slant trait value.
    @discussion Use this key to access the normalized slant angle from the font traits dictionary. The value returned is a CFNumberRef representing a float value between -1.0 and 1.0 for normalized slant angle. The value or 0.0 corresponds to 0 degree clockwise rotation from the vertical and 1.0 corresponds to 30 degrees clockwise rotation.
*/
extern const CFStringRef kCTFontSlantTrait CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @const      kCTFontClassMaskShift
    @abstract   The font class shift.
    @discussion This is used to shift the font class to the upper most 4 bits of the symbolic traits.
*/
enum {
    kCTFontClassMaskShift = 28
};

/*!
    @enum       CTFontSymbolicTraits
    @abstract   Symbolic representation of stylistic font attributes.
    @discussion CTFontSymbolicTraits symbolically describes stylistic aspects of a font. The upper 16 bits is used to describe appearance of the font whereas the lower 16 bits for typeface. The font appearance information represented by the upper 16 bits can be used for stylistic font matching.

    @constant   kCTFontClassMaskShift
                Shift value to reserve the upper most 4 bits for the font class.
*/
enum {
    kCTFontItalicTrait              = (1 << 0),     // Additional detail available via kCTFontSlantTrait
    kCTFontBoldTrait                = (1 << 1),     // Additional detail available via kCTFontWeightTrait
    kCTFontExpandedTrait            = (1 << 5),     // Expanded and condensed traits are mutually exclusive
    kCTFontCondensedTrait           = (1 << 6),     // Additional detail available via kCTFontWidthTrait
    kCTFontMonoSpaceTrait           = (1 << 10),    // Use fixed-pitch glyphs if available. May have multiple glyph advances (most CJK glyphs may contain two spaces)
    kCTFontVerticalTrait            = (1 << 11),    // Use vertical glyph variants and metrics
    kCTFontUIOptimizedTrait         = (1 << 12),    // Synthesize appropriate attributes for UI rendering such as control titles if necessary
    kCTFontColorGlyphsTrait         = (1 << 13),    // Color bitmap glyphs are available. 

    kCTFontClassMaskTrait           = (15 << kCTFontClassMaskShift) // Mask for the font class
};
typedef uint32_t CTFontSymbolicTraits;

/*!
    @enum       CTFontStylisticClass
    @abstract   Stylistic class values.
    @discussion CTFontStylisticClass classifies certain stylistic qualities of the font. These values correspond closely to the font class values in the OpenType 'OS/2' table. The class values are bundled in the upper four bits of the CTFontSymbolicTraits and can be obtained via the kCTFontClassMaskTrait.
*/
enum {
    kCTFontUnknownClass             = (0 << kCTFontClassMaskShift),
    kCTFontOldStyleSerifsClass      = (1 << kCTFontClassMaskShift),
    kCTFontTransitionalSerifsClass  = (2 << kCTFontClassMaskShift),
    kCTFontModernSerifsClass        = (3 << kCTFontClassMaskShift),
    kCTFontClarendonSerifsClass     = (4 << kCTFontClassMaskShift),
    kCTFontSlabSerifsClass          = (5 << kCTFontClassMaskShift),
    kCTFontFreeformSerifsClass      = (7 << kCTFontClassMaskShift),
    kCTFontSansSerifClass           = (8 << kCTFontClassMaskShift),
    kCTFontOrnamentalsClass         = (9 << kCTFontClassMaskShift),
    kCTFontScriptsClass             = (10 << kCTFontClassMaskShift),
    kCTFontSymbolicClass            = (12 << kCTFontClassMaskShift)
};
typedef uint32_t CTFontStylisticClass;

#if defined(__cplusplus)
}
#endif

#endif
