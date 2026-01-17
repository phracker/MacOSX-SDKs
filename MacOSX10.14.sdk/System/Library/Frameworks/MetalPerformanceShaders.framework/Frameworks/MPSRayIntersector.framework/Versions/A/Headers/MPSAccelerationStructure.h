/*!
 *  @header MPSAccelerationStructure.h
 *  @framework MPSRayIntersector
 *  @description  MPSRayIntersector acceleration structure interface.
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef MPSAccelerationStructure_h
#define MPSAccelerationStructure_h

#import <MPSCore/MPSCoreTypes.h>
#import <MPSCore/MPSKernel.h>

#import <MPSRayIntersector/MPSRayIntersectorTypes.h>

@class MPSAccelerationStructure;
@class MPSAccelerationStructureGroup;

/**
 * @brief A block of code invoked when an operation on an MPSAccelerationStructure is completed
 */
MPS_AVAILABLE_STARTING(macos(10.14), ios(12.0), tvos(12.0))
typedef void (^MPSAccelerationStructureCompletionHandler)(MPSAccelerationStructure * _Nullable);

/**
 * @brief Options describing how an acceleration structure will be used
 */
typedef NS_OPTIONS(NSUInteger, MPSAccelerationStructureUsage) {
    /**
     * @brief No usage options specified
     */
    MPSAccelerationStructureUsageNone = 0,

    /**
     * @brief Enable support for refitting the acceleration structure after it has been built.
     * This option may reduce raytracing performance so do not use it unless the acceleration
     * structure will be refit.
     */
    MPSAccelerationStructureUsageRefit = 1,

    /**
     * @brief Option indicating that the acceleration structure will be rebuilt frequently. In this
     * case, the acceleration structure may choose a higher performance but lower quality
     * acceleration structure construction algorithm. This option may reduce raytracing performance
     * performance so do not use it unless reduced acceleration structure build time is
     * worth reduced raytracing performance. This option may be useful if, for example, the user
     * is interactively editing a live view of the scene.
     */
    MPSAccelerationStructureUsageFrequentRebuild = 2,
} MPS_ENUM_AVAILABLE_STARTING(macos(10.14), ios(12.0), tvos(12.0));

/**
 * @brief Possible values of the acceleration structure status property
 */
typedef NS_ENUM(NSUInteger, MPSAccelerationStructureStatus) {
    /**
     * @brief The acceleration structure has not been built yet
     */
    MPSAccelerationStructureStatusUnbuilt = 0,

    /**
     * @brief The acceleration structure has finished building
     */
    MPSAccelerationStructureStatusBuilt = 1
} MPS_ENUM_AVAILABLE_STARTING(macos(10.14), ios(12.0), tvos(12.0));

