#ifndef SPSize3DFloat_h
#define SPSize3DFloat_h


#include <Spatial/StructuresFloat.h>
#include <Spatial/SPRect3DFloat.h>
#include <Spatial/SPAffineTransform3DFloat.h>
#include <Spatial/SPProjectiveTransform3DFloat.h>
#include <math.h>

// MARK: - SINGLE-PRECISION Public API

// MARK: - Creating a size

/*!
 @abstract Creates a size structure with dimensions specified as a Spatial vector.
 
 @param xyz The source vector.
 @returns A new size stucture.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatMakeWithVector(SPVector3DFloat xyz)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Creates a size structure with dimensions specified as the coordinates of a  point structure.
 
 @param point The source point.
 @returns A new size stucture.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatMakeWithPoint(SPPoint3DFloat point)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Querying size properties

/*!
 @abstract Returns the @p width, @p height, and @p depth components of the size expressed as a simd vector.
 
 @param size The source size.
 @returns A vector that represents the size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_float3 SPSize3DFloatGetVector(SPSize3DFloat size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/// Returns @p true if both sizes are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DFloatEqualToSize(SPSize3DFloat size1, SPSize3DFloat size2)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Transforming a size

/*!
 @abstract Returns a size with dimensions scaled by the specified values.
 
 @param size The source size.
 @param x The scale value along the @p width dimension.
 @param y The scale value along the @p height dimension.
 @param z The scale value along the @p depth dimension.
 @returns A size that's scaled by the specified values.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatScaleBy(SPSize3DFloat size, float x, float y, float z)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a size with dimensions scaled by the specified size.
 
 @param size The source size.
 @param scale The scale value.
 @returns A size that's scaled by the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatScaleBySize(SPSize3DFloat size, SPSize3DFloat scale)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a size with dimensions uniformly scaled by the specified value.
 
 @param size The source size.
 @param scale The scale value.
 @returns A size that's uniformly scaled by the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatScaleUniform(SPSize3DFloat size, float scale)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a size that's rotated by the specified rotation around the origin.
 
 @param size The source size.
 @param rotation The rotation.
 @returns A size that's rotated by the specified rotation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatRotate(SPSize3DFloat size, SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a size that's rotated by the specified quaternion around the origin.
 
 @param size The source size.
 @param quaternion The quaternion that defines the rotation.
 @returns A size that's rotated by the specified rotation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatRotateByQuaternion(SPSize3DFloat size, simd_quatf quaternion)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a size that's transformed by the specified affine transform.
 
 @param size The source size.
 @param transform The affine transform that the function applies to the size.
 @returns The transformed size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatApplyAffineTransform(SPSize3DFloat size,
                                      SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a size that's transformed by the specified projective transform.
 
 @param size The source size.
 @param transform The projective transform that the function applies to the size.
 @returns The transformed size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatApplyProjectiveTransform(SPSize3DFloat size,
                                          SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a size that's transformed by the inverse of the specified affine transform.
 
 @param size The source size.
 @param transform The affine transform that the function unapplies to the size.
 @returns The transformed size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatUnapplyAffineTransform(SPSize3DFloat size,
                                        SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a size that's transformed by the inverse of the specified projective transform.
 
 @param size The source size.
 @param transform The projective transform that the function unapplies to the size.
 @returns The transformed size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatUnapplyProjectiveTransform(SPSize3DFloat size,
                                            SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a size that's sheared over an axis by shear factors for the other two axes.
 
 @param size The source size.
 @param shearAxis The shear axis.
 @param shearFactor0 The first shear factor.
 @param shearFactor1 The second shear factor.
 @returns The transformed size.
 @discussion
 When the shear axis is @p x , @p shearFactor0 is the @p y shear factor and @p shearFactor0 is the @p z shear factor.
 
 When the shear axis is @p y , @p shearFactor0 is the @p x  shear factor and @p shearFactor0 is the @p z shear factor.
 
 When the shear axis is @p z , @p shearFactor0 is the @p x  shear factor and @p shearFactor0 is the @p y shear factor.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatShear(SPSize3DFloat size,
                       SPAxis shearAxis,
                       float shearFactor0,
                       float shearFactor1)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Deriving new sizes

/*!
 @abstract Returns the smallest size that contains two sizes.
 
 @param size The first size.
 @param other The second size.
 @returns A size structure that is the smallest size that contains two sizes.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatUnion(SPSize3DFloat size, SPSize3DFloat other)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns the intersection of the two sizes.
 
 @param size The first size.
 @param other The second size.
 @returns A size structure that is the intersection of the two sizes.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatIntersection(SPSize3DFloat size, SPSize3DFloat other)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Volumetric operations

/*!
 @abstract Returns a Boolean value that indicates whether the first size contains the second size.
 
 @param size The first size.
 @param other The second size.
 @returns A Boolean value that indicates whether the first size contains the second size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DFloatContainsSize(SPSize3DFloat size, SPSize3DFloat other)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the size contains the point.
 
 @param size The size.
 @param other The point.
 @returns A Boolean value that indicates whether the size contains the point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DFloatContainsPoint(SPSize3DFloat size, SPPoint3DFloat other)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the size contains any of the specified points.
 
 @param size The size.
 @param points The points.
 @param pointCount The number of points.
 @returns A Boolean value that indicates whether the size contains any of the specified points.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DFloatContainsAnyPoint(SPSize3DFloat size,
                               const SPPoint3DFloat *points, int pointCount)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: Header inline implementations

// MARK: - Creating a size

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatMakeWithVector(SPVector3DFloat xyz) {
    return SPSize3DFloatMake(xyz.vector.x, xyz.vector.y, xyz.vector.z);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatMakeWithPoint(SPPoint3DFloat point) {
    return SPSize3DFloatMake(point.vector.x, point.vector.y, point.vector.z);
}

// MARK: - Querying size properties

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_float3 SPSize3DFloatGetVector(SPSize3DFloat size) {
    return size.vector;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPSize3DFloatEqualToSize(SPSize3DFloat size1, SPSize3DFloat size2) {
    return simd_equal(size1.vector, size2.vector);
}
// MARK: - Transforming a size

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatScaleBy(SPSize3DFloat size, float x, float y, float z) {
    
    return SPSize3DFloatMakeWithVector(size.vector * simd_make_float3(x, y, z));
}

SPATIAL_SWIFT_NAME(Size3DFloat.scaled(self:by:))
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatScaleBySize(SPSize3DFloat size, SPSize3DFloat scale) {
    
    return SPSize3DFloatMakeWithVector(size.vector * scale.vector);
}

SPATIAL_SWIFT_NAME(Size3DFloat.uniformlyScaled(self:by:))
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatScaleUniform(SPSize3DFloat size, float scale) {
    
    return SPSize3DFloatMakeWithVector(size.vector * scale);
}

SPATIAL_SWIFT_NAME(Size3DFloat.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatRotate(SPSize3DFloat size, SPRotation3DFloat rotation) {
    
    SPAffineTransform3DFloat t = SPAffineTransform3DFloatMakeRotation(rotation);

    return SPSize3DFloatApplyAffineTransform(size, t);
}

SPATIAL_SWIFT_NAME(Size3DFloat.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatRotateByQuaternion(SPSize3DFloat size, simd_quatf quaternion) {

    SPRotation3DFloat r = SPRotation3DFloatMakeWithQuaternion(quaternion);
  
    return SPSize3DFloatRotate(size, r);
}

SPATIAL_SWIFT_NAME(Size3DFloat.applying(self:_:))
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatApplyAffineTransform(SPSize3DFloat size, SPAffineTransform3DFloat transform) {
    
    simd_float4 rhs = simd_make_float4(size.vector, 0);
    
    simd_float3 transformed = simd_mul(transform.matrix, rhs).xyz;
    
    return SPSize3DFloatMakeWithVector(transformed);
}

SPATIAL_SWIFT_NAME(Size3DFloat.applying(self:_:))
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatApplyProjectiveTransform(SPSize3DFloat size, SPProjectiveTransform3DFloat transform) {

    simd_float4 rhs = simd_make_float4(size.vector, 0);
    
    simd_float3 transformed = simd_mul(transform.matrix, rhs).xyz;
    
    return SPSize3DFloatMakeWithVector(transformed);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatUnapplyAffineTransform(SPSize3DFloat size, SPAffineTransform3DFloat transform) {
  
    SPAffineTransform3DFloat invertedTransform = SPAffineTransform3DFloatInverted(transform);
    
    return SPSize3DFloatApplyAffineTransform(size, invertedTransform);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatUnapplyProjectiveTransform(SPSize3DFloat size, SPProjectiveTransform3DFloat transform) {

    SPProjectiveTransform3DFloat invertedTransform = SPProjectiveTransform3DFloatInverted(transform);
    
    return SPSize3DFloatApplyProjectiveTransform(size, invertedTransform);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatShear(SPSize3DFloat size,
                       SPAxis shearAxis,
                       float shearFactor0,
                       float shearFactor1) {
    
    SPRect3DFloat rect = SPRect3DFloatMakeAtOrigin(SPPoint3DFloatZero,
                                                   size);
    
    SPSize3DFloat transformed = SPRect3DFloatShear(rect, shearAxis,
                                                   shearFactor0, shearFactor1).size;
    
    return transformed;
}

SPATIAL_SWIFT_NAME(Size3DFloat.contains(self:_:))
SPATIAL_OVERLOADABLE
bool SPSize3DFloatContainsSize(SPSize3DFloat size, SPSize3DFloat other)  {
    
    simd_float3 v0 = size.vector;
    simd_float3 v1 = other.vector;
    
    return simd_equal(v0 >= v1, (simd_int3){-1, -1, -1});
}

// MARK: - Deriving new sizes

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatIntersection(SPSize3DFloat size, SPSize3DFloat other) {
    
    SPRect3DFloat rect = (SPRect3DFloat){ SPPoint3DFloatZero, size };
    
    SPRect3DFloat otherRect = (SPRect3DFloat){ SPPoint3DFloatZero, other };
    
    return SPRect3DFloatIntersection(rect, otherRect).size;
}

SPATIAL_SWIFT_NAME(Size3DFloat.union(self:_:))
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatUnion(SPSize3DFloat size, SPSize3DFloat other) {
    
    SPRect3DFloat rect = (SPRect3DFloat){SPPoint3DFloatZero,
        size};
    
    SPRect3DFloat otherRect = (SPRect3DFloat){SPPoint3DFloatZero,
        other};
    
    return SPRect3DFloatUnion(rect, otherRect).size;
}

// MARK: - Volumetric operations

SPATIAL_SWIFT_NAME(Size3DFloat.contains(self:point:))
SPATIAL_OVERLOADABLE
bool SPSize3DFloatContainsPoint(SPSize3DFloat size, SPPoint3DFloat other) {
    
    SPRect3DFloat rect = (SPRect3DFloat){SPPoint3DFloatZero, size};
    
    return SPRect3DFloatContainsPoint(rect, other);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPSize3DFloatContainsAnyPoint(SPSize3DFloat size, const SPPoint3DFloat *points, int pointCount) {
    
    SPRect3DFloat rect = (SPRect3DFloat){ SPPoint3DFloatZero, size };
    
    return SPRect3DFloatContainsAnyPoint(rect, points, pointCount);
}

// MARK: - Transform by Pose

/*!
 @abstract Returns a size that's transformed by the specified pose.
 
 @param size The source size.
 @param pose The pose that the function applies to the size.
 @returns The transformed size.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatApplyPose(SPSize3DFloat size,
                           SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatApplyPose(SPSize3DFloat size,
                           SPPose3DFloat pose) {
    
    return SPSize3DFloatRotate(size, pose.rotation);
}

/*!
 @abstract Returns a size that's transformed by the inverse of the specified pose.
 
 @param size The source size.
 @param pose The pose that the function unapplies to the size.
 @returns The transformed size.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatUnapplyPose(SPSize3DFloat size,
                             SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatUnapplyPose(SPSize3DFloat size,
                             SPPose3DFloat pose) {
    
    
    return SPSize3DFloatRotate(size, SPRotation3DFloatInverse(pose.rotation));
}

// MARK: - Transform by Scaled Pose

/*!
 @abstract Returns a size that's transformed by the specified scaled pose.
 
 @param size The source size.
 @param pose The scaled pose that the function applies to the size.
 @returns The transformed size.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatApplyScaledPose(SPSize3DFloat size,
                                           SPScaledPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatApplyScaledPose(SPSize3DFloat size,
                                           SPScaledPose3DFloat pose) {
    
    simd_float3 v = size.vector * pose.scale;
    v = simd_act(pose.rotation.quaternion, v);
    
    return SPSize3DFloatMakeWithVector(v);
}

/*!
 @abstract Returns a size that's transformed by the inverse of the specified scaled pose.
 
 @param size The source size.
 @param pose The pose that the function unapplies to the size.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatUnapplyScaledPose(SPSize3DFloat size,
                                             SPScaledPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatUnapplyScaledPose(SPSize3DFloat size,
                                             SPScaledPose3DFloat pose) {
    
    simd_quatf invPoseRot = simd_inverse(pose.rotation.quaternion);
    simd_float3 invPosePos = simd_act(invPoseRot, -pose.position.vector);
    
    simd_float3 v = simd_act(invPoseRot, size.vector);
    v /= pose.scale;
    
    return SPSize3DFloatMakeWithVector(v);
}

#endif /* SPSize3DFloat_h */
