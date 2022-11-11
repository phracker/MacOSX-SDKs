//
//  NSFileProviderItem.h
//  FileProvider
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDefines.h>
#import <Foundation/Foundation.h>

@class UTType;

NS_ASSUME_NONNULL_BEGIN

FILEPROVIDER_API_AVAILABILITY_V1_V2_V3
typedef NSString *NSFileProviderItemIdentifier NS_EXTENSIBLE_STRING_ENUM;

/**
 The root of the hierarchical enumeration, i.e the container enumerated when the
 user starts browsing your file provider.
 */
FOUNDATION_EXPORT NSFileProviderItemIdentifier const NSFileProviderRootContainerItemIdentifier NS_SWIFT_NAME(NSFileProviderItemIdentifier.rootContainer) FILEPROVIDER_API_AVAILABILITY_V2_V3;

/**
 The item identifier of the working set, a synthetic container used by the
 extension to communicate changes to the system even when the parent directories
 of these items aren't actively being enumerated.  Items in this set should have
 their parentItemIdentifier set to the identifier of their parent directory.

 The working set is the set of files and directories that should be made
 available to the system regardless of the local browsing history.  Files listed
 in the working set are indexed in the local Spotlight index and appear in
 offline search results.  They contribute to the Recents view of the Files app,
 sorted by lastUsedDate, and it is therefore important to provide a consistent
 experience across devices by including in the working set all the documents
 recently used, trashed, favorited, shared or tagged.

 The Spotlight index and the Recents view will show outdated information unless
 the file provider extension keeps the working set up to date with local and
 remote changes.  When an item in the working set is remotely modified, the
 extension calls -signalEnumeratorForContainerItemIdentifier: on the identifier
 of the working set; the system will then enumerate changes and update its caches.

 Starting in iOS 12 and macOS 10.15, the system maintains a cache on the local
 file system of files and directories previously enumerated.  The working set
 is the container used to update that set of files.  The extension may know
 whether an item is in that set by checking whether its parentItemIdentifier
 is listed in the materialized containers, see the documentation on
 -materializedItemsDidChangeWithCompletionHandler:.
 */
FOUNDATION_EXPORT NSFileProviderItemIdentifier const NSFileProviderWorkingSetContainerItemIdentifier NS_SWIFT_NAME(NSFileProviderItemIdentifier.workingSet) FILEPROVIDER_API_AVAILABILITY_V2_V3;

/**
 The container containing all the trashed items.

 When an item is trashed, its `parentItemIdentifier` becomes `NSFileProviderTrashContainerItemIdentifier`.

 Extension should be able to return all trashed items by supporting the creation of a NSFileProviderEnumerator
 for the trashed items.
 */
FOUNDATION_EXPORT NSFileProviderItemIdentifier const NSFileProviderTrashContainerItemIdentifier NS_SWIFT_NAME(NSFileProviderItemIdentifier.trashContainer) FILEPROVIDER_API_AVAILABILITY_V3;

FILEPROVIDER_API_AVAILABILITY_V3
@interface NSFileProviderItemVersion : NSObject

/**
 Version component exposed by the system to denote a state that predates a version returned by the provider.

 In case an item was created by calling `createItemBasedOnTemplate` and the item returned by the provider in
 the completion handler of that call didn't match the item template passed by the system, the system will try
 to apply the changes asked by the provider to the disk. However, the system may detect conflicts when applying
 those content back to the disk, which will cause the system to send the new disk version to the extension,
 by calling `modifyItem` or `deleteItemWithIdentifier` with a `baseVersion` that represents the item as passed in
 the template of the `createItemBasedOnTemplate` call.

 This constant is used by the system to represent that specific version that was communicated by the system to
 the extension but does not have a corresponding version assigned by the extension.
 */
@property (class, readonly, nonnull) NSData *beforeFirstSyncComponent FILEPROVIDER_API_AVAILABILITY_V4_0;

/**
 Items versions have two distinct components, one for the file contents and one
 for metadata.

 Components are limited to 128 bytes in size.
 */
