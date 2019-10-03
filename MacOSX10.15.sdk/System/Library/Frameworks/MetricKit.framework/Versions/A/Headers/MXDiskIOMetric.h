//
//  MXDiskIOMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetric.h>
#import <MetricKit/MXUnit.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXDiskIOMetric
 @abstract      An MXMetric subclass that encapsulates disk IO metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXDiskIOMetric : MXMetric

/*!
 @property      cumulativeLogicalWrites
 @abstract      Cumulative amount of logical writes.
 @discussion    Dimensioned as NSUnitInformationStorage.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *cumulativeLogicalWrites;

@end

NS_ASSUME_NONNULL_END
