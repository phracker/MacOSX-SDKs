/*	NSFileManager.h
	Copyright 1994-2001, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSUtilities.h>
#import <CoreFoundation/CFBase.h>

@class NSString, NSDate, NSDirectoryEnumerator, NSDictionary, NSArray, NSData;

// Version number where NSFileManager can copy/move/enumerate resources forks correctly
#define NSFoundationVersionWithFileManagerResourceForkSupport 412

@interface NSFileManager : NSObject

+ (NSFileManager *)defaultManager;

- (NSString *)currentDirectoryPath;
- (BOOL)changeCurrentDirectoryPath:(NSString *)path;

- (NSDictionary *)fileAttributesAtPath:(NSString *)path traverseLink:(BOOL)yorn;

- (BOOL)changeFileAttributes:(NSDictionary *)attributes atPath:(NSString *)path;

- (BOOL)fileExistsAtPath:(NSString *)path;
- (BOOL)fileExistsAtPath:(NSString *)path isDirectory:(BOOL *)isDirectory;
- (BOOL)isReadableFileAtPath:(NSString *)path;
- (BOOL)isWritableFileAtPath:(NSString *)path;
- (BOOL)isExecutableFileAtPath:(NSString *)path;
- (BOOL)isDeletableFileAtPath:(NSString *)path;

- (NSString *)displayNameAtPath:(NSString *)path;

- (BOOL)contentsEqualAtPath:(NSString *)path1 andPath:(NSString *)path2;
- (BOOL)linkPath:(NSString *)src toPath:(NSString *)dest handler:handler;
- (BOOL)copyPath:(NSString *)src toPath:(NSString *)dest handler:handler;

- (BOOL)movePath:(NSString *)src toPath:(NSString *)dest handler:handler;	

- (BOOL)removeFileAtPath:(NSString *)path handler:handler;

- (NSArray *)directoryContentsAtPath:(NSString *)path;
- (NSDirectoryEnumerator *)enumeratorAtPath:(NSString *)path;
- (NSArray *)subpathsAtPath:(NSString *)path;

- (BOOL)createDirectoryAtPath:(NSString *)path attributes:(NSDictionary *)attributes;

- (NSData *)contentsAtPath:(NSString *)path;
- (BOOL)createFileAtPath:(NSString *)path contents:(NSData *)data attributes:(NSDictionary *)attr;

- (NSString *)pathContentOfSymbolicLinkAtPath:(NSString *)path;
- (BOOL)createSymbolicLinkAtPath:(NSString *)path pathContent:(NSString *)otherpath;

- (NSDictionary *)fileSystemAttributesAtPath:(NSString *)path;

- (const char *)fileSystemRepresentationWithPath:(NSString *)path;
- (NSString *)stringWithFileSystemRepresentation:(const char *)str length:(unsigned)len;

@end

@interface NSObject (NSCopyLinkMoveHandler)
- (BOOL)fileManager:(NSFileManager *)fm shouldProceedAfterError:(NSDictionary *)errorInfo;
- (void)fileManager:(NSFileManager *)fm willProcessPath:(NSString *)path;
@end

@interface NSDirectoryEnumerator : NSEnumerator
- (NSDictionary *)fileAttributes;
- (NSDictionary *)directoryAttributes;
- (void)skipDescendents;
@end

/**************** File Attributes ****************/

FOUNDATION_EXPORT NSString * const NSFileType;
FOUNDATION_EXPORT NSString 	* const NSFileTypeDirectory;
FOUNDATION_EXPORT NSString 	* const NSFileTypeRegular;
FOUNDATION_EXPORT NSString 	* const NSFileTypeSymbolicLink;
FOUNDATION_EXPORT NSString 	* const NSFileTypeSocket;
FOUNDATION_EXPORT NSString 	* const NSFileTypeCharacterSpecial;
FOUNDATION_EXPORT NSString 	* const NSFileTypeBlockSpecial;
FOUNDATION_EXPORT NSString 	* const NSFileTypeUnknown;
FOUNDATION_EXPORT NSString	* const NSFileSize;
FOUNDATION_EXPORT NSString * const NSFileModificationDate;
FOUNDATION_EXPORT NSString * const NSFileReferenceCount;
FOUNDATION_EXPORT NSString * const NSFileDeviceIdentifier;
FOUNDATION_EXPORT NSString * const NSFileOwnerAccountName;
FOUNDATION_EXPORT NSString * const NSFileGroupOwnerAccountName;
FOUNDATION_EXPORT NSString * const NSFilePosixPermissions;
FOUNDATION_EXPORT NSString * const NSFileSystemNumber;
FOUNDATION_EXPORT NSString * const NSFileSystemFileNumber;
FOUNDATION_EXPORT NSString * const NSFileExtensionHidden;
FOUNDATION_EXPORT NSString * const NSFileHFSCreatorCode;
FOUNDATION_EXPORT NSString * const NSFileHFSTypeCode;

/* File System attributes */
FOUNDATION_EXPORT NSString * const NSFileSystemSize;
FOUNDATION_EXPORT NSString * const NSFileSystemFreeSize;
FOUNDATION_EXPORT NSString * const NSFileSystemNodes;
FOUNDATION_EXPORT NSString * const NSFileSystemFreeNodes;

@interface NSDictionary (NSFileAttributes)

- (unsigned long long)fileSize;
- (NSDate *)fileModificationDate;
- (NSString *)fileType;
- (unsigned long)filePosixPermissions;
- (NSString *)fileOwnerAccountName;
- (NSString *)fileGroupOwnerAccountName;
#if !defined(__WIN32__)
- (unsigned long)fileSystemNumber;
- (unsigned long)fileSystemFileNumber;
#endif	/* ! __WIN32__ */
- (BOOL)fileExtensionHidden;
- (OSType)fileHFSCreatorCode;
- (OSType)fileHFSTypeCode;

@end

