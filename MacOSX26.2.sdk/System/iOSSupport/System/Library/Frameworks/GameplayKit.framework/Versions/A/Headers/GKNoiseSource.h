//
//  GKNoiseSource.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A GKNoiseSource instance is a description of procedural noise in 3D space.  Noise sources generate values
 * between -1.0 and 1.0, inclusive, for any position in continuous 3D space.
 * Subclasses represent specific types of noise, each with their own parameters that affect the nature of the noise.
 * Noise sources are the starting point for generating and using procedural noise.  The 3D noise values may be manipulated and
 * combined with the GKNoise class.  Portions of this 3D noise can be extracted and utilized via the GKNoiseMap class.
 * Extracted portions of noise are useful in both 2D and 3D games.  Applications include creating realistic textures,
 * height maps for 2D and 3D game world terrain, tile maps for 2D games, and intentionally imperfect game object and
 * camera movements in 2D and 3D games.
 * This class is not intended to be instantiated.
 *
 * @see GKNoise
 * @see GKNoiseMap
 */
GK_BASE_AVAILABILITY_2 @interface GKNoiseSource : NSObject

@end

/**
 * Coherent noise is smoothly-changing, semi-random noise.  A given input always produces the same output.
 * A small change in input produces a small change in output.  A large change in input produces a random
 * change in output. This class is not intended to be instantiated.
 */
GK_BASE_AVAILABILITY_2 @interface GKCoherentNoiseSource : GKNoiseSource

@property (nonatomic) double frequency;
@property (nonatomic) NSInteger octaveCount;
@property (nonatomic) double lacunarity;
@property (nonatomic) int32_t seed;

@end

/**
 * Perlin noise is useful for creating natural-looking textures and realistic-looking terrain.
 */
GK_BASE_AVAILABILITY_2 @interface GKPerlinNoiseSource : GKCoherentNoiseSource

@property (nonatomic) double persistence;

+ (instancetype)perlinNoiseSourceWithFrequency:(double)frequency octaveCount:(NSInteger)octaveCount persistence:(double)persistence lacunarity:(double)lacunarity seed:(int32_t)seed;
- (instancetype)initWithFrequency:(double)frequency octaveCount:(NSInteger)octaveCount persistence:(double)persistence lacunarity:(double)lacunarity seed:(int32_t)seed NS_DESIGNATED_INITIALIZER;

@end

/**
 * Billow noise is similar to Perlin noise, with more rounded shapes and clearly-defined transitions beween values.
 */
GK_BASE_AVAILABILITY_2 @interface GKBillowNoiseSource : GKCoherentNoiseSource

@property (nonatomic) double persistence;

+ (instancetype)billowNoiseSourceWithFrequency:(double)frequency octaveCount:(NSInteger)octaveCount persistence:(double)persistence lacunarity:(double)lacunarity seed:(int32_t)seed;
- (instancetype)initWithFrequency:(double)frequency octaveCount:(NSInteger)octaveCount persistence:(double)persistence lacunarity:(double)lacunarity seed:(int32_t)seed NS_DESIGNATED_INITIALIZER;

@end

/**
 * Ridged noise is similar to Perlin noise, with sharply-defined, relatively thin peaks.
 */
GK_BASE_AVAILABILITY_2 @interface GKRidgedNoiseSource : GKCoherentNoiseSource

+ (instancetype)ridgedNoiseSourceWithFrequency:(double)frequency octaveCount:(NSInteger)octaveCount lacunarity:(double)lacunarity seed:(int32_t)seed;
- (instancetype)initWithFrequency:(double)frequency octaveCount:(NSInteger)octaveCount lacunarity:(double)lacunarity seed:(int32_t)seed NS_DESIGNATED_INITIALIZER;

@end

/**
 * Voronoi noise partitions the space into angular, polygonal "cells", which are reminiscent
 * of stained glass or crystal-like structures.
 */
GK_BASE_AVAILABILITY_2 @interface GKVoronoiNoiseSource : GKNoiseSource

@property (nonatomic) double frequency;
@property (nonatomic) double displacement;
@property (nonatomic, getter=isDistanceEnabled) BOOL distanceEnabled;
@property (nonatomic) int32_t seed;

+ (instancetype)voronoiNoiseWithFrequency:(double)frequency displacement:(double)displacement distanceEnabled:(BOOL)distanceEnabled seed:(int32_t)seed;
- (instancetype)initWithFrequency:(double)frequency displacement:(double)displacement distanceEnabled:(BOOL)distanceEnabled seed:(int32_t)seed NS_DESIGNATED_INITIALIZER;

@end

/**
 * Produces a single, constant value at all positions in the space.
 */
GK_BASE_AVAILABILITY_2 @interface GKConstantNoiseSource : GKNoiseSource

@property (nonatomic) double value;

+ (instancetype)constantNoiseWithValue:(double)value;
- (instancetype)initWithValue:(double)value NS_DESIGNATED_INITIALIZER;

@end

/**
 * Produces 3D cylindrical noise with an infinite number of cylinders-within-cyliners of constantly-increasing radius.
 */
GK_BASE_AVAILABILITY_2 @interface GKCylindersNoiseSource : GKNoiseSource

@property (nonatomic) double frequency;

+ (instancetype)cylindersNoiseWithFrequency:(double)frequency;
- (instancetype)initWithFrequency:(double)frequency NS_DESIGNATED_INITIALIZER;

@end

/**
 * Produces 3D spherical noise with an infinite number of spheres-within-spheres of constantly-increasing radius.
 */
GK_BASE_AVAILABILITY_2 @interface GKSpheresNoiseSource : GKNoiseSource

@property (nonatomic) double frequency;

+ (instancetype)spheresNoiseWithFrequency:(double)frequency;
- (instancetype)initWithFrequency:(double)frequency NS_DESIGNATED_INITIALIZER;

@end

/**
 * Produces noise in a checkerboard pattern.
 */
GK_BASE_AVAILABILITY_2 @interface GKCheckerboardNoiseSource : GKNoiseSource

@property (nonatomic) double squareSize;

+ (instancetype)checkerboardNoiseWithSquareSize:(double)squareSize;
- (instancetype)initWithSquareSize:(double)squareSize NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
