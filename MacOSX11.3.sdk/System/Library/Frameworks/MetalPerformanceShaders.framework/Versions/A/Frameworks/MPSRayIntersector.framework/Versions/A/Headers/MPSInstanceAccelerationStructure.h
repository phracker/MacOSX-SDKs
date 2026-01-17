/*!
 *  @header MPSInstanceAccelerationStructure.h
 *  @framework MPSRayIntersector
 *  @description  MPSRayIntersector instance acceleration structure interface.
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef MPSInstanceAccelerationStructure_h
#define MPSInstanceAccelerationStructure_h

#import <MPSRayIntersector/MPSAccelerationStructure.h>

@class MPSAccelerationStructureGroup;
@class MPSPolygonAccelerationStructure;

/**
 * @brief Instance transformation type options
 */
typedef NS_ENUM(NSUInteger, MPSTransformType) {
    /**
     * @brief Instance transformations are represented by a 4x4 column major matrix of 32 bit
     * floats
     */
    MPSTransformTypeFloat4x4 = 0,

    /**
     * @brief All instances have the identity transformation (no transformation). This can be used
     * to compose multiple polygon acceleration structures in an instance acceleration structure
     * without the cost of transforming instances. For example, geometry can be divided into
     * static and dynamic polygon acceleration structures which can be rebuilt and refit
     * independently.
     */
    MPSTransformTypeIdentity = 1
} MPS_ENUM_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0));

/**
 * @brief An acceleration structure built over instances of other acceleration structures
 *
 * @discussion Instancing can be used to reduce memory usage in scenes that contain many copies
 * of the same object(s) or to combine multiple acceleration structures such as a static and
 * dynamic acceleration structure into a two-level instance hierarchy.
 *
 * The typical pattern for creating an instance acceleration structure is as follows. First,
 * create individual bottom-level acceleration structures. Then assign these acceleration
 * structures to the accelerationStructures property of an instance acceleration structure.
 *
 * All of the acceleration structures in the instance hierarchy must share the same
 * MPSAccelerationStructureGroup. Furthermore, all of the bottom-level acceleration structures
 * must share the same vertex buffer, index buffer, etc. although they may have different offsets
 * within those buffers.
 *
 *     @code
 *     MPSAccelerationStructureGroup *group = nil;
 *     group = [[MPSAccelerationStructureGroup alloc] initWithDevice:device];
 *
 *     MPSInstanceAccelerationStructure *instanceAccel = nil;
 *     instanceAccel = [[MPSInstanceAccelerationStructure alloc] initWithGroup:group];
 *
 *     NSMutableArray *accelerationStructures = [NSMutableArray array];
 *     instanceAccel.accelerationStructures = accelerationStructures;
 *
 *     instanceAccel.instanceCount = instanceCount;
 *
 *     for (ObjectType *objectType in objectTypes) {
 *         MPSTriangleAccelerationStructure *triAccel = nil;
 *         triAccel = [[MPSTriangleAccelerationStructure alloc] initWithGroup:group];
 *
 *         triAccel.vertexBuffer = objectType.vertexBuffer;
 *         triAccel.vertexBufferOffset = objectType.vertexBufferOffset;
 *         triAccel.triangleCount = objectType.triangleCount;
 *
 *         [triAccel rebuild];
 *
 *         [accelerationStructures addObject:triAccel];
 *     }
 *     @endcode
 *
 * Next, create a buffer containing the acceleration structure index for each instance, and
 * another acceleration structure containing the transformation matrix for each instance:
 *
 *     @code
 *     NSUInteger instanceBufferLength = sizeof(uint32_t) * instanceCount;
 *    
 *     id <MTLBuffer> instanceBuffer =
 *         [device newBufferWithLength:instanceBufferLength
 *                             options:MTLResourceStorageModeManaged];
 *    
 *     memcpy(instanceBuffer.contents, instances,
 *         instanceBufferLength);
 *     [instanceBuffer
 *         didModifyRange:NSMakeRange(0, instanceBufferLength)];
 *    
 *     instanceAccel.instanceBuffer = instanceBuffer;
 *
 *     // Similar for transformation matrix buffer
 *     @endcode
 *
 * Finally, rebuild the instance acceleration structure:
 *
 *     @code
 *     [instanceAccel rebuild];
 *     @endcode
 *
 * Refitting and Rebuilding Bottom-Level Acceleration Structures: when a bottom level acceleration
 * structure is rebuild or refit, its' bounding box may change. Therefore, the instance
 * acceleration structure also needs to be rebuilt or refit.
 *
 * Copying and Serializing Instance Acceleration Structures: When an instance acceleration
 * structure is copied or serialized, the bottom level acceleration structures are not copied or
 * serialized. These must be copied or serialized along with the instance acceleration structure
 * and assigned to the new instance acceleration structure. This also applies to buffer properties
 * such as the instance buffer, transformation buffer, etc.
 *
 * Performance Guidelines:
 *
 *     - Use instancing to reduce memory usage: if there are many copies of the same object(s) in
 *       a scene, using instances of the same object can reduce memory usage and acceleration
 *       structure build time. Rebuilding or refitting the top level acceleration structure can
 *       also be much faster than rebuilding a large single level acceleration structure.
 *
 *     - Consider flattening your instance hierarchy into a single acceleration structure if the
 *       increased memory usage and acceleration structure build time are not a concern.
 *       Intersecting a two level acceleration structure can have a significant performance cost so
 *       only use it when necessary. Which technique to use depends on the scene and use case. For
 *       example, in a rendering application, it may be best to use an instance hierarchy for
 *       interactive scene editing and preview and flattening the instance hierarchy for the final
 *       render. For smaller scenes, it may also be sufficient to refit a flattened acceleration
 *       structure rather than rebuilding an instance hierarchy.
 *
 *     - If there is only a single object in the scene, intersect its acceleration structure
 *       directly instead of using an instance hierarchy.
 *
 *     - Consider dividing objects into static and dynamic acceleration structures. If dynamic
 *       objects require the acceleration structure to be rebuilt frequently, create a high quality
 *       static acceleration structure and a lower quality but faster to build dynamic acceleration
 *       structure. These two acceleration structures can then be combined with a two level
 *       acceleration structure. Use MPSTransformTypeIdentity to reduce the overhead of this
 *       technique. Whether this technique is more efficient than rebuilding the entire
 *       acceleration structure depends on the scene.
 *
 * See MPSAccelerationStructure for more information
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0))
@interface MPSInstanceAccelerationStructure : MPSAccelerationStructure

/**
 * @brief Acceleration structures available for use in this instance acceleration structure. Each
 * instance must provide an index into this array in the instance buffer as well as a
 * transformation matrix in the transform buffer. All acceleration structures must share a single
 * vertex buffer, optional index buffer, and optional mask buffer, though they may have different
 * offsets within each buffer, and all acceleration structures must share the same acceleration
 * structure group. If a polygon acceleration structure is rebuilt or refit, the instance
 * acceleration structure must subsequently be rebuilt or refit.
 */
