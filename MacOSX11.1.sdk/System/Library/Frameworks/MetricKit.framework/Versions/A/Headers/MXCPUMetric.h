//
//  MXCPUMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <MetricKit/MXMetric.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXCPUMetric
 @abstract      An MXMetric subclass that encapsulates CPU metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXCPUMetric : MXMetric

/*!
 @property      cumulativeCPUTime
 @abstract      CPU time aggregated cumulatively.
 @discussion    The data here represents the total CPU time an application consumed over the date range of the containing payload.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeCPUTime;

/*!
 @property      cumulativeCPUInstructions
 @abstract      CPU instructions retired aggregated cumulatively.
 @discussion    The data here represents the total number of CPU instructions an application retired over the date range of the containing payload.
 @discussion    Dimensionless.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnit *> *cumulativeCPUInstructions API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos, watchos);

@end

NS_ASSUME_NONNULL_END
