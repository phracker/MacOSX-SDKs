#ifndef Spatial_SPRect3D_h
#define Spatial_SPRect3D_h

#include <Spatial/Structures.h>
#include <Spatial/SPAffineTransform3D.h>
#include <Spatial/SPProjectiveTransform3D.h>
#include <Spatial/SPPoint3D.h>

// MARK: - Public API

// MARK: - Creating a rectangle

/*!
 @abstract Returns a rectangle at the specified origin.
 
 @param origin A point structure that specifies the origin of the rectangle.
 @param size A size structure that specifies the size of the rectangle.
 @returns A new rectangle stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMakeAtOrigin(SPPoint3D origin,
                              SPSize3D size)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Creates a rectangle at the specified center with the specified size.
/*!
 @abstract Returns a rectangle at the specified center.
 
 @param center A point structure that specifies the center of the rectangle.
 @param size A size structure that specifies the sie of the rectangle.
 @returns A new rectangle stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMakeAtCenter(SPPoint3D center,
                              SPSize3D size)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle at the specified origin using simd vectors.
 
 @param origin A three-element vector that specifies the origin of the rectangle.
 @param size A three-element vector that specifies the size of the rectangle.
 @returns A new rectangle stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMakeAtOriginWithVector(simd_double3 origin,
                                        simd_double3 size)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle at the specified origin using Spatial vectors.
 
 @param origin A Spatial vector that specifies the origin of the rectangle.
 @param size A Spatial vector that specifies the size of the rectangle.
 @returns A new rectangle stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMakeAtOriginWithVector(SPVector3D origin,
                                        SPVector3D size)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle at the specified center using simd vectors.
 
 @param center A three-element vector that specifies the center of the rectangle.
 @param size A three-element vector that specifies the size of the rectangle.
 @returns A new rectangle stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMakeAtCenterWithVector(simd_double3 center,
                                        simd_double3 size)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle at the specified center using Spatial vectors.
 
 @param center A Spatial vector that specifies the center of the rectangle.
 @param size A Spatial vector that specifies the size of the rectangle.
 @returns A new rectangle stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMakeAtCenterWithVector(SPVector3D center,
                                        SPVector3D size)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Working with points

/*!
 @abstract Returns a point with coordinates clamped to the specified rectangle.
 
 @param point The source point.
 @param rect A 3D rectangle that defines the volume to clamp the point.
 @returns A point that's clamped to the rectangle.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DClampToRect(SPPoint3D point, SPRect3D rect)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the rectangle contains any of the specified points.
 
 @param rect The rectangle.
 @param points The points.
 @param pointCount The number of points.
 @returns A Boolean value that indicates whether the rectangle contains any of the specified points.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRect3DContainsAnyPoint(SPRect3D rect,
                               const SPPoint3D *points, int pointCount)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the rectangle contains the point.
 
 @param rect The rectangle.
 @param other The point.
 @returns A Boolean value that indicates whether the rectangle contains the point.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRect3DContainsPoint(SPRect3D rect, SPPoint3D other)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle that's the bounding box of the specified points.
 
 @param points The source points.
 @param pointCount The number of points.
 @returns A new rectangle stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMakeBoundingFromPoints(SPPoint3D points[], int pointCount)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns the corner points of the specified rectangle.
 
 @param rect The 3D rectangle that provides the points.
 @param points An array of eight points that the function populates with the corner points.
 
 @discussion
 This function returns the vertices in a clockwise direction, starting from the origin:
 @code
     5-----6
     |     |
    1-----2  |
    |  |  |  |         y  z
    |  4--|--7         | /
    |     |            |/
    0-----3            +-- x
 @endcode
 For example, @p points[0] equals @p rect.origin, and @p points[6] is at @p rect.origin
 offset by @p rect.size.
 */

SPATIAL_INLINE
SPATIAL_OVERLOADABLE
void SPRect3DGetCornerPoints(SPRect3D rect, SPPoint3D points[])
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Querying rectangle properties

