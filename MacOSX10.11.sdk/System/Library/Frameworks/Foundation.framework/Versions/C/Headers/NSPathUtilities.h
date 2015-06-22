/*	NSPathUtilities.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSString (NSStringPathExtensions)

+ (NSString *)pathWithComponents:(NSArray<NSString *> *)components;
@property (readonly, copy) NSArray<NSString *> *pathComponents;

@property (getter=isAbsolutePath, readonly) BOOL absolutePath;

@property (readonly, copy) NSString *lastPathComponent;
@property (readonly, copy) NSString *stringByDeletingLastPathComponent;
- (NSString *)stringByAppendingPathComponent:(NSString *)str;

@property (readonly, copy) NSString *pathExtension;
@property (readonly, copy) NSString *stringByDeletingPathExtension;
- (nullable NSString *)stringByAppendingPathExtension:(NSString *)str;

@property (readonly, copy) NSString *stringByAbbreviatingWithTildeInPath;
@property (readonly, copy) NSString *stringByExpandingTildeInPath;

@property (readonly, copy) NSString *stringByStandardizingPath;

@property (readonly, copy) NSString *stringByResolvingSymlinksInPath;

- (NSArray<NSString *> *)stringsByAppendingPaths:(NSArray<NSString *> *)paths;

- (NSUInteger)completePathIntoString:(NSString * __nonnull * __nullable)outputName caseSensitive:(BOOL)flag matchesIntoArray:(NSArray<NSString *> * __nonnull * __nullable)outputArray filterTypes:(nullable NSArray<NSString *> *)filterTypes;

@property (readonly) __strong const char *fileSystemRepresentation NS_RETURNS_INNER_POINTER;
- (BOOL)getFileSystemRepresentation:(char *)cname maxLength:(NSUInteger)max;

@end

@interface NSArray<ObjectType> (NSArrayPathExtensions)

- (NSArray<NSString *> *)pathsMatchingExtensions:(NSArray<NSString *> *)filterTypes;

@end

FOUNDATION_EXPORT NSString *NSUserName(void);
FOUNDATION_EXPORT NSString *NSFullUserName(void);

FOUNDATION_EXPORT NSString *NSHomeDirectory(void);
FOUNDATION_EXPORT NSString * __nullable NSHomeDirectoryForUser(NSString * __nullable userName);

FOUNDATION_EXPORT NSString *NSTemporaryDirectory(void);

FOUNDATION_EXPORT NSString *NSOpenStepRootDirectory(void);

typedef NS_ENUM(NSUInteger, NSSearchPathDirectory) {
    NSApplicationDirectory = 1,             // supported applications (Applications)
    NSDemoApplicationDirectory,             // unsupported applications, demonstration versions (Demos)
    NSDeveloperApplicationDirectory,        // developer applications (Developer/Applications). DEPRECATED - there is no one single Developer directory.
    NSAdminApplicationDirectory,            // system and network administration applications (Administration)
    NSLibraryDirectory,                     // various documentation, support, and configuration files, resources (Library)
    NSDeveloperDirectory,                   // developer resources (Developer) DEPRECATED - there is no one single Developer directory.
    NSUserDirectory,                        // user home directories (Users)
    NSDocumentationDirectory,               // documentation (Documentation)
    NSDocumentDirectory,                    // documents (Documents)
    NSCoreServiceDirectory,                 // location of CoreServices directory (System/Library/CoreServices)
    NSAutosavedInformationDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 11,   // location of autosaved documents (Documents/Autosaved)
    NSDesktopDirectory = 12,                // location of user's desktop
    NSCachesDirectory = 13,                 // location of discardable cache files (Library/Caches)
    NSApplicationSupportDirectory = 14,     // location of application support files (plug-ins, etc) (Library/Application Support)
    NSDownloadsDirectory NS_ENUM_AVAILABLE(10_5, 2_0) = 15,              // location of the user's "Downloads" directory
    NSInputMethodsDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 16,           // input methods (Library/Input Methods)
    NSMoviesDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 17,                 // location of user's Movies directory (~/Movies)
    NSMusicDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 18,                  // location of user's Music directory (~/Music)
    NSPicturesDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 19,               // location of user's Pictures directory (~/Pictures)
    NSPrinterDescriptionDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 20,     // location of system's PPDs directory (Library/Printers/PPDs)
    NSSharedPublicDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 21,           // location of user's Public sharing directory (~/Public)
    NSPreferencePanesDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 22,        // location of the PreferencePanes directory for use with System Preferences (Library/PreferencePanes)
    NSApplicationScriptsDirectory NS_ENUM_AVAILABLE(10_8, NA) = 23,      // location of the user scripts folder for the calling application (~/Library/Application Scripts/code-signing-id)
    NSItemReplacementDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 99,	    // For use with NSFileManager's URLForDirectory:inDomain:appropriateForURL:create:error:
    NSAllApplicationsDirectory = 100,       // all directories where applications can occur
    NSAllLibrariesDirectory = 101,          // all directories where resources can occur
    NSTrashDirectory NS_ENUM_AVAILABLE(10_8, NA) = 102                   // location of Trash directory

};

typedef NS_OPTIONS(NSUInteger, NSSearchPathDomainMask) {
    NSUserDomainMask = 1,       // user's home directory --- place to install user's personal items (~)
    NSLocalDomainMask = 2,      // local to the current machine --- place to install items available to everyone on this machine (/Library)
    NSNetworkDomainMask = 4,    // publically available location in the local area network --- place to install items available on the network (/Network)
    NSSystemDomainMask = 8,     // provided by Apple, unmodifiable (/System)
    NSAllDomainsMask = 0x0ffff  // all domains: all of the above and future items
};

FOUNDATION_EXPORT NSArray<NSString *> *NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory directory, NSSearchPathDomainMask domainMask, BOOL expandTilde);

NS_ASSUME_NONNULL_END
