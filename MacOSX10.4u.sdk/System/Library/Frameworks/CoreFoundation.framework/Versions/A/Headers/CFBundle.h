/*	CFBundle.h
	Copyright (c) 1999-2005, Apple, Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFBUNDLE__)
#define __COREFOUNDATION_CFBUNDLE__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFURL.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct __CFBundle *CFBundleRef;
typedef struct __CFBundle *CFPlugInRef;

/* ===================== Standard Info.plist keys ===================== */
CF_EXPORT
const CFStringRef kCFBundleInfoDictionaryVersionKey;
    /* The version of the Info.plist format */
CF_EXPORT
const CFStringRef kCFBundleExecutableKey;
    /* The name of the executable in this bundle (if any) */
CF_EXPORT
const CFStringRef kCFBundleIdentifierKey;
    /* The bundle identifier (for CFBundleGetBundleWithIdentifier()) */
CF_EXPORT
const CFStringRef kCFBundleVersionKey;
    /* The version number of the bundle.  For Mac OS 9 style version numbers (for example "2.5.3d5"), clients can use CFBundleGetVersionNumber() instead of accessing this key directly since that function will properly convert the version string into its compact integer representation. */
CF_EXPORT
const CFStringRef kCFBundleDevelopmentRegionKey;
    /* The name of the development language of the bundle. */
CF_EXPORT
const CFStringRef kCFBundleNameKey;
    /* The human-readable name of the bundle.  This key is often found in the InfoPlist.strings since it is usually localized. */
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
CF_EXPORT
const CFStringRef kCFBundleLocalizationsKey;
    /* Allows an unbundled application that handles localization itself to specify which localizations it has available. */
#endif

/* ===================== Finding Bundles ===================== */

CF_EXPORT
CFBundleRef CFBundleGetMainBundle(void);

CF_EXPORT
CFBundleRef CFBundleGetBundleWithIdentifier(CFStringRef bundleID);
    /* A bundle can name itself by providing a key in the info dictionary. */
    /* This facility is meant to allow bundle-writers to get hold of their */
    /* bundle from their code without having to know where it was on the disk. */
    /* This is meant to be a replacement mechanism for +bundleForClass: users. */
    /* Note that this does not search for bundles on the disk; it will locate */
    /* only bundles already loaded or otherwise known to the current process. */

CF_EXPORT
CFArrayRef CFBundleGetAllBundles(void);
    /* This is potentially expensive.  Use with care. */

/* ===================== Creating Bundles ===================== */

CF_EXPORT
UInt32 CFBundleGetTypeID(void);

CF_EXPORT
CFBundleRef CFBundleCreate(CFAllocatorRef allocator, CFURLRef bundleURL);
    /* Might return an existing instance with the ref-count bumped. */

CF_EXPORT
CFArrayRef CFBundleCreateBundlesFromDirectory(CFAllocatorRef allocator, CFURLRef directoryURL, CFStringRef bundleType);
    /* Create instances for all bundles in the given directory matching the given */
    /* type (or all of them if bundleType is NULL) */

/* ==================== Basic Bundle Info ==================== */

CF_EXPORT
CFURLRef CFBundleCopyBundleURL(CFBundleRef bundle);

CF_EXPORT
CFTypeRef CFBundleGetValueForInfoDictionaryKey(CFBundleRef bundle, CFStringRef key);
    /* Returns a localized value if available, otherwise the global value. */
    /* This is the recommended function for examining the info dictionary. */

CF_EXPORT
CFDictionaryRef CFBundleGetInfoDictionary(CFBundleRef bundle);
    /* This is the global info dictionary.  Note that CFBundle may add */
    /* extra keys to the dictionary for its own use. */

CF_EXPORT
CFDictionaryRef CFBundleGetLocalInfoDictionary(CFBundleRef bundle);
    /* This is the localized info dictionary. */

CF_EXPORT
void CFBundleGetPackageInfo(CFBundleRef bundle, UInt32 *packageType, UInt32 *packageCreator);

CF_EXPORT
CFStringRef CFBundleGetIdentifier(CFBundleRef bundle);

CF_EXPORT
UInt32 CFBundleGetVersionNumber(CFBundleRef bundle);

CF_EXPORT
CFStringRef CFBundleGetDevelopmentRegion(CFBundleRef bundle);

CF_EXPORT
CFURLRef CFBundleCopySupportFilesDirectoryURL(CFBundleRef bundle);

CF_EXPORT
CFURLRef CFBundleCopyResourcesDirectoryURL(CFBundleRef bundle);

