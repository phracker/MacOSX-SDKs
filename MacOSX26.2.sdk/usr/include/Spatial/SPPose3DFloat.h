#ifndef SPPose3DFloat_h
#define SPPose3DFloat_h


#include <Spatial/StructuresFloat.h>
#include <Spatial/SPRotation3DFloat.h>
#include <Spatial/SPPoint3DFloat.h>
#include <Spatial/SPAffineTransform3DFloat.h>

// MARK: - SINGLE-PRECISION Public API

// MARK: - Identity pose

/*!
 @abstract The identity pose.
 */
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_REFINED_FOR_SWIFT
static const SPPose3DFloat SPPose3DFloatIdentity = {
    .position = (SPPoint3DFloat){ 0, 0, 0, 1 },
    .rotation = (SPRotation3DFloat) {
        .quaternion = (simd_quatf){ .vector = {0, 0, 0, 1}
        }
    }
};

// MARK: - Creating a pose
/*!
 @abstract Returns a pose with the specified position and rotation.
 
 @param position A point structure that specifies the position of the pose.
 @param rotation A rotation structure that specifies the rotation of the pose.
 @returns A new pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMake(SPPoint3DFloat position,
                                SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMake(SPPoint3DFloat position,
                                SPRotation3DFloat rotation) {
    
    return (SPPose3DFloat) {
        .position = position,
        .rotation = rotation
    };
}

// MARK: - Creating a pose from simd vectors
/*!
 @abstract Returns a pose with the specified position and rotation.
 
 @param position A point structure that specifies the position of the pose.
 @param rotation A rotation structure that specifies the rotation of the pose.
 @returns A new pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMakeWithVector(simd_float3 position,
                                          simd_quatf rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMakeWithVector(simd_float3 position,
                                          simd_quatf rotation) {
    
    return (SPPose3DFloat) {
        .position = SPPoint3DFloatMakeWithVector(position),
        .rotation.quaternion = rotation
    };
}

// MARK: - Returning a 4 x 4 matrix from a pose

/*!
 @abstract Returns a 4 x 4 matrix that represents the pose's translation and rotation.
 
 @param pose The source pose.
 @returns A new pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_float4x4 SPPose3DFloatGet4x4Matrix(SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_float4x4 SPPose3DFloatGet4x4Matrix(SPPose3DFloat pose) {
    
    simd_float4x4 m = simd_matrix4x4(pose.rotation.quaternion);
    m.columns[3].xyz = pose.position.vector;
    
    return m;
}

// MARK: - Comparing poses

/// Returns @p true if both rays are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPPose3DFloatEqualToPose(SPPose3DFloat pose1, SPPose3DFloat pose2)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPPose3DFloatEqualToPose(SPPose3DFloat pose1, SPPose3DFloat pose2) {
    
    return (
            SPPoint3DFloatEqualToPoint(pose1.position, pose2.position) &&
            SPRotation3DFloatEqualToRotation(pose1.rotation, pose2.rotation)
            );
}

/*!
 @abstract Returns a Boolean value that indicates whether the two poses's matrices are equal within the specified absolute tolerance.
 
 @param p1 The first pose.
 @param p2 The first pose.
 @returns A Boolean value that indicates whether the two pose's matrices are equal within the specified default absolute tolerance.
 @note The Spatial default tolerance is @p sqrt(__DBL_EPSILON__) .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPPose3DFloatAlmostEqualToPose(SPPose3DFloat p1,
                                    SPPose3DFloat p2,
                                    float tolerance)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
bool SPPose3DFloatAlmostEqualToPose(SPPose3DFloat p1,
                                    SPPose3DFloat p2,
                                    float tolerance) {
    
    bool rotationIsEqual = _sp_almost_equal_tolerance(p1.rotation.quaternion.vector.x, p2.rotation.quaternion.vector.x, tolerance) &&
    _sp_almost_equal_tolerance(p1.rotation.quaternion.vector.y, p2.rotation.quaternion.vector.y, tolerance) &&
    _sp_almost_equal_tolerance(p1.rotation.quaternion.vector.z, p2.rotation.quaternion.vector.z, tolerance) &&
    _sp_almost_equal_tolerance(p1.rotation.quaternion.vector.w, p2.rotation.quaternion.vector.w, tolerance);
    
    bool positionIsEqual = _sp_almost_equal_tolerance(p1.position.x, p2.position.x, tolerance) &&
    _sp_almost_equal_tolerance(p1.position.y, p2.position.y, tolerance) &&
    _sp_almost_equal_tolerance(p1.position.z, p2.position.z, tolerance);
    
    return rotationIsEqual && positionIsEqual;
}

/*!
 @abstract Returns a Boolean value that indicates whether the two poses's matrices are equal within the Spatial default absolute tolerance.
 
 @param p1 The first pose.
 @param p2 The first pose.
 @returns A Boolean value that indicates whether the two pose's matrices are equal within the Spatial default absolute tolerance.
 @note The Spatial default tolerance is @p sqrt(__DBL_EPSILON__) .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPPose3DFloatAlmostEqualToPose(SPPose3DFloat p1,
                                    SPPose3DFloat p2)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
bool SPPose3DFloatAlmostEqualToPose(SPPose3DFloat p1,
                                    SPPose3DFloat p2) {
    
    return SPPose3DFloatAlmostEqualToPose(p1, p2, SPDefaultToleranceFloat);
}

// MARK: - Comparing against identity

/*!
 @abstract Returns a Boolean value that indicates whether the pose is the identity transform.
 
 @param pose The source pose.
 @returns A Boolean value that indicates whether the transform is the identity transform.
 @note This function checks for equality within the Spatial default tolerance.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPPose3DFloatIsIdentity(SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPPose3DFloatIsIdentity(SPPose3DFloat pose) {
    return SPPose3DFloatAlmostEqualToPose(pose, SPPose3DFloatIdentity);
}
// MARK: - Creating a pose with lookat

/*!
 @abstract Returns a pose at the specified position with the rotation towards the target.
 
 @param position A point structure that specifies the position of the pose.
 @param target The point that the pose orients towards.
 @param up The up direction.
 @returns A new pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMakeLookAt(SPPoint3DFloat position,
                                      SPPoint3DFloat target,
                                      SPVector3DFloat up)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMakeLookAt(SPPoint3DFloat position,
                                      SPPoint3DFloat target,
                                      SPVector3DFloat up) {
    
    SPRotation3DFloat r = SPRotation3DFloatMakeLookAt(position, target, up);
    
    return (SPPose3DFloat) {
        .position = position,
        .rotation = r
    };
}

/*!
 @abstract Returns a pose at the origin with the rotation towards the target.
 
 @param target The point that the pose orients towards.
 @param up The up direction.
 @returns A new pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMakeLookAt(SPPoint3DFloat target,
                                      SPVector3DFloat up)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMakeLookAt(SPPoint3DFloat target,
                                      SPVector3DFloat up) {
    
    SPPoint3DFloat position = SPPoint3DFloatZero;
    
    return SPPose3DFloatMakeLookAt(position, target, up);
}

/*!
 @abstract Returns a pose with the specified forward and up vectors.
 
 @param forward The forward direction.
 @param up The up direction.
 @returns A new pose stucture.
 @note This function creates a pose where @p +z is forward.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMakeLookAt(SPVector3DFloat forward, SPVector3DFloat up)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMakeLookAt(SPVector3DFloat forward, SPVector3DFloat up) {
    
    SPPoint3DFloat position = SPPoint3DFloatZero;
    
    SPPoint3DFloat target = SPPoint3DFloatMakeWithVector(forward.vector);
    
    return SPPose3DFloatMakeLookAt(position, target, up);
}

/*!
 @abstract Returns a pose with with a position and rotation that are defined by a projective transform.
 
 @param transform The source transform. The function only considers the transform's rotation and
 translation components.
 @returns A pose with a position and rotation that are defined by a projective transform.
 @note
 This function can't extract rotation from a non-scale-rotate-translate projective transform. In that case, the function
 returns @p SPPose3DFloatInvalid.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMakeWithProjectiveTransform(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMakeWithProjectiveTransform(SPProjectiveTransform3DFloat transform) {
    
    SPRotation3DFloat rotation = SPProjectiveTransform3DFloatGetRotation(transform);
    
    if (!SPRotation3DFloatIsValid(rotation)) {
        return SPPose3DFloatInvalid;
    }
    
    SPPoint3DFloat position = SPPoint3DFloatMakeWithVector(SPProjectiveTransform3DFloatGetTranslation(transform));
    
    return SPPose3DFloatMake(position, rotation);
}

// MARK: - Creating a pose from a 4x4 matrix

/*!
 @abstract Returns a new pose structure from the specified 4 x 4 matrix.
 
 @param matrix The source matrix.
 @returns A new pose structure.
 @note
 This function can't extract rotation from a non-scale-rotate-translate matrix transform. In that case, the function
 returns @p SPPose3DFloatInvalid.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMakeWith4x4Matrix(simd_float4x4 matrix)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMakeWith4x4Matrix(simd_float4x4 matrix) {
    
    SPProjectiveTransform3DFloat transform = SPProjectiveTransform3DFloatMakeWith4x4Matrix(matrix);
    
    return SPPose3DFloatMakeWithProjectiveTransform(transform);
}

// MARK: - Calculating the inverse of a pose

/*!
 @abstract Returns a new pose with the inverse matrix of the specified pose.
 
 @param pose The source pose.
 @returns A new pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatGetInverse(SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatGetInverse(SPPose3DFloat pose) {
    
    simd_quatf q = simd_inverse(pose.rotation.quaternion);
    simd_float3 p = simd_act(q, -pose.position.vector);
    
    return SPPose3DFloatMakeWithVector(p, q);
}

// MARK: - Returning the product of two poses

/*!
 @abstract Returns a new pose that's constructed by concatenating two existing  poses.
 
 @param lhs The first pose to multiply.
 @param rhs The second pose to multiply.
 @returns A new pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatConcatenation(SPPose3DFloat lhs, SPPose3DFloat rhs)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatConcatenation(SPPose3DFloat lhs, SPPose3DFloat rhs) {
    
    simd_float4x4 m = simd_mul(SPPose3DFloatGet4x4Matrix(lhs),
                                SPPose3DFloatGet4x4Matrix(rhs));
    
    return SPPose3DFloatMakeWith4x4Matrix(m);
}

// MARK: - Rotation
/*!
 @abstract Returns a pose with a rotation that's rotated by the specified quaternion.
 
 @param pose The source pose.
 @param quaternion The quaternion that defines the rotation.
 @returns A pose with a rotation that's rotated by the specified quaternion.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatRotateByQuaternion(SPPose3DFloat pose, simd_quatf quaternion)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatRotateByQuaternion(SPPose3DFloat pose, simd_quatf quaternion) {
    
    simd_quatf q = simd_mul(quaternion, pose.rotation.quaternion);
    
    SPPose3DFloat p = SPPose3DFloatMake(pose.position,
                                        (SPRotation3DFloat) { .quaternion = q });
    
    return p;
}

/*!
 @abstract Returns a pose with a rotation that's rotated by the specified rotation.
 
 @param pose The source pose.
 @param rotation The rotation structure that defines the rotation.
 @returns A pose with a rotation that's rotated by the specified rotation structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatRotate(SPPose3DFloat pose, SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatRotate(SPPose3DFloat pose, SPRotation3DFloat rotation) {
    
    return SPPose3DFloatRotateByQuaternion(pose, rotation.quaternion);
}

// MARK: - Translation

/*!
 @abstract Returns a pose with a position that is offset from that of the source pose.
 
 @param pose The source pose.
 @param offset A vector that defines the offset.
 @returns A pose that's offset by the @p x, @p y, and @p z of the vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatTranslate(SPPose3DFloat pose, SPVector3DFloat offset)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatTranslate(SPPose3DFloat pose, SPVector3DFloat offset) {
    
    SPPose3DFloat p = SPPose3DFloatMake(SPPoint3DFloatTranslate(pose.position, offset),
                                        pose.rotation);
    
    return p;
}

// MARK: - Creating a pose from a transform

/*!
 @abstract Returns a pose with with a position and rotation that are defined by an affine transform.
 
 @param transform The source transform. The function only considers the transform's rotation and
 translation components.
 @returns A pose with a position and rotation that are defined by an affine transform.
 @note
 This function can't extract rotation from a non-scale-rotate-translate affine transform. In that case, the function
 returns @p SPPose3DFloatInvalid.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMakeWithAffineTransform(SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatMakeWithAffineTransform(SPAffineTransform3DFloat transform) {
    
    SPRotation3DFloat rotation = SPAffineTransform3DFloatGetRotation(transform);
    
    if (!SPRotation3DFloatIsValid(rotation)) {
        return SPPose3DFloatInvalid;
    }
    
    SPPoint3DFloat position = SPPoint3DFloatMakeWithVector(SPAffineTransform3DFloatGetTranslation(transform));
    
    return SPPose3DFloatMake(position, rotation);
}



// MARK: - Flipping a pose

/*!
 @abstract Returns a pose that's flipped along the specified axis.
 
 @discussion
 If you pass a flip axis that's not @p x , @p y , or @p z , the function returns @p pose unmodified.
 
 @param pose The source pose.
 @param flipAxis The flip axis.
 @returns A new pose flipped along the specified axis.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatFlip(SPPose3DFloat pose,
                                SPAxis flipAxis)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPose3DFloat SPPose3DFloatFlip(SPPose3DFloat pose,
                                SPAxis flipAxis) {
    
    if(flipAxis != SPAxisX && flipAxis != SPAxisY && flipAxis != SPAxisZ) {
        return pose;
    }
    
    SPAffineTransform3DFloat t = SPAffineTransform3DFloatMakeWithPose(pose);
    t = SPAffineTransform3DFloatFlip(t, flipAxis);
    return SPPose3DFloatMakeWithAffineTransform(t);
}


#endif /* SPPose3DFloat_h */