/**
 * @brief A data structure built over geometry used to acceleration ray tracing
 *
 * @discussion Do not use this base class directly. Use one of the derived classes instead.
 * The general pattern for creating an acceleration structure is as follows. First, create the
 * acceleration structure:
 *
 *     @code
 *     MPSTriangleAccelerationStructure *accelerationStructure = nil;
 *     accelerationStructure = [[MPSTriangleAccelerationStructure alloc] initWithDevice:device];
 *     @endcode
 *
 * Then, assign values to the acceleration structure's properties:
 *
 *     @code
 *     accelerationStructure.vertexBuffer = vertexBuffer;
 *     accelerationStructure.triangleCount = triangleCount;
 *     @endcode
 *
 * Finally, the acceleration structure must be built:
 *
 *     @code
 *     [accelerationStructure rebuild];
 *     @endcode
 *
 * The acceleration structure can then be used to encode ray intersection tests with an
 * MPSRayIntersector:
 *
 *     @code
 *     [raytracer encodeIntersectionToCommandBuffer:commandBuffer
 *                                 intersectionType:MPSIntersectionTypeNearest
 *                                        rayBuffer:rayBuffer
 *                                  rayBufferOffset:0
 *                               intersectionBuffer:intersectionBuffer
 *                         intersectionBufferOffset:0
 *                                         rayCount:rayCount
 *                            accelerationStructure:accelerationStructure];
 *     @endcode
 *
 * Asynchronous Acceleration Structure Builds: Rebuilding an acceleration structure is an expensive
 * operation. Note that there is also a method to rebuild the acceleration structure asynchronously
 * to avoid blocking the main thread.
 *
 *     @code
 *     [accelerationStructure rebuildWithCompletionHandler:^(MPSAccelerationStructure *accel) {
 *         // Kick off ray intersection work
 *     }];
 *     @endcode
 *
 * Streaming Geometry Updates: It is generally safe to change buffer properties such as the vertex
 * buffer after intersection tests have been encoded into a command buffer, but the contents of
 * those buffers cannot be safely changed by the CPU until the command buffer has finished
 * executing on the GPU. It is also not safe to rebuild the acceleration structure until the
 * command buffer has completed.
 *
 * If the CPU needs to stream geometry updates to the GPU, ensure the vertex and other buffers are
 * double or triple buffered.
 *
 *     @code
 *     #define MAX_ASYNC_OPERATIONS 3
 *
 *     // Initialization:
 *
 *     // Create a semaphore with the maximum number of asynchronous operations in flight
 *     dispatch_semaphore_t asyncOperationSemaphore = dispatch_semaphore_create(MAX_ASYNC_OPERATIONS);
 *
 *     // Create an acceleration structure for each vertex buffer range
 *     NSMutableArray *accelerationStructures = [NSMutableArray array];
 *
 *     NSUInteger vertexBufferLength = sizeof(float3) * vertexCount * MAX_ASYNC_OPERATIONS;
 *     id <MTLBuffer> vertexBuffer = [device newBufferWithLength:vertexBufferLength
 *                                                       options:MTLResourceStorageModeManaged];
 *
 *     for (NSUInteger i = 0; i < MAX_ASYNC_OPERATIONS; i++) {
 *         MPSTriangleAccelerationStructure *accel = nil;
 *         accel = [[MPSTriangleAccelerationStructure alloc] initWithDevice:device];
 *
 *         // Configure acceleration structure
 *         accel.vertexBuffer = vertexBuffer;
 *         accel.vertexBufferOffset = i * sizeof(float3) * vertexCount;
 *
 *         [accelerationStructures addObject:accel];
 *     }
 *
 *     NSUInteger asyncOperationIndex = 0;
 *
 *     // Encode intersection testing:
 *
 *     // Wait until there is a free acceleration structure
 *     dispatch_semaphore_wait(asyncOperationSemaphore, DISPATCH_TIME_FOREVER);
 *
 *     MPSTriangleAccelerationStructure *accel = accelerationStructures[asyncOperationIndex];
 *     asyncOperationIndex = (asyncOperationIndex + 1) % MAX_ASYNC_OPERATIONS;
 *
 *     float3 *vertices = (float3 *)((uint8_t *)vertexBuffer.contents + accel.vertexBufferOffset);
 *     // Update vertices
 *     [vertexBuffer didModifyRange:NSMakeRange(accel.vertexBufferOffset, sizeof(float3) * vertexCount)];
 *
 *     // Rebuild the acceleration structure
 *     [accel rebuild];
 *
 *     // Encode actual intersection work
 *     [raytracer encodeIntersectionToCommandBuffer:commandBuffer
 *                                 intersectionType:MPSIntersectionTypeNearest
 *                                        rayBuffer:rayBuffer
 *                                  rayBufferOffset:rayBufferOffset
 *                               intersectionBuffer:intersectionBuffer
 *                         intersectionBufferOffset:intersectionBufferOffset
 *                                         rayCount:rayCount
 *                            accelerationStructure:accel];
 *
 *     // Register a completion handler to run when the GPU finishes executing
 *     [commandBuffer addCompletedHandler:^(id <MTLCommandBuffer> commandBuffer) {
 *         Intersection *intersections = (Intersection *)((uint8_t *)intersectionBuffer.contents +
 *             intersectionBufferOffset);
 *
 *         // Process intersections
 *
 *         // Signal that the acceleration structure is now available for reuse
 *         dispatch_semaphore_signal(asyncOperationSemaphore);
 *     }];
 *
 *     // Commit the command buffer to allow the GPU to start executing
 *     [commandBuffer commit];
 *     @endcode
 *
 * Refitting acceleration structures: If geometry has only moved slightly and not added or removed
 * from the scene, it can be much faster to refit the existing topology of an acceleration
 * structure to the new geometry than to rebuild the acceleration structure from scratch. Refitting
 * can also be pipelined with other GPU work such as intersection testing. If the geometry is
 * transformed entirely on the GPU, it is not necessary to use double or triple buffering. For
 * example:
 *
 *     @code
 *     id <MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
 *
 *     id <MTLComputeCommandEncoder> encoder = [commandBuffer computeCommandEncoder];
 *
 *     [encoder setBuffer:untransformedVertexBuffer offset:0 atIndex:0];
 *
 *     [encoder setBuffer:accelerationStructure.vertexBuffer
 *                 offset:accelerationStructure.vertexBufferOffset
 *                atIndex:1];
 *
 *     [encoder setBuffer:transformationMatrices offset:0 atIndex:2];
 *
 *     [encoder setComputePipelineState:transformVerticesPipeline];
 *
 *     [encoder dispatchThreads:MTLSizeMake(accelerationStructure.triangleCount * 3, 1, 1)
 *        threadsPerThreadgroup:MTLSizeMake(64, 1, 1)];
 *
 *     [encoder endEncoding];
 *
 *     [accelerationStructure encodeRefitToCommandBuffer:commandBuffer];
 *
 *     [commandBuffer commit];
 *     @endcode
 * 
 * Serializing Acceleration Structures: Instead of rebuilding acceleration structures from scratch
 * they can be built offline, serialized, and reloaded at runtime using the NSSecureCoding
 * protocol:
 *
 *     @code
 *     // Build time:
 *     NSError *error = nil;
 *     NSData *data = [NSKeyedArchiver archivedDataWithRootObject:accel
 *                                          requiringSecureCoding:YES
 *                                                          error:&error];
 *        
 *     if (!data)
 *         NSLog(@"Error archiving MPSAccelerationStructure: %@",
 *             error.localizedDescription);
 *
 *     // Runtime:
 *     MPSTriangleAccelerationStructure *accel;
 *     accel = [NSKeyedUnarchiver unarchivedObjectOfClass:[MPSTriangleAccelerationStructure class]
 *                                               fromData:data
 *                                                  error:&error];
 *
 *     if (!accel)
 *         NSLog(@"Error unarchiving MPSAccelerationStructure: %@",
 *             error.localizedDescription);
 *     @endcode
 *
 * Copying Acceleration Structures: Acceleration structures can be copied using the NSCopying
 * protocol, even to a different Metal device. This can be used for multi-GPU raytracing. Buffer
 * properties are not copied to the new acceleration structure. These buffers must instead be
 * copied to the new Metal device and assigned to the new acceleration structure. For example:
 *
 *     @code
 *     MPSTriangleAccelerationStructure *copy = [accelerationStructure copyWithZone:nil
 *                                                                           device:newDevice];
 *
 *     copy.vertexBuffer = [self copyBuffer:accelerationStructure.vertexBuffer
 *                               withDevice:newDevice];
 *     @endcode
 *
 * Performance Guidelines:
 *
 *     - Provide accurate acceleration structure hints: if an acceleration structure does not
 *       require support for refitting, a higher quality construction algorithm can be used.
 *       However, if an acceleration structure must be rebuilt frequently, a lower quality
 *       but higher performance construction algorithm can be used.
 *
 *     - Consider refitting existing acceleration structures rather than rebuilding them from
 *       scratch. This is typically much faster and can result in a reasonably high quality
 *       tree if the geometry has not been modified dramatically. Refitting can also be pipelined
 *       with other GPU work. If objects have been added to or removed from the scene, it is
 *       typically necessary to rebuild the acceleration structure rather than refit it.
 *
 *     - Rebuild acceleration structures asynchronously when possible to avoid blocking the main
 *       thread. Consider presenting a UI indicating that work is happening in the background while
 *       allowing the user to consider interacting with your application.
 *
 *     - If you need to mix intersection testing with acceleration structure builds (e.g. if the
 *       user is interactively editing the scene while rendering or if objects are moving
 *       significantly) consider allocating two independent acceleration structures that refer to
 *       two copies of the scene data. Then, asynchronously rebuild one acceleration structure
 *       while the other one is used for rendering. Once the rebuild has completed, swap the
 *       acceleration structures. The intermediate frames could be filled by refitting the
 *       rendering acceleration structure until the rebuilt acceleration structure is ready.
 *
 *     - When running in Xcode, disable "Enable Backtrace Recording" in your scheme settings.
 *       Enabling this setting can significantly increase acceleration structure build time.
 *
 * Thread Safety: MPSAccelerationStructures are generally not thread safe. Changing properties
 * and rebuilding acceleration structures from multiple threads result in undefined behavior.
 * However, it is safe to encode intersection tests with a single acceleration structure
 * from multiple threads as long as each thread uses its own MPSRayIntersector.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), tvos(12.0))
@interface MPSAccelerationStructure : MPSKernel <NSSecureCoding, NSCopying>

/**
 * @brief The group this acceleration structure was created with
 */
