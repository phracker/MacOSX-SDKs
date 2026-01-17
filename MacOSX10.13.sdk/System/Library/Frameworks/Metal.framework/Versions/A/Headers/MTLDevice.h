//
//  MTLDevice.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLTypes.h>
#import <Metal/MTLPixelFormat.h>
#import <Metal/MTLResource.h>
#import <Metal/MTLLibrary.h>
#import <IOSurface/IOSurface.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLCommandQueue;
@protocol MTLDevice;
@protocol MTLBuffer;
@protocol MTLDepthStencilState;
@protocol MTLFunction;
@protocol MTLLibrary;
@protocol MTLTexture;
@protocol MTLSamplerState;
@protocol MTLRenderPipelineState;
@protocol MTLComputePipelineState;
@protocol MTLHeap;
@protocol MTLFence;
@protocol MTLArgumentEncoder;
@class MTLSamplerDescriptor;
@class MTLRenderPipelineColorAttachmentDescriptor;
@class MTLDepthStencilDescriptor;
@class MTLTextureDescriptor;
@class MTLCompileOptions;
@class MTLRenderPipelineDescriptor;
@class MTLRenderPassDescriptor;
@class MTLRenderPipelineReflection;
@class MTLComputePipelineDescriptor;
@class MTLComputePipelineReflection;
@class MTLCommandQueueDescriptor;
@class MTLHeapDescriptor;

/*!
 @brief Returns a reference to the preferred system default Metal device.
 @discussion On Mac OS X systems that support automatic graphics switching, calling
 this API to get a Metal device will cause the system to switch to the high power
 GPU.  On other systems that support more than one GPU it will return the GPU that
 is associated with the main display.
 */
MTL_EXTERN id <MTLDevice> __nullable MTLCreateSystemDefaultDevice(void) NS_AVAILABLE(10_11, 8_0) NS_RETURNS_RETAINED;

/*!
 @brief Returns all Metal devices in the system.
 @discussion This API will not cause the system to switch devices and leaves the
 decision about which GPU to use up to the application based on whatever criteria
 it deems appropriate.
*/
MTL_EXTERN NSArray <id<MTLDevice>> *MTLCopyAllDevices(void) NS_AVAILABLE_MAC(10_11) NS_RETURNS_RETAINED;

/*!
 @brief Type for device notifications
*/
typedef NSString *MTLDeviceNotificationName NS_STRING_ENUM NS_AVAILABLE_MAC(10_13);

/*!
 @brief This notification is posted when a new Metal device is added to the system
*/
MTL_EXTERN MTLDeviceNotificationName const MTLDeviceWasAddedNotification NS_AVAILABLE_MAC(10_13);

/*!
 @brief This notification is posted when the user has requested that applications cease using a particular device.  Applications
 should assume that the device will be removed (terminated) imminently.  Additionally, the device will be removed from the internal
 device array prior to this notification being posted.  Applications should immediately begin the process of releasing all resources
 created on the given device, as well as any references to the device itself.
*/
MTL_EXTERN MTLDeviceNotificationName const MTLDeviceRemovalRequestedNotification NS_AVAILABLE_MAC(10_13);

/*!
 @brief This notification is posted once the device has been removed.  Applications must expect that any attempt to use
 the device at this point will fail.  This includes creating new device specific objects of any kind.   Also, this notification
 may be posted without a prior MTLDeviceRemovalRequestedNotification notification in the case of unexpected removal.
*/
MTL_EXTERN MTLDeviceNotificationName const MTLDeviceWasRemovedNotification NS_AVAILABLE_MAC(10_13);

/*!
 @brief Block signature for device notifications
 */
typedef void (^MTLDeviceNotificationHandler)(id <MTLDevice> device, MTLDeviceNotificationName notifyName);

/*!
 @brief Returns an NSArray of the current set of available Metal devices and installs a notification handler
 to be notified of any further changes (additions, removals, etc.).  The observer return value is retained by Metal and may be
 passed to MTLRemoveDeviceObserver() if the application no longer wishes to receive notifications.
*/
MTL_EXTERN NSArray <id<MTLDevice>> *MTLCopyAllDevicesWithObserver(id <NSObject> __nullable * __nonnull observer, MTLDeviceNotificationHandler handler) NS_AVAILABLE_MAC(10_13) NS_RETURNS_RETAINED;

