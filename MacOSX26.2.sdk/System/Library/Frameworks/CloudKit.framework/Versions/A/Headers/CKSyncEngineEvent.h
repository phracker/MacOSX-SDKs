//
//  CKSyncEngineEvent.h
//  CloudKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKRecord.h>

@class CKRecordZone, CKRecordZoneID;
@class CKSyncEngineAccountChangeEvent, CKSyncEngineDidFetchChangesEvent, CKSyncEngineDidFetchRecordZoneChangesEvent, CKSyncEngineDidSendChangesEvent, CKSyncEngineFetchedDatabaseChangesEvent, CKSyncEngineFetchedRecordDeletion, CKSyncEngineFetchedRecordZoneChangesEvent, CKSyncEngineSentDatabaseChangesEvent, CKSyncEngineSentRecordZoneChangesEvent, CKSyncEngineStateUpdateEvent, CKSyncEngineWillFetchChangesEvent, CKSyncEngineWillFetchRecordZoneChangesEvent, CKSyncEngineWillSendChangesEvent;
@class CKSyncEngineFailedRecordSave, CKSyncEngineFailedZoneSave, CKSyncEngineFetchChangesContext, CKSyncEngineFetchedZoneDeletion, CKSyncEngineSendChangesContext, CKSyncEngineStateSerialization;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An event that occurs during the operation of a `CKSyncEngine`.
/// See ``CKSyncEngineEvent`` for more details.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, CKSyncEngineEventType) {

    //
    // Local State Changes
    //
    
    /// The sync engine state was updated. You should persist it locally.
    CKSyncEngineEventTypeStateUpdate,
    
    /// The user signed in or out of their account.
    CKSyncEngineEventTypeAccountChange,
    
    //
    // Fetched Changes
    //
    
    /// The sync engine fetched new database changes from the server.
    CKSyncEngineEventTypeFetchedDatabaseChanges,
    
    /// The sync engine fetched new record zone changes from the server.
    CKSyncEngineEventTypeFetchedRecordZoneChanges,
    
    //
    // Sent Changes
    //
    
    /// The sync engine sent a batch of database changes to the server.
    CKSyncEngineEventTypeSentDatabaseChanges,
    
    /// The sync engine sent a batch of record zone changes to the server.
    CKSyncEngineEventTypeSentRecordZoneChanges,
    
    //
    // Fetch Changes Lifecycle
    //
    
    /// The sync engine is about to fetch changes from the server.
    CKSyncEngineEventTypeWillFetchChanges,
    
    /// The sync engine is about to fetch record zone changes from the server for a specific zone.
    CKSyncEngineEventTypeWillFetchRecordZoneChanges,
    
    /// The sync engine finished fetching record zone changes from the server for a specific zone.
    CKSyncEngineEventTypeDidFetchRecordZoneChanges,
    
    /// The sync engine finished fetching changes from the server.
    CKSyncEngineEventTypeDidFetchChanges,
    
    //
    // Send Changes Lifecycle
    //
    
    /// The sync engine is about to send changes to the server.
    CKSyncEngineEventTypeWillSendChanges,
    
    /// The sync engine finished sending changes to the server.
    CKSyncEngineEventTypeDidSendChanges,
};

/// An event that occurs during the operation of a `CKSyncEngine`.
///
/// While syncing, `CKSyncEngine` posts several different types of events.
/// Each event has an associated struct value with details describing the nature of the event.
///
/// At a high level, the sync engine events can be grouped into a few different categories:
///
/// ## Local state changes
///
/// - ``CKSyncEngineStateUpdateEvent``
/// - ``CKSyncEngineAccountChangeEvent``
///
/// ## Fetched changes
///
/// - ``CKSyncEngineFetchedDatabaseChangesEvent``
/// - ``CKSyncEngineFetchedRecordZoneChangesEvent``
///
/// ## Sent changes
///
/// - ``CKSyncEngineSentDatabaseChangesEvent``
/// - ``CKSyncEngineSentRecordZoneChangesEvent``
///
/// ## Fetch changes lifecycle
///
/// - ``CKSyncEngineWillFetchChangesEvent``
/// - ``CKSyncEngineWillFetchRecordZoneChangesEvent``
/// - ``CKSyncEngineDidFetchRecordZoneChangesEvent``
/// - ``CKSyncEngineDidFetchChangesEvent``
///
/// ## Send changes lifecycle
///
/// - ``CKSyncEngineWillSendChangesEvent``
/// - ``CKSyncEngineDidSendChangesEvent``
///
/// See the documentation for each event struct for more details about when and why an event might be posted.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
// This class should not be subclassed. If it is, Sendable may no longer apply.
NS_SWIFT_SENDABLE
@interface CKSyncEngineEvent : NSObject

