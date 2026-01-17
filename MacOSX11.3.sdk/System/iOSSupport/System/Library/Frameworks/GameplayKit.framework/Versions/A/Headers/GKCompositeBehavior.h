//
//  GKCompositeBehavior.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GKBehavior.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * A GKBehavior that can also contain a number of sub-behaviors
 * Sub-behaviors and goals are both weighted and produce a force to apply to a GKAGENT
 */
GK_DEFAULT
@interface GKCompositeBehavior : GKBehavior

/**
 * Number of sub-behaviors in this behavior
 **/
@property (readonly) NSInteger behaviorCount;

/**
 * Creates a behavior with an array of sub-behaviors
 */
+ (instancetype)behaviorWithBehaviors:(NSArray<GKBehavior *> *)behaviors;

/**
 * Creates a behavior with two associated arrays of sub-behaviors and weights
 */
+ (instancetype)behaviorWithBehaviors:(NSArray<GKBehavior *> *)behaviors andWeights:(NSArray<NSNumber*> *)weights;


/**
 * Adds a new sub-behavior or changes the weight of the existing sub-behavior in this behavior.
 * If the sub-behavior  does not exist in this behavior, it is added.
 * @param weight the weight for this goal
 * @param behavior the sub-behavior who's weight to change
 */
- (void)setWeight:(float)weight forBehavior:(GKBehavior *)behavior;

/**
 * Gets the current weight for a given sub-behavior.
 * @return the weight of the sub-behavior, or 0 if there is no such sub-behavior on this behavior
 */
- (float)weightForBehavior:(GKBehavior *)behavior;

/**
 * Remove the indicated sub-behavior from this behavior.
 * @param behavior the sub-behavior to be removed
 */
- (void)removeBehavior:(GKBehavior *)behavior;

/**
 * Removes all the sub-behavior on the behavior.
 */
- (void)removeAllBehaviors;

/**
 * Supports getting behaviors via a [int] subscript.
 */
- (GKBehavior *)objectAtIndexedSubscript:(NSUInteger)idx;

/**
 * Supports setting a weight via a [behavior] subscript.
 */
- (void)setObject:(NSNumber *)weight forKeyedSubscript:(GKBehavior *)behavior;

/**
 * Supports getting a weight via a [behavior] subscript.
 */
- (NSNumber *)objectForKeyedSubscript:(GKBehavior *)behavior;

@end

NS_ASSUME_NONNULL_END
