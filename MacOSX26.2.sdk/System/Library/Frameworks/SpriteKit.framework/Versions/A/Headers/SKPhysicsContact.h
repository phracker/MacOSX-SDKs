//
//  SKPhysicsContact.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SKPhysicsBody.h>
#import <SpriteKit/SpriteKitBase.h>


NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @interface SKPhysicsContact : NSObject

@property (nonatomic, readonly) SKPhysicsBody *bodyA;
@property (nonatomic, readonly) SKPhysicsBody *bodyB;
@property (nonatomic, readonly) CGPoint contactPoint;
@property (nonatomic, readonly) CGVector contactNormal;
@property (nonatomic, readonly) CGFloat collisionImpulse;

@end

NS_ASSUME_NONNULL_END
