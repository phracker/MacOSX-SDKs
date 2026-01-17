/*
 *  CMAttitude.h
 *  CoreMotion
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMRotationMatrix
 *  
 *  Discussion:
 *    Type represents a rotation matrix.
 */
typedef struct 
{
	double m11, m12, m13;
	double m21, m22, m23;
	double m31, m32, m33;
} CMRotationMatrix;

/*
 *  CMQuaternion
 *  
 *  Discussion:
 *    Type represents a quaternion (one way of parameterizing attitude). If q
 *		is an instance of CMQuaternion, mathematically it represents the 
 *		following quaternion:
 *		q.x*i + q.y*j + q.z*k + q.w
 *		
 */
typedef struct
{
	double x, y, z, w;
} CMQuaternion;

/*
 *  CMAttitudeReferenceFrame
 *  
 *  Discussion:
 *    CMAttitudeReferenceFrame indicates the reference frame from which all CMAttitude
 *        samples are referenced.
 *
 *    Definitions of each reference frame is as follows:
 *        - CMAttitudeReferenceFrameXArbitraryZVertical describes a reference frame in
 *          which the Z axis is vertical and the X axis points in an arbitrary direction
 *          in the horizontal plane.
 *        - CMAttitudeReferenceFrameXArbitraryCorrectedZVertical describes the same reference
 *          frame as CMAttitudeReferenceFrameXArbitraryZVertical with the following exception:
 *          when available and calibrated, the magnetometer will be used to correct for accumulated
 *          yaw errors. The downside of using this over CMAttitudeReferenceFrameXArbitraryZVertical
 *          is increased CPU usage.
 *        - CMAttitudeReferenceFrameXMagneticNorthZVertical describes a reference frame
 *          in which the Z axis is vertical and the X axis points toward magnetic north.
 *          Note that using this reference frame may require device movement to 
 *          calibrate the magnetometer.
 *        - CMAttitudeReferenceFrameXTrueNorthZVertical describes a reference frame in
 *          which the Z axis is vertical and the X axis points toward true north.
 *          Note that using this reference frame may require device movement to 
 *          calibrate the magnetometer.
 */
typedef NS_OPTIONS(NSUInteger, CMAttitudeReferenceFrame) API_UNAVAILABLE(tvos) {
	CMAttitudeReferenceFrameXArbitraryZVertical = 1 << 0,
	CMAttitudeReferenceFrameXArbitraryCorrectedZVertical = 1 << 1,
	CMAttitudeReferenceFrameXMagneticNorthZVertical = 1 << 2,
	CMAttitudeReferenceFrameXTrueNorthZVertical = 1 << 3
};

COREMOTION_EXPORT API_AVAILABLE(ios(4.0)) API_UNAVAILABLE(tvos)
@interface CMAttitude : NSObject <NSCopying, NSSecureCoding>
{
@private
	id _internal;
}

/*
 *  roll
 *  
 *  Discussion:
 *    Returns the roll of the device in radians.
 *
 */
@property(readonly, nonatomic) double roll;

/*
 *  pitch
 *  
 *  Discussion:
 *    Returns the pitch of the device in radians.
 *
 */
@property(readonly, nonatomic) double pitch;

/*
 *  yaw
 *  
 *  Discussion:
 *    Returns the yaw of the device in radians.
 *
 */
@property(readonly, nonatomic) double yaw;

/*
 *  rotationMatrix
 *  
 *  Discussion:
 *    Returns a rotation matrix representing the device's attitude.
 *
 */
@property(readonly, nonatomic) CMRotationMatrix rotationMatrix;

/*
 *  quaternion
 *  
 *  Discussion:
 *    Returns a quaternion representing the device's attitude.
 *
 */
@property(readonly, nonatomic) CMQuaternion quaternion;

/*
 *  multiplyByInverseOfAttitude:
 *  
 *  Discussion:
 *      Multiplies attitude by the inverse of the specified attitude. This gives
 *			the attitude change from the specified attitude.
 */
- (void)multiplyByInverseOfAttitude:(CMAttitude *)attitude;

@end

NS_ASSUME_NONNULL_END
