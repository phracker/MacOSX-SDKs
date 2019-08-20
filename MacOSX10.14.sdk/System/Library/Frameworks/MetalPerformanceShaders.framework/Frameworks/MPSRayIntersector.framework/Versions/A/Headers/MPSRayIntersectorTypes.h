/*!
 *  @header MPSRayIntersectorTypes.h
 *  @framework MPSRayIntersector.framework
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 *
 *  @discussion MPSRayIntersector type definitions shared between the host and device.
 */

#ifndef MPSRayIntersectorTypes_h
#define MPSRayIntersectorTypes_h

#define MPS_ALWAYS_INLINE __attribute__((always_inline)) inline

#ifdef __METAL_VERSION__
#include <metal_stdlib>

using namespace metal;

typedef packed_float3 MPSPackedFloat3;
#else
#import <Metal/Metal.h>
#import <simd/simd.h>
#import <MPSCore/MPSCoreTypes.h>

typedef struct _MPSPackedFloat3 {
    union {
        struct {
            float x;
            float y;
            float z;
        };
        float elements[3];
    };

#ifdef __cplusplus
    MPS_ALWAYS_INLINE _MPSPackedFloat3()
        : x(0.0f), y(0.0f), z(0.0f)
    {
    }

    MPS_ALWAYS_INLINE _MPSPackedFloat3(float x, float y, float z)
        : x(x), y(y), z(z)
    {
    }

    MPS_ALWAYS_INLINE _MPSPackedFloat3(vector_float3 xyz)
        : x(xyz.x), y(xyz.y), z(xyz.z)
    {
    }

    MPS_ALWAYS_INLINE operator vector_float3() const {
        return (vector_float3){ x, y, z };
    }

    MPS_ALWAYS_INLINE float & operator[](int idx) {
        return elements[idx];
    }

    MPS_ALWAYS_INLINE const float & operator[](int idx) const {
        return elements[idx];
    }
#endif
} MPSPackedFloat3;
#endif

/**
 * @brief An axis aligned bounding box with a min and max point
 */
typedef struct _MPSAxisAlignedBoundingBox {
    /**
     * @brief Minimum point
     */
    vector_float3 min;

    /**
     * @brief Maximum point
     */
    vector_float3 max;

#ifdef __cplusplus
    MPS_ALWAYS_INLINE _MPSAxisAlignedBoundingBox()
        : min(INFINITY),
          max(-INFINITY)
    {
    }

    MPS_ALWAYS_INLINE _MPSAxisAlignedBoundingBox(vector_float3 p)
        : min(p),
          max(p)
    {
    }

    MPS_ALWAYS_INLINE _MPSAxisAlignedBoundingBox(vector_float3 min, vector_float3 max)
        : min(min),
          max(max)
    {
    }
#endif
} MPSAxisAlignedBoundingBox;

/**
 * @brief Represents a 3D ray with an origin and a direction
 *
 * @discussion This type is available from the Metal Shading Language by including the
 * MetalPerformanceShaders/MetalPerformanceShaders.h header.
 */
typedef struct {
    /**
     * @brief Ray origin. The intersection test will be skipped if the origin contains NaNs
     * or infinities.
     */
    vector_float3 origin;

    /**
     * @brief Ray direction. Does not need to be normalized. The intersection test will be
     * skipped if the direction has length zero or contains NaNs or infinities.
     */
    vector_float3 direction;
} MPSRayOriginDirection;

/**
 * @brief Represents a 3D ray with an origin, a direction, and an intersection
 * distance range from the origin
 *
 * @discussion This type is available from the Metal Shading Language by including the
 * MetalPerformanceShaders/MetalPerformanceShaders.h header.
 */
typedef struct {
    /**
     * @brief Ray origin. The intersection test will be skipped if the origin contains NaNs
     * or infinities.
     */
    MPSPackedFloat3 origin;

    /**
     * @brief Minimum intersection distance from the origin along the ray direction. The
     * intersection test will be skipped if the minimum distance is equal to positive
     * infinity or NaN.
     */
    float minDistance;

    /**
     * @brief Ray direction. Does not need to be normalized. The intersection test will be
     * skipped if the direction has length zero or contains NaNs or infinities.
     */
    MPSPackedFloat3 direction;

    /**
     * @brief Maximum intersection distance from the origin along the ray direction. May be
     * infinite. The intersection test will be skipped if the maximum distance is less than
     * zero, NaN, or less than the minimum intersection distance.
     */
    float maxDistance;
} MPSRayOriginMinDistanceDirectionMaxDistance;

/**
 * @brief Represents a 3D ray with an origin, a direction, and a mask to filter out intersections
 *
 * @discussion This type is available from the Metal Shading Language by including the
 * MetalPerformanceShaders/MetalPerformanceShaders.h header.
 */
typedef struct {
    /**
     * @brief Ray origin. The intersection test will be skipped if the origin contains NaNs
     * or infinities.
     */
    MPSPackedFloat3 origin;

    /**
     * @brief Ray mask which is bitwise AND-ed with instance and primitive masks to filter out
     * intersections. The intersection test will be skipped if the mask is zero.
     */
    unsigned int mask;

    /**
     * @brief Ray direction. Does not need to be normalized. The intersection test will be
     * skipped if the direction has length zero or contains NaNs or infinities.
     */
    MPSPackedFloat3 direction;

    /**
     * @brief Maximum intersection distance from the origin along the ray direction. May be
     * infinite. The intersection test will be skipped if the maximum distance is less than
     * zero or NaN.
     */
    float maxDistance;
} MPSRayOriginMaskDirectionMaxDistance;

