//
//  NSFileProviderActions.h
//  FileProvider
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderExtension.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FILEPROVIDER_API_AVAILABILITY_V2_V3
typedef NSString *NSFileProviderExtensionActionIdentifier NS_EXTENSIBLE_STRING_ENUM;

/**
 This category encapsulates common user-driven actions on FileProvider's items.
 */
FILEPROVIDER_API_AVAILABILITY_V2
@interface NSFileProviderExtension (NSFileProviderActions)

/**
 Import a document.

 The file or package at fileURL should be moved on disk into the file provider's
 own storage, where it will later be uploaded.  The completion block should be
 executed after the move on disk, but before the upload.  Before doing any
 network, actually.

 In the completion block, importedDocumentItem should have these properties set:
   - itemIdentifier
   - parentItemIdentifier (to the value passed in to this method)
   - filename (to fileURL's resource value for key NSURLNameKey)
   - creationDate (to NSURLCreationDateKey)
   - contentModificationDate (to NSURLContentModificationDateKey)
   - contentType (to NSURLContentTypeKey)
   - documentSize (to NSURLTotalFileSizeKey on a flat file, or to the sum of the
     files sizes for a package)
   - capabilities

 [fileURL startAccessingSecurityScopedResource] needs to be called prior to
 accessing this security scoped URL, and stopAccessingSecurityScopedResource
 needs to be called when done.

 Note that itemIdentifier should be set with no network call.  It doesn't have
 to be the final identifier.  If the identifier changes after talking to the
 server then the file provider should send a delete for the temporary, local
 identifier immediately followed by an add with the final identifier.

 A reasonable way of organizing files in the file provider storage is:
     <file provider storage path>/<itemIdentifier>/<filename>.<extension>
 If the item identifier was to change, you should move the file on disk to
 update its path, under coordination with NSFileCoordinatorWritingForMoving.

 This is expected to work offline even if there might be a collision (another
 item with the same filename and parentItemIdentifier) only detected when later
 syncing up this change to the server.  In that case, it is suggested that a
 follow up update to the item change its filename to something unique.  This
 wouldn't be considered an error to import.

 If however you can tell right away, with no communication to your server, that
 there is a collision then this call should fail with error code
 NSFileProviderErrorFilenameCollision generated with this method:
   -[NSError (NSFileProviderError) fileProviderErrorForCollisionWithItem:].

 The existing item set in this error will be used to handle the collision, and
 ask the user if she or he would like to replace the existing item.  This takes
 into account the existing item's capabilities (particularly
 NSFileProviderItemCapabilitiesAllowsTrashing and AllowsDeleting.)

 Collision checks should be case insensitive even if the filesystem or file
 provider might allow two coexisting filenames differing only by their case.

 Upload errors (such as NSFileProviderErrorInsufficientQuota) should be handled
 with a subsequent update to the item, setting its uploadingError property.
 Upload errors should not prevent creating or importing a document, because they
 can be resolved at a later date (for example, when the user has quota again.)

 Other errors will be presented to the user, but are unexpected.  If you want to
 prevent imports in a given directory, then the directory item's capacities
 should exclude NSFileProviderItemCapabilitiesAllowsAddingSubItems.
 */
- (void)importDocumentAtURL:(NSURL *)fileURL
     toParentItemIdentifier:(NSFileProviderItemIdentifier)parentItemIdentifier
          completionHandler:(void (^)(NSFileProviderItem _Nullable importedDocumentItem, NSError * _Nullable error))completionHandler;

/**
 Create a directory.

 This is expected to complete before doing any network.

 In the completion block, createdDirectoryItem should have these properties set:
 - itemIdentifier
 - parentItemIdentifier (to the value passed in to this method)
 - filename (to directoryName)
 - creationDate (to the current date and time)
 - contentType (to "public.folder" - UTTypeFolder)
 - childItemCount (to 0)
 - capabilities

 Errors (including collision errors) are handled as documented for the import
 method above.  Directory creation is gated by the capabilities of the
 destination directory, with NSFileProviderItemCapabilitiesAllowsAddingSubItems.
 */
- (void)createDirectoryWithName:(NSString *)directoryName
         inParentItemIdentifier:(NSFileProviderItemIdentifier)parentItemIdentifier
              completionHandler:(void (^)(NSFileProviderItem _Nullable createdDirectoryItem, NSError * _Nullable error))completionHandler;


/**
 Rename a document or a directory.

 This is expected to complete before doing any network.

 itemName is the full file or directory name, complete with its file extension.
 In the completion block, property renamedItem.filename should change to
 itemName.  Property renamedItem.displayName should also be updated if you
 chose to overwrite that method.

 Errors (including collision errors) are handled as documented for the import
 method above.  Renames are gated by the capabilities of the renamed item, with
 NSFileProviderItemCapabilitiesAllowsRenaming.
 */
- (void)renameItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                          toName:(NSString *)itemName
               completionHandler:(void (^)(NSFileProviderItem _Nullable renamedItem, NSError * _Nullable error))completionHandler;

