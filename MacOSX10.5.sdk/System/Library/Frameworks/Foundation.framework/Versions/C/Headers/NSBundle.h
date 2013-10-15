/*	NSBundle.h
	Copyright (c) 1994-2007, Apple Inc.  All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSDictionary, NSString, NSError;

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

+ (NSBundle *)mainBundle;
+ (NSBundle *)bundleWithPath:(NSString *)path;
- (id)initWithPath:(NSString *)path;

+ (NSBundle *)bundleForClass:(Class)aClass;
+ (NSBundle *)bundleWithIdentifier:(NSString *)identifier;

+ (NSArray *)allBundles;
+ (NSArray *)allFrameworks;

- (BOOL)load;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (BOOL)isLoaded;
- (BOOL)unload;
#endif /* MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED */

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (BOOL)preflightAndReturnError:(NSError **)error;
- (BOOL)loadAndReturnError:(NSError **)error;
#endif /* MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED */

- (NSString *)bundlePath;
- (NSString *)resourcePath;
- (NSString *)executablePath;
- (NSString *)pathForAuxiliaryExecutable:(NSString *)executableName;

- (NSString *)privateFrameworksPath;
- (NSString *)sharedFrameworksPath;
- (NSString *)sharedSupportPath;
- (NSString *)builtInPlugInsPath;

- (NSString *)bundleIdentifier;

- (Class)classNamed:(NSString *)className;

- (Class)principalClass;

/* In the following methods, bundlePath is an absolute path to a bundle, and may not be nil; subpath is a relative path to a subdirectory inside the relevant global or localized resource directory, and should be nil if the resource file in question is not in a subdirectory. */
+ (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)bundlePath;
- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext;
- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)subpath;
- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)subpath forLocalization:(NSString *)localizationName;

+ (NSArray *)pathsForResourcesOfType:(NSString *)ext inDirectory:(NSString *)bundlePath;
- (NSArray *)pathsForResourcesOfType:(NSString *)ext inDirectory:(NSString *)subpath;
- (NSArray *)pathsForResourcesOfType:(NSString *)ext inDirectory:(NSString *)subpath forLocalization:(NSString *)localizationName;

- (NSString *)localizedStringForKey:(NSString *)key value:(NSString *)value table:(NSString *)tableName;

- (NSDictionary *)infoDictionary;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (NSDictionary *)localizedInfoDictionary;
- (id)objectForInfoDictionaryKey:(NSString *)key;
#endif /* MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED */

- (NSArray *)localizations;
- (NSArray *)preferredLocalizations;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (NSString *)developmentLocalization;
#endif /* MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED */

+ (NSArray *)preferredLocalizationsFromArray:(NSArray *)localizationsArray;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
+ (NSArray *)preferredLocalizationsFromArray:(NSArray *)localizationsArray forPreferences:(NSArray *)preferencesArray;
#endif /* MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED */

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED
enum {
    NSBundleExecutableArchitectureI386      = 0x00000007,
    NSBundleExecutableArchitecturePPC       = 0x00000012,
    NSBundleExecutableArchitectureX86_64    = 0x01000007,
    NSBundleExecutableArchitecturePPC64     = 0x01000012
};

- (NSArray *)executableArchitectures;
#endif /* MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED */

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

