/*	NSBundle.h
	Copyright (c) 1994-2013, Apple Inc.  All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSDictionary, NSString, NSURL, NSError;

/* Because NSBundle caches allocated instances, subclasses should be prepared
   to receive an already initialized object back from [super initWithPath:] */
@interface NSBundle : NSObject {
@private
    NSUInteger		_flags;
    id		        _cfBundle;
    NSUInteger		_reserved2;
    Class		_principalClass;
    id                  _initialPath;
    id                  _resolvedPath;
    id                  _reserved3;
    id                  _lock;
}

/* Methods for creating or retrieving bundle instances. */
+ (NSBundle *)mainBundle;
+ (NSBundle *)bundleWithPath:(NSString *)path;
- (id)initWithPath:(NSString *)path;

+ (NSBundle *)bundleWithURL:(NSURL *)url NS_AVAILABLE(10_6, 4_0);
- (id)initWithURL:(NSURL *)url NS_AVAILABLE(10_6, 4_0);

+ (NSBundle *)bundleForClass:(Class)aClass;
+ (NSBundle *)bundleWithIdentifier:(NSString *)identifier;

+ (NSArray *)allBundles;
+ (NSArray *)allFrameworks;

/* Methods for loading and unloading bundles. */
- (BOOL)load;
- (BOOL)isLoaded;
- (BOOL)unload;

- (BOOL)preflightAndReturnError:(NSError **)error NS_AVAILABLE(10_5, 2_0);
- (BOOL)loadAndReturnError:(NSError **)error NS_AVAILABLE(10_5, 2_0);

/* Methods for locating various components of a bundle. */
- (NSURL *)bundleURL NS_AVAILABLE(10_6, 4_0);
- (NSURL *)resourceURL NS_AVAILABLE(10_6, 4_0);
- (NSURL *)executableURL NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLForAuxiliaryExecutable:(NSString *)executableName NS_AVAILABLE(10_6, 4_0);

- (NSURL *)privateFrameworksURL NS_AVAILABLE(10_6, 4_0);
- (NSURL *)sharedFrameworksURL NS_AVAILABLE(10_6, 4_0);
- (NSURL *)sharedSupportURL NS_AVAILABLE(10_6, 4_0);
- (NSURL *)builtInPlugInsURL NS_AVAILABLE(10_6, 4_0);

- (NSURL *)appStoreReceiptURL NS_AVAILABLE(10_7, 7_0);

- (NSString *)bundlePath;
- (NSString *)resourcePath;
- (NSString *)executablePath;
- (NSString *)pathForAuxiliaryExecutable:(NSString *)executableName;

- (NSString *)privateFrameworksPath;
- (NSString *)sharedFrameworksPath;
- (NSString *)sharedSupportPath;
- (NSString *)builtInPlugInsPath;

/* Methods for locating bundle resources.  Instance methods locate resources in the bundle indicated by the receiver; class methods take an argument pointing to a bundle on disk.  In the class methods, bundleURL is a URL pointing to the location of a bundle on disk, and may not be nil; bundlePath is the path equivalent of bundleURL, an absolute path pointing to the location of a bundle on disk.  By contrast, subpath is a relative path to a subdirectory inside the relevant global or localized resource directory, and should be nil if the resource file in question is not in a subdirectory.  Where appropriate, localizationName is the name of a .lproj directory in the bundle, minus the .lproj extension; passing nil for localizationName retrieves only global resources, whereas using a method without this argument retrieves both global and localized resources (using the standard localization search algorithm).  */

+ (NSURL *)URLForResource:(NSString *)name withExtension:(NSString *)ext subdirectory:(NSString *)subpath inBundleWithURL:(NSURL *)bundleURL NS_AVAILABLE(10_6, 4_0);
+ (NSArray *)URLsForResourcesWithExtension:(NSString *)ext subdirectory:(NSString *)subpath inBundleWithURL:(NSURL *)bundleURL NS_AVAILABLE(10_6, 4_0);

- (NSURL *)URLForResource:(NSString *)name withExtension:(NSString *)ext NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLForResource:(NSString *)name withExtension:(NSString *)ext subdirectory:(NSString *)subpath NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLForResource:(NSString *)name withExtension:(NSString *)ext subdirectory:(NSString *)subpath localization:(NSString *)localizationName NS_AVAILABLE(10_6, 4_0);

- (NSArray *)URLsForResourcesWithExtension:(NSString *)ext subdirectory:(NSString *)subpath NS_AVAILABLE(10_6, 4_0);
- (NSArray *)URLsForResourcesWithExtension:(NSString *)ext subdirectory:(NSString *)subpath localization:(NSString *)localizationName NS_AVAILABLE(10_6, 4_0);

+ (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)bundlePath;
+ (NSArray *)pathsForResourcesOfType:(NSString *)ext inDirectory:(NSString *)bundlePath;

- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext;
- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)subpath;
- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)subpath forLocalization:(NSString *)localizationName;

- (NSArray *)pathsForResourcesOfType:(NSString *)ext inDirectory:(NSString *)subpath;
- (NSArray *)pathsForResourcesOfType:(NSString *)ext inDirectory:(NSString *)subpath forLocalization:(NSString *)localizationName;

/* Method for retrieving localized strings. */
- (NSString *)localizedStringForKey:(NSString *)key value:(NSString *)value table:(NSString *)tableName NS_FORMAT_ARGUMENT(1);

/* Methods for obtaining various information about a bundle. */
- (NSString *)bundleIdentifier;
- (NSDictionary *)infoDictionary;
- (NSDictionary *)localizedInfoDictionary;
- (id)objectForInfoDictionaryKey:(NSString *)key;
- (Class)classNamed:(NSString *)className;
- (Class)principalClass;

/* Methods for dealing with localizations. */
- (NSArray *)preferredLocalizations;	// a subset of this bundle's localizations, re-ordered into the preferred order for this process's current execution environment; the main bundle's preferred localizations indicate the language (of text) the user is most likely seeing in the UI

- (NSArray *)localizations;		// list of language names this bundle appears to be localized to
- (NSString *)developmentLocalization;

+ (NSArray *)preferredLocalizationsFromArray:(NSArray *)localizationsArray;
+ (NSArray *)preferredLocalizationsFromArray:(NSArray *)localizationsArray forPreferences:(NSArray *)preferencesArray;

/* Method for determining executable architectures. */
enum {
    NSBundleExecutableArchitectureI386      = 0x00000007,
    NSBundleExecutableArchitecturePPC       = 0x00000012,
    NSBundleExecutableArchitectureX86_64    = 0x01000007,
    NSBundleExecutableArchitecturePPC64     = 0x01000012
};

- (NSArray *)executableArchitectures NS_AVAILABLE(10_5, 2_0);

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

