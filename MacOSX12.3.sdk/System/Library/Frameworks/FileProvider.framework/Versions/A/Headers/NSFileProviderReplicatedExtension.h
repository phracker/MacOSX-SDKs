//
//  NSFileProviderReplicatedExtension.h
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderItem.h>
#import <FileProvider/NSFileProviderExtension.h>
#import <FileProvider/NSFileProviderEnumerating.h>
#import <FileProvider/NSFileProviderService.h>
#import <FileProvider/NSFileProviderActions.h>
#import <FileProvider/NSFileProviderRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class NSFileProviderDomain;

#pragma mark - Options

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
     may be recreated with the mayAlreadyExist option. This allows the
     extension to recursively merge directories.

     The Extension should assess whether the item could actually be a disk
     representation of an already existing item.

     Since this can happens when the system has to reimport all the existing
     item from disk, it is advised that the assessment method avoids
     computational intensive tasks, such as checksumming the item.

     When all the items pending reimport have been processed, the system
     will call -[NSFileProviderExtension importDidFinishWithCompletionHandler:].
     */
    NSFileProviderCreateItemMayAlreadyExist = 1 << 0,

    /**
     This item is recreated after the system failed to apply a deletion requested
     by the extension because the item was found to be edited locally.
     This happens only if the edit wasn't yet known by the system at the time the
     deletion was requested.
     */
    NSFileProviderCreateItemDeletionConflicted FILEPROVIDER_API_AVAILABILITY_V3_1 = 1 << 1,

} FILEPROVIDER_API_AVAILABILITY_V3;

/**
 Options passed on item deletion.
 */
typedef NS_OPTIONS(NSUInteger, NSFileProviderDeleteItemOptions) {
    /**
     The deletion of the item is recursive.
     */
    NSFileProviderDeleteItemRecursive = 1 << 0,
} FILEPROVIDER_API_AVAILABILITY_V3;

typedef NS_OPTIONS(NSUInteger, NSFileProviderModifyItemOptions) {
    /**
     We're moving the item to a location where it may refer to an item that already exists. This may happen
     when two directories are being merged together. When this happens some items may be merged to the
     same directory and we end up in a situation where the merged contains may also exist.

     This is similar to NSFileProviderCreateItemMayAlreadyExist
     */
    NSFileProviderModifyItemMayAlreadyExist = 1 << 0,
} FILEPROVIDER_API_AVAILABILITY_V3;

/**
 NSFileProviderItemContents corresponds to the item's contents.

 Each subsequent field corresponds to a property on NSFileProviderItem that can
 change.
 */
typedef NS_OPTIONS(NSUInteger, NSFileProviderItemFields) {
    NSFileProviderItemContents = 1 << 0,
    NSFileProviderItemFilename = 1 << 1,
    NSFileProviderItemParentItemIdentifier = 1 << 2,
    NSFileProviderItemLastUsedDate = 1 << 3,
    NSFileProviderItemTagData = 1 << 4,
    NSFileProviderItemFavoriteRank = 1 << 5,
    NSFileProviderItemCreationDate = 1 << 6,
    NSFileProviderItemContentModificationDate = 1 << 7,
    NSFileProviderItemFileSystemFlags = 1 << 8,
    NSFileProviderItemExtendedAttributes = 1 << 9,
    NSFileProviderItemTypeAndCreator FILEPROVIDER_API_AVAILABILITY_V4_0 = 1 << 10,
} FILEPROVIDER_API_AVAILABILITY_V3;

/**
 NSFileProviderMaterializationFlags are used to inform the system about specific conditions
 that apply to the content retrieved by the provider in fetchPartialContentsForItemWithIdentifier.

 */
typedef NS_OPTIONS(NSUInteger, NSFileProviderMaterializationFlags) {
    /**
     Mark the file as fully materialized even though it's sparse.
     This flag is ignored if the provided range doesn't cover the entire file (ie. [0, EOF])
     */
    NSFileProviderMaterializationFlagsKnownSparseRanges = (1 << 0)
} FILEPROVIDER_API_AVAILABILITY_V4_1;

/**
 Used by the system to express options and constraints to the provider in fetchPartialContentsForItemWithIdentifier.
 */
typedef NS_OPTIONS(NSUInteger, NSFileProviderFetchContentsOptions) {
    /**
     Set by the system to inform the provider that any other content version than the requested one
     will be discarded.
     If the provider cannot supply this version, it should fail with NSFileProviderErrorVersionNoLongerAvailable.
     */
    NSFileProviderFetchContentsOptionsStrictVersioning = (1 << 0)
} FILEPROVIDER_API_AVAILABILITY_V4_1;

#pragma mark - Extension with FPFS support

FILEPROVIDER_API_AVAILABILITY_V3
@protocol NSFileProviderEnumerating <NSObject>

/**
 Create an enumerator for an item.

 This method is called when the user lists the content of folder it never accessed
 before. This can happen either when using Finder or when listing the content of
 the directory from a Terminal (for instance using the `ls` command line tool). The
 system will use the enumerator to list the children of the directory by calling
 -[NSFileProviderEnumerator enumerateItemsForObserver:startingAtPage:] until nil
 is passed to -[NSFileProviderEnumerationObserver finishEnumeratingUpToPage:].
 Once this has been called, the directory and its children should be included in the
 working set.

 This is also used to subscribe to live updates for a single document.

 The system will keep an enumerator open in the extension on directories that are
 presented to the user (for instance, in Finder), and on document on which an application
 has a NSFilePresenter. The provider can use the existence of that enumerator as a hint
 that the user is actively seeing / using the item in question, and prioritize the delivery
 of updates on the item or its children in the working set.

 If returning nil, you must set the error out parameter.

 Working set enumerator:
 -----------------------
 The working set enumerator is a special enumerator (NSFileProviderWorkingSetContainerItemIdentifier)
 the system uses to detect changes that should be synced to the disk and/or searchable
 in Spotlight. Because that enumerator is by definition used for change detection, the
 working set enumerator must implement
 -[NSFileProviderEnumerator enumerateChangesForObserver:fromSyncAnchor:] and
 -[NSFileProviderEnumerator currentSyncAnchorWithCompletionHandler:].

 The system guarantees that it has a single consumer for the working set. This means there
 will never be two concurrent enumerations of the working set and will always do forward
 progress: the system will only ask for changes from the last requested sync anchor or
 the last returned sync anchor and the extension should be prepared for it.

 The expiration of the sync anchor of the working set will cause a very expensive scan
 of all the items known by the system.

 The system ingests the changes from the working set and applies the changes to the
 disk replicate and the spotlight index. Before ingesting the update for an item,
 the system will check if the enumeration of the item races against a call to
 createItemBasedOnTemplate, modifyItem, ... that may affect the item. If a potential race
 is detected, the system will call itemForItemIdentifier in order to resolve the race.

 If the provider exposes the key NSExtensionFileProviderAppliesChangesAtomically with value
 YES in its Info.plist, it is considered to apply the changes atomically, in which case the
 system does not need to check for potential races.

 Error cases:
 ------------
 If containerItemIdentifier is NSFileProviderTrashContainerItemIdentifier and
 the extension does not support trashing items, then it should fail the call
 with the NSFeatureUnsupportedError error code from the NSCocoaErrorDomain
 domain.

 If the item requested containerItemIdentifier does not exist in the provider,
 the extension should fail with NSFileProviderErrorNoSuchItem. In that case,
 the system will consider the item has been deleted and attempt to delete the
 item from disk.

 The extension can also report the NSFileProviderErrorNotAuthenticated,
 NSFileProviderErrorServerUnreachable in case the item cannot be fetched
 because of the current state of the system / domain. In that case, the
 system will present an appropriate error message and back off until the
 next time it is signalled.

 Any other error, including crashes of the extension process, will be considered to be transient
 and will cause the enumeration to be retried.

 Errors must be in one of the following domains: NSCocoaErrorDomain, NSFileProviderErrorDomain.

 For errors which can not be represented using an existing error code in one of these domains, the extension
 should construct an NSError with domain NSCocoaErrorDomain and code NSXPCConnectionReplyInvalid.
 The extension should set the NSUnderlyingErrorKey in the NSError's userInfo to the error which could not
 be represented.
 */
