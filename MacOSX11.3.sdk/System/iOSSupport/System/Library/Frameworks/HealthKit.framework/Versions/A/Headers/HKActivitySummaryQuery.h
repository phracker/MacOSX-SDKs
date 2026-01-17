//
//  HKActivitySummaryQuery.h
//  HealthKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <HealthKit/HKQuery.h>

@class HKActivitySummary;

NS_ASSUME_NONNULL_BEGIN

HK_EXTERN API_AVAILABLE(ios(9.3), watchos(2.2))
@interface HKActivitySummaryQuery : HKQuery

/**
  @property      updateHandler
  @abstract      An optional handler to be called when activity summaries matching the given predicate are updated.
  @discussion    This property may not be modified once the query has been executed. If this property is nonnull, then
                 the query must be manually stopped.
  */
@property (nonatomic, copy, nullable) void(^updateHandler)(HKActivitySummaryQuery *query, NSArray<HKActivitySummary *> * _Nullable updatedActivitySummaries, NSError * _Nullable error);

/*!
  @method        initWithPredicate:resultsHandler:
  @abstract      Returns a query that will retrieve HKActivitySummaries matching the given predicate.
  @discussion    If no updateHandler is set on the query, the query will automatically stop after calling resultsHandler.
                 Otherwise, the query continues to run and calls the updateHandler as HKActivitySummaries matching the
                 predicate are updated.
  
  @param         predicate  The predicate which HKActivitySummaries should match.
  @param         handler    The block to invoke with results when the query has finished.
  */
- (instancetype)initWithPredicate:(nullable NSPredicate *)predicate
                   resultsHandler:(void(^)(HKActivitySummaryQuery *query, NSArray<HKActivitySummary *> * _Nullable activitySummaries, NSError * _Nullable error))handler;

@end

NS_ASSUME_NONNULL_END
