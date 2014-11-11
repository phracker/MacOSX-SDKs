//
//  CKFetchRecordZonesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKFetchRecordZonesOperation : CKDatabaseOperation

+ (instancetype)fetchAllRecordZonesOperation;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordZoneIDs:(NSArray /* CKRecordZoneID */ *)zoneIDs;

@property (nonatomic, copy) NSArray /* CKRecordZoneID */ *recordZoneIDs;

/*  This block is called when the operation completes.
    The [NSOperation completionBlock] will also be called if both are set.
    If the error is CKErrorPartialFailure, the error's userInfo dictionary contains
    a dictionary of zoneIDs to errors keyed off of CKPartialErrorsByItemIDKey.
*/
@property (nonatomic, copy) void (^fetchRecordZonesCompletionBlock)(NSDictionary /* CKRecordZoneID -> CKRecordZone */ *recordZonesByZoneID, NSError *operationError);

@end