@property (nonatomic, retain) NSArray <MPSPolygonAccelerationStructure *> * _Nullable accelerationStructures;

/**
 * @brief Buffer containing the 32 bit unsigned integer index into the acceleration structure array
 * for each instance
 */
@property (nonatomic, retain) id <MTLBuffer> _Nullable instanceBuffer;

/**
 * @brief Offset, in bytes, into the instance buffer. Defaults to 0 bytes. Must be aligned to 4
 * bytes.
 */
@property (nonatomic) NSUInteger instanceBufferOffset;

/**
 * @brief Buffer containing one column major matrix_float4x4 transformation matrix per instance
 */
@property (nonatomic, retain) id <MTLBuffer> _Nullable transformBuffer;

/**
 * @brief Offset, in bytes, into the transform buffer. Defaults to 0 bytes. Must be aligned to the
 * stride of the transform type.
 */
@property (nonatomic) NSUInteger transformBufferOffset;

/**
 * @brief Instance transform type. Defaults to MPSTransformTypeFloat4x4. Changes to this property
 * require rebuilding the acceleration structure.
 */
@property (nonatomic) MPSTransformType transformType;

/**
 * @brief Mask buffer containing one uint32_t mask per instance. May be nil.
 */
@property (nonatomic, retain) id <MTLBuffer> _Nullable maskBuffer;

/**
 * @brief Offset, in bytes, into the mask buffer. Defaults to 0 bytes. Must be aligned to 4 bytes.
 */
@property (nonatomic) NSUInteger maskBufferOffset;

/**
 * @brief Number of instances. Changes to this property require rebuilding the acceleration
 * structure.
 */
@property (nonatomic) NSUInteger instanceCount;

@end

#endif
