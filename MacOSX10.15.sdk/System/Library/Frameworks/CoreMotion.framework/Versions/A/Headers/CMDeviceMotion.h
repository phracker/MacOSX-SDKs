/*
 *  CMDeviceMotion.h
 *  CoreMotion
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */

#import <CoreMotion/CMAccelerometer.h>
#import <CoreMotion/CMAttitude.h>
#import <CoreMotion/CMGyro.h>
#import <CoreMotion/CMMagnetometer.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMMagneticFieldCalibrationAccuracy
 *
 *  Discussion:
 *    CMMagneticFieldCalibrationAccuracy indicates the calibration
 *    accuracy of a magnetic field estimate.
 *
 */
typedef NS_ENUM(int, CMMagneticFieldCalibrationAccuracy) {
	CMMagneticFieldCalibrationAccuracyUncalibrated = -1,
	CMMagneticFieldCalibrationAccuracyLow,
	CMMagneticFieldCalibrationAccuracyMedium,
	CMMagneticFieldCalibrationAccuracyHigh
} ;

/*
 *  CMCalibratedMagneticField
 *
 *  Discussion:
 *    A structure containing 3-axis calibrated magnetic field data
 *    and an estimate of the accuracy of the calibration
 *
 *  Fields:
 *    field:
 *      The 3-axis calibrated magnetic field vector.
 *    accuracy:
 *      An estimate of the calibration accuracy.
 */
typedef struct {
    CMMagneticField field;
    CMMagneticFieldCalibrationAccuracy accuracy;
} CMCalibratedMagneticField;


/*
 *  CMDeviceMotion
 *
 *  Discussion:
 *    A CMDeviceMotion object contains basic information about the device's
 *    motion.
 */
COREMOTION_EXPORT API_AVAILABLE(ios(4.0)) API_UNAVAILABLE(tvos)
@interface CMDeviceMotion : CMLogItem
{
@private
	id _internal;
}

/*
 *  attitude
 *
 *  Discussion:
 *    Returns the attitude of the device.
 *
 */
@property(readonly, nonatomic) CMAttitude *attitude;

/*
 *  rotationRate
 *
 *  Discussion:
 *    Returns the rotation rate of the device for devices with a gyro.
 *
 */
@property(readonly, nonatomic) CMRotationRate rotationRate;

/*
 *  gravity
 *
 *  Discussion:
 *    Returns the gravity vector expressed in the device's reference frame. Note
 *    that the total acceleration of the device is equal to gravity plus
 *    userAcceleration.
 *
 */
@property(readonly, nonatomic) CMAcceleration gravity;

/*
 *  userAcceleration
 *
 *  Discussion:
 *    Returns the acceleration that the user is giving to the device. Note
 *    that the total acceleration of the device is equal to gravity plus
 *    userAcceleration.
 *
 */
@property(readonly, nonatomic) CMAcceleration userAcceleration;

/*
 *  magneticField
 *
 *  Discussion:
 *    Returns the magnetic field vector with respect to the device for devices with a magnetometer.
 *    Note that this is the total magnetic field in the device's vicinity without device
 *    bias (Earth's magnetic field plus surrounding fields, without device bias),
 *    unlike CMMagnetometerData magneticField.
 */
@property(readonly, nonatomic) CMCalibratedMagneticField magneticField COREMOTION_EXPORT API_AVAILABLE(ios(5.0));

/*
 *  heading
 *
 *  Discussion:
 *    Returns heading angle in the range [0,360) degrees with respect to the CMAttitude reference frame. A negative value is returned
 *    for CMAttitudeReferenceFrameXArbitraryZVertical and CMAttitudeReferenceFrameXArbitraryCorrectedZVertical.
 *
 */
@property(readonly, nonatomic) double heading COREMOTION_EXPORT API_AVAILABLE(ios(11.0));

@end

NS_ASSUME_NONNULL_END
