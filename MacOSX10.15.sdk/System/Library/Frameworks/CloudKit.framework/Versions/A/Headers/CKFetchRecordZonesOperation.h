//
//  CKFetchRecordZonesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKRecordZone, CKRecordZoneID;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKFetchRecordZonesOperation : CKDatabaseOperation

+ (instancetype)fetchAllRecordZonesOperation;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordZoneIDs:(NSArray<CKRecordZoneID *> *)zoneIDs;

@property (nonatomic, copy, nullable) NSArray<CKRecordZoneID *> *recordZoneIDs;

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The [NSOperation completionBlock] will also be called if both are set.
 *  If the error is `CKErrorPartialFailure`, the error's userInfo dictionary contains a dictionary of zoneIDs to errors keyed off of `CKPartialErrorsByItemIDKey`.
*/
@property (nonatomic, copy, nullable) void (^fetchRecordZonesCompletionBlock)(NSDictionary<CKRecordZoneID *, CKRecordZone *> * _Nullable recordZonesByZoneID, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
