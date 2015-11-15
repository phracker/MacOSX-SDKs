//
//  GKBehavior.h
//  GameLogic
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameplayKitBase.h"

NS_ASSUME_NONNULL_BEGIN

@class GKGoal;

/**
 * A collection of GKGoals and weights that can be applied to a GKAgent
 */
GK_BASE_AVAILABILITY @interface GKBehavior : NSObject<NSFastEnumeration>

/*
 * The number of GKGoals in this behavior
 */
@property (readonly) NSInteger goalCount;

/**
 * Creates a behavior with a single goal and weight
 */
+ (instancetype)behaviorWithGoal:(GKGoal *)goal weight:(float)weight;

/**
 * Creates a behavior with an array of goals.  All weights are set to 1.0f
 */
+ (instancetype)behaviorWithGoals:(NSArray<GKGoal *> *)goals;

/**
 * Creates a behavior with two associated arrays of goals and weights
 */
+ (instancetype)behaviorWithGoals:(NSArray<GKGoal *> *)goals andWeights:(NSArray<NSNumber*> *)weights;

/**
 * Creates a behavior with a dictionary of goal/weight pairs
 */
+ (instancetype)behaviorWithWeightedGoals:(NSDictionary<GKGoal *, NSNumber *> *)weightedGoals;

/**
 * Adds a new goal or changes the weight of the existing goal in this behavior.
 * If the goal does not exist in this behavior, it is added.
 * @param weight the weight for this goal
 * @param goal the goal who's weight to change
 */
- (void)setWeight:(float)weight forGoal:(GKGoal *)goal;

/**
 * Gets the current weight for a given goal.
 * @return the weight of the goal, or 0 if there is no such goal on this behavior
 */
- (float)weightForGoal:(GKGoal *)goal;

/**
 * Remove the indicated goal from this behavior.
 * @param goal the goal to be removed
 */
- (void)removeGoal:(GKGoal *)goal;

/**
 * Removes all the goals on the behavior.
 */
- (void)removeAllGoals;

/**
 * Supports getting goals via a [int] subscript.
 */
- (GKGoal *)objectAtIndexedSubscript:(NSUInteger)idx;
/**
 * Supports setting a weight via a [goal] subscript.
 */
- (void)setObject:(NSNumber *)weight forKeyedSubscript:(GKGoal *)goal;

/**
 * Supports getting a weight via a [goal] subscript.
 */
- (NSNumber *)objectForKeyedSubscript:(GKGoal *)goal;

@end

NS_ASSUME_NONNULL_END