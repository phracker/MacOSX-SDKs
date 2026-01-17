#ifndef Spatial_Structures_Float_h
#define Spatial_Structures_Float_h

#include <Spatial/Base.h>
#include <simd/simd.h>
#include <stdbool.h>

// MARK: - SINGLE PRECISION

// MARK: - SPAngleFloat Structure

/// A single-precision geometric angle whose value you access in either radians or degrees.
typedef struct {
    /// The angle in radians.
    float radians;
} SPAngleFloat
SPATIAL_SWIFT_NAME(Angle2DFloat)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Axis Structure

/// A 3D axis.
typedef
union {
    struct {
        /// The x-axis value.
        SPATIAL_REFINED_FOR_SWIFT
        float x;
        
        /// The y-axis value.
        SPATIAL_REFINED_FOR_SWIFT
        float y;
        
        /// The z-axis value.
        SPATIAL_REFINED_FOR_SWIFT
        float z;
    };
    simd_float3 vector;
} SPRotationAxis3DFloat
__attribute__((__aligned__(16)))
SPATIAL_SWIFT_NAME(RotationAxis3DFloat)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Rotation Structure

/// A single-precision structure that represents a rotation in three dimensions.
typedef
union {
    struct {
        /// The underlying vector of the quaternion.
        simd_float4 vector;
    };
    simd_quatf quaternion;
} SPRotation3DFloat
__attribute__((__aligned__(16)))
SPATIAL_SWIFT_NAME(Rotation3DFloat)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - 3D Point Structure

/// A single-precision structure that contains a point in a three-dimensional coordinate system.
typedef
union {
    struct {
        /// The x-coordinate of the point.
        float x;
        
        /// The y-coordinate of the point.
        float y;
        
        /// The z-coordinate of the point.
        float z;
        
        /// The explicit padding
        float _padding
        SPATIAL_REFINED_FOR_SWIFT;
    };
    simd_float3 vector;
} SPPoint3DFloat
__attribute__((__aligned__(16)))
SPATIAL_SWIFT_NAME(Point3DFloat)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - 3D Vector Structure

/// A single-precision structure that defines a three-element vector
typedef
union {
    struct {
        /// The first element of the vector.
        float x;
        
        /// The second element of the vector.
        float y;
        
        /// The third element of the vector.
        float z;
        
        /// The explicit padding
        float _padding
        SPATIAL_REFINED_FOR_SWIFT;
    };
    simd_float3 vector;
} SPVector3DFloat
__attribute__((__aligned__(16)))
SPATIAL_SWIFT_NAME(Vector3DFloat)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - 3D Size Structure

/// A single-precision structure that contains width, height, and depth values.
typedef
union {
    struct {
        /// The width of the size.
        float width;
        
        /// The height of the size.
        float height;
        
        /// The depth of the size.
        float depth;
        
        /// The explicit padding
        float _padding
        SPATIAL_REFINED_FOR_SWIFT;
    };
    simd_float3 vector;
} SPSize3DFloat
__attribute__((__aligned__(16)))
SPATIAL_SWIFT_NAME(Size3DFloat)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - 3D Rectangle Structure

/// A single-precision structure that contains the location and dimensions of a 3D rectangle.
typedef struct {
    /// The origin of the rectangle.
    SPPoint3DFloat origin;
    
    /// The size of the rectangle.
   SPSize3DFloat size;
} SPRect3DFloat
SPATIAL_SWIFT_NAME(Rect3DFloat)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - 3D Ray Structure

/// A single-precision structure that contains the origin and direction of a 3D ray.
typedef struct {
    /// The origin of the ray.
    SPPoint3DFloat origin;
    
    /// The direction of the ray.
    SPVector3DFloat direction;
} SPRay3DFloat
SPATIAL_SWIFT_NAME(Ray3DFloat)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - 3D Pose Structure

/// A single-precision structure that contains a position and rotation.
typedef struct {
    /// The position
    SPPoint3DFloat position;
    
    /// The rotation
    SPRotation3DFloat rotation;
} SPPose3DFloat
SPATIAL_SWIFT_NAME(Pose3DFloat)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - 3D Scaled Pose Structure

