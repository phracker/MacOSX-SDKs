//
//  SCNParticleSystem.h
//  SceneKit
//
//  Copyright © 2014-2020 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNNode.h>
#import <SceneKit/SCNScene.h>

NS_ASSUME_NONNULL_BEGIN

@class UIColor;
@class SCNGeometry;

typedef NSString * SCNParticleProperty NS_STRING_ENUM;
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyPosition API_AVAILABLE(macos(10.10));        // float3 : {x,y,z}     controller animation type : {NSValue(SCNVector3)}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyAngle API_AVAILABLE(macos(10.10));           // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyRotationAxis API_AVAILABLE(macos(10.10));    // float3 : {x,y,z}     controller animation type : {NSValue(SCNVector3)}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyVelocity API_AVAILABLE(macos(10.10));        // float3 : {x,y,z}     controller animation type : {NSValue(SCNVector3)}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyAngularVelocity API_AVAILABLE(macos(10.10)); // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyLife API_AVAILABLE(macos(10.10));            // float                not controllable
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyColor API_AVAILABLE(macos(10.10));           // float4 : {r,g,b,a}   controller animation type : {UIColor}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyOpacity API_AVAILABLE(macos(10.10));         // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertySize API_AVAILABLE(macos(10.10));            // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyFrame API_AVAILABLE(macos(10.10));           // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyFrameRate API_AVAILABLE(macos(10.10));       // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyBounce API_AVAILABLE(macos(10.10));          // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyCharge API_AVAILABLE(macos(10.10));          // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyFriction API_AVAILABLE(macos(10.10));        // float                controller animation type : {NSNumber}

// These two properties are only available when handling the events of type SCNParticleEventCollision.
// They are read-only values.
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyContactPoint API_AVAILABLE(macos(10.10));    // float3               not controllable
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyContactNormal API_AVAILABLE(macos(10.10));   // float3               not controllable

/*!
 @typedef SCNParticleEventBlock
 @param data array of particle properties data stripes, ordered by the given NSArray of properties name in [- handleEvent:forProperties:withBlock:]
 @param dataStride array of particle properties data stripes stride, with the same ordering than data.
 @param indices optional array of count indices referencing the particles affected by the event. Only SCNParticleEventDeath and SCNParticleEventCollision provide this array. For SCNParticleEventBirth the indices are implicitely [0,1,2,..,count-1]
 @param count number of particles affected by the event
 @discussion This is a small example of usage of an event handling:
 [particleSystem handleEvent:SCNParticleEventCollision forProperties:@[SCNParticlePropertyAngle, SCNParticlePropertyRotationAxis, SCNParticlePropertyContactNormal] withBlock:^(void **data, size_t *dataStride, uint32_t *indices, NSInteger count) {
    for (NSInteger i = 0; i < count; ++i) {
        // SCNParticlePropertyAngle (float)
        float *angle = (float *)((char *)data[0] + dataStride[0] * indices[i]);
        // SCNParticlePropertyRotationAxis (float3)
        float *axis = (float *)((char *)data[1] + dataStride[1] * indices[i]);
        // SCNParticlePropertyContactNormal (float3)
        float *colNrm = (float *)((char *)data[2] + dataStride[2] * indices[i]);
     
        // rotate the particle (angle[0] and axis[0..2] based on the collision normal (colNrm[0..2])
        // ...
     }
 }];
*/
typedef void (^SCNParticleEventBlock)(void * _Nonnull * _Nonnull data, size_t * _Nonnull dataStride, uint32_t * _Nullable indices, NSInteger count);

/*!
 @typedef SCNParticleModifierBlock
 @param data array of particle properties data stripes, ordered by the given NSArray of properties name in [- handleEvent:forProperties:withBlock:]
 @param dataStride array of particle properties data stripes stride, with the same ordering than data.
 @param start index of the first particle
 @param end index of the last particle
 @param deltaTime duration of the simulation step, in seconds.
 @discussion This is a small example of usage of a modifier block:
 [self.particleSystem addModifierForProperties:@[SCNParticlePropertyPosition, SCNParticlePropertyVelocity] atStage:SCNParticleModifierStagePreCollision withBlock:^(void **data, size_t *dataStride, NSInteger start, NSInteger end, float deltaTime) {
     for (NSInteger i = start; i < end; ++i) {
        // SCNParticlePropertyPosition (float3)
        float *pos = (float *)((char *)data[0] + dataStride[0] * i);
        // SCNParticlePropertyVelocity (float3)
        float *vel = (float *)((char *)data[1] + dataStride[1] * i);
        
         // change velocity and/or position
         // ...
     }
 }];
*/
typedef void (^SCNParticleModifierBlock)(void * _Nonnull * _Nonnull data, size_t * _Nonnull dataStride, NSInteger start, NSInteger end, float deltaTime);

