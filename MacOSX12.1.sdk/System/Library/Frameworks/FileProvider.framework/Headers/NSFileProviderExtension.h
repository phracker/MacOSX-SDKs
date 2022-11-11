//
//  NSFileProviderExtension.h
//
//  Copyright (c) 2014-2020 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderItem.h>

NS_ASSUME_NONNULL_BEGIN

@class NSFileProviderDomain;

FILEPROVIDER_API_AVAILABILITY_V1
@interface NSFileProviderExtension : NSObject

- (nullable NSFileProviderItem)itemForIdentifier:(NSFileProviderItemIdentifier)identifier error:(NSError * _Nullable *)error NS_SWIFT_NAME(item(for:)) FILEPROVIDER_API_AVAILABILITY_V2;

/**
 Should return the URL corresponding to a specific identifier. Fail if it's not
 a subpath of documentStorageURL.

 This is a static mapping; each identifier must always return a path
 corresponding to the same file. By default, this returns the path relative to
 the path returned by documentStorageURL.
 */
- (nullable NSURL *)URLForItemWithPersistentIdentifier:(NSFileProviderItemIdentifier)identifier;
- (nullable NSFileProviderItemIdentifier)persistentIdentifierForItemAtURL:(NSURL *)url;

/**
 This method is called when a placeholder URL should be provided for the item at
 the given URL.

 The implementation of this method should call +[NSFileProviderManager
 writePlaceholderAtURL:withMetadata:error:] with the URL returned by
 +[NSFileProviderManager placeholderURLForURL:], then call the completion
 handler.
 */
- (void)providePlaceholderAtURL:(NSURL *)url completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/**
 Should ensure that the actual file is in the position returned by
 URLForItemWithPersistentIdentifier:, then call the completion handler.
 */
- (void)startProvidingItemAtURL:(NSURL *)url completionHandler:(void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(startProvidingItem(at:completionHandler:));

/**
 Called after the last claim to the file has been released. At this point, it is
 safe for the file provider to remove the content file.

 Care should be taken that the corresponding placeholder file stays behind after
 the content file has been deleted.
 */
- (void)stopProvidingItemAtURL:(NSURL *)url NS_SWIFT_NAME(stopProvidingItem(at:));

/**
 Called at some point after the file has changed; the provider may then trigger
 an upload.
 */
- (void)itemChangedAtURL:(NSURL *)url;

@end

FILEPROVIDER_API_AVAILABILITY_V2
@interface NSFileProviderExtension (Deprecated)

/**
 Writes out a placeholder at the specified URL. The URL should be one returned
 by placeholderURLForURL:; if URL resource values are requested, the system will
 consult the placeholder before consulting your app extension.

 Metadata contains NSURLNameKey, NSURLFileSizeKey, NSURLIsPackageKey.
 */
+ (BOOL)writePlaceholderAtURL:(NSURL *)placeholderURL withMetadata:(NSDictionary <NSURLResourceKey, id> *)metadata error:(NSError **)error API_DEPRECATED("Use the corresponding method on NSFileProviderManager instead", ios(8.0, 11.0)) API_UNAVAILABLE(macos, tvos, watchos);

/**
 Returns the designated placeholder URL for a given URL. This placeholder will
 be consulted before falling back to your app extension to enhance
 performance. To write out a placeholder, use the writePlaceHolderAtURL: method
 above.
 */
+ (NSURL *)placeholderURLForURL:(NSURL *)url API_DEPRECATED_WITH_REPLACEMENT("NSFileProviderManager +placeholderURLForURL:", ios(8.0, 11.0)) API_UNAVAILABLE(macos, tvos, watchos);

/**
 An identifier unique to this provider.

 When modifying the files stored in the directory returned by
 documentStorageURL, you should pass this identifier to your file coordinator's
 setPurposeIdentifier: method.
 */
@property(nonatomic, readonly) NSString *providerIdentifier API_DEPRECATED_WITH_REPLACEMENT("NSFileProviderManager -providerIdentifier", ios(8.0, 11.0)) API_UNAVAILABLE(macos, tvos, watchos);

/**
 The root URL for provided documents. This URL is derived by consulting the
 NSExtensionFileProviderDocumentGroup property on your extension. The document
 storage URL is the folder "File Provider Storage" in the corresponding
 container.
 */
@property(nonatomic, readonly) NSURL *documentStorageURL API_DEPRECATED_WITH_REPLACEMENT("NSFileProviderManager -documentStorageURL", ios(8.0, 11.0)) API_UNAVAILABLE(macos, tvos, watchos);

@end

NS_ASSUME_NONNULL_END
