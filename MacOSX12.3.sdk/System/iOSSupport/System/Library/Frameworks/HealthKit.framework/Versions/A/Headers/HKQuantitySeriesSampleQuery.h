//
//  HKQuantitySeriesSampleQuery.h
//  HealthKit
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;
@class HKQuantitySample;

/*!
 @class         HKQuantitySeriesSampleQuery
 @abstract      An HKQuantitySeriesSampleQuery is used to access series data associated with
                HKQuantitySample(s).
 @discussion    Once instantiated, call -[HKHealthStore executeQuery:] to begin enumerating
                the series data.
                Call -[HKHealthStore stopQuery:] to discontinue further quantity data reporting.
 */
HK_EXTERN
#if defined(__swift__) && __swift__
API_DEPRECATED("Use HKQuantitySeriesSampleQueryDescriptor", ios(12.0, API_TO_BE_DEPRECATED), watchos(5.0, API_TO_BE_DEPRECATED));
#else
API_AVAILABLE(ios(12.0), watchos(5.0))
#endif
@interface HKQuantitySeriesSampleQuery : HKQuery

/*!
 @property      includeSample
 @abstract      Include owning HKQuantitySample in quantityHandler handler.
 @discussion    Default value is NO.
                If includeSample is set then the quantitySample parameter of quantityHandler will
                be non-nil anytime the quantity parameter is non-nil.
                Specifying this option has a performance cost.
                This property may not be modified once the query has been executed.
 */
@property (nonatomic, assign) BOOL includeSample API_AVAILABLE(ios(13.0), watchos(6.0));

/*!
 @property      orderByQuantitySampleStartDate
 @abstract      Order enumerated results first by quantitySample.startDate,
                then by the quantity's dateInterval.startDate.
 @discussion    Default value is NO.
                All quantities owned by a given quantitySample will be
                enumerated before any quantities owned by any other quantity sample,
                and the quantity samples will be enumerated in their startDate order.
                Note that individual quantities may not be returned in their
                dateInterval.startDate order if more than one quantitySample overlap in time.
                This property may not be modified once the query has been executed.
 */
@property (nonatomic, assign) BOOL orderByQuantitySampleStartDate API_AVAILABLE(ios(13.0), watchos(6.0));

/*!
 @method        initWithSample:dataHandler:
 @abstract      Returns a query that will retrieve HKQuantity objects for samples of a specified
                type that match the specified predicate.
 
 @param         quantityType        The type of HKQuantitySample to retrieve.
 @param         predicate           The predicate which the query results should match.
                                    To query for the quantities for a specific quantity sample
                                    see: +[HKPredicates predicateForObjectWithUUID:]

 @param         quantityHandler     The block to invoke with results from the query. It will be
                                    called repeatedly with HKQuantity, and NSDateInterval objects in
                                    ascending dateInterval.startDate order, until all quantities are
                                    returned and the done parameter is YES
                                    or -[HKHealthStore stopQuery:] is called.
                                    The quantitySample parameter is nil unless includeSample is YES,
                                    in which case it will be the quantitySample which owns the current
                                    quantity anytime the quantity paramater is non-nil.
                                    The stopQuery call can be made within the quantityHandler block.
                                    Once done is YES, or stopQuery has been called, the query is
                                    complete and no more calls to quantityHandler will be made.
 */
- (instancetype)initWithQuantityType:(HKQuantityType *)quantityType
                           predicate:(nullable NSPredicate *)predicate
                     quantityHandler:(void(^)(HKQuantitySeriesSampleQuery *query, HKQuantity * _Nullable quantity, NSDateInterval * _Nullable dateInterval, __kindof HKQuantitySample * _Nullable quantitySample, BOOL done, NSError * _Nullable error))quantityHandler API_AVAILABLE(ios(13.0), watchos(6.0));

- (instancetype)initWithSample:(HKQuantitySample *)quantitySample
               quantityHandler:(void(^)(HKQuantitySeriesSampleQuery *query, HKQuantity * _Nullable quantity, NSDate * _Nullable date, BOOL done, NSError * _Nullable error))quantityHandler API_DEPRECATED_WITH_REPLACEMENT("initWithQuantityType:predicate:quantityHandler:", ios(12.0, 13.0), watchos(5.0, 6.0));

@end

NS_ASSUME_NONNULL_END
