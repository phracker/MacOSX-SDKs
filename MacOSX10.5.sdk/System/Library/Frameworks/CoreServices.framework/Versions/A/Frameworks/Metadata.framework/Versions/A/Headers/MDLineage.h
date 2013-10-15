/*
 *  MDLineage.h
 *
 *  Copyright 2006 Apple. All rights reserved.
 *
 */

#if !defined(__MDLINEAGE__)
#define __MDLINEAGE__ 1

#include <CoreFoundation/CoreFoundation.h>

/*!
@header MDItem

 The MDLineage APIs can be used to set, alter, and store data concerning 
 the relationships between different versions of the same logical file.
 
 Lineage information is stored on files in plist-encoded dictionaries.
 
 */

#if !defined(MD_EXPORT)
    #if defined(macintosh) && defined(__MWERKS__)
        #define MD_EXPORT __declspec(export) extern
    #else
        #define MD_EXPORT extern
    #endif
    #define MD_AVAIL AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER
    #define MD_AVAIL_LEOPARD AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
    #if defined(__cplusplus)
        #define MD_BEGIN_C_DECLS extern "C" {
        #define MD_END_C_DECLS   }
    #else
        #define MD_BEGIN_C_DECLS
        #define MD_END_C_DECLS
    #endif
    #if defined(macintosh) && defined(__MWERKS__)
        #define MD_DEPRECATED
    #else
        #define MD_DEPRECATED __attribute__ ((deprecated))
    #endif
#endif

MD_BEGIN_C_DECLS

/*!
    @function 
    @abstract   This function creates a new, unique lineage.
    @param      allocator The allocator to use to allocate memory for the new object. Pass NULL or kCFAllocatorDefault to use the current default allocator.
    @result     A new, globally unique lineage, or NULL if there was an error.
 */
MD_EXPORT CFDictionaryRef MDLineageCreate(CFAllocatorRef allocator) MD_AVAIL_LEOPARD;


/*!
    @function 
    @abstract   This function copies lineage data from a file.
    @param      allocator The allocator to use to allocate memory for the new object. Pass NULL or kCFAllocatorDefault to use the current default allocator.
    @param      fileURL The URL for a file to copy lineage data from.
    @result     The function will return a CFDictionaryRef containing lineage data.  In the case where there was no lineage data associated with the file, NULL will be returned.  If there was an error, NULL will be returned.
*/
MD_EXPORT CFDictionaryRef MDLineageCreateFromFile(CFAllocatorRef allocator, CFURLRef fileURL) MD_AVAIL_LEOPARD;

/*!
 @function 
 @abstract   This file will create a new lineage descending from the provided lineage.
 @param      allocator The allocator to use to allocate memory for the new object. Pass NULL or kCFAllocatorDefault to use the current default allocator.
 @param      originalLineage The lineage to create a branched lineage from.
 @result     The function will return a CFDictionaryRef containing lineage data.  If there was an error, NULL will be returned.
 */

MD_EXPORT CFDictionaryRef MDLineageCreateBranch(CFAllocatorRef allocator, CFDictionaryRef originalLineage) MD_AVAIL_LEOPARD;

/*!
    @function 
    @abstract   This file will create a new lineage descending from the provided file.
    @param      allocator The allocator to use to allocate memory for the new object. Pass NULL or kCFAllocatorDefault to use the current default allocator.
    @param      fileURL The URL for a file to create branched lineage from.
    @result     The function will return a CFDictionaryRef containing lineage data.  In the case where there was no lineage data associated with the file, NULL will be returned.  If there was an error, NULL will be returned.
*/
MD_EXPORT CFDictionaryRef MDLineageCreateBranchFromFile(CFAllocatorRef allocator, CFURLRef fileURL) MD_AVAIL_LEOPARD;


/*!
    @function 
    @abstract   This function will write the provided lineage data on the file at fileURL.
    @discussion This function overwrites any lineage data already marked on the file.
    @param      lineage lineage data obtained from one of the MDLineageCreate functions.
    @param      fileURL The URL for a file to write the lineage data onto.
    @result     Returns true if the operation succeeded, and false otherwise.
 */
MD_EXPORT Boolean MDLineageSetOnFile(CFDictionaryRef lineage, CFURLRef fileURL) MD_AVAIL_LEOPARD;

/*!
    @function 
    @abstract   This function removes any existing lineage from the provided document.
    @param      fileURL the file to remove all lineage data from.
    @result     Returns true if all lineage data was removed from the file at fileURL, and false otherwise.  If there was no lineage data on the file, the function returns true.
 */
MD_EXPORT Boolean MDLineageRemoveFromFile(CFURLRef fileURL) MD_AVAIL_LEOPARD;

/*!
 @function 
 @abstract   This function creates a query string which will find members of the provided MDItem's document lineage family.  The query string is suitable for passing to MDQueryCreate.
 @param      item a member of the document family to locate
 @result     Returns a CFStringRef appropriate for passing to MDQueryCreate, or NULL if an error occurred.
 */

MD_EXPORT CFStringRef MDLineageCreateQueryString(MDItemRef item) MD_AVAIL_LEOPARD;

/*!
 @function 
 @abstract   This function creates a CFArray with the most direct ancestor(s) of the given item, within the context of the MDItemRefs listed in the family parameter.
 @param      item the item whose direct ancestor(s) should be returned
 @param      family a CFArrayRef of MDItemRefs  
 @result     Returns a CFArrayRef containing the most direct ancestor(s) of item.  An item could have more than one parent if a single most direct ancestor cannot be determined.  NULL is returned if no ancestors can be found in family, or if an error occurred.
 */

MD_EXPORT CFArrayRef MDLineageCopyParents(MDItemRef item, CFArrayRef family) MD_AVAIL_LEOPARD;

/*!
 @function 
 @abstract   This function creates a CFArray with the root ancestor(s) of the given item, within the context of the MDItemRefs listed in the family parameter.
 @param      item the item whose root ancestor(s) should be returned
 @param      family a CFArrayRef of MDItemRefs  
 @result     Returns a CFArrayRef containing the root ancestor(s) of item.  Note that in some cases there may be multiple items returned in the array.  NULL is returned if no ancestors can be found in family, or if an error occurred.
 */

MD_EXPORT CFArrayRef MDLineageCopyRootAncestors(MDItemRef item, CFArrayRef family) MD_AVAIL_LEOPARD;

/*!
 @function 
 @abstract   This function creates a CFArray with the most direct descendants of the given item, within the context of the MDItemRefs listed in the family parameter.
 @param      item the item whose direct descendants should be returned
 @param      family a CFArrayRef of MDItemRefs
 @result     Returns a CFArrayRef containing the most direct descendents of item.  Note that in some cases there may be multiple items returned in the array.  NULL is returned if no descendants of item can be found in family, or if an error occurred.
 */

MD_EXPORT CFArrayRef MDLineageCopyChildren(MDItemRef item, CFArrayRef family) MD_AVAIL_LEOPARD;

/*!
 @function 
 @abstract   This function creates a CFArray with the leaf descendants of the given item (the "leaf nodes" on the tree), within the context of the MDItemRefs listed in the family parameter.
 @param      item the item whose leaf descendants should be returned
 @param      family a CFArrayRef of MDItemRefs
 @result     Returns a CFArrayRef containing the leaf descendants of the item.   NULL is returned if no descendants of item can be found in family, or if an error occurred.
 */

MD_EXPORT CFArrayRef MDLineageCopyLeafDescendants(MDItemRef item, CFArrayRef family) MD_AVAIL_LEOPARD;

MD_END_C_DECLS
#endif