- (instancetype)initWithContentVersion:(NSData *)contentVersion
                       metadataVersion:(NSData *)metadataVersion;

/**
 Version data for the content of the file.
 
 This property is used by the system for two purposes: if the contentVersion changes,
 - the system assumes that the contents have changed and will trigger a redownload if
   necessary. The exception to this is the case where the extension accepts a content
   sent by the system when replying to a createItemBasedOnTemplate or modifyItem call
   with shouldFetchContent set to NO.
 - the thumbnail cache is invalidated

 Note that the resource fork of the file is considered content, so this version
 data should change when either the data fork or the resource fork changes.
 */
@property (nonatomic, readonly) NSData *contentVersion;

/**
 Version data for the metadata of the item, i.e everything but the data fork and
 the resource fork.
 
 The system will store this version, but otherwise ignore it:
 - metadata changes on an item will be applied even if the metadataVersion remains unchanged
 - if the metadata version changes without any corresponding observable changes in the metadata returned
   to the system, the system will simply store the updated metadata version (to return it as the base version
   of a possible future change request).
 */
@property (nonatomic, readonly) NSData *metadataVersion;

@end


/**
 A special value for favorite ranks, to use when no rank was set when the item
 was favorited.
 */
FOUNDATION_EXPORT unsigned long long const NSFileProviderFavoriteRankUnranked FILEPROVIDER_API_AVAILABILITY_V2_V3;

FILEPROVIDER_API_AVAILABILITY_V2_V3
typedef NS_OPTIONS(NSUInteger, NSFileProviderItemCapabilities) {
    /**
     Indicates that the file can be opened for reading.  If set on a folder
     this is equivalent to @c .allowsContentEnumerating.
     */
    NSFileProviderItemCapabilitiesAllowsReading     = 1 << 0,

    /**
     Indicates that the file can be opened for writing. If set on a folder,
     this is equivalent to @c .allowsAddingSubItems.
     */
    NSFileProviderItemCapabilitiesAllowsWriting     = 1 << 1,

    /** Indicates that the item can be moved to another folder */
    NSFileProviderItemCapabilitiesAllowsReparenting = 1 << 2,

    /** Indicates that the item can be renamed */
    NSFileProviderItemCapabilitiesAllowsRenaming    = 1 << 3,

    /** Indicates that the item can be moved to the trash */
    NSFileProviderItemCapabilitiesAllowsTrashing    = 1 << 4,

    /** Indicates that the item can be deleted */
    NSFileProviderItemCapabilitiesAllowsDeleting    = 1 << 5,

    /**
     Indicates that the item can be evicted.

     If this capability is set on an item, the item will become evictable when the item is fully uploaded
     (-[NSFileProviderItem isUploaded] not implemented or set to YES), is not actively used and contains no
     local changes. The eviction can happen either because the user selected the "Remove Download" option
     in Finder, because the provider decided to evict the item using `-[NSFileProviderManager evictItemWithIdentifier:completionHandler:]`,
     or because the system ran into a low-disk space scenario.

     If this capability is not present, the item will never be evicted.
     If the provider wishes to only suppress the user's ability to evict the item in the UI (but retain the ability
     of the OS or the provider's program to evict items), the provider can set the following key to false in
     their Info.plist, in the NSExtension section: NSExtensionFileProviderAllowsUserControlledEviction
     */
    NSFileProviderItemCapabilitiesAllowsEvicting FILEPROVIDER_API_AVAILABILITY_V3 = 1 << 6,

    /**
     Indicates that the item can be excluded from sync.

     The user can choose to exclude the item in the UI (Finder), in which case the system will stop
     monitoring changes for the item and its children and will remove the item from the provider.

     This capability can be used to allow an item to be excluded from sync.
     */
    NSFileProviderItemCapabilitiesAllowsExcludingFromSync FILEPROVIDER_API_AVAILABILITY_V3_1 = 1 << 7,

    /**
     Indicates that items can be imported to the folder. If set on a file,
     this is equivalent to @c .allowsWriting.
     */
    NSFileProviderItemCapabilitiesAllowsAddingSubItems = NSFileProviderItemCapabilitiesAllowsWriting,

    /**
     Indicates that the folder can be enumerated. If set on a file, this is
     equivalent to @c .allowsReading.
     */
    NSFileProviderItemCapabilitiesAllowsContentEnumerating = NSFileProviderItemCapabilitiesAllowsReading,

    NSFileProviderItemCapabilitiesAllowsAll API_DEPRECATED("This capability is no longer supported, and does not contain all capabilities. Please migrate to directly specifying each of the individual capabilities that should be allowed for the item.", ios(11.0, 15.0), macos(11.0, 12.0)) =
          NSFileProviderItemCapabilitiesAllowsReading
        | NSFileProviderItemCapabilitiesAllowsWriting
        | NSFileProviderItemCapabilitiesAllowsReparenting
        | NSFileProviderItemCapabilitiesAllowsRenaming
        | NSFileProviderItemCapabilitiesAllowsTrashing
        | NSFileProviderItemCapabilitiesAllowsDeleting
};

