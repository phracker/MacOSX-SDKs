/*
 *  CTFontDescriptor.h
 *  CoreText
 *
 *  Copyright (c) 2006-2015 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTFONTDESCRIPTOR__
#define __CTFONTDESCRIPTOR__

#include <CoreText/CTDefines.h>
#include <CoreText/CTFontTraits.h>

#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFCharacterSet.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFSet.h>
#include <CoreGraphics/CGAffineTransform.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/*! --------------------------------------------------------------------------
    @group Descriptor Types
*///--------------------------------------------------------------------------

/*!
    @typedef    CTFontDescriptorRef
    @abstract   The Core Text Font Descriptor reference.
    @discussion This is a opaque reference to a font descriptor.
*/
#if TARGET_OS_IPHONE
typedef const struct CF_BRIDGED_TYPE(UIFontDescriptor) __CTFontDescriptor * CTFontDescriptorRef;
#else
typedef const struct CF_BRIDGED_TYPE(NSFontDescriptor) __CTFontDescriptor * CTFontDescriptorRef;
#endif

/*!
    @function   CTFontDescriptorGetTypeID
    @abstract   Returns the type identifier for Core Text font descriptor
                references.
    @result     The identifier for the opaque type CTFontDescriptorRef.
*/
CFTypeID CTFontDescriptorGetTypeID( void ) CT_AVAILABLE(10_5, 3_2);

/*! --------------------------------------------------------------------------
    @group Descriptor Constants
*///--------------------------------------------------------------------------

/*!
    @defined    kCTFontURLAttribute
    @abstract   The font URL.
    @discussion This is the key for accessing the font URL from the font descriptor. The value associated with this key is a CFURLRef.
*/
extern const CFStringRef kCTFontURLAttribute CT_AVAILABLE(10_6, 3_2);
/*!
    @defined    kCTFontNameAttribute
    @abstract   The PostScript name.
    @discussion This is the key for retrieving the PostScript name from the font descriptor. When matching, this is treated more generically: the system first tries to find fonts with this PostScript name. If none is found, the system tries to find fonts with this family name, and, finally, if still nothing, tries to find fonts with this display name. The value associated with this key is a CFStringRef. If unspecified, defaults to "Helvetica", if unavailable falls back to global font cascade list.
*/
extern const CFStringRef kCTFontNameAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontDisplayNameAttribute
    @abstract   The display name.
    @discussion This is the key for accessing the name used to display the font. Most commonly this is the full name. The value associated with this key is a CFStringRef.
*/
extern const CFStringRef kCTFontDisplayNameAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFamilyNameAttribute
    @abstract   The family name.
    @discussion This is the key for accessing the family name from the font descriptor. The value associated with this key is a CFStringRef.
*/
extern const CFStringRef kCTFontFamilyNameAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontStyleNameAttribute
    @abstract   The style name.
    @discussion This is the key for accessing the style name of the font. This name represents the designer's description of the font's style. The value associated with this key is a CFStringRef.
*/
extern const CFStringRef kCTFontStyleNameAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontTraitsAttribute
    @abstract   The font traits dictionary.
    @discussion This is the key for accessing the dictionary of font traits for stylistic information. See CTFontTraits.h for the list of font traits. The value associated with this key is a CFDictionaryRef.
*/
extern const CFStringRef kCTFontTraitsAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontVariationAttribute
    @abstract   The font variation dictionary.
    @discussion This key is used to obtain the font variation instance as a CFDictionaryRef. If specified in a font descriptor, fonts with the specified axes will be primary match candidates, if no such fonts exist, this attribute will be ignored.
*/
extern const CFStringRef kCTFontVariationAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontSizeAttribute
    @abstract   The font point size.
    @discussion This key is used to obtain or specify the font point size. Creating a font with this unspecified will default to a point size of 12.0. The value for this key is represented as a CFNumberRef.
*/
extern const CFStringRef kCTFontSizeAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontMatrixAttribute
    @abstract   The font transformation matrix.
    @discussion This key is used to specify the font transformation matrix when creating a font. The default value is CGAffineTransformIdentity. The value for this key is a CFDataRef containing a CGAffineTransform, of which only the a, b, c, and d fields are used.
