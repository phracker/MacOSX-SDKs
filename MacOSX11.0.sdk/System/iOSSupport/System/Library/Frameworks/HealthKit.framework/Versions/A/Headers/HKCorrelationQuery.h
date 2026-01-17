//
//  HKCorrelationQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

@class HKCorrelationType;
@class HKCorrelation;

/*!
 @class         HKCorrelationQuery
 @abstract      A query to find HKCorrelations
 @discussion    Correlations are HKSamples that contain a set of correlated samples. HKCorrelationQuery
                accepts a predicate to filter HKCorrelations and a dictionary of predicates to filter the
                correlated samples.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKCorrelationQuery : HKQuery

@property (readonly, copy) HKCorrelationType *correlationType;
/*!
 @property      samplePredicates
 @abstract      A dictionary of predicates for the HKCorrelation's objects
 @discussion    samplePredicates maps HKSampleTypes to NSPredicates. The predicate value will apply
                to objects of the key type. 
 
 */
@property (readonly, copy, nullable) NSDictionary<__kindof HKSampleType *, NSPredicate *> *samplePredicates;

/*!
 @method    initWithTypes:predicate:samplePredicate:completion:
 @abstract  The designated initializer for HKCorrelationQuery.

 @param     correlationType     The type of correlation that is being queried for

 @param     predicate           The predicate for scoping which HKCorrelations are returned

 @param     samplePredicates    A dictionary mapping HKSampleTypes to NSPredicates. If no predicate for a particular type
                                is provided, it is assumed to be a nil predicate and objects of that type will not be
                                filtered.
 */
- (instancetype)initWithType:(HKCorrelationType *)correlationType
                   predicate:(nullable NSPredicate *)predicate
            samplePredicates:(nullable NSDictionary<HKSampleType *, NSPredicate *> *)samplePredicates
                  completion:(void(^)(HKCorrelationQuery *query, NSArray<HKCorrelation *> * _Nullable correlations, NSError * _Nullable error))completion;
@end

NS_ASSUME_NONNULL_END
