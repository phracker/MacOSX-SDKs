#ifndef Spatial_SPRotationAxis3D_h
#define Spatial_SPRotationAxis3D_h

#include <Spatial/Structures.h>

// MARK: - Public API

/*!
 @abstract Creates an axis with the specified components.
 
 @param x The x component.
 @param y The y component.
 @param z The z component.
 @returns A new rotation axis.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotationAxis3D SPRotationAxis3DMake(double x, double y, double z)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Creates an axis with components specified as a 3-element SIMD vector.
 
 @param xyz The source vector.
 @returns A new rotation axis.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotationAxis3D SPRotationAxis3DMakeWithVector(simd_double3 xyz)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Creates an axis with components specified as a Spatial vector.
 
 @param xyz The source vector.
 @returns A new rotation axis.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotationAxis3D SPRotationAxis3DMakeWithVector(SPVector3D xyz)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns the @p x, @p y, and @p z components of the axis expressed as a simd vector.
 
 @param axis The source axis.
 @returns A three-element vector that contains the axis values.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_double3 SPRotationAxis3DGetVector(SPRotationAxis3D axis)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Returns @p true if both rotation axes are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRotationAxis3DEqualToRotationAxis(SPRotationAxis3D axis1, SPRotationAxis3D axis2)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Header inline implementations

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotationAxis3D SPRotationAxis3DMake(double x, double y, double z) {
    return (SPRotationAxis3D){ .x = x, .y = y, .z = z };
  }

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotationAxis3D SPRotationAxis3DMakeWithVector(simd_double3 xyz) {
  return (SPRotationAxis3D){ .vector = xyz };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotationAxis3D SPRotationAxis3DMakeWithVector(SPVector3D xyz) {
  return (SPRotationAxis3D){ .vector = xyz.vector };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_double3 SPRotationAxis3DGetVector(SPRotationAxis3D axis) {
    return axis.vector;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRotationAxis3DEqualToRotationAxis(SPRotationAxis3D axis1, SPRotationAxis3D axis2) {
    return simd_equal(axis1.vector, axis2.vector);
}





#endif /* Spatial_SPRotationAxis3D_h */