@property (nonatomic, readonly) MPSAccelerationStructureGroup * _Nonnull group;

/**
 * @brief The bounding box fully enclosing the geometry this acceleration structure was built over.
 *
 * @discussion The value of this property is not available until the acceleration structure
 * has finished rebuilding or refitting
 */
@property (nonatomic, readonly) MPSAxisAlignedBoundingBox boundingBox;

/**
 * @brief Status indicating whether the acceleration structure has finished building
 */
@property (nonatomic, readonly) MPSAccelerationStructureStatus status;

/**
 * @brief Acceleration structure usage options. Changes to this property require rebuilding the
 * acceleration structure. Defaults to MPSAccelerationStructureUsageNone.
 */
@property (nonatomic) MPSAccelerationStructureUsage usage;

- (nonnull instancetype)init NS_UNAVAILABLE;

/**
 * @brief Initialize the acceleration structure with a Metal device
 */
- (nonnull instancetype)initWithDevice:(nonnull id <MTLDevice>)device NS_DESIGNATED_INITIALIZER;

/**
 * @brief Initialize the acceleration structure with an NSCoder and a Metal device. Buffer
 * properties such as the vertex buffer, instance buffer, etc. are set to nil. Encode and decode
 * these buffers along with the acceleration structure instead.
 */
