//
//  HKVerifiableClinicalRecordQuery.h
//  HealthKit
//
//  Copyright © 2021 Apple. All rights reserved.
//

#import <HealthKit/HKQuery.h>
#import <HealthKit/HKVerifiableClinicalRecord.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKVerifiableClinicalRecordQuery
 @abstract      A one-time share query that returns user-selected verifiable clinical records.
 */
HK_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos)
@interface HKVerifiableClinicalRecordQuery : HKQuery

/*!
 @property      recordTypes
 @abstract      The record types that need to be present on desired records.
 */
@property (readonly, copy) NSArray<NSString *> *recordTypes;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 @method        initWithRecordTypes:predicate:resultsHandler:
 @abstract      Returns an one-time query that will ask for access to verifiable clinical records that match the query.
 
 @param         recordTypes     The record types that need to be present on a verifiable clinical record.
 @param         predicate       The predicate which records should match.
 @param         resultsHandler  The block to invoke with the verifiable clinical records from the query.
*/
- (instancetype)initWithRecordTypes:(NSArray<NSString *> *)recordTypes
                          predicate:(nullable NSPredicate *)predicate
                     resultsHandler:(void(^)(HKVerifiableClinicalRecordQuery *query,
                                             NSArray<HKVerifiableClinicalRecord *> * _Nullable records,
                                             NSError * _Nullable error))resultsHandler;

@end

NS_ASSUME_NONNULL_END
