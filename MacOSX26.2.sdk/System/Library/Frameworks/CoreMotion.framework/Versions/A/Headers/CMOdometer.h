/*
 *  CMOdometer.h
 *  CoreMotion
 *
 *  Copyright (c) 2022 Apple Inc. All rights reserved.
 *
 */

#ifndef CMOdometer_h
#define CMOdometer_h
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreMotion/CMAvailability.h>


NS_ASSUME_NONNULL_BEGIN

/*
 *	CMOdometerOriginDevice
 *
 *  Discussion:
 * 		  The device from which the odometer sample originates
 */
typedef NS_ENUM(NSInteger, CMOdometerOriginDevice) {
	/*
	 *  The origin of the odometer sample is unknown; it could be either local or remote.
	 */
	CMOdometerOriginDeviceUnknown = 0,

	/*
	 *  The odometer sample originated locally (i.e. the same device requesting the sample).
	 */
	CMOdometerOriginDeviceLocal,

	/* 
	 *  The odometer sample originated on a paired device different to the local device.
	 */
	CMOdometerOriginDeviceRemote
} API_AVAILABLE(ios(15.4), watchos(8.4));

/*
 *  CMOdometerData
 *
 *  Discussion:
 *      An encapsulated odometer update for workouts.
 */
COREMOTION_EXPORT API_AVAILABLE(ios(8.0), watchos(1.0)) NS_SWIFT_SENDABLE
@interface CMOdometerData : NSObject <NSSecureCoding, NSCopying>
/*
 *  startDate
 *
 *  Discussion:
 *      The start time for the odometer data.
 */
@property(strong, readonly, nonatomic) NSDate *startDate;
/*
 *  endDate
 *
 *  Discussion:
 *      The end time for the odometer data.
 */
@property(strong, readonly, nonatomic) NSDate *endDate;
/*
 *	deltaDistance
 *
 *	Discussion:
 * 		The change in distance traveled since the last location, measured in meters.
 */
@property(readonly, nonatomic)  CLLocationDistance deltaDistance API_AVAILABLE(ios(17.0), watchos(10.0));
/*
 *	deltaDistanceAccuracy
 *
 *	Discussion:
 * 		Uncertainty in the estimated delta distance in meters.
 */
@property(readonly, nonatomic) CLLocationAccuracy deltaDistanceAccuracy API_AVAILABLE(ios(17.0), watchos(10.0));
/*
 *	speed
 *
 *	Discussion:
 * 		The instantaneous speed of the device, measured in meters per second.
 */
@property(readonly, nonatomic) CLLocationSpeed speed API_AVAILABLE(ios(17.0), watchos(10.0));
/*
 *	speedAccuracy
 *
 *	Discussion:
 * 		The accuracy of the speed value, measured in meters per second.
 *      When this property contains 0 or a positive number, the value in the speed property is plus or minus the specified number of meters per second. When this property contains a negative number, the value in the speed property is invalid.
 */
@property(readonly, nonatomic) CLLocationSpeedAccuracy speedAccuracy API_AVAILABLE(ios(17.0), watchos(10.0));
/*
 *	gpsDate
 *
 *	Discussion:
 * 		Timestamp corresponding to the GPS measurement
 */
@property(strong, nonatomic, readonly) NSDate *gpsDate API_AVAILABLE(ios(17.0), watchos(10.0));
/*
 *	deltaAltitude
 *
 *	Discussion:
 * 		The change in altitude above mean sea level associated with a location, measured in meters.
 */
@property(readonly, nonatomic)  CLLocationDistance deltaAltitude API_AVAILABLE(ios(17.0), watchos(10.0));
/*
 *	verticalAccuracy
 *
 *	Discussion:
 * 		The validity of the altitude values, and their estimated uncertainty, measured in meters.
 */
@property(readonly, nonatomic) CLLocationAccuracy verticalAccuracy API_AVAILABLE(ios(17.0), watchos(10.0));
/*
 *	originDevice
 *
 *	Discussion:
 * 		The device from which this measurement comes from
 */
@property(readonly, assign, nonatomic) CMOdometerOriginDevice originDevice API_AVAILABLE(ios(15.4), watchos(8.4));
/*
 *	slope
 *
 *	Discussion:
 * 		The slope at the current location towards the direction of travel measured in degrees.
 *      nil if the measurement is invalid.
 */
@property(strong, nonatomic, readonly, nullable) NSNumber *slope NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(17.0), watchos(10.0));
/*
 *	maxAbsSlope
 *
 *	Discussion:
 * 		The maximum absolute slope at current location towards all directions measured in degrees.
 *      nil if invalid due to low GPS accuracy.
 */
@property(strong, nonatomic, readonly, nullable) NSNumber *maxAbsSlope NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(17.0), watchos(10.0));


@end

NS_ASSUME_NONNULL_END




#endif /* CMOdometer_h */
