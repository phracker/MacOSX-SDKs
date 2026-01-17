#ifndef StucturesPackedFloat_h
#define StucturesPackedFloat_h

#include <Spatial/StructuresFloat.h>

// MARK: - POINT

/*!
 @abstract Creates a Spatial point from a packed simd vector.
 
 @param source The source vector.
 @returns A new point.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatMakeWithPackedVector(simd_packed_float4 source)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatMakeWithPackedVector(simd_packed_float4 source) {
    return SPPoint3DFloatMake(source.x, source.y, source.z);
}

/*!
 @abstract Creates a packed simd vector from a Spatial point.
 
 @param point The source point.
 @returns A new packed simd vector .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_packed_float4 SPPoint3DFloatGetPackedVector(SPPoint3DFloat point)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_packed_float4 SPPoint3DFloatGetPackedVector(SPPoint3DFloat point) {
    return (simd_packed_float4){point.x, point.y, point.z, point._padding };
}

// MARK: - VECTOR

/*!
 @abstract Creates a Spatial vector from a packed simd vector.
 
 @param source The source vector.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMakeWithPackedVector(simd_packed_float4 source)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMakeWithPackedVector(simd_packed_float4 source) {
    return SPVector3DFloatMake(source.x, source.y, source.z);
}

/*!
 @abstract Creates a packed simd vector from a Spatial vector.
 
 @param vector The source vector.
 @returns A new packed simd vector .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_packed_float4 SPVector3DFloatGetPackedVector(SPVector3DFloat vector)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_packed_float4 SPVector3DFloatGetPackedVector(SPVector3DFloat vector) {
    return (simd_packed_float4){vector.x, vector.y, vector.z, vector._padding };
}

// MARK: - SIZE

/*!
 @abstract Creates a Spatial size from a packed simd vector.
 
 @param source The source vector.
 @returns A new size.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatMakeWithPackedVector(simd_packed_float4 source)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatMakeWithPackedVector(simd_packed_float4 source) {
    return SPSize3DFloatMake(source.x, source.y, source.z);
}

/*!
 @abstract Creates a packed simd vector from a Spatial vector.
 
 @param size The source size.
 @returns A new packed simd vector .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_packed_float4 SPSize3DFloatGetPackedVector(SPSize3DFloat size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_packed_float4 SPSize3DFloatGetPackedVector(SPSize3DFloat size) {
    return (simd_packed_float4){size.width, size.height, size.depth, size._padding };
}

// MARK: - SPSphericalCoordinates3DFloat

/*!
 @abstract Creates a Spatial spherical coordinates structure from a packed simd vector.
 
 @param source The source vector, where `x` is the radius, `y` is the inclination (in radians), and `z` is the azimuth (in radians).
 
 @returns A new spherical coordinates structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3DFloat SPSphericalCoordinates3DFloatMakeWithPackedVector(simd_packed_float4 source)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3DFloat SPSphericalCoordinates3DFloatMakeWithPackedVector(simd_packed_float4 source) {
    
    return SPSphericalCoordinates3DFloatMake(source.x,
                                             (SPAngleFloat){ .radians = source.y },
                                             (SPAngleFloat){ .radians = source.z });
}

/*!
 @abstract Creates a packed simd vector from a Spatial spherical coordinates structure.
 
 @param coords The source spherical coordinates structure.
 @returns A new packed simd vector, where `x` is the radius, `y` is the inclination (in radians), and `z` is the azimuth (in radians).
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_packed_float4 SPSphericalCoordinates3DFloatGetPackedVector(SPSphericalCoordinates3DFloat coords)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_packed_float4 SPSphericalCoordinates3DFloatGetPackedVector(SPSphericalCoordinates3DFloat coords) {
    
    return (simd_packed_float4) {
        coords.radius,
        coords.inclination.radians,
        coords.azimuth.radians,
        coords._padding
    };
}

// MARK: - SPRotation3DFloat

/*!
 @abstract Creates a Spatial rotation structure from a packed simd vector.
 
 @param source The source vector that supplies the imaginary part of the quaternion from elements `0`, `1`, and `2`; and the real part from element `3`.
 
 @returns A new rotation structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMakeWithPackedVector(simd_packed_float4 source)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3DFloat SPRotation3DFloatMakeWithPackedVector(simd_packed_float4 source) {
    
    simd_quatf q = simd_quaternion(source.x, source.y, source.z, source.w);
    
    return (SPRotation3DFloat) { .quaternion = q };
}

/*!
 @abstract Creates a packed simd vector from a Spatial rotation structure.
 
 @param rotation The source rotation structure.
 @returns A new packed simd vector, where elements `0`, `1`, and `2` are the imaginary parts, and element `3` is the real part.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_packed_float4 SPRotation3DFloatGetPackedVector(SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_packed_float4 SPRotation3DFloatGetPackedVector(SPRotation3DFloat rotation) {
    
    return (simd_packed_float4) rotation.vector;
}

// MARK: - SPRotationAxis3DFloat

/*!
 @abstract Creates a Spatial 3D rotation axis from a packed simd vector.
 
 @param source The source vector.
 @returns A new rotation axis.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotationAxis3DFloat SPRotationAxis3DFloatMakeWithPackedVector(simd_packed_float4 source)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotationAxis3DFloat SPRotationAxis3DFloatMakeWithPackedVector(simd_packed_float4 source) {
    return (SPRotationAxis3DFloat){ .vector = source.xyz };
}

/*!
 @abstract Creates a packed simd vector from a Spatial 3D rotation axis.
 
 @param axis The source rotation axis.
 @returns A new packed simd vector .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_packed_float4 SPRotationAxis3DFloatGetPackedVector(SPRotationAxis3DFloat axis)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_packed_float4 SPRotationAxis3DFloatGetPackedVector(SPRotationAxis3DFloat axis) {
    return (simd_packed_float4){axis.x, axis.y, axis.z, 0 };
}

#endif /* StucturesPackedFloat_h */
