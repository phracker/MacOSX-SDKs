//
//  MPSState.h
//  MPS
//
//  Created by Ian Ollmann on 10/17/16.
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef MPSState_h
#define MPSState_h

#ifdef __cplusplus
extern "C" {
#endif
    
#import <MPSCore/MPSCoreTypes.h>
 
/*!
 *  @class          MPSState
 *  @dependency     This depends on Metal Framework
 *  @abstract       An opaque data container for large storage in MPS CNN filters
 *  @discussion     Some MPS CNN kernels produce additional information beyond a
 *                  MPSImage. These may be pooling indices where the result came from,
 *                  convolution weights, or other information not contained in the
 *                  usual MPSImage result from a MPSCNNKernel. A MPSState object 
 *                  typically contains one or more expensive MTLResources such as 
 *                  textures or buffers to store this information.  It provides a 
 *                  base class with interfaces for managing this storage. Child 
 *                  classes may add additional functionality specific to their
 *                  contents.
 *
 *                  Some MPSState objects are temporary. Temporary state objects, 
 *                  like MPSTemporaryImages and Matrices, are for very short lived storage,
 *                  perhaps just a few lines of code within the scope of a single
 *                  MTLCommandBuffer.  They are very efficient for storage, as several
 *                  temporary objects can share the same memory over the course of a 
 *                  MTLCommandBuffer. This can improve both memory usage and time spent
 *                  in the kernel wiring down memory and such. You may find that some 
 *                  large CNN tasks can not be computed without them, as non-temporary
 *                  storage would simply take up too much memory.
 *
 *                  In exchange, the lifetime of the underlying storage in temporary 
 *                  MPSState objects needs to be carefully managed. ARC often waits 
 *                  until the end of scope to release objects. Temporary storage often 
 *                  needs to be released sooner than that. Consequently the lifetime of 
 *                  the data in the underlying MTLResources is managed by a readCount 
 *                  property. Each time a MPSCNNKernel reads a temporary MPSState object
 *                  the readCount is automatically decremented. When it reaches zero, the
 *                  underlying storage is recycled for use by other MPS temporary objects,
 *                  and the data is becomes undefined.  If you need to consume the data
 *                  multiple times, you should set the readCount to a larger number to 
 *                  prevent the data from becomming undefined.  You may set the readCount
 *                  to 0 yourself to return the storage to MPS, if for any reason, you 
 *                  realize that the MPSState object will no longer be used. 
 *
 *                  The contents of a temporary MPSState object are only valid from 
 *                  creation to the time the readCount reaches 0. The data is only valid 
 *                  for the MTLCommandBuffer on which it was created.  Non-temporary
 *                  MPSState objects are valid on any MTLCommandBuffer on the same
 *                  device until they are released.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSState : NSObject

-(nullable instancetype) init NS_UNAVAILABLE;

/*
 *  @abstract       The number of times temporary data may be read by a MPSCNNKernel
 *                  before its contents become undefined.
 *
 *  @discussion     MPSState must release their underlying resources for reuse
 *                  immediately after last use. So as to facilitate *prompt* convenient
 *                  memory recycling, each time a temporary MPSState is read by a
 *                  MPSCNNKernel -encode... method, its readCount is automatically
 *                  decremented. When the readCount reaches 0, the underlying resources are
 *                  automatically made available for reuse by MPS prior to return from 
 *                  the -encode.. method. Any data stored by the MPSState becomes undefined 
 *                  at this time.
 *
 *                  By default, the readCount is initialized to 1, indicating a image that
 *                  may be overwritten any number of times, but read only once. Non-temporary
 *                  MPSState objects have their readCount initialized to 0. Please use the
 *                  isTemporary method to learn whether a MPSState object is temporary.
 *
 *                  You may change the readCount as desired to allow MPSCNNKernels to read
 *                  the state object additional times. However, it is an error to change
 *                  the readCount once it is zero. It is an error to read or write to a
 *                  temporary MPSState object with a zero readCount. You may set the 
 *                  readCount to 0 yourself to cause the underlying storage to be returned
 *                  to MPS.
 *
 *                  The Metal API Validation layer will assert if a temporary MPSState is
 *                  deallocated with non-zero readCount to help identify cases when resources
 *                  are not returned promptly.
 */
@property (readwrite, nonatomic)  NSUInteger  readCount;

/*
 *  @abstract       Describes whether or not a MPSState object is temporary or not.
 *  
 *  @discussion     Temporary MPSState objects are designed to efficiently share
 *                  memory with other objects on a MTLCommandBuffer. Their valid lifetime
 *                  is limited to the lifetime of a MTLCommandBuffer. The valid lifetime
 *                  of the data that they contain stretches from creation to when their
 *                  readcount reaches 0. Non-temporary MPSState objects can in contrast
 *                  be used at any time with any command buffer, until they are released and
 *                  their reference count reaches 0. (Reference and read counts are different
 *                  things.)  Since the lifetimes of temporary and non-temporary MPSState
 *                  objects vary widely, it can be important to know what sort of state
 *                  object it is so that it can be handled correctly.
 */
@property (readonly, nonatomic) BOOL    isTemporary;


/*!
 *  @property label
 *  @abstract A string to help identify this object.
 */
@property (nullable, copy, atomic) NSString *label;


@end
   
    
#ifdef __cplusplus
}
#endif

#endif /* MPSState_h */