- (nullable instancetype)initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>)device NS_DESIGNATED_INITIALIZER;

/**
 * @brief Initialize the acceleration structure with an acceleration structure group, if the
 * acceleration structure will be used in an instance hierarchy.
 *
 * @discussion The Metal device is determined from the acceleration structure group. All
 * acceleration structures in the instance hierarchy must share the same group.
 */
- (nonnull instancetype)initWithGroup:(MPSAccelerationStructureGroup * _Nonnull)group
      NS_DESIGNATED_INITIALIZER;

/**
 * @brief Initialize the acceleration structure with an NSCoder and an acceleration structure
 * group, if the acceleration structure will be used in an instance hierarchy. All acceleration
 * structures in the instance hierarchy must share the same group. Buffer properties such as the
 * vertex buffer, instance buffer, etc. are set to nil. Encode and decode these buffers along with
 * the acceleration structure instead.
 */
- (nullable instancetype)initWithCoder:(NSCoder * __nonnull)aDecoder
                                 group:(nonnull MPSAccelerationStructureGroup *)group
                                 NS_DESIGNATED_INITIALIZER;

/**
 * @brief Rebuild the acceleration structure
 *
 * @discussion This method must be called before any intersection tests can be scheduled with this
 * acceleration structure. Before calling this method, fill out the properties of the acceleration
 * structure such as vertex buffer, instance buffer, etc. The acceleration structure should be
 * rebuilt when its contents (e.g. vertices in a triangle acceleration structure) have been
 * modified significantly and must be rebuilt when properties such as triangle count,
 * vertex stride, etc. have changed. When the contents of the acceleration structure have only been
 * modified slightly, it may be cheaper to refit the acceleration structure instead.
 *
 * This method blocks until the acceleration structure has been rebuilt. Until the rebuild has
 * completed, the acceleration structure cannot be copied, encoded with NSSecureCoding, rebuilt, or
 * refit. Before this method can be called, any pending GPU writes to the vertex buffer, index
 * buffer, etc. must be completed (and, for managed buffers, synchronized). Any prior intersection
 * tests must also be completed before the acceleration structure can be rebuilt.
 */
