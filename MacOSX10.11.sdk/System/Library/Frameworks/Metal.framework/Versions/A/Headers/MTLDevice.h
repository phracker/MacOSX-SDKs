//
//  MTLDevice.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

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

/*!
 @brief Returns a reference to the preferred system default Metal device.
 @discussion On Mac OS X systems that support automatic graphics switching, calling
 this API to get a Metal device will cause the system to switch to the high power
 GPU.  On other systems that support more than one GPU it will return the GPU that
 is associated with the main display.
 */
MTL_EXTERN id <MTLDevice> __nullable MTLCreateSystemDefaultDevice(void) NS_AVAILABLE(10_11, 8_0);

/*!
 @brief Returns all Metal devices in the system.
 @discussion This API will not cause the system to switch devices and leaves the
 decision about which GPU to use up to the application based on whatever criteria
 it deems appropriate.
*/
MTL_EXTERN NSArray <id<MTLDevice>> *MTLCopyAllDevices(void) NS_AVAILABLE_MAC(10_11);


typedef NS_ENUM(NSUInteger, MTLFeatureSet)
{
    MTLFeatureSet_iOS_GPUFamily1_v1 NS_ENUM_AVAILABLE_IOS(8_0) = 0,
    MTLFeatureSet_iOS_GPUFamily2_v1 NS_ENUM_AVAILABLE_IOS(8_0) = 1,
    
    MTLFeatureSet_iOS_GPUFamily1_v2 NS_ENUM_AVAILABLE_IOS(9_0) = 2,
    MTLFeatureSet_iOS_GPUFamily2_v2 NS_ENUM_AVAILABLE_IOS(9_0) = 3,

    MTLFeatureSet_OSX_GPUFamily1_v1 NS_ENUM_AVAILABLE_MAC(10_11)   = 10000,
} NS_ENUM_AVAILABLE(10_11, 8_0);

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

/* Convenience typedefs that make it easy to declare storage for certain return types. */
typedef __autoreleasing MTLRenderPipelineReflection * __nullable MTLAutoreleasedRenderPipelineReflection;
typedef __autoreleasing MTLComputePipelineReflection * __nullable MTLAutoreleasedComputePipelineReflection;

typedef void (^MTLNewLibraryCompletionHandler)(id <MTLLibrary> __nullable library, NSError * __nullable error);

typedef void (^MTLNewRenderPipelineStateCompletionHandler)(id <MTLRenderPipelineState> __nullable renderPipelineState, NSError * __nullable error);
typedef void (^MTLNewRenderPipelineStateWithReflectionCompletionHandler)(id <MTLRenderPipelineState> __nullable renderPipelineState, MTLRenderPipelineReflection * __nullable reflection, NSError * __nullable error);

typedef void (^MTLNewComputePipelineStateCompletionHandler)(id <MTLComputePipelineState> __nullable computePipelineState, NSError * __nullable error);
typedef void (^MTLNewComputePipelineStateWithReflectionCompletionHandler)(id <MTLComputePipelineState> __nullable computePipelineState, MTLComputePipelineReflection * __nullable reflection, NSError * __nullable error);

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
@property (nullable, readonly) NSString *name;

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
 @property depth24Stencil8PixelFormatSupported
 @abstract If YES, device supports MTLPixelFormatDepth24Unorm_Stencil8.
 */
@property (readonly, getter=isDepth24Stencil8PixelFormatSupported) BOOL depth24Stencil8PixelFormatSupported NS_AVAILABLE_MAC(10_11);

/*!
 @method newCommandQueue
 @brief Create and return a new command queue.   Command Queues created via this method will only allow up to 64 non-completed command buffers.
 @return The new command queue object
 */
- (id <MTLCommandQueue>)newCommandQueue;

/*!
 @method newCommandQueueWithMaxCommandBufferCount
 @brief Create and return a new command queue with a given upper bound on non-completed command buffers.
 @return The new command queue object
 */
- (id <MTLCommandQueue>)newCommandQueueWithMaxCommandBufferCount:(NSUInteger)maxCommandBufferCount;

/*!
 @method newBufferWithLength:options:
 @brief Create a buffer by allocating new memory.
 */
- (id <MTLBuffer>)newBufferWithLength:(NSUInteger)length options:(MTLResourceOptions)options;

/*!
 @method newBufferWithBytes:length:options:
 @brief Create a buffer by allocating new memory and specifing the initial contents to be copied into it.
 */
- (id <MTLBuffer>)newBufferWithBytes:(const void *)pointer length:(NSUInteger)length options:(MTLResourceOptions)options;

/*!
 @method newBufferWithBytesNoCopy:length:options:deallocator:
 @brief Create a buffer by wrapping an existing part of the address space.
 */
- (id <MTLBuffer>)newBufferWithBytesNoCopy:(void *)pointer length:(NSUInteger)length options:(MTLResourceOptions)options deallocator:(void (^ __nullable)(void *pointer, NSUInteger length))deallocator;

/*!
 @method newDepthStencilStateWithDescriptor:
 @brief Create a depth/stencil test state object.
 */
- (id <MTLDepthStencilState>)newDepthStencilStateWithDescriptor:(MTLDepthStencilDescriptor *)descriptor;

/*!
 @method newTextureWithDescriptor:
 @abstract Allocate a new texture with privately owned storage.
 */
- (id <MTLTexture>)newTextureWithDescriptor:(MTLTextureDescriptor *)descriptor;

/*!
 @method newTextureWithDescriptor:iosurface:plane
 @abstract Create a new texture from an IOSurface.
 @param descriptor A description of the properties for the new texture.
 @param iosurface The IOSurface to use as storage for the new texture.
 @param plane The plan within the IOSurface to use.
 @return A new texture object.
 */
- (id <MTLTexture>)newTextureWithDescriptor:(MTLTextureDescriptor *)descriptor iosurface:(IOSurfaceRef)iosurface plane:(NSUInteger)plane NS_AVAILABLE_MAC(10_11);

/*!
 @method newSamplerStateWithDescriptor:
 @abstract Create a new sampler.
*/
- (id <MTLSamplerState>)newSamplerStateWithDescriptor:(MTLSamplerDescriptor *)descriptor;

/*!
 @method newDefaultLibrary
 @abstract Returns the default library for the main bundle.
 */
- (nullable id <MTLLibrary>)newDefaultLibrary;

/*!
 @method newLibraryWithFile:
 @abstract Load a MTLLibrary from a metallib file.
 */
- (nullable id <MTLLibrary>)newLibraryWithFile:(NSString *)filepath error:(__autoreleasing NSError **)error;

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

@end
NS_ASSUME_NONNULL_END

