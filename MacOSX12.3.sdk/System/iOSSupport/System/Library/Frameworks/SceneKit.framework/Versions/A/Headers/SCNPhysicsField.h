//
//  SCNPhysicsField.h
//  SceneKit
//
//  Copyright © 2014-2021 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;

/*! 
 @enum SCNPhysicsFieldScope
 @abstract Specifies the domain of influence of a physics field.
 */
typedef NS_ENUM(NSInteger, SCNPhysicsFieldScope) {
    SCNPhysicsFieldScopeInsideExtent,
    SCNPhysicsFieldScopeOutsideExtent,
} API_AVAILABLE(macos(10.10));

/*!
 @class SCNPhysicsField
 @abstract SCNPhysicsField is an abstract class that describes a force field that applies in the physics world.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsField : NSObject <NSCopying, NSSecureCoding>

// The following properties control the behavior of the field
@property(nonatomic) CGFloat strength;                               // The strength factor of the force field. Defaults to 1.0.
@property(nonatomic) CGFloat falloffExponent;                        // Changes the power of the force based on the distance from the center of the field (1 / distance ^ falloffExponent). Defaults to 0.0.
@property(nonatomic) CGFloat minimumDistance;                        // Distance from the center of the field where the effect is at full strength. Defaults to 1e-6.

@property(nonatomic, getter=isActive) BOOL active;                   // Specifies whether force field is active or not. Defaults to YES.
@property(nonatomic, getter=isExclusive) BOOL exclusive;             // If YES, it suppresses any other field in its area. Defaults to NO.

// The following properties control the area of effect
@property(nonatomic) SCNVector3 halfExtent;                          // Specifies the half extent of the area of effect. Defaults to FLT_MAX.
@property(nonatomic) BOOL usesEllipsoidalExtent;                     // YES means that the area of effect is rounded within the extent. Defaults to NO.
@property(nonatomic) SCNPhysicsFieldScope scope;                     // Controls whether the force field should apply inside or outside of the area. Defaults to inside.

@property(nonatomic) SCNVector3 offset;                              // Offset of origin effect within the area.
@property(nonatomic) SCNVector3 direction;                           // Direction of the field. Only applies to linear gravity and vortex fields. Defaults to (0,-1,0).

/*!
 @property categoryBitMask
 @abstract Determines the node physicsBody's categories that will be influenced by the receiver. Defaults to all bit set.
 */
@property(nonatomic) NSUInteger categoryBitMask API_AVAILABLE(macos(10.10));


/**
 Slows an object proportionally to the object’s velocity.
 Use this to simulate effects such as friction from motion through the air.
 */
+ (SCNPhysicsField *)dragField;

/**
 Applies a force tangential to the direction from the sample point to the field's position.
 The force will be CCW to the direction. Make the strength negative to apply force in the CW direction.
 Amount is proportional to distance from center and the object's mass.
 Use this to create effects such as tornadoes.
 */
+ (SCNPhysicsField *)vortexField;

/**
 Applies a force in the direction of the origin of the field in local space. To repel objects, use a negative strength.
 The force is proportional to the distance from the field origin. Varies with the mass of the object according to F = ma
 The field node's rotation property can be used to orient the gravity in a particular direction.
 */
+ (SCNPhysicsField *)radialGravityField;

/**
 Applies a force in the direction of the "direction" vector in the local space. To repel objects, use a negative strength.
 The force is the same everywhere in the field. Varies with the mass of the object according to F = ma
 The field node's rotation property can be used to orient the gravity in a particular direction.
 */
+ (SCNPhysicsField *)linearGravityField;

/**
 A time varying differentiable Perlin simplex noise field. A smoothness of 0 means as noisy as possible.
 Use this to simulate such effects as fireflies, or snow.
 To freeze the noise in place, set animationSpeed to 0.0. Mass is ignored.
 You can change the "smoothness" and "animationSpeed" using KVC.
 */
+ (SCNPhysicsField *)noiseFieldWithSmoothness:(CGFloat)smoothness animationSpeed:(CGFloat)speed;

/**
 Just like Noise, except the strength of the noise is proportional to the velocity of the object in the field.
 */
+ (SCNPhysicsField *)turbulenceFieldWithSmoothness:(CGFloat)smoothness animationSpeed:(CGFloat)speed;

/**
 A Hooke’s law force - a force linearly proportional to distance from the center of the field. An object in this
 field will oscillate with a period proportional to the inverse of the mass.
 An example use is to keep objects confined to a particular region.
 */
+ (SCNPhysicsField *)springField;

/**
 A force proportional to the charge on the object. An example use of this field is to make objects behavior differently
 from one another when they enter a region, or to make an object's behavior different than its mass based behavior
 This field models the first part of the Lorentz equation, F = qE
 */
+ (SCNPhysicsField *)electricField;

/**
 A force proportional to the charge on the object and the object’s velocity. 
 An example use of this field is to make objects behavior differently from one another when they enter a region, or to make an object's behavior different than its mass based behavior
 This field models the second part of the Lorentz equation, F = qvB
 */
+ (SCNPhysicsField *)magneticField;

typedef SCNVector3 (^SCNFieldForceEvaluator)(SCNVector3 position, SCNVector3 velocity, float mass, float charge, NSTimeInterval time);

/**
 A field force with a custom force evaluator.
 */
+ (SCNPhysicsField *)customFieldWithEvaluationBlock:(SCNFieldForceEvaluator)block;

@end

NS_ASSUME_NONNULL_END