CF_EXPORT
CFURLRef CFBundleCopyPrivateFrameworksURL(CFBundleRef bundle);

CF_EXPORT
CFURLRef CFBundleCopySharedFrameworksURL(CFBundleRef bundle);

CF_EXPORT
CFURLRef CFBundleCopySharedSupportURL(CFBundleRef bundle);

CF_EXPORT
CFURLRef CFBundleCopyBuiltInPlugInsURL(CFBundleRef bundle);

/* ------------- Basic Bundle Info without a CFBundle instance ------------- */
/* This API is provided to enable developers to retrieve basic information */
/* about a bundle without having to create an instance of CFBundle. */
/* Because of caching behavior when a CFBundle instance exists, it will be faster */
/* to actually create a CFBundle if you need to retrieve multiple pieces of info. */
CF_EXPORT
CFDictionaryRef CFBundleCopyInfoDictionaryInDirectory(CFURLRef bundleURL);

CF_EXPORT
Boolean CFBundleGetPackageInfoInDirectory(CFURLRef url, UInt32 *packageType, UInt32 *packageCreator);
    
/* ==================== Resource Handling API ==================== */

CF_EXPORT
CFURLRef CFBundleCopyResourceURL(CFBundleRef bundle, CFStringRef resourceName, CFStringRef resourceType, CFStringRef subDirName);

CF_EXPORT
CFArrayRef CFBundleCopyResourceURLsOfType(CFBundleRef bundle, CFStringRef resourceType, CFStringRef subDirName);

CF_EXPORT
CFStringRef CFBundleCopyLocalizedString(CFBundleRef bundle, CFStringRef key, CFStringRef value, CFStringRef tableName);

#define CFCopyLocalizedString(key, comment) \
            CFBundleCopyLocalizedString(CFBundleGetMainBundle(), (key), (key), NULL)
#define CFCopyLocalizedStringFromTable(key, tbl, comment) \
            CFBundleCopyLocalizedString(CFBundleGetMainBundle(), (key), (key), (tbl))
#define CFCopyLocalizedStringFromTableInBundle(key, tbl, bundle, comment) \
            CFBundleCopyLocalizedString((bundle), (key), (key), (tbl))
#define CFCopyLocalizedStringWithDefaultValue(key, tbl, bundle, value, comment) \
            CFBundleCopyLocalizedString((bundle), (key), (value), (tbl))

/* ------------- Resource Handling without a CFBundle instance ------------- */
/* This API is provided to enable developers to use the CFBundle resource */
/* searching policy without having to create an instance of CFBundle. */
/* Because of caching behavior when a CFBundle instance exists, it will be faster */
/* to actually create a CFBundle if you need to access several resources. */

CF_EXPORT
CFURLRef CFBundleCopyResourceURLInDirectory(CFURLRef bundleURL, CFStringRef resourceName, CFStringRef resourceType, CFStringRef subDirName);

CF_EXPORT
CFArrayRef CFBundleCopyResourceURLsOfTypeInDirectory(CFURLRef bundleURL, CFStringRef resourceType, CFStringRef subDirName);

/* =========== Localization-specific Resource Handling API =========== */
/* This API allows finer-grained control over specific localizations,  */
/* as distinguished from the above API, which always uses the user's   */
/* preferred localizations for the bundle in the current app context.  */

CF_EXPORT
CFArrayRef CFBundleCopyBundleLocalizations(CFBundleRef bundle);
    /* Lists the localizations that a bundle contains.  */

CF_EXPORT
CFArrayRef CFBundleCopyPreferredLocalizationsFromArray(CFArrayRef locArray);
    /* Given an array of possible localizations, returns the one or more */
    /* of them that CFBundle would use in the current application context. */
    /* To determine the localizations that would be used for a particular */
    /* bundle in the current application context, apply this function to the */
    /* result of CFBundleCopyBundleLocalizations.  */

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
CF_EXPORT
CFArrayRef CFBundleCopyLocalizationsForPreferences(CFArrayRef locArray, CFArrayRef prefArray);
    /* Given an array of possible localizations, returns the one or more of */
    /* them that CFBundle would use, without reference to the current application */
    /* context, if the user's preferred localizations were given by prefArray. */
    /* If prefArray is NULL, the current user's actual preferred localizations will */
    /* be used. This is not the same as CFBundleCopyPreferredLocalizationsFromArray, */
    /* because that function takes the current application context into account. */
    /* To determine the localizations that another application would use, apply */
    /* this function to the result of CFBundleCopyBundleLocalizations.  */
#endif

