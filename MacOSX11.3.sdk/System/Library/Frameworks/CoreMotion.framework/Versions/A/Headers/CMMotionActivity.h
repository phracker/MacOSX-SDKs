/*
 *  CMMotionActivity.h
 *  CoreMotion
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMLogItem.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMMotionActivityConfidence
 *
 *  Discussion:
 *    Enumerates the level of accuracy of the activity estimate.
 */
typedef NS_ENUM(NSInteger, CMMotionActivityConfidence) {
	CMMotionActivityConfidenceLow = 0,
	CMMotionActivityConfidenceMedium,
	CMMotionActivityConfidenceHigh
};

/*
 *  CMMotionActivity
 *
 *  Discussion:
 *    An estimate of the user's activity based on the motion of the device.
 *
 *    The activity is exposed as a set of properties, the properties are not
 *    mutually exclusive.
 *
 *    For example, if you're in a car stopped at a stop sign the state might
 *    look like:
 *       stationary = YES, walking = NO, running = NO, automotive = YES
 *
 *    Or a moving vehicle,
 *       stationary = NO, walking = NO, running = NO, automotive = YES
 *
 *    Or the device could be in motion but not walking or in a vehicle.
 *       stationary = NO, walking = NO, running = NO, automotive = NO.
 *    Note in this case all of the properties are NO.
 *
 */
COREMOTION_EXPORT API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(macos)
@interface CMMotionActivity : CMLogItem

/*
 *  confidence
 *
 *  Discussion:
 *    A confidence estimate associated with this state.
 *
 *    CoreMotion always provides the most likely state.  Confidence represents
 *    how likely that the state is to be correct.
 */
@property(readonly, nonatomic) CMMotionActivityConfidence confidence;

/*
 *  startDate
 *
 *  Discussion:
 *    Time at which the activity started.
 */
@property(readonly, nonatomic) NSDate *startDate;

/*
 *  unknown
 *
 *  Discussion:
 *    True if there is no estimate of the current state.  This can happen if
 *    the device was turned off.
 */
@property(readonly, nonatomic) BOOL unknown;

/*
 *  stationary
 *
 *  Discussion:
 *    True if the device is not moving.
 */
@property(readonly, nonatomic) BOOL stationary;

/*
 *  walking
 *
 *  Discussion:
 *    True if the device is on a walking person.
 */
@property(readonly, nonatomic) BOOL walking;

/*
 *  running
 *
 *  Discussion:
 *    True if the device is on a running person.
 */
@property(readonly, nonatomic) BOOL running;

/*
 *  automotive
 *
 *  Discussion:
 *    True if the device is in a vehicle.
 */
@property(readonly, nonatomic) BOOL automotive;

/*
 *  cycling
 *
 *  Discussion:
 *    True if the device is on a bicycle.
 */
@property(readonly, nonatomic) BOOL cycling COREMOTION_EXPORT API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END
