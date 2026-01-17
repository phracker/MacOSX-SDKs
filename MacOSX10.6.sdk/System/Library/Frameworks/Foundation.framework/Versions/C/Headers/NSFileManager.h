/*	NSFileManager.h
	Copyright (c) 1994-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSPathUtilities.h>
#import <CoreFoundation/CFBase.h>

@class NSArray, NSData, NSDate, NSDirectoryEnumerator, NSError, NSNumber;

/* Version number where NSFileManager can copy/move/enumerate resources forks correctly. 
*/
#define NSFoundationVersionWithFileManagerResourceForkSupport 412

#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED
enum {
    /* The mounted volume enumeration will skip hidden volumes.
     */
    NSVolumeEnumerationSkipHiddenVolumes = 1UL << 1,
    
    /* The mounted volume enumeration will produce file reference URLs rather than path-based URLs.
     */
    NSVolumeEnumerationProduceFileReferenceURLs = 1UL << 2
};
#endif
typedef NSUInteger NSVolumeEnumerationOptions;

#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED
enum {
    /* NSDirectoryEnumerationSkipsSubdirectoryDescendants causes the NSDirectoryEnumerator to perform a shallow enumeration and not descend into directories it encounters.
     */
    NSDirectoryEnumerationSkipsSubdirectoryDescendants = 1UL << 0,
    
    /* NSDirectoryEnumerationSkipsPackageDescendants will cause the NSDirectoryEnumerator to not descend into packages.
     */
    NSDirectoryEnumerationSkipsPackageDescendants      = 1UL << 1,
    
    /* NSDirectoryEnumerationSkipsHiddenFiles causes the NSDirectoryEnumerator to not enumerate hidden files.
     */
    NSDirectoryEnumerationSkipsHiddenFiles             = 1UL << 2
};
#endif
typedef NSUInteger NSDirectoryEnumerationOptions;

#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED
enum {
    /* NSFileManagerItemReplacementUsingNewMetadataOnly causes -replaceItemAtURL:withItemAtURL:backupItemName:options:resultingItemURL:error: to use metadata from the new item only and not to attempt to preserve metadata from the original item.
     */
    NSFileManagerItemReplacementUsingNewMetadataOnly = 1UL << 0,
    
    /* NSFileManagerItemReplacementWithoutDeletingBackupItem causes -replaceItemAtURL:withItemAtURL:backupItemName:options:resultingItemURL:error: to leave the backup item in place after a successful replacement. The default behavior is to remove the item.
     */
     NSFileManagerItemReplacementWithoutDeletingBackupItem = 1UL << 1
};
#endif
typedef NSUInteger NSFileManagerItemReplacementOptions;

@interface NSFileManager : NSObject

/* Returns the default singleton instance.
*/
+ (NSFileManager *)defaultManager;

/* -mountedVolumeURLsIncludingResourceValuesForKeys:options: returns an NSArray of NSURLs locating the mounted volumes available on the computer. The property keys that can be requested are available in <Foundation/NSURL.h>.
 */
- (NSArray *)mountedVolumeURLsIncludingResourceValuesForKeys:(NSArray *)propertyKeys options:(NSVolumeEnumerationOptions)options AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* -contentsOfDirectoryAtURL:includingPropertiesForKeys:options:error: returns an NSArray of NSURLs identifying the the directory entries. If this method returns nil, an NSError will be returned by reference in the 'error' parameter. If the directory contains no entries, this method will return the empty array. When an array is specified for the 'keys' parameter, the specified property values will be pre-fetched and cached with each enumerated URL.
 
    This method always does a shallow enumeration of the specified directory (i.e. it always acts as if NSDirectoryEnumerationSkipsSubdirectoryDescendants has been specified). If you need to perform a deep enumeration, use +[NSFileManager enumeratorAtURL:includingPropertiesForKeys:options:errorHandler:].
 
    If you wish to only receive the URLs and no other attributes, then pass '0' for 'options' and an empty NSArray ('[NSArray array]') for 'keys'. If you wish to have the property caches of the vended URLs pre-populated with a default set of attributes, then pass '0' for 'options' and 'nil' for 'keys'.
 */
