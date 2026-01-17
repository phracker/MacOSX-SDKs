//
//  SKPhysicsJoint.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SKPhysicsBody.h>
#import <SpriteKit/SpriteKitBase.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @interface SKPhysicsJoint : NSObject <NSCoding>

@property (nonatomic, retain) SKPhysicsBody *bodyA;
@property (nonatomic, retain) SKPhysicsBody *bodyB;

// Instantaneous directed reaction force, in Newtons at anchor point
@property (nonatomic, readonly) CGVector reactionForce;

// Instantaneous reaction torque, in Newton-meters, at anchor point
@property (nonatomic, readonly) CGFloat reactionTorque;

@end


SK_EXPORT @interface SKPhysicsJointPin : SKPhysicsJoint

+ (SKPhysicsJointPin *)jointWithBodyA:(SKPhysicsBody *)bodyA bodyB:(SKPhysicsBody *)bodyB anchor:(CGPoint)anchor;

@property (nonatomic) BOOL shouldEnableLimits;
@property (nonatomic) CGFloat lowerAngleLimit;
@property (nonatomic) CGFloat upperAngleLimit;
@property (nonatomic) CGFloat frictionTorque;
@property (nonatomic) CGFloat rotationSpeed;     // in radians/sec

@end

SK_EXPORT @interface SKPhysicsJointSpring : SKPhysicsJoint

+ (SKPhysicsJointSpring *)jointWithBodyA:(SKPhysicsBody *)bodyA bodyB:(SKPhysicsBody *)bodyB anchorA:(CGPoint)anchorA anchorB:(CGPoint)anchorB;

@property (nonatomic) CGFloat damping;
@property (nonatomic) CGFloat frequency;

@end

SK_EXPORT @interface SKPhysicsJointFixed : SKPhysicsJoint

+ (SKPhysicsJointFixed *)jointWithBodyA:(SKPhysicsBody *)bodyA bodyB:(SKPhysicsBody *)bodyB anchor:(CGPoint)anchor;

@end

SK_EXPORT @interface SKPhysicsJointSliding : SKPhysicsJoint

+ (SKPhysicsJointSliding *)jointWithBodyA:(SKPhysicsBody *)bodyA bodyB:(SKPhysicsBody *)bodyB anchor:(CGPoint)anchor axis:(CGVector)axis;

@property (nonatomic) BOOL shouldEnableLimits;
@property (nonatomic) CGFloat lowerDistanceLimit;
@property (nonatomic) CGFloat upperDistanceLimit;

@end

SK_EXPORT @interface SKPhysicsJointLimit : SKPhysicsJoint

@property (nonatomic) CGFloat maxLength;

+ (SKPhysicsJointLimit *)jointWithBodyA:(SKPhysicsBody *)bodyA bodyB:(SKPhysicsBody *)bodyB anchorA:(CGPoint)anchorA anchorB:(CGPoint)anchorB;

@end

NS_ASSUME_NONNULL_END
