//
//  SKPhysicsJoint.h
//  SpriteKitMac
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SKPhysicsBody.h>
#import <SpriteKit/SpriteKitBase.h>

SK_EXPORT @interface SKPhysicsJoint : NSObject <NSCoding>

@property (SK_NONATOMIC_IOSONLY, retain) SKPhysicsBody *bodyA;
@property (SK_NONATOMIC_IOSONLY, retain) SKPhysicsBody *bodyB;

@end


SK_EXPORT @interface SKPhysicsJointPin : SKPhysicsJoint

+ (SKPhysicsJointPin *)jointWithBodyA:(SKPhysicsBody *)bodyA bodyB:(SKPhysicsBody *)bodyB anchor:(CGPoint)anchor;

@property (SK_NONATOMIC_IOSONLY) BOOL shouldEnableLimits;
@property (SK_NONATOMIC_IOSONLY) CGFloat lowerAngleLimit;
@property (SK_NONATOMIC_IOSONLY) CGFloat upperAngleLimit;
@property (SK_NONATOMIC_IOSONLY) CGFloat frictionTorque;

@end

SK_EXPORT @interface SKPhysicsJointSpring : SKPhysicsJoint

+ (SKPhysicsJointSpring *)jointWithBodyA:(SKPhysicsBody *)bodyA bodyB:(SKPhysicsBody *)bodyB anchorA:(CGPoint)anchorA anchorB:(CGPoint)anchorB;

@property (SK_NONATOMIC_IOSONLY) CGFloat damping;
@property (SK_NONATOMIC_IOSONLY) CGFloat frequency;

@end

SK_EXPORT @interface SKPhysicsJointFixed : SKPhysicsJoint

+ (SKPhysicsJointFixed *)jointWithBodyA:(SKPhysicsBody *)bodyA bodyB:(SKPhysicsBody *)bodyB anchor:(CGPoint)anchor;

@end

SK_EXPORT @interface SKPhysicsJointSliding : SKPhysicsJoint

+ (SKPhysicsJointSliding *)jointWithBodyA:(SKPhysicsBody *)bodyA bodyB:(SKPhysicsBody *)bodyB anchor:(CGPoint)anchor axis:(CGVector)axis;

@property (SK_NONATOMIC_IOSONLY) BOOL shouldEnableLimits;
@property (SK_NONATOMIC_IOSONLY) CGFloat lowerDistanceLimit;
@property (SK_NONATOMIC_IOSONLY) CGFloat upperDistanceLimit;

@end

SK_EXPORT @interface SKPhysicsJointLimit : SKPhysicsJoint

@property (SK_NONATOMIC_IOSONLY) CGFloat maxLength;

+ (SKPhysicsJointLimit *)jointWithBodyA:(SKPhysicsBody *)bodyA bodyB:(SKPhysicsBody *)bodyB anchorA:(CGPoint)anchorA anchorB:(CGPoint)anchorB;

@end