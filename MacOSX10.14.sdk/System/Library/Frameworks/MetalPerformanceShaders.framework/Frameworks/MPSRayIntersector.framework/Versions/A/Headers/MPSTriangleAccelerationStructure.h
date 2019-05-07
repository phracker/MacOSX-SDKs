/*!
 *  @header MPSTriangleAccelerationStructure.h
 *  @framework MPSRayIntersector
 *  @description  MPSRayIntersector triangle acceleration structure interface.
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef MPSTriangleAccelerationStructure_h
#define MPSTriangleAccelerationStructure_h

#import <MPSRayIntersector/MPSAccelerationStructure.h>

/**
 * @brief An acceleration structure built over triangles
 *
 * @discussion See MPSAccelerationStructure for more information
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), tvos(12.0))
@interface MPSTriangleAccelerationStructure : MPSAccelerationStructure

/**
 * @brief Vertex buffer containing vertex data encoded as three 32 bit floats per vertex. Note
 * that by default each vertex is aligned to the alignment of the vector_float3 type: 16 bytes.
 * This can be changed using the vertexStride property. A vertex buffer must be provided before
 * the acceleration structure is built. Degenerate (zero or negative area) triangles are ignored
 * during acceleration structure construction. This can be used to pad triangle indices if needed.
 */
@property (nonatomic, retain) id <MTLBuffer> _Nullable vertexBuffer;

/**
 * @brief Offset, in bytes, into the vertex buffer. Defaults to 0 bytes. Must be aligned to 4
 * bytes.
 */
@property (nonatomic) NSUInteger vertexBufferOffset;

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
 * @brief Index buffer containing index data encoded as uint32_t per index. Each index references
 * a vertex in the vertex buffer. May be nil.
 */
@property (nonatomic, retain) id <MTLBuffer> _Nullable indexBuffer;

/**
 * @brief Index type. Defaults to MPSDataTypeUInt32. Only MPSDataTypeUInt16 and MPSDataTypeUInt32
 * are supported.
 */
@property (nonatomic) MPSDataType indexType;

/**
 * @brief Offset, in bytes, into the index buffer. Defaults to 0 bytes. Must be aligned to a
 * multiple of the index type. Changes to this property require rebuilding the acceleration
 * structure.
 */
@property (nonatomic) NSUInteger indexBufferOffset;

/**
 * @brief Mask buffer containing one uint32_t mask per triangle. May be nil. Otherwise, the mask
 * type must be specified on the MPSRayIntersector with which it is used.
 */
@property (nonatomic, retain) id <MTLBuffer> _Nullable maskBuffer;

/**
 * @brief Offset, in bytes, into the mask buffer. Defaults to 0 bytes. Must be aligned to 4 bytes.
 */
@property (nonatomic) NSUInteger maskBufferOffset;

/**
 * @brief Number of triangles. Changes to this property require rebuilding the acceleration
 * structure.
 */
@property (nonatomic) NSUInteger triangleCount;

@end

#endif
