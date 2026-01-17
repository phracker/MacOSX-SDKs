/*!
 *  @header MPSPolygonBuffer.h
 *  @framework MPSRayIntersector
 *  @description  MPSRayIntersector polygon buffer interface.
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef MPSPolygonBuffer_h
#define MPSPolygonBuffer_h

#import <MPSRayIntersector/MPSAccelerationStructure.h>

/**
 * @brief A vertex buffer and optional index and mask buffer for a set of polygons
 */
MPS_AVAILABLE_STARTING_BUT_DEPRECATED("Use Metal ray tracing API instead", macos(10.15, 14.0), ios(13.0, 17.0), macCatalyst(13.0, 17.0), tvos(13.0, 17.0))
@interface MPSPolygonBuffer : NSObject <NSCopying, NSSecureCoding>

/**
 * @brief Initialize the polygon buffer
 */
- (nonnull instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 * @brief Initialize the polygon buffer with an NSCoder. Buffer properties such as the vertex
 * buffer, instance buffer, etc. are set to nil. Encode and decode these buffers along with the
 * polygon buffer instead.
 */
- (nullable instancetype)initWithCoder:(NSCoder * __nonnull)aDecoder NS_DESIGNATED_INITIALIZER;

+ (nonnull instancetype)polygonBuffer;

/**
 * @brief Create a a copy of this polygon buffer
 *
 * @discussion Buffer properties of the polygon buffer such as the vertex buffer, instance, buffer,
 * etc. are set to nil. Copy these buffers and assign them to the new polygon buffer or reassign
 * the existing buffers to the new polygon buffer.
 *
 * @param zone This parameter is ignored. Memory zones are no longer used by Objective-C.
 */
- (nonnull instancetype)copyWithZone:(nullable NSZone *)zone;

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
 */
@property (nonatomic, retain) id <MTLBuffer> _Nullable vertexBuffer;

/**
 * @brief Offset, in bytes, into the vertex buffer. Defaults to 0 bytes. Must be aligned to 4
 * bytes.
 */
@property (nonatomic) NSUInteger vertexBufferOffset;

/**
 * @brief Index buffer containing index data. Each index references a vertex in the vertex buffer.
 * May be nil.
 */
@property (nonatomic, retain) id <MTLBuffer> _Nullable indexBuffer;

/**
 * @brief Offset, in bytes, into the index buffer. Defaults to 0 bytes. Must be aligned to a
 * multiple of the index type. Changes to this property require rebuilding the acceleration
 * structure.
 */
@property (nonatomic) NSUInteger indexBufferOffset;

/**
 * @brief Mask buffer containing one uint32_t mask per polygon. May be nil. Otherwise, the mask
 * type must be specified on the MPSRayIntersector with which it is used.
 */
@property (nonatomic, retain) id <MTLBuffer> _Nullable maskBuffer;

/**
 * @brief Offset, in bytes, into the mask buffer. Defaults to 0 bytes. Must be aligned to 4 bytes.
 */
@property (nonatomic) NSUInteger maskBufferOffset;

/**
 * @brief Number of polygons. Changes to this property require rebuilding the acceleration
 * structure.
 */
@property (nonatomic) NSUInteger polygonCount;

@end

#endif
