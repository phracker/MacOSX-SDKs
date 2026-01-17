//
//  CKModifyRecordZonesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKModifyRecordZonesOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordZonesToSave:(NSArray /* CKRecordZone */ *)recordZonesToSave recordZoneIDsToDelete:(NSArray /* CKRecordZoneID */ *)recordZoneIDsToDelete;

@property (nonatomic, copy) NSArray /* CKRecordZone */ *recordZonesToSave;
@property (nonatomic, copy) NSArray /* CKRecordZoneID */ *recordZoneIDsToDelete;

/*  This block is called when the operation completes.
 The [NSOperation completionBlock] will also be called if both are set.
 If the error is CKErrorPartialFailure, the error's userInfo dictionary contains
 a dictionary of recordZoneIDs to errors keyed off of CKPartialErrorsByItemIDKey.
 This call happens as soon as the server has
 seen all record changes, and may be invoked while the server is processing the side effects
 of those changes.
 */
@property (nonatomic, copy) void (^modifyRecordZonesCompletionBlock)(NSArray /* CKRecordZone */ *savedRecordZones, NSArray /* CKRecordZoneID */ *deletedRecordZoneIDs, NSError *operationError);

@end
