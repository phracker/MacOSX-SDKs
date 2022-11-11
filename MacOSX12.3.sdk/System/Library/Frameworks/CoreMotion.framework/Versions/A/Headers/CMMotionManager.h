/*
 *  CMMotionManager.h
 *  CoreMotion
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

#import <CoreMotion/CMAccelerometer.h>
#import <CoreMotion/CMGyro.h>
#import <CoreMotion/CMDeviceMotion.h>
#import <CoreMotion/CMMagnetometer.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * There are two methods to receive data from CMMotionManager: push and pull.
 *
 * Before using either method, be sure to set the update interval property
 * appropriate to the type of data you're interested in. These properties are:
 * accelerometerUpdateInterval, gyroUpdateInterval, and deviceMotionUpdateInterval.
 *
 * To use the pull method, simply call startAccelerometerUpdates, startGyroUpdates,
 * and/or startDeviceMotionUpdates, depending on the type of data desired. Then,
 * whenever a new sample of data is desired, simply examine the appropriate
 * CMMotionManager property (accelerometerData, gyroData, or deviceMotion).
 *
 * To use the push method, simply call startAccelerometerUpdatesToQueue:withHandler:,
 * startGyroUpdatesToQueue:withHandler:, and/or
 * startDeviceMotionUpdatesToQueue:withHandler:, depending on the type of data
 * desired. You'll need to pass an NSOperationQueue and block to each call. When a new sample of
 * data arrives, a new instance of the block will be added to the appropriate NSOperationQueue.
 * When you stop the updates (see below), all operations in the given NSOperationQueue will be
 * cancelled, so it is recommended to pass CMMotionManager a queue that will not be used in other
 * contexts.
 *
 * Regardless of whether you used push or pull, when you're done, be sure to call the stop method
 * appropriate for the type of updates you started.  These methods are: stopAccelerometerUpdates,
 * stopGyroUpdates, and stopDeviceMotionUpdates.
 *
 */

/*
 *  CMAccelerometerHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when accelerometer data is available.
 */
typedef void (^CMAccelerometerHandler)(CMAccelerometerData * __nullable accelerometerData, NSError * __nullable error) API_UNAVAILABLE(tvos);

/*
 *  CMGyroHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when gyro data is available.
 */
typedef void (^CMGyroHandler)(CMGyroData * __nullable gyroData, NSError * __nullable error) API_UNAVAILABLE(tvos);

/*
 *  CMDeviceMotionHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when device motion data is available.
 */
typedef void (^CMDeviceMotionHandler)(CMDeviceMotion * __nullable motion, NSError * __nullable error) API_UNAVAILABLE(tvos);

/*
 *  CMMagnetometerHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when magnetometer data is available.
 */
typedef void (^CMMagnetometerHandler)(CMMagnetometerData * __nullable magnetometerData, NSError * __nullable error) COREMOTION_EXPORT API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos);

/*
 *  CMMotionManager
 *
 *  Discussion:
 *    The CMMotionManager object is your entry point to the motion service.
 */
COREMOTION_EXPORT API_AVAILABLE(ios(4.0)) API_UNAVAILABLE(macos)
@interface CMMotionManager : NSObject
{
@private
	id _internal;
}

/*
 *  accelerometerUpdateInterval
 *
 *  Discussion:
 *    The interval at which to deliver accelerometer data to the specified
 *    handler once startAccelerometerUpdatesToQueue:withHandler: is called.
 *    The units are in seconds. The value of this property is capped to
 *    certain minimum and maximum values. The maximum value is determined by
 *    the maximum frequency supported by the hardware. If sensitive to the
 *    interval of acceleration data, an application should always check the
 *    timestamps on the delivered CMAcceleration instances to determine the
 *    true update interval.
 */
@property(assign, nonatomic) NSTimeInterval accelerometerUpdateInterval API_UNAVAILABLE(tvos);

/*
 *  accelerometerAvailable
 *
 *  Discussion:
 *    Determines whether accelerometer is available.
 */
@property(readonly, nonatomic, getter=isAccelerometerAvailable) BOOL accelerometerAvailable API_UNAVAILABLE(tvos);

/*
 *  accelerometerActive
 *
 *  Discussion:
 *    Determines whether the CMMotionManager is currently providing
 *    accelerometer updates.
 */
@property(readonly, nonatomic, getter=isAccelerometerActive) BOOL accelerometerActive API_UNAVAILABLE(tvos);

/*
 *  accelerometerData
 *
 *  Discussion:
 *    Returns the latest sample of accelerometer data, or nil if none is available.
 */

@property(readonly, nullable) CMAccelerometerData *accelerometerData API_UNAVAILABLE(tvos);

/*
 *  startAccelerometerUpdates
 *
 *  Discussion:
 *    Starts accelerometer updates with no handler. To receive the latest accelerometer data
 *    when desired, examine the accelerometerData property.
 */