/**
 * @brief Returned intersection result which contains the distance from the ray origin to the
 * intersection point
 *
 * @discussion This type is available from the Metal Shading Language by including the
 * MetalPerformanceShaders/MetalPerformanceShaders.h header.
 */
typedef struct {
    /**
     * @brief Distance from the ray origin to the intersection point along the ray direction
     * vector such that intersection = ray.origin + ray.direction * distance. Is negative if
     * there is no intersection. If the intersection type is MPSIntersectionTypeAny, is
     * a positive value for a hit or a negative value for a miss.
     */
    float distance;
} MPSIntersectionDistance;

/**
 * @brief Intersection result which contains the distance from the ray origin to the
 * intersection point and the index of the intersected primitive
 *
 * @discussion This type is available from the Metal Shading Language by including the
 * MetalPerformanceShaders/MetalPerformanceShaders.h header.
 */
typedef struct {
    /**
     * @brief Distance from the ray origin to the intersection point along the ray direction
     * vector such that intersection = ray.origin + ray.direction * distance. Is negative if
     * there is no intersection. If the intersection type is MPSIntersectionTypeAny, is
     * a positive value for a hit or a negative value for a miss.
     */
    float distance;

    /**
     * @brief Index of the intersected primitive. Undefined if the ray does not intersect
     * a primitive or if the intersection type is MPSIntersectionTypeAny.
     */
    unsigned int primitiveIndex;
} MPSIntersectionDistancePrimitiveIndex;

/**
 * @brief Intersection result which contains the distance from the ray origin to the intersection
 * point, the index of the intersected primitive, and the first two barycentric coordinates of
 * the intersection point.
 *
 * @discussion This type is available from the Metal Shading Language by including the
 * MetalPerformanceShaders/MetalPerformanceShaders.h header.
 */
typedef struct {
    /**
     * @brief Distance from the ray origin to the intersection point along the ray direction
     * vector such that intersection = ray.origin + ray.direction * distance. Is negative if
     * there is no intersection. If the intersection type is MPSIntersectionTypeAny, is
     * a positive value for a hit or a negative value for a miss.
     */
    float distance;

    /**
     * @brief Index of the intersected primitive. Undefined if the ray does not intersect
     * a primitive or if the intersection type is MPSIntersectionTypeAny.
     */
    unsigned int primitiveIndex;

    /**
     * @brief The first two barycentric coordinates U and V of the intersection point. The
     * third coordinate W = 1 - U - V. Undefined if the ray does not intersect a primitive
     * or if the intersection type is MPSIntersectionTypeAny.
     */
    vector_float2 coordinates;
} MPSIntersectionDistancePrimitiveIndexCoordinates;

/**
 * @brief Intersection result which contains the distance from the ray origin to the intersection
 * point, the index of the intersected primitive, and the index of the intersected instance.
 *
 * @discussion This type is available from the Metal Shading Language by including the
 * MetalPerformanceShaders/MetalPerformanceShaders.h header.
 */
typedef struct {
    /**
     * @brief Distance from the ray origin to the intersection point along the ray direction
     * vector such that intersection = ray.origin + ray.direction * distance. Is negative if
     * there is no intersection. If the intersection type is MPSIntersectionTypeAny, is
     * a positive value for a hit or a negative value for a miss.
     */
    float distance;

    /**
     * @brief Index of the intersected primitive. Undefined if the ray does not intersect
     * a primitive or if the intersection type is MPSIntersectionTypeAny.
     */
    unsigned int primitiveIndex;

    /**
     * @brief Index of the intersected instance. Undefined if the ray does not intersect a
     * primitive, if the acceleration structure is not an instance acceleration structure,
     * or if the intersection type is MPSIntersectionTypeAny.
     */
    unsigned int instanceIndex;
} MPSIntersectionDistancePrimitiveIndexInstanceIndex;

/**
 * @brief Intersection result which contains the distance from the ray origin to the intersection
 * point, the index of the intersected primitive, the index of the intersected instance, and the
 * first two barycentric coordinates of the intersection point.
 *
 * @discussion This type is available from the Metal Shading Language by including the
 * MetalPerformanceShaders/MetalPerformanceShaders.h header.
 */
typedef struct {
    /**
     * @brief Distance from the ray origin to the intersection point along the ray direction
     * vector such that intersection = ray.origin + ray.direction * distance. Is negative if
     * there is no intersection. If the intersection type is MPSIntersectionTypeAny, is
     * a positive value for a hit or a negative value for a miss.
     */
    float distance;

    /**
     * @brief Index of the intersected primitive. Undefined if the ray does not intersect
     * a primitive or if the intersection type is MPSIntersectionTypeAny.
     */
    unsigned int primitiveIndex;

    /**
     * @brief Index of the intersected instance. Undefined if the ray does not intersect a
     * primitive, if the acceleration structure is not an instance acceleration structure,
     * or if the intersection type is MPSIntersectionTypeAny.
     */
    unsigned int instanceIndex;

    /**
     * @brief The first two barycentric coordinates U and V of the intersection point. The
     * third coordinate W = 1 - U - V. Undefined if the ray does not intersect a primitive
     * or if the intersection type is MPSIntersectionTypeAny.
     */
    vector_float2 coordinates;
} MPSIntersectionDistancePrimitiveIndexInstanceIndexCoordinates;

#endif