// Particle Sorting Mode
typedef NS_ENUM(NSInteger, SCNParticleSortingMode) {
	SCNParticleSortingModeNone,                        //particles are not sorted
	SCNParticleSortingModeProjectedDepth,              //particles are sorted by depth (far rendered first)
	SCNParticleSortingModeDistance,                    //particles are sorted by distance from the point of view
	SCNParticleSortingModeOldestFirst,                 //particles are sorted by birth date - oldest first
	SCNParticleSortingModeYoungestFirst                //particles are sorted by birth date - yougest first
} API_AVAILABLE(macos(10.10));

// Particle Blend Mode
typedef NS_ENUM(NSInteger, SCNParticleBlendMode) {
	SCNParticleBlendModeAdditive,
	SCNParticleBlendModeSubtract,
	SCNParticleBlendModeMultiply,
	SCNParticleBlendModeScreen,
	SCNParticleBlendModeAlpha,
	SCNParticleBlendModeReplace
} API_AVAILABLE(macos(10.10));

// Particle Orientation Mode
typedef NS_ENUM(NSInteger, SCNParticleOrientationMode) {
	SCNParticleOrientationModeBillboardScreenAligned,  // particles are aligned on screen
	SCNParticleOrientationModeBillboardViewAligned,    // particles are perpendicular with the vector from the point of view to the particle.
	SCNParticleOrientationModeFree, 	               // free on all axis.
    SCNParticleOrientationModeBillboardYAligned        // fixed on Y axis.
} API_AVAILABLE(macos(10.10));

// Particle Birth Location
typedef NS_ENUM(NSInteger, SCNParticleBirthLocation) {
    SCNParticleBirthLocationSurface,                   //particles are emitted on the surface of the emitter shape.
    SCNParticleBirthLocationVolume,                    //particles are emitted inside the volume of the emitter shape.
    SCNParticleBirthLocationVertex                     //particles are emitted on the vertices of the emitter shape.
} API_AVAILABLE(macos(10.10));

// Particle Birth Direction
typedef NS_ENUM(NSInteger, SCNParticleBirthDirection) {
    SCNParticleBirthDirectionConstant,                 // Z Direction of the Emitter.
    SCNParticleBirthDirectionSurfaceNormal,	           // Use the direction induced by the shape
    SCNParticleBirthDirectionRandom                    // Random direction.
} API_AVAILABLE(macos(10.10));

// Texture Animation Mode
typedef NS_ENUM(NSInteger, SCNParticleImageSequenceAnimationMode) {
    SCNParticleImageSequenceAnimationModeRepeat,             // The animation will loop.
    SCNParticleImageSequenceAnimationModeClamp,              // The animation will stop at both ends.
    SCNParticleImageSequenceAnimationModeAutoReverse         // The animation will reverse when reaching an end.
} API_AVAILABLE(macos(10.10));

// Particle Variation Mode
typedef NS_ENUM(NSInteger, SCNParticleInputMode) {
	SCNParticleInputModeOverLife,                  // The input time for the controller animation is the current life duration of the particle
	SCNParticleInputModeOverDistance,              // The input time for the controller animation is the distance from the variation origin node.
	SCNParticleInputModeOverOtherProperty,         // The input time for the controller animation is the current value of another specified property.
} API_AVAILABLE(macos(10.10));

// Particle Modifier Stage
typedef NS_ENUM(NSInteger, SCNParticleModifierStage) {
	SCNParticleModifierStagePreDynamics,
	SCNParticleModifierStagePostDynamics,
	SCNParticleModifierStagePreCollision,
	SCNParticleModifierStagePostCollision
} API_AVAILABLE(macos(10.10));

// Particle Event
typedef NS_ENUM(NSInteger, SCNParticleEvent) {
	SCNParticleEventBirth,                             // Event triggered when a new particle spawns.
	SCNParticleEventDeath,                             // Event triggered when a particle dies.
	SCNParticleEventCollision                          // Event triggered when a particle collides with a collider node.
} API_AVAILABLE(macos(10.10));

