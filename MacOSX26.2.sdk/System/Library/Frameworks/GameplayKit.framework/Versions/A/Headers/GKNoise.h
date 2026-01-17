//
//  GKNoise.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>
#import <SpriteKit/SpriteKitBase.h>

@class GKNoiseSource;

NS_ASSUME_NONNULL_BEGIN

/**
 * GKNoise is the object used to manipulate and combine noise in continuous 3D space.  It takes a GKNoiseSource as input.
 * To extract and use a portion of the noise within the 3D space use the GKNoiseMap class.
 *
 * @see GKNoiseSource
 * @see GKNoiseMap
 */
GK_BASE_AVAILABILITY_2 @interface GKNoise : NSObject

/**
 * Color gradient of this noise, represented as 'value : color' pairs.  Utilized when this noise is rendered to a texture.
 */
@property (nonatomic, copy) NSDictionary<NSNumber *, SKColor *> *gradientColors;

/**
 * Initializes a constant noise of 0.0 at all positions.
 */
- (instancetype)init;

/**
 * Initializes a noise with the specified noise source.
 *
 * @param noiseSource The noise source to use to initially populate the 3D noise space.
 */
+ (instancetype)noiseWithNoiseSource:(GKNoiseSource *)noiseSource;

/**
 * Initializes a noise with the specified noise source and parameters.
 *
 * @param noiseSource The noise source to use to initially populate the 3D noise space.
 * @param gradientColors The color gradient to use for this noise in 'value : color' pairs.
 */
+ (instancetype)noiseWithNoiseSource:(GKNoiseSource *)noiseSource gradientColors:(NSDictionary<NSNumber *, SKColor *> *)gradientColors;

/**
 * Initializes a noise with the specified noise source.
 *
 * @param noiseSource The noise source to use to initially populate the 3D noise space.
 */
- (instancetype)initWithNoiseSource:(GKNoiseSource *)noiseSource;

/**
 * Initializes a noise with the specified noise source and parameters.
 *
 * @param noiseSource The noise source to use to initially populate the 3D noise space.
 * @param gradientColors The color gradient to use for this noise in 'value : color' pairs.
 */
- (instancetype)initWithNoiseSource:(GKNoiseSource *)noiseSource gradientColors:(NSDictionary<NSNumber *, SKColor *> *)gradientColors NS_DESIGNATED_INITIALIZER;

/**
 * Initializes a composite noise from one or more component noises.  Useful for combining and layering noises together.
 *
 * @param noises The component noises to combine.
 * @param selectionNoise The noise that governs which component noise is chosen for each position of the resulting noise.
 * The range of values is equally-subdivided for each component noise.
 */
+ (instancetype)noiseWithComponentNoises:(NSArray<GKNoise *> *)noises selectionNoise:(GKNoise *)selectionNoise;

/**
 * Initializes a composite noise from one or more component noises.  Useful for combining and layering noises together.
 *
 * @param noises The component noises to combine.
 * @param selectionNoise The noise that governs which component noise is chosen for each position of the resulting noise.
 * The range of values is equally-subdivided for each component noise.
 * @param componentBoundaries The noise value boundaries of the selection noise to use for the component noises.  Specify
 * one less boundary than the number of component noises.  This is a parallel array to blendDistances.
 * @param blendDistances The size of smoothing that is applied to boundaries where two component noises meet.  Specify
 * one less blend distance than the number of component noises.  This is a parallel array to componentBoundaries.
 */
+ (instancetype)noiseWithComponentNoises:(NSArray<GKNoise *> *)noises selectionNoise:(GKNoise *)selectionNoise componentBoundaries:(NSArray<NSNumber *> *)componentBoundaries boundaryBlendDistances:(NSArray<NSNumber *> *)blendDistances;

/**
 * The noise value at the specified sample index of the 2D plane.
 *
 * @param position Sample index of the extracted 2D plane at which to query the value
 *
 * @return The noise map value at the specified position.
 */
