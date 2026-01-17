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
#import <FileProvider/NSFileProviderModifyItemOptions.h>

NS_ASSUME_NONNULL_BEGIN

@class NSURLSessionTask;
@class NSFileProviderRequest;


typedef NS_ENUM(NSInteger, NSFileProviderDomainRemovalMode) {
    /// Don't keep any files that are current in the domain
    NSFileProviderDomainRemovalModeRemoveAll FILEPROVIDER_API_AVAILABILITY_V4_0_IOS = 0,

    /// Delete the domain from the system but keeps the at least all the
    /// dirty corresponding user data around.
    NSFileProviderDomainRemovalModePreserveDirtyUserData FILEPROVIDER_API_AVAILABILITY_V4_0 = 1,

    /// Delete the domain from the system but keeps all the downloaded
    /// corresponding user data around.
    NSFileProviderDomainRemovalModePreserveDownloadedUserData FILEPROVIDER_API_AVAILABILITY_V4_0 = 2,
} NS_SWIFT_NAME(NSFileProviderManager.DomainRemovalMode) FILEPROVIDER_API_AVAILABILITY_V4_0_IOS;

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

 When using NSFileProviderExtension, the system will enumerate containers
 while the user is viewing them in the UI. If there are changes to the container
 while an enumerator is open, call this method with the identifier of that
 container. This will trigger another call to
 -[NSFileProviderEnumerator enumerateChangesForObserver:fromSyncAnchor:] on
 that enumerator, and the UI will be refreshed, giving the user live updates on
 the presented enumeration.

 If there are changes in the working set, call this method with
 containerItemIdentifier set to NSFileProviderWorkingSetContainerItemIdentifier,
 even if there is no live enumeration for the working set container.

 When using NSFileProviderReplicatedExtension, only call this
 method with NSFileProviderWorkingSetContainerItemIdentifier. Other container
 identifiers are ignored. The system will automatically propagate
 working set changes to the UI, without explicitly signaling the
 containers currently being viewed in the UI.

 In addition to using this method, your application/extension can register for
 pushes using the PKPushTypeFileProvider push type. Pushes of the form
 {
     "container-identifier": "<identifier>",
     "domain": "<domain identifier>"
 }
 with a topic of "<your application identifier>.pushkit.fileprovider" will be
 translated into a call to signalEnumeratorForContainerItemIdentifier:completionHandler:.
 */
- (void)signalEnumeratorForContainerItemIdentifier:(NSFileProviderItemIdentifier)containerItemIdentifier completionHandler:(void (^)(NSError * __nullable error))completion NS_SWIFT_NAME(signalEnumerator(for:completionHandler:));

/**
 Return the security scoped URL to the user visible location for an item identifier.

 The caller must use file coordination (see NSFileCoordinator) if it wishes to read the
 content or list the children of the URL. The caller should not try to manipulate files
 in the user visible location. All changes coming from the provider should go through
 updates in the working set that will be applied to the user visible items by the
 system.

 The location may differ from the logical parentURL/filename.
 If an item on disk cannot be assigned the requested name (e.g. because the local
 file system has different case collision rules from the provider), one of the items can be assigned
 a different local name. In that case, the "com.apple.fileprovider.before-bounce#PX" extended
 attribute will contain the filename before collision resolution.
 This attribute is only set if the item has been assigned a different local name following
 a collision. Such local names are not synced up to the provider; the purpose of the attribute is
 to enable consistency checkers to detect this case.

 Before accessing the content of the returned URL, the caller must call `-[NSURL startAccessingSecurityScopedResource]
 on the returned URL and call `-[NSURL stopAccessingSecurityScopedResource]` when done accessing the content.

 The returned URL grants read-write access to the user visible location for the corresponding item.

 On iOS, for replicated domains, the extension process will never be granted access to the user
 visible location, this function will always fail with `NSFileReadNoPermissionError`.
 */
- (void)getUserVisibleURLForItemIdentifier:(NSFileProviderItemIdentifier)itemIdentifier completionHandler:(void (^)(NSURL * __nullable userVisibleFile, NSError * __nullable error))completionHandler FILEPROVIDER_API_AVAILABILITY_V3_IOS NS_SWIFT_NAME(getUserVisibleURL(for:completionHandler:));

/**
 Return the identifier and domain for a user visible URL.

 This method returns the identifier and domain of a user visible URL if
 applicable. Calling this method on a file which doesn't reside in your
 provider/domain, or which hasn't yet been assigned an identifier by
 the provider will return the Cocoa error NSFileNoSuchFileError.
 */