/*!
 @class SCNParticlePropertyController
 @abstract The SCNParticlePropertyController class controls the variation over time or over distance of a particle property.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNParticlePropertyController: NSObject <NSSecureCoding, NSCopying>

// Creates and initializes a particle property controller with the specified animation.
+ (instancetype)controllerWithAnimation:(CAAnimation *)animation API_UNAVAILABLE(watchos);

// Specifies the animation to be applied on the particle system property. The type of the animation will depend of the property controlled.
// See the documentation along property name definition.
@property(nonatomic, retain) CAAnimation *animation API_UNAVAILABLE(watchos);

// Specify the input mode of the receiver.
// This can be over life, over distance or over the evolution of another proprety.
// Defaults to SCNParticleInputModeOverLife.
@property(nonatomic) SCNParticleInputMode inputMode;

// Specifies the input scale and bias.
// inputScale defaults to 1 and inputBias to 0.
@property(nonatomic) CGFloat inputScale;
@property(nonatomic) CGFloat inputBias;

// Specifies an origin for the variation mode "SCNParticleInputModeOverDistance".
@property(nonatomic, weak, nullable) SCNNode *inputOrigin;

// Specifies which property to use as input for the input mode "SCNParticleInputModeOverOtherProperty".
@property(nonatomic, copy, nullable) SCNParticleProperty inputProperty;

@end


/*!
 @class SCNParticleSystem
 @abstract The SCNParticleSystem class represents a system of particles.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNParticleSystem : NSObject <NSCopying, NSSecureCoding, SCNAnimatable>

// Create an instance of a particle system
+ (instancetype)particleSystem;
+ (nullable instancetype)particleSystemNamed:(NSString *)name inDirectory:(nullable NSString *)directory;

#pragma mark Emitter properties

// Specifies the duration of the emission. Defaults to 1. Animatable.
@property(nonatomic) CGFloat emissionDuration;

// Specifies the variation of the emission duration. Defaults to 0. Animatable.
@property(nonatomic) CGFloat emissionDurationVariation;

// Specifies the idle duration between two emissions. Defaults to 0. Animatable.
@property(nonatomic) CGFloat idleDuration;

// Specifies the variation of the idle duration. Defaults to 0. Animatable.
@property(nonatomic) CGFloat idleDurationVariation;

// Specifies the looping behavior of the emission. Defaults to YES.
@property(nonatomic) BOOL loops;

// Specifies the particle rate flow, in particles per emissionDuration.
// An emissionDuration of 0 without looping means that the particles are emitted instantaneously
// 0 means that the emitter emits nothing, unless it has variation. Defaults to 1. Animatable.
@property(nonatomic) CGFloat birthRate;

// Specifies the variation of the rate flow. Defaults to 0. Animatable.
@property(nonatomic) CGFloat birthRateVariation;

// Specifies the time length during which particles are emit before the first rendering of the system.
// For example this allows to start a scene with snow that already has fallen. Defaults to 0. Animatable.
@property(nonatomic) CGFloat warmupDuration;

// Specifies the shape of the emitter. nil means a punctual emitter. Defaults to nil.
@property(nonatomic, retain, nullable) SCNGeometry *emitterShape;

// Specifies the location of newly created particles. Defaults to SCNParticleBirthLocationSurface.
@property(nonatomic) SCNParticleBirthLocation birthLocation;

// Specifies the direction of newly created particles. Defaults to SCNParticleBirthDirectionConstant.
@property(nonatomic) SCNParticleBirthDirection birthDirection;

// Specifies the spreading direction of newly created particles, in degrees. Not used in SCNParticleBirthDirectionRandom. Defaults to 0. Animatable.
@property(nonatomic) CGFloat spreadingAngle;

// Specifies the emitting direction of newly created particles, used in the SCNParticleBirthDirectionConstant mode. Defaults to {0, 0, 1}. Animatable.
@property(nonatomic) SCNVector3 emittingDirection;

// Specifies the orientation direction of newly created particles, used in the SCNParticleOrientationModeFree mode. The particle will rotate around this axis. Defaults to {0, 0, 0}, which means random. The particle will then rotate arbitraly. Animatable.
@property(nonatomic) SCNVector3 orientationDirection API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

// Specifies the acceleration applied to particles, in world coordinates.
// Allows to simulate winds or gravity. Defaults to {0, 0, 0}. Animatable.
@property(nonatomic) SCNVector3 acceleration;

// Specifies the rendering and simulation type of the system.
// If set to YES, the system is rendered with the transform of the attached node. Defaults to NO.
@property(nonatomic, getter=isLocal) BOOL local;

#pragma mark Particle properties

//  Specifies the initial angle of the particles at birth, in degrees. Defaults to 0. Animatable.
@property(nonatomic) CGFloat particleAngle;

// Specifies the variation of the initial angle of the particles at birth, in degrees. Defaults to 0. Animatable.
@property(nonatomic) CGFloat particleAngleVariation;

// Specifies the initial velocity of the particles at birth,
// in units per second. Defaults to 0. Animatable.
@property(nonatomic) CGFloat particleVelocity;

//  Specifies the variation of the velocity. Defaults to 0. Animatable.
@property(nonatomic) CGFloat particleVelocityVariation;

// Specifies the initial angular velocity of the particles at birth,
// in degrees per second. Defaults to 0. Animatable.
@property(nonatomic) CGFloat particleAngularVelocity;

// Specifies the variation of the angular velocity, in degrees per second. Defaults to 0. Animatable.
@property(nonatomic) CGFloat particleAngularVelocityVariation;

// Specifies the life span of particles. Animatable.
@property(nonatomic) CGFloat particleLifeSpan;

// Specifies the life span variation of particles. Animatable.
@property(nonatomic) CGFloat particleLifeSpanVariation;

// Specifies an optional system to spawn new particles when a particle dies
@property(nonatomic, retain, nullable) SCNParticleSystem *systemSpawnedOnDying;

// Specifies an optional system to spawn new particles when a particle dies
@property(nonatomic, retain, nullable) SCNParticleSystem *systemSpawnedOnCollision;

// Specifies an optional system to spawn new particles when a particle is alive
@property(nonatomic, retain, nullable) SCNParticleSystem *systemSpawnedOnLiving;

#pragma mark Particle Rendering

// Specifies the image of the particle.
// Can be set to an NSImage/UIImage, a path or a URL.
@property(nonatomic, retain, nullable) id particleImage;

// Specifies the number of column in the image sequence. Defaults to 1.
@property(nonatomic) NSUInteger imageSequenceColumnCount;

// Specifies the number of row in the image sequence. Defaults to 1
@property(nonatomic) NSUInteger imageSequenceRowCount;

// Specifies the texture initial frame index. Ranges from 0 to (imageSequenceColumnCount * imageSequenceRowCount - 1). Defaults to 0. Animatable.
@property(nonatomic) CGFloat imageSequenceInitialFrame;

// Specifies the texture initial frame variation. Animatable.
@property(nonatomic) CGFloat imageSequenceInitialFrameVariation;

// Specifies the texture animation frame rate, in frames per second. Defaults to 0. Animatable.
@property(nonatomic) CGFloat imageSequenceFrameRate;

// Specifies the texture animation frame rate variation, in frames per second. Defaults to 0. Animatable.
@property(nonatomic) CGFloat imageSequenceFrameRateVariation;

// Specifies the texture animation mode. Defaults to SCNTextureAnimationModeRepeat.
@property(nonatomic) SCNParticleImageSequenceAnimationMode imageSequenceAnimationMode;

// Specifies the initial color of the particle. Animatable. Defaults to opaque white.
@property(nonatomic, retain) UIColor *particleColor;

// Specifies the normalized variation of the color.
// With x : hue variation, y : saturation variation, z : brightness variation, w : alpha variation. Animatable.
@property(nonatomic) SCNVector4 particleColorVariation;

// Specifies the initial size of the particle. Animatable.
@property(nonatomic) CGFloat particleSize;

// Specifies the initial size variation of the particle. Animatable.
@property(nonatomic) CGFloat particleSizeVariation;

// Specifies the initial intensity of the particle. Animatable.
@property(nonatomic) CGFloat particleIntensity API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

// Specifies the initial intensity variation of the particle. Animatable.
@property(nonatomic) CGFloat particleIntensityVariation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

// Specifies the blend mode to use to render the particle system. Defaults to SCNParticleBlendModeAdditive.
@property(nonatomic) SCNParticleBlendMode blendMode;

// Specifies whether a black pass is required or not when rendering the particle system.
// This reinforces the contrast of additive/light systems. Defaults to NO.
@property(nonatomic, getter=isBlackPassEnabled) BOOL blackPassEnabled;

// Specifies the orientation mode of the particles. Defaults to SCNParticleOrientationModeBillboardScreenAligned.
@property(nonatomic) SCNParticleOrientationMode orientationMode;

// Specifies the sorting mode of the particles. Defaults to SCNParticleSortingModeNone.
@property(nonatomic) SCNParticleSortingMode sortingMode;

// Enables the lighting of particle systems
@property(nonatomic, getter=isLightingEnabled) BOOL lightingEnabled;

#pragma mark Particle Simulation

// Enables the use of the gravity defined in SCNPhysicsWorld
@property(nonatomic) BOOL affectedByGravity;

// Enables the effect of the physics fields added to the SCNPhysicsWorld
@property(nonatomic) BOOL affectedByPhysicsFields;

// Specifies whether particles die on collision
@property(nonatomic) BOOL particleDiesOnCollision;

// Specifies an array of SCNNode to collide with.
@property(nonatomic, copy, nullable) NSArray<SCNNode *> *colliderNodes;

// Specifies the particle mass. Animatable.
@property(nonatomic) CGFloat particleMass;

// Specifies the particle mass variation. Animatable.
@property(nonatomic) CGFloat particleMassVariation;

// Specifies the particle bounce. Animatable.
@property(nonatomic) CGFloat particleBounce;

// Specifies the particle bounce variation. Animatable.
@property(nonatomic) CGFloat particleBounceVariation;

// Specifies the particle friction. Animatable.
@property(nonatomic) CGFloat particleFriction;

// Specifies the particle friction variation. Animatable.
@property(nonatomic) CGFloat particleFrictionVariation;

// Specifies the charge on the particle. Charge determines the degree to which a particle is affected by
// electric and magnetic fields. Note that this is a unitless quantity, it is up to the developer to
// set charge and field strength appropriately. Defaults to 0.0. Animatable.
@property(nonatomic) CGFloat particleCharge;

// Specifies the particle charge variation. Animatable.
@property(nonatomic) CGFloat particleChargeVariation;

// Specifies the particle air resistance. Defaults to 0. Animatable.
@property(nonatomic) CGFloat dampingFactor;

// Specifies the simulation speed multiplier. Defaults to 1. Animatable.
@property(nonatomic) CGFloat speedFactor;

// Specifies whether particles stretch along their direction. Defaults to 0. Animatable.
@property(nonatomic) CGFloat stretchFactor;

// Specifies the receiver's fresnel exponent value. Defaults to 3. Animatable.
// Only used if the particleImage is a cube map. The bigger the amount, the more concentrated the reflection is around the edges
@property(nonatomic) CGFloat fresnelExponent;

// Property controllers.
@property(nonatomic, copy, nullable) NSDictionary<SCNParticleProperty, SCNParticlePropertyController *> *propertyControllers;

// Remove all the already-emitted particles and restart the simulation.
- (void)reset;

// Events handling
// "block" will be invoked for particles that trigger the specified event, with the data and dataStride that corresponds to "properties". The block should only update the particle properties reference by the "indices" passed as argument in the block.
- (void)handleEvent:(SCNParticleEvent)event forProperties:(NSArray<SCNParticleProperty> *)properties withBlock:(SCNParticleEventBlock)block;

// Modifications handling
// "block" will be invoked at every simulation step at the specified stage. The data and dataStride passed to the block will corresponds to the specified "properties".
- (void)addModifierForProperties:(NSArray<SCNParticleProperty> *)properties atStage:(SCNParticleModifierStage)stage withBlock:(SCNParticleModifierBlock)block;
- (void)removeModifiersOfStage:(SCNParticleModifierStage)stage;
- (void)removeAllModifiers;

@end


@interface SCNNode (SCNParticleSystemSupport)

// Add a particle system to the receiver.
- (void)addParticleSystem:(SCNParticleSystem *)system API_AVAILABLE(macos(10.10));

// Remove all particle systems of the receiver.
- (void)removeAllParticleSystems API_AVAILABLE(macos(10.10));

// Remove the specified particle system from the receiver.
- (void)removeParticleSystem:(SCNParticleSystem *)system API_AVAILABLE(macos(10.10));

// The particle systems attached to the node.
@property(readonly, nullable) NSArray<SCNParticleSystem *> *particleSystems API_AVAILABLE(macos(10.10));

@end


@interface SCNScene (SCNParticleSystemSupport)

// Add a particle system at the given location.
- (void)addParticleSystem:(SCNParticleSystem *)system withTransform:(SCNMatrix4)transform API_AVAILABLE(macos(10.10));

// Remove all particle systems in the scene.
- (void)removeAllParticleSystems API_AVAILABLE(macos(10.10));

// Remove the specified particle system from the receiver.
- (void)removeParticleSystem:(SCNParticleSystem *)system API_AVAILABLE(macos(10.10));

// The particle systems attached to the scene that are active.
@property(readonly, nullable) NSArray<SCNParticleSystem *> *particleSystems API_AVAILABLE(macos(10.10));

@end

NS_ASSUME_NONNULL_END