/// A structure that contains a position, rotation, and scale.
typedef struct {
    /// The position
    SPPoint3DFloat position;
    
    /// The rotation
    SPRotation3DFloat rotation;

    /// The uniform scale
    float scale;
} SPScaledPose3DFloat
SPATIAL_SWIFT_NAME(ScaledPose3DFloat);
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - 3D Affine Transform Structure

/*!
 @abstract A single-precision 3D affine transformation matrix.
 
 @field matrix The 4x3 matrix that describes the affine transform.
 */
typedef struct {
    simd_float4x3 matrix;
} SPAffineTransform3DFloat
SPATIAL_SWIFT_NAME(AffineTransform3DFloat)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - 3D Projective Transform Structure

/// A single-precision 3D projective transformation matrix.
typedef struct {
    simd_float4x4 matrix;
} SPProjectiveTransform3DFloat
SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Spherical coordinates structure

/// A single-precision structure that defines spherical coordinates in radial, inclination, azimuthal order.
typedef
union {
    struct {
        /// The distance to the origin.
        float radius;
        
        /// The inclination angle.
        SPAngleFloat inclination;
        
        /// The azimuthal angle.
        SPAngleFloat azimuth;
        
        /// The explicit padding.
        float _padding;
    };
    simd_float3 vector;
} SPSphericalCoordinates3DFloat
__attribute__((__aligned__(16)))
SPATIAL_SWIFT_NAME(SphericalCoordinates3DFloat)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));


// MARK: - Fundamental make functions for SPPoint3D

