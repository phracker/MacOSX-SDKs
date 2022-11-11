#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFieldBehavior.h>)
//
//  UIFieldBehavior.h
//  UIKit
//
//  Copyright (c) 2015-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIDynamicBehavior.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIRegion;

UIKIT_EXTERN API_AVAILABLE(ios(9.0)) NS_SWIFT_UI_ACTOR
@interface UIFieldBehavior : UIDynamicBehavior

- (instancetype)init NS_UNAVAILABLE; // Use one of the convenience initializers

- (void)addItem:(id <UIDynamicItem>)item;
- (void)removeItem:(id <UIDynamicItem>)item;

@property (nonatomic, readonly, copy) NSArray<id <UIDynamicItem>> *items;

/*!
 The position (origin) of the field in the reference coordinate system
 */
@property (nonatomic, assign) CGPoint position;

/*! 
 The region property is the domain of the field's effect. No force is applied to objects outside the region.
 The default region is the infiniteRegion
 */
@property (nonatomic, strong) UIRegion *region;

/*! Strength scaling value. default 1.0 */
@property (nonatomic, assign) CGFloat strength;

/*! The falloff exponent used to calculate field strength at a distance.
 Falloff starts at the minimum radius.
 The default exponent is zero, which results in a uniform field with no falloff.
 @see minimumRadius
 */
@property (nonatomic, assign) CGFloat falloff;

/*! Minimum radius of effect. Default is very small. */
@property (nonatomic, assign) CGFloat minimumRadius;

/*! The direction of the field.
 If the field is non-directional, a zero vector will be returned
 @see linearGravityFieldWithVector:direction
 @see velocityFieldWithVector:direction
 */
@property (nonatomic, assign) CGVector direction;

/*! Fields without a smoothness component will return 0
 @see noiseFieldWithSmoothness:smoothness:animationSpeed
 @see turbulenceFieldWithSmoothness:smoothness:animationSpeed
 */
@property (nonatomic, assign) CGFloat smoothness;

/*! Fields that can be animated can have non zero values. A value of 2 will animate twice as fast as a value of 1.
 @see noiseFieldWithSmoothness:smoothness:animationSpeed
 @see turbulenceFieldWithSmoothness:smoothness:animationSpeed
 */
@property (nonatomic, assign) CGFloat animationSpeed;

/*!
 Slows an object proportionally to the object’s velocity.
 Use this to simulate effects such as friction from motion through the air.
 */
+ (instancetype)dragField;

/*!
 Applies a force tangential to the direction from the sample point to the field's position.
 The force will be CCW to the direction. Make the strength negative to apply force in the CW direction.
 Amount is proportional to distance from center and the object's mass. This can be used to create rotational effects.
 */
+ (instancetype)vortexField;

/*!
 Applies a force in the direction of the origin of the field in local space. To repel objects, use a negative strength.
 The force is proportional to the distance from the field origin. Varies with the mass of the object according to F = ma
 @param position the origin of the field
 @see position
 */
+ (instancetype)radialGravityFieldWithPosition:(CGPoint)position;

/*!
 Applies a force in the direction of the vector in the local space. To repel objects, use a negative strength.
 The force is the same everywhere in the field. Varies with the mass of the object according to F = ma
 @param direction The direction the force is applied in the x,y plane. The length of the direction vector is multiplied by 
 the field's strength property to get the final calculated force. All components of the direction vector are used to calculate the length.
 @see direction
 */
+ (instancetype)linearGravityFieldWithVector:(CGVector)direction;

/*!
 Uses the supplied velocity vector for any object entering the field’s region of effect.
 Velocity fields override the effect of any other acceleration applied to the body.
 @param direction The directed velocity that will be applied to the body.
 @see direction
 */
+ (instancetype)velocityFieldWithVector:(CGVector)direction;

/*!
 A time varying differentiable Perlin simplex noise field. By default a smooth noise is calculated,
 and the field is time varying. To freeze the noise in place, set animationSpeed to 0.0. Mass is ignored.
 @param smoothness value of 0 means as noisy as possible, 1 means as smooth as possible
 @param animationSpeed is the general field rate of change in Hz
 @see smoothness
 @see animationSpeed
 */
+ (instancetype)noiseFieldWithSmoothness:(CGFloat)smoothness animationSpeed:(CGFloat)speed;

/*!
 Just like Noise, except the strength of the noise is proportional to the velocity of the object in the field.
 @param smoothness value of 0 means as noisy as possible, 1 means as smooth as possible
 @param animationSpeed is the general field rate of change in Hz
 @see smoothness
 @see animationSpeed
 */
+ (instancetype)turbulenceFieldWithSmoothness:(CGFloat)smoothness animationSpeed:(CGFloat)speed;

/*!
 A Hooke’s law force - a force linearly proportional to distance from the center of the field. An object in this
 field will oscillate with a period proportional to the inverse of the mass.
 An example use is to keep objects confined to a particular region.
 */
+ (instancetype)springField;

/*!
 A force proportional to the charge on the object. A charge property has been
 added to UIDynamicItemBehavior to accomplish this. An example use of this field is to make objects behavior differently
 from one another when they enter a region, or to make an object's behavior different than its mass based behavior
 This field models the first part of the Lorentz equation, F = qE
 */
+ (instancetype)electricField;

/*!
 The magnetic field is a uniform field in the positive-z direction (coming out of the screen). When the velocity 
 of a charged dynamic item is perpendicular to the uniform magnetic field, the item feels a resulting force normal
 to both the velocity and the B field. This results CCW circular motion. You can adjust the strength of the B field
 to be negative which will result in circular motion being CW instead of CCW. An example use of this field is to make 
 objects behavior differently from one another when they enter a region, or to make an object's behavior different 
 than its mass based behavior. This field models the second part of the Lorentz equation, F = qvB
 */
+ (instancetype)magneticField;

/*!
 A field force with a custom force evaluator.
 @param field the field being evaluated
 @param position The location to evaluate the force at
 @param velocity The velocity to be considered during force evaluation. Useful for calculating drag.
 @param mass The mass to be taken into account during force evaluation
 @param charge The charge to be taken into account during force evaluation
 @param deltaTime The current time step
 */
+ (instancetype)fieldWithEvaluationBlock:(CGVector(^)(UIFieldBehavior *field, CGPoint position, CGVector velocity, CGFloat mass, CGFloat charge, NSTimeInterval deltaTime))block;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIFieldBehavior.h>
#endif
