/*	NSBundle.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSDictionary, NSString;

/* Because NSBundle caches allocated instances, subclasses should be prepared
   to receive an already initialized object back from [super initWithPath:] */
@interface NSBundle : NSObject {
@private
    unsigned int	_flags;
    id		        _cfBundle;
    void		*_reserved5;
    Class		_principalClass;
    void		*_tmp1;
    void		*_tmp2;
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
#endif

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
#endif

- (NSArray *)localizations;
- (NSArray *)preferredLocalizations;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (NSString *)developmentLocalization;
#endif

+ (NSArray *)preferredLocalizationsFromArray:(NSArray *)localizationsArray;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
+ (NSArray *)preferredLocalizationsFromArray:(NSArray *)localizationsArray forPreferences:(NSArray *)preferencesArray;
#endif

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

