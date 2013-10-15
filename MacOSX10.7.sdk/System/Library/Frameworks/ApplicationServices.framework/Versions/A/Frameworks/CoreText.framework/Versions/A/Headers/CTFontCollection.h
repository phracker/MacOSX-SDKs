/*
 *  CTFontCollection.h
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

#ifndef __CTFONTCOLLECTION__
#define __CTFONTCOLLECTION__

#include <CoreText/CTDefines.h>
#include <CoreText/CTFontDescriptor.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*! --------------------------------------------------------------------------
    @group Collection Types
*///--------------------------------------------------------------------------

/*!
    @typedef    CTFontCollectionRef
    @abstract   The Core Text font collection reference.
    @discussion An opaque reference to an immutable font collection.
*/
typedef const struct __CTFontCollection * CTFontCollectionRef;

/*!
    @typedef    CTMutableFontCollectionRef
    @abstract   The Core Text mutable font collection reference.
    @discussion An opaque reference to a mutable font collection.
*/
typedef struct __CTFontCollection * CTMutableFontCollectionRef;

/*!
    @function   CTFontCollectionGetTypeID
    @abstract   Returns the type identifier for Core Text font collection references.
    @result     The identifier for the opaque types CTFontCollectionRef or CTMutableFontCollectionRef.
*/
CFTypeID CTFontCollectionGetTypeID( void ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @typedef    CTFontCollectionSortDescriptorsCallback
    @abstract   Collection sorting callback.
    @discussion This callback can be specified to obtain the matching font descriptors of a collection in sorted order. Return the appropriate comparison result of first descriptor to second descriptor.
*/
typedef CFComparisonResult (*CTFontCollectionSortDescriptorsCallback)(
    CTFontDescriptorRef first,
    CTFontDescriptorRef second,
    void *refCon );

/*! --------------------------------------------------------------------------
    @group Collection Matching Options
*///--------------------------------------------------------------------------

/*!
    @defined    kCTFontCollectionRemoveDuplicatesOption
    @abstract   Option key to specify filtering of duplicates.
    @discussion Specify this option key in the options dictionary with a non- zero value to enable automatic filtering of duplicate font descriptors.
*/
extern const CFStringRef kCTFontCollectionRemoveDuplicatesOption    CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @defined    kCTFontCollectionIncludeDisabledOption
    @abstract   Option key to include disabled fonts in the matching results.
    @discussion Specify this option key in the options dictionary with a non-zero value to enable matching of disabled fonts. You can pass font descriptors specifying disabled fonts to CTFontManagerEnableFontDescriptors, but you cannot use such a font descriptor to query font attributes from the system database or create a CTFontRef.
*/
extern const CFStringRef kCTFontCollectionIncludeDisabledFontsOption CT_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_NA);

/*!
    @defined    kCTFontCollectionDisallowAutoActivationOption
    @abstract   Option key to avoid auto-activating fonts.
    @discussion Specify this option key in the options dictionary with a non-zero value to disallow searches for missing fonts (font descriptors returning no results).
*/
extern const CFStringRef kCTFontCollectionDisallowAutoActivationOption CT_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_NA);

