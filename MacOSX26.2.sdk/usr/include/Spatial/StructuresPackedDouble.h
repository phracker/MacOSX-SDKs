#ifndef StructuresPackedDouble_h
#define StructuresPackedDouble_h

#include <Spatial/Structures.h>

// MARK: - POINT

/*!
 @abstract Creates a Spatial point from a packed simd vector.
 
 @param source The source vector.
 @returns A new point.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DMakeWithPackedVector(simd_packed_double4 source)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DMakeWithPackedVector(simd_packed_double4 source) {
    return SPPoint3DMake(source.x, source.y, source.z);
}

/*!
 @abstract Creates a packed simd vector from a Spatial point.
 
 @param point The source point.
 @returns A new packed simd vector .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_packed_double4 SPPoint3DGetPackedVector(SPPoint3D point)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_packed_double4 SPPoint3DGetPackedVector(SPPoint3D point) {
    return (simd_packed_double4){point.x, point.y, point.z, 1.0 }; // point._padding
}

// MARK: - VECTOR

/*!
 @abstract Creates a Spatial vector from a packed simd vector.
 
 @param source The source vector.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithPackedVector(simd_packed_double4 source)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithPackedVector(simd_packed_double4 source) {
    return SPVector3DMake(source.x, source.y, source.z);
}

/*!
 @abstract Creates a packed simd vector from a Spatial vector.
 
 @param vector The source vector.
 @returns A new packed simd vector .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_packed_double4 SPVector3DGetPackedVector(SPVector3D vector)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_packed_double4 SPVector3DGetPackedVector(SPVector3D vector) {
    return (simd_packed_double4){vector.x, vector.y, vector.z, 0.0 }; // vector._padding
}

// MARK: - SIZE

/*!
 @abstract Creates a Spatial size from a packed simd vector.
 
 @param source The source vector.
 @returns A new size.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DMakeWithPackedVector(simd_packed_double4 source)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3D SPSize3DMakeWithPackedVector(simd_packed_double4 source) {
    return SPSize3DMake(source.x, source.y, source.z);
}

/*!
 @abstract Creates a packed simd vector from a Spatial vector.
 
 @param size The source size.
 @returns A new packed simd vector .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_packed_double4 SPSize3DGetPackedVector(SPSize3D size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_packed_double4 SPSize3DGetPackedVector(SPSize3D size) {
    return (simd_packed_double4){size.width, size.height, size.depth, 0.0 }; // size._padding
}

// MARK: - SPSphericalCoordinates3D

/*!
 @abstract Creates a Spatial spherical coordinates structure from a packed simd vector.
 
 @param source The source vector, where `x` is the radius, `y` is the inclination (in radians), and `z` is the azimuth (in radians).
 
 @returns A new spherical coordinates structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3D SPSphericalCoordinates3DMakeWithPackedVector(simd_packed_double4 source)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3D SPSphericalCoordinates3DMakeWithPackedVector(simd_packed_double4 source) {
    
    return SPSphericalCoordinates3DMake(source.x,
                                             (SPAngle){ .radians = source.y },
                                             (SPAngle){ .radians = source.z });
}

/*!
 @abstract Creates a packed simd vector from a Spatial spherical coordinates structure.
 
 @param coords The source spherical coordinates structure.
 @returns A new packed simd vector, where `x` is the radius, `y` is the inclination (in radians), and `z` is the azimuth (in radians).
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_packed_double4 SPSphericalCoordinates3DGetPackedVector(SPSphericalCoordinates3D coords)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_packed_double4 SPSphericalCoordinates3DGetPackedVector(SPSphericalCoordinates3D coords) {
    
    return (simd_packed_double4) {
        coords.radius,
        coords.inclination.radians,
        coords.azimuth.radians,
        coords._padding
    };
}

// MARK: - SPRotation3D

/*!
 @abstract Creates a Spatial rotation structure from a packed simd vector.
 
 @param source The source vector that supplies the imaginary part of the quaternion from elements `0`, `1`, and `2`; and the real part from element `3`.
 
 @returns A new rotation structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeWithPackedVector(simd_packed_double4 source)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeWithPackedVector(simd_packed_double4 source) {
    
    simd_quatd q = simd_quaternion(source.x, source.y, source.z, source.w);
    
    return (SPRotation3D) { .quaternion = q };
}

/*!
 @abstract Creates a packed simd vector from a Spatial rotation structure.
 
 @param rotation The source rotation structure.
 @returns A new packed simd vector, where elements `0`, `1`, and `2` are the imaginary parts, and element `3` is the real part.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_packed_double4 SPRotation3DGetPackedVector(SPRotation3D rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_packed_double4 SPRotation3DGetPackedVector(SPRotation3D rotation) {
    
    return (simd_packed_double4) rotation.vector;
}

// MARK: - SPRotationAxis3D

/*!
 @abstract Creates a Spatial 3D rotation axis from a packed simd vector.
 
 @param source The source vector.
 @returns A new rotation axis.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotationAxis3D SPRotationAxis3DMakeWithPackedVector(simd_packed_double4 source)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotationAxis3D SPRotationAxis3DMakeWithPackedVector(simd_packed_double4 source) {
    return (SPRotationAxis3D){ .vector = source.xyz };
}

/*!
 @abstract Creates a packed simd vector from a Spatial 3D rotation axis.
 
 @param axis The source rotation axis.
 @returns A new packed simd vector .
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_packed_double4 SPRotationAxis3DGetPackedVector(SPRotationAxis3D axis)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_packed_double4 SPRotationAxis3DGetPackedVector(SPRotationAxis3D axis) {
    return (simd_packed_double4){axis.x, axis.y, axis.z, 0 };
}

#endif /* StructuresPackedDouble_h */
