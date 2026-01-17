//
//  MXLocationActivityMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetric.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXLocationActivityMetric
 @abstract      An MXMetric subclass that encapsulates location metrics
 @discussion    The metrics contained in this class describe properties of location activity. See MXAppRunTimeMetric for time spent performing location activities.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXLocationActivityMetric : MXMetric

/*!
 @property      cumulativeBestAccuracyTime
 @abstract      Cumulative time spent acquiring location at kCLLocationAccuracyBest.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeBestAccuracyTime;

/*!
 @property      cumulativeBestAccuracyForNavigationTime
 @abstract      Cumulative time spent acquiring location at kCLLocationAccuracyBestForNavigation.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeBestAccuracyForNavigationTime;

/*!
 @property      cumulativeNearestTenMetersAccuracyTime
 @abstract      Cumulative time spent acquiring location at kCLLocationAccuracyNearestTenMeters.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeNearestTenMetersAccuracyTime;

/*!
 @property      cumulativeHundredMetersAccuracyTime
 @abstract      Cumulative time spent acquiring location at kCLLocationAccuracyHundredMeters.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeHundredMetersAccuracyTime;

/*!
 @property      cumulativeKilometerAccuracyTime
 @abstract      Cumulative time spent acquiring location at kCLLocationAccuracyKilometer.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeKilometerAccuracyTime;

/*!
 @property      cumulativeThreeKilometersAccuracyTime
 @abstract      Cumulative time spent acquiring location at kCLLocationAccuracyThreeKilometers.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeThreeKilometersAccuracyTime;

@end

NS_ASSUME_NONNULL_END
