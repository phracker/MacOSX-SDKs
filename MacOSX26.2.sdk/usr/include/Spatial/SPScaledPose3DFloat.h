#ifndef SPScaledPose3DFloatFloat_h
#define SPScaledPose3DFloatFloat_h

#include <Spatial/StructuresFloat.h>
#include <Spatial/SPAffineTransform3DFloat.h>

// MARK: - Creating a scaled pose

/*!
 @abstract Returns a scaled pose with the specified position, rotation, and scale.
 
 @param position A point structure that specifies the position of the scaled pose.
 @param rotation A rotation structure that specifies the rotation of the scaled pose.
 @param scale The uniform scale of the pose.
 @returns A new scaled pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMake(SPPoint3DFloat position,
                                            SPRotation3DFloat rotation,
                                            float scale)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMake(SPPoint3DFloat position,
                                            SPRotation3DFloat rotation,
                                            float scale) {
    
    return (SPScaledPose3DFloat) {
        .position = position,
        .rotation = rotation,
        .scale = scale
    };
}

/*!
 @abstract Returns a scaled pose with the specified position, rotation, and scale.
 
 @param position A point structure that specifies the position of the scaled pose.
 @param rotation A rotation structure that specifies the rotation of the scaled pose.
 @param scale The uniform scale of the pose.
 @returns A new scaled pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMakeWithVector(simd_float3 position,
                                                      simd_quatf rotation,
                                                      float scale)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMakeWithVector(simd_float3 position,
                                                      simd_quatf rotation,
                                                      float scale) {
    
    return (SPScaledPose3DFloat) {
        .position = SPPoint3DFloatMakeWithVector(position),
        .rotation.quaternion = rotation,
        .scale = scale
    };
}

/*!
 @abstract Returns a scaled pose with the specified pose and uniform scale.
 
 @param pose The pose structure.
 @param scale The uniform scale.
 @returns A new scaled pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMake(SPPose3DFloat pose,
                                            float scale)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMake(SPPose3DFloat pose,
                                            float scale) {
    
    return SPScaledPose3DFloatMake(pose.position,
                                   pose.rotation,
                                   scale);
}

// MARK: - SPScaledPose3DFloatGet4x4Matrix

/*!
 @abstract Returns a 4 x 4 matrix that represents the scaled pose's translation, rotation, and scale.
 
 @param scaledPose The source scaled pose.
 @returns A new scaled pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_float4x4 SPScaledPose3DFloatGet4x4Matrix(SPScaledPose3DFloat scaledPose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_float4x4 SPScaledPose3DFloatGet4x4Matrix(SPScaledPose3DFloat scaledPose) {
    
    SPAffineTransform3DFloat tx = SPAffineTransform3DFloatMakeWithScaledPose(scaledPose);
    return SPAffineTransform3DFloatGet4x4Matrix(tx);
}

// MARK: - Comparing scaled poses

/// Returns @p true if both scaled poses are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPScaledPose3DFloatEqualToPose(SPScaledPose3DFloat scaledPose1, SPScaledPose3DFloat scaledPose2)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPScaledPose3DFloatEqualToPose(SPScaledPose3DFloat scaledPose1, SPScaledPose3DFloat scaledPose2) {
    
    return (
            SPPoint3DFloatEqualToPoint(scaledPose1.position, scaledPose2.position) &&
            SPRotation3DFloatEqualToRotation(scaledPose1.rotation, scaledPose2.rotation) &&
            scaledPose1.scale == scaledPose2.scale
            );
}

/*!
 @abstract Returns a Boolean value that indicates whether the two scaled poses are equal within the specified absolute tolerance.
 
 @param p1 The first scaled pose.
 @param p2 The first scaled pose.
 @returns A Boolean value that indicates whether the two scaled poses are equal within the specified absolute tolerance.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPScaledPose3DFloatAlmostEqualToPose(SPScaledPose3DFloat p1,
                                          SPScaledPose3DFloat p2,
                                          float tolerance)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
bool SPScaledPose3DFloatAlmostEqualToPose(SPScaledPose3DFloat p1,
                                          SPScaledPose3DFloat p2,
                                          float tolerance) {
    
    bool rotationIsEqual = _sp_almost_equal_tolerance(p1.rotation.quaternion.vector.x, p2.rotation.quaternion.vector.x, tolerance) &&
    _sp_almost_equal_tolerance(p1.rotation.quaternion.vector.y, p2.rotation.quaternion.vector.y, tolerance) &&
    _sp_almost_equal_tolerance(p1.rotation.quaternion.vector.z, p2.rotation.quaternion.vector.z, tolerance) &&
    _sp_almost_equal_tolerance(p1.rotation.quaternion.vector.w, p2.rotation.quaternion.vector.w, tolerance);
    
    bool positionIsEqual = _sp_almost_equal_tolerance(p1.position.x, p2.position.x, tolerance) &&
    _sp_almost_equal_tolerance(p1.position.y, p2.position.y, tolerance) &&
    _sp_almost_equal_tolerance(p1.position.z, p2.position.z, tolerance);
    
    bool scaleIsEqual = _sp_almost_equal_tolerance(p1.scale, p2.scale, tolerance);
    
    return rotationIsEqual && positionIsEqual && scaleIsEqual;
}

/*!
 @abstract Returns a Boolean value that indicates whether the two scaled poses are equal within the Spatial default absolute tolerance.
 
 @param p1 The first scaled pose.
 @param p2 The first scaled pose.
 @returns A Boolean value that indicates whether the two scaled poses are equal within the Spatial default absolute tolerance.
 @note The Spatial default tolerance is @p sqrt(__DBL_EPSILON__) .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPScaledPose3DFloatAlmostEqualToPose(SPScaledPose3DFloat p1,
                                          SPScaledPose3DFloat p2)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
bool SPScaledPose3DFloatAlmostEqualToPose(SPScaledPose3DFloat p1,
                                          SPScaledPose3DFloat p2) {
    
    return SPScaledPose3DFloatAlmostEqualToPose(p1, p2, SPDefaultTolerance);
}

// MARK: - SPScaledPose3DFloat identity

/*!
 @abstract The identity scaled pose.
 */
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_REFINED_FOR_SWIFT
static const SPScaledPose3DFloat SPScaledPose3DFloatIdentity = {
    .position = (SPPoint3DFloat){ 0, 0, 0, 1 },
    .rotation = (SPRotation3DFloat) {
        .quaternion = (simd_quatf){ .vector = {0, 0, 0, 1}
        }
    },
        .scale = 1.0
};

