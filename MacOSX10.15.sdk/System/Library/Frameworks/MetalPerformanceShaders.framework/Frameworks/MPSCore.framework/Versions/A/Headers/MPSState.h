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
 
@class MPSImage;
@class MPSKernel;
@class MPSImageDescriptor;
    
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface MPSStateResourceList : NSObject
/*! @abstract Init an empty autoreleased resource list */
+(nonnull instancetype) resourceList;

/*! @abstract Init a resource list with a nil terminated list of MTLTextureDescriptors */
+(nonnull instancetype) resourceListWithTextureDescriptors: (MTLTextureDescriptor *__nonnull) d, ...
                            NS_REQUIRES_NIL_TERMINATION;

/*! @abstract Init a resource list with a 0 terminated list of Buffer Sizes */
+(nonnull instancetype) resourceListWithBufferSizes: (NSUInteger) firstSize, ...
                            NS_REQUIRES_NIL_TERMINATION;

/*! @abstract Init an empty list */
-(nonnull instancetype) init;

/*! @abstract append a texture to the resource list */
-(void) appendTexture: (MTLTextureDescriptor * __nonnull) descriptor;

/*! @abstract append a buffer to the resource list */
-(void) appendBuffer: (NSUInteger) size;

@end
    
typedef struct MPSStateTextureInfo
{
    NSUInteger          width;          // MTLTexture.width
    NSUInteger          height;         // MTLTexture.height
    NSUInteger          depth;          // MTLTexture.depth
    NSUInteger          arrayLength;    // MTLTexture.arrayLength
    MTLPixelFormat      pixelFormat;    // MTLTexture.pixelFormat
    MTLTextureType      textureType;    // MTLTexture.textureType
    MTLTextureUsage     usage;          // MTLTexture.usage
    
    NSUInteger          _reserved[4];
}MPSStateTextureInfo;
    
#if defined(DOXYGEN)
    typedef enum MPSStateResourceType
#else
    typedef NS_ENUM(NSUInteger, MPSStateResourceType)
#endif
    {
        MPSStateResourceTypeNone            MPS_ENUM_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3)) MPS_SWIFT_NAME(none)  = 0,
        MPSStateResourceTypeBuffer          MPS_ENUM_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))  = 1,
        MPSStateResourceTypeTexture         MPS_ENUM_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))  = 2,
    }
#if defined(DOXYGEN)
    MPSStateResourceType
#endif
;


/*!
 *  @class          MPSState
 *  @dependency     This depends on Metal Framework
 *  @abstract       A semi-opaque data container for large storage in MPS CNN filters
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
 *
 *
 *                  Finally, temporary MPSState objects are complicated to use with blit encoders.
 *                  Your application should assume that the temporary MPSState is backed by a MTLHeap,
 *                  and consequently needs a MTLFence to ensure that compute command encoders and other
 *                  encoders do not trip over one another with heap based memory. MPS will almost never
 *                  use a blit encoder for this reason. If you do need one, then you will need to make
 *                  a new compute encoder to block on whatever previous compute encoder last used the
 *                  heap block. (MPS will not tell you who previously used the heap block. That encoder
 *                  is almost certainly long dead anyway.) If concurrent encoders are involved, then a
 *                  barrier might be needed. Within that compute encoder, you will call -updateFence.
 *                  End the compute encoder, make a blit encoder wait for the fence, do the blit, update
 *                  a new fence, then make a new compute encoder, wait for the second fence, then you
 *                  can continue. Possibly the second do-nothing compute encoder needs to be ended so
 *                  MPS can be called. Frankly, we don't bother with blit encoders and just write a compute
 *                  operation for copy / clear as needed, or better yet find a way to eliminate the
 *                  clear / copy pass so we don't have to pay for it. Your application needs to use
 *                  temporary MPSStates and MPSTemporaryImages. Memory costs skyrocket, otherwise.
 *                  It is the blit encoder that is hopefully optional. Note: the most common use of a
 *                  blit encoder, -synchronizeResource: can not encounter this problem because temporary
 *                  images and states live in GPU private memory and can not be read by the CPU.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface MPSState : NSObject

/******************************
 *  States with one resource  *
 ******************************/

/*! @abstract Create a MPSState holding a temporary MTLBuffer
 *  @param   cmdBuf     The command buffer against which the temporary resource is allocated
 *  @param   bufferSize The size of the buffer in bytes
 */
+(nonnull instancetype) temporaryStateWithCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                                             bufferSize: (size_t) bufferSize;

/*! @abstract Create a MPSState holding a temporary MTLTexture
 *  @param   cmdBuf     The command buffer against which the temporary resource is allocated
 *  @param   descriptor A descriptor for the new temporary texture
 */
+(nonnull instancetype) temporaryStateWithCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                                      textureDescriptor: (MTLTextureDescriptor * __nonnull) descriptor;