/*!
 @abstract Creates a single-precision point with the specified coordinates.
 
 @param x The x coordinate.
 @param y The y coordinate.
 @param z The z coordinate.
 @returns A new point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatMake(float x, float y, float z)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatMake(float x, float y, float z) {
    return (SPPoint3DFloat) {
        x,
        y,
        z,
        1.0 };
}

/*!
 @abstract Creates a single-precision point with coordinates specified as a 3-element SIMD vector.
 
 @param xyz The source vector.
 @returns A new point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatMakeWithVector(simd_float3 xyz)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3DFloat SPPoint3DFloatMakeWithVector(simd_float3 xyz) {
    return SPPoint3DFloatMake(xyz.x, xyz.y, xyz.z);
}


// MARK: - Fundamental make functions for SPVector3D

/*!
 @abstract Creates a single-precision  vector with the specified coordinates.
 
 @param x The first element of the vector.
 @param y The second element of the vector.
 @param z The third element of the vector.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMake(float x, float y, float z)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMake(float x, float y, float z) {
    return (SPVector3DFloat) {
        x,
        y,
        z,
        0.0 };
}

/*!
 @abstract Creates a single-precision vector with elements specified as a 3-element SIMD vector.
 
 @param xyz The source simd vector.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMakeWithVector(simd_float3 xyz)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3DFloat SPVector3DFloatMakeWithVector(simd_float3 xyz) {
    return SPVector3DFloatMake(xyz.x, xyz.y, xyz.z);
}

// MARK: - Fundamental make functions for SPSize3D

/*!
 @abstract Creates a single-precision size structure with the specified dimensions.
 
 @param width The width.
 @param height The height.
 @param depth The depth.
 @returns A new size stucture.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatMake(float width, float height, float depth)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatMake(float width, float height, float depth) {
    return (SPSize3DFloat){
        width,
        height,
        depth,
        0.0 };
}

/*!
 @abstract Creates a single-precision size structure with dimensions specified as a 3-element SIMD vector.
 
 @param xyz The source vector.
 @returns A new size stucture.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatMakeWithVector(simd_float3 xyz)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPSize3DFloat SPSize3DFloatMakeWithVector(simd_float3 xyz) {
    return SPSize3DFloatMake(xyz.x, xyz.y, xyz.z);
}

/*!
 @abstract Creates a single-precision spherical coordinates structure.
 
 @param radius The distance to the origin.
 @param inclination The inclination angle.
 @param azimuth The azimuthal angle.
 @returns A new point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3DFloat SPSphericalCoordinates3DFloatMake(float radius, SPAngleFloat inclination, SPAngleFloat azimuth)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(SphericalCoordinates3DFloat.init(radius:inclination:azimuth:))
SPATIAL_OVERLOADABLE
SPSphericalCoordinates3DFloat SPSphericalCoordinates3DFloatMake(float radius, SPAngleFloat inclination, SPAngleFloat azimuth) {
    return (SPSphericalCoordinates3DFloat) {
        radius,
        inclination,
        azimuth,
        1.0 };
}

// MARK: - Special Values

/// The angle with the value zero.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_SWIFT_NAME(Angle2DFloat.zero)
static const SPAngleFloat SPAngleFloatZero  = { 0 };

/// The axis whose x, y, and z values are all zero.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_SWIFT_NAME(RotationAxis3DFloat.zero)
static const SPRotationAxis3DFloat SPRotationAxis3DFloatZero = { 0 };

/// The identity rotation.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_SWIFT_NAME(Rotation3DFloat.identity)
static const SPRotation3DFloat SPRotation3DFloatIdentity = (SPRotation3DFloat){ .vector = {0, 0, 0, 1 }};

/// A rotation that represents an invalid rotation.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_REFINED_FOR_SWIFT
static const SPRotation3DFloat SPRotation3DFloatInvalid = {
    { .vector = {INFINITY, INFINITY, INFINITY, INFINITY }}
};

/// A pose that represents an invalid pose.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_REFINED_FOR_SWIFT
static const SPPose3DFloat SPPose3DFloatInvalid = {
    .position = {INFINITY, INFINITY, INFINITY},
    .rotation = (SPRotation3DFloat){ .vector = {INFINITY, INFINITY, INFINITY, INFINITY }}
};

/// A pose that represents an invalid scaled pose.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_REFINED_FOR_SWIFT
static const SPScaledPose3DFloat SPScaledPose3DFloatInvalid = {
    .position = {INFINITY, INFINITY, INFINITY},
    .rotation = (SPRotation3DFloat){ .vector = {INFINITY, INFINITY, INFINITY, INFINITY }},
    .scale = INFINITY
};

/// The point with the value zero.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_SWIFT_NAME(Point3DFloat.zero)
static const SPPoint3DFloat SPPoint3DFloatZero = { 0, 0, 0, 1.0 };

/// The point with location @p (infinity,infinity,infinity) .
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_SWIFT_NAME(Point3DFloat.infinity)
static const SPPoint3DFloat SPPoint3DFloatInfinity = { INFINITY, INFINITY, INFINITY, 1.0 };

/// The vector with the value zero.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_SWIFT_NAME(Vector3DFloat.zero)
static const SPVector3DFloat SPVector3DFloatZero = { 0 };

/// The vector with values @p (infinity,infinity,infinity) .
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_SWIFT_NAME(Vector3DFloat.infinity)
static const SPVector3DFloat SPVector3DFloatInfinity = { INFINITY, INFINITY, INFINITY, 0 };

/// The size with the value zero.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_SWIFT_NAME(Size3DFloat.zero)
static const SPSize3DFloat SPSize3DFloatZero = { 0 };

/// The size with dimensions @p (infinity,infinity,infinity) .
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_SWIFT_NAME(Size3DFloat.infinity)
static const SPSize3DFloat SPSize3DFloatInfinity = { INFINITY, INFINITY, INFINITY, 0 };

/// A size that represents an invalid size.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_REFINED_FOR_SWIFT
static const SPSize3DFloat SPSize3DFloatInvalid = {
    INFINITY, INFINITY, INFINITY, 0
};

/// The rect with the value zero.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_SWIFT_NAME(Rect3DFloat.zero)
static const SPRect3DFloat SPRect3DFloatZero = { 0 };

/// The rect with dimensions @p (infinity,infinity,infinity) .
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_SWIFT_NAME(Rect3DFloat.infinity)
static const SPRect3DFloat SPRect3DFloatInfinity = {
    .origin = { INFINITY, INFINITY, INFINITY, 1.0 },
    .size = { INFINITY, INFINITY, INFINITY, 0.0 }
};

/// The null rectangle, that represents an invalid value.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_REFINED_FOR_SWIFT
static const SPRect3DFloat SPRect3DFloatNull = {
    .origin = { INFINITY, INFINITY, INFINITY, 1.0 },
    .size = { 0 }
};

/// The identity affine transform.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_SWIFT_NAME(AffineTransform3DFloat.identity)
static const SPAffineTransform3DFloat SPAffineTransform3DFloatIdentity = {
    .matrix = {
        (simd_float3){1, 0, 0},
        (simd_float3){0, 1, 0},
        (simd_float3){0, 0, 1},
        (simd_float3){0, 0, 0}
    }
};

/// An affine transform that represents an invalid transform.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_REFINED_FOR_SWIFT
static const SPAffineTransform3DFloat SPAffineTransform3DFloatInvalid = {
    (simd_float3) {INFINITY, INFINITY, INFINITY},
    (simd_float3) {INFINITY, INFINITY, INFINITY},
    (simd_float3) {INFINITY, INFINITY, INFINITY},
    (simd_float3) {INFINITY, INFINITY, INFINITY}
};

/// The identity projective transform.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_SWIFT_NAME(ProjectiveTransform3DFloat.identity)
static const SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatIdentity = {
    .matrix = {
        (simd_float4){1, 0, 0, 0},
        (simd_float4){0, 1, 0, 0},
        (simd_float4){0, 0, 1, 0},
        (simd_float4){0, 0, 0, 1}
    }
};

/// A projective transform that represents an invalid transform.
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
SPATIAL_REFINED_FOR_SWIFT
static const SPProjectiveTransform3DFloat SPProjectiveTransform3DFloatInvalid = {
    (simd_float4) {INFINITY, INFINITY, INFINITY, INFINITY},
    (simd_float4) {INFINITY, INFINITY, INFINITY, INFINITY},
    (simd_float4) {INFINITY, INFINITY, INFINITY, INFINITY},
    (simd_float4) {INFINITY, INFINITY, INFINITY, INFINITY}
};

// MARK: - Checking Special Values

/*!
 @abstract Returns a Boolean value that indicates whether the rotation axis is zero.
 
 @param axis The source rotation axis.
 @returns A Boolean value that indicates whether the rotation axis is zero.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRotationAxis3DFloatIsZero(SPRotationAxis3DFloat axis)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRotationAxis3DFloatIsZero(SPRotationAxis3DFloat axis) {
    simd_float3 p = (simd_float3){axis.x, axis.y, axis.z};
    return simd_equal(p, 0);
}

/*!
 @abstract Returns a Boolean value that indicates whether the point is zero.
 
 @param point The source point.
 @returns A Boolean value that indicates whether the point is zero.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPPoint3DFloatIsZero(SPPoint3DFloat point)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(getter:Point3DFloat.isZero(self:))
SPATIAL_OVERLOADABLE
bool SPPoint3DFloatIsZero(SPPoint3DFloat point) {
    simd_float3 p = (simd_float3){point.x, point.y, point.z};
    return simd_equal(p, 0);
}

/*!
 @abstract Returns a Boolean value that indicates whether all of the coordinates of the point are finite.
 
 @param point The source point.
 @returns A Boolean value that indicates whether all of the coordinates of the point are finite.
*/
SPATIAL_INLINE
bool SPPoint3DFloatIsFinite(SPPoint3DFloat point)
SPATIAL_OVERLOADABLE
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(getter:Point3DFloat.isFinite(self:))
SPATIAL_OVERLOADABLE
bool SPPoint3DFloatIsFinite(SPPoint3DFloat point) {
    simd_float3 p = (simd_float3){point.x, point.y, point.z};
    
    return simd_all(_sp_simd_isfinite(p));
}

