//
//  CKModifyRecordsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKRecord, CKRecordID;

NS_ASSUME_NONNULL_BEGIN

/*! @enum CKRecordSavePolicy
 *
 *  @constant CKRecordSaveIfServerRecordUnchanged
 *  @discussion Locally-edited keys are sent to the server.
 *  If the record on the server has been modified, fail the write and return an error. A CKShare's participants array is always treated as @c CKRecordSaveIfServerRecordUnchanged, regardless of the @c savePolicy of the operation that modifies the share.
 *
 *  @constant CKRecordSaveChangedKeys
 *  @discussion Locally-edited keys are written to the server.
 *  Any unseen changes on the server will be overwritten to the locally-edited value.
 *
 *  @constant CKRecordSaveAllKeys
 *  @discussion All local keys are written to the server.
 *  Any unseen changes on the server will be overwritten to the local values.  Keys present only on the server remain unchanged. There are two common ways in which a server record will contain keys not present locally:
 *  1 - Since you've fetched this record, another client has added a new key to the record.
 *  2 - The presence of @c desiredKeys on the fetch / query that returned this record meant that only a portion of the record's keys were downloaded.
 */

typedef NS_ENUM(NSInteger, CKRecordSavePolicy) {
    CKRecordSaveIfServerRecordUnchanged = 0,
    CKRecordSaveChangedKeys             = 1,
    CKRecordSaveAllKeys                 = 2,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKModifyRecordsOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordsToSave:(nullable NSArray<CKRecord *> *)records recordIDsToDelete:(nullable NSArray<CKRecordID *> *)recordIDs;

@property (nonatomic, copy, nullable) NSArray<CKRecord *> *recordsToSave;
@property (nonatomic, copy, nullable) NSArray<CKRecordID *> *recordIDsToDelete;

/*! The default value is @c CKRecordSaveIfServerRecordUnchanged. */
@property (nonatomic, assign) CKRecordSavePolicy savePolicy;

/*! @discussion This property is kept by the server to identify the last known request from this client.
 *  Multiple requests from the client with the same change token will be ignored by the server.
 */
@property (nonatomic, copy, nullable) NSData *clientChangeTokenData;

/*! @abstract  Determines whether the batch should fail atomically or not.
 *
 *  @discussion YES by default.
 *  Server-side write atomicity is only enforced on zones that have @c CKRecordZoneCapabilityAtomic.
 *  If @c isAtomic is YES, client-side checks are enforced regardless of the zone's capabilities.  (For example, if a record is malformed, and cannot be sent to the server, the client will forcibly fail all other records-to-be-modified in that zone)
 */
@property (nonatomic, assign) BOOL atomic NS_SWIFT_NAME(isAtomic);

/*! @abstract Indicates the progress for each record.
 *
 *  @discussion This method is called at least once with a progress of 1.0 for every record. Intermediate progress is only reported for records that contain assets.
 *  It is possible for progress to regress when a retry is automatically triggered.
 *  Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 */
@property (nonatomic, copy, nullable) void (^perRecordProgressBlock)(CKRecord *record, double progress);
/*! @abstract Called on success or failure for each record.
 *
 *  @discussion Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 */
@property (nonatomic, copy, nullable) void (^perRecordCompletionBlock)(CKRecord *record, NSError * _Nullable error);

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The @code -[NSOperation completionBlock] @endcode will also be called if both are set.
 *  If the error is @c CKErrorPartialFailure, the error's userInfo dictionary contains a dictionary of recordIDs to errors keyed off of @c CKPartialErrorsByItemIDKey.
 *  This call happens as soon as the server has seen all record changes, and may be invoked while the server is processing the side effects of those changes.
 *  Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 */
@property (nonatomic, copy, nullable) void (^modifyRecordsCompletionBlock)(NSArray<CKRecord *> * _Nullable savedRecords, NSArray<CKRecordID *> * _Nullable deletedRecordIDs, NSError * _Nullable operationError);

@end

NS_ASSUME_NONNULL_END
