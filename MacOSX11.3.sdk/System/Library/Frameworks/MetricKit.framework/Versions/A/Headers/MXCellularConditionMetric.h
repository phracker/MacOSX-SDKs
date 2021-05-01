//
//  MXCellConditionMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <MetricKit/MXMetric.h>
#import <MetricKit/MXUnit.h>
#import <MetricKit/MXHistogram.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXCellConditionMetric
 @abstract      An MXMetric subclass that encapsulates cellular condition metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXCellularConditionMetric : MXMetric

/*!
 @property      cellularConditionTime
 @abstract      Application run time bucketized by cellular condition.
 @discussion    This data represents the percentage of time an application spent running in different cellular conditions.
 @discussion    In the event that no data for any buckets is available, the histogram data will be empty.
 @discussion    Dimensioned as MXUnitSignalBars.
 */
@property (readonly, strong, nonnull) MXHistogram<MXUnitSignalBars *> *histogrammedCellularConditionTime;

@end

NS_ASSUME_NONNULL_END
