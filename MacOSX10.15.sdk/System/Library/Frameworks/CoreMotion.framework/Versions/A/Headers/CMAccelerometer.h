/*
 *  CMAccelerometer.h
 *  CoreMotion
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMLogItem.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMAcceleration
 *  
 *  Discussion:
 *    A structure containing 3-axis acceleration data.
 *
 *  Fields:
 *    x:
 *      X-axis acceleration in G's.
 *    y:
 *      Y-axis acceleration in G's.
 *		z:
 *			Z-axis acceleration in G's.
 */
typedef struct {
	double x;
	double y;
	double z;
} CMAcceleration;

/*
 *  CMAccelerometerData
 *  
 *  Discussion:
 *    Contains a single accelerometer measurement.
 *
 */
COREMOTION_EXPORT API_AVAILABLE(ios(4.0)) API_UNAVAILABLE(tvos)
@interface CMAccelerometerData : CMLogItem
{
@private
	id _internal;
}

/*
 *  acceleration
 *  
 *  Discussion:
 *    The acceleration measured by the accelerometer.
 *
 */
@property(readonly, nonatomic) CMAcceleration acceleration;

@end

NS_ASSUME_NONNULL_END
