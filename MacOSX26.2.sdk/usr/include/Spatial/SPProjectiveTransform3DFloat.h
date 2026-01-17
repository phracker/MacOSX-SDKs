#ifndef Spatial_SPProjectiveTransform3DFloat_h
#define Spatial_SPProjectiveTransform3DFloat_h

#include <Spatial/StructuresFloat.h>
#include <Spatial/SPRotation3DFloat.h>
#include <Spatial/SPAffineTransform3DFloat.h>

// MARK: - SINGLE-PRECISION Public API

// MARK: - Creating a projective transform

/// Returns a new transform from the specified 4 x 4 matrix.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeWith4x4Matrix(simd_float4x4 matrix)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/// Returns a new transform from the specified affine transform.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeWithAffine(SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/// Returns a new scale transform.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeScale(SPSize3DFloat scale)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/// Returns a new rotation transform.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeRotation(SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/// Returns a new translate transform.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeTranslation(SPVector3DFloat offset)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a projective transform with right-hand side perspective.
 
 @param fovY The field of view angle on the @p y axis.
 @param aspectRatio The aspect ratio.
 @param nearZ The near @p z .
 @param farZ The far @p z .
 @returns A projective transform with right-hand side perspective.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeWithRightHandPerspective(SPAngleFloat fovY,
                                                                                      float aspectRatio,
                                                                                      float nearZ,
                                                                                      float farZ)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a projective transform with right-hand side perspective.
 
 @param fovY The field of view angle on the @p y axis.
 @param aspectRatio The aspect ratio.
 @param nearZ The near @p z .
 @param farZ The far @p z .
 @param reverseZ A Boolean value that specifies whether the matrix should use reverse z.
 @returns A projective transform with right-hand side perspective.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeWithRightHandPerspective(SPAngleFloat fovY,
                                                                                      float aspectRatio,
                                                                                      float nearZ,
                                                                                      float farZ,
                                                                                      bool reverseZ)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a projective transform from tangents for each side of its frustum.
 
 @param leftTangent The left tangent.
 @param rightTangent The right tangent.
 @param topTangent The top tangent.
 @param bottomTangent bottom left tangent.
 @param nearZ The near @p z .
 @param farZ The far @p z .
 @param reverseZ A Boolean value that specifies whether the matrix should use reverse z.
 @returns A projective transform from tangents for each side of its frustum.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeFromTangents(float leftTangent,
                                                                          float rightTangent,
                                                                          float topTangent,
                                                                          float bottomTangent,
                                                                          float nearZ,
                                                                          float farZ,
                                                                          bool reverseZ)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a new scale, rotate, translate affine transform.
 
 @param scale The scale.
 @param rotation The rotation.
 @param translation The translation.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMake(SPSize3DFloat scale,
                                                              SPRotation3DFloat rotation,
                                                              SPVector3DFloat translation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a new shear affine transform.
 
 @param shearAxis The shear axis.
 @param shearFactor0 The first shear factor.
 @param shearFactor1 The second shear factor.
 @returns A new affine transform structure.
 @discussion
 When the shear axis is @p x , @p shearFactor0 is the @p y shear factor and @p shearFactor0 is the @p z shear factor.
 
 When the shear axis is @p y , @p shearFactor0 is the @p x  shear factor and @p shearFactor0 is the @p z shear factor.
 
 When the shear axis is @p z , @p shearFactor0 is the @p x  shear factor and @p shearFactor0 is the @p y shear factor.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeShear(SPAxis shearAxis,
                                                                   float shearFactor0,
                                                                   float shearFactor1)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Querying transform properties

/*!
 @abstract Returns a Boolean value that indicates whether the transform is affine.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is affine.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsAffine(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether a projective transform is a valid transform.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the projective transform is a valid transform.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsValid(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform only contains a translation.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform only contains a translation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsTranslation(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform is the identity transform.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is the identity transform.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsIdentity(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform is a 3DFloat projection.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is a 3DFloat projection.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIs3DFloatProjection(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform is affine and scales equally over all dimensions.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is affine and uniform over all dimensions.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsUniform(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns `true` if the transform is affine and scales equally over the specified dimensions.
 
 @discussion
 Passing  @p dimensionFlags of @p SPAxisX|SPAxisY|SPAxisZ returns the same result as @p SPProjectiveTransform3DFloatIsUniform .
 Passing a @p dimensionFlags  that specifies zero or one axis returns the same result as @p SPProjectiveTransform3DFloatIsRectilinear .
 
 @param transform The transform.
 @param dimensionFlags  A bitmask that specifies which dimensions the function queries. Use logical OR to combine axes .
 
 @returns @p true if the transform is affine, rectilinear, and the specified axes have equal scales.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsUniformOverDimensions(SPProjectiveTransform3DFloat transform,
                                                         SPAxis dimensionFlags)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform is affine and rectilinear.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is affine and rectilinear.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsRectilinear(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform's underlying matrix has an inverse.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform's underlying matrix has an inverse.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsInvertible(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Deriving new transforms

/*!
 @abstract Returns a new transform that's constructed by inverting an existing projective transform.
 
 @param transform The source transform.
 @returns A new transform that's constructed by inverting an existing projective transform.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatInverted(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/// Returns a projective transformation matrix constructed by concatenating two existing Projective transforms.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatConcatenation(SPProjectiveTransform3DFloat t1,
                                                                       SPProjectiveTransform3DFloat t2)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: Extracting component transforms

/*!
 @abstract Returns a projective transform's scale.
 
 @param transform The source transform.
 @returns A size structure that represents the transform's scale.
 @note This function computes the scale from the first three rows of the transform matrix and ignores the fourth row.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPProjectiveTransform3DFloatGetScale(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a projective transform's rotation.
 
 @param transform The source transform.
 @returns A rotation structure that represents the transform's rotation.
 @note This function computes the rotation from the first three rows of the transform matrix and ignores the fourth row.
 If the projective transform isn't an affine scale-rotate-translate transform, this function returns @p SPRotation3DFloatInvalid.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPProjectiveTransform3DFloatGetRotation(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a projective transform's translation.
 
 @param transform The source transform.
 @returns A size structure that represents the transform's translation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPProjectiveTransform3DFloatGetTranslation(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Sets the translation component on the specified transform.
 
 @param transform The transform.
 @param offset The translation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
void SPProjectiveTransform3DFloatSetTranslation(SPProjectiveTransform3DFloat *transform, SPVector3DFloat offset)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Transform equality

/*!
 @abstract Returns a Boolean value that indicates whether the two transform's matrices are equal within the Spatial default absolute tolerance.
 
 @param t1 The first transform.
 @param t2 The first transform.
 @returns A Boolean value that indicates whether the two transform's matrices are equal within the Spatial default absolute tolerance.
 @note The Spatial default tolerance is @p sqrt(__DBL_EPSILON__) .
 */
SPATIAL_INLINE
bool SPProjectiveTransform3DFloatAlmostEqualToTransform(SPProjectiveTransform3DFloat t1,
                                                        SPProjectiveTransform3DFloat t2)
SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the two transform's matrices are equal within the specified absolute tolerance.
 
 @param t1 The first transform.
 @param t2 The first transform.
 @returns A Boolean value that indicates whether the two transform's matrices are equal within the specified absolute tolerance.
 */
SPATIAL_INLINE
bool SPProjectiveTransform3DFloatAlmostEqualToTransform(SPProjectiveTransform3DFloat t1,
                                                        SPProjectiveTransform3DFloat t2,
                                                        float tolerance)
SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Applying transform

/*!
 @abstract Returns a projective transform that's constructed by concatenating an existing projective transform and a scale.
 
 @param transform The source transform.
 @param x The scale value along the @p width dimension.
 @param y The scale value along the @p height dimension.
 @param z The scale value along the @p depth dimension.
 @returns A transform that's scaled by the specified values.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatScaleBy(SPProjectiveTransform3DFloat transform,
                                                                 float x, float y, float z)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a projective transform that's constructed by concatenating an existing projective transform and a scale specified by a @p Size3DFloat structure.
 
 @param transform The source transform.
 @param scale The scale value.
 @returns A transform that's scaled by the specified value.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatScaleBySize(SPProjectiveTransform3DFloat transform, SPSize3DFloat scale)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a projective transform that's constructed by concatenating an existing projective transform and a uniform scale.
 
 @param transform The source transform.
 @param scale The scale value.
 @returns A transform that's uniformly scaled by the specified value.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatScaleUniform(SPProjectiveTransform3DFloat transform, float scale)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a projective transform that's constructed by concatenating an existing projective transform and a rotation.
 
 @param transform The source transform.
 @param rotation The rotation.
 @returns A transform that's rotated by the specified rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatRotate(SPProjectiveTransform3DFloat transform,
                                                                SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a projective transform that's constructed by concatenating an existing projective transform and a rotation specified by a quaternion.
 
 @param transform The source transform.
 @param quaternion The quaternion that defines the rotation.
 @returns A transform that's rotated by the specified quaternion.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatRotateByQuaternion(SPProjectiveTransform3DFloat transform,
                                                                            simd_quatf quaternion)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a projective transform that's constructed by concatenating an existing projective transform and a translation.
 
 @param transform The source transform.
 @param offset A vector that defines the translation.
 @returns A transform that's offset by the @p width, @p height, and @p depth of the size.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatTranslate(SPProjectiveTransform3DFloat transform,
                                                                   SPVector3DFloat offset)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a new shear transform.
 
 @discussion
 When the shear axis is @p x , @p shearFactor0 is the @p y shear factor and @p shearFactor0 is the @p z shear factor.
 
 When the shear axis is @p y , @p shearFactor0 is the @p x  shear factor and @p shearFactor0 is the @p z shear factor.
 
 When the shear axis is @p z , @p shearFactor0 is the @p x  shear factor and @p shearFactor0 is the @p y shear factor.
 
 If you pass a flip axis that's not @p x , @p y , or @p z , the function returns @p transform unmodified.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatShear(SPProjectiveTransform3DFloat transform,
                                                               SPAxis shearAxis,
                                                               float shearFactor0,
                                                               float shearFactor1)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a projective transform that's flipped along the specified axis.
 
 @param flipAxis The flip axis.
 @returns A new transform flipped along the specified axis.
 @note The transform must be affine, otherwise the function returns @p SPProjectiveTransform3DFloatInvalid .
 
 @discussion
 If you pass a shear axis that's not @p x , @p y , or @p z , the function returns @p transform unmodified.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatFlip(SPProjectiveTransform3DFloat transform,
                                                              SPAxis flipAxis)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: Header inline implementations

// MARK: - Creating a projective transform

SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.init(_:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeWith4x4Matrix(simd_float4x4 matrix) {
    SPProjectiveTransform3DFloat transform = { .matrix = matrix };
    
    return transform;
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.init(_:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeWithAffine(SPAffineTransform3DFloat transform) {
    
    simd_float4 col0 = simd_make_float4(transform.matrix.columns[0], 0);
    simd_float4 col1 = simd_make_float4(transform.matrix.columns[1], 0);
    simd_float4 col2 = simd_make_float4(transform.matrix.columns[2], 0);
    simd_float4 col3 = simd_make_float4(transform.matrix.columns[3], 1);
    
    simd_float4x4 matrix = simd_matrix(col0, col1, col2, col3);
    
    SPProjectiveTransform3DFloat projectiveTransform = { .matrix = matrix };
    
    return projectiveTransform;
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.init(scale:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeScale(SPSize3DFloat scale) {
    
    simd_float4x4 matrix = simd_diagonal_matrix((simd_float4){
        scale.width,
        scale.height,
        scale.depth,
        1
    });
    
    SPProjectiveTransform3DFloat projectiveTransform = { .matrix = matrix };
    
    return projectiveTransform;
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.init(rotation:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeRotation(SPRotation3DFloat rotation) {
    
    simd_quatf quaternion = SPRotation3DFloatGetQuaternion(rotation);
    
    simd_float4x4 matrix = simd_matrix4x4(quaternion);
    
    SPProjectiveTransform3DFloat projectiveTransform = { .matrix = matrix };
    
    return projectiveTransform;
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.init(translation:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeTranslation(SPVector3DFloat offset) {
    
    simd_float4x4 matrix = matrix_identity_float4x4;
    
    matrix.columns[3] = (simd_float4){
        offset.x,
        offset.y,
        offset.z,
        1
    };
    
    SPProjectiveTransform3DFloat projectiveTransform = { .matrix = matrix };
    
    return projectiveTransform;
}


SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMake(SPSize3DFloat scale,
                                                              SPRotation3DFloat rotation,
                                                              SPVector3DFloat translation) {
    
    SPProjectiveTransform3DFloat scaleTransform = SPProjectiveTransform3DFloatMakeScale(scale);
    SPProjectiveTransform3DFloat rotateTransfrom = SPProjectiveTransform3DFloatMakeRotation(rotation);
    SPProjectiveTransform3DFloat translateTransform = SPProjectiveTransform3DFloatMakeTranslation(translation);
    
    
    SPProjectiveTransform3DFloat t = SPProjectiveTransform3DFloatConcatenation(rotateTransfrom, scaleTransform);
    t = SPProjectiveTransform3DFloatConcatenation(translateTransform, t);
    
    return t;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeShear(SPAxis shearAxis,
                                                                   float shearFactor0,
                                                                   float shearFactor1) {
    
    SPAffineTransform3DFloat affine = SPAffineTransform3DFloatMakeShear(shearAxis,
                                                                        shearFactor0,
                                                                        shearFactor1);
    
    return SPProjectiveTransform3DFloatMakeWithAffine(affine);
    
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.init(fovY:aspectRatio:nearZ:farZ:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeWithRightHandPerspective(SPAngleFloat fovY,
                                                                                      float aspectRatio,
                                                                                      float nearZ,
                                                                                      float farZ) SPATIAL_OVERLOADABLE {
    
    return SPProjectiveTransform3DFloatMakeWithRightHandPerspective(fovY, aspectRatio, nearZ, farZ, false);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.init(fovY:aspectRatio:nearZ:farZ:reverseZ:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeWithRightHandPerspective(SPAngleFloat fovY,
                                                                                      float aspectRatio,
                                                                                      float nearZ,
                                                                                      float farZ,
                                                                                      bool reverseZ) SPATIAL_OVERLOADABLE {
    float ys = 1 / tan(fovY.radians * 0.5);
    float xs = ys / aspectRatio;
    float zs = farZ / (nearZ - farZ);
    
    simd_float4x4 m = (simd_float4x4) {
        (simd_float4) { xs, 0, 0, 0 },
        (simd_float4) { 0, ys, 0, 0 },
        (simd_float4) { 0, 0, zs, -1 },
        (simd_float4) { 0, 0, nearZ * zs, 0}
    };
    
    if (reverseZ) {
        if (isinf(farZ)) {
            m.columns[2].z = 0;
            m.columns[3].z = nearZ;
        } else {
            m.columns[2].z = -m.columns[2].z - 1;
            m.columns[3].z = -m.columns[3].z;
        }
    } else if (isinf(farZ)) {
        m.columns[2].z = -1;
        m.columns[3].z = -nearZ;
    }
    
    SPProjectiveTransform3DFloat transform = { .matrix = m };
    
    return transform;
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.init(leftTangent:rightTangent:topTangent:bottomTangent:nearZ:farZ:reverseZ:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeFromTangents(float leftTangent,
                                                                          float rightTangent,
                                                                          float topTangent,
                                                                          float bottomTangent,
                                                                          float nearZ,
                                                                          float farZ,
                                                                          bool reverseZ){
    
    leftTangent = -leftTangent * nearZ;
    rightTangent = rightTangent * nearZ;
    topTangent = topTangent * nearZ;
    bottomTangent = -bottomTangent * nearZ;
    
    simd_float4x4 matrix = (simd_float4x4) {
        (simd_float4) { 2 * nearZ / (rightTangent - leftTangent), 0, 0, 0 },
        (simd_float4) { 0, 2 * nearZ / (topTangent - bottomTangent), 0, 0 },
        (simd_float4) { (rightTangent + leftTangent) / (rightTangent - leftTangent),
            (topTangent + bottomTangent) / (topTangent - bottomTangent), farZ / (nearZ - farZ), -1 },
        (simd_float4) { 0, 0, (farZ * nearZ) / (nearZ - farZ), 0}
    };
    
    if (reverseZ) {
        if (isinf(farZ)) {
            
            matrix.columns[2].z = 0;
            
            matrix.columns[2].z = 0;
            matrix.columns[3].z = nearZ;
        } else {
            matrix.columns[2].z = -matrix.columns[2].z - 1;
            matrix.columns[3].z = -matrix.columns[3].z;
        }
    } else if (isinf(farZ)) {
        matrix.columns[2].z = -1;
        matrix.columns[3].z = -nearZ;
    }
    
    SPProjectiveTransform3DFloat transform = { .matrix = matrix };
    
    return transform;
}

// MARK: - Querying transform properties

SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.is3DFloatProjection(self:))
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIs3DFloatProjection(SPProjectiveTransform3DFloat transform) {
    
    if (!SPProjectiveTransform3DFloatIsAffine(transform)) {
        return 1;
    } else {
        return (transform.matrix.columns[0].z != 0 ||
                transform.matrix.columns[1].z != 0 ||
                transform.matrix.columns[2].z != 0);
    }
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsValid(SPProjectiveTransform3DFloat transform) {
    return (simd_all(_sp_simd_isfinite(transform.matrix.columns[0])) &&
            simd_all(_sp_simd_isfinite(transform.matrix.columns[1])) &&
            simd_all(_sp_simd_isfinite(transform.matrix.columns[2])) &&
            simd_all(_sp_simd_isfinite(transform.matrix.columns[3])));
}

SPATIAL_SWIFT_NAME(getter:ProjectiveTransform3DFloat.isAffine(self:))
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsAffine(SPProjectiveTransform3DFloat transform) {
    
    return (transform.matrix.columns[0].w == 0 &&
            transform.matrix.columns[1].w == 0 &&
            transform.matrix.columns[2].w == 0 &&
            transform.matrix.columns[3].w == 1);
}

SPATIAL_SWIFT_NAME(getter:ProjectiveTransform3DFloat.isIdentity(self:))
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsIdentity(SPProjectiveTransform3DFloat transform) {
    
    return (simd_equal(transform.matrix.columns[0], (simd_float4){1, 0, 0, 0}) &&
            simd_equal(transform.matrix.columns[1], (simd_float4){0, 1, 0, 0}) &&
            simd_equal(transform.matrix.columns[2], (simd_float4){0, 0, 1, 0}) &&
            simd_equal(transform.matrix.columns[3], (simd_float4){0, 0, 0, 1}));
    
}

SPATIAL_SWIFT_NAME(getter:ProjectiveTransform3DFloat.isTranslation(self:))
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsTranslation(SPProjectiveTransform3DFloat transform) {
    
    return (simd_equal(transform.matrix.columns[0], (simd_float4){1, 0, 0, 0}) &&
            simd_equal(transform.matrix.columns[1], (simd_float4){0, 1, 0, 0}) &&
            simd_equal(transform.matrix.columns[2], (simd_float4){0, 0, 1, 0}) &&
            transform.matrix.columns[3].w == 1);
}

SPATIAL_SWIFT_NAME(getter:ProjectiveTransform3DFloat.isRectilinear(self:))
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsRectilinear(SPProjectiveTransform3DFloat transform) {
    
    bool isAffine = SPProjectiveTransform3DFloatIsAffine(transform);
    
    if (isAffine) {
        SPAffineTransform3DFloat affine = SPAffineTransform3DFloatMakeWithTruncatedProjective(transform);
        return SPAffineTransform3DFloatIsRectilinear(affine);
    } else {
        return isAffine;
    }
}

SPATIAL_SWIFT_NAME(getter:ProjectiveTransform3DFloat.isUniform(self:))
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsUniform(SPProjectiveTransform3DFloat transform) {
    
    bool isAffine = SPProjectiveTransform3DFloatIsAffine(transform);
    
    if (isAffine) {
        SPAffineTransform3DFloat affine = SPAffineTransform3DFloatMakeWithTruncatedProjective(transform);
        return SPAffineTransform3DFloatIsUniform(affine);
    } else {
        return isAffine;
    }
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsUniformOverDimensions(SPProjectiveTransform3DFloat transform,
                                                         SPAxis dimensionFlags) {
    bool isAffine = SPProjectiveTransform3DFloatIsAffine(transform);
    
    if (isAffine) {
        SPAffineTransform3DFloat affine = SPAffineTransform3DFloatMakeWithTruncatedProjective(transform);
        return SPAffineTransform3DFloatIsUniformOverDimensions(affine, dimensionFlags);
    } else {
        return isAffine;
    }
}

SPATIAL_SWIFT_NAME(getter:ProjectiveTransform3DFloat.isInvertible(self:))
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DFloatIsInvertible(SPProjectiveTransform3DFloat transform) {
    
    return simd_determinant(transform.matrix) != 0;
}

// MARK: - Deriving new transforms

SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.concatenating(self:_:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatConcatenation(SPProjectiveTransform3DFloat t1,
                                                                       SPProjectiveTransform3DFloat t2) {
    
    simd_float4x4 conatenatedMatrix = t1.matrix;
    
    if (SPProjectiveTransform3DFloatIsAffine(t1) && SPProjectiveTransform3DFloatIsTranslation(t1) &&
        SPProjectiveTransform3DFloatIsAffine(t2) && SPProjectiveTransform3DFloatIsTranslation(t2)) {
        
        // Both transforms are affine translations only, return sum of translate columns:
        conatenatedMatrix.columns[3].xyz = t1.matrix.columns[3].xyz + t2.matrix.columns[3].xyz;
        
    } else if (SPProjectiveTransform3DFloatIsAffine(t1) &&
               simd_all(t1.matrix.columns[3].xyz == (simd_float3){0, 0, 0}) &&
               SPProjectiveTransform3DFloatIsAffine(t2) &&
               simd_all(t2.matrix.columns[3].xyz == (simd_float3){0, 0, 0})) {
        
        // Both transforms are affine without translation, return 3x3 * 3x3:
        simd_float3x3 t1_3x3 = (simd_float3x3) {
            t1.matrix.columns[0].xyz,
            t1.matrix.columns[1].xyz,
            t1.matrix.columns[2].xyz } ;
        simd_float3x3 t2_3x3 = (simd_float3x3) {
            t2.matrix.columns[0].xyz,
            t2.matrix.columns[1].xyz,
            t2.matrix.columns[2].xyz } ;
        
        t1_3x3 = simd_mul(t1_3x3, t2_3x3);
        
        conatenatedMatrix = (simd_float4x4) {
            simd_make_float4(t1_3x3.columns[0], 0 ),
            simd_make_float4(t1_3x3.columns[1], 0 ),
            simd_make_float4(t1_3x3.columns[2], 0 ),
            (simd_float4) { 0, 0, 0, 1}
        };
    } else {
        
        // Return 4x4 * 4x4:
        conatenatedMatrix = simd_mul(t1.matrix,
                                     t2.matrix);
    }
    
    SPProjectiveTransform3DFloat transform = { .matrix = conatenatedMatrix };
    
    return transform;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatInverted(SPProjectiveTransform3DFloat transform) {
    
    if (!SPProjectiveTransform3DFloatIsInvertible(transform)) {
        return SPProjectiveTransform3DFloatInvalid;
    }
    
    simd_float4x4 inverse = simd_inverse(transform.matrix);
    
    return (SPProjectiveTransform3DFloat){ .matrix = inverse };
}

// MARK: Extracting component transforms

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPProjectiveTransform3DFloatGetScale(SPProjectiveTransform3DFloat transform) {
    
    simd_float4x4 p = transform.matrix;
    
    simd_float3 column0 = p.columns[0].xyz;
    simd_float3 column1 = p.columns[1].xyz;
    simd_float3 column2 = p.columns[2].xyz;
    simd_float3 column3 = p.columns[3].xyz;
    
    simd_float4x3 m = simd_matrix(column0,
                                  column1,
                                  column2,
                                  column3);
    
    SPAffineTransform3DFloat affine = SPAffineTransform3DFloatMakeWith4x3Matrix(m);
    
    return SPAffineTransform3DFloatGetScale(affine);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPProjectiveTransform3DFloatGetRotation(SPProjectiveTransform3DFloat transform) {
    
    simd_float4x4 p = transform.matrix;
    
    simd_float3 column0 = p.columns[0].xyz;
    simd_float3 column1 = p.columns[1].xyz;
    simd_float3 column2 = p.columns[2].xyz;
    simd_float3 column3 = p.columns[3].xyz;
    
    simd_float4x3 m = simd_matrix(column0,
                                  column1,
                                  column2,
                                  column3);
    
    SPAffineTransform3DFloat affine = SPAffineTransform3DFloatMakeWith4x3Matrix(m);
    return SPAffineTransform3DFloatGetRotation(affine);
    
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPProjectiveTransform3DFloatGetTranslation(SPProjectiveTransform3DFloat transform) {
    
    simd_float3 translation = transform.matrix.columns[3].xyz;
    
    return SPVector3DFloatMakeWithVector(translation);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
void SPProjectiveTransform3DFloatSetTranslation(SPProjectiveTransform3DFloat *transform, SPVector3DFloat offset) {
    
    transform->matrix.columns[3].xyz = offset.vector;
}

// MARK: - Transform equality

bool SPProjectiveTransform3DFloatAlmostEqualToTransform(SPProjectiveTransform3DFloat t1,
                                                        SPProjectiveTransform3DFloat t2) SPATIAL_OVERLOADABLE {
    
    return simd_almost_equal_elements(t1.matrix, t2.matrix, SPDefaultToleranceFloat);
}

bool SPProjectiveTransform3DFloatAlmostEqualToTransform(SPProjectiveTransform3DFloat t1,
                                                        SPProjectiveTransform3DFloat t2,
                                                        float tolerance) SPATIAL_OVERLOADABLE {
    
    return simd_almost_equal_elements(t1.matrix, t2.matrix, tolerance);
}

// MARK: - Applying transform

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatScaleBy(SPProjectiveTransform3DFloat transform,
                                                                 float x, float y, float z) {
    
    SPSize3DFloat scale = SPSize3DFloatMake(x, y, z);
    SPProjectiveTransform3DFloat scaleTransform = SPProjectiveTransform3DFloatMakeScale(scale);
    
    return SPProjectiveTransform3DFloatConcatenation(transform, scaleTransform);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.scaled(self:by:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatScaleBySize(SPProjectiveTransform3DFloat transform,
                                                                     SPSize3DFloat scale) {
    SPProjectiveTransform3DFloat scaleTransform = SPProjectiveTransform3DFloatMakeScale(scale);
    
    return SPProjectiveTransform3DFloatConcatenation(transform, scaleTransform);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.uniformlyScaled(self:by:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatScaleUniform(SPProjectiveTransform3DFloat transform,
                                                                      float scale) {
    SPSize3DFloat scaleSize = SPSize3DFloatMake(scale, scale, scale);
    SPProjectiveTransform3DFloat scaleTransform = SPProjectiveTransform3DFloatMakeScale(scaleSize);
    
    return SPProjectiveTransform3DFloatConcatenation(transform, scaleTransform);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatRotate(SPProjectiveTransform3DFloat transform,
                                                                SPRotation3DFloat rotation) {
    SPProjectiveTransform3DFloat rotationTransform = SPProjectiveTransform3DFloatMakeRotation(rotation);
    
    return SPProjectiveTransform3DFloatConcatenation(transform, rotationTransform);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatRotateByQuaternion(SPProjectiveTransform3DFloat transform,
                                                                            simd_quatf quaternion) {
    SPRotation3DFloat rotation = SPRotation3DFloatMakeWithQuaternion(quaternion);
    SPProjectiveTransform3DFloat rotationTransform = SPProjectiveTransform3DFloatMakeRotation(rotation);
    
    return SPProjectiveTransform3DFloatConcatenation(transform, rotationTransform);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.translated(self:by:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatTranslate(SPProjectiveTransform3DFloat transform,
                                                                   SPVector3DFloat offset) {
    SPProjectiveTransform3DFloat translate = SPProjectiveTransform3DFloatMakeTranslation(offset);
    
    return SPProjectiveTransform3DFloatConcatenation(transform, translate);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatShear(SPProjectiveTransform3DFloat transform,
                                                               SPAxis shearAxis,
                                                               float shearFactor0,
                                                               float shearFactor1) {
    
    SPProjectiveTransform3DFloat shearTransform = SPProjectiveTransform3DFloatMakeShear(shearAxis,
                                                                                        shearFactor0,
                                                                                        shearFactor1);
    return SPProjectiveTransform3DFloatConcatenation(transform, shearTransform);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatFlip(SPProjectiveTransform3DFloat transform,
                                                              SPAxis flipAxis) {
    if (!SPProjectiveTransform3DFloatIsAffine(transform)) {
        return SPProjectiveTransform3DFloatInvalid;
    }
    
    SPAffineTransform3DFloat affine = SPAffineTransform3DFloatMakeWithTruncatedProjective(transform);
    affine = SPAffineTransform3DFloatFlip(affine, flipAxis);
    
    return SPProjectiveTransform3DFloatMakeWithAffine(affine);
}

// MARK: - make from pose

/*!
 @abstract Returns a new projective transform structure from the specified scaled pose structure.
 
 @param pose The source scaled pose.
 @returns A new projective transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeWithScaledPose(SPScaledPose3DFloat pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeWithScaledPose(SPScaledPose3DFloat pose) {
    
    return SPProjectiveTransform3DFloatMake(SPSize3DFloatMake(pose.scale, pose.scale, pose.scale),
                                            pose.rotation,
                                            SPVector3DFloatMakeWithVector(pose.position.vector));
}

/*!
 @abstract Returns a new projective transform structure from the specified pose structure.
 
 @param pose The source pose.
 @returns A new projective transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeWithPose(SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatMakeWithPose(SPPose3DFloat pose) {
    
    SPVector3DFloat v = SPVector3DFloatMakeWithVector(pose.position.vector);
    
    return SPProjectiveTransform3DFloatMake(SPSize3DFloatMake(1, 1, 1),
                                            pose.rotation,
                                            v);
    
}

#endif /* Spatial_SPProjectiveTransform3DFloat_h */