@property (readonly, assign) CKSyncEngineEventType type;

// Helpers to cast an event to the proper subclass.
// These will crash if used for the wrong event type.
@property (readonly, strong, nonatomic) CKSyncEngineStateUpdateEvent *stateUpdateEvent;
@property (readonly, strong, nonatomic) CKSyncEngineAccountChangeEvent *accountChangeEvent;

@property (readonly, strong, nonatomic) CKSyncEngineWillFetchChangesEvent *willFetchChangesEvent;
@property (readonly, strong, nonatomic) CKSyncEngineFetchedDatabaseChangesEvent *fetchedDatabaseChangesEvent;
@property (readonly, strong, nonatomic) CKSyncEngineDidFetchChangesEvent *didFetchChangesEvent;

@property (readonly, strong, nonatomic) CKSyncEngineWillFetchRecordZoneChangesEvent *willFetchRecordZoneChangesEvent;
@property (readonly, strong, nonatomic) CKSyncEngineFetchedRecordZoneChangesEvent *fetchedRecordZoneChangesEvent;
@property (readonly, strong, nonatomic) CKSyncEngineDidFetchRecordZoneChangesEvent *didFetchRecordZoneChangesEvent;

@property (readonly, strong, nonatomic) CKSyncEngineWillSendChangesEvent *willSendChangesEvent;
@property (readonly, strong, nonatomic) CKSyncEngineSentDatabaseChangesEvent *sentDatabaseChangesEvent;
@property (readonly, strong, nonatomic) CKSyncEngineSentRecordZoneChangesEvent *sentRecordZoneChangesEvent;
@property (readonly, strong, nonatomic) CKSyncEngineDidSendChangesEvent *didSendChangesEvent;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// The sync engine state was updated, and you should persist it locally.
///
/// In order to function properly and efficiently, `CKSyncEngine` tracks some state internally.
/// When the sync engine state changes, it will give you the latest serialized version in a ``CKSyncEngine/Event/StateUpdate``.
/// This event will happen occasionally when the sync engine modifies the state internally during normal sync operation.
/// This event will also happen when you change the state yourself.
///
/// The sync engine does not persist this state to disk, so you need to persist it in alongside your own local data.
/// The next time your process launches, use this latest state serialization in ``CKSyncEngineConfiguration/stateSerialization`` to initialize your sync engine.
///
/// This state is directly tied to the changes you fetch and send with the sync engine.
/// You should ensure that any changes fetched prior to receiving this state are also persisted alongside this state.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineStateUpdateEvent : CKSyncEngineEvent
    
@property (readonly, copy, nonatomic) CKSyncEngineStateSerialization *stateSerialization;

@end

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, CKSyncEngineAccountChangeType) {
    
    /// The user signed in to an account.
    ///
    /// If you already have data stored locally, you have a few options:
    ///
    /// - Merge the local data with the newly-signed-in account's data.
    /// - Keep the local data separate from cloud-synced data (e.g. a separate "local account").
    /// - Delete the local data.
    /// - Prompt the user to make the decision.
    CKSyncEngineAccountChangeTypeSignIn,
    
    /// The user signed out of their account.
    ///
    /// You should delete any locally-stored data for the previous account.
    CKSyncEngineAccountChangeTypeSignOut,
    
    /// The user switched from one account to another.
    /// This might happen if the user signs out and in to a new account while your application is quit.
    ///
    /// You should delete any locally-stored data for the previous account.
    CKSyncEngineAccountChangeTypeSwitchAccounts,
};

