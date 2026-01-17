//
//  NSFileProviderExtension.h
//
//  Copyright (c) 2014-2017 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderItem.h>

NS_ASSUME_NONNULL_BEGIN

@class NSFileProviderDomain;

/**
 NSFileProviderItemFieldContents corresponds to the item's contents.

 Each subsequent field corresponds to a property on NSFileProviderItem that can
 change.
 */
typedef NS_OPTIONS(NSUInteger, NSFileProviderItemField) {
    NSFileProviderItemFieldContents = 1 << 0,
    NSFileProviderItemFieldFilename = 1 << 1,
    NSFileProviderItemFieldParentItemIdentifier = 1 << 2,
    NSFileProviderItemFieldLastUsedDate = 1 << 3,
    NSFileProviderItemFieldTagData = 1 << 4,
    NSFileProviderItemFieldFavoriteRank = 1 << 5,
    NSFileProviderItemFieldCreationDate = 1 << 6,
    NSFileProviderItemFieldContentModificationDate = 1 << 7,
    NSFileProviderItemFieldFlags = 1 << 8,
    NSFileProviderItemFieldTrashed = 1 << 9,
    NSFileProviderItemFieldExtendedAttributes = 1 << 10
} API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@interface NSFileProviderExtension : NSObject

- (nullable NSFileProviderItem)itemForIdentifier:(NSFileProviderItemIdentifier)identifier error:(NSError * _Nullable *)error NS_SWIFT_NAME(item(for:)) API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

/**
 Download the item for the given identifier and return it via the completion handler.

 The system learns of items through enumerations. Initially, this means that the
 system is aware that an item (with a specific version) exists on the device.

 When the user accesses the item, the system makes a request for the contents of
 the item. The provider can then fulfill the request by providing the item.

 The system takes ownership of the item and will move it out of the sandbox of
 the provider.

 The requestedVersion parameter specifies which version should be returned. A nil value
 means that the latest known version should be returned. Except for the error case, the
 version of the returned item is assumed to be identical to what was requested.
 */