*/
extern const CFStringRef kCTFontMatrixAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontCascadeListAttribute
    @abstract   The font cascade list.
    @discussion This key is used to specify or obtain the cascade list used for a font reference. The cascade list is a CFArrayRef containing CTFontDescriptorRefs. If unspecified, the global cascade list is used. This list is not consulted for private-use characters on OS X 10.10, iOS 8, or earlier.
*/
extern const CFStringRef kCTFontCascadeListAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontCharacterSetAttribute
    @abstract   The font unicode character coverage set.
    @discussion This key is used to specify or obtain the character set for a font reference. This value for this key is a CFCharacterSetRef. If specified this can be used to restrict the font to a subset of its actual character set. If unspecified this attribute is ignored and the actual character set is used.
*/
extern const CFStringRef kCTFontCharacterSetAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontLanguagesAttribute
    @abstract   The list of supported languages.
    @discussion This key is used to specify or obtain a list of covered languages for a font reference. The value for this key is a CFArrayRef of CFStringRefs. If specified this restricts the search to matching fonts that support the specified languages. The language identifier string should conform to UTS #35. If unspecified this attribute is ignored.
*/
extern const CFStringRef kCTFontLanguagesAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontBaselineAdjustAttribute
    @abstract   The baseline adjustment to apply to font metrics.
    @discussion This key is used to specify or obtain the baseline adjustment for a font reference. This is primary used when defining font descriptors for a cascade list to keep the baseline of all fonts even. The value associated with this is a float represented as a CFNumberRef.
*/
extern const CFStringRef kCTFontBaselineAdjustAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontMacintoshEncodingsAttribute
    @abstract   The macintosh encodings attribute.
    @discussion This key is used to specify or obtain the macintosh encodings for a font reference. The value associated with this key is a CFNumberRef containing a bitfield of the Macintosh encodings. This attribute is provided for legacy compatibility.
*/
extern const CFStringRef kCTFontMacintoshEncodingsAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFeaturesAttribute
    @abstract   The array of font features.
    @discussion This key is used to specify or obtain the font features for a font reference. The value associated with this key is a CFArrayRef of font feature dictionaries. This features list contains the feature information from the 'feat' table of the font. See the CTFontCopyFeatures() API in   CTFont.h.
*/
extern const CFStringRef kCTFontFeaturesAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFeatureSettingsAttribute
    @abstract   The array of typographic feature settings.
    @discussion This key is used to specify an array of zero or more feature settings. In the case of duplicate or conflicting settings the last setting in the list will take precedence. In the case of AAT settings, it is the caller's responsibility to handle exclusive and non-exclusive settings as necessary.
                An AAT setting dictionary contains a tuple of a kCTFontFeatureTypeIdentifierKey key-value pair and a kCTFontFeatureSelectorIdentifierKey key-value pair.
                An OpenType setting dictionary contains a tuple of a kCTFontOpenTypeFeatureTag key-value pair and a kCTFontOpenTypeFeatureValue key-value pair. Each setting dictionary indicates which setting should be applied. In the case of duplicate or conflicting settings the last setting in the list will take precedence.

                Starting with OS X 10.10 and iOS 8.0, settings are also accepted (but not returned) in the following simplified forms:
                An OpenType setting can be either an array pair of tag string and value number, or a tag string on its own. For example: @[ @"c2sc", @1 ] or simply @"c2sc". An unspecified value enables the feature and a value of zero disables it.
                An AAT setting can be specified as an array pair of type and selector numbers. For example: @[ @(kUpperCaseType), @(kUpperCaseSmallCapsSelector) ].
*/
extern const CFStringRef kCTFontFeatureSettingsAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontFixedAdvanceAttribute
    @abstract   Specifies advance width.
    @discussion This key is used to specify a constant advance width, which affects the glyph metrics of any font instance created with this key; it overrides font values and the font transformation matrix, if any. The value associated with this key must be a CFNumberRef.
*/
extern const CFStringRef kCTFontFixedAdvanceAttribute CT_AVAILABLE(10_5, 3_2);
/*!
    @defined    kCTFontOrientationAttribute
    @abstract   The orientation attribute.
    @discussion This key is used to specify a particular orientation for the glyphs of the font. The value associated with this key is a int as a CFNumberRef. If you want to receive vertical metrics from a font for vertical rendering, specify kCTFontVerticalOrientation. If unspecified, the font will use its native orientation.
*/
extern const CFStringRef kCTFontOrientationAttribute CT_AVAILABLE(10_5, 3_2);

