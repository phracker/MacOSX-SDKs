//
//  MXUnit.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXUnitSignalBars
 @abstract      An NSUnit subclass representing the number of signal bars for signal strength.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXUnitSignalBars : NSDimension
/*
 Base unit - bars
 */
@property (class, readonly, copy) MXUnitSignalBars *bars;
@end

/*!
 @class         MXUnitAveragePixelLuminance
 @abstract      An NSUnit subclass representing the linear space Display APL.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXUnitAveragePixelLuminance : NSDimension
/*
 Base unit - apl
 */
@property (class, readonly, copy) MXUnitAveragePixelLuminance *apl;
@end

NS_ASSUME_NONNULL_END
