//
//  GSSyncedDirectory.h
//  GameSave
//
//  Copyright © 2024 Apple. All rights reserved.
//

#ifndef GameSave_GSSyncedDirectory_h
#define GameSave_GSSyncedDirectory_h

#import <Foundation/Foundation.h>
#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#elif TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_UNAVAILABLE("");
typedef NS_ENUM(NSInteger, GSSyncState) {
    /// The directory is fully synced and ready to use.
    ///
    /// In this state, the value of ``GSSyncedDirectoryState/url`` is nonnull.
    GSSyncStateReady,
    /// The directory is available locally, but not fully synced because the device is offline.
    ///
    /// In this state, the value of ``GSSyncedDirectoryState/url`` is nonnull.
    GSSyncStateOffline,
    /// The directory is local-only and not synced to iCloud.
    ///
    /// In this state, the value of ``GSSyncedDirectoryState/url`` is nonnull.
    GSSyncStateLocal,
    /// The directory is currently syncing and is not ready yet.
    GSSyncStateSyncing,
    /// The directory has conflicts with the cloud, which the game needs to resolve.
    ///
    /// In this state, the value of ``GSSyncedDirectoryState/conflictedVersions`` is nonnull.
    GSSyncStateConflicted,
    /// The directory is in error state and can't be used.
    ///
    /// In this state, the value of ``GSSyncedDirectoryState/error`` is nonnull.
    GSSyncStateError,
    /// The directory is closed.
    GSSyncStateClosed
};

API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(watchos, tvos)
NS_SWIFT_UNAVAILABLE("Use GameSaveSyncedDirectory.Version instead");
/// A representation of a version of the directory.
///
/// Used to describe the conflicted or local versions of a directory in case there are conflicts.
API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(watchos, tvos)
NS_SWIFT_UNAVAILABLE("Use GameSaveSyncedDirectory.Version instead");
@interface GSSyncedDirectoryVersion: NSObject
/// `YES` if the directory version is local; otherwise `NO`.
@property (readonly) BOOL isLocal;
/// The localized name of the device that saved this version.
@property (readonly, nonnull) NSString* localizedNameOfSavingComputer;
/// The date that this version was last modified.
@property (readonly, nonnull) NSDate* modifiedDate;
/// The URL of a directory where you read and write game-save data.
///
/// You define the format and structure of files you write in this directory.
@property (readonly, nonnull) NSURL* url;
@property (readonly, nonnull) NSString* description;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)new NS_UNAVAILABLE;
@end

API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(watchos, tvos)
NS_SWIFT_UNAVAILABLE("Use GameSaveSyncedDirectory.State instead");
/// Represents the state and its associated properties of the directory
///
/// Use the ``state`` property to determine the validity of the other properties
@interface GSSyncedDirectoryState: NSObject
/// Specifies the current state of the directory
@property (readonly) GSSyncState state;
/// The URL of a directory to read and write game-save data in.
///
/// This property's value is `nil` unless the state is `GSSyncStateReady`, `GSSyncStateOffline`, or `GSSyncStateLocal`.
@property (readonly, nullable) NSURL *url;
/// The conflicting versions.
///
/// If you're implementing your own conflict resolution,
/// read all of the conflicting versions,
/// and modify one of them to incorporate the state and changes from the others.
/// Then call ``GSSyncedDirectory/resolveConflictsWithVersion:``, passing that version.
///
/// This property's value is `nil` unless the state is `GSSyncStateConflicted`.
@property (readonly, nullable) NSArray<GSSyncedDirectoryVersion *> *conflictedVersions;
/// The error preventing you from using the directory.
///
/// This property's value is `nil` unless the state is `GSSyncStateError`.
@property (readonly, nullable) NSError *error;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)new NS_UNAVAILABLE;
@end