+ (void)getIdentifierForUserVisibleFileAtURL:(NSURL *)url completionHandler:(void (^)(NSFileProviderItemIdentifier __nullable itemIdentifier, NSFileProviderDomainIdentifier __nullable domainIdentifier, NSError * __nullable error))completionHandler FILEPROVIDER_API_AVAILABILITY_V3_IOS;

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
 does not exist or is in instance of initialization.

 This call succeeds when called from the extension process with an instance of the extension for the domain 
 unless domain was disconnected by
 `-[NSFileProviderExternalVolumeHandling shouldConnectExternalDomainWithCompletionHandler:]`.
 It can also fail in the extension process if the domain (external) is being setup for the very first time
 (meaning it never existed).
 */
- (nullable NSURL *)temporaryDirectoryURLWithError:(NSError **)error FILEPROVIDER_API_AVAILABILITY_V3_IOS;

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

 If a domain with the same identifier already exists, `addDomain` will update the display name
 and hidden state of the domain and succeed.

 When the domain is backed by a NSFileProviderReplicatedExtension, the system will create
 a disk location where the domain will be replicated. If that location already exists on disk
 this call will fail with the code NSFileWriteFileExistsError.
 */
+ (void)addDomain:(NSFileProviderDomain *)domain completionHandler:(void(^)(NSError *_Nullable error))completionHandler;

/**
 Remove a domain.
 */
+ (void)removeDomain:(NSFileProviderDomain *)domain completionHandler:(void(^)(NSError *_Nullable error))completionHandler;

/**
 Remove a domain with options
 */
+ (void)removeDomain:(NSFileProviderDomain *)domain mode:(NSFileProviderDomainRemovalMode)mode completionHandler:(void(^)(NSURL *_Nullable_result preservedLocation, NSError *_Nullable error))completionHandler FILEPROVIDER_API_AVAILABILITY_V4_0_IOS;

/**
 Get all registered domains.
 */
+ (void)getDomainsWithCompletionHandler:(void (^)(NSArray<NSFileProviderDomain *> *domains, NSError * _Nullable error))completionHandler;

/**
 Remove all registered domains.
 */
+ (void)removeAllDomainsWithCompletionHandler:(void(^)(NSError *_Nullable error))completionHandler;

/**
 Calling this method will cause the system to cancel throttling on every item which has been throttled due to the given error.

 This call supports the following errors:
 - NSFileProviderErrorNotAuthenticated
 - NSFileProviderErrorInsufficientQuota
 - NSFileProviderErrorServerUnreachable
 - NSFileProviderErrorCannotSynchronize
 - NSFileProviderErrorExcludedFromSync
 */
- (void)signalErrorResolved:(NSError *)error completionHandler:(void(^)(NSError *_Nullable error))completionHandler
FILEPROVIDER_API_AVAILABILITY_V3_IOS;

/**
 Returns the global progress for the specified kind of operations

 This progress tracks all the ongoing kind of operations (from disk to the provider).
 Uploading operations are the operations from disk to the provider.
 Downloading operations are the operations from the provider to the disk.

 The global progress exposes the two following data:
 - Number of items with an ongoing matching kind operation along with the grand total;
 - Number of bytes already transferred along with the total amount of bytes to transfer.

 `totalUnitCount` will only be reset when there are no operations left. If new operations of the matching
 kind arrive while the global progress is already ongoing, they will just be summed to the existing global
 progress.

 By default, when no matching kind operations are active, the progress has its values set to 1 and its state set
 to finished.

 The progress will be updated on the main queue. It is to be retained by the caller and to be observed through
 KVO.

 The two only supported values for kind are:
 - NSProgressFileOperationKindUploading
 - NSProgressFileOperationKindDownloading

 The returned progress will have its fileOperationKind property set.
 */
- (NSProgress *)globalProgressForKind:(NSProgressFileOperationKind)kind NS_SWIFT_NAME(globalProgress(for:)) FILEPROVIDER_API_AVAILABILITY_V3_1_IOS;

@end

/** Posted when the materialized set has changed.

 Interested clients can then use the materialized set enumerator returned by -enumeratorForMaterializedItems to enumerate changes on the materialized set.

 Note, this notification starts to be posted only after `+[NSFileProviderManager getDomainsWithCompletionHandler:]` is called.
 */

FOUNDATION_EXPORT NSNotificationName const NSFileProviderMaterializedSetDidChange
FILEPROVIDER_API_AVAILABILITY_V3_1_IOS;

