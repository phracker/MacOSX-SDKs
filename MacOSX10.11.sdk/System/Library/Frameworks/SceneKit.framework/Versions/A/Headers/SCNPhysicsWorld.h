//
//  SCNPhysicsWorld.h
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@class SCNPhysicsContact;
@class SCNPhysicsBehavior;

//Keys for ray, contact and sweep tests
SCN_EXTERN NSString * const SCNPhysicsTestCollisionBitMaskKey NS_AVAILABLE(10_10, 8_0); //Allows to filter the objects tested by rayTest, contactTest and convexSweep. Default is SCNPhysicsCollisionCategoryAll
SCN_EXTERN NSString * const SCNPhysicsTestSearchModeKey NS_AVAILABLE(10_10, 8_0);       //Specifies how to perform the ray/contact/sweep test. Values are defined below. If not defined, then defaults to SCNPhysicsTestSearchModeAny
SCN_EXTERN NSString * const SCNPhysicsTestBackfaceCullingKey NS_AVAILABLE(10_10, 8_0);  //Specifies whether the back faces should be ignored or not. Defaults to YES.

//Values for SCNPhysicsTestSearchModeKey
SCN_EXTERN NSString * const SCNPhysicsTestSearchModeAny NS_AVAILABLE(10_10, 8_0);       //Returns the first contact found.
SCN_EXTERN NSString * const SCNPhysicsTestSearchModeClosest NS_AVAILABLE(10_10, 8_0);   //Returns the nearest contact found only.
SCN_EXTERN NSString * const SCNPhysicsTestSearchModeAll NS_AVAILABLE(10_10, 8_0);       //All contacts are returned.

/*!
 @protocol SCNPhysicsContactDelegate
 @abstract The SCNPhysicsContactDelegate protocol is to be implemented by delegates that want to be notified when a contact occured.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@protocol SCNPhysicsContactDelegate <NSObject>
@optional
- (void)physicsWorld:(SCNPhysicsWorld *)world didBeginContact:(SCNPhysicsContact *)contact;
- (void)physicsWorld:(SCNPhysicsWorld *)world didUpdateContact:(SCNPhysicsContact *)contact;
- (void)physicsWorld:(SCNPhysicsWorld *)world didEndContact:(SCNPhysicsContact *)contact;
@end

/*!
 @class SCNPhysicsWorld
 @abstract The SCNPhysicsWorld class describes and allows to control the physics simulation of a 3d scene.
 @discussion The SCNPhysicsWorld class should not be allocated directly but retrieved from the SCNScene class using the physicsWorld property.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface SCNPhysicsWorld : NSObject <NSSecureCoding>

//A global 3D vector specifying the field force acceleration due to gravity. The unit is meter per second. Default is {0, -9.8, 0}.
@property(nonatomic) SCNVector3 gravity;

//A speed multiplier applied to the physics simulation. Default is 1.0.
//The speed can be reduced to slowdown the simulation, but beware that increasing the speed factor will decrease the accuracy of the simulation.
@property(nonatomic) CGFloat speed;

//The time step of the physics simulation. Default is 1/60s (60 Hz).
@property(nonatomic) NSTimeInterval timeStep;

//A delegate that is called when two physic bodies come in contact with each other.
@property(atomic, assign, nullable) id <SCNPhysicsContactDelegate> contactDelegate;

//Behaviors management
- (void)addBehavior:(SCNPhysicsBehavior *)behavior;
- (void)removeBehavior:(SCNPhysicsBehavior *)behavior;
- (void)removeAllBehaviors;
@property(nonatomic, readonly) NSArray<SCNPhysicsBehavior *> *allBehaviors;

//Performs a ray test on the physics bodies and their physics shapes.
- (NSArray<SCNHitTestResult *> *)rayTestWithSegmentFromPoint:(SCNVector3)origin toPoint:(SCNVector3)dest options:(nullable NSDictionary<NSString *, id> *)options;

//The methods below perform contact tests.
- (NSArray<SCNPhysicsContact *> *)contactTestBetweenBody:(SCNPhysicsBody *)bodyA andBody:(SCNPhysicsBody *)bodyB options:(nullable NSDictionary<NSString *, id> *)options;
- (NSArray<SCNPhysicsContact *> *)contactTestWithBody:(SCNPhysicsBody *)body options:(nullable NSDictionary<NSString *, id> *)options;
- (NSArray<SCNPhysicsContact *> *)convexSweepTestWithShape:(SCNPhysicsShape *)shape fromTransform:(SCNMatrix4)from toTransform:(SCNMatrix4)to options:(nullable NSDictionary<NSString *, id> *)options;

//Force the physics engine to re-evaluate collisions.
//This needs to be called if kinematic are moved and the contacts are wanted before the next simulation step.
- (void)updateCollisionPairs;

@end

NS_ASSUME_NONNULL_END
