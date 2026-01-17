//
//  MXGPUMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <MetricKit/MXMetric.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXGPUMetric
 @abstract      An MXMetric subclass that encapsulates GPU metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXGPUMetric : MXMetric

/*!
 @property      cumulativeGPUTime
 @abstract      GPU time aggregated cumulatively.
 @discussion    The data here represents the total GPU time an application consumed over the date range of the containing payload.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeGPUTime;

@end

NS_ASSUME_NONNULL_END