/*!
 @brief Removes a previously installed observer for device change notifications.
*/
MTL_EXTERN void MTLRemoveDeviceObserver(id <NSObject> observer) NS_AVAILABLE_MAC(10_13);

typedef NS_ENUM(NSUInteger, MTLFeatureSet)
{
    MTLFeatureSet_iOS_GPUFamily1_v1 NS_ENUM_AVAILABLE_IOS(8_0) __TVOS_UNAVAILABLE = 0,
    MTLFeatureSet_iOS_GPUFamily2_v1 NS_ENUM_AVAILABLE_IOS(8_0) __TVOS_UNAVAILABLE = 1,

    MTLFeatureSet_iOS_GPUFamily1_v2 NS_ENUM_AVAILABLE_IOS(9_0) __TVOS_UNAVAILABLE = 2,
    MTLFeatureSet_iOS_GPUFamily2_v2 NS_ENUM_AVAILABLE_IOS(9_0) __TVOS_UNAVAILABLE = 3,
    MTLFeatureSet_iOS_GPUFamily3_v1 NS_ENUM_AVAILABLE_IOS(9_0) __TVOS_UNAVAILABLE = 4,

    MTLFeatureSet_iOS_GPUFamily1_v3 NS_ENUM_AVAILABLE_IOS(10_0) __TVOS_UNAVAILABLE = 5,
    MTLFeatureSet_iOS_GPUFamily2_v3 NS_ENUM_AVAILABLE_IOS(10_0) __TVOS_UNAVAILABLE = 6,
    MTLFeatureSet_iOS_GPUFamily3_v2 NS_ENUM_AVAILABLE_IOS(10_0) __TVOS_UNAVAILABLE = 7,

    MTLFeatureSet_iOS_GPUFamily1_v4 NS_ENUM_AVAILABLE_IOS(11_0) __TVOS_UNAVAILABLE = 8,
    MTLFeatureSet_iOS_GPUFamily2_v4 NS_ENUM_AVAILABLE_IOS(11_0) __TVOS_UNAVAILABLE = 9,
    MTLFeatureSet_iOS_GPUFamily3_v3 NS_ENUM_AVAILABLE_IOS(11_0) __TVOS_UNAVAILABLE = 10,

    MTLFeatureSet_macOS_GPUFamily1_v1 NS_ENUM_AVAILABLE_MAC(10_11) = 10000,
    MTLFeatureSet_OSX_GPUFamily1_v1 NS_ENUM_AVAILABLE_MAC(10_11) = MTLFeatureSet_macOS_GPUFamily1_v1, // deprecated

    MTLFeatureSet_macOS_GPUFamily1_v2 NS_ENUM_AVAILABLE_MAC(10_12) = 10001,
    MTLFeatureSet_OSX_GPUFamily1_v2 NS_ENUM_AVAILABLE_MAC(10_12) = MTLFeatureSet_macOS_GPUFamily1_v2, // deprecated
    MTLFeatureSet_macOS_ReadWriteTextureTier2 NS_ENUM_AVAILABLE_MAC(10_12) = 10002,
    MTLFeatureSet_OSX_ReadWriteTextureTier2 NS_ENUM_AVAILABLE_MAC(10_12) = MTLFeatureSet_macOS_ReadWriteTextureTier2, // deprecated

    MTLFeatureSet_macOS_GPUFamily1_v3 NS_ENUM_AVAILABLE_MAC(10_13) = 10003,


    MTLFeatureSet_tvOS_GPUFamily1_v1 __TVOS_AVAILABLE(9_0) __IOS_UNAVAILABLE __OSX_UNAVAILABLE = 30000,
    MTLFeatureSet_TVOS_GPUFamily1_v1 __TVOS_AVAILABLE(9_0) __IOS_UNAVAILABLE __OSX_UNAVAILABLE = MTLFeatureSet_tvOS_GPUFamily1_v1, // deprecated

    MTLFeatureSet_tvOS_GPUFamily1_v2 __TVOS_AVAILABLE(10_0) __IOS_UNAVAILABLE __OSX_UNAVAILABLE = 30001,

    MTLFeatureSet_tvOS_GPUFamily1_v3 __TVOS_AVAILABLE(11_0) __IOS_UNAVAILABLE __OSX_UNAVAILABLE = 30002,
} NS_ENUM_AVAILABLE(10_11, 8_0) __TVOS_AVAILABLE(9_0);