/*! @abstract Create a new autoreleased temporary state object without underlying resource
    @param cmdBuf  The command buffer with which the temporary resource is associated */
+(nonnull instancetype) temporaryStateWithCommandBuffer:(__nonnull id<MTLCommandBuffer>)cmdBuf;

-(nonnull instancetype) initWithDevice: (__nonnull id <MTLDevice>) device
                            bufferSize: (size_t) bufferSize;
-(nonnull instancetype) initWithDevice: (__nonnull id <MTLDevice>) device
                     textureDescriptor: (MTLTextureDescriptor * __nonnull) descriptor;

/*! @abstract Create a MPSState with a non-temporary MTLResource
 *  @param      resource    A MTLBuffer or MTLTexture. May be nil.  */
-(nonnull instancetype) initWithResource: (__nullable id <MTLResource>) resource;
-(nullable instancetype) init NS_UNAVAILABLE;



/*! @abstract       Initialize a non-temporary state to hold a number of textures and buffers
 *  @discussion     The allocation of each resource will be deferred  until it is needed.
 *                  This occurs when -resource or -resourceAtIndex: is called.
 *  @param          resourceList The list of resources to create. */
-(nonnull instancetype) initWithDevice: (__nonnull id <MTLDevice>) device
                          resourceList: (MPSStateResourceList * __nonnull) resourceList
        MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @abstract       Initialize a temporary state to hold a number of textures and buffers
 *  @discussion     The textures occur first in sequence*/
 +(nonnull instancetype) temporaryStateWithCommandBuffer: (__nonnull id <MTLCommandBuffer>) commandBuffer
                                            resourceList: (MPSStateResourceList * __nonnull) resourceList
        MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));
 
/*! @abstract Create a state object with a list of MTLResources
 *  @discussion     Because MPS prefers deferred allocation of resources
 *                  your application should use -initWithTextures:bufferSizes:bufferCount:
 *                  whenever possible. This method is useful for cases when the
 *                  MTLResources must be initialized by the CPU. */
-(nonnull instancetype) initWithResources: (NSArray<id <MTLResource>>*__nullable) resources;


/*! @abstract   Return the number of MTLResource objects held by the state */
@property (readonly, nonatomic)  NSUInteger resourceCount;

/*! @abstract   Get the MTLResource at the indicated index
 *  @discussion  By convention, except where otherwise documented, the MTLResources
 *               held by the MPSState are private to the MPSState object, owned
 *               by the MPSState subclass author. If the MPSState subclass
 *               author is MPS, then the identity (e.g. texture vs. buffer)
 *               and information contained in the resource should be considered
 *               implementation dependent. It may change by operating system
 *               version or device. If you are the author of the subclass then it
 *               is for your own use, and MPS will not look at it, except perhaps
 *               so as to pass it to a custom kernel.  Otherwise, the method is made
 *               available to facilitate debugging and to allow you to write your own
 *               state objects. Provide accessors to read this information
 *               in a defined format.
 *
 *  @param  index   The index of the MTLResource to retrieve
 *  @param  allocateMemory  It is very important to avoid allocating memory to hold
 *               MTLResources until it is absolutely necessary, especially when working
 *               with temporary MPSStates. When allocateMemory is set to NO and the
 *               resource has not yet been allocated, nil will be returned instead.
 *               If you just need information about the resource such as buffer size
 *               or MTLTexture properties, but not the resource itself, please use
 *               -bufferSizeAtIndex: or -textureInfoAtIndex: instead, as these will
 *               not force the creation of the MTLResource.
 */
-(__nullable id <MTLResource>) resourceAtIndex: (NSUInteger) index
                                allocateMemory: (BOOL) allocateMemory;


/*******************
 *   All states    *
 *******************/
#pragma mark -
#pragma mark All MPSStates

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
 *
 *                  ReadCount behavior for MPSStateBatches:
 *                      In some cases, the same state object is used for the entire batch.
 *                  This is common when the filter needs to accumulate state over an entire
 *                  batch, such as during weight update for convolution or statistics accumulation
 *                  in batch normalization. In such cases, the single MPSState accumulator
 *                  is represented as a MPSStateBatch with batch.count pointers to the same
 *                  MPSState object.  When MPS decrements the read count on states or images
 *                  in a batch it only does so on unique objects. Your application should follow
 *                  the same convention. MPSStateBatchIncrementReadCount() is provided to help you.
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
 *                  object it is so that it can be handled correctly.  MPSStates without
 *                  a resource are not temporary.
 */
@property (readonly, nonatomic) BOOL    isTemporary;


/*!
 *  @property label
 *  @abstract A string to help identify this object.
 */
@property (nullable, copy, atomic) NSString *label;