FILEPROVIDER_API_AVAILABILITY_V3
typedef NS_OPTIONS(NSUInteger, NSFileProviderFileSystemFlags) {
    /// Item has the POSIX user-executable (u+x) permission.
    NSFileProviderFileSystemUserExecutable      = 1 << 0,

    /// Item has the POSIX user-readable (u+r) permission.
    NSFileProviderFileSystemUserReadable        = 1 << 1,

    /// Item has the POSIX user-writable (u+w) permission.
    NSFileProviderFileSystemUserWritable        = 1 << 2,

    /// Item should not be presented in the file viewers.
    ///
    /// This includes both the UF_HIDDEN BSD flag and the Invisible bit from the
    /// FinderInfo. When syncing down, the system only sets the UF_HIDDEN
    /// flag.
    NSFileProviderFileSystemHidden              = 1 << 3,

    /// The extension of the item should not be presented in the file viewers.
    NSFileProviderFileSystemPathExtensionHidden = 1 << 4,
};

FILEPROVIDER_API_AVAILABILITY_V4_0
typedef struct NSFileProviderTypeAndCreator {
    /**
     The first word of the FinderInfo structure. It matches the file type code
     */
    OSType type;
    /**
     The second word of the FinderInfo structure. It matches the creator code
     */
    OSType creator;
} NSFileProviderTypeAndCreator;

FILEPROVIDER_API_AVAILABILITY_V2_V3
@protocol NSFileProviderItem <NSObject>

/**
 The identifier of the item.

 The itemIdentifier should not contain sensitive information, as it may be recorded in system logs and
 diagnostic files.
 */
@property (nonatomic, readonly, copy) NSFileProviderItemIdentifier itemIdentifier;

/**
 The parent identifier specifies the parent of the item in the hierarchy.

 Set to NSFileProviderRootContainerItemIdentifier for an item at the root of the
 user's storage.  Set to the itemIdentifier of the item's parent otherwise.

 When enumerating the root container or a generic container, the
 parentItemIdentifier of the enumerated items is expected to match the
 enumerated item's identifier.  When enumerating the working set, the
 parentItemIdentifier is expected to match the actual parent of the item in the
 hierarchy (ie. it is not NSFileProviderWorkingSetContainerItemIdentifier).

 The parents of trashed items and of the root item are ignored.
 */
@property (nonatomic, readonly, copy) NSFileProviderItemIdentifier parentItemIdentifier;

/**
 The file or directory name, complete with its file extension.

 The filename property must not be an empty string, including when the item identifier is
 NSFileProviderRootContainerItemIdentifier. The filename for NSFileProviderRootContainerItemIdentifier
 may be displayed in the user interface. Therefore it should be a user-friendly string.
 */
@property (nonatomic, readonly, copy) NSString *filename;

@optional

