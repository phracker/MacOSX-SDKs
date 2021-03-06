//
//  NSFileProviderManager.h
//  FileProvider
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderItem.h>
#import <FileProvider/NSFileProviderDomain.h>
#import <FileProvider/NSFileProviderEnumerating.h>

NS_ASSUME_NONNULL_BEGIN

@class NSURLSessionTask;
@class NSFileProviderDomain;
@class NSFileProviderRequest;

/**
 The file provider manager allows you to communicate with the file provider
 framework from both the extension and related processes.

 NSFileProviderManager can be used from the following processes:
 - the extension
 - the main app containing the extension
 - sibling extensions to the extension
 - executables contained in the main app bundle (on macOS only)

 Executables contained in the main app bundle need to have a bundle identifier that is
 prefixed by the bundle identifier of the main app (note that this is generally required
 for extensions). They must also have access to the document group defined for the provider
 (via its `NSExtensionFileProviderDocumentGroup` key).

 The file provider framework will invoke your file provider extension in response
 to those calls if appropriate.

 The class also provides methods to manage provider domains. Each domain has a
 corresponding manager.
 */
FILEPROVIDER_API_AVAILABILITY_V2_V3
@interface NSFileProviderManager : NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
Return the manager responsible for the default domain.
 */
@property (class, readonly, strong) NSFileProviderManager *defaultManager API_UNAVAILABLE(macos);

/**
 Return the manager for the specified domain.
 */
+ (nullable instancetype)managerForDomain:(NSFileProviderDomain *)domain;

/**
 Call this method either in the app or in the extension to trigger an
 enumeration, typically in response to a push.

 Set the containerItemIdentifier to the identifier of the enumerated container
 that was specified in
 -[NSFileProviderExtension enumeratorForContainerItemIdentifier:error:]

 This will trigger another call to
 -[NSFileProviderEnumerator enumerateChangesForObserver:fromSyncAnchor:]
 and the UI will be refreshed, giving the user live updates on the presented
 enumeration.

 If you have a change in the working set, call this method with
 containerItemIdentifier set to NSFileProviderWorkingSetContainerItemIdentifier,
 even if there is no live enumeration for this item.  The working set is cached
 on the device and it's important to keep the cache in sync.

 In addition to using this method, your application/extension can register for
 pushes using the PKPushTypeFileProvider push type. Pushes of the form
 {
     container-identifier = "<identifier>"
     domain = "<domain identifier>"
 }
 with a topic of "<your application identifier>.pushkit.fileprovider" will be
 translated into a call to signalEnumeratorForContainerItemIdentifier:completionHandler:.
 */
- (void)signalEnumeratorForContainerItemIdentifier:(NSFileProviderItemIdentifier)containerItemIdentifier completionHandler:(void (^)(NSError * __nullable error))completion NS_SWIFT_NAME(signalEnumerator(for:completionHandler:));

/**
 Return the user visible URL for an item identifier.

 The caller must use file coordination (see NSFileCoordinator) if it wishes to read the
 content or list the children of the URL. The caller should not try to manipulate files
 in the user visible location. All changes coming from the provider should go through
 updates in the working set that will be applied to the user visible items by the
 system.
 */
- (void)getUserVisibleURLForItemIdentifier:(NSFileProviderItemIdentifier)itemIdentifier completionHandler:(void (^)(NSURL * __nullable userVisibleFile, NSError * __nullable error))completionHandler FILEPROVIDER_API_AVAILABILITY_V3 NS_SWIFT_NAME(getUserVisibleURL(for:completionHandler:));

/**
 Return the identifier and domain for a user visible URL.

 This method returns the identifier and domain of a user visible URL if
 applicable. Calling this method on a file which doesn't reside in your
 provider/domain, or which hasn't yet been assigned an identifier by
 the provider will return the Cocoa error NSFileNoSuchFileError.
 */
