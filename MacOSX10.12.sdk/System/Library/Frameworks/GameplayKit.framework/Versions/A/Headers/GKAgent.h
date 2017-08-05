//
//  GKAgent.h
//  GameplayKit
//
//  Copyright © 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

#import <GameplayKit/GKComponent.h>
#import <GameplayKit/GKObstacle.h>
#import <GameplayKit/GKBehavior.h>
#import <GameplayKit/GKGoal.h>

@class GKAgent, GKBehavior, GKPath;

NS_ASSUME_NONNULL_BEGIN

/**
 * Delegate that will receive messages regarding GKAgent updates.
 */
@protocol GKAgentDelegate <NSObject>

@optional
/*
 * Called before [GKAgent updateWithDeltaTime:] is called each frame.
 */
- (void)agentWillUpdate:(GKAgent *)agent;

/*
 * Called after [GKAgent updateWithDeltaTime:] is called each frame.
 */
- (void)agentDidUpdate:(GKAgent *)agent;

@end


/**
 * An agent is a point mass whose local coordinate system is aligned to its velocity.  Agents have a variety of
 * steering functions that can be used to simulate vehicles or entities with agency.
 * The units of mass, velocity and radius are dimensionless but related. The visual representation of these values
 * are specific to each game's own situation.
 *
 * @discussion Values close to 1.0 should be canonical and are expected to yield pleasing results. When applied to visuals
 * these values should be scaled and biased into their target coordinate system and a simple filter on top ensures
 * any noise generated from the steering logic doesn't affect the visual represtentation.
 */
GK_BASE_AVAILABILITY @interface GKAgent : GKComponent <NSCoding>

/**
 * Object which has agentDidUpdate called on it during this agent's behavior updatekbeha
 */
@property (nullable, nonatomic, weak) id<GKAgentDelegate> delegate;

/**
 * The behavior to apply when updateWithDeltaTime is called.
 * All forces from the goals in the behavior are summed and then applied.
 */
@property (nullable, nonatomic, retain) GKBehavior *behavior;

/**
 * Agent's mass. Used for agent impulse application purposes.
 * 
 * Defaults to 1.0
 */
@property (nonatomic) float mass;

/**
 * Radius of the agent's bounding circle.  Used by the agent avoid steering functions.
 *
 * Defaults to 0.5 for a canonical diameter of 1.0
 */
@property (nonatomic) float radius;

/**
 * Current speed of the agent along its foward direction.
 *
 * Defaults to 0.0
 */
@property (nonatomic) float speed;

/**
 * Maximum amount of acceleration that can be applied to this agent.  All applied impulses are clipped to this amount.
 *
 * Defaults to 1.0
 */
@property (nonatomic) float maxAcceleration;

/**
 * Maximum speed of this agent. Impulses cannot cause the agents speed to ever be greater than this value.
 *
 * Defaults to 1.0
 */
@property (nonatomic) float maxSpeed;

@end


/**
 * A 2D specalization of an agent that moves on a 2-axis logical coordinate system. This coordinate system does not
 * need to match the visual coordinate system of the delegate. One simple case of that is isometric 2D content where the
 * game model is on a flat 2D plane but the visuals are displayed on an angle where one of the logical axes are used for
 * simulated depth as well as some translation in the display plane.
 */
GK_BASE_AVAILABILITY @interface GKAgent2D : GKAgent <NSCoding>

/**
 * Position of the agent on the logical XY plane
 */
@property (nonatomic, assign) vector_float2 position;

/**
 * Current logical velocity of the agent. The forward vector can be derived by normalizing this.
 */
@property (nonatomic, readonly) vector_float2 velocity;

/**
 * Z rotation of the agent on the logical XY plane
 */
@property (nonatomic) float rotation;

/**
 * Overridden from GKComponent.
 * Updates this agent with the current behavior, generating a force to reach its goals and applying that force.
 */
- (void)updateWithDeltaTime:(NSTimeInterval)seconds;

@end

/**
 * A 3D specialization of an agent that moves on a 3-axis logical coordinate system.
 */
GK_BASE_AVAILABILITY @interface GKAgent3D : GKAgent


/**
 * Position of the agent on the logical XYZ plane
 */
@property (nonatomic, assign) vector_float3 position;

/**
 * Current logical velocity of the agent. The forward vector can be derived by normalizing this.
 */
@property (nonatomic, readonly) vector_float3 velocity;

/**
 * Should this vehicle operate in a right-handed coordinate system? NO means it will be left-handed
 */
@property (nonatomic) BOOL rightHanded;


/**
 * The 3x3 rotation matrix that defines the orientation of this agent in 3D space
 * columns[0] is forward, columns[1] is up, columns[2] is side
 */
@property (nonatomic, assign) matrix_float3x3 rotation;


/**
 * Overridden from GKComponent.
 * Updates this agent with the current behavior, generating a force to reach its goals and applying that force.
 */
- (void)updateWithDeltaTime:(NSTimeInterval)seconds;

@end

NS_ASSUME_NONNULL_END
