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
API_AVAILABLE(ios(14.0), macos(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface MXAnimationMetric : MXMetric

/*!
 @property      scrollHitchTimeRatio
 @abstract      Ratio of time the application spent hitching while scrolling.
 @discussion    Scroll hitches are user perceptible animation issues that occur during scrolling.
 @discussion    This metric only applies to UIScrollViews.
 @discussion    Dimensionless.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnit *> *scrollHitchTimeRatio;

/*!
 @property      hitchTimeRatio
 @abstract      Ratio of time the application spent hitching during tracked animations.
 @discussion    Hitches are user perceptible frame delays that can occur during animations and scrolling.
 @discussion    This metric incorporates adjustments that optimize for user perception, and typically will be the most accurate representation of what hitches users experience during app usage.
 @discussion    This metric is normalized against total animation duration.
 @discussion    Many animations are tracked by default. You can track additional animations using the -[NSProcessInfo beginActivityWithOptions:reason:] method with the NSActivityAnimationTrackingEnabled option.
 @discussion    Dimensionless.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnit *> *hitchTimeRatio API_AVAILABLE(ios(26.0), macos(26.0)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END