- (NSArray *)contentsOfDirectoryAtURL:(NSURL *)url includingPropertiesForKeys:(NSArray *)keys options:(NSDirectoryEnumerationOptions)mask error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* -URLsForDirectory:inDomains: is analogous to NSSearchPathForDirectoriesInDomains(), but returns an array of NSURL instances for use with URL-taking APIs. This API is suitable when you need to search for a file or files which may live in one of a variety of locations in the domains specified.
 */
- (NSArray *)URLsForDirectory:(NSSearchPathDirectory)directory inDomains:(NSSearchPathDomainMask)domainMask AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* -URLForDirectory:inDomain:appropriateForURL:create:error: is a URL-based replacement for FSFindFolder(). It allows for the specification and (optional) creation of a specific directory for a particular purpose (e.g. the replacement of a particular item on disk, or a particular Library directory.
 
    You may pass only one of the values from the NSSearchPathDomainMask enumeration, and you may not pass NSAllDomainsMask.
 */
- (NSURL *)URLForDirectory:(NSSearchPathDirectory)directory inDomain:(NSSearchPathDomainMask)domain appropriateForURL:(NSURL *)url create:(BOOL)shouldCreate error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED

/* Instances of NSFileManager may now have delegates. Each instance has one delegate, and the delegate is not retained. In versions of Mac OS X prior to 10.5, the behavior of calling [[NSFileManager alloc] init] was undefined. In Mac OS X 10.5 "Leopard" and later, calling [[NSFileManager alloc] init] returns a new instance of an NSFileManager.
 */
- (void)setDelegate:(id)delegate;
- (id)delegate;

/* setAttributes:ofItemAtPath:error: returns YES when the attributes specified in the 'attributes' dictionary are set successfully on the item specified by 'path'. If this method returns NO, a presentable NSError will be provided by-reference in the 'error' parameter. If no error is required, you may pass 'nil' for the error.
 
    This method replaces changeFileAttributes:atPath:.
 */
- (BOOL)setAttributes:(NSDictionary *)attributes ofItemAtPath:(NSString *)path error:(NSError **)error;

/* createDirectoryAtPath:withIntermediateDirectories:attributes:error: creates a directory at the specified path. If you pass 'NO' for createIntermediates, the directory must not exist at the time this call is made. Passing 'YES' for 'createIntermediates' will create any necessary intermediate directories. This method returns YES if all directories specified in 'path' were created and attributes were set. Directories are created with attributes specified by the dictionary passed to 'attributes'. If no dictionary is supplied, directories are created according to the umask of the process. This method returns NO if a failure occurs at any stage of the operation. If an error parameter was provided, a presentable NSError will be returned by reference.
 
    This method replaces createDirectoryAtPath:attributes:
 */
- (BOOL)createDirectoryAtPath:(NSString *)path withIntermediateDirectories:(BOOL)createIntermediates attributes:(NSDictionary *)attributes error:(NSError **)error;

/* contentsOfDirectoryAtPath:error: returns an NSArray of NSStrings representing the filenames of the items in the directory. If this method returns 'nil', an NSError will be returned by reference in the 'error' parameter. If the directory contains no items, this method will return the empty array.
 
    This method replaces directoryContentsAtPath:
 */
- (NSArray *)contentsOfDirectoryAtPath:(NSString *)path error:(NSError **)error;

/* subpathsOfDirectoryAtPath:error: returns an NSArray of NSStrings represeting the filenames of the items in the specified directory and all its subdirectories recursively. If this method returns 'nil', an NSError will be returned by reference in the 'error' parameter. If the directory contains no items, this method will return the empty array.
 
    This method replaces subpathsAtPath:
 */
- (NSArray *)subpathsOfDirectoryAtPath:(NSString *)path error:(NSError **)error;

/* attributesOfItemAtPath:error: returns an NSDictionary of key/value pairs containing the attributes of the item (file, directory, symlink, etc.) at the path in question. If this method returns 'nil', an NSError will be returned by reference in the 'error' parameter. This method does not traverse a terminal symlink.
 
    This method replaces fileAttributesAtPath:traverseLink:.
 */
- (NSDictionary *)attributesOfItemAtPath:(NSString *)path error:(NSError **)error;

/* attributesOfFileSystemForPath:error: returns an NSDictionary of key/value pairs containing the attributes of the filesystem containing the provided path. If this method returns 'nil', an NSError will be returned by reference in the 'error' parameter. This method does not traverse a terminal symlink.
 
    This method replaces fileSystemAttributesAtPath:.
 */
- (NSDictionary *)attributesOfFileSystemForPath:(NSString *)path error:(NSError **)error;

/* createSymbolicLinkAtPath:withDestination:error: returns YES if the symbolic link that point at 'destPath' was able to be created at the location specified by 'path'. If this method returns NO, the link was unable to be created and an NSError will be returned by reference in the 'error' parameter. This method does not traverse a terminal symlink.
 
    This method replaces createSymbolicLinkAtPath:pathContent:
 */
- (BOOL)createSymbolicLinkAtPath:(NSString *)path withDestinationPath:(NSString *)destPath error:(NSError **)error;

/* destinationOfSymbolicLinkAtPath:error: returns an NSString containing the path of the item pointed at by the symlink specified by 'path'. If this method returns 'nil', an NSError will be returned by reference in the 'error' parameter.
 
    This method replaces pathContentOfSymbolicLinkAtPath:
 */
- (NSString *)destinationOfSymbolicLinkAtPath:(NSString *)path error:(NSError **)error;

/* These methods replace their non-error returning counterparts below. See the NSFileManagerFileOperationAdditions category below for methods that are dispatched to the NSFileManager instance's delegate.
 */
- (BOOL)copyItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath error:(NSError **)error;
- (BOOL)moveItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath error:(NSError **)error;
- (BOOL)linkItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath error:(NSError **)error;
- (BOOL)removeItemAtPath:(NSString *)path error:(NSError **)error;

#endif

/* These methods are URL-taking equivalents of the four methods above. Their delegate methods are defined in the NSFileManagerFileOperationAdditions category below.
 */
- (BOOL)copyItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (BOOL)moveItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (BOOL)linkItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (BOOL)removeItemAtURL:(NSURL *)URL error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* The following methods are deprecated on Mac OS X 10.5. Their URL-based and/or error-returning replacements are listed above.
 */
- (NSDictionary *)fileAttributesAtPath:(NSString *)path traverseLink:(BOOL)yorn DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (BOOL)changeFileAttributes:(NSDictionary *)attributes atPath:(NSString *)path DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSArray *)directoryContentsAtPath:(NSString *)path DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSDictionary *)fileSystemAttributesAtPath:(NSString *)path DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSString *)pathContentOfSymbolicLinkAtPath:(NSString *)path DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (BOOL)createSymbolicLinkAtPath:(NSString *)path pathContent:(NSString *)otherpath DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (BOOL)createDirectoryAtPath:(NSString *)path attributes:(NSDictionary *)attributes DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
- (BOOL)linkPath:(NSString *)src toPath:(NSString *)dest handler:(id)handler DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (BOOL)copyPath:(NSString *)src toPath:(NSString *)dest handler:(id)handler DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (BOOL)movePath:(NSString *)src toPath:(NSString *)dest handler:(id)handler DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (BOOL)removeFileAtPath:(NSString *)path handler:(id)handler DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
#endif

