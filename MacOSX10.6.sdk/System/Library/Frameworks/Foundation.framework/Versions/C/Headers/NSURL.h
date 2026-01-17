/*	NSURL.h
	Copyright (c) 1997-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#if !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#import <Foundation/NSURLHandle.h>
#endif

#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED
enum {
    NSURLBookmarkCreationPreferFileIDResolution = ( 1UL << 8 ),  /* At resolution time, this alias will prefer resolving by the embedded fileID to the path */
    NSURLBookmarkCreationMinimalBookmark = ( 1UL << 9 ), /* Creates a bookmark with "less" information, which may be smaller but still be able to resolve in certain ways */
    NSURLBookmarkCreationSuitableForBookmarkFile = ( 1UL << 10 ),	/* include properties required in Finder alias files in created bookmark */
};

enum {
    NSURLBookmarkResolutionWithoutUI = ( 1UL << 8 ),		/* don't perform any UI during bookmark resolution */
    NSURLBookmarkResolutionWithoutMounting = ( 1UL << 9 ),	/* don't mount a volume during bookmark resolution */
};
#endif

typedef NSUInteger NSURLBookmarkCreationOptions;
typedef NSUInteger NSURLBookmarkResolutionOptions;
typedef NSUInteger NSURLBookmarkFileCreationOptions;

@class NSNumber, NSData, NSDictionary;

// As more schemes are used and understood, strong constants for them will be added here
FOUNDATION_EXPORT NSString *NSURLFileScheme;

#if (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
@interface NSURL: NSObject <NSCoding, NSCopying>
#else
@interface NSURL: NSObject <NSCoding, NSCopying, NSURLHandleClient>
#endif
{
    NSString *_urlString;
    NSURL *_baseURL;
    void *_clients;
    __strong void *_reserved;
}
        
// Convenience initializers
- (id)initWithScheme:(NSString *)scheme host:(NSString *)host path:(NSString *)path; // this call percent-encodes both the host and path, so this cannot be used to set a username/password or port in the hostname part or with a IPv6 '[...]' type address; use initWithString: and construct the string yourself in those cases

- (id)initFileURLWithPath:(NSString *)path isDirectory:(BOOL)isDir AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (id)initFileURLWithPath:(NSString *)path;  // Better to use initFileURLWithPath:isDirectory: if you know if the path is a file vs directory, as it saves an i/o.

+ (id)fileURLWithPath:(NSString *)path isDirectory:(BOOL) isDir AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
+ (id)fileURLWithPath:(NSString *)path; // Better to use fileURLWithPath:isDirectory: if you know if the path is a file vs directory, as it saves an i/o.

// These methods expect their string arguments to contain any percent escape codes that are necessary
- initWithString:(NSString *)URLString;
- initWithString:(NSString *)URLString relativeToURL:(NSURL *)baseURL; // It is an error for URLString to be nil
+ (id)URLWithString:(NSString *)URLString;
+ (id)URLWithString:(NSString *)URLString relativeToURL:(NSURL *)baseURL;

- (NSString *)absoluteString;
- (NSString *)relativeString; // The relative portion of a URL.  If baseURL is nil, or if the receiver is itself absolute, this is the same as absoluteString
- (NSURL *)baseURL; // may be nil.
- (NSURL *)absoluteURL; // if the receiver is itself absolute, this will return self.

// Any URL is composed of these two basic pieces.  The full URL would be the concatenation of [myURL scheme], ':', [myURL resourceSpecifier]
- (NSString *)scheme;
- (NSString *)resourceSpecifier;

/* If the URL conforms to rfc 1808 (the most common form of URL), the following accessors will return the various components; otherwise they return nil.  The litmus test for conformance is as recommended in RFC 1808 - whether the first two characters of resourceSpecifier is @"//".  In all cases, they return the component's value after resolving the receiver against its base URL. */
- (NSString *)host;
- (NSNumber *)port;
- (NSString *)user;
- (NSString *)password;
- (NSString *)path;
- (NSString *)fragment;
- (NSString *)parameterString;
- (NSString *)query;
- (NSString *)relativePath; // The same as path if baseURL is nil

