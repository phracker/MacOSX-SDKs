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

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @protocol SKPhysicsContactDelegate<NSObject>
@optional
- (void)didBeginContact:(SKPhysicsContact *)contact;
- (void)didEndContact:(SKPhysicsContact *)contact;
@end

SK_EXPORT @interface SKPhysicsWorld : NSObject<NSSecureCoding>

/**
 A global 2D vector specifying the field force acceleration due to gravity. The unit is meters per second so standard earth gravity would be { 0.0, +/-9.8 }.
 */
@property (nonatomic) CGVector gravity;
@property (nonatomic) CGFloat speed;

@property (nonatomic, assign, nullable) id<SKPhysicsContactDelegate> contactDelegate;

- (void)addJoint:(SKPhysicsJoint *)joint;
- (void)removeJoint:(SKPhysicsJoint *)joint;
- (void)removeAllJoints;

- (vector_float3)sampleFieldsAt:(vector_float3)position API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

- (nullable SKPhysicsBody *)bodyAtPoint:(CGPoint)point;
- (nullable SKPhysicsBody *)bodyInRect:(CGRect)rect;
- (nullable SKPhysicsBody *)bodyAlongRayStart:(CGPoint)start end:(CGPoint)end;

- (void)enumerateBodiesAtPoint:(CGPoint)point usingBlock:(void (^)(SKPhysicsBody *body, BOOL *stop))block;
- (void)enumerateBodiesInRect:(CGRect)rect usingBlock:(void (^)(SKPhysicsBody *body, BOOL *stop))block;
- (void)enumerateBodiesAlongRayStart:(CGPoint)start end:(CGPoint)end
                          usingBlock:(void (^)(SKPhysicsBody *body, CGPoint point, CGVector normal, BOOL *stop))block;

@end

NS_ASSUME_NONNULL_END


