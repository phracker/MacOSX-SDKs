/*
    CFURLEnumerator.h
    Copyright (c) 2008-2009, Apple Inc. All rights reserved.
 */

#if !defined(__COREFOUNDATION_CFURLENUMERATOR__)
#define __COREFOUNDATION_CFURLENUMERATOR__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFError.h>
#include <CoreFoundation/CFURL.h>

CF_EXTERN_C_BEGIN


typedef const struct __CFURLEnumerator *CFURLEnumeratorRef;

/* CFURLEnumeratorGetTypeID - Returns the CFURLEnumerator CFTypeID. */
CF_EXPORT
CFTypeID CFURLEnumeratorGetTypeID( void ) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* CFURLEnumeratorOptions - Options for controlling enumerator behavior. */
enum {
    kCFURLEnumeratorDescendRecursively		= 1UL << 0,  /* The directory enumerator will recurse ("depth-first") into each subdirectory enumerated */
    kCFURLEnumeratorSkipInvisibles		= 1UL << 1,  /* The directory or volume enumerator skips "hidden" or "invisible" objects */
    kCFURLEnumeratorGenerateFileReferenceURLs	= 1UL << 2,  /* The volume enumerator generates file reference URLs */
    kCFURLEnumeratorSkipPackageContents		= 1UL << 3,  /* The directory enumerator skips package directory contents */
};
typedef CFOptionFlags CFURLEnumeratorOptions;

/* CFURLEnumeratorCreateForDirectoryURL - Creates a directory enumerator, flat or recursive. Client specifies the directory URL to enumerate, a bit array of options, and an optional array of property keys to pre-fetch for the found URLs. Specifying pre-fetch properties allows the implementation to optimize device access by using bulk operations when available. Pre-fetching more properties than are actually needed may degrade performance.

A directory enumerator generates URLs with the same type as the directory URL being enumerated. If the directoryURL input parameter is a file reference URL, then generated URLs will be file reference URLs. If the directoryURL input parameter is a file path URL, then generated URLs will be file path URLs.

The kCFURLEnumeratorGenerateFileReferenceURLs option is ignored by CFURLEnumeratorCreateForDirectoryURL.
*/
CF_EXPORT
CFURLEnumeratorRef CFURLEnumeratorCreateForDirectoryURL( CFAllocatorRef alloc, CFURLRef directoryURL, CFURLEnumeratorOptions option, CFArrayRef propertyKeys ) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* CFURLEnumeratorCreateForMountedVolumes - Creates an enumerator for mounted filesystem volumes. Client specifies an allocator, a bit array of options, and an optional array of property keys to pre-fetch for the volume URLs. Specifying pre-fetch properties allows the implementation to optimize device access by using bulk operations when available. Pre-fetching more properties than are actually needed may degrade performance.

A volume enumerator generates file path URLs. If you want a volume enumerator to generate file reference URLs, pass the kCFURLEnumeratorGenerateFileReferenceURLs option.

The kCFURLEnumeratorDescendRecursively and kCFURLEnumeratorSkipPackageContents options are ignored by CFURLEnumeratorCreateForMountedVolumes.
*/
CF_EXPORT
CFURLEnumeratorRef CFURLEnumeratorCreateForMountedVolumes( CFAllocatorRef alloc, CFURLEnumeratorOptions option, CFArrayRef propertyKeys ) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* CFURLEnumeratorResult - Results for CFURLEnumeratorGetNextURL */
enum {
    kCFURLEnumeratorSuccess = 1,    /* The enumeration was successful. The url output parameter is valid. */
    kCFURLEnumeratorEnd = 2,	    /* The enumeration is complete. */
    kCFURLEnumeratorError = 3	    /* An error occured during enumeration. The retained error output parameter describes the error. */
};
typedef CFIndex CFURLEnumeratorResult;

/* CFURLEnumeratorGetNextURL - Advances the enumerator. If kCFURLEnumeratorSuccess is returned, the url output parameter returns the next URL found. If kCFURLEnumeratorError is returned, an error has occured and the error output parameter describes the error. If kCFURLEnumeratorEnd, the enumeration is finished.

The url output parameter, if returned, is not retained. The error output parameter, if returned, is retained and must be released.
*/
CF_EXPORT
CFURLEnumeratorResult CFURLEnumeratorGetNextURL( CFURLEnumeratorRef enumerator, CFURLRef *url, CFErrorRef *error ) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* CFURLEnumeratorSkipDescendents - Tells a recursive CFURLEnumerator not to descend into the directory of the last CFURLRef returned by CFURLEnumeratorGetNextURL.

Calls to CFURLEnumeratorSkipDescendents are ignored if:
    * CFURLEnumeratorGetNextURL has never been called with the CFURLEnumerator.
    * The last CFURL returned by CFURLEnumeratorGetNextURL is not a directory.
    * The CFURLEnumerator was not created with CFURLEnumeratorCreateForDirectoryURL using the kCFURLEnumeratorDescendRecursively option.
*/
CF_EXPORT
void CFURLEnumeratorSkipDescendents( CFURLEnumeratorRef enumerator ) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* CFURLEnumeratorGetDescendentLevel - Returns the number of levels a directory enumerator has descended down into the directory hierarchy from the starting directory. The children of the starting directory are at level 1. Each time a recursive enumerator descends into a subdirectory, it adds one to the descendent level. It then subtracts one from the level when it finishes a subdirectory and continues enumerating the parent directory.
*/
CF_EXPORT
CFIndex CFURLEnumeratorGetDescendentLevel( CFURLEnumeratorRef enumerator ) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* CFURLEnumeratorGetSourceDidChange - Returns true if the data source changed while being enumerated. If the directory contents (or the volume list) changes during enumeration, the enumerator's results may be stale. Best practice is to check the result CFURLEnumeratorGetSourceDidChange() after completing enumeration, and repeat if necessary by creating a new enumerator. Be prepared to handle rapidly changing directories, for which clean enumeration may not be possible.
*/
CF_EXPORT
Boolean CFURLEnumeratorGetSourceDidChange( CFURLEnumeratorRef enumerator ) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


CF_EXTERN_C_END

#endif /* ! __COREFOUNDATION_CFURLENUMERATOR__ */

