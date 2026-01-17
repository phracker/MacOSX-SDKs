//
//  CKDatabase.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKDatabaseOperation, CKRecord, CKRecordID, CKRecordZone, CKRecordZoneID, CKQuery, CKSubscription;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKDatabase : NSObject
- (instancetype)init NS_UNAVAILABLE;
- (void)addOperation:(CKDatabaseOperation *)operation;
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
- (void)fetchRecordWithID:(CKRecordID *)recordID completionHandler:(void (^)(CKRecord * __nullable record, NSError * __nullable error))completionHandler;
- (void)saveRecord:(CKRecord *)record completionHandler:(void (^)(CKRecord * __nullable record, NSError * __nullable error))completionHandler;
- (void)deleteRecordWithID:(CKRecordID *)recordID completionHandler:(void (^)(CKRecordID * __nullable recordID, NSError * __nullable error))completionHandler;

#pragma mark Query Convenience Method
/* CKQueryOperation is the more configurable, CKOperation-based
 alternative to this method */
- (void)performQuery:(CKQuery *)query inZoneWithID:(nullable CKRecordZoneID *)zoneID completionHandler:(void (^)(NSArray <CKRecord *> * __nullable results, NSError * __nullable error))completionHandler;

#pragma mark Record Zone Convenience Methods
/* CKFetchRecordZonesOperation and CKModifyRecordZonesOperation are the more configurable,
 CKOperation-based alternatives to these methods */
- (void)fetchAllRecordZonesWithCompletionHandler:(void (^)(NSArray <CKRecordZone *> * __nullable zones, NSError * __nullable error))completionHandler;
- (void)fetchRecordZoneWithID:(CKRecordZoneID *)zoneID completionHandler:(void (^)(CKRecordZone * __nullable zone, NSError * __nullable error))completionHandler;
- (void)saveRecordZone:(CKRecordZone *)zone completionHandler:(void (^)(CKRecordZone * __nullable zone, NSError * __nullable error))completionHandler;
- (void)deleteRecordZoneWithID:(CKRecordZoneID *)zoneID completionHandler:(void (^)(CKRecordZoneID * __nullable zoneID, NSError * __nullable error))completionHandler;

#pragma mark Subscription Convenience Methods
/* CKFetchSubscriptionsOperation and CKModifySubscriptionsOperation are the more configurable,
 CKOperation-based alternative to these methods */
- (void)fetchSubscriptionWithID:(NSString *)subscriptionID completionHandler:(void (^)(CKSubscription * __nullable subscription, NSError * __nullable error))completionHandler;
- (void)fetchAllSubscriptionsWithCompletionHandler:(void (^)(NSArray <CKSubscription *> * __nullable subscriptions, NSError * __nullable error))completionHandler;
- (void)saveSubscription:(CKSubscription *)subscription completionHandler:(void (^)(CKSubscription * __nullable subscription, NSError * __nullable error))completionHandler;
- (void)deleteSubscriptionWithID:(NSString *)subscriptionID completionHandler:(void (^)(NSString * __nullable subscriptionID, NSError * __nullable error))completionHandler;

@end
NS_ASSUME_NONNULL_END