CF_EXPORT
CFURLRef CFBundleCopyResourceURLForLocalization(CFBundleRef bundle, CFStringRef resourceName, CFStringRef resourceType, CFStringRef subDirName, CFStringRef localizationName);

CF_EXPORT
CFArrayRef CFBundleCopyResourceURLsOfTypeForLocalization(CFBundleRef bundle, CFStringRef resourceType, CFStringRef subDirName, CFStringRef localizationName);

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
/* =================== Unbundled application info ===================== */
/* This API is provided to enable developers to retrieve bundle-related */
/* information about an application that may be bundled or unbundled.   */
CF_EXPORT
CFDictionaryRef CFBundleCopyInfoDictionaryForURL(CFURLRef url);
    /* For a directory URL, this is equivalent to CFBundleCopyInfoDictionaryInDirectory. */
    /* For a plain file URL representing an unbundled application, this will attempt to read */
    /* an info dictionary either from the (__TEXT, __info_plist) section (for a Mach-o file) */
    /* or from a 'plst' resource.  */

CF_EXPORT
CFArrayRef CFBundleCopyLocalizationsForURL(CFURLRef url);
    /* For a directory URL, this is equivalent to calling CFBundleCopyBundleLocalizations */
    /* on the corresponding bundle.  For a plain file URL representing an unbundled application, */
    /* this will attempt to determine its localizations using the CFBundleLocalizations and */
    /* CFBundleDevelopmentRegion keys in the dictionary returned by CFBundleCopyInfoDictionaryForURL,*/
    /* or a 'vers' resource if those are not present.  */
#endif

/* ==================== Primitive Code Loading API ==================== */
/* This API abstracts the various different executable formats supported on */
/* various platforms.  It can load DYLD, CFM, or DLL shared libraries (on their */
/* appropriate platforms) and gives a uniform API for looking up functions. */
/* Note that Cocoa-based bundles containing Objective-C or Java code must */
/* be loaded with NSBundle, not CFBundle.  Once they are loaded, however, */
/* either CFBundle or NSBundle can be used. */

CF_EXPORT
CFURLRef CFBundleCopyExecutableURL(CFBundleRef bundle);

CF_EXPORT
Boolean CFBundleIsExecutableLoaded(CFBundleRef bundle);

CF_EXPORT
Boolean CFBundleLoadExecutable(CFBundleRef bundle);

CF_EXPORT
void CFBundleUnloadExecutable(CFBundleRef bundle);

CF_EXPORT
void *CFBundleGetFunctionPointerForName(CFBundleRef bundle, CFStringRef functionName);

CF_EXPORT
void CFBundleGetFunctionPointersForNames(CFBundleRef bundle, CFArrayRef functionNames, void *ftbl[]);

CF_EXPORT
void *CFBundleGetDataPointerForName(CFBundleRef bundle, CFStringRef symbolName);

CF_EXPORT
void CFBundleGetDataPointersForNames(CFBundleRef bundle, CFArrayRef symbolNames, void *stbl[]);

CF_EXPORT
CFURLRef CFBundleCopyAuxiliaryExecutableURL(CFBundleRef bundle, CFStringRef executableName);
    /* This function can be used to find executables other than your main */
    /* executable.  This is useful, for instance, for applications that have */
    /* some command line tool that is packaged with and used by the application. */
    /* The tool can be packaged in the various platform executable directories */
    /* in the bundle and can be located with this function.  This allows an */
    /* app to ship versions of the tool for each platform as it does for the */
    /* main app executable. */

/* ==================== Getting a bundle's plugIn ==================== */

CF_EXPORT
CFPlugInRef CFBundleGetPlugIn(CFBundleRef bundle);

/* ==================== Resource Manager-Related API ==================== */

CF_EXPORT
short CFBundleOpenBundleResourceMap(CFBundleRef bundle);
   /* This function opens the non-localized and the localized resource files */
   /* (if any) for the bundle, creates and makes current a single read-only */
   /* resource map combining both, and returns a reference number for it. */
   /* If it is called multiple times, it opens the files multiple times, */
   /* and returns distinct reference numbers.  */

CF_EXPORT
SInt32 CFBundleOpenBundleResourceFiles(CFBundleRef bundle, short *refNum, short *localizedRefNum);
   /* Similar to CFBundleOpenBundleResourceMap, except that it creates two */
   /* separate resource maps and returns reference numbers for both. */

CF_EXPORT
void CFBundleCloseBundleResourceMap(CFBundleRef bundle, short refNum);

#if defined(__cplusplus)
}
#endif

#endif /* ! __COREFOUNDATION_CFBUNDLE__ */

