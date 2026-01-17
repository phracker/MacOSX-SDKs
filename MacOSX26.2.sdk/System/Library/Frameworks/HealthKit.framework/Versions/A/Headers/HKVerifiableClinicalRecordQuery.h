//
//  HKVerifiableClinicalRecordQuery.h
//  HealthKit
//
//  Copyright © 2021-2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKQuery.h>
#import <HealthKit/HKVerifiableClinicalRecord.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKVerifiableClinicalRecordQuery
 @abstract      A one-time share query that returns user-selected verifiable clinical records.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
#if defined(__swift__) && __swift__
API_DEPRECATED("Use HKVerifiableClinicalRecordQueryDescriptor", ios(15.0, API_TO_BE_DEPRECATED));
#else
API_AVAILABLE(ios(15.0), macCatalyst(15.0), macos(13.0))
#endif
API_UNAVAILABLE(watchos)
@interface HKVerifiableClinicalRecordQuery : HKQuery

/*!
 @property      recordTypes
 @abstract      The record types that need to be present on desired records.
 */
@property (readonly, copy) NSArray<NSString *> *recordTypes;

/*!
 @property      sourceTypes
 @abstract      The source type(s) of the records.
 */
@property (readonly, copy) NSArray<HKVerifiableClinicalRecordSourceType> *sourceTypes API_AVAILABLE(ios(15.4), macCatalyst(15.4), macos(13.0));

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
                     resultsHandler:(void(^NS_SWIFT_SENDABLE)(HKVerifiableClinicalRecordQuery *query,
                                             NSArray<HKVerifiableClinicalRecord *> * _Nullable records,
                                             NSError * _Nullable error))resultsHandler;

/*!
 @method        initWithRecordTypes:sourceTypes:predicate:resultsHandler:
 @abstract      Returns a one-time query that will ask for access to and return verifiable clinical records that match the query.
 
 @param         recordTypes     The record types that need to be present on a verifiable clinical record.
 @param         sourceTypes     The source type(s) of the records.
 @param         predicate       The predicate which records should match.
 @param         resultsHandler  The block to invoke with the verifiable clinical records from the query.
 */
- (instancetype)initWithRecordTypes:(NSArray<NSString *> *)recordTypes
                        sourceTypes:(NSArray<HKVerifiableClinicalRecordSourceType> *)sourceTypes
                          predicate:(nullable NSPredicate *)predicate
                     resultsHandler:(void(^NS_SWIFT_SENDABLE)(HKVerifiableClinicalRecordQuery *query,
                                             NSArray<HKVerifiableClinicalRecord *> * _Nullable records,
                                             NSError * _Nullable error))resultsHandler API_AVAILABLE(ios(15.4), macCatalyst(15.4), macos(13.0));

@end

NS_ASSUME_NONNULL_END