- (nullable id<NSFileProviderEnumerator>)enumeratorForContainerItemIdentifier:(NSFileProviderItemIdentifier)containerItemIdentifier
                                                                      request:(NSFileProviderRequest *)request
                                                                        error:(NSError **)error
    NS_SWIFT_NAME(enumerator(for:request:));

@end

/**
 FileProvider extension for which the system replicates the content on disk.

 The extension exposes a hierarchy of NSFileProviderItem instances that the system
 will replicate on disk as a file hierarchy. The file hierarchy reflects the filename,
 parent, content, and metadata described by the NSFileProviderItem. In case two items
 are at the same disk location (same parent and filename), the system may choose to
 "bounce" an item.

 The system lazily replicates the item hierarchy: items are created "dataless" on disk
 and the content (for files) or list of children (for folders) is fetched on first
 access by calling fetchContentsForItemWithIdentifier, or enumeratorForContainerItemIdentifier.

 The provider can notify the system of changes on the items by publishing those on the
 enumerator for the working set. The system notifies the extension of changes made by the
 user on disk by calling createItemBasedOnTemplate, modifyItem, or deleteItemWithIdentifier.

 Concurrency:
 ------------
 A replicated extension class must be prepared to handle multiple concurrent calls since the
 system may perform several concurrent operations (for instance, modifying an item, while enumerating
 the working set, creating another item, and fetching the contents of yet another item).

 The system has limits to the number of concurrent operations.When the number of concurrent
 operations is reached, the system will not schedule additional operations falling in that category
 until at least one of the running operation has completed by calling its completion handler.

 The system currently separates the operations into the following categories:
 - enumeration of the working set. At most 1 enumeration of the working set can happen at a given time
 - downloads. The system has a limit on the number of concurrent calls to fetchContents and similar calls
   That limit is configurable by setting the NSExtensionFileProviderDownloadPipelineDepth key to an integer
   value (between 1 and 128) in the Info.plist of the extension.
 - uploads. The system has a limit on the number of concurrent calls to createItemBasedOnTemplate and
   modifyItem when the call includes new content to be uploaded. That limit is configurable by setting the
   NSExtensionFileProviderUploadPipelineDepth key to an integer value (between 1 and 128) in the Info.plist
   of the extension.
 */
FILEPROVIDER_API_AVAILABILITY_V3
@protocol NSFileProviderReplicatedExtension <NSObject, NSFileProviderEnumerating>

/**
 Create a new instance of the replicated provider for the specified domain.
 */
- (instancetype)initWithDomain:(NSFileProviderDomain *)domain;

/**
 Called before the instance is discarded.

 Several instances of a replicated provider can be hosted by the same process, either because
 the user has several active domains, or because an instance got discarded and a new one
 is created by the system. This method is called before an instance is discarded and should
 make sure that all references to the instance are released so that the instance can be
 deallocated.
 */
- (void)invalidate;

/**
 Fetch the metadata for the item with the provider identifier.

 Error cases:
 ------------
 If the metadata lookup fails because the item is unknown, the call should
 fail with the NSFileProviderErrorNoSuchItem error. In that case, the system
 will consider the item has been removed from the domain and will attempt to
 delete it from disk. In case that deletion fails because there are local
 changes on this item, the system will re-create the item using createItemBasedOnTemplate.

 The extension can also report the NSFileProviderErrorNotAuthenticated,
 NSFileProviderErrorServerUnreachable in case the item cannot be fetched
 because of the current state of the system / domain. In that case, the
 system will present an appropriate error message and back off until the
 next time it is signalled.

 Any other error, including crashes of the extension process, will be considered to be
 transient and will cause the lookup to be retried.

 Errors must be in one of the following domains: NSCocoaErrorDomain, NSFileProviderErrorDomain.

 For errors which can not be represented using an existing error code in one of these domains, the extension
 should construct an NSError with domain NSCocoaErrorDomain and code NSXPCConnectionReplyInvalid.
 The extension should set the NSUnderlyingErrorKey in the NSError's userInfo to the error which could not
 be represented.

 Cancellations:
 ------------
 If the NSProgress returned by this method is cancelled, the extension should
 call the completion handler with (nil, NSUserCancelledError) in the NSProgress
 cancellation handler.
 */
- (NSProgress *)itemForIdentifier:(NSFileProviderItemIdentifier)identifier
                          request:(NSFileProviderRequest *)request
                completionHandler:(void(^)(NSFileProviderItem _Nullable, NSError * _Nullable))completionHandler
    NS_SWIFT_NAME(item(for:request:completionHandler:));

