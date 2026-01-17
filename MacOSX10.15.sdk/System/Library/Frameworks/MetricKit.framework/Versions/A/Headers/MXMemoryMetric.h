//
//  MXMemoryMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetric.h>
#import <MetricKit/MXUnit.h>
#import <os/availability.h>
#import <MetricKit/MXAverage.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXMemoryMetric
 @abstract      An MXMetric subclass that encapsulates memory metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXMemoryMetric : MXMetric

/*!
 @property      peakMemoryUsage
 @abstract      A single value representing the peak memory consumption of the application.
 @discussion    Dimensioned as NSUnitInformationStorage.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *peakMemoryUsage;

/*!
 @property      averageSuspendedMemory
 @abstract      Average memory of the application upon suspend.
 @discussion    Dimensioned as NSUnitInformationStorage.
 */
@property (readonly, strong, nonnull) MXAverage<NSUnitInformationStorage *> *averageSuspendedMemory;

@end

NS_ASSUME_NONNULL_END
