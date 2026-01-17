#ifndef Spatial_SPAffineTransform3DFloat_h
#define Spatial_SPAffineTransform3DFloat_h

#include <Spatial/StructuresFloat.h>
#include <Spatial/SPRotation3DFloat.h>

// MARK: - SINGLE-PRECISION Public API

// MARK: - Creating an affine transform

/*!
 @abstract Returns a new affine transform structure from the specified 4 x 3 matrix.
 
 @param matrix The source matrix.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeWith4x3Matrix(simd_float4x3 matrix)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a new affine transform structure from the specified 4 x 4 matrix truncated to a  4 x 3 matrix.
 
 @param matrix The source matrix.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeWithTruncated4x4Matrix(simd_float4x4 matrix)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));;

/*!
 @abstract Returns a new affine transform structure from the first three rows of the specified projective transform.
 
 @param transform The source transform.
 @returns A new affine transform structure.
 @note This function is similar to @p SPAffineTransform3DFloatMakeWithProjective, but it ignores the last
 row of the matrix.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeWithTruncatedProjective(SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a new scale affine transform.
 
 @param scale The scale.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeScale(SPSize3DFloat scale)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a new rotation affine transform.
 
 @param rotation The rotation.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeRotation(SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a new translation affine transform.
 
 @param offset The translation.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeTranslation(SPVector3DFloat offset)
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
SPAffineTransform3DFloat SPAffineTransform3DFloatMake(SPSize3DFloat scale,
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
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeShear(SPAxis shearAxis,
                                                           float shearFactor0,
                                                           float shearFactor1)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Querying transform properties

/*!
 @abstract Returns the first three columns of an affine transform's underlying matrix.
 
 @param transform The source transform.
 @returns A 3 x 3 matrix that's constructed from the first three columns of an affine transform's underlying matrix.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_float3x3 SPAffineTransform3DFloatGet3x3Matrix(SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a 4 x 4 matrix constructed from the affine transform's underlying matrix.
 
 @param transform The source transform.
 @returns A 4 x 4 matrix that's constructed from the affine transform's underlying 4 x 3 matrix with an
 additional row that contains the values @p [0,0,0,1] .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_float4x4 SPAffineTransform3DFloatGet4x4Matrix(SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform's underlying matrix has an inverse.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform's underlying matrix has an inverse.
 */
