#ifndef Spatial_SPAffineTransform3D_h
#define Spatial_SPAffineTransform3D_h

#include <Spatial/Structures.h>
#include <Spatial/SPRotation3D.h>

// MARK: - Public API

// MARK: - Creating an affine transform

/*!
 @abstract Returns a new affine transform structure from the specified 4 x 3 matrix.
 
 @param matrix The source matrix.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeWith4x3Matrix(simd_double4x3 matrix)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a new affine transform structure from the specified 4 x 4 matrix.
 
 @param matrix The source matrix.
 @returns A new affine transform structure.
 @note The the last row of the source matrix must be @p {0,0,0,1}).
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeWith4x4Matrix(simd_double4x4 matrix)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));
__API_DEPRECATED("Use `SPAffineTransform3DMakeWithTruncated4x4Matrix` instead.",
                 macos(13.0, 15.0),
                 ios(16.0, 18.0),
                 watchos(9.0, 11.0),
                 tvos(16.0, 18.0));

/*!
 @abstract Returns a new affine transform structure from the specified 4 x 4 matrix truncated to a  4 x 3 matrix.
 
 @param matrix The source matrix.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeWithTruncated4x4Matrix(simd_double4x4 matrix)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/*!
 @abstract Returns a new affine transform structure from the specified projective transform.
 
 @param transform The source transform.
 @returns A new affine transform structure.
 @note The projective transform must be affine (that is,its last row must be @p {0,0,0,1}), you can
 check this by calling @p SPProjectiveTransform3DIsAffine .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeWithProjective(SPProjectiveTransform3D transform)
__API_DEPRECATED("Use `SPAffineTransform3DMakeWithTruncatedProjective` instead.",
                 macos(13.0, 15.0),
                 ios(16.0, 18.0),
                 watchos(9.0, 11.0),
                 tvos(16.0, 18.0));

/*!
 @abstract Returns a new affine transform structure from the first three rows of the specified projective transform.
 
 @param transform The source transform.
 @returns A new affine transform structure.
 @note This function is similar to @p SPAffineTransform3DMakeWithProjective, but it ignores the last
 row of the matrix.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeWithTruncatedProjective(SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

/*!
 @abstract Returns a new scale affine transform.
 
 @param scale The scale.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeScale(SPSize3D scale)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a new rotation affine transform.
 
 @param rotation The rotation.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeRotation(SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a new translation affine transform.
 
 @param translation The translation.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeTranslation(SPSize3D translation)
__API_DEPRECATED("Use `SPVector3D` variant.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Returns a new translation affine transform.
 
 @param offset The translation.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeTranslation(SPVector3D offset)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a new scale, rotate, translate affine transform.
 
 @param scale The scale.
 @param rotation The rotation.
 @param translation The translation.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMake(SPSize3D scale,
                                            SPRotation3D rotation,
                                            SPSize3D translation)
__API_DEPRECATED("Use `SPVector3D` variant.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Returns a new scale, rotate, translate affine transform.
 
 @param scale The scale.
 @param rotation The rotation.
 @param translation The translation.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMake(SPSize3D scale,
                                            SPRotation3D rotation,
                                            SPVector3D translation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

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
SPAffineTransform3D SPAffineTransform3DMakeShear(SPAxis shearAxis,
                                                 double shearFactor0,
                                                 double shearFactor1)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Querying transform properties

/*!
 @abstract Returns the first three columns of an affine transform's underlying matrix.
 
 @param transform The source transform.
 @returns A 3 x 3 matrix that's constructed from the first three columns of an affine transform's underlying matrix.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_double3x3 SPAffineTransform3DGet3x3Matrix(SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a 4 x 4 matrix constructed from the affine transform's underlying matrix.
 
 @param transform The source transform.
 @returns A 4 x 4 matrix that's constructed from the affine transform's underlying 4 x 3 matrix with an
 additional row that contains the values @p [0,0,0,1] .
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_double4x4 SPAffineTransform3DGet4x4Matrix(SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform's underlying matrix has an inverse.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform's underlying matrix has an inverse.
*/
SPATIAL_INLINE bool SPAffineTransform3DIsInvertible(SPAffineTransform3D transform)
SPATIAL_OVERLOADABLE
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether an affine transform is a valid transform.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the affine transform is a valid transform.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DIsValid(SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform only contains a translation.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform only contains a translation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DIsTranslation(SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform is the identity transform.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is the identity transform.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DIsIdentity(SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform scales equally over all dimensions.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is uniform over all dimensions.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DIsUniform(SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns `true` if the transform scales equally over the specified dimensions.
 
 @discussion
 Passing @p dimensionFlags of @p SPAxisX|SPAxisY|SPAxisZ returns the same result as @p SPAffineTransform3DIsUniform .
 Passing a @p dimensionFlags  that specifies zero or one axis returns the same result as @p SPAffineTransform3DIsRectilinear .
 
 @param transform The transform.
 @param dimensionFlags  A bitmask that specifies which dimensions the function queries. Use logical OR to combine axes .
 
 @returns @p true if the transform is rectilinear and the specified axes have equal scales.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DIsUniformOverDimensions(SPAffineTransform3D transform,
                                                SPAxis dimensionFlags)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform is rectilinear.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is rectilinear.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DIsRectilinear(SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Deriving new transforms

/*!
 @abstract Returns a new transform that's constructed by inverting an existing affine transform.
 
 @param transform The source transform.
 @returns A new transform that's constructed by inverting an existing affine transform.
 @note The source transform must be invertible, call @p SPAffineTransform3DIsInvertible to test
 whether this is the case. If the source transform isn't invertible, the function returns @p SPAffineTransform3DInvalid .
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DInverted(SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns an affine transformation matrix that's constructed by concatenating two existing affine transforms.
 
 @param t1 The first transform.
 @param t2 The second transform.
 @returns An affine transformation matrix that's constructed by concatenating two existing affine transforms.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DConcatenation(SPAffineTransform3D t1,
                                                     SPAffineTransform3D t2)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: Extracting component transforms

/*!
 @abstract Returns an affine transform's scale.
 
 @param transform The source transform.
 @returns A size structure that represents the transform's scale.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPAffineTransform3DGetScale(SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns an affine transform's rotation.
 
 @param transform The source transform.
 @returns A rotation structure that represents the transform's rotation.
 @note
 This function can't extract rotation from a non-scale-rotate-translate affine transform. In that case, the function
 returns @p SPRotation3DInvalid.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPAffineTransform3DGetRotation(SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns an affine transform's translation.
 
 @param transform The source transform.
 @returns A size structure that represents the transform's translation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPAffineTransform3DGetTranslation(SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns an affine transform's translation.
 
 @param transform The source transform.
 @returns A vector that represents the transform's translation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPAffineTransform3DGetOffset(SPAffineTransform3D transform)
__API_DEPRECATED("Use `SPAffineTransform3DGetTranslation`.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Sets the translation component on the specified transform.
 
 @param transform The transform.
 @param offset The translation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
void SPAffineTransform3DSetOffset(SPAffineTransform3D *transform, SPVector3D offset)
__API_DEPRECATED("Use `SPAffineTransform3DSetTranslation`.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Sets the translation component on the specified transform.
 
 @param transform The transform.
 @param offset The translation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
void SPAffineTransform3DSetTranslation(SPAffineTransform3D *transform, SPVector3D offset)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Transform equality

/*!
 @abstract Returns a Boolean value that indicates whether the two transform's matrices are equal within the Spatial default absolute tolerance.
 
 @param t1 The first transform.
 @param t2 The first transform.
 @returns A Boolean value that indicates whether the two transform's matrices are equal within the Spatial default absolute tolerance.
 @note The Spatial default tolerance is @p sqrt(__DBL_EPSILON__) .
 */
SPATIAL_INLINE
bool SPAffineTransform3DAlmostEqualToTransform(SPAffineTransform3D t1,
                                                SPAffineTransform3D t2)
SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the two transform's matrices are equal within the specified absolute tolerance.
 
 @param t1 The first transform.
 @param t2 The first transform.
 @returns A Boolean value that indicates whether the two transform's matrices are equal within the specified absolute tolerance.
 */
SPATIAL_INLINE
bool SPAffineTransform3DAlmostEqualToTransform(SPAffineTransform3D t1,
                                                SPAffineTransform3D t2,
                                                double tolerance)
SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

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
SPAffineTransform3D SPAffineTransform3DScaleBy(SPAffineTransform3D transform,
                                               double x, double y, double z)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns an affine transform that's constructed by concatenating an existing affine transform and a scale specified by an @p SPSize3D structure.
 
 @param transform The source transform.
 @param scale The scale value.
 @returns A transform that's scaled by the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DScaleBySize(SPAffineTransform3D transform,
                                                   SPSize3D scale)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns an affine transform that's constructed by concatenating an existing affine transform and a uniform scale.
 
 @param transform The source transform.
 @param scale The scale value.
 @returns A transform that's uniformly scaled by the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DScaleUniform(SPAffineTransform3D transform,
                                                    double scale)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns an affine transform that's constructed by concatenating an existing affine transform and a rotation.
 
 @param transform The source transform.
 @param rotation The rotation.
 @returns A transform that's rotated by the specified rotation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DRotate(SPAffineTransform3D transform,
                                              SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns an affine transform that's constructed by concatenating an existing affine transform and a rotation specified by a quaternion.
 
 @param transform The source transform.
 @param quaternion The quaternion that defines the rotation.
 @returns A transform that's rotated by the specified quaternion.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DRotateByQuaternion(SPAffineTransform3D transform,
                                                          simd_quatd quaternion)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns an affine transform that's constructed by concatenating an existing affine transform and a translation.
 
 @param transform The source transform.
 @param size A size structure that defines the translation.
 @returns A transform that's offset by the @p width, @p height, and @p depth of the size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DTranslate(SPAffineTransform3D transform,
                                                 SPSize3D size)
__API_DEPRECATED("Use `SPVector3D` variant.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Returns an affine transform that's constructed by concatenating an existing affine transform and a translation.
 
 @param transform The source transform.
 @param offset A vector that defines the translation.
 @returns A transform that's offset by the @p x, @p y, and @p z of the vector.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DTranslate(SPAffineTransform3D transform,
                                                 SPVector3D offset)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns an affine transform that's flipped along the specified axis.
 
 @discussion
 If you pass a flip axis that's not @p x , @p y , or @p z , the function returns @p transform unmodified.
 
 @param flipAxis The flip axis.
 @returns A new transform flipped along the specified axis.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DFlip(SPAffineTransform3D transform,
                                            SPAxis flipAxis)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

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
SPAffineTransform3D SPAffineTransform3DShear(SPAffineTransform3D transform,
                                             SPAxis shearAxis,
                                             double shearFactor0,
                                             double shearFactor1)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: Header inline implementations

// MARK: - Creating an affine transform

SPATIAL_SWIFT_NAME(AffineTransform3D.init(_:))
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeWith4x3Matrix(simd_double4x3 matrix) {
    SPAffineTransform3D transform = { .matrix = matrix };
    
    return transform;
}

SPATIAL_SWIFT_NAME(AffineTransform3D.init(truncating:))
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeWithTruncatedProjective(SPProjectiveTransform3D transform) {
    simd_double3 column0 = transform.matrix.columns[0].xyz;
    simd_double3 column1 = transform.matrix.columns[1].xyz;
    simd_double3 column2 = transform.matrix.columns[2].xyz;
    simd_double3 column3 = transform.matrix.columns[3].xyz;
    
    SPAffineTransform3D affine = { .matrix = simd_matrix(column0,
                                                         column1,
                                                         column2,
                                                         column3) };
    
    return affine;
}

SPATIAL_SWIFT_NAME(AffineTransform3D.init(truncating:))
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeWithTruncated4x4Matrix(simd_double4x4 matrix) {

    simd_double3 column0 = matrix.columns[0].xyz;
    simd_double3 column1 = matrix.columns[1].xyz;
    simd_double3 column2 = matrix.columns[2].xyz;
    simd_double3 column3 = matrix.columns[3].xyz;
    
    SPAffineTransform3D affine = { .matrix = simd_matrix(column0,
                                                         column1,
                                                         column2,
                                                         column3) };
    
    return affine;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeWith4x4Matrix(simd_double4x4 matrix) {
 
    if (!_sp_almost_equal(0, matrix.columns[0].w) ||
        !_sp_almost_equal(0, matrix.columns[1].w) ||
        !_sp_almost_equal(0, matrix.columns[2].w) ||
        !_sp_almost_equal(1, matrix.columns[3].w)) {
        return  SPAffineTransform3DInvalid;
    }
    
    simd_double3 column0 = matrix.columns[0].xyz;
    simd_double3 column1 = matrix.columns[1].xyz;
    simd_double3 column2 = matrix.columns[2].xyz;
    simd_double3 column3 = matrix.columns[3].xyz;
    
    SPAffineTransform3D affine = { .matrix = simd_matrix(column0,
                                                         column1,
                                                         column2,
                                                         column3) };
    
    return affine;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeWithProjective(SPProjectiveTransform3D transform) {
    
    return SPAffineTransform3DMakeWith4x4Matrix(transform.matrix);
}

SPATIAL_SWIFT_NAME(AffineTransform3D.init(scale:))
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeScale(SPSize3D scale) {
    
    simd_double3 column0 = {scale.width, 0, 0};
    simd_double3 column1 = {0, scale.height, 0};
    simd_double3 column2 = {0, 0, scale.depth};
    simd_double3 column3 = {0, 0, 0};
    
    simd_double4x3 matrix = simd_matrix(column0, column1, column2, column3);
    
    SPAffineTransform3D transform = { .matrix = matrix };
    
    return transform;
}

SPATIAL_SWIFT_NAME(AffineTransform3D.init(rotation:))
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeRotation(SPRotation3D rotation) {
    
    simd_quatd quaternion = SPRotation3DGetQuaternion(rotation);
    
    simd_double3x3 quaternionMatrix = simd_matrix3x3(quaternion);
    
    simd_double4x3 matrix = simd_matrix(quaternionMatrix.columns[0],
                                        quaternionMatrix.columns[1],
                                        quaternionMatrix.columns[2],
                                        simd_make_double3(0, 0, 0));
    
    SPAffineTransform3D transform = { .matrix = matrix };
    
    return transform;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeTranslation(SPSize3D translation) {
    
    SPVector3D v = SPVector3DMakeWithVector(translation.vector);
    
    return SPAffineTransform3DMakeTranslation(v);
}

SPATIAL_SWIFT_NAME(AffineTransform3D.init(translation:))
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeTranslation(SPVector3D offset) {
    
    simd_double3 column0 = {1, 0, 0};
    simd_double3 column1 = {0, 1, 0};
    simd_double3 column2 = {0, 0, 1};
    simd_double3 column3 = {offset.x, offset.y, offset.z};
    
    simd_double4x3 matrix = simd_matrix(column0, column1, column2, column3);
    
    SPAffineTransform3D transform = { .matrix = matrix };
    
    return transform;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMake(SPSize3D scale,
                                            SPRotation3D rotation,
                                            SPSize3D translation) {
    
    SPVector3D v = SPVector3DMakeWithVector(translation.vector);
    
    return SPAffineTransform3DMake(scale, rotation, v);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMake(SPSize3D scale,
                                            SPRotation3D rotation,
                                            SPVector3D translation) {
    
    SPAffineTransform3D scaleTransform = SPAffineTransform3DMakeScale(scale);
    SPAffineTransform3D rotateTransfrom = SPAffineTransform3DMakeRotation(rotation);
    SPAffineTransform3D translateTransform = SPAffineTransform3DMakeTranslation(translation);
    
    
    SPAffineTransform3D t = SPAffineTransform3DConcatenation(rotateTransfrom, scaleTransform);
    t = SPAffineTransform3DConcatenation(translateTransform, t);
    
    return t;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeShear(SPAxis shearAxis,
                                                 double shearFactor0,
                                                 double shearFactor1) {
    
    SPAffineTransform3D transform = SPAffineTransform3DIdentity;
    
    transform = SPAffineTransform3DShear(transform,
                                         shearAxis,
                                         shearFactor0,
                                         shearFactor1);
    
    return transform;
}
// MARK: - Querying transform properties

SPATIAL_SWIFT_NAME(getter:AffineTransform3D.matrix3x3(self:))
SPATIAL_OVERLOADABLE
simd_double3x3 SPAffineTransform3DGet3x3Matrix(SPAffineTransform3D transform) {

    return simd_matrix(transform.matrix.columns[0],
                       transform.matrix.columns[1],
                       transform.matrix.columns[2]);
}

SPATIAL_SWIFT_NAME(getter:AffineTransform3D.matrix4x4(self:))
SPATIAL_OVERLOADABLE
simd_double4x4 SPAffineTransform3DGet4x4Matrix(SPAffineTransform3D transform) {
    
    simd_double4 col0 = simd_make_double4(transform.matrix.columns[0].xyz, 0);
    simd_double4 col1 = simd_make_double4(transform.matrix.columns[1].xyz, 0);
    simd_double4 col2 = simd_make_double4(transform.matrix.columns[2].xyz, 0);
    simd_double4 col3 = simd_make_double4(transform.matrix.columns[3].xyz, 1);
    
    return simd_matrix(col0, col1, col2, col3);
}

SPATIAL_SWIFT_NAME(getter:AffineTransform3D.isInvertible(self:))
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DIsInvertible(SPAffineTransform3D transform) {
    simd_double3x3 matrix3x3 = (simd_double3x3){
        transform.matrix.columns[0],
        transform.matrix.columns[1],
        transform.matrix.columns[2]
    };
    return simd_determinant(matrix3x3) != 0;
}

SPATIAL_SWIFT_NAME(getter:AffineTransform3D.isTranslation(self:))
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DIsTranslation(SPAffineTransform3D transform) {
    
    simd_double3x3 matrix3x3 = SPAffineTransform3DGet3x3Matrix(transform);

    return  simd_equal(matrix_identity_double3x3,
                       matrix3x3);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DIsValid(SPAffineTransform3D transform) {
    return (simd_all(_sp_simd_isfinite(transform.matrix.columns[0])) &&
            simd_all(_sp_simd_isfinite(transform.matrix.columns[1])) &&
            simd_all(_sp_simd_isfinite(transform.matrix.columns[2])) &&
            simd_all(_sp_simd_isfinite(transform.matrix.columns[3])));
}

SPATIAL_SWIFT_NAME(getter:AffineTransform3D.isIdentity(self:))
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DIsIdentity(SPAffineTransform3D transform){
    return simd_equal(transform.matrix, SPAffineTransform3DIdentity.matrix);
}

SPATIAL_SWIFT_NAME(getter:AffineTransform3D.isUniform(self:))
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DIsUniform(SPAffineTransform3D transform) {
    
    SPSize3D scale = SPAffineTransform3DGetScale(transform);
    bool isRectilinear = SPAffineTransform3DIsRectilinear(transform);
    
    return isRectilinear && scale.width == scale.height && scale.height == scale.depth;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DIsUniformOverDimensions(SPAffineTransform3D transform,
                                                 SPAxis dimensionFlags) {
    
    if (dimensionFlags == 0b111) {
        return SPAffineTransform3DIsUniform(transform);
    }
    
    SPSize3D scale = SPAffineTransform3DGetScale(transform);
    bool isUniform = SPAffineTransform3DIsRectilinear(transform);
    
    if (dimensionFlags == 0b011) {
        isUniform = isUniform && (scale.width == scale.height);
    } else if (dimensionFlags == 0b101) {
        isUniform = isUniform && (scale.width == scale.depth);
    } else if (dimensionFlags == 0b110) {
        isUniform = isUniform && (scale.height == scale.depth);
    }
    
    return isUniform;
}

SPATIAL_SWIFT_NAME(getter:AffineTransform3D.isRectilinear(self:))
SPATIAL_OVERLOADABLE
bool SPAffineTransform3DIsRectilinear(SPAffineTransform3D transform) {
    
    simd_double3x3 matrix3x3 = SPAffineTransform3DGet3x3Matrix(transform);
    
    double angle = fabs(remainder(simd_angle(simd_quaternion(matrix3x3)), M_PI / 2));
    
    return angle < SPDefaultTolerance;
}

// MARK: - Deriving new transforms

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DInverted(SPAffineTransform3D transform) {
    
    simd_double3x3 matrix3x3 = SPAffineTransform3DGet3x3Matrix(transform);
    
    if (!SPAffineTransform3DIsInvertible(transform)) {
        return SPAffineTransform3DInvalid;
    }
    
    simd_double3x3 m_inv = matrix_invert(matrix3x3);
    
    simd_double3 t = simd_mul(m_inv, transform.matrix.columns[3]);
    t = t * simd_make_double3(-1, -1, -1);
    
    simd_double4x3 matrix = simd_matrix(m_inv.columns[0],
                                        m_inv.columns[1],
                                        m_inv.columns[2],
                                        t);
    
    SPAffineTransform3D invertedTransform = { .matrix = matrix };
    
    return invertedTransform;
}

SPATIAL_SWIFT_NAME(AffineTransform3D.concatenating(self:_:))
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DConcatenation(SPAffineTransform3D t1, SPAffineTransform3D t2) {
    
    if (SPAffineTransform3DIsTranslation(t1) && SPAffineTransform3DIsTranslation(t2)) {
        
        // Both transforms are translations only, return sum of translate columns:
        t1.matrix.columns[3] = t1.matrix.columns[3] + t2.matrix.columns[3];
        return t1;
        
    } else if (simd_all(t1.matrix.columns[3] == (simd_double3){0, 0, 0}) &&
               simd_all(t2.matrix.columns[3] == (simd_double3){0, 0, 0})) {
        
        // Neither transform contains a translation, return 3x3 * 3x3:
        simd_double3x3 t1_3x3 = SPAffineTransform3DGet3x3Matrix(t1);
        simd_double3x3 t2_3x3 = SPAffineTransform3DGet3x3Matrix(t2);
        
        simd_double3x3 product = simd_mul(t1_3x3, t2_3x3);
        
        simd_double4x3 matrix = simd_matrix(product.columns[0],
                                            product.columns[1],
                                            product.columns[2],
                                            t1.matrix.columns[3]);
        
        SPAffineTransform3D transform = { .matrix = matrix };
        
        return transform;
        
    } else {
        
        // Return 4x4 * 4x4:
        simd_double4x4 t1_4x4 = SPAffineTransform3DGet4x4Matrix(t1);
        simd_double4x4 t2_4x4 = SPAffineTransform3DGet4x4Matrix(t2);
        
        simd_double4x4 product = simd_mul(t1_4x4, t2_4x4);
        
        simd_double4x3 matrix = simd_matrix(product.columns[0].xyz,
                                            product.columns[1].xyz,
                                            product.columns[2].xyz,
                                            product.columns[3].xyz);
        
        SPAffineTransform3D transform = { .matrix = matrix };
        
        return transform;
    }
}

// MARK: Extracting component transforms

SPATIAL_SWIFT_NAME(getter:AffineTransform3D.scale(self:))
SPATIAL_OVERLOADABLE
SPSize3D SPAffineTransform3DGetScale(SPAffineTransform3D transform) {
    
    simd_double3x3 matrix3x3 = SPAffineTransform3DGet3x3Matrix(transform);
    double sign = simd_determinant(matrix3x3) >= 0 ? 1.0 : -1.0;
    simd_double3 scale = {
        simd_length(matrix3x3.columns[0]),
        simd_length(matrix3x3.columns[1]),
        simd_length(matrix3x3.columns[2])
    };
    
    simd_double3 signedScale = scale * sign;
    
    return SPSize3DMakeWithVector(signedScale);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPAffineTransform3DGetRotation(SPAffineTransform3D transform) {
    
    simd_double3x3 matrix3x3 = SPAffineTransform3DGet3x3Matrix(transform);
    
    SPSize3D scaleSize = SPAffineTransform3DGetScale(transform);
    simd_double3 scale = (simd_double3){ scaleSize.width, scaleSize.height, scaleSize.depth };
    
    matrix3x3.columns[0] /= scale.x;
    matrix3x3.columns[1] /= scale.y;
    matrix3x3.columns[2] /= scale.z;
    
    // orthogonalize matrix...
    
    matrix3x3.columns[1] = matrix3x3.columns[1] - simd_project(matrix3x3.columns[1], matrix3x3.columns[0]);
    matrix3x3.columns[2] = matrix3x3.columns[2] - simd_project(matrix3x3.columns[2], matrix3x3.columns[0]) - simd_project(matrix3x3.columns[2], matrix3x3.columns[1]);
    
    matrix3x3.columns[0] = simd_normalize(matrix3x3.columns[0]);
    matrix3x3.columns[1] = simd_normalize(matrix3x3.columns[1]);
    matrix3x3.columns[2] = simd_normalize(matrix3x3.columns[2]);
    
    simd_quatd quaternion = simd_quaternion(matrix3x3);
    
    if (simd_any(_sp_simd_isnan(quaternion.vector))) {
        // Cannot extract rotation from non-SRT compliant `SPAffineTransform3D`
        return SPRotation3DInvalid;
    }
    
    return SPRotation3DMakeWithQuaternion(simd_normalize(quaternion));
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPAffineTransform3DGetTranslation(SPAffineTransform3D transform) {
    
    simd_double3 translation = transform.matrix.columns[3];
    
    return SPVector3DMakeWithVector(translation);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPAffineTransform3DGetOffset(SPAffineTransform3D transform) {
    
    simd_double3 translation = transform.matrix.columns[3];
    
    return SPVector3DMakeWithVector(translation.x);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
void SPAffineTransform3DSetOffset(SPAffineTransform3D *transform, SPVector3D offset) {
    
    SPAffineTransform3DSetTranslation(transform, offset);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
void SPAffineTransform3DSetTranslation(SPAffineTransform3D *transform, SPVector3D offset) {
    
    transform->matrix.columns[3] = offset.vector;
}

// MARK: - Transform equality

bool SPAffineTransform3DAlmostEqualToTransform(SPAffineTransform3D t1,
                                                SPAffineTransform3D t2) SPATIAL_OVERLOADABLE {
    
    return simd_almost_equal_elements(t1.matrix, t2.matrix, SPDefaultTolerance);
}

bool SPAffineTransform3DAlmostEqualToTransform(SPAffineTransform3D t1,
                                                SPAffineTransform3D t2,
                                                double tolerance) SPATIAL_OVERLOADABLE {
    
    return simd_almost_equal_elements(t1.matrix, t2.matrix, tolerance);
}

// MARK: - Applying transform

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DScaleBy(SPAffineTransform3D transform,
                                               double x, double y, double z) {
    
    SPSize3D scale = SPSize3DMake(x, y, z);
    SPAffineTransform3D scaleTransform = SPAffineTransform3DMakeScale(scale);
    
    return SPAffineTransform3DConcatenation(transform, scaleTransform);
}

SPATIAL_SWIFT_NAME(AffineTransform3D.scaled(self:by:))
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DScaleBySize(SPAffineTransform3D transform,
                                                   SPSize3D scale) {
    SPAffineTransform3D scaleTransform = SPAffineTransform3DMakeScale(scale);
    
    return SPAffineTransform3DConcatenation(transform, scaleTransform);
}

SPATIAL_SWIFT_NAME(AffineTransform3D.uniformlyScaled(self:by:))
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DScaleUniform(SPAffineTransform3D transform,
                                                    double scale) {
    
    SPSize3D scaleSize = SPSize3DMake(scale, scale, scale);
    SPAffineTransform3D scaleTransform = SPAffineTransform3DMakeScale(scaleSize);
    
    return SPAffineTransform3DConcatenation(transform, scaleTransform);
}

SPATIAL_SWIFT_NAME(AffineTransform3D.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DRotate(SPAffineTransform3D transform,
                                              SPRotation3D rotation) {
    
    SPAffineTransform3D rotationTransform = SPAffineTransform3DMakeRotation(rotation);
    
    return SPAffineTransform3DConcatenation(transform, rotationTransform);
}

SPATIAL_SWIFT_NAME(AffineTransform3D.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DRotateByQuaternion(SPAffineTransform3D transform,
                                                          simd_quatd quaternion) {
    
    SPRotation3D rotation = SPRotation3DMakeWithQuaternion(quaternion);
    SPAffineTransform3D rotationTransform = SPAffineTransform3DMakeRotation(rotation);
    
    return SPAffineTransform3DConcatenation(transform, rotationTransform);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DTranslate(SPAffineTransform3D transform,
                                                 SPSize3D size) {
    
    SPAffineTransform3D translate = SPAffineTransform3DMakeTranslation(size);
    
    return SPAffineTransform3DConcatenation(transform, translate);
}

SPATIAL_SWIFT_NAME(AffineTransform3D.translated(self:by:))
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DTranslate(SPAffineTransform3D transform,
                                                 SPVector3D offset) {
    
    SPAffineTransform3D translate = SPAffineTransform3DMakeTranslation(offset);
    
    return SPAffineTransform3DConcatenation(transform, translate);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DFlip(SPAffineTransform3D transform,
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
    
    SPAffineTransform3D flip = SPAffineTransform3DIdentity;
    
    flip.matrix.columns[index][index] = -1;
    flip.matrix.columns[3][0] = 0;
    
    SPAffineTransform3D x = SPAffineTransform3DConcatenation(flip, transform);
    x = SPAffineTransform3DConcatenation(x, flip);
    
    return x;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DShear(SPAffineTransform3D transform,
                                             SPAxis shearAxis,
                                             double shearFactor0,
                                             double shearFactor1) {
    
    if(shearAxis != SPAxisX && shearAxis != SPAxisY && shearAxis != SPAxisZ) {
        return transform;
    }
    
    simd_double3 column0;
    simd_double3 column1;
    simd_double3 column2;
    simd_double3 column3;
    
    switch (shearAxis) {
    case SPAxisX:
        column0 = (simd_double3){1, shearFactor0, shearFactor1};
        column1 = (simd_double3){0, 1, 0};
        column2 = (simd_double3){0, 0, 1};
        column3 = (simd_double3){0, 0, 0};
        break;
    case SPAxisY:
        column0 = (simd_double3){1, 0, 0};
        column1 = (simd_double3){shearFactor0, 1, shearFactor1};
        column2 = (simd_double3){0, 0, 1};
        column3 = (simd_double3){0, 0, 0};
        break;
    case SPAxisZ:
        column0 = (simd_double3){1, 0, 0};
        column1 = (simd_double3){0, 1, 0};
        column2 = (simd_double3){shearFactor0, shearFactor1, 1};
        column3 = (simd_double3){0, 0, 0};
        break;
    }
    
    simd_double4x3 shearMatrix = simd_matrix(column0,
                                             column1,
                                             column2,
                                             column3);
    
    SPAffineTransform3D shearTransform = { .matrix = shearMatrix };
    
    return SPAffineTransform3DConcatenation(transform, shearTransform);
}

// MARK: - make from pose

/*!
 @abstract Returns a new affine transform structure from the specified pose structure.

 @param pose The source pose.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeWithPose(SPPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeWithPose(SPPose3D pose) {
    
    return SPAffineTransform3DMake(SPSize3DMake(1, 1, 1),
                                   pose.rotation,
                                   SPVector3DMakeWithVector(pose.position.vector));
    
}

/*!
 @abstract Returns a new affine transform structure from the specified scaled pose structure.

 @param pose The source scaled pose.
 @returns A new affine transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeWithScaledPose(SPScaledPose3D pose)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DMakeWithScaledPose(SPScaledPose3D pose) {
    
    return SPAffineTransform3DMake(SPSize3DMake(pose.scale, pose.scale, pose.scale),
                                   pose.rotation,
                                   SPVector3DMakeWithVector(pose.position.vector));
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
SPAffineTransform3D SPAffineTransform3DChangeBasis(SPAffineTransform3D transform,
                                                   SPAffineTransform3D from,
                                                   SPAffineTransform3D to)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAffineTransform3D SPAffineTransform3DChangeBasis(SPAffineTransform3D transform,
                                                   SPAffineTransform3D from,
                                                   SPAffineTransform3D to) {
    
    SPAffineTransform3D fromInverted = SPAffineTransform3DInverted(from);
    if (!SPAffineTransform3DIsValid(fromInverted)) {
        return SPAffineTransform3DInvalid;
    }
    
    SPAffineTransform3D toInverted = SPAffineTransform3DInverted(to);
    if (!SPAffineTransform3DIsValid(toInverted)) {
        return SPAffineTransform3DInvalid;
    }
    
    // from * to.inverse * self * to * from.inverse
    SPAffineTransform3D tx = SPAffineTransform3DConcatenation(from, toInverted);
    tx = SPAffineTransform3DConcatenation(tx, transform);
    tx = SPAffineTransform3DConcatenation(tx, to);
    tx = SPAffineTransform3DConcatenation(tx, fromInverted);
    
    return tx;
}

#endif /* Spatial_SPAffineTransform3D_h */