/*! @abstract Return the buffer size of the MTLBuffer at index or 0 if it is not a MTLBuffer
 *  @discussion Does not force allocation of the MTLResource */
-(NSUInteger) bufferSizeAtIndex: (NSUInteger) index;

/*! @abstract Return the texture size {width,height,depth} or {0,0,0} if it is not a MTLTexture
 *  @discussion Does not force allocation of the MTLResource */
-(MPSStateTextureInfo) textureInfoAtIndex: (NSUInteger) index;

/*! @abstract Return YES if the resource at index is a buffer
 *  @discussion Does not force allocation of the MTLResource */
-(MPSStateResourceType) resourceTypeAtIndex:(NSUInteger) index;


/*! @abstract   Flush any copy of MTLResources held by the state from the device's caches, and invalidate any CPU caches if needed.
 *  @discussion This will call [id <MTLBlitEncoder> synchronizeResource: ] on the state's MTLResources.
 *              This is necessary for all MTLStorageModeManaged resources. For other resources, including temporary
 *              resources (these are all MTLStorageModePrivate), nothing is done.
 *  @param      commandBuffer       The commandbuffer on which to synchronize   */
-(void) synchronizeOnCommandBuffer: (__nonnull id <MTLCommandBuffer>) commandBuffer
            MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @abstract       Get the number of bytes used to allocate underyling MTLResources
 *  @discussion     This is the size of the backing store of underlying MTLResources.
 *                  It does not include all storage used by the object, for example
 *                  the storage used to hold the MPSState instantiation and MTLTexture
 *                  or MTLBuffer is not included. It only measures the size of the
 *                  allocation used to hold the texels in the texture or bytes in the
 *                  buffer. This value is subject to change between different devices
 *                  and operating systems.
 *
 *                  Except when -initWithResource: is used, most MPSStates are allocated
 *                  without a backing store. The backing store is allocated lazily when
 *                  it is needed, typically when the .texture property is called.
 *                  Consequently, in most cases, it should be inexpensive to make
 *                  a MPSImage to see how much memory it will need, and release it
 *                  if it is too large.
 *
 *                  This method may fail in certain circumstances, such as when the
 *                  MPSImage is created with -initWithTexture:featureChannels:, in
 *                  which case 0 will be returned.
 */
-(NSUInteger)  resourceSize
        MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));


/*! @abstract       Determine padding and sizing of result images
 *  @discussion     A MPSState has the opportunity to reconfigure the MPSImageDescriptor
 *                  used to create the filter result state and set the MPSKernel.offset
 *                  to the correct value.  By default, the MPSState does not modify the
 *                  descriptor.
 *
 *                  There is a order of operations defined for who may update the descriptor:
 *
 *                      1) Default padding code runs based on the MPSNNPaddingMethod in
 *                          the MPSCNNKernel.padding. This creates the descriptor and
 *                          picks a starting value for the MPSCNNKernel.offset.
 *                      2) MPSStates are called in order to apply this function and update
 *                          the offset.
 *                      3) The MPSNNPadding custom padding method of the same name is called.
 *                      4)
 *
 *
 *                  Some code that may prove helpful:
 *
 *                  @code
 *                  const int centeringPolicy = 0;  // When kernelSize is even: 0 pad bottom right. 1 pad top left.    Centers the kernel for even sized kernels.
 *
 *                  typedef enum Style{
 *                      StyleValidOnly = -1,
 *                      StyleSame = 0,
 *                      StyleFull = 1
 *                  }Style;
 *
 *                  // Typical destination size in one dimension for forward filters (most filters)
 *                  static int DestSize( int sourceSize, int stride, int filterWindowSize, Style style ){
 *                      sourceSize += style * (filterWindowSize - 1);       // adjust how many pixels we are allowed to read
 *                      return (sourceSize + stride - 1) / stride;          // sourceSize / stride, round up
 *                  }
 *
 *                  // Typical destination size in one dimension for reverse filters (e.g. convolution transpose)
 *                  static int DestSizeReverse( int sourceSize, int stride, int filterWindowSize, Style style ){
 *                      return (sourceSize-1) * stride +        // center tap for the last N-1 results. Take stride into account
 *                              1 +                             // center tap for the first result
 *                              style * (filterWindowSize-1);   // add or subtract (or ignore) the filter extent
 *                  }
 *
 *                  // Find the MPSOffset in one dimension
 *                  static int Offset( int sourceSize, int stride, int filterWindowSize, Style style ){
 *                      // The correction needed to adjust from position of left edge to center per MPSOffset definition
 *                      int correction = filterWindowSize / 2;
 *
 *                      // exit if all we want is to start consuming pixels at the left edge of the image.
 *                      if( 0 )
 *                          return correction;
 *
 *                      // Center the area consumed in the source image:
 *                      // Calculate the size of the destination image
 *                      int destSize = DestSize( sourceSize, stride, filterWindowSize, style ); // use DestSizeReverse here instead as appropriate
 *
 *                      // calculate extent of pixels we need to read in source to populate the destination
 *                      int readSize = (destSize-1) * stride + filterWindowSize;
 *
 *                      // calculate number of missing pixels in source
 *                      int extraSize = readSize - sourceSize;
 *
 *                      // number of missing pixels on left side
 *                      int leftExtraPixels = (extraSize + centeringPolicy) / 2;
 *
 *                      // account for the fact that the offset is based on the center pixel, not the left edge
 *                      return correction - leftExtraPixels;
 *                  }
 *                  @endcode
 *
 *  @param          sourceImages        The list of source images to be used
 *  @param          sourceStates        The list of source states to be used
 *  @param          kernel              The MPSKernel the padding method will be applied to. Set the kernel.offset
 *  @param          inDescriptor        MPS will prepare a starting guess based on the padding policy (exclusive of
 *                                      MPSNNPaddingMethodCustom) set for the object. You should adjust the offset
 *                                      and image size accordingly. It is on an autoreleasepool.
 *
 *  @return         The MPSImageDescriptor to use to make a MPSImage to capture the results from the filter.
 *                  The MPSImageDescriptor is assumed to be on an autoreleasepool. Your method must also set the
 *                  kernel.offset property.
 */
