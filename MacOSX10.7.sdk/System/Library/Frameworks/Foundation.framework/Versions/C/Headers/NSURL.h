/*	NSURL.h
	Copyright (c) 1997-2011, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#if !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#import <Foundation/NSURLHandle.h>
#endif

#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
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

- (id)initFileURLWithPath:(NSString *)path isDirectory:(BOOL)isDir NS_AVAILABLE(10_5, 2_0);
- (id)initFileURLWithPath:(NSString *)path;  // Better to use initFileURLWithPath:isDirectory: if you know if the path is a file vs directory, as it saves an i/o.

+ (id)fileURLWithPath:(NSString *)path isDirectory:(BOOL) isDir NS_AVAILABLE(10_5, 2_0);
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
- (BOOL)getResourceValue:(out id *)value forKey:(NSString *)key error:(out NSError **)error NS_AVAILABLE(10_6, 4_0);


/* Returns multiple resource values as a dictionary. On error, returns nil and sets the optional error result. When there is no value for a key, the key will be absent in the result dictionary.
*/
- (NSDictionary *)resourceValuesForKeys:(NSArray *)keys error:(NSError **)error NS_AVAILABLE(10_6, 4_0);


/* Setting resource properties: The resource is modified synchronously. Returns YES on success, NO on error. When setting multiple properties, partial failure may occur. Processing stops when any error occurs. The user info dictionary in the error result will contain an array of keys that were not set with the dictionary key NSURLKeysOfUnsetValuesKey.
*/
- (BOOL)setResourceValue:(id)value forKey:(NSString *)key error:(NSError **)error NS_AVAILABLE(10_6, 4_0);
- (BOOL)setResourceValues:(NSDictionary *)keyedValues error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

FOUNDATION_EXPORT NSString * const NSURLKeysOfUnsetValuesKey NS_AVAILABLE(10_7, 5_0); // If setResourceValues returns an error, this is key in the error's userInfo dictionary to the array of keys of unset values.

/* Primitive for checking if the underlying resource exists and is reachable. Returns YES when the resource can be accessed. When the return value is NO, the optional error result indicates the reason for failure. Note: Checking reachability is appropriate when making decisions that do not require other immediate operations on the resource, e.g. periodic maintenance of UI state that depends on the existence of a specific document. When performing operations such as opening a file, it is more efficient to simply try the operation and handle failures. This method is currently applicable only to URLs for file system resources. For other URL types, returns NO.
*/
- (BOOL)checkResourceIsReachableAndReturnError:(NSError **)error NS_AVAILABLE(10_6, 4_0);


/* Working with file reference URLs
*/

/* Returns YES if the receiver is a file reference URL, a path-independent file URL form. Returns NO for file path URLs or non-file URL schemes.
*/
- (BOOL)isFileReferenceURL NS_AVAILABLE(10_6, 4_0);

/* For file URLs, returns a file reference URL, converting if the receiver is file path URL. For other URL schemes, returns nil.
*/
- (NSURL *)fileReferenceURL NS_AVAILABLE(10_6, 4_0);

/* For file URLs, returns a file path URL, converting if the receiver is a file reference URL. For other URL schemes, returns nil.
*/
- (NSURL *)filePathURL NS_AVAILABLE(10_6, 4_0);

/* Working with Boomarks and alias (bookmark) files 
 */

/* Create a NSData containing a externalizable representation from a given url, which can later be resolved or interrogated for properties */
- (NSData *)bookmarkDataWithOptions:(NSURLBookmarkCreationOptions)options includingResourceValuesForKeys:(NSArray *)keys relativeToURL:(NSURL *)relativeURL error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Resolve bookmark data into a url; init and factory methods  */
- (id)initByResolvingBookmarkData:(NSData *)bookmarkData options:(NSURLBookmarkResolutionOptions)options relativeToURL:(NSURL *)relativeURL bookmarkDataIsStale:(BOOL *)isStale error:(NSError **)error NS_AVAILABLE(10_6, 4_0);
+ (id)URLByResolvingBookmarkData:(NSData *)bookmarkData options:(NSURLBookmarkResolutionOptions)options relativeToURL:(NSURL *)relativeURL bookmarkDataIsStale:(BOOL *)isStale error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Property access.  Given a NSData* created with bookmarkDataWithOptions, return a given property or all of the properties in bookmark data */
+ (NSDictionary *)resourceValuesForKeys:(NSArray *)keys fromBookmarkData:(NSData *)bookmarkData NS_AVAILABLE(10_6, 4_0);

