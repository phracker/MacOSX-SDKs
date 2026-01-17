//
//  MXAnimationMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetric.h>
#import <os/availability.h>
#import <MetricKit/MXAverage.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXAnimationMetric
 @abstract      An MXMetric subclass that encapsulates app animation metrics.
 */
API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXAnimationMetric : MXMetric

/*!
 @property      scrollHitchTimeRatio
 @abstract      Ratio of time the application spent hitching while scrolling.
 @discussion    Scroll hitches are user perceptible animation issues that occur during scrolling.
 @discussion    This metric only applies to UIScrollViews.
 @discussion    Dimensionless.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnit *> *scrollHitchTimeRatio;

@end

NS_ASSUME_NONNULL_END