/*!
    @enum       CTFontOrientation
    @abstract   Specifies the intended rendering orientation of the font for obtaining glyph metrics.
*/
typedef CF_ENUM(uint32_t, CTFontOrientation) {
    kCTFontOrientationDefault    CT_ENUM_AVAILABLE(10_8, 6_0) = 0,
    kCTFontOrientationHorizontal CT_ENUM_AVAILABLE(10_8, 6_0) = 1,
    kCTFontOrientationVertical   CT_ENUM_AVAILABLE(10_8, 6_0) = 2,

    kCTFontDefaultOrientation CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontOrientationDefault,
    kCTFontHorizontalOrientation CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontOrientationHorizontal,
    kCTFontVerticalOrientation CT_ENUM_DEPRECATED(10_5, 10_11, 3_2, 9_0) = kCTFontOrientationVertical
};

/*!
    @defined    kCTFontFormatAttribute
    @abstract   Specifies the recognized format of the font.
    @discussion The attribute is used to specify or obtain the format of the font. The returned value is a CFNumber containing one of the constants defined below.
*/
extern const CFStringRef kCTFontFormatAttribute CT_AVAILABLE(10_6, 3_2);

/*!
    @constant   kCTFontFormatUnrecognized
                The font is not a recognized format
    @constant   kCTFontFormatOpenTypePostScript
                The font is an OpenType format containing PostScript data
    @constant   kCTFontFormatOpenTypeTrueType
                The font is an OpenType format containing TrueType data
    @constant   kCTFontFormatTrueType
                The font is a recognized TrueType format
    @constant   kCTFontFormatPostScript
                The font is a recognized PostScript format
    @constant   kCTFontFormatBitmap
                The font is a bitmap only format
*/
typedef CF_ENUM(uint32_t, CTFontFormat) {
    kCTFontFormatUnrecognized       = 0,
    kCTFontFormatOpenTypePostScript = 1,
    kCTFontFormatOpenTypeTrueType   = 2,
    kCTFontFormatTrueType           = 3,
    kCTFontFormatPostScript         = 4,
    kCTFontFormatBitmap             = 5
};

/*!
    @defined    kCTFontRegistrationScopeAttribute
    @abstract   Specifies the font descriptor's registration scope.
    @discussion The attribute is used to specify or obtain the font registration scope. The value returned is a CFNumberRef containing one of the CTFontManagerScope enumerated values. A value of NULL can be returned for font descriptors that are not registered.
*/
extern const CFStringRef kCTFontRegistrationScopeAttribute CT_AVAILABLE(10_6, 3_2);
/*!
    @defined    kCTFontPriorityAttribute
    @abstract   The font descriptors priority when resolving duplicates and sorting match results.
    @discussion This key is used to obtain or specify the font priority. The value returned is a CFNumberRef containing an integer value as defined below. The higher the value, the higher the priority of the font. Only registered fonts will have a priority. Unregistered font descriptors will return NULL.
*/
extern const CFStringRef kCTFontPriorityAttribute CT_AVAILABLE(10_6, 3_2);

/*!
    @constant   kCTFontPrioritySystem
                Priority of system fonts (located in /System/Library/Fonts).
    @constant   kCTFontPriorityNetwork
                Priority of network fonts (located in /Network/Library/Fonts).
    @constant   kCTFontPriorityComputer
                Priority of computer local fonts (located in /Library/Fonts).
    @constant   kCTFontPriorityUser
                Priority of local fonts (located in user's Library/Fonts).
    @constant   kCTFontPriorityDynamic
                Priority of fonts registered dynamically, not located in a standard location (either kCTFontManagerScopeUser, or kCTFontManagerScopeSession).
    @constant   kCTFontPriorityProcess
                Priority of fonts registered for the process (kCTFontManagerScopeProcess).
*/
enum {
    kCTFontPrioritySystem       =  10000,
    kCTFontPriorityNetwork      =  20000,
    kCTFontPriorityComputer     =  30000,
    kCTFontPriorityUser         =  40000,
    kCTFontPriorityDynamic      =  50000,
    kCTFontPriorityProcess      =  60000
};
typedef uint32_t CTFontPriority;

/*!
    @defined    kCTFontEnabledAttribute
    @abstract   The font enabled state.
    @discussion This key is used to obtain the font state. The returned value is a CFNumberRef representing a boolean value. Unregistered font descriptors will return NULL, which is equivalent to false.
*/
extern const CFStringRef kCTFontEnabledAttribute CT_AVAILABLE(10_6, 3_2);

