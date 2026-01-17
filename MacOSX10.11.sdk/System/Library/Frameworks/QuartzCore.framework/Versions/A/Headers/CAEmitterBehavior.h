/* CoreAnimation - CAEmitterBehavior.h

   Copyright (c) 2013-2015, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

NS_ASSUME_NONNULL_BEGIN

@interface CAEmitterBehavior : NSObject <NSCoding>
{
@private
  unsigned int _type;
  NSString *_name;
  void *_attr;
  void *_cache;
  uint32_t _flags;
}

+ (NSArray<NSString *> *)behaviorTypes;

+ (CAEmitterBehavior *)behaviorWithType:(NSString *)type;
- (id)initWithType:(NSString *)type;

@property(readonly) NSString *type;

@property(nullable, copy) NSString *name;

@property(getter=isEnabled) BOOL enabled;

- (NSArray *)inputKeys;
+ (NSDictionary *)attributesForKey:(NSString *)key;
- (NSDictionary *)attributesForKeyPath:(NSString *)keyPath;

@end

/** Behavior types. **/

/* `wave': Adds a force vector to each particle, modulating the
 * force value by a time-based wave function.
 *
 * CAPoint3D force: force vector [X Y Z].
 *
 * CGFloat frequency: oscillation frequency. The actual modulation
 * value is a triangular wave of the specified frequency composed with
 * a quadratic smoothstep function. */

CA_EXTERN NSString * const kCAEmitterBehaviorWave;

/* `drag': Adds a constant drag force to each particle.
 *
 * CGFloat drag: slowing amount, the force on the particle is
 * calculated as "V * -drag" where "V" is the particle's current
 * velocity. */

CA_EXTERN NSString * const kCAEmitterBehaviorDrag;

/* `alignToMotion': Aligns the particle image's Y axis to its velocity
 * vector.
 *
 * CGFloat rotation: angle in rotations to apply in addition to
 * orientation of the velocity vector.
 *
 * BOOL preservesDepth: if true will operate in 3D, i.e. by picking
 * an axis orthogonal to the required rotation. If false (the default)
 * operates in 2D by rotating about the Z axis. Note that only `plane'
 * type particles support a 3D orientation. */

CA_EXTERN NSString * const kCAEmitterBehaviorAlignToMotion;

/* `valueOverLife': Defines a particle property as a function of
 * their current time.
 *
 * NSString *keyPath: name of the property to change.
 * NSArray<NSNumber> *values: array of numeric values.
 * NSArray<NSNumber> *locations: optional array of stop-locations.
 *
 * The particles current time is divided by its lifetime to give a
 * value in the [0,1] range, which is then interpolated into the values
 * array. The property is then replaced by the color from the gradient.
 *
 * Supported property names include: `position.x', `position.y',
 * `position.z', `velocity.x', `velocity.y', `velocity.z', `mass',
 * `rotation', `spin', scale', `scaleSpeed', `color.red',
 * `color.green', `color.blue', `color.alpha'. */

CA_EXTERN NSString * const kCAEmitterBehaviorValueOverLife;

/* `colorOverLife': Defines the color of each particle as a function
 * of their current time.
 *
 * NSArray<CGColorRef> *colors: array of gradient color stops.
 * NSArray<NSNumber> *locations: optional array of stop-locations.
 *
 * The particles current time is divided by its lifetime to give a
 * value in the [0,1] range, which is then interpolated into the
 * gradient. The particle's color is then replaced by the color from
 * the gradient. */

CA_EXTERN NSString * const kCAEmitterBehaviorColorOverLife;

/* `light': Three-dimensional lighting.
 *
 * CGColorRef color: the light's color, alpha is ignored.
 * CGPoint position: the light's 2D position.
 * CGFloat zPosition: the light's position on Z axis.
 * NSNumber falloff, falloffDistance: falloff values.
 * NSNumber spot: if true, light is a spot-light.
 * NSNumber appliesAlpha: if true, lit object's alpha is also affected.
 *
 * For spot-lights:
 *   NSNumber directionLatitude, directionLongitude: the light's direction.
 *   NSNumber coneAngle, coneEdgeSoftness: the spot's lighting cone.
 *
 * See CALight.h for more description of the lighting behavior. */

CA_EXTERN NSString * const kCAEmitterBehaviorLight;

/* `attractor': force field.
 *
 * NSString attractorType: "radial" (default), "axial" or "planar".
 * NSNumber stiffness: the spring stiffness.
 * NSNumber radius: attractor radius, no effect inside.
 * CGPoint position: the attractor's 2D position.
 * CGFloat zPosition: the attractor's position on Z axis.
 * NSNumber orientationLatitude, orientationLongitude: the orientation
 * used as the axis of axial attractors or normal of planar attractors.
 * NSNumber falloff, falloffDistance: falloff values. */

CA_EXTERN NSString * const kCAEmitterBehaviorAttractor;

NS_ASSUME_NONNULL_END
