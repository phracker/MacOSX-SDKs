//
//  CKDatabase.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKDatabaseOperation, CKRecord, CKRecordID, CKRecordZone, CKRecordZoneID, CKQuery, CKSubscription;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CKDatabaseScope) {
    CKDatabaseScopePublic = 1,
    CKDatabaseScopePrivate,
    CKDatabaseScopeShared,
} NS_ENUM_AVAILABLE(10_12, 10_0);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKDatabase : NSObject
- (instancetype)init NS_UNAVAILABLE;
- (void)addOperation:(CKDatabaseOperation *)operation;
@property (nonatomic, readonly, assign) CKDatabaseScope databaseScope NS_AVAILABLE(10_12, 10_0);
@end

@interface CKDatabase (ConvenienceMethods)

/* Convenience APIs
   These calls operate on a single item in the default zone and allow for simple operations.
   If you'd like to batch your requests, add dependencies between requests, set priorities,
   or schedule operations on your own queue, take a look at the corresponding CKOperation.
   This work is treated as having NSQualityOfServiceUserInitiated quality of service.
 */

#pragma mark Record Convenience Methods
/* CKFetchRecordsOperation and CKModifyRecordsOperation are the more configurable,
 CKOperation-based alternatives to these methods */
- (void)fetchRecordWithID:(CKRecordID *)recordID completionHandler:(void (^)(CKRecord * _Nullable record, NSError * _Nullable error))completionHandler;
- (void)saveRecord:(CKRecord *)record completionHandler:(void (^)(CKRecord * _Nullable record, NSError * _Nullable error))completionHandler;
- (void)deleteRecordWithID:(CKRecordID *)recordID completionHandler:(void (^)(CKRecordID * _Nullable recordID, NSError * _Nullable error))completionHandler;

#pragma mark Query Convenience Method
/* CKQueryOperation is the more configurable, CKOperation-based alternative to this method 
 Queries can potentially return a large number of records, and the server will return those records in batches.
 This convenience API will only fetch the first batch of results (equivalent to using CKQueryOperationMaximumResults).
 If you would like to fetch all results, use CKQueryOperation and its CKQueryCursor instead.
 Queries invoked within a sharedCloudDatabase must specify a zoneID.  Cross-zone queries are not supported in a sharedCloudDatabase */
- (void)performQuery:(CKQuery *)query inZoneWithID:(nullable CKRecordZoneID *)zoneID completionHandler:(void (^)(NSArray<CKRecord *> * _Nullable results, NSError * _Nullable error))completionHandler;

#pragma mark Record Zone Convenience Methods
/* CKFetchRecordZonesOperation and CKModifyRecordZonesOperation are the more configurable,
 CKOperation-based alternatives to these methods */
- (void)fetchAllRecordZonesWithCompletionHandler:(void (^)(NSArray<CKRecordZone *> * _Nullable zones, NSError * _Nullable error))completionHandler;
- (void)fetchRecordZoneWithID:(CKRecordZoneID *)zoneID completionHandler:(void (^)(CKRecordZone * _Nullable zone, NSError * _Nullable error))completionHandler;
- (void)saveRecordZone:(CKRecordZone *)zone completionHandler:(void (^)(CKRecordZone * _Nullable zone, NSError * _Nullable error))completionHandler;
- (void)deleteRecordZoneWithID:(CKRecordZoneID *)zoneID completionHandler:(void (^)(CKRecordZoneID * _Nullable zoneID, NSError * _Nullable error))completionHandler;

#pragma mark Subscription Convenience Methods
/* CKFetchSubscriptionsOperation and CKModifySubscriptionsOperation are the more configurable,
 CKOperation-based alternative to these methods */
- (void)fetchSubscriptionWithID:(NSString *)subscriptionID completionHandler:(void (^)(CKSubscription * _Nullable subscription, NSError * _Nullable error))completionHandler __WATCHOS_PROHIBITED;
- (void)fetchAllSubscriptionsWithCompletionHandler:(void (^)(NSArray<CKSubscription *> * _Nullable subscriptions, NSError * _Nullable error))completionHandler __WATCHOS_PROHIBITED;
- (void)saveSubscription:(CKSubscription *)subscription completionHandler:(void (^)(CKSubscription * _Nullable subscription, NSError * _Nullable error))completionHandler __WATCHOS_PROHIBITED;
- (void)deleteSubscriptionWithID:(NSString *)subscriptionID completionHandler:(void (^)(NSString * _Nullable subscriptionID, NSError * _Nullable error))completionHandler __WATCHOS_PROHIBITED;

@end
NS_ASSUME_NONNULL_END
