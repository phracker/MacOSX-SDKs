#ifndef SPRect3DFloat_h
#define SPRect3DFloat_h

#include <Spatial/StructuresFloat.h>
#include <Spatial/SPAffineTransform3DFloat.h>
#include <Spatial/SPProjectiveTransform3DFloat.h>
#include <Spatial/SPPoint3DFloat.h>


// MARK: - SINGLE-PRECISION Public API

// MARK: - Creating a rectangle

/*!
 @abstract Returns a rectangle at the specified origin.
 
 @param origin A point structure that specifies the origin of the rectangle.
 @param size A size structure that specifies the size of the rectangle.
 @returns A new rectangle stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMakeAtOrigin(SPPoint3DFloat origin,
                                        SPSize3DFloat size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/// Creates a rectangle at the specified center with the specified size.
/*!
 @abstract Returns a rectangle at the specified center.
 
 @param center A point structure that specifies the center of the rectangle.
 @param size A size structure that specifies the sie of the rectangle.
 @returns A new rectangle stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMakeAtCenter(SPPoint3DFloat center,
                                        SPSize3DFloat size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle at the specified origin using simd vectors.
 
 @param origin A three-element vector that specifies the origin of the rectangle.
 @param size A three-element vector that specifies the size of the rectangle.
 @returns A new rectangle stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMakeAtOriginWithVector(simd_float3 origin,
                                                  simd_float3 size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle at the specified origin using Spatial vectors.
 
 @param origin A Spatial vector that specifies the origin of the rectangle.
 @param size A Spatial vector that specifies the size of the rectangle.
 @returns A new rectangle stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMakeAtOriginWithVector(SPVector3DFloat origin,
                                                  SPVector3DFloat size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle at the specified center using simd vectors.
 
 @param center A three-element vector that specifies the center of the rectangle.
 @param size A three-element vector that specifies the size of the rectangle.
 @returns A new rectangle stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMakeAtCenterWithVector(simd_float3 center,
                                                  simd_float3 size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle at the specified center using Spatial vectors.
 
 @param center A Spatial vector that specifies the center of the rectangle.
 @param size A Spatial vector that specifies the size of the rectangle.
 @returns A new rectangle stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMakeAtCenterWithVector(SPVector3DFloat center,
                                                  SPVector3DFloat size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Working with points

/*!
 @abstract Returns a point with coordinates clamped to the specified rectangle.
 
 @param point The source point.
 @param rect A 3DFloat rectangle that defines the volume to clamp the point.
 @returns A point that's clamped to the rectangle.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatClampToRect(SPPoint3DFloat point, SPRect3DFloat rect)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the rectangle contains any of the specified points.
 
 @param rect The rectangle.
 @param points The points.
 @param pointCount The number of points.
 @returns A Boolean value that indicates whether the rectangle contains any of the specified points.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRect3DFloatContainsAnyPoint(SPRect3DFloat rect,
                                   const SPPoint3DFloat *points, int pointCount)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the rectangle contains the point.
 
 @param rect The rectangle.
 @param other The point.
 @returns A Boolean value that indicates whether the rectangle contains the point.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRect3DFloatContainsPoint(SPRect3DFloat rect, SPPoint3DFloat other)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle that's the bounding box of the specified points.
 
 @param points The source points.
 @param pointCount The number of points.
 @returns A new rectangle stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMakeBoundingFromPoints(SPPoint3DFloat points[], int pointCount)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns the corner points of the specified rectangle.
 
 @param rect The 3DFloat rectangle that provides the points.
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
void SPRect3DFloatGetCornerPoints(SPRect3DFloat rect, SPPoint3DFloat points[])
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Querying rectangle properties

/*!
 @abstract Returns a point that represents the center of the rectangle.
 
 @param rect The source rectangle.
 @returns A point that represents the center of the rectangle.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPRect3DFloatGetCenter(SPRect3DFloat rect)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates if two or three of the dimensions are zero.
 
 @param rect The source rectangle.
 @returns A Boolean value that  that indicates if two or three of the dimensions are zero.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRect3DFloatIsEmpty(SPRect3DFloat rect)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a point that represents the corner of the rectangle with smallest x-, y-, and z-coordinates.
 
 @param rect The source rectangle.
 @returns A point that represents the corner of the rectangle with smallest x-, y-, and z-coordinates.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPRect3DFloatGetMinimum(SPRect3DFloat rect)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a point that represents the corner of the rectangle with largest x-, y-, and z-coordinates.
 
 @param rect The source rectangle.
 @returns A point that represents the corner of the rectangle with largest x-, y-, and z-coordinates.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPRect3DFloatGetMaximum(SPRect3DFloat rect)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/// Returns @p true if both rectangles are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRect3DFloatEqualToRect(SPRect3DFloat rect1, SPRect3DFloat rect2)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

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
SPRect3DFloat SPRect3DFloatIntegral(SPRect3DFloat rect)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

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
SPRect3DFloat SPRect3DFloatInset(SPRect3DFloat rect, SPSize3DFloat dXYZ)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns the smallest rectangle that contains two rectangles.
 
 @param rect The first rectangle.
 @param other The second rectangle.
 @returns A rectangle structure that is the smallest rectangle that contains two sizes.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatUnion(SPRect3DFloat rect, SPRect3DFloat other)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns the intersection of the two rectangles.
 
 @param rect The first rectangle.
 @param other The second rectangle.
 @returns A rectangle structure that is the intersection of the two rectangles.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatIntersection(SPRect3DFloat rect, SPRect3DFloat other)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/// Returns a rectangle with a positive width and height.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatStandardize(SPRect3DFloat rect)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

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
SPRect3DFloat SPRect3DFloatScaleBy(SPRect3DFloat rect, float x, float y, float z)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle with dimensions scaled by the specified size.
 
 @param rect The source rectangle.
 @param scale The scale value.
 @returns A rectangle that's scaled by the specified value.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatScaleBySize(SPRect3DFloat rect, SPSize3DFloat scale)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle with dimensions uniformly scaled by the specified value.
 
 @param rect The source rectangle.
 @param scale The scale value.
 @returns A rectangle that's uniformly scaled by the specified value.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatScaleUniform(SPRect3DFloat rect, float scale)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle that's rotated by the specified quaternion around the origin.
 
 @param rect The source rectangle.
 @param quaternion The quaternion that defines the rotation.
 @returns A rectangle that's rotated by the specified rotation.
 @discussion
 This function is equivalent to calling @p SPRect3DFloatRotateByQuaternionAroundPoint with a zero vector for the pivot.
 
 Because affine transforms do not preserve rectangles in general, this function returns the smallest rectangle that contains the transformed corner points of the `rect` parameter.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatRotateByQuaternion(SPRect3DFloat rect, simd_quatf quaternion)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle that's rotated by the specified rotation around the origin.
 
 @param rect The source rectangle.
 @param rotation The rotation.
 @returns A rectangle that's rotated by the specified rotation.
 @discussion
 This function is equivalent to calling @p SPRect3DFloatRotateAroundPoint with a zero vector
 for the pivot.
 
 Because affine transforms do not preserve rectangles in general, this function returns the smallest rectangle that contains the transformed corner points of the `rect` parameter.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatRotate(SPRect3DFloat rect, SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle that's rotated by a rotation around a specified pivot.
 
 @param rect The source rectangle.
 @param rotation The rotation.
 @param pivot The center of rotation.
 @returns A point that's rotated by the specified rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatRotateAroundPoint(SPRect3DFloat rect, SPRotation3DFloat rotation, SPPoint3DFloat pivot)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle that's rotated by a quaternion around a specified pivot.
 
 @param rect The source rectangle.
 @param quaternion The quaternion that defines the rotation.
 @param pivot The center of rotation.
 @returns A point that's rotated by the specified rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatRotateByQuaternionAroundPoint(SPRect3DFloat rect, simd_quatf quaternion, SPPoint3DFloat pivot)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle with an origin that is offset from that of the source rectangle.
 
 @param rect The source rectangle.
 @param offset A vector that defines the offset.
 @returns A rectangle that's offset by the @p x, @p y, and @p z of the vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatTranslate(SPRect3DFloat rect, SPVector3DFloat offset)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle that's transformed by the specified affine transform.
 
 @param rect The source rectangle.
 @param transform The affine transform that the function applies to the rectangle.
 @returns The transformed rectangle.
 @discussion Because affine transforms do not preserve rectangles in general, this function returns the smallest rectangle that contains the transformed corner points of the `rect` parameter. If the affine transform `transform` consists solely of scaling and translation operations, then the returned rectangle coincides with the rectangle constructed from the eight transformed corners.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatApplyAffineTransform(SPRect3DFloat rect, SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle that's transformed by the specified projective transform.
 
 @param rect The source rectangle.
 @param transform The projective transform that the function applies to the rectangle.
 @returns The transformed rectangle.
 @discussion Because affine transforms do not preserve rectangles in general, this function returns the smallest rectangle that contains the transformed corner points of the `rect` parameter. If the affine transform `transform` consists solely of scaling and translation operations, then the returned rectangle coincides with the rectangle constructed from the eight transformed corners.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatApplyProjectiveTransform(SPRect3DFloat rect,
                                                    SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle that's transformed by the inverse of the specified affine transform.
 
 @param rect The source rectangle.
 @param transform The affine transform that the function unapplies to the rectangle.
 @returns The transformed rectangle.
 @note The transform must be rectilinear otherwise this function returns @p SPRect3DFloatNull .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatUnapplyAffineTransform(SPRect3DFloat rect,
                                                  SPAffineTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a rectangle that's transformed by the inverse of the specified projective transform.
 
 @param rect The source rectangle.
 @param transform The projective transform that the function unapplies to the rectangle.
 @returns The transformed rectangle.
 @note The transform must be rectilinear otherwise this function returns @p SPRect3DFloatNull .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatUnapplyProjectiveTransform(SPRect3DFloat rect,
                                                      SPProjectiveTransform3DFloat transform)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

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
SPRect3DFloat SPRect3DFloatShear(SPRect3DFloat rect,
                                 SPAxis shearAxis,
                                 float shearFactor0,
                                 float shearFactor1)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Volumetric operations

/*!
 @abstract Returns a Boolean value that indicates whether two rectangles intersect.
 
 @param rect The first rectangle.
 @param other The second rectangle.
 
 @returns A Boolean value that indicates whether two rectangles intersect.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRect3DFloatIntersectsRect(SPRect3DFloat rect, SPRect3DFloat other)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the first rectangle contains the second rectangle.
 
 @param rect The first rectangle.
 @param other The second rectangle.
 @returns A Boolean value that indicates whether the first rectangle contains the second rectangle.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRect3DFloatContainsRect(SPRect3DFloat rect, SPRect3DFloat other)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Header inline implementations

// MARK: - Creating a rectangle

SPATIAL_SWIFT_NAME(Rect3DFloat.init(origin:size:))
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMakeAtOrigin(SPPoint3DFloat origin,
                                        SPSize3DFloat size) {
    return (SPRect3DFloat){ .origin = origin, .size = size };
}

SPATIAL_SWIFT_NAME(Rect3DFloat.init(center:size:))
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMakeAtCenter(SPPoint3DFloat center,
                                        SPSize3DFloat size) {
    
    return SPRect3DFloatMakeAtCenterWithVector(center.vector,
                                               size.vector);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMakeAtOriginWithVector(simd_float3 origin,
                                                  simd_float3 size) {
    
    return SPRect3DFloatMakeAtOrigin(SPPoint3DFloatMakeWithVector(origin),
                                     SPSize3DFloatMakeWithVector(size));
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMakeAtOriginWithVector(SPVector3DFloat origin,
                                                  SPVector3DFloat size) {
    
    return SPRect3DFloatMakeAtOrigin(SPPoint3DFloatMakeWithVector(origin.vector),
                                     SPSize3DFloatMakeWithVector(size.vector));
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMakeAtCenterWithVector(simd_float3 center,
                                                  simd_float3 size) {
    return SPRect3DFloatMakeAtOriginWithVector(center - size/2, size);
}


SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMakeAtCenterWithVector(SPVector3DFloat center,
                                                  SPVector3DFloat size) {
    return SPRect3DFloatMakeAtOriginWithVector(center.vector - size.vector/2, size.vector);
}

// MARK: - Working with points

SPATIAL_SWIFT_NAME(Point3DFloat.clamped(self:to:))
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatClampToRect(SPPoint3DFloat point, SPRect3DFloat rect) {
    
    rect = SPRect3DFloatStandardize(rect);
    
    simd_float3 p = point.vector;
    
    simd_float3 clampMin = rect.origin.vector;
    
    simd_float3 clampMax = rect.origin.vector + rect.size.vector;
    
    p = simd_max(p, clampMin);
    p = simd_min(p, clampMax);
    
    return SPPoint3DFloatMakeWithVector(p);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRect3DFloatContainsAnyPoint(SPRect3DFloat rect, const SPPoint3DFloat *points, int pointCount) {
    for (int i=0; i<pointCount; i++) {
        if (SPRect3DFloatContainsPoint(rect, points[i])) return 1;
    }
    return 0;
}

SPATIAL_SWIFT_NAME(Rect3DFloat.contains(self:point:))
SPATIAL_OVERLOADABLE
bool SPRect3DFloatContainsPoint(SPRect3DFloat rect, SPPoint3DFloat other) {
    simd_float3 r1_min = SPRect3DFloatGetMinimum(rect).vector;
    simd_float3 r1_max = SPRect3DFloatGetMaximum(rect).vector;
    
    simd_float3 p = other.vector;
    return simd_all((r1_min <= p) & (r1_max >= p));
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatMakeBoundingFromPoints(SPPoint3DFloat points[], int pointCount) {
    if (pointCount == 0) { return (SPRect3DFloat) { 0 }; }
    
    simd_float3 minimum =  INFINITY;
    simd_float3 maximum = -INFINITY;
    for (int i=0; i<pointCount; i++) {
        minimum = simd_min(minimum, points[i].vector);
        maximum = simd_max(maximum, points[i].vector);
    }
    
    simd_float3 size = maximum - minimum;
    
    return (SPRect3DFloat) {
        SPPoint3DFloatMakeWithVector(minimum),
        SPSize3DFloatMakeWithVector(size)
    };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
void SPRect3DFloatGetCornerPoints(SPRect3DFloat rect, SPPoint3DFloat points[]) {
    
    SPPoint3DFloat origin = rect.origin;
    SPSize3DFloat size = rect.size;
    
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

SPATIAL_SWIFT_NAME(getter:Rect3DFloat.center(self:))
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPRect3DFloatGetCenter(SPRect3DFloat rect) {
    
    simd_float3 size = rect.size.vector;
    
    return SPPoint3DFloatMakeWithVector(rect.origin.vector + size/2);
}

SPATIAL_SWIFT_NAME(getter:Rect3DFloat.isEmpty(self:))
SPATIAL_OVERLOADABLE
bool SPRect3DFloatIsEmpty(SPRect3DFloat rect) {
    simd_float3 size = rect.size.vector;
    
    return simd_reduce_add(size == 0) <= -2;
}

SPATIAL_SWIFT_NAME(getter:Rect3DFloat.min(self:))
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPRect3DFloatGetMinimum(SPRect3DFloat rect) {
    simd_float3 origin = rect.origin.vector;
    simd_float3 size = rect.size.vector;
    
    simd_float3 result = origin + simd_min(0, size);
    
    return SPPoint3DFloatMakeWithVector(result);
}

SPATIAL_SWIFT_NAME(getter:Rect3DFloat.max(self:))
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPRect3DFloatGetMaximum(SPRect3DFloat rect) {
    simd_float3 origin = rect.origin.vector;
    simd_float3 size = rect.size.vector;
    
    simd_float3 result = origin + simd_max(0, size);
    return SPPoint3DFloatMakeWithVector(result);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRect3DFloatEqualToRect(SPRect3DFloat rect1, SPRect3DFloat rect2) {
    
    return (SPPoint3DFloatEqualToPoint(rect1.origin, rect2.origin) &&
            simd_equal(rect1.size.vector, rect2.size.vector));
}

// MARK: - Deriving new rectangles

SPATIAL_SWIFT_NAME(getter:Rect3DFloat.integral(self:))
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatIntegral(SPRect3DFloat rect) {
    rect = SPRect3DFloatStandardize(rect);
    
    simd_float3 minimum = SPRect3DFloatGetMinimum(rect).vector;
    simd_float3 maximum = SPRect3DFloatGetMaximum(rect).vector;
    simd_float3 origin = _sp_simd_floor(minimum);
    simd_float3 size = _sp_simd_ceil(maximum) - origin;
    return SPRect3DFloatMakeAtOriginWithVector(origin, size);
}

SPATIAL_SWIFT_NAME(Rect3DFloat.inset(self:by:))
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatInset(SPRect3DFloat rect, SPSize3DFloat dXYZ) {
    rect = SPRect3DFloatStandardize(rect);
    simd_float3 inset = dXYZ.vector;
    simd_float3 origin = rect.origin.vector + inset;
    simd_float3 size = rect.size.vector - 2*inset;
    return SPRect3DFloatMakeAtOriginWithVector(origin, size);
}

SPATIAL_SWIFT_NAME(Rect3DFloat.union(self:_:))
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatUnion(SPRect3DFloat rect, SPRect3DFloat other) {
    
    rect = SPRect3DFloatStandardize(rect);
    other = SPRect3DFloatStandardize(other);
    
    simd_float3 origin = simd_min(rect.origin.vector, other.origin.vector);
    
    simd_float3 size = simd_max(SPRect3DFloatGetMaximum(rect).vector,
                                SPRect3DFloatGetMaximum(other).vector) - origin;
    
    return (SPRect3DFloat){
        .origin = SPPoint3DFloatMakeWithVector(origin),
        .size = SPSize3DFloatMakeWithVector(size)
    };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatIntersection(SPRect3DFloat rect, SPRect3DFloat other) {
    
    rect = SPRect3DFloatStandardize(rect);
    other = SPRect3DFloatStandardize(other);
    
    simd_float3 origin = simd_max(rect.origin.vector, other.origin.vector);
    
    simd_float3 size = simd_min(SPRect3DFloatGetMaximum(rect).vector,
                                SPRect3DFloatGetMaximum(other).vector) - origin;
    
    float minSize = simd_reduce_min(size);
    
    if (minSize >= 0) {
        return (SPRect3DFloat){
            .origin = SPPoint3DFloatMakeWithVector(origin),
            .size = SPSize3DFloatMakeWithVector(size)
        };
    } else {
        return SPRect3DFloatNull;
    }
}

SPATIAL_SWIFT_NAME(getter:Rect3DFloat.standardized(self:))
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatStandardize(SPRect3DFloat rect) {
    
    simd_float3 size = rect.size.vector;
    size = simd_abs(size);
    
    return (SPRect3DFloat){
        .origin =  SPRect3DFloatGetMinimum(rect),
        .size = SPSize3DFloatMakeWithVector(size)
    };
}

// MARK: - Transforming rectangles

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatScaleBy(SPRect3DFloat rect, float x, float y, float z) {
    simd_float3 scale = simd_make_float3(x, y, z);
    return SPRect3DFloatMakeAtOriginWithVector(rect.origin.vector * scale,
                                               rect.size.vector * scale);
}

SPATIAL_SWIFT_NAME(Rect3DFloat.scaled(self:by:))
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatScaleBySize(SPRect3DFloat rect, SPSize3DFloat scale) {
    simd_float3 vectorScale = scale.vector;
    return SPRect3DFloatMakeAtOriginWithVector(rect.origin.vector * vectorScale,
                                               rect.size.vector * vectorScale);
}

SPATIAL_SWIFT_NAME(Rect3DFloat.uniformlyScaled(self:by:))
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatScaleUniform(SPRect3DFloat rect, float scale) {
    return SPRect3DFloatMakeAtOriginWithVector(rect.origin.vector * scale,
                                               rect.size.vector * scale);
}

SPATIAL_SWIFT_NAME(Rect3DFloat.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatRotate(SPRect3DFloat rect, SPRotation3DFloat rotation) {
    
        SPAffineTransform3DFloat transform = SPAffineTransform3DFloatMakeRotation(rotation);
        
        return SPRect3DFloatApplyAffineTransform(rect, transform);
}

SPATIAL_SWIFT_NAME(Rect3DFloat.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatRotateByQuaternion(SPRect3DFloat rect, simd_quatf quaternion) {
    
    SPRotation3DFloat rotation = SPRotation3DFloatMakeWithQuaternion(quaternion);
    
    
    return SPRect3DFloatRotate(rect, rotation);
}

SPATIAL_SWIFT_NAME(Rect3DFloat.rotated(self:by:around:))
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatRotateAroundPoint(SPRect3DFloat rect, SPRotation3DFloat rotation, SPPoint3DFloat pivot) {
    
    SPPoint3DFloat points[8] = {0};
    
    SPRect3DFloatGetCornerPoints(rect, points);
    
    for (int i = 0; i < 8; ++i) {
        points[i] = SPPoint3DFloatRotateAroundPoint(points[i], rotation, pivot);
    }
    
    SPRect3DFloat transformed = SPRect3DFloatMakeBoundingFromPoints(points, 8);
    
    return transformed;
}

SPATIAL_SWIFT_NAME(Rect3DFloat.rotated(self:by:around:))
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatRotateByQuaternionAroundPoint(SPRect3DFloat rect, simd_quatf quaternion, SPPoint3DFloat pivot) {
    
    SPRotation3DFloat rotation = SPRotation3DFloatMakeWithQuaternion(quaternion);
    
    return SPRect3DFloatRotateAroundPoint(rect, rotation, pivot);
}

SPATIAL_SWIFT_NAME(Rect3DFloat.translated(self:by:))
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatTranslate(SPRect3DFloat rect, SPVector3DFloat offset) {
    return SPRect3DFloatMakeAtOrigin(SPPoint3DFloatTranslate(rect.origin, offset), rect.size);
}

SPATIAL_SWIFT_NAME(Rect3DFloat.applying(self:_:))
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatApplyAffineTransform(SPRect3DFloat rect, SPAffineTransform3DFloat transform) {
    
    SPPoint3DFloat points[8] = {0};
    
    SPRect3DFloatGetCornerPoints(rect, points);
    
    for (int i = 0; i < 8; ++i) {
        points[i] = SPPoint3DFloatApplyAffineTransform(points[i], transform);
    }
    
    SPRect3DFloat transformed = SPRect3DFloatMakeBoundingFromPoints(points, 8);
    
    return transformed;
}

SPATIAL_SWIFT_NAME(Rect3DFloat.applying(self:_:))
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatApplyProjectiveTransform(SPRect3DFloat rect, SPProjectiveTransform3DFloat transform){
    
    SPPoint3DFloat points[8] = {0};
    
    SPRect3DFloatGetCornerPoints(rect, points);
    
    for (int i = 0; i < 8; ++i) {
        points[i] = SPPoint3DFloatApplyProjectiveTransform(points[i], transform);
    }
    
    SPRect3DFloat transformed = SPRect3DFloatMakeBoundingFromPoints(points, 8);
    
    return transformed;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatUnapplyAffineTransform(SPRect3DFloat rect, SPAffineTransform3DFloat transform) {
    
        if(!SPAffineTransform3DFloatIsRectilinear(transform)) {
            return SPRect3DFloatNull;
        }
        
        SPAffineTransform3DFloat invertedTransform = SPAffineTransform3DFloatInverted(transform);
        
        return SPRect3DFloatApplyAffineTransform(rect, invertedTransform);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatUnapplyProjectiveTransform(SPRect3DFloat rect, SPProjectiveTransform3DFloat transform) {
    
        if(!SPProjectiveTransform3DFloatIsRectilinear(transform)) {
            return SPRect3DFloatNull;
        }
        
        SPProjectiveTransform3DFloat invertedTransform = SPProjectiveTransform3DFloatInverted(transform);
        
        return SPRect3DFloatApplyProjectiveTransform(rect, invertedTransform);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatShear(SPRect3DFloat rect,
                                 SPAxis shearAxis,
                                 float shearFactor0,
                                 float shearFactor1) {
    
        SPAffineTransform3DFloat shearTransform = SPAffineTransform3DFloatMakeShear(shearAxis,
                                                                          shearFactor0,
                                                                          shearFactor1);
        
        return SPRect3DFloatApplyAffineTransform(rect, shearTransform);
}

// MARK: - Volumetric operations

SPATIAL_SWIFT_NAME(Rect3DFloat.contains(self:_:))
SPATIAL_OVERLOADABLE
bool SPRect3DFloatContainsRect(SPRect3DFloat rect, SPRect3DFloat other) {
    
    simd_float3 r1_min = SPRect3DFloatGetMinimum(rect).vector;
    simd_float3 r1_max = SPRect3DFloatGetMaximum(rect).vector;
    
    simd_float3 r2_min = SPRect3DFloatGetMinimum(other).vector;
    simd_float3 r2_max = SPRect3DFloatGetMaximum(other).vector;
    
    return simd_all((r1_min <= r2_min) & (r1_max >= r2_max));
}

SPATIAL_SWIFT_NAME(Rect3DFloat.intersects(self:_:))
SPATIAL_OVERLOADABLE
bool SPRect3DFloatIntersectsRect(SPRect3DFloat rect, SPRect3DFloat other) {
    return !SPRect3DFloatIsEmpty(SPRect3DFloatIntersection(rect, other));
}

// MARK: - Transform by Pose

/*!
 @abstract Returns a rectangle that's transformed by the specified pose.
 
 @param rect The source rectangle.
 @param pose The pose that the function applies to the size.
 @returns The transformed rectangle.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatApplyPose(SPRect3DFloat rect,
                                     SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatApplyPose(SPRect3DFloat rect,
                                     SPPose3DFloat pose) {
    
    SPPoint3DFloat points[8] = {0};
    
    SPRect3DFloatGetCornerPoints(rect, points);
    
    for (int i = 0; i < 8; ++i) {
        
        points[i] = SPPoint3DFloatApplyPose(points[i], pose);
    }
    
    SPRect3DFloat transformed = SPRect3DFloatMakeBoundingFromPoints(points, 8);
    
    return transformed;
}

/*!
 @abstract Returns a rectangle that's transformed by the inverse of the specified pose.
 
 @param rect The source rectangle.
 @param pose The pose that the function unapplies to the size.
 @returns The transformed rectangle.
 @note The pose's rotation angle must be zero, otherwise this function returns @p SPRect3DFloatNull .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatUnapplyPose(SPRect3DFloat rect,
                                       SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatUnapplyPose(SPRect3DFloat rect,
                                       SPPose3DFloat pose) {
    
    if(fabs(simd_angle(pose.rotation.quaternion)) > SPDefaultToleranceFloat) {
        return SPRect3DFloatNull;
    }
    
    SPPoint3DFloat points[8] = {0};
    
    SPRect3DFloatGetCornerPoints(rect, points);
    
    for (int i = 0; i < 8; ++i) {
        points[i] = SPPoint3DFloatUnapplyPose(points[i], pose);
    }
    
    SPRect3DFloat transformed = SPRect3DFloatMakeBoundingFromPoints(points, 8);
    
    return transformed;
}

/*!
 @abstract Returns a rectangle that's transformed by the specified scaled pose.
 
 @param rect The source rectangle.
 @param pose The scaled pose that the function applies to the rectangle.
 @returns The transformed rectangle.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatApplyScaledPose(SPRect3DFloat rect,
                                           SPScaledPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatApplyScaledPose(SPRect3DFloat rect,
                                           SPScaledPose3DFloat pose) {
    
    SPPoint3DFloat points[8] = {0};
    
    SPRect3DFloatGetCornerPoints(rect, points);
    
    for (int i = 0; i < 8; ++i) {
        
        points[i] = SPPoint3DFloatApplyScaledPose(points[i], pose);
    }
    
    SPRect3DFloat transformed = SPRect3DFloatMakeBoundingFromPoints(points, 8);
    
    return transformed;
}

/*!
 @abstract Returns a rectangle that's transformed by the inverse of the specified scaled pose.
 
 @param rect The source rectangle.
 @param pose The scaled pose that the function unapplies to the rectangle.
 @returns The transformed rectangle.
 @note The pose's rotation angle must be zero, otherwise this function returns @p SPRect3DFloatNull .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatUnapplyScaledPose(SPRect3DFloat rect,
                                             SPScaledPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRect3DFloat SPRect3DFloatUnapplyScaledPose(SPRect3DFloat rect,
                                             SPScaledPose3DFloat pose) {
    
    if(fabs(simd_angle(pose.rotation.quaternion)) > SPDefaultTolerance) {
        return SPRect3DFloatNull;
    }
    
    SPPoint3DFloat points[8] = {0};
    
    SPRect3DFloatGetCornerPoints(rect, points);
    
    for (int i = 0; i < 8; ++i) {
        points[i] = SPPoint3DFloatUnapplyScaledPose(points[i], pose);
    }
    
    SPRect3DFloat transformed = SPRect3DFloatMakeBoundingFromPoints(points, 8);
    
    return transformed;
}

#endif /* SPRect3DFloat_h */
