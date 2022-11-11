//
//  HKStatisticsQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKQuery.h>
#import <HealthKit/HKStatistics.h>

NS_ASSUME_NONNULL_BEGIN

@class HKStatistics;

/*!
 @class     HKStatisticsQuery
 @abstract  Calculates statistics on quantity samples matching the given quantity type and predicate.
 */
HK_EXTERN
#if defined(__swift__) && __swift__
API_DEPRECATED("Use HKStatisticsQueryDescriptor", ios(8.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED));
#else
API_AVAILABLE(ios(8.0), watchos(2.0))
#endif
@interface HKStatisticsQuery : HKQuery

- (instancetype)initWithQuantityType:(HKQuantityType *)quantityType
             quantitySamplePredicate:(nullable NSPredicate *)quantitySamplePredicate
                             options:(HKStatisticsOptions)options
                   completionHandler:(void(^)(HKStatisticsQuery *query, HKStatistics * _Nullable result, NSError * _Nullable error))handler;

@end

NS_ASSUME_NONNULL_END
