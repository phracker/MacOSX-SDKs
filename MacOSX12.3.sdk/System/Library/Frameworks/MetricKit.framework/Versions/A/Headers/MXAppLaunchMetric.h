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

/*!
@property      histogrammedOptimizedTimeToFirstDraw
@abstract      Histogrammed optimized application time-to-first-draw data.
@discussion    Dimensioned as NSUnitDuration.
@discussion    This represents the time when the first CA commit is finished where the application launch has been optimized by the system.
@discussion    In iOS 15, the system will opportunistically start applications that are not running in the background to reduce the amount of time a user may have to wait before an application is usable. These launches can occur after a system reboot and periodically as system conditions allow.
*/
@property (readonly, strong, nonnull) MXHistogram<NSUnitDuration *> *histogrammedOptimizedTimeToFirstDraw API_AVAILABLE(ios(15.2)) API_UNAVAILABLE(macos, tvos, watchos);

@end

NS_ASSUME_NONNULL_END
