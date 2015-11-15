//
//  SKPhysicsBody.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SpriteKitBase.h>

@class SKPhysicsBody;
@class SKNode;
@class SKTexture;
@class SKPhysicsJoint;

/**
 A SpriteKit physics body. These are the physical representations of your nodes. These specify the area and mass and any collision masking needed.
 
 All bodies have zero, one or more shapes that define its area. A body with no shapes is ethereal and does not collide with other bodies.
 */

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @interface SKPhysicsBody : NSObject <NSCopying, NSCoding>

/**
 Creates a circle of radius r centered at the node's origin.
 @param r the radius in points
 */
+ (SKPhysicsBody *)bodyWithCircleOfRadius:(CGFloat)r;

/**
 Creates a circle of radius r centered at a point in the node's coordinate space.
 @param r the radius in points
 */
+ (SKPhysicsBody *)bodyWithCircleOfRadius:(CGFloat)r center:(CGPoint)center;

/**
 Creates a rectangle of the specified size centered at the node's origin.
 @param s the size in points
 */
+ (SKPhysicsBody *)bodyWithRectangleOfSize:(CGSize)s;

/**
 Creates a rectangle of the specified size centered at a point in the node's coordinate space.
 @param s the size in points
 */
+ (SKPhysicsBody *)bodyWithRectangleOfSize:(CGSize)s center:(CGPoint)center;

/**
 The path must represent a convex or concave polygon with counter clockwise winding and no self intersection. Positions are relative to the node's origin.
 @param path the path to use
 */
+ (SKPhysicsBody *)bodyWithPolygonFromPath:(CGPathRef)path;

/**
 Creates an edge from p1 to p2. Edges have no volume and are intended to be used to create static environments. Edges can collide with bodies of volume, but not with each other.
 @param p1 start point
 @param p2 end point
 */
+ (SKPhysicsBody *)bodyWithEdgeFromPoint:(CGPoint)p1 toPoint:(CGPoint)p2;

/**
 Creates an edge chain from a path. The path must have no self intersection. Edges have no volume and are intended to be used to create static environments. Edges can collide with bodies of volume, but not with each other.
 @param path the path to use
 */
+ (SKPhysicsBody *)bodyWithEdgeChainFromPath:(CGPathRef)path;

/**
 Creates an edge loop from a path. A loop is automatically created by joining the last point to the first. The path must have no self intersection. Edges have no volume and are intended to be used to create static environments. Edges can collide with body's of volume, but not with each other.
 @param path the path to use
 */
+ (SKPhysicsBody *)bodyWithEdgeLoopFromPath:(CGPathRef)path;

/**
 Creates an edge loop from a CGRect. Edges have no volume and are intended to be used to create static environments. Edges can collide with body's of volume, but not with each other.
 @param rect the CGRect to use
 */
+ (SKPhysicsBody *)bodyWithEdgeLoopFromRect:(CGRect)rect;

/**
 Creates a body from the alpha values in the supplied texture.
 @param texture the texture to be interpreted
 @param size of the generated physics body
 */
+ (SKPhysicsBody *)bodyWithTexture:(SKTexture*)texture size:(CGSize)size NS_AVAILABLE(10_10, 8_0);

/**
 Creates a body from the alpha values in the supplied texture.
 @param texture the texture to be interpreted
 @param alphaThreshold the alpha value above which a pixel is interpreted as opaque
 @param size of the generated physics body
 */
+ (SKPhysicsBody *)bodyWithTexture:(SKTexture*)texture alphaThreshold:(float)alphaThreshold size:(CGSize)size NS_AVAILABLE(10_10, 8_0);


/**
 Creates an compound body that is the union of the bodies used to create it.
 */
+ (SKPhysicsBody *)bodyWithBodies:(NSArray<SKPhysicsBody*> *)bodies;

@property (nonatomic, getter = isDynamic) BOOL dynamic;
@property (nonatomic) BOOL usesPreciseCollisionDetection;
@property (nonatomic) BOOL allowsRotation;
@property (nonatomic) BOOL pinned NS_AVAILABLE(10_10, 8_0);


/**
 If the physics simulation has determined that this body is at rest it may set the resting property to YES. Resting bodies do not participate
 in the simulation until some collision with a non-resting  object, or an impulse is applied, that unrests it. If all bodies in the world are resting
 then the simulation as a whole is "at rest".
 */