/**
 Move an item to a new directory.

 This is expected to complete before doing any network.

 If newName is non null, the moved item should be renamed to newName.

 Errors (including collision errors) are handled as documented for the import
 method above.  Moves are gated by the capabilities of both the moved item with
 NSFileProviderItemCapabilitiesAllowsReparenting, and the destination directory
 with NSFileProviderItemCapabilitiesAllowsAddingSubItems.
 */
- (void)reparentItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
        toParentItemWithIdentifier:(NSFileProviderItemIdentifier)parentItemIdentifier
                           newName:(nullable NSString *)newName
                 completionHandler:(void (^)(NSFileProviderItem _Nullable reparentedItem, NSError * _Nullable error))completionHandler;

/**
 Move an item to the trash.

 In the completion block, property trashedItem.isTrashed should be set to YES.
 You should keep track of the original parentItemIdentifier of the item before
 it was moved to trash, so you can move the item back where it used to be in the
 untrash method.  You could use the trashedItem.parentItemIdentifier property
 for that.

 The trashed item should continue to belong to the working set of documents
 cached on the device and visible offline to the user.  But if it is a
 directory, then all of its children should be removed from the working set and
 the file provider extension should send deletion events to make sure that they
 no longer appear in the recent lists.

 It is also suggested that shared documents be unshared when trashed.

 Trash is gated by the capabilities of the trashed item with
 NSFileProviderItemCapabilitiesAllowsTrashing.
 */
- (void)trashItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
              completionHandler:(void (^)(NSFileProviderItem _Nullable trashedItem, NSError * _Nullable error))completionHandler;

/**
 Move an item out of the trash.

 If parentItemIdentifier is nil, the file provider should attempt to put the
 item back where it was when it was moved to the trash; otherwise it should move
 it to this new parent.

 If the item is a directory, then the file provider extension should enumerate
 the children and send addition events in the working set so that the documents
 in the now untrashed directory may be reindexed.

 Untrash is gated by the capabilities of the destination directory, with
 NSFileProviderItemCapabilitiesAllowsAddingSubItems.
 */
- (void)untrashItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
           toParentItemIdentifier:(nullable NSFileProviderItemIdentifier)parentItemIdentifier
                completionHandler:(void (^)(NSFileProviderItem _Nullable untrashedItem, NSError * _Nullable error))completionHandler;

/**
 Delete an item forever.

 This is called when the user deletes an item that was already in the Trash and
 the item should no longer appear there after this call.  This call should
 remove the item from the working set.

 Delete is gated by the capabilities of the removed item with
 NSFileProviderItemCapabilitiesAllowsDeleting.
 */
- (void)deleteItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
               completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/**
 Mark an item as recently used, or clear its lastUsedDate if nil.

 This last used date is the sort key for the recent lists.  It is the primary
 hint that an item must belong to the working set cached and indexed on the
 user's device.

 The file provider is asked to persist the new last used date on disk, then call
 the completion callback with the updated last used date.  At a later point, the
 file provider should sync the new last used date to their server.

 The error parameter is here for debugging purposes alone; it won't be presented
 to the user or otherwise handled, but it will be logged.
 */
- (void)setLastUsedDate:(nullable NSDate *)lastUsedDate
      forItemIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
      completionHandler:(void (^)(NSFileProviderItem _Nullable recentlyUsedItem, NSError * _Nullable error))completionHandler;

/**
 Tag an item, or untag it if tagData is nil.

 The file provider is asked to persist the new tag data on disk, then call the
 completion callback with the updated tagged data.  At a later point, the file
 provider should sync the new tag data to their server.

 Tagged items are relevant to the user and should be in the working set even if
 they haven't been used recently.

 If set, the error will be immediately presented to the user and the item just
 won't be tagged.

 On shared items, tags should sync across the devices of any one participant but
 shouldn't sync across users.
 */
- (void)setTagData:(nullable NSData *)tagData
 forItemIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
 completionHandler:(void (^)(NSFileProviderItem _Nullable taggedItem, NSError * _Nullable error))completionHandler;

/**
 Mark a directory as favorite (or no longer favorite if favoriteRank is nil.)

 The favorite rank is used to represent the relative order of two favorite
 directories in the UI.  It is a 64 bit unsigned integer.  It needs to be synced.

 Favorite directories are relevant to the user and should be in the working set
 even if they haven't been used recently.  The documents and directories in the
 favorite directory however don't all have to be in the working set, and don't
 all have to be made accessible offline.

 The file provider is asked to persist the new favorite rank on disk, then call
 the completion callback with the updated favorite rank.  At a later point, the
 file provider should sync the new favorite rank to their server.
 */
- (void)setFavoriteRank:(nullable NSNumber *)favoriteRank
      forItemIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
      completionHandler:(void (^)(NSFileProviderItem _Nullable favoriteItem, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