SPATIAL_INLINE bool SPAffineTransform3DFloatIsInvertible(SPAffineTransform3DFloat transform)
SPATIAL_OVERLOADABLE
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether an affine transform is a valid transform.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the affine transform is a valid transform.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DFloatIsValid(SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform only contains a translation.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform only contains a translation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DFloatIsTranslation(SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform is the identity transform.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is the identity transform.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DFloatIsIdentity(SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform scales equally over all dimensions.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is uniform over all dimensions.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DFloatIsUniform(SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns `true` if the transform scales equally over the specified dimensions.
 
 @discussion
 Passing @p dimensionFlags of @p SPAxisX|SPAxisY|SPAxisZ returns the same result as @p SPAffineTransform3DFloatIsUniform .
 Passing a @p dimensionFlags  that specifies zero or one axis returns the same result as @p SPAffineTransform3DFloatIsRectilinear .
 
 @param transform The transform.
 @param dimensionFlags  A bitmask that specifies which dimensions the function queries. Use logical OR to combine axes .
 
 @returns @p true if the transform is rectilinear and the specified axes have equal scales.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DFloatIsUniformOverDimensions(SPAffineTransform3DFloat transform,
                                                     SPAxis dimensionFlags)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform is rectilinear.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is rectilinear.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DFloatIsRectilinear(SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Deriving new transforms

/*!
 @abstract Returns a new transform that's constructed by inverting an existing affine transform.
 
 @param transform The source transform.
 @returns A new transform that's constructed by inverting an existing affine transform.
 @note The source transform must be invertible, call @p SPAffineTransform3DFloatIsInvertible to test
 whether this is the case. If the source transform isn't invertible, the function returns @p SPAffineTransform3DFloatInvalid .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatInverted(SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns an affine transformation matrix that's constructed by concatenating two existing affine transforms.
 
 @param t1 The first transform.
 @param t2 The second transform.
 @returns An affine transformation matrix that's constructed by concatenating two existing affine transforms.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatConcatenation(SPAffineTransform3DFloat t1,
                                                               SPAffineTransform3DFloat t2)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: Extracting component transforms

/*!
 @abstract Returns an affine transform's scale.
 
 @param transform The source transform.
 @returns A size structure that represents the transform's scale.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPAffineTransform3DFloatGetScale(SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns an affine transform's rotation.
 
 @param transform The source transform.
 @returns A rotation structure that represents the transform's rotation.
 @note
 This function can't extract rotation from a non-scale-rotate-translate affine transform. In that case, the function
 returns @p SPRotation3DFloatInvalid.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPAffineTransform3DFloatGetRotation(SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns an affine transform's translation.
 
 @param transform The source transform.
 @returns A size structure that represents the transform's translation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPAffineTransform3DFloatGetTranslation(SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Sets the translation component on the specified transform.
 
 @param transform The transform.
 @param offset The translation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
void SPAffineTransform3DFloatSetTranslation(SPAffineTransform3DFloat *transform, SPVector3DFloat offset)
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
bool SPAffineTransform3DFloatAlmostEqualToTransform(SPAffineTransform3DFloat t1,
                                                    SPAffineTransform3DFloat t2)
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
bool SPAffineTransform3DFloatAlmostEqualToTransform(SPAffineTransform3DFloat t1,
                                                    SPAffineTransform3DFloat t2,
                                                    float tolerance)
SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Applying transform

/*!
 @abstract Returns an affine transform that's constructed by concatenating an existing affine transform and a scale.
 
 @param transform The source transform.
 @param x The scale value along the @p width dimension.
 @param y The scale value along the @p height dimension.
 @param z The scale value along the @p depth dimension.
 @returns A transform that's scaled by the specified values.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatScaleBy(SPAffineTransform3DFloat transform,
                                                         float x, float y, float z)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns an affine transform that's constructed by concatenating an existing affine transform and a scale specified by an @p SPSize3DFloat structure.
 
 @param transform The source transform.
 @param scale The scale value.
 @returns A transform that's scaled by the specified value.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatScaleBySize(SPAffineTransform3DFloat transform,
                                                             SPSize3DFloat scale)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns an affine transform that's constructed by concatenating an existing affine transform and a uniform scale.
 
 @param transform The source transform.
 @param scale The scale value.
 @returns A transform that's uniformly scaled by the specified value.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatScaleUniform(SPAffineTransform3DFloat transform,
                                                              float scale)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns an affine transform that's constructed by concatenating an existing affine transform and a rotation.
 
 @param transform The source transform.
 @param rotation The rotation.
 @returns A transform that's rotated by the specified rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatRotate(SPAffineTransform3DFloat transform,
                                                        SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns an affine transform that's constructed by concatenating an existing affine transform and a rotation specified by a quaternion.
 
 @param transform The source transform.
 @param quaternion The quaternion that defines the rotation.
 @returns A transform that's rotated by the specified quaternion.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatRotateByQuaternion(SPAffineTransform3DFloat transform,
                                                                    simd_quatf quaternion)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns an affine transform that's constructed by concatenating an existing affine transform and a translation.
 
 @param transform The source transform.
 @param offset A vector that defines the translation.
 @returns A transform that's offset by the @p x, @p y, and @p z of the vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatTranslate(SPAffineTransform3DFloat transform,
                                                           SPVector3DFloat offset)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns an affine transform that's flipped along the specified axis.
 
 @discussion
 If you pass a flip axis that's not @p x , @p y , or @p z , the function returns @p transform unmodified.
 
 @param flipAxis The flip axis.
 @returns A new transform flipped along the specified axis.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatFlip(SPAffineTransform3DFloat transform,
                                                      SPAxis flipAxis)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns an affine transform that's sheared over an axis by shear factors for the other two axes.
 
 @param transform The source transform.
 @param shearAxis The shear axis.
 @param shearFactor0 The first shear factor.
 @param shearFactor1 The second shear factor.
 @returns The transformed transform.
 @discussion
 When the shear axis is @p x , @p shearFactor0 is the @p y shear factor and @p shearFactor0 is the @p z shear factor.
 
 When the shear axis is @p y , @p shearFactor0 is the @p x  shear factor and @p shearFactor0 is the @p z shear factor.
 
 When the shear axis is @p z , @p shearFactor0 is the @p x  shear factor and @p shearFactor0 is the @p y shear factor.
 
 If you pass a shear axis that's not @p x , @p y , or @p z , the function returns @p transform unmodified.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatShear(SPAffineTransform3DFloat transform,
                                                       SPAxis shearAxis,
                                                       float shearFactor0,
                                                       float shearFactor1)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: Header inline implementations

// MARK: - Creating an affine transform

SPATIAL_SWIFT_NAME(AffineTransform3DFloat.init(_:))
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeWith4x3Matrix(simd_float4x3 matrix) {
    SPAffineTransform3DFloat transform = { .matrix = matrix };
    
    return transform;
}

SPATIAL_SWIFT_NAME(AffineTransform3DFloat.init(truncating:))
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeWithTruncatedProjective(SPProjectiveTransform3DFloat transform) {
    simd_float3 column0 = transform.matrix.columns[0].xyz;
    simd_float3 column1 = transform.matrix.columns[1].xyz;
    simd_float3 column2 = transform.matrix.columns[2].xyz;
    simd_float3 column3 = transform.matrix.columns[3].xyz;
    
    SPAffineTransform3DFloat affine = { .matrix = simd_matrix(column0,
                                                              column1,
                                                              column2,
                                                              column3) };
    
    return affine;
}

SPATIAL_SWIFT_NAME(AffineTransform3DFloat.init(truncating:))
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeWithTruncated4x4Matrix(simd_float4x4 matrix) {
    
    simd_float3 column0 = matrix.columns[0].xyz;
    simd_float3 column1 = matrix.columns[1].xyz;
    simd_float3 column2 = matrix.columns[2].xyz;
    simd_float3 column3 = matrix.columns[3].xyz;
    
    SPAffineTransform3DFloat affine = { .matrix = simd_matrix(column0,
                                                              column1,
                                                              column2,
                                                              column3) };
    
    return affine;
}

SPATIAL_SWIFT_NAME(AffineTransform3DFloat.init(scale:))
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeScale(SPSize3DFloat scale) {
    
    simd_float3 column0 = {scale.width, 0, 0};
    simd_float3 column1 = {0, scale.height, 0};
    simd_float3 column2 = {0, 0, scale.depth};
    simd_float3 column3 = {0, 0, 0};
    
    simd_float4x3 matrix = simd_matrix(column0, column1, column2, column3);
    
    SPAffineTransform3DFloat transform = { .matrix = matrix };
    
    return transform;
}

SPATIAL_SWIFT_NAME(AffineTransform3DFloat.init(rotation:))
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeRotation(SPRotation3DFloat rotation) {
    
    simd_quatf quaternion = SPRotation3DFloatGetQuaternion(rotation);
    
    simd_float3x3 quaternionMatrix = simd_matrix3x3(quaternion);
    
    simd_float4x3 matrix = simd_matrix(quaternionMatrix.columns[0],
                                       quaternionMatrix.columns[1],
                                       quaternionMatrix.columns[2],
                                       simd_make_float3(0, 0, 0));
    
    SPAffineTransform3DFloat transform = { .matrix = matrix };
    
    return transform;
}

SPATIAL_SWIFT_NAME(AffineTransform3DFloat.init(translation:))
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeTranslation(SPVector3DFloat offset) {
    
    simd_float3 column0 = {1, 0, 0};
    simd_float3 column1 = {0, 1, 0};
    simd_float3 column2 = {0, 0, 1};
    simd_float3 column3 = {offset.x, offset.y, offset.z};
    
    simd_float4x3 matrix = simd_matrix(column0, column1, column2, column3);
    
    SPAffineTransform3DFloat transform = { .matrix = matrix };
    
    return transform;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMake(SPSize3DFloat scale,
                                                      SPRotation3DFloat rotation,
                                                      SPVector3DFloat translation) {
    
    SPAffineTransform3DFloat scaleTransform = SPAffineTransform3DFloatMakeScale(scale);
    SPAffineTransform3DFloat rotateTransfrom = SPAffineTransform3DFloatMakeRotation(rotation);
    SPAffineTransform3DFloat translateTransform = SPAffineTransform3DFloatMakeTranslation(translation);
    
    
    SPAffineTransform3DFloat t = SPAffineTransform3DFloatConcatenation(rotateTransfrom, scaleTransform);
    t = SPAffineTransform3DFloatConcatenation(translateTransform, t);
    
    return t;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeShear(SPAxis shearAxis,
                                                           float shearFactor0,
                                                           float shearFactor1) {
    
    SPAffineTransform3DFloat transform = SPAffineTransform3DFloatIdentity;
    
    transform = SPAffineTransform3DFloatShear(transform,
                                              shearAxis,
                                              shearFactor0,
                                              shearFactor1);
    
    return transform;
}
// MARK: - Querying transform properties

SPATIAL_SWIFT_NAME(getter:AffineTransform3DFloat.matrix3x3(self:))
SPATIAL_OVERLOADABLE
simd_float3x3 SPAffineTransform3DFloatGet3x3Matrix(SPAffineTransform3DFloat transform) {
    
    return simd_matrix(transform.matrix.columns[0],
                       transform.matrix.columns[1],
                       transform.matrix.columns[2]);
}

SPATIAL_SWIFT_NAME(getter:AffineTransform3DFloat.matrix4x4(self:))
SPATIAL_OVERLOADABLE
simd_float4x4 SPAffineTransform3DFloatGet4x4Matrix(SPAffineTransform3DFloat transform) {
    
    simd_float4 col0 = simd_make_float4(transform.matrix.columns[0].xyz, 0);
    simd_float4 col1 = simd_make_float4(transform.matrix.columns[1].xyz, 0);
    simd_float4 col2 = simd_make_float4(transform.matrix.columns[2].xyz, 0);
    simd_float4 col3 = simd_make_float4(transform.matrix.columns[3].xyz, 1);
    
    return simd_matrix(col0, col1, col2, col3);
}

SPATIAL_SWIFT_NAME(getter:AffineTransform3DFloat.isInvertible(self:))
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DFloatIsInvertible(SPAffineTransform3DFloat transform) {
    simd_float3x3 matrix3x3 = (simd_float3x3){
        transform.matrix.columns[0],
        transform.matrix.columns[1],
        transform.matrix.columns[2]
    };
    return simd_determinant(matrix3x3) != 0;
}

SPATIAL_SWIFT_NAME(getter:AffineTransform3DFloat.isTranslation(self:))
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DFloatIsTranslation(SPAffineTransform3DFloat transform) {
    
    simd_float3x3 matrix3x3 = SPAffineTransform3DFloatGet3x3Matrix(transform);
    
    return  simd_equal(matrix_identity_float3x3,
                       matrix3x3);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DFloatIsValid(SPAffineTransform3DFloat transform) {
    return (simd_all(_sp_simd_isfinite(transform.matrix.columns[0])) &&
            simd_all(_sp_simd_isfinite(transform.matrix.columns[1])) &&
            simd_all(_sp_simd_isfinite(transform.matrix.columns[2])) &&
            simd_all(_sp_simd_isfinite(transform.matrix.columns[3])));
}

SPATIAL_SWIFT_NAME(getter:AffineTransform3DFloat.isIdentity(self:))
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DFloatIsIdentity(SPAffineTransform3DFloat transform){
    
    return simd_almost_equal_elements(transform.matrix,
                                      SPAffineTransform3DFloatIdentity.matrix,
                                      SPDefaultToleranceFloat);
}

SPATIAL_SWIFT_NAME(getter:AffineTransform3DFloat.isUniform(self:))
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DFloatIsUniform(SPAffineTransform3DFloat transform) {
    
    SPSize3DFloat scale = SPAffineTransform3DFloatGetScale(transform);
    bool isRectilinear = SPAffineTransform3DFloatIsRectilinear(transform);
    
    return isRectilinear && scale.width == scale.height && scale.height == scale.depth;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DFloatIsUniformOverDimensions(SPAffineTransform3DFloat transform,
                                                     SPAxis dimensionFlags) {
    
    if (dimensionFlags == 0b111) {
        return SPAffineTransform3DFloatIsUniform(transform);
    }
    
    SPSize3DFloat scale = SPAffineTransform3DFloatGetScale(transform);
    bool isUniform = SPAffineTransform3DFloatIsRectilinear(transform);
    
    if (dimensionFlags == 0b011) {
        isUniform = isUniform && (scale.width == scale.height);
    } else if (dimensionFlags == 0b101) {
        isUniform = isUniform && (scale.width == scale.depth);
    } else if (dimensionFlags == 0b110) {
        isUniform = isUniform && (scale.height == scale.depth);
    }
    
    return isUniform;
}

SPATIAL_SWIFT_NAME(getter:AffineTransform3DFloat.isRectilinear(self:))
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DFloatIsRectilinear(SPAffineTransform3DFloat transform) {
    
    simd_float3x3 matrix3x3 = SPAffineTransform3DFloatGet3x3Matrix(transform);
    
    float angle = fabs(remainder(simd_angle(simd_quaternion(matrix3x3)), (float)M_PI / 2));
    
    return angle < SPDefaultToleranceFloat;
}

// MARK: - Deriving new transforms

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatInverted(SPAffineTransform3DFloat transform) {
    
    simd_float3x3 matrix3x3 = SPAffineTransform3DFloatGet3x3Matrix(transform);
    
    if (!SPAffineTransform3DFloatIsInvertible(transform)) {
        return SPAffineTransform3DFloatInvalid;
    }
    
    simd_float3x3 m_inv = matrix_invert(matrix3x3);
    
    simd_float3 t = simd_mul(m_inv, transform.matrix.columns[3]);
    t = t * simd_make_float3(-1, -1, -1);
    
    simd_float4x3 matrix = simd_matrix(m_inv.columns[0],
                                       m_inv.columns[1],
                                       m_inv.columns[2],
                                       t);
    
    SPAffineTransform3DFloat invertedTransform = { .matrix = matrix };
    
    return invertedTransform;
}

SPATIAL_SWIFT_NAME(AffineTransform3DFloat.concatenating(self:_:))
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatConcatenation(SPAffineTransform3DFloat t1, SPAffineTransform3DFloat t2) {
    
    if (SPAffineTransform3DFloatIsTranslation(t1) && SPAffineTransform3DFloatIsTranslation(t2)) {
        
        // Both transforms are translations only, return sum of translate columns:
        t1.matrix.columns[3] = t1.matrix.columns[3] + t2.matrix.columns[3];
        return t1;
        
    } else if (simd_all(t1.matrix.columns[3] == (simd_float3){0, 0, 0}) &&
               simd_all(t2.matrix.columns[3] == (simd_float3){0, 0, 0})) {
        
        // Neither transform contains a translation, return 3x3 * 3x3:
        simd_float3x3 t1_3x3 = SPAffineTransform3DFloatGet3x3Matrix(t1);
        simd_float3x3 t2_3x3 = SPAffineTransform3DFloatGet3x3Matrix(t2);
        
        simd_float3x3 product = simd_mul(t1_3x3, t2_3x3);
        
        simd_float4x3 matrix = simd_matrix(product.columns[0],
                                           product.columns[1],
                                           product.columns[2],
                                           t1.matrix.columns[3]);
        
        SPAffineTransform3DFloat transform = { .matrix = matrix };
        
        return transform;
        
    } else {
        
        // Return 4x4 * 4x4:
        simd_float4x4 t1_4x4 = SPAffineTransform3DFloatGet4x4Matrix(t1);
        simd_float4x4 t2_4x4 = SPAffineTransform3DFloatGet4x4Matrix(t2);
        
        simd_float4x4 product = simd_mul(t1_4x4, t2_4x4);
        
        simd_float4x3 matrix = simd_matrix(product.columns[0].xyz,
                                           product.columns[1].xyz,
                                           product.columns[2].xyz,
                                           product.columns[3].xyz);
        
        SPAffineTransform3DFloat transform = { .matrix = matrix };
        
        return transform;
    }
}

// MARK: Extracting component transforms

SPATIAL_SWIFT_NAME(getter:AffineTransform3DFloat.scale(self:))
SPATIAL_OVERLOADABLE
SPSize3DFloat SPAffineTransform3DFloatGetScale(SPAffineTransform3DFloat transform) {
    
    simd_float3x3 matrix3x3 = SPAffineTransform3DFloatGet3x3Matrix(transform);
    float sign = simd_determinant(matrix3x3) >= 0 ? 1.0 : -1.0;
    simd_float3 scale = {
        simd_length(matrix3x3.columns[0]),
        simd_length(matrix3x3.columns[1]),
        simd_length(matrix3x3.columns[2])
    };
    
    simd_float3 signedScale = scale * sign;
    
    return SPSize3DFloatMakeWithVector(signedScale);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPAffineTransform3DFloatGetRotation(SPAffineTransform3DFloat transform) {
    
    simd_float3x3 matrix3x3 = SPAffineTransform3DFloatGet3x3Matrix(transform);
    
    SPSize3DFloat scaleSize = SPAffineTransform3DFloatGetScale(transform);
    simd_float3 scale = (simd_float3){ scaleSize.width, scaleSize.height, scaleSize.depth };
    
    matrix3x3.columns[0] /= scale.x;
    matrix3x3.columns[1] /= scale.y;
    matrix3x3.columns[2] /= scale.z;
    
    // orthogonalize matrix...
    
    matrix3x3.columns[1] = matrix3x3.columns[1] - simd_project(matrix3x3.columns[1], matrix3x3.columns[0]);
    matrix3x3.columns[2] = matrix3x3.columns[2] - simd_project(matrix3x3.columns[2], matrix3x3.columns[0]) - simd_project(matrix3x3.columns[2], matrix3x3.columns[1]);
    
    matrix3x3.columns[0] = simd_normalize(matrix3x3.columns[0]);
    matrix3x3.columns[1] = simd_normalize(matrix3x3.columns[1]);
    matrix3x3.columns[2] = simd_normalize(matrix3x3.columns[2]);
    
    simd_quatf quaternion = simd_quaternion(matrix3x3);
    
    if (simd_any(_sp_simd_isnan(quaternion.vector))) {
        // Cannot extract rotation from non-SRT compliant `SPAffineTransform3DFloat`
        return SPRotation3DFloatInvalid;
    }
    
    return SPRotation3DFloatMakeWithQuaternion(simd_normalize(quaternion));
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPAffineTransform3DFloatGetTranslation(SPAffineTransform3DFloat transform) {
    
    simd_float3 translation = transform.matrix.columns[3];
    
    return SPVector3DFloatMakeWithVector(translation);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
void SPAffineTransform3DFloatSetTranslation(SPAffineTransform3DFloat *transform, SPVector3DFloat offset) {
    
    transform->matrix.columns[3] = offset.vector;
}

// MARK: - Transform equality

bool SPAffineTransform3DFloatAlmostEqualToTransform(SPAffineTransform3DFloat t1,
                                                    SPAffineTransform3DFloat t2) SPATIAL_OVERLOADABLE {
    
    return simd_almost_equal_elements(t1.matrix, t2.matrix, SPDefaultToleranceFloat);
}

bool SPAffineTransform3DFloatAlmostEqualToTransform(SPAffineTransform3DFloat t1,
                                                    SPAffineTransform3DFloat t2,
                                                    float tolerance) SPATIAL_OVERLOADABLE {
    
    return simd_almost_equal_elements(t1.matrix, t2.matrix, tolerance);
}

// MARK: - Applying transform

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatScaleBy(SPAffineTransform3DFloat transform,
                                                         float x, float y, float z) {
    
    SPSize3DFloat scale = SPSize3DFloatMake(x, y, z);
    SPAffineTransform3DFloat scaleTransform = SPAffineTransform3DFloatMakeScale(scale);
    
    return SPAffineTransform3DFloatConcatenation(transform, scaleTransform);
}

SPATIAL_SWIFT_NAME(AffineTransform3DFloat.scaled(self:by:))
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatScaleBySize(SPAffineTransform3DFloat transform,
                                                             SPSize3DFloat scale) {
    SPAffineTransform3DFloat scaleTransform = SPAffineTransform3DFloatMakeScale(scale);
    
    return SPAffineTransform3DFloatConcatenation(transform, scaleTransform);
}

SPATIAL_SWIFT_NAME(AffineTransform3DFloat.uniformlyScaled(self:by:))
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatScaleUniform(SPAffineTransform3DFloat transform,
                                                              float scale) {
    
    SPSize3DFloat scaleSize = SPSize3DFloatMake(scale, scale, scale);
    SPAffineTransform3DFloat scaleTransform = SPAffineTransform3DFloatMakeScale(scaleSize);
    
    return SPAffineTransform3DFloatConcatenation(transform, scaleTransform);
}

SPATIAL_SWIFT_NAME(AffineTransform3DFloat.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatRotate(SPAffineTransform3DFloat transform,
                                                        SPRotation3DFloat rotation) {
    
    SPAffineTransform3DFloat rotationTransform = SPAffineTransform3DFloatMakeRotation(rotation);
    
    return SPAffineTransform3DFloatConcatenation(transform, rotationTransform);
}

SPATIAL_SWIFT_NAME(AffineTransform3DFloat.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatRotateByQuaternion(SPAffineTransform3DFloat transform,
                                                                    simd_quatf quaternion) {
    
    SPRotation3DFloat rotation = SPRotation3DFloatMakeWithQuaternion(quaternion);
    SPAffineTransform3DFloat rotationTransform = SPAffineTransform3DFloatMakeRotation(rotation);
    
    return SPAffineTransform3DFloatConcatenation(transform, rotationTransform);
}

SPATIAL_SWIFT_NAME(AffineTransform3DFloat.translated(self:by:))
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatTranslate(SPAffineTransform3DFloat transform,
                                                           SPVector3DFloat offset) {
    
    SPAffineTransform3DFloat translate = SPAffineTransform3DFloatMakeTranslation(offset);
    
    return SPAffineTransform3DFloatConcatenation(transform, translate);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatFlip(SPAffineTransform3DFloat transform,
                                                      SPAxis flipAxis) {
    
    int index;
    
    switch(flipAxis) {
        case SPAxisX:
            index = 0;
            break;
        case SPAxisY:
            index = 1;
            break;
        case SPAxisZ:
            index = 2;
            break;
        default:
            return transform;
            break;
    }
    
    SPAffineTransform3DFloat flip = SPAffineTransform3DFloatIdentity;
    
    flip.matrix.columns[index][index] = -1;
    flip.matrix.columns[3][0] = 0;
    
    SPAffineTransform3DFloat x = SPAffineTransform3DFloatConcatenation(flip, transform);
    x = SPAffineTransform3DFloatConcatenation(x, flip);
    
    return x;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatShear(SPAffineTransform3DFloat transform,
                                                       SPAxis shearAxis,
                                                       float shearFactor0,
                                                       float shearFactor1) {
    
    if(shearAxis != SPAxisX && shearAxis != SPAxisY && shearAxis != SPAxisZ) {
        return transform;
    }
    
    simd_float3 column0;
    simd_float3 column1;
    simd_float3 column2;
    simd_float3 column3;
    
    switch (shearAxis) {
        case SPAxisX:
            column0 = (simd_float3){1, shearFactor0, shearFactor1};
            column1 = (simd_float3){0, 1, 0};
            column2 = (simd_float3){0, 0, 1};
            column3 = (simd_float3){0, 0, 0};
            break;
        case SPAxisY:
            column0 = (simd_float3){1, 0, 0};
            column1 = (simd_float3){shearFactor0, 1, shearFactor1};
            column2 = (simd_float3){0, 0, 1};
            column3 = (simd_float3){0, 0, 0};
            break;
        case SPAxisZ:
            column0 = (simd_float3){1, 0, 0};
            column1 = (simd_float3){0, 1, 0};
            column2 = (simd_float3){shearFactor0, shearFactor1, 1};
            column3 = (simd_float3){0, 0, 0};
            break;
    }
    
    simd_float4x3 shearMatrix = simd_matrix(column0,
                                            column1,
                                            column2,
                                            column3);
    
    SPAffineTransform3DFloat shearTransform = { .matrix = shearMatrix };
    
    return SPAffineTransform3DFloatConcatenation(transform, shearTransform);
}

// MARK: - make from pose

/*!
 @abstract Returns a new affine transform structure from the specified pose structure.
 
 @param pose The source pose.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeWithPose(SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeWithPose(SPPose3DFloat pose) {
    
    return SPAffineTransform3DFloatMake(SPSize3DFloatMake(1, 1, 1),
                                        pose.rotation,
                                        SPVector3DFloatMakeWithVector(pose.position.vector));
    
}

/*!
 @abstract Returns a new affine transform structure from the specified scaled pose structure.
 
 @param pose The source scaled pose.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeWithScaledPose(SPScaledPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatMakeWithScaledPose(SPScaledPose3DFloat pose) {
    
    return SPAffineTransform3DFloatMake(SPSize3DFloatMake(pose.scale, pose.scale, pose.scale),
                                        pose.rotation,
                                        SPVector3DFloatMakeWithVector(pose.position.vector));
}

// MARK: Change basis

/*!
 @abstract Returns a new affine transform structure by applying a change-of-basis.
 @param transform The source transform.
 @param from The old basis.
 @param to The new basis.
 @returns A new affine transform structure or `SPAffineTransform3DInvalid`.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatChangeBasis(SPAffineTransform3DFloat transform,
                                                             SPAffineTransform3DFloat from,
                                                             SPAffineTransform3DFloat to)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3DFloat SPAffineTransform3DFloatChangeBasis(SPAffineTransform3DFloat transform,
                                                             SPAffineTransform3DFloat from,
                                                             SPAffineTransform3DFloat to) {
    
    SPAffineTransform3DFloat fromInverted = SPAffineTransform3DFloatInverted(from);
    if (!SPAffineTransform3DFloatIsValid(fromInverted)) {
        return SPAffineTransform3DFloatInvalid;
    }
    
    SPAffineTransform3DFloat toInverted = SPAffineTransform3DFloatInverted(to);
    if (!SPAffineTransform3DFloatIsValid(toInverted)) {
        return SPAffineTransform3DFloatInvalid;
    }
    
    // from * to.inverse * self * to * from.inverse
    SPAffineTransform3DFloat tx = SPAffineTransform3DFloatConcatenation(from, toInverted);
    tx = SPAffineTransform3DFloatConcatenation(tx, transform);
    tx = SPAffineTransform3DFloatConcatenation(tx, to);
    tx = SPAffineTransform3DFloatConcatenation(tx, fromInverted);
    
    return tx;
}

#endif /* Spatial_SPAffineTransform3DFloat_h */
