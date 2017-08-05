//
//  SCNPhysicsWorld.h
//
//  Copyright (c) 2014-2017 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNPhysicsBody;
@class SCNPhysicsShape;
@class SCNPhysicsWorld;
@class SCNPhysicsContact;
@class SCNPhysicsBehavior;
@class SCNHitTestResult;

// Keys for ray, contact and sweep tests
#if defined(SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH) && SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH >= 3
typedef NSString * SCNPhysicsTestOption NS_STRING_ENUM;
#else
typedef NSString * SCNPhysicsTestOption;
#endif

FOUNDATION_EXTERN SCNPhysicsTestOption const SCNPhysicsTestCollisionBitMaskKey API_AVAILABLE(macos(10.10)); // Allows to filter the objects tested by rayTest, contactTest and convexSweep. Default is SCNPhysicsCollisionCategoryAll
FOUNDATION_EXTERN SCNPhysicsTestOption const SCNPhysicsTestSearchModeKey       API_AVAILABLE(macos(10.10)); // Specifies how to perform the ray/contact/sweep test. Values are defined below. If not defined, then defaults to SCNPhysicsTestSearchModeAny
FOUNDATION_EXTERN SCNPhysicsTestOption const SCNPhysicsTestBackfaceCullingKey  API_AVAILABLE(macos(10.10)); // Specifies whether the back faces should be ignored or not. Defaults to YES.

#define SCNPhysicsTestOptionCollisionBitMask SCNPhysicsTestCollisionBitMaskKey
#define SCNPhysicsTestOptionSearchMode       SCNPhysicsTestSearchModeKey
#define SCNPhysicsTestOptionBackfaceCulling  SCNPhysicsTestBackfaceCullingKey

// Values for SCNPhysicsTestSearchModeKey
#if defined(SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH) && SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH >= 3
typedef NSString * SCNPhysicsTestSearchMode NS_STRING_ENUM;
#else
typedef NSString * SCNPhysicsTestSearchMode;
#endif

FOUNDATION_EXTERN SCNPhysicsTestSearchMode const SCNPhysicsTestSearchModeAny     API_AVAILABLE(macos(10.10)); // Returns the first contact found.
FOUNDATION_EXTERN SCNPhysicsTestSearchMode const SCNPhysicsTestSearchModeClosest API_AVAILABLE(macos(10.10)); // Returns the nearest contact found only.
FOUNDATION_EXTERN SCNPhysicsTestSearchMode const SCNPhysicsTestSearchModeAll     API_AVAILABLE(macos(10.10)); // All contacts are returned.

/*!
 @protocol SCNPhysicsContactDelegate
 @abstract The SCNPhysicsContactDelegate protocol is to be implemented by delegates that want to be notified when a contact occured.
 */
API_AVAILABLE(macos(10.10))
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
API_AVAILABLE(macos(10.10))
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
- (NSArray<SCNHitTestResult *> *)rayTestWithSegmentFromPoint:(SCNVector3)origin toPoint:(SCNVector3)dest options:(nullable NSDictionary<SCNPhysicsTestOption, id> *)options;

//The methods below perform contact tests.
- (NSArray<SCNPhysicsContact *> *)contactTestBetweenBody:(SCNPhysicsBody *)bodyA andBody:(SCNPhysicsBody *)bodyB options:(nullable NSDictionary<SCNPhysicsTestOption, id> *)options;
- (NSArray<SCNPhysicsContact *> *)contactTestWithBody:(SCNPhysicsBody *)body options:(nullable NSDictionary<SCNPhysicsTestOption, id> *)options;
- (NSArray<SCNPhysicsContact *> *)convexSweepTestWithShape:(SCNPhysicsShape *)shape fromTransform:(SCNMatrix4)from toTransform:(SCNMatrix4)to options:(nullable NSDictionary<SCNPhysicsTestOption, id> *)options;

//Force the physics engine to re-evaluate collisions.
//This needs to be called if kinematic are moved and the contacts are wanted before the next simulation step.
- (void)updateCollisionPairs;

@end

NS_ASSUME_NONNULL_END