/*!
 @enum MTLPipelineOption
 @abstract Controls the creation of the pipeline
 */
typedef NS_OPTIONS(NSUInteger, MTLPipelineOption)
{
    MTLPipelineOptionNone               = 0,
    MTLPipelineOptionArgumentInfo       = 1 << 0,
    MTLPipelineOptionBufferTypeInfo     = 1 << 1,
} NS_ENUM_AVAILABLE(10_11, 8_0);

/*!
 @enum MTLReadWriteTextureTier
 @abstract MTLReadWriteTextureTier determines support level for read-write texture formats.
 */
typedef NS_ENUM(NSUInteger, MTLReadWriteTextureTier)
{
    MTLReadWriteTextureTierNone = 0,
    MTLReadWriteTextureTier1 = 1,
    MTLReadWriteTextureTier2 = 2,
} NS_ENUM_AVAILABLE(10_13, 11_0);

/*!
 @enum MTLArgumentBuffersTier
 @abstract MTLArgumentBuffersTier determines support level for argument buffers.
 */
typedef NS_ENUM(NSUInteger, MTLArgumentBuffersTier)
{
    MTLArgumentBuffersTier1 = 0,
    MTLArgumentBuffersTier2 = 1,
} NS_ENUM_AVAILABLE(10_13, 11_0);


/*!
 @abstract Represent a memory size and alignment in bytes.
 */
typedef struct {
    NSUInteger size;
    NSUInteger align;
} MTLSizeAndAlign;

/* Convenience typedefs that make it easy to declare storage for certain return types. */
typedef __autoreleasing MTLRenderPipelineReflection * __nullable MTLAutoreleasedRenderPipelineReflection;
typedef __autoreleasing MTLComputePipelineReflection * __nullable MTLAutoreleasedComputePipelineReflection;

typedef void (^MTLNewLibraryCompletionHandler)(id <MTLLibrary> __nullable library, NSError * __nullable error);

typedef void (^MTLNewRenderPipelineStateCompletionHandler)(id <MTLRenderPipelineState> __nullable renderPipelineState, NSError * __nullable error);
typedef void (^MTLNewRenderPipelineStateWithReflectionCompletionHandler)(id <MTLRenderPipelineState> __nullable renderPipelineState, MTLRenderPipelineReflection * __nullable reflection, NSError * __nullable error);

typedef void (^MTLNewComputePipelineStateCompletionHandler)(id <MTLComputePipelineState> __nullable computePipelineState, NSError * __nullable error);
typedef void (^MTLNewComputePipelineStateWithReflectionCompletionHandler)(id <MTLComputePipelineState> __nullable computePipelineState, MTLComputePipelineReflection * __nullable reflection, NSError * __nullable error);


/*!
 * @class MTLArgumentDescriptor
 * @abstract Represents a member of an argument buffer
 */
NS_CLASS_AVAILABLE(10_13, 11_0)
@interface MTLArgumentDescriptor : NSObject <NSCopying>

/*!
 * @method argumentDescriptor
 * @abstract Create an autoreleased default argument descriptor
 */
+ (MTLArgumentDescriptor *)argumentDescriptor;

/*!
 * @property dataType
 * @abstract For constants, the data type. Otherwise, MTLDataTypeTexture, MTLDataTypeSampler, or
 * MTLDataTypePointer.
 */
@property (nonatomic) MTLDataType dataType;

/*!
 * @property index
 * @abstract The binding point index of the argument
 */
@property (nonatomic) NSUInteger index;

/*!
 * @property arrayLength
 * @abstract The length of an array of constants, textures, or samplers, or 0 for non-array arguments
 */
@property (nonatomic) NSUInteger arrayLength;

/*!
 * @property access
 * @abstract Access flags for the argument
 */
@property (nonatomic) MTLArgumentAccess access;

