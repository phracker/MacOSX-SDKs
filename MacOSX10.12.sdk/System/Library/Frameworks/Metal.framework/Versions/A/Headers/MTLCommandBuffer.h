//
//  MTLCommandBuffer.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;
@protocol MTLCommandQueue;
@protocol MTLBlitCommandEncoder;
@protocol MTLRenderCommandEncoder;
@protocol MTLParallelRenderCommandEncoder;
@protocol MTLComputeCommandEncoder;
@protocol MTLCommandQueue;
@protocol MTLDrawable;
@protocol MTLCommandBuffer;

@class MTLRenderPassDescriptor;

/*!
 @enum MTLCommandBufferStatus
 
 @abstract MTLCommandBufferStatus reports the current stage in the lifetime of MTLCommandBuffer, as it proceeds to enqueued, committed, scheduled, and completed.
 
 @constant MTLCommandBufferStatusNotEnqueued
 The command buffer has not been enqueued yet.
 
 @constant MTLCommandBufferStatusEnqueued
 This command buffer is enqueued, but not committed.
 
 @constant MTLCommandBufferStatusCommitted
 Commited to its command queue, but not yet scheduled for execution.
 
 @constant MTLCommandBufferStatusScheduled
 All dependencies have been resolved and the command buffer has been scheduled for execution.
 
 @constant MTLCommandBufferStatusCompleted
 The command buffer has finished executing successfully: any blocks set with -addCompletedHandler: may now be called.
 
 @constant MTLCommandBufferStatusError
 Execution of the command buffer was aborted due to an error during execution.  Check -error for more information.
 */
typedef NS_ENUM(NSUInteger, MTLCommandBufferStatus) {
    MTLCommandBufferStatusNotEnqueued = 0,
    MTLCommandBufferStatusEnqueued = 1,
    MTLCommandBufferStatusCommitted = 2,
    MTLCommandBufferStatusScheduled = 3,
    MTLCommandBufferStatusCompleted = 4,
    MTLCommandBufferStatusError = 5,
} NS_ENUM_AVAILABLE(10_11, 8_0);

 /*!
 @constant MTLCommandBufferErrorDomain
 @abstract An error domain for NSError objects produced by MTLCommandBuffer
 */
NS_AVAILABLE(10_11, 8_0)
MTL_EXTERN NSString *const MTLCommandBufferErrorDomain;

/*!
 @enum MTLCommandBufferError
 @abstract Error codes that can be found in MTLCommandBuffer.error
 @constant MTLCommandBufferErrorInternal An internal error that doesn't fit into the other categories. The actual low level error code is encoded in the local description.
 @constant MTLCommandBufferErrorTimeout Execution of this command buffer took too long, execution of this command was interrupted and aborted.
 @constant MTLCommandBufferErrorPageFault Execution of this command buffer generated an unserviceable GPU page fault. This can caused by buffer read write attribute mismatch or out of boundary access.
 @constant MTLCommandBufferErrorBlacklisted Access to this device has been revoked because this client has been responsible for too many timeouts or hangs.
 @constant MTLCommandBufferErrorNotPermitted This process does not have access to use this device.
 @constant MTLCommandBufferErrorOutOfMemory Insufficient memory was available to execute this command buffer.
 @constant MTLCommandBufferErrorInvalidResource The command buffer referenced an invalid resource.  This is most commonly caused when the caller deletes a resource before executing a command buffer that refers to it.
 @constant MTLCommandBufferErrorMemoryless One or more internal resources limits reached that prevent using memoryless render pass attachments. See error string for more detail.
 */
typedef NS_ENUM(NSUInteger, MTLCommandBufferError)
{
    MTLCommandBufferErrorNone = 0,
    MTLCommandBufferErrorInternal = 1,
    MTLCommandBufferErrorTimeout = 2,
    MTLCommandBufferErrorPageFault = 3,
    MTLCommandBufferErrorBlacklisted = 4,
    MTLCommandBufferErrorNotPermitted = 7,
    MTLCommandBufferErrorOutOfMemory = 8,
    MTLCommandBufferErrorInvalidResource = 9,
    MTLCommandBufferErrorMemoryless NS_AVAILABLE_IOS(10_0) = 10 ,
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef void (^MTLCommandBufferHandler)(id <MTLCommandBuffer>);

/*!
 @protocol MTLCommandBuffer
 @abstract A serial list of commands for the device to execute.
 */
NS_AVAILABLE(10_11, 8_0)
@protocol MTLCommandBuffer <NSObject>

/*!
 @property device
 @abstract The device this resource was created against.
 */
@property (readonly) id <MTLDevice> device;

/*!
 @property commandQueue
 @abstract The command queue this command buffer was created from.
 */
@property (readonly) id <MTLCommandQueue> commandQueue;

/*!
 @property retainedReferences
 @abstract If YES, this command buffer holds strong references to objects needed to execute this command buffer.
 */
@property (readonly) BOOL retainedReferences;

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, copy, atomic) NSString *label;

/*!
 @method enqueue
 @abstract Append this command buffer to the end of its MTLCommandQueue.
*/
- (void)enqueue;

/*!
 @method commit
 @abstract Commit a command buffer so it can be executed as soon as possible.
 */
- (void)commit;

/*!
 @method addScheduledHandler:block:
 @abstract Adds a block to be called when this command buffer has been scheduled for execution.
 */
- (void)addScheduledHandler:(MTLCommandBufferHandler)block;

/*!
 @method presentDrawable:
 @abstract Add a drawable present that will be invoked when this command buffer has been scheduled for execution.
 */
- (void)presentDrawable:(id <MTLDrawable>)drawable;

/*!
 @method presentDrawable:atTime:
 @abstract Add a drawable present for a specific host time that will be invoked when this command buffer has been scheduled for execution.
 */
- (void)presentDrawable:(id <MTLDrawable>)drawable atTime:(CFTimeInterval)presentationTime;


/*!
 @method waitUntilScheduled
 @abstract Synchronously wait for this command buffer to be scheduled.
 */
- (void)waitUntilScheduled;

/*!
 @method addCompletedHandler:block:
 @abstract Add a block to be called when this command buffer has completed execution.
 */
- (void)addCompletedHandler:(MTLCommandBufferHandler)block;

/*!
 @method waitUntilCompleted
 @abstract Synchronously wait for this command buffer to complete.
 */
- (void)waitUntilCompleted;

/*!
 @property status
 @abstract status reports the current stage in the lifetime of MTLCommandBuffer, as it proceeds to enqueued, committed, scheduled, and completed.
 */
@property (readonly) MTLCommandBufferStatus status;

/*!
 @property error
 @abstract If an error occurred during execution, the NSError may contain more details about the problem.
 */
@property (nullable, readonly) NSError *error;

/*!
 @method blitCommandEncoder
 @abstract returns a blit command encoder to encode into this command buffer.
 */
- (id <MTLBlitCommandEncoder>)blitCommandEncoder;

/*!
 @method renderCommandEncoderWithDescriptor:
 @abstract returns a render command endcoder to encode into this command buffer.
 */
- (id <MTLRenderCommandEncoder>)renderCommandEncoderWithDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor;

/*!
 @method computeCommandEncoder
 @abstract returns a compute command encoder to encode into this command buffer.
 */
- (id <MTLComputeCommandEncoder>)computeCommandEncoder;


/*!
 @method parallelRenderCommandEncoderWithDescriptor:
 @abstract returns a parallel render pass encoder to encode into this command buffer.
 */
- (id <MTLParallelRenderCommandEncoder>)parallelRenderCommandEncoderWithDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor;

@end
NS_ASSUME_NONNULL_END
