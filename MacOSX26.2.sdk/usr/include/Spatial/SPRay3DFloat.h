#ifndef SPRay3DFloat_h
#define SPRay3DFloat_h

#include <Spatial/StructuresFloat.h>
#include <Spatial/SPPoint3DFloat.h>
#include <Spatial/SPVector3DFloat.h>
#include <Spatial/SPRect3DFloat.h>

// MARK: - SINGLE-PRECISION Public API

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
SPRay3DFloat SPRay3DFloatMake(SPPoint3DFloat origin,
                              SPVector3DFloat direction)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatMake(SPPoint3DFloat origin,
                              SPVector3DFloat direction) {
    
    if (SPVector3DFloatIsZero(direction)) {
        return (SPRay3DFloat){
            .origin = origin,
            .direction = direction
        };
    } else {
        return (SPRay3DFloat){
            .origin = origin,
            .direction = SPVector3DFloatNormalize(direction)
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
SPRay3DFloat SPRay3DFloatMakeWithVector(simd_float3 origin,
                                        simd_float3 direction)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatMakeWithVector(simd_float3 origin,
                                        simd_float3 direction) {
    
    return (SPRay3DFloat){
        .origin.vector = origin,
        .direction.vector = simd_normalize(direction)
    };
    
}

// MARK: - Comparing Rays

/// Returns @p true if both rays are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRay3DFloatEqualToRay(SPRay3DFloat ray1, SPRay3DFloat ray2)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRay3DFloatEqualToRay(SPRay3DFloat ray1, SPRay3DFloat ray2) {
    
    return (
            SPPoint3DFloatEqualToPoint(ray1.origin, ray2.origin) &&
            SPVector3DFloatEqualToVector(ray1.direction, ray2.direction)
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
SPRay3DFloat SPRay3DFloatTranslate(SPRay3DFloat ray, SPVector3DFloat offset)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(Ray3DFloat.translated(self:by:))
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatTranslate(SPRay3DFloat ray, SPVector3DFloat offset) {
    
    SPRay3DFloat r = SPRay3DFloatMake(SPPoint3DFloatTranslate(ray.origin, offset),
                                      ray.direction);
    
    return r;
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
SPRay3DFloat SPRay3DFloatRotate(SPRay3DFloat ray, SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatRotate(SPRay3DFloat ray, SPRotation3DFloat rotation) {
    
    SPPoint3DFloat origin = SPPoint3DFloatRotate(ray.origin, rotation);
    SPVector3DFloat direction = SPVector3DFloatRotate(ray.direction, rotation);
    
    SPRay3DFloat r = SPRay3DFloatMake(origin, direction);
    
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
SPRay3DFloat SPRay3DFloatRotateByQuaternion(SPRay3DFloat ray, simd_quatf quaternion)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatRotateByQuaternion(SPRay3DFloat ray, simd_quatf quaternion) {
    
    SPRotation3DFloat r = SPRotation3DFloatMakeWithQuaternion(quaternion);
    
    return SPRay3DFloatRotate(ray, r);
}

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
SPRay3DFloat SPRay3DFloatApplyPose(SPRay3DFloat ray,
                                   SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatApplyPose(SPRay3DFloat ray,
                                   SPPose3DFloat pose) {
    
    ray = SPRay3DFloatRotate(ray, pose.rotation);
    ray = SPRay3DFloatTranslate(ray,
                                SPVector3DFloatMakeWithVector(pose.position.vector));
    
    return ray;
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
SPRay3DFloat SPRay3DFloatApplyScaledPose(SPRay3DFloat ray,
                                         SPScaledPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatApplyScaledPose(SPRay3DFloat ray,
                                         SPScaledPose3DFloat pose) {
    
    ray = SPRay3DFloatRotate(ray, pose.rotation);
    ray.origin = SPPoint3DFloatMakeWithVector(ray.origin.vector * pose.scale);
    ray = SPRay3DFloatTranslate(ray,
                                SPVector3DFloatMakeWithVector(pose.position.vector));
    
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
SPRay3DFloat SPRay3DFloatUnapplyScaledPose(SPRay3DFloat ray,
                                           SPScaledPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatUnapplyScaledPose(SPRay3DFloat ray,
                                           SPScaledPose3DFloat pose) {
    
    return SPRay3DFloatMake(SPPoint3DFloatUnapplyScaledPose(ray.origin, pose),
                            SPVector3DFloatUnapplyScaledPose(ray.direction, pose));
    
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
bool SPRay3DFloatIntersectsSphere(SPRay3DFloat ray, SPPoint3DFloat sphereOrigin, float sphereRadius)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(Ray3DFloat.intersects(self:sphereOrigin:sphereRadius:))
SPATIAL_OVERLOADABLE
bool SPRay3DFloatIntersectsSphere(SPRay3DFloat ray, SPPoint3DFloat sphereOrigin, float sphereRadius) {
    
    simd_float3 x = ray.origin.vector - sphereOrigin.vector;
    float y = 4.0 * simd_dot(ray.direction.vector, ray.direction.vector);
    float z = 2.0 * simd_dot(x, ray.direction.vector);
    z *= z;
    float w = simd_dot(x, x) - sphereRadius * sphereRadius;
    
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
bool SPRay3DFloatIntersectsRect(SPRay3DFloat ray, SPRect3DFloat rect)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRay3DFloatIntersectsRect(SPRay3DFloat ray, SPRect3DFloat rect) {
    
    simd_float3 direction = ray.direction.vector;
    simd_float3 origin = ray.origin.vector;
    
    simd_float3 invDirection = 1.0 / direction;
    
    simd_float3 bounds[] = {
        SPRect3DFloatGetMinimum(rect).vector,
        SPRect3DFloatGetMaximum(rect).vector,
    };
    
    simd_int3 sign = {
        invDirection.x < 0 ? 1 : 0,
        invDirection.y < 0 ? 1 : 0,
        invDirection.z < 0 ? 1 : 0
    };
    
    float tx0 = (bounds[  sign.x].x - origin.x) * invDirection.x;
    float tx1 = (bounds[1-sign.x].x - origin.x) * invDirection.x;
    float ty0 = (bounds[  sign.y].y - origin.y) * invDirection.y;
    float ty1 = (bounds[1-sign.y].y - origin.y) * invDirection.y;
    float tz0 = (bounds[  sign.z].z - origin.z) * invDirection.z;
    float tz1 = (bounds[1-sign.z].z - origin.z) * invDirection.z;
    
    float tmin = fmax(fmax(fmin(tx0, tx1), fmin(ty0, ty1)), fmin(tz0, tz1));
    float tmax = fmin(fmin(fmax(tx0, tx1), fmax(ty0, ty1)), fmax(tz0, tz1));
    
    return tmax >= tmin;
}

// MARK: - Primitive3DFloat supprt: macOS 14.0, iOS 17.0, tvOS 17.0, watchOS 10.0

/*!
 @abstract Returns a ray that's transformed by the specified affine transform.
 
 @param ray The source ray.
 @param transform The affine transform that the function applies to the ray.
 @returns The transformed ray.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatApplyAffineTransform(SPRay3DFloat ray,
                                              SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatApplyAffineTransform(SPRay3DFloat ray,
                                              SPAffineTransform3DFloat transform) {
    
    return SPRay3DFloatMake(SPPoint3DFloatApplyAffineTransform(ray.origin, transform),
                            SPVector3DFloatApplyAffineTransform(ray.direction, transform));
}

/*!
 @abstract Returns a ray that's transformed by the inverse of the specified affine transform.
 
 @param ray The source ray.
 @param transform The affine transform that the function unapplies to the ray.
 @returns The transformed ray.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatUnapplyAffineTransform(SPRay3DFloat ray,
                                                SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatUnapplyAffineTransform(SPRay3DFloat ray,
                                                SPAffineTransform3DFloat transform) {
    
    return SPRay3DFloatMake(SPPoint3DFloatUnapplyAffineTransform(ray.origin, transform),
                            SPVector3DFloatUnapplyAffineTransform(ray.direction, transform));
}

/*!
 @abstract Returns a ray that's transformed by the specified projective transform.
 
 @param ray The source ray.
 @param transform The projective transform that the function applies to the ray.
 @returns The transformed ray.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatApplyProjectiveTransform(SPRay3DFloat ray,
                                                  SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatApplyProjectiveTransform(SPRay3DFloat ray,
                                                  SPProjectiveTransform3DFloat transform) {
    
    return SPRay3DFloatMake(SPPoint3DFloatApplyProjectiveTransform(ray.origin, transform),
                            SPVector3DFloatApplyProjectiveTransform(ray.direction, transform));
}

/*!
 @abstract Returns a ray that's transformed by the inverse of the specified projective transform.
 
 @param ray The source ray.
 @param transform The projective transform that the function unapplies to the ray.
 @returns The transformed ray.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatUnapplyProjectiveTransform(SPRay3DFloat ray,
                                                    SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatUnapplyProjectiveTransform(SPRay3DFloat ray,
                                                    SPProjectiveTransform3DFloat transform) {
    
    return SPRay3DFloatMake(SPPoint3DFloatUnapplyProjectiveTransform(ray.origin, transform),
                            SPVector3DFloatUnapplyProjectiveTransform(ray.direction, transform));
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
SPRay3DFloat SPRay3DFloatUnapplyPose(SPRay3DFloat ray,
                                     SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatUnapplyPose(SPRay3DFloat ray,
                                     SPPose3DFloat pose) {
    
    return SPRay3DFloatMake(SPPoint3DFloatUnapplyPose(ray.origin, pose),
                            SPVector3DFloatUnapplyPose(ray.direction, pose));
    
}

/*!
 @abstract  The ray with the value zero.
 */
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
SPATIAL_SWIFT_NAME(Ray3DFloat.zero)
static const SPRay3DFloat SPRay3DFloatZero = {
    .origin = { 0, 0, 0 },
    .direction = { 0, 0, 0 }
};

/*!
 @abstract The ray with an infinite origin and direction.
 */
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
SPATIAL_SWIFT_NAME(Ray3DFloat.infinity)
static const SPRay3DFloat SPRay3DFloatInfinity = {
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
bool SPRay3DFloatIsNaN(SPRay3DFloat ray)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRay3DFloatIsNaN(SPRay3DFloat ray) {
    simd_float3 p = (simd_float3){ray.origin.x, ray.origin.y, ray.origin.z};
    simd_float3 q = (simd_float3){ray.direction.x, ray.direction.y, ray.direction.z};
    return simd_any(_sp_simd_isnan(p)) || simd_any(_sp_simd_isnan(q));
}

/*!
 @abstract Returns a Boolean value that indicates whether all of the values of the ray are finite.
 
 @param ray The source ray.
 @returns A Boolean value that indicates whether all of the values of the ray are finite.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRay3DFloatIsFinite(SPRay3DFloat ray)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRay3DFloatIsFinite(SPRay3DFloat ray) {
    simd_float3 p = (simd_float3){ray.origin.x, ray.origin.y, ray.origin.z};
    simd_float3 q = (simd_float3){ray.direction.x, ray.direction.y, ray.direction.z};
    return simd_all(_sp_simd_isfinite(p)) && simd_all(_sp_simd_isfinite(q));
}

/*!
 @abstract Returns a Boolean value that indicates whether all of the values of the ray are zero.
 
 @param ray The source ray.
 @returns A Boolean value that indicates whether all of the values of the ray are zero.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRay3DFloatIsZero(SPRay3DFloat ray)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRay3DFloatIsZero(SPRay3DFloat ray) {
    
    return SPPoint3DFloatIsZero(ray.origin) && SPVector3DFloatIsZero(ray.direction);
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
SPRay3DFloat SPRay3DFloatRotateAroundPoint(SPRay3DFloat ray, SPRotation3DFloat rotation, SPPoint3DFloat pivot)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatRotateAroundPoint(SPRay3DFloat ray, SPRotation3DFloat rotation, SPPoint3DFloat pivot) {
    
    SPPoint3DFloat origin = SPPoint3DFloatRotateAroundPoint(ray.origin,
                                                            rotation,
                                                            pivot);
    SPPoint3DFloat direction = SPPoint3DFloatRotateAroundPoint(SPPoint3DFloatMakeWithVector(ray.direction),
                                                               rotation,
                                                               pivot);
    
    return SPRay3DFloatMake(origin, SPVector3DFloatMakeWithPoint(direction));
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
SPRay3DFloat SPRay3DFloatRotateByQuaternionAroundPoint(SPRay3DFloat ray, simd_quatf quaternion, SPPoint3DFloat pivot)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3DFloat SPRay3DFloatRotateByQuaternionAroundPoint(SPRay3DFloat ray, simd_quatf quaternion, SPPoint3DFloat pivot) {
    
    SPPoint3DFloat origin = SPPoint3DFloatRotateByQuaternionAroundPoint(ray.origin,
                                                                        quaternion,
                                                                        pivot);
    SPPoint3DFloat direction = SPPoint3DFloatRotateByQuaternionAroundPoint(SPPoint3DFloatMakeWithVector(ray.direction),
                                                                           quaternion,
                                                                           pivot);
    
    return SPRay3DFloatMake(origin, SPVector3DFloatMakeWithPoint(direction));
}


#endif /* SPRay3DFloat_h */