- (void)startAccelerometerUpdates API_UNAVAILABLE(tvos);

/*
 *  startAccelerometerUpdatesToQueue:withHandler:
 *
 *  Discussion:
 *    Starts accelerometer updates, providing data to the given handler through the given queue.
 *    Note that when the updates are stopped, all operations in the
 *    given NSOperationQueue will be cancelled.
 */
- (void)startAccelerometerUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMAccelerometerHandler)handler API_UNAVAILABLE(tvos);

/*
 *  stopAccelerometerUpdates
 *
 *  Discussion:
 *    Stop accelerometer updates.
 */
- (void)stopAccelerometerUpdates API_UNAVAILABLE(tvos);

/*
 *  gyroUpdateInterval
 *
 *  Discussion:
 *    The interval at which to deliver gyro data to the specified
 *    handler once startGyroUpdatesToQueue:withHandler: is called.
 *    The units are in seconds. The value of this property is capped to
 *    certain minimum and maximum values. The maximum value is determined by
 *    the maximum frequency supported by the hardware. If sensitive to the
 *    interval of gyro data, an application should always check the
 *    timestamps on the delivered CMGyroData instances to determine the
 *    true update interval.
 */
@property(assign, nonatomic) NSTimeInterval gyroUpdateInterval API_UNAVAILABLE(tvos);

/*
 *  gyroAvailable
 *
 *  Discussion:
 *    Determines whether gyro is available.
 */
@property(readonly, nonatomic, getter=isGyroAvailable) BOOL gyroAvailable API_UNAVAILABLE(tvos);

/*
 *  gyroActive
 *
 *  Discussion:
 *    Determines whether the CMMotionManager is currently providing gyro updates.
 */
@property(readonly, nonatomic, getter=isGyroActive) BOOL gyroActive API_UNAVAILABLE(tvos);

/*
 *  gyroData
 *
 *  Discussion:
 *    Returns the latest sample of gyro data, or nil if none is available.
 */
@property(readonly, nullable) CMGyroData *gyroData API_UNAVAILABLE(tvos);

/*
 *  startGyroUpdates
 *
 *  Discussion:
 *    Starts gyro updates with no handler. To receive the latest gyro data
 *    when desired, examine the gyroData property.
 */
- (void)startGyroUpdates API_UNAVAILABLE(tvos);

/*
 *  startGyroUpdatesToQueue:withHandler:
 *
 *  Discussion:
 *    Starts gyro updates, providing data to the given handler through the given queue.
 *    Note that when the updates are stopped, all operations in the
 *    given NSOperationQueue will be cancelled.

 */
- (void)startGyroUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMGyroHandler)handler API_UNAVAILABLE(tvos);

/*
 *  stopGyroUpdates
 *
 *  Discussion:
 *    Stops gyro updates.
 */
- (void)stopGyroUpdates API_UNAVAILABLE(tvos);

/*
 *  magnetometerUpdateInterval
 *
 *  Discussion:
 *    The interval at which to deliver magnetometer data to the specified
 *    handler once startMagnetometerUpdatesToQueue:withHandler: is called.
 *    The units are in seconds. The value of this property is capped to
 *    certain minimum and maximum values. The maximum value is determined by
 *    the maximum frequency supported by the hardware. If sensitive to the
 *    interval of magnetometer data, an application should always check the
 *    timestamps on the delivered CMMagnetometerData instances to determine the
 *    true update interval.
 */
@property(assign, nonatomic) NSTimeInterval magnetometerUpdateInterval COREMOTION_EXPORT API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*
 *  magnetometerAvailable
 *
 *  Discussion:
 *    Determines whether magetometer is available.
 */
@property(readonly, nonatomic, getter=isMagnetometerAvailable) BOOL magnetometerAvailable COREMOTION_EXPORT API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*
 *  magnetometerActive
 *
 *  Discussion:
 *    Determines whether the CMMotionManager is currently providing magnetometer updates.
 */
@property(readonly, nonatomic, getter=isMagnetometerActive) BOOL magnetometerActive COREMOTION_EXPORT API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*
 *  magnetometerData
 *
 *  Discussion:
 *    Returns the latest sample of magnetometer data, or nil if none is available.
 */
@property(readonly, nullable) CMMagnetometerData *magnetometerData COREMOTION_EXPORT API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*
 *  startMagnetometerUpdates
 *
 *  Discussion:
 *    Starts magnetometer updates with no handler. To receive the latest magnetometer data
 *    when desired, examine the magnetometerData property.
 */
- (void)startMagnetometerUpdates COREMOTION_EXPORT API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*
 *  startMagnetometerUpdatesToQueue:withHandler:
 *
 *  Discussion:
 *    Starts magnetometer updates, providing data to the given handler through the given queue.
 */
- (void)startMagnetometerUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMMagnetometerHandler)handler COREMOTION_EXPORT API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*
 *  stopMagnetometerUpdates
 *
 *  Discussion:
 *    Stops magnetometer updates.
 */
