#ifndef SPVector3D_h
#define SPVector3D_h

#include <Spatial/Structures.h>
#include <Spatial/SPAffineTransform3D.h>
#include <Spatial/SPProjectiveTransform3D.h>
#include <Spatial/SPPoint3D.h>

// MARK: - SPVector3DMakeWithRotationAxis

/*!
 @abstract Creates a vector with elements specified as dimensions of a rotation axis structure.
 
 @param axis The source rotation axis.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithRotationAxis(SPRotationAxis3D axis)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithRotationAxis(SPRotationAxis3D axis) {
    return SPVector3DMake(axis.vector.x, axis.vector.y, axis.vector.z);
}

// MARK: - SPVector3DMakeWithSize

/*!
 @abstract Creates a vector with elements specified as dimensions of a size structure.
 
 @param size The source size.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithSize(SPSize3D size)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithSize(SPSize3D size) {
    return SPVector3DMake(size.vector.x, size.vector.y, size.vector.z);
}

// MARK: - SPVector3DMakeWithPoint

/*!
 @abstract Creates a vector with elements specified a coordinates of a point structure.
 
 @param point The source point.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithPoint(SPPoint3D point)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithPoint(SPPoint3D point) {
    return SPVector3DMake(point.vector.x, point.vector.y,point.vector.z);
}

// MARK: - SPVector3DEqualToPoint

/// Returns @p true if both points are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPVector3DEqualToVector(SPVector3D vector1, SPVector3D vector2)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPVector3DEqualToVector(SPVector3D vector1, SPVector3D vector2) {
    return simd_equal(vector1.vector, vector2.vector);
}

// MARK: - SPVector3DScaleBy

/*!
 @abstract Returns a vector with elements scaled by the specified values.
 
 @param vector The source vector.
 @param x The scale value for the @p x element.
 @param y The scale value for the @p y element.
 @param z The scale value for the @p z element.
 @returns A vector that's scaled by the specified values.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DScaleBy(SPVector3D vector, double x, double y, double z)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DScaleBy(SPVector3D vector, double x, double y, double z) {
    
    return SPVector3DMakeWithVector(vector.vector * simd_make_double3(x, y, z));
}


// MARK: - SPVector3DApplyAffineTransform

/*!
 @abstract Returns a vector that's transformed by the specified affine transform.
 
 @param vector The source vector.
 @param transform The affine transform that the function applies to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DApplyAffineTransform(SPVector3D vector,
                                          SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DApplyAffineTransform(SPVector3D vector,
                                          SPAffineTransform3D transform) {
    
    simd_double4 rhs = simd_make_double4(vector.vector, 0);
    
    simd_double3 transformed = simd_mul(transform.matrix, rhs).xyz;
    
    return SPVector3DMakeWithVector(transformed);
}

// MARK: - SPVector3DApplyProjectiveTransform

/*!
 @abstract Returns a vector that's transformed by the specified projective transform.
 
 @param vector The source vector.
 @param transform The projective transform that the function applies to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DApplyProjectiveTransform(SPVector3D vector,
                                              SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DApplyProjectiveTransform(SPVector3D vector,
                                              SPProjectiveTransform3D transform) {
    
    simd_double4 rhs = simd_make_double4(vector.vector, 0);
    
    simd_double3 transformed = simd_mul(transform.matrix, rhs).xyz;
    
    return SPVector3DMakeWithVector(transformed);
}

// MARK: - SPVector3DUnapplyAffineTransform

/*!
 @abstract Returns a vector that's transformed by the inverse of the specified affine transform.
 
 @param vector The source vector.
 @param transform The affine transform whose inverse is to be applied to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DUnapplyAffineTransform(SPVector3D vector,
                                            SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DUnapplyAffineTransform(SPVector3D vector,
                                            SPAffineTransform3D transform) {
    
    SPAffineTransform3D invertedTransform = SPAffineTransform3DInverted(transform);
    
    return SPVector3DApplyAffineTransform(vector, invertedTransform);
}

// MARK: - SPVector3DUnapplyProjectiveTransform

/*!
 @abstract Returns a vector that's transformed by the inverse of the specified projective transform.
 
 @param vector The source vector.
 @param transform The projective transform whose inverse is to be applied to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DUnapplyProjectiveTransform(SPVector3D vector,
                                                SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DUnapplyProjectiveTransform(SPVector3D vector,
                                                SPProjectiveTransform3D transform) {
    
    SPProjectiveTransform3D invertedTransform = SPProjectiveTransform3DInverted(transform);
    
    return SPVector3DApplyProjectiveTransform(vector, invertedTransform);
}

// MARK: - SPVector3DRotationToVector

/*!
 @abstract Returns the rotation from the normalized first vector to the normalized second vector.
 
 @param vector The first vector.
 @param other The second vector.
 @returns A rotation structure that represents the rotation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPVector3DRotationToVector(SPVector3D vector, SPVector3D other)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPVector3DRotationToVector(SPVector3D vector, SPVector3D other) {
    
    simd_quatd quaternion = simd_quaternion(simd_normalize(vector.vector),
                                            simd_normalize(other.vector));
    
    return (SPRotation3D) { .quaternion = quaternion };
}

// MARK: - shear

/*!
 @abstract Returns a vector that's sheared over an axis by shear factors for the other two axes.
 
 @param vector The source vector.
 @param shearAxis The shear axis.
 @param shearFactor0 The first shear factor.
 @param shearFactor1 The second shear factor.
 @returns The transformed vector.
 @discussion
 When the shear axis is @p x , @p shearFactor0 is the @p y shear factor and @p shearFactor0 is the @p z shear factor.
 
 When the shear axis is @p y , @p shearFactor0 is the @p x  shear factor and @p shearFactor0 is the @p z shear factor.
 
 When the shear axis is @p z , @p shearFactor0 is the @p x  shear factor and @p shearFactor0 is the @p y shear factor.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DShear(SPVector3D vector,
                           SPAxis shearAxis,
                           double shearFactor0,
                           double shearFactor1)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DShear(SPVector3D vector,
                           SPAxis shearAxis,
                           double shearFactor0,
                           double shearFactor1) {
    
    SPAffineTransform3D shearTransform = SPAffineTransform3DMakeShear(shearAxis,
                                                                      shearFactor0,
                                                                      shearFactor1);
    
    return SPVector3DApplyAffineTransform(vector, shearTransform);
}

// MARK: - SPVector3DScaleBySize

/*!
 @abstract Returns a vector with elements scaled by the specified size.
 
 @param vector The source vector.
 @param scale The scale value.
 @returns A vector that's scaled by the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DScaleBySize(SPVector3D vector, SPSize3D scale)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DScaleBySize(SPVector3D vector, SPSize3D scale) {
    
    return SPVector3DMakeWithVector(vector.vector * scale.vector);
}

// MARK: - SPVector3DScaleUniform

/*!
 @abstract Returns a vector with elements uniformly scaled by the specified value.
 
 @param vector The source vector.
 @param scale The scale value.
 @returns A vector that's uniformly scaled by the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DScaleUniform(SPVector3D vector, double scale)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DScaleUniform(SPVector3D vector, double scale) {
    
    return SPVector3DMakeWithVector(vector.vector * scale);
}

// MARK: - SPVector3DRotate

/*!
 @abstract Returns a vector that's rotated by the specified rotation around the origin.
 
 @param vector The source vector.
 @param rotation The rotation.
 @returns A vector that's rotated by the specified rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DRotate(SPVector3D vector, SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DRotate(SPVector3D vector, SPRotation3D rotation) {
    
    SPAffineTransform3D transform = SPAffineTransform3DMakeRotation(rotation);
    
    return SPVector3DApplyAffineTransform(vector, transform);
}

// MARK: - SPVector3DRotateByQuaternion

/*!
 @abstract Returns a vector that's rotated by the specified quaternion around the origin.
 
 @param vector The source vector.
 @param quaternion The quaternion that defines the rotation.
 @returns A vector that's rotated by the specified quaternion.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DRotateByQuaternion(SPVector3D vector, simd_quatd quaternion)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DRotateByQuaternion(SPVector3D vector, simd_quatd quaternion) {
    
    SPRotation3D rotation = SPRotation3DMakeWithQuaternion(quaternion);
    
    return SPVector3DRotate(vector, rotation);
}

// MARK: - Geometry functions

/*!
 @abstract Returns the dot product of two vectors.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
double SPVector3DDotProduct(SPVector3D x, SPVector3D y)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
double SPVector3DDotProduct(SPVector3D x, SPVector3D y) {
    
    double d = simd_dot(x.vector, y.vector);
    return d;
}

/*!
 @abstract Returns the cross product of two vectors.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DCrossProduct(SPVector3D x, SPVector3D y)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DCrossProduct(SPVector3D x, SPVector3D y) {
    
    simd_double3 d = simd_cross(x.vector, y.vector);
    return SPVector3DMakeWithVector(d);
}

/*!
 @abstract Returns a vector pointing in the same direction of the supplied vector with a length of 1.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DNormalize(SPVector3D x)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DNormalize(SPVector3D x) {
    
    simd_double3 d = simd_normalize(x.vector);
    return SPVector3DMakeWithVector(d);
}

/*!
 @abstract Returns the first vector projected onto the second vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DProject(SPVector3D x, SPVector3D y)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DProject(SPVector3D x, SPVector3D y) {
    
    simd_double3 d = simd_project(x.vector, y.vector);
    return SPVector3DMakeWithVector(d);
}

/*!
 @abstract Returns the reflection direction of an incident vector and a unit normal vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DReflect(SPVector3D x, SPVector3D y)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DReflect(SPVector3D x, SPVector3D y) {
    
    simd_double3 d = simd_reflect(x.vector, y.vector);
    return SPVector3DMakeWithVector(d);
}

/*!
 @abstract Returns the length of the vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
double SPVector3DLength(SPVector3D x)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
double SPVector3DLength(SPVector3D x) {

    return simd_length(x.vector);
}

/*!
 @abstract Returns the squared length of the vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
double SPVector3DLengthSquared(SPVector3D x)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
double SPVector3DLengthSquared(SPVector3D x) {

    return simd_length_squared(x.vector);
}

// MARK: - Transform by Pose

/*!
 @abstract Returns a vector that's transformed by the specified pose.
 
 @param vector The source vector.
 @param pose The pose that the function applies to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DApplyPose(SPVector3D vector,
                               SPPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DApplyPose(SPVector3D vector,
                               SPPose3D pose) {
    
    return SPVector3DRotate(vector, pose.rotation);
}

/*!
 @abstract Returns a vector that's transformed by the inverse of the specified pose.
 
 @param vector The source vector.
 @param pose The pose that the function unapplies to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DUnapplyPose(SPVector3D vector,
                                 SPPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DUnapplyPose(SPVector3D vector,
                                 SPPose3D pose) {
    
    return SPVector3DRotate(vector, SPRotation3DInverse(pose.rotation));
}

// MARK: - Transform by Scaled Pose

/*!
 @abstract Returns a vector that's transformed by the specified scaled pose.
 
 @param vector The source vector.
 @param pose The scaled pose that the function applies to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DApplyScaledPose(SPVector3D vector,
                                     SPScaledPose3D pose)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DApplyScaledPose(SPVector3D vector,
                                     SPScaledPose3D pose) {
    
    simd_double3 v = vector.vector * pose.scale;
    v = simd_act(pose.rotation.quaternion, v);
    
    return SPVector3DMakeWithVector(v);
}

/*!
 @abstract Returns a vector that's transformed by the inverse of the specified scaled pose.
 
 @param vector The source vector.
 @param pose The pose that the function unapplies to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DUnapplyScaledPose(SPVector3D vector,
                                       SPScaledPose3D pose)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DUnapplyScaledPose(SPVector3D vector,
                                       SPScaledPose3D pose) {
    
    simd_quatd invPoseRot = simd_inverse(pose.rotation.quaternion);
    simd_double3 invPosePos = simd_act(invPoseRot, -pose.position.vector);
    
    simd_double3 v = simd_act(invPoseRot, vector.vector);
    v /= pose.scale;
    
    return SPVector3DMakeWithVector(v);
}

// MARK: - Spherical coordinate support

/*!
 @abstract Returns a Spatial vector that represents the Cartesian coordinates of the specified spherical coordinates structure.
 
 @param coords The source spherical coordinates structure.
 @returns A new vector that contains the spherical coorddinates converted to Cartesian coordinates.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithSphericalCoordinates(SPSphericalCoordinates3D coords)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithSphericalCoordinates(SPSphericalCoordinates3D coords) {
    
    SPPoint3D point = SPPoint3DMakeWithSphericalCoordinates(coords);
    
    return SPVector3DMakeWithPoint(point);
}

/*!
 @abstract Returns a Spatial vector that represents the linear interpolation at @p t between two vectors.
 
 @param from The starting vector.
 @param to The ending vector.
 @param t The value, between @p 0 and @p 1, that the function interpolates at.
 
 @returns A new rotation. When @p t=0, the result is the @p from vector. When @p t=1.0, the result
 is the @p to vector. For any other value of @p t, the result is a linear linear interpolation between the
 two vectors.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DLerp(SPVector3D from, SPVector3D to, SPVector3D t)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DLerp(SPVector3D from, SPVector3D to, SPVector3D t) {
    
    return SPVector3DMakeWithVector(simd_mix(from.vector, to.vector, t.vector));
}

/*!
 @abstract Returns a Spatial vector that represents the smooth interpolation at @p x between two vectors.
 
 @param edge0 The lower edge of the interpolation function.
 @param edge1 The upper edge of the interpolation function.
 @param x The value that the function interpolates at.
 
 @returns A new vector with each element set to `0` if `x <= edge0`, `1` if `x >= edge1`, and a Hermite interpolation between `0` and `1` if `edge0 < x < edge1`.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DSmoothstep(SPVector3D edge0, SPVector3D edge1, SPVector3D x)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DSmoothstep(SPVector3D edge0, SPVector3D edge1, SPVector3D x) {
    
    return SPVector3DMakeWithVector(simd_smoothstep(edge0.vector, edge1.vector, x.vector));
}

#endif /* SPVector3D_h */