/**
 Download the item for the given identifier and return it via the completion handler.

 The system learns of items through enumerations. Initially, this means that the
 system is aware that an item (with a specific version) exists on the device.

 When the user accesses the item, the system makes a request for the contents of
 the item. The provider can then fulfill the request by providing the item.

 The system takes ownership of the item and will move it out of the sandbox of
 the provider.

 If the provider wishes to force materialization of a given item, the provider should use the NSFileCoordinator
 API to coordinate a read on the user visible URL of the item, retrieved using
 -[NSFileProviderManager getUserVisibleURLForItemIdentifier:completionHandler:]

 The requestedVersion parameter specifies which version should be returned. A nil value
 means that the latest known version should be returned. Except for the error case, the
 version of the returned item is assumed to be identical to what was requested.

 requestedVersion is currently always set to nil.

 Concurrent Downloads:
 ----------
 The system will call fetchContents concurrently if there are multiple outstanding file download requests.
 The provider can control the concurrency by setting the key NSExtensionFileProviderDownloadPipelineDepth
 in the Info.plist of the extension to the number of concurrent downloads that the system should create
 per domain. This number must be between 1 and 128, inclusive.

 File ownership:
 ---------------
 The system clones and unlinks the received fileContents. The extension should not mutate the corresponding
 file after calling the completion handler. If the extension wishes to keep a copy of the content, it must
 provide a clone of the that content as the URL passed to the completion handler.

 In case the extension or the system crashes between the moment the completion handler is called and the
 moment the system unlinks the file, the file may unexpectedly still be on disk the next time an instance
 of the extension is created. The extension is then responsible for deleting that file.

 Disallowing processes from fetching items:
 ---------------

 The system automatically downloads files on POSIX accesses. The extension may wish to disallow this class of
 downloads for specific applications.

 The extension can set an array of strings into the UserDefault key
 "NSFileProviderExtensionNonMaterializingProcessNames". A process whose name is an exact match for an
 entry in this array will not be allowed to fetch items in the extension's domains.

 In macOS 11.0 and later, this list will be checked when a download is initiated through a POSIX filesystem call.
 In macOS 11.4 and later, this list will also be checked for downloads initiated through file coordination.

 Error cases:
 ------------
 If the download fails because the item was deleted on the server, the call should
 fail with the NSFileProviderErrorNoSuchItem error. In that case, the system
 will consider the item has been removed from the domain and will attempt to
 delete it from disk. In case that deletion fails because there are local
 changes on this item, the system will re-create the item using createItemBasedOnTemplate,
 passing the NSFileProviderCreateItemDeletionConflicted flag.

 If the user does not have access to the content of the file, the provider
 can fail the call with NSCocoaErrorDomain and code NSFileReadNoPermissionError.
 That error will then be presented to the user. The extension can also report
 the NSFileProviderErrorNotAuthenticated, NSFileProviderErrorServerUnreachable
 in case the item cannot be fetched because of the current state of the system / domain.
 In those cases, the system will present an appropriate error message and back off
 until the next time it is signalled.

 Any other error, including crashes of the extension process, will be considered to be transient
 and will cause the download to be retried.

 Errors must be in one of the following domains: NSCocoaErrorDomain, NSFileProviderErrorDomain.

 For errors which can not be represented using an existing error code in one of these domains, the extension
 should construct an NSError with domain NSCocoaErrorDomain and code NSXPCConnectionReplyInvalid.
 The extension should set the NSUnderlyingErrorKey in the NSError's userInfo to the error which could not
 be represented.

 Cancellations:
 ------------
 If the NSProgress returned by this method is cancelled, the extension should
 call the completion handler with (nil, nil, NSUserCancelledError) in the NSProgress
 cancellation handler.

 The returned NSProgress is used to show progress to the user. If the user cancels the
 fetch, the extension should stop fetching the item, as it is no longer required.

 */
- (NSProgress *)fetchContentsForItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                                           version:(nullable NSFileProviderItemVersion *)requestedVersion
                                           request:(NSFileProviderRequest *)request
                                 completionHandler:(void(^)(NSURL * _Nullable fileContents, NSFileProviderItem _Nullable item, NSError * _Nullable error))completionHandler
    NS_SWIFT_NAME(fetchContents(for:version:request:completionHandler:));