/* Create a bookmark file on disk at bookmarkFileURL which can be resolved back to the file system item represented by bookmarkData, using the given options. If relativeToURL is non-NULL, create a relative url. The bookmark data must have been created with the NSURLBookmarkCreationSuitableForBookmarkFile flag or this routine will fail.  If bookmarkFileURL is a directory then the file will be created in that directory with the name of the item represented by the bookmarkData with ".alias" appended.  If bookmarkFileURL is a file url then its extension will be changed to ".alias", if not present.
*/
+ (BOOL)writeBookmarkData:(NSData *)bookmarkData toURL:(NSURL *)bookmarkFileURL options:(NSURLBookmarkFileCreationOptions)options error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Given the url of a file which is a Finder "alias" file, return a NSData with the bookmark data from the file.  If bookmarkFileURL points to an alias file created before SnowLeopard which contains Alias Manager information and no bookmark data, then a NSData will be synthesized which contains a approximation of the alias information in a format which can be used to resolve the bookmark.  If an error prevents reading the data or if it is corrupt, NULL will be returned and error will be filled in if errorRef is non-NULL.
*/
+ (NSData *)bookmarkDataWithContentsOfURL:(NSURL *)bookmarkFileURL error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

@end

@interface NSString (NSURLUtilities)

/* Adds all percent escapes necessary to convert the receiver in to a legal URL string.  Uses the given encoding to determine the correct percent escapes (returning nil if the given encoding cannot encode a particular character).  See CFURLCreateStringByAddingPercentEscapes in CFURL.h for more complex transformations */
- (NSString *)stringByAddingPercentEscapesUsingEncoding:(NSStringEncoding)enc;

/* Replaces all percent escapes with the matching characters as determined by the given encoding.  Returns nil if the transformation is not possible (i.e. the percent escapes give a byte sequence not legal in the given encoding).  See CFURLCreateStringByReplacingPercentEscapes in CFURL.h for more complex transformations */
- (NSString *)stringByReplacingPercentEscapesUsingEncoding:(NSStringEncoding)enc;

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
// Client informal protocol for use with the deprecated loadResourceDataNotifyingClient: below.  
@interface NSObject(NSURLClient)
- (void)URL:(NSURL *)sender resourceDataDidBecomeAvailable:(NSData *)newBytes NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)URLResourceDidFinishLoading:(NSURL *)sender NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)URLResourceDidCancelLoading:(NSURL *)sender NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)URL:(NSURL *)sender resourceDidFailLoadingWithReason:(NSString *)reason NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
@end

//  This entire protocol is deprecated; use NSURLConnection instead.
@interface NSURL (NSURLLoading)
- (NSData *)resourceDataUsingCache:(BOOL)shouldUseCache NS_DEPRECATED(10_0, 10_4, 2_0, 2_0); // Blocks to load the data if necessary.  If shouldUseCache is YES, then if an equivalent URL has already been loaded and cached, its resource data will be returned immediately.  If shouldUseCache is NO, a new load will be started
- (void)loadResourceDataNotifyingClient:(id)client usingCache:(BOOL)shouldUseCache NS_DEPRECATED(10_0, 10_4, 2_0, 2_0); // Starts an asynchronous load of the data, registering delegate to receive notification.  Only one such background load can proceed at a time.
- (id)propertyForKey:(NSString *)propertyKey NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

    // These attempt to write the given arguments for the resource specified by the URL; they return success or failure
- (BOOL)setResourceData:(NSData *)data NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (BOOL)setProperty:(id)property forKey:(NSString *)propertyKey NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

- (NSURLHandle *)URLHandleUsingCache:(BOOL)shouldUseCache NS_DEPRECATED(10_0, 10_4, 2_0, 2_0); // Sophisticated clients will want to ask for this, then message the handle directly.  If shouldUseCache is NO, a newly instantiated handle is returned, even if an equivalent URL has been loaded

@end
#endif

@interface NSURL(NSURLPathUtilities)
    
/* The following methods work on the path portion of a URL in the same manner that the NSPathUtilities methods on NSString do.
*/
+ (NSURL *)fileURLWithPathComponents:(NSArray *)components NS_AVAILABLE(10_6, 4_0);
- (NSArray *)pathComponents NS_AVAILABLE(10_6, 4_0);
- (NSString *)lastPathComponent NS_AVAILABLE(10_6, 4_0);
- (NSString *)pathExtension NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLByAppendingPathComponent:(NSString *)pathComponent NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLByAppendingPathComponent:(NSString *)pathComponent isDirectory:(BOOL)isDirectory NS_AVAILABLE(10_7, 5_0);
- (NSURL *)URLByDeletingLastPathComponent NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLByAppendingPathExtension:(NSString *)pathExtension NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLByDeletingPathExtension NS_AVAILABLE(10_6, 4_0);