/*!
 @abstract Returns a Boolean value that indicates whether the point contains any NaN values.
 
 @param point The source point.
 @returns A Boolean value that indicates whether the point contains any NaN values.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPPoint3DFloatIsNaN(SPPoint3DFloat point)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(getter:Point3DFloat.isNaN(self:))
SPATIAL_OVERLOADABLE
bool SPPoint3DFloatIsNaN(SPPoint3DFloat point) {
    simd_float3 p = (simd_float3){point.x, point.y, point.z};
    return simd_any(_sp_simd_isnan(p));
}

/*!
 @abstract Returns a Boolean value that indicates whether the vector is zero.
 
 @param vector The source vector.
 @returns A Boolean value that indicates whether the vector is zero.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPVector3DFloatIsZero(SPVector3DFloat vector)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(getter:Vector3DFloat.isZero(self:))
SPATIAL_OVERLOADABLE
bool SPVector3DFloatIsZero(SPVector3DFloat vector) {
    simd_float3 v = (simd_float3){vector.x, vector.y, vector.z};
    return simd_equal(v, 0);
}

/*!
 @abstract Returns a Boolean value that indicates whether all of the elements of the vector are finite.
 
 @param vector The source vector.
 @returns A Boolean value that indicates whether all of the coordinates of the point are finite.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPVector3DFloatIsFinite(SPVector3DFloat vector)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(getter:Vector3DFloat.isFinite(self:))
SPATIAL_OVERLOADABLE
bool SPVector3DFloatIsFinite(SPVector3DFloat vector) {
    simd_float3 v = (simd_float3){vector.x, vector.y, vector.z};
    
    return simd_all(_sp_simd_isfinite(v));
}

/*!
 @abstract Returns a Boolean value that indicates whether the vector contains any NaN values.
 
 @param vector The source point.
 @returns A Boolean value that indicates whether the point contains any NaN values.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPVector3DFloatIsNaN(SPVector3DFloat vector)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(getter:Vector3DFloat.isNaN(self:))
SPATIAL_OVERLOADABLE
bool SPVector3DFloatIsNaN(SPVector3DFloat vector) {
    simd_float3 v = (simd_float3){vector.x, vector.y, vector.z};
    return simd_any(_sp_simd_isnan(v));
}

/*!
 @abstract Returns a Boolean value that indicates whether the size is zero.
 
 @param size The source size.
 @returns A Boolean value that indicates whether the size is zero.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DFloatIsZero(SPSize3DFloat size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether all of the dimensions of the size are finite.
 
 @param size The source size.
 @returns A Boolean value that indicates whether all of the dimensions of the size are finite.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DFloatIsFinite(SPSize3DFloat size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns a Boolean value that indicates whether the size contains any NaN values.
 
 @param size The source size.
 @returns A Boolean value that indicates whether the size contains any NaN values.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DFloatIsNaN(SPSize3DFloat size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(getter:Size3DFloat.isZero(self:))
SPATIAL_OVERLOADABLE
bool SPSize3DFloatIsZero(SPSize3DFloat size) {
    simd_float3 v = (simd_float3){size.width, size.height, size.depth};
    return simd_equal(v, 0);
}

SPATIAL_SWIFT_NAME(getter:Size3DFloat.isFinite(self:))
SPATIAL_OVERLOADABLE
bool SPSize3DFloatIsFinite(SPSize3DFloat size) {
    simd_float3 v = (simd_float3){size.width, size.height, size.depth};
    return simd_all(_sp_simd_isfinite(v));
}

SPATIAL_SWIFT_NAME(getter:Size3DFloat.isNaN(self:))
SPATIAL_OVERLOADABLE
bool SPSize3DFloatIsNaN(SPSize3DFloat size) {
    simd_float3 v = (simd_float3){size.width, size.height, size.depth};
    return simd_any(_sp_simd_isnan(v));
}

/*!
 @abstract Returns a Boolean value that indicates whether a size structure represents a valid size.
 
 @param size The source size.
 @returns A Boolean value that indicates whether a size structure represents a valid size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DFloatIsValid(SPSize3DFloat size)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPSize3DFloatIsValid(SPSize3DFloat size) {
    return !(size.width == INFINITY &&
             size.height == INFINITY &&
             size.depth == INFINITY);
}

/*!
 @abstract Returns a Boolean value that indicates whether a rotation structure represents a valid rotation.
 
 @param rotation The source rotation.
 @returns A Boolean value that indicates whether a rotation structure represents a valid rotation.
*/
SPATIAL_INLINE
bool SPRotation3DFloatIsValid(SPRotation3DFloat rotation)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
bool SPRotation3DFloatIsValid(SPRotation3DFloat rotation) {

    return simd_all(_sp_simd_isfinite(rotation.quaternion.vector));
}

