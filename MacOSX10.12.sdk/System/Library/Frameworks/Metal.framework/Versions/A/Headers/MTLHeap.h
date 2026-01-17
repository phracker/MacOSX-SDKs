//
//  MTLHeap.h
//  Metal
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLResource.h>
#import <Metal/MTLBuffer.h>
#import <Metal/MTLTexture.h>
#import <Metal/MTLTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class MTLHeapDescriptor
 */
NS_CLASS_AVAILABLE(NA, 10_0)
@interface MTLHeapDescriptor : NSObject <NSCopying>

/*!
 @property size
 @abstract Requested size of the heap's backing memory.
 @discussion The size may be rounded up to GPU page granularity.
 */
@property (readwrite, nonatomic) NSUInteger size;

/*!
 @property storageMode
 @abstract Storage mode for the heap. Default is MTLStorageModePrivate.
 @discussion All resources created from this heap share the same storage mode.
 MTLStorageModeManaged and MTLStorageModeMemoryless are disallowed.
 */
@property (readwrite, nonatomic) MTLStorageMode storageMode;

/*!
 @property cpuCacheMode
 @abstract CPU cache mode for the heap. Default is MTLCPUCacheModeDefaultCache.
 @discussion All resources created from this heap share the same cache mode.
 CPU cache mode is ignored for MTLStorageModePrivate.
 */
@property (readwrite, nonatomic) MTLCPUCacheMode cpuCacheMode;

@end

/*!
 @protocol MTLHeap
 */
NS_AVAILABLE(NA, 10_0)
@protocol MTLHeap <NSObject>

/*!
 @property label
 @abstract A string to help identify this heap.
 */
@property (nullable, copy, atomic) NSString *label;

/*!
 @property device
 @abstract The device this heap was created against. This heap can only be used with this device.
 */
@property (readonly) id <MTLDevice> device;

/*!
 @property storageMode
 @abstract Current heap storage mode, default is MTLStorageModePrivate.
 @discussion All resources created from this heap share the same storage mode.
 */
@property (readonly) MTLStorageMode storageMode;

/*!
 @property cpuCacheMode
 @abstract CPU cache mode for the heap. Default is MTLCPUCacheModeDefaultCache.
 @discussion All resources created from this heap share the same cache mode.
 */
@property (readonly) MTLCPUCacheMode cpuCacheMode;

/*!
 @property size
 @abstract Heap size in bytes, specified at creation time and rounded up to device specific alignment.
 */
@property (readonly) NSUInteger size;


/*!
 @property usedSize
 @abstract The size in bytes, of all resources allocated from the heap.
 */
@property (readonly) NSUInteger usedSize;

/*!
 @method maxAvailableSizeWithAlignment:
 @abstract The maximum size that can be successfully allocated from the heap in bytes, taking into notice given alignment. Alignment needs to be zero, or power of two.
 @discussion Provides a measure of fragmentation within the heap.
 */
- (NSUInteger)maxAvailableSizeWithAlignment:(NSUInteger)alignment;

/*!
 @method newBufferWithLength:options:
 @abstract Create a new buffer backed by heap memory.
 @discussion The requested storage and CPU cache modes must match the storage and CPU cache modes of the heap.
 @return The buffer or nil if heap is full.
 */
- (id <MTLBuffer>)newBufferWithLength:(NSUInteger)length 
                              options:(MTLResourceOptions)options;

/*!
 @method newTextureWithDescriptor:
 @abstract Create a new texture backed by heap memory.
 @discussion The requested storage and CPU cache modes must match the storage and CPU cache modes of the heap, with the exception that the requested storage mode can be MTLStorageModeMemoryless. 
 @return The texture or nil if heap is full.
 */
- (id <MTLTexture>)newTextureWithDescriptor:(MTLTextureDescriptor *)desc;

/*!
 @method setPurgeabilityState:
 @abstract Set or query the purgeability state of the heap.
 */
- (MTLPurgeableState)setPurgeableState:(MTLPurgeableState)state;

@end

NS_ASSUME_NONNULL_END
