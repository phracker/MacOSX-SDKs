#ifndef Spatial_SPSize3D_h
#define Spatial_SPSize3D_h

#include <Spatial/Structures.h>
#include <Spatial/SPRect3D.h>
#include <Spatial/SPAffineTransform3D.h>
#include <Spatial/SPProjectiveTransform3D.h>
#include <math.h>

// MARK: - Public API

// MARK: - Creating a size

/*!
 @abstract Creates a size structure with dimensions specified as a Spatial vector.
 
 @param xyz The source vector.
 @returns A new size stucture.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DMakeWithVector(SPVector3D xyz)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Creates a size structure with dimensions specified as the coordinates of a  point structure.
 
 @param point The source point.
 @returns A new size stucture.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DMakeWithPoint(SPPoint3D point)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Querying size properties

/*!
 @abstract Returns the @p width, @p height, and @p depth components of the size expressed as a simd vector.
 
 @param size The source size.
 @returns A vector that represents the size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_double3 SPSize3DGetVector(SPSize3D size)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Returns @p true if both sizes are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DEqualToSize(SPSize3D size1, SPSize3D size2)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

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
SPSize3D SPSize3DScaleBy(SPSize3D size, double x, double y, double z)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a size with dimensions scaled by the specified size.
 
 @param size The source size.
 @param scale The scale value.
 @returns A size that's scaled by the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DScaleBySize(SPSize3D size, SPSize3D scale)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a size with dimensions uniformly scaled by the specified value.
 
 @param size The source size.
 @param scale The scale value.
 @returns A size that's uniformly scaled by the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DScaleUniform(SPSize3D size, double scale)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a size that's rotated by the specified rotation around the origin.
 
 @param size The source size.
 @param rotation The rotation.
 @returns A size that's rotated by the specified rotation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DRotate(SPSize3D size, SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a size that's rotated by the specified quaternion around the origin.
 
 @param size The source size.
 @param quaternion The quaternion that defines the rotation.
 @returns A size that's rotated by the specified rotation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DRotateByQuaternion(SPSize3D size, simd_quatd quaternion)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a size that's transformed by the specified affine transform.
 
 @param size The source size.
 @param transform The affine transform that the function applies to the size.
 @returns The transformed size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DApplyAffineTransform(SPSize3D size,
                                      SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a size that's transformed by the specified projective transform.
 
 @param size The source size.
 @param transform The projective transform that the function applies to the size.
 @returns The transformed size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DApplyProjectiveTransform(SPSize3D size,
                                          SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a size that's transformed by the inverse of the specified affine transform.
 
 @param size The source size.
 @param transform The affine transform that the function unapplies to the size.
 @returns The transformed size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DUnapplyAffineTransform(SPSize3D size,
                                        SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a size that's transformed by the inverse of the specified projective transform.
 
 @param size The source size.
 @param transform The projective transform that the function unapplies to the size.
 @returns The transformed size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DUnapplyProjectiveTransform(SPSize3D size,
                                            SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

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
SPSize3D SPSize3DShear(SPSize3D size,
                       SPAxis shearAxis,
                       double shearFactor0,
                       double shearFactor1)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Deriving new sizes

/*!
 @abstract Returns the smallest size that contains two sizes.
 
 @param size The first size.
 @param other The second size.
 @returns A size structure that is the smallest size that contains two sizes.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DUnion(SPSize3D size, SPSize3D other)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns the intersection of the two sizes.
 
 @param size The first size.
 @param other The second size.
 @returns A size structure that is the intersection of the two sizes.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DIntersection(SPSize3D size, SPSize3D other)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Volumetric operations

/*!
 @abstract Returns a Boolean value that indicates whether the first size contains the second size.
 
 @param size The first size.
 @param other The second size.
 @returns A Boolean value that indicates whether the first size contains the second size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DContainsSize(SPSize3D size, SPSize3D other)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the size contains the point.
 
 @param size The size.
 @param other The point.
 @returns A Boolean value that indicates whether the size contains the point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DContainsPoint(SPSize3D size, SPPoint3D other)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the size contains any of the specified points.
 
 @param size The size.
 @param points The points.
 @param pointCount The number of points.
 @returns A Boolean value that indicates whether the size contains any of the specified points.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DContainsAnyPoint(SPSize3D size,
                               const SPPoint3D *points, int pointCount)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: Header inline implementations

// MARK: - Creating a size

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DMakeWithVector(SPVector3D xyz) {
    return SPSize3DMake(xyz.vector.x, xyz.vector.y, xyz.vector.z);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DMakeWithPoint(SPPoint3D point) {
    return SPSize3DMake(point.vector.x, point.vector.y, point.vector.z);
}

// MARK: - Querying size properties

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_double3 SPSize3DGetVector(SPSize3D size) {
    return size.vector;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPSize3DEqualToSize(SPSize3D size1, SPSize3D size2) {
    return simd_equal(size1.vector, size2.vector);
}
// MARK: - Transforming a size

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DScaleBy(SPSize3D size, double x, double y, double z) {
    
    return SPSize3DMakeWithVector(size.vector * simd_make_double3(x, y, z));
}

SPATIAL_SWIFT_NAME(Size3D.scaled(self:by:))
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DScaleBySize(SPSize3D size, SPSize3D scale) {
    
    return SPSize3DMakeWithVector(size.vector * scale.vector);
}

SPATIAL_SWIFT_NAME(Size3D.uniformlyScaled(self:by:))
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DScaleUniform(SPSize3D size, double scale) {
    
    return SPSize3DMakeWithVector(size.vector * scale);
}

SPATIAL_SWIFT_NAME(Size3D.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DRotate(SPSize3D size, SPRotation3D rotation) {
    
    SPAffineTransform3D t = SPAffineTransform3DMakeRotation(rotation);

    return SPSize3DApplyAffineTransform(size, t);
}

SPATIAL_SWIFT_NAME(Size3D.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DRotateByQuaternion(SPSize3D size, simd_quatd quaternion) {

    SPRotation3D r = SPRotation3DMakeWithQuaternion(quaternion);
  
    return SPSize3DRotate(size, r);
}

SPATIAL_SWIFT_NAME(Size3D.applying(self:_:))
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DApplyAffineTransform(SPSize3D size, SPAffineTransform3D transform) {
    
    simd_double4 rhs = simd_make_double4(size.vector, 0);
    
    simd_double3 transformed = simd_mul(transform.matrix, rhs).xyz;
    
    return SPSize3DMakeWithVector(transformed);
}

SPATIAL_SWIFT_NAME(Size3D.applying(self:_:))
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DApplyProjectiveTransform(SPSize3D size, SPProjectiveTransform3D transform) {

    simd_double4 rhs = simd_make_double4(size.vector, 0);
    
    simd_double3 transformed = simd_mul(transform.matrix, rhs).xyz;
    
    return SPSize3DMakeWithVector(transformed);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DUnapplyAffineTransform(SPSize3D size, SPAffineTransform3D transform) {
  
    SPAffineTransform3D invertedTransform = SPAffineTransform3DInverted(transform);
    
    return SPSize3DApplyAffineTransform(size, invertedTransform);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DUnapplyProjectiveTransform(SPSize3D size, SPProjectiveTransform3D transform) {

    SPProjectiveTransform3D invertedTransform = SPProjectiveTransform3DInverted(transform);
    
    return SPSize3DApplyProjectiveTransform(size, invertedTransform);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DShear(SPSize3D size,
                       SPAxis shearAxis,
                       double shearFactor0,
                       double shearFactor1) {
    
    SPRect3D rect = SPRect3DMakeAtOrigin(SPPoint3DZero,
                                         size);
    
    SPSize3D transformed = SPRect3DShear(rect, shearAxis,
                                         shearFactor0, shearFactor1).size;
    
    return transformed;
}

SPATIAL_SWIFT_NAME(Size3D.contains(self:_:))
SPATIAL_OVERLOADABLE
bool SPSize3DContainsSize(SPSize3D size, SPSize3D other)  {
    
    simd_double3 v0 = size.vector;
    simd_double3 v1 = other.vector;
    
    return simd_equal(v0 >= v1, (simd_long3){-1, -1, -1});
}

// MARK: - Deriving new sizes

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DIntersection(SPSize3D size, SPSize3D other) {
    
    SPRect3D rect = (SPRect3D){ SPPoint3DZero, size };
    
    SPRect3D otherRect = (SPRect3D){ SPPoint3DZero, other };
    
    return SPRect3DIntersection(rect, otherRect).size;
}

SPATIAL_SWIFT_NAME(Size3D.union(self:_:))
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DUnion(SPSize3D size, SPSize3D other) {
    
    SPRect3D rect = (SPRect3D){SPPoint3DZero,
        size};
    
    SPRect3D otherRect = (SPRect3D){SPPoint3DZero,
        other};
    
    return SPRect3DUnion(rect, otherRect).size;
}

// MARK: - Volumetric operations

SPATIAL_SWIFT_NAME(Size3D.contains(self:point:))
SPATIAL_OVERLOADABLE
bool SPSize3DContainsPoint(SPSize3D size, SPPoint3D other) {
    
    SPRect3D rect = (SPRect3D){SPPoint3DZero, size};
    
    return SPRect3DContainsPoint(rect, other);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPSize3DContainsAnyPoint(SPSize3D size, const SPPoint3D *points, int pointCount) {
    
    SPRect3D rect = (SPRect3D){ SPPoint3DZero, size };
    
    return SPRect3DContainsAnyPoint(rect, points, pointCount);
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
SPSize3D SPSize3DApplyPose(SPSize3D size,
                           SPPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DApplyPose(SPSize3D size,
                           SPPose3D pose) {
    
    return SPSize3DRotate(size, pose.rotation);
}

/*!
 @abstract Returns a size that's transformed by the inverse of the specified pose.
 
 @param size The source size.
 @param pose The pose that the function unapplies to the size.
 @returns The transformed size.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DUnapplyPose(SPSize3D size,
                             SPPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DUnapplyPose(SPSize3D size,
                             SPPose3D pose) {
    
    return SPSize3DRotate(size, SPRotation3DInverse(pose.rotation));
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
SPSize3D SPSize3DApplyScaledPose(SPSize3D size,
                                 SPScaledPose3D pose)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DApplyScaledPose(SPSize3D size,
                                 SPScaledPose3D pose) {
    
    simd_double3 v = size.vector * pose.scale;
    v = simd_act(pose.rotation.quaternion, v);
    
    return SPSize3DMakeWithVector(v);
}

/*!
 @abstract Returns a size that's transformed by the inverse of the specified scaled pose.
 
 @param size The source size.
 @param pose The pose that the function unapplies to the size.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DUnapplyScaledPose(SPSize3D size,
                                   SPScaledPose3D pose)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DUnapplyScaledPose(SPSize3D size,
                                   SPScaledPose3D pose) {
    
    simd_quatd invPoseRot = simd_inverse(pose.rotation.quaternion);
    simd_double3 invPosePos = simd_act(invPoseRot, -pose.position.vector);
    
    simd_double3 v = simd_act(invPoseRot, size.vector);
    v /= pose.scale;
    
    return SPSize3DMakeWithVector(v);
}

#endif /* Spatial_SPSize3D_h */