- (NSProgress *)fetchContentsForItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                                           version:(nullable NSFileProviderItemVersion *)requestedVersion
                                 completionHandler:(void(^)(NSURL * _Nullable fileContents, NSFileProviderItem _Nullable item, NSError * _Nullable error))completionHandler  NS_SWIFT_NAME(fetchContents(for:version:completionHandler:)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

/**
 Update a previously provided item to a new version.

 If the system already has a version of an item and learns that a new version is
 available, it may call this method to update the existing version to a new
 version.

 The semantics of the requestedVersion parameter are the same as for the non-delta update method above.
 */
- (NSProgress *)fetchContentsForItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                                           version:(nullable NSFileProviderItemVersion *)requestedVersion
                        usingExistingContentsAtURL:(NSURL *)existingContents
                                   existingVersion:(NSFileProviderItemVersion *)existingVersion
                                 completionHandler:(void(^)(NSURL * _Nullable fileContents, NSFileProviderItem _Nullable item, NSError * _Nullable error))completionHandler
NS_SWIFT_NAME(fetchContents(for:version:usingExistingContentsAt:existingVersion:completionHandler:))
API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

/**
 Informs the provider that an item or its metadata have changed. More than one
 property may have changed, e.g.  an item may have been renamed, moved and also
 changed contents, in which case changedFields might contain [.contents,
 .filename, .parentItemIdentifier, .contentModificationDate].

 The provider should merge the changes into the current item state, persist them
 to disk, then call the completion callback with the updated, merged item. At a
 later point, the provider should sync the changes to the server.

 If the completion block is called with an error, the behavior of the system
 depends on the exact error: in an interactive scenario, the error will be
 presented to the user. Otherwise, depending on the error the system will either
 retry at a later time or drop the modifications.
 */
- (void)itemChanged:(NSFileProviderItem)item
        baseVersion:(NSFileProviderItemVersion *)version
      changedFields:(NSFileProviderItemField)changedFields
           contents:(nullable NSURL *)newContents
  completionHandler:(void(^)(NSFileProviderItem _Nullable item, NSError * _Nullable error))completionHandler API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

@end

/**
 Options passed on item creation.
 */
typedef NS_OPTIONS(NSUInteger, NSFileProviderCreateItemOptions) {
    /**
     The imported item may already exists.

     This can happen because:

     1. The imported item was found on disk after the synchronisation state was
     lost, for example following the restoration of a backup, or the migration
     to a new device.

     2. Two directories are merged together. Each child resulting of the merge
     may be recreated with the .mayAlreadyExists option. This allows the
     extension to recursively merge directories.

     The Extension should assess whether the item could actually be a disk
     representation of an already existing item.

     Since this can happens when the system has to reimport all the existing
     item from disk, it is advised that the assessment method avoids
     computational intensive tasks, such as checksumming the item.

     When all the items pending reimport have been processed, the system
     will call -[NSFileProviderExtension importDidFinishWithCompletionHandler:].
     */
    NSFileProviderCreateItemOptionsItemMayAlreadyExist = 1 << 0,
} API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

@interface NSFileProviderExtension (CreateItem)

/**
 Create a new item.

 This is expected to complete before doing any network.

 The itemTemplate object describes the expected state of the newly created item,
 including its location provided by parentItemIdentifier and filename. The list
 of fields to conside in that object is defined by the fields parameter. Fields
 not listed should be considered as not being defined.

 The itemIdentifier of \the itemTemplate should not be accessed and is actual
 value is not defined. Importing the item should assign a unique itemIdentifier
 to the newly imported item.

 In the completion block, the createdItem is expected to have its properties
 matching the values of the item properties with the exception of the
 itemIdentifier that should be a newly allocated identifier.

 If the item is a document, the contents should be fetched from provided
 URL. Otherwise url will be nil. In case the NSFileProviderCreateItemOptionsItemMayAlreadyExist
 is passed, the content may be nil if the item is found by the system without any
 associated content. In that case, you should return a nil item if you are not
 able to match the imported item with existing items from the provider.

 The provider can indicates it has merged the new item into an existing one by
 returning an item with the identifier of the existing one. Only merging directories
 is supported.

 Note that the itemIdentifier on the returned item should be assigned without a
 network call.  It doesn't have to be the final identifier.  If the identifier
 changes after talking to the server then the file provider should send a delete
 for the temporary, local identifier immediately followed by an add with the
 final identifier.

 This is expected to work offline even if there might be a collision (two items
 are at the same location) only detected when later syncing up this change to
 the server.  In that case, it is suggested that a follow up update to the item
 change its filename to something unique.  This wouldn't be considered an error
 to import.

 If the imported item is refused by the extension, it should return nil for the
 createdItem without any error. In that case, the source item will be deleted
 from disk. If the extension does not wish to synchronise the item, while still
 keeping it on disk, it should still import it locally, but not sync it to its
 server, and return a valid createItem object.

 If however you can tell right away, with no communication to your server, that
 there is a collision then this call should fail with error code
 NSFileProviderErrorFilenameCollision generated with this method:
 -[NSError (NSFileProviderError) fileProviderErrorForCollisionWithItem:].

 The existing item set in this error will be used to handle the collision, and
 ask the user if she or he would like to replace the existing item.  This takes
 into account the existing item's capabilities (particularly
 NSFileProviderItemCapabilitiesAllowsTrashing and AllowsDeleting.)

 Upload errors (such as NSFileProviderErrorInsufficientQuota) should be handled
 with a subsequent update to the item, setting its uploadingError property.
 Upload errors should not prevent creating or importing a document, because they
 can be resolved at a later date (for example, when the user has quota again.)

 Other errors will be presented to the user, but are unexpected.  If you want to
 prevent imports in a given directory, then the directory item's capacities
 should exclude NSFileProviderItemCapabilitiesAllowsAddingSubItems.
 */
- (void)createItemBasedOnTemplate:(NSFileProviderItem)itemTemplate
                           fields:(NSFileProviderItemField)fields
                         contents:(nullable NSURL *)url
                          options:(NSFileProviderCreateItemOptions)options
                completionHandler:(void (^)(NSFileProviderItem _Nullable createdItem, NSError * _Nullable error))completionHandler
    NS_SWIFT_NAME(createItem(basedOn:fields:contents:options:completionHandler:))
    API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

@end

/**
 Options passed on item deletion.
 */
typedef NS_OPTIONS(NSUInteger, NSFileProviderDeleteItemOptions) {
    NSFileProviderDeleteItemOptionsRecursive = 1 << 0
} API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

@interface NSFileProviderExtension (DeleteItem)

/**
 Delete an item forever.

 This is called when the user deletes an item that was already in the Trash and
 the item should no longer appear there after this call.  This call should
 remove the item from the working set.

 This call receives an optional baseVersion which represent the version of the
 item we are trying to delete.  The extension may fail with
 NSFileProviderErrorVersionOutOfDate if the item does not match the provided
 baseVersion.

 Unless the NSFileProviderDeleteItemOptionsRecursive options is passed, the
 deletion of a directory should be non-recursive and the call must fail with
 NSFileProviderErrorDirectoryNotEmpty if the directory contains some children.

 Delete is gated by the capabilities of the removed item with
 NSFileProviderItemCapabilitiesAllowsDeleting.
 */
- (void)deleteItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                     baseVersion:(NSFileProviderItemVersion *)version
                         options:(NSFileProviderDeleteItemOptions)options
               completionHandler:(void (^)(NSError * _Nullable))completionHandler API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

@end

@interface NSFileProviderExtension (Import)

/** Signal the end of import of on-disk items.

 This is called after an import of on-disk items has been triggered by either
 -[NSFileProviderManager reimportItemsBelowItemWithIdentifier:completionHandler:] or
 +[NSFileProviderManager importDomain:fromDirectoryAtURL:completionHandler:]. A
 reimport can also be started by the system independently from any request by the
 provider.

 During import, found items will be created via the
 -[NSFileProviderExtension createItemBasedOnTemplate:fields:contents:options:completionHandler:]
 call with the NSFileProviderCreateItemOptionsItemMayAlreadyExist flag set.
 At the end of an import the -[NSFileProviderExtension importDidFinishWithCompletionHandler:]
 is called.
 */
- (void)importDidFinishWithCompletionHandler:(void (^)(void))completionHandler
API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

@end

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

/**
 Should return the URL corresponding to a specific identifier. Fail if it's not
 a subpath of documentStorageURL.

 This is a static mapping; each identifier must always return a path
 corresponding to the same file. By default, this returns the path relative to
 the path returned by documentStorageURL.
 */
- (nullable NSURL *)URLForItemWithPersistentIdentifier:(NSFileProviderItemIdentifier)identifier API_DEPRECATED("No longer called", ios(8.0, 13.0)) API_UNAVAILABLE(tvos, watchos) API_UNAVAILABLE(macos);
- (nullable NSFileProviderItemIdentifier)persistentIdentifierForItemAtURL:(NSURL *)url API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos, watchos) API_UNAVAILABLE(macos);

