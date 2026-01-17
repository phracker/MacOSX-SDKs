//
//  MXAverage.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXAverage
 @abstract      A class representing metric data that is averaged.
 */
API_AVAILABLE(ios(13.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos)
@interface MXAverage<UnitType: NSUnit *> : NSObject <NSSecureCoding>

/*!
 @property      averageMeasurement
 @abstract      An NSMeasurement that contains the average measurement.
 */
@property (readonly, strong, nonnull) NSMeasurement<UnitType> *averageMeasurement;

/*!
 @property      sampleCount
 @abstract      An NSInteger representation of the number of samples in the distribution used to formulate the average.
 @discussion    This value is negative if an unknown number of samples was used to compute the average.
 */
@property (readonly) NSInteger sampleCount;


/*!
 @property      standardDeviation
 @abstract      An double representation of the standard deviation of the distribution.
 @discussion    This value is negative an unknown number of samples was used to compute the standard deviation.
 */
@property (readonly) double standardDeviation;



@end

NS_ASSUME_NONNULL_END
