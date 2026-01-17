#ifndef Spatial_SPRotation3D_h
#define Spatial_SPRotation3D_h

#include <Spatial/Structures.h>
#include <Spatial/SPRotationAxis3D.h>
#include <Spatial/SPAngle.h>
#include <Spatial/SpatialEnumerations.h>
#include <math.h>

// MARK: - Public API

/*!
 @abstract Returns a rotation over the specified axis with the specified angle.
 
 @param axis The axis of the rotation.
 @param angle The angle of the rotation.
 @returns A new rotation stucture.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMake(SPRotationAxis3D axis, SPAngle angle)
__API_DEPRECATED("Use `SPRotation3DMake(SPAngle angle, SPRotationAxis3D axis)`.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Returns a rotation over the specified axis with the specified angle.
 
 @param angle The angle of the rotation.
 @param axis The axis of the rotation.
 @returns A new rotation stucture.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMake(SPAngle angle, SPRotationAxis3D axis)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract  Returns the rotation represented as a normalized quaternion.
 
 @param rotation The source rotation.
 @returns A quaternion with an axis and angle derived from the source rotation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_quatd SPRotation3DGetQuaternion(SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rotation from the specified quaternion.
 
 @param quaternion The source quaternion.
 @returns A new rotation stucture.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeWithQuaternion(simd_quatd quaternion)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Returns @p true if both rotations are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRotation3DEqualToRotation(SPRotation3D rotation1, SPRotation3D rotation2)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Header inline implementations

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeWithQuaternion(simd_quatd quaternion) {
  
    return (SPRotation3D) { .quaternion = quaternion };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMake(SPRotationAxis3D axis, SPAngle angle) {
    return SPRotation3DMake(angle, axis);
}

SPATIAL_SWIFT_NAME(Rotation3D.init(angle:axis:))
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMake(SPAngle angle, SPRotationAxis3D axis) {
    
    if (SPRotationAxis3DIsZero(axis)) {
        return (SPRotation3D){ .vector = {0, 0, 0, 1 }};
    }
    
    simd_quatd q = simd_quaternion(angle.radians, simd_normalize(axis.vector));
    
    return (SPRotation3D){
        .quaternion = q
    };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_quatd SPRotation3DGetQuaternion(SPRotation3D rotation) {
    return rotation.quaternion;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRotation3DEqualToRotation(SPRotation3D rotation1, SPRotation3D rotation2) {
    
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
SPRotation3D SPRotation3DMakeLookAt(SPPoint3D position, SPPoint3D target, SPVector3D up)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeLookAt(SPPoint3D position, SPPoint3D target, SPVector3D up) {
    
    simd_double3 axisZ = simd_normalize(target.vector - position.vector);
    simd_double3 axisX = simd_normalize(simd_cross(axisZ, simd_normalize(up.vector)));
    simd_double3 axisY = simd_normalize(simd_cross(axisX, axisZ));
    
    simd_double3x3 m = simd_matrix(-axisX, axisY, axisZ);
    simd_quatd q = simd_normalize(simd_quaternion(m));
    
    return SPRotation3DMakeWithQuaternion(q);
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
SPRotation3D SPRotation3DMakeLookAt(SPPoint3D target, SPVector3D up)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeLookAt(SPPoint3D target, SPVector3D up) {
 
    SPPoint3D position = SPPoint3DZero;
    
    return SPRotation3DMakeLookAt(position, target, up);
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
SPRotation3D SPRotation3DMakeLookAt(SPVector3D forward, SPVector3D up)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(Rotation3D.init(forward:up:))
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeLookAt(SPVector3D forward, SPVector3D up) {
 
    SPPoint3D position = SPPoint3DZero;
    
    SPPoint3D target = SPPoint3DMakeWithVector(forward.vector);
    
    return SPRotation3DMakeLookAt(position, target, up);
}

// MARK: EULER headers

/*!
 @abstract A structure that represents Euler angles, in radians, and ordering.
*/
typedef struct {
    /*!
     A three-element vector that contains the angles, in radians.
     */
    simd_double3 angles;
    
    /*!
     A constant that specify the Euler angle order.
     */
    SPEulerAngleOrder order;
} SPEulerAngles
SPATIAL_SWIFT_NAME(EulerAngles)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rotation structure from the specified Euler angles.
 
 @param eulerAngles The source Euler angles, in radians.
 @returns A rotation structure.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeWithEulerAngles(SPEulerAngles eulerAngles)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns the Euler angles, in radians, from the specified rotation structure.
 
 @param rotation The source rotation structure.
 @param order The Euler angle ordering.
 @returns A rotation structure.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPEulerAngles SPRotation3DGetEulerAngles(SPRotation3D rotation, SPEulerAngleOrder order)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));