/**
 ContentType (UTType) for the item.

 On macOS, items must implement contentType.

 On iOS, items must implement either contentType or typeIdentifier. Note
 that contentType is not available on iOS 13 and earlier, so typeIdentifier
 is required in order to target iOS 13 and earlier.

 When using NSFileProviderReplicatedExtension, providers must be prepared
 to handle the following contentType in the appropriate manner
 when they are passed in itemTemplates contentType to createItem/modifyItem calls:
 * UTType.symbolicLink
 * UTType.folder
 * UTType.package
 * UTType.aliasFile

 Changing the contentType for a given item that would result in a transition to/from a folder
 or to/from a symlink is not supported.
 */
@property (nonatomic, readonly, copy) UTType *contentType API_AVAILABLE(ios(14.0), macos(11.0));

/**
 Uniform type identifier (UTI) for the item.

 This property is deprecated in favor of the "contentType" property.

 On macOS, typeIdentifier is not available. Items must implement contentType
 on macOS.

 On iOS, items must implement either contentType or typeIdentifier. Note
 that contentType is not available on iOS 13 and earlier, so typeIdentifier
 is required in order to target iOS 13 and earlier.
 */
@property (nonatomic, readonly, copy) NSString *typeIdentifier
    API_DEPRECATED_WITH_REPLACEMENT("contentType", ios(11.0, 15.0))
    API_UNAVAILABLE(macos);

/**
 File type and creator code for the item.

 This property contains two variables, one for the file type code and one for the creator code.
 Both will be synchronized at the same time, so you have to define both when changing one.

 On change on this structure, the NSFileProviderItemTypeAndCreator field will be set in the
 NSFileProviderItemFields argument to createItem/modifyItem.

 These will be written down in the FinderInfo structure if relevant.
 */
@property (nonatomic, readonly) NSFileProviderTypeAndCreator typeAndCreator FILEPROVIDER_API_AVAILABILITY_V4_0;

/**
 The capabilities of the item.  This controls the list of actions that the UI
 will allow for the item.

 Capabilities on an item only apply to the item itself. They are not inherited by the children of directories.
 */
@property (nonatomic, readonly) NSFileProviderItemCapabilities capabilities;

/**
 File System level flags.

 This includes POSIX permissions and presentation options for the item.

 Prior to macOS 11.3, fileSystemFlags are not honored for directories.
 */
@property (nonatomic, readonly) NSFileProviderFileSystemFlags fileSystemFlags FILEPROVIDER_API_AVAILABILITY_V3;

@property (nonatomic, readonly, copy, nullable) NSNumber *documentSize;
@property (nonatomic, readonly, copy, nullable) NSNumber *childItemCount;
@property (nonatomic, readonly, copy, nullable) NSDate *creationDate;
@property (nonatomic, readonly, copy, nullable) NSDate *contentModificationDate;

/**
 Syncable extended attributes on the file.

 The system decides which extended attributes should be synced from the device,
 based on a set of rules largely inferred from the name of the extended
 attribute.  Extended attributes named with xattr_name_with_flags(XATTR_FLAG_SYNCABLE)
 will be listed in this dictionary; some extended attributes introduced before
 this API are also whitelisted for sync. The provider can declare of list of
 attributes it wants to sync even if the system heuristic won't consider those
 as syncable. For this, it can add a list of xattr names in the Info.plist of the
 extension under the key NSExtensionFileProviderAdditionalSyncableExtendedAttributes.

 Syncable xattrs are capped in size to about 32KiB total for a given item.
 When the set of extended attributes on a file is larger than that, the system
 demotes some of the extended attributes to non-syncable.

 The system decides which non-syncable extended attributes should be preserved
 locally when the item is updated remotely, based on a set of rules again largely
 inferred from the name of the extended attribute.  Extended attributes named
 with xattr_name_with_flags(XATTR_FLAG_CONTENT_DEPENDENT) will be preserved only
 if itemVersion.contentVersion was not modified by the remote update.

 Some NSFileProviderItem properties (lastUsedDate, tagData...) happen to be
 stored on disk in extended attributes that won't be listed in this dictionary
 because that would be redundant.  The 32 bits of Finder info in the extended
 attribute named XATTR_FINDERINFO_NAME ("com.apple.FinderInfo") is not listed
 here for the same reason: the syncable Finder info bits are deserialized to
 other properties of NSFileProviderItem.

 The system will set extended attributes on dataless files, and will preserve
 them when a file is rendered dataless.  I.e extended attributes are considered
 metadata, not content.  The resource fork however is considered content and
 will not be included in this dictionary.  Local changes to the resource fork
 will be communicated under NSFileProviderItemContents.  Remote changes to
 the resource fork should bump itemVersion.contentVersion.
 */