-(MPSImageDescriptor * __nonnull) destinationImageDescriptorForSourceImages: (NSArray <MPSImage *> *__nonnull) sourceImages
                                                               sourceStates: (NSArray <MPSState *> * __nullable) sourceStates
                                                                  forKernel: (MPSKernel * __nonnull) kernel
                                                        suggestedDescriptor: (MPSImageDescriptor * __nonnull) inDescriptor;




/*! @abstract Get the private MTLResource underlying the MPSState
 *  @discussion  When the state is not directly initialized with a MTLResource,
 *               the actuall MTLResource creation is deferred. Especially with
 *               temporary resources, it is important to delay this creation
 *               as late as possible to avoid increasing the memory footprint.
 *               The memory is returned for reuse when the readCount = 0. Calling
 *               the -resource method will force the resource to be allocated,
 *               so you should not use it lightly, for purposes such as finding
 *               the MTLPixelFormat of a texture in the state.
 *
 *               By convention, except where otherwise documented, the MTLResources
 *               held by the MPSState are private to the MPSState object, owned
 *               by the MPSState subclass author. If the MPSState subclass
 *               author is MPS, then the identity (e.g. texture vs. buffer)
 *               and information contained in the resource should be considered
 *               implementation dependent. It may change by operating system
 *               version or device. If you are the author of the subclass then it
 *               is for your own use, and MPS will not look at it, except perhaps
 *               so as to pass it to a custom kernel.  Otherwise, the method is made
 *               available to facilitate debugging and to allow you to write your own
 *               state objects.
 */
@property (readonly, nonatomic, retain, nullable) id <MTLResource> resource
    MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "Please use -resourceAtIndex:allocateMemory: instead",
        macos(10.13, 10.13.4), ios(11.0,12.0), tvos(11.0, 12.0))  MPS_UNAVAILABLE(macCatalyst);


@end
   
typedef NSArray<MPSState*>  MPSStateBatch;
    
/*! @abstract raise or lower the readcount of a batch by a set amount
 *  @discussion     In some circumstances, a MPSState may appear in a MPSStateBatch
 *                  multiple times. This is particularly common when the MPSState serves
 *                  as an accumulator across the entire batch, such as when accumulating
 *                  gradients for convolution weight update or batch statistics for
 *                  batch normalization.  A naive function would then end up incrementing
 *                  the state multiple times, probably leading to an error.
 *
 *                  MPSStateBatchIncrementReadCount() will efficiently increment the
 *                  readCounts of each object in the batch only once, avoiding this problem.
 *
 *  @param  batch   The MPSStateBatch to increment
 *  @param  amount  The value to add to the read count for each unique state in the batch
 *  @return  The number of different objects in the batch
 */
NSUInteger MPSStateBatchIncrementReadCount( MPSStateBatch * __nullable batch, NSInteger amount )
     MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));
    
/*! @abstract Call [MTLBlitEncoder synchronizeResource:] on unique resources */
void MPSStateBatchSynchronize( MPSStateBatch * __nonnull batch, __nonnull id <MTLCommandBuffer> cmdBuf )
    MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @abstract Call [MTLBlitEncoder resourceSize] on unique resources */
NSUInteger MPSStateBatchResourceSize( MPSStateBatch * __nullable batch )
    MPS_AVAILABLE_STARTING( macos(10.14.0), ios(12.0), macCatalyst(13.0), tvos(12.0));

#ifdef __cplusplus
}
#endif

#endif /* MPSState_h */
