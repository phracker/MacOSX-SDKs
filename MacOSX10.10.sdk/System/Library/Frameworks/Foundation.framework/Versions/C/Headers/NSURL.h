/*	NSURL.h
	Copyright (c) 1997-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSCharacterSet.h>
#if !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#import <Foundation/NSURLHandle.h>
#endif

@class NSNumber, NSData, NSDictionary;

#if (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
@interface NSURL: NSObject <NSSecureCoding, NSCopying>
#else
@interface NSURL: NSObject <NSSecureCoding, NSCopying, NSURLHandleClient>
#endif
{
    NSString *_urlString;
    NSURL *_baseURL;
    void *_clients;
    __strong void *_reserved;
}


/* As more schemes are used and understood, strong constants for them will be added here
 */
FOUNDATION_EXPORT NSString *NSURLFileScheme;


/* Convenience initializers
 */
- (instancetype)initWithScheme:(NSString *)scheme host:(NSString *)host path:(NSString *)path; // this call percent-encodes both the host and path, so this cannot be used to set a username/password or port in the hostname part or with a IPv6 '[...]' type address; use initWithString: and construct the string yourself in those cases

- (instancetype)initFileURLWithPath:(NSString *)path isDirectory:(BOOL)isDir NS_AVAILABLE(10_5, 2_0) NS_DESIGNATED_INITIALIZER;
- (instancetype)initFileURLWithPath:(NSString *)path NS_DESIGNATED_INITIALIZER;  // Better to use initFileURLWithPath:isDirectory: if you know if the path is a directory vs non-directory, as it saves an i/o.

+ (NSURL *)fileURLWithPath:(NSString *)path isDirectory:(BOOL) isDir NS_AVAILABLE(10_5, 2_0);
+ (NSURL *)fileURLWithPath:(NSString *)path; // Better to use fileURLWithPath:isDirectory: if you know if the path is a directory vs non-directory, as it saves an i/o.

/* Initializes a newly created URL referencing the local file or directory at the file system representation of the path. File system representation is a null-terminated C string with canonical UTF-8 encoding.
 */
- (instancetype)initFileURLWithFileSystemRepresentation:(const char *)path isDirectory:(BOOL)isDir relativeToURL:(NSURL *)baseURL NS_AVAILABLE(10_9, 7_0) NS_DESIGNATED_INITIALIZER;

/* Initializes and returns a newly created URL referencing the local file or directory at the file system representation of the path. File system representation is a null-terminated C string with canonical UTF-8 encoding.
 */
+ (NSURL *)fileURLWithFileSystemRepresentation:(const char *)path isDirectory:(BOOL) isDir relativeToURL:(NSURL *)baseURL NS_AVAILABLE(10_9, 7_0);

/* These methods expect their string arguments to contain any percent escape codes that are necessary. It is an error for URLString to be nil.
 */
- (instancetype)initWithString:(NSString *)URLString;
- (instancetype)initWithString:(NSString *)URLString relativeToURL:(NSURL *)baseURL NS_DESIGNATED_INITIALIZER;
+ (instancetype)URLWithString:(NSString *)URLString;
+ (instancetype)URLWithString:(NSString *)URLString relativeToURL:(NSURL *)baseURL;


@property (readonly, copy) NSString *absoluteString;
@property (readonly, copy) NSString *relativeString; // The relative portion of a URL.  If baseURL is nil, or if the receiver is itself absolute, this is the same as absoluteString
@property (readonly, copy) NSURL *baseURL; // may be nil.
@property (readonly, copy) NSURL *absoluteURL; // if the receiver is itself absolute, this will return self.

/* Any URL is composed of these two basic pieces.  The full URL would be the concatenation of [myURL scheme], ':', [myURL resourceSpecifier]
 */
@property (readonly, copy) NSString *scheme;
@property (readonly, copy) NSString *resourceSpecifier;

/* If the URL conforms to rfc 1808 (the most common form of URL), the following accessors will return the various components; otherwise they return nil.  The litmus test for conformance is as recommended in RFC 1808 - whether the first two characters of resourceSpecifier is @"//".  In all cases, they return the component's value after resolving the receiver against its base URL.
 */
@property (readonly, copy) NSString *host;
@property (readonly, copy) NSNumber *port;
@property (readonly, copy) NSString *user;
@property (readonly, copy) NSString *password;
@property (readonly, copy) NSString *path;
@property (readonly, copy) NSString *fragment;
@property (readonly, copy) NSString *parameterString;
@property (readonly, copy) NSString *query;
@property (readonly, copy) NSString *relativePath; // The same as path if baseURL is nil

/* Returns the URL's path in file system representation. File system representation is a null-terminated C string with canonical UTF-8 encoding.
 */
- (BOOL)getFileSystemRepresentation:(char *)buffer maxLength:(NSUInteger)maxBufferLength NS_AVAILABLE(10_9, 7_0);

/* Returns the URL's path in file system representation. File system representation is a null-terminated C string with canonical UTF-8 encoding. The returned C string will be automatically freed just as a returned object would be released; your code should copy the representation or use getFileSystemRepresentation:maxLength: if it needs to store the representation outside of the autorelease context in which the representation is created.
 */
@property (readonly) __strong const char *fileSystemRepresentation NS_RETURNS_INNER_POINTER NS_AVAILABLE(10_9, 7_0);

@property (readonly, getter=isFileURL) BOOL fileURL; // Whether the scheme is file:; if [myURL isFileURL] is YES, then [myURL path] is suitable for input into NSFileManager or NSPathUtilities.

@property (readonly, copy) NSURL *standardizedURL;


/* Returns whether the URL's resource exists and is reachable. This method synchronously checks if the resource's backing store is reachable. Checking reachability is appropriate when making decisions that do not require other immediate operations on the resource, e.g. periodic maintenance of UI state that depends on the existence of a specific document. When performing operations such as opening a file or copying resource properties, it is more efficient to simply try the operation and handle failures. If this method returns NO, the optional error is populated. This method is currently applicable only to URLs for file system resources. For other URL types, NO is returned. Symbol is present in iOS 4, but performs no operation.
 */
- (BOOL)checkResourceIsReachableAndReturnError:(NSError **)error NS_AVAILABLE(10_6, 4_0);


/* Working with file reference URLs
 */

