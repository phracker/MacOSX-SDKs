#ifndef SPScaledPose3D_h
#define SPScaledPose3D_h

#include <Spatial/Structures.h>

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
SPScaledPose3D SPScaledPose3DMake(SPPoint3D position,
                                  SPRotation3D rotation,
                                  double scale)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DMake(SPPoint3D position,
                                  SPRotation3D rotation,
                                  double scale) {
    
    return (SPScaledPose3D) {
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
SPScaledPose3D SPScaledPose3DMakeWithVector(simd_double3 position,
                                            simd_quatd rotation,
                                            double scale)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DMakeWithVector(simd_double3 position,
                                            simd_quatd rotation,
                                            double scale) {
    
    return (SPScaledPose3D) {
        .position = SPPoint3DMakeWithVector(position),
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
SPScaledPose3D SPScaledPose3DMake(SPPose3D pose,
                                  double scale)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DMake(SPPose3D pose,
                                  double scale) {
    
    return SPScaledPose3DMake(pose.position,
                              pose.rotation,
                              scale);
}

// MARK: - SPScaledPose3DGet4x4Matrix

/*!
 @abstract Returns a 4 x 4 matrix that represents the scaled pose's translation, rotation, and scale.
 
 @param scaledPose The source scaled pose.
 @returns A new scaled pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_double4x4 SPScaledPose3DGet4x4Matrix(SPScaledPose3D scaledPose)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_double4x4 SPScaledPose3DGet4x4Matrix(SPScaledPose3D scaledPose) {
    
    SPAffineTransform3D tx = SPAffineTransform3DMakeWithScaledPose(scaledPose);
    return SPAffineTransform3DGet4x4Matrix(tx);
}

// MARK: - Comparing scaled poses

/// Returns @p true if both scaled poses are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPScaledPose3DEqualToPose(SPScaledPose3D scaledPose1, SPScaledPose3D scaledPose2)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPScaledPose3DEqualToPose(SPScaledPose3D scaledPose1, SPScaledPose3D scaledPose2) {
    
    return (
            SPPoint3DEqualToPoint(scaledPose1.position, scaledPose2.position) &&
            SPRotation3DEqualToRotation(scaledPose1.rotation, scaledPose2.rotation) &&
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
bool SPScaledPose3DAlmostEqualToPose(SPScaledPose3D p1,
                                     SPScaledPose3D p2,
                                     double tolerance)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
bool SPScaledPose3DAlmostEqualToPose(SPScaledPose3D p1,
                                     SPScaledPose3D p2,
                                     double tolerance) {
    
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
bool SPScaledPose3DAlmostEqualToPose(SPScaledPose3D p1,
                                     SPScaledPose3D p2)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
bool SPScaledPose3DAlmostEqualToPose(SPScaledPose3D p1,
                                     SPScaledPose3D p2) {
    
    return SPScaledPose3DAlmostEqualToPose(p1, p2, SPDefaultTolerance);
}

// MARK: - SPScaledPose3D identity

/*!
 @abstract The identity scaled pose.
 */
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));
SPATIAL_REFINED_FOR_SWIFT
static const SPScaledPose3D SPScaledPose3DIdentity = {
    .position = (SPPoint3D){ 
        0,
        0,
        0,
#if !defined __swift__
        1.0
#endif
    },
    .rotation = (SPRotation3D) {
        .quaternion = (simd_quatd){ .vector = {0, 0, 0, 1}
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
bool SPScaledPose3DIsIdentity(SPScaledPose3D scaledPose)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPScaledPose3DIsIdentity(SPScaledPose3D scaledPose) {
    return SPScaledPose3DAlmostEqualToPose(scaledPose, SPScaledPose3DIdentity);
}

// MARK: - SPScaledPose3DMakeLookAt

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
SPScaledPose3D SPScaledPose3DMakeLookAt(SPPoint3D position,
                                        SPPoint3D target,
                                        double scale,
                                        SPVector3D up)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DMakeLookAt(SPPoint3D position,
                                        SPPoint3D target,
                                        double scale,
                                        SPVector3D up) {
    
    SPRotation3D r = SPRotation3DMakeLookAt(position, target, up);
    
    return (SPScaledPose3D) {
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
SPScaledPose3D SPScaledPose3DMakeLookAt(SPPoint3D target,
                                        double scale,
                                        SPVector3D up)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DMakeLookAt(SPPoint3D target,
                                        double scale,
                                        SPVector3D up) {
    
    SPPoint3D position = SPPoint3DZero;
    
    return SPScaledPose3DMakeLookAt(position, target, scale, up);
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
SPScaledPose3D SPScaledPose3DMakeLookAt(SPVector3D forward,
                                        double scale,
                                        SPVector3D up)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DMakeLookAt(SPVector3D forward,
                                        double scale,
                                        SPVector3D up) {
 
    SPPoint3D position = SPPoint3DZero;
    
    SPPoint3D target = SPPoint3DMakeWithVector(forward.vector);
    
    return SPScaledPose3DMakeLookAt(position, target, scale, up);
}

// MARK: - SPScaledPose3DMakeWithProjectiveTransform

/*!
 @abstract Returns a scaled pose with with a position, rotation, and scale that are defined by a projective transform.
 
 @param transform The source transform. The function only considers the transform's scale, rotation, and
 translation components.
 @returns A scaled pose with a scale, position and rotation that are defined by a projective transform.
 @note
 This function can't extract rotation from a non-scale-rotate-translate projective transform. In that case, the function
 returns @p SPScaledPose3DInvalid. If the specified  @p SPProjectiveTransform3D doesn't have uniform
 scale (that is,  @p SPProjectiveTransform3DIsUniform returns  @p false) the function returns
 @p SPScaledPose3DInvalid.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DMakeWithProjectiveTransform(SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DMakeWithProjectiveTransform(SPProjectiveTransform3D transform) {
    
    SPRotation3D rotation = SPProjectiveTransform3DGetRotation(transform);
    
    if (!SPRotation3DIsValid(rotation)) {
        return SPScaledPose3DInvalid;
    }
    
    SPSize3D scale = SPProjectiveTransform3DGetScale(transform);
    
    if(!_sp_almost_equal(scale.width, scale.height) || !_sp_almost_equal(scale.depth, scale.height)) {
        return SPScaledPose3DInvalid;
    }
    
    SPPoint3D position = SPPoint3DMakeWithVector(SPProjectiveTransform3DGetTranslation(transform));
    
    return SPScaledPose3DMake(position, rotation, scale.width);
}

// MARK: - SPScaledPose3DMakeWith4x4Matrix

/*!
 @abstract Returns a new scaled pose structure from the specified 4 x 4 matrix.
 
 @param matrix The source matrix.
 @returns A new scaled pose structure.
 @note
 This function can't extract rotation from a non-scale-rotate-translate matrix transform. In that case, the function
 returns @p SPScaledPose3DInvalid. If the specified matrix doesn't have uniform scale, the function returns
 @p SPScaledPose3DInvalid.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DMakeWith4x4Matrix(simd_double4x4 matrix)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DMakeWith4x4Matrix(simd_double4x4 matrix) {
    
    SPProjectiveTransform3D transform = SPProjectiveTransform3DMakeWith4x4Matrix(matrix);
    
    return SPScaledPose3DMakeWithProjectiveTransform(transform);
}

// MARK: - SPScaledPose3DRotateByQuaternion

/*!
 @abstract Returns a scaled pose with a rotation that's rotated by the specified quaternion.
 
 @param scaledPose The source scaled pose.
 @param quaternion The quaternion that defines the rotation.
 @returns A scaled pose with a rotation that's rotated by the specified quaternion.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DRotateByQuaternion(SPScaledPose3D scaledPose, simd_quatd quaternion)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DRotateByQuaternion(SPScaledPose3D scaledPose, simd_quatd quaternion) {
    
    simd_quatd q = simd_mul(quaternion, scaledPose.rotation.quaternion);
    
    SPScaledPose3D p = SPScaledPose3DMake(scaledPose.position,
                                          (SPRotation3D) { .quaternion = q },
                                          scaledPose.scale);
    
    return p;
}

// MARK: - SPScaledPose3DRotate

/*!
 @abstract Returns a scaled pose with a rotation that's rotated by the specified rotation.
 
 @param scaledPose The source scaled pose.
 @param rotation The rotation structure that defines the rotation.
 @returns A scaled pose with a rotation that's rotated by the specified rotation structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DRotate(SPScaledPose3D scaledPose, SPRotation3D rotation)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DRotate(SPScaledPose3D scaledPose, SPRotation3D rotation) {
    
    return SPScaledPose3DRotateByQuaternion(scaledPose, rotation.quaternion);
}

// MARK: - SPScaledPose3DTranslate

/*!
 @abstract Returns a scaled pose with a position that is offset from that of the source scaled pose.
 
 @param scaledPose The source scaled pose.
 @param offset A vector that defines the offset.
 @returns A scaled pose that's offset by the @p x, @p y, and @p z of the vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DTranslate(SPScaledPose3D scaledPose, SPVector3D offset)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DTranslate(SPScaledPose3D scaledPose, SPVector3D offset) {
    
    SPScaledPose3D p = SPScaledPose3DMake(SPPoint3DTranslate(scaledPose.position, offset),
                                          scaledPose.rotation,
                                          scaledPose.scale);
    
    return p;
}

// MARK: - SPScaledPose3DMakeWithAffineTransform

/*!
 @abstract Returns a scaled pose with with a position, rotation, and scale that are defined by an affine transform.
 
 @param transform The source transform. The function only considers the transform's scale, rotation, and
 translation components.
 @returns A scaled pose with a position and rotation that are defined by an affine transform.
 @note
 This function can't extract rotation from a non-scale-rotate-translate affine transform. In that case, the function
 returns @p SPScaledPose3DInvalid. If the specified  @p SPAffineTransform3D doesn't have uniform
 scale (that is,  @p SPAffineTransform3DIsUniform returns  @p false), the function returns
 @p SPScaledPose3DInvalid.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DMakeWithAffineTransform(SPAffineTransform3D transform)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DMakeWithAffineTransform(SPAffineTransform3D transform) {
    
    SPRotation3D rotation = SPAffineTransform3DGetRotation(transform);
    
    if (!SPRotation3DIsValid(rotation)) {
        return SPScaledPose3DInvalid;
    }
 
    SPSize3D scale = SPAffineTransform3DGetScale(transform);
    
    if(!_sp_almost_equal(scale.width, scale.height) || !_sp_almost_equal(scale.depth, scale.height)) {
        return SPScaledPose3DInvalid;
    }
    
    SPPoint3D position = SPPoint3DMakeWithVector(SPAffineTransform3DGetTranslation(transform));

    return SPScaledPose3DMake(position, rotation, scale.width);
}

// MARK: - SPScaledPose3DGetInverse

/*!
 @abstract Returns a new scaled pose with the inverse matrix of the specified scaled pose.
 
 @param scaledPose The source scaled pose.
 @returns A new scaled pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DGetInverse(SPScaledPose3D scaledPose)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DGetInverse(SPScaledPose3D scaledPose) {
  
    SPAffineTransform3D tx = SPAffineTransform3DMakeWithScaledPose(scaledPose);
    tx = SPAffineTransform3DInverted(tx);
    return SPScaledPose3DMakeWithAffineTransform(tx);
}

// MARK: - SPScaledPose3DFlip

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
SPScaledPose3D SPScaledPose3DFlip(SPScaledPose3D scaledPose,
                                  SPAxis flipAxis)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DFlip(SPScaledPose3D scaledPose,
                                  SPAxis flipAxis) {

    if(flipAxis != SPAxisX && flipAxis != SPAxisY && flipAxis != SPAxisZ) {
        return scaledPose;
    }
  
    SPAffineTransform3D t = SPAffineTransform3DMakeWithScaledPose(scaledPose);
    t = SPAffineTransform3DFlip(t, flipAxis);
    return SPScaledPose3DMakeWithAffineTransform(t);
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
SPScaledPose3D SPScaledPose3DConcatenation(SPScaledPose3D lhs, SPScaledPose3D rhs)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DConcatenation(SPScaledPose3D lhs, SPScaledPose3D rhs) {
    
    SPAffineTransform3D product = SPAffineTransform3DConcatenation(
                           SPAffineTransform3DMakeWithScaledPose(lhs),
                           SPAffineTransform3DMakeWithScaledPose(rhs));
    
    return SPScaledPose3DMakeWithAffineTransform(product);
}

/*!
 @abstract Returns a new scaled pose that's constructed by concatenating a scaled pose and a pose.
 
 @param lhs The first scaled pose to multiply.
 @param rhs The second pose to multiply.
 @returns A new scaled pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DConcatenation(SPScaledPose3D lhs, SPPose3D rhs)
SPATIAL_REFINED_FOR_SWIFT
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DConcatenation(SPScaledPose3D lhs, SPPose3D rhs) {

    return SPScaledPose3DConcatenation(lhs,
                                       SPScaledPose3DMake(rhs, 1.0));
}

/*!
 @abstract Returns a new scaled pose that's constructed by concatenating a pose and a scaled pose.
 
 @param lhs The first pose to multiply.
 @param rhs The second scaled pose to multiply.
 @returns A new pose structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DConcatenation(SPPose3D lhs, SPScaledPose3D rhs)
SPATIAL_REFINED_FOR_SWIFT
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPScaledPose3D SPScaledPose3DConcatenation(SPPose3D lhs, SPScaledPose3D rhs) {
    
    return SPScaledPose3DConcatenation(SPScaledPose3DMake(lhs, 1.0),
                                       rhs);
}

#endif /* SPScaledPose3D_h */