/**
 Create a new item.

 The itemTemplate object describes the expected state of the newly created item,
 including its location provided by parentItemIdentifier and filename. The list
 of fields to conside in that object is defined by the fields parameter. Fields
 not listed should be considered as not being defined.

 The url is used to transfer the content of the file from the system to the
 extension. It can be nil if the item has no content. This will be the case if
 the item is a folder or if the item is being reimported (flag
 NSFileProviderCreateItemMayAlreadyExist set) and the file is dataless on disk.
 If the item is a symbolic link, the target path is provided by the symlinkTargetPath
 of the itemTemplate.

 The system is setting the itemIdentifier of the itemTemplate to a unique value that
 is guaranteed to stay the same for a given item in case the creation is replayed
 after a crash. That itemIdentifier is not intended to be the identifier assigned
 to the item by the provider.

 In the completion block, the createdItem is expected to reflect the properties of the
 newly created item, which usually means matching the properties passed in by the
 template. An exception is the itemIdentifier which should be the identifier assigned
 to that item by the provider rather than the identifier passed in through the template.
 If the provider reuses an existing identifier, the item that used that identifier will
 be removed from disk, replaced by the createdItem. If the item is a directory, the two
 directories will be merged and the items from the existing one will be modified with
 the NSFileProviderModifyItemMayAlreadyExist option set.

 If the provider is not able to apply all the fields at once, it should return a
 set of stillPendingFields in its completion handler. In that case, the system will
 attempt to modify the item later by calling modifyItem with those fields.

 If a field in the returned createdItem does not match the itemTemplate, and is
 not in the list of stillPendingFields, the value from the createdItem will be
 propagated to the disk. If the content of the item as described by createdItem
 does not match the content from url, the provider should set shouldFetchContent
 in the completion handler. The content from the provider will then be fetched
 and propagated to disk.

 In case the deletion of an item from the working set could not be applied to the
 disk by the system because it conflicted with a local edit of the file, the system
 will attempt to create the edited item. In that case the creation call will receive
 the NSFileProviderCreateItemDeletionConflicted option and the itemIdentifier in the
 template will be set to the itemIdentifier of the item deleted from the working set.
 The itemVersion will also be set to the last itemVersion of the item that was made
 available on disk before the item was edited locally. If such a conflict happens
 on a dataless item on disk, the item will be immediately deleted from the disk instead
 of issuing a new creation.

 In case the NSFileProviderCreateItemMayAlreadyExist option
 is passed, the content may be nil if the item is found by the system without any
 associated content. In that case, you should return a nil item if you are not
 able to match the created item with an existing item from the provider.

 In case of path collision with an already existing item, the provider
 can either fail using -[NSError (NSFileProviderError) fileProviderErrorForCollisionWithItem:]
 or resolve the collision by itself (e.g. by returning an item with a different name).
 If the error is returned, the system will try to resolve the collision by itself by bouncing
 away one of the items (renaming the item).

 If the imported item is refused by the extension, it should return nil for the
 createdItem without any error. In that case, the source item will be deleted
 from disk. In case the item represents a directory, the content will be deleted
 recursively. If the extension does not wish to synchronise the item, while still
 keeping it on disk, it should still import it locally, but not sync it to its
 server, and return a valid createItem object.

 The progress returned by createItemBasedOnTemplate is expected to include the
 upload progress of the item and will be presented in the user interface until
 the completion handler is called.

 Creation is gated by the NSFileProviderItemCapabilitiesAllowsAddingSubItems
 capability on the parent folder on a UI level, but direct file system changes
 (e.g. from Terminal) can still result in changes that must be handled.

 Structural consistency:
 -----------------------
 The system guarantees that the creation is called after the creation of the
 parent completed.

 File ownership:
 ---------------
 The file at `url` is owned by the system and is unlinked after the completion
 handler is called. If the extension wishes to keep access to the content of
 file after calling the completion handler, it should clone the file in its
 container.

 Atomicity:
 ----------
 By default, the system assumes all the changes are applied non-atomically, which
 means that the change or an intermediary state from the change can be observed
 (for instance while enumerating the working set) while the call is in progress
 (before the completion handler is called). The provider can indicate to the system
 that it applies changes atomically (that is, the change cannot be observed before
 the completion handler is called) by setting the key NSExtensionFileProviderAppliesChangesAtomically
 in the Info.plist of the extension to YES.

 The atomicity declaration only describes the visibility of the changes, not
 the ability of the provider to apply all the fields at once: a provider that applies
 changes atomically might still apply a subset of the changedFields communicated
 by the system and defer the remaining fields by setting the stillPendingFields
 parameter in the completion handler.

 Error cases:
 ------------
 If the creation fails because the target directory does not exist, the extension
 must fail the creation using the NSFileProviderErrorNoSuchItem error code. In
 that case, the system will attempt the re-create the parent directory.

 In case the location of the new item is already in use by another item, the extension
 can chose to either resolve the collision by moving one of the items
 away, or reject the creation with the NSFileProviderErrorFilenameCollision
 error code. In that error case, the system will be responsible for resolving the
 collision, by renaming one of the colliding items. When the collision is resolved,
 the system will call createItemBasedOnTemplate again.

 The extension can also report the NSFileProviderErrorNotAuthenticated,
 NSFileProviderErrorServerUnreachable, NSFileProviderErrorInsufficientQuota
 or NSFileProviderErrorCannotSynchronize in case the modification cannot be applied
 because of the current state of the system / domain. In that case, the system will
 present an appropriate error message and back off until the next time it is signalled.
 The provider can signal the error resolution by calling signalErrorResolved:completionHandler:.

 Any other error, including crashes of the extension process, will be considered to be transient
 and will cause the creation to be retried.

 Errors must be in one of the following domains: NSCocoaErrorDomain, NSFileProviderErrorDomain.

 For errors which can not be represented using an existing error code in one of these domains, the extension
 should construct an NSError with domain NSCocoaErrorDomain and code NSXPCConnectionReplyInvalid.
 The extension should set the NSUnderlyingErrorKey in the NSError's userInfo to the error which could not
 be represented.

 Cancellations:
 ------------
 If the NSProgress returned by this method is cancelled, the extension should
 call the completion handler with (nil, [], NO, NSUserCancelledError) in the NSProgress
 cancellation handler.
 */
- (NSProgress *)createItemBasedOnTemplate:(NSFileProviderItem)itemTemplate
                                   fields:(NSFileProviderItemFields)fields
                                 contents:(nullable NSURL *)url
                                  options:(NSFileProviderCreateItemOptions)options
                                  request:(NSFileProviderRequest *)request
                        completionHandler:(void (^)(NSFileProviderItem _Nullable createdItem,
                                                    NSFileProviderItemFields stillPendingFields,
                                                    BOOL shouldFetchContent,
                                                    NSError * _Nullable error))completionHandler
NS_SWIFT_NAME(createItem(basedOn:fields:contents:options:request:completionHandler:));

