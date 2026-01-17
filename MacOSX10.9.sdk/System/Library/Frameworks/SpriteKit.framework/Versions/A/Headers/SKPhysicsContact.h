//
//  SKPhysicsContact.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SKPhysicsBody.h>
#import <SpriteKit/SpriteKitBase.h>

SK_EXPORT @interface SKPhysicsContact : NSObject

@property (SK_NONATOMIC_IOSONLY, readonly) SKPhysicsBody *bodyA;
@property (SK_NONATOMIC_IOSONLY, readonly) SKPhysicsBody *bodyB;
@property (SK_NONATOMIC_IOSONLY, readonly) CGPoint contactPoint;
@property (SK_NONATOMIC_IOSONLY, readonly) CGFloat collisionImpulse;

@end
