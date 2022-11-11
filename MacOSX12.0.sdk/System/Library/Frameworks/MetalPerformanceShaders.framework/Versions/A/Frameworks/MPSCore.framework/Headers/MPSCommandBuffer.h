//
//  MPSCommandBuffer.h
//  MPSCore
//
//  Created on 4/15/19.
//  Copyright © 2019 Apple. All rights reserved.
//

#ifndef MPSCommandBuffer_h
#define MPSCommandBuffer_h

#include <MPSCore/MPSCoreTypes.h>

#ifdef __cplusplus
    extern "C" {
#endif

/*!
 *  @class      MPSPredicate
 *  @dependency This depends on Metal.framework
 *  @abstract   A MPSPredicate can be used to run MPS kernels subject to a predicate.
 *  @discussion The MPSPredicate defines a way to refrain running a kernel on the GPU
 *              based on values computed on the GPU. That way one can build control flow operations
 *              that do the decisions on the GPU side mitigating the need to synchronize CPU and GPU
 *              execution. The predicate is used with the version of encode calls that take
 *              a object of type @ref MPSKernelEncodeOptions as a parameter (@see MPSCNNKernel for example).
 *              The code associated with the kernel's encode call is executed on the GPU if and only if
 *              the predicate is considered to be true.
 *              NOTE: It is advisable to release MPSPredicate objects promptly as they take a reference
 *              to a MTLBuffer object and therefore can keep the memory allocated for long periods of time.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSPredicate :  NSObject

/*! @property predicateBuffer
 *  @abstract The buffer that is used as the predicate
 */
@property (readonly, retain, nonatomic, nonnull)  id <MTLBuffer> predicateBuffer;

/*! @property   predicateOffset
 *  @abstract   Location of the predicate in bytes, must be multiple of four.
 *  @discussion If the uint32_t value stored at this location in @ref predicateBuffer is other than zero,
 *              then the predicate is considered to be true and the code is executed on the GPU.
 *              With this property a single MPSPredicate object can be used with multiple different predication
 *              operations.
 *              Default = 0;
 */
@property (readonly, nonatomic) NSUInteger predicateOffset;

/*!
 *  @abstract   Initializes a MPSPredicate object with a buffer and given offset.
 *  @param      buffer      The buffer to use as a predicate.
 *  @param      offset      Byteoffset to the predicate buffer where the predicate is stored.
 *  @result     A pointer to the newly initialized MPSPredicate object.
 */
+(__nonnull instancetype) predicateWithBuffer: (nonnull id <MTLBuffer>)buffer
                                       offset: (NSUInteger) offset;

/*!
 *  @abstract   Initializes a MPSPredicate object with a buffer and given offset.
 *  @param      buffer      The buffer to use as a predicate.
 *  @param      offset      Byteoffset to the predicate buffer where the predicate is stored.
 *  @result     A pointer to the newly initialized MPSPredicate object.
 */
-(nonnull instancetype)  initWithBuffer: (nonnull id <MTLBuffer>)buffer
                                 offset: (NSUInteger) offset
NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract   Initializes a MPSPredicate object for a given device.
 *  @discussion NOTE: The metal buffer used by the resulting MPSPredicate object may be
 *              shared among many MPSPredicate objects and therefore care must be used when
 *              writing to this buffer: writing to any other location in this buffer than the
 *              four bytes at the offset @ref predicateOffset results in undefined behavior.
 *
 *  @param      device      The device the predicate is used with
 *  @result     A pointer to the newly initialized MPSPredicate object.
 */
-(nonnull instancetype)  initWithDevice: (nonnull id <MTLDevice>)device
NS_DESIGNATED_INITIALIZER;

@end /* MPSPredicate */

#pragma mark MPSPredicate
@protocol MPSHeapProvider <NSObject>
@required

/*! @abstract   Return a heap of the size indicated
 *  @discussion The heap may be larger than requested. 
 *              id <MTLDevice> implements this method.
 *  @param      descriptor    A descriptor for the new heap
 *  @return     A new heap of size at least descriptor.size.  If nil is returned, MPS
 *              will use the MPS internal heap cache instead to satisfy the allocation. */
-(nullable id <MTLHeap>) newHeapWithDescriptor: (MTLHeapDescriptor * __nonnull) descriptor;
        
@optional
/*! @abstract   Retire a heap
 *  @discussion When MPS is done with the heap, this is called to return the heap to the heap provider
 *              MPS will release the heap after this is called.
 *  @param      heap                The heap to be retired
 *  @param      seconds          A hint for how long to cache the heap before retiring it.  See MPSSetHeapCacheDuration(). */
-(void) retireHeap: (nonnull id <MTLHeap>) heap
        cacheDelay: (double) seconds;
        
@end /* MPSHeapProvider */




/*!
 *  @class      MPSCommandBuffer
 *  @dependency This depends on Metal.framework
 *  @abstract   A MPSCommandBuffer object is used to wrap an existing command buffer with MPS specific options.
 *  @discussion A MPS kernel typically operates between a fixed set of inputs and outputs.
 *              The MPSCommandBuffer class provides a way to add further encode-time parameters
 *              to the encode call using the command buffer. Currently the only parameter included in the
 *              MPSCommandBuffer that all MPS kernels support is the the predicate option,
 *              which can be used to pre-empt the kernel from the GPU side.
 *              NOTE: the options that contain metal resources will be referenced by this object and
 *              therefore it is advisable to make the lifetime of this object as short as possible as is the
 *              case for all command buffers.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSCommandBuffer : NSObject <MTLCommandBuffer>

/*! @property   commandBuffer
 *  @abstract   The Metal Command Buffer that was used to initialize this object.
 */
@property (readonly, retain, nonatomic, nonnull)  id <MTLCommandBuffer> commandBuffer;

/*! @property   rootCommandBuffer
 *  @abstract   The base MTLCommandBuffer underlying the MPSCommandBuffer
 *  @discussion MPSCommandBuffers may wrap other MPSCommandBuffers, in the process
 *              creating what is in effect a stack of predicate objects that may be
 *              pushed or popped by making new MPSCommandBuffers or by calling -commandBuffer.
 *              In some circumstances, it is preferable to use the root command buffer,
 *              particularly when trying to identify the command buffer that will be commited
 *              by -commitAndContinue. */
@property (readonly, retain, nonatomic, nonnull) id <MTLCommandBuffer> rootCommandBuffer;


/*! @property   predicate
 *  @abstract   A GPU predicate object. Default: nil.
 */
@property (readwrite, retain, nonatomic, nullable)  MPSPredicate * predicate;

/*! @property   heapProvider
 *  @abstract   A application supplied object to allocate MTLHeaps for MPS
 *  @discussion By default this is nil, which will use MPS' device level global heap cache to
 *              allocate the heaps. This is a reasonable choice. However, it may be inefficient
 *              if you are keeping your own MTLHeap, since there will be two pessimistically
 *              sized free stores which may be larger than is strictly necessary, and of course
 *              fragmentation across multiple heaps. In such cases, the problem may be solved
 *              either by using MPS' automatically managed heap (simple) or having MPS use
 *              your heap. The heapProvider allows you to implement the second case.  To use
 *              the MPS heap, simply make temporary MPSImages, vectors and matrices.
 *
 *              If multiple MPSCommandBuffers reference the same MTLCommandBuffer, changing
 *              the heapProvider on one will change the heap provider for all of them. */
@property (readwrite, retain, nonatomic, nullable) id <MPSHeapProvider> heapProvider;

/*!
 *  @abstract   Initializes a MPSCommandBuffer object with given MTLCommandBuffer.
 *              Once we create this MPSCommandBuffer, any methods utilizing it could call commitAndContinue and so the users original commandBuffer may have been committed.
 *              Please use the rootCommandBuffer method to get the current alive underlying MTLCommandBuffer.
 *  @result     A pointer to the newly initialized MPSCommandBuffer object.
 */
+(__nonnull instancetype) commandBufferWithCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer;

/*!
 *  @abstract   Initializes a MPSCommandBuffer object from a given command queue.
 *  @result     A pointer to the newly initialized MPSCommandBuffer object.
 */
+(__nonnull instancetype) commandBufferFromCommandQueue: (nonnull id <MTLCommandQueue>) commandQueue;


/*!
 *  @abstract   Initializes an empty MPSCommandBuffer object with given MTLCommandBuffer.
 *              Once we create this MPSCommandBuffer, any methods utilizing it could call commitAndContinue and so the users original commandBuffer may have been committed.
 *              Please use the rootCommandBuffer method to get the current alive underlying MTLCommandBuffer.
 *  @result     A pointer to the newly initialized MPSCommandBuffer object.
 */
-(nonnull instancetype) initWithCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
NS_DESIGNATED_INITIALIZER;

/*
 * Use initWithCommandBuffer: instead
 */
-(nonnull instancetype) init NS_UNAVAILABLE;

/*!     @abstract   Commit work encoded so far and continue with a new underlying command buffer
 *      @discussion This method commits the underlying root MTLCommandBuffer, and makes
 *                  a new one on the same command queue. The MPS heap is moved forward
 *                  to the new command buffer such that temporary objects used by
 *                  the previous command buffer can be still be used with the new one.
 *
 *                  This provides a way to move work already encoded into consideration
 *                  by the Metal back end sooner. For large workloads, e.g. a neural networking graph
 *                  periodically calling -commitAndContinue may allow you to improve CPU / GPU parallelism
 *                  without the substantial memory increases associated with double buffering.
 *                  It will also help decrease overall latency.
 *
 *                  Any Metal schedule or completion callbacks previously attached to this
 *                  object will remain attached to the old command buffer and
 *                  will fire as expected as the old command buffer is scheduled and
 *                  completes. If your application is relying on such callbacks to coordinate
 *                  retain / release of important objects that are needed for work encoded after
 *                  -commitAndContinue, your application should retain these objects before
 *                  calling commitAndContinue, and attach new release callbacks to this
 *                  object with a new completion handler so that they persist through the
 *                  lifetime of the new underlying command buffer. You may do this, for example
 *                  by adding the objects to a mutable array before calling -commitAndContinue, then
 *                  release the mutable array in a new completion callback added after -commitAndContinue.
 *
 *                  Because -commitAndContinue commits the old command buffer then switches to a new one,
 *                  some aspects of command buffer completion may surprise unwary developers. For example,
 *                  -waitUntilCompleted called immediately after -commitAndContinue asks Metal to wait for
 *                  the new command buffer to finish, not the old one. Since the new command buffer presumably
 *                  hasn't been committed yet, it is formally a deadlock, resources may leak and Metal may
 *                  complain. Your application should ether call -commit before -waitUntilCompleted, or
 *                  capture the -rootCommandBuffer from before the call to -commitAndContinue and wait
 *                  on that.  Similarly, your application should be sure to use the appropriate command buffer
 *                  when querying the [MTLCommandBuffer status] property.
 *
 *                  If the underlying MTLCommandBuffer also implements -commitAndContinue, then the message
 *                  will be forwarded to that object instead. In this way, underlying predicate objects and
 *                  other state will be preserved.
 */
-(void) commitAndContinue;

/*! @abstract   Prefetch heap into the MPS command buffer heap cache.
 *  @discussion If there is not sufficient free storage in the MPS heap for the command buffer for allocations of total size size,
 *              pre-warm the MPS heap with a new MTLHeap allocation of sufficient size.  If this size turns out to be too small
 *              MPS may ask for more heaps later to cover additional allocations. If heapProvider is not nil, the heapProvider
 *              will be used.
 *  @param      size        The minimum size of the free store needed */
-(void) prefetchHeapForWorkloadSize: (size_t) size;

@end /* MPSCommandBuffer */


#ifdef __cplusplus
    }   // extern "C"
#endif

#endif /* MPSCommandBuffer_h */
