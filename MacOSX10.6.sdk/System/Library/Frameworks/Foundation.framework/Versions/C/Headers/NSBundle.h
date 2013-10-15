/*	NSBundle.h
	Copyright (c) 1994-2009, Apple Inc.  All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSDictionary, NSString, NSURL, NSError;

/* Because NSBundle caches allocated instances, subclasses should be prepared
   to receive an already initialized object back from [super initWithPath:] */
@interface NSBundle : NSObject {
@private
    NSUInteger	_flags;
    id		        _cfBundle;
    NSUInteger	_refCount;
    Class		_principalClass;
    id                  _tmp1;
    id                  _tmp2;
    void		*_reserved1;
    void		*_reserved0;
}

/* Methods for creating or retrieving bundle instances. */
+ (NSBundle *)mainBundle;
+ (NSBundle *)bundleWithPath:(NSString *)path;
- (id)initWithPath:(NSString *)path;

+ (NSBundle *)bundleWithURL:(NSURL *)url AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (id)initWithURL:(NSURL *)url AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

+ (NSBundle *)bundleForClass:(Class)aClass;
+ (NSBundle *)bundleWithIdentifier:(NSString *)identifier;

+ (NSArray *)allBundles;
+ (NSArray *)allFrameworks;

/* Methods for loading and unloading bundles. */
- (BOOL)load;
- (BOOL)isLoaded AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
- (BOOL)unload AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

- (BOOL)preflightAndReturnError:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (BOOL)loadAndReturnError:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Methods for locating various components of a bundle. */
- (NSURL *)bundleURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSURL *)resourceURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSURL *)executableURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSURL *)URLForAuxiliaryExecutable:(NSString *)executableName AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (NSURL *)privateFrameworksURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSURL *)sharedFrameworksURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSURL *)sharedSupportURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSURL *)builtInPlugInsURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (NSString *)bundlePath;
- (NSString *)resourcePath;
- (NSString *)executablePath;
- (NSString *)pathForAuxiliaryExecutable:(NSString *)executableName;

- (NSString *)privateFrameworksPath;
- (NSString *)sharedFrameworksPath;
- (NSString *)sharedSupportPath;
- (NSString *)builtInPlugInsPath;

/* Methods for locating bundle resources.  Instance methods locate resources in the bundle indicated by the receiver; class methods take an argument pointing to a bundle on disk.  In the class methods, bundleURL is a URL pointing to the location of a bundle on disk, and may not be nil; bundlePath is the path equivalent of bundleURL, an absolute path pointing to the location of a bundle on disk.  By contrast, subpath is a relative path to a subdirectory inside the relevant global or localized resource directory, and should be nil if the resource file in question is not in a subdirectory.  Where appropriate, localizationName is the name of a .lproj directory in the bundle, minus the .lproj extension; passing nil for localizationName retrieves only global resources, whereas using a method without this argument retrieves both global and localized resources (using the standard localization search algorithm).  */

+ (NSURL *)URLForResource:(NSString *)name withExtension:(NSString *)ext subdirectory:(NSString *)subpath inBundleWithURL:(NSURL *)bundleURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (NSArray *)URLsForResourcesWithExtension:(NSString *)ext subdirectory:(NSString *)subpath inBundleWithURL:(NSURL *)bundleURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (NSURL *)URLForResource:(NSString *)name withExtension:(NSString *)ext AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSURL *)URLForResource:(NSString *)name withExtension:(NSString *)ext subdirectory:(NSString *)subpath AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSURL *)URLForResource:(NSString *)name withExtension:(NSString *)ext subdirectory:(NSString *)subpath localization:(NSString *)localizationName AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (NSArray *)URLsForResourcesWithExtension:(NSString *)ext subdirectory:(NSString *)subpath AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSArray *)URLsForResourcesWithExtension:(NSString *)ext subdirectory:(NSString *)subpath localization:(NSString *)localizationName AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

+ (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)bundlePath;
+ (NSArray *)pathsForResourcesOfType:(NSString *)ext inDirectory:(NSString *)bundlePath;

- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext;
- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)subpath;
- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)subpath forLocalization:(NSString *)localizationName;

- (NSArray *)pathsForResourcesOfType:(NSString *)ext inDirectory:(NSString *)subpath;
- (NSArray *)pathsForResourcesOfType:(NSString *)ext inDirectory:(NSString *)subpath forLocalization:(NSString *)localizationName;

/* Method for retrieving localized strings. */
- (NSString *)localizedStringForKey:(NSString *)key value:(NSString *)value table:(NSString *)tableName;

/* Methods for obtaining various information about a bundle. */
- (NSString *)bundleIdentifier;
- (NSDictionary *)infoDictionary;
- (NSDictionary *)localizedInfoDictionary AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
- (id)objectForInfoDictionaryKey:(NSString *)key AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
- (Class)classNamed:(NSString *)className;
- (Class)principalClass;

/* Methods for dealing with localizations. */
- (NSArray *)localizations;
- (NSArray *)preferredLocalizations;
- (NSString *)developmentLocalization AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

+ (NSArray *)preferredLocalizationsFromArray:(NSArray *)localizationsArray;
+ (NSArray *)preferredLocalizationsFromArray:(NSArray *)localizationsArray forPreferences:(NSArray *)preferencesArray AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Method for determining executable architectures. */
enum {
    NSBundleExecutableArchitectureI386      = 0x00000007,
    NSBundleExecutableArchitecturePPC       = 0x00000012,
    NSBundleExecutableArchitectureX86_64    = 0x01000007,
    NSBundleExecutableArchitecturePPC64     = 0x01000012
};

- (NSArray *)executableArchitectures AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@end

#define NSLocalizedString(key, comment) \
	    [[NSBundle mainBundle] localizedStringForKey:(key) value:@"" table:nil]
#define NSLocalizedStringFromTable(key, tbl, comment) \
	    [[NSBundle mainBundle] localizedStringForKey:(key) value:@"" table:(tbl)]
#define NSLocalizedStringFromTableInBundle(key, tbl, bundle, comment) \
	    [bundle localizedStringForKey:(key) value:@"" table:(tbl)]
#define NSLocalizedStringWithDefaultValue(key, tbl, bundle, val, comment) \
	    [bundle localizedStringForKey:(key) value:(val) table:(tbl)]

FOUNDATION_EXPORT NSString * const NSBundleDidLoadNotification;
FOUNDATION_EXPORT NSString * const NSLoadedClasses;	// notification key

