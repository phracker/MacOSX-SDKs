//
//  MXAppTimeMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <MetricKit/MXMetric.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXAppRunTimeMetric
 @abstract      An MXMetric subclass that encapsulates app runtime metrics.
 @discussion    Runtime metrics describe application time spent running in different modes, such as audio, location, etc.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXAppRunTimeMetric : MXMetric

/*!
 @property      cumulativeForegroundTime
 @abstract      Cumulative application foreground time.
 @discussion    Time spent on screen and visible to the user.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeForegroundTime;

/*!
 @property      cumulativeBackgroundTime
 @abstract      Cumulative application background time.
 @discussion    Time spent off screen and in the background, invisible to the user.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeBackgroundTime;

/*!
 @property      cumulativeBackgroundAudioTime
 @abstract      Cumulative time the application spent running in the background to play audio
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeBackgroundAudioTime;

/*!
 @property      cumulativeBackgroundLocationTime
 @abstract      Cumulative time the application spent running in the background to acquire or process location.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeBackgroundLocationTime;

@end

NS_ASSUME_NONNULL_END