+ (void)getIdentifierForUserVisibleFileAtURL:(NSURL *)url completionHandler:(void (^)(NSFileProviderItemIdentifier __nullable itemIdentifier, NSFileProviderDomainIdentifier __nullable domainIdentifier, NSError * __nullable error))completionHandler FILEPROVIDER_API_AVAILABILITY_V3;

/**
 Registers the given NSURLSessionTask to be responsible for the specified item.
 A given item can only have one task registered at a time. The task must be
 suspended at the time of calling.
 The task's progress is displayed on the item when the task is executed.
 */
- (void)registerURLSessionTask:(NSURLSessionTask *)task forItemWithIdentifier:(NSFileProviderItemIdentifier)identifier completionHandler:(void (^)(NSError * __nullable error))completion;




/**
 The purpose identifier of your file provider extension. A coordination using a
 file coordinator with this purpose identifier set will not trigger your file
 provider extension. You can use this to e.g. perform speculative work on behalf
 of the file provider from the main app.
 */
@property(nonatomic, readonly) NSString *providerIdentifier FILEPROVIDER_API_AVAILABILITY_V2;

/**
 The root URL for provided documents. This URL is derived by consulting the
 NSExtensionFileProviderDocumentGroup property on your extension. The document
 storage URL is the folder "File Provider Storage" in the corresponding
 container.

 If the NSExtensionFileProviderDocumentGroup property is not set, calling this
 method will result in an error.
 */
@property(nonatomic, readonly) NSURL *documentStorageURL FILEPROVIDER_API_AVAILABILITY_V2;

/**
 A temporary directory suitable to store files that will be exchanged with the system.

 The returned URL is guaranteed to be on the same volume as the user visible URL, making sure the system
 can atomatically clone/move files from that location to the user visible URL. The provider can also use
 that directory as a target for moves and clones of content URL passed to createItemBasedOnTemplate
 or modifyItem.

 If the system cannot find a suitable directory, this calls will fail. This could happen e.g. if the domain
 does not exist.

 This call will not fail when called from the extension process with an active instance of the extension
 for that domain.
 */
- (nullable NSURL *)temporaryDirectoryURLWithError:(NSError **)error FILEPROVIDER_API_AVAILABILITY_V3;

/**
 Writes out a placeholder at the specified URL. The placeholder is used in place
 of the actual file for operations that do not require the file's actual data to
 be on disk:
 - if attributes are requested by an application via the
 getPromisedItemResourceValue: method on NSURL
 - or via a coordination with the
 NSFileCoordinatorReadingImmediatelyAvailableMetadataOnly flag set
 - to verify whether an application has access to a file

 Your extension should provide placeholders by implementing the
 providePlaceholderAtURL: method, but your application may choose to proactively
 write out placeholders to facilitate access to files. This is especially useful
 if your application wants to actively hand out a file URL, e.g. using
 UIActivityViewController, in which case it should ensure that either the file
 or a placeholder is present on disk first.

 The path of the placeholder is fixed and must be determined in advance by
 calling the placeholderURLForURL: method.
 */
+ (BOOL)writePlaceholderAtURL:(NSURL *)placeholderURL
                 withMetadata:(NSFileProviderItem)metadata
                        error:(NSError **)error FILEPROVIDER_API_AVAILABILITY_V2;

/**
 Returns the designated placeholder URL for a given file URL. Used in
 conjunction with writePlaceholderAtURL.
 */
+ (NSURL *)placeholderURLForURL:(NSURL *)url FILEPROVIDER_API_AVAILABILITY_V2;

/**
 Register a domain in which items can be stored.
 */
+ (void)addDomain:(NSFileProviderDomain *)domain completionHandler:(void(^)(NSError *_Nullable error))completionHandler;

/**
 Remove a domain.
 */
+ (void)removeDomain:(NSFileProviderDomain *)domain completionHandler:(void(^)(NSError *_Nullable error))completionHandler;

/**
 Get all registered domains.
 */