/* Returns whether the URL is a file reference URL. Symbol is present in iOS 4, but performs no operation.
 */
- (BOOL)isFileReferenceURL NS_AVAILABLE(10_6, 4_0);

/* Returns a file reference URL that refers to the same resource as a specified file URL. File reference URLs use a URL path syntax that identifies a file system object by reference, not by path. This form of file URL remains valid when the file system path of the URL’s underlying resource changes. An error will occur if the url parameter is not a file URL. File reference URLs cannot be created to file system objects which do not exist or are not reachable. In some areas of the file system hierarchy, file reference URLs cannot be generated to the leaf node of the URL path. A file reference URL's path should never be persistently stored because is not valid across system restarts, and across remounts of volumes -- if you want to create a persistent reference to a file system object, use a bookmark (see -bookmarkDataWithOptions:includingResourceValuesForKeys:relativeToURL:error:). Symbol is present in iOS 4, but performs no operation.
 */
- (NSURL *)fileReferenceURL NS_AVAILABLE(10_6, 4_0);

/* Returns a file path URL that refers to the same resource as a specified URL. File path URLs use a file system style path. An error will occur if the url parameter is not a file URL. A file reference URL's resource must exist and be reachable to be converted to a file path URL. Symbol is present in iOS 4, but performs no operation.
 */
@property (readonly, copy) NSURL *filePathURL NS_AVAILABLE(10_6, 4_0);


/* Resource access

 The behavior of resource value caching is slightly different between the NSURL and CFURL API.
 
 When the NSURL methods which get, set, or use cached resource values are used from the main thread, resource values cached by the URL (except those added as temporary properties) are removed the next time the main thread's run loop runs. -removeCachedResourceValueForKey: and -removeAllCachedResourceValues also may be used to remove cached resource values.
 
 The CFURL functions do not automatically remove any resource values cached by the URL. The client has complete control over the cache lifetime. If you are using CFURL API, you must use CFURLClearResourcePropertyCacheForKey or CFURLClearResourcePropertyCache to remove cached resource values.
 */

/* Returns the resource value identified by a given resource key. This method first checks if the URL object already caches the resource value. If so, it returns the cached resource value to the caller. If not, then this method synchronously obtains the resource value from the backing store, adds the resource value to the URL object's cache, and returns the resource value to the caller. The type of the resource value varies by resource property (see resource key definitions). If this method returns YES and value is populated with nil, it means the resource property is not available for the specified resource and no errors occurred when determining the resource property was not available. If this method returns NO, the optional error is populated. This method is currently applicable only to URLs for file system resources. Symbol is present in iOS 4, but performs no operation.
 */