@interface NSFileProviderManager (MaterializedSet)

/**
 Returns an enumerator for the set of materialized items.

 When calling -[NSFileProviderEnumerator enumerateItemsForObserver:startingAtPage:] on the returned
 enumerator, pass the result of [NSData new] as the starting page. The sorting page constants
 (NSFileProviderInitialPageSortedByName and NSFileProviderInitialPageSortedByDate) will not influence
 the order of the items enumerated from the materialized set.

 This enumerator is unlike other enumerators because the roles of the system
 and the app/extension are reversed:
 - The system enumerates the working set after the extension calls
   'signalEnumeratorForContainerItemIdentifier';
 - The app/extension enumerates the materialized set after the system calls
   'materializedItemsDidChangeWithCompletionHandler'.
 */
- (id<NSFileProviderEnumerator>)enumeratorForMaterializedItems FILEPROVIDER_API_AVAILABILITY_V3_IOS;

@end

/** Posted when the pending set has changed.

 Interested clients can then use the pending set enumerator returned by -enumeratorForPendingItems to enumerate changes on the pending set.

 Note, this notification starts to be posted only after `+[NSFileProviderManager getDomainsWithCompletionHandler:]` is called.
 */
FOUNDATION_EXPORT NSNotificationName const NSFileProviderPendingSetDidChange
FILEPROVIDER_API_AVAILABILITY_V3_1_IOS;

FILEPROVIDER_API_AVAILABILITY_V3_1_IOS
@protocol NSFileProviderPendingSetEnumerator <NSFileProviderEnumerator>

/**
 The version of the domain when the pending set was last refreshed by the system.

 This property is updated when the enumeration methods are called on the pending set enumerator. The value
 is initially nil.
 */
@property (nonatomic, readonly, nullable) NSFileProviderDomainVersion *domainVersion;

/**
 The amount of time in seconds at which the pending set is refreshed on modifications.
 */
@property (nonatomic, readonly) NSTimeInterval refreshInterval;

/**
 This property is set to YES when the enumeration of the pending set was capped at or below its maximum size.
 Under normal conditions, the count of items pending sync will get lower as sync progresses, and this variable
 will eventually be set to NO when the pending set again includes all items pending sync.
 */
@property (nonatomic, readonly, getter=isMaximumSizeReached) BOOL maximumSizeReached FILEPROVIDER_API_AVAILABILITY_V5_0_IOS;

@end

@interface NSFileProviderManager (PendingSet)

/**
 Returns an enumerator for the set of pending items.

 This enumerator behaves like the materialized set enumerator.
 On later modifications in the set, the system will call
 'pendingItemsDidChangeWithCompletionHandler'.
 */
- (id<NSFileProviderPendingSetEnumerator>)enumeratorForPendingItems FILEPROVIDER_API_AVAILABILITY_V3_1_IOS;

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
FILEPROVIDER_API_AVAILABILITY_V3_IOS;

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

 The completion handler is called as soon as the reimport is initiated and does not not reflect
 the end of the import. When the import of the file hierarchy is finished, the system calls
 -[NSFileProviderExtension importDidFinishWithCompletionHandler:].

 In some circumstances, in particular in case the requested item is the root item, calling
 reimport will cause the system to stop the extension process. If the call is initiated
 from the extension, the system does not guarantee that the completion handler will be called
 before the extension is stopped. When called on the root item, reimport will cause the system
 to rebuild its backing store for the domain. See `-[NSFileProviderDomain backingStoreIdentity]`.

 If this method succeeds, the system will reimport at least the requested sub-tree, but may
 import more.

 If the requested item has no on-disk representation, the completion handler will be called with
 a NSFileProviderErrorNoSuchItem error. The same error will be reported if the reimport request
 happens quickly after a previous import / reimport and the corresponding item hasn't been
 reimported yet.
 */
- (void)reimportItemsBelowItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                           completionHandler:(void (^)(NSError * _Nullable error))completionHandler
    NS_SWIFT_NAME(reimportItems(below:completionHandler:))
FILEPROVIDER_API_AVAILABILITY_V3_IOS;

/**
  Request that the system schedules a call to -[NSFileProviderReplicatedExtension modifyItem:] for the given item identifier.
  The fields passed to modifyItem will contain at least the set requested via the `fields` parameter.
  The completion handler is called when the system has persisted the request. There is no guarantee as to when the
  modifyItem call will be scheduled.
  The completion handler may be called with an error. If the provider passes the `.content` field when the item
  is not downloaded, or when the item is a folder, then the system will return CocoaError(.ubiquitousFileUnavailable).
 */
