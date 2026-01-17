#ifndef SPSphericalCoordinates3DFloat_h
#define SPSphericalCoordinates3DFloat_h

#include <Spatial/StructuresFloat.h>
#include <Spatial/SPAngleFloat.h>

// MARK: - SINGLE-PRECISION

// MARK: - SPSphericalCoordinates3DFloat ⇋ SPPoint3DFloat

/*!
 @abstract Creates a spherical coordinates structure from the Cartesian coordinates represented by the specified Spatial point.
 
 @param xyz The source point.
 @returns A new spherical coordinates structure.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3DFloat SPSphericalCoordinates3DFloatMakeWithCartesianPoint(SPPoint3DFloat xyz)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3DFloat SPSphericalCoordinates3DFloatMakeWithCartesianPoint(SPPoint3DFloat xyz) {
    
    float radius = simd_length(xyz.vector);
    
    SPAngleFloat inclination = SPAngleFloatAsin(xyz.y / radius);
    inclination.radians = isnan(inclination.radians) ? 0.0 : inclination.radians;
    
    SPAngleFloat azimuth = SPAngleFloatAtan(xyz.x / xyz.z);
    azimuth.radians = isnan(azimuth.radians) ? 0.0 : azimuth.radians;
    
    return SPSphericalCoordinates3DFloatMake(radius,
                                        inclination,
                                        azimuth);
}

// MARK: - SPSphericalCoordinates3DFloat ⇋ simd conversion

/*!
 @abstract Creates a spherical coordinates structure from the Cartesian coordinates represented by the specified simd vector.
 
 @param xyz The source vector.
 @returns A new spherical coordinates structure.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3DFloat SPSphericalCoordinates3DFloatMakeWithCartesianVector(simd_float3 xyz)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3DFloat SPSphericalCoordinates3DFloatMakeWithCartesianVector(simd_float3 xyz) {
    
    return SPSphericalCoordinates3DFloatMakeWithCartesianPoint(SPPoint3DFloatMakeWithVector(xyz));
}


// MARK: - SPSphericalCoordinates3DFloat ⇋ SPVector3DFloat

/*!
 @abstract Creates a spherical coordinates structure from the Cartesian coordinates represented by the specified Spatial vector.
 
 @param xyz The source vector.
 @returns A new spherical coordinates structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3DFloat SPSphericalCoordinates3DFloatMakeWithCartesianVector(SPVector3DFloat xyz)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3DFloat SPSphericalCoordinates3DFloatMakeWithCartesianVector(SPVector3DFloat xyz) {
    
    return SPSphericalCoordinates3DFloatMakeWithCartesianVector(xyz.vector);
}


#endif /* SPSphericalCoordinates3DFloat_h */