SPATIAL_SWIFT_NAME(Rotation3D.init(eulerAngles:))
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeWithEulerAngles(SPEulerAngles eulerAngles) {
    
    SPEulerAngleOrder order = eulerAngles.order;

    simd_double3 halves = (simd_double3){0.5, 0.5, 0.5} * eulerAngles.angles;
    simd_double3 cosines = _sp_simd_cos(halves).xyz;
    simd_double3 sines = _sp_simd_sin(halves).xyz;
    
    double cr;
    double cp;
    double cy;
    double sr;
    double sp;
    double sy;
    double cpcy;
    double spsy;
    
    simd_double4 v;
    
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
            
            v = (simd_double4){
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
            
            v = (simd_double4){
                cr * sp * cy + sr * cp * sy,
                cr * cp * sy - sr * sp * cy,
                sr * cpcy - cr * spsy,
                cr * cpcy + sr * spsy
            };
            
            break;
        default:
            return SPRotation3DInvalid;
            break;
    }
 
    return SPRotation3DMakeWithQuaternion(simd_quaternion(v));
}

SPATIAL_SWIFT_NAME(Rotation3D.eulerAngles(self:order:))
SPATIAL_OVERLOADABLE
SPEulerAngles SPRotation3DGetEulerAngles(SPRotation3D rotation, SPEulerAngleOrder order) {

    simd_double4 qv = rotation.quaternion.vector;
    double ix;
    double iy;
    double iz;
    
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
    double r  = qv.w;
    double iy2 = iy * iy;

    double t0 = 2. * (r * ix + iy * iz);
    double t1 = 1. - 2. * (ix * ix + iy2);
    double roll = _sp_simd_atan2(t0, t1);

    double t2 = 2. * (r * iy - iz * ix);
    t2 = t2 > 1. ? 1. : t2;
    t2 = t2 < -1. ? -1. : t2;
    double pitch = _sp_simd_asin(t2);

    float t3 = 2. * (r * iz + ix * iy);
    float t4 = 1. - 2. * (iy2 + iz * iz);
    double yaw = _sp_simd_atan2(t3, t4);
    
    switch(order) {
        case 1:
            // SPEulerPitchYawRoll, SPEulerXYZ
            return (SPEulerAngles){(simd_double3){ roll, pitch, yaw }, order };
            break;
        case SPEulerZXY:
            return (SPEulerAngles){(simd_double3){ pitch, yaw, roll}, order };
            break;
        default:
            return (SPEulerAngles){ { NAN, NAN, NAN }, order};
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
SPAngle SPRotation3DGetAngle(SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngle SPRotation3DGetAngle(SPRotation3D rotation) {
    
    double radians = simd_angle(rotation.quaternion);
    
    return SPAngleMakeWithRadians(radians);
}

/*!
 @abstract Sets the angle on the specified rotation structure.
 
 @param rotation A pointer to the rotation structure.
 @param angle The angle structure.
 */

SPATIAL_INLINE
SPATIAL_OVERLOADABLE
void SPRotation3DSetAngle(SPRotation3D *rotation, SPAngle angle)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
void SPRotation3DSetAngle(SPRotation3D *rotation, SPAngle angle) {
    
    simd_double3 axis = simd_axis(rotation->quaternion);
    
    simd_quatd quaternion = simd_quaternion(angle.radians, axis);
    
    rotation->quaternion = quaternion;
}

/*!
 @abstract Returns the axis of the normalized underlying quaternion.
 
 @param rotation The source rotation.
 @returns An angle structure.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotationAxis3D SPRotation3DGetAxis(SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotationAxis3D SPRotation3DGetAxis(SPRotation3D rotation) {
    
    simd_double3 axis = simd_axis(rotation.quaternion);
    
    if(!simd_all(_sp_simd_isfinite(axis))) {
        axis = simd_make_double3(0, 0, 0);
    }
    
    return SPRotationAxis3DMakeWithVector(axis);
}


/*!
 @abstract Sets the axis on the specified rotation structure.
 
 @param rotation A pointer to the rotation structure.
 @param axis The axis structure.
 */

SPATIAL_INLINE
SPATIAL_OVERLOADABLE
void SPRotation3DSetAxis(SPRotation3D *rotation, SPRotationAxis3D axis)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
void SPRotation3DSetAxis(SPRotation3D *rotation, SPRotationAxis3D axis) {
    
    double angle = simd_angle(rotation->quaternion);
    
    simd_quatd quaternion = simd_quaternion(angle, simd_normalize(axis.vector));
    
    rotation->quaternion = quaternion;
}

/*!
 @abstract Returns a Boolean value that indicates whether the rotation's angle is zero.
 
 @param rotation The source rotation.
 @returns A Boolean value that indicates whether the rotation is zero.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRotation3DIsZero(SPRotation3D rotation)
__API_DEPRECATED("This function is deprecated.",
                 macos(13.0, 14.0),
                 ios(16.0, 17.0),
                 watchos(9.0, 10.0),
                 tvos(16.0, 17.0));

SPATIAL_SWIFT_NAME(getter:Rotation3D.isZero(self:))
SPATIAL_OVERLOADABLE
bool SPRotation3DIsZero(SPRotation3D rotation) {

    SPAngle angle = SPRotation3DGetAngle(rotation);
    
    return angle.radians == 0;
}

/*!
 @abstract Returns a Boolean value that indicates whether the rotation's angle is zero.
 
 @param rotation The source rotation.
 @returns A Boolean value that indicates whether the rotation is zero.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRotation3DIsIdentity(SPRotation3D rotation)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_SWIFT_NAME(getter:Rotation3D.isIdentity(self:))
SPATIAL_OVERLOADABLE
bool SPRotation3DIsIdentity(SPRotation3D rotation) {

    return simd_equal(rotation.vector, SPRotation3DIdentity.vector);
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
SPRotation3D SPRotation3DSlerp(SPRotation3D from, SPRotation3D to, double t)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DSlerp(SPRotation3D from, SPRotation3D to, double t) {

    simd_quatd q = simd_slerp(from.quaternion, to.quaternion, t);
    
    return SPRotation3DMakeWithQuaternion(q);
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
SPRotation3D SPRotation3DSlerpLongest(SPRotation3D from, SPRotation3D to, double t)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DSlerpLongest(SPRotation3D from, SPRotation3D to, double t) {

    simd_quatd q = simd_slerp_longest(from.quaternion, to.quaternion, t);
    
    return SPRotation3DMakeWithQuaternion(q);
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
SPRotation3D SPRotation3DSpline(SPRotation3D r0, SPRotation3D r1, SPRotation3D r2, SPRotation3D r3, double t)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DSpline(SPRotation3D r0, SPRotation3D r1, SPRotation3D r2, SPRotation3D r3, double t) {

    simd_quatd q = simd_spline(r0.quaternion, r1.quaternion, r2.quaternion, r3.quaternion, t);
    
    return SPRotation3DMakeWithQuaternion(q);
}

/*!
 @abstract Returns the inverse of a rotation.
 @param rotation The source rotation.
 @returns The inverse of a rotation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DInverse(SPRotation3D rotation)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_SWIFT_NAME(getter:Rotation3D.inverse(self:))
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DInverse(SPRotation3D rotation) {

    simd_quatd q = simd_inverse(rotation.quaternion);
    
    return SPRotation3DMakeWithQuaternion(q);
}

/*!
 @abstract Returns the twist component of the rotation's swing-twist decomposition for a given twist axis.
 @param rotation The source rotation.
 @param twistAxis The twist axis.
 @returns The twist component of the rotation's swing-twist decomposition for a given twist axis.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DTwist(SPRotation3D rotation, SPRotationAxis3D twistAxis)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_SWIFT_NAME(Rotation3D.twist(self:twistAxis:))
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DTwist(SPRotation3D rotation, SPRotationAxis3D twistAxis) {

    simd_double3 projection = simd_project(simd_imag(rotation.quaternion),
                                           twistAxis.vector);
    simd_quatd twist = simd_quaternion(projection.x,
                                       projection.y,
                                       projection.z,
                                       simd_real(rotation.quaternion));
    
    return SPRotation3DMakeWithQuaternion(simd_normalize(twist));
}

/*!
 @abstract Returns the swing component of the rotation's swing-twist decomposition for a given twist axis.
 @param rotation The source rotation.
 @param twistAxis The twist axis.
 @returns The swing component of the rotation's swing-twist decomposition for a given twist axis.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DSwing(SPRotation3D rotation, SPRotationAxis3D twistAxis)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_SWIFT_NAME(Rotation3D.swing(self:twistAxis:))
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DSwing(SPRotation3D rotation, SPRotationAxis3D twistAxis) {
    
    simd_quatd inverseTwist = simd_inverse(SPRotation3DTwist(rotation, twistAxis).quaternion);
    simd_quatd swing = simd_mul(rotation.quaternion, inverseTwist);
    
    return SPRotation3DMakeWithQuaternion(simd_normalize(swing));
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
bool SPRotation3DAlmostEqualToRotation(SPRotation3D r1,
                                       SPRotation3D r2,
                                       double tolerance)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
bool SPRotation3DAlmostEqualToRotation(SPRotation3D r1,
                                       SPRotation3D r2,
                                       double tolerance) {
    
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
bool SPRotation3DAlmostEqualToRotation(SPRotation3D r1,
                                       SPRotation3D r2)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
bool SPRotation3DAlmostEqualToRotation(SPRotation3D r1,
                                       SPRotation3D r2) {
    
    return SPRotation3DAlmostEqualToRotation(r1, r2, SPDefaultTolerance);
}



#endif /* Spatial_SPRotation3D_h */