/// The user signed in or out of their account.
///
/// The sync engine automatically listens for account changes, and it will send this event when the user signs in or out.
/// It's your responsibility to react appropriately to this change and update your local persistence.
///
/// When the logged-in account changes, the sync engine will reset its internal state under the hood.
/// This means that it will clear any pending database or record zone changes that you may have added.
///
/// Note that it's possible the account changes multiple times while your app is quit.
/// If this happens, you will only receive one account change event representing the transition between the last known state and the current state.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineAccountChangeEvent : CKSyncEngineEvent

/// The type of account change that occurred.
@property (readonly, assign, nonatomic) CKSyncEngineAccountChangeType changeType;

/// The user record ID for the previous user.
///
/// If the user just signed in, this will be `nil`.
/// If the user signed out or switched accounts, this will be the old account.
@property (nullable, readonly, copy, nonatomic) CKRecordID *previousUser;

/// The user record ID for the current user.
///
/// If the user just signed in or switched accounts, this will be the new user record ID.
/// If the user signed out, this will be `nil`.
@property (nullable, readonly, copy, nonatomic) CKRecordID *currentUser;

@end

/// A batch of database changes was fetched from the server.
///
/// If there are a lot of new changes on the server, then you might receive many of these events in a row.
///
/// The ordering of fetched changes is not guaranteed, but changes will typically be fetched from oldest to newest.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFetchedDatabaseChangesEvent : CKSyncEngineEvent

@property (readonly, copy, nonatomic) NSArray<CKRecordZone *> *modifications;
@property (readonly, copy, nonatomic) NSArray<CKSyncEngineFetchedZoneDeletion *> *deletions;

@end

/// A batch of record zone changes was fetched from the server.
///
/// If there are a lot of new changes on the server, then you might receive many of these events in a row.
///
/// The ordering of fetched changes is not guaranteed, but changes will typically be fetched from oldest to newest.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFetchedRecordZoneChangesEvent : CKSyncEngineEvent

@property (readonly, copy, nonatomic) NSArray<CKRecord *> *modifications;
@property (readonly, copy, nonatomic) NSArray<CKSyncEngineFetchedRecordDeletion *> *deletions;

@end

/// The sync engine finished sending a batch of database changes to the server.
///
/// If a change failed, try to resolve the issue causing the error and make the change again if necessary.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineSentDatabaseChangesEvent : CKSyncEngineEvent

@property (readonly, copy, nonatomic) NSArray<CKRecordZone *> *savedZones;
@property (readonly, copy, nonatomic) NSArray<CKSyncEngineFailedZoneSave *> *failedZoneSaves;

@property (readonly, copy, nonatomic) NSArray<CKRecordZoneID *> *deletedZoneIDs;
@property (readonly, copy, nonatomic) NSDictionary<CKRecordZoneID *, NSError *> *failedZoneDeletes;

@end

/// The sync engine finished sending a batch of record zone changes to the server.
///
/// If a record save succeeded, you should encode the system fields of this record to use the next time you save. See `encodeSystemFields` on ``CKRecord``.
///
/// If a record deletion succeeded, you should remove any local system fields for that record.
///
/// If the record change failed, try to resolve the issue causing the error and save the record again if necessary.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineSentRecordZoneChangesEvent : CKSyncEngineEvent

@property (readonly, copy, nonatomic) NSArray<CKRecord *> *savedRecords;
@property (readonly, copy, nonatomic) NSArray<CKSyncEngineFailedRecordSave *> *failedRecordSaves;

@property (readonly, copy, nonatomic) NSArray<CKRecordID *> *deletedRecordIDs;
@property (readonly, copy, nonatomic) NSDictionary<CKRecordID *, NSError *> *failedRecordDeletes;

@end

