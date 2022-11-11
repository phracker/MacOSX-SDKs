//
//  HKStatisticsCollectionQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKStatistics.h>
#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

@class HKStatistics;

HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKStatisticsCollection : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 @method        statisticsForDate:
 @abstract      Returns the statistics object that this date is inside of
 @discussion    If there are no samples for the given date, an HKStatistics instance with nil quantities will be returned.
 */
- (nullable HKStatistics *)statisticsForDate:(NSDate *)date;

/*!
 @method        enumerateStatisticsFromDate:toDate:withBlock:
 @abstract      Enumerates all statistics objects from startDate to endDate.
 @discussion    Statistics objects will be enumerated in chronological order. If there are no samples for an interval
                between the start and end date, then the HKStatistics object for that interval will have nil quantities.
 */
- (void)enumerateStatisticsFromDate:(NSDate *)startDate toDate:(NSDate *)endDate withBlock:(void(^)(HKStatistics *result, BOOL *stop))block;

/*!
 @method        statistics
 @abstract      Returns a copy of the populated statistics objects.
 @discussion    The statistics objects are ordered chronologically.
 */
- (NSArray<HKStatistics *> *)statistics;

/*!
 @method        sources
 @abstract      Returns all HKSources found in the contained HKStatistics objects.
 @discussion    Sources will be empty unless HKStatisticsOptionSeparateBySource is specified in the
                HKStatisticsCollectionQuery options.
 */
- (NSSet<HKSource *> *)sources;

@end

HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKStatisticsCollectionQuery : HKQuery

@property (readonly, strong) NSDate *anchorDate;
@property (readonly) HKStatisticsOptions options;
@property (readonly, copy) NSDateComponents *intervalComponents;

@property (nonatomic, copy, nullable) void(^initialResultsHandler)(HKStatisticsCollectionQuery *query, HKStatisticsCollection * _Nullable result, NSError * _Nullable error);
@property (nonatomic, copy, nullable) void(^statisticsUpdateHandler)(HKStatisticsCollectionQuery *query, HKStatistics * _Nullable statistics, HKStatisticsCollection * _Nullable collection, NSError * _Nullable error);

- (instancetype)initWithQuantityType:(HKQuantityType *)quantityType
             quantitySamplePredicate:(nullable NSPredicate *)quantitySamplePredicate
                             options:(HKStatisticsOptions)options
                          anchorDate:(NSDate *)anchorDate
                  intervalComponents:(NSDateComponents *)intervalComponents;

@end

NS_ASSUME_NONNULL_END