- (BOOL)isFileURL; // Whether the scheme is file:; if [myURL isFileURL] is YES, then [myURL path] is suitable for input into NSFileManager or NSPathUtilities.

- (NSURL *)standardizedURL;


/* Resource access
*/

/* Fetch a resource value, with error reporting. Sets the `value` output argument. The output value may be nil. Returns YES when the value is set. Returns NO when an error occurs and also sets the optional error result.
*/
- (BOOL)getResourceValue:(id *)value forKey:(NSString *)key error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Returns multiple resource values as a dictionary. On error, returns nil and sets the optional error result. When there is no value for a key, the key will be absent in the result dictionary.
*/
- (NSDictionary *)resourceValuesForKeys:(NSArray *)keys error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Setting resource properties: The resource is modified synchronously. Returns YES on success, NO on error. When setting multiple properties, partial failure may occur. Processing stops when any error occurs. The user info dictionary in the error result will contain an array of keys that were not set.
*/
- (BOOL)setResourceValue:(id)value forKey:(NSString *)key error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (BOOL)setResourceValues:(NSDictionary *)keyedValues error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Primitive for checking if the underlying resource exists and is reachable. Returns YES when the resource can be accessed. When the return value is NO, the optional error result indicates the reason for failure. Note: Checking reachability is appropriate when making decisions that do not require other immediate operations on the resource, e.g. periodic maintenance of UI state that depends on the existence of a specific document. When performing operations such as opening a file, it is more efficient to simply try the operation and handle failures. This method is currently applicable only to URLs for file system resources. For other URL types, returns NO.
*/
- (BOOL)checkResourceIsReachableAndReturnError:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Working with file reference URLs
*/

/* Returns YES if the receiver is a file reference URL, a path-independent file URL form. Returns NO for file path URLs or non-file URL schemes.
*/
- (BOOL)isFileReferenceURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* For file URLs, returns a file reference URL, converting if the receiver is file path URL. For other URL schemes, returns nil.
*/
- (NSURL *)fileReferenceURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* For file URLs, returns a file path URL, converting if the receiver is a file reference URL. For other URL schemes, returns nil.
*/
- (NSURL *)filePathURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Working with Boomarks and alias (bookmark) files 
 */

/* Create a NSData containing a externalizable representation from a given url, which can later be resolved or interrogated for properties */
- (NSData *)bookmarkDataWithOptions:(NSURLBookmarkCreationOptions)options includingResourceValuesForKeys:(NSArray *)keys relativeToURL:(NSURL *)relativeURL error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Resolve bookmark data into a url; init and factory methods  */
- (id)initByResolvingBookmarkData:(NSData *)bookmarkData options:(NSURLBookmarkResolutionOptions)options relativeToURL:(NSURL *)relativeURL bookmarkDataIsStale:(BOOL *)isStale error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (id)URLByResolvingBookmarkData:(NSData *)bookmarkData options:(NSURLBookmarkResolutionOptions)options relativeToURL:(NSURL *)relativeURL bookmarkDataIsStale:(BOOL *)isStale error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Property access.  Given a NSData* created with bookmarkDataWithOptions, return a given property or all of the properties in bookmark data */
+ (NSDictionary *)resourceValuesForKeys:(NSArray *)keys fromBookmarkData:(NSData *)bookmarkData AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Create a bookmark file on disk at bookmarkFileURL which can be resolved back to the file system item represented by bookmarkData, using the given options. If relativeToURL is non-NULL, create a relative url. The bookmark data must have been created with the NSURLBookmarkCreationSuitableForBookmarkFile flag or this routine will fail.  If bookmarkFileURL is a directory then the file will be created in that directory with the name of the item represented by the bookmarkData with ".alias" appended.  If bookmarkFileURL is a file url then its extension will be changed to ".alias", if not present.
*/
+ (BOOL)writeBookmarkData:(NSData *) bookmarkData toURL:(NSURL *)bookmarkFileURL options:(NSURLBookmarkFileCreationOptions)options error:(NSError **)error;