/*!
 @abstract Returns a point that represents the center of the rectangle.
 
 @param rect The source rectangle.
 @returns A point that represents the center of the rectangle.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPRect3DGetCenter(SPRect3D rect)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates if two or three of the dimensions are zero.
 
 @param rect The source rectangle.
 @returns A Boolean value that  that indicates if two or three of the dimensions are zero.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRect3DIsEmpty(SPRect3D rect)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns the distance between the origins of two rectangle.
 
 @param rect The first rectangle.
 @param other The second rectangle.
 @returns The distance between the two rectangle.
 */
SPATIAL_INLINE
double SPRect3DDistanceToRect(SPRect3D rect, SPRect3D other)
__API_DEPRECATED("This function is deprecated.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Returns the distance between the origins of two rectangle.
 
 @param rect The first rectangle.
 @param other The second rectangle.
 @returns The distance between the two rectangle.
 */
SPATIAL_INLINE
double SPRect3DDistanceBetweenOrigins(SPRect3D rect, SPRect3D other)
__API_DEPRECATED("This function is deprecated.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Returns the rotation around @p (0,0,0)  from the first rectangle to the second rectangle.
 
 @param rect The first rectangle.
 @param other The second rectangle.
 @returns A rotation structure that represents the rotation.
 */
SPATIAL_INLINE
SPRotation3D SPRect3DRotationToRect(SPRect3D rect, SPRect3D other)
__API_DEPRECATED("This function is deprecated.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Returns a point that represents the corner of the rectangle with smallest x-, y-, and z-coordinates.
 
 @param rect The source rectangle.
 @returns A point that represents the corner of the rectangle with smallest x-, y-, and z-coordinates.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPRect3DGetMinimum(SPRect3D rect)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a point that represents the corner of the rectangle with largest x-, y-, and z-coordinates.
 
 @param rect The source rectangle.
 @returns A point that represents the corner of the rectangle with largest x-, y-, and z-coordinates.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPRect3DGetMaximum(SPRect3D rect)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Returns @p true if both rectangles are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRect3DEqualToRect(SPRect3D rect1, SPRect3D rect2)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Deriving new rectangles

/*!
 @abstract Returns the smallest rectangle with integer coordinates that contains the source rectangle.
 
 @param rect The source rectangle.
 @returns The smallest rectangle with integer coordinates that contains the source rectangle.
 
 @discussion
 A rectangle with the smallest integer values for its origin and size that contains the source rectangle.
 That is, given a rectangle with fractional origin or size values, integral rounds the rectangle’s origin
 downward and its size upward to the nearest whole integers, such that the result contains the original
 rectangle.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DIntegral(SPRect3D rect)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a new rectangle with the size updated by the specified amount and the same center point.
 
 @param rect The source rectangle.
 @param dXYZ A size structure that specifies the inset amount.
 
 @discussion
 This function returns a new rectangle that's inset by the specified values on each axis.
 The origin value is offset by the distance specified by the @p dXYZ parameter.
 
 The size is adjusted by @p (2*dXYZ) , relative to the source rectangle. If the width, height, or depth
 are positive values, then the rectangle’s size is decreased on that dimension.  If width, height, or depth
 are negative values, the rectangle’s size is increased on that dimension.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DInset(SPRect3D rect, SPSize3D dXYZ)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns the smallest rectangle that contains two rectangles.
 
 @param rect The first rectangle.
 @param other The second rectangle.
 @returns A rectangle structure that is the smallest rectangle that contains two sizes.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DUnion(SPRect3D rect, SPRect3D other)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns the intersection of the two rectangles.
 
 @param rect The first rectangle.
 @param other The second rectangle.
 @returns A rectangle structure that is the intersection of the two rectangles.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DIntersection(SPRect3D rect, SPRect3D other)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Returns a rectangle with a positive width and height.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DStandardize(SPRect3D rect)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Transforming rectangles

/*!
 @abstract Returns a rectangle with dimensions scaled by the specified values.
 
 @param rect The source rectangle.
 @param x The scale value along the @p width dimension.
 @param y The scale value along the @p height dimension.
 @param z The scale value along the @p depth dimension.
 @returns A rectangle that's scaled by the specified values.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DScaleBy(SPRect3D rect, double x, double y, double z)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle with dimensions scaled by the specified size.
 
 @param rect The source rectangle.
 @param scale The scale value.
 @returns A rectangle that's scaled by the specified value.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DScaleBySize(SPRect3D rect, SPSize3D scale)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle with dimensions uniformly scaled by the specified value.
 
 @param rect The source rectangle.
 @param scale The scale value.
 @returns A rectangle that's uniformly scaled by the specified value.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DScaleUniform(SPRect3D rect, double scale)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle that's rotated by the specified quaternion around the origin.
 
 @param rect The source rectangle.
 @param quaternion The quaternion that defines the rotation.
 @returns A rectangle that's rotated by the specified rotation.
 @discussion
 This function is equivalent to calling @p SPRect3DRotateByQuaternionAroundPoint with a zero vector for the pivot.
 
 Because affine transforms do not preserve rectangles in general, this function returns the smallest rectangle that contains the transformed corner points of the `rect` parameter.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DRotateByQuaternion(SPRect3D rect, simd_quatd quaternion)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle that's rotated by the specified rotation around the origin.
 
 @param rect The source rectangle.
 @param rotation The rotation.
 @returns A rectangle that's rotated by the specified rotation.
 @discussion
 This function is equivalent to calling @p SPRect3DRotateAroundPoint with a zero vector
 for the pivot.
 
 Because affine transforms do not preserve rectangles in general, this function returns the smallest rectangle that contains the transformed corner points of the `rect` parameter.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DRotate(SPRect3D rect, SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle that's rotated by a rotation around a specified pivot.
 
 @param rect The source rectangle.
 @param rotation The rotation.
 @param pivot The center of rotation.
 @returns A point that's rotated by the specified rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DRotateAroundPoint(SPRect3D rect, SPRotation3D rotation, SPPoint3D pivot)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle that's rotated by a quaternion around a specified pivot.
 
 @param rect The source rectangle.
 @param quaternion The quaternion that defines the rotation.
 @param pivot The center of rotation.
 @returns A point that's rotated by the specified rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DRotateByQuaternionAroundPoint(SPRect3D rect, simd_quatd quaternion, SPPoint3D pivot)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle with an origin that is offset from that of the source rectangle.
 
 @param rect The source rectangle.
 @param offset A size structure that defines the offset.
 @returns A rectangle that's offset by the @p width, @p height, and @p depth of the size.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DTranslate(SPRect3D rect, SPSize3D offset)
__API_DEPRECATED("Use `SPVector3D` variant.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Returns a rectangle with an origin that is offset from that of the source rectangle.
 
 @param rect The source rectangle.
 @param offset A vector that defines the offset.
 @returns A rectangle that's offset by the @p x, @p y, and @p z of the vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DTranslate(SPRect3D rect, SPVector3D offset)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle that's transformed by the specified affine transform.
 
 @param rect The source rectangle.
 @param transform The affine transform that the function applies to the rectangle.
 @returns The transformed rectangle.
 @discussion Because affine transforms do not preserve rectangles in general, this function returns the smallest rectangle that contains the transformed corner points of the `rect` parameter. If the affine transform `transform` consists solely of scaling and translation operations, then the returned rectangle coincides with the rectangle constructed from the eight transformed corners.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DApplyAffineTransform(SPRect3D rect, SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle that's transformed by the specified projective transform.
 
 @param rect The source rectangle.
 @param transform The projective transform that the function applies to the rectangle.
 @returns The transformed rectangle.
 @discussion Because affine transforms do not preserve rectangles in general, this function returns the smallest rectangle that contains the transformed corner points of the `rect` parameter. If the affine transform `transform` consists solely of scaling and translation operations, then the returned rectangle coincides with the rectangle constructed from the eight transformed corners.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DApplyProjectiveTransform(SPRect3D rect,
                                          SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle that's transformed by the inverse of the specified affine transform.
 
 @param rect The source rectangle.
 @param transform The affine transform that the function unapplies to the rectangle.
 @returns The transformed rectangle.
 @note The transform must be rectilinear otherwise this function returns @p SPRect3DNull .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DUnapplyAffineTransform(SPRect3D rect,
                                        SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle that's transformed by the inverse of the specified projective transform.
 
 @param rect The source rectangle.
 @param transform The projective transform that the function unapplies to the rectangle.
 @returns The transformed rectangle.
 @note The transform must be rectilinear otherwise this function returns @p SPRect3DNull .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DUnapplyProjectiveTransform(SPRect3D rect,
                                            SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rectangle that's sheared over an axis by shear factors for the other two axes.
 
 @param rect The source rectangle.
 @param shearAxis The shear axis.
 @param shearFactor0 The first shear factor.
 @param shearFactor1 The second shear factor.
 @returns The transformed rectangle.
 @discussion
 When the shear axis is @p x , @p shearFactor0 is the @p y shear factor and @p shearFactor0 is the @p z shear factor.
 
 When the shear axis is @p y , @p shearFactor0 is the @p x  shear factor and @p shearFactor0 is the @p z shear factor.
 
 When the shear axis is @p z , @p shearFactor0 is the @p x  shear factor and @p shearFactor0 is the @p y shear factor.
 
 Because affine transforms do not preserve rectangles in general, this function returns the smallest rectangle that contains the transformed corner points of the rect parameter.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DShear(SPRect3D rect,
                       SPAxis shearAxis,
                       double shearFactor0,
                       double shearFactor1)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Volumetric operations

/*!
 @abstract Returns a Boolean value that indicates whether two rectangles intersect.
 
 @param rect The first rectangle.
 @param other The second rectangle.
 
 @returns A Boolean value that indicates whether two rectangles intersect.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRect3DIntersectsRect(SPRect3D rect, SPRect3D other)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the first rectangle contains the second rectangle.
 
 @param rect The first rectangle.
 @param other The second rectangle.
 @returns A Boolean value that indicates whether the first rectangle contains the second rectangle.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRect3DContainsRect(SPRect3D rect, SPRect3D other)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Header inline implementations

// MARK: - Creating a rectangle

SPATIAL_SWIFT_NAME(Rect3D.init(origin:size:))
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMakeAtOrigin(SPPoint3D origin,
                              SPSize3D size) {
    return (SPRect3D){ .origin = origin, .size = size };
}

SPATIAL_SWIFT_NAME(Rect3D.init(center:size:))
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMakeAtCenter(SPPoint3D center,
                              SPSize3D size) {
    
    return SPRect3DMakeAtCenterWithVector(center.vector,
                                          size.vector);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMakeAtOriginWithVector(simd_double3 origin,
                                        simd_double3 size) {
    
    return SPRect3DMakeAtOrigin(SPPoint3DMakeWithVector(origin),
                                SPSize3DMakeWithVector(size));
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMakeAtOriginWithVector(SPVector3D origin,
                                        SPVector3D size) {
    
    return SPRect3DMakeAtOrigin(SPPoint3DMakeWithVector(origin.vector),
                                SPSize3DMakeWithVector(size.vector));
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMakeAtCenterWithVector(simd_double3 center,
                                        simd_double3 size) {
    return SPRect3DMakeAtOriginWithVector(center - size/2, size);
}


SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMakeAtCenterWithVector(SPVector3D center,
                                        SPVector3D size) {
    return SPRect3DMakeAtOriginWithVector(center.vector - size.vector/2, size.vector);
}

// MARK: - Working with points

SPATIAL_SWIFT_NAME(Point3D.clamped(self:to:))
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DClampToRect(SPPoint3D point, SPRect3D rect) {
    
    rect = SPRect3DStandardize(rect);
    
    simd_double3 p = point.vector;
    
    simd_double3 clampMin = rect.origin.vector;
    
    simd_double3 clampMax = rect.origin.vector + rect.size.vector;
    
    p = simd_max(p, clampMin);
    p = simd_min(p, clampMax);
    
    return SPPoint3DMakeWithVector(p);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRect3DContainsAnyPoint(SPRect3D rect, const SPPoint3D *points, int pointCount) {
    for (int i=0; i<pointCount; i++) {
        if (SPRect3DContainsPoint(rect, points[i])) return 1;
    }
    return 0;
}

SPATIAL_SWIFT_NAME(Rect3D.contains(self:point:))
SPATIAL_OVERLOADABLE
bool SPRect3DContainsPoint(SPRect3D rect, SPPoint3D other) {
    simd_double3 r1_min = SPRect3DGetMinimum(rect).vector;
    simd_double3 r1_max = SPRect3DGetMaximum(rect).vector;
    
    simd_double3 p = other.vector;
    return simd_all((r1_min <= p) & (r1_max >= p));
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DMakeBoundingFromPoints(SPPoint3D points[], int pointCount) {
    if (pointCount == 0) { return (SPRect3D) { 0 }; }
    
    simd_double3 minimum =  INFINITY;
    simd_double3 maximum = -INFINITY;
    for (int i=0; i<pointCount; i++) {
        minimum = simd_min(minimum, points[i].vector);
        maximum = simd_max(maximum, points[i].vector);
    }
    
    simd_double3 size = maximum - minimum;
    
    return (SPRect3D) {
        SPPoint3DMakeWithVector(minimum),
        SPSize3DMakeWithVector(size)
    };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
void SPRect3DGetCornerPoints(SPRect3D rect, SPPoint3D points[]) {
    
    SPPoint3D origin = rect.origin;
    SPSize3D size = rect.size;
    
    for (int i = 0; i < 8; ++i) {
        points[i] = origin;
    }
    
    // front
    
    points[1].y += size.height;
    
    points[2].x += size.width;
    points[2].y += size.height;
    
    points[3].x += size.width;
    
    // back
    
    points[4].z += size.depth;
    
    points[5].y += size.height;
    points[5].z += size.depth;
    
    points[6].x += size.width;
    points[6].y += size.height;
    points[6].z += size.depth;
    
    points[7].x += size.width;
    points[7].z += size.depth;
}

// MARK: - Querying rectangle properties

SPATIAL_SWIFT_NAME(getter:Rect3D.center(self:))
SPATIAL_OVERLOADABLE
SPPoint3D SPRect3DGetCenter(SPRect3D rect) {
    
    simd_double3 size = rect.size.vector;
    
    return SPPoint3DMakeWithVector(rect.origin.vector + size/2);
}

SPATIAL_SWIFT_NAME(getter:Rect3D.isEmpty(self:))
SPATIAL_OVERLOADABLE
bool SPRect3DIsEmpty(SPRect3D rect) {
    simd_double3 size = rect.size.vector;
    
    return simd_reduce_add(size == 0) <= -2;
}

SPATIAL_REFINED_FOR_SWIFT
double SPRect3DDistanceToRect(SPRect3D rect, SPRect3D other) {
    return SPPoint3DDistanceToPoint(rect.origin, other.origin);
}

SPATIAL_REFINED_FOR_SWIFT
double SPRect3DDistanceBetweenOrigins(SPRect3D rect, SPRect3D other) {
    return SPPoint3DDistanceToPoint(rect.origin, other.origin);
}

SPATIAL_REFINED_FOR_SWIFT
SPRotation3D SPRect3DRotationToRect(SPRect3D rect, SPRect3D other) {
    return SPPoint3DRotationToPoint(rect.origin, other.origin);
}

SPATIAL_SWIFT_NAME(getter:Rect3D.min(self:))
SPATIAL_OVERLOADABLE
SPPoint3D SPRect3DGetMinimum(SPRect3D rect) {
    simd_double3 origin = rect.origin.vector;
    simd_double3 size = rect.size.vector;
    
    simd_double3 result = origin + simd_min(0, size);
    
    return SPPoint3DMakeWithVector(result);
}

SPATIAL_SWIFT_NAME(getter:Rect3D.max(self:))
SPATIAL_OVERLOADABLE
SPPoint3D SPRect3DGetMaximum(SPRect3D rect) {
    simd_double3 origin = rect.origin.vector;
    simd_double3 size = rect.size.vector;
    
    simd_double3 result = origin + simd_max(0, size);
    return SPPoint3DMakeWithVector(result);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRect3DEqualToRect(SPRect3D rect1, SPRect3D rect2) {
    
    return (SPPoint3DEqualToPoint(rect1.origin, rect2.origin) &&
            simd_equal(rect1.size.vector, rect2.size.vector));
}

// MARK: - Deriving new rectangles

SPATIAL_SWIFT_NAME(getter:Rect3D.integral(self:))
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DIntegral(SPRect3D rect) {
    rect = SPRect3DStandardize(rect);
    
    simd_double3 minimum = SPRect3DGetMinimum(rect).vector;
    simd_double3 maximum = SPRect3DGetMaximum(rect).vector;
    simd_double3 origin = _sp_simd_floor(minimum);
    simd_double3 size = _sp_simd_ceil(maximum) - origin;
    return SPRect3DMakeAtOriginWithVector(origin, size);
}

SPATIAL_SWIFT_NAME(Rect3D.inset(self:by:))
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DInset(SPRect3D rect, SPSize3D dXYZ) {
    rect = SPRect3DStandardize(rect);
    simd_double3 inset = dXYZ.vector;
    simd_double3 origin = rect.origin.vector + inset;
    simd_double3 size = rect.size.vector - 2*inset;
    return SPRect3DMakeAtOriginWithVector(origin, size);
}

SPATIAL_SWIFT_NAME(Rect3D.union(self:_:))
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DUnion(SPRect3D rect, SPRect3D other) {
    
    rect = SPRect3DStandardize(rect);
    other = SPRect3DStandardize(other);
    
    simd_double3 origin = simd_min(rect.origin.vector, other.origin.vector);
    
    simd_double3 size = simd_max(SPRect3DGetMaximum(rect).vector,
                                 SPRect3DGetMaximum(other).vector) - origin;
    
    return (SPRect3D){
        .origin = SPPoint3DMakeWithVector(origin),
        .size = SPSize3DMakeWithVector(size)
    };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DIntersection(SPRect3D rect, SPRect3D other) {
    
    rect = SPRect3DStandardize(rect);
    other = SPRect3DStandardize(other);
    
    simd_double3 origin = simd_max(rect.origin.vector, other.origin.vector);
    
    simd_double3 size = simd_min(SPRect3DGetMaximum(rect).vector,
                                 SPRect3DGetMaximum(other).vector) - origin;
    
    double minSize = simd_reduce_min(size);
    
    if (minSize >= 0) {
        return (SPRect3D){
            .origin = SPPoint3DMakeWithVector(origin),
            .size = SPSize3DMakeWithVector(size)
        };
    } else {
        return SPRect3DNull;
    }
}

SPATIAL_SWIFT_NAME(getter:Rect3D.standardized(self:))
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DStandardize(SPRect3D rect) {
    
    simd_double3 size = rect.size.vector;
    size = simd_abs(size);
    
    return (SPRect3D){
        .origin =  SPRect3DGetMinimum(rect),
        .size = SPSize3DMakeWithVector(size)
    };
}

// MARK: - Transforming rectangles

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DScaleBy(SPRect3D rect, double x, double y, double z) {
    simd_double3 scale = simd_make_double3(x, y, z);
    return SPRect3DMakeAtOriginWithVector(rect.origin.vector * scale,
                                          rect.size.vector * scale);
}

SPATIAL_SWIFT_NAME(Rect3D.scaled(self:by:))
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DScaleBySize(SPRect3D rect, SPSize3D scale) {
    simd_double3 vectorScale = scale.vector;
    return SPRect3DMakeAtOriginWithVector(rect.origin.vector * vectorScale,
                                          rect.size.vector * vectorScale);
}

SPATIAL_SWIFT_NAME(Rect3D.uniformlyScaled(self:by:))
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DScaleUniform(SPRect3D rect, double scale) {
    return SPRect3DMakeAtOriginWithVector(rect.origin.vector * scale,
                                          rect.size.vector * scale);
}

SPATIAL_SWIFT_NAME(Rect3D.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DRotate(SPRect3D rect, SPRotation3D rotation) {
    
    SPAffineTransform3D transform = SPAffineTransform3DMakeRotation(rotation);
    
    return SPRect3DApplyAffineTransform(rect, transform);
}

SPATIAL_SWIFT_NAME(Rect3D.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DRotateByQuaternion(SPRect3D rect, simd_quatd quaternion) {
    
    SPRotation3D rotation = SPRotation3DMakeWithQuaternion(quaternion);
    
    
    return SPRect3DRotate(rect, rotation);
}

SPATIAL_SWIFT_NAME(Rect3D.rotated(self:by:around:))
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DRotateAroundPoint(SPRect3D rect, SPRotation3D rotation, SPPoint3D pivot) {

    SPPoint3D points[8] = {0};
    
    SPRect3DGetCornerPoints(rect, points);
    
    for (int i = 0; i < 8; ++i) {
        points[i] = SPPoint3DRotateAroundPoint(points[i], rotation, pivot);
    }
    
    SPRect3D transformed = SPRect3DMakeBoundingFromPoints(points, 8);
    
    return transformed;
}

SPATIAL_SWIFT_NAME(Rect3D.rotated(self:by:around:))
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DRotateByQuaternionAroundPoint(SPRect3D rect, simd_quatd quaternion, SPPoint3D pivot) {
    
    SPRotation3D rotation = SPRotation3DMakeWithQuaternion(quaternion);

    return SPRect3DRotateAroundPoint(rect, rotation, pivot);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DTranslate(SPRect3D rect, SPSize3D offset) {
    SPVector3D v = SPVector3DMakeWithVector(offset.vector);
    return SPRect3DMakeAtOrigin(SPPoint3DTranslate(rect.origin, v), rect.size);
}

SPATIAL_SWIFT_NAME(Rect3D.translated(self:by:))
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DTranslate(SPRect3D rect, SPVector3D offset) {
    return SPRect3DMakeAtOrigin(SPPoint3DTranslate(rect.origin, offset), rect.size);
}

SPATIAL_SWIFT_NAME(Rect3D.applying(self:_:))
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DApplyAffineTransform(SPRect3D rect, SPAffineTransform3D transform) {
    
    SPPoint3D points[8] = {0};
    
    SPRect3DGetCornerPoints(rect, points);
    
    for (int i = 0; i < 8; ++i) {
        points[i] = SPPoint3DApplyAffineTransform(points[i], transform);
    }
    
    SPRect3D transformed = SPRect3DMakeBoundingFromPoints(points, 8);
    
    return transformed;
}

SPATIAL_SWIFT_NAME(Rect3D.applying(self:_:))
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DApplyProjectiveTransform(SPRect3D rect, SPProjectiveTransform3D transform){
    
    SPPoint3D points[8] = {0};
    
    SPRect3DGetCornerPoints(rect, points);
    
    for (int i = 0; i < 8; ++i) {
        points[i] = SPPoint3DApplyProjectiveTransform(points[i], transform);
    }
    
    SPRect3D transformed = SPRect3DMakeBoundingFromPoints(points, 8);
    
    return transformed;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DUnapplyAffineTransform(SPRect3D rect, SPAffineTransform3D transform) {
    
    if(!SPAffineTransform3DIsRectilinear(transform)) {
        return SPRect3DNull;
    }
    
    SPAffineTransform3D invertedTransform = SPAffineTransform3DInverted(transform);
    
    return SPRect3DApplyAffineTransform(rect, invertedTransform);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DUnapplyProjectiveTransform(SPRect3D rect, SPProjectiveTransform3D transform) {
    
    if(!SPProjectiveTransform3DIsRectilinear(transform)) {
        return SPRect3DNull;
    }
    
    SPProjectiveTransform3D invertedTransform = SPProjectiveTransform3DInverted(transform);
    
    return SPRect3DApplyProjectiveTransform(rect, invertedTransform);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DShear(SPRect3D rect,
                       SPAxis shearAxis,
                       double shearFactor0,
                       double shearFactor1) {
    
    SPAffineTransform3D shearTransform = SPAffineTransform3DMakeShear(shearAxis,
                                                                      shearFactor0,
                                                                      shearFactor1);
    
    return SPRect3DApplyAffineTransform(rect, shearTransform);
}

// MARK: - Volumetric operations

SPATIAL_SWIFT_NAME(Rect3D.contains(self:_:))
SPATIAL_OVERLOADABLE
bool SPRect3DContainsRect(SPRect3D rect, SPRect3D other) {
    
    simd_double3 r1_min = SPRect3DGetMinimum(rect).vector;
    simd_double3 r1_max = SPRect3DGetMaximum(rect).vector;
    
    simd_double3 r2_min = SPRect3DGetMinimum(other).vector;
    simd_double3 r2_max = SPRect3DGetMaximum(other).vector;
    
    return simd_all((r1_min <= r2_min) & (r1_max >= r2_max));
}

SPATIAL_SWIFT_NAME(Rect3D.intersects(self:_:))
SPATIAL_OVERLOADABLE
bool SPRect3DIntersectsRect(SPRect3D rect, SPRect3D other) {
    return !SPRect3DIsEmpty(SPRect3DIntersection(rect, other));
}

// MARK: - Transform by Pose

/*!
 @abstract Returns a rectangle that's transformed by the specified pose.
 
 @param rect The source rectangle.
 @param pose The pose that the function applies to the rectangle.
 @returns The transformed rectangle.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DApplyPose(SPRect3D rect,
                           SPPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DApplyPose(SPRect3D rect,
                           SPPose3D pose) {
    
    SPPoint3D points[8] = {0};
    
    SPRect3DGetCornerPoints(rect, points);
    
    for (int i = 0; i < 8; ++i) {
        
        points[i] = SPPoint3DApplyPose(points[i], pose);
    }
    
    SPRect3D transformed = SPRect3DMakeBoundingFromPoints(points, 8);
    
    return transformed;
}

/*!
 @abstract Returns a rectangle that's transformed by the inverse of the specified pose.
 
 @param rect The source rectangle.
 @param pose The pose that the function unapplies to the rectangle.
 @returns The transformed rectangle.
 @note The pose's rotation angle must be zero, otherwise this function returns @p SPRect3DNull .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DUnapplyPose(SPRect3D rect,
                             SPPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DUnapplyPose(SPRect3D rect,
                             SPPose3D pose) {
    
    if(fabs(simd_angle(pose.rotation.quaternion)) > SPDefaultTolerance) {
        return SPRect3DNull;
    }
    
    SPPoint3D points[8] = {0};
    
    SPRect3DGetCornerPoints(rect, points);
    
    for (int i = 0; i < 8; ++i) {
        points[i] = SPPoint3DUnapplyPose(points[i], pose);
    }
    
    SPRect3D transformed = SPRect3DMakeBoundingFromPoints(points, 8);
    
    return transformed;
}

// MARK: - Transform by Scaled Pose

/*!
 @abstract Returns a rectangle that's transformed by the specified scaled pose.
 
 @param rect The source rectangle.
 @param pose The scaled pose that the function applies to the rectangle.
 @returns The transformed rectangle.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DApplyScaledPose(SPRect3D rect,
                                 SPScaledPose3D pose)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DApplyScaledPose(SPRect3D rect,
                           SPScaledPose3D pose) {
    
    SPPoint3D points[8] = {0};
    
    SPRect3DGetCornerPoints(rect, points);
    
    for (int i = 0; i < 8; ++i) {
        
        points[i] = SPPoint3DApplyScaledPose(points[i], pose);
    }
    
    SPRect3D transformed = SPRect3DMakeBoundingFromPoints(points, 8);
    
    return transformed;
}

/*!
 @abstract Returns a rectangle that's transformed by the inverse of the specified scaled pose.
 
 @param rect The source rectangle.
 @param pose The scaled pose that the function unapplies to the rectangle.
 @returns The transformed rectangle.
 @note The pose's rotation angle must be zero, otherwise this function returns @p SPRect3DNull .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DUnapplyScaledPose(SPRect3D rect,
                                   SPScaledPose3D pose)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3D SPRect3DUnapplyScaledPose(SPRect3D rect,
                             SPScaledPose3D pose) {
    
    if(fabs(simd_angle(pose.rotation.quaternion)) > SPDefaultTolerance) {
        return SPRect3DNull;
    }
    
    SPPoint3D points[8] = {0};
    
    SPRect3DGetCornerPoints(rect, points);
    
    for (int i = 0; i < 8; ++i) {
        points[i] = SPPoint3DUnapplyScaledPose(points[i], pose);
    }
    
    SPRect3D transformed = SPRect3DMakeBoundingFromPoints(points, 8);
    
    return transformed;
}

#endif /* Spatial_SPRect3D_h */