/**
 Informs the provider that an item or its metadata have changed. More than one
 property may have changed, e.g.  an item may have been renamed, moved and also
 changed contents, in which case changedFields might contain [.contents,
 .filename, .parentItemIdentifier, .contentModificationDate].

 If the provider is not able to apply all the fields at once, it should return a
 set of stillPendingFields in its completion handler. In that case, the system will
 attempt to modify the item later by calling modifyItem with those fields.

 Starting in macOS 12.0, if the set of stillPendingFields returned by the provider is
 identical to the set of fields passed to modifyItem, then the system will consider that these fields
 are not supported by the provider. The system will not send these fields to the provider again,
 until the item is modified.

 If a field in the returned item does not match the itemTemplate, and is
 not in the list of stillPendingFields, the value from the item will be
 propagated to the disk. In case there is a content change and the content of
 the returned item as described by item does not match the content from url,
 the provider should set shouldFetchContent in the completion handler. The
 content from the provider will then be fetched and propagated to disk.

 If the item modification results from the parent directory being merged into another
 directory, the NSFileProviderModifyItemMayAlreadyExist flag will be passed
 to the call.

 The provider can chose to merge two existing items when receiving modifyItem. In that
 case, the item returned should carry the itemIdentifier of the item with which the
 item will be merged and well as the resulting state of that item. The system will then
 keep one of the items (the one whose itemIdentifier was returned) and remove
 the other one from disk. In case of directories, the content of the two directories
 is merged and sub-items will be modified with the
 NSFileProviderModifyItemMayAlreadyExist flag set.

 If the extension wishes the modify item to cause the deletion of the item on disk,
 it can call the completion handler with nil in place of the resulting item. If the
 item is directory, the item will be kept on disk until all its children has been deleted
 from the working set. The system will only apply the deletion on the disk if this
 does not conflict with local edits. Otherwise, the system will attempt to re-create
 the item with the NSFileProviderCreateItemDeletionConflicted option set.

 The progress returned by modifyItem is expected to include the upload progress if any,
 even if the provider chose to call the completion handler before the upload finishes.
 For example, the provider might decide to call the completion handler as soon as the
 metadata have been stored in a local database.

 Modifications are gated by the corresponding capabilities of the item on a UI level,
 but direct file system changes (e.g. from Terminal) can still result in changes that
 must be handled.

 Conflict resolution:
 -------------------
 The system passes a `baseVersion` parameter to the modifyItem call. This
 baseVersion describes the latest version of the file which was reflected on disk.
 This parameter can be used to detect conflicts with remote edits.

 For instance, if content version A of the file was downloaded to the local system, and
 the content was modified locally, the modifyItem call will receive baseVersion of A. If the server
 has in the meantime received another content edit of the same file, the server may
 have content version C. In this case, the extension can detect the mismatching baseVersion,
 and decide how to resolve the conflict. The extension informs the system of how it
 wishes to resolve the conflict by returning the resolved metadata on the completion handler.
 As an example resolution, if the extension informs that it wishes for the remote version
 of the item to be on disk (and to ignore the local edits), it should return the new
 contentVersion in the completion handler's item. The system will subsequently call
 fetchContents to retrieve the new contents and replace them on disk.

 The `baseVersion` might contain one or both component set to
 `NSFileProviderItemVersionComponentZero` in case there has never been a version for
 which the item on disk and the item in the provider were known to be in sync.

 Structural consistency and Cycle handling:
 ------------------------------------------
 In case the parentItemIdentifier is modified, the system guarantees that the new
 parent has been created and the creation completed before the call to modifyItem
 is issued.

 The system guarantees that modifyItem called after local changes from the user will
 never create a cycle: that is all items will always be a descendent of either the
 root item or the trash item.

 However, cycles that are caused by concurrent local changes by the user and changes
 on the remote server can also create cycles. This is handled by the system as a
 conflict. This means the provider must validate that the call of modifyItem is not
 creating a cycle with a change it observed from the server. If such a cycle is
 detected, the provider must fix the conflict by breaking the cycle, and return the
 state of the item after resolving that conflict. If the resolution affects other
 items as well, updates for those other items must be published on the working set.

 File ownership:
 ---------------
 The file at `url` is owned by the system and is unlinked after the completion
 handler is called. If the extension wishes to keep access to the content of
 file after calling the completion handler, it should clone the file in its
 container.

 Atomicity:
 ----------
 By default, the system assumes all the changes are applied non-atomically, which
 means that the change or an intermediary state from the change can be observed
 (for instance while enumerating the working set) while the call is in progress
 (before the completion handler is called). The provider can indicate to the system
 that it applies changes atomically (that is, the change cannot be observed before
 the completion handler is called) by setting the key NSExtensionFileProviderAppliesChangesAtomically
 in the Info.plist of the extension to YES.

 The atomicity declaration only describes the visibility of the changes, not
 the ability of the provider to apply all the fields at once: a provider that applies
 changes atomically might still apply a subset of the changedFields communicated
 by the system and defer the remaining fields by setting the stillPendingFields
 parameter in the completion handler.

 Error cases:
 ------------
 The extension may fail the modification if the modified item does not exist
 anymore. In that case, the extension should fail the call the
 NSFileProviderErrorNoSuchItem error code. The system will attempt to delete
 the item on disk. If the item on disk actually has changes since this call
 to modifyItem, then it will be re-created by a call to createItemBasedOnTemplate.
 Likewise, if the item is reparented to a parent that no longer exists, the extension
 may return a NSFileProviderErrorNoSuchItem error with the parent item.

 In case the modification updates the location of the item and another item is
 already known at this location, the extension can chose to either resolve the
 collision by moving one of the items away, or reject the modification with
 the NSFileProviderErrorFilenameCollision error code. In that error case,
 the system will be responsible for resolving the collision, by renaming one of
 the colliding items. When the collision is resolved, the system will call
 modifyItem again.

 The extension can also report the NSFileProviderErrorNotAuthenticated,
 NSFileProviderErrorServerUnreachable, NSFileProviderErrorInsufficientQuota
 or NSFileProviderErrorCannotSynchronize in case the modification cannot be applied
 because of the current state of the system / domain. In that case, the system will
 present an appropriate error message and back off until the next time it is signalled.
 The provider can signal the error resolution by calling signalErrorResolved:completionHandler:.

 Any other error, including crashes of the extension process, will be considered to be transient
 and will cause the modification to be retried.

 Errors must be in one of the following domains: NSCocoaErrorDomain, NSFileProviderErrorDomain.

 For errors which can not be represented using an existing error code in one of these domains, the extension
 should construct an NSError with domain NSCocoaErrorDomain and code NSXPCConnectionReplyInvalid.
 The extension should set the NSUnderlyingErrorKey in the NSError's userInfo to the error which could not
 be represented.

 Cancellations:
 ------------
 If the NSProgress returned by this method is cancelled, the extension should
 call the completion handler with (nil, [], NO, NSUserCancelledError) in the NSProgress
 cancellation handler.
 */
- (NSProgress *)modifyItem:(NSFileProviderItem)item
               baseVersion:(NSFileProviderItemVersion *)version
             changedFields:(NSFileProviderItemFields)changedFields
                  contents:(nullable NSURL *)newContents
                   options:(NSFileProviderModifyItemOptions)options
                   request:(NSFileProviderRequest *)request
         completionHandler:(void(^)(NSFileProviderItem _Nullable item,
                                    NSFileProviderItemFields stillPendingFields,
                                    BOOL shouldFetchContent,
                                    NSError * _Nullable error))completionHandler;

/**
 Delete an item forever.

 This is called when the user deletes an item that was already in the Trash and
 the item should no longer appear there after this call.  This call should
 remove the item from the working set.

 This call receives an optional baseVersion which represent the version of the
 item we are trying to delete.

 Unless the NSFileProviderDeleteItemRecursive options is passed, the
 deletion of a directory should be non-recursive. If the deletion is recursive
 the provider should take care of reporting the deletion of all the deleted
 items through the working set.

 Delete is gated by the capabilities of the removed item with
 NSFileProviderItemCapabilitiesAllowsDeleting.

 Modifications are gated by NSFileProviderItemCapabilitiesAllowsDeleting
 of the item on a UI level, but direct file system changes (e.g. from Terminal)
 can still result in changes that must be handled.

 Atomicity:
 ----------
 By default, the system assumes all the changes are applied non-atomically, which
 means that the change or an intermediary state from the change can be observed
 (for instance while enumerating the working set) while the call is in progress
 (before the completion handler is called). The provider can indicate to the system
 that it applies changes atomically (that is, the change cannot be observed before
 the completion handler is called) by setting the key NSExtensionFileProviderAppliesChangesAtomically
 in the Info.plist of the extension to YES.

 Error cases:
 ------------
 The extension may fail the deletion in different scenarios, for instance because
 the baseVersion is out of date or because the user does not have permissions to
 delete the item. In that case the extension should fail the call with the
 NSFileProviderErrorDeletionRejected error code which will cause the system to
 re-create the deleted item on disk based on the latest metadata available from
 the extension.

 If the options don't include NSFileProviderDeleteItemRecursive and the
 deletion targets a non-empty directory, the extension must reject the deletion
 with the NSFileProviderErrorDirectoryNotEmpty error code. This error can also
 be reported in case some children of the directory cannot be deleted when
 receiving the NSFileProviderDeleteItemRecursive option. In both cases,
 the system will re-create the deleted item on disk based on the latest metadata
 available from the extension.

 If the deletion targets an item that is unknown from the extension because
 that item may have already been deleted remotely, then the extension should
 report a success.

 The extension can also report the NSFileProviderErrorNotAuthenticated,
 NSFileProviderErrorServerUnreachable, or NSFileProviderErrorCannotSynchronize
 in case the deletion cannot be applied because of the current state of the
 system / domain. In that case, the system will present an appropriate error
 message and back off until the next time it is signalled.

 Any other error, including crashes of the extension process, will be considered to be transient
 and will cause the deletion to be retried.

 Errors must be in one of the following domains: NSCocoaErrorDomain, NSFileProviderErrorDomain.

 For errors which can not be represented using an existing error code in one of these domains, the extension
 should construct an NSError with domain NSCocoaErrorDomain and code NSXPCConnectionReplyInvalid.
 The extension should set the NSUnderlyingErrorKey in the NSError's userInfo to the error which could not
 be represented.

 Cancellations:
 ------------
 If the NSProgress returned by this method is cancelled, the extension should
 call the completion handler with (NSUserCancelledError) in the NSProgress
 cancellation handler.
 */
