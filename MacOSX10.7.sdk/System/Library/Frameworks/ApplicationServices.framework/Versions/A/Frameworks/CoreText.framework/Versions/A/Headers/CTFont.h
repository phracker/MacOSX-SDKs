/*
 *  CTFont.h
 *  CoreText
 *
 *  Copyright (c) 2006-2011 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTFONT__
#define __CTFONT__

#include <CoreText/CTDefines.h>
#include <CoreText/CTFontDescriptor.h>

#if !TARGET_OS_IPHONE
#include <ATS/ATSTypes.h>
#endif // !TARGET_OS_IPHONE
#include <CoreGraphics/CGFont.h>
#include <CoreGraphics/CGPath.h>
#include <CoreGraphics/CGContext.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*! --------------------------------------------------------------------------
    @group Font Types
*///--------------------------------------------------------------------------

/*!
    @typedef    CTFontRef
    @abstract   The Core Text Font reference.
    @discussion This is a opaque reference to a core font object.
*/
typedef const struct __CTFont * CTFontRef;

/*!
    @function   CTFontGetTypeID
    @abstract   Returns the type identifier for Core Text font references.
    @result     The identifier for the opaque type CTFontRef.
*/
CFTypeID CTFontGetTypeID( void ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*! --------------------------------------------------------------------------
    @group Font Constants
*///--------------------------------------------------------------------------

// Name specifier constants
/*!
    @defined    kCTFontCopyrightNameKey
    @abstract   The name specifier for the copyright name.
*/
extern const CFStringRef kCTFontCopyrightNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontFamilyNameKey
    @abstract   The name specifier for the family name.
*/
extern const CFStringRef kCTFontFamilyNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontSubFamilyNameKey
    @abstract   The name specifier for the subfamily name.
*/
extern const CFStringRef kCTFontSubFamilyNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontStyleNameKey
    @abstract   The name specifier for the style name.
*/
extern const CFStringRef kCTFontStyleNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontUniqueNameKey
    @abstract   The name specifier for the unique name.
    @discussion Note that this name is often not unique and should not be
                assumed to be truly unique.
*/
extern const CFStringRef kCTFontUniqueNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontFullNameKey
    @abstract   The name specifier for the full name.
*/
extern const CFStringRef kCTFontFullNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontVersionNameKey
    @abstract   The name specifier for the version name.
*/
extern const CFStringRef kCTFontVersionNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontPostScriptNameKey
    @abstract   The name specifier for the Postscript name.
*/
extern const CFStringRef kCTFontPostScriptNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontTrademarkNameKey
    @abstract   The name specifier for the trademark name.
*/
extern const CFStringRef kCTFontTrademarkNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontManufacturerNameKey
    @abstract   The name specifier for the manufacturer name.
*/
extern const CFStringRef kCTFontManufacturerNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontDesignerNameKey
    @abstract   The name specifier for the designer name.
*/
extern const CFStringRef kCTFontDesignerNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontDescriptionNameKey
    @abstract   The name specifier for the description name.
*/
extern const CFStringRef kCTFontDescriptionNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontVendorURLNameKey
    @abstract   The name specifier for the vendor url name.
*/
extern const CFStringRef kCTFontVendorURLNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontDesignerURLNameKey
    @abstract   The name specifier for the designer url name.
*/
extern const CFStringRef kCTFontDesignerURLNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontLicenseNameKey
    @abstract   The name specifier for the license name.
*/
extern const CFStringRef kCTFontLicenseNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontLicenseURLNameKey
    @abstract   The name specifier for the license url name.
*/
extern const CFStringRef kCTFontLicenseURLNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontSampleTextNameKey
    @abstract   The name specifier for the sample text name string.
*/
extern const CFStringRef kCTFontSampleTextNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontPostScriptCIDNameKey
    @abstract   The name specifier for the Postscript CID name.
*/
extern const CFStringRef kCTFontPostScriptCIDNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*! --------------------------------------------------------------------------
    @group Font Creation
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCreateWithName
    @abstract   Returns a new font reference for the given name.

    @param      name
                The font name for which you wish to create a new font reference. A valid PostScript name is preferred, although other font name types will be matched in a fallback manner.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default font size of 12.0 will be used.

    @param      matrix
                The transformation matrix for the font. If unspecified, the identity matrix will be used. Optional.

    @result     This function will return a CTFontRef that best matches the name provided with size and matrix attributes. The name parameter is the only required parameters, and default values will be used for unspecified parameters. A best match will be found if all parameters cannot be matched identically.
*/
CTFontRef CTFontCreateWithName(
    CFStringRef                 name,
    CGFloat                     size,
    const CGAffineTransform     *matrix ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCreateWithFontDescriptor
    @abstract   Returns a new font reference that best matches the font descriptor.

    @param      descriptor
                A font descriptor containing attributes that specify the requested font.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default font size of 12.0 will be used.

    @param      matrix
                The transformation matrix for the font. If unspecified, the identity matrix will be used. Optional.

    @result     This function will return a CTFontRef that best matches the attributes provided with the font descriptor. The size and matrix parameters will override any specified in the font descriptor, unless they are unspecified. A best match font will always be returned, and default values will be used for any unspecified.
*/
CTFontRef CTFontCreateWithFontDescriptor(
    CTFontDescriptorRef     descriptor,
    CGFloat                 size,
    const CGAffineTransform *matrix ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @enum       CTFontOptions
    @abstract   Options for descriptor match and font creation.
    @constant   kCTFontOptionsPreventAutoActivation
                Prevents automatic font activation from taking place.
    @constant   kCTFontOptionsPreferSystemFont
                Font matching will prefer to match Apple system fonts.
*/
enum {
    kCTFontOptionsDefault               = 0,
    kCTFontOptionsPreventAutoActivation = 1 << 0,
    kCTFontOptionsPreferSystemFont      = 1 << 2
};
typedef CFOptionFlags CTFontOptions;


/*!
    @function   CTFontCreateWithNameAndOptions
    @abstract   Returns a new font reference for the given name.

    @param      name
                The font name for which you wish to create a new font reference. A valid PostScript name is preferred, although other font name types will be matched in a fallback manner.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default font size of 12.0 will be used.

    @param      matrix
                The transformation matrix for the font. If unspecified, the identity matrix will be used. Optional.
                
    @param      options
                Options flags.

    @result     This function will return a CTFontRef that best matches the name provided with size and matrix attributes. The name parameter is the only required parameters, and default values will be used for unspecified parameters. A best match will be found if all parameters cannot be matched identically.
*/
CTFontRef CTFontCreateWithNameAndOptions(
    CFStringRef                 name,
    CGFloat                     size,
    const CGAffineTransform     *matrix,
    CTFontOptions               options ) CT_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_3_2);

/*!
    @function   CTFontCreateWithFontDescriptorAndOptions
    @abstract   Returns a new font reference that best matches the font descriptor.

    @param      descriptor
                A font descriptor containing attributes that specify the requested font.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default font size of 12.0 will be used.

    @param      matrix
                The transformation matrix for the font. If unspecified, the identity matrix will be used. Optional.

    @param      options
                Options flags.

    @result     This function will return a CTFontRef that best matches the attributes provided with the font descriptor. The size and matrix parameters will override any specified in the font descriptor, unless they are unspecified. A best match font will always be returned, and default values will be used for any unspecified.
*/
CTFontRef CTFontCreateWithFontDescriptorAndOptions(
    CTFontDescriptorRef     descriptor,
    CGFloat                 size,
    const CGAffineTransform *matrix,
    CTFontOptions           options ) CT_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_3_2);

/*!
    @enum       UI Type constants
    @abstract   These constants represent the specific user interface purpose to specify for font creation.
    @discussion Use these constants with CTFontCreateUIFontForLanguage to indicate the intended user interface usage of the font reference to be created.
*/
enum {
    kCTFontNoFontType                           = (uint32_t)-1,
    kCTFontUserFontType                         =  0,
    kCTFontUserFixedPitchFontType               =  1,
    kCTFontSystemFontType                       =  2,
    kCTFontEmphasizedSystemFontType             =  3,
    kCTFontSmallSystemFontType                  =  4,
    kCTFontSmallEmphasizedSystemFontType        =  5,
    kCTFontMiniSystemFontType                   =  6,
    kCTFontMiniEmphasizedSystemFontType         =  7,
    kCTFontViewsFontType                        =  8,
    kCTFontApplicationFontType                  =  9,
    kCTFontLabelFontType                        = 10,
    kCTFontMenuTitleFontType                    = 11,
    kCTFontMenuItemFontType                     = 12,
    kCTFontMenuItemMarkFontType                 = 13,
    kCTFontMenuItemCmdKeyFontType               = 14,
    kCTFontWindowTitleFontType                  = 15,
    kCTFontPushButtonFontType                   = 16,
    kCTFontUtilityWindowTitleFontType           = 17,
    kCTFontAlertHeaderFontType                  = 18,
    kCTFontSystemDetailFontType                 = 19,
    kCTFontEmphasizedSystemDetailFontType       = 20,
    kCTFontToolbarFontType                      = 21,
    kCTFontSmallToolbarFontType                 = 22,
    kCTFontMessageFontType                      = 23,
    kCTFontPaletteFontType                      = 24,
    kCTFontToolTipFontType                      = 25,
    kCTFontControlContentFontType               = 26
};
typedef uint32_t CTFontUIFontType;

/*!
    @function   CTFontCreateUIFontForLanguage
    @abstract   Returns the special UI font for the given language and UI type.

    @param      uiType
                A uiType constant specifying the intended UI use for the requested font reference.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default size for the requested uiType is used.

    @param      language
                Language specifier string to select a font for a particular localization. If unspecified, the current system language is used. The format of the language identifier should conform to the BCP 47 standard.

    @result     This function returns the correct font for various UI uses. The only required parameter is the uiType selector, unspecified optional parameters will use default values.
*/
CTFontRef CTFontCreateUIFontForLanguage(
    CTFontUIFontType    uiType,
    CGFloat             size,
    CFStringRef         language ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCreateCopyWithAttributes
    @abstract   Returns a new font with additional attributes based on the original font.

    @discussion This function provides a mechanism to quickly change attributes on a given font reference in response to user actions. For instance, the size can be changed in response to a user manipulating a size slider.

    @param      font
                Original font reference to base new font on.

    @param      size
                The point size for the font reference. If 0.0 is specified, the original font's size will be preserved.

    @param      matrix
                The transformation matrix for the font. If unspecified, the original font matrix will be preserved. Optional.

    @param      attributes
                A font descriptor containing additional attributes that the new font should contain.

    @result     Returns a new font reference converted from the original with the specified attributes.
*/
CTFontRef CTFontCreateCopyWithAttributes(
    CTFontRef                   font,
    CGFloat                     size,
    const CGAffineTransform     *matrix,
    CTFontDescriptorRef         attributes ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCreateCopyWithSymbolicTraits
    @abstract   Returns a new font based on the original font with the specified symbolic traits.

    @param      font
                Original font reference on which to base the new font.

    @param      size
                The point size for the font reference. If 0.0 is specified, the original font's size will be preserved.

    @param      matrix
                The transformation matrix for the font. If unspecified, the original font matrix will be preserved. Optional.

    @param      symTraitValue
                The value of the symbolic traits. This bitfield is used to indicate the desired value for the traits specified by the symTraitMask parameter. Used in conjunction, they can allow for trait removal as well as addition.

    @param      symTraitMask
                The mask bits of the symbolic traits. This bitfield is used to indicate the traits that should be changed.

    @result     Returns a new font reference in the same family with the given symbolic traits, or NULL if none found in the system.
*/
CTFontRef CTFontCreateCopyWithSymbolicTraits(
    CTFontRef                   font,
    CGFloat                     size,
    const CGAffineTransform     *matrix,
    CTFontSymbolicTraits        symTraitValue,
    CTFontSymbolicTraits        symTraitMask ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCreateCopyWithFamily
    @abstract   Returns a new font in the specified family based on the traits of the original font.

    @param      font
                Original font reference to base new font on.

    @param      size
                The point size for the font reference. If 0.0 is specified, the original font's size will be preserved.

    @param      matrix
                The transformation matrix for the font. If unspecified, the original font matrix will be preserved. Optional.

    @param      family
                The name of the desired family.

    @result     Returns a new font reference with the original traits in the given family. NULL if non found in the system.
*/
CTFontRef CTFontCreateCopyWithFamily(
    CTFontRef                   font,
    CGFloat                     size,
    const CGAffineTransform     *matrix,
    CFStringRef                 family ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*! --------------------------------------------------------------------------
    @group Font Cascading
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCreateForString
    @abstract   Returns a new font reference that can best map the given string range based on the current font.

    @param      currentFont
                The current font that contains a valid cascade list.

    @param      string
                A unicode string containing characters that cannot be encoded by the current font.

    @param      range
                A CFRange specifying the range of the string that needs to be mapped.

    @result     This function returns the best substitute font from the cascade list of the current font that can encode the specified string range. If the current font is capable of encoding the string range then it will be retained and returned.
*/
CTFontRef CTFontCreateForString(
    CTFontRef       currentFont,
    CFStringRef     string,
    CFRange         range ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*! --------------------------------------------------------------------------
    @group Font Accessors
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCopyFontDescriptor
    @abstract   Returns the normalized font descriptors for the given font reference.

    @param      font
                The font reference.

    @result     This function returns a normalized font descriptor for a font. The font descriptor contains enough information to recreate this font at a later time.
*/
CTFontDescriptorRef CTFontCopyFontDescriptor(
    CTFontRef       font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCopyAttribute
    @abstract   Returns the value associated with an arbitrary attribute.

    @param      font
                The font reference.

    @param      attribute
                The requested attribute.

    @result     This function returns a retained reference to an arbitrary attribute. If the requested attribute is not present, NULL is returned. Refer to the attribute definitions for documentation as to how each attribute is packaged as a CFType.
*/
CFTypeRef CTFontCopyAttribute(
    CTFontRef       font,
    CFStringRef     attribute ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetSize
    @abstract   Returns the point size of the font reference.

    @param      font
                The font reference.

    @result     This function returns the point size of the given font reference. This is the point size provided when the font was created.
*/
CGFloat CTFontGetSize( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetMatrix
    @abstract   Returns the transformation matrix of the font.

    @param      font
                The font reference.

    @result     This function returns the transformation matrix for this given font reference. This is the matrix that was provided when the font was created.
*/
CGAffineTransform CTFontGetMatrix( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetSymbolicTraits
    @abstract   Returns the symbolic font traits.

    @param      font
                The font reference.

    @result     This function returns the symbolic traits of the font. This is equivalent to the kCTFontSymbolicTrait of traits dictionary. See CTFontTraits.h for a definition of the font traits.
*/
CTFontSymbolicTraits CTFontGetSymbolicTraits( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCopyTraits
    @abstract   Returns the font traits dictionary.

    @param      font
                The font reference.

    @result     This function returns a retained reference to the font traits dictionary. Individual traits can be accessed with the trait key constants. See CTFontTraits.h for a definition of the font traits.
*/
CFDictionaryRef CTFontCopyTraits( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*! --------------------------------------------------------------------------
    @group Font Names
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCopyPostScriptName
    @abstract   Returns the PostScript name.

    @param      font
                The font reference.

    @result     This function returns a retained reference to the PostScript name of the font.
*/
CFStringRef CTFontCopyPostScriptName( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCopyFamilyName
    @abstract   Returns the family name.

    @param      font
                The font reference.

    @result     This function returns a retained reference to the family name of the font.
*/
CFStringRef CTFontCopyFamilyName( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCopyFullName
    @abstract   Returns the display name.

    @param      font
                The font reference.

    @result     This function returns a retained reference to the full name of the font.
*/
CFStringRef CTFontCopyFullName( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCopyDisplayName
    @abstract   Returns the display name.

    @param      font
                The font reference.

    @result     This function returns a retained reference to the localized display name of the font.
*/
CFStringRef CTFontCopyDisplayName( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCopyName
    @abstract   Returns a reference to the requested name.

    @param      font
                The font reference.

    @param      nameKey
                The name specifier. See name specifier constants.

    @result     This function creates the requested name for the font, or NULL if the font does not have an entry for the requested name. The Unicode version of the name will be preferred, otherwise the first available will be used.
*/
CFStringRef CTFontCopyName(
    CTFontRef       font,
    CFStringRef     nameKey ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCopyLocalizedName
    @abstract   Returns a reference to a localized font name.

    @param      font
                The font reference.

    @param      nameKey
                The name specifier. See name specifier constants.

    @param      language
                Pointer to a CFStringRef to receive the language string of the returned name string. The format of the language identifier will conform to the BCP 47 standard.

    @result     This function returns a specific localized name from the font reference. The name is localized based on the user's global language precedence. If the font does not have an entry for the requested name, NULL will be returned. The matched language will be returned in the caller's buffer.
*/
CFStringRef CTFontCopyLocalizedName(
    CTFontRef       font,
    CFStringRef     nameKey,
    CFStringRef     *language ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*! --------------------------------------------------------------------------
    @group Font Encoding
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCopyCharacterSet
    @abstract   Returns the Unicode character set of the font.

    @param      font
                The font reference.

    @result     This function returns a retained reference to the font's character set. This character set covers the nominal referenced by the font's Unicode cmap table (or equivalent).
*/
CFCharacterSetRef CTFontCopyCharacterSet( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetStringEncoding
    @abstract   Returns the best string encoding for legacy format support.

    @param      font
                The font reference.

    @result     This function returns the best string encoding for the font.
*/
CFStringEncoding CTFontGetStringEncoding( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCopySupportedLanguages
    @abstract   Returns an array of languages supported by the font.

    @param      font
                The font reference.

    @result     This function returns a retained reference to an array of languages supported by the font. The array contains language identifier strings as CFStringRefs. The format of the language identifier will conform to the BCP 47 standard.
*/
CFArrayRef CTFontCopySupportedLanguages( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetGlyphsForCharacters
    @abstract   Performs basic character-to-glyph mapping.

    @discussion This function only provides the nominal mapping as specified by the font's Unicode cmap (or equivalent); such mapping does not constitute proper Unicode layout: it is the caller's responsibility to handle the Unicode properties of the characters.

    @param      font
                The font reference.

    @param      characters
                An array of characters (UTF-16 code units). Non-BMP characters must be encoded as surrogate pairs.

    @param      glyphs
                A pointer to a buffer to receive the glyphs. Glyphs for non-BMP characters are sparse: the first glyph corresponds to the full character and the second glyph will be 0.

    @param      count
                The capacity of both the characters and glyphs arrays.

    @result     The return value indicates whether all provided characters were successfully mapped. A return value of true indicates that the font mapped all characters. A return value of false indicates that some or all of the characters were not mapped; glyphs for unmapped characters will be 0 (with the exception of those corresponding non-BMP characters as described above).

    @seealso    CTFontCopyCharacterSet
*/
bool CTFontGetGlyphsForCharacters(
    CTFontRef       font,
    const UniChar   characters[],
    CGGlyph         glyphs[],
    CFIndex         count ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*! --------------------------------------------------------------------------
    @group Font Metrics
*///--------------------------------------------------------------------------

/*!
    @function   CTFontGetAscent
    @abstract   Returns the scaled font ascent metric.

    @param      font
                The font reference.

    @result     This function returns the font ascent metric scaled based on the point size and matrix of the font reference.
*/
CGFloat CTFontGetAscent( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetDescent
    @abstract   Returns the scaled font descent metric.

    @param      font
                The font reference.

    @result     This function returns the font descent metric scaled based on the point size and matrix of the font reference.
*/
CGFloat CTFontGetDescent( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetLeading
    @abstract   Returns the scaled font leading metric.

    @param      font
                The font reference.

    @result     This function returns the font leading metric scaled based on the point size and matrix of the font reference.
*/
CGFloat CTFontGetLeading( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetUnitsPerEm
    @abstract   Returns the units per em metric.

    @param      font
                The font reference.

    @result     This function returns the units per em of the font.
*/
unsigned CTFontGetUnitsPerEm( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetGlyphCount
    @abstract   Returns the number of glyphs.

    @param      font
                The font reference.

    @result     This function returns the number of glyphs in the font.
*/
CFIndex CTFontGetGlyphCount( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetBoundingBox
    @abstract   Returns the scaled bounding box.

    @param      font
                The font reference.

    @result     This will return the design bounding box of the font, which is the rectangle defined by xMin, yMin, xMax, and yMax values for the font.
*/
CGRect CTFontGetBoundingBox( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetUnderlinePosition
    @abstract   Returns the scaled underline position.

    @param      font
                The font reference.

    @result     This function returns the font underline position metric scaled based on the point size and matrix of the font reference.
*/
CGFloat CTFontGetUnderlinePosition( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetUnderlineThickness
    @abstract   Returns the scaled underline thickness metric.

    @param      font
                The font reference.

    @result     This function returns the font underline thickness metric scaled based on the point size and matrix of the font reference.
*/
CGFloat CTFontGetUnderlineThickness( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetSlantAngle
    @abstract   Returns the slant angle of the font.

    @param      font
                The font reference.

    @result     This function returns the transformed slant angle of the font. This is equivalent to the italic or caret angle with any skew from the transformation matrix applied.
*/
CGFloat CTFontGetSlantAngle( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetCapHeight
    @abstract   Returns the cap height metric.

    @param      font
                The font reference.

    @result     This function returns the font cap height metric scaled based on the point size and matrix of the font reference.
*/
CGFloat CTFontGetCapHeight( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetXHeight
    @abstract   Returns the X height metric.

    @param      font
                The font reference.

    @result     This function returns the font X height metric scaled based on the point size and matrix of the font reference.
*/
CGFloat CTFontGetXHeight( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*! --------------------------------------------------------------------------
    @group Font Glyphs
*///--------------------------------------------------------------------------

/*!
    @function   CTFontGetGlyphWithName
    @abstract   Returns the CGGlyph for the specified glyph name.

    @param      font
                The font reference.

    @param      glyphName
                The glyph name as a CFString.

    @result     The glyph with the specified name or 0 if the name is not recognized; this glyph can be used with other Core Text glyph data accessors or with Quartz.
*/
CGGlyph CTFontGetGlyphWithName(
    CTFontRef           font,
    CFStringRef         glyphName ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);


/*!
    @function   CTFontGetBoundingRectsForGlyphs
    @abstract   Calculates the bounding rects for an array of glyphs and returns the overall bounding rect for the run.

    @param      font
                The font reference.

    @param      orientation
                The intended drawing orientation of the glyphs. Used to determined which glyph metrics to return.

    @param      glyphs
                An array of count number of glyphs.

    @param      boundingRect
                An array of count number of CGRects to receive the computed glyph rects. Can be NULL, in which case only the overall bounding rect is calculated.

    @param      count
                The capacity of the glyphs and boundingRects buffers.

    @result     This function returns the overall bounding rectangle for an array or run of glyphs. The bounding rects of the individual glyphs are returned through the boundingRects parameter. These are the design metrics from the font transformed in font space.
*/
CGRect CTFontGetBoundingRectsForGlyphs(
    CTFontRef           font,
    CTFontOrientation   orientation,
    const CGGlyph       glyphs[],
    CGRect              boundingRects[],
    CFIndex             count ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetAdvancesForGlyphs
    @abstract   Calculates the advances for an array of glyphs and returns the summed advance.

    @param      font
                The font reference.

    @param      orientation
                The intended drawing orientation of the glyphs. Used to determined which glyph metrics to return.

    @param      glyphs
                An array of count number of glyphs.

    @param      advances
                An array of count number of CGSize to receive the computed glyph advances. Can be NULL, in which case only the overall advance is calculated.

    @param      count
                The capacity of the glyphs and advances buffers.

    @result     This function returns the summed glyph advance of an array of glyphs. Individual glyph advances are passed back via the advances parameter. These are the ideal metrics for each glyph scaled and transformed in font space.
*/
double CTFontGetAdvancesForGlyphs(
    CTFontRef           font,
    CTFontOrientation   orientation,
    const CGGlyph       glyphs[],
    CGSize              advances[],
    CFIndex             count ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontGetVerticalTranslationsForGlyphs
    @abstract   Calculates the offset from the default (horizontal) origin to the vertical origin for an array of glyphs.

    @param      font
                The font reference.

    @param      glyphs
                An array of count number of glyphs.

    @param      translations
                An array of count number of CGSize to receive the computed origin offsets.

    @param      count
                The capacity of the glyphs and translations buffers.
*/
void CTFontGetVerticalTranslationsForGlyphs(
    CTFontRef       font,
    const CGGlyph   glyphs[],
    CGSize          translations[],
    CFIndex         count ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCreatePathForGlyph
    @abstract   Creates a path for the specified glyph.

    @discussion Creates a path from the outlines of the glyph for the specified font. The path will reflect the font point size, matrix, and transform parameter, in that order. The transform parameter will most commonly be used to provide a translation to the desired glyph origin.

    @param      font
                The font reference.

    @param      glyph
                The glyph.

    @param      transform
                An affine transform applied to the path. Can be NULL, in which case CGAffineTransformIdentity will be used.

    @result     A retained CGPath reference containing the glyph outlines or NULL if an error occurred.
*/
CGPathRef CTFontCreatePathForGlyph(
    CTFontRef                   font,
    CGGlyph                     glyph,
    const CGAffineTransform *   transform ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*! --------------------------------------------------------------------------
    @group Font Variations        (this functionality is not supported on iOS)
*///--------------------------------------------------------------------------

/*!
    @defined    kCTFontVariationAxisIdentifierKey
    @abstract   Key to get the variation axis identifier.
    @discussion This key is used with a variation axis dictionary to get the axis identifier value as a CFNumberRef.
*/
extern const CFStringRef kCTFontVariationAxisIdentifierKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontVariationAxisMinimumValueKey
    @abstract   Key to get the variation axis minimum value.
    @discussion This key is used with a variation axis dictionary to get the minimum axis value as a CFNumberRef.
*/
extern const CFStringRef kCTFontVariationAxisMinimumValueKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontVariationAxisMaximumValueKey
    @abstract   Key to get the variation axis maximum value.
    @discussion This key is used with a variation axis dictionary to get the maximum axis value as a CFNumberRef.
*/
extern const CFStringRef kCTFontVariationAxisMaximumValueKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontVariationAxisDefaultValueKey
    @abstract   Key to get the variation axis default value.
    @discussion This key is used with a variation axis dictionary to get the default axis value as a CFNumberRef.
*/
extern const CFStringRef kCTFontVariationAxisDefaultValueKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontVariationAxisNameKey
    @abstract   Key to get the variation axis name string.
    @discussion This key is used with a variation axis dictionary to get the localized variation axis name.
*/
extern const CFStringRef kCTFontVariationAxisNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCopyVariationAxes
    @abstract   Returns an array of variation axes.

    @param      font
                The font reference.

    @result     This function returns an array of variation axis dictionaries. Each variation axis dictionary contains the five variation axis keys above.
*/
CFArrayRef CTFontCopyVariationAxes( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCopyVariation
    @abstract   Returns a variation dictionary from the font reference.

    @param      font
                The font reference.

    @result     This function returns the current variation instance as a dictionary. The keys for each variation correspond to the variation identifier obtained via kCTVariationAxisIdentifierKey which represents the axis' four character code as a CFNumber.
*/
CFDictionaryRef CTFontCopyVariation( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*! --------------------------------------------------------------------------
    @group Font Features              (only AAT features are supported on iOS)
*///--------------------------------------------------------------------------

/*!
    @defined    kCTFontFeatureTypeIdentifierKey
    @abstract   Key to get the font feature type value.
    @discussion This key can be used with a font feature dictionary to get the type identifier as a CFNumberRef.
*/
extern const CFStringRef kCTFontFeatureTypeIdentifierKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontFeatureTypeNameKey
    @abstract   Key to get the font feature name.
    @discussion This key can be used with a font feature dictionary to get the localized type name string as a CFString.
*/
extern const CFStringRef kCTFontFeatureTypeNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontFeatureTypeExclusiveKey
    @abstract   Key to get the font feature exclusive setting.
    @discussion This key can be used with a font feature dictionary to get the the exclusive setting of the feature as a CFBoolean. The value associated with this key indicates whether the feature selectors associated with this type should be mutually exclusive.
*/
extern const CFStringRef kCTFontFeatureTypeExclusiveKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontFeatureTypeSelectorsKey
    @abstract   Key to get the font feature selectors.
    @discussion This key can be used with a font feature dictionary to get the array of font feature selectors as a CFArrayRef. This is an array of selector dictionaries that contain the values for the following selector keys.
*/
extern const CFStringRef kCTFontFeatureTypeSelectorsKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontFeatureSelectorIdentifierKey
    @abstract   Key to get the font feature selector identifier.
    @discussion This key can be used with a selector dictionary corresponding to a feature type to obtain the selector identifier value as a CFNumberRef.
*/
extern const CFStringRef kCTFontFeatureSelectorIdentifierKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontFeatureSelectorNameKey
    @abstract   Key to get the font feature selector name.
    @discussion This key is used with a selector dictionary to get the localized name string for the selector as a CFStringRef.
*/
extern const CFStringRef kCTFontFeatureSelectorNameKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontFeatureSelectorDefaultKey
    @abstract   Key to get the font feature selector default setting value.
    @discussion This key is used with a selector dictionary to get the default indicator for the selector. This value is a CFBooleanRef which if present and true indicates that this selector is the default setting for the current feature type.
*/
extern const CFStringRef kCTFontFeatureSelectorDefaultKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);
/*!
    @defined    kCTFontFeatureSelectorSettingKey
    @abstract   Key to get or specify the current feature setting.
    @discussion This key is used with a selector dictionary to get or specify the current setting for the selector. This value is a CFBooleanRef to indicate whether this selector is on or off. If this key is not present, the default setting is used.
*/
extern const CFStringRef kCTFontFeatureSelectorSettingKey CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCopyFeatures
    @abstract   Returns an array of font features

    @param      font
                The font reference.

    @result     This function returns an array of font feature dictionaries for the font reference.
*/
CFArrayRef CTFontCopyFeatures( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCopyFeatureSettings
    @abstract   Returns an array of font feature setting tuples

    @discussion A setting tuple is a dictionary of a kCTFontFeatureTypeIdentifierKey key-value pair and a kCTFontFeatureSelectorIdentifierKey key-value pair. Each tuple corresponds to an enabled non-default setting. It is the caller's responsibility to handle exclusive and non-exclusive settings as necessary.

    @param      font
                The font reference.

    @result     This function returns a normalized array of font feature setting dictionaries. The array will only contain the non-default settings that should be applied to the font, or NULL if the default settings should be used.
*/
CFArrayRef CTFontCopyFeatureSettings( CTFontRef font ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*! --------------------------------------------------------------------------
    @group Font Conversion
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCopyGraphicsFont
    @abstract   Returns a CGFontRef and attributes.

    @param      font
                The font reference.

    @param      attributes
                A pointer to a CTFontDescriptorRef to receive a font descriptor containing additional attributes. Can be NULL. Must be released by caller.

    @result     This function returns a CGFontRef for the given font reference. Additional attributes from the font will be passed back as a font descriptor via the attributes parameter. The result must be released by the caller.
*/
CGFontRef CTFontCopyGraphicsFont(
    CTFontRef           font,
    CTFontDescriptorRef *attributes ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCreateWithGraphicsFont
    @abstract   Creates a new font reference from a CGFontRef.

    @param      graphicsFont
                A valid CGFontRef.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default font size of 12.0 will be used.

    @param      matrix
                The transformation matrix for the font. If unspecified, the identity matrix will be used. Optional.

    @param      attributes
                A CTFontDescriptorRef containing additional attributes that should be matched. Optional.

    @result     This function returns a new font reference for an existing CGFontRef with the specified size, matrix, and additional attributes.
*/
CTFontRef CTFontCreateWithGraphicsFont(
    CGFontRef                   graphicsFont,
    CGFloat                     size,
    const CGAffineTransform     *matrix,
    CTFontDescriptorRef         attributes ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

#if !TARGET_OS_IPHONE
/*!
    @function   CTFontGetPlatformFont
    @abstract   Returns the ATSFontRef and attributes.

    @param      font
                The font reference.

    @param      attributes
                A pointer to a CTFontDescriptorRef to receive a font descriptor containing additional attributes. Can be NULL. Must be released by caller.

    @result     This function returns a an ATSFontRef for the given font reference. Additional attributes from the font will be passed back as a font descriptor via the attributes parameter.
*/

ATSFontRef CTFontGetPlatformFont(
    CTFontRef               font,
    CTFontDescriptorRef     *attributes ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCreateWithPlatformFont
    @abstract   Creates a new font reference from an ATSFontRef.

    @param      platformFont
                A valid ATSFontRef.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default font size of 12.0 will be used.

    @param      matrix
                The transformation matrix for the font. If unspecified, the identity matrix will be used. Optional.

    @param      attributes
                A CTFontDescriptorRef containing additional attributes that should be matched. Optional.

    @result     This function returns a new font reference for an ATSFontRef with the specified size, matrix, and additional attributes.
*/
CTFontRef CTFontCreateWithPlatformFont(
    ATSFontRef                  platformFont,
    CGFloat                     size,
    const CGAffineTransform     *matrix,
    CTFontDescriptorRef         attributes ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCreateWithQuickdrawInstance
    @abstract   Returns a font reference for the given Quickdraw instance.

    @discussion This function is provided for compatibility support between Core Text and clients needing to support Quickdraw font references.

    @param      name
                The Quickdraw font name. If NULL or zero length, an identifier must be specified instead.

    @param      identifier
                The Quickdraw font identifier. If 0, a name must be specified instead.

    @param      style
                The Quickdraw font style.

    @param      size
                The point size for the font reference. If 0.0 is specified, the default size of 12.0 is used.

    @result     This function returns the best font instance matching the Quickdraw instance information.
*/
CTFontRef CTFontCreateWithQuickdrawInstance(
    ConstStr255Param    name,
    int16_t             identifier,
    uint8_t             style,
    CGFloat             size ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

#endif // !TARGET_OS_IPHONE
/*! --------------------------------------------------------------------------
    @group Font Tables
*///--------------------------------------------------------------------------

enum {
    kCTFontTableBASE    = 'BASE',   // Baseline
    kCTFontTableCFF     = 'CFF ',   // PostScript font program
    kCTFontTableDSIG    = 'DSIG',   // Digital signature
    kCTFontTableEBDT    = 'EBDT',   // Embedded bitmap
    kCTFontTableEBLC    = 'EBLC',   // Embedded bitmap location
    kCTFontTableEBSC    = 'EBSC',   // Embedded bitmap scaling
    kCTFontTableGDEF    = 'GDEF',   // Glyph definition
    kCTFontTableGPOS    = 'GPOS',   // Glyph positioning
    kCTFontTableGSUB    = 'GSUB',   // Glyph substitution
    kCTFontTableJSTF    = 'JSTF',   // Justification
    kCTFontTableLTSH    = 'LTSH',   // Linear threshold
    kCTFontTableOS2     = 'OS/2',   // OS/2 and Windows specific metrics
    kCTFontTablePCLT    = 'PCLT',   // PCL 5 data
    kCTFontTableVDMX    = 'VDMX',   // Vertical device metrics
    kCTFontTableVORG    = 'VORG',   // Vertical origin
    kCTFontTableZapf    = 'Zapf',   // Glyph reference
    kCTFontTableAcnt    = 'acnt',   // Accent attachment
    kCTFontTableAvar    = 'avar',   // Axis variation
    kCTFontTableBdat    = 'bdat',   // Bitmap data
    kCTFontTableBhed    = 'bhed',   // Bitmap font header
    kCTFontTableBloc    = 'bloc',   // Bitmap location
    kCTFontTableBsln    = 'bsln',   // Baseline
    kCTFontTableCmap    = 'cmap',   // Character to glyph mapping
    kCTFontTableCvar    = 'cvar',   // CVT variation
    kCTFontTableCvt     = 'cvt ',   // Control value table
    kCTFontTableFdsc    = 'fdsc',   // Font descriptor
    kCTFontTableFeat    = 'feat',   // Layout feature
    kCTFontTableFmtx    = 'fmtx',   // Font metrics
    kCTFontTableFpgm    = 'fpgm',   // Font program
    kCTFontTableFvar    = 'fvar',   // Font variation
    kCTFontTableGasp    = 'gasp',   // Grid-fitting/Scan-conversion
    kCTFontTableGlyf    = 'glyf',   // Glyph data
    kCTFontTableGvar    = 'gvar',   // Glyph variation
    kCTFontTableHdmx    = 'hdmx',   // Horizontal device metrics
    kCTFontTableHead    = 'head',   // Font header
    kCTFontTableHhea    = 'hhea',   // Horizontal header
    kCTFontTableHmtx    = 'hmtx',   // Horizontal metrics
    kCTFontTableHsty    = 'hsty',   // Horizontal style
    kCTFontTableJust    = 'just',   // Justification
    kCTFontTableKern    = 'kern',   // Kerning
    kCTFontTableKerx    = 'kerx',   // Extended kerning
    kCTFontTableLcar    = 'lcar',   // Ligature caret
    kCTFontTableLoca    = 'loca',   // Index to location
    kCTFontTableMaxp    = 'maxp',   // Maximum profile
    kCTFontTableMort    = 'mort',   // Morph
    kCTFontTableMorx    = 'morx',   // Extended morph
    kCTFontTableName    = 'name',   // Naming table
    kCTFontTableOpbd    = 'opbd',   // Optical bounds
    kCTFontTablePost    = 'post',   // PostScript information
    kCTFontTablePrep    = 'prep',   // CVT program
    kCTFontTableProp    = 'prop',   // Properties
    kCTFontTableSbit    = 'sbit',   // Bitmap data
    kCTFontTableSbix    = 'sbix',   // Extended bitmap data
    kCTFontTableTrak    = 'trak',   // Tracking
    kCTFontTableVhea    = 'vhea',   // Vertical header
    kCTFontTableVmtx    = 'vmtx'    // Vertical metrics
};
typedef uint32_t CTFontTableTag;

enum {
    kCTFontTableOptionNoOptions = 0,
    kCTFontTableOptionExcludeSynthetic = (1 << 0)
};
typedef uint32_t CTFontTableOptions;

/*!
    @function   CTFontCopyAvailableTables
    @abstract   Returns an array of font table tags.

    @param      font
                The font reference.

    @param      options

    @result     This function returns an array of CTFontTableTag values for the given font and the supplied options. The returned set will contain unboxed values, which may be extracted like so:
                <code>CTFontTableTag tag = (CTFontTableTag)(uintptr_t)CFArrayGetValueAtIndex(tags, index);</code>
*/
CFArrayRef CTFontCopyAvailableTables(
    CTFontRef           font,
    CTFontTableOptions  options ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCopyTable
    @abstract   Returns a reference to the font table data.

    @param      font
                The font reference.

    @param      table
                The font table identifier as a CTFontTableTag.

    @param      options

    @result     This function returns a retained reference to the font table data as CFDataRef. The table data is not actually copied, however the data reference must be released.
*/
CFDataRef CTFontCopyTable(
    CTFontRef           font,
    CTFontTableTag      table,
    CTFontTableOptions  options ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);


/*!
    @function   CTFontDrawGlyphs
    @abstract   Renders the given glyphs from the CTFont at the given positions in the CGContext.
    @discussion This function will modify the CGContext's font, text size, and text matrix if specified in the CTFont. These attributes will not be restored.
        The given glyphs should be the result of proper Unicode text layout operations (such as CTLine). Results from CTFontGetGlyphsForCharacters (or similar APIs) do not perform any Unicode text layout.

    @param      font
                The font to render glyphs from. If the font has a size or matrix attribute, the CGContext will be set with these values.

    @param      glyphs
                The glyphs to be rendered. See above discussion of how the glyphs should be derived.

    @param      positions
                The positions (origins) for each glyph. The positions are in user space. The number of positions passed in must be equivalent to the number of glyphs.

    @param      count
                The number of glyphs to be rendered from the glyphs array.

    @param      context
                CGContext used to render the glyphs.

    @result     void
*/
void CTFontDrawGlyphs(
    CTFontRef       font, 
    const CGGlyph   glyphs[], 
    const CGPoint   positions[], 
    size_t          count, 
    CGContextRef    context ) CT_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_4_2);


/*!
    @function   CTFontGetLigatureCaretPositions
    @abstract   Returns caret positions within a glyph.
    @discussion This function is used to obtain caret positions for a specific glyph.
                The return value is the max number of positions possible, and the function
                will populate the caller's positions buffer with available positions if possible.
                This function may not be able to produce positions if the font does not
                have the appropriate data, in which case it will return 0.
 
    @param      font
                The font reference.
    
    @param      glyph
                The glyph.
 
    @param      positions
                A buffer of at least maxPositions to receive the ligature caret positions for
                the glyph.
 
    @param      maxPositions
                The maximum number of positions to return.
 
    @result     Returns the number of caret positions for the specified glyph.
 */
CFIndex CTFontGetLigatureCaretPositions(
    CTFontRef       font,
    CGGlyph         glyph,
    CGFloat         positions[],
    CFIndex         maxPositions ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

#if defined(__cplusplus)
}
#endif

#endif