@property (nonatomic, getter = isResting) BOOL resting;

/**
 Determines the 'roughness' for the surface of the physics body (0.0 - 1.0). Defaults to 0.2
 */
@property (nonatomic) CGFloat friction;

/**
 Specifies the charge on the body. Charge determines the degree to which a body is affected by
 electric and magnetic fields. Note that this is a unitless quantity, it is up to the developer to
 set charge and field strength appropriately. Defaults to 0.0
 */
@property (nonatomic) CGFloat charge NS_AVAILABLE(10_10, 8_0);

/**
 Determines the 'bounciness' of the physics body (0.0 - 1.0). Defaults to 0.2
 */
@property (nonatomic) CGFloat restitution;

/**
 Optionally reduce the body's linear velocity each frame to simulate fluid/air friction. Value should be zero or greater. Defaults to 0.1.
 Used in conjunction with per frame impulses, an object can be made to move at a constant speed. For example, if an object 64 points in size
 and default density and a linearDamping of 25 will slide across the screen in a few seconds if an impulse of magnitude 10 is applied every update.
 */
@property (nonatomic, assign) CGFloat linearDamping;

/**
 Optionally reduce the body's angular velocity each frame to simulate rotational friction. (0.0 - 1.0). Defaults to 0.1
 */
@property (nonatomic, assign) CGFloat angularDamping;

/**
 The density of the body.
 @discussion
 The unit is arbitrary, as long as the relative densities are consistent throughout the application. Note that density and mass are inherently related (they are directly proportional), so changing one also changes the other. Both are provided so either can be used depending on what is more relevant to your usage.
 */
@property (nonatomic) CGFloat density;

/**
 The mass of the body.
 @discussion
 The unit is arbitrary, as long as the relative masses are consistent throughout the application. Note that density and mass are inherently related (they are directly proportional), so changing one also changes the other. Both are provided so either can be used depending on what is more relevant to your usage.
 */
@property (nonatomic) CGFloat mass;

/**
 The area of the body.
 @discussion
 The unit is arbitrary, as long as the relative areas are consistent throughout the application.
 */
@property (nonatomic, readonly) CGFloat area;

/**
 Bodies are affected by field forces such as gravity if this property is set and the field's category mask is set appropriately. The default value is YES.
 @discussion
 If this is set a force is applied to the object based on the mass. Set the field force vector in the scene to modify the strength of the force.
 */
@property (nonatomic, assign) BOOL affectedByGravity;

/**
 Defines what logical 'categories' of fields this body responds to. Defaults to all bits set (all categories).
 Can be forced off via affectedByGravity.
 */
@property (nonatomic, assign) uint32_t fieldBitMask NS_AVAILABLE(10_10, 8_0);

/**
 Defines what logical 'categories' this body belongs to. Defaults to all bits set (all categories).
 */
@property (nonatomic, assign) uint32_t categoryBitMask;

/**
 Defines what logical 'categories' of bodies this body responds to collisions with. Defaults to all bits set (all categories).
 */
@property (nonatomic, assign) uint32_t collisionBitMask;

/**
 Defines what logical 'categories' of bodies this body generates intersection notifications with. Defaults to all bits cleared (no categories).
 */
@property (nonatomic, assign) uint32_t contactTestBitMask;


@property (nonatomic, readonly) NSArray<SKPhysicsJoint*> *joints;

/**
 The representedObject this physicsBody is currently bound to, or nil if it is not.
 */
@property (nonatomic, readonly, weak, nullable) SKNode *node;


@property (nonatomic) CGVector velocity;
@property (nonatomic) CGFloat angularVelocity;

- (void)applyForce:(CGVector)force;
- (void)applyForce:(CGVector)force atPoint:(CGPoint)point;

- (void)applyTorque:(CGFloat)torque;

- (void)applyImpulse:(CGVector)impulse;
- (void)applyImpulse:(CGVector)impulse atPoint:(CGPoint)point;

- (void)applyAngularImpulse:(CGFloat)impulse;

/* Returns an array of all SKPhysicsBodies currently in contact with this one */
- (NSArray<SKPhysicsBody*> *)allContactedBodies;

@end

NS_ASSUME_NONNULL_END

