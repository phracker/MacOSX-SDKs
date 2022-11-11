//
//  MXAppResponsivenessMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetric.h>
#import <os/availability.h>
#import <MetricKit/MXHistogram.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXAppResponsivenessMetric
 @abstract      An MXMetric subclass that encapsulates app responsiveness metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXAppResponsivenessMetric : MXMetric

/*!
 @property      histogrammedApplicationHangTime
 @abstract      Histogrammed app hang time data.
 @discussion    Applications are considered to be "hanging" when they are unable to handle user input responsively.
 @discussion    The durations for periods of hangs will be reported in the histogram returned here.
 @discussion    Application hang times that exceeds 9 seconds of wall clock time are reported in the final bucket of the histogram.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) MXHistogram<NSUnitDuration *> *histogrammedApplicationHangTime;

@end

NS_ASSUME_NONNULL_END
