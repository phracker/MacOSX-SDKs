//
//  GKNoiseMap.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

@class GKNoiseSource;
@class GKNoise;

NS_ASSUME_NONNULL_BEGIN

/**
 * GKNoiseMap represents an extracted portion of sampled points from continuous 3D noise.  Extracted values are useful
 * for 2D and 3D games.  Noise values may be queried, set to explicit values or used as input for other uses,
 * including textures and tile maps.
 *
 * @see GKNoiseSource
 * @see GKNoise
 * @see SKTexture
 * @see SKTileMapNode
 */
GK_BASE_AVAILABILITY_2 @interface GKNoiseMap : NSObject

/**
 * The size of the 2D plane to extract from the 3D noise space, in noise space coordinates.  Used together
 * with origin to determine the bounds of the extracted plane.  A smaller size captures a more "zoomed in"
 * view of the noise, and vice versa.
 *
 * @see origin
 */
@property (nonatomic, readonly) vector_double2 size;

/**
 * The origin of the 2D plane to extract from the 3D noise space, in noise space coordinates.  Used together
 * with size to determine the bounds of the extracted plane.
 *
 * @see size
 */
@property (nonatomic, readonly) vector_double2 origin;

/**
 * The number of equally-spaced samples to make across the 2D plane.  A higher number of samples produces finer
 * resolution at the expense of increased memory.
 */
@property (nonatomic, readonly) vector_int2 sampleCount;

/**
 * Whether the values at the edges of the 2D plane are modified to allow seamless tiling of the extracted noise map.
 */
@property (nonatomic, readonly, getter=isSeamless) BOOL seamless;

/**
 * Initializes a noise map with constant noise of 0.0 at all positions.
 */
- (instancetype)init;

/**
 * Initializes a noise map with specified noise.
 *
 * @param noise The 3D noise from which to sample a 2D plane.
 */
+ (instancetype)noiseMapWithNoise:(GKNoise *)noise;

/**
 * Initializes a noise map with specified noise and parameters.
 *
 * @param noise The 3D noise from which to sample a 2D plane.
 * @param size The size of the 2D plane to extract from the 3D noise space, in noise space coordinates.
 * @param origin The origin of the 2D plane to extract from the 3D noise space, in noise space coordinates.
 * @param sampleCount The number of equally-spaced samples to make across the 2D plane.
 * @param seamless Whether the values at the edges of the 2D plane are modified to allow seamless tiling of the extracted noise map.
 */
+ (instancetype)noiseMapWithNoise:(GKNoise *)noise size:(vector_double2)size origin:(vector_double2)origin sampleCount:(vector_int2)sampleCount seamless:(BOOL)seamless;

/**
 * Initializes a noise map with specified noise.
 *
 * @param noise The 3D noise from which to sample a 2D plane.
 */
- (instancetype)initWithNoise:(GKNoise *)noise;

/**
 * Initializes a noise map with specified noise and parameters.
 *
 * @param noise The 3D noise from which to sample a 2D plane.
 * @param size The size of the 2D plane to extract from the 3D noise space, in noise space coordinates.
 * @param origin The origin of the 2D plane to extract from the 3D noise space, in noise space coordinates.
 * @param sampleCount The number of equally-spaced samples to make across the 2D plane.
 * @param seamless Whether the values at the edges of the 2D plane are modified to allow seamless tiling of the extracted noise map.
 */
- (instancetype)initWithNoise:(GKNoise *)noise size:(vector_double2)size origin:(vector_double2)origin sampleCount:(vector_int2)sampleCount seamless:(BOOL)seamless NS_DESIGNATED_INITIALIZER;

/**
 * The noise map value at the specified sample index of the 2D plane.
 *
 * @param position Sample index of the extracted 2D plane at which to query the value.  Valid range
 * is from 0 to sampleCount-1, inclusive.
 *
 * @return The noise map value at the specified sample index.
 */
- (float)valueAtPosition:(vector_int2)position;

/**
 * The noise map value at the specified sample point of the 2D plane.  Returns an interpolated value for
 * points not aligned on integer boundaries.
 *
 * @param position Sample point of the extracted 2D plane at which to query the value.  Valid range
 * is from 0.0 to sampleCount-1.0, inclusive.
 *
 * @return The noise map value at the specified sample index. Returns an interpolated value for points not
 * aligned on integer boundaries.
 */
- (float)interpolatedValueAtPosition:(vector_float2)position;

/**
 * Sets the specified value to the noise map at the specified sample index of the 2D plane.
 *
 * @param value The noise map value to assign to the specified position.
 * @param position Sample index of the extracted 2D plane at which to set the value.  Valid range
 * is from 0 to sampleCount-1, inclusive.
 *
 */
- (void)setValue:(float)value atPosition:(vector_int2)position;

@end

NS_ASSUME_NONNULL_END
