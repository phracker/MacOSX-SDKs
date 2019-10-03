//
//  MXDisplayMetric.h
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
 @class         MXDisplayMetric
 @abstract      An MXMetric subclass that encapsulates display metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXDisplayMetric : MXMetric

/*!
 @property      averagePixelLuminance
 @abstract      Average Pixel Luminance for the application.
 @discussion    APL data ranges from 0-100, in increments of 1.
 @discussion    This value is null when the device does not support APL.
 @discussion    Dimensioned as MXUnitAveragePixelLuminance.
 */
@property (readonly, strong, nullable) MXAverage<MXUnitAveragePixelLuminance *> *averagePixelLuminance;

@end

NS_ASSUME_NONNULL_END
