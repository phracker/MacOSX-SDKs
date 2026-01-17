//
//  CKSyncEngineState.h
//  CloudKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

@class CKAsset, CKRecordID, CKRecordZone, CKRecordZoneID;
@class CKSyncEnginePendingRecordZoneChange, CKSyncEnginePendingDatabaseChange;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that tracks some state required for proper and efficient operation of ``CKSyncEngine-5sie5``.
///
/// ``CKSyncEngine-5sie5`` needs to track several things in order to properly sync.
/// For example, it needs to remember the last server change tokens for your database and zones.
/// It also needs to keep track of things like the last known user record ID and other various pieces of state.
///
/// A lot of this state is hidden internally, but some of it you can control.
///
/// ## Pending changes
///
/// One of the main things you can control is the list of pending changes to send to the server.
/// You can control these by calling functions like ``addPendingDatabaseChanges:`` and ``addPendingRecordZoneChanges:``.
/// When you add new pending changes, the sync engine will automatically schedule a task to sync with the server.
///
/// ## State serialization
///
/// ``CKSyncEngine-5sie5`` will occasionally update its state in the background.
/// When it updates its state, your delegate will receive a ``CKSyncEngineStateUpdateEvent``.
///
/// This event will contain a ``CKSyncEngineStateSerialization``, which you should persist locally.
/// The next time your process launches, you initialize your sync engine with the last state serialization you received.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineState : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// A list of record changes that need to be sent to the server.
///
/// ``CKSyncEngine-5sie5`` provides the convenience of tracking your pending record zone changes.
/// When the user makes some changes that need to be sent to the server, you can track them in this list.
/// Then, you can use this list when creating your next ``CKSyncEngineRecordZoneChangeBatch`` in your ``CKSyncEngineDelegate-1q7g8``.
///
/// The sync engine will ensure consistency and deduplicate these pending changes under the hood.
/// For example, if you add a pending save for record A, then record B, then record A again, this will result in a list of `[saveRecordA, saveRecordB]`.
/// Similarly, if you add a pending save for record A, then add a pending delete for the same record A, this will result in a single pending change of `[deleteRecordA]`.
///
/// The sync engine will manage this list while it sends changes to the server.
/// For example, when it successfully saves a record, it will remove that change from this list.
/// If it fails to send a change due to some retryable error (e.g. a network failure), it will keep that change in this list.
///
/// If you'd prefer to track pending changes yourself, you can use ``CKSyncEngine/State/hasPendingUntrackedChanges`` instead.
@property (readonly, copy) NSArray<CKSyncEnginePendingRecordZoneChange *> *pendingRecordZoneChanges;

/// A list of database changes that need to be sent to the server, similar to `pendingRecordZoneChanges`.
@property (readonly, copy) NSArray<CKSyncEnginePendingDatabaseChange *> *pendingDatabaseChanges;

/// This represents whether or not you have pending changes to send to the server that aren't tracked in ``CKSyncEngine/State/pendingRecordZoneChanges``.
/// This is useful if you want to track pending changes in your own local database instead of the sync engine state.
///
/// When this property is set, the sync engine will automatically schedule a sync.
/// When the sync task runs, it will ask your delegate for pending changes in ``CKSyncEngineDelegate/nextRecordZoneChangeBatch(_:syncEngine:)``.
@property (assign) BOOL hasPendingUntrackedChanges;

/// The list of zone IDs that have new changes to fetch from the server.
/// ``CKSyncEngine-5sie5`` keeps track of these zones and will update this list as it receives new information.
@property (readonly, copy) NSArray<CKRecordZoneID *> *zoneIDsWithUnfetchedServerChanges;

/// Adds to the list of pending record zone changes.
///
/// When you add a new pending change, the sync engine will automatically schedule a sync task.
///
/// The sync engine will ensure consistency and deduplicate these changes under the hood.
- (void)addPendingRecordZoneChanges:(NSArray<CKSyncEnginePendingRecordZoneChange *> *)changes NS_SWIFT_NAME(add(pendingRecordZoneChanges:));

/// Removes from the list of pending record zone changes.
- (void)removePendingRecordZoneChanges:(NSArray<CKSyncEnginePendingRecordZoneChange *> *)changes NS_SWIFT_NAME(remove(pendingRecordZoneChanges:));

/// Adds to the list of pending database changes.
///
/// When you add a new pending change, the sync engine will automatically schedule a sync task.
///
/// The sync engine will ensure consistency and deduplicate these changes under the hood.
- (void)addPendingDatabaseChanges:(NSArray<CKSyncEnginePendingDatabaseChange *> *)changes NS_SWIFT_NAME(add(pendingDatabaseChanges:));

/// Removes from the list of pending database changes.
- (void)removePendingDatabaseChanges:(NSArray<CKSyncEnginePendingDatabaseChange *> *)changes NS_SWIFT_NAME(remove(pendingDatabaseChanges:));

@end

#pragma mark - CKSyncEngineStateSerialization

/// A serialized representation of a ``CKSyncEngineState``.
///
/// This will be passed to your delegate via ``CKSyncEngine/Event/StateUpdate``.
/// You should use `NSSecureCoding` to persist this locally alongside your other data and use it the next time you initialize your sync engine.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineStateSerialization : NSObject <NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - CKSyncEnginePendingRecordZoneChange

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, CKSyncEnginePendingRecordZoneChangeType) {
    CKSyncEnginePendingRecordZoneChangeTypeSaveRecord,
    CKSyncEnginePendingRecordZoneChangeTypeDeleteRecord,
};

/// A change in a record zone that needs to be sent to the server.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEnginePendingRecordZoneChange : NSObject

- (instancetype)initWithRecordID:(CKRecordID *)recordID
                            type:(CKSyncEnginePendingRecordZoneChangeType)type NS_DESIGNATED_INITIALIZER NS_SWIFT_NAME(init(_:type:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (readonly, copy, nonatomic) CKRecordID *recordID;
@property (readonly, assign, nonatomic) CKSyncEnginePendingRecordZoneChangeType type;

@end

#pragma mark - CKSyncEnginePendingDatabaseChange

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, CKSyncEnginePendingDatabaseChangeType) {
    CKSyncEnginePendingDatabaseChangeTypeSaveZone,
    CKSyncEnginePendingDatabaseChangeTypeDeleteZone,
};

/// A change in a database that needs to be sent to the server.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
// This class should not be subclassed. If it is, Sendable may no longer apply.
NS_SWIFT_SENDABLE
@interface CKSyncEnginePendingDatabaseChange : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (readonly, copy, nonatomic) CKRecordZoneID *zoneID;
@property (readonly, assign, nonatomic) CKSyncEnginePendingDatabaseChangeType type;

@end

/// A zone save that needs to be sent to the server.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEnginePendingZoneSave : CKSyncEnginePendingDatabaseChange

- (instancetype)initWithZone:(CKRecordZone *)zone NS_SWIFT_NAME(init(_:));

@property (readonly, copy, nonatomic) CKRecordZone *zone;

@end

/// A zone delete that needs to be sent to the server.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEnginePendingZoneDelete : CKSyncEnginePendingDatabaseChange

- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID NS_SWIFT_NAME(init(_:));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
