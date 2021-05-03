//
//  GKRandomSource.h
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A protocol for random sources that can generate random numbers. This is the minimal interface needed
 * to consume random values from a source; concrete subclasses should be used for configuring the
 * production of random values.
 * The availability of deterministic random sources is critical to creating reliable gameplay mechanics.
 * Ensure that systems that should not influence each other have unique random sources and avoid sharing
 * sources unless absolutely needed.
 *
 * This protocol allows you to provide custom random sources from classes that are not able to
 * derive from GKRandomSource directly.
 */
@protocol GKRandom

@required
/**
 * Returns the next integer in the random sequence and moves ahead to the next one.
 * The value is in the range of [INT32_MIN, INT32_MAX].
 * The lower bits are not guaranteed to be random so please use another
 * property for simple choices.
 *
 * @see nextBool
 * @see nextUniform
 */
- (NSInteger)nextInt;

/**
 * Returns the next unsigned value in the random sequence that is less than upperBound.
 * The value is in the range of [0, upperBound). Thus the value never equals or exceeeds upperBound.
 * The unsigned nature and upper bound allows implementations to use logical shifts to return a
 * value whose lower bits are more random than a similar call to nextInt.
 *
 * This is used to implement nextBool and nextUniform by default.
 */
- (NSUInteger)nextIntWithUpperBound:(NSUInteger)upperBound;

/**
 * Returns the next uniform float in the random sequence and moves ahead to the next one.
 * The value is in the range of [0.0, 1.0].
 * There is no weighting across the range so remapping this with a curve may give the best
 * sampling distribution for your algorithm.
 *
 * By default this should be based on nextIntWithUpperBound:. Implementions may base it on
 * another representation if needed.
 *
 * @see nextIntWithUpperBound:
 * @see nextInt
 */
- (float)nextUniform;

/**
 * Returns the next true or false value in the random sequence and moves ahead to the next one.
 * The value is either nonzero (true) or zero (false).
 * Use this for simple boolean switches in logic that don't require fuzzy evaluation.
 * For fuzzy evaluation use nextUniform.
 *
 * By default this should be based on nextIntWithUpperBound:. Implementations may base it on
 * another representation if needed.
 *
 * @see nextIntWithUpperBound:
 * @see nextUniform
 */
- (BOOL)nextBool;

@end

/**
 * A concrete random source that can generate random numbers. The implementation details are up to the system and
 * if a particular algorithm is needed then use one of the provided subclasses.
 *
 * For certain specialized applications a shared system source may be needed and for those instances there is
 * a wrapped interface over arc4random_*, accessible via +[GKRandomSource sharedRandom].
 *
 * @see GKARC4RandomSource
 * @see GKLinearCongruentialRandomSource
 * @see GKMersenneTwisterRandomSource
 * @see GKRandomSource.systemRandom
 */
GK_BASE_AVAILABILITY @interface GKRandomSource : NSObject <GKRandom, NSSecureCoding, NSCopying>

/**
 * Creates a new random source initialized using bits from an entropy source like SecRandomCopyBytes.
 * When used directly from the base class; this source is deterministic and performant but the underlying implementation
 * details are not specified. Use a subclass with a specific algorithm implementation guaranteed if your application requires
 * very stringent random source charateristics.
 *
 * @see GKARC4RandomSource
 * @see GKLinearCongruentialRandomSource
 * @see GKMersenneTwisterRandomSource
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 * Deserializes a random source from an NSCoder. All random sources support coding for serializing and deserializing the state
 * of the random source. Each subclass has its own contract for what parts of the state is preserved when serialized but the
 * general contract is that a serialized source must generate the same sequence of values as the original source would from the
 * instant it was serialized.
 *
 * Note that the sharedRandom instance is an exception as it is explicitly seedless and a shared singleton instance.
 * When serialized and deserialized it will return the current sharedRandom instance instead.
 */
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/**
 * Returns a shared instance of a random source that uses the system's underlying random source.
 * Using this instance modifies the outcome of future calls to the arc4random family of C calls. It is
 * also affected by calls to the C apis and should not be used for sources that are intended to
 * be deterministic.
 *
 * @discussion Note that while it may seem semantically similar to a GKARC4RandomSource, this is not a drop in replacement.
 */
