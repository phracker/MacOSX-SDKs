/*	NSPathUtilities.h
	Copyright (c) 1994-2003, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

@interface NSString (NSStringPathExtensions)

+ (NSString *)pathWithComponents:(NSArray *)components;
- (NSArray *)pathComponents;

- (BOOL)isAbsolutePath;

- (NSString *)lastPathComponent;
- (NSString *)stringByDeletingLastPathComponent;
- (NSString *)stringByAppendingPathComponent:(NSString *)str;

- (NSString *)pathExtension;
- (NSString *)stringByDeletingPathExtension;
- (NSString *)stringByAppendingPathExtension:(NSString *)str;

- (NSString *)stringByAbbreviatingWithTildeInPath;
- (NSString *)stringByExpandingTildeInPath;

- (NSString *)stringByStandardizingPath;

- (NSString *)stringByResolvingSymlinksInPath;

- (NSArray *)stringsByAppendingPaths:(NSArray *)paths;

- (unsigned)completePathIntoString:(NSString **)outputName caseSensitive:(BOOL)flag matchesIntoArray:(NSArray **)outputArray filterTypes:(NSArray *)filterTypes;

- (const char *)fileSystemRepresentation;
- (BOOL)getFileSystemRepresentation:(char *)cname maxLength:(unsigned)max;

@end

@interface NSArray (NSArrayPathExtensions)

- (NSArray *)pathsMatchingExtensions:(NSArray *)filterTypes;

@end

FOUNDATION_EXPORT NSString *NSUserName(void);
FOUNDATION_EXPORT NSString *NSFullUserName(void);

FOUNDATION_EXPORT NSString *NSHomeDirectory(void);
FOUNDATION_EXPORT NSString *NSHomeDirectoryForUser(NSString *userName);

FOUNDATION_EXPORT NSString *NSTemporaryDirectory(void);

FOUNDATION_EXPORT NSString *NSOpenStepRootDirectory(void);

typedef enum {
    NSApplicationDirectory = 1,		// supported applications (Applications)
    NSDemoApplicationDirectory,		// unsupported applications, demonstration versions (Demos)
    NSDeveloperApplicationDirectory,	// developer applications (Developer/Applications)
    NSAdminApplicationDirectory,	// system and network administration applications (Administration)
    NSLibraryDirectory, 		// various user-visible documentation, support, and configuration files, resources (Library)
    NSDeveloperDirectory,		// developer resources (Developer)
    NSUserDirectory,			// user home directories (Users)
    NSDocumentationDirectory,		// documentation (Documentation)
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
    NSDocumentDirectory,		// documents (Documents)
#endif
    NSAllApplicationsDirectory = 100,	// all directories where applications can occur
    NSAllLibrariesDirectory = 101	// all directories where resources can occur
} NSSearchPathDirectory;

typedef enum {
    NSUserDomainMask = 1,	// user's home directory --- place to install user's personal items (~)
    NSLocalDomainMask = 2,	// local to the current machine --- place to install items available to everyone on this machine (/Library)
    NSNetworkDomainMask = 4, 	// publically available location in the local area network --- place to install items available on the network (/Network)
    NSSystemDomainMask = 8,	// provided by Apple, unmodifiable (/System)
    NSAllDomainsMask = 0x0ffff	// all domains: all of the above and future items
} NSSearchPathDomainMask;

FOUNDATION_EXPORT NSArray *NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory directory, NSSearchPathDomainMask domainMask, BOOL expandTilde);


