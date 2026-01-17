#ifndef Spatial_SPProjectiveTransform3D_h
#define Spatial_SPProjectiveTransform3D_h

#include <Spatial/Structures.h>
#include <Spatial/SPRotation3D.h>
#include <Spatial/SPAffineTransform3D.h>

// MARK: - Public API

// MARK: - Creating a projective transform

/// Returns a new transform from the specified 4 x 4 matrix.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWith4x4Matrix(simd_double4x4 matrix)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Returns a new transform from the specified affine transform.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithAffine(SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Returns a new scale transform.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeScale(SPSize3D scale)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Returns a new rotation transform.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeRotation(SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Returns a new translate transform.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeTranslation(SPSize3D translation)
__API_DEPRECATED("Use `SPVector3D` variant.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));


/// Returns a new translate transform.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeTranslation(SPVector3D offset)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a projective transform with right-hand side perspective.
 
 @param fovyRadians The field of view angle on the @p y axis.
 @param aspectRatio The aspect ratio.
 @param nearZ The near @p z .
 @param farZ The far @p z .
 @returns A projective transform with right-hand side perspective.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithRHPerspective(double fovyRadians,
                                                                     double aspectRatio,
                                                                     double nearZ,
                                                                     double farZ)
__API_DEPRECATED("Use `SPProjectiveTransform3DMakeWithRightHandPerspective`.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Returns a projective transform with right-hand side perspective.
 
 @param fovyRadians The field of view angle on the @p y axis.
 @param aspectRatio The aspect ratio.
 @param nearZ The near @p z .
 @param farZ The far @p z .
 @returns A projective transform with right-hand side perspective.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithRightHandPerspective(double fovyRadians,
                                                                            double aspectRatio,
                                                                            double nearZ,
                                                                            double farZ)
__API_DEPRECATED("Use `SPAngle` variant of `SPProjectiveTransform3DMakeWithRightHandPerspective`.",
                 macos(13.0, 15.0),
                 ios(16.0, 18.0),
                 watchos(9.0, 11.0),
                 tvos(16.0, 18.0));

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
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithRightHandPerspective(SPAngle fovY,
                                                                            double aspectRatio,
                                                                            double nearZ,
                                                                            double farZ)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/*!
 @abstract Returns a projective transform with right-hand side perspective.
 
 @param fovyRadians The field of view angle on the @p y axis.
 @param aspectRatio The aspect ratio.
 @param nearZ The near @p z .
 @param farZ The far @p z .
 @param reverseZ A Boolean value that specifies whether the matrix should use reverse z.
 @returns A projective transform with right-hand side perspective.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithRHPerspective(double fovyRadians,
                                                                     double aspectRatio,
                                                                     double nearZ,
                                                                     double farZ,
                                                                     bool reverseZ)
__API_DEPRECATED("Use `SPProjectiveTransform3DMakeWithRightHandPerspective`.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Returns a projective transform with right-hand side perspective.
 
 @param fovyRadians The field of view angle on the @p y axis.
 @param aspectRatio The aspect ratio.
 @param nearZ The near @p z .
 @param farZ The far @p z .
 @param reverseZ A Boolean value that specifies whether the matrix should use reverse z.
 @returns A projective transform with right-hand side perspective.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithRightHandPerspective(double fovyRadians,
                                                                            double aspectRatio,
                                                                            double nearZ,
                                                                            double farZ,
                                                                            bool reverseZ)
__API_DEPRECATED("Use `SPAngle` variant of `SPProjectiveTransform3DMakeWithRightHandPerspective`.",
                 macos(13.0, 15.0),
                 ios(16.0, 18.0),
                 watchos(9.0, 11.0),
                 tvos(16.0, 18.0));

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
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithRightHandPerspective(SPAngle fovY,
                                                                            double aspectRatio,
                                                                            double nearZ,
                                                                            double farZ,
                                                                            bool reverseZ)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

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
SPProjectiveTransform3D SPProjectiveTransform3DMakeFromTangents(double leftTangent,
                                                                double rightTangent,
                                                                double topTangent,
                                                                double bottomTangent,
                                                                double nearZ,
                                                                double farZ,
                                                                bool reverseZ)
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
SPProjectiveTransform3D SPProjectiveTransform3DMake(SPSize3D scale,
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
SPProjectiveTransform3D SPProjectiveTransform3DMake(SPSize3D scale,
                                                    SPRotation3D rotation,
                                                    SPVector3D translation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a new shear affine transform..
 
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
SPProjectiveTransform3D SPProjectiveTransform3DMakeShear(SPAxis shearAxis,
                                                         double shearFactor0,
                                                         double shearFactor1)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Querying transform properties

/*!
 @abstract Returns a Boolean value that indicates whether the transform is affine.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is affine.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsAffine(SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether a projective transform is a valid transform.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the projective transform is a valid transform.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsValid(SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform only contains a translation.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform only contains a translation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsTranslation(SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform is the identity transform.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is the identity transform.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsIdentity(SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform is a 3D projection.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is a 3D projection.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIs3DProjection(SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform is affine and scales equally over all dimensions.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is affine and uniform over all dimensions.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsUniform(SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns `true` if the transform is affine and scales equally over the specified dimensions.
 
 @discussion
 Passing  @p dimensionFlags of @p SPAxisX|SPAxisY|SPAxisZ returns the same result as @p SPProjectiveTransform3DIsUniform .
 Passing a @p dimensionFlags  that specifies zero or one axis returns the same result as @p SPProjectiveTransform3DIsRectilinear .
 
 @param transform The transform.
 @param dimensionFlags  A bitmask that specifies which dimensions the function queries. Use logical OR to combine axes .
 
 @returns @p true if the transform is affine, rectilinear, and the specified axes have equal scales.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsUniformOverDimensions(SPProjectiveTransform3D transform,
                                                     SPAxis dimensionFlags)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform is affine and rectilinear.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform is affine and rectilinear.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsRectilinear(SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the transform's underlying matrix has an inverse.
 
 @param transform The source transform.
 @returns A Boolean value that indicates whether the transform's underlying matrix has an inverse.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsInvertible(SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Deriving new transforms

/*!
 @abstract Returns a new transform that's constructed by inverting an existing projective transform.
 
 @param transform The source transform.
 @returns A new transform that's constructed by inverting an existing projective transform.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DInverted(SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Returns a projective transformation matrix constructed by concatenating two existing Projective transforms.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DConcatenation(SPProjectiveTransform3D t1,
                                                             SPProjectiveTransform3D t2)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: Extracting component transforms

/*!
 @abstract Returns a projective transform's scale.
 
 @param transform The source transform.
 @returns A size structure that represents the transform's scale.
 @note This function computes the scale from the first three rows of the transform matrix and ignores the fourth row.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPProjectiveTransform3DGetScale(SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a projective transform's rotation.
 
 @param transform The source transform.
 @returns A rotation structure that represents the transform's rotation.
 @note This function computes the rotation from the first three rows of the transform matrix and ignores the fourth row.
 If the projective transform isn't an affine scale-rotate-translate transform, this function returns @p SPRotation3DInvalid.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPProjectiveTransform3DGetRotation(SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a projective transform's translation.
 
 @param transform The source transform.
 @returns A size structure that represents the transform's translation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPProjectiveTransform3DGetTranslation(SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a projective transform's translation.
 
 @param transform The source transform.
 @returns A size structure that represents the transform's translation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPProjectiveTransform3DGetOffset(SPProjectiveTransform3D transform)
__API_DEPRECATED("Use `SPProjectiveTransform3DGetTranslation`.",
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
void SPProjectiveTransform3DSetOffset(SPProjectiveTransform3D *transform, SPVector3D offset)
__API_DEPRECATED("Use `SPProjectiveTransform3DSetTranslation`.",
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
void SPProjectiveTransform3DSetTranslation(SPProjectiveTransform3D *transform, SPVector3D offset)
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
bool SPProjectiveTransform3DAlmostEqualToTransform(SPProjectiveTransform3D t1,
                                                    SPProjectiveTransform3D t2)
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
bool SPProjectiveTransform3DAlmostEqualToTransform(SPProjectiveTransform3D t1,
                                                    SPProjectiveTransform3D t2,
                                                    double tolerance)
SPATIAL_OVERLOADABLE
SPATIAL_REFINED_FOR_SWIFT
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

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
SPProjectiveTransform3D SPProjectiveTransform3DScaleBy(SPProjectiveTransform3D transform,
                                                       double x, double y, double z)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a projective transform that's constructed by concatenating an existing projective transform and a scale specified by a @p Size3D structure.
 
 @param transform The source transform.
 @param scale The scale value.
 @returns A transform that's scaled by the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DScaleBySize(SPProjectiveTransform3D transform, SPSize3D scale)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a projective transform that's constructed by concatenating an existing projective transform and a uniform scale.
 
 @param transform The source transform.
 @param scale The scale value.
 @returns A transform that's uniformly scaled by the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DScaleUniform(SPProjectiveTransform3D transform, double scale)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a projective transform that's constructed by concatenating an existing projective transform and a rotation.
 
 @param transform The source transform.
 @param rotation The rotation.
 @returns A transform that's rotated by the specified rotation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DRotate(SPProjectiveTransform3D transform,
                                                      SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a projective transform that's constructed by concatenating an existing projective transform and a rotation specified by a quaternion.
 
 @param transform The source transform.
 @param quaternion The quaternion that defines the rotation.
 @returns A transform that's rotated by the specified quaternion.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DRotateByQuaternion(SPProjectiveTransform3D transform,
                                                                  simd_quatd quaternion)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a projective transform that's constructed by concatenating an existing projective transform and a translation.
 
 @param transform The source transform.
 @param size A size structure that defines the translation.
 @returns A transform that's offset by the @p width, @p height, and @p depth of the size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DTranslate(SPProjectiveTransform3D transform,
                                                         SPSize3D size)
__API_DEPRECATED("Use `SPVector3D` variant.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Returns a projective transform that's constructed by concatenating an existing projective transform and a translation.
 
 @param transform The source transform.
 @param offset A vector that defines the translation.
 @returns A transform that's offset by the @p width, @p height, and @p depth of the size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DTranslate(SPProjectiveTransform3D transform,
                                                         SPVector3D offset)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

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
SPProjectiveTransform3D SPProjectiveTransform3DShear(SPProjectiveTransform3D transform,
                                                     SPAxis shearAxis,
                                                     double shearFactor0,
                                                     double shearFactor1)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a projective transform that's flipped along the specified axis.
 
 @param flipAxis The flip axis.
 @returns A new transform flipped along the specified axis.
 @note The transform must be affine, otherwise the function returns @p SPProjectiveTransform3DInvalid .
 
 @discussion
 If you pass a shear axis that's not @p x , @p y , or @p z , the function returns @p transform unmodified.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DFlip(SPProjectiveTransform3D transform,
                                                    SPAxis flipAxis)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: Header inline implementations

// MARK: - Creating a projective transform

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.init(_:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWith4x4Matrix(simd_double4x4 matrix) {
    SPProjectiveTransform3D transform = { .matrix = matrix };
    
    return transform;
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.init(_:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithAffine(SPAffineTransform3D transform) {
    
    simd_double4 col0 = simd_make_double4(transform.matrix.columns[0], 0);
    simd_double4 col1 = simd_make_double4(transform.matrix.columns[1], 0);
    simd_double4 col2 = simd_make_double4(transform.matrix.columns[2], 0);
    simd_double4 col3 = simd_make_double4(transform.matrix.columns[3], 1);
    
    simd_double4x4 matrix = simd_matrix(col0, col1, col2, col3);
    
    SPProjectiveTransform3D projectiveTransform = { .matrix = matrix };
    
    return projectiveTransform;
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.init(scale:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeScale(SPSize3D scale) {
    
    simd_double4x4 matrix = simd_diagonal_matrix((simd_double4){
        scale.width,
        scale.height,
        scale.depth,
        1
    });
    
    SPProjectiveTransform3D projectiveTransform = { .matrix = matrix };
    
    return projectiveTransform;
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.init(rotation:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeRotation(SPRotation3D rotation) {
    
    simd_quatd quaternion = SPRotation3DGetQuaternion(rotation);
    
    simd_double4x4 matrix = simd_matrix4x4(quaternion);
    
    SPProjectiveTransform3D projectiveTransform = { .matrix = matrix };
    
    return projectiveTransform;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeTranslation(SPSize3D translation) {
    
    SPVector3D v = SPVector3DMakeWithVector(translation.vector);
    
    return SPProjectiveTransform3DMakeTranslation(v);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.init(translation:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeTranslation(SPVector3D offset) {
    
    simd_double4x4 matrix = matrix_identity_double4x4;
    
    matrix.columns[3] = (simd_double4){
        offset.x,
        offset.y,
        offset.z,
        1
    };
    
    SPProjectiveTransform3D projectiveTransform = { .matrix = matrix };
    
    return projectiveTransform;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMake(SPSize3D scale,
                                                    SPRotation3D rotation,
                                                    SPSize3D translation) {
    
    SPVector3D v = SPVector3DMakeWithVector(translation.vector);
    
    return SPProjectiveTransform3DMake(scale, rotation, v);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMake(SPSize3D scale,
                                                    SPRotation3D rotation,
                                                    SPVector3D translation) {
    
    SPProjectiveTransform3D scaleTransform = SPProjectiveTransform3DMakeScale(scale);
    SPProjectiveTransform3D rotateTransfrom = SPProjectiveTransform3DMakeRotation(rotation);
    SPProjectiveTransform3D translateTransform = SPProjectiveTransform3DMakeTranslation(translation);
    
    
    SPProjectiveTransform3D t = SPProjectiveTransform3DConcatenation(rotateTransfrom, scaleTransform);
    t = SPProjectiveTransform3DConcatenation(translateTransform, t);
    
    return t;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeShear(SPAxis shearAxis,
                                                         double shearFactor0,
                                                         double shearFactor1) {
    
    SPAffineTransform3D affine = SPAffineTransform3DMakeShear(shearAxis,
                                                              shearFactor0,
                                                              shearFactor1);
    
    return SPProjectiveTransform3DMakeWithAffine(affine);
    
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithRHPerspective(double fovyRadians,
                                                                     double aspectRatio,
                                                                     double nearZ,
                                                                     double farZ) SPATIAL_OVERLOADABLE {
    
    return SPProjectiveTransform3DMakeWithRightHandPerspective(fovyRadians, aspectRatio, nearZ, farZ, false);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithRHPerspective(double fovyRadians,
                                                                     double aspectRatio,
                                                                     double nearZ,
                                                                     double farZ,
                                                                     bool reverseZ) SPATIAL_OVERLOADABLE {
    return SPProjectiveTransform3DMakeWithRightHandPerspective(fovyRadians, aspectRatio, nearZ, farZ, reverseZ);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.init(fovyRadians:aspectRatio:nearZ:farZ:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithRightHandPerspective(double fovyRadians,
                                                                            double aspectRatio,
                                                                            double nearZ,
                                                                            double farZ) SPATIAL_OVERLOADABLE {
    
    return SPProjectiveTransform3DMakeWithRightHandPerspective(fovyRadians, aspectRatio, nearZ, farZ, false);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.init(fovY:aspectRatio:nearZ:farZ:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithRightHandPerspective(SPAngle fovY,
                                                                            double aspectRatio,
                                                                            double nearZ,
                                                                            double farZ) SPATIAL_OVERLOADABLE {
    
    return SPProjectiveTransform3DMakeWithRightHandPerspective(fovY.radians, aspectRatio, nearZ, farZ, false);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.init(fovyRadians:aspectRatio:nearZ:farZ:reverseZ:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithRightHandPerspective(double fovyRadians,
                                                                            double aspectRatio,
                                                                            double nearZ,
                                                                            double farZ,
                                                                            bool reverseZ) SPATIAL_OVERLOADABLE {
    
    double ys = 1 / tan(fovyRadians * 0.5);
    double xs = ys / aspectRatio;
    double zs = farZ / (nearZ - farZ);
    
    simd_double4x4 m = (simd_double4x4) {
        (simd_double4) { xs, 0, 0, 0 },
        (simd_double4) { 0, ys, 0, 0 },
        (simd_double4) { 0, 0, zs, -1 },
        (simd_double4) { 0, 0, nearZ * zs, 0}
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
    
    SPProjectiveTransform3D transform = { .matrix = m };
    
    return transform;
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.init(fovY:aspectRatio:nearZ:farZ:reverseZ:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithRightHandPerspective(SPAngle fovY,
                                                                            double aspectRatio,
                                                                            double nearZ,
                                                                            double farZ,
                                                                            bool reverseZ) SPATIAL_OVERLOADABLE {
    return SPProjectiveTransform3DMakeWithRightHandPerspective(fovY.radians, aspectRatio, nearZ, farZ, reverseZ);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.init(leftTangent:rightTangent:topTangent:bottomTangent:nearZ:farZ:reverseZ:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeFromTangents(double leftTangent,
                                                                double rightTangent,
                                                                double topTangent,
                                                                double bottomTangent,
                                                                double nearZ,
                                                                double farZ,
                                                                bool reverseZ){
    
    leftTangent = -leftTangent * nearZ;
    rightTangent = rightTangent * nearZ;
    topTangent = topTangent * nearZ;
    bottomTangent = -bottomTangent * nearZ;
    
    simd_double4x4 matrix = (simd_double4x4) {
        (simd_double4) { 2 * nearZ / (rightTangent - leftTangent), 0, 0, 0 },
        (simd_double4) { 0, 2 * nearZ / (topTangent - bottomTangent), 0, 0 },
        (simd_double4) { (rightTangent + leftTangent) / (rightTangent - leftTangent),
            (topTangent + bottomTangent) / (topTangent - bottomTangent), farZ / (nearZ - farZ), -1 },
        (simd_double4) { 0, 0, (farZ * nearZ) / (nearZ - farZ), 0}
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
    
    SPProjectiveTransform3D transform = { .matrix = matrix };
    
    return transform;
}

// MARK: - Querying transform properties

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.is3DProjection(self:))
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIs3DProjection(SPProjectiveTransform3D transform) {
    
    if (!SPProjectiveTransform3DIsAffine(transform)) {
        return 1;
    } else {
        return (transform.matrix.columns[0].z != 0 ||
                transform.matrix.columns[1].z != 0 ||
                transform.matrix.columns[2].z != 0);
    }
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsValid(SPProjectiveTransform3D transform) {
    return (simd_all(_sp_simd_isfinite(transform.matrix.columns[0])) &&
            simd_all(_sp_simd_isfinite(transform.matrix.columns[1])) &&
            simd_all(_sp_simd_isfinite(transform.matrix.columns[2])) &&
            simd_all(_sp_simd_isfinite(transform.matrix.columns[3])));
}

SPATIAL_SWIFT_NAME(getter:ProjectiveTransform3D.isAffine(self:))
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsAffine(SPProjectiveTransform3D transform) {
    
    return (transform.matrix.columns[0].w == 0 &&
            transform.matrix.columns[1].w == 0 &&
            transform.matrix.columns[2].w == 0 &&
            transform.matrix.columns[3].w == 1);
}

SPATIAL_SWIFT_NAME(getter:ProjectiveTransform3D.isIdentity(self:))
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsIdentity(SPProjectiveTransform3D transform) {
    
    return (simd_equal(transform.matrix.columns[0], (simd_double4){1, 0, 0, 0}) &&
            simd_equal(transform.matrix.columns[1], (simd_double4){0, 1, 0, 0}) &&
            simd_equal(transform.matrix.columns[2], (simd_double4){0, 0, 1, 0}) &&
            simd_equal(transform.matrix.columns[3], (simd_double4){0, 0, 0, 1}));
    
}

SPATIAL_SWIFT_NAME(getter:ProjectiveTransform3D.isTranslation(self:))
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsTranslation(SPProjectiveTransform3D transform) {
    
    return (simd_equal(transform.matrix.columns[0], (simd_double4){1, 0, 0, 0}) &&
            simd_equal(transform.matrix.columns[1], (simd_double4){0, 1, 0, 0}) &&
            simd_equal(transform.matrix.columns[2], (simd_double4){0, 0, 1, 0}) &&
            transform.matrix.columns[3].w == 1);
}

SPATIAL_SWIFT_NAME(getter:ProjectiveTransform3D.isRectilinear(self:))
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsRectilinear(SPProjectiveTransform3D transform) {
    
    bool isAffine = SPProjectiveTransform3DIsAffine(transform);
    
    if (isAffine) {
        SPAffineTransform3D affine = SPAffineTransform3DMakeWithProjective(transform);
        return SPAffineTransform3DIsRectilinear(affine);
    } else {
        return isAffine;
    }
}

SPATIAL_SWIFT_NAME(getter:ProjectiveTransform3D.isUniform(self:))
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsUniform(SPProjectiveTransform3D transform) {
    
    bool isAffine = SPProjectiveTransform3DIsAffine(transform);
    
    if (isAffine) {
        SPAffineTransform3D affine = SPAffineTransform3DMakeWithProjective(transform);
        return SPAffineTransform3DIsUniform(affine);
    } else {
        return isAffine;
    }
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsUniformOverDimensions(SPProjectiveTransform3D transform,
                                                     SPAxis dimensionFlags) {
    bool isAffine = SPProjectiveTransform3DIsAffine(transform);
    
    if (isAffine) {
        SPAffineTransform3D affine = SPAffineTransform3DMakeWithProjective(transform);
        return SPAffineTransform3DIsUniformOverDimensions(affine, dimensionFlags);
    } else {
        return isAffine;
    }
}

SPATIAL_SWIFT_NAME(getter:ProjectiveTransform3D.isInvertible(self:))
SPATIAL_OVERLOADABLE
bool SPProjectiveTransform3DIsInvertible(SPProjectiveTransform3D transform) {

    return simd_determinant(transform.matrix) != 0;
}

// MARK: - Deriving new transforms

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.concatenating(self:_:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DConcatenation(SPProjectiveTransform3D t1,
                                                             SPProjectiveTransform3D t2) {
    
    simd_double4x4 conatenatedMatrix = t1.matrix;
    
    if (SPProjectiveTransform3DIsAffine(t1) && SPProjectiveTransform3DIsTranslation(t1) &&
        SPProjectiveTransform3DIsAffine(t2) && SPProjectiveTransform3DIsTranslation(t2)) {
        
        // Both transforms are affine translations only, return sum of translate columns:
        conatenatedMatrix.columns[3].xyz = t1.matrix.columns[3].xyz + t2.matrix.columns[3].xyz;
        
    } else if (SPProjectiveTransform3DIsAffine(t1) &&
               simd_all(t1.matrix.columns[3].xyz == (simd_double3){0, 0, 0}) &&
               SPProjectiveTransform3DIsAffine(t2) &&
               simd_all(t2.matrix.columns[3].xyz == (simd_double3){0, 0, 0})) {
        
        // Both transforms are affine without translation, return 3x3 * 3x3:
        simd_double3x3 t1_3x3 = (simd_double3x3) {
            t1.matrix.columns[0].xyz,
            t1.matrix.columns[1].xyz,
            t1.matrix.columns[2].xyz } ;
        simd_double3x3 t2_3x3 = (simd_double3x3) {
            t2.matrix.columns[0].xyz,
            t2.matrix.columns[1].xyz,
            t2.matrix.columns[2].xyz } ;
        
        t1_3x3 = simd_mul(t1_3x3, t2_3x3);
        
        conatenatedMatrix = (simd_double4x4) {
            simd_make_double4(t1_3x3.columns[0], 0 ),
            simd_make_double4(t1_3x3.columns[1], 0 ),
            simd_make_double4(t1_3x3.columns[2], 0 ),
            (simd_double4) { 0, 0, 0, 1}
        };
    } else {
        
        // Return 4x4 * 4x4:
        conatenatedMatrix = simd_mul(t1.matrix,
                                     t2.matrix);
    }
    
    SPProjectiveTransform3D transform = { .matrix = conatenatedMatrix };
    
    return transform;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DInverted(SPProjectiveTransform3D transform) {

    if (!SPProjectiveTransform3DIsInvertible(transform)) {
        return SPProjectiveTransform3DInvalid;
    }
    
    simd_double4x4 inverse = simd_inverse(transform.matrix);
    
    return (SPProjectiveTransform3D){ .matrix = inverse };
}

// MARK: Extracting component transforms

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3D SPProjectiveTransform3DGetScale(SPProjectiveTransform3D transform) {
    
    simd_double4x4 p = transform.matrix;
    
    simd_double3 column0 = p.columns[0].xyz;
    simd_double3 column1 = p.columns[1].xyz;
    simd_double3 column2 = p.columns[2].xyz;
    simd_double3 column3 = p.columns[3].xyz;
    
    simd_double4x3 m = simd_matrix(column0,
                                   column1,
                                   column2,
                                   column3);
    
    SPAffineTransform3D affine = SPAffineTransform3DMakeWith4x3Matrix(m);
    
    return SPAffineTransform3DGetScale(affine);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPProjectiveTransform3DGetRotation(SPProjectiveTransform3D transform) {
    
    simd_double4x4 p = transform.matrix;
    
    simd_double3 column0 = p.columns[0].xyz;
    simd_double3 column1 = p.columns[1].xyz;
    simd_double3 column2 = p.columns[2].xyz;
    simd_double3 column3 = p.columns[3].xyz;
    
    simd_double4x3 m = simd_matrix(column0,
                                   column1,
                                   column2,
                                   column3);
    
    SPAffineTransform3D affine = SPAffineTransform3DMakeWith4x3Matrix(m);
    return SPAffineTransform3DGetRotation(affine);
    
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPProjectiveTransform3DGetTranslation(SPProjectiveTransform3D transform) {
    
    simd_double3 translation = transform.matrix.columns[3].xyz;
    
    return SPVector3DMakeWithVector(translation);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPProjectiveTransform3DGetOffset(SPProjectiveTransform3D transform) {
    
    simd_double3 translation = transform.matrix.columns[3].xyz;
    
    return SPVector3DMakeWithVector(translation);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
void SPProjectiveTransform3DSetOffset(SPProjectiveTransform3D *transform, SPVector3D offset) {
    
    SPProjectiveTransform3DSetTranslation(transform, offset);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
void SPProjectiveTransform3DSetTranslation(SPProjectiveTransform3D *transform, SPVector3D offset) {
    
    transform->matrix.columns[3].xyz = offset.vector;
}

// MARK: - Transform equality

bool SPProjectiveTransform3DAlmostEqualToTransform(SPProjectiveTransform3D t1,
                                                    SPProjectiveTransform3D t2) SPATIAL_OVERLOADABLE {
    
    return simd_almost_equal_elements(t1.matrix, t2.matrix, SPDefaultTolerance);
}

bool SPProjectiveTransform3DAlmostEqualToTransform(SPProjectiveTransform3D t1,
                                                    SPProjectiveTransform3D t2,
                                                    double tolerance) SPATIAL_OVERLOADABLE {
    
    return simd_almost_equal_elements(t1.matrix, t2.matrix, tolerance);
}

// MARK: - Applying transform

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DScaleBy(SPProjectiveTransform3D transform,
                                                       double x, double y, double z) {
    
    SPSize3D scale = SPSize3DMake(x, y, z);
    SPProjectiveTransform3D scaleTransform = SPProjectiveTransform3DMakeScale(scale);
    
    return SPProjectiveTransform3DConcatenation(transform, scaleTransform);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.scaled(self:by:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DScaleBySize(SPProjectiveTransform3D transform,
                                                           SPSize3D scale) {
    SPProjectiveTransform3D scaleTransform = SPProjectiveTransform3DMakeScale(scale);
    
    return SPProjectiveTransform3DConcatenation(transform, scaleTransform);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.uniformlyScaled(self:by:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DScaleUniform(SPProjectiveTransform3D transform,
                                                            double scale) {
    SPSize3D scaleSize = SPSize3DMake(scale, scale, scale);
    SPProjectiveTransform3D scaleTransform = SPProjectiveTransform3DMakeScale(scaleSize);
    
    return SPProjectiveTransform3DConcatenation(transform, scaleTransform);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DRotate(SPProjectiveTransform3D transform,
                                                      SPRotation3D rotation) {
    SPProjectiveTransform3D rotationTransform = SPProjectiveTransform3DMakeRotation(rotation);
    
    return SPProjectiveTransform3DConcatenation(transform, rotationTransform);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DRotateByQuaternion(SPProjectiveTransform3D transform,
                                                                  simd_quatd quaternion) {
    SPRotation3D rotation = SPRotation3DMakeWithQuaternion(quaternion);
    SPProjectiveTransform3D rotationTransform = SPProjectiveTransform3DMakeRotation(rotation);
    
    return SPProjectiveTransform3DConcatenation(transform, rotationTransform);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DTranslate(SPProjectiveTransform3D transform,
                                                         SPSize3D size) {
    SPProjectiveTransform3D translate = SPProjectiveTransform3DMakeTranslation(size);
    
    return SPProjectiveTransform3DConcatenation(transform, translate);
}

SPATIAL_SWIFT_NAME(ProjectiveTransform3D.translated(self:by:))
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DTranslate(SPProjectiveTransform3D transform,
                                                         SPVector3D offset) {
    SPProjectiveTransform3D translate = SPProjectiveTransform3DMakeTranslation(offset);
    
    return SPProjectiveTransform3DConcatenation(transform, translate);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DShear(SPProjectiveTransform3D transform,
                                                     SPAxis shearAxis,
                                                     double shearFactor0,
                                                     double shearFactor1) {
    
    SPProjectiveTransform3D shearTransform = SPProjectiveTransform3DMakeShear(shearAxis,
                                                                              shearFactor0,
                                                                              shearFactor1);
    return SPProjectiveTransform3DConcatenation(transform, shearTransform);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DFlip(SPProjectiveTransform3D transform,
                                                    SPAxis flipAxis) {
    if (!SPProjectiveTransform3DIsAffine(transform)) {
        return SPProjectiveTransform3DInvalid;
    }
    
    SPAffineTransform3D affine = SPAffineTransform3DMakeWithProjective(transform);
    affine = SPAffineTransform3DFlip(affine, flipAxis);
    
    return SPProjectiveTransform3DMakeWithAffine(affine);
}

// MARK: - make from pose

/*!
 @abstract Returns a new projective transform structure from the specified scaled pose structure.
 
 @param pose The source scaled pose.
 @returns A new projective transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithScaledPose(SPScaledPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithScaledPose(SPScaledPose3D pose) {
    
    return SPProjectiveTransform3DMake(SPSize3DMake(pose.scale, pose.scale, pose.scale),
                                       pose.rotation,
                                       SPVector3DMakeWithVector(pose.position.vector));
}

/*!
 @abstract Returns a new projective transform structure from the specified pose structure.

 @param pose The source pose.
 @returns A new projective transform structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithPose(SPPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPProjectiveTransform3D SPProjectiveTransform3DMakeWithPose(SPPose3D pose) {
    
    SPVector3D v = SPVector3DMakeWithVector(pose.position.vector);
    
    return SPProjectiveTransform3DMake(SPSize3DMake(1, 1, 1),
                                       pose.rotation,
                                       v);
    
}




#endif /* Spatial_SPProjectiveTransform3D_h */
