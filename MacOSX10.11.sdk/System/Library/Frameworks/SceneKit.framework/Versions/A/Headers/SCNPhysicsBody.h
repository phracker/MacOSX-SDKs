//
//  SCNPhysicsBody.h
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@class SCNPhysicsShape;

//Physics Body type
typedef NS_ENUM(NSInteger, SCNPhysicsBodyType) {
	SCNPhysicsBodyTypeStatic,
	SCNPhysicsBodyTypeDynamic,
	SCNPhysicsBodyTypeKinematic
} NS_ENUM_AVAILABLE(10_10, 8_0);

//Collision default category
typedef NS_OPTIONS(NSUInteger, SCNPhysicsCollisionCategory) {
	SCNPhysicsCollisionCategoryDefault = 1 << 0,    // default collision group for dynamic and kinematic objects
	SCNPhysicsCollisionCategoryStatic  = 1 << 1,    // default collision group for static objects
	SCNPhysicsCollisionCategoryAll     = ~0UL       // default for collision mask
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 @class SCNPhysicsBody
 @abstract The SCNPhysicsBody class describes the physics properties (such as mass, friction...) of a node.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface SCNPhysicsBody : NSObject <NSCopying, NSSecureCoding>

//Creates an instance of a static body with default properties.
+ (instancetype)staticBody;

//Creates an instance of a dynamic body with default properties.
+ (instancetype)dynamicBody;

//Creates an instance of a kinematic body with default properties.
+ (instancetype)kinematicBody;

//Creates an instance of a rigid body with a specific shape.
+ (instancetype)bodyWithType:(SCNPhysicsBodyType)type shape:(nullable SCNPhysicsShape *)shape;

//Specifies the type of the receiver.
@property(nonatomic) SCNPhysicsBodyType type;

//Specifies the Mass of the body in kilogram. Defaults to 1 for dynamic bodies, defaults to 0 for static bodies.
@property(nonatomic) CGFloat mass;

//Specifies the moment of inertia of the body as a vector in 3D. Disable usesDefaultMomentOfInertia for this value to be used instead of the default moment of inertia that is calculated from the shape geometry.
@property(nonatomic) SCNVector3 momentOfInertia NS_AVAILABLE(10_11, 9_0);

//Permits to disable the use of the default moment of inertia in favor of the one stored in momentOfInertia.
@property(nonatomic) BOOL usesDefaultMomentOfInertia NS_AVAILABLE(10_11, 9_0);

// Specifies the charge on the body. Charge determines the degree to which a body is affected by
// electric and magnetic fields. Note that this is a unitless quantity, it is up to the developer to
// set charge and field strength appropriately. Defaults to 0.0
@property(nonatomic) CGFloat charge;

//Specifies the force resisting the relative motion of solid sliding against each other. Defaults to 0.5.
@property(nonatomic) CGFloat friction;

//Specifies the restitution of collisions. Defaults to 0.5.
@property(nonatomic) CGFloat restitution;

//Specifies the force resisting the relative motion of solid rolling against each other. Defaults to 0.
@property(nonatomic) CGFloat rollingFriction;

//Specifies the physics shape of the receiver. Leaving this nil will let the system decide and use the most efficients bounding representation of the actual geometry.
@property(nonatomic, retain, nullable) SCNPhysicsShape *physicsShape;

//If the physics simulation has determined that this body is at rest it may set the resting property to YES. Resting bodies do not participate in the simulation until some collision with a non-resting object, or an impulse is applied, that unrests it. If all bodies in the world are resting then the simulation as a whole is "at rest".
@property(nonatomic, readonly) BOOL isResting;

//Specifies if the receiver can be set at rest.
@property(nonatomic) BOOL allowsResting;

//Specifies the linear velocity of the receiver.
@property(nonatomic) SCNVector3 velocity;

//Specifies the angular velocity of the receiver as an axis angle.
@property(nonatomic) SCNVector4 angularVelocity;

//Specifies the damping factor of the receiver. Optionally reduce the body's linear velocity each frame to simulate fluid/air friction. Value should be zero or greater. Defaults to 0.1.
@property(nonatomic) CGFloat damping;

//Specifies the angular damping of the receiver. Optionally reduce the body's angular velocity each frame to simulate rotational friction. (0.0 - 1.0). Defaults to 0.1.
@property(nonatomic) CGFloat angularDamping;

//Specifies a factor applied on the translation that results from the physics simulation before applying it to the node.
@property(nonatomic) SCNVector3 velocityFactor;

//Specifies a factor applied on the rotation on each axis that results from the physics simulation before applying it to the node.
@property(nonatomic) SCNVector3 angularVelocityFactor;

//Defines what logical 'categories' this body belongs too.
//Defaults to SCNPhysicsCollisionCategoryStatic for static bodies and SCNPhysicsCollisionCategoryDefault for the other body types.
//limited to the first 15 bits on OS X 10.10 and iOS 8.
@property(nonatomic) NSUInteger categoryBitMask;

//Defines what logical 'categories' of bodies this body responds to collisions with. Defaults to all bits set (all categories).
@property(nonatomic) NSUInteger collisionBitMask;

//A mask that defines which categories of bodies cause intersection notifications with this physics body. Defaults to 0.
//On iOS 8 and OS X 10.10 and lower the intersection notifications are always sent when a collision occurs.
@property(nonatomic) NSUInteger contactTestBitMask NS_AVAILABLE(10_11, 9_0);

//If set to YES this node will be affected by gravity. The default is YES.
@property(nonatomic, getter=isAffectedByGravity) BOOL affectedByGravity NS_AVAILABLE(10_11, 9_0);

//Applies a linear force in the specified direction. The linear force is applied on the center of mass of the receiver. If impulse is set to YES then the force is applied for just one frame, otherwise it applies a continuous force.
- (void)applyForce:(SCNVector3)direction impulse:(BOOL)impulse;

//Applies a linear force with the specified position and direction. The position is relative to the node that owns the physics body.
- (void)applyForce:(SCNVector3)direction atPosition:(SCNVector3)position impulse:(BOOL)impulse;

//Applies an angular force (torque). If impulse is set to YES then the force is applied for just one frame, otherwise it applies a continuous force.
- (void)applyTorque:(SCNVector4)torque impulse:(BOOL)impulse;

//Clears the forces applied one the receiver.
- (void)clearAllForces;

//Reset the physical transform to the node's model transform.
- (void)resetTransform;

@end
    
NS_ASSUME_NONNULL_END