/* Process working directory management. Despite the fact that these are instance methods on NSFileManager, these methods report and change (respectively) the working directory for the entire process. Developers are cautioned that doing so is fraught with peril.
 */
- (NSString *)currentDirectoryPath;
- (BOOL)changeCurrentDirectoryPath:(NSString *)path;

/* The following methods are of limited utility. Attempting to predicate behavior based on the current state of the filesystem or a particular file on the filesystem is encouraging odd behavior in the face of filesystem race conditions. It's far better to attempt an operation (like loading a file or creating a directory) and handle the error gracefully than it is to try to figure out ahead of time whether the operation will succeed.
 */
- (BOOL)fileExistsAtPath:(NSString *)path;
- (BOOL)fileExistsAtPath:(NSString *)path isDirectory:(BOOL *)isDirectory;
- (BOOL)isReadableFileAtPath:(NSString *)path;
- (BOOL)isWritableFileAtPath:(NSString *)path;
- (BOOL)isExecutableFileAtPath:(NSString *)path;
- (BOOL)isDeletableFileAtPath:(NSString *)path;

/* -contentsEqualAtPath:andPath: does not take into account data stored in the resource fork or filesystem extended attributes.
 */
- (BOOL)contentsEqualAtPath:(NSString *)path1 andPath:(NSString *)path2;