+ (void)getDomainsWithCompletionHandler:(void (^)(NSArray<NSFileProviderDomain *> *domains, NSError * _Nullable error))completionHandler;

/**
 Remove all registered domains.
 */
+ (void)removeAllDomainsWithCompletionHandler:(void(^)(NSError *_Nullable error))completionHandler;

/**
 Cancel throttling applied by the system to any item because of that error.
 
 This call supports 3 types of errors:
 - NSFileProviderErrorNotAuthenticated
 - NSFileProviderErrorInsufficientQuota
 - NSFileProviderErrorServerUnreachable
 */
- (void)signalErrorResolved:(NSError *)error completionHandler:(void(^)(NSError *_Nullable error))completionHandler
    FILEPROVIDER_API_AVAILABILITY_V3;

@end

@interface NSFileProviderManager (MaterializedSet)

/**
 Returns an enumerator for the set of materialized containers.

 This enumerator is unlike other enumerators because the roles of the system
 and the app/extension are reversed:
 - The system enumerates the working set after the extension calls
   'signalEnumeratorForContainerItemIdentifier';
 - The app/extension enumerates the materialized set after the system calls
   'materializedItemsDidChangeWithCompletionHandler'.
 */
- (id<NSFileProviderEnumerator>)enumeratorForMaterializedItems FILEPROVIDER_API_AVAILABILITY_V3;

@end

@interface NSFileProviderManager (Import)

/** Request the creation of a new domain that will take ownership of on-disk data that
 were previously managed without a file provider.

 You can use this method in order to migrate from a software that managed a file hierarchy
 on disk to a NSFileProviderExtension without having to redownload the data that was
 already on disk.

 The URL is expected to point to a directory. That directory will be moved away, its
 ownership being taken by the system. From this point, your extension's
 createItemFromTemplate method will be called for every item found in the directory
 with the special NSFileProviderCreateItemMayAlreadyExist option.

 In case a domain with the same name already exists in the file provider manager, the
 call will fail with the code NSFileWriteFileExistsError. The URL will remain untouched.
 In case the system does not allow the extension to request a migration, the call will
 fail with NSFeatureUnsupportedError.

 In case of success, the URL will become invalid and the domain will be created. The
 completion handler is called as soon as the domain is created. Your provider will
 receive calls to createItemBasedOnTemplate afterward.

 When the import of the file hierarchy is finished, the system calls
 -[NSFileProviderExtension signalDidFinishImportingItemsFromDiskWithCompletionHandler:].
 In case -[NSFileProviderManager reimportItemsBelowItemWithIdentifier:completionHandler:]
 is called before the end of the import, a single call to importDidFinishWithCompletionHandler
 will be received for both the import and the scan.
 */
+ (void)importDomain:(NSFileProviderDomain *)domain fromDirectoryAtURL:(NSURL *)url completionHandler:(void(^)(NSError * _Nullable error))completionHandler
    FILEPROVIDER_API_AVAILABILITY_V3;

/** Notify the system that the itemIdentifiers known by the system are not valid anymore.

 This can be called by an extension in case it has lost track of its synchronisation state
 and as a consequence is not able to guarantee the stability of the itemIdentifiers anymore.
 In that case, the system will trigger a scan of any data that is cached on disk and call
 createItemBasedOnTemplate with the special NSFileProviderCreateItemMayAlreadyExist
 option so that the extension can specify the new itemIdentifier for those items. The provided
 item identifier is inclusive, meaning the specified item will be re-import as well as any
 children in case it is a container.

 In case the extension has lost its synchronisation state but is still able to guarantee the
 stability of the itemIdentifiers, it should make sure that querying the working set
 enumerator with an anchor that predates the synchronisation loss will cause a
 NSFileProviderErrorSyncAnchorExpired error.

 In case the extension has lost its synchronisation state and is not interested in preserving
 the data cached on disk, it can remove and re-add the affected domain.

 The completion handler is called immediately and does not reflect the end of the import.
 When the import of the file hierarchy is finished, the system calls
 -[NSFileProviderExtension importDidFinishWithCompletionHandler:].

 If this method succeeds, the system will reimport at least the requested sub-tree, but may
 import more.

 If the requested item has no on-disk representation, the completion handler will be called with
 a NSFileProviderErrorNoSuchItem error.
 */