/*!
 @abstract Returns a Boolean value that indicates whether the scaled pose is the identity transform.
 
 @param scaledPose The source scaled pose.
 @returns A Boolean value that indicates whether the transform is the identity pose.
 @note This function checks for equality within the Spatial default tolerance.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPScaledPose3DFloatIsIdentity(SPScaledPose3DFloat scaledPose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPScaledPose3DFloatIsIdentity(SPScaledPose3DFloat scaledPose) {
    return SPScaledPose3DFloatAlmostEqualToPose(scaledPose, SPScaledPose3DFloatIdentity);
}

// MARK: - SPScaledPose3DFloatMakeLookAt

/*!
 @abstract Returns a scaled pose at the specified position with the rotation towards the target.
 
 @param position A point structure that specifies the position of the scaled pose.
 @param target The point that the scaled pose orients towards.
 @param scale The uniform scale of the pose.
 @param up The up direction.
 @returns A new scaled pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMakeLookAt(SPPoint3DFloat position,
                                                  SPPoint3DFloat target,
                                                  float scale,
                                                  SPVector3DFloat up)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMakeLookAt(SPPoint3DFloat position,
                                                  SPPoint3DFloat target,
                                                  float scale,
                                                  SPVector3DFloat up) {
    
    SPRotation3DFloat r = SPRotation3DFloatMakeLookAt(position, target, up);
    
    return (SPScaledPose3DFloat) {
        .position = position,
        .rotation = r,
        .scale = scale
    };
}

/*!
 @abstract Returns a scaled pose at the origin with the rotation towards the target.
 
 @param target The point that the scaled pose orients towards.
 @param scale The uniform scale of the pose.
 @param up The up direction.
 @returns A new scaled pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMakeLookAt(SPPoint3DFloat target,
                                                  float scale,
                                                  SPVector3DFloat up)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMakeLookAt(SPPoint3DFloat target,
                                                  float scale,
                                                  SPVector3DFloat up) {
    
    SPPoint3DFloat position = SPPoint3DFloatZero;
    
    return SPScaledPose3DFloatMakeLookAt(position, target, scale, up);
}

/*!
 @abstract Returns a scaled pose with the specified forward and up vectors.
 
 @param forward The forward direction.
 @param scale The uniform scale of the pose.
 @param up The up direction.
 @returns A new scaled pose stucture.
 @note This function creates a scaled pose where @p +z is forward.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMakeLookAt(SPVector3DFloat forward,
                                                  float scale,
                                                  SPVector3DFloat up)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMakeLookAt(SPVector3DFloat forward,
                                                  float scale,
                                                  SPVector3DFloat up) {
    
    SPPoint3DFloat position = SPPoint3DFloatZero;
    
    SPPoint3DFloat target = SPPoint3DFloatMakeWithVector(forward.vector);
    
    return SPScaledPose3DFloatMakeLookAt(position, target, scale, up);
}

// MARK: - SPScaledPose3DFloatMakeWithProjectiveTransform

/*!
 @abstract Returns a scaled pose with with a position, rotation, and scale that are defined by a projective transform.
 
 @param transform The source transform. The function only considers the transform's scale, rotation, and
 translation components.
 @returns A scaled pose with a scale, position and rotation that are defined by a projective transform.
 @note
 This function can't extract rotation from a non-scale-rotate-translate projective transform. In that case, the function
 returns @p SPScaledPose3DFloatInvalid. If the specified  @p SPProjectiveTransform3DFloat doesn't have uniform
 scale (that is,  @p SPProjectiveTransform3DFloatIsUniform returns  @p false) the function returns
 @p SPScaledPose3DFloatInvalid.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMakeWithProjectiveTransform(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMakeWithProjectiveTransform(SPProjectiveTransform3DFloat transform) {
    
    SPRotation3DFloat rotation = SPProjectiveTransform3DFloatGetRotation(transform);
    
    if (!SPRotation3DFloatIsValid(rotation)) {
        return SPScaledPose3DFloatInvalid;
    }
    
    SPSize3DFloat scale = SPProjectiveTransform3DFloatGetScale(transform);
    
    if(!_sp_almost_equal_tolerance(scale.width, scale.height, SPDefaultToleranceFloat) || !_sp_almost_equal_tolerance(scale.depth, scale.height, SPDefaultToleranceFloat)) {
        return SPScaledPose3DFloatInvalid;
    }
    
    SPPoint3DFloat position = SPPoint3DFloatMakeWithVector(SPProjectiveTransform3DFloatGetTranslation(transform));
    
    return SPScaledPose3DFloatMake(position, rotation, scale.width);
}

// MARK: - SPScaledPose3DFloatMakeWith4x4Matrix

/*!
 @abstract Returns a new scaled pose structure from the specified 4 x 4 matrix.
 
 @param matrix The source matrix.
 @returns A new scaled pose structure.
 @note
 This function can't extract rotation from a non-scale-rotate-translate matrix transform. In that case, the function
 returns @p SPScaledPose3DFloatInvalid. If the specified matrix doesn't have uniform scale, the function returns
 @p SPScaledPose3DFloatInvalid.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMakeWith4x4Matrix(simd_float4x4 matrix)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMakeWith4x4Matrix(simd_float4x4 matrix) {
    
    SPProjectiveTransform3DFloat transform = SPProjectiveTransform3DFloatMakeWith4x4Matrix(matrix);
    
    return SPScaledPose3DFloatMakeWithProjectiveTransform(transform);
}

// MARK: - SPScaledPose3DFloatRotateByQuaternion

/*!
 @abstract Returns a scaled pose with a rotation that's rotated by the specified quaternion.
 
 @param scaledPose The source scaled pose.
 @param quaternion The quaternion that defines the rotation.
 @returns A scaled pose with a rotation that's rotated by the specified quaternion.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatRotateByQuaternion(SPScaledPose3DFloat scaledPose, simd_quatf quaternion)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatRotateByQuaternion(SPScaledPose3DFloat scaledPose, simd_quatf quaternion) {
    
    simd_quatf q = simd_mul(quaternion, scaledPose.rotation.quaternion);
    
    SPScaledPose3DFloat p = SPScaledPose3DFloatMake(scaledPose.position,
                                                    (SPRotation3DFloat) { .quaternion = q },
                                                    scaledPose.scale);
    
    return p;
}

// MARK: - SPScaledPose3DFloatRotate

/*!
 @abstract Returns a scaled pose with a rotation that's rotated by the specified rotation.
 
 @param scaledPose The source scaled pose.
 @param rotation The rotation structure that defines the rotation.
 @returns A scaled pose with a rotation that's rotated by the specified rotation structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatRotate(SPScaledPose3DFloat scaledPose, SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatRotate(SPScaledPose3DFloat scaledPose, SPRotation3DFloat rotation) {
    
    return SPScaledPose3DFloatRotateByQuaternion(scaledPose, rotation.quaternion);
}

// MARK: - SPScaledPose3DFloatTranslate

/*!
 @abstract Returns a scaled pose with a position that is offset from that of the source scaled pose.
 
 @param scaledPose The source scaled pose.
 @param offset A vector that defines the offset.
 @returns A scaled pose that's offset by the @p x, @p y, and @p z of the vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatTranslate(SPScaledPose3DFloat scaledPose, SPVector3DFloat offset)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatTranslate(SPScaledPose3DFloat scaledPose, SPVector3DFloat offset) {
    
    SPScaledPose3DFloat p = SPScaledPose3DFloatMake(SPPoint3DFloatTranslate(scaledPose.position, offset),
                                                    scaledPose.rotation,
                                                    scaledPose.scale);
    
    return p;
}

// MARK: - SPScaledPose3DFloatMakeWithAffineTransform

/*!
 @abstract Returns a scaled pose with with a position, rotation, and scale that are defined by an affine transform.
 
 @param transform The source transform. The function only considers the transform's scale, rotation, and
 translation components.
 @returns A scaled pose with a position and rotation that are defined by an affine transform.
 @note
 This function can't extract rotation from a non-scale-rotate-translate affine transform. In that case, the function
 returns @p SPScaledPose3DFloatInvalid. If the specified  @p SPAffineTransform3DFloat doesn't have uniform
 scale (that is,  @p SPAffineTransform3DFloatIsUniform returns  @p false), the function returns
 @p SPScaledPose3DFloatInvalid.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMakeWithAffineTransform(SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatMakeWithAffineTransform(SPAffineTransform3DFloat transform) {
    
    SPRotation3DFloat rotation = SPAffineTransform3DFloatGetRotation(transform);
    
    if (!SPRotation3DFloatIsValid(rotation)) {
        return SPScaledPose3DFloatInvalid;
    }
    
    SPSize3DFloat scale = SPAffineTransform3DFloatGetScale(transform);
    
    if(!_sp_almost_equal_tolerance(scale.width, scale.height, SPDefaultToleranceFloat) || !_sp_almost_equal_tolerance(scale.depth, scale.height, SPDefaultToleranceFloat)) {
        return SPScaledPose3DFloatInvalid;
    }
    
    SPPoint3DFloat position = SPPoint3DFloatMakeWithVector(SPAffineTransform3DFloatGetTranslation(transform));
    
    return SPScaledPose3DFloatMake(position, rotation, scale.width);
}

// MARK: - SPScaledPose3DFloatGetInverse

/*!
 @abstract Returns a new scaled pose with the inverse matrix of the specified scaled pose.
 
 @param scaledPose The source scaled pose.
 @returns A new scaled pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatGetInverse(SPScaledPose3DFloat scaledPose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatGetInverse(SPScaledPose3DFloat scaledPose) {
    
    SPAffineTransform3DFloat tx = SPAffineTransform3DFloatMakeWithScaledPose(scaledPose);
    tx = SPAffineTransform3DFloatInverted(tx);
    return SPScaledPose3DFloatMakeWithAffineTransform(tx);
}

// MARK: - SPScaledPose3DFloatFlip

/*!
 @abstract Returns a scaled pose that's flipped along the specified axis.
 
 @discussion
 If you pass a flip axis that's not @p x , @p y , or @p z , the function returns @p scaled pose unmodified.
 
 @param scaledPose The source scaled pose.
 @param flipAxis The flip axis.
 @returns A new scaled pose flipped along the specified axis.
 @note
 The flipped scaled pose that this function returns has the same scale as the specified pose.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatFlip(SPScaledPose3DFloat scaledPose,
                                            SPAxis flipAxis)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatFlip(SPScaledPose3DFloat scaledPose,
                                            SPAxis flipAxis) {
    
    if(flipAxis != SPAxisX && flipAxis != SPAxisY && flipAxis != SPAxisZ) {
        return scaledPose;
    }
    
    SPAffineTransform3DFloat t = SPAffineTransform3DFloatMakeWithScaledPose(scaledPose);
    t = SPAffineTransform3DFloatFlip(t, flipAxis);
    return SPScaledPose3DFloatMakeWithAffineTransform(t);
}

// MARK: - Concatenation

/*!
 @abstract Returns a new scaled pose that's constructed by concatenating two existing  poses.
 
 @param lhs The first scaled pose to multiply.
 @param rhs The second scaled pose to multiply.
 @returns A new scaled pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatConcatenation(SPScaledPose3DFloat lhs, SPScaledPose3DFloat rhs)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatConcatenation(SPScaledPose3DFloat lhs, SPScaledPose3DFloat rhs) {
    
    SPAffineTransform3DFloat product = SPAffineTransform3DFloatConcatenation(
                                                                             SPAffineTransform3DFloatMakeWithScaledPose(lhs),
                                                                             SPAffineTransform3DFloatMakeWithScaledPose(rhs));
    
    return SPScaledPose3DFloatMakeWithAffineTransform(product);
}

/*!
 @abstract Returns a new scaled pose that's constructed by concatenating a scaled pose and a pose.
 
 @param lhs The first scaled pose to multiply.
 @param rhs The second pose to multiply.
 @returns A new scaled pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatConcatenation(SPScaledPose3DFloat lhs, SPPose3DFloat rhs)
SPATIAL_REFINED_FOR_SWIFT
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatConcatenation(SPScaledPose3DFloat lhs, SPPose3DFloat rhs) {
    
    return SPScaledPose3DFloatConcatenation(lhs,
                                            SPScaledPose3DFloatMake(rhs, 1.0));
}

/*!
 @abstract Returns a new scaled pose that's constructed by concatenating a pose and a scaled pose.
 
 @param lhs The first pose to multiply.
 @param rhs The second scaled pose to multiply.
 @returns A new pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatConcatenation(SPPose3DFloat lhs, SPScaledPose3DFloat rhs)
SPATIAL_REFINED_FOR_SWIFT
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3DFloat SPScaledPose3DFloatConcatenation(SPPose3DFloat lhs, SPScaledPose3DFloat rhs) {
    
    return SPScaledPose3DFloatConcatenation(SPScaledPose3DFloatMake(lhs, 1.0),
                                            rhs);
}

#endif /* SPScaledPose3DFloatFloat_h */