/* displayNameAtPath: returns an NSString suitable for presentation to the user. For directories which have localization information, this will return the appropriate localized string. This string is not suitable for passing to anything that must interact with the filesystem.
 */
- (NSString *)displayNameAtPath:(NSString *)path;

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
/* componentsToDisplayForPath: returns an NSArray of display names for the path provided. Localization will occur as in displayNameAtPath: above. This array cannot and should not be reassembled into an usable filesystem path for any kind of access.
 */
- (NSArray *)componentsToDisplayForPath:(NSString *)path;
#endif

/* enumeratorAtPath: returns an NSDirectoryEnumerator rooted at the provided path. If the enumerator cannot be created, this returns NULL. Because NSDirectoryEnumerator is a subclass of NSEnumerator, the returned object can be used in the for...in construct.
 */
- (NSDirectoryEnumerator *)enumeratorAtPath:(NSString *)path;

#if NS_BLOCKS_AVAILABLE
/* enumeratorAtURL:includingPropertiesForKeys:options:errorHandler: returns an NSDirectoryEnumerator rooted at the provided directory URL. The NSDirectoryEnumerator returns NSURLs from the -nextObject method. The optional 'includingPropertiesForKeys' parameter indicates which resource properties should be pre-fetched and cached with each enumerated URL. The optional 'errorHandler' block argument is invoked when an error occurs. Parameters to the block are the URL on which an error occurred and the error. When the error handler returns YES, enumeration continues if possible. Enumeration stops immediately when the error handler returns NO.

    If you wish to only receive the URLs and no other attributes, then pass '0' for 'options' and an empty NSArray ('[NSArray array]') for 'keys'. If you wish to have the property caches of the vended URLs pre-populated with a default set of attributes, then pass '0' for 'options' and 'nil' for 'keys'.
 */
- (NSDirectoryEnumerator *)enumeratorAtURL:(NSURL *)url includingPropertiesForKeys:(NSArray *)keys options:(NSDirectoryEnumerationOptions)mask errorHandler:(BOOL (^)(NSURL *url, NSError *error))handler AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
#endif

/* subpathsAtPath: returns an NSArray of all contents and subpaths recursively from the provided path. This may be very expensive to compute for deep filesystem hierarchies, and should probably be avoided.
 */
- (NSArray *)subpathsAtPath:(NSString *)path;

/* These methods are provided here for compatibility. The corresponding methods on NSData which return NSErrors should be regarded as the primary method of creating a file from an NSData or retrieving the contents of a file as an NSData.
 */
- (NSData *)contentsAtPath:(NSString *)path;
- (BOOL)createFileAtPath:(NSString *)path contents:(NSData *)data attributes:(NSDictionary *)attr;

/* fileSystemRepresentationWithPath: returns an array of characters suitable for passing to lower-level POSIX style APIs. The string is provided in the representation most appropriate for the filesystem in question.
 */
- (__strong const char *)fileSystemRepresentationWithPath:(NSString *)path;