@property (nonatomic, readonly, strong) NSDictionary <NSString *, NSData *> *extendedAttributes FILEPROVIDER_API_AVAILABILITY_V3;


/*
 The three properties below (lastUsedDate, tagData and favoriteRank) are
 indications that the item is part of the working set.
 */

/**
 The date this item was last used.  This is neither the modification date nor
 the last access date exposed in traditional file system APIs, and indicates a
 very clear user intent to use the document.  For example, this is set when the
 document is open full screen on a device.

 This is the system's cue that the document is recent and should appear in the
 recent list of the UIDocumentBrowserViewController.

 This property must not be shared between users, even if the item is.
 */
@property (nonatomic, readonly, copy, nullable) NSDate *lastUsedDate;

/**
 An abstract data blob representing the tags associated with the item.  The same
 tags that are available via -[NSURL getResourceValue:forKey:error:] with key
 NSURLTagNamesKey on macOS, except that this data blob may transport more
 information than just the tag names.

 This property must not be shared between users, even if the item is.

 Starting in macOS 12 and iOS 15, the system suppports the value of the
 `com.apple.metadata:_kMDItemUserTags` xattr as a valid `tagData` blob input.
 */
@property (nonatomic, readonly, copy, nullable) NSData *tagData;

/**
 The presence of a favorite rank indicates that a directory is a favorite.
 Favorite ranks are 64-bit unsigned integers.  The initial value for the first
 item is the time since the unix epoch in milliseconds, but subsequent items are
 simply placed relative to that.  Favorite ranks are modified when the user
 reorders favorites.

 When favoriting folders on other platforms, set the rank to the time since the
 unix epoch in milliseconds.  Special value @(NSFileProviderFavoriteRankUnranked)
 may be used if no rank is available: the system will then figure out the best
 rank and set it.  Please persist and sync the new value.

 This property must not be shared between users, even if the item is.
 */
@property (nonatomic, readonly, copy, nullable) NSNumber *favoriteRank FILEPROVIDER_API_AVAILABILITY_V2;

/**
 Set on a directory or a document if it should appear in the trash.

 This flag should only be set on the top-level item: trashing a directory sets
 this flag on the directory itself, but not on its children.

 Trashed items should remain in the working set; however, children of trashed
 directories should be removed from the working set.

 Additionally, when an item is trashed, the `parentItemIdentifier` refers to the location the item was before being
 trashed. As such, when the user decides to restore the item from trash, `parentItemIdentifier` will be used for
 the default restore location.
 */
@property (nonatomic, readonly, getter=isTrashed) BOOL trashed FILEPROVIDER_API_AVAILABILITY_V2;

/**
 Uploaded and uploading are used to inform the cloud badge which will be shown on the item.

 When using NSFileProviderReplicatedExtension, uploaded is used to inform whether the item may be
 evicted from the local disk. If you choose to finish uploading items after calling the completion handler
 of creteItem/modifyItem, you must set the uploaded flag to false, in order for the item to be excluded from
 eviction.
 */
@property (nonatomic, readonly, getter=isUploaded) BOOL uploaded;
@property (nonatomic, readonly, getter=isUploading) BOOL uploading;

/**
 An error that occurred while uploading to your remote server.

 \note Typical uploading errors include:
 - NSFileProviderErrorInsufficientQuota
 - NSFileProviderErrorServerUnreachable

 \seealso NSFileProviderErrorInsufficientQuota
 \seealso NSFileProviderErrorServerUnreachable
 */
@property (nonatomic, readonly, copy, nullable) NSError *uploadingError;