- (void)requestModificationOfFields:(NSFileProviderItemFields)fields
              forItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                            options:(NSFileProviderModifyItemOptions)options
                  completionHandler:(void(^)(NSError *_Nullable error))completionHandler
FILEPROVIDER_API_AVAILABILITY_V2_V5;


@end

@interface NSFileProviderManager (Eviction)

/**
 Request that the system remove an item from its cache.

 When called on a file, the file will be made dataless.

 When called on a directory, first each of the directory's children will be evicted (child files are made
 dataless, child directories are recursively evicted). Then the directory itself will be made dataless.
 If a non-evictable child is encountered, eviction will stop immediately and the completionHandler will be called with
 the NSFileProviderErrorNonEvictableChildren error. The error will include information on why and which
 children could not be evicted in -[NSError underlyingErrors].

 The materialization state of the remaining items may be either materialized or evicted, depending on the traversal order.

 The completion handler is called after the items have been evicted from disk or immediately when an error occurs.

 Eviction might fail with the following errors :
   - NSFileProviderErrorDomain.NSFileProviderErrorUnsyncedEdits if the item had non-uploaded changes.
   - NSFileProviderErrorDomain.NSFileProviderErrorNonEvictable if the item has been marked as non-purgeable by the provider.
   - NSPOSIXErrorDomain.EBUSY : if the item has open file descriptors on it.
   - NSPOSIXErrorDomain.EMLINK : if the item has several hardlinks.
   - other NSPOSIXErrorDomain error codes if the system was unable to access or manipulate the corresponding file.
 */
- (void)evictItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
              completionHandler:(void (^)(NSError * _Nullable error))completionHandler
    NS_SWIFT_NAME(evictItem(identifier:completionHandler:))
FILEPROVIDER_API_AVAILABILITY_V3_IOS;

@end

@interface NSFileProviderManager (Barrier)

/**
 Wait for all changes on disk in the sub-hierarchy of the item to be acknowledged by the extension.

 This call can be used to guarantee operation ordering in a sub-hierarchy of the provider. The completion
 handler is called when all the changes for descendents of the item have been acknowledged by the extension.
 If any error is met during that process, an error will be raised, in which case the caller should not
 assume all the changes have been received.

 This call will only wait for changes affecting items that were already descendents of the requested item
 in the provider, or items that have been newly created on disk. It will not wait for items that are already
 known from the provider and are being moved in the directory. As a consequence, that call can be used from within a call
 to -[NSFileProviderReplicatedExtension modifyItem:baseVersion:changedFields:contents:options:completionHandler:].
 Also note that the call will return immediately on items that are not directories.

 In case a change cannot be applied to the provider, the call will fail with NSFileProviderErrorCannotSynchronize
 including the NSFileProviderErrorItemKey with the identifier of the item that could not be synced if that item
 is known by the provider.
 */
- (void)waitForChangesOnItemsBelowItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                                   completionHandler:(void (^)(NSError * _Nullable error))completionHandler
    NS_SWIFT_NAME(waitForChanges(below:completionHandler:))
FILEPROVIDER_API_AVAILABILITY_V3_IOS;
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
- (void)waitForStabilizationWithCompletionHandler:(void(^)(NSError * _Nullable error))completionHandler FILEPROVIDER_API_AVAILABILITY_V3_IOS;
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

@interface NSFileProviderManager (Materialize)

/**
 Request that the system schedule a download for an item.

 The completion handler is called when the system acknowledges the download request,
 or with an error indicating why it didn't (e.g NSFileProviderErrorNoSuchItem.)
 The system will then call -fetchContentsForItemWithIdentifier at the earliest
 convenient time.

 Set rangeToMaterialize to NSMakeRange(offset, nbytes) to request a partial download.
 The system will then invoke -fetchPartialContentsForItemWithIdentifier instead of
 fetchContentsForItemWithIdentifier. For a full download, set rangeToMaterialize to
 NSMakeRange(NSNotFound, 0). -[NSFileProviderManager evictItemWithIdentifier:completionHandler:]
 must be called on a partially materialized file before requesting an extent to be downloaded from a
 later version of the file. 

 This method cannot be used to download directories recursively. When invoked on a
 dataless directory, it will trigger an enumeration of the directory, causing a
 materialization of the directory one level down only. All the children of the
 directory will remain dataless after the enumeration.
 */
