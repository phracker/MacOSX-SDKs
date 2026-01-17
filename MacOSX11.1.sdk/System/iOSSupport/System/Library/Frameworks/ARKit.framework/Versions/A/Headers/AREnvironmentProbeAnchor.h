//
//  AREnvironmentProbeAnchor.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

@protocol MTLTexture;

NS_ASSUME_NONNULL_BEGIN

/**
 An object representing an environment probe in the world.
 @discussion Environment probes are used to light virtual geometry by producing environment
 textures from the probe's location in the world.
 */
API_AVAILABLE(ios(12.0))
@interface AREnvironmentProbeAnchor : ARAnchor

/**
 The environment texture of the probe.
 @discussion The texture is provided as a cube using MTLTextureTypeCube.
 */
@property (nonatomic, strong, nullable, readonly) id<MTLTexture> environmentTexture;

/**
 The extent of the probe in the anchor's coordinate space.
 @discussion This is the size of the box that is assumed when projecting the environment texture for parallax correction.
 The extent defaults to infinity for probes that do not need parallax correction.
 */
@property (nonatomic, readonly) simd_float3 extent;

/**
 Initializes a new environment probe anchor with the provided transform and extent.
 @param transform The transformation matrix that defines the anchor’s rotation, translation and scale in world coordinates.
 @param extent The extent of the probe in the anchor's coordinate space.
 */
- (instancetype)initWithTransform:(simd_float4x4)transform extent:(simd_float3)extent;

/**
 Initializes a new environment probe anchor with the provided name, transform, and extent.
 @param name A name to associate with the anchor.
 @param transform The transformation matrix that defines the anchor’s rotation, translation and scale in world coordinates.
 @param extent The extent of the probe in the anchor's coordinate space.
 */
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform extent:(simd_float3)extent;

@end

NS_ASSUME_NONNULL_END