/**
 When using NSFileProviderExtension, downloaded and downloading are used to inform the cloud badge
 which will be shown on the item.

 When using NSFileProviderReplicatedExtension, downloaded and downloading are ignored, as they can be
 inferred from the result of calls to fetchContentsForItemWithIdentifier.
 */
@property (nonatomic, readonly, getter=isDownloaded) BOOL downloaded;
@property (nonatomic, readonly, getter=isDownloading) BOOL downloading;

/**
 An error that occurred while downloading from your remote server.
 */
@property (nonatomic, readonly, copy, nullable) NSError *downloadingError;

@property (nonatomic, readonly, getter=isMostRecentVersionDownloaded) BOOL mostRecentVersionDownloaded;

@property (nonatomic, readonly, getter=isShared) BOOL shared;
@property (nonatomic, readonly, getter=isSharedByCurrentUser) BOOL sharedByCurrentUser;

/**
 ownerNameComponents should be nil when sharedByCurrentUser is equal to YES or
 when the item is not shared.
 */
@property (nonatomic, strong, readonly, nullable) NSPersonNameComponents *ownerNameComponents;
@property (nonatomic, strong, readonly, nullable) NSPersonNameComponents *mostRecentEditorNameComponents;

/**
 The versionIdentifier is used to invalidate the thumbnail in the thumbnail cache.
 A content hash would be a reasonable choice.

 Version identifiers are limited to 1000 bytes.

 This property is deprecated in favor of the "itemVersion" property.
 */
@property (nonatomic, strong, readonly, nullable) NSData *versionIdentifier API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos) API_UNAVAILABLE(macos);

/**
 The version is used to track which version of an item has been modified when informing a provider about changes. It is also used to invalidate the thumbnail cache.
 */
@property (nonatomic, strong, readonly) NSFileProviderItemVersion *itemVersion FILEPROVIDER_API_AVAILABILITY_V3;

/**
 The target of a symlink.

 If a replicated extension expose an item with the contentType public.symlink (UTTypeSymbolicLink),
 this field should contain the target of the symlink.
 */
@property (nonatomic, readonly, copy, nullable) NSString *symlinkTargetPath
    FILEPROVIDER_API_AVAILABILITY_V3;