API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(watchos, tvos)
NS_SWIFT_UNAVAILABLE("Use GameSaveSyncedDirectory instead");
/// A cloud-synced directory for game-save data.
///
/// To get an instance of the directory,
/// call ``openDirectoryForContainerIdentifier:``,
/// which returns the directory for the iCloud container associated with the specified identifier.
/// Calling this method starts syncing the directory in the background on the specified container.
/// When the game needs to access the contents of the directory,
/// show a UI while the directory fully syncs using
/// the ``finishSyncing:completionHandler:`` method.
/// If you're showing your own UI,
/// call the ``finishSyncingWithCompletionHandler:`` method to wait for the directory to finish syncing.
///
/// After the directory is ready to use,
/// syncing pauses until you close the directory object or the object is deallocated.
/// To resume syncing during the game,
/// close and re-open the directory by calling ``close`` and then ``openDirectoryForContainerIdentifier:``.
@interface GSSyncedDirectory: NSObject
/// Requests an instance of the game-save directory.
///
/// - Parameter containerIdentifier: The identifier of the directory to request.
///   If you pass `nil`, this method uses the first container identifier
///   listed in the `com.apple.developer.icloud-container-identifiers` entitlements array.
///
/// This method returns immediately, and starts syncing the directory in the background.
/// To wait for syncing to complete, call the ``finishSyncingWithCompletionHandler:`` method.
+ (nonnull GSSyncedDirectory*) openDirectoryForContainerIdentifier:(NSString* _Nullable)containerIdentifier;
/// Closes the directory, and resumes syncing the directory to the cloud.
- (void) close;
/// Triggers an upload of the directory for any changes that were pending.
///
/// Calls the completion block with `YES` if there were pending uploads; otherwise with `NO`.
- (void) triggerPendingUploadWithCompletionHandler:(void(^_Nonnull)(BOOL))completion;
/// Indicates that you resolved a conflict.
///
/// - Parameter version: The version to use.
///
/// If you're implementing your own conflict resolution,
/// read all of the conflicting versions,
/// and modify one of them to incorporate the state and changes from the others.
/// Then call this method, passing that version.
///
/// Call this method only when the directory is in the ``GSSyncState/GSSyncStateConflicted`` state.
- (void) resolveConflictsWithVersion:(GSSyncedDirectoryVersion* _Nonnull)version;
/// Waits for the directory sync to complete, without showing any user interface.
///
/// Use this method to wait if your app displays its own syncing UI.
- (void) finishSyncingWithCompletionHandler:(void(^_Nonnull)(void))completion;
#if TARGET_OS_OSX
/// Waits for the directory sync to complete, showing the sync's progress in a modal alert.
///
/// - Parameters:
///   - statusDisplay: The window where the system shows progress and alerts.
///   - completion: The block that GameSave calls after syncing finishes.
///
/// If the sync results in a conflict, the framework displays a conflict resolution UI
/// for the user to chose a version that will be used.
/// If the user isn't signed in to iCloud or iCloud drive,
/// the framework informs the user and then switches to local saving.
- (void) finishSyncing:(NSWindow* _Nonnull)statusDisplay completionHandler:(void(^_Nonnull)(void))completion;
#elif TARGET_OS_IPHONE
/// Waits for the directory sync to complete, showing the sync's progress in a modal alert.
///
/// - Parameters:
///   - statusDisplay: The window where the system shows progress and alerts.
///   - completion: The block that GameSave calls after syncing finishes.
///
/// If the sync results in a conflict, the framework displays a conflict resolution UI
/// for the user to chose a version that will be used.
/// If the user isn't signed in to iCloud or iCloud drive,
/// the framework informs the user and then switches to local saving.
- (void) finishSyncing:(UIWindow* _Nonnull)statusDisplay completionHandler:(void(^_Nonnull)(void))completion;
#endif

/// The state of the directory.
@property (readonly, nonnull) GSSyncedDirectoryState *directoryState;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)new NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END


#endif /* GameSave_GSSyncedDirectory_h */
