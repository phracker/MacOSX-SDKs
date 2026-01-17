/*!
 *  @header MPSPolygonAccelerationStructure.h
 *  @framework MPSRayIntersector
 *  @description  MPSRayIntersector polygon acceleration structure interface.
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef MPSPolygonAccelerationStructure_h
#define MPSPolygonAccelerationStructure_h

#import <MPSRayIntersector/MPSAccelerationStructure.h>
#import <MPSRayIntersector/MPSPolygonBuffer.h>

typedef NS_ENUM(NSUInteger, MPSPolygonType) {
    /**
     * @brief Triangles with three vertices
     */
    MPSPolygonTypeTriangle = 0,

    /**
     * @brief Quadrilaterals with four vertices
     */
    MPSPolygonTypeQuadrilateral = 1,
} MPS_ENUM_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0));

/**
 * @brief An acceleration structure built over polygonal shapes
 *
 * @discussion See MPSAccelerationStructure for more information
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSPolygonAccelerationStructure : MPSAccelerationStructure

/**
 * @brief The type of polygon. Defaults to MPSPolygonTypeTriangle. Changes to this property require
 * rebuilding the acceleration structure.
 */
@property (nonatomic) MPSPolygonType polygonType;

/**
 * @brief Offset, in bytes, between consecutive vertices in the vertex buffer. Defaults to 0 bytes,
 * indicating that the vertices are packed according to the natural alignment of the vector_float3
 * type: 16 bytes.
 *
 * @discussion This can be used to skip past any additional per-vertex data which may be stored
 * alongside the position such as the vertex normal and texture coordinates. Must be a multiple of
 * 4 bytes, and must be at least 12 bytes. Changes to this property require rebuilding the
 * acceleration structure.
 */
@property (nonatomic) NSUInteger vertexStride;

/**
 * @brief Index type. Defaults to MPSDataTypeUInt32. Only MPSDataTypeUInt16 and MPSDataTypeUInt32
 * are supported.
 */
@property (nonatomic) MPSDataType indexType;

/**
 * @brief Vertex buffer containing vertex data encoded as three 32 bit floats per vertex. Note
 * that by default each vertex is aligned to the alignment of the vector_float3 type: 16 bytes.
 * This can be changed using the vertexStride property. A vertex buffer must be provided before
 * the acceleration structure is built.
 *
 * When using triangle polygons, degenerate (zero or negative area) triangles are ignored
 * during acceleration structure construction. This can be used to pad triangle indices if needed.
 *
 * Quadrilateral polygons are internally treated as two triangles. If the quadrilateral has
 * vertices v0, v1, v2, and v3, the two triangles will have vertices v0, v1, v2 and v0, v2, v3.
 * A quadrilateral may be used to represent a triangle by repeating the last vertex. If the first
 * triangle is degenerate (zero or negative area), the entire quadrilateral will be ignored. This
 * can be used to pad quadrilateral indices if needed. All four vertices of a quadrilateral must
 * be coplanar and the quadrilateral must be convex.
 *
 * This is an alias for polygonBuffers[0].vertexBuffer. There must be exactly one polygon buffer
 * to use this property, or the polygonBuffers property must be nil, in which case an
 * MPSPolygonBuffer will be created automatically.
 */
@property (nonatomic, retain) id <MTLBuffer> _Nullable vertexBuffer;

/**
 * @brief Offset, in bytes, into the vertex buffer. Defaults to 0 bytes. Must be aligned to 4
 * bytes.
 *
 * This is an alias for polygonBuffers[0].vertexBufferOffset. There must be exactly one polygon
 * buffer to use this property, or the polygonBuffers property must be nil, in which case an
 * MPSPolygonBuffer will be created automatically.
 */
@property (nonatomic) NSUInteger vertexBufferOffset;

/**
 * @brief Index buffer containing index data. Each index references a vertex in the vertex buffer.
 * May be nil.
 *
 * This is an alias for polygonBuffers[0].indexBuffer. There must be exactly one polygon buffer
 * to use this property, or the polygonBuffers property must be nil, in which case an
 * MPSPolygonBuffer will be created automatically.
 */
@property (nonatomic, retain) id <MTLBuffer> _Nullable indexBuffer;

/**
 * @brief Offset, in bytes, into the index buffer. Defaults to 0 bytes. Must be aligned to a
 * multiple of the index type. Changes to this property require rebuilding the acceleration
 * structure.
 *
 * This is an alias for polygonBuffers[0].indexBufferOffset. There must be exactly one polygon
 * buffer to use this property, or the polygonBuffers property must be nil, in which case an
 * MPSPolygonBuffer will be created automatically.
 */
@property (nonatomic) NSUInteger indexBufferOffset;

/**
 * @brief Mask buffer containing one uint32_t mask per polygon. May be nil. Otherwise, the mask
 * type must be specified on the MPSRayIntersector with which it is used.
 *
 * This is an alias for polygonBuffers[0].maskBuffer. There must be exactly one polygon buffer
 * to use this property, or the polygonBuffers property must be nil, in which case an
 * MPSPolygonBuffer will be created automatically.
 */
@property (nonatomic, retain) id <MTLBuffer> _Nullable maskBuffer;

/**
 * @brief Offset, in bytes, into the mask buffer. Defaults to 0 bytes. Must be aligned to 4 bytes.
 *
 * This is an alias for polygonBuffers[0].maskBufferOffset. There must be exactly one polygon
 * buffer to use this property, or the polygonBuffers property must be nil, in which case an
 * MPSPolygonBuffer will be created automatically.
 */
@property (nonatomic) NSUInteger maskBufferOffset;

/**
 * @brief Number of polygons. Changes to this property require rebuilding the acceleration
 * structure.
 *
 * This is an alias for polygonBuffers[0].polygonCount. There must be exactly one polygon buffer
 * to use this property, or the polygonBuffers property must be nil, in which case an
 * MPSPolygonBuffer will be created automatically.
 */
@property (nonatomic) NSUInteger polygonCount;

/**
 * @brief Array of polygon buffers. Each buffer contains a vertex buffer and optional index and
 * mask buffer for an array of polygons. Changing the length of this array requires rebuilding the
 * acceleration structure.
 *
 * Using more than one MPSPolygonBuffer will reduce performance. It is better to concatenate
 * these buffers into a single vertex buffer, index buffer, and mask buffer and use a single
 * MPSPolygonBuffer if possible. This also applies when using an MPSInstanceAccelerationStructure:
 * each instance or subclass of MPSPolygonAccelerationStructure in an instance hierarchy should use
 * the same vertex buffer, index buffer, and mask buffer, although each acceleration structure
 * may use different offsets into these buffers. This allows for the vertex, index, and mask
 * buffers to be bound directly instead of indirectly through an argument buffer.
 *
 * There must be at least one MPSPolygonBuffer. On argument buffer tier 1 devices, there must be
 * be exactly one MPSPolygonBuffer. Use the argumentBuffersSupport property of the MTLDevice to
 * check for support.
 */
@property (nonatomic, retain) NSArray <MPSPolygonBuffer *> * _Nullable polygonBuffers;

@end

#endif