- (void)reimportItemsBelowItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                           completionHandler:(void (^)(NSError * _Nullable error))completionHandler
    NS_SWIFT_NAME(reimportItems(below:completionHandler:))
    FILEPROVIDER_API_AVAILABILITY_V3;

@end

@interface NSFileProviderManager (Eviction)

/**
 Request that the system removes an item from its cache.

 This removes the contents of a file, or the metadata and contents of all the
 files in a directory.

 Note that directory eviction is not available yet. Attempt to evict a directory will
 fail with NSCocoaErrorDomain.NSFeatureUnsupportedError.

 The completion handler is called when the item has been evicted from disk.
 */
- (void)evictItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
              completionHandler:(void (^)(NSError * _Nullable error))completionHandler
    NS_SWIFT_NAME(evictItem(identifier:completionHandler:))
    FILEPROVIDER_API_AVAILABILITY_V3;

@end

@interface NSFileProviderManager (Barrier)

/**
 Wait for all changes on disk in the sub-hierarchy of the item to be acknowledged by the extension.

 This call can be used to guarantee operation ordering in a sub-hierarchy of the provider. The completion
 handler is called when all the changes for descendents of the item have been acknowledged by the extension.
 If any error is met during that process, an error will be raised, in which case the caller should not
 assume all the changes have been received.

 This call will only wait for changes affecting items that were descendents (recursively) of the requested
 item, but will not consider the item itself. As a consequence, that call can be used from within a call
 to -[NSFileProviderReplicatedExtension modifyItem:baseVersion:changedFields:contents:options:completionHandler:].
 Also note that the call will return immediately on items that are not directories.
 */
- (void)waitForChangesOnItemsBelowItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                                   completionHandler:(void (^)(NSError * _Nullable error))completionHandler
    NS_SWIFT_NAME(waitForChanges(below:completionHandler:))
    FILEPROVIDER_API_AVAILABILITY_V3;
@end

@interface NSFileProviderManager (Stabilization)

/**
 Wait for stabilization of the domain.

 The system will wait until it is caught up with the file system's changes up to
 the time of the call, then wait until it is caught up with the provider's changes up to
 the time of the call.

 The completion handler is called when both sets of changes are caught up to at least the time
 of the call. This is useful to enforce a consistent state for testing.
 */
- (void)waitForStabilizationWithCompletionHandler:(void(^)(NSError * _Nullable error))completionHandler FILEPROVIDER_API_AVAILABILITY_V3;
@end

typedef NS_OPTIONS(NSUInteger, NSFileProviderManagerDisconnectionOptions) {
    /*
     A temporary disconnection would be used during e.g. an update; a non-temporary disconnection would be used in preparation of a log-out.
     */
    NSFileProviderManagerDisconnectionOptionsTemporary = 1 << 0,
} FILEPROVIDER_API_AVAILABILITY_V3 NS_SWIFT_NAME(NSFileProviderManager.DisconnectionOptions);

@interface NSFileProviderManager (Disconnection)
- (void)disconnectWithReason:(NSString *)localizedReason
                     options:(NSFileProviderManagerDisconnectionOptions)options
           completionHandler:(void(^)(NSError * _Nullable error))completionHandler FILEPROVIDER_API_AVAILABILITY_V3
    NS_SWIFT_NAME(disconnect(reason:options:completionHandler:));

- (void)reconnectWithCompletionHandler:(void(^)(NSError * _Nullable error))completionHandler FILEPROVIDER_API_AVAILABILITY_V3;
@end

NS_ASSUME_NONNULL_END
