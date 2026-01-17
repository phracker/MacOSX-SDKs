#ifndef SPPoint3DFloat_h
#define SPPoint3DFloat_h

#include <Spatial/StructuresFloat.h>
#include <Spatial/SPProjectiveTransform3DFloat.h>
#include <Spatial/SPAffineTransform3DFloat.h>
#include <Spatial/SPAngleFloat.h>


// MARK: - SINGLE-PRECISION Public API

/*!
 @abstract Creates a point with coordinates specified as a Spatial vector.
 
 @param xyz The source vector.
 @returns A new point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatMakeWithVector(SPVector3DFloat xyz)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatMakeWithVector(SPVector3DFloat xyz) {
    return SPPoint3DFloatMake(xyz.vector.x, xyz.vector.y, xyz.vector.z);
}

/*!
 @abstract Creates a point with coordinates specified as a dimensions of a size structure.
 
 @param size The source size.
 @returns A new point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatMakeWithSize(SPSize3DFloat size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatMakeWithSize(SPSize3DFloat size) {
    return SPPoint3DFloatMake(size.vector.x, size.vector.y, size.vector.z);
}

/*!
 @abstract Returns a point that's transformed by the specified affine transform.
 
 @param point The source point.
 @param transform The affine transform that the function applies to the point.
 @returns The transformed point,
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatApplyAffineTransform(SPPoint3DFloat point,
                                                  SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(Point3DFloat.applying(self:_:))
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatApplyAffineTransform(SPPoint3DFloat point,
                                                  SPAffineTransform3DFloat transform) {
 
    simd_float4 rhs = simd_make_float4(point.vector, 1);
    
    simd_float3 transformed = simd_mul(transform.matrix, rhs).xyz;
    
    return SPPoint3DFloatMakeWithVector(transformed);
}

/*!
 @abstract Returns a point that's rotated by the specified rotation around the origin.
 
 @param point The source point.
 @param rotation The rotation.
 @returns A point that's rotated by the specified rotation.
 @discussion This function is equivalent to calling @p SPPoint3DRotateAroundPoint with a zero vector
 for the pivot.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatRotate(SPPoint3DFloat point, SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(Point3DFloat.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatRotate(SPPoint3DFloat point, SPRotation3DFloat rotation) {
    
    SPAffineTransform3DFloat transform = SPAffineTransform3DFloatMakeRotation(rotation);
    
    return SPPoint3DFloatApplyAffineTransform(point, transform);
}

/*!
 @abstract Returns a point that's rotated by a rotation around a specified pivot.
 
 @param point The source point.
 @param rotation The rotation.
 @param pivot The center of rotation.
 @returns A point that's rotated by the specified rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatRotateAroundPoint(SPPoint3DFloat point, SPRotation3DFloat rotation, SPPoint3DFloat pivot)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(Point3DFloat.rotated(self:by:around:))
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatRotateAroundPoint(SPPoint3DFloat point, SPRotation3DFloat rotation, SPPoint3DFloat pivot) {
    
    SPAffineTransform3DFloat transform = SPAffineTransform3DFloatMakeRotation(rotation);
    
    point = SPPoint3DFloatMakeWithVector(point.vector - pivot.vector);
    point = SPPoint3DFloatApplyAffineTransform(point, transform);
    
    return SPPoint3DFloatMakeWithVector(point.vector + pivot.vector);
}

/*!
 @abstract Returns a point that's rotated by the specified quaternion around the origin.
 
 @param point The source point.
 @param quaternion The quaternion that defines the rotation.
 @returns A point that's rotated by the specified rotation.
 @discussion This function is equivalent to calling @p SPPoint3DFloatRotateByQuaternionAroundPoint with a zero vector for the pivot.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatRotateByQuaternion(SPPoint3DFloat point, simd_quatf quaternion)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(Point3DFloat.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatRotateByQuaternion(SPPoint3DFloat point, simd_quatf quaternion) {
    
     SPRotation3DFloat rotation = SPRotation3DFloatMakeWithQuaternion(quaternion);
   
     return SPPoint3DFloatRotate(point, rotation);
}

/*!
 @abstract Returns a point that's rotated by a quaternion around a specified pivot.
 
 @param point The source point.
 @param quaternion The quaternion that defines the rotation.
 @param pivot The center of rotation.
 @returns A point that's rotated by the specified rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatRotateByQuaternionAroundPoint(SPPoint3DFloat point, simd_quatf quaternion, SPPoint3DFloat pivot)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(Point3DFloat.rotated(self:by:around:))
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatRotateByQuaternionAroundPoint(SPPoint3DFloat point, simd_quatf quaternion, SPPoint3DFloat pivot) {
    
     SPRotation3DFloat rotation = SPRotation3DFloatMakeWithQuaternion(quaternion);
    
    
     return SPPoint3DFloatRotateAroundPoint(point, rotation, pivot);
}


/*!
 @abstract Returns a point with an origin that is offset from that of the source point.
 
 @param point The source point.
 @param offset A vector that defines the offset.
 @returns A point that's offset by the @p x, @p y, and @p z of the vector.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatTranslate(SPPoint3DFloat point, SPVector3DFloat offset)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(Point3DFloat.translated(self:by:))
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatTranslate(SPPoint3DFloat point, SPVector3DFloat offset) {
    
    return SPPoint3DFloatMakeWithVector(point.vector + offset.vector);
}

/*!
 @abstract Returns the distance between the origins of two points.
 
 @param point The first point.
 @param other The second point.
 @returns The distance between the two points.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
float SPPoint3DFloatDistanceToPoint(SPPoint3DFloat point, SPPoint3DFloat other)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT // SPATIAL_SWIFT_NAME(Point3DFloat.distance(self:to:))
SPATIAL_OVERLOADABLE
float SPPoint3DFloatDistanceToPoint(SPPoint3DFloat point, SPPoint3DFloat other) {
    return simd_distance(point.vector, other.vector);
}

/*!
 @abstract Returns the @p x, @p y, and @p z components of the point expressed as a simd vector.
 
 @param point The source point.
 @returns A vector that represents the point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_float3 SPPoint3DFloatGetVector(SPPoint3DFloat point)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_float3 SPPoint3DFloatGetVector(SPPoint3DFloat point) {
    return point.vector;
}

// MARK: - Affine and Projctive Transforms



/*!
 @abstract Returns a point that's transformed by the specified projective transform.
 
 @param point The source point.
 @param transform The projective transform that the function applies to the point.
 @returns The transformed point.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatApplyProjectiveTransform(SPPoint3DFloat point,
                                                      SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(Point3DFloat.applying(self:_:))
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatApplyProjectiveTransform(SPPoint3DFloat point,
                                                      SPProjectiveTransform3DFloat transform) {
    
    simd_float4 rhs = simd_make_float4(point.vector, 1);
    
    simd_float3 transformed = simd_mul(transform.matrix, rhs).xyz;
    
    return SPPoint3DFloatMakeWithVector(transformed);
}

/*!
 @abstract Returns a point that's transformed by the inverse of the specified affine transform.
 
 @param point The source point.
 @param transform The affine transform that the function unapplies to the point.
 @returns The transformed point.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatUnapplyAffineTransform(SPPoint3DFloat point,
                                                    SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(Point3DFloat.unapplying(self:_:))
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatUnapplyAffineTransform(SPPoint3DFloat point,
                                                    SPAffineTransform3DFloat transform) {
    
    SPAffineTransform3DFloat invertedTransform = SPAffineTransform3DFloatInverted(transform);
    
    return SPPoint3DFloatApplyAffineTransform(point, invertedTransform);
}

/*!
 @abstract Returns a point that's transformed by the inverse of the specified projective transform.
 
 @param point The source point.
 @param transform The projective transform that the function unapplies to the point.
 @returns The transformed point.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatUnapplyProjectiveTransform(SPPoint3DFloat point,
                                                        SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(Point3DFloat.unapplying(self:_:))
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatUnapplyProjectiveTransform(SPPoint3DFloat point,
                                                        SPProjectiveTransform3DFloat transform) {
    
    SPProjectiveTransform3DFloat invertedTransform = SPProjectiveTransform3DFloatInverted(transform);
    
    return SPPoint3DFloatApplyProjectiveTransform(point, invertedTransform);
}

// MARK: - Transform by Pose

/*!
 @abstract Returns a point that's transformed by the specified pose.
 
 @param point The source point.
 @param pose The pose that the function applies to the point.
 @returns The transformed point.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatApplyPose(SPPoint3DFloat point,
                                       SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatApplyPose(SPPoint3DFloat point,
                                       SPPose3DFloat pose) {
    
    simd_float3 v = simd_act(pose.rotation.quaternion, point.vector);
    v += pose.position.vector;
    
    return SPPoint3DFloatMakeWithVector(v);
}

/*!
 @abstract Returns a point that's transformed by the inverse of the specified pose.
 
 @param point The source point.
 @param pose The pose that the function unapplies to the point.
 @returns The transformed point.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatUnapplyPose(SPPoint3DFloat point,
                                         SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatUnapplyPose(SPPoint3DFloat point,
                                         SPPose3DFloat pose) {
    
    simd_quatf invPoseRot = simd_inverse(pose.rotation.quaternion);
    simd_float3 invPosePos = simd_act(invPoseRot, -pose.position.vector);
    
    simd_float3 v = simd_act(invPoseRot, point.vector);
    v += invPosePos;
    
    return SPPoint3DFloatMakeWithVector(v);
}

// MARK: - Transform by Scaled Pose

/*!
 @abstract Returns a point that's transformed by the specified scaled pose.
 
 @param point The source point.
 @param pose The scaled pose that the function applies to the point.
 @returns The transformed point.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatApplyScaledPose(SPPoint3DFloat point,
                                             SPScaledPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatApplyScaledPose(SPPoint3DFloat point,
                                             SPScaledPose3DFloat pose) {
    
    simd_float3 v = point.vector * pose.scale;
    v = simd_act(pose.rotation.quaternion, v);
    v += pose.position.vector;
    
    return SPPoint3DFloatMakeWithVector(v);
}

/*!
 @abstract Returns a point that's transformed by the inverse of the specified scaled pose.
 
 @param point The source point.
 @param pose The pose that the function unapplies to the point.
 @returns The transformed point.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatUnapplyScaledPose(SPPoint3DFloat point,
                                               SPScaledPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatUnapplyScaledPose(SPPoint3DFloat point,
                                               SPScaledPose3DFloat pose) {
    
    simd_quatf invPoseRot = simd_inverse(pose.rotation.quaternion);
    simd_float3 invPosePos = simd_act(invPoseRot, -pose.position.vector);
    
    simd_float3 v = simd_act(invPoseRot, point.vector);
    v += invPosePos;
    v /= pose.scale;
    
    return SPPoint3DFloatMakeWithVector(v);
}

// MARK: - Equality

/// Returns @p true if both points are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPPoint3DFloatEqualToPoint(SPPoint3DFloat point1, SPPoint3DFloat point2)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPPoint3DFloatEqualToPoint(SPPoint3DFloat point1, SPPoint3DFloat point2) {
    return simd_equal(point1.vector, point2.vector);
}

/*!
 @abstract Returns a Boolean value that indicates whether the two points are equal within the specified default absolute tolerance.
 
 @param p1 The first point.
 @param p2 The first point.
 @returns A Boolean value that indicates whether the two points are equal within the specified default absolute tolerance.
 @note The Spatial default tolerance is @p sqrt(__DBL_EPSILON__) .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPPoint3DFloatAlmostEqualToPoint(SPPoint3DFloat p1,
                                      SPPoint3DFloat p2,
                                      float tolerance)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
bool SPPoint3DFloatAlmostEqualToPoint(SPPoint3DFloat p1,
                                      SPPoint3DFloat p2,
                                      float tolerance) {
    
    return _sp_almost_equal_tolerance(p1.x, p2.x, tolerance) &&
    _sp_almost_equal_tolerance(p1.y, p2.y, tolerance) &&
    _sp_almost_equal_tolerance(p1.z, p2.z, tolerance);
}

/*!
 @abstract Returns a Boolean value that indicates whether the two points are equal within the specified default absolute tolerance.
 
 @param p1 The first point.
 @param p2 The first point.
 @returns A Boolean value that indicates whether the two points are equal within the specified default absolute tolerance.
 @note The Spatial default tolerance is @p sqrt(__DBL_EPSILON__) .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPPoint3DFloatAlmostEqualToPoint(SPPoint3DFloat p1,
                                      SPPoint3DFloat p2)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
bool SPPoint3DFloatAlmostEqualToPoint(SPPoint3DFloat p1,
                                      SPPoint3DFloat p2) {
    
    return SPPoint3DFloatAlmostEqualToPoint(p1, p2, SPDefaultToleranceFloat);
}

// MARK: - Spherical coordinate support

/*!
 @abstract Returns a Spatial point that represents the Cartesian coordinates of the specified spherical coordinates structure.
 
 @param coords The source spherical coordinates structure.
 @returns A new point that contains the spherical coorddinates converted to Cartesian coordinates.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatMakeWithSphericalCoordinates(SPSphericalCoordinates3DFloat coords)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
 
SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatMakeWithSphericalCoordinates(SPSphericalCoordinates3DFloat coords) {
    
    float x = coords.radius * SPAngleFloatCos(coords.inclination) * SPAngleFloatSin(coords.azimuth);
    float y = coords.radius * SPAngleFloatSin(coords.inclination);
    float z = coords.radius * SPAngleFloatCos(coords.inclination) * SPAngleFloatCos(coords.azimuth);

    return SPPoint3DFloatMake(x, y, z);
}

#endif /* SPPoint3DFloat_h */
