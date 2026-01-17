/**
 @header
 
 Field Nodes apply force to physics bodies and particles.
 
 @copyright 2014 Apple Inc. All rights reserved.
 
*/

#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKAction.h>
#import <SpriteKit/SKNode.h>
#import <Foundation/Foundation.h>

@class SKTexture, SKRegion;

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT NS_AVAILABLE(10_10, 8_0) @interface SKFieldNode : SKNode

/** The region property is the domain of the field's effect. No force is applied to objects outside the region.
 */
@property (nonatomic, retain, nullable) SKRegion *region;

/** strength scaling value. default 1.0 */
@property (nonatomic) float strength;

/** The falloff exponent used to calculate field strength at a distance.
    Falloff starts at the minimum radius.

    The default exponent is zero, which results in a uniform field with no falloff.
 
    @see minimumRadius
 */
@property (nonatomic) float falloff;

/** minimum radius of effect. Default is very small. */
@property (nonatomic) float minimumRadius;

/** If enabled, a field has an effect.
    
    default YES
 */
@property (nonatomic, getter = isEnabled) BOOL enabled;

/** If a field is exclusive, it suppresses any other field in its region of effect.
    If two or more exclusive fields overlap, it is undefined which one of them will take effect
 
    @see region
 */
@property (nonatomic, getter = isExclusive) BOOL exclusive;

/** Logical categories the field belongs to. Default is all categories.
    These categories correspond to fieldBitMasks, and can be used to enforce that a particular field applies
    to a particular category of objects.
 
    @see SKPhysicsBody.fieldBitMask
    @see SKEmitterNode.fieldBitMask
 */
@property (nonatomic) uint32_t categoryBitMask;

/** directed fields' directions can be accessed here. If the field is non-directional, a zero vector will be returned
 
 @see linearGravityFieldWithVector:direction
 @see velocityFieldWithVector:direction
 */
@property (nonatomic) vector_float3 direction;

/** fields without a smoothness component will return 0
 
    @see noiseFieldWithSmoothness:smoothness:animationSpeed
    @see turbulenceFieldWithSmoothness:smoothness:animationSpeed
 */
@property (nonatomic) float smoothness;

/** fields that can be animated can have non zero values.
 
    A value of 2 will animated twice as fast as a value of 1.
 
   @see noiseFieldWithSmoothness:smoothness:animationSpeed
   @see turbulenceFieldWithSmoothness:smoothness:animationSpeed
 */
@property (nonatomic) float animationSpeed;

/** fields constructed with a texture can be uppdated by assigning a new texture
 
    @see velocityFieldWithTexture:velocityTexture
 */
@property (nonatomic, retain, nullable) SKTexture* texture;

/**
 Slows an object proportionally to the object’s velocity.
 Use this to simulate effects such as friction from motion through the air.
 */
+ (SKFieldNode *)dragField;

/**
 Applies a force tangential to the direction from the sample point to the field's position.
 The force will be CCW to the direction. Make the strength negative to apply force in the CW direction.
 Amount is proportional to distance from center and the object's mass.
 Use this to create effects such as tornadoes.
 */
+ (SKFieldNode *)vortexField;

/**
 Applies a force in the direction of the origin of the field in local space. To repel objects, use a negative strength.
 The force is proportional to the distance from the field origin. Varies with the mass of the object according to F = ma
 The field node's rotation property can be used to orient the gravity in a particular direction.
 */
+ (SKFieldNode *)radialGravityField;

/**
 Applies a force in the direction of the vector in the local space. To repel objects, use a negative strength.
 The force is the same everywhere in the field. Varies with the mass of the object according to F = ma
 The field node's rotation property can be used to orient the gravity in a particular direction.
 @param direction The direction the force is applied in the x,y plane. The length of the direction vector is multiplied by the field's strength property to get the final calculated force. All three components of the direction vector are used to calculate the length.
 
 @see direction
 */
+ (SKFieldNode *)linearGravityFieldWithVector:(vector_float3)direction;

/**
 Uses the supplied velocity vector for any object entering the field’s area of effect.
 Velocity fields override the effect of any other acceleration applied to the body.
 Velocity fields are typically used for such effects as advection, for example, a velocity field
 might describe the velocity on the surface of a river. An object placed in the river would then follow the river.

 @param direction The directed velocity that will be applied to the body. The z component is ignored.

 @see direction
 */
+ (SKFieldNode *)velocityFieldWithVector:(vector_float3)direction;

/**
 The supplied texture contains velocity values for any object entering the field’s area of effect.
 If no texture is supplied, the direction property is used instead.
 Velocity fields override the effect of any other acceleration applied to the body.
 Velocity fields are typically used for such effects as advection, for example, a velocity field
 might describe the velocity on the surface of a river. An object placed in the river would then follow the river.

 @param velocityTexture The R and G channels of the supplied texture become x and y components of velocity. B and A, if present in the SKTexture, are ignored.
 
 @see texture
 */
+ (SKFieldNode *)velocityFieldWithTexture:(SKTexture *)velocityTexture;

/**
 A time varying differentiable Perlin simplex noise field. By default a smooth noise is calculated,
 and the field is time varying. Use this to simulate such effects as fireflies, or snow.
 To freeze the noise in place, set animationSpeed to 0.0. Mass is ignored.

 @param smoothness value of 0 means as noisy as possible, 1 means as smooth as possible
 @param animationSpeed is the general rate in Hz that any particular texel changes to a different value
 
 @see smoothness
 @see animationSpeed
 */
+ (SKFieldNode *)noiseFieldWithSmoothness:(CGFloat)smoothness animationSpeed:(CGFloat)speed;

/**
 Just like Noise, except the strength of the noise is proportional to the velocity of the object in the field.
 
 @param smoothness value of 0 means as noisy as possible, 1 means as smooth as possible
 @param animationSpeed is the general rate in Hz that any particular texel changes to a different value
 
 @see smoothness
 @see animationSpeed
 */
+ (SKFieldNode *)turbulenceFieldWithSmoothness:(CGFloat)smoothness animationSpeed:(CGFloat)speed;

/**
 A Hooke’s law force - a force linearly proportional to distance from the center of the field. An object in this
 field will oscillate with a period proportional to the inverse of the mass.
 An example use is to keep objects confined to a particular region.
 */
+ (SKFieldNode *)springField;

/**
 A force proportional to the charge on the object. A charge property has been
 added to SKPhysicsBodies to accomplish this. An example use of this field is to make objects behavior differently
 from one another when they enter a region, or to make an object's behavior different than its mass based behavior
 This field models the first part of the Lorentz equation, F = qE
 */
+ (SKFieldNode *)electricField;

/**
 A force proportional to the charge on the object and the object’s velocity. A charge property has been
 added to SKPhysicsBodies to accomplish this. An example use of this field is to make objects behavior differently
 from one another when they enter a region, or to make an object's behavior different than its mass based behavior
 This field models the second part of the Lorentz equation, F = qvB
 */
+ (SKFieldNode *)magneticField;


/**
 A field force with a custom force evaluator.
 
 @param position The location to evaluate the force at
 @param velocity The velocity to be considered during force evaluation. Useful for calculating drag.
 @param mass The mass to be taken into account during force evaluation
 @param charge The charge to be taken into accoutn during force evaluation
 @param deltaTime The current time step
 */
typedef vector_float3 (^SKFieldForceEvaluator)(vector_float3 position, vector_float3 velocity, float mass, float charge, NSTimeInterval deltaTime);
+ (SKFieldNode *)customFieldWithEvaluationBlock:(SKFieldForceEvaluator)block;

@end

NS_ASSUME_NONNULL_END
