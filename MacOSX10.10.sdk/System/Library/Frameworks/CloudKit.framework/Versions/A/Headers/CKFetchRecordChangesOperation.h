//
//  CKFetchRecordChangesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKRecord, CKRecordID, CKRecordZoneID;

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKServerChangeToken : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
@end

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKFetchRecordChangesOperation : CKDatabaseOperation

/* This operation will fetch all records changes in the given record zone.
   If a change anchor from a previous CKFetchRecordChangesOperation is passed in, only the records that have changed
    since that anchor will be fetched.
   If this is your first fetch or if you wish to re-fetch all records, pass nil for the change anchor.
   Change anchors are opaque tokens and clients should not infer any behavior based on their content. */
- (instancetype)initWithRecordZoneID:(CKRecordZoneID *)recordZoneID previousServerChangeToken:(CKServerChangeToken *)previousServerChangeToken;

@property (nonatomic, copy) CKRecordZoneID *recordZoneID;
@property (nonatomic, copy) CKServerChangeToken *previousServerChangeToken;

@property (nonatomic, assign) NSUInteger resultsLimit;

/* Declares which user-defined keys should be fetched and added to the resulting CKRecords.  If nil, declares the entire record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.  Defaults to nil. */
@property (nonatomic, copy) NSArray /* NSString */ *desiredKeys;

@property (nonatomic, copy) void (^recordChangedBlock)(CKRecord *record);
@property (nonatomic, copy) void (^recordWithIDWasDeletedBlock)(CKRecordID *recordID);

/* Will be set before fetchRecordChangesCompletionBlock is called. If moreComing is true then the server wasn't able to return all the changes in this response.
    Another CKFetchRecordChangesOperation operation should be run with the updated serverChangeToken token from this operation. */
@property (nonatomic, readonly) BOOL moreComing;

/* Clients are responsible for saving the change token at the end of the operation and passing it in to the next call to CKFetchRecordChangesOperation.
   Note that a fetch can fail partway. If that happens, an updated change token may be returned in the completion
    block so that already fetched records don't need to be re-downloaded on a subsequent operation.
   The clientChangeToken from the most recent CKModifyRecordsOperation is also returned, or nil if none was provided. 
   If the server returns a CKErrorChangeTokenExpired error, the previousServerChangeToken value was too old and the client should toss its local cache and 
    re-fetch the changes in this record zone starting with a nil previousServerChangeToken. */
@property (nonatomic, copy) void (^fetchRecordChangesCompletionBlock)(CKServerChangeToken *serverChangeToken, NSData *clientChangeTokenData, NSError *operationError);

@end