+ (GKRandomSource *)sharedRandom;

/**
 * Returns a shuffled instance of the given array. The objects in the array are shuffled based on a Fisher-Yates shuffle.
 *
 * Any random, be it custom, source or a distribution, that can provide a number with an upper bound of at least the
 * array.count is suitable for this shuffle.
 */
- (NSArray *)arrayByShufflingObjectsInArray:(NSArray *)array;

@end

@interface NSArray<ObjectType> (GameplayKit)

/*
 * Returns a shuffled instance of this array using the given random source.
 */
- (NSArray<ObjectType>*)shuffledArrayWithRandomSource:(GKRandomSource*)randomSource;

/*
 * Returns a shuffled instance of this array using the systems underlying random source, as with [GKRandomSource sharedRandom]
 */
- (NSArray<ObjectType>*)shuffledArray;

@end


/**
 * A deterministic pseudo-random source that generates random numbers based on an arc4 algorithm.
 * This is a deterministic random source suitable for creating reliable gameplay mechanics.
 *
 * While deterministic, this is not a cryptographic random source, however it may be useful
 * for obfuscation of gameplay data in manner similar to a stream cipher.
 */
GK_BASE_AVAILABILITY @interface GKARC4RandomSource : GKRandomSource

/**
 * The seed used to stir the arc4 random source.
 * The seed is not encoded through archiving, but the equivalent state buffers are encoded.
 */
@property (nonatomic, copy) NSData *seed;

/**
 * Initializes an arc4 random source with bits from high entropy system resource like SecRandomCopyBytes.
 */
- (instancetype)init;

/**
 * Initializes an arc4 random source with bits from the seed.
 */
- (instancetype)initWithSeed:(NSData *)seed NS_DESIGNATED_INITIALIZER;

/**
 * Arc4 based random sources have repeatable initial sequences. If used for obfuscation you should
 * drop N values from the start, where N should be any number larger than 768 to ensure the initial
 * sequence is flushed.
 */
- (void)dropValuesWithCount:(NSUInteger)count;

@end


/**
 * A deterministic pseudo-random source that generates random numbers based on a linear congruential algorithm.
 * This is a deterministic random source suitable for creating reliable gameplay mechanics.
 * It is slightly faster than an Arc4 source, but less random. In particular the lower bits
 * of the generated values are less random than the higher bits.
 *
 * While deterministic, this is not a cryptographic random source. It is also not suitable
 * for obfuscation of gameplay data.
 */
GK_BASE_AVAILABILITY @interface GKLinearCongruentialRandomSource : GKRandomSource

/**
 * The seed used to stir the linear congruential random source.
 * The seed changes each time a random value is generated from this source, as the seed is the state buffer.
 * The seed is encoded through archiving.
 */
@property (nonatomic, assign) uint64_t seed;

/**
 * Initializes a linear congruential random source with bits from high entropy system resource like SecRandomCopyBytes.
 */
- (instancetype)init;

/**
 * Initializes a linear congruential random source with bits the given 64 bit seed.
 */
- (instancetype)initWithSeed:(uint64_t)seed NS_DESIGNATED_INITIALIZER;

@end

/**
 * A deterministic pseudo-random source that generates random numbers based on a mersenne twister algorithm.
 * This is a deterministic random source suitable for creating reliable gameplay mechanics.
 * It is slightly slower than an Arc4 source, but more random, in that it has a longer period until repeating sequences.
 *
 * While deterministic, this is not a cryptographic random source. It is however suitable
 * for obfuscation of gameplay data.
 */
GK_BASE_AVAILABILITY @interface GKMersenneTwisterRandomSource : GKRandomSource

/**
 * The seed used to stir the mersenne twister random source.
 * The seed is not encoded through archiving, but the equivalent state buffers are encoded.
 */
@property (nonatomic, assign) uint64_t seed;

/**
 * Initializes a linear congruential random source with bits from a high entropy system resource like SecRandomCopyBytes.
 */
- (instancetype)init;

/**
 * Initializes a linear congruential random source with bits the given 64 bit seed.
 */
- (instancetype)initWithSeed:(uint64_t)seed NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