/*!
 * @property textureType
 * @abstract For texture arguments, the texture type
 */
@property (nonatomic) MTLTextureType textureType;

/*!
 @property constantBlockAlignment
 @abstract if set forces the constant block to be aligned to the given alignment
 @discussion Should only be set on the first constant of the block and is only valid if a corresponding
     explicit "alignas" is applied to the constant in the metal shader language.
 */
@property (nonatomic) NSUInteger constantBlockAlignment;

@end



/*!
 @protocol MTLDevice
 @abstract MTLDevice represents a processor capable of data parallel computations
 */
NS_AVAILABLE(10_11, 8_0)
@protocol MTLDevice <NSObject>

/*!
 @property name
 @abstract The full name of the vendor device.
 */
@property (nonnull, readonly) NSString *name;

/*!
 @property registryID
 @abstract Returns the IORegistry ID for the Metal device
 @discussion The registryID value for a Metal device is global to all tasks, and may be used
 to identify the GPU across task boundaries.
*/
@property (readonly) uint64_t registryID NS_AVAILABLE(10_13, 11_0) ;

/*!
 @property maxThreadsPerThreadgroup
 @abstract The maximum number of threads along each dimension.
 */
@property (readonly) MTLSize maxThreadsPerThreadgroup NS_AVAILABLE(10_11, 9_0);

/*!
 @property lowPower
 @abstract On systems that support automatic graphics switching, this will return YES for the the low power device.
 */
@property (readonly, getter=isLowPower) BOOL lowPower NS_AVAILABLE_MAC(10_11);

/*!
 @property headless
 @abstract On systems that include more that one GPU, this will return YES for any device that does not support any displays.  Only available on Mac OS X.
 */
@property (readonly, getter=isHeadless) BOOL headless NS_AVAILABLE_MAC(10_11);

/*!
 @property removable
 @abstract If this GPU is removable, this property will return YES.  
 @discussion If a GPU is is removed without warning, APIs may fail even with good input, even before a notification can get posted informing
 the application that the device has been removed.
 */
@property (readonly, getter=isRemovable) BOOL removable NS_AVAILABLE_MAC(10_13);

/*!
 @property recommendedMaxWorkingSetSize
 @abstract Returns an approximation of how much memory this device can use with good performance.
 @discussion Performance may be improved by keeping the total size of all resources (texture and buffers)
 and heaps less than this threshold, beyond which the device is likely to be overcommitted and incur a
 performance penalty. */
@property (readonly) uint64_t recommendedMaxWorkingSetSize NS_AVAILABLE_MAC(10_12);

/*!
 @property depth24Stencil8PixelFormatSupported
 @abstract If YES, device supports MTLPixelFormatDepth24Unorm_Stencil8.
 */
@property (readonly, getter=isDepth24Stencil8PixelFormatSupported) BOOL depth24Stencil8PixelFormatSupported NS_AVAILABLE_MAC(10_11);

/*!
 @property readWriteTextureSupport
 @abstract Query support tier for read-write texture formats.
 @return MTLReadWriteTextureTier enum value.
 */
@property (readonly) MTLReadWriteTextureTier readWriteTextureSupport NS_AVAILABLE(10_13, 11_0);

/*!
 @property argumentBuffersSupport
 @abstract Query support tier for Argument Buffers.
 @return MTLArgumentBuffersTier enum value.
 */
@property (readonly) MTLArgumentBuffersTier argumentBuffersSupport NS_AVAILABLE(10_13, 11_0);


/*!
 @property rasterOrderGroupsSupported
 @abstract Query device for raster order groups support.
 @return BOOL value. If YES, the device supports raster order groups. If NO, the device does not.
 */
@property (readonly, getter=areRasterOrderGroupsSupported) BOOL rasterOrderGroupsSupported NS_AVAILABLE(10_13, 11_0);


/*!
 @property currentAllocatedSize
 @abstract The current size in bytes of all resources allocated by this device
 */
@property (readonly) NSUInteger currentAllocatedSize NS_AVAILABLE(10_13, 11_0);

/*!
 @method newCommandQueue
 @brief Create and return a new command queue.   Command Queues created via this method will only allow up to 64 non-completed command buffers.
 @return The new command queue object
 */
