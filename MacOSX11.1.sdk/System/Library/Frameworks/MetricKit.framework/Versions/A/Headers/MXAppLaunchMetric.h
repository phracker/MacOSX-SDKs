//
//  MXAppLaunchMetric.h
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
 @class         MXAppLaunchMetric
 @abstract      An MXMetric subclass that encapsulates app launch metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXAppLaunchMetric : MXMetric

/*!
 @property      histogrammedTimeToFirstDraw
 @abstract      Histogrammed application time-to-first-draw data.
 @discussion    Dimensioned as NSUnitDuration.
 @discussion    This represents the time when the first CA commit is finished.
 */
@property (readonly, strong, nonnull) MXHistogram<NSUnitDuration *> *histogrammedTimeToFirstDraw;

/*!
 @property      histogrammedApplicationResumeTime
 @abstract      Histogrammed application resume time data.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) MXHistogram<NSUnitDuration *> *histogrammedApplicationResumeTime;

@end

NS_ASSUME_NONNULL_END
