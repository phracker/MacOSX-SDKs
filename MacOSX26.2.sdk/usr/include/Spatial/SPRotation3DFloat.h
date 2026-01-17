#ifndef SPRotation3DFloat_h
#define SPRotation3DFloat_h

#include <Spatial/StructuresFloat.h>
#include <Spatial/SPRotationAxis3DFloat.h>
#include <Spatial/SPAngleFloat.h>
#include <Spatial/SpatialEnumerations.h>
#include <math.h>

// MARK: - Single-Precision Public API

/*!
 @abstract Returns a rotation over the specified axis with the specified angle.
 
 @param angle The angle of the rotation.
 @param axis The axis of the rotation.
 @returns A new rotation stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMake(SPAngleFloat angle, SPRotationAxis3DFloat axis)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract  Returns the rotation represented as a normalized quaternion.
 
 @param rotation The source rotation.
 @returns A quaternion with an axis and angle derived from the source rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_quatf SPRotation3DFloatGetQuaternion(SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rotation from the specified quaternion.
 
 @param quaternion The source quaternion.
 @returns A new rotation stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMakeWithQuaternion(simd_quatf quaternion)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/// Returns @p true if both rotations are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRotation3DFloatEqualToRotation(SPRotation3DFloat rotation1, SPRotation3DFloat rotation2)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Header inline implementations

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMakeWithQuaternion(simd_quatf quaternion) {
    
    return (SPRotation3DFloat) { .quaternion = quaternion };
}

SPATIAL_REFINED_FOR_SWIFT // SPATIAL_SWIFT_NAME(Rotation3DFloat.init(angle:axis:))
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMake(SPAngleFloat angle, SPRotationAxis3DFloat axis) {
    
    if (SPRotationAxis3DFloatIsZero(axis)) {
        return (SPRotation3DFloat){ .vector = {0, 0, 0, 1 }};
    }
    
    simd_quatf q = simd_quaternion(angle.radians, simd_normalize(axis.vector));
    
    return (SPRotation3DFloat){
        .quaternion = q
    };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_quatf SPRotation3DFloatGetQuaternion(SPRotation3DFloat rotation) {
    return rotation.quaternion;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRotation3DFloatEqualToRotation(SPRotation3DFloat rotation1, SPRotation3DFloat rotation2) {
    
    return simd_equal(rotation1.quaternion.vector, rotation2.quaternion.vector) ||
    simd_equal(rotation1.quaternion.vector, simd_negate(rotation2.quaternion).vector);
}


// MARK: - Look At

/*!
 @abstract Returns a rotation that's the look at direction from the position position to the target.
 
 @param position The eye position.
 @param target The point that the rotation looks at.
 @param up The up direction.
 @returns A new rotation stucture.
 @note This function creates a rotation where @p +z is forward.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMakeLookAt(SPPoint3DFloat position, SPPoint3DFloat target, SPVector3DFloat up)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMakeLookAt(SPPoint3DFloat position, SPPoint3DFloat target, SPVector3DFloat up) {
    
    simd_float3 axisZ = simd_normalize(target.vector - position.vector);
    simd_float3 axisX = simd_normalize(simd_cross(axisZ, simd_normalize(up.vector)));
    simd_float3 axisY = simd_normalize(simd_cross(axisX, axisZ));
    
    simd_float3x3 m = simd_matrix(-axisX, axisY, axisZ);
    simd_quatf q = simd_normalize(simd_quaternion(m));
    
    return SPRotation3DFloatMakeWithQuaternion(q);
}

/*!
 @abstract Returns a rotation that's the look at direction from the origin to the target.
 
 @param target The point that the rotation looks at.
 @param up The up direction.
 @returns A new rotation stucture.
 @note This function creates a rotation where @p +z is forward.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMakeLookAt(SPPoint3DFloat target, SPVector3DFloat up)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMakeLookAt(SPPoint3DFloat target, SPVector3DFloat up) {
    
    SPPoint3DFloat position = SPPoint3DFloatZero;
    
    return SPRotation3DFloatMakeLookAt(position, target, up);
}

/*!
 @abstract Returns a rotation with the specified forward and up vectors.
 
 @param forward The forward direction.
 @param up The up direction.
 @returns A new rotation stucture.
 @note This function creates a rotation where @p +z is forward.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMakeLookAt(SPVector3DFloat forward, SPVector3DFloat up)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT // SPATIAL_SWIFT_NAME(Rotation3DFloat.init(forward:up:))
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMakeLookAt(SPVector3DFloat forward, SPVector3DFloat up) {
    
    SPPoint3DFloat position = SPPoint3DFloatZero;
    
    SPPoint3DFloat target = SPPoint3DFloatMakeWithVector(forward.vector);
    
    return SPRotation3DFloatMakeLookAt(position, target, up);
}

// MARK: EULER headers



/*!
 @abstract A structure that represents Euler angles, in radians, and ordering.
 */
