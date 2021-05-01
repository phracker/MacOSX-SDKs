//
//  SCNPhysicsBehavior.h
//  SceneKit
//
//  Copyright © 2014-2020 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;
@class SCNPhysicsBody;

/*!
 @class SCNPhysicsBehavior
 @abstract SCNPhysicsBehavior is an abstract class that represents a behavior in the physics world.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsBehavior : NSObject <NSSecureCoding>
@end

/*!
 @class SCNPhysicsHingeJoint
 @abstract SCNPhysicsHingeJoint makes two bodies to move like they are connected by a hinge. It is for example suitable for doors, chains...
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsHingeJoint : SCNPhysicsBehavior

//Initializes and returns a physics hinge joint.
//The hinge attaches bodyA and bodyB on anchorA and anchorB respectively. "axisA" and "axisB" specify the axis of rotation for bodyA and bodyB.
+ (instancetype)jointWithBodyA:(SCNPhysicsBody *)bodyA axisA:(SCNVector3)axisA anchorA:(SCNVector3)anchorA bodyB:(SCNPhysicsBody *)bodyB axisB:(SCNVector3)axisB anchorB:(SCNVector3)anchorB;

//Initializes and returns a physics hinge joint.
//The hinge attaches body to a specific location in 3d space specified by "anchor" and relative to the node that owns the body. "axis" specifies the axis of rotation for "body".
+ (instancetype)jointWithBody:(SCNPhysicsBody *)body axis:(SCNVector3)axis anchor:(SCNVector3)anchor;

@property(nonatomic, readonly) SCNPhysicsBody *bodyA; //the first body constrained by the hinge
@property(nonatomic) SCNVector3 axisA;                //the axis of rotation of bodyA
@property(nonatomic) SCNVector3 anchorA;              //the anchor point on which bodyA is attached

@property(nonatomic, readonly, nullable) SCNPhysicsBody *bodyB; //the second body attached to the hinge.
@property(nonatomic) SCNVector3 axisB;                          //the axis of rotation of bodyB
@property(nonatomic) SCNVector3 anchorB;                        //the anchor point on which bodyB is attached

@end

/*!
 @class SCNPhysicsBallSocketJoint
 @abstract SCNPhysicsBallSocketJoint makes two bodies to move like they are connected by a ball-and-socket joint (i.e it allows rotations around all axes).
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsBallSocketJoint : SCNPhysicsBehavior

//Initializes and returns a physics ball-and-socket joint.
//The joint attaches bodyA and bodyB on anchorA and anchorB respectively.
+ (instancetype)jointWithBodyA:(SCNPhysicsBody *)bodyA anchorA:(SCNVector3)anchorA bodyB:(SCNPhysicsBody *)bodyB anchorB:(SCNVector3)anchorB;

//Initializes and returns a physics ball-and-socket joint.
//The joint attaches "body" to the 3d location specified by "anchor" and relative to the node that owns the body.
+ (instancetype)jointWithBody:(SCNPhysicsBody *)body anchor:(SCNVector3)anchor;

@property(nonatomic, readonly) SCNPhysicsBody *bodyA; //the first body attached to the ball-and-socket joint
@property(nonatomic) SCNVector3 anchorA;              //the attach point of bodyA

@property(nonatomic, readonly, nullable) SCNPhysicsBody *bodyB; //the second body attached to the ball-and-socket joint
@property(nonatomic) SCNVector3 anchorB;                        //the attach point of bodyB

@end

/*!
 @class SCNPhysicsSliderJoint
 @abstract SCNPhysicsSliderJoint provides a linear sliding joint between two bodies.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsSliderJoint : SCNPhysicsBehavior

//Initializes and returns a physics slider joint.
//The joint attaches bodyA and bodyB on anchorA and anchorB respectively.
+ (instancetype)jointWithBodyA:(SCNPhysicsBody *)bodyA axisA:(SCNVector3)axisA anchorA:(SCNVector3)anchorA bodyB:(SCNPhysicsBody *)bodyB axisB:(SCNVector3)axisB anchorB:(SCNVector3)anchorB;

//Initializes and returns a physics slider joint.
//The joint attaches "body" to the 3d location specified by "anchor" and relative to the node that owns the body.
+ (instancetype)jointWithBody:(SCNPhysicsBody *)body axis:(SCNVector3)axis anchor:(SCNVector3)anchor;

@property(nonatomic, readonly) SCNPhysicsBody *bodyA; //the first body attached to the slider joint
@property(nonatomic) SCNVector3 axisA;                //the axis on which bodyA can slide
@property(nonatomic) SCNVector3 anchorA;              //the attach point of bodyA

@property(nonatomic, readonly, nullable) SCNPhysicsBody *bodyB; //the second body attached to the slider joint
@property(nonatomic) SCNVector3 axisB;                          //the axis on which bodyB can slide
@property(nonatomic) SCNVector3 anchorB;                        //the attach point of bodyB

//The minimum and maximum linear/angular limits in radians
@property(nonatomic) CGFloat minimumLinearLimit;
@property(nonatomic) CGFloat maximumLinearLimit;

@property(nonatomic) CGFloat minimumAngularLimit;
@property(nonatomic) CGFloat maximumAngularLimit;

//Linear and angular motors in newtons
@property(nonatomic) CGFloat motorTargetLinearVelocity;
@property(nonatomic) CGFloat motorMaximumForce;

@property(nonatomic) CGFloat motorTargetAngularVelocity;
@property(nonatomic) CGFloat motorMaximumTorque;

@end

/*!
 @class SCNPhysicsConeTwistJoint
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNPhysicsConeTwistJoint : SCNPhysicsBehavior

//Initializes and returns a physics cone-twist joint.
//The joint attaches bodyA and bodyB on frameA and frameB respectively.
+ (instancetype)jointWithBodyA:(SCNPhysicsBody *)bodyA frameA:(SCNMatrix4)frameA bodyB:(SCNPhysicsBody *)bodyB frameB:(SCNMatrix4)frameB;

//Initializes and returns a physics cone-twist joint.
//The joint attaches "body" to the 3d location specified by "frame" and relative to the node that owns the body.
+ (instancetype)jointWithBody:(SCNPhysicsBody *)body frame:(SCNMatrix4)frame;

@property(nonatomic, readonly) SCNPhysicsBody *bodyA; //the first body attached to the slider joint
@property(nonatomic) SCNMatrix4 frameA;

@property(nonatomic, readonly, nullable) SCNPhysicsBody *bodyB; //the second body attached to the slider joint
@property(nonatomic) SCNMatrix4 frameB;

//The maximum angular limits in radians in each cone tangent directions
@property(nonatomic) CGFloat maximumAngularLimit1;
@property(nonatomic) CGFloat maximumAngularLimit2;

//Maximum twist angle alon the cone axis
@property(nonatomic) CGFloat maximumTwistAngle;

@end

/*!
 @class SCNPhysicsVehicleWheel
 @abstract SCNPhysicsVehicleWheel represents a wheel that can be attached to a SCNPhysicsVehicle instance.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsVehicleWheel : NSObject <NSCopying, NSSecureCoding>

//Initializes and returns a wheel.
+ (instancetype)wheelWithNode:(SCNNode *)node;

//The node of the receiver.
@property(readonly) SCNNode *node;

//The wheel suspension stiffness. Defaults to 2.0.
@property CGFloat suspensionStiffness;

//The wheel suspension compression. Defaults to 4.4.
@property CGFloat suspensionCompression;

//The wheel suspension damping. Defaults to 2.3.
@property CGFloat suspensionDamping;

//The wheel maximum suspension travel in centimeters. Defaults to 500.
@property CGFloat maximumSuspensionTravel;

//The wheel friction slip coefficient. Defaults to 1.
@property CGFloat frictionSlip;

//The wheel maximum suspension force in newtons. Defaults to 6000.
@property CGFloat maximumSuspensionForce;

//The wheel connection point relative to the chassis. Defaults to the node position.
@property SCNVector3 connectionPosition;

//The wheel steering axis in the vehicle chassis space. Defaults to (0,-1,0).
@property SCNVector3 steeringAxis;

//The wheel axle in the vehicle chassis space. Defaults to (-1,0,0).
@property SCNVector3 axle;

//The wheel radius. Defaults to the half of the max dimension of the bounding box of the node.
@property CGFloat radius;

//The wheel suspension rest length. Defaults to 1.6.
@property CGFloat suspensionRestLength;

@end

/*!
 @class SCNPhysicsVehicle
 @abstract SCNPhysicsVehicle provides a vehicle behavior.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsVehicle : SCNPhysicsBehavior

// Initializes and returns a physics vehicle that applies on the physics body "chassisBody" with the given wheels.
//The wheel properties can be modified at anytime by calling setValue:forKeyPath: on each wheel with the format 'wheel[n].property', where n if the zero based wheel index.
//A wheel can't be shared to multiple vehicle
+ (instancetype)vehicleWithChassisBody:(SCNPhysicsBody *)chassisBody wheels:(NSArray<SCNPhysicsVehicleWheel *> *)wheels;

//The actual speed in kilometers per hour.
@property(nonatomic, readonly) CGFloat speedInKilometersPerHour;

//The wheels of the vehicle
@property(nonatomic, readonly) NSArray<SCNPhysicsVehicleWheel *> *wheels;

//The chassis of the vehicle
@property(nonatomic, readonly) SCNPhysicsBody *chassisBody;

//Applies a force on the wheel at the specified index
- (void)applyEngineForce:(CGFloat)value forWheelAtIndex:(NSInteger)index;

//Allows to control the direction of the wheel at the specified index. The steering value is expressed in radian, 0 means straight ahead.
- (void)setSteeringAngle:(CGFloat)value forWheelAtIndex:(NSInteger)index;

//Applies a brake force on the wheel at the specified index.
- (void)applyBrakingForce:(CGFloat)value forWheelAtIndex:(NSInteger)index;

@end

NS_ASSUME_NONNULL_END