- (NSProgress *)deleteItemWithIdentifier:(NSFileProviderItemIdentifier)identifier
                             baseVersion:(NSFileProviderItemVersion *)version
                                 options:(NSFileProviderDeleteItemOptions)options
                                 request:(NSFileProviderRequest *)request
                       completionHandler:(void (^)(NSError * _Nullable))completionHandler
    NS_SWIFT_NAME(deleteItem(identifier:baseVersion:options:request:completionHandler:));


#pragma mark - Optional selectors

@optional

/** Signal the end of import of on-disk items.

 This is called after a reimport of on-disk items has been triggered by either
 `-[NSFileProviderManager reimportItemsBelowItemWithIdentifier:completionHandler:]`
 or after a new domain is created using
 `+[NSFileProviderManager importDomain:fromDirectoryAtURL:completionHandler:]` or
 `+[NSFileProviderManager addDomain:completionHandler:]`.

 `reimport` can also be started by the system independently from any request by the
 provider. The provider can detect those events by monitoring
 `-[NSFileProviderDomain backingStoreIdentity]`.

 During import, found items will be created via the
 -[NSFileProviderExtension createItemBasedOnTemplate:fields:contents:options:completionHandler:]
 call with the NSFileProviderCreateItemMayAlreadyExist flag set.
 At the end of an import the -[NSFileProviderExtension importDidFinishWithCompletionHandler:]
 is called.

 The system will attempt to import items as they are accessed by the user or applications. Import
 of the other items is scheduled by the system as a background task. That task may be delayed,
 for instance in low-power situations, or when the system is under heavy load. The provider can
 force the system to process a folder and its direct children by issuing a coordination request
 on that folder.
 */
- (void)importDidFinishWithCompletionHandler:(void (^)(void))completionHandler;

/**
 Called by the system if the set of materialized items changes.

 Materialized items are items that have synced to disk and are not
 dataless.  They may contain a mix of dataless and materialized files and
 directories, but in any case, all their children are represented on disk.
 Traversals of dataless directories by applications trigger an enumeration
 against the file provider extension; traversals of materialized directories
 do not.  It is the responsability of the file provider extension to notify
 the system on remote changes of these files: there is no alternative cache
 invalidation mechanism.

 If the extension doesn't keep track of the materialized set, it will have to
 notify the system of all remote changes.  In that case the working set is the
 entire dataset.  The system may drop items whose parent isn't materialized, to
 avoid unnecessary disk usage.  This saves some I/O, but isn't optimal.  The
 filtering by parentItemIdentifier is better done in the extension;  ideally,
 it would even be done server-side.  A hybrid model is possible, where some
 filtering is done server-side, and some finer filtering is done client-side.

 The file provider extension should therefore keep a list of the identifiers of
 the materialized directories.  This method is called when a new directory is
 materialized or when a materialized directory is rendered dataless.

 To enumerate the set of materialized containers,
 - Call -enumeratorForMaterializedItems on the instance of
   NSFileProviderManager corresponding to your domain;
 - Implement the NSFileProviderEnumerationObserver and
   NSFileProviderChangeObserver on an object;
 - Pass that object to the enumerator;
 - Use the identifiers of items or changes you receive to note the
   materialization status in your database.

 When an item is created, modified or deleted remotely, the file provider
 extension should check whether its parentItemIdentifier is in the materialized
 set.  If it is, the extension needs to inform the system so the system may
 create, modify or delete the file or directory (initially dataless) on disk.
 In the case when an item is reparented, the test should be that either the new
 or the old parentItemIdentifier is in the materialized set.  No need to pretend
 that the iten was deleted if the new parentItemIdentifier is no longer in the
 materialized set: the system will know what to do with an unknown parent
 identifier.

 To notify the system of this created, modified or deleted item,
 - Call -signalEnumeratorForContainerItemIdentifier: on the working set, i.e the
   container identified by NSFileProviderWorkingSetContainerItemIdentifier;
 - Include this item in the next enumeration of the working set.

 Since this method is called on every change of the set of materialized items,
 it is advisable to use it to set a flag and perform any resulting work as a
 timed task rather than performing any work directly.
 */
- (void)materializedItemsDidChangeWithCompletionHandler:(void (^)(void))completionHandler;

/**
 Called by the system when the set of pending items is refreshed.

 The pending enumerator lists all the items for which a change has been observed either
 on the disk or in the working set more than one second ago and that change hasn't been
 applied on the other side yet. An item can appear in the pending set for various reasons:
 - the system is under load and cannot process all the events in a timely fashion
 - a long running operation is scheduled or running for the item to be in sync (for instance,
    the download or the upload of a new content)
 - an error occurred, in which case the error will be set on the item as `downloadError` if
    it occurred when applying a change to the disk, or `uploadError` in the other way around.

 The pending set will only include items that comply to the following rules:
 - They have been queued for changes for more time than the refresh interval;
 - The items are already known by the provider.

 These constraints imply that initial transfer of a file from the disk to the provider will not
 be listed in the pending set, even though the transfer could take several minutes to complete

 The pending set is refreshed regurlary but only if there are meaningful changes:
 new pending items, items that were pending but are not anymore (deletions from the set),
 or domain version changed and set is not empty

 To enumerate the set of pending items,
 - Call -enumeratorForPendingItems on the instance of
   NSFileProviderManager corresponding to your domain;
 - Implement the NSFileProviderEnumerationObserver and
   NSFileProviderChangeObserver on an object;
 - Pass that object to the enumerator;
 - It will get called upon change to the set.

 This method is regularly called when changes happen to the pending set.
 implementeers are advised that this call will not happen as soon as an item is pending.
 Thus, implementeers should not use the pending set to detect when a change happens.
 The pending set will only contain items that were pending for a least one second before the
 last refresh date.
 */
