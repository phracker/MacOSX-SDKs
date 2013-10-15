/*
 *  CTFontCollection.h
 *  CoreText
 *
 *  Copyright (c) 2006-2008 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTFONTCOLLECTION__
#define __CTFONTCOLLECTION__

#include <CoreText/CTFontDescriptor.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*! --------------------------------------------------------------------------
    @group Collection Types
*///--------------------------------------------------------------------------

/*!
    @typedef    CTFontCollectionRef
    @abstract   The Core Text Font Collection reference.
    @discussion An opaque reference to a font collection.
*/
typedef const struct __CTFontCollection * CTFontCollectionRef;

/*!
    @function   CTFontCollectionGetTypeID
    @abstract   Returns the type identifier for Core Text font collection references.
    @result     The identifier for the opaque type CTFontCollectionRef.
*/
CFTypeID CTFontCollectionGetTypeID( void ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @typedef    CTFontCollectionSortDescriptorsCallback
    @abstract   Collection sorting callback.
    @discussion This callback can be specified to obtain the matching font descriptors of a collection in sorted order. Return the appropriate comparison result of first descriptor to second descriptor.
*/
typedef CFComparisonResult (*CTFontCollectionSortDescriptorsCallback)(CTFontDescriptorRef first, CTFontDescriptorRef second, void *refCon);

/*! --------------------------------------------------------------------------
    @group Collection Constants
*///--------------------------------------------------------------------------

/*!
    @defined    kCTFontCollectionRemoveDuplicatesOption
    @abstract   Option key to specify filtering of duplicates.
    @discussion Specify this option key in the options dictionary with a non- zero value to enable automatic filtering of duplicate font descriptors.
*/
extern const CFStringRef kCTFontCollectionRemoveDuplicatesOption    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! --------------------------------------------------------------------------
    @group Collection Creation
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCollectionCreateFromAvailableFonts
    @abstract   Returns a new font collection containing all available fonts.

    @param      options
                The options dictionary. See constant option keys.

    @result     This function creates a new collection containing all fonts available to the current application.
*/
CTFontCollectionRef CTFontCollectionCreateFromAvailableFonts( CFDictionaryRef options ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   CTFontCollectionCreateWithFontDescriptors
    @abstract   Returns a new collection based on the array of font descriptors.

    @param      descriptors
                An array of font descriptors.

    @param      options
                The options dictionary. See constant option keys.

    @result     This function creates a new collection based on the provided font descriptors. The contents of this collection is defined by matching the provided descriptors against all available font descriptors.
*/
CTFontCollectionRef CTFontCollectionCreateWithFontDescriptors(
    CFArrayRef          descriptors,
    CFDictionaryRef     options ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @function   CTFontCollectionCreateCopyWithFontDescriptors
    @abstract   Returns a copy of the original collection augmented with the new font descriptors.

    @param      original
                The original font collection reference.

    @param      descriptor
                An array of font descriptors to augment those of the original collection.

    @param      options
                The options dictionary. See constant option keys.

    @result     This function creates a copy of the original font collection augmented by the new font descriptors and options. The new font descriptors are merged with the existing descriptors to create a single set.
*/
CTFontCollectionRef CTFontCollectionCreateCopyWithFontDescriptors(
    CTFontCollectionRef original,
    CFArrayRef          descriptors,
    CFDictionaryRef     options ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*! --------------------------------------------------------------------------
    @group Collection Access
*///--------------------------------------------------------------------------

/*!
    @function   CTFontCollectionCreateMatchingFontDescriptors
    @abstract   Returns an array of font descriptors matching the collection.

    @param      collection
                The font collection reference.

    @result     This function returns a retained reference to an array of normalized font descriptors   matching the collection definition.
*/
CFArrayRef CTFontCollectionCreateMatchingFontDescriptors( CTFontCollectionRef collection ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

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
    void                                    *refCon ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

#if defined(__cplusplus)
}
#endif

#endif