/* Given the url of a file which is a Finder "alias" file, return a NSData with the bookmark data from the file.  If bookmarkFileURL points to an alias file created before SnowLeopard which contains Alias Manager information and no bookmark data, then a NSData will be synthesized which contains a approximation of the alias information in a format which can be used to resolve the bookmark.  If an error prevents reading the data or if it is corrupt, NULL will be returned and error will be filled in if errorRef is non-NULL.
*/
+ (NSData *)bookmarkDataWithContentsOfURL:(NSURL *)bookmarkFileURL error:(NSError **)error;

@end

@interface NSString (NSURLUtilities)

/* Adds all percent escapes necessary to convert the receiver in to a legal URL string.  Uses the given encoding to determine the correct percent escapes (returning nil if the given encoding cannot encode a particular character).  See CFURLCreateStringByAddingPercentEscapes in CFURL.h for more complex transformations */
- (NSString *)stringByAddingPercentEscapesUsingEncoding:(NSStringEncoding)enc AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Replaces all percent escapes with the matching characters as determined by the given encoding.  Returns nil if the transformation is not possible (i.e. the percent escapes give a byte sequence not legal in the given encoding).  See CFURLCreateStringByReplacingPercentEscapes in CFURL.h for more complex transformations */
- (NSString *)stringByReplacingPercentEscapesUsingEncoding:(NSStringEncoding)enc AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
// Client informal protocol for use with the deprecated loadResourceDataNotifyingClient: below.  
@interface NSObject(NSURLClient)
- (void)URL:(NSURL *)sender resourceDataDidBecomeAvailable:(NSData *)newBytes DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)URLResourceDidFinishLoading:(NSURL *)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)URLResourceDidCancelLoading:(NSURL *)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)URL:(NSURL *)sender resourceDidFailLoadingWithReason:(NSString *)reason DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
@end

//  This entire protocol is deprecated; use NSURLConnection instead.
@interface NSURL (NSURLLoading)
- (NSData *)resourceDataUsingCache:(BOOL)shouldUseCache DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // Blocks to load the data if necessary.  If shouldUseCache is YES, then if an equivalent URL has already been loaded and cached, its resource data will be returned immediately.  If shouldUseCache is NO, a new load will be started
- (void)loadResourceDataNotifyingClient:(id)client usingCache:(BOOL)shouldUseCache DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // Starts an asynchronous load of the data, registering delegate to receive notification.  Only one such background load can proceed at a time.
- (id)propertyForKey:(NSString *)propertyKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

    // These attempt to write the given arguments for the resource specified by the URL; they return success or failure
- (BOOL)setResourceData:(NSData *)data DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (BOOL)setProperty:(id)property forKey:(NSString *)propertyKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSURLHandle *)URLHandleUsingCache:(BOOL)shouldUseCache DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // Sophisticated clients will want to ask for this, then message the handle directly.  If shouldUseCache is NO, a newly instantiated handle is returned, even if an equivalent URL has been loaded

@end
#endif

@interface NSURL (NSURLPathUtilities)

/* The following methods work on the path portion of a URL in the same manner that the NSPathUtilities methods on NSString do.
*/
+ (NSURL *)fileURLWithPathComponents:(NSArray *)components AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSArray *)pathComponents AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSString *)lastPathComponent AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSString *)pathExtension AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSURL *)URLByAppendingPathComponent:(NSString *)pathComponent AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSURL *)URLByDeletingLastPathComponent AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSURL *)URLByAppendingPathExtension:(NSString *)pathExtension AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSURL *)URLByDeletingPathExtension AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* The following methods work only on `file:` scheme path-based URLs; for file reference URLs or for non-`file:` scheme URLs, these methods return the URL unchanged.
*/
- (NSURL *)URLByStandardizingPath AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSURL *)URLByResolvingSymlinksInPath AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER ;

@end

/*
The File System Resource Keys
    
URLs to file system resources support the properties defined below. Note that not all property values will exist for all file system URLs. For example, if a file is located on a volume that does not support creation dates, it is valid to request the creation date property, but the returned value will be NULL, and no error will be generated.
*/