- (nullable id <MTLCommandQueue>)newCommandQueue;

/*!
 @method newCommandQueueWithMaxCommandBufferCount
 @brief Create and return a new command queue with a given upper bound on non-completed command buffers.
 @return The new command queue object
 */
- (nullable id <MTLCommandQueue>)newCommandQueueWithMaxCommandBufferCount:(NSUInteger)maxCommandBufferCount;

/*!
 @method heapTextureSizeAndAlignWithDescriptor:
 @abstract Determine the byte size of textures when sub-allocated from a heap.
 @discussion This method can be used to help determine the required heap size.
 */
- (MTLSizeAndAlign)heapTextureSizeAndAlignWithDescriptor:(MTLTextureDescriptor *)desc NS_AVAILABLE(10_13, 10_0);

/*!
 @method heapBufferSizeAndAlignWithLength:options:
 @abstract Determine the byte size of buffers when sub-allocated from a heap.
 @discussion This method can be used to help determine the required heap size.
 */
- (MTLSizeAndAlign)heapBufferSizeAndAlignWithLength:(NSUInteger)length options:(MTLResourceOptions)options NS_AVAILABLE(10_13, 10_0);

/*!
 @method newHeapWithDescriptor:
 @abstract Create a new heap with the given descriptor.
 */
- (nullable id <MTLHeap>)newHeapWithDescriptor:(MTLHeapDescriptor *)descriptor NS_AVAILABLE(10_13, 10_0);

/*!
 @method newBufferWithLength:options:
 @brief Create a buffer by allocating new memory.
 */
- (nullable id <MTLBuffer>)newBufferWithLength:(NSUInteger)length options:(MTLResourceOptions)options;

/*!
 @method newBufferWithBytes:length:options:
 @brief Create a buffer by allocating new memory and specifing the initial contents to be copied into it.
 */
- (nullable id <MTLBuffer>)newBufferWithBytes:(const void *)pointer length:(NSUInteger)length options:(MTLResourceOptions)options;

/*!
 @method newBufferWithBytesNoCopy:length:options:deallocator:
 @brief Create a buffer by wrapping an existing part of the address space.
 */
- (nullable id <MTLBuffer>)newBufferWithBytesNoCopy:(void *)pointer length:(NSUInteger)length options:(MTLResourceOptions)options deallocator:(void (^ __nullable)(void *pointer, NSUInteger length))deallocator;

/*!
 @method newDepthStencilStateWithDescriptor:
 @brief Create a depth/stencil test state object.
 */
- (nullable id <MTLDepthStencilState>)newDepthStencilStateWithDescriptor:(MTLDepthStencilDescriptor *)descriptor;

/*!
 @method newTextureWithDescriptor:
 @abstract Allocate a new texture with privately owned storage.
 */
- (nullable id <MTLTexture>)newTextureWithDescriptor:(MTLTextureDescriptor *)descriptor;

/*!
 @method newTextureWithDescriptor:iosurface:plane
 @abstract Create a new texture from an IOSurface.
 @param descriptor A description of the properties for the new texture.
 @param iosurface The IOSurface to use as storage for the new texture.
 @param plane The plan within the IOSurface to use.
 @return A new texture object.
 */
- (nullable id <MTLTexture>)newTextureWithDescriptor:(MTLTextureDescriptor *)descriptor iosurface:(IOSurfaceRef)iosurface plane:(NSUInteger)plane NS_AVAILABLE(10_11, 11_0);

/*!
 @method newSamplerStateWithDescriptor:
 @abstract Create a new sampler.
*/
- (nullable id <MTLSamplerState>)newSamplerStateWithDescriptor:(MTLSamplerDescriptor *)descriptor;

/*!
 @method newDefaultLibrary
 @abstract Returns the default library for the main bundle.
 @discussion use newDefaultLibraryWithBundle:error: to get an NSError in case of failure.
 */
- (nullable id <MTLLibrary>)newDefaultLibrary;

