//
//  CKFetchRecordZoneChangesOperation.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>
#import <CloudKit/CKServerChangeToken.h>

@class CKRecord, CKRecordID, CKRecordZoneID, CKFetchRecordZoneChangesOptions;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKFetchRecordZoneChangesOperation : CKDatabaseOperation

/* This operation will fetch records changes across the given record zones

 For each previousServerChangeToken passed in with a CKFetchRecordZoneChangesOptions, 
 only records that have changed since that anchor will be fetched.

 If this is your first fetch of a zone or if you wish to re-fetch all records within a zone, do not
 include a previousServerChangeToken.

 Change tokens are opaque tokens and clients should not infer any behavior based on their content. */
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordZoneIDs:(NSArray<CKRecordZoneID *> *)recordZoneIDs optionsByRecordZoneID:(nullable NSDictionary<CKRecordZoneID *, CKFetchRecordZoneChangesOptions *> *)optionsByRecordZoneID;

@property (nonatomic, copy, nullable) NSArray<CKRecordZoneID *> *recordZoneIDs;
@property (nonatomic, copy, nullable) NSDictionary<CKRecordZoneID *, CKFetchRecordZoneChangesOptions *> *optionsByRecordZoneID;

/* When set to YES, this operation will send repeated requests to the server until all record changes have been fetched.
 recordZoneChangeTokensUpdatedBlock will be invoked periodically, to give clients an updated change token so that already-fetched
 record changes don't need to be re-fetched on a subsequent operation. recordZoneFetchCompletionBlock will only be called once and moreComing 
 will always be NO.
 
 When set to NO, it is the responsibility of the caller to issue subsequent fetch-changes operations when moreComing is YES
 in a recordZoneFetchCompletionBlock invocation.
 fetchAllChanges is YES by default */
@property (nonatomic, assign) BOOL fetchAllChanges;

@property (nonatomic, copy, nullable) void (^recordChangedBlock)(CKRecord *record);
@property (nonatomic, copy, nullable) void (^recordWithIDWasDeletedBlock)(CKRecordID *recordID, NSString *recordType);

/* Clients are responsible for saving this per-recordZone serverChangeToken and passing it in to the next call to CKFetchRecordZoneChangesOperation.
 Note that a fetch can fail partway. If that happens, an updated change token may be returned in this
  block so that already fetched records don't need to be re-downloaded on a subsequent operation.
 recordZoneChangeTokensUpdatedBlock will not be called after the last batch of changes in a zone; the recordZoneFetchCompletionBlock block will be called instead.
 The clientChangeTokenData from the most recent CKModifyRecordsOperation issued on this zone is also returned, or nil if none was provided.
 If the server returns a CKErrorChangeTokenExpired error, the serverChangeToken used for this record zone when initting this operation was too old and the client should toss its local cache and re-fetch the changes in this record zone starting with a nil serverChangeToken. 
 recordZoneChangeTokensUpdatedBlock will not be called if fetchAllChanges is NO. */
@property (nonatomic, copy, nullable) void (^recordZoneChangeTokensUpdatedBlock)(CKRecordZoneID *recordZoneID, CKServerChangeToken * _Nullable serverChangeToken, NSData * _Nullable clientChangeTokenData);
@property (nonatomic, copy, nullable) void (^recordZoneFetchCompletionBlock)(CKRecordZoneID *recordZoneID, CKServerChangeToken * _Nullable serverChangeToken, NSData * _Nullable clientChangeTokenData, BOOL moreComing, NSError * _Nullable recordZoneError);

/* serverChangeTokens previously returned via a recordZoneChangeTokensUpdatedBlock or recordZoneFetchCompletionBlock invocation,
 along with the record changes that preceded it, are valid even if there is a subsequent operationError */
@property (nonatomic, copy, nullable) void (^fetchRecordZoneChangesCompletionBlock)(NSError * _Nullable operationError);

@end


API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKFetchRecordZoneChangesOptions : NSObject <NSSecureCoding, NSCopying>

@property (nonatomic, copy, nullable) CKServerChangeToken *previousServerChangeToken;

@property (nonatomic, assign) NSUInteger resultsLimit;

/* Declares which user-defined keys should be fetched and added to the resulting CKRecords.  If nil, declares the entire record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.  Defaults to nil. */
@property (nonatomic, copy, nullable) NSArray<NSString *> *desiredKeys;
@end
NS_ASSUME_NONNULL_END