/*!
	@defined    kCTFontDownloadableAttribute
	@abstract   The font downloadable state.
	@discussion The value associated with this key is a CFBoolean.  If it is kCFBooleanTrue, CoreText attempts to download a font if necessary when matching a descriptor.
*/
extern const CFStringRef kCTFontDownloadableAttribute CT_AVAILABLE(10_8, 6_0);

/*!
    @defined    kCTFontDownloadedAttribute
    @abstract   The download state.
    @discussion The value associated with this key is a CFBoolean.  If it is kCFBooleanTrue, corresponding FontAsset has been downloaded. (but still it may be necessary to call appropriate API in order to use the font in the FontAsset.)
*/
extern const CFStringRef kCTFontDownloadedAttribute CT_AVAILABLE_IOS(7_0);

/*! --------------------------------------------------------------------------
    @group Descriptor Creation
*///--------------------------------------------------------------------------

/*!
    @function   CTFontDescriptorCreateWithNameAndSize
    @abstract   Creates a new font descriptor with the provided PostScript name and size.

    @param      name
                The PostScript name to be used for the font descriptor as a CFStringRef.

    @param      size
                The point size. If 0.0, the kCTFontSizeAttribute will be omitted from the font descriptor.

    @result     This function creates a new font descriptor reference with the given PostScript name and point size.
*/
CTFontDescriptorRef CTFontDescriptorCreateWithNameAndSize(
    CFStringRef         name,
    CGFloat             size ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontDescriptorCreateWithAttributes
    @abstract   Creates a new font descriptor reference from a dictionary of attributes.

    @param      attributes
                A CFDictionaryRef of arbitrary attributes.

    @result     This function creates a new font descriptor with the attributes specified. This dictionary can contain arbitrary attributes that will be preserved, however unrecognized attributes will be ignored on font creation and and may not be preserved over the round trip (descriptor -> font -> descriptor).
*/
CTFontDescriptorRef CTFontDescriptorCreateWithAttributes(
    CFDictionaryRef     attributes ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontDescriptorCreateCopyWithAttributes
    @abstract   Creates a copy of the original font descriptor with new attributes.

    @param      original
                The original font descriptor reference.

    @param      attributes
                A CFDictionaryRef of arbitrary attributes.

    @result     This function creates a new copy of the original font descriptor with attributes augmented by those specified. If there are conflicts between attributes, the new attributes will replace existing ones, except for kCTFontVariationAttribute and kCTFontFeatureSettingsAttribute which will be merged.
*/
CTFontDescriptorRef CTFontDescriptorCreateCopyWithAttributes(
    CTFontDescriptorRef     original,
    CFDictionaryRef         attributes ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontCreateCopyWithFamily
    @abstract   Returns a new font descriptor in the specified family based on the traits of the original descriptor.

    @param      original
                The original font descriptor reference.

    @param		family
                The name of the desired family.

    @result     Returns a new font reference with the original traits in the given family, or NULL if none found in the system.
*/
CTFontDescriptorRef __nullable CTFontDescriptorCreateCopyWithFamily(
    CTFontDescriptorRef     original,
    CFStringRef             family ) CT_AVAILABLE(10_9, 7_0);

/*!
    @function   CTFontDescriptorCreateCopyWithSymbolicTraits
    @abstract   Returns a new font descriptor based on the original descriptor having the specified symbolic traits.

    @param      original
                The original font descriptor reference.

    @param		symTraitValue
                The value of the symbolic traits. This bitfield is used to indicate the desired value for the traits specified by the symTraitMask parameter. Used in conjunction, they can allow for trait removal as well as addition.

    @param		symTraitMask
                The mask bits of the symbolic traits. This bitfield is used to indicate the traits that should be changed.

    @result     Returns a new font descriptor reference in the same family with the given symbolic traits, or NULL if none found in the system.
*/
CTFontDescriptorRef __nullable CTFontDescriptorCreateCopyWithSymbolicTraits(
    CTFontDescriptorRef     original,
    CTFontSymbolicTraits    symTraitValue,
    CTFontSymbolicTraits    symTraitMask ) CT_AVAILABLE(10_9, 7_0);

/*!
    @function   CTFontDescriptorCreateCopyWithVariation
    @abstract   Creates a copy of the original font descriptor with a new variation instance.

    @param      original
                The original font descriptor reference.

    @param      variationIdentifier
                The variation axis identifier. This is the four character code of the variation axis as a CFNumberRef.

    @param      variationValue
                The value corresponding with the variation instance.

    @result     This function returns a copy of the original font descriptor with a new variation instance. This is a convenience method for easily creating new variation font instances.
*/
CTFontDescriptorRef CTFontDescriptorCreateCopyWithVariation(
    CTFontDescriptorRef     original,
    CFNumberRef             variationIdentifier,
    CGFloat                 variationValue ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontDescriptorCreateCopyWithFeature
    @abstract   Copies a font descriptor with new feature setting.

    @discussion This is a convenience method to more easily toggle the state of individual features.

    @param      original
                The original font descriptor reference.

    @param      featureTypeIdentifier
                The feature type identifier.

    @param      featureSelectorIdentifier
                The feature selector identifier.

    @result     A copy of the original font descriptor modified with the given feature settings.
*/
CTFontDescriptorRef CTFontDescriptorCreateCopyWithFeature(
    CTFontDescriptorRef     original,
    CFNumberRef             featureTypeIdentifier,
    CFNumberRef             featureSelectorIdentifier ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontDescriptorCreateMatchingFontDescriptors
    @abstract   Returns an array of font normalized font descriptors matching the provided descriptor.

    @param      descriptor
                The font descriptor reference.

    @param      mandatoryAttributes
                A set of attribute keys which are required to be identically matched in any returned font descriptors. Optional.

    @result     This function returns a retained array of normalized font descriptors matching the attributes present in descriptor. If descriptor itself is normalized then the array will contain only one item, the original descriptor.
*/
CFArrayRef __nullable CTFontDescriptorCreateMatchingFontDescriptors(
    CTFontDescriptorRef     descriptor,
    CFSetRef __nullable     mandatoryAttributes ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontDescriptorCreateMatchingFontDescriptor
    @abstract   Returns an the single preferred matching font descriptor based on the original descriptor and system precedence.

    @param      descriptor
                The font descriptor reference.

    @param      mandatoryAttributes
                A set of attribute keys which are required to be identically matched in any returned font descriptors. Optional.

    @result     This function returns a retained normalized font descriptor matching the attributes present in descriptor. The original descriptor may be returned in normalized form.
*/
CTFontDescriptorRef __nullable CTFontDescriptorCreateMatchingFontDescriptor(
    CTFontDescriptorRef     descriptor,
    CFSetRef __nullable     mandatoryAttributes ) CT_AVAILABLE(10_5, 3_2);

    
/*!
    Progress state
 */

typedef CF_ENUM(uint32_t, CTFontDescriptorMatchingState) {
    kCTFontDescriptorMatchingDidBegin,              // called once at the beginning.
    kCTFontDescriptorMatchingDidFinish,             // called once at the end.
    
    kCTFontDescriptorMatchingWillBeginQuerying,     // called once before talking to the server.  Skipped if not necessary.
    kCTFontDescriptorMatchingStalled,               // called when stalled. (e.g. while waiting for server response.)
    
    // Downloading and activating are repeated for each descriptor.
    kCTFontDescriptorMatchingWillBeginDownloading,  // Downloading part may be skipped if all the assets are already downloaded
    kCTFontDescriptorMatchingDownloading,
    kCTFontDescriptorMatchingDidFinishDownloading,
    kCTFontDescriptorMatchingDidMatch,              // called when font descriptor is matched.
    
    kCTFontDescriptorMatchingDidFailWithError       // called when an error occurred.  (may be called multiple times.)
};

/*!
    keys for progressParameter dictionary.
 */

/* CTFontDescriptorRef; The current font descriptor.   Valid when state is kCTFontDescriptorMatchingDidMatch. */
extern const CFStringRef kCTFontDescriptorMatchingSourceDescriptor CT_AVAILABLE(10_8, 6_0);

/* CFArray; Array of descriptors to be queried.   Valid while downloading or when state is kCTFontDescriptorMatchingWillBeginQuerying. */
extern const CFStringRef kCTFontDescriptorMatchingDescriptors CT_AVAILABLE(10_8, 6_0);

/* CFArray; Array of matched font descriptors.   Valid when state is kCTFontDescriptorMatchingDidMatch or CTFontDescriptorMatchingEnd. */
extern const CFStringRef kCTFontDescriptorMatchingResult CT_AVAILABLE(10_8, 6_0);

/* CFNumber; Download progress in 0 - 100.   Valid during Downloading state. */
extern const CFStringRef kCTFontDescriptorMatchingPercentage CT_AVAILABLE(10_8, 6_0);

/* CFNumber; Byte size to download for the current descriptor.   Valid during Downloading state. */
extern const CFStringRef kCTFontDescriptorMatchingCurrentAssetSize CT_AVAILABLE(10_8, 6_0);

/* CFNumber; Total downloaded byte size.   Valid during Downloading state. */
extern const CFStringRef kCTFontDescriptorMatchingTotalDownloadedSize CT_AVAILABLE(10_8, 6_0);

/* CFNumber; Total byte size to download.   Always valid, but may be Zero when information is not available. */
extern const CFStringRef kCTFontDescriptorMatchingTotalAssetSize CT_AVAILABLE(10_8, 6_0);

/* CFError; Valid when state kCTFontDescriptorMatchingDidFailWithError. */
extern const CFStringRef kCTFontDescriptorMatchingError CT_AVAILABLE(10_8, 6_0);

#if defined(__BLOCKS__)

/* Progress callback type */
typedef bool (^CTFontDescriptorProgressHandler)(CTFontDescriptorMatchingState state, CFDictionaryRef progressParameter);

/*
    @function   CTFontDescriptorMatchFontDescriptorsWithProgressHandler
                This function returns immediately, but can potentially take long time to process.  The progress is notified via progressBlock.
     
    @param      descriptors
                An array of descriptors to process.
     
    @param      mandatoryAttributes
     
    @param      progressBlock
                Callback block to indicate the progress.
                Return true to continue, and return false to cancel the process.
     
    @result     false if it couldn't start the work.
*/
    
bool CTFontDescriptorMatchFontDescriptorsWithProgressHandler(
    CFArrayRef                          descriptors,
    CFSetRef __nullable                 mandatoryAttributes,
    CTFontDescriptorProgressHandler     progressBlock) CT_AVAILABLE(10_9, 6_0);

#endif // defined(__BLOCKS__)

/*! --------------------------------------------------------------------------
    @group Descriptor Accessors
*///--------------------------------------------------------------------------

/*!
    @function   CTFontDescriptorCopyAttributes
    @abstract   Returns the attributes dictionary of the font descriptor.

    @param      descriptor
                The font descriptor reference.

    @result     A retained reference to the font descriptor attributes dictionary. This dictionary will contain the minimum number of attributes to fully specify this particular font descriptor.
*/
CFDictionaryRef CTFontDescriptorCopyAttributes(
    CTFontDescriptorRef     descriptor ) CT_AVAILABLE(10_5, 3_2);

/*!
    @function   CTFontDescriptorCopyAttribute
    @abstract   Returns the value associated with an arbitrary attribute.

    @param      descriptor
                The font descriptor.

    @param      attribute
                The requested attribute.

    @result     A retained reference to the requested attribute, or NULL if the requested attribute is not present. Refer to the attribute definitions for documentation as to how each attribute is packaged as a CFType.
*/
CFTypeRef __nullable CTFontDescriptorCopyAttribute(
    CTFontDescriptorRef     descriptor,
    CFStringRef             attribute ) CT_AVAILABLE(10_5, 3_2);

/*!
    function    CTFontDescriptorCopyLocalizedAttribute
    @abstract   Returns a localized value for the requested attribute if available.

    @discussion This function returns a localized attribute based on the global language list. If localization is not possible for the attribute the behavior matches CTFontDescriptorCopyAttribute(). Generally, localization of attributes is only applicable to name attributes of a normalized font descriptor.

    @param      descriptor
                The font descriptor reference.

    @param      attribute
                The requested font attribute.

    @param      language
                If non-NULL, this will be receive a retained reference to the matched language. The language identifier will conform to UTS #35.
                If CoreText can supply its own localized string where the font cannot, this value will be NULL.

    @result     A retained reference to the requested attribute, or NULL if the requested attribute is not present. Refer to the attribute definitions for documentation as to how each attribute is packaged as a CFType.
*/
CFTypeRef __nullable CTFontDescriptorCopyLocalizedAttribute(
    CTFontDescriptorRef     descriptor,
    CFStringRef             attribute,
    CFStringRef __nullable * __nullable language ) CT_AVAILABLE(10_5, 3_2);

CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
