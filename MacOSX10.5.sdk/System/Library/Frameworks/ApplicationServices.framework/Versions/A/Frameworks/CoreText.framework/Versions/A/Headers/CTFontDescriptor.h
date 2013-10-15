/*
 *  CTFontDescriptor.h
 *	CoreText
 *
 *  Copyright (c) 2006-2007 Apple Inc. All rights reserved.
 *
 */
/*!
    @header		CTFontDescriptor
    @abstract   The definition of the public font descriptor API.
*/


#ifndef __CTFONTDESCRIPTOR__
#define __CTFONTDESCRIPTOR__

#include <CoreText/CTFontTraits.h>

#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFCharacterSet.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFSet.h>
#include <CoreGraphics/CGAffineTransform.h>

#if defined(__cplusplus)
extern "C" {
#endif

// ---------------------------------------------------------------------------
// Descriptor Types
// ---------------------------------------------------------------------------

/*!
	@typedef	CTFontDescriptorRef
	@abstract   The Core Text Font Descriptor reference.
	@discussion This is a opaque reference to a font descriptor.
 */
typedef const struct __CTFontDescriptor * CTFontDescriptorRef;

// ---------------------------------------------------------------------------
// Descriptor Attributes
// ---------------------------------------------------------------------------
/*!
    @defined	kCTFontNameAttribute
    @abstract   The PostScript name.
    @discussion This is the key for accessing the PostScript name from the 
				font descriptor. The value associated with this key is a 
				CFStringRef. If unspecified, defaults to "Helvetica", if
				unavailable falls back to global font cascade list.
*/
extern const CFStringRef kCTFontNameAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!
	defined		kCTFontDisplayNameAttribute
	@abstract   The display name.
	@discussion This is the key for accessing the name used to display the font.
				Most commonly this is the full name. The value associated with
				this key is a CFStringRef. If unspecified, defaults to "Helvetica",
				if unavailable falls back to global font cascade list.
 */
extern const CFStringRef kCTFontDisplayNameAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!
	defined		kCTFontFamilyNameAttribute
	@abstract   The family name.
	@discussion This is the key for accessing the family name from the font
				descriptor. The value associated with this key is a CFStringRef.
 */
extern const CFStringRef kCTFontFamilyNameAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!
	defined		kCTFontStyleNameAttribute
	@abstract   The style name.
	@discussion This is the key for accessing the style name of the font. This 
				name represents the designer's description of the font's style. 
				The value associated with this key is a CFStringRef.  If 
				unspecified, defaults to "Helvetica", if unavailable falls back 
				to global font cascade list.
 */
extern const CFStringRef kCTFontStyleNameAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!
	defined		kCTFontTraitsAttribute
	@abstract   The font traits dictionary.
	@discussion This is the key for accessing the dictionary of font traits for
				stylistic information. See CTFontTraits.h for the list of font
				traits. The value associated with this key is a CFDictionaryRef.
 */
extern const CFStringRef kCTFontTraitsAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!
	defined		kCTFontVariationAttribute
	@abstract   The font variation dictionary.
	@discussion This key is used to obtain the font variation instance as a
				CFDictionaryRef. If specified in a font descriptor, fonts
				with the specified axes will be primary match candidates, if no
				such fonts exist, this attribute will be ignored.
 */
extern const CFStringRef kCTFontVariationAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!
	defined		kCTFontSizeAttribute
	@abstract   The font point size.
	@discussion This key is used to obtain or specify the font point size. 
				Creating a font with this unspecified will default to a point
				size of 12.0. The value for this key is represented as a CFNumberRef.
 */
extern const CFStringRef kCTFontSizeAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!
	defined		kCTFontMatrixAttribute
	@abstract   The font transformation matrix.
	@discussion This key is used to specify the font transformation matrix when
				creating a font. If unspecified it defaults to the unit matrix.
				The value for this key is a CFDataRef containing a CGAffineTransform.
 */
extern const CFStringRef kCTFontMatrixAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!
	defined		kCTFontCascadeListAttribute
	@abstract   The font cascade list.
	@discussion This key is used to specify or obtain the cascade list used for
				a font reference. The cascade list is a CFArrayRef containing
				CTFontDescriptorRefs. If unspecified, the global cascade list is
				used.
 */
extern const CFStringRef kCTFontCascadeListAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!
	defined		kCTFontCharacterSetAttribute
	@abstract   The font unicode character coverage set.
	@discussion This key is used to specify or obtain the character set for a
				font reference. This value for this key is a CFCharacterSetRef.
				If specified this can be used to restrict the font to a subset of
				its actual character set. If unspecified this attribute is
				ignored and the actual character set is used.
 */
extern const CFStringRef kCTFontCharacterSetAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!
	@defined	kCTFontLanguagesAttribute
	@abstract   The list of supported languages.
	@discussion This key is used to specify or obtain a list of covered languages
				for a font reference. The value for this key is a CFArrayRef of
				CFStringRefs. If specified this restricts the search to matching
				fonts that support the specified languages. The language identifier
				string should conform to the BCP 47 standard. If unspecified this 
				attribute is ignored. 
 */
extern const CFStringRef kCTFontLanguagesAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!
	defined		kCTFontBaselineAdjustAttribute
	@abstract   The baseline adjustment to apply to font metrics.
	@discussion This key is used to specify or obtain the baseline adjustment for
				a font reference. This is primary used when defining font 
				descriptors for a cascade list to keep the baseline of all 
				fonts even. The value associated with this is a float represented
				as a CFNumberRef.
 */
extern const CFStringRef kCTFontBaselineAdjustAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!		
	@defined	kCTFontMacintoshEncodingsAttribute
	@abstract   The macintosh encodings attribute.
	@discussion This key is used to specify or obtain the macintosh encodings for a
				font reference. The value associated with this key is a CFNumberRef
				containing a bitfield of the Macintosh encodings. This attribute
				is provide for legacy compatibility.
 */
extern const CFStringRef kCTFontMacintoshEncodingsAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!
	@defined	kCTFontFeaturesAttribute
	@abstract   The array of font features.
	@discussion This key is used to specify or obtain the font features for a 
				font reference. The value associated with this key is a CFArrayRef
				of font feature dictionaries. This features list contains the 
				feature information from the 'feat' table of the font. See the 
				CTFontCopyFeatures() API in	CTFont.h.
 */
extern const CFStringRef kCTFontFeaturesAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!
	@defined	kCTFontFeatureSettingsAttribute
	@abstract   The array of font settings.
	@discussion This key is used to specify or obtain the font features settings
				for a font reference. The value associated with this key is a 
				CFArrayRef of font feature setting dictionaries. A setting dictionary
				contains a tuple of a kCTFontFeatureTypeIdentifierKey key-value pair
				and a kCTFontFeatureSelectorIdentifierKey key-value pair. Each setting 
				dictionary indicates which setting should be turned on. In the case
				of duplicate or conflicting setting the last setting in the list
				will take precedence. It is the caller's responsibility to handle 
				exclusive and non-exclusive settings as necessary.
 */
extern const CFStringRef kCTFontFeatureSettingsAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!		
    @defined	kCTFontFixedAdvanceAttribute
    @abstract   The fixed advanced attribute.
    @discussion This key is used to specify a fixed advance to be used for a font
				reference. If present and specified this is used to specify a
				constant advance to override any font values. The value associated
				with this key is a float represented as a CFNumberRef.
*/
extern const CFStringRef kCTFontFixedAdvanceAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*!		
    @defined	kCTFontOrientationAttribute
    @abstract   The orientation attribute.
    @discussion This key is used to specify a particular orientation for the glyphs 
				of the font. The value associated with this key is a int as a
				CFNumberRef. If you want to receive vertical metrics from a font
				for vertical rendering, specify kCTFontVerticalOrientation. If
				unspecified, the font will use its native orientation.
	*/
extern const CFStringRef kCTFontOrientationAttribute AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
	@enum		CTFontOrientation
	@abstract   Specifies the intended rendering orientation of the font for
				obtaining glyph metrics.
 */
enum {
	kCTFontDefaultOrientation		= 0,
	kCTFontHorizontalOrientation	= 1,
	kCTFontVerticalOrientation		= 2
};
typedef uint32_t CTFontOrientation;

// ---------------------------------------------------------------------------
// Descriptor Creation
// ---------------------------------------------------------------------------

/*!
    @function   CTFontDescriptorCreateWithNameAndSize
    @abstract   Creates a new font descriptor with the provided Postscript
				name and size. 

	@param      name
				The Postscript name to be used for the font descriptor as
				a CFStringRef.
 
	@param		size
				The point size. If 0.0, the kCTFontSizeAttribute will be omitted
				from the font descriptor.
 
    @result     This function creates a new font descriptor reference with the 
				given Postscript name and point size.
*/
CTFontDescriptorRef CTFontDescriptorCreateWithNameAndSize( 
	CFStringRef			name,
	CGFloat				size ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   CTFontDescriptorCreateWithAttributes
    @abstract   Creates a new font descriptor reference from a dictionary of
				attributes.

	@param      attributes
				A CFDictionaryRef of arbitrary attributes.
 
    @result     This function creates a new font descriptor with the attributes
				specified. This dictionary can contain arbitrary attributes 
				that will be preserved, however unrecognized attributes will be
				ignored on font creation and and may not be preserved over the
				round trip (descriptor -> font -> descriptor).
*/
CTFontDescriptorRef CTFontDescriptorCreateWithAttributes( 
	CFDictionaryRef		attributes ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   CTFontDescriptorCreateCopyWithAttributes
    @abstract   Creates a copy of the original font descriptor with new attributes.

	@param      original
				The original font descriptor reference.
 
	@param		attributes
				A CFDictionaryRef of arbitrary attributes.
 
    @result     This function creates a new copy of the original font descriptor
				with attributes augmented by those specified. If there are 
				conflicts between attributes, the new attributes will replace
				existing ones, except for kCTFontVariationAttribute and 
				kCTFontFeatureSettingsAttribute which will be merged.
*/
CTFontDescriptorRef CTFontDescriptorCreateCopyWithAttributes( 
	CTFontDescriptorRef		original,
	CFDictionaryRef			attributes ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   CTFontDescriptorCreateCopyWithVariation
    @abstract   Creates a copy of the original font descriptor with a new 
				variation instance.

	@param      original
				The original font descriptor reference.
 
	@param		variationIdentifier
				The variation axis identifier. This is the four character code
				of the variation axis as a CFNumberRef.
 
	@param		variationValue
				The value corresponding with the variation instance.
 
	@result     This function returns a copy of the original font descriptor
				with a new variation instance. This is a convenience method for
				easily creating new variation font instances.
*/
CTFontDescriptorRef CTFontDescriptorCreateCopyWithVariation( 
	CTFontDescriptorRef		original,
	CFNumberRef				variationIdentifier,
	CGFloat					variationValue ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   CTFontDescriptorCreateCopyWithFeature
	@abstract   Copies a font descriptor with new feature setting.
 
	@param      original
				The original font descriptor reference.
	
	@param		featureTypeIdentifier
				The feature type identifier.
 
	@param		featureSelectorIdentifier
				The feature selector identifier.
	
	@result     This function returns a copy of the original font descriptor
				modified with the given feature settings. This is a convenience
				method to more easily toggle the state of individual features.
 */
CTFontDescriptorRef CTFontDescriptorCreateCopyWithFeature( 
	CTFontDescriptorRef		original,
	CFNumberRef				featureTypeIdentifier,
	CFNumberRef				featureSelectorIdentifier ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   CTFontDescriptorCreateMatchingFontDescriptors
    @abstract   Returns an array of font normalized font descriptors matching
				the provided descriptor.

	@param      descriptor
				The font descriptor reference.
 
	@param		mandatoryAttributes
				A set of attribute keys which are required to be identically
				matched in any returned font descriptors. Optional.
 
    @result     This function returns a retained array of normalized font descriptors
				matching the attributes present in descriptor. If descriptor
				itself is normalized then the array will contain only one item,
				the original descriptor.
*/
CFArrayRef CTFontDescriptorCreateMatchingFontDescriptors( 
	CTFontDescriptorRef		descriptor,
	CFSetRef				mandatoryAttributes ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   CTFontDescriptorCreateMatchingFontDescriptor
	@abstract   Returns an the single preferred matching font descriptor
				based on the original descriptor and system precedence.
 
	@param      descriptor
				The font descriptor reference.
 
	@param		mandatoryAttributes
				A set of attribute keys which are required to be identically
				matched in any returned font descriptors. Optional.
 
	@result		This function returns a retained normalized font descriptor
				matching the attributes present in descriptor. The original 
				descriptor may be returned in normalized form. The caller 
				is responsible for releasing the result.
 */
CTFontDescriptorRef CTFontDescriptorCreateMatchingFontDescriptor( 
	CTFontDescriptorRef		descriptor,
	CFSetRef				mandatoryAttributes ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

// ---------------------------------------------------------------------------
// Descriptor Access
// ---------------------------------------------------------------------------

/*!
    @function   CTFontDescriptorCopyAttributes
    @abstract   Returns the attributes dictionary of the font descriptor.
 
    @param      descriptor
				The font descriptor reference.
 
    @result     This function returns a reference to the font descriptor
				attributes dictionary. This dictionary will contain the minimum
				number of attributes to fully specify this particular font 
				descriptor.
*/
CFDictionaryRef CTFontDescriptorCopyAttributes( 
	CTFontDescriptorRef		descriptor ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   CTFontDescriptorCopyAttribute
    @abstract   Returns the value associated with an arbitrary attribute.

	@param      descriptor
				The font descriptor.
 
	@param		attribute
				The requested attribute.
 
    @result     This function returns a retained reference to an arbitrary 
				attribute. If the requested attribute is not present, NULL is 
				returned. Refer to the attribute definitions for documentation
				as to how each attribute is packaged as a CFType.
*/
CFTypeRef CTFontDescriptorCopyAttribute( 
	CTFontDescriptorRef		descriptor,
	CFStringRef				attribute ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
	function	CTFontDescriptorCopyLocalizedAttribute
	@abstract   Returns a localized value for the requested attribute if
				available.
 
	@param      descriptor
				The font descriptor reference.
 
	@param		attribute
				The requested font attribute.
 
	@param		language
				Pointer to buffer to receive language reference. The language
				identifier will conform to the BCP 47 standard.
 
	@result     This function returns a retained reference to a localized
				attribute based on the global language list, and passes back the 
				matched language. If localization is not possible for the attribute
				the behavior matches CTFontDescriptorGetAttribute(). Generally,
				localization of attributes is only applicable to name attributes
				of a normalized font descriptor.
 */
CFTypeRef CTFontDescriptorCopyLocalizedAttribute( 
	CTFontDescriptorRef		descriptor,
	CFStringRef				attribute,
	CFStringRef				*language) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

// ---------------------------------------------------------------------------
// CF Support
// ---------------------------------------------------------------------------

/*!
	@function   CTFontDescriptorGetTypeID
	@abstract   Returns the type identifier for Core Text font descriptor
				references.
	@result     The identifier for the opaque type CTFontDescriptorRef.
 */
CFTypeID CTFontDescriptorGetTypeID( void ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

#if defined(__cplusplus)
}
#endif

#endif