/// The sync engine is about to fetch changes from the server.
///
/// This might be a good signal to prepare your local data store for incoming changes if necessary.
/// The changes themselves will be delivered via `CKSyncEngineFetchedDatabaseChanges` and `CKSyncEngineFetchedRecordZoneChangesEvent`.
///
/// Note that this event might not always occur every time you call `fetchChanges`.
/// For example, if you call `fetchChanges` concurrently while the engine is already fetching changes, this event might not be sent.
/// Similarly, if there's no logged-in account, the engine might short-circuit the call to `fetchChanges`, and this event won't be sent.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineWillFetchChangesEvent : CKSyncEngineEvent

@property (readonly, strong, nonatomic) CKSyncEngineFetchChangesContext *context API_AVAILABLE(macos(14.2), macCatalyst(17.2), ios(17.2), tvos(17.2), watchos(10.2));

@end

/// The sync engine is about to fetch record zone changes from the server for a specific zone.
///
/// This might be a good signal to prepare your local data store for incoming changes if necessary.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineWillFetchRecordZoneChangesEvent : CKSyncEngineEvent
    
@property (readonly, copy, nonatomic) CKRecordZoneID *zoneID;

@end

/// The sync engine finished fetching record zone changes from the server for a specific zone.
///
/// This might be a good signal to perform any post-processing tasks on a per-zone basis if necessary.
///
/// You should receive one `CKSyncEngineDidFetchRecordZoneChangesEvent` for each `CKSyncEngineWillFetchRecordZoneChangesEvent`.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineDidFetchRecordZoneChangesEvent : CKSyncEngineEvent

@property (readonly, copy, nonatomic) CKRecordZoneID *zoneID;
@property (nullable, readonly, copy, nonatomic) NSError *error;

@end

/// The sync engine finished fetching changes from the server.
///
/// This might be a good signal to perform any post-processing tasks required after persisting fetched changes to disk.
///
/// You should receive one `CKSyncEngineDidFetchChangesEvent` for each `CKSyncEngineWillFetchChangesEvent`.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineDidFetchChangesEvent : CKSyncEngineEvent

@property (readonly, strong, nonatomic) CKSyncEngineFetchChangesContext *context API_AVAILABLE(macos(14.2), macCatalyst(17.2), ios(17.2), tvos(17.2), watchos(10.2));

@end

/// The sync engine is about to send changes to the server.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineWillSendChangesEvent : CKSyncEngineEvent
    
@property (readonly, strong, nonatomic) CKSyncEngineSendChangesContext *context;

@end

/// The sync engine finished sending changes to the server.
///
/// You should receive one `CKSyncEngineDidSendChangesEvent` for every `CKSyncEngineWillSendChangesEvent`.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineDidSendChangesEvent : CKSyncEngineEvent
    
@property (readonly, strong, nonatomic) CKSyncEngineSendChangesContext *context;

@end

#pragma mark - Data

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFetchedRecordDeletion : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (readonly, copy, nonatomic) CKRecordID *recordID;
@property (readonly, copy, nonatomic) CKRecordType recordType;

@end

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, CKSyncEngineZoneDeletionReason) {
    /// A deletion from your software.
    CKSyncEngineZoneDeletionReasonDeleted,
    
    /// A deletion from the user via the iCloud storage UI.
    /// This is an indication that the user wanted all data deleted, so local cached data should be wiped and not re-uploaded to the server.
    CKSyncEngineZoneDeletionReasonPurged,

    /// The user chose to reset all encrypted data for their account.
    /// This is an indication that the user had to reset encrypted data during account recovery, so local cached data should be re-uploaded to the server to minimize data loss.
    CKSyncEngineZoneDeletionReasonEncryptedDataReset,
};

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFetchedZoneDeletion : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (readonly, copy, nonatomic) CKRecordZoneID *zoneID;
@property (readonly, assign, nonatomic) CKSyncEngineZoneDeletionReason reason;

@end

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFailedRecordSave : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (readonly, strong, nonatomic) CKRecord *record;
@property (readonly, strong, nonatomic) NSError *error;

@end

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
NS_SWIFT_SENDABLE
CK_SUBCLASSING_RESTRICTED
@interface CKSyncEngineFailedZoneSave : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (readonly, strong, nonatomic) CKRecordZone *recordZone;
@property (readonly, strong, nonatomic) NSError *error;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
