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
@protocol MTLEvent;

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
} API_AVAILABLE(macos(10.11), ios(8.0));

 /*!
 @constant MTLCommandBufferErrorDomain
 @abstract An error domain for NSError objects produced by MTLCommandBuffer
 */
API_AVAILABLE(macos(10.11), ios(8.0))
MTL_EXTERN NSString *const MTLCommandBufferErrorDomain;

/*!
 @enum MTLCommandBufferError
 @abstract Error codes that can be found in MTLCommandBuffer.error
 
 @constant MTLCommandBufferErrorInternal
 An internal error that doesn't fit into the other categories. The actual low level error code is encoded in the local description.
 
 @constant MTLCommandBufferErrorTimeout
 Execution of this command buffer took too long, execution of this command was interrupted and aborted.
 
 @constant MTLCommandBufferErrorPageFault
 Execution of this command buffer generated an unserviceable GPU page fault. This can caused by buffer read write attribute mismatch or out of boundary access.
 
 @constant MTLCommandBufferErrorBlacklisted
 Access to this device has been revoked because this client has been responsible for too many timeouts or hangs.
 
 @constant MTLCommandBufferErrorNotPermitted
 This process does not have access to use this device.
 
 @constant MTLCommandBufferErrorOutOfMemory
 Insufficient memory was available to execute this command buffer.
 
 @constant MTLCommandBufferErrorInvalidResource
 The command buffer referenced an invalid resource.  This is most commonly caused when the caller deletes a resource before executing a command buffer that refers to it.
 
 @constant MTLCommandBufferErrorMemoryless
 One or more internal resources limits reached that prevent using memoryless render pass attachments. See error string for more detail.
 
 @constant MTLCommandBufferErrorDeviceRemoved
 The device was physically removed before the command could finish execution
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
    MTLCommandBufferErrorMemoryless API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos) = 10,
    MTLCommandBufferErrorDeviceRemoved API_AVAILABLE(macos(10.13)) API_UNAVAILABLE(ios) = 11,
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef void (^MTLCommandBufferHandler)(id <MTLCommandBuffer>);

/*!
 @enum MTLDispatchType
 
 @abstract MTLDispatchType Describes how a command encoder will execute dispatched work.
 
 @constant MTLDispatchTypeSerial
 Command encoder dispatches are executed in dispatched order.
 
 @constant MTLDispatchTypeConcurrent
 Command encoder dispatches are executed in parallel with each other. 
*/

typedef NS_ENUM(NSUInteger, MTLDispatchType){
    MTLDispatchTypeSerial,
    MTLDispatchTypeConcurrent,
}API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @protocol MTLCommandBuffer
 @abstract A serial list of commands for the device to execute.
 */
API_AVAILABLE(macos(10.11), ios(8.0))
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

@property (readonly) CFTimeInterval kernelStartTime API_AVAILABLE(ios(10.3)) API_UNAVAILABLE(macos);
@property (readonly) CFTimeInterval kernelEndTime API_AVAILABLE(ios(10.3)) API_UNAVAILABLE(macos);

/*!
 @property GPUStartTime
 @abstract The host time in seconds that GPU starts executing this command buffer. Returns zero if it has not started. This usually can be called in command buffer completion handler.
 */
@property (readonly) CFTimeInterval GPUStartTime API_AVAILABLE(ios(10.3)) API_UNAVAILABLE(macos);
/*!
 @property GPUEndTime
 @abstract The host time in seconds that GPU finishes executing this command buffer. Returns zero if CPU has not received completion notification. This usually can be called in command buffer completion handler.
 */
@property (readonly) CFTimeInterval GPUEndTime API_AVAILABLE(ios(10.3)) API_UNAVAILABLE(macos);

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
 @discussion The submission thread will be lock stepped with present call been serviced by window server
 */
- (void)presentDrawable:(id <MTLDrawable>)drawable;

/*!
 @method presentDrawable:atTime:
 @abstract Add a drawable present for a specific host time that will be invoked when this command buffer has been scheduled for execution.
 @discussion The submission thread will be lock stepped with present call been serviced by window server
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
- (nullable id <MTLBlitCommandEncoder>)blitCommandEncoder;

/*!
 @method renderCommandEncoderWithDescriptor:
 @abstract returns a render command endcoder to encode into this command buffer.
 */
- (nullable id <MTLRenderCommandEncoder>)renderCommandEncoderWithDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor;

/*!
 @method computeCommandEncoder
 @abstract returns a compute command encoder to encode into this command buffer.
 */
- (nullable id <MTLComputeCommandEncoder>)computeCommandEncoder;
/*! 
 @method computeCommandEncoderWithDispatchType
 @abstract returns a compute command encoder to encode into this command buffer. Optionally allow this command encoder to execute dispatches concurrently.
 @discussion On devices that do not support concurrent command encoders, this call is equivalent to computeCommandEncoder
 */

 - (nullable id<MTLComputeCommandEncoder>)computeCommandEncoderWithDispatchType:(MTLDispatchType) dispatchType API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method encodeWaitForEvent:value:
 @abstract Encodes a command that pauses execution of this command buffer until the specified event reaches a given value.
 @discussion This method may only be called if there is no current command encoder on the receiver.
*/
- (void)encodeWaitForEvent:(id <MTLEvent>)event value:(uint64_t)value API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method encodeSignalEvent:value:
 @abstract Encodes a command that signals an event with a given value.
 @discussion This method may only be called if there is no current command encoder on the receiver.
 */
- (void)encodeSignalEvent:(id <MTLEvent>)event value:(uint64_t)value API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method parallelRenderCommandEncoderWithDescriptor:
 @abstract returns a parallel render pass encoder to encode into this command buffer.
 */
- (nullable id <MTLParallelRenderCommandEncoder>)parallelRenderCommandEncoderWithDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor;


/*!
 @method pushDebugGroup:
 @abstract Push a new named string onto a stack of string labels.
 */
- (void)pushDebugGroup:(NSString *)string API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @method popDebugGroup
 @abstract Pop the latest named string off of the stack.
 */
- (void)popDebugGroup API_AVAILABLE(macos(10.13), ios(11.0));


@end
NS_ASSUME_NONNULL_END
