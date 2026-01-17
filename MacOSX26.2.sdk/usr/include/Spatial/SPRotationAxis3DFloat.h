//
//  SPRotationAxis3DFloatFloat.h
//  Spatial_dylib
//
//  Created by Simon James Gladman on 16.11.2023.
//

#ifndef SPRotationAxis3DFloat_h
#define SPRotationAxis3DFloat_h

#include <Spatial/StructuresFloat.h>

// MARK: - SINGLE-PRECISION Public API

/*!
 @abstract Creates an axis with the specified components.
 
 @param x The x component.
 @param y The y component.
 @param z The z component.
 @returns A new rotation axis.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotationAxis3DFloat SPRotationAxis3DFloatMake(float x, float y, float z)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Creates an axis with components specified as a 3-element SIMD vector.
 
 @param xyz The source vector.
 @returns A new rotation axis.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotationAxis3DFloat SPRotationAxis3DFloatMakeWithVector(simd_float3 xyz)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Creates an axis with components specified as a Spatial vector.
 
 @param xyz The source vector.
 @returns A new rotation axis.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotationAxis3DFloat SPRotationAxis3DFloatMakeWithVector(SPVector3DFloat xyz)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns the @p x, @p y, and @p z components of the axis expressed as a simd vector.
 
 @param axis The source axis.
 @returns A three-element vector that contains the axis values.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_float3 SPRotationAxis3DFloatGetVector(SPRotationAxis3DFloat axis)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/// Returns @p true if both rotation axes are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRotationAxis3DFloatEqualToRotationAxis(SPRotationAxis3DFloat axis1, SPRotationAxis3DFloat axis2)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Header inline implementations

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotationAxis3DFloat SPRotationAxis3DFloatMake(float x, float y, float z) {
    return (SPRotationAxis3DFloat){ .x = x, .y = y, .z = z };
  }

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotationAxis3DFloat SPRotationAxis3DFloatMakeWithVector(simd_float3 xyz) {
  return (SPRotationAxis3DFloat){ .vector = xyz };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotationAxis3DFloat SPRotationAxis3DFloatMakeWithVector(SPVector3DFloat xyz) {
  return (SPRotationAxis3DFloat){ .vector = xyz.vector };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_float3 SPRotationAxis3DFloatGetVector(SPRotationAxis3DFloat axis) {
    return axis.vector;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRotationAxis3DFloatEqualToRotationAxis(SPRotationAxis3DFloat axis1, SPRotationAxis3DFloat axis2) {
    return simd_equal(axis1.vector, axis2.vector);
}

#endif /* SPRotationAxis3DFloat_h */