/*! --------------------------------------------------------------------------
    @group Collection Creation
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCollectionCreateFromAvailableFonts
    @abstract   Returns a new font collection matching all available fonts.

    @param      options
                The options dictionary. See constant option keys.

    @result     This function creates a new collection containing all fonts available to the current application.
*/
CTFontCollectionRef CTFontCollectionCreateFromAvailableFonts( CFDictionaryRef options ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCollectionCreateWithFontDescriptors
    @abstract   Returns a new collection based on the array of font descriptors.

    @param      queryDescriptors
                An array of font descriptors to use for matching. May be NULL, in which case the matching descriptors will be NULL.

    @param      options
                The options dictionary. See constant option keys.

    @result     This function creates a new collection based on the provided font descriptors. The contents of this collection is defined by matching the provided descriptors against all available font descriptors.
*/
CTFontCollectionRef CTFontCollectionCreateWithFontDescriptors(
    CFArrayRef          queryDescriptors,
    CFDictionaryRef     options ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCollectionCreateCopyWithFontDescriptors
    @abstract   Returns a copy of the original collection augmented with the new font descriptors.

    @param      original
                The original font collection reference.

    @param      queryDescriptors
                An array of font descriptors to augment those of the original collection.

    @param      options
                The options dictionary. See constant option keys.

    @result     This function creates a copy of the original font collection augmented by the new font descriptors and options. The new font descriptors are merged with the existing descriptors to create a single set.
*/
CTFontCollectionRef CTFontCollectionCreateCopyWithFontDescriptors(
    CTFontCollectionRef original,
    CFArrayRef          queryDescriptors,
    CFDictionaryRef     options ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCollectionCreateMutableCopy
    @abstract   Returns a mutable copy of the original collection.

    @param      original
                The original font collection reference.

    @result     This function creates a mutable copy of the original font collection.
*/
CTMutableFontCollectionRef CTFontCollectionCreateMutableCopy(
    CTFontCollectionRef original ) CT_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_NA);

/*! --------------------------------------------------------------------------
    @group Editing the query descriptors
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCollectionCopyQueryDescriptors
    @abstract   Returns the array of descriptors to match.

    @param      collection
                The font collection reference.

    @result     This function returns a retained reference to the array of descriptors to be used to query (match) the system font database. The return value is undefined if CTFontCollectionCreateFromAvailableFonts was used to create the collection.
*/
CFArrayRef CTFontCollectionCopyQueryDescriptors( CTFontCollectionRef collection ) CT_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_NA);

/*!
    @function   CTFontCollectionSetQueryDescriptors
    @abstract   Replaces the array of descriptors to match.

    @param      collection
                The font collection reference.

    @param      descriptors
                An array of CTFontDescriptorRef. May be NULL to represent an empty collection, in which case the matching descriptors will also be NULL.
*/
void CTFontCollectionSetQueryDescriptors(
    CTMutableFontCollectionRef  collection,
    CFArrayRef                  descriptors ) CT_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_NA);

/*!
    @function   CTFontCollectionCopyExclusionDescriptors
    @abstract   Returns the array of descriptors to exclude from the match.

    @param      collection
                The font collection reference.

    @result     This function returns a retained reference to the array of descriptors to be used to query (match) the system font database.
*/
CFArrayRef CTFontCollectionCopyExclusionDescriptors( CTFontCollectionRef collection ) CT_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_NA);

/*!
    @function   CTFontCollectionSetExclusionDescriptors
    @abstract   Replaces the array of descriptors to exclude from the match.

    @param      collection
                The font collection reference.

    @param      descriptors
                An array of CTFontDescriptorRef. May be NULL.
*/
void CTFontCollectionSetExclusionDescriptors(
    CTMutableFontCollectionRef  collection,
    CFArrayRef                  descriptors ) CT_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_NA);

/*! --------------------------------------------------------------------------
    @group Retrieving Matching Descriptors
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCollectionCreateMatchingFontDescriptors
    @abstract   Returns an array of font descriptors matching the collection.

    @param      collection
                The font collection reference.

    @result     This function returns a retained reference to an array of normalized font descriptors   matching the collection definition.
*/
CFArrayRef CTFontCollectionCreateMatchingFontDescriptors( CTFontCollectionRef collection ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCollectionCreateMatchingFontDescriptorsSortedWithCallback
    @abstract   Returns the array of matching font descriptors sorted with the callback function.

    @param      collection
                The collection reference.

    @param      sortCallback
                The sorting callback function that defines the sort order.

    @param      refCon
                Pointer to client data define context for the callback.

    @result     This function returns an array of font descriptors matching the criteria of the collection and sorted by the results of the sorting callback function.
*/
CFArrayRef CTFontCollectionCreateMatchingFontDescriptorsSortedWithCallback(
    CTFontCollectionRef                     collection,
    CTFontCollectionSortDescriptorsCallback sortCallback,
    void                                    *refCon ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);

/*!
    @function   CTFontCollectionCreateMatchingFontDescriptorsWithOptions
    @abstract   Returns an array of font descriptors matching the collection.

    @param      collection
                The font collection reference.

    @param      options
                The options dictionary. See constant option keys. May be NULL, in which case this call returns the same results as CTFontCollectionCreateMatchingFontDescriptors, using the options passed in when the collection was created.

    @result     This function returns a retained reference to an array of normalized font descriptors   matching the collection definition.
*/
CFArrayRef CTFontCollectionCreateMatchingFontDescriptorsWithOptions( CTFontCollectionRef collection,
    CFDictionaryRef     options ) CT_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_NA);

