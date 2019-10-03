//
//  HKSampleQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

// The query returns all samples that match the given sampleType and predicate.
static const NSUInteger HKObjectQueryNoLimit = 0;

/*!
 @class         HKSampleQuery
 @abstract      A concrete subclass of HKQuery that provides an interface to retrieve HKSample objects.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKSampleQuery : HKQuery

/*!
 @property      limit
 @abstract      The maximum number of results the receiver will return upon completion.
 */
@property (readonly) NSUInteger limit;

/*!
 @property      sortDescriptors
 @abstract      An array of NSSortDescriptors.
 */
@property (readonly, copy, nullable) NSArray<NSSortDescriptor *> *sortDescriptors;

/*!
 @method        initWithSampleType:predicate:limit:sortDescriptors:resultsHandler:
 @abstract      Returns a query that will retrieve HKSamples matching the given predicate.
 
 @param         sampleType      The type of sample to retrieve.
 @param         predicate       The predicate which samples should match.
 @param         limit           The maximum number of samples to return.  Pass HKObjectQueryNoLimit for no limit.
 @param         sortDescriptors The sort descriptors to use to order the resulting samples.
 @param         resultsHandler  The block to invoke with results when the query has finished executing.
 */
- (instancetype)initWithSampleType:(HKSampleType *)sampleType
                         predicate:(nullable NSPredicate *)predicate
                             limit:(NSUInteger)limit
                   sortDescriptors:(nullable NSArray<NSSortDescriptor *> *)sortDescriptors
                    resultsHandler:(void(^)(HKSampleQuery *query, NSArray<__kindof HKSample *> * _Nullable results, NSError * _Nullable error))resultsHandler;


@end

NS_ASSUME_NONNULL_END
