/*
    CFURLEnumerator.h
    Copyright (c) 2008-2012, Apple Inc. All rights reserved.
 */

#if (TARGET_OS_MAC || TARGET_OS_EMBEDDED || TARGET_OS_IPHONE) || CF_BUILDING_CF || NSBUILDINGFOUNDATION

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
CFTypeID CFURLEnumeratorGetTypeID( void ) CF_AVAILABLE(10_6, 4_0);


/* CFURLEnumeratorOptions - Options for controlling enumerator behavior. */
typedef CF_OPTIONS(CFOptionFlags, CFURLEnumeratorOptions) {
    kCFURLEnumeratorDefaultBehavior                 = 0,        /* Use the default behavior for the enumerator. */
    kCFURLEnumeratorDescendRecursively              = 1UL << 0, /* The directory enumerator will recurse ("depth-first") into each subdirectory enumerated */
    kCFURLEnumeratorSkipInvisibles                  = 1UL << 1, /* The directory or volume enumerator skips "hidden" or "invisible" objects */
    kCFURLEnumeratorGenerateFileReferenceURLs       = 1UL << 2, /* The volume enumerator generates file reference URLs */
    kCFURLEnumeratorSkipPackageContents             = 1UL << 3, /* The directory enumerator skips package directory contents */
    kCFURLEnumeratorIncludeDirectoriesPreOrder      = 1UL << 4, /* With this option set, a recursive directory enumerator will return directory URLs when CFURLEnumeratorGetNextURL() returns kCFURLEnumeratorSuccess before any of the directory's descendants are visited (pre-order). */
    kCFURLEnumeratorIncludeDirectoriesPostOrder     = 1UL << 5, /* With this option set, a recursive directory enumerator will return directory URLs when CFURLEnumeratorGetNextURL() returns kCFURLEnumeratorDirectoryPostOrderSuccess after all of directory's descendants have been visited (post-order). */
    /* Note: if both kCFURLEnumeratorIncludeDirectoriesPreOrder and kCFURLEnumeratorIncludeDirectoriesPostOrder are used, directories will be seen twice (even empty directories and directories whose descendants are skipped) -- once when kCFURLEnumeratorSuccess is returned and once when kCFURLEnumeratorDirectoryPostOrderSuccess is returned. */
};

/* CFURLEnumeratorCreateForDirectoryURL - Creates a directory enumerator, flat or recursive. Client specifies the directory URL to enumerate, a bit array of options, and an optional array of property keys to pre-fetch for the found URLs. Specifying pre-fetch properties allows the implementation to optimize device access by using bulk operations when available. Pre-fetching more properties than are actually needed may degrade performance.

A directory enumerator generates URLs with the same type as the directory URL being enumerated. If the directoryURL input parameter is a file reference URL, then generated URLs will be file reference URLs. If the directoryURL input parameter is a file path URL, then generated URLs will be file path URLs.

The kCFURLEnumeratorGenerateFileReferenceURLs option is ignored by CFURLEnumeratorCreateForDirectoryURL.
*/
CF_EXPORT
CFURLEnumeratorRef CFURLEnumeratorCreateForDirectoryURL( CFAllocatorRef alloc, CFURLRef directoryURL, CFURLEnumeratorOptions option, CFArrayRef propertyKeys ) CF_AVAILABLE(10_6, 4_0);


/* CFURLEnumeratorCreateForMountedVolumes - Creates an enumerator for mounted filesystem volumes. Client specifies an allocator, a bit array of options, and an optional array of property keys to pre-fetch for the volume URLs. Specifying pre-fetch properties allows the implementation to optimize device access by using bulk operations when available. Pre-fetching more properties than are actually needed may degrade performance.

A volume enumerator generates file path URLs. If you want a volume enumerator to generate file reference URLs, pass the kCFURLEnumeratorGenerateFileReferenceURLs option.

The kCFURLEnumeratorDescendRecursively and kCFURLEnumeratorSkipPackageContents options are ignored by CFURLEnumeratorCreateForMountedVolumes.
*/
CF_EXPORT
CFURLEnumeratorRef CFURLEnumeratorCreateForMountedVolumes( CFAllocatorRef alloc, CFURLEnumeratorOptions option, CFArrayRef propertyKeys ) CF_AVAILABLE(10_6, 4_0);


/* CFURLEnumeratorResult - Results for CFURLEnumeratorGetNextURL */
typedef CF_ENUM(CFIndex, CFURLEnumeratorResult) {
    kCFURLEnumeratorSuccess = 1,                    /* The enumeration was successful. The url output parameter is valid. */
    kCFURLEnumeratorEnd = 2,                        /* The enumeration is complete. */
    kCFURLEnumeratorError = 3,			    /* An error occured during enumeration. The retained error output parameter describes the error. */
    kCFURLEnumeratorDirectoryPostOrderSuccess = 4,  /* The enumeration was successful. The url output parameter is for a directory after all of directory's descendants have been visited (post-order). This result will only be returned for directories when both the kCFURLEnumeratorDescendRecursively and kCFURLEnumeratorIncludeDirectoriesPostOrder options are passed to CFURLEnumeratorCreateForDirectoryURL. */
};

/* CFURLEnumeratorGetNextURL - Advances the enumerator. If kCFURLEnumeratorSuccess is returned, the url output parameter returns the next URL found. If kCFURLEnumeratorError is returned, an error has occured and the error output parameter describes the error. If kCFURLEnumeratorEnd, the enumeration is finished.

The url output parameter, if returned, is not retained. The error output parameter, if returned, is retained and must be released.
*/
CF_EXPORT
CFURLEnumeratorResult CFURLEnumeratorGetNextURL( CFURLEnumeratorRef enumerator, CFURLRef *url, CFErrorRef *error ) CF_AVAILABLE(10_6, 4_0);


/* CFURLEnumeratorSkipDescendents - Tells a recursive CFURLEnumerator not to descend into the directory of the last CFURLRef returned by CFURLEnumeratorGetNextURL.

Calls to CFURLEnumeratorSkipDescendents are ignored if:
    * CFURLEnumeratorGetNextURL has never been called with the CFURLEnumerator.
    * The last CFURL returned by CFURLEnumeratorGetNextURL is not a directory.
    * The CFURLEnumerator was not created with CFURLEnumeratorCreateForDirectoryURL using the kCFURLEnumeratorDescendRecursively option.
*/
CF_EXPORT
void CFURLEnumeratorSkipDescendents( CFURLEnumeratorRef enumerator ) CF_AVAILABLE(10_6, 4_0);


/* CFURLEnumeratorGetDescendentLevel - Returns the number of levels a directory enumerator has descended down into the directory hierarchy from the starting directory. The children of the starting directory are at level 1. Each time a recursive enumerator descends into a subdirectory, it adds one to the descendent level. It then subtracts one from the level when it finishes a subdirectory and continues enumerating the parent directory.
*/
CF_EXPORT
CFIndex CFURLEnumeratorGetDescendentLevel( CFURLEnumeratorRef enumerator ) CF_AVAILABLE(10_6, 4_0);


/* CFURLEnumeratorGetSourceDidChange is deprecated. If your program is interested in directory hierarchy changes during enumeration (and most programs are not interested), you should use the File System Events API.
 
 CFURLEnumeratorGetSourceDidChange does nothing and always returns false.
 */
CF_EXPORT
Boolean CFURLEnumeratorGetSourceDidChange( CFURLEnumeratorRef enumerator ) CF_DEPRECATED(10_6, 10_7, 4_0, 5_0);


CF_EXTERN_C_END

#endif /* ! __COREFOUNDATION_CFURLENUMERATOR__ */

#endif