- (void)pendingItemsDidChangeWithCompletionHandler:(void (^)(void))completionHandler FILEPROVIDER_API_AVAILABILITY_V3_1;

@end

#pragma mark - Additional protocols

/**
 Protocol to implement if the provider instance supports fetching incremental content changes.
 */
FILEPROVIDER_API_AVAILABILITY_V3
@protocol NSFileProviderIncrementalContentFetching <NSObject>

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
                                           request:(NSFileProviderRequest *)request
                                 completionHandler:(void(^)(NSURL * _Nullable fileContents, NSFileProviderItem _Nullable item, NSError * _Nullable error))completionHandler
    NS_SWIFT_NAME(fetchContents(for:version:usingExistingContentsAt:existingVersion:request:completionHandler:));

@end

FILEPROVIDER_API_AVAILABILITY_V3
@protocol NSFileProviderServicing <NSObject>

/**
 A file provider can implemement this method to return service sources that provide custom
 communication channels to client applications.

 The service sources must be tied to the item identified by @c itemIdentifier.
 Client applications can retrieve the list of supported services by calling
 @c -[NSFileManager getFileProviderServicesForItemAtURL:] for a specific item URL.

 Cancellations:
 ------------
 If the NSProgress returned by this method is cancelled, the extension should
 call the completion handler with (nil, NSUserCancelledError) in the NSProgress
 cancellation handler.
*/
- (NSProgress *)supportedServiceSourcesForItemIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                                       completionHandler:(void (^)(NSArray <id <NSFileProviderServiceSource>> * _Nullable, NSError * _Nullable))completionHandler
    NS_SWIFT_NAME(supportedServiceSources(for:completionHandler:));

@end

/**
 Protocol to implement if the provider supports fetching thumbnails for its items.
 */
FILEPROVIDER_API_AVAILABILITY_V3
@protocol NSFileProviderThumbnailing <NSObject>

/**
 The system calls this method to fetch thumbnails.

 The @p perThumbnailCompletionHandler should be called for each thumbnail, and
 @p completionHandler only after all the per thumbnail completion blocks.

 In the event of a global error, the implementation is allowed to skip calling
 the @p perThumbnailCompletionHandler for individual thumbnails. In that case,
 the @p completionHandler's error parameter would apply to all item identifiers
 for which @p perThumbnailCompletionHandler had not been called.

 If there is no thumbnail for a given item, the @p perThumbnailCompletionHandler
 should be called with its @p imageData and @p error parameters both
 set to nil.

 If the system decides that an in-flight thumbnail request is not needed anymore,
 it will call the returned @p NSProgress object's @p -cancel method,
 at which time the implementation should clean up any held resources.

 The system will cache the thumbnail for the item, and the cache will be
 invalidated when itemVersion.contentVersion changes.

 Thread safety:
 ------------

 The @p perThumbnailCompletionHandler may be called from multiple threads
 concurrently.

 Cancellations:
 ------------
 If the NSProgress returned by this method is cancelled, the extension should
 call the completion handler with (NSUserCancelledError) in the NSProgress
 cancellation handler.
 */
- (NSProgress *)fetchThumbnailsForItemIdentifiers:(NSArray<NSFileProviderItemIdentifier> *)itemIdentifiers
                                    requestedSize:(CGSize)size
                    perThumbnailCompletionHandler:(void (^)(NSFileProviderItemIdentifier identifier, NSData * _Nullable imageData, NSError * _Nullable error))perThumbnailCompletionHandler
                                completionHandler:(void (^)(NSError * _Nullable error))completionHandler
    NS_SWIFT_NAME(fetchThumbnails(for:requestedSize:perThumbnailCompletionHandler:completionHandler:));

@end

FILEPROVIDER_API_AVAILABILITY_V3
@protocol NSFileProviderCustomAction  <NSObject>

/**
 Perform a custom action identified by `actionIdentifier`, on items identified by
 `itemIdentifiers`.

 Custom actions are defined in the File Provider Extension's Info.plist, under the
 `NSExtensionFileProviderActions` key. The format of this key is identical to actions
 defined in a FileProviderUI extension.

 Cancellations:
 ------------
 If the NSProgress returned by this method is cancelled, the extension should
 call the completion handler with (NSUserCancelledError) in the NSProgress
 cancellation handler.
 */
- (NSProgress *)performActionWithIdentifier:(NSFileProviderExtensionActionIdentifier)actionIdentifier
                     onItemsWithIdentifiers:(NSArray <NSFileProviderItemIdentifier> *)itemIdentifiers
                          completionHandler:(void (^)(NSError * _Nullable error))completionHandler
    NS_SWIFT_NAME(performAction(identifier:onItemsWithIdentifiers:completionHandler:));

@end

/**
 Protocol to implement for managing UserInteraction alerts.
 */
FILEPROVIDER_API_AVAILABILITY_V4_0
@protocol NSFileProviderUserInteractionSuppressing  <NSObject>

/**
 Suppression management:

 The extension may choose to give the user the option to suppress certain UserInteraction alerts.
 In order to do so, the extension must both implement NSFileProviderUserInteractionSuppressing, as well as
 configure the desired UserInteractions in the Info.plist with the `SuppressionIdentifier` field.

 When FileProvider needs to evaluate whether to display a UserInteraction alert, it will call
 -[NSFileProviderUserInteractionSuppressing isInteractionSuppressedForIdentifier:]. When the user indicates that they do not
 wish to see a given SuppressionIdentifiers's alert again, FileProvider will call
 -[NSFileProviderUserInteractionSuppressing setInteractionSuppressed:forIdentifier:].

 The extension can choose whether the suppression should apply only to the domain upon which
 -[NSFileProviderUserInteractionSuppressing setInteractionSuppressed:forIdentifier:] was called, or if it should apply to all
 domains for their provider. For instance, the extension could choose to suppress future alerts related
 to adding an item to a shared folder across all domains, after the user chooses to suppress the alerts
 in a specific domain's context. Or, the extension could choose to only suppress that alert for the
 specific domain it was displayed within, and in the future, the user would see the same alert in the same
 context, if they take the same action in another domain.
 */

