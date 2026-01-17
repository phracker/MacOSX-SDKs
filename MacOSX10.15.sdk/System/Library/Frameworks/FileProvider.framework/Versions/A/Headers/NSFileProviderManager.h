//
//  NSFileProviderManager.h
//  FileProvider
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderItem.h>
#import <FileProvider/NSFileProviderDomain.h>

NS_ASSUME_NONNULL_BEGIN

@class NSURLSessionTask;
@class NSFileProviderDomain;


/**
 The file provider manager allows you to communicate with the file provider
 framework for purposes that may be relevant from both the extension and
 the containing application (or sibling extensions).

 The file provider framework will invoke your file provider extension in response
 to those calls if appropriate.

 The class also provides methods to manage provider domains. Each domain has a
 corresponding manager.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
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
 Registers the given NSURLSessionTask to be responsible for the specified item.
 A given item can only have one task registered at a time. The task must be
 suspended at the time of calling.
 The task's progress is displayed on the item when the task is executed.
 */
- (void)registerURLSessionTask:(NSURLSessionTask *)task forItemWithIdentifier:(NSFileProviderItemIdentifier)identifier completionHandler:(void (^)(NSError * __nullable error))completion;

/**
 Return the user visible URL for an item identifier.

 Calling this method marks the calling process in such a way that accessing
 files will not trigger materialization; instead, accesses to unmd
 files will fail with EDEADLK.
 */
- (void)getUserVisibleURLForItemIdentifier:(NSFileProviderItemIdentifier)itemIdentifier completionHandler:(void (^)(NSURL * __nullable userVisibleFile, NSError * __nullable error))completionHandler API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos) NS_SWIFT_NAME(getUserVisibleURL(for:completionHandler:));


/**
 Return the identifier and domain for a user visible URL.

 This method returns the identifier and domain of a user visible URL if
 applicable. Calling this method on a file which doesn't reside in your
 provider/domain will return the Cocoa error NSFileNoSuchFileError.
 */
+ (void)getIdentifierForUserVisibleFileAtURL:(NSURL *)url completionHandler:(void (^)(NSFileProviderItemIdentifier __nullable itemIdentifier, NSFileProviderDomainIdentifier __nullable domainIdentifier, NSError * __nullable error))completionHandler API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);



/**
 The purpose identifier of your file provider extension. A coordination using a
 file coordinator with this purpose identifier set will not trigger your file
 provider extension. You can use this to e.g. perform speculative work on behalf
 of the file provider from the main app.
 */
@property(nonatomic, readonly) NSString *providerIdentifier;

/**
 The root URL for provided documents. This URL is derived by consulting the
 NSExtensionFileProviderDocumentGroup property on your extension. The document
 storage URL is the folder "File Provider Storage" in the corresponding
 container.

 If the NSExtensionFileProviderDocumentGroup property is not set, calling this
 method will result in an error.
 */
@property(nonatomic, readonly) NSURL *documentStorageURL;

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
                        error:(NSError **)error;

/**
 Returns the designated placeholder URL for a given file URL. Used in
 conjunction with writePlaceholderAtURL.
 */
+ (NSURL *)placeholderURLForURL:(NSURL *)url;

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
 with the special NSFileProviderCreateItemOptionsItemMayAlreadyExist option.

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
API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

/** Notify the system that the itemIdentifiers known by the system are not valid anymore.

 This can be called by an extension in case it has lost track of its synchronisation state
 and as a consequence is not able to guarantee the stability of the itemIdentifiers anymore.
 In that case, the system will trigger a scan of any data that is cached on disk and call
 createItemBasedOnTemplate with the special NSFileProviderCreateItemOptionsItemMayAlreadyExist
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
    API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

@end

/**
 Policy regarding download and caching of an item by the system.
 */
typedef NS_ENUM(NSUInteger, NSFileProviderDownloadPolicy) {
    /**
     By default, files are downloaded on demand (e.g. when explicitely open by
     the user) and may be evicted when needed (e.g. on low disk pressure.)
     */
    NSFileProviderDownloadPolicyDefault = 0,

    /**
     Download this item when appropriate, minding shared resources like
     available disk space.

     Set this policy on files that are likely to be needed by the user in the
     near future.
     */
    NSFileProviderDownloadPolicySpeculative = 1,

    /**
     Download this item and keep it downloaded forever.

     This policy applies recursively to all the items in a directory.
     Set this policy only on files that the user must keep locally available for
     offline use; abusing this policy causes shared resources like availabe disk
     space to run out.
     */
    NSFileProviderDownloadPolicyKeepDownloaded = 2,
} API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

@interface NSFileProviderManager (DownloadAndEviction)

/**
 Trigger a download or change the download policy.
 See the documentation on the download policies for details.

 The completion handler is called to acknowledge the change of policy: the
 actual downloads are scheduled asynchronously when appropriate.
 */
- (void)setDownloadPolicy:(NSFileProviderDownloadPolicy)downloadPolicy
    forItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
        completionHandler:(void (^)(NSError * _Nullable))completionHandler
    API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

/**
 Request that the system removes an item from its cache.

 This removes the contents of a file, or the metadata and contents of all the
 files in a directory.  It resets the download policies of all the evicted
 items back to the default policy.

 The completion handler is called when the item has been evicted from disk.
 */
- (void)evictItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
              completionHandler:(void (^)(NSError * _Nullable))completionHandler
    API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

@end

NS_ASSUME_NONNULL_END
