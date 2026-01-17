#ifndef SpatialTypeConversion_h
#define SpatialTypeConversion_h

#include <Spatial/Structures.h>
#include <Spatial/StructuresFloat.h>

// MARK: - Angle

/*!
 @abstract Returns a single-precision angle from a double-precision angle.
 
 @param degrees The angle.
 @returns A new angle structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatMake(SPAngle angle)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatMake(SPAngle angle) {
    return (SPAngleFloat){ .radians = (float)angle.radians };
}

/*!
 @abstract Returns a double-precision angle from a single-precision angle.
 
 @param degrees The angle.
 @returns A new angle structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngle SPAngleMake(SPAngleFloat angle)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngle SPAngleMake(SPAngleFloat angle) {
    return (SPAngle){ .radians = (double)angle.radians };
}

// MARK: - Rotation Axis

/*!
 @abstract Returns a single-precision rotation axis from a double-precision rotation axis.
 
 @param axis The rotation axis.
 @returns A new rotation axis.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotationAxis3DFloat SPRotationAxis3DFloatMake(SPRotationAxis3D axis)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotationAxis3DFloat SPRotationAxis3DFloatMake(SPRotationAxis3D axis) {
    return  SPRotationAxis3DFloatMake((float)axis.x, (float)axis.y, (float)axis.z);
}

/*!
 @abstract Returns a double-precision rotation axis from a single-precision rotation axis.
 
 @param axis The rotation axis.
 @returns A new rotation axis.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotationAxis3D SPRotationAxis3DMake(SPRotationAxis3DFloat axis)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotationAxis3D SPRotationAxis3DMake(SPRotationAxis3DFloat axis) {
    return  SPRotationAxis3DMake((double)axis.x, (double)axis.y, (double)axis.z);
}

// MARK: - Rotation

/*!
 @abstract Returns a single-precision rotation from a double-precision rotation.
 
 @param axis The rotation.
 @returns A new rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMake(SPRotation3D rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMake(SPRotation3D rotation) {
    return  SPRotation3DFloatMakeWithQuaternion(simd_quaternion(simd_float(rotation.quaternion.vector)));
}

/*!
 @abstract Returns a double-precision rotation from a single-precision rotation.
 
 @param axis The rotation.
 @returns A new rotation..
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMake(SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMake(SPRotation3DFloat rotation) {
    return  SPRotation3DMakeWithQuaternion(simd_quaternion(simd_double(rotation.quaternion.vector)));
}

// MARK: - Point

/*!
 @abstract Returns a single-precision point from a double-precision point.
 
 @param point The point.
 @returns A new point.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatMake(SPPoint3D point)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatMake(SPPoint3D point) {
    return  SPPoint3DFloatMakeWithVector(simd_float(point.vector));
}

/*!
 @abstract Returns a double-precision point from a single-precision point.
 
 @param point The point.
 @returns A new point.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DMake(SPPoint3DFloat point)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DMake(SPPoint3DFloat point) {
    return  SPPoint3DMakeWithVector(simd_double(point.vector));
}

// MARK: - Vector

/*!
 @abstract Returns a single-precision vector from a double-precision vector.
 
 @param vector The vector.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMake(SPVector3D vector)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMake(SPVector3D vector) {
    return  SPVector3DFloatMakeWithVector(simd_float(vector.vector));
}

/*!
 @abstract Returns a double-precision vector from a single-precision vector.
 
 @param vector The vector.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMake(SPVector3DFloat vector)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMake(SPVector3DFloat vector) {
    return  SPVector3DMakeWithVector(simd_double(vector.vector));
}

// MARK: - Size

/*!
 @abstract Returns a single-precision size from a double-precision size.
 
 @param size The size.
 @returns A new size.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatMake(SPSize3D size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatMake(SPSize3D size) {
    return  SPSize3DFloatMakeWithVector(simd_float(size.vector));
}

/*!
 @abstract Returns a double-precision size from a single-precision size.
 
 @param size The size.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DMake(SPSize3DFloat size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DMake(SPSize3DFloat size) {
    return  SPSize3DMakeWithVector(simd_double(size.vector));
}

// MARK: - Rect

/*!
 @abstract Returns a single-precision rectangle from a double-precision rectangle.
 
 @param rect The rectangle.
 @returns A new rectangle.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMake(SPRect3D rect)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMake(SPRect3D rect) {
    return SPRect3DFloatMakeAtOrigin(SPPoint3DFloatMake(rect.origin),
                                     SPSize3DFloatMake(rect.size));
}

/*!
 @abstract Returns a double-precision rectangle from a single-precision rectangle.
 
 @param rect The rectangle.
 @returns A new rectangle.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMake(SPRect3DFloat rect)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMake(SPRect3DFloat rect) {
    return SPRect3DMakeAtOrigin(SPPoint3DMake(rect.origin),
                                SPSize3DMake(rect.size));
}

// MARK: - Ray

/*!
 @abstract Returns a single-precision ray from a double-precision ray.
 
 @param ray The ray.
 @returns A new ray.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatMake(SPRay3D ray)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatMake(SPRay3D ray) {
    return SPRay3DFloatMake(SPPoint3DFloatMake(ray.origin),
                            SPVector3DFloatMake(ray.direction));
}

/*!
 @abstract Returns a double-precision ray from a single-precision ray.
 
 @param ray The ray.
 @returns A new ray.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DMake(SPRay3DFloat ray)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DMake(SPRay3DFloat ray) {
    return SPRay3DMake(SPPoint3DMake(ray.origin),
                       SPVector3DMake(ray.direction));
}

// MARK: - Pose

/*!
 @abstract Returns a single-precision pose from a double-precision pose.
 
 @param pose The pose.
 @returns A new pose.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMake(SPPose3D pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMake(SPPose3D pose) {
    return SPPose3DFloatMake(SPPoint3DFloatMake(pose.position),
                             SPRotation3DFloatMake(pose.rotation));
}

/*!
 @abstract Returns a double-precision pose from a single-precision pose.
 
 @param pose The pose.
 @returns A new pose.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3D SPPose3DMake(SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3D SPPose3DMake(SPPose3DFloat pose) {
    return SPPose3DMake(SPPoint3DMake(pose.position),
                        SPRotation3DMake(pose.rotation));
}

// MARK: - Scaled pose

/*!
 @abstract Returns a single-precision scaled pose from a double-precision scaled pose.
 
 @param pose The pose.
 @returns A new pose.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMake(SPScaledPose3D pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMake(SPScaledPose3D pose) {
    return SPScaledPose3DFloatMake(SPPoint3DFloatMake(pose.position),
                                   SPRotation3DFloatMake(pose.rotation),
                                   (float)pose.scale);
}

/*!
 @abstract Returns a double-precision pose from a single-precision pose.
 
 @param pose The pose.
 @returns A new pose.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DMake(SPScaledPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DMake(SPScaledPose3DFloat pose) {
    return SPScaledPose3DMake(SPPoint3DMake(pose.position),
                              SPRotation3DMake(pose.rotation),
                              (double)pose.scale);
}

// MARK: - Affine

/*!
 @abstract Returns a single-precision affine transformation from a double-precision affine transformation.
 
 @param transform The transform.
 @returns A new transform.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMake(SPAffineTransform3D transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMake(SPAffineTransform3D transform) {
    simd_float3 column0 = simd_float(transform.matrix.columns[0]);
    simd_float3 column1 = simd_float(transform.matrix.columns[1]);
    simd_float3 column2 = simd_float(transform.matrix.columns[2]);
    simd_float3 column3 = simd_float(transform.matrix.columns[3]);
    
    SPAffineTransform3DFloat affine = { .matrix = simd_matrix(column0,
                                                              column1,
                                                              column2,
                                                              column3) };
    
    return affine;
}

/*!
 @abstract Returns a double-precision affine transformation from a single-precision affine transformation.
 
 @param transform The transform.
 @returns A new transform.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMake(SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMake(SPAffineTransform3DFloat transform) {
    simd_double3 column0 = simd_double(transform.matrix.columns[0]);
    simd_double3 column1 = simd_double(transform.matrix.columns[1]);
    simd_double3 column2 = simd_double(transform.matrix.columns[2]);
    simd_double3 column3 = simd_double(transform.matrix.columns[3]);
    
    SPAffineTransform3D affine = { .matrix = simd_matrix(column0,
                                                         column1,
                                                         column2,
                                                         column3) };
    
    return affine;
}

// MARK: - Projective

/*!
@abstract Returns a single-precision projective transformation from a double-precision projective transformation.

@param transform The transform.
@returns A new transform.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMake(SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMake(SPProjectiveTransform3D transform) {
   simd_float4 column0 = simd_float(transform.matrix.columns[0]);
   simd_float4 column1 = simd_float(transform.matrix.columns[1]);
   simd_float4 column2 = simd_float(transform.matrix.columns[2]);
   simd_float4 column3 = simd_float(transform.matrix.columns[3]);
   
    SPProjectiveTransform3DFloat projective = { .matrix = simd_matrix(column0,
                                                             column1,
                                                             column2,
                                                             column3) };
   
   return projective;
}

/*!
 @abstract Returns a double-precision projective transformation from a single-precision projective transformation.
 
 @param transform The transform.
 @returns A new transform.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMake(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMake(SPProjectiveTransform3DFloat transform) {
    simd_double4 column0 = simd_double(transform.matrix.columns[0]);
    simd_double4 column1 = simd_double(transform.matrix.columns[1]);
    simd_double4 column2 = simd_double(transform.matrix.columns[2]);
    simd_double4 column3 = simd_double(transform.matrix.columns[3]);
    
    SPProjectiveTransform3D projective = { .matrix = simd_matrix(column0,
                                                                 column1,
                                                                 column2,
                                                                 column3) };
    
    return projective;
}

// MARK: - Spherical coordinates

/*!
 @abstract Returns a single-precision spherical coordinates structure from a double-precision spherical coordinates structure.
 
 @param coords The spherical coordinates structure.
 @returns A new  spherical coordinates structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3DFloat SPSphericalCoordinates3DFloatMake(SPSphericalCoordinates3D coords)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3DFloat SPSphericalCoordinates3DFloatMake(SPSphericalCoordinates3D coords) {
    
    return SPSphericalCoordinates3DFloatMake((float)coords.radius,
                                             SPAngleFloatMake(coords.inclination),
                                             SPAngleFloatMake(coords.azimuth));
}

/*!
 @abstract Returns a double-precision spherical coordinates structure from a single-precision spherical coordinates structure.
 
 @param coords The spherical coordinates structure.
 @returns A new  spherical coordinates structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3D SPSphericalCoordinates3DMake(SPSphericalCoordinates3DFloat coords)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3D SPSphericalCoordinates3DMake(SPSphericalCoordinates3DFloat coords) {
    
    return SPSphericalCoordinates3DMake((double)coords.radius,
                                        SPAngleMake(coords.inclination),
                                        SPAngleMake(coords.azimuth));
}

#endif /* SpatialTypeConversion_h */
