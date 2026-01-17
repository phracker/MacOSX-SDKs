//
//  NSFileProviderKnownFolders.h
//  FileProvider
//
//  Copyright © 2018-2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderDomain.h>
#import <FileProvider/NSFileProviderManager.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Defining Location

/** Specify the location of a known folder in the replicated tree.
 */
FILEPROVIDER_API_AVAILABILITY_DESKTOP
NS_SWIFT_NAME(NSFileProviderKnownFolderLocations.Location)
@interface NSFileProviderKnownFolderLocation : NSObject

/** Initialize a location with the filename of the folder in a specified parent.

 When replicating a known folder the system will reuse a folder located at the specified
 filename within the parent if one exists, or create a new item at this location if none
 exists yet.
 */
- (instancetype)initWithParentItemIdentifier:(NSFileProviderItemIdentifier)parentItemIdentifier
                                    filename:(NSString *)filename;

/** Initialize a location with the item identifier of a folder that already exists on the server.

 If the known folder already exists on the server, the provider can specify the exact identifier
 of the item that needs to be used to back the known folder.
 */
- (instancetype)initWithExistingItemIdentifier:(NSFileProviderItemIdentifier)existingItemIdentifier;

@end

/** Specify the locations at which known folders should be synced in the replicated tree.

 Desktop and Documents candidate items need to have the same parent folder.
 */
FILEPROVIDER_API_AVAILABILITY_DESKTOP
@interface NSFileProviderKnownFolderLocations : NSObject

/** Specify whether the system should create a binary compatibility symlink folders.

 If YES, the system creates a symlink from the logical location of the folder in the domain
 sync root to the known folder location. This symlink allows any app that would have hardcoded
 the previous location of the folder to still work after enabling the feature.

 Default value is YES.
 */
@property (readwrite, assign, nonatomic) BOOL shouldCreateBinaryCompatibilitySymlink;

/** Candidate item for ~/Desktop

    For user experience reasons, it is strongly recommended to name the target folder "Desktop".
 */
@property (readwrite, strong, nullable, nonatomic) NSFileProviderKnownFolderLocation *desktopLocation;

/** Candidate item for ~/Documents

 For user experience reasons, it is strongly recommended to name the target folder "Documents".
 */
@property (readwrite, strong, nullable, nonatomic) NSFileProviderKnownFolderLocation *documentsLocation;

- (instancetype)init;
@end

#pragma mark - Claiming replication of known folders

@interface NSFileProviderManager (KnownFolders)

/** Request the specified known folders to be synced by this domain.

 This method allows the provider to claim a set of known folders described by the non-null
 properties of the knownFolders parameter. The system will only enable sync for those folders
 in that domain if the set of locations is valid and if the user agrees.

 This API should only be called as a result of the user requesting, via UI in the provider's application,
 that they wish to start syncing the Desktop and Document folders.
 If the provider chooses to implement a UI which invokes this API, the provider should also implement a UI
 for the user to request to stop syncing the Desktop and Document folders,
 using the `-[NSFileProviderManager releaseKnownFolders:localizedReason:completionHandler:]` method.

 The reason specified in this call is a custom string that the provider can pass and will be
 presented to the user as a way to explain why it is claiming those known folders. One suggested
 phrasing would be:

 > Keep your Desktop & Documents in sync with <Provider name> and access them from other devices and from <Provider website>.

 If the user denies the transition of the known folders, the call will fail with `NSUserCancelledError`.

 The call will fail if:
 - one or more locations are not folders
 - multiple locations are backed by the same folder
 - a known folder doesn't live on the same volume as the root of the domain
 - the known folders don't have the same parent folder
 - ...

 Currently, only claiming both ~/Desktop and ~/Documents together is allowed.
 */
- (void)claimKnownFolders:(NSFileProviderKnownFolderLocations *)knownFolders
          localizedReason:(NSString *)localizedReason
        completionHandler:(void (^)(NSError * _Nullable))completionHandler
                            NS_SWIFT_NAME(claimKnownFolders(_:localizedReason:completionHandler:))
                            FILEPROVIDER_API_AVAILABILITY_DESKTOP;

/** Request that the system stops replicating the specified known folders in the domain.

 This call can be used by the provider to immediately disable replication of the specified
 known folders.
 */
- (void)releaseKnownFolders:(NSFileProviderKnownFolders)knownFolders
            localizedReason:(NSString *)localizedReason
          completionHandler:(void (^)(NSError * _Nullable))completionHandler
                            NS_SWIFT_NAME(releaseKnownFolders(_:localizedReason:completionHandler:))
                            FILEPROVIDER_API_AVAILABILITY_DESKTOP;
@end

#pragma mark - Responding to the system

FILEPROVIDER_API_AVAILABILITY_DESKTOP
@protocol NSFileProviderKnownFolderSupporting <NSObject>

/** Request suitable locations for known folders.

 This function is called when the user decides to switch some known folders to the current domain, outside of the `claimKnownFolders` call.
 The system provides a list of folders that the user decides to move to this domain, and expect in return non-nil locations for those known
 folders.
 */
- (void)getKnownFolderLocations:(NSFileProviderKnownFolders)knownFolders
              completionHandler:(void (^)(NSFileProviderKnownFolderLocations * _Nullable, NSError * _Nullable))completionHandler;

@end

NS_ASSUME_NONNULL_END