/*!
    @function   CTFontCollectionCreateMatchingFontDescriptorsForFamily
    @abstract   Returns an array of font descriptors matching the specified family, one descriptor for each style in the collection.

    @param      collection
                The font collection reference.

    @param      familyName
                The font family name

    @result     This function returns a retained reference to an array of normalized font descriptors matching the collection definition.
*/
CFArrayRef CTFontCollectionCreateMatchingFontDescriptorsForFamily(
    CTFontCollectionRef collection,
    CFStringRef         familyName,
    CFDictionaryRef     options ) CT_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_NA);

/*! --------------------------------------------------------------------------
    @group Bulk attribute access
*///--------------------------------------------------------------------------
/*!
    @enum       CTFontCollectionCopyOptions
    @abstract   Option bits for use with CTFontCollectionCopyFontAttribute(s).

    @constant   kCTFontCollectionCopyStandardSort
                Passing this option indicates that the return values should be sorted in standard UI order, suitable for display to the user. This is the same sorting behavior used by NSFontPanel and Font Book.

    @constant   kCTFontCollectionCopyUnique
                Passing this option indicates that duplicate values should be removed from the results.
 */
enum
{
    kCTFontCollectionCopyDefaultOptions = 0,
    kCTFontCollectionCopyUnique = (1L << 0),
    kCTFontCollectionCopyStandardSort = (1L << 1)
};
typedef uint32_t CTFontCollectionCopyOptions;

/*!
    @function   CTFontCollectionCopyFontAttribute
    @abstract   Returns an array of font descriptor attribute values.

    @param      collection
                The font collection reference.

    @param      attributeName
                The attribute to retrieve for each descriptor in the collection.

    @param      options
                Options to alter the return value.

    @result     This function returns a retained reference to a CFArray, or NULL on error. The caller is reponsible for releasing the array. The array contains one value for each descriptor, in the same order as the results from CTFontCollectionCreateMatchingDescriptors. When the kCTFontCollectionCopyUnique is set, duplicate values will be removed. When kCTFontCollectionCopyStandardSort is set, the values will be sorted in standard UI order.
 */
CFArrayRef CTFontCollectionCopyFontAttribute(
    CTFontCollectionRef         collection,
    CFStringRef                 attributeName,
    CTFontCollectionCopyOptions options ) CT_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_NA);

/*!
    @function   CTFontCollectionCopyFontAttributes
    @abstract   Returns an array of dictionaries containing font descriptor attribute values.
 
    @param      collection
                The font collection reference.

    @param      attributeNames
                The attributes to retrieve for each descriptor in the collection.

    @param      options
                Options to alter the return value.

    @result     This function returns a retained reference to a CFArray, or NULL on error. The caller is reponsible for releasing the array. The array contains one value for each descriptor, in the same order as the results from CTFontCollectionCreateMatchingDescriptors. When the kCTFontCollectionCopyUnique is set, duplicate values will be removed. When kCTFontCollectionCopyStandardSort is set, the values will be sorted in standard UI order.
 */
CFArrayRef CTFontCollectionCopyFontAttributes(
    CTFontCollectionRef         collection,
    CFSetRef                    attributeNames,
    CTFontCollectionCopyOptions options ) CT_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_NA);

#if defined(__cplusplus)
}
#endif

#endif