- (void)rebuild;

/**
 * @brief Rebuild the acceleration structure asynchronously
 *
 * @discussion This method must be called before any intersection tests can be scheduled with this
 * acceleration structure. Before calling this method, fill out the properties of the acceleration
 * structure such as vertex buffer, instance buffer, etc. The acceleration structure should be
 * rebuilt when its contents (e.g. vertices in a triangle acceleration structure) have been
 * modified significantly and must be rebuilt when properties such as triangle count,
 * vertex stride, etc. have changed. When the contents of the acceleration structure have only been
 * modified slightly, it may be cheaper to refit the acceleration structure instead.
 *
 * Until the rebuild has completed, the acceleration structure cannot be copied, encoded with
 * NSSecureCoding, rebuilt, or refit. Before this method can be called, any pending GPU writes to
 * the vertex buffer, index buffer, etc. must be completed (and, for managed buffers,
 * synchronized). Any prior intersection tests must also be completed before the acceleration
 * structure can be rebuilt.
 */
- (void)rebuildWithCompletionHandler:(nonnull MPSAccelerationStructureCompletionHandler)completionHandler;

/**
 * @brief Refit the existing acceleration structure to new data
 *
 * @discussion This method is used to refit the acceleration structure to new vertex data,
 * index data, instance data, etc. while preserving the existing acceleration structure topology.
 * This is typically much faster than a full rebuild of the acceleration structure. Refitting can
 * also be pipelined with other GPU work such as ray intersection.
 *
 * Until the command buffer has completed, the acceleration structure cannot be copied,
 * encoded with NSSecureCoding, or rebuilt. Changes to properties such as the triangle count or
 * instance might not be reflected. These changes require that the acceleration structure be
 * rebuilt instead. The acceleration structure must be rebuilt at least once before this method can
 * be called.
 */
- (void)encodeRefitToCommandBuffer:(nonnull id <MTLCommandBuffer>)commandBuffer
    MPS_SWIFT_NAME(encodeRefit(commandBuffer:));

/**
 * @brief Create a a copy of this acceleration structure
 *
 * @discussion The acceleration structure may be copied to a different Metal device. Buffer
 * properties of the acceleration structure such as the vertex buffer, instance, buffer, etc. are
 * set to nil. Copy these buffers to new Metal device and assign them to the new acceleration
 * structure instead. Do not copy the acceleration structure until any prior refit or rebuild
 * operations have completed.
 *
 * @param zone   This parameter is ignored. Memory zones are no longer used by Objective-C.
 * @param device New Metal device
 */
- (nonnull instancetype)copyWithZone:(nullable NSZone *)zone
                              device:(nullable id <MTLDevice>)device;

/**
 * @brief Create a a copy of this acceleration structure
 *
 * @discussion The acceleration structure may be copied with a different acceleration structure
 * group. Buffer properties of the acceleration structure such as the vertex buffer, instance
 * buffer, etc. are set to nil. Copy these buffers with the new Metal device and assign them to
 * the new acceleration structure instead. Do not copy the acceleration structure until any prior
 * refit or rebuild operations have completed.
 *
 * @param zone  This parameter is ignored. Memory zones are no longer used by Objective-C.
 * @param group New acceleration structure group
 */
- (nonnull instancetype)copyWithZone:(nullable NSZone *)zone
                               group:(nonnull MPSAccelerationStructureGroup *)group;

/**
 * @brief Encode the acceleration structure with an NSCoder
 *
 * @discussion Buffer properties such as the vertex buffer, index buffer, etc. are not be encoded.
 * Encode and decode these buffers along with the acceleration structure instead. Do not encode
 * the acceleration structure until any prior refit or rebuild operations have completed.
 *
 * @param coder An archiver object
 */
- (void)encodeWithCoder:(NSCoder * __nonnull)coder;

@end

#endif
