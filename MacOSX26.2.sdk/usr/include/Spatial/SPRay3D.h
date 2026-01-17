#ifndef SPRay3D_h
#define SPRay3D_h

#include <Spatial/Structures.h>
#include <Spatial/SPPoint3D.h>
#include <Spatial/SPVector3D.h>
#include <Spatial/SPRect3D.h>

// MARK: - Public API

// MARK: - Creating a ray from Spatial primitives

/*!
 @abstract Returns a ray at the specified origin.
 
 @param origin A point structure that specifies the origin of the ray.
 @param direction A Spatial vector that specifies the direction of the ray.
 @note This function normalizes nonzero direction vectors.
 @returns A new ray stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DMake(SPPoint3D origin,
                    SPVector3D direction)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DMake(SPPoint3D origin,
                    SPVector3D direction) {
    
    if (SPVector3DIsZero(direction)) {
        return (SPRay3D){
            .origin = origin,
            .direction = direction
        };
    } else {
        return (SPRay3D){
            .origin = origin,
            .direction = SPVector3DNormalize(direction)
        };
    }
}

// MARK: - Creating a ray from simd vectors

/*!
 @abstract Returns a ray at the specified origin.
 
 @param origin A point structure that specifies the origin of the ray.
 @param direction A Spatial vector that specifies the direction of the ray.
 @note This function normalizes the direction vector.
 @returns A new ray stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DMakeWithVector(simd_double3 origin,
                              simd_double3 direction)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DMakeWithVector(simd_double3 origin,
                              simd_double3 direction) {
    
    return (SPRay3D){
        .origin.vector = origin,
        .direction.vector = simd_normalize(direction)
    };
    
}

// MARK: - Comparing Rays

/// Returns @p true if both rays are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRay3DEqualToRay(SPRay3D ray1, SPRay3D ray2)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRay3DEqualToRay(SPRay3D ray1, SPRay3D ray2) {
    
    return (
            SPPoint3DEqualToPoint(ray1.origin, ray2.origin) &&
            SPVector3DEqualToVector(ray1.direction, ray2.direction)
            );
}

// MARK: - Translation

/*!
 @abstract Returns a ray with an origin that is offset from that of the source ray.
 
 @param ray The source ray.
 @param offset A vector that defines the offset.
 @returns A ray that's offset by the @p x, @p y, and @p z of the vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DTranslate(SPRay3D ray, SPVector3D offset)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(Ray3D.translated(self:by:))
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DTranslate(SPRay3D ray, SPVector3D offset) {
    
    SPRay3D r = SPRay3DMake(SPPoint3DTranslate(ray.origin, offset),
                            ray.direction);
    
    return r;
}

SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DTranslate(SPRay3D ray, SPSize3D offset)
__API_DEPRECATED("Use `SPVector3D` variant.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DTranslate(SPRay3D ray, SPSize3D offset) {
    return SPRay3DTranslate(
                            ray,
                            SPVector3DMakeWithVector(offset.vector)
                            );
}

// MARK: - Rotation

/*!
 @abstract Returns a ray that's rotated by the specified rotation.

 @param ray The source ray.
 @param rotation The rotation.
 @returns A ray with a direction that's rotated by the specified quaternion.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DRotate(SPRay3D ray, SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DRotate(SPRay3D ray, SPRotation3D rotation) {
    
    SPPoint3D origin = SPPoint3DRotate(ray.origin, rotation);
    SPVector3D direction = SPVector3DRotate(ray.direction, rotation);
    
    SPRay3D r = SPRay3DMake(origin, direction);
    
    return r;
}

/*!
 @abstract Returns a ray that's rotated by the specified quaternion.

 @param ray The source ray.
 @param quaternion The quaternion that defines the rotation.
 @returns A ray with a direction that's rotated by the specified quaternion.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DRotateByQuaternion(SPRay3D ray, simd_quatd quaternion)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DRotateByQuaternion(SPRay3D ray, simd_quatd quaternion) {
    
    SPRotation3D r = SPRotation3DMakeWithQuaternion(quaternion);
    
    return SPRay3DRotate(ray, r);
}

// MARK: - Transform by Pose

/*!
 @abstract Returns a ray that's transformed by the specified pose.
 
 @param ray The source ray.
 @param pose The pose that the function applies to the ray.
 @returns The transformed ray.
 @note This function rotates the ray's direction by the pose's rotation and offsets the ray's origin
 by the pose's position.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DApplyPose(SPRay3D ray,
                               SPPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DApplyPose(SPRay3D ray,
                               SPPose3D pose) {
    
    ray = SPRay3DRotate(ray, pose.rotation);
    ray = SPRay3DTranslate(ray,
                           SPVector3DMakeWithVector(pose.position.vector));
    
    return ray;
}

/*!
 @abstract Returns a ray that's transformed by the inverse of the specified pose.
 
 @param ray The source ray.
 @param pose The pose that the function unapplies to the ray.
 @returns The transformed ray.
 @note This function rotates the ray's direction by the pose's rotation and offsets the ray's origin
 by the pose's position.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DUnapplyPose(SPRay3D ray,
                           SPPose3D pose)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DUnapplyPose(SPRay3D ray,
                           SPPose3D pose) {
    
    return SPRay3DMake(SPPoint3DUnapplyPose(ray.origin, pose),
                       SPVector3DUnapplyPose(ray.direction, pose));
    
}

// MARK: - Transform by Scaled Pose

/*!
 @abstract Returns a ray that's transformed by the specified scaled pose.
 
 @param ray The source ray.
 @param pose The scaled pose that the function applies to the ray.
 @returns The transformed ray.
 @note This function rotates the ray's direction by the pose's rotation and offsets the ray's origin
 by the pose's position.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DApplyScaledPose(SPRay3D ray,
                               SPScaledPose3D pose)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DApplyScaledPose(SPRay3D ray,
                               SPScaledPose3D pose) {
    
    ray = SPRay3DRotate(ray, pose.rotation);
    ray.origin = SPPoint3DMakeWithVector(ray.origin.vector * pose.scale);
    ray = SPRay3DTranslate(ray,
                           SPVector3DMakeWithVector(pose.position.vector));
    
    return ray;
}

/*!
 @abstract Returns a ray that's transformed by the inverse of the specified scaled pose.
 
 @param ray The source ray.
 @param pose The scaled pose that the function unapplies to the ray.
 @returns The transformed ray.
 @note This function rotates the ray's direction by the pose's rotation and offsets the ray's origin
 by the pose's position.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DUnapplyScaledPose(SPRay3D ray,
                                 SPScaledPose3D pose)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DUnapplyScaledPose(SPRay3D ray,
                                 SPScaledPose3D pose) {
    
    return SPRay3DMake(SPPoint3DUnapplyScaledPose(ray.origin, pose),
                       SPVector3DUnapplyScaledPose(ray.direction, pose));
    
}

// MARK: - Test for intersection with sphere

/*!
 @abstract Returns a Boolean value that indicates whether the ray intersects a specified sphere.

 @param ray The ray.
 @param sphereOrigin A point structure that defines the center of the sphere.
 @param sphereRadius The radius of the sphere.
 @returns A  Boolean value that indicates whether the ray intersects the sphere.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRay3DIntersectsSphere(SPRay3D ray, SPPoint3D sphereOrigin, double sphereRadius)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_SWIFT_NAME(Ray3D.intersects(self:sphereOrigin:sphereRadius:))
SPATIAL_OVERLOADABLE
bool SPRay3DIntersectsSphere(SPRay3D ray, SPPoint3D sphereOrigin, double sphereRadius) {
    
    simd_double3 x = ray.origin.vector - sphereOrigin.vector;
    double y = 4.0 * simd_dot(ray.direction.vector, ray.direction.vector);
    double z = 2.0 * simd_dot(x, ray.direction.vector);
    z *= z;
    double w = simd_dot(x, x) - sphereRadius * sphereRadius;
    
    return (z - y * w) > 0.0;
}

// MARK: - Test for intersection with rectangle

/*!
 @abstract Returns a Boolean value that indicates whether the ray intersects a specified rectangle.

 @param ray The ray.
 @param rect The rectangle.
 @returns A  Boolean value that indicates whether the ray intersects a specified rectangle.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRay3DIntersectsRect(SPRay3D ray, SPRect3D rect)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRay3DIntersectsRect(SPRay3D ray, SPRect3D rect) {
    
    simd_double3 direction = ray.direction.vector;
    simd_double3 origin = ray.origin.vector;
    
    simd_double3 invDirection = 1.0 / direction;
    
    simd_double3 bounds[] = {
        SPRect3DGetMinimum(rect).vector,
        SPRect3DGetMaximum(rect).vector,
    };
    
    simd_int3 sign = {
        invDirection.x < 0 ? 1 : 0,
        invDirection.y < 0 ? 1 : 0,
        invDirection.z < 0 ? 1 : 0
    };
    
    double tx0 = (bounds[  sign.x].x - origin.x) * invDirection.x;
    double tx1 = (bounds[1-sign.x].x - origin.x) * invDirection.x;
    double ty0 = (bounds[  sign.y].y - origin.y) * invDirection.y;
    double ty1 = (bounds[1-sign.y].y - origin.y) * invDirection.y;
    double tz0 = (bounds[  sign.z].z - origin.z) * invDirection.z;
    double tz1 = (bounds[1-sign.z].z - origin.z) * invDirection.z;
    
    double tmin = fmax(fmax(fmin(tx0, tx1), fmin(ty0, ty1)), fmin(tz0, tz1));
    double tmax = fmin(fmin(fmax(tx0, tx1), fmax(ty0, ty1)), fmax(tz0, tz1));
    
    return tmax >= tmin;
}

// MARK: - Primitive3D supprt: macOS 14.0, iOS 17.0, tvOS 17.0, watchOS 10.0

/*!
 @abstract Returns a ray that's transformed by the specified affine transform.
 
 @param ray The source ray.
 @param transform The affine transform that the function applies to the ray.
 @returns The transformed ray.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DApplyAffineTransform(SPRay3D ray,
                                    SPAffineTransform3D transform)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DApplyAffineTransform(SPRay3D ray,
                                    SPAffineTransform3D transform) {
    
    return SPRay3DMake(SPPoint3DApplyAffineTransform(ray.origin, transform),
                       SPVector3DApplyAffineTransform(ray.direction, transform));
}

/*!
 @abstract Returns a ray that's transformed by the inverse of the specified affine transform.
 
 @param ray The source ray.
 @param transform The affine transform that the function unapplies to the ray.
 @returns The transformed ray.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DUnapplyAffineTransform(SPRay3D ray,
                                      SPAffineTransform3D transform)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DUnapplyAffineTransform(SPRay3D ray,
                                      SPAffineTransform3D transform) {
    
    return SPRay3DMake(SPPoint3DUnapplyAffineTransform(ray.origin, transform),
                       SPVector3DUnapplyAffineTransform(ray.direction, transform));
}

/*!
 @abstract Returns a ray that's transformed by the specified projective transform.
 
 @param ray The source ray.
 @param transform The projective transform that the function applies to the ray.
 @returns The transformed ray.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DApplyProjectiveTransform(SPRay3D ray,
                                        SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DApplyProjectiveTransform(SPRay3D ray,
                                        SPProjectiveTransform3D transform) {

    return SPRay3DMake(SPPoint3DApplyProjectiveTransform(ray.origin, transform),
                       SPVector3DApplyProjectiveTransform(ray.direction, transform));
}

/*!
 @abstract Returns a ray that's transformed by the inverse of the specified projective transform.
 
 @param ray The source ray.
 @param transform The projective transform that the function unapplies to the ray.
 @returns The transformed ray.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DUnapplyProjectiveTransform(SPRay3D ray,
                                          SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DUnapplyProjectiveTransform(SPRay3D ray,
                                          SPProjectiveTransform3D transform) {

    return SPRay3DMake(SPPoint3DUnapplyProjectiveTransform(ray.origin, transform),
                       SPVector3DUnapplyProjectiveTransform(ray.direction, transform));
}

/*!
 @abstract  The ray with the value zero.
 */
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
SPATIAL_SWIFT_NAME(Ray3D.zero)
static const SPRay3D SPRay3DZero = {
    .origin = { 0, 0, 0 },
    .direction = { 0, 0, 0 }
};

