//
//  GKRandomDistribution.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <GameplayKit/GKRandomSource.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A random distribution is a random source itself with a specific mapping from the input source to the output values.
 * The distribution is uniform, meaning there is no bias towards any of the possible outcomes.
 */
GK_BASE_AVAILABILITY @interface GKRandomDistribution : NSObject<GKRandom>

/**The lowest value the distribution will output.*/
@property (nonatomic, assign, readonly) NSInteger lowestValue;
/**The highest value the distribution will output.*/
@property (nonatomic, assign, readonly) NSInteger highestValue;
/**The number of unique possible outcomes, depending on the distribution type this is not always highest - lowest + 1.*/
@property (nonatomic, assign, readonly) NSUInteger numberOfPossibleOutcomes;

/**Initializes a random distribution within the range [lowest, highest] using a source to grab input values from.*/
- (instancetype)initWithRandomSource:(id<GKRandom>)source lowestValue:(NSInteger)lowestInclusive highestValue:(NSInteger)highestInclusive NS_DESIGNATED_INITIALIZER;

/**
 * Returns the next integer in the distribution sequence and moves ahead to the next one.
 * The value is in the range of [lowest, highest].
 */
- (NSInteger)nextInt;

/**
 * Returns the next unsigned value in the distribution sequence that is less than upperBound.
 * The value never equals or exceeeds upperBounds, and in this case it will also never exceed
 * the highest value of the distribution.
 */
- (NSUInteger)nextIntWithUpperBound:(NSUInteger)upperBound;

/**
 * Returns the next uniform float in the random sequence and moves ahead to the next one.
 * The value is in the range of [lowest / higest, 1.0].
 * 
 * The value is quantized to the distribution's lowest and highest bounds. Thus on a d20
 * distribution the value is quantized to 5% increments. The output value 0 is not possible
 * to get unless the lowest value bound is also 0 or below.
 *
 * @see nextInt
 */
- (float)nextUniform;

/**
 * Returns the next true or false value in the distribution sequence and moves ahead to the next one.
 * The value is either nonzero (true) or zero (false).
 * Use this for simple boolean switches in logic that don't require fuzzy evaluation.
 * For fuzzy evaluation use nextUniform.
 *
 * By default this is based on the referenced source's definition of nextBool.
 * 
 * @see GKRandomSource.nextBool
 */
- (BOOL)nextBool;


/**
 * Convenience creation of random distribution within the range [lowest, highest] using an isolated source to grab input values from.
 * This is equivalent to calling alloc followed by initWithSource:lowest:highest:, where source is [[GKRandomSource alloc] init].
 * @see initWithRandomSource:lowestValue:highestValue:
 */
+ (instancetype)distributionWithLowestValue:(NSInteger)lowestInclusive highestValue:(NSInteger)highestInclusive;

/**
 * Convenience creation of random distribution with the die like range [1, sideCount] using an isolated source to grab input values from.
 * This is equivalent to calling alloc followed by initWithSource:lowest:highest:, where source is [[GKRandomSource alloc] init].
 * @see initWithRandomSource:lowestValue:highestValue:
 */
+ (instancetype)distributionForDieWithSideCount:(NSInteger)sideCount;

/**
 * Convenience creation for the very common d6 range [1, 6] with an isolated random source
 * shielded from outside sources.
 */
+ (instancetype)d6;

/**
 * Convenience creation for the very common d20 range [1, 20] with an isolated random source
 * shielded from outside sources.
 */
+ (instancetype)d20;

@end


/**
 * A gaussian distribution is biased towards the mean value, the possible outcomes are spread out from the mean
 * with decreasing probability. Values within 1 deviation of the mean make up 68.27% of the distribution, values
 * within 2 deviations make up 95% and values within 3 deviations make up 99.7%.
 *
 * Note that a gaussian distribution's unbounded behavior beyond 3 deviations is undesired,
 * thus this distribution deviates nominally by modifying the bounds to 3 deviations.
 * Thus values within 3 deviations actually make up 100% of the distribution.
 */
GK_BASE_AVAILABILITY @interface GKGaussianDistribution : GKRandomDistribution

/**
 * The mean, or expected, value of the distribution. Values are more probable the closer to the mean they are.
 */
@property (nonatomic, assign, readonly) float mean;

/**
 * The deviation, often called 'sigma', is the deviation from the mean that would include roughly 68% of the distribution.
 * The range of the distribution is [mean - 3 * deviation, mean + 3 * deviation]. Values beyond 3 deviations
 * are considered so improbable that they are removed from the output set.
 */
@property (nonatomic, assign, readonly) float deviation;

/**
 * Initializes a Gaussian random distribution within the range [lowest, highest] using a source to grab input values from.
 * This sets the gaussian parameters to:
 *
 * mean = (highest + lowest) / 2
 * deviation = (highest - lowest) / 6
 *
 * The mean and deviation will be floating point numbers even if the distribution is meant to produce integer values.
 * @see mean
 * @see deviation
 */
- (instancetype)initWithRandomSource:(id<GKRandom>)source lowestValue:(NSInteger)lowestInclusive highestValue:(NSInteger)highestInclusive NS_DESIGNATED_INITIALIZER;

/**
 * Initializes a Gaussian random distribution within the range [mean - 3 * deviation, mean + 3 * deviation]
 * using a source to grab input values from.
 */
- (instancetype)initWithRandomSource:(id<GKRandom>)source mean:(float)mean deviation:(float)deviation NS_DESIGNATED_INITIALIZER;

@end


/**
 * A shuffled distribution tries to make sure individual samples are not clustered whilst retaining a uniform distribution of values
 * over time. This is often referred to as fair or less random, as the predicatability of the outcomes in a series is vastly increased,
 * yet the distribution of values is uniform.
 *
 * Do not use with distributions ranging more than 256 between lowest and highest as the shuffling seqeunce is stored internally in memory.
 */
GK_BASE_AVAILABILITY @interface GKShuffledDistribution : GKRandomDistribution

@end

NS_ASSUME_NONNULL_END
