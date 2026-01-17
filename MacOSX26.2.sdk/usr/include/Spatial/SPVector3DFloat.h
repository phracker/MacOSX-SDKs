#ifndef SPVector3DFloat_h
#define SPVector3DFloat_h

#include <Spatial/StructuresFloat.h>
#include <Spatial/SPAffineTransform3DFloat.h>
#include <Spatial/SPProjectiveTransform3DFloat.h>
#include <Spatial/SPPoint3DFloat.h>


// MARK: - SINGLE-PRECISION

// MARK: - SPVector3DFloatMakeWithRotationAxis

/*!
 @abstract Creates a vector with elements specified as dimensions of a rotation axis structure.
 
 @param axis The source rotation axis.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMakeWithRotationAxis(SPRotationAxis3DFloat axis)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMakeWithRotationAxis(SPRotationAxis3DFloat axis) {
    return SPVector3DFloatMake(axis.vector.x, axis.vector.y, axis.vector.z);
}

// MARK: - SPVector3DFloatMakeWithSize

/*!
 @abstract Creates a vector with elements specified as dimensions of a size structure.
 
 @param size The source size.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMakeWithSize(SPSize3DFloat size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMakeWithSize(SPSize3DFloat size) {
    return SPVector3DFloatMake(size.vector.x, size.vector.y, size.vector.z);
}

// MARK: - SPVector3DFloatMakeWithPoint

/*!
 @abstract Creates a vector with elements specified a coordinates of a point structure.
 
 @param point The source point.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMakeWithPoint(SPPoint3DFloat point)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMakeWithPoint(SPPoint3DFloat point) {
    return SPVector3DFloatMake(point.vector.x, point.vector.y,point.vector.z);
}

// MARK: - SPVector3DFloatEqualToPoint

/// Returns @p true if both points are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPVector3DFloatEqualToVector(SPVector3DFloat vector1, SPVector3DFloat vector2)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPVector3DFloatEqualToVector(SPVector3DFloat vector1, SPVector3DFloat vector2) {
    return simd_equal(vector1.vector, vector2.vector);
}

// MARK: - SPVector3DFloatScaleBy

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
SPVector3DFloat SPVector3DFloatScaleBy(SPVector3DFloat vector, float x, float y, float z)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatScaleBy(SPVector3DFloat vector, float x, float y, float z) {
    
    return SPVector3DFloatMakeWithVector(vector.vector * simd_make_float3(x, y, z));
}


// MARK: - SPVector3DFloatApplyAffineTransform

/*!
 @abstract Returns a vector that's transformed by the specified affine transform.
 
 @param vector The source vector.
 @param transform The affine transform that the function applies to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatApplyAffineTransform(SPVector3DFloat vector,
                                                    SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatApplyAffineTransform(SPVector3DFloat vector,
                                                    SPAffineTransform3DFloat transform) {
    
    simd_float4 rhs = simd_make_float4(vector.vector, 0);
    
    simd_float3 transformed = simd_mul(transform.matrix, rhs).xyz;
    
    return SPVector3DFloatMakeWithVector(transformed);
}

// MARK: - SPVector3DFloatApplyProjectiveTransform

/*!
 @abstract Returns a vector that's transformed by the specified projective transform.
 
 @param vector The source vector.
 @param transform The projective transform that the function applies to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatApplyProjectiveTransform(SPVector3DFloat vector,
                                                        SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatApplyProjectiveTransform(SPVector3DFloat vector,
                                                        SPProjectiveTransform3DFloat transform) {
    
    simd_float4 rhs = simd_make_float4(vector.vector, 0);
    
    simd_float3 transformed = simd_mul(transform.matrix, rhs).xyz;
    
    return SPVector3DFloatMakeWithVector(transformed);
}

// MARK: - SPVector3DFloatUnapplyAffineTransform

/*!
 @abstract Returns a vector that's transformed by the inverse of the specified affine transform.
 
 @param vector The source vector.
 @param transform The affine transform whose inverse is to be applied to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatUnapplyAffineTransform(SPVector3DFloat vector,
                                                      SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatUnapplyAffineTransform(SPVector3DFloat vector,
                                                      SPAffineTransform3DFloat transform) {
    
        SPAffineTransform3DFloat invertedTransform = SPAffineTransform3DFloatInverted(transform);
    
        return SPVector3DFloatApplyAffineTransform(vector, invertedTransform);
}

// MARK: - SPVector3DFloatUnapplyProjectiveTransform

/*!
 @abstract Returns a vector that's transformed by the inverse of the specified projective transform.
 
 @param vector The source vector.
 @param transform The projective transform whose inverse is to be applied to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatUnapplyProjectiveTransform(SPVector3DFloat vector,
                                                          SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatUnapplyProjectiveTransform(SPVector3DFloat vector,
                                                          SPProjectiveTransform3DFloat transform) {
    
        SPProjectiveTransform3DFloat invertedTransform = SPProjectiveTransform3DFloatInverted(transform);
    
        return SPVector3DFloatApplyProjectiveTransform(vector, invertedTransform);
}

// MARK: - SPVector3DFloatRotationToVector

/*!
 @abstract Returns the rotation from the normalized first vector to the normalized second vector.
 
 @param vector The first vector.
 @param other The second vector.
 @returns A rotation structure that represents the rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPVector3DFloatRotationToVector(SPVector3DFloat vector, SPVector3DFloat other)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPVector3DFloatRotationToVector(SPVector3DFloat vector, SPVector3DFloat other) {
    
    simd_quatf quaternion = simd_quaternion(simd_normalize(vector.vector),
                                            simd_normalize(other.vector));
    
    return (SPRotation3DFloat) { .quaternion = quaternion };
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
SPVector3DFloat SPVector3DFloatShear(SPVector3DFloat vector,
                                     SPAxis shearAxis,
                                     float shearFactor0,
                                     float shearFactor1)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatShear(SPVector3DFloat vector,
                                     SPAxis shearAxis,
                                     float shearFactor0,
                                     float shearFactor1) {
    
        SPAffineTransform3DFloat shearTransform = SPAffineTransform3DFloatMakeShear(shearAxis,
                                                                          shearFactor0,
                                                                          shearFactor1);
    
        return SPVector3DFloatApplyAffineTransform(vector, shearTransform);
}

// MARK: - SPVector3DFloatScaleBySize

/*!
 @abstract Returns a vector with elements scaled by the specified size.
 
 @param vector The source vector.
 @param scale The scale value.
 @returns A vector that's scaled by the specified value.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatScaleBySize(SPVector3DFloat vector, SPSize3DFloat scale)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatScaleBySize(SPVector3DFloat vector, SPSize3DFloat scale) {
    
    return SPVector3DFloatMakeWithVector(vector.vector * scale.vector);
}

// MARK: - SPVector3DFloatScaleUniform

/*!
 @abstract Returns a vector with elements uniformly scaled by the specified value.
 
 @param vector The source vector.
 @param scale The scale value.
 @returns A vector that's uniformly scaled by the specified value.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatScaleUniform(SPVector3DFloat vector, float scale)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatScaleUniform(SPVector3DFloat vector, float scale) {
    
    return SPVector3DFloatMakeWithVector(vector.vector * scale);
}

// MARK: - SPVector3DFloatRotate

/*!
 @abstract Returns a vector that's rotated by the specified rotation around the origin.
 
 @param vector The source vector.
 @param rotation The rotation.
 @returns A vector that's rotated by the specified rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatRotate(SPVector3DFloat vector, SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatRotate(SPVector3DFloat vector, SPRotation3DFloat rotation) {
    
        SPAffineTransform3DFloat transform = SPAffineTransform3DFloatMakeRotation(rotation);
    
        return SPVector3DFloatApplyAffineTransform(vector, transform);
}

// MARK: - SPVector3DFloatRotateByQuaternion

/*!
 @abstract Returns a vector that's rotated by the specified quaternion around the origin.
 
 @param vector The source vector.
 @param quaternion The quaternion that defines the rotation.
 @returns A vector that's rotated by the specified quaternion.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatRotateByQuaternion(SPVector3DFloat vector, simd_quatf quaternion)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatRotateByQuaternion(SPVector3DFloat vector, simd_quatf quaternion) {
    
    SPRotation3DFloat rotation = SPRotation3DFloatMakeWithQuaternion(quaternion);
    
    return SPVector3DFloatRotate(vector, rotation);
}

// MARK: - Geometry functions

/*!
 @abstract Returns the dot product of two vectors.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
float SPVector3DFloatDotProduct(SPVector3DFloat x, SPVector3DFloat y)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
float SPVector3DFloatDotProduct(SPVector3DFloat x, SPVector3DFloat y) {
    
    float d = simd_dot(x.vector, y.vector);
    return d;
}

/*!
 @abstract Returns the cross product of two vectors.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatCrossProduct(SPVector3DFloat x, SPVector3DFloat y)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatCrossProduct(SPVector3DFloat x, SPVector3DFloat y) {
    
    simd_float3 d = simd_cross(x.vector, y.vector);
    return SPVector3DFloatMakeWithVector(d);
}

/*!
 @abstract Returns a vector pointing in the same direction of the supplied vector with a length of 1.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatNormalize(SPVector3DFloat x)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatNormalize(SPVector3DFloat x) {
    
    simd_float3 d = simd_normalize(x.vector);
    return SPVector3DFloatMakeWithVector(d);
}

/*!
 @abstract Returns the first vector projected onto the second vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatProject(SPVector3DFloat x, SPVector3DFloat y)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatProject(SPVector3DFloat x, SPVector3DFloat y) {
    
    simd_float3 d = simd_project(x.vector, y.vector);
    return SPVector3DFloatMakeWithVector(d);
}

/*!
 @abstract Returns the reflection direction of an incident vector and a unit normal vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatReflect(SPVector3DFloat x, SPVector3DFloat y)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatReflect(SPVector3DFloat x, SPVector3DFloat y) {
    
    simd_float3 d = simd_reflect(x.vector, y.vector);
    return SPVector3DFloatMakeWithVector(d);
}

/*!
 @abstract Returns the length of the vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
float SPVector3DFloatLength(SPVector3DFloat x)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
float SPVector3DFloatLength(SPVector3DFloat x) {
    
    return simd_length(x.vector);
}

/*!
 @abstract Returns the squared length of the vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
float SPVector3DFloatLengthSquared(SPVector3DFloat x)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
float SPVector3DFloatLengthSquared(SPVector3DFloat x) {
    
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
SPVector3DFloat SPVector3DFloatApplyPose(SPVector3DFloat vector,
                                         SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatApplyPose(SPVector3DFloat vector,
                                         SPPose3DFloat pose) {
    
    return SPVector3DFloatRotate(vector, pose.rotation);
}

/*!
 @abstract Returns a vector that's transformed by the inverse of the specified pose.
 
 @param vector The source vector.
 @param pose The pose that the function unapplies to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatUnapplyPose(SPVector3DFloat vector,
                                           SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatUnapplyPose(SPVector3DFloat vector,
                                           SPPose3DFloat pose) {
    
    return SPVector3DFloatRotate(vector, SPRotation3DFloatInverse(pose.rotation));
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
SPVector3DFloat SPVector3DFloatApplyScaledPose(SPVector3DFloat vector,
                                               SPScaledPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatApplyScaledPose(SPVector3DFloat vector,
                                               SPScaledPose3DFloat pose) {
    
    simd_float3 v = vector.vector * pose.scale;
    v = simd_act(pose.rotation.quaternion, v);
    
    return SPVector3DFloatMakeWithVector(v);
}

/*!
 @abstract Returns a vector that's transformed by the inverse of the specified scaled pose.
 
 @param vector The source vector.
 @param pose The pose that the function unapplies to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatUnapplyScaledPose(SPVector3DFloat vector,
                                                 SPScaledPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatUnapplyScaledPose(SPVector3DFloat vector,
                                                 SPScaledPose3DFloat pose) {
    
    simd_quatf invPoseRot = simd_inverse(pose.rotation.quaternion);
    simd_float3 invPosePos = simd_act(invPoseRot, -pose.position.vector);
    
    simd_float3 v = simd_act(invPoseRot, vector.vector);
    v /= pose.scale;
    
    return SPVector3DFloatMakeWithVector(v);
}

// MARK: - Spherical coordinate support

/*!
 @abstract Returns a Spatial vector that represents the Cartesian coordinates of the specified spherical coordinates structure.
 
 @param coords The source spherical coordinates structure.
 @returns A new vector that contains the spherical coorddinates converted to Cartesian coordinates.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMakeWithSphericalCoordinates(SPSphericalCoordinates3DFloat coords)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMakeWithSphericalCoordinates(SPSphericalCoordinates3DFloat coords) {
    
    SPPoint3DFloat point = SPPoint3DFloatMakeWithSphericalCoordinates(coords);
    
    return SPVector3DFloatMakeWithPoint(point);
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
SPVector3DFloat SPVector3DFloatLerp(SPVector3DFloat from, SPVector3DFloat to, SPVector3DFloat t)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatLerp(SPVector3DFloat from, SPVector3DFloat to, SPVector3DFloat t) {
    
    return SPVector3DFloatMakeWithVector(simd_mix(from.vector, to.vector, t.vector));
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
SPVector3DFloat SPVector3DFloatSmoothstep(SPVector3DFloat edge0, SPVector3DFloat edge1, SPVector3DFloat x)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatSmoothstep(SPVector3DFloat edge0, SPVector3DFloat edge1, SPVector3DFloat x) {
    
    return SPVector3DFloatMakeWithVector(simd_smoothstep(edge0.vector, edge1.vector, x.vector));
}

#endif /* SPVector3DFloat_h */