typedef struct {
    /*!
     A three-element vector that contains the angles, in radians.
     */
    simd_float3 angles;
    
    /*!
     A constant that specify the Euler angle order.
     */
    SPEulerAngleOrder order;
} SPEulerAnglesFloat
SPATIAL_SWIFT_NAME(EulerAnglesFloat)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rotation structure from the specified Euler angles.
 
 @param eulerAngles The source Euler angles, in radians.
 @returns A rotation structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMakeWithEulerAngles(SPEulerAnglesFloat eulerAngles)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns the Euler angles, in radians, from the specified rotation structure.
 
 @param rotation The source rotation structure.
 @param order The Euler angle ordering.
 @returns A rotation structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPEulerAnglesFloat SPRotation3DFloatGetEulerAngles(SPRotation3DFloat rotation, SPEulerAngleOrder order)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));


SPATIAL_SWIFT_NAME(Rotation3DFloat.init(eulerAngles:))
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMakeWithEulerAngles(SPEulerAnglesFloat eulerAngles) {
    
    SPEulerAngleOrder order = eulerAngles.order;
    
    simd_float3 halves = (simd_float3){0.5, 0.5, 0.5} * eulerAngles.angles;
    simd_float3 cosines = _sp_simd_cos(halves).xyz;
    simd_float3 sines = _sp_simd_sin(halves).xyz;
    
    float cr;
    float cp;
    float cy;
    float sr;
    float sp;
    float sy;
    float cpcy;
    float spsy;
    
    simd_float4 v;
    
    switch(order) {
        case 1:
            // SPEulerPitchYawRoll, SPEulerXYZ
            cr = cosines.x;
            cp = cosines.y;
            cy = cosines.z;
            
            sr = sines.x;
            sp = sines.y;
            sy = sines.z;
            
            cpcy = cp * cy;
            spsy = sp * sy;
            
            v = (simd_float4){
                sr * cpcy - cr * spsy,
                cr * sp * cy + sr * cp * sy,
                cr * cp * sy - sr * sp * cy,
                cr * cpcy + sr * spsy
            };
            
            break;
        case SPEulerZXY:
            cr = cosines.z;
            cp = cosines.x;
            cy = cosines.y;
            
            sr = sines.z;
            sp = sines.x;
            sy = sines.y;
            
            cpcy = cp * cy;
            spsy = sp * sy;
            
            v = (simd_float4){
                cr * sp * cy + sr * cp * sy,
                cr * cp * sy - sr * sp * cy,
                sr * cpcy - cr * spsy,
                cr * cpcy + sr * spsy
            };
            
            break;
        default:
            return SPRotation3DFloatInvalid;
            break;
    }
    
    return SPRotation3DFloatMakeWithQuaternion(simd_quaternion(v));
}

