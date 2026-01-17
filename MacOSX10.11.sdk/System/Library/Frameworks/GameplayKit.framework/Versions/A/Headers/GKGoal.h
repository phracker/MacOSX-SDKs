//
//  GKGoal.h
//  GameLogic
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameplayKitBase.h"

NS_ASSUME_NONNULL_BEGIN

@class GKAgent, GKPath, GKObstacle;

/**
 * Defines a spatial directive.
 * The various goals cause force to be applied to agents to try to achieve said goal.
 */
GK_BASE_AVAILABILITY @interface GKGoal : NSObject <NSCopying>

/**
 * Creates a goal to move toward the agent
 * @param agent the agent to seek
 */
+ (instancetype)goalToSeekAgent:(GKAgent *)agent;

/**
 * Creates a goal to move away from the agent
 * @param agent the agent to flee from
 */
+ (instancetype)goalToFleeAgent:(GKAgent *)agent;

/**
 * Creates a goal to avoid colliding with a group of agents without taking into account those agents' momentum
 * @param maxPredictionTime how far ahead in the future, in seconds, should we look for potential collisions
 */
+ (instancetype)goalToAvoidObstacles:(NSArray<GKObstacle *> *)obstacles maxPredictionTime:(NSTimeInterval)maxPredictionTime;

/**
 * Creates a goal to avoid colliding with a group of agents taking into account those agent's momentum
 * @param timeBeforeCollisionToAvoid how far ahead in the future, in seconds, should we look for potential collisions
 */
+ (instancetype)goalToAvoidAgents:(NSArray<GKAgent *> *)agents maxPredictionTime:(NSTimeInterval)maxPredictionTime;

/**
 * Creates a goal that tries to repel this agent away from the other agents and attempts to prevent overlap
 * @param maxDistance the distance between agents before repelling happens
 * @param maxAngle the angle, in radians, between this agent's foward and the vector toward the other agent before the repelling happens
 */
+ (instancetype)goalToSeparateFromAgents:(NSArray<GKAgent *> *)agents maxDistance:(float)maxDistance maxAngle:(float)maxAngle;

/**
 * Creates a goal to align this agent's orientation with the average orientation of the group of agents.
 * @param maxDistance the distance between agents before alignment happens
 * @param maxAngle the angle, in radians, between this agent's foward and the vector toward the other agent before alignment happens
 */
+ (instancetype)goalToAlignWithAgents:(NSArray<GKAgent *> *)agents maxDistance:(float)maxDistance maxAngle:(float)maxAngle;

/**
 * Creates a goal to seek the average position of the group of agents.
 * @param maxDistance the distance between agents before cohesion happens
 * @param maxAngle the angle between this agent's foward and the vector toward the other agent before cohesion happens
 */
+ (instancetype)goalToCohereWithAgents:(NSArray<GKAgent *> *)agents maxDistance:(float)maxDistance maxAngle:(float)maxAngle;

/**
 * Creates a goal that attempts to change our momentum to reach the target speed
 * @param targetSpeed the target speed
 */
+ (instancetype)goalToReachTargetSpeed:(float)targetSpeed;

/**
 * Creates a goal that will make the agent appear to wander, aimlessly moving forward and turning randomly
 * @param deltaTime how much time, in seconds, has elapsed since the last simulation step
 * @param speed the speed at which to wander
 */
+ (instancetype)goalToWander:(float)speed;

/**
 * Creates a goal that will attempt to intercept another target agent taking into account that agent's momentum
 * @param target agent to intercept
 * @param maxPredictionTime how far ahead in the future, in seconds, should we look for potential intercepts
 */
+ (instancetype)goalToInterceptAgent:(GKAgent *)target maxPredictionTime:(NSTimeInterval)maxPredictionTime;

/**
 * Creates a goal that will attempt to follow the given path
 * @param path the path to follow
 * @param maxPredictionTime how far ahead in the future, in seconds, should we look for potential intercepts
 * @param forward direction to follow the path. forward = NO is reverse
 */
+ (instancetype)goalToFollowPath:(GKPath *)path maxPredictionTime:(NSTimeInterval)maxPredictionTime forward:(BOOL)forward;

/**
 * Creates a goal that will attempt to stay on the given path
 * @param path the path to follow
 * @param maxPredictionTime how far ahead in the future, in seconds, should we look for potential intercepts
 */
+ (instancetype)goalToStayOnPath:(GKPath *)path maxPredictionTime:(NSTimeInterval)maxPredictionTime;

@end

NS_ASSUME_NONNULL_END
