//
//  NSFileProviderError.h
//  FileProvider
//
//  Copyright (c) 2014-2020 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderItem.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSErrorDomain const NSFileProviderErrorDomain FILEPROVIDER_API_AVAILABILITY_V2_V3;

FOUNDATION_EXPORT NSErrorUserInfoKey const NSFileProviderErrorCollidingItemKey API_DEPRECATED("NSFileProviderErrorItemKey", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos) API_UNAVAILABLE(macCatalyst);
FOUNDATION_EXPORT NSErrorUserInfoKey const NSFileProviderErrorItemKey API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos);
FOUNDATION_EXPORT NSErrorUserInfoKey const NSFileProviderErrorNonExistentItemIdentifierKey FILEPROVIDER_API_AVAILABILITY_V2_V3;


typedef NS_ERROR_ENUM(NSFileProviderErrorDomain, NSFileProviderErrorCode) {
    /** The user credentials cannot be verified */
    NSFileProviderErrorNotAuthenticated  = -1000,

    /** An item already exists with the same parentItemIdentifier and filename (or with a filename differing only in case.)

     \note Please use -[NSError (NSFileProviderError) fileProviderErrorForCollisionWithItem:] to build an error with this code.
     \see -[NSError (NSFileProviderError) fileProviderErrorForCollisionWithItem:]
     */
    NSFileProviderErrorFilenameCollision = -1001,

    /** The value of the sync anchor is too old, and the system must re-sync from scratch */
    NSFileProviderErrorSyncAnchorExpired = -1002,

    /** The value of the page token is too old, and the system must re-sync from scratch */
    NSFileProviderErrorPageExpired        = NSFileProviderErrorSyncAnchorExpired,

    /** The item has not been uploaded because it would push the account over quota */
    NSFileProviderErrorInsufficientQuota = -1003,

    /** Connecting to the servers failed */
    NSFileProviderErrorServerUnreachable = -1004,

    /** The requested item doesn't exist

     \note Please use -[NSError (NSFileProviderError) fileProviderErrorForNonExistentItemWithIdentifier:] to build an error with this code.
     \see -[NSError (NSFileProviderError) fileProviderErrorForNonExistentItemWithIdentifier:]
     */
    NSFileProviderErrorNoSuchItem        = -1005,

    /** The provider disallowed the deletion of the item.

     \note Please use -[NSError (NSFileProviderError) fileProviderErrorForRejectedDeletionOfItem:] to build an error with this code.
     \see -[NSError (NSFileProviderError) fileProviderErrorForRejectedDeletionOfItem:]
     */
    NSFileProviderErrorDeletionRejected FILEPROVIDER_API_AVAILABILITY_V3_IOS = -1006,

    /** We're trying to non-recursively delete a non-empty directory
     */
    NSFileProviderErrorDirectoryNotEmpty FILEPROVIDER_API_AVAILABILITY_V3_IOS = -1007,

    /**
     Returned by NSFileProviderManager if no provider could be found in the application
     */
    NSFileProviderErrorProviderNotFound FILEPROVIDER_API_AVAILABILITY_V3_IOS = -2001,

    /**
     Returned by NSFileProviderManager if the application's provider has been disabled due to app translocation
     */
    NSFileProviderErrorProviderTranslocated FILEPROVIDER_API_AVAILABILITY_V3 = -2002,

    /**
     Returned by NSFileProviderManager if the provider registered in the system is an older version than the one corresponding to this app.
     The `NSFilePathErrorKey` key points to the location of the older version. If the location of the older version cannot be determined (e.g. because it was since deleted), the `NSFilePathErrorKey` will not be set.
     */
    NSFileProviderErrorOlderExtensionVersionRunning FILEPROVIDER_API_AVAILABILITY_V3 = -2003,

    /**
     Returned by NSFileProviderManager if the provider registered in the system is a newer version than the one corresponding to this app.
     */
    NSFileProviderErrorNewerExtensionVersionFound FILEPROVIDER_API_AVAILABILITY_V3 = -2004,

    /**
     Indicates that synchronization cannot happen.

     This error can be returned by the provider or the system.

     This is returned by NSFileProviderManager if a barrier failed for a sync-related error.

     If the failure is caused by a specific item, the system will set the NSFileProviderErrorItemKey to the corresponding item identifier
     and the NSUnderlyingErrorKey will be set to the error encountered by that item.

     When a provider returns this error on createItem or updateItem, it means that syncing that item is definitively broken.
     The system will not retry syncing those items, until either:
     * The operating system has been updated.
     * The FileProvider extension has been updated.
     * The item is modified on disk.
     */
    NSFileProviderErrorCannotSynchronize FILEPROVIDER_API_AVAILABILITY_V3_IOS = -2005,

    /**
    Returned by NSFileProviderManager if directory eviction failed because the target contains non-evictable items.

    -[NSError underlyingErrors] is set to an array of the underlying errors. Each one has NSURLErrorKey set
    to identify the particular file or directory affected by this error. The number of reported failing items is capped to an
    implementation-defined number.

    + domain: NSFileProviderErrorDomain errorCode: NSFileProviderErrorUnsyncedEdits error: if the item had unsynced content.
    + domain: NSFileProviderErrorDomain errorCode: NSFileProviderErrorNonEvictable error: if the item has been marked as non-purgeable by the provider.
    + domain: NSPOSIXErrorDomain errorCode: EBUSY - if the item had open file descriptors on it.
    + domain: NSPOSIXErrorDomain errorCode: EMLINK : if the item had several hardlinks.
    */
    NSFileProviderErrorNonEvictableChildren FILEPROVIDER_API_AVAILABILITY_V3_1_IOS = -2006,

    /**
     Returned by NSFileProviderManager if item eviction is failing because the item has edits that have not been synced yet

     The NSURLErrorKey will be set to with the item URL that has unsynced content.
    */
    NSFileProviderErrorUnsyncedEdits FILEPROVIDER_API_AVAILABILITY_V3_1_IOS = -2007,

    /**
     Returned by NSFileProviderManager if item eviction is failing because the item has not been assigned the evictable capability.

     The NSURLErrorKey will be set to with the corresponding item URL.
    */
    NSFileProviderErrorNonEvictable FILEPROVIDER_API_AVAILABILITY_V3_1_IOS = -2008,

    /**
     Returned by the provider to indicate that the requested version for an item cannot be provided.

     When a provider returns that error, it means the version for this item is definitively unavailable. It is intended to be returned by
     fetchPartialContentsForItemWithIdentifier, when NSFileProviderFetchContentsOptionsStrictVersioning is set, to tell the system that a remote update
     happened to the item that outdated the requested version.
    */
    NSFileProviderErrorVersionNoLongerAvailable FILEPROVIDER_API_AVAILABILITY_V4_1 = -2009,

    /**
     Returned by createItemBasedOnTemplate or modifyItem if the provider does not wish to sync the item.

     When a provider returns this error, it causes the item to be excluded from sync. The system will ensure that
     the item (and any descendents, in case of a directory), are downloaded, and then issue a deleteItem call to the
     provider for the item.

     The system will call createItemBasedOnTemplate for the item, whenever the item's metadata changes on disk.
     This ensures that the provider's rules for excluding from sync are re-evaluated whenever the
     item's properties change.

     Re-evaluating items
     ------

     If the provider wishes for previously excluded items to be re-sent as createItemBasedOnTemplate calls,
     the provider may call -[NSFileProviderManager signalErrorResolved:completionHandler:] with this error code.

     If the provider wishes to exclude items which had previously been synced, the provider may call
     -[NSFileProviderManager requestModificationOfFields:forItemWithIdentifier:options:completionHandler:].
     This will cause the system to send a new modifyItem call to the provider. At that time, the provider can choose to
     return this error code.
    */
    NSFileProviderErrorExcludedFromSync FILEPROVIDER_API_AVAILABILITY_V2_V5 = -2010,

    /*
     Returned by the system to indicate that the domain is disabled by the user, and therefore the operation cannot be
     completed.
    */
    NSFileProviderErrorDomainDisabled FILEPROVIDER_API_AVAILABILITY_V5_0_IOS = -2011,

    /*
     Returned by the system to indicate that it is temporarily unable to service requests for this domain.
     The caller should expect the same API call to succeed at a later time.
     */
    NSFileProviderErrorProviderDomainTemporarilyUnavailable FILEPROVIDER_API_AVAILABILITY_V6_0_IOS = -2012,

    /*
     Returned by the system to indicate that there is no NSFileProviderDomain registered in the
     system which has the same identifier that was used to construct the NSFileProviderManager
     which made the API call.
     */
    NSFileProviderErrorProviderDomainNotFound FILEPROVIDER_API_AVAILABILITY_V6_0_IOS = -2013,

    /*
     Returned by the system to indicate that the system does not have any launchable
     `com.apple.fileprovider-nonui` application extension for this domain's app bundle.
     */
    NSFileProviderErrorApplicationExtensionNotFound FILEPROVIDER_API_AVAILABILITY_V6_0_IOS = -2014,

    /*
     Returned by the provider when a modifyItem with the failUploadOnConflict policy fails
     because of a conflict with the server version.
    */
    NSFileProviderErrorLocalVersionConflictingWithServer FILEPROVIDER_API_AVAILABILITY_SYNC_CONTROLS = -2015,
} FILEPROVIDER_API_AVAILABILITY_V2_V3;

@interface NSError (NSFileProviderError)
+ (instancetype)fileProviderErrorForCollisionWithItem:(NSFileProviderItem)existingItem FILEPROVIDER_API_AVAILABILITY_V2_V3;
+ (instancetype)fileProviderErrorForNonExistentItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier FILEPROVIDER_API_AVAILABILITY_V2_V3;
+ (instancetype)fileProviderErrorForRejectedDeletionOfItem:(NSFileProviderItem)updatedVersion NS_SWIFT_NAME(fileProviderErrorForRejectedDeletion(of:)) FILEPROVIDER_API_AVAILABILITY_V3_IOS;
@end

NS_ASSUME_NONNULL_END