/*!
 @abstract The ray with an infinite origin and direction.
 */
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
SPATIAL_SWIFT_NAME(Ray3D.infinity)
static const SPRay3D SPRay3DInfinity = {
    .origin = { INFINITY, INFINITY, INFINITY },
    .direction = { INFINITY, INFINITY, INFINITY}
};

/*!
 @abstract Returns a Boolean value that indicates whether the ray contains any NaN values.
 
 @param ray The source ray.
 @returns A Boolean value that indicates whether the ray contains any NaN values.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRay3DIsNaN(SPRay3D ray)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRay3DIsNaN(SPRay3D ray) {
    simd_double3 p = (simd_double3){ray.origin.x, ray.origin.y, ray.origin.z};
    simd_double3 q = (simd_double3){ray.direction.x, ray.direction.y, ray.direction.z};
    return simd_any(_sp_simd_isnan(p)) || simd_any(_sp_simd_isnan(q));
}

/*!
 @abstract Returns a Boolean value that indicates whether all of the values of the ray are finite.
 
 @param ray The source ray.
 @returns A Boolean value that indicates whether all of the values of the ray are finite.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRay3DIsFinite(SPRay3D ray)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRay3DIsFinite(SPRay3D ray) {
    simd_double3 p = (simd_double3){ray.origin.x, ray.origin.y, ray.origin.z};
    simd_double3 q = (simd_double3){ray.direction.x, ray.direction.y, ray.direction.z};
    return simd_all(_sp_simd_isfinite(p)) && simd_all(_sp_simd_isfinite(q));
}

/*!
 @abstract Returns a Boolean value that indicates whether all of the values of the ray are zero.

 @param ray The source ray.
 @returns A Boolean value that indicates whether all of the values of the ray are zero.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRay3DIsZero(SPRay3D ray)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRay3DIsZero(SPRay3D ray) {

    return SPPoint3DIsZero(ray.origin) && SPVector3DIsZero(ray.direction);
}

/*!
 @abstract Returns a ray that's rotated by the specified rotation around a specified pivot.

 @param ray The source ray.
 @param rotation The rotation.
 @param pivot The center of rotation.
 @returns A ray with a direction that's rotated by the specified quaternion.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DRotateAroundPoint(SPRay3D ray, SPRotation3D rotation, SPPoint3D pivot)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DRotateAroundPoint(SPRay3D ray, SPRotation3D rotation, SPPoint3D pivot) {

    SPPoint3D origin = SPPoint3DRotateAroundPoint(ray.origin,
                                                  rotation,
                                                  pivot);
    SPPoint3D direction = SPPoint3DRotateAroundPoint(SPPoint3DMakeWithVector(ray.direction),
                                                     rotation,
                                                     pivot);
    
    return SPRay3DMake(origin, SPVector3DMakeWithPoint(direction));
}

/*!
 @abstract Returns a ray that's rotated by the specified quaternion around a specified pivot.
 
 @param ray The source ray.
 @param quaternion The quaternion that defines the rotation.
 @param pivot The center of rotation.
 @returns A ray with a direction that's rotated by the specified quaternion.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DRotateByQuaternionAroundPoint(SPRay3D ray, simd_quatd quaternion, SPPoint3D pivot)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DRotateByQuaternionAroundPoint(SPRay3D ray, simd_quatd quaternion, SPPoint3D pivot) {
    
    SPPoint3D origin = SPPoint3DRotateByQuaternionAroundPoint(ray.origin,
                                                              quaternion,
                                                              pivot);
    SPPoint3D direction = SPPoint3DRotateByQuaternionAroundPoint(SPPoint3DMakeWithVector(ray.direction),
                                                                 quaternion,
                                                                 pivot);
    
    return SPRay3DMake(origin, SPVector3DMakeWithPoint(direction));
}



#endif /* SPRay3D_h */