- (BOOL)getResourceValue:(out id *)value forKey:(NSString *)key error:(out NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Returns the resource values identified by specified array of resource keys. This method first checks if the URL object already caches the resource values. If so, it returns the cached resource values to the caller. If not, then this method synchronously obtains the resource values from the backing store, adds the resource values to the URL object's cache, and returns the resource values to the caller. The type of the resource values vary by property (see resource key definitions). If the result dictionary does not contain a resource value for one or more of the requested resource keys, it means those resource properties are not available for the specified resource and no errors occurred when determining those resource properties were not available. If this method returns NULL, the optional error is populated. This method is currently applicable only to URLs for file system resources. Symbol is present in iOS 4, but performs no operation.
 */
- (NSDictionary *)resourceValuesForKeys:(NSArray *)keys error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Sets the resource value identified by a given resource key. This method writes the new resource value out to the backing store. Attempts to set a read-only resource property or to set a resource property not supported by the resource are ignored and are not considered errors. If this method returns NO, the optional error is populated. This method is currently applicable only to URLs for file system resources. Symbol is present in iOS 4, but performs no operation.
 */
- (BOOL)setResourceValue:(id)value forKey:(NSString *)key error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Sets any number of resource values of a URL's resource. This method writes the new resource values out to the backing store. Attempts to set read-only resource properties or to set resource properties not supported by the resource are ignored and are not considered errors. If an error occurs after some resource properties have been successfully changed, the userInfo dictionary in the returned error contains an array of resource keys that were not set with the key kCFURLKeysOfUnsetValuesKey. The order in which the resource values are set is not defined. If you need to guarantee the order resource values are set, you should make multiple requests to this method or to -setResourceValue:forKey:error: to guarantee the order. If this method returns NO, the optional error is populated. This method is currently applicable only to URLs for file system resources. Symbol is present in iOS 4, but performs no operation.
 */
- (BOOL)setResourceValues:(NSDictionary *)keyedValues error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

FOUNDATION_EXPORT NSString * const NSURLKeysOfUnsetValuesKey NS_AVAILABLE(10_7, 5_0); // Key for the resource properties that have not been set after setResourceValues:error: returns an error, returned as an array of of strings.

/* Removes the cached resource value identified by a given resource value key from the URL object. Removing a cached resource value may remove other cached resource values because some resource values are cached as a set of values, and because some resource values depend on other resource values (temporary resource values have no dependencies). This method is currently applicable only to URLs for file system resources.
 */
- (void)removeCachedResourceValueForKey:(NSString *)key NS_AVAILABLE(10_9, 7_0);

/* Removes all cached resource values and all temporary resource values from the URL object. This method is currently applicable only to URLs for file system resources.
 */
- (void)removeAllCachedResourceValues NS_AVAILABLE(10_9, 7_0);

/* Sets a temporary resource value on the URL object. Temporary resource values are for client use. Temporary resource values exist only in memory and are never written to the resource's backing store. Once set, a temporary resource value can be copied from the URL object with -getResourceValue:forKey:error: or -resourceValuesForKeys:error:. To remove a temporary resource value from the URL object, use -removeCachedResourceValueForKey:. Care should be taken to ensure the key that identifies a temporary resource value is unique and does not conflict with system defined keys (using reverse domain name notation in your temporary resource value keys is recommended). This method is currently applicable only to URLs for file system resources.
 */
- (void)setTemporaryResourceValue:(id)value forKey:(NSString *)key NS_AVAILABLE(10_9, 7_0);

/*
 The File System Resource Keys
 
 URLs to file system resources support the properties defined below. Note that not all property values will exist for all file system URLs. For example, if a file is located on a volume that does not support creation dates, it is valid to request the creation date property, but the returned value will be nil, and no error will be generated.
 */

/* Resource keys applicable to all file system objects
 */
FOUNDATION_EXPORT NSString * const NSURLNameKey                        NS_AVAILABLE(10_6, 4_0); // The resource name provided by the file system (Read-write, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLLocalizedNameKey               NS_AVAILABLE(10_6, 4_0); // Localized or extension-hidden name as displayed to users (Read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLIsRegularFileKey               NS_AVAILABLE(10_6, 4_0); // True for regular files (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsDirectoryKey                 NS_AVAILABLE(10_6, 4_0); // True for directories (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsSymbolicLinkKey              NS_AVAILABLE(10_6, 4_0); // True for symlinks (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsVolumeKey                    NS_AVAILABLE(10_6, 4_0); // True for the root directory of a volume (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsPackageKey                   NS_AVAILABLE(10_6, 4_0); // True for packaged directories (Read-only 10_6 and 10_7, read-write 10_8, value type boolean NSNumber). Note: You can only set or clear this property on directories; if you try to set this property on non-directory objects, the property is ignored. If the directory is a package for some other reason (extension type, etc), setting this property to false will have no effect.
FOUNDATION_EXPORT NSString * const NSURLIsSystemImmutableKey           NS_AVAILABLE(10_6, 4_0); // True for system-immutable resources (Read-write, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsUserImmutableKey             NS_AVAILABLE(10_6, 4_0); // True for user-immutable resources (Read-write, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsHiddenKey                    NS_AVAILABLE(10_6, 4_0); // True for resources normally not displayed to users (Read-write, value type boolean NSNumber). Note: If the resource is a hidden because its name starts with a period, setting this property to false will not change the property.
FOUNDATION_EXPORT NSString * const NSURLHasHiddenExtensionKey          NS_AVAILABLE(10_6, 4_0); // True for resources whose filename extension is removed from the localized name property (Read-write, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLCreationDateKey                NS_AVAILABLE(10_6, 4_0); // The date the resource was created (Read-write, value type NSDate)
FOUNDATION_EXPORT NSString * const NSURLContentAccessDateKey           NS_AVAILABLE(10_6, 4_0); // The date the resource was last accessed (Read-only, value type NSDate)
FOUNDATION_EXPORT NSString * const NSURLContentModificationDateKey     NS_AVAILABLE(10_6, 4_0); // The time the resource content was last modified (Read-write, value type NSDate)
FOUNDATION_EXPORT NSString * const NSURLAttributeModificationDateKey   NS_AVAILABLE(10_6, 4_0); // The time the resource's attributes were last modified (Read-write, value type NSDate)
FOUNDATION_EXPORT NSString * const NSURLLinkCountKey                   NS_AVAILABLE(10_6, 4_0); // Number of hard links to the resource (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLParentDirectoryURLKey          NS_AVAILABLE(10_6, 4_0); // The resource's parent directory, if any (Read-only, value type NSURL)
FOUNDATION_EXPORT NSString * const NSURLVolumeURLKey                   NS_AVAILABLE(10_6, 4_0); // URL of the volume on which the resource is stored (Read-only, value type NSURL)
FOUNDATION_EXPORT NSString * const NSURLTypeIdentifierKey              NS_AVAILABLE(10_6, 4_0); // Uniform type identifier (UTI) for the resource (Read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLLocalizedTypeDescriptionKey    NS_AVAILABLE(10_6, 4_0); // User-visible type or "kind" description (Read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLLabelNumberKey                 NS_AVAILABLE(10_6, 4_0); // The label number assigned to the resource (Read-write, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLLabelColorKey                  NS_AVAILABLE(10_6, 4_0); // The color of the assigned label (Read-only, value type NSColor)
FOUNDATION_EXPORT NSString * const NSURLLocalizedLabelKey              NS_AVAILABLE(10_6, 4_0); // The user-visible label text (Read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLEffectiveIconKey               NS_AVAILABLE(10_6, 4_0); // The icon normally displayed for the resource (Read-only, value type NSImage)
FOUNDATION_EXPORT NSString * const NSURLCustomIconKey                  NS_AVAILABLE(10_6, 4_0); // The custom icon assigned to the resource, if any (Currently not implemented, value type NSImage)
FOUNDATION_EXPORT NSString * const NSURLFileResourceIdentifierKey      NS_AVAILABLE(10_7, 5_0); // An identifier which can be used to compare two file system objects for equality using -isEqual (i.e, two object identifiers are equal if they have the same file system path or if the paths are linked to same inode on the same file system). This identifier is not persistent across system restarts. (Read-only, value type id <NSCopying, NSCoding, NSObject>)
FOUNDATION_EXPORT NSString * const NSURLVolumeIdentifierKey            NS_AVAILABLE(10_7, 5_0); // An identifier that can be used to identify the volume the file system object is on. Other objects on the same volume will have the same volume identifier and can be compared using for equality using -isEqual. This identifier is not persistent across system restarts. (Read-only, value type id <NSCopying, NSCoding, NSObject>)
FOUNDATION_EXPORT NSString * const NSURLPreferredIOBlockSizeKey        NS_AVAILABLE(10_7, 5_0); // The optimal block size when reading or writing this file's data, or nil if not available. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsReadableKey                  NS_AVAILABLE(10_7, 5_0); // true if this process (as determined by EUID) can read the resource. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsWritableKey                  NS_AVAILABLE(10_7, 5_0); // true if this process (as determined by EUID) can write to the resource. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsExecutableKey                NS_AVAILABLE(10_7, 5_0); // true if this process (as determined by EUID) can execute a file resource or search a directory resource. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLFileSecurityKey                NS_AVAILABLE(10_7, 5_0); // The file system object's security information encapsulated in a NSFileSecurity object. (Read-write, Value type NSFileSecurity)
FOUNDATION_EXPORT NSString * const NSURLIsExcludedFromBackupKey        NS_AVAILABLE(10_8, 5_1); // true if resource should be excluded from backups, false otherwise (Read-write, value type boolean NSNumber). This property is only useful for excluding cache and other application support files which are not needed in a backup. Some operations commonly made to user documents will cause this property to be reset to false and so this property should not be used on user documents.
FOUNDATION_EXPORT NSString * const NSURLTagNamesKey                    NS_AVAILABLE(10_9, NA);	// The array of Tag names (Read-write, value type NSArray of NSString)
FOUNDATION_EXPORT NSString * const NSURLPathKey                        NS_AVAILABLE(10_8, 6_0); // the URL's path as a file system path (Read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLIsMountTriggerKey              NS_AVAILABLE(10_7, 5_0); // true if this URL is a file system trigger directory. Traversing or opening a file system trigger will cause an attempt to mount a file system on the trigger directory. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLGenerationIdentifierKey NS_AVAILABLE(10_10, 8_0); // An opaque generation identifier which can be compared using isEqual: to determine if the data in a document has been modified. For URLs which refer to the same file inode, the generation identifier will change when the data in the file's data fork is changed (changes to extended attributes or other file system metadata do not change the generation identifier). For URLs which refer to the same directory inode, the generation identifier will change when direct children of that directory are added, removed or renamed (changes to the data of the direct children of that directory will not change the generation identifier). The generation identifier is persistent across system restarts. The generation identifier is tied to a specific document on a specific volume and is not transferred when the document is copied to another volume. This property is not supported by all volumes. (Read-only, value type id <NSCopying, NSCoding, NSObject>
FOUNDATION_EXPORT NSString * const NSURLDocumentIdentifierKey NS_AVAILABLE(10_10, 8_0); // The document identifier -- a value assigned by the kernel to a document (which can be either a file or directory) and is used to identify the document regardless of where it gets moved on a volume. The document identifier survives "safe save” operations; i.e it is sticky to the path it was assigned to (-replaceItemAtURL:withItemAtURL:backupItemName:options:resultingItemURL:error: is the preferred safe-save API). The document identifier is persistent across system restarts. The document identifier is not transferred when the file is copied. Document identifiers are only unique within a single volume. This property is not supported by all volumes. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLAddedToDirectoryDateKey NS_AVAILABLE(10_10, 8_0); // The date the resource was created, or renamed into or within its parent directory. Note that inconsistent behavior may be observed when this attribute is requested on hard-linked items. This property is not supported by all volumes. (Read-only, value type NSDate)
FOUNDATION_EXPORT NSString * const NSURLQuarantinePropertiesKey NS_AVAILABLE(10_10, NA); // The quarantine properties as defined in LSQuarantine.h. To remove quarantine information from a file, pass NSNull as the value when setting this property. (Read-write, value type NSDictionary)
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeKey            NS_AVAILABLE(10_7, 5_0); // Returns the file system object type. (Read-only, value type NSString)

/* The file system object type values returned for the NSURLFileResourceTypeKey
 */
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeNamedPipe      NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeCharacterSpecial NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeDirectory      NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeBlockSpecial   NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeRegular        NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeSymbolicLink   NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeSocket         NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSURLFileResourceTypeUnknown        NS_AVAILABLE(10_7, 5_0);

FOUNDATION_EXPORT NSString * const NSURLThumbnailDictionaryKey         NS_AVAILABLE(10_10, 8_0); // dictionary of NSImage/UIImage objects keyed by size
FOUNDATION_EXPORT NSString * const NSURLThumbnailKey                   NS_AVAILABLE_MAC(10_10); // returns all thumbnails as a single NSImage

/* size keys for the dictionary returned by NSURLThumbnailDictionaryKey
 */
FOUNDATION_EXPORT NSString * const NSThumbnail1024x1024SizeKey         NS_AVAILABLE(10_10, 8_0); // size key for a 1024 x 1024 thumbnail image

/* Resource keys applicable only to regular files
 */
FOUNDATION_EXPORT NSString * const NSURLFileSizeKey                    NS_AVAILABLE(10_6, 4_0); // Total file size in bytes (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLFileAllocatedSizeKey           NS_AVAILABLE(10_6, 4_0); // Total size allocated on disk for the file in bytes (number of blocks times block size) (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLTotalFileSizeKey               NS_AVAILABLE(10_7, 5_0); // Total displayable size of the file in bytes (this may include space used by metadata), or nil if not available. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLTotalFileAllocatedSizeKey      NS_AVAILABLE(10_7, 5_0); // Total allocated size of the file in bytes (this may include space used by metadata), or nil if not available. This can be less than the value returned by NSURLTotalFileSizeKey if the resource is compressed. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLIsAliasFileKey		   NS_AVAILABLE(10_6, 4_0); // true if the resource is a Finder alias file or a symlink, false otherwise ( Read-only, value type boolean NSNumber)

/* Volumes resource keys 
 
 As a convenience, volume resource values can be requested from any file system URL. The value returned will reflect the property value for the volume on which the resource is located.
 */
FOUNDATION_EXPORT NSString * const NSURLVolumeLocalizedFormatDescriptionKey NS_AVAILABLE(10_6, 4_0); // The user-visible volume format (Read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLVolumeTotalCapacityKey              NS_AVAILABLE(10_6, 4_0); // Total volume capacity in bytes (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeAvailableCapacityKey          NS_AVAILABLE(10_6, 4_0); // Total free space in bytes (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeResourceCountKey              NS_AVAILABLE(10_6, 4_0); // Total number of resources on the volume (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsPersistentIDsKey      NS_AVAILABLE(10_6, 4_0); // true if the volume format supports persistent object identifiers and can look up file system objects by their IDs (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsSymbolicLinksKey      NS_AVAILABLE(10_6, 4_0); // true if the volume format supports symbolic links (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsHardLinksKey          NS_AVAILABLE(10_6, 4_0); // true if the volume format supports hard links (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsJournalingKey         NS_AVAILABLE(10_6, 4_0); // true if the volume format supports a journal used to speed recovery in case of unplanned restart (such as a power outage or crash). This does not necessarily mean the volume is actively using a journal. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeIsJournalingKey               NS_AVAILABLE(10_6, 4_0); // true if the volume is currently using a journal for speedy recovery after an unplanned restart. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsSparseFilesKey        NS_AVAILABLE(10_6, 4_0); // true if the volume format supports sparse files, that is, files which can have 'holes' that have never been written to, and thus do not consume space on disk. A sparse file may have an allocated size on disk that is less than its logical length (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsZeroRunsKey           NS_AVAILABLE(10_6, 4_0); // For security reasons, parts of a file (runs) that have never been written to must appear to contain zeroes. true if the volume keeps track of allocated but unwritten runs of a file so that it can substitute zeroes without actually writing zeroes to the media. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsCaseSensitiveNamesKey NS_AVAILABLE(10_6, 4_0); // true if the volume format treats upper and lower case characters in file and directory names as different. Otherwise an upper case character is equivalent to a lower case character, and you can't have two names that differ solely in the case of the characters. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsCasePreservedNamesKey NS_AVAILABLE(10_6, 4_0); // true if the volume format preserves the case of file and directory names.  Otherwise the volume may change the case of some characters (typically making them all upper or all lower case). (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsRootDirectoryDatesKey NS_AVAILABLE(10_7, 5_0); // true if the volume supports reliable storage of times for the root directory. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsVolumeSizesKey        NS_AVAILABLE(10_7, 5_0); // true if the volume supports returning volume size values (NSURLVolumeTotalCapacityKey and NSURLVolumeAvailableCapacityKey). (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsRenamingKey           NS_AVAILABLE(10_7, 5_0); // true if the volume can be renamed. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsAdvisoryFileLockingKey NS_AVAILABLE(10_7, 5_0); // true if the volume implements whole-file flock(2) style advisory locks, and the O_EXLOCK and O_SHLOCK flags of the open(2) call. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLVolumeSupportsExtendedSecurityKey   NS_AVAILABLE(10_7, 5_0); // true if the volume implements extended security (ACLs). (Read-only, value type boolean NSNumber)
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
FOUNDATION_EXPORT NSString * const NSURLVolumeNameKey                       NS_AVAILABLE(10_7, 5_0); // The name of the volume (Read-write if NSURLVolumeSupportsRenamingKey is YES, otherwise read-only, value type NSString)
FOUNDATION_EXPORT NSString * const NSURLVolumeLocalizedNameKey              NS_AVAILABLE(10_7, 5_0); // The user-presentable name of the volume (Read-only, value type NSString)

/* Ubiquitous item resource keys
 */
FOUNDATION_EXPORT NSString * const NSURLIsUbiquitousItemKey                     NS_AVAILABLE(10_7, 5_0); // true if this item is synced to the cloud, false if it is only a local file. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemHasUnresolvedConflictsKey NS_AVAILABLE(10_7, 5_0); // true if this item has conflicts outstanding. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemIsDownloadedKey           NS_DEPRECATED(10_7, 10_9, 5_0, 7_0, "Use NSURLUbiquitousItemDownloadingStatusKey instead"); // equivalent to NSURLUbiquitousItemDownloadingStatusKey == NSURLUbiquitousItemDownloadingStatusCurrent. Has never behaved as documented in earlier releases, hence deprecated.  (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemIsDownloadingKey          NS_AVAILABLE(10_7, 5_0); // true if data is being downloaded for this item. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemIsUploadedKey             NS_AVAILABLE(10_7, 5_0); // true if there is data present in the cloud for this item. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemIsUploadingKey            NS_AVAILABLE(10_7, 5_0); // true if data is being uploaded for this item. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemPercentDownloadedKey      NS_DEPRECATED(10_7, 10_8, 5_0, 6_0); // Use NSMetadataQuery and NSMetadataUbiquitousItemPercentDownloadedKey on NSMetadataItem instead
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemPercentUploadedKey        NS_DEPRECATED(10_7, 10_8, 5_0, 6_0); // Use NSMetadataQuery and NSMetadataUbiquitousItemPercentUploadedKey on NSMetadataItem instead
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemDownloadingStatusKey      NS_AVAILABLE(10_9, 7_0); // returns the download status of this item. (Read-only, value type NSString). Possible values below.
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemDownloadingErrorKey       NS_AVAILABLE(10_9, 7_0); // returns the error when downloading the item from iCloud failed, see the NSUbiquitousFile section in FoundationErrors.h (Read-only, value type NSError)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemUploadingErrorKey         NS_AVAILABLE(10_9, 7_0); // returns the error when uploading the item to iCloud failed, see the NSUbiquitousFile section in FoundationErrors.h (Read-only, value type NSError)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemDownloadRequestedKey      NS_AVAILABLE(10_10, 8_0); // returns whether a download of this item has already been requested with an API like -startDownloadingUbiquitousItemAtURL:error: (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemContainerDisplayNameKey   NS_AVAILABLE(10_10, 8_0); // returns the name of this item's container as displayed to users.


/* The values returned for the NSURLUbiquitousItemDownloadingStatusKey
 */
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemDownloadingStatusNotDownloaded  NS_AVAILABLE(10_9, 7_0); // this item has not been downloaded yet. Use startDownloadingUbiquitousItemAtURL:error: to download it.
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemDownloadingStatusDownloaded     NS_AVAILABLE(10_9, 7_0); // there is a local version of this item available. The most current version will get downloaded as soon as possible.
FOUNDATION_EXPORT NSString * const NSURLUbiquitousItemDownloadingStatusCurrent        NS_AVAILABLE(10_9, 7_0); // there is a local version of this item and it is the most up-to-date version known to this device.

/* Working with Bookmarks and alias (bookmark) files 
 */

typedef NS_OPTIONS(NSUInteger, NSURLBookmarkCreationOptions) {
    NSURLBookmarkCreationPreferFileIDResolution NS_ENUM_DEPRECATED(10_6, 10_9, 4_0, 7_0) = ( 1UL << 8 ), /* This option does nothing and has no effect on bookmark resolution */
    NSURLBookmarkCreationMinimalBookmark = ( 1UL << 9 ), /* creates bookmark data with "less" information, which may be smaller but still be able to resolve in certain ways */
    NSURLBookmarkCreationSuitableForBookmarkFile = ( 1UL << 10 ), /* include the properties required by writeBookmarkData:toURL:options: in the bookmark data created */
    NSURLBookmarkCreationWithSecurityScope NS_ENUM_AVAILABLE(10_7, NA) = ( 1 << 11 ), /* include information in the bookmark data which allows the same sandboxed process to access the resource after being relaunched */
    NSURLBookmarkCreationSecurityScopeAllowOnlyReadAccess NS_ENUM_AVAILABLE(10_7, NA) = ( 1 << 12 ), /* if used with kCFURLBookmarkCreationWithSecurityScope, at resolution time only read access to the resource will be granted */
} NS_ENUM_AVAILABLE(10_6, 4_0);

typedef NS_OPTIONS(NSUInteger, NSURLBookmarkResolutionOptions) {
    NSURLBookmarkResolutionWithoutUI = ( 1UL << 8 ), /* don't perform any user interaction during bookmark resolution */
    NSURLBookmarkResolutionWithoutMounting = ( 1UL << 9 ), /* don't mount a volume during bookmark resolution */
    NSURLBookmarkResolutionWithSecurityScope NS_ENUM_AVAILABLE(10_7, NA) = ( 1 << 10 ) /* use the secure information included at creation time to provide the ability to access the resource in a sandboxed process */
} NS_ENUM_AVAILABLE(10_6, 4_0);

typedef NSUInteger NSURLBookmarkFileCreationOptions;

/* Returns bookmark data for the URL, created with specified options and resource values. If this method returns nil, the optional error is populated.
 */
- (NSData *)bookmarkDataWithOptions:(NSURLBookmarkCreationOptions)options includingResourceValuesForKeys:(NSArray *)keys relativeToURL:(NSURL *)relativeURL error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Initializes a newly created NSURL that refers to a location specified by resolving bookmark data. If this method returns nil, the optional error is populated.
 */
- (instancetype)initByResolvingBookmarkData:(NSData *)bookmarkData options:(NSURLBookmarkResolutionOptions)options relativeToURL:(NSURL *)relativeURL bookmarkDataIsStale:(BOOL *)isStale error:(NSError **)error NS_AVAILABLE(10_6, 4_0);
/* Creates and Initializes an NSURL that refers to a location specified by resolving bookmark data. If this method returns nil, the optional error is populated.
 */
+ (instancetype)URLByResolvingBookmarkData:(NSData *)bookmarkData options:(NSURLBookmarkResolutionOptions)options relativeToURL:(NSURL *)relativeURL bookmarkDataIsStale:(BOOL *)isStale error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Returns the resource values for properties identified by a specified array of keys contained in specified bookmark data. If the result dictionary does not contain a resource value for one or more of the requested resource keys, it means those resource properties are not available in the bookmark data.
 */
+ (NSDictionary *)resourceValuesForKeys:(NSArray *)keys fromBookmarkData:(NSData *)bookmarkData NS_AVAILABLE(10_6, 4_0);

/* Creates an alias file on disk at a specified location with specified bookmark data. bookmarkData must have been created with the NSURLBookmarkCreationSuitableForBookmarkFile option. bookmarkFileURL must either refer to an existing file (which will be overwritten), or to location in an existing directory. If this method returns NO, the optional error is populated.
*/
+ (BOOL)writeBookmarkData:(NSData *)bookmarkData toURL:(NSURL *)bookmarkFileURL options:(NSURLBookmarkFileCreationOptions)options error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Initializes and returns bookmark data derived from an alias file pointed to by a specified URL. If bookmarkFileURL refers to an alias file created prior to OS X v10.6 that contains Alias Manager information but no bookmark data, this method synthesizes bookmark data for the file. If this method returns nil, the optional error is populated.
*/
+ (NSData *)bookmarkDataWithContentsOfURL:(NSURL *)bookmarkFileURL error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Creates and initializes a NSURL that refers to the location specified by resolving the alias file at url. If the url argument does not refer to an alias file as defined by the NSURLIsAliasFileKey property, the NSURL returned is the same as url argument. This method fails and returns nil if the url argument is unreachable, or if the original file or directory could not be located or is not reachable, or if the original file or directory is on a volume that could not be located or mounted. If this method fails, the optional error is populated. The NSURLBookmarkResolutionWithSecurityScope option is not supported by this method.
 */
+ (instancetype)URLByResolvingAliasFileAtURL:(NSURL *)url options:(NSURLBookmarkResolutionOptions)options error:(NSError **)error NS_AVAILABLE(10_10, 8_0);

/*  Given a NSURL created by resolving a bookmark data created with security scope, make the resource referenced by the url accessible to the process. When access to this resource is no longer needed the client must call stopAccessingSecurityScopedResource. Each call to startAccessingSecurityScopedResource must be balanced with a call to stopAccessingSecurityScopedResource (Note: this is not reference counted).
 */
- (BOOL)startAccessingSecurityScopedResource NS_AVAILABLE(10_7, 8_0);

/*  Revokes the access granted to the url by a prior successful call to startAccessingSecurityScopedResource.
 */
- (void)stopAccessingSecurityScopedResource NS_AVAILABLE(10_7, 8_0);

@end


@interface NSURL (NSPromisedItems)

/* Get resource values from URLs of 'promised' items. A promised item is not guaranteed to have its contents in the file system until you use NSFileCoordinator to perform a coordinated read on its URL, which causes the contents to be downloaded or otherwise generated. Promised item URLs are returned by various APIs, including currently:
 - NSMetadataQueryUbiquitousDataScope
 - NSMetadataQueryUbiquitousDocumentsScope
 - An NSFilePresenter presenting the contents of the directory located by -URLForUbiquitousContainerIdentifier: or a subdirectory thereof
 
 The following methods behave identically to their similarly named methods above (-getResourceValue:forKey:error:, etc.), except that they allow you to get resource values and check for presence regardless of whether the promised item's contents currently exist at the URL. You must use these APIs instead of the normal NSURL resource value APIs if and only if any of the following are true:
 - You are using a URL that you know came directly from one of the above APIs
 - You are inside the accessor block of a coordinated read or write that used NSFileCoordinatorReadingImmediatelyAvailableMetadataOnly, NSFileCoordinatorWritingForDeleting, NSFileCoordinatorWritingForMoving, or NSFileCoordinatorWritingContentIndependentMetadataOnly
 
 Most of the NSURL resource value keys will work with these APIs. However, there are some that are tied to the item's contents that will not work, such as NSURLContentAccessDateKey or NSURLGenerationIdentifierKey. If one of these keys is used, the method will return YES, but the value for the key will be nil.
*/
- (BOOL)getPromisedItemResourceValue:(id *)value forKey:(NSString *)key error:(NSError **)error NS_AVAILABLE(10_10, 8_0);
- (NSDictionary *)promisedItemResourceValuesForKeys:(NSArray *)keys error:(NSError **)error NS_AVAILABLE(10_10, 8_0);
- (BOOL)checkPromisedItemIsReachableAndReturnError:(NSError **)error NS_AVAILABLE(10_10, 8_0);

@end



NS_CLASS_AVAILABLE(10_10, 8_0)
// NSURLQueryItem encapsulates a single query name-value pair. The name and value strings of a query name-value pair are not percent encoded. For use with the NSURLComponents queryItems property.
@interface NSURLQueryItem : NSObject <NSSecureCoding, NSCopying> {
@private
    NSString *_name;
    NSString *_value;
}
- (instancetype)initWithName:(NSString *)name value:(NSString *)value NS_DESIGNATED_INITIALIZER;
+ (instancetype)queryItemWithName:(NSString *)name value:(NSString *)value;
@property (readonly) NSString *name;
@property (readonly) NSString *value;
@end


NS_CLASS_AVAILABLE(10_9, 7_0)
@interface NSURLComponents : NSObject <NSCopying>

// Initialize a NSURLComponents with all components undefined. Designated initializer.
- (instancetype)init;

// Initialize a NSURLComponents with the components of a URL. If resolvingAgainstBaseURL is YES and url is a relative URL, the components of [url absoluteURL] are used. If the url string from the NSURL is malformed, nil is returned.
- (instancetype)initWithURL:(NSURL *)url resolvingAgainstBaseURL:(BOOL)resolve;

// Initializes and returns a newly created NSURLComponents with the components of a URL. If resolvingAgainstBaseURL is YES and url is a relative URL, the components of [url absoluteURL] are used. If the url string from the NSURL is malformed, nil is returned.
+ (instancetype)componentsWithURL:(NSURL *)url resolvingAgainstBaseURL:(BOOL)resolve;

// Initialize a NSURLComponents with a URL string. If the URLString is malformed, nil is returned.
- (instancetype)initWithString:(NSString *)URLString;

// Initializes and returns a newly created NSURLComponents with a URL string. If the URLString is malformed, nil is returned.
+ (instancetype)componentsWithString:(NSString *)URLString;

// Returns a URL created from the NSURLComponents. If the NSURLComponents has an authority component (user, password, host or port) and a path component, then the path must either begin with "/" or be an empty string. If the NSURLComponents does not have an authority component (user, password, host or port) and has a path component, the path component must not start with "//". If those requirements are not met, nil is returned.
@property (readonly, copy) NSURL *URL;

// Returns a URL created from the NSURLComponents relative to a base URL. If the NSURLComponents has an authority component (user, password, host or port) and a path component, then the path must either begin with "/" or be an empty string. If the NSURLComponents does not have an authority component (user, password, host or port) and has a path component, the path component must not start with "//". If those requirements are not met, nil is returned.
- (NSURL *)URLRelativeToURL:(NSURL *)baseURL;

// Returns a URL string created from the NSURLComponents. If the NSURLComponents has an authority component (user, password, host or port) and a path component, then the path must either begin with "/" or be an empty string. If the NSURLComponents does not have an authority component (user, password, host or port) and has a path component, the path component must not start with "//". If those requirements are not met, nil is returned.
@property (readonly, copy) NSString *string NS_AVAILABLE(10_10, 8_0);

// Warning: IETF STD 66 (rfc3986) says the use of the format "user:password" in the userinfo subcomponent of a URI is deprecated because passing authentication information in clear text has proven to be a security risk. However, there are cases where this practice is still needed, and so the user and password components and methods are provided.

// Getting these properties removes any percent encoding these components may have (if the component allows percent encoding). Setting these properties assumes the subcomponent or component string is not percent encoded and will add percent encoding (if the component allows percent encoding).
@property (copy) NSString *scheme; // Attempting to set the scheme with an invalid scheme string will cause an exception.
@property (copy) NSString *user;
@property (copy) NSString *password;
@property (copy) NSString *host;
@property (copy) NSNumber *port; // Attempting to set a negative port number will cause an exception.
@property (copy) NSString *path;
@property (copy) NSString *query;
@property (copy) NSString *fragment;

// Getting these properties retains any percent encoding these components may have. Setting these properties assumes the component string is already correctly percent encoded. Attempting to set an incorrectly percent encoded string will cause an exception. Although ';' is a legal path character, it is recommended that it be percent-encoded for best compatibility with NSURL (-stringByAddingPercentEncodingWithAllowedCharacters: will percent-encode any ';' characters if you pass the URLPathAllowedCharacterSet).
@property (copy) NSString *percentEncodedUser;
@property (copy) NSString *percentEncodedPassword;
@property (copy) NSString *percentEncodedHost;
@property (copy) NSString *percentEncodedPath;
@property (copy) NSString *percentEncodedQuery;
@property (copy) NSString *percentEncodedFragment;

// The getter method that underlies the queryItems property parses the query string based on these delimiters and returns an NSArray containing any number of NSURLQueryItem objects, each of which represents a single key-value pair, in the order in which they appear in the original query string.  Note that a name may appear more than once in a single query string, so the name values are not guaranteed to be unique. If the NSURLComponents object has an empty query component, queryItems returns an empty NSArray. If the NSURLComponents object has no query component, queryItems returns nil.
// The setter method that underlies the queryItems property combines an NSArray containing any number of NSURLQueryItem objects, each of which represents a single key-value pair, into a query string and sets the NSURLComponents' query property. Passing an empty NSArray to setQueryItems sets the query component of the NSURLComponents object to an empty string. Passing nil to setQueryItems removes the query component of the NSURLComponents object.
// Note: If a name-value pair in a query is empty (i.e. the query string starts with '&', ends with '&', or has "&&" within it), you get a NSURLQueryItem with a zero-length name and and a nil value. If a query's name-value pair has nothing before the equals sign, you get a zero-length name. If a query's name-value pair has nothing after the equals sign, you get a zero-length value. If a query's name-value pair has no equals sign, the query name-value pair string is the name and you get a nil value.
@property (copy) NSArray *queryItems NS_AVAILABLE(10_10, 8_0);

@end


@interface NSCharacterSet (NSURLUtilities)

// Predefined character sets for the six URL components and subcomponents which allow percent encoding. These character sets are passed to -stringByAddingPercentEncodingWithAllowedCharacters:.

// Returns a character set containing the characters allowed in an URL's user subcomponent.
+ (NSCharacterSet *)URLUserAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

// Returns a character set containing the characters allowed in an URL's password subcomponent.
+ (NSCharacterSet *)URLPasswordAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

// Returns a character set containing the characters allowed in an URL's host subcomponent.
+ (NSCharacterSet *)URLHostAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

// Returns a character set containing the characters allowed in an URL's path component. ';' is a legal path character, but it is recommended that it be percent-encoded for best compatibility with NSURL (-stringByAddingPercentEncodingWithAllowedCharacters: will percent-encode any ';' characters if you pass the URLPathAllowedCharacterSet).
+ (NSCharacterSet *)URLPathAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

// Returns a character set containing the characters allowed in an URL's query component.
+ (NSCharacterSet *)URLQueryAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

// Returns a character set containing the characters allowed in an URL's fragment component.
+ (NSCharacterSet *)URLFragmentAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

@end


@interface NSString (NSURLUtilities)

// Returns a new string made from the receiver by replacing all characters not in the allowedCharacters set with percent encoded characters. UTF-8 encoding is used to determine the correct percent encoded characters. Entire URL strings cannot be percent-encoded. This method is intended to percent-encode an URL component or subcomponent string, NOT the entire URL string. Any characters in allowedCharacters outside of the 7-bit ASCII range are ignored.
- (NSString *)stringByAddingPercentEncodingWithAllowedCharacters:(NSCharacterSet *)allowedCharacters NS_AVAILABLE(10_9, 7_0);

// Returns a new string made from the receiver by replacing all percent encoded sequences with the matching UTF-8 characters.
@property (readonly, copy) NSString *stringByRemovingPercentEncoding NS_AVAILABLE(10_9, 7_0);


/* Adds all percent escapes necessary to convert the receiver into a legal URL string.  Uses the given encoding to determine the correct percent escapes (returning nil if the given encoding cannot encode a particular character).  See CFURLCreateStringByAddingPercentEscapes in CFURL.h for more complex transformations
 */
- (NSString *)stringByAddingPercentEscapesUsingEncoding:(NSStringEncoding)enc;

/* Replaces all percent escapes with the matching characters as determined by the given encoding.  Returns nil if the transformation is not possible (i.e. the percent escapes give a byte sequence not legal in the given encoding).  See CFURLCreateStringByReplacingPercentEscapes in CFURL.h for more complex transformations
 */
- (NSString *)stringByReplacingPercentEscapesUsingEncoding:(NSStringEncoding)enc;

@end


@interface NSURL (NSURLPathUtilities)
    
/* The following methods work on the path portion of a URL in the same manner that the NSPathUtilities methods on NSString do.
 */
+ (NSURL *)fileURLWithPathComponents:(NSArray *)components NS_AVAILABLE(10_6, 4_0);
@property (readonly, copy) NSArray *pathComponents NS_AVAILABLE(10_6, 4_0);
@property (readonly, copy) NSString *lastPathComponent NS_AVAILABLE(10_6, 4_0);
@property (readonly, copy) NSString *pathExtension NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLByAppendingPathComponent:(NSString *)pathComponent NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLByAppendingPathComponent:(NSString *)pathComponent isDirectory:(BOOL)isDirectory NS_AVAILABLE(10_7, 5_0);
@property (readonly, copy) NSURL *URLByDeletingLastPathComponent NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLByAppendingPathExtension:(NSString *)pathExtension NS_AVAILABLE(10_6, 4_0);
@property (readonly, copy) NSURL *URLByDeletingPathExtension NS_AVAILABLE(10_6, 4_0);

/* The following methods work only on `file:` scheme URLs; for non-`file:` scheme URLs, these methods return the URL unchanged.
 */
@property (readonly, copy) NSURL *URLByStandardizingPath NS_AVAILABLE(10_6, 4_0);
@property (readonly, copy) NSURL *URLByResolvingSymlinksInPath NS_AVAILABLE(10_6, 4_0);

@end


#if (TARGET_OS_MAC || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
/* NSFileSecurity encapsulates a file system object's security information. NSFileSecurity and CFFileSecurity are toll-free bridged. Use the CFFileSecurity API for access to the low-level file security properties encapsulated by NSFileSecurity.
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSFileSecurity : NSObject <NSCopying, NSCoding>
- (instancetype) initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
@end
#endif


/* deprecated interfaces
 */

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
/* NSURLClient and NSURLLoading are deprecated; use NSURLConnection instead.
 */

/* Client informal protocol for use with the deprecated loadResourceDataNotifyingClient: below.
 */
@interface NSObject (NSURLClient)
- (void)URL:(NSURL *)sender resourceDataDidBecomeAvailable:(NSData *)newBytes NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)URLResourceDidFinishLoading:(NSURL *)sender NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)URLResourceDidCancelLoading:(NSURL *)sender NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)URL:(NSURL *)sender resourceDidFailLoadingWithReason:(NSString *)reason NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
@end