SPATIAL_SWIFT_NAME(Rotation3DFloat.eulerAngles(self:order:))
SPATIAL_OVERLOADABLE
SPEulerAnglesFloat SPRotation3DFloatGetEulerAngles(SPRotation3DFloat rotation, SPEulerAngleOrder order) {
    
    simd_float4 qv = rotation.quaternion.vector;
    float ix;
    float iy;
    float iz;
    
    switch(order) {
        case 1:
            // SPEulerPitchYawRoll, SPEulerXYZ
            ix = qv.x;
            iy = qv.y;
            iz = qv.z;
            break;
        case SPEulerZXY:
            ix = qv.z;
            iy = qv.x;
            iz = qv.y;
            break;
    }
    float r  = qv.w;
    float iy2 = iy * iy;
    
    float t0 = 2. * (r * ix + iy * iz);
    float t1 = 1. - 2. * (ix * ix + iy2);
    float roll = _sp_simd_atan2(t0, t1);
    
    float t2 = 2. * (r * iy - iz * ix);
    t2 = t2 > 1. ? 1. : t2;
    t2 = t2 < -1. ? -1. : t2;
    float pitch = _sp_simd_asin(t2);
    
    float t3 = 2. * (r * iz + ix * iy);
    float t4 = 1. - 2. * (iy2 + iz * iz);
    float yaw = _sp_simd_atan2(t3, t4);
    
    switch(order) {
        case 1:
            // SPEulerPitchYawRoll, SPEulerXYZ
            return (SPEulerAnglesFloat){(simd_float3){ roll, pitch, yaw }, order };
            break;
        case SPEulerZXY:
            return (SPEulerAnglesFloat){(simd_float3){ pitch, yaw, roll}, order };
            break;
        default:
            return (SPEulerAnglesFloat){ { NAN, NAN, NAN }, order};
            break;
    }
}

// MARK: - Angle and axis components of the angle and axis form.

/*!
 @abstract Returns the angle, in radians, of the normalized underlying quaternion.
 
 @param rotation The source rotation.
 @returns An angle structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngleFloat SPRotation3DFloatGetAngle(SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngleFloat SPRotation3DFloatGetAngle(SPRotation3DFloat rotation) {
    
    float radians = simd_angle(rotation.quaternion);
    
    return SPAngleFloatMakeWithRadians(radians);
}

/*!
 @abstract Sets the angle on the specified rotation structure.
 
 @param rotation A pointer to the rotation structure.
 @param angle The angle structure.
 */

SPATIAL_INLINE
SPATIAL_OVERLOADABLE
void SPRotation3DFloatSetAngle(SPRotation3DFloat *rotation, SPAngleFloat angle)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
void SPRotation3DFloatSetAngle(SPRotation3DFloat *rotation, SPAngleFloat angle) {
    
    simd_float3 axis = simd_axis(rotation->quaternion);
    
    simd_quatf quaternion = simd_quaternion(angle.radians, axis);
    
    rotation->quaternion = quaternion;
}

/*!
 @abstract Returns the axis of the normalized underlying quaternion.
 
 @param rotation The source rotation.
 @returns An angle structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotationAxis3DFloat SPRotation3DFloatGetAxis(SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotationAxis3DFloat SPRotation3DFloatGetAxis(SPRotation3DFloat rotation) {
    
    simd_float3 axis = simd_axis(rotation.quaternion);
    
    if(!simd_all(_sp_simd_isfinite(axis))) {
        axis = simd_make_float3(0, 0, 0);
    }
    
    return SPRotationAxis3DFloatMakeWithVector(axis);
}


/*!
 @abstract Sets the axis on the specified rotation structure.
 
 @param rotation A pointer to the rotation structure.
 @param axis The axis structure.
 */