- (void)setInteractionSuppressed:(BOOL)suppression forIdentifier:(NSString *)suppressionIdentifier;
- (BOOL)isInteractionSuppressedForIdentifier:(NSString *)suppressionIdentifier;

@end

FILEPROVIDER_API_AVAILABILITY_V3_1
@protocol NSFileProviderDomainState <NSObject>

/**
 Version of the domain.

 The domain version is an opaque value assigned by the provider. It is read by the system in the
 completion handler for createItemBasedOnTemplate, modifyItem, deleteItem and itemForIdentifier, as
 well as in the finish calls when enumerating the working set. The read is guaranteed to happen
 on the same dispatch queue the completion handler was called on.

 When the system discovers a change on disk, it associates that change to the currently known
 domain version. When that change get communicated to the extension, that version is included in
 the NSFileProviderRequest object passed by the system to the extension. As a consequence, the
 provider can use the domain version to identify the state of the system when a change was made on disk.

 The provider is responsible for defining when the domain version changes. When that value is
 updated, the provider must notify the system by signaling the working set.

 The system ignore any domain version that is smaller than the previously known version.
 */
@property (nonatomic, readonly) NSFileProviderDomainVersion *domainVersion;

/**
 Global state of the domain.

 Use this dictionary to add state information to the domain. It is accessible to predicates for
 User Interactions, FileProvider Actions, and FileProviderUI Actions, via the top-level `domainUserInfo` context
 key.

 This dictionary must only contain key and value classes in the following list:
 NSString, NSNumber, NSDate, and NSPersonNameComponents.

 The system expects the domainVersion to be updated when the value of the userInfo property
 changes.
 */
@property (nonatomic, strong, readonly, nonnull) NSDictionary *userInfo;

@end

FILEPROVIDER_API_AVAILABILITY_V4_1
@protocol NSFileProviderPartialContentFetching <NSObject>

/**
 Download the requested extent of an item for the given identifier and return it via the completion
 handler.  If this protocol is not implemented the system defaults to fetchContentsForItemWithIdentifier.

 The requestedVersion parameter specifies which version should be returned. This version will always be
 specified by the system so as to prevent extents from different versions from being written into the same
 file. The system tolerates a version mismatch for the first materialization of a fully dataless file (strictVersion=NO).

 The requested range is <location, length>.  The implementation can provide any properly aligned range that
 covers the requested range (including the entire item).  The system provides the minimal alignment value.
 The location (or start offset) of the fetched range should be a multiple of this value for it to be considered
 properly aligned. The length of the fetched range should be a multiple of this value, with an exception for
 the end of the file, checked against the documentSize attribute the implementation supplied for this item.
 The alignment value should not be expected to be stable across reboots. It is guaranteed by the system to be
 a power of two.
 In addition to the content the extension needs to fill in fetchedRange with either the requestest range,
 <location, length>, or indicate full materialization with, <0, file size>.

 Concurrent Downloads:
 ----------
 The system will call fetchContents concurrently if there are multiple outstanding file download requests.
 The provider can control the concurrency by setting the key NSExtensionFileProviderDownloadPipelineDepth
 in the Info.plist of the extension to the number of concurrent downloads that the system should create
 per domain. This number must be between 1 and 128, inclusive.

 File ownership:
 ---------------
 The system clones and unlinks the received fileContents. The extension should not mutate the corresponding
 file after calling the completion handler. If the extension wishes to keep a copy of the content, it must
 provide a clone of the that content as the URL passed to the completion handler.

 In case the extension or the system crashes between the moment the completion handler is called and the
 moment the system unlinks the file, the file may unexpectedly still be on disk the next time an instance
 of the extension is created. The extension is then responsible for deleting that file.

 Disallowing processes from fetching items:
 ---------------

 The system automatically downloads files on POSIX accesses. The extension may wish to disallow this class of
 downloads for specific applications.  Currently only POSIX accesses trigger this message so that would render this
 message superfluous in such cases.

 The extension can set an array of strings into the UserDefault key
 "NSFileProviderExtensionNonMaterializingProcessNames". A process whose name is an exact match for an
 entry in this array will not be allowed to fetch items in the extension's domains.

 This list will not be checked for downloads requested through file coordination.

 Error cases:
 ------------
 If the download fails because the item is unknown, the call should
 fail with the NSFileProviderErrorNoSuchItem error. In that case, the system
 will consider the item has been removed from the domain and will attempt to
 delete it from disk. In case that deletion fails because there are local
 changes on this item, the system will re-create the item using createItemBasedOnTemplate.

 If the user does not have access to the content of the file, the provider
 can fail the call with NSCocoaErrorDomain and code NSFileReadNoPermissionError.
 That error will then be presented to the user. The extension can also report
 the NSFileProviderErrorNotAuthenticated, NSFileProviderErrorServerUnreachable
 in case the item cannot be fetched because of the current state of the system / domain.
 In those cases, the system will present an appropriate error message and back off
 until the next time it is signalled.

 If the requested version cannot be retrieved, the provider can choose to provide a different
 version of the file, unless NSFileProviderFetchContentsOptionsStrictVersioning  is set. In this case,
 the provider should fail with NSFileProviderErrorVersionNoLongerAvailable.
 If some content is returned, the item must have the corresponding version. The system will detect
 any mismatch and handle it as a remote update.
 For the reading application, the materialization will fail with the same error as reading from
 a dataless file that got remotely updated (-1/errno=ESTALE). Upon retry the new version will be
 requested by the system.

 Any other error will be considered to be transient and will cause the
 download to be retried.

 Cancellations:
 ------------
 If the NSProgress returned by this method is cancelled, the extension should
 call the completion handler with (nil, nil, someRange, 0, NSUserCancelledError) in the NSProgress
 cancellation handler.

 The returned NSProgress is used to show progress to the user. If the user cancels the
 fetch, the extension should stop fetching the item, as it is no longer required.

 */
- (NSProgress *)fetchPartialContentsForItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                                                  version:(NSFileProviderItemVersion *)requestedVersion
                                                  request:(NSFileProviderRequest *)request
                                             minimalRange:(NSRange)requestedRange
                                               aligningTo:(NSUInteger)alignment
                                                  options:(NSFileProviderFetchContentsOptions)options
                                        completionHandler:(void(^)(NSURL * _Nullable fileContents,
                                                                   NSFileProviderItem _Nullable item,
                                                                   NSRange retrievedRange,
                                                                   NSFileProviderMaterializationFlags flags,
                                                                   NSError * _Nullable error))completionHandler
    NS_SWIFT_NAME(fetchPartialContents(for:version:request:minimalRange:aligningTo:options:completionHandler:));

@end

NS_ASSUME_NONNULL_END