/*
 @method newDefaultLibraryWithBundle:error:
 @abstract Returns the default library for a given bundle.
 @return A pointer to the library, nil if an error occurs.
*/
- (nullable id <MTLLibrary>)newDefaultLibraryWithBundle:(NSBundle *)bundle error:(__autoreleasing NSError **)error NS_AVAILABLE(10_12, 10_0);

/*!
 @method newLibraryWithFile:
 @abstract Load a MTLLibrary from a metallib file.
 */
- (nullable id <MTLLibrary>)newLibraryWithFile:(NSString *)filepath error:(__autoreleasing NSError **)error;

/*!
 @method newLibraryWithURL:
 @abstract Load a MTLLibrary from a metallib file.
 */
- (nullable id <MTLLibrary>)newLibraryWithURL:(NSURL *)url error:(__autoreleasing NSError **)error NS_AVAILABLE(10_13, 11_0);

/*!
 @method newLibraryWithData:
 @abstract Load a MTLLibrary from a dispatch_data_t
 @param data A metallib file already loaded as data in the form of dispatch_data_t.
 @param error An error if we fail to open the metallib data.
 */
- (nullable id <MTLLibrary>)newLibraryWithData:(dispatch_data_t)data error:(__autoreleasing NSError **)error;

/*!
 @method newLibraryWithSource:options:error:
 @abstract Load a MTLLibrary from source.
 */
- (nullable id <MTLLibrary>)newLibraryWithSource:(NSString *)source options:(nullable MTLCompileOptions *)options error:(__autoreleasing NSError **)error;

/*!
 @method newLibraryWithSource:options:completionHandler:
 @abstract Load a MTLLibrary from source.
 */
- (void)newLibraryWithSource:(NSString *)source options:(nullable MTLCompileOptions *)options completionHandler:(MTLNewLibraryCompletionHandler)completionHandler;

/*!
 @method newRenderPipelineStateWithDescriptor:error:
 @abstract Create and compile a new MTLRenderPipelineState object synchronously.
 */
- (nullable id <MTLRenderPipelineState>)newRenderPipelineStateWithDescriptor:(MTLRenderPipelineDescriptor *)descriptor error:(__autoreleasing NSError **)error;

/*!
 @method newRenderPipelineStateWithDescriptor:options:reflection:error:
 @abstract Create and compile a new MTLRenderPipelineState object synchronously and returns additional reflection information.
 */
- (nullable id <MTLRenderPipelineState>)newRenderPipelineStateWithDescriptor:(MTLRenderPipelineDescriptor *)descriptor options:(MTLPipelineOption)options reflection:(MTLAutoreleasedRenderPipelineReflection * __nullable)reflection error:(__autoreleasing NSError **)error;

/*!
 @method newRenderPipelineState:completionHandler:
 @abstract Create and compile a new MTLRenderPipelineState object asynchronously.
 */
- (void)newRenderPipelineStateWithDescriptor:(MTLRenderPipelineDescriptor *)descriptor completionHandler:(MTLNewRenderPipelineStateCompletionHandler)completionHandler;

/*!
 @method newRenderPipelineState:options:completionHandler:
 @abstract Create and compile a new MTLRenderPipelineState object asynchronously and returns additional reflection information
 */
- (void)newRenderPipelineStateWithDescriptor:(MTLRenderPipelineDescriptor *)descriptor options:(MTLPipelineOption)options completionHandler:(MTLNewRenderPipelineStateWithReflectionCompletionHandler)completionHandler;

/*!
 @method newComputePipelineStateWithDescriptor:error:
 @abstract Create and compile a new MTLComputePipelineState object synchronously.
 */
- (nullable id <MTLComputePipelineState>)newComputePipelineStateWithFunction:(id <MTLFunction>)computeFunction error:(__autoreleasing NSError **)error;

/*!
 @method newComputePipelineStateWithDescriptor:options:reflection:error:
 @abstract Create and compile a new MTLComputePipelineState object synchronously.
 */
- (nullable id <MTLComputePipelineState>)newComputePipelineStateWithFunction:(id <MTLFunction>)computeFunction options:(MTLPipelineOption)options reflection:(MTLAutoreleasedComputePipelineReflection * __nullable)reflection error:(__autoreleasing NSError **)error;

