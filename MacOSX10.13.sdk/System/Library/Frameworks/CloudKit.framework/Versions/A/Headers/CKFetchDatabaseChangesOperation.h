//
//  CKFetchDatabaseChangesOperation.h
//  CloudKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKRecordZoneID, CKServerChangeToken;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKFetchDatabaseChangesOperation : CKDatabaseOperation

/* This operation will fetch changes to record zones within a database
 If a change anchor from a previous CKFetchDatabaseChangesOperation is passed in, only the zones that have changed since that anchor will be returned.
 This per-database serverChangeToken is not to be confused with the per-recordZone serverChangeToken from
 CKFetchRecordZoneChangesOperation.
 If this is your first fetch or if you wish to re-fetch all zones, pass nil for the change token.
 Change token are opaque tokens and clients should not infer any behavior based on their content.
 CKFetchDatabaseChangesOperations are supported in a privateCloudDatabase and sharedCloudDatabase */
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithPreviousServerChangeToken:(nullable CKServerChangeToken *)previousServerChangeToken;

@property (nonatomic, copy, nullable) CKServerChangeToken *previousServerChangeToken;
@property (nonatomic, assign) NSUInteger resultsLimit;

/* When set to YES, this operation will send repeated requests to the server until all record zone changes have been fetched.
 changeTokenUpdatedBlock will be invoked periodically, to give clients an updated change token so that already-fetched
 record zone changes don't need to be re-fetched on a subsequent operation.
 When set to NO, it is the responsibility of the caller to issue subsequent fetch-changes operations when moreComing is YES
 in a fetchDatabaseChangesCompletionBlock invocation.
 fetchAllChanges is YES by default */
@property (nonatomic, assign) BOOL fetchAllChanges;

@property (nonatomic, copy, nullable) void (^recordZoneWithIDChangedBlock)(CKRecordZoneID *zoneID);
@property (nonatomic, copy, nullable) void (^recordZoneWithIDWasDeletedBlock)(CKRecordZoneID *zoneID);

/* If this block is set it will be called instead of recordZoneWithIDWasDeletedBlock if the user deleted this zone via the iCloud storage UI.
   This is an indication that the user wanted all data deleted, so local cached data should be wiped and not re-uploaded to the server. */
@property (nonatomic, copy, nullable) void (^recordZoneWithIDWasPurgedBlock)(CKRecordZoneID *zoneID) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@property (nonatomic, copy, nullable) void (^changeTokenUpdatedBlock)(CKServerChangeToken * serverChangeToken);

/* Clients are responsible for saving the change token at the end of the operation and passing it in to the next call to CKFetchDatabaseChangesOperation.
 If the server returns a CKErrorChangeTokenExpired error, the previousServerChangeToken value was too old and the client should toss its local cache and
 re-fetch the changes in this record zone starting with a nil previousServerChangeToken.
 If moreComing is true then the server wasn't able to return all the changes in this response.
 Another CKFetchDatabaseChangesOperation operation should be run with the previousServerChangeToken token from this operation. */
@property (nonatomic, copy, nullable) void (^fetchDatabaseChangesCompletionBlock)(CKServerChangeToken * _Nullable serverChangeToken, BOOL moreComing, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
