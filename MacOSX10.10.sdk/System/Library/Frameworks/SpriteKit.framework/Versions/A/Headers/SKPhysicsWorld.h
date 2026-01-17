//
//  SKPhysicsWorld.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SKPhysicsContact.h>
#import <SpriteKit/SpriteKitBase.h>

@class SKPhysicsJoint;
@class SKFieldNode;

SK_EXPORT @protocol SKPhysicsContactDelegate<NSObject>
@optional
- (void)didBeginContact:(SKPhysicsContact *)contact;
- (void)didEndContact:(SKPhysicsContact *)contact;
@end

SK_EXPORT @interface SKPhysicsWorld : NSObject<NSCoding>

/**
 A global 2D vector specifying the field force acceleration due to gravity. The unit is meters per second so standard earth gravity would be { 0.0, +/-9.8 }.
 */
@property (nonatomic) CGVector gravity;
@property (nonatomic) CGFloat speed;

@property (nonatomic, assign) id<SKPhysicsContactDelegate> contactDelegate;

- (void)addJoint:(SKPhysicsJoint *)joint;
- (void)removeJoint:(SKPhysicsJoint *)joint;
- (void)removeAllJoints;

- (vector_float3)sampleFieldsAt:(vector_float3)position NS_AVAILABLE(10_10, 8_0);

- (SKPhysicsBody *)bodyAtPoint:(CGPoint)point;
- (SKPhysicsBody *)bodyInRect:(CGRect)rect;
- (SKPhysicsBody *)bodyAlongRayStart:(CGPoint)start end:(CGPoint)end;

- (void)enumerateBodiesAtPoint:(CGPoint)point usingBlock:(void (^)(SKPhysicsBody *body, BOOL *stop))block;
- (void)enumerateBodiesInRect:(CGRect)rect usingBlock:(void (^)(SKPhysicsBody *body, BOOL *stop))block;
- (void)enumerateBodiesAlongRayStart:(CGPoint)start end:(CGPoint)end
                          usingBlock:(void (^)(SKPhysicsBody *body, CGPoint point, CGVector normal, BOOL *stop))block;

@end
