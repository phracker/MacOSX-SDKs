//
//  CKFetchRecordChangesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>
#import <CloudKit/CKServerChangeToken.h>

@class CKRecord, CKRecordID, CKRecordZoneID;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKFetchRecordChangesOperation : CKDatabaseOperation

/* This operation will fetch records changes in the given record zone.

   If a change anchor from a previous CKFetchRecordChangesOperation is passed in, only the records that have changed
    since that anchor will be fetched.

   If this is your first fetch or if you wish to re-fetch all records, pass nil for the change anchor.

   Change anchors are opaque tokens and clients should not infer any behavior based on their content. */
- (instancetype)initWithRecordZoneID:(CKRecordZoneID *)recordZoneID previousServerChangeToken:(nullable CKServerChangeToken *)previousServerChangeToken;

@property (nonatomic, copy) CKRecordZoneID *recordZoneID;
@property (nonatomic, copy, nullable) CKServerChangeToken *previousServerChangeToken;

@property (nonatomic, assign) NSUInteger resultsLimit;

/* If fetchAllChanges is YES then this operation will send repeated requests to the server until moreComing is NO. 
   serverChangeTokenFetchedBlock will be called with an incremental change token after every request.
   This value is YES by default if you are linked on or after iOS 9.0 or OS X 10.11 */
@property (nonatomic, assign) BOOL fetchAllChanges NS_AVAILABLE(10_11, 9_0);

/* Declares which user-defined keys should be fetched and added to the resulting CKRecords.  If nil, declares the entire record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.  Defaults to nil. */
@property (nonatomic, copy, nullable) NSArray <NSString *> *desiredKeys;

@property (nonatomic, copy, nullable) void (^recordChangedBlock)(CKRecord *record);
@property (nonatomic, copy, nullable) void (^recordWithIDWasDeletedBlock)(CKRecordID *recordID);

/* If fetchAllChanges is YES, this operation will continue sending requests to the server until all changes have been fetched (moreComing == NO).
   Change tokens will be returned incrementally after each request. Your application should save those change tokens so it can efficiently 
    restart in the case of a network failure or other error that may interrupt a CKFetchRecordChangesOperation */
@property (nonatomic, copy, nullable) void (^serverChangeTokenFetchedBlock)(CKServerChangeToken *serverChangeToken) NS_AVAILABLE(10_11, 9_0);

/* Will be set before fetchRecordChangesCompletionBlock is called. If moreComing is true then the server wasn't able to return all the changes in this response.
    Another CKFetchRecordChangesOperation operation should be run with the updated serverChangeToken token from this operation. */
@property (nonatomic, readonly) BOOL moreComing;

/* Clients are responsible for saving the change token at the end of the operation and passing it in to the next call to CKFetchRecordChangesOperation.
   Note that a fetch can fail partway. If that happens, an updated change token may be returned in the completion
    block so that already fetched records don't need to be re-downloaded on a subsequent operation.
   The clientChangeToken from the most recent CKModifyRecordsOperation is also returned, or nil if none was provided. 
   If the server returns a CKErrorChangeTokenExpired error, the previousServerChangeToken value was too old and the client should toss its local cache and 
    re-fetch the changes in this record zone starting with a nil previousServerChangeToken. */
@property (nonatomic, copy, nullable) void (^fetchRecordChangesCompletionBlock)(CKServerChangeToken * __nullable serverChangeToken, NSData * __nullable clientChangeTokenData, NSError * __nullable operationError);

@end
NS_ASSUME_NONNULL_END
