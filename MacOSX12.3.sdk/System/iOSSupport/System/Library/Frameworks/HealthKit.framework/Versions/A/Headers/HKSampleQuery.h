//
//  HKSampleQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKQuery.h>
#import <HealthKit/HKQueryDescriptor.h>

NS_ASSUME_NONNULL_BEGIN

// The query returns all samples that match the given sampleType and predicate.
static const NSUInteger HKObjectQueryNoLimit = 0;

/*!
 @class         HKSampleQuery
 @abstract      A concrete subclass of HKQuery that provides an interface to retrieve HKSample objects.
 */
HK_EXTERN
#if defined(__swift__) && __swift__
API_DEPRECATED("Use HKSampleQueryDescriptor", ios(8.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED));
#else
API_AVAILABLE(ios(8.0), watchos(2.0))
#endif
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

/*!
 @method        initWithQueryDescriptors:limit:resultsHandler:
 @abstract      Returns a query that will retrieve HKSamples matching any of the given queryDescriptors.
 
 @param         queryDescriptors          An array of query descriptors that describes the sample types and predicates
                                          used for querying.
 @param         limit                     The maximum number of samples to return. Pass HKObjectQueryNoLimit
                                          for no limit.
 @param         resultsHandler            The block to invoke with results when the query has finished executing. This
                                          block is invoked once with results, an array of HKSamples matching the
                                          queryDescriptors passed in, or nil if an error occurred.
 */
- (instancetype)initWithQueryDescriptors:(NSArray<HKQueryDescriptor *> *)queryDescriptors
                                   limit:(NSInteger)limit
                          resultsHandler:(void(^)(HKSampleQuery *query, NSArray<__kindof HKSample *> * _Nullable results, NSError * _Nullable error))resultsHandler API_AVAILABLE(ios(15.0), watchos(8.0));

/*!
 @method        initWithQueryDescriptors:limit:sortDescriptors:resultsHandler:
 @abstract      Returns a query that will retrieve HKSamples matching any of the given queryDescriptors.
 
 @param         queryDescriptors          An array of query descriptors that describes the sample types and predicates
                                          used for querying.
 @param         limit                     The maximum number of samples to return. Pass HKObjectQueryNoLimit
                                          for no limit.
 @param         sortDescriptors           The sort descriptors to use to order the resulting samples.
 @param         resultsHandler            The block to invoke with results when the query has finished executing. This
                                          block is invoked once with results, an array of HKSamples matching the
                                          queryDescriptors passed in, or nil if an error occurred. The HKSamples in the
                                          array are sorted by the specified sortDescriptors.
 */
- (instancetype)initWithQueryDescriptors:(NSArray<HKQueryDescriptor *> *)queryDescriptors
                                   limit:(NSInteger)limit
                         sortDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors
                          resultsHandler:(void(^)(HKSampleQuery *query, NSArray<__kindof HKSample *> * _Nullable results, NSError * _Nullable error))resultsHandler API_AVAILABLE(ios(15.0), watchos(8.0));
@end

NS_ASSUME_NONNULL_END