/* stringWithFileSystemRepresentation:length: returns an NSString created from an array of bytes that are in the filesystem representation.
 */
- (NSString *)stringWithFileSystemRepresentation:(const char *)str length:(NSUInteger)len;

/* -replaceItemAtURL:withItemAtURL:backupItemName:options:resultingItemURL:error: is for developers who wish to perform a safe-save without using the full NSDocument machinery that is available in the AppKit.
 
    The `originalItemURL` is the item being replaced.
    `newItemURL` is the item which will replace the original item. This item should be placed in a temporary directory as provided by the OS, or in a uniquely named directory placed in the same directory as the original item if the temporary directory is not available.
    If `backupItemName` is provided, that name will be used to create a backup of the original item. The backup is placed in the same directory as the original item. If an error occurs during the creation of the backup item, the operation will fail. If there is already an item with the same name as the backup item, that item will be removed. The backup item will be removed in the event of success unless the `NSFileManagerItemReplacementWithoutDeletingBackupItem` option is provided in `options`.
    For `options`, pass `0` to get the default behavior, which uses only the metadata from the new item while adjusting some properties using values from the original item. Pass `NSFileManagerItemReplacementUsingNewMetadataOnly` in order to use all possible metadata from the new item.
 */
- (BOOL)replaceItemAtURL:(NSURL *)originalItemURL withItemAtURL:(NSURL *)newItemURL backupItemName:(NSString *)backupItemName options:(NSFileManagerItemReplacementOptions)options resultingItemURL:(NSURL **)resultingURL error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

/* These delegate methods are for the use of the deprecated handler-taking methods on NSFileManager for copying, moving, linking or deleting files.
 */
@interface NSObject (NSCopyLinkMoveHandler)
- (BOOL)fileManager:(NSFileManager *)fm shouldProceedAfterError:(NSDictionary *)errorInfo DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)fileManager:(NSFileManager *)fm willProcessPath:(NSString *)path DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
@end

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED

@interface NSObject (NSFileManagerFileOperationAdditions)

/* fileManager:shouldCopyItemAtPath:toPath: gives the delegate an opportunity to filter the resulting copy. Returning YES from this method will allow the copy to happen. Returning NO from this method causes the item in question to be skipped. If the item skipped was a directory, no children of that directory will be copied, nor will the delegate be notified of those children.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldCopyItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldCopyItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* fileManager:shouldProceedAfterError:copyingItemAtPath:toPath: gives the delegate an opportunity to recover from or continue copying after an error. If an error occurs, the error object will contain an NSError indicating the problem. The source path and destination paths are also provided. If this method returns YES, the NSFileManager instance will continue as if the error had not occurred. If this method returns NO, the NSFileManager instance will stop copying, return NO from copyItemAtPath:toPath:error: and the error will be provied there.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error copyingItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error copyingItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* fileManager:shouldMoveItemAtPath:toPath: gives the delegate an opportunity to not move the item at the specified path. If the source path and the destination path are not on the same device, a copy is performed to the destination path and the original is removed. If the copy does not succeed, an error is returned and the incomplete copy is removed, leaving the original in place.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldMoveItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldMoveItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* fileManager:shouldProceedAfterError:movingItemAtPath:toPath: functions much like fileManager:shouldProceedAfterError:copyingItemAtPath:toPath: above. The delegate has the opportunity to remedy the error condition and allow the move to continue.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error movingItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error movingItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* fileManager:shouldLinkItemAtPath:toPath: acts as the other "should" methods, but this applies to the file manager creating hard links to the files in question.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldLinkItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldLinkItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* fileManager:shouldProceedAfterError:linkingItemAtPath:toPath: allows the delegate an opportunity to remedy the error which occurred in linking srcPath to dstPath. If the delegate returns YES from this method, the linking will continue. If the delegate returns NO from this method, the linking operation will stop and the error will be returned via linkItemAtPath:toPath:error:.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error linkingItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error linkingItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* fileManager:shouldRemoveItemAtPath: allows the delegate the opportunity to not remove the item at path. If the delegate returns YES from this method, the NSFileManager instance will attempt to remove the item. If the delegate returns NO from this method, the remove skips the item. If the item is a directory, no children of that item will be visited.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldRemoveItemAtPath:(NSString *)path;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldRemoveItemAtURL:(NSURL *)URL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* fileManager:shouldProceedAfterError:removingItemAtPath: allows the delegate an opportunity to remedy the error which occurred in removing the item at the path provided. If the delegate returns YES from this method, the removal operation will continue. If the delegate returns NO from this method, the removal operation will stop and the error will be returned via linkItemAtPath:toPath:error:.

    If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
 */
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error removingItemAtPath:(NSString *)path;
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error removingItemAtURL:(NSURL *)URL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