/**
 This method is called when a placeholder URL should be provided for the item at
 the given URL.

 The implementation of this method should call +[NSFileProviderManager
 writePlaceholderAtURL:withMetadata:error:] with the URL returned by
 +[NSFileProviderManager placeholderURLForURL:], then call the completion
 handler.
 */
- (void)providePlaceholderAtURL:(NSURL *)url completionHandler:(void (^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos, watchos) API_UNAVAILABLE(macos);

/**
 Should ensure that the actual file is in the position returned by
 URLForItemWithPersistentIdentifier:, then call the completion handler.
 */
- (void)startProvidingItemAtURL:(NSURL *)url completionHandler:(void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(startProvidingItem(at:completionHandler:)) API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos, watchos) API_UNAVAILABLE(macos);

/**
 Called after the last claim to the file has been released. At this point, it is
 safe for the file provider to remove the content file.

 Care should be taken that the corresponding placeholder file stays behind after
 the content file has been deleted.
 */
- (void)stopProvidingItemAtURL:(NSURL *)url NS_SWIFT_NAME(stopProvidingItem(at:)) API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos, watchos) API_UNAVAILABLE(macos);

/**
 Called at some point after the file has changed; the provider may then trigger
 an upload.
 */
- (void)itemChangedAtURL:(NSURL *)url API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos, watchos) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END