- (float)valueAtPosition:(vector_float2)position;

/**
 * Takes the absoltue value of all noise positions.
 */
- (void)applyAbsoluteValue;

/**
 * Clamps all noise values to the specified bounds.
 *
 * @param lowerBound The noise value lower bound.
 * @param upperBound The noise value upper bound.
 */
- (void)clampWithLowerBound:(double)lowerBound upperBound:(double)upperBound;

/**
 * Raises all noise values to the specified power.
 *
 * @param power The power to which to raise all noise values.
 */
- (void)raiseToPower:(double)power;

/**
 * Inverts all noise values, from positive to negative and vice versa.
 */
- (void)invert;

/**
 * Applies a turbulent displacement to all noise values.
 */
- (void)applyTurbulenceWithFrequency:(double)frequency power:(double)power roughness:(int)roughness seed:(int32_t)seed;

/**
 * Remaps all noise values to a smooth curve that passes through the specified control points.
 *
 * @param controlPoints Pairs of 'input : output' values to use as control points for the smooth remapping curve.
 * Duplicate input values are not permitted.
 */
- (void)remapValuesToCurveWithControlPoints:(NSDictionary<NSNumber *, NSNumber *> *)controlPoints;

/**
 * Remaps all noise values to one or more terraces with peaks.  Useful for creating valleys and trenches.
 *
 * @param peakInputValues Inputs positions of terrace peaks.
 * @param inverted Governs the curve direction from peak to peak.
 */
- (void)remapValuesToTerracesWithPeaks:(NSArray<NSNumber *> *)peakInputValues terracesInverted:(BOOL)inverted;

/**
 * Translates all noise values by the specified amount.
 *
 * @param delta The amount by which to move all noise values.
 */
- (void)moveBy:(vector_double3)delta;

/**
 * Scales all noise values by the specified amount.
 *
 * @param factor The factor by which to scale all noise values.
 */
- (void)scaleBy:(vector_double3)factor;

/**
 * Rotates all noise values by the specified amount.
 *
 * @param radians The number of radians in x-, y- and z-axes by which to rotate all noise values.
 */
- (void)rotateBy:(vector_double3)radians;

/**
 * Adds all noise values by the noise values at the same position in specified noise.
 *
 * @param noise The noise from which to add values to this noise.
 */
- (void)addWithNoise:(GKNoise *)noise;

/**
 * Multiplies all noise values by the noise values at the same position in specified noise.
 *
 * @param noise The noise from which to multiply values to this noise.
 */
- (void)multiplyWithNoise:(GKNoise *)noise;

/**
 * Takes the minimum value between this noise and the specified noise at each position.
 *
 * @param noise The noise to compare against this noise at each position in determining which to take the minimum value from.
 */
- (void)minimumWithNoise:(GKNoise *)noise;

/**
 * Takes the maximum value between this noise and the specified noise at each position.
 *
 * @param noise The noise to compare against this noise at each position in determining which to take the maximum value from.
 */
- (void)maximumWithNoise:(GKNoise *)noise;

/**
 * Raises all noise values to the power of the value at the same position of the specified noise.
 *
 * @param noise The noise from which to raise this noise's values by.
 */
- (void)raiseToPowerWithNoise:(GKNoise *)noise;

/**
 * Displaces all noise values by the values at the same positions of the specified noises.
 *
 * @param xDisplacementNoise The noise from which to displace along the x-axis this noise's values at the same positions.
 * @param yDisplacementNoise The noise from which to displace along the y-axis this noise's values at the same positions.
 * @param zDisplacementNoise The noise from which to displace along the z-axis this noise's values at the same positions.
 */
- (void)displaceXWithNoise:(GKNoise *)xDisplacementNoise yWithNoise:(GKNoise *)yDisplacementNoise zWithNoise:(GKNoise *)zDisplacementNoise;

@end

NS_ASSUME_NONNULL_END