/*!
 @abstract Returns a Boolean value that indicates whether a pose structure represents a valid pose.
 
 @param pose The source pose.
 @returns A Boolean value that indicates whether a size structure represents a valid size.
*/
SPATIAL_INLINE
bool SPPose3DFloatIsValid(SPPose3DFloat pose)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
bool SPPose3DFloatIsValid(SPPose3DFloat pose) {
    return SPRotation3DFloatIsValid(pose.rotation) && SPPoint3DFloatIsFinite(pose.position);
}

/*!
 @abstract Returns a Boolean value that indicates whether a scaled pose structure represents a valid scaled pose.
 
 @param pose The source pose.
 @returns A Boolean value that indicates whether a scaled pose structure represents a valid size.
*/
SPATIAL_INLINE
bool SPScaledPose3DFloatIsValid(SPScaledPose3DFloat pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
bool SPScaledPose3DFloatIsValid(SPScaledPose3DFloat pose) {
    return SPRotation3DFloatIsValid(pose.rotation) && SPPoint3DFloatIsFinite(pose.position) && isnormal(pose.scale);
}

/*!
 @abstract Returns a Boolean value that indicates whether the rectangle represents an invalid value.
 
 @param rect The source rectangle.
 @returns A Boolean value that indicates whether the rectangle is invalid.
*/
SPATIAL_INLINE
bool SPRect3DFloatIsNull(SPRect3DFloat rect)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(getter:Rect3DFloat.isNull(self:))
bool SPRect3DFloatIsNull(SPRect3DFloat rect) {
    return SPSize3DFloatIsZero(rect.size) && !SPPoint3DFloatIsFinite(rect.origin);
}

/*!
 @abstract Returns a Boolean value that indicates whether the rectangle is zero.
 
 @param rect The source rectangle.
 @returns A Boolean value that indicates whether the rectangle is zero.
*/
SPATIAL_INLINE
bool SPRect3DFloatIsZero(SPRect3DFloat rect)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(getter:Rect3DFloat.isZero(self:))
bool SPRect3DFloatIsZero(SPRect3DFloat rect) {
    return SPPoint3DFloatIsZero(rect.origin) && SPSize3DFloatIsZero(rect.size);
}

/*!
 @abstract Returns a Boolean value that indicates whether all of the coordinates and dimensions of the rectangle are finite.
 
 @param rect The source rectangle.
 @returns A Boolean value that indicates whether all of the coordinates and dimensions of the rectangle are finite.
*/
SPATIAL_INLINE
bool SPRect3DFloatIsFinite(SPRect3DFloat rect)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(getter:Rect3DFloat.isFinite(self:))
bool SPRect3DFloatIsFinite(SPRect3DFloat rect) {
    return SPPoint3DFloatIsFinite(rect.origin) && SPSize3DFloatIsFinite(rect.size);
}

/*!
 @abstract Returns a Boolean value that indicates whether any of the coordinates and dimensions of the rectangle are NaN.
 
 @param rect The source rectangle.
 @returns A Boolean value that indicates whether any of the coordinates and dimensions of the rectangle are NaN.
*/
SPATIAL_INLINE
bool SPRect3DFloatIsNaN(SPRect3DFloat rect)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_SWIFT_NAME(getter:Rect3DFloat.isNaN(self:))
bool SPRect3DFloatIsNaN(SPRect3DFloat rect) {
    return SPPoint3DFloatIsNaN(rect.origin) || SPSize3DFloatIsNaN(rect.size);
}

#endif /* Spatial_Structures_h */
