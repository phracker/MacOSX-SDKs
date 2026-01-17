#ifndef SPSphericalCoordinates3D_h
#define SPSphericalCoordinates3D_h

#include <Spatial/Structures.h>
#include <Spatial/SPAngle.h>

// MARK: - SPSphericalCoordinates3D ⇋ SPPoint3D

/*!
 @abstract Creates a spherical coordinates structure from the Cartesian coordinates represented by the specified Spatial point.
 
 @param xyz The source point.
 @returns A new spherical coordinates structure.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3D SPSphericalCoordinates3DMakeWithCartesianPoint(SPPoint3D xyz)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3D SPSphericalCoordinates3DMakeWithCartesianPoint(SPPoint3D xyz) {
    
    double radius = simd_length(xyz.vector);
    
    SPAngle inclination = SPAngleAsin(xyz.y / radius);
    inclination.radians = isnan(inclination.radians) ? 0.0 : inclination.radians;
    
    SPAngle azimuth = SPAngleAtan(xyz.x / xyz.z);
    azimuth.radians = isnan(azimuth.radians) ? 0.0 : azimuth.radians;
    
    return SPSphericalCoordinates3DMake(radius,
                                        inclination,
                                        azimuth);
}

// MARK: - SPSphericalCoordinates3D ⇋ simd conversion

/*!
 @abstract Creates a spherical coordinates structure from the Cartesian coordinates represented by the specified simd vector.
 
 @param xyz The source vector.
 @returns A new spherical coordinates structure.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3D SPSphericalCoordinates3DMakeWithCartesianVector(simd_double3 xyz)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3D SPSphericalCoordinates3DMakeWithCartesianVector(simd_double3 xyz) {
    
    return SPSphericalCoordinates3DMakeWithCartesianPoint(SPPoint3DMakeWithVector(xyz));
}


// MARK: - SPSphericalCoordinates3D ⇋ SPVector3D

/*!
 @abstract Creates a spherical coordinates structure from the Cartesian coordinates represented by the specified Spatial vector.
 
 @param xyz The source vector.
 @returns A new spherical coordinates structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3D SPSphericalCoordinates3DMakeWithCartesianVector(SPVector3D xyz)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3D SPSphericalCoordinates3DMakeWithCartesianVector(SPVector3D xyz) {
    
    return SPSphericalCoordinates3DMakeWithCartesianVector(xyz.vector);
}



#endif /* SPSphericalCoordinates3D_h */
