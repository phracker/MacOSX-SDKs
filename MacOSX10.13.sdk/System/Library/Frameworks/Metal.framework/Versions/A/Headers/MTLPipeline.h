//
//  MTLPipeline.h
//  Metal
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Metal/MTLDevice.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @enum MTLMutability
 * @abstract Specifies whether a buffer will be modified between the time it is bound and a compute
 * or render pipeline is executed in a draw or dispatch.
 */
typedef NS_ENUM(NSUInteger, MTLMutability)
{
    MTLMutabilityDefault   = 0,
    MTLMutabilityMutable   = 1,
    MTLMutabilityImmutable = 2,
} NS_ENUM_AVAILABLE(10_13, 11_0);

NS_CLASS_AVAILABLE(10_13, 11_0)
@interface MTLPipelineBufferDescriptor : NSObject <NSCopying>

/*! Buffer mutability. Defaults to MTLMutabilityDefault: mutable for standard buffers, immutable for argument buffers */
@property (nonatomic) MTLMutability mutability;

@end

NS_CLASS_AVAILABLE(10_13, 11_0)
@interface MTLPipelineBufferDescriptorArray : NSObject
/* Individual buffer descriptor access */
- (MTLPipelineBufferDescriptor *)objectAtIndexedSubscript:(NSUInteger)bufferIndex;

/* This always uses 'copy' semantics. It is safe to set the buffer descriptor at any legal index to nil, which resets that buffer descriptor to default vaules. */
- (void)setObject:(nullable MTLPipelineBufferDescriptor *)buffer atIndexedSubscript:(NSUInteger)bufferIndex;

@end

NS_ASSUME_NONNULL_END
