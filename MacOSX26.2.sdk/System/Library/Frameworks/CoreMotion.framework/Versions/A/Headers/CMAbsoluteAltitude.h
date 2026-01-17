/*
*  CMAbsoluteAltitude.h
*  CoreMotion
*
*  Copyright (c) 2020 Apple Inc. All rights reserved.
*
*/

#import <Foundation/Foundation.h>
#import <CoreMotion/CMLogItem.h>
#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

COREMOTION_EXPORT
API_AVAILABLE(ios(15.0), watchos(8.0)) API_UNAVAILABLE(macos, tvos)
@interface CMAbsoluteAltitudeData : CMLogItem

/*
 *  altitude
 *
 *  Discussion:
 *    The absolute altitude of the device in meters relative to sea level; could be positive or negative.
 *
 */
@property(readonly, nonatomic) double altitude;

/*
 *  accuracy
 *
 *  Discussion:
 *    The accuracy of the altitude estimate, in meters.
 *
 */
@property(readonly, nonatomic) double accuracy;

/*
 *  precision
 *
 *  Discussion:
 *    The precision of the altitude estimate, in meters.
 *
 */
@property(readonly, nonatomic) double precision;

@end

NS_ASSUME_NONNULL_END
