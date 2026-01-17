//
//  CKModifyRecordsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKRecord, CKRecordID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*! @enum CKRecordSavePolicy
 *
 *  @constant CKRecordSaveIfServerRecordUnchanged
 *  @discussion Locally edited keys are sent to the server, updating the record if the server record has not been modified. This is the default and recommended save policy for regular use.
 *  This policy compares the record change tag with the server record, and may return @c CKErrorServerRecordChanged if the server record has been modified, for example by another device.
 *  Note: A @c CKShare record is always treated as @c CKRecordSaveIfServerRecordUnchanged, regardless of the @c savePolicy of the operation that modifies the share.
 *
 *  @constant CKRecordSaveChangedKeys
 *  @discussion Locally edited keys are written to the server, updating the record even if the server record has been modified.
 *  Note: This policy should be used with care, as it can overwrite changes made by other devices.
 *  Any previously committed change to the server, for example by other devices, will always be overwritten by the locally changed value.
 *  Note: A @c CKShare record is always treated as @c CKRecordSaveIfServerRecordUnchanged, regardless of the @c savePolicy of the operation that modifies the share.
 *  For non-CKShare records, this policy does not compare the record change tag and therefore will not return @c CKErrorServerRecordChanged
 *
 *  @constant CKRecordSaveAllKeys
 *  @discussion All local keys are written to the server, updating the record even if the server record has been modified.
 *  Note: This policy should be used with care. Any previously committed change to the server, for example by other devices, will be overwritten by the local value.
 *  Keys present only on the server remain unchanged.
 *  There are two common ways in which a server record will contain keys not present locally:
 *  1 - Another client may have added a new key to the record since it was fetched.
 *  2 - If @c desiredKeys was used with the fetch / query that returned this record, only a portion of the record's keys may have been downloaded.
 *  Note: A @c CKShare record is always treated as @c CKRecordSaveIfServerRecordUnchanged, regardless of the @c savePolicy of the operation that modifies the share.
 *  For non-CKShare records, this policy does not compare the record change tag and therefore will not return @c CKErrorServerRecordChanged
 */

typedef NS_ENUM(NSInteger, CKRecordSavePolicy) {
    CKRecordSaveIfServerRecordUnchanged = 0,
    CKRecordSaveChangedKeys             = 1, /** Does not compare record change tags */
    CKRecordSaveAllKeys                 = 2, /** Does not compare record change tags */
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKModifyRecordsOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordsToSave:(nullable NSArray<CKRecord *> *)records recordIDsToDelete:(nullable NSArray<CKRecordID *> *)recordIDs;

@property (nullable, copy, nonatomic) NSArray<CKRecord *> *recordsToSave;
@property (nullable, copy, nonatomic) NSArray<CKRecordID *> *recordIDsToDelete;

/*! @abstract  Determines what data is sent to the server and whether the save should succeed even if the record on the server has changed.
 *
 *  @discussion:  The default value is @c CKRecordSaveIfServerRecordUnchanged, which is the recommended value for regular use.
 *  A @c CKShare record is always treated as @c CKRecordSaveIfServerRecordUnchanged, regardless of the @c savePolicy specified.
 */
@property (assign, nonatomic) CKRecordSavePolicy savePolicy;

/*! @discussion This property is kept by the server to identify the last known request from this client.
 *  Multiple requests from the client with the same change token will be ignored by the server.
 */
@property (nullable, copy, nonatomic) NSData *clientChangeTokenData;

/*! @abstract  Determines whether the batch should fail atomically or not.
 *
 *  @discussion YES by default.
 *  Server-side write atomicity is only enforced on zones that have @c CKRecordZoneCapabilityAtomic.
 *  If @c isAtomic is YES, client-side checks are enforced regardless of the zone's capabilities.  (For example, if a record is malformed, and cannot be sent to the server, the client will forcibly fail all other records-to-be-modified in that zone)
 */
@property (assign, nonatomic) BOOL atomic NS_SWIFT_NAME(isAtomic);

/*! @abstract Indicates the progress for each record.
 *
 *  @discussion This method is called at least once with a progress of 1.0 for every record. Intermediate progress is only reported for records that contain assets.
 *  It is possible for progress to regress when a retry is automatically triggered.
 *  Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 *  This block may share mutable state with other blocks assigned to this operation, but any such mutable state
 *  should not be concurrently used outside of blocks assigned to this operation.
 */
@property (nullable, copy, nonatomic) void (^perRecordProgressBlock)(CKRecord *record, double progress);

/*! @abstract Called on success or failure for each record.
 *
 *  @discussion Will not be invoked if @c perRecordSaveBlock is set.
 *  Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 *  This block may share mutable state with other blocks assigned to this operation, but any such mutable state
 *  should not be concurrently used outside of blocks assigned to this operation.
 */
@property (nullable, copy, nonatomic) void (^perRecordCompletionBlock)(CKRecord *record, NSError * _Nullable error) API_DEPRECATED_WITH_REPLACEMENT("perRecordSaveBlock", macos(10.10, 12.0), ios(8.0, 15.0), tvos(9.0, 15.0), watchos(3.0, 8.0));


/*! @abstract Called on success or failure of a record save
 *
 *  @discussion Following a successful record save, this callback will be invoked with a nonnull @c record, and a nil @c error.
 *  Following a save failure due to a per-item error (@c CKErrorServerRecordChanged, for example), this callback will be invoked with a nil @c record, and a nonnull @c error
 *  Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 *  This block may share mutable state with other blocks assigned to this operation, but any such mutable state
 *  should not be concurrently used outside of blocks assigned to this operation.
 */
@property (nullable, copy, nonatomic) void (^perRecordSaveBlock)(CKRecordID *recordID, CKRecord * _Nullable record, NSError * _Nullable error) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_REFINED_FOR_SWIFT;

/*! @abstract Called on success or failure of a record deletion
 *
 *  Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 *  This block may share mutable state with other blocks assigned to this operation, but any such mutable state
 *  should not be concurrently used outside of blocks assigned to this operation.
 */
@property (nullable, copy, nonatomic) void (^perRecordDeleteBlock)(CKRecordID *recordID, NSError * _Nullable error) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_REFINED_FOR_SWIFT;

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The @code -[NSOperation completionBlock] @endcode will also be called if both are set.
 *  If the error is @c CKErrorPartialFailure, the error's userInfo dictionary contains a dictionary of recordIDs to errors keyed off of @c CKPartialErrorsByItemIDKey.
 *  @c savedRecords, @c deletedRecordIDs and any @c CKPartialErrorsByItemIDKey errors are repeats of the data sent back in previous @c perRecordSaveBlock and @c perRecordDeleteBlock invocations
 *  This call happens as soon as the server has seen all record changes, and may be invoked while the server is processing the side effects of those changes.
 *  Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 *  This block may share mutable state with other blocks assigned to this operation, but any such mutable state
 *  should not be concurrently used outside of blocks assigned to this operation.
 */
@property (nullable, copy, nonatomic) void (^modifyRecordsCompletionBlock)(NSArray<CKRecord *> * _Nullable savedRecords, NSArray<CKRecordID *> * _Nullable deletedRecordIDs, NSError * _Nullable operationError)
CK_SWIFT_DEPRECATED("Use modifyRecordsResultBlock instead", macos(10.10, 12.0), ios(8.0, 15.0), tvos(9.0, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