/* Common Keys - applicable to all file system URLs
*/
FOUNDATION_EXPORT NSString * const NSURLNameKey                        AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Name in the file system; NSString
FOUNDATION_EXPORT NSString * const NSURLLocalizedNameKey               AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Localized or extension-hidden name as displayed to users; NSString
FOUNDATION_EXPORT NSString * const NSURLIsRegularFileKey               AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLIsDirectoryKey                 AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLIsSymbolicLinkKey              AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLIsVolumeKey                    AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Root directory of a volume; boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLIsPackageKey                   AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // A packaged directory; boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLIsSystemImmutableKey           AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLIsUserImmutableKey             AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLIsHiddenKey                    AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Resource is normally not displayed to users; boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLHasHiddenExtensionKey          AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Filename extension is normally removed from the localized name property; boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLCreationDateKey                AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // NSDate or nil on volumes that do not support creation date
FOUNDATION_EXPORT NSString * const NSURLContentAccessDateKey           AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // NSDate or nil on volumes that do not support access date
FOUNDATION_EXPORT NSString * const NSURLContentModificationDateKey     AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // NSDate or nil on volumes that do not support modification date
FOUNDATION_EXPORT NSString * const NSURLAttributeModificationDateKey   AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // NSDate or nil on volumes that do not support attribute modification date
FOUNDATION_EXPORT NSString * const NSURLLinkCountKey                   AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Number of hard links to the resource; NSNumber
FOUNDATION_EXPORT NSString * const NSURLParentDirectoryURLKey          AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Resource parent directory; NSURL or nil if the receiver is the file system root directory
FOUNDATION_EXPORT NSString * const NSURLVolumeURLKey                   AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Volume containing the resource; NSURL
FOUNDATION_EXPORT NSString * const NSURLTypeIdentifierKey              AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Uniform type identifier (UTI) describing the resource; NSString
FOUNDATION_EXPORT NSString * const NSURLLocalizedTypeDescriptionKey    AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Localized type description; NSString
FOUNDATION_EXPORT NSString * const NSURLLabelNumberKey                 AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // NSNumber
FOUNDATION_EXPORT NSString * const NSURLLabelColorKey                  AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // NSColor or nil
FOUNDATION_EXPORT NSString * const NSURLLocalizedLabelKey              AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Localized label text; NSString or nil
FOUNDATION_EXPORT NSString * const NSURLEffectiveIconKey               AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // The icon normally displayed for this resource; NSImage
FOUNDATION_EXPORT NSString * const NSURLCustomIconKey                  AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // The icon image stored with the resource, if any; NSImage or nil if no custom icon is assigned

/* File Properties 
*/
FOUNDATION_EXPORT NSString * const NSURLFileSizeKey                    AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // File size in bytes; NSNumber
FOUNDATION_EXPORT NSString * const NSURLFileAllocatedSizeKey           AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Total size allocated on disk for the file (number of blocks times block size); NSNumber
FOUNDATION_EXPORT NSString * const NSURLIsAliasFileKey		       AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // true if the item is an alias file, false otherwise ; boolean NSNumber

/* Volume Properties

As a convenience, volume properties can be requested from any file system URL. The value returned will reflect the property value for the volume on which the resource is located.
*/
FOUNDATION_EXPORT NSString * const NSURLVolumeLocalizedFormatDescriptionKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Descriptive volume format name; NSString
FOUNDATION_EXPORT NSString * const NSURLVolumeTotalCapacityKey              AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Total volume capacity in bytes; NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeAvailableCapacityKey          AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Bytes free; NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeResourceCountKey              AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Total number of resources on the volume; NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsPersistentIDsKey      AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsSymbolicLinksKey      AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsHardLinksKey          AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsJournalingKey         AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeIsJournalingKey               AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsSparseFilesKey        AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsZeroRunsKey           AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsCaseSensitiveNamesKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsCasePreservedNamesKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // boolean NSNumber