/* The following methods work only on `file:` scheme path-based URLs; for file reference URLs or for non-`file:` scheme URLs, these methods return the URL unchanged.
*/
- (NSURL *)URLByStandardizingPath NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLByResolvingSymlinksInPath NS_AVAILABLE(10_6, 4_0) ;

@end

#if (TARGET_OS_MAC || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
/* NSFileSecurity encapsulates a file system object's security information. NSFileSecurity and CFFileSecurity are toll-free bridged.
 */
@interface NSFileSecurity : NSObject <NSCopying, NSCoding>

@end
#endif

/*
The File System Resource Keys
    
URLs to file system resources support the properties defined below. Note that not all property values will exist for all file system URLs. For example, if a file is located on a volume that does not support creation dates, it is valid to request the creation date property, but the returned value will be NULL, and no error will be generated.
*/

/* Common Keys - applicable to all file system URLs
*/
FOUNDATION_EXPORT NSString * const NSURLNameKey                        NS_AVAILABLE(10_6, 4_0); // Name in the file system; NSString
FOUNDATION_EXPORT NSString * const NSURLLocalizedNameKey               NS_AVAILABLE(10_6, 4_0); // Localized or extension-hidden name as displayed to users; NSString
FOUNDATION_EXPORT NSString * const NSURLIsRegularFileKey               NS_AVAILABLE(10_6, 4_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLIsDirectoryKey                 NS_AVAILABLE(10_6, 4_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLIsSymbolicLinkKey              NS_AVAILABLE(10_6, 4_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLIsVolumeKey                    NS_AVAILABLE(10_6, 4_0); // Root directory of a volume; boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLIsPackageKey                   NS_AVAILABLE(10_6, 4_0); // A packaged directory; boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLIsSystemImmutableKey           NS_AVAILABLE(10_6, 4_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLIsUserImmutableKey             NS_AVAILABLE(10_6, 4_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLIsHiddenKey                    NS_AVAILABLE(10_6, 4_0); // Resource is normally not displayed to users; boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLHasHiddenExtensionKey          NS_AVAILABLE(10_6, 4_0); // Filename extension is normally removed from the localized name property; boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLCreationDateKey                NS_AVAILABLE(10_6, 4_0); // NSDate or nil on volumes that do not support creation date
FOUNDATION_EXPORT NSString * const NSURLContentAccessDateKey           NS_AVAILABLE(10_6, 4_0); // NSDate or nil on volumes that do not support access date (Read-only)
FOUNDATION_EXPORT NSString * const NSURLContentModificationDateKey     NS_AVAILABLE(10_6, 4_0); // NSDate or nil on volumes that do not support modification date
FOUNDATION_EXPORT NSString * const NSURLAttributeModificationDateKey   NS_AVAILABLE(10_6, 4_0); // NSDate or nil on volumes that do not support attribute modification date
FOUNDATION_EXPORT NSString * const NSURLLinkCountKey                   NS_AVAILABLE(10_6, 4_0); // Number of hard links to the resource; NSNumber
FOUNDATION_EXPORT NSString * const NSURLParentDirectoryURLKey          NS_AVAILABLE(10_6, 4_0); // Resource parent directory; NSURL or nil if the receiver is the file system root directory
FOUNDATION_EXPORT NSString * const NSURLVolumeURLKey                   NS_AVAILABLE(10_6, 4_0); // Volume containing the resource; NSURL
FOUNDATION_EXPORT NSString * const NSURLTypeIdentifierKey              NS_AVAILABLE(10_6, 4_0); // Uniform type identifier (UTI) describing the resource; NSString
FOUNDATION_EXPORT NSString * const NSURLLocalizedTypeDescriptionKey    NS_AVAILABLE(10_6, 4_0); // Localized type description; NSString
FOUNDATION_EXPORT NSString * const NSURLLabelNumberKey                 NS_AVAILABLE(10_6, 4_0); // NSNumber
FOUNDATION_EXPORT NSString * const NSURLLabelColorKey                  NS_AVAILABLE(10_6, 4_0); // NSColor or nil
FOUNDATION_EXPORT NSString * const NSURLLocalizedLabelKey              NS_AVAILABLE(10_6, 4_0); // Localized label text; NSString or nil
FOUNDATION_EXPORT NSString * const NSURLEffectiveIconKey               NS_AVAILABLE(10_6, 4_0); // The icon normally displayed for this resource; NSImage
FOUNDATION_EXPORT NSString * const NSURLCustomIconKey                  NS_AVAILABLE(10_6, 4_0); // The icon image stored with the resource, if any; NSImage or nil if no custom icon is assigned
FOUNDATION_EXPORT NSString * const NSURLFileResourceIdentifierKey      NS_AVAILABLE(10_7, 5_0); // An identifier which can be used to compare two file system objects for equality using -isEqual (i.e, two object identifiers are equal if they have the same file system path or if the paths are linked to same inode on the same file system). This identifier is not persistent across system restarts. (Read-only, value type id)
FOUNDATION_EXPORT NSString * const NSURLVolumeIdentifierKey            NS_AVAILABLE(10_7, 5_0); // An identifier that can be used to identify the volume the file system object is on. Other objects on the same volume will have the same volume identifier and can be compared using for equality using -isEqual. This identifier is not persistent across system restarts. (Read-only, value type id)
FOUNDATION_EXPORT NSString * const NSURLPreferredIOBlockSizeKey        NS_AVAILABLE(10_7, 5_0); // The optimal block size when reading or writing this file's data, or nil if not available. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsReadableKey                  NS_AVAILABLE(10_7, 5_0); // true if this process (as determined by EUID) can read the resource. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsWritableKey                  NS_AVAILABLE(10_7, 5_0); // true if this process (as determined by EUID) can write to the resource. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsExecutableKey                NS_AVAILABLE(10_7, 5_0); // true if this process (as determined by EUID) can execute a file resource or search a directory resource. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsMountTriggerKey              NS_AVAILABLE(10_7, 5_0); // true if this URL is a file system trigger directory. Traversing or opening a file system trigger will cause an attempt to mount a file system on the trigger directory. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLFileSecurityKey                NS_AVAILABLE(10_7, 5_0); // The file system object's security information encapsulated in a NSFileSecurity object. (Value type NSFileSecurity)
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeKey            NS_AVAILABLE(10_7, 5_0); // Returns the file system object type. (Read-only, value type NSString)

// The file system object type values returned for the NSURLFileResourceTypeKey
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeNamedPipe      NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeCharacterSpecial NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeDirectory      NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeBlockSpecial   NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeRegular        NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeSymbolicLink   NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeSocket         NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeUnknown        NS_AVAILABLE(10_7, 5_0);

/* File Properties 
*/
FOUNDATION_EXPORT NSString * const NSURLFileSizeKey                    NS_AVAILABLE(10_6, 4_0); // File size in bytes; NSNumber
FOUNDATION_EXPORT NSString * const NSURLFileAllocatedSizeKey           NS_AVAILABLE(10_6, 4_0); // Total size allocated on disk for the file (number of blocks times block size); NSNumber
FOUNDATION_EXPORT NSString * const NSURLTotalFileSizeKey               NS_AVAILABLE(10_7, 5_0); // Total displayable size of the file, in bytes (this may include space used by metadata), or nil if not available. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLTotalFileAllocatedSizeKey      NS_AVAILABLE(10_7, 5_0); // Total allocated size of the file, in bytes (this may include space used by metadata), or nil if not available. This can be less than the value returned by NSURLTotalFileSizeKey if the resource is compressed. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsAliasFileKey		       NS_AVAILABLE(10_6, 4_0); // true if the item is an alias file, false otherwise ; boolean NSNumber

/* Volume Properties

As a convenience, volume properties can be requested from any file system URL. The value returned will reflect the property value for the volume on which the resource is located.
*/
FOUNDATION_EXPORT NSString * const NSURLVolumeLocalizedFormatDescriptionKey NS_AVAILABLE(10_6, 4_0); // Descriptive volume format name; NSString
FOUNDATION_EXPORT NSString * const NSURLVolumeTotalCapacityKey              NS_AVAILABLE(10_6, 4_0); // Total volume capacity in bytes; NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeAvailableCapacityKey          NS_AVAILABLE(10_6, 4_0); // Bytes free; NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeResourceCountKey              NS_AVAILABLE(10_6, 4_0); // Total number of resources on the volume; NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsPersistentIDsKey      NS_AVAILABLE(10_6, 4_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsSymbolicLinksKey      NS_AVAILABLE(10_6, 4_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsHardLinksKey          NS_AVAILABLE(10_6, 4_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsJournalingKey         NS_AVAILABLE(10_6, 4_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeIsJournalingKey               NS_AVAILABLE(10_6, 4_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsSparseFilesKey        NS_AVAILABLE(10_6, 4_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsZeroRunsKey           NS_AVAILABLE(10_6, 4_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsCaseSensitiveNamesKey NS_AVAILABLE(10_6, 4_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsCasePreservedNamesKey NS_AVAILABLE(10_6, 4_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsRootDirectoryDatesKey NS_AVAILABLE(10_7, 5_0); // true if the volume supports reliable storage of times for the root directory. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsVolumeSizesKey        NS_AVAILABLE(10_7, 5_0); // true if the volume supports returning volume size values (NSURLVolumeTotalCapacityKey and NSURLVolumeAvailableCapacityKey). (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsRenamingKey           NS_AVAILABLE(10_7, 5_0); // true if the volume can be renamed. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsAdvisoryFileLockingKey NS_AVAILABLE(10_7, 5_0); // true if the volume implements whole-file flock(2) style advisory locks, and the O_EXLOCK and O_SHLOCK flags of the open(2) call. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsExtendedSecurityKey NS_AVAILABLE(10_7, 5_0); // true if the volume implements extended security (ACLs). (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsBrowsableKey                NS_AVAILABLE(10_7, 5_0); // true if the volume should be visible via the GUI (i.e., appear on the Desktop as a separate volume). (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeMaximumFileSizeKey            NS_AVAILABLE(10_7, 5_0); // The largest file size (in bytes) supported by this file system, or nil if this cannot be determined. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsEjectableKey                NS_AVAILABLE(10_7, 5_0); // true if the volume's media is ejectable from the drive mechanism under software control. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsRemovableKey                NS_AVAILABLE(10_7, 5_0); // true if the volume's media is removable from the drive mechanism. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsInternalKey                 NS_AVAILABLE(10_7, 5_0); // true if the volume's device is connected to an internal bus, false if connected to an external bus, or nil if not available. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsAutomountedKey              NS_AVAILABLE(10_7, 5_0); // true if the volume is automounted. Note: do not mistake this with the functionality provided by kCFURLVolumeSupportsBrowsingKey. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsLocalKey                    NS_AVAILABLE(10_7, 5_0); // true if the volume is stored on a local device. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsReadOnlyKey                 NS_AVAILABLE(10_7, 5_0); // true if the volume is read-only. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeCreationDateKey               NS_AVAILABLE(10_7, 5_0); // The volume's creation date, or nil if this cannot be determined. (Read-only, value type NSDate)
FOUNDATION_EXPORT NSString * const NSURLVolumeURLForRemountingKey           NS_AVAILABLE(10_7, 5_0); // The NSURL needed to remount a network volume, or nil if not available. (Read-only, value type NSURL)
FOUNDATION_EXPORT NSString * const NSURLVolumeUUIDStringKey                 NS_AVAILABLE(10_7, 5_0); // The volume's persistent UUID as a string, or nil if a persistent UUID is not available for the volume. (Read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLVolumeNameKey                       NS_AVAILABLE(10_7, 5_0); // The name of the volume (settable if NSURLVolumeSupportsRenamingKey is YES, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLVolumeLocalizedNameKey              NS_AVAILABLE(10_7, 5_0); // The user-presentable name of the volume (Read-only, value type NSString)

/* Ubiquitous item properties */

FOUNDATION_EXPORT NSString * const NSURLIsUbiquitousItemKey                     NS_AVAILABLE(10_7, 5_0); // true if this item is synced to the cloud, false if it is only a local file. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemHasUnresolvedConflictsKey NS_AVAILABLE(10_7, 5_0); // true if this item has conflicts outstanding. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemIsDownloadedKey           NS_AVAILABLE(10_7, 5_0); // true if there is local data present for this item. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemIsDownloadingKey          NS_AVAILABLE(10_7, 5_0); // true if data is being downloaded for this item. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemIsUploadedKey             NS_AVAILABLE(10_7, 5_0); // true if there is data present in the cloud for this item. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemIsUploadingKey            NS_AVAILABLE(10_7, 5_0); // true if data is being uploaded for this item. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemPercentDownloadedKey      NS_AVAILABLE(10_7, 5_0); // [0-100] percent of data downloaded. (Read-only, value type double NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemPercentUploadedKey        NS_AVAILABLE(10_7, 5_0); // [0-100] percent of data uploaded. (Read-only, value type double NSNumber)

