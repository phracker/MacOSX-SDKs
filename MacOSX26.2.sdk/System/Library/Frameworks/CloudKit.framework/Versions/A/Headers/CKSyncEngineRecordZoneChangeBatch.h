//
//  CKSyncEngineRecordZoneChangeBatch.h
//  CloudKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

@class CKRecord, CKRecordID, CKRecordZoneID;

#import <CloudKit/CKDefines.h>
#import <CloudKit/CKSyncEngineState.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A batch of record zone changes that `CKSyncEngine` will send to the server in a single request.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineRecordZoneChangeBatch : NSObject

/// Creates a batch of record zone changes according to a list of pending changes.
///
/// This will iterate over the pending changes in order and add them to the batch until it reaches the max batch size.
///
/// When it sees a pending save, it will ask the record provider for the actual ``CKRecord`` to send to the server.
/// If you return `nil` from the record provider, this will skip to the next pending change.
///
/// This will return `nil` if there are no pending changes to send.
- (nullable instancetype)initWithPendingChanges:(NSArray<CKSyncEnginePendingRecordZoneChange *> *)pendingChanges
                                 recordProvider:(CKRecord * _Nullable (NS_SWIFT_SENDABLE NS_NOESCAPE ^)(CKRecordID *recordID))recordProvider;

/// Creates a batch of record zone changes to send to the server with a specific set of changes.
///
/// If you'd like to construct your own custom batches of changes to send to the server, you can do so with this initializer.
///
/// ## Batch size limitations
///
/// When creating your own batches, you need to consider batch size limitations.
/// There is a maximum count and size of records that can be sent to the server in a single batch.
/// If you supply too many changes, or if the total size of the records is too large, then you might get a ``CKError/limitExceeded``.
///
/// > Tip: These batch size limitations are handled automatically by the ``initWithPendingChanges:recordProvider:`` initializer.
- (instancetype)initWithRecordsToSave:(nullable NSArray<CKRecord *> *)recordsToSave
                    recordIDsToDelete:(nullable NSArray<CKRecordID *> *)recordIDsToDelete
                         atomicByZone:(BOOL)atomicByZone;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The records to save to the server.
@property (readonly, copy) NSArray<CKRecord *> *recordsToSave;

/// The IDs of the records to delete from the server.
@property (readonly, copy) NSArray<CKRecordID *> *recordIDsToDelete;

/// If set to true, the sync engine will modify these records atomically by zone.
///
/// If this is true, and if any record change fails, then any other changes from that zone in this batch will also fail with ``CKError/batchRequestFailed``.
///
/// Records that exist in different zones will not be modified together atomically.
@property (assign) BOOL atomicByZone;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