@interface NSURL (NSURLLoading)
- (NSData *)resourceDataUsingCache:(BOOL)shouldUseCache NS_DEPRECATED(10_0, 10_4, 2_0, 2_0); // Blocks to load the data if necessary.  If shouldUseCache is YES, then if an equivalent URL has already been loaded and cached, its resource data will be returned immediately.  If shouldUseCache is NO, a new load will be started
- (void)loadResourceDataNotifyingClient:(id)client usingCache:(BOOL)shouldUseCache NS_DEPRECATED(10_0, 10_4, 2_0, 2_0); // Starts an asynchronous load of the data, registering delegate to receive notification.  Only one such background load can proceed at a time.
- (id)propertyForKey:(NSString *)propertyKey NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

/* These attempt to write the given arguments for the resource specified by the URL; they return success or failure
 */
- (BOOL)setResourceData:(NSData *)data NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (BOOL)setProperty:(id)property forKey:(NSString *)propertyKey NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

- (NSURLHandle *)URLHandleUsingCache:(BOOL)shouldUseCache NS_DEPRECATED(10_0, 10_4, 2_0, 2_0); // Sophisticated clients will want to ask for this, then message the handle directly.  If shouldUseCache is NO, a newly instantiated handle is returned, even if an equivalent URL has been loaded
@end
#endif