/**
 Use this dictionary to add state information to the item. Entries are accessible to
 FileProviderUI and non-UI action predicates and user interaction predicates [1] via the
 `userInfo` context key.

 Additionally, any entry of this dictionary with a key ending in `.inherited`
 will be accessible to predicates for descendants of this item via the context key `inheritedUserInfo`.

 Items can redefine inherited values for their descendants by specifying the same key used in an ancestor's `userInfo`.
 Thus, `inheritedUserInfo` for a given item is a dictionary of `*.inherited` keys from all if its ancestors, with each value
 taken from the nearest ancestor that has the entry defined.

 In this example directory structure:
 root
 |_ parent
   |_ child
     |_ grandchild

 with the following userInfo values set:
 parent.userInfo = { "a.inherited": YES, "b.inherited": YES }
 child.userInfo = { "a.inherited": NO, "c.inherited": NO }
 grandchild.userInfo = { }

 the following inheritedUserInfo values will be provided:
 parent.inheritedUserInfo = { }
 child.inheritedUserInfo = { "a.inherited": YES, "b.inherited": YES }
 grandchild.inheritedUserInfo = { "a.inherited": NO, "b.inherited": YES, "c.inherited": NO }

 The context key `resolvedUserInfo` is also available. For each item, the resolvedUserInfo is it's
 inheritedUserInfo, combined with the keys suffixed with .inherited from it's userInfo.
 Continuing the previous example:
 parent.resolvedUserInfo = { "a.inherited": YES, "b.inherited": YES }
 child.resolvedUserInfo = { "a.inherited": NO, "b.inherited": YES, "c.inherited": NO }
 grandchild.resolvedUserInfo = { "a.inherited": NO, "b.inherited": YES, "c.inherited": NO }

 All values for this dictionary must be of type String, Number, Bool or Date.

 [1] UserInteraction can be defined when a user level action occurs with a file.

  - `NSFileProviderUserInteractions` *array*
    - `ActivationRule ` *string*, the predicate.
        @parameters predicates
            - `destinationItem`: the destination item for an action. Present for Move/MoveIn/Copy/CopyIn/Create
            - `action` : the action that is being performed
                 'Move'       : moving item(s) within the same provider
                 'MoveOut'    : moving item(s) out of the provider
                 'MoveIn'     : importing item(s) into a folder/root of the provider
                 'Copy'       : copying item(s) within the same provider
                 'CopyOut'    : copying item(s) out of the provider
                 'CopyIn'     : copying item(s) into a folder/root of the provider
                 'Trash'      : trashing item(s)
                 'Create'      : creating an item (available in macOS 12.0 and later)
                            The Create action will be evaluated when the user creates a new file
                            or folder in a system Open/Save panel.
                            The sourceItem is the file/folder being created. The only field that is
                            populated for this item is the filename. The type of file/folder, size, etc,
                            are unknown at Create evaluation time.
                            The destinationItem is the directory which the file/folder is being created
                            within.
                 'Delete'     : deleting item(s)
                             If the provider wishes to take full responsibility for showing warnings on Delete,
                             the provider can set NSExtensionFileProviderAllowsSystemDeleteAlerts=0 in the provider's Info.plist.
                             This will ensure that the system does not display it's warnings when the user is deleting a file.
                 'ExcludeFromSync' : deleting items(s) because the user chose to exclude those from sync (available in macOS 12.0 and later)
                 'Rename'  : renaming item(s) (available in macOS 11.3 and later)
                             The destinationItem has only the `filename` field populated (available in macOS 12.0.1 and later).
            - `sourceItem` : current item that the predicate is evaluating. Present for Move/MoveOut/Copy/CopyOut/Create/Trash/Delete/ExcludeFromSync/Rename
            - `sourceItemsCount` :
                - In userInteraction, represents the count of sourceItems of an action operation
                - In subUserInteraction: represents the count of items that matched the previous predicate
            - `domainUserInfo`: The latest dictionary returned from -[NSFileProviderDomainState userInfo]
    - `Alert` *dictionary*
        - `LocalizedTitle` *string*, title of the alert
        - `LocalizedSubTitle` *string*, sub title of the alert
            - @parameters for LocalizedTitle/LocalizedSubTitle
                - `matchingItemsCount`: count of source items that matched the predicate (only present if matchingItemsCount > 0)
                - `matchingItemsCountMinusOne`: matchingItemsCount minus one (only present if matchingItemsCount > 1)
                - `matchingItemsCountMinusTwo`: matchingItemsCount minus two (only present if matchingItemsCount > 2)
                - `firstMatchingItem`: first sourceItem that matched the predicate (only present if matchingItemsCount > 1)
                - `secondMatchingItem`: second sourceItem that matched the predicate (only present if matchingItemsCount > 2)
        - `LocalizedRecoveryOptions`
            - `Continue` *string*, the string for the continue button - default value if not specified
            - `Cancel` *string*, the string for the cancel button - default value if not specified
        - `RecoveryOptions` (optional)
            - `Continue` *bool*, the boolean for whether to have a continue button - default value is YES if not specified
            - `Destructive` *bool*, the boolean for whether continuing is a destructive action - default value is NO if not specified
    - `HelpURL` *string*: If present, a help button will be displayed on the Alert that is shown. If the user
                   clicks the help button, this help URL will be opened. This URL is not restricted to Web URLs. For instance, the extension could configure
                   the HelpURL to launch it's application with a custom URL scheme. (available in macOS 12.0 and later)
    - `SubInteractions `: *dictionary* (same as `NSFileProviderUserInteractions`)
    - `SupressionIdentifier` *string*: If present, when this predicate matches, the alert will display an option to
                           suppress future alerts from UserInteractions with the same
                           SuppressionIdentifier (including the current UserInteraction). This also
                           requires implementing the `NSFileProviderUserInteractionSuppressing`
                           protocol on the principal class of the FileProvider extension (available in
                           macOS 12.0 and later).

 For each interaction, either Alert or SubInteractions must be specified. SubInteractions will be evaluated if the main ActivationRule evaluates to
 YES for at least once. This allows you to match a general pattern via the top-level activation rule and then select a specialized error message from a list
 of subpatterns.

 At most one UserInteraction alert will be shown for each FileProvider domain involved in the user's Action. For
 instance, if provider A defines a UserInteraction for MoveOut actions, and provider B defines a UserInteraction
 for MoveIn operations. When the user moves a file from A to B, and the predicate for both UserInteraction
 matches, then both of the UserInteraction alerts will be shown to the user. However, as soon as the user
 denies any of the alerts, the remainder will not be shown, and the action will be denied.

 If the provider wishes to take full responsibility for showing a custom contextual menu item for Download,
 the provider can set NSExtensionFileProviderAllowsContextualMenuDownloadEntry=0 in the provider's Info.plist.
 This will ensure that the system does not display the "Download Now" button in the contextual menu.

 Here is a sample extension Info.plist:

 ```
 <key>NSExtension</key>
 <key>NSExtensionFileProviderAllowsContextualMenuDownloadEntry</key>
 <false/>
 <key>NSFileProviderUserInteractions</key>
 <array>
    <key>ActivationRule</key>
    <string>action == "Move"</string>
    <key>SubInteractions</key>
    <array>
        <dict>
            <key>ActivationRule</key>
            <string>sourceItem.isShared == NO AND
                    destinationItem.isShared == YES AND
                    destinationItem.isSharedByCurrentUser == YES</string>
            <key>SubInteractions</key>
            <array>
                <dict>
                    <key>ActivationRule</key>
                    <string>sourceItemsCount == 1</string>
                    <key>Alert</key>
                    <dict>
                        <key>LocalizedTitle</key>
                        <dict>
                            <key>NSStringFormat</key>
                            <string>Are you sure you want to move %@ into %@?</string>
                            <key>NSStringFormatValues</key>
                            <array>
                                <string>firstMatchingItem.filename</string>
                                <string>destinationItem.filename</string>
                            </array>
                        </dict>
                        <key>LocalizedSubTitle</key>
                        <dict>
                            <key>NSStringFormat</key>
                            <string>If you move it, people added to the shared folder “%@” will be able to access it</string>
                            <key>NSStringFormatValues</key>
                            <array>
                                <string>destinationItem.filename</string>
                            </array>
                        </dict>
                        <key>LocalizedRecoveryOptions</key>
                        <array>
                            <key>Continue</key><string>Save to shared folder</string>
                        </array>
                    </dict>
                </dict>
            </array>
        </dict>
        <dict>
            <key>ActivationRule</key>
            <string>sourceItem.isShared == YES AND
                    sourceItem.isSharedByCurrentUser == NO AND
                    destinationItem.isSharedByCurrentUser == YES</string>
            <key>SubInteractions</key>
            <array>
                <dict>
                    <key>ActivationRule</key>
                    <string>sourceItemsCount == 1</string>
                    <key>Alert</key>
                    <dict>
                        <key>LocalizedTitle</key>
                        <dict>
                            <key>NSStringFormat</key>
                            <string>This shared item can't be moved.</string>
                        </dict>
                        <key>LocalizedSubTitle</key>
                        <dict>
                            <key>NSStringFormat</key>
                            <string>Items shared with you can’t be moved to shared folders</string>
                        </dict>
                    </dict>
                    <key>RecoveryOptions</key>
                    <dict>
                        <key>Continue</key>
                        <false/>
                    </dict>
                </dict>
            </array>
        </dict>
    </array>
 </array>
 ```
 */
@property (nonatomic, strong, readonly, nullable) NSDictionary *userInfo;


@end

FILEPROVIDER_API_AVAILABILITY_V2_V3
typedef id<NSFileProviderItem> NSFileProviderItem;

NS_ASSUME_NONNULL_END