/*!
 @method newComputePipelineStateWithDescriptor:completionHandler:
 @abstract Create and compile a new MTLComputePipelineState object asynchronously.
 */
- (void)newComputePipelineStateWithFunction:(id <MTLFunction>)computeFunction completionHandler:(MTLNewComputePipelineStateCompletionHandler)completionHandler;

/*!
 @method newComputePipelineStateWithDescriptor:options:completionHandler:
 @abstract Create and compile a new MTLComputePipelineState object asynchronously.
 */
- (void)newComputePipelineStateWithFunction:(id <MTLFunction>)computeFunction options:(MTLPipelineOption)options completionHandler:(MTLNewComputePipelineStateWithReflectionCompletionHandler)completionHandler;

/*!
 @method newComputePipelineStateWithDescriptor:options:reflection:error:
 @abstract Create and compile a new MTLComputePipelineState object synchronously.
 */
- (nullable id <MTLComputePipelineState>)newComputePipelineStateWithDescriptor:(MTLComputePipelineDescriptor *)descriptor options:(MTLPipelineOption)options reflection:(MTLAutoreleasedComputePipelineReflection * __nullable)reflection error:(__autoreleasing NSError **)error NS_AVAILABLE(10_11, 9_0);

/*!
 @method newComputePipelineStateWithDescriptor:options:completionHandler:
 @abstract Create and compile a new MTLComputePipelineState object asynchronously.
 */
- (void)newComputePipelineStateWithDescriptor:(MTLComputePipelineDescriptor *)descriptor options:(MTLPipelineOption)options completionHandler:(MTLNewComputePipelineStateWithReflectionCompletionHandler)completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 @method newFence
 @abstract Create a new MTLFence object
 */
- (nullable id <MTLFence>)newFence NS_AVAILABLE(10_13, 10_0);

/*!
 @method supportsFeatureSet:
 @abstract Returns TRUE if the feature set is supported by this MTLDevice.
 */
- (BOOL)supportsFeatureSet:(MTLFeatureSet)featureSet;

/*!
 @method supportsTextureSampleCount:
 @brief Query device if it support textures with a given sampleCount.
 @return BOOL value. If YES, device supports the given sampleCount for textures. If NO, device does not support the given sampleCount.
 */
- (BOOL)supportsTextureSampleCount:(NSUInteger)sampleCount NS_AVAILABLE(10_11, 9_0);

/*!
 @method minimumLinearTextureAlignmentForPixelFormat:
 @abstract Returns the minimum alignment required for offset and rowBytes when creating a linear texture. An error is thrown for queries with invalid pixel formats (depth, stencil, or compressed formats).
 */
- (NSUInteger)minimumLinearTextureAlignmentForPixelFormat:(MTLPixelFormat)format NS_AVAILABLE(10_13, 10_0);

/*!
 @property maxThreadgroupMemoryLength
 @abstract The maximum threadgroup memory available, in bytes.
 */
@property (readonly) NSUInteger maxThreadgroupMemoryLength NS_AVAILABLE(10_13, 11_0);

/*!
 @property programmableSaplePositionsSupported
 @abstract Query device for programmable sample position support.
 @return BOOL value. If YES, the device supports programmable sample positions. If NO, the device does not.
 */
@property (readonly, getter=areProgrammableSamplePositionsSupported) BOOL programmableSamplePositionsSupported NS_AVAILABLE(10_13, 11_0);

/*!
 @method getDefaultSamplePositions:count:
 @abstract Retrieve the default sample positions.
 @param positions The destination array for default sample position data.
 @param count Specifies the sample count for which to retrieve the default positions, the length of the positions array, and must be set to a valid sample count.
 */
- (void)getDefaultSamplePositions:(MTLSamplePosition *)positions count:(NSUInteger)count NS_AVAILABLE(10_13, 11_0);


/*!
 * @method newArgumentEncoderWithArguments:count:
 * @abstract Creates an argument encoder for an array of argument descriptors which will be encoded sequentially.
 */
- (nullable id <MTLArgumentEncoder>)newArgumentEncoderWithArguments:(NSArray <MTLArgumentDescriptor *> *)arguments NS_AVAILABLE(10_13, 11_0);




@end
NS_ASSUME_NONNULL_END