- (void)stopMagnetometerUpdates COREMOTION_EXPORT API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*
 *  deviceMotionUpdateInterval
 *
 *  Discussion:
 *    The interval at which to deliver device motion data to the specified
 *    handler once startDeviceMotionUpdatesToQueue:withHandler: is called.
 *    The units are in seconds. The value of this property is capped to
 *    certain minimum and maximum values. The maximum value is determined by
 *    the maximum frequency supported by the hardware. If sensitive to the
 *    interval of device motion data, an application should always check the
 *    timestamps on the delivered CMDeviceMotion instances to determine the
 *    true update interval.
 */
@property(assign, nonatomic) NSTimeInterval deviceMotionUpdateInterval API_UNAVAILABLE(tvos);

/*
 *  availableAttitudeReferenceFrames
 *
 *  Discussion:
 *     Returns a bitmask specifying the available attitude reference frames on the device.
 */
+ (CMAttitudeReferenceFrame)availableAttitudeReferenceFrames COREMOTION_EXPORT API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*
 *  attitudeReferenceFrame
 *
 *  Discussion:
 *    If device motion is active, returns the reference frame currently in-use.
 *    If device motion is not active, returns the default attitude reference frame
 *    for the device. If device motion is not available on the device, the value
 *    is undefined.
 *
 */
@property(readonly, nonatomic) CMAttitudeReferenceFrame attitudeReferenceFrame COREMOTION_EXPORT API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos);

/*
 *  deviceMotionAvailable
 *
 *  Discussion:
 *    Determines whether device motion is available using any available attitude reference frame.
 */
@property(readonly, nonatomic, getter=isDeviceMotionAvailable) BOOL deviceMotionAvailable API_UNAVAILABLE(tvos);

/*
 *  deviceMotionActive
 *
 *  Discussion:
 *    Determines whether the CMMotionManager is currently providing device
 *    motion updates.
 */
@property(readonly, nonatomic, getter=isDeviceMotionActive) BOOL deviceMotionActive API_UNAVAILABLE(tvos);

/*
 *  deviceMotion
 *
 *  Discussion:
 *    Returns the latest sample of device motion data, or nil if none is available.
 */
@property(readonly, nullable) CMDeviceMotion *deviceMotion API_UNAVAILABLE(tvos);

/*
 *  startDeviceMotionUpdates
 *
 *  Discussion:
 *    Starts device motion updates with no handler. To receive the latest device motion data
 *    when desired, examine the deviceMotion property. Uses the default reference frame for
 *    the device. Examine CMMotionManager's attitudeReferenceFrame to determine this.
 */
- (void)startDeviceMotionUpdates API_UNAVAILABLE(tvos);

/*
 *  startDeviceMotionUpdatesToQueue:withHandler:
 *
 *  Discussion:
 *    Starts device motion updates, providing data to the given handler through the given queue.
 *    Uses the default reference frame for the device. Examine CMMotionManager's
 *    attitudeReferenceFrame to determine this.
 *
 */
- (void)startDeviceMotionUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMDeviceMotionHandler)handler API_UNAVAILABLE(tvos);

/*
 *  startDeviceMotionUpdatesUsingReferenceFrame:
 *
 *  Discussion:
 *    Starts device motion updates with no handler. To receive the latest device motion data
 *    when desired, examine the deviceMotion property. The specified frame will be used as
 *    reference for the attitude estimates.
 *
 */
- (void)startDeviceMotionUpdatesUsingReferenceFrame:(CMAttitudeReferenceFrame)referenceFrame COREMOTION_EXPORT API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*
 *  startDeviceMotionUpdatesUsingReferenceFrame:toQueue:withHandler
 *
 *  Discussion:
 *    Starts device motion updates, providing data to the given handler through the given queue.
 *    The specified frame will be used as reference for the attitude estimates.
 *
 */
- (void)startDeviceMotionUpdatesUsingReferenceFrame:(CMAttitudeReferenceFrame)referenceFrame toQueue:(NSOperationQueue *)queue withHandler:(CMDeviceMotionHandler)handler COREMOTION_EXPORT API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

/*
 *  stopDeviceMotionUpdates
 *
 *  Discussion:
 *    Stops device motion updates.
 */
- (void)stopDeviceMotionUpdates API_UNAVAILABLE(tvos);

/*
 *  showsDeviceMovementDisplay
 *
 *  Discussion:
 *    When the device requires movement, showsDeviceMovementDisplay indicates if the system device
 *    movement display should be shown. Note that when device requires movement,
 *    CMErrorDeviceRequiresMovement is reported once via CMDeviceMotionHandler. By default,
 *    showsDeviceMovementDisplay is NO.
 */
@property(assign, nonatomic) BOOL showsDeviceMovementDisplay COREMOTION_EXPORT API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

@end

NS_ASSUME_NONNULL_END