SPATIAL_INLINE
SPATIAL_OVERLOADABLE
void SPRotation3DFloatSetAxis(SPRotation3DFloat *rotation, SPRotationAxis3DFloat axis)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
void SPRotation3DFloatSetAxis(SPRotation3DFloat *rotation, SPRotationAxis3DFloat axis) {
    
    float angle = simd_angle(rotation->quaternion);
    
    simd_quatf quaternion = simd_quaternion(angle, simd_normalize(axis.vector));
    
    rotation->quaternion = quaternion;
}

/*!
 @abstract Returns a Boolean value that indicates whether the rotation's angle is zero.
 
 @param rotation The source rotation.
 @returns A Boolean value that indicates whether the rotation is zero.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRotation3DFloatIsIdentity(SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(getter:Rotation3DFloat.isIdentity(self:))
SPATIAL_OVERLOADABLE
bool SPRotation3DFloatIsIdentity(SPRotation3DFloat rotation) {
    
    return simd_equal(rotation.vector, SPRotation3DFloatIdentity.vector);
}

/*!
 @abstract Returns the spherical linear interpolation along the shortest arc between two rotations.
 
 @param from The starting rotation.
 @param to The ending rotation.
 @param t The value, between @p 0 and @p 1, that the function interpolates at.
 
 @returns A new rotation. When @p t=0, the result is the @p from rotation. When @p t=1.0, the result
 is the @p to rotation. For any other value of @p t, the result is a spherical linear interpolation between the
 two rotations.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatSlerp(SPRotation3DFloat from, SPRotation3DFloat to, float t)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatSlerp(SPRotation3DFloat from, SPRotation3DFloat to, float t) {
    
    simd_quatf q = simd_slerp(from.quaternion, to.quaternion, t);
    
    return SPRotation3DFloatMakeWithQuaternion(q);
}

/*!
 @abstract Returns the spherical linear interpolation along the longest arc between two rotations.
 
 @param from The starting rotation.
 @param to The ending rotation.
 @param t The value, between @p 0 and @p 1, that the function interpolates at.
 
 @returns A new rotation. When @p t=0, the result is the @p from rotation. When @p t=1.0, the result
 is the @p to rotation. For any other value of @p t, the result is a spherical linear interpolation between the
 two rotations.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatSlerpLongest(SPRotation3DFloat from, SPRotation3DFloat to, float t)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatSlerpLongest(SPRotation3DFloat from, SPRotation3DFloat to, float t) {
    
    simd_quatf q = simd_slerp_longest(from.quaternion, to.quaternion, t);
    
    return SPRotation3DFloatMakeWithQuaternion(q);
}

/*!
 @abstract Returns an interpolated value between two rotations along a spherical cubic spline.
 
 @param r0 The left endpoint of the previous interval.
 @param r1 The starting rotation.
 @param r2 The ending rotation.
 @param r3 The right endpoint of the next interval.
 @param t The value, between @p 0 and @p 1, that the function interpolates at.
 
 @discussion The function interpolates between @p r1 and @p r2. @p r0 is the left
 endpoint of the previous interval, and @p r3 is the right endpoint of the next
 interval. Use this function to smoothly interpolate between a sequence of
 rotations.
 
 @returns A new rotation that's the interpolated value between the two rotations along a spherical cubic spline.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatSpline(SPRotation3DFloat r0, SPRotation3DFloat r1, SPRotation3DFloat r2, SPRotation3DFloat r3, float t)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatSpline(SPRotation3DFloat r0, SPRotation3DFloat r1, SPRotation3DFloat r2, SPRotation3DFloat r3, float t) {
    
    simd_quatf q = simd_spline(r0.quaternion, r1.quaternion, r2.quaternion, r3.quaternion, t);
    
    return SPRotation3DFloatMakeWithQuaternion(q);
}

/*!
 @abstract Returns the inverse of a rotation.
 @param rotation The source rotation.
 @returns The inverse of a rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatInverse(SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(getter:Rotation3DFloat.inverse(self:))
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatInverse(SPRotation3DFloat rotation) {
    
    simd_quatf q = simd_inverse(rotation.quaternion);
    
    return SPRotation3DFloatMakeWithQuaternion(q);
}

/*!
 @abstract Returns the twist component of the rotation's swing-twist decomposition for a given twist axis.
 @param rotation The source rotation.
 @param twistAxis The twist axis.
 @returns The twist component of the rotation's swing-twist decomposition for a given twist axis.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatTwist(SPRotation3DFloat rotation, SPRotationAxis3DFloat twistAxis)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(Rotation3DFloat.twist(self:twistAxis:))
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatTwist(SPRotation3DFloat rotation, SPRotationAxis3DFloat twistAxis) {
    
    simd_float3 projection = simd_project(simd_imag(rotation.quaternion),
                                          twistAxis.vector);
    simd_quatf twist = simd_quaternion(projection.x,
                                       projection.y,
                                       projection.z,
                                       simd_real(rotation.quaternion));
    
    return SPRotation3DFloatMakeWithQuaternion(simd_normalize(twist));
}

/*!
 @abstract Returns the swing component of the rotation's swing-twist decomposition for a given twist axis.
 @param rotation The source rotation.
 @param twistAxis The twist axis.
 @returns The swing component of the rotation's swing-twist decomposition for a given twist axis.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatSwing(SPRotation3DFloat rotation, SPRotationAxis3DFloat twistAxis)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(Rotation3DFloat.swing(self:twistAxis:))
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatSwing(SPRotation3DFloat rotation, SPRotationAxis3DFloat twistAxis) {
    
    simd_quatf inverseTwist = simd_inverse(SPRotation3DFloatTwist(rotation, twistAxis).quaternion);
    simd_quatf swing = simd_mul(rotation.quaternion, inverseTwist);
    
    return SPRotation3DFloatMakeWithQuaternion(simd_normalize(swing));
}

// MARK: - Almost Equal

/*!
 @abstract Returns a Boolean value that indicates whether the two rotations are equal within the specified absolute tolerance.
 
 @param r1 The first rotation.
 @param r2 The first rotation.
 @returns A Boolean value that indicates whether the two rotations are equal within the specified absolute tolerance.
 @note The Spatial default tolerance is @p sqrt(__DBL_EPSILON__) .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRotation3DFloatAlmostEqualToRotation(SPRotation3DFloat r1,
                                            SPRotation3DFloat r2,
                                            float tolerance)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
bool SPRotation3DFloatAlmostEqualToRotation(SPRotation3DFloat r1,
                                            SPRotation3DFloat r2,
                                            float tolerance) {
    
    return _sp_almost_equal_tolerance(r1.quaternion.vector.x, r2.quaternion.vector.x, tolerance) &&
    _sp_almost_equal_tolerance(r1.quaternion.vector.y, r2.quaternion.vector.y, tolerance) &&
    _sp_almost_equal_tolerance(r1.quaternion.vector.z, r2.quaternion.vector.z, tolerance) &&
    _sp_almost_equal_tolerance(r1.quaternion.vector.w, r2.quaternion.vector.w, tolerance);
}

/*!
 @abstract Returns a Boolean value that indicates whether the two rotations are equal within the Spatial default absolute tolerance.
 
 @param r1 The first rotation.
 @param r2 The first rotation.
 @returns A Boolean value that indicates whether the two rotations are equal within the Spatial default absolute tolerance.
 @note The Spatial default tolerance is @p sqrt(__DBL_EPSILON__) .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRotation3DFloatAlmostEqualToRotation(SPRotation3DFloat r1,
                                            SPRotation3DFloat r2)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
bool SPRotation3DFloatAlmostEqualToRotation(SPRotation3DFloat r1,
                                            SPRotation3DFloat r2) {
    
    return SPRotation3DFloatAlmostEqualToRotation(r1, r2, SPDefaultToleranceFloat);
}

#endif /* SPRotation3DFloat_h */
