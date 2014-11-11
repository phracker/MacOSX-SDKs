//
//  CKDatabase.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKDatabaseOperation, CKRecord, CKRecordID, CKRecordZone, CKRecordZoneID, CKQuery, CKSubscription;

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
*/
- (void)fetchRecordWithID:(CKRecordID *)recordID completionHandler:(void (^)(CKRecord *record, NSError *error))completionHandler;
- (void)saveRecord:(CKRecord *)record completionHandler:(void (^)(CKRecord *record, NSError *error))completionHandler;
- (void)deleteRecordWithID:(CKRecordID *)recordID completionHandler:(void (^)(CKRecordID *recordID, NSError *error))completionHandler;

- (void)performQuery:(CKQuery *)query inZoneWithID:(CKRecordZoneID *)zoneID completionHandler:(void (^)(NSArray /* CKRecord */ *results, NSError *error))completionHandler;

- (void)fetchAllRecordZonesWithCompletionHandler:(void (^)(NSArray /* CKRecordZone */ *zones, NSError *error))completionHandler;
- (void)fetchRecordZoneWithID:(CKRecordZoneID *)zoneID completionHandler:(void (^)(CKRecordZone *zone, NSError *error))completionHandler;
- (void)saveRecordZone:(CKRecordZone *)zone completionHandler:(void (^)(CKRecordZone *zone, NSError *error))completionHandler;
- (void)deleteRecordZoneWithID:(CKRecordZoneID *)zoneID completionHandler:(void (^)(CKRecordZoneID *zoneID, NSError *error))completionHandler;

- (void)fetchSubscriptionWithID:(NSString *)subscriptionID completionHandler:(void (^)(CKSubscription *subscription, NSError *error))completionHandler;
- (void)fetchAllSubscriptionsWithCompletionHandler:(void (^)(NSArray /* CKSubscription */ *subscriptions, NSError *error))completionHandler;
- (void)saveSubscription:(CKSubscription *)subscription completionHandler:(void (^)(CKSubscription *subscription, NSError *error))completionHandler;
- (void)deleteSubscriptionWithID:(NSString *)subscriptionID completionHandler:(void (^)(NSString *subscriptionID, NSError *error))completionHandler;

@end
