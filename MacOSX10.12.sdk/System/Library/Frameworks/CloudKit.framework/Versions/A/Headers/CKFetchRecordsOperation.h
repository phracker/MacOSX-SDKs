//
//  CKFetchRecordsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKRecord, CKRecordID;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKFetchRecordsOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordIDs:(NSArray<CKRecordID *> *)recordIDs;

+ (instancetype)fetchCurrentUserRecordOperation;

@property (nonatomic, copy, nullable) NSArray<CKRecordID *> *recordIDs;

/* Declares which user-defined keys should be fetched and added to the resulting CKRecords.  If nil, declares the entire record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.  Defaults to nil. */
@property (nonatomic, copy, nullable) NSArray<NSString *> *desiredKeys;

/* Called repeatedly during transfer. */
@property (nonatomic, copy, nullable) void (^perRecordProgressBlock)(CKRecordID *recordID, double progress);
/* Called on success or failure for each record. */
@property (nonatomic, copy, nullable) void (^perRecordCompletionBlock)(CKRecord * _Nullable record, CKRecordID * _Nullable recordID, NSError * _Nullable error);

/*  This block is called when the operation completes.
    The [NSOperation completionBlock] will also be called if both are set.
    If the error is CKErrorPartialFailure, the error's userInfo dictionary contains
    a dictionary of recordIDs to errors keyed off of CKPartialErrorsByItemIDKey.
*/
@property (nonatomic, copy, nullable) void (^fetchRecordsCompletionBlock)(NSDictionary<CKRecordID * , CKRecord *> * _Nullable recordsByRecordID, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