#endif

@interface NSDirectoryEnumerator : NSEnumerator

/* For NSDirectoryEnumerators created with -enumeratorAtPath:, the -fileAttributes and -directoryAttributes methods return an NSDictionary containing the keys listed below. For NSDirectoryEnumerators created with -enumeratorAtURL:includingPropertiesForKeys:options:errorHandler:, these two methods return nil.
 */
- (NSDictionary *)fileAttributes;
- (NSDictionary *)directoryAttributes;

- (void)skipDescendents;

/* This method returns the number of levels deep the current object is in the directory hierarchy being enumerated. The directory passed to -enumeratorAtURL:includingPropertiesForKeys:options:errorHandler: is considered to be level 0.
 */
- (NSUInteger)level AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* This method is spelled correctly.
 */
- (void)skipDescendants AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

FOUNDATION_EXPORT NSString * const NSFileType;
FOUNDATION_EXPORT NSString 	* const NSFileTypeDirectory;
FOUNDATION_EXPORT NSString 	* const NSFileTypeRegular;
FOUNDATION_EXPORT NSString 	* const NSFileTypeSymbolicLink;
FOUNDATION_EXPORT NSString 	* const NSFileTypeSocket;
FOUNDATION_EXPORT NSString 	* const NSFileTypeCharacterSpecial;
FOUNDATION_EXPORT NSString 	* const NSFileTypeBlockSpecial;
FOUNDATION_EXPORT NSString 	* const NSFileTypeUnknown;
FOUNDATION_EXPORT NSString * const NSFileSize;
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
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
FOUNDATION_EXPORT NSString * const NSFileImmutable;
FOUNDATION_EXPORT NSString * const NSFileAppendOnly;
FOUNDATION_EXPORT NSString * const NSFileCreationDate;
FOUNDATION_EXPORT NSString * const NSFileOwnerAccountID;
FOUNDATION_EXPORT NSString * const NSFileGroupOwnerAccountID;
#endif
#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED
FOUNDATION_EXPORT NSString * const NSFileBusy;
#endif

FOUNDATION_EXPORT NSString * const NSFileSystemSize;
FOUNDATION_EXPORT NSString * const NSFileSystemFreeSize;
FOUNDATION_EXPORT NSString * const NSFileSystemNodes;
FOUNDATION_EXPORT NSString * const NSFileSystemFreeNodes;

@interface NSDictionary (NSFileAttributes)

- (unsigned long long)fileSize;
- (NSDate *)fileModificationDate;
- (NSString *)fileType;
- (NSUInteger)filePosixPermissions;
- (NSString *)fileOwnerAccountName;
- (NSString *)fileGroupOwnerAccountName;
- (NSInteger)fileSystemNumber;
- (NSUInteger)fileSystemFileNumber;
- (BOOL)fileExtensionHidden;
- (OSType)fileHFSCreatorCode;
- (OSType)fileHFSTypeCode;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (BOOL)fileIsImmutable;
- (BOOL)fileIsAppendOnly;
- (NSDate *)fileCreationDate;
- (NSNumber *)fileOwnerAccountID;
- (NSNumber *)fileGroupOwnerAccountID;
#endif
@end