- (void)requestDownloadForItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                              requestedRange:(NSRange)rangeToMaterialize
                           completionHandler:(void (^)(NSError * _Nullable error))completionHandler NS_REFINED_FOR_SWIFT FILEPROVIDER_API_AVAILABILITY_V5_0;
@end

@interface NSFileProviderManager (StateDirectory)
/**
 A directory suitable for storing state information for the domain.

 The returned URL is guaranteed to be on the same volume as the user visible URL and the temporary URL, making sure
 the system can atomatically clone/move files from that location to the user visible URL.
 The caller is responsible for managing the security scope of the returned URL.

 When syncing a domain on an external volume, all information about the sync state must be kept in this directory
 if the volume is to be shared between multiple machines.

 If the system cannot find a suitable directory, this call will fail. This could happen e.g. if the domain
 does not exist or is in instance of initialization.

 This call will not fail when called from the extension process with an active instance of the extension
 for that domain unless the domain is being setup for the very first time (meaning it never existed).

 Removing the domain will remove the corresponding directory along with it.
*/
- (nullable NSURL *)stateDirectoryURLWithError:(NSError *__autoreleasing  _Nullable *)error FILEPROVIDER_API_AVAILABILITY_EXTERNAL_VOLUME;
@end

typedef NS_OPTIONS(NSUInteger, NSFileProviderVolumeUnsupportedReason) {
    NSFileProviderVolumeUnsupportedReasonNone           = 0,
    NSFileProviderVolumeUnsupportedReasonUnknown        = 1 << 0,
    NSFileProviderVolumeUnsupportedReasonNonAPFS        = 1 << 1,
    NSFileProviderVolumeUnsupportedReasonNonEncrypted   = 1 << 2,
    NSFileProviderVolumeUnsupportedReasonReadOnly       = 1 << 3,
    NSFileProviderVolumeUnsupportedReasonNetwork        = 1 << 4,
    NSFileProviderVolumeUnsupportedReasonQuarantined    = 1 << 5
} FILEPROVIDER_API_AVAILABILITY_EXTERNAL_VOLUME;

@interface NSFileProviderManager (ExternalDomain)

/**
 Check if a URL is eligible for storing a domain.

 This returns whether the check has been performed succesfully - NOT whether the drive is eligible.

 If an error was encountered while checking, this method returns FALSE and an error describing
 the problem will be set.

 The eligible parameter will contain the result of the check and indicate whether the volume can be
 used to store FP domains. Its value is only defined if the call returns YES.

 The url can be any existing and accessible URL on the volume for which you want to assess eligibility.
 The checks are volume-wide and the exact location on the volume doesn't impact them.

 If a drive is eligible, unsupportedReason will be empty (0). Otherwise it will contain the list of identified
 conditions that currently prevent this drive from being used to store FP domains.
 */
+ (BOOL)checkDomainsCanBeStored:(BOOL *)eligible
                  onVolumeAtURL:(NSURL *)url
              unsupportedReason:(NSFileProviderVolumeUnsupportedReason * _Nullable)unsupportedReason
                          error:(NSError *_Nullable *_Nullable)error NS_REFINED_FOR_SWIFT FILEPROVIDER_API_AVAILABILITY_EXTERNAL_VOLUME;
@end

@interface NSFileProviderManager (Diagnostics)

/**
 Request diagnostics collection for the item.

 This will prompt the user about an issue with the sync in the provider and ask their permission
 to collection diagnostic information and to send them to Apple for further analysis.

 This call is to be used wisely with care given there's global throttling on it preventing
 spamming the users. Furthermore it should be used in collaboration with Apple when you
 detect a misbehavior in the sync in your provider likely caused by a system bug and you need to
 work with Apple in order to resolve it.

 This will return whether the call was allowed or not - not if it suceed
 This method will only return an error if the user was not on a Seed build

 It is mandatory to provide an error for the item why the collection is requested.
 The error won't be shown to the user (a generic message will be shown instead)
 It will surface in the generated report though

 It is important to note that even if the call is allowed, it might not trigger diagnostic collection
 nor prompt to the user depending on the system state and other throttling parameters
 */
- (void)requestDiagnosticCollectionForItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                                             errorReason:(NSError *)errorReason
                                       completionHandler:(void (^)(NSError * _Nullable error))completionHandler
                                    NS_SWIFT_NAME(requestDiagnosticCollection(for:errorReason:completionHandler:))
                                    FILEPROVIDER_API_AVAILABILITY_FEEDBACK;

@end

NS_ASSUME_NONNULL_END
