/**
 @header
 
 
 Particle Emitter Node
 
 
 @copyright 2011 Apple, Inc. All rights reserve.
 
 */

#import <SpriteKit/SKSpriteNode.h>
#import <SpriteKit/SKKeyframeSequence.h>
#import <SpriteKit/SpriteKitBase.h>

/**
 An emitter of particle sprites.
 */
SK_EXPORT @interface SKEmitterNode : SKNode

/**
 The particle simulation is stepped automatically each frame when present in the scene. This allows the user to manually advance the simulation by a fixed amount of time. Useful for pre-populating particles before adding them to the scene.
 */

- (void)advanceSimulationTime:(NSTimeInterval)sec;

/* Removes all particles and restarts the emitter */
- (void)resetSimulation;

/**
 The texture to be used for the particles.
 */
@property (SK_NONATOMIC_IOSONLY, retain) SKTexture *particleTexture;

/**
 The starting z-position for each particle. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleZPosition;

/**
 The random variance about the starting z-position for each particle. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleZPositionRange;

/**
 The blend mode for each particle. Defaults to SKBlendModeAlpha.
 */
@property (SK_NONATOMIC_IOSONLY) SKBlendMode particleBlendMode;

/**
 The starting color for each particle. Defaults to clear.
 */
@property (SK_NONATOMIC_IOSONLY, retain) SKColor *particleColor;

/**
 The random variance about each color component for each particle. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleColorRedRange;
@property (SK_NONATOMIC_IOSONLY) CGFloat particleColorGreenRange;
@property (SK_NONATOMIC_IOSONLY) CGFloat particleColorBlueRange;
@property (SK_NONATOMIC_IOSONLY) CGFloat particleColorAlphaRange;

/**
 The rate at which to modify each color component for each particle (per second).
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleColorRedSpeed;
@property (SK_NONATOMIC_IOSONLY) CGFloat particleColorGreenSpeed;
@property (SK_NONATOMIC_IOSONLY) CGFloat particleColorBlueSpeed;
@property (SK_NONATOMIC_IOSONLY) CGFloat particleColorAlphaSpeed;

@property (SK_NONATOMIC_IOSONLY, retain) SKKeyframeSequence *particleColorSequence;

/**
 The starting color blend for each particle. Behaves the same as SKSpriteNode. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleColorBlendFactor;

/**
 The random variance about the starting color blend for each particle. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleColorBlendFactorRange;

/**
 The rate at which to modify the color blend for each particle. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleColorBlendFactorSpeed;

@property (SK_NONATOMIC_IOSONLY, retain) SKKeyframeSequence *particleColorBlendFactorSequence;

/**
 The starting position for each particle in the emitter's coordinate space. Defaults to (0.0, 0,0).
 */
@property (SK_NONATOMIC_IOSONLY) CGPoint particlePosition;

/**
 The random variance about the starting position for each particle in the emitter's coordinate space. Defaults to (0.0, 0,0).
 */
@property (SK_NONATOMIC_IOSONLY) CGVector particlePositionRange;


/**
 The starting speed for each particle along its emission vector. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleSpeed;

/**
 The random variance about the starting speed for each particle along its emission vector. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleSpeedRange;

/**
 The angle at which to emit each new particle, in radians. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat emissionAngle;

/**
 The random variance about the angle at which to emit each new particle, in radians. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat emissionAngleRange;

/**
 The acceleration to apply to each particles velocity. Useful for simulating effects such as wind or gravity. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat xAcceleration;
@property (SK_NONATOMIC_IOSONLY) CGFloat yAcceleration;


/**
 The rate at which new particles are generated, in particles per second. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleBirthRate;


/**
 The number of particles that will be emitted. If set to 0, there is no limit. Defaults to 0.
 */
@property (SK_NONATOMIC_IOSONLY) NSUInteger numParticlesToEmit;

/**
 The lifetime of each particle, in seconds. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleLifetime;

/**
 The random variance about the lifetime of each particle, in seconds. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleLifetimeRange;


/**
 The starting z-rotation for each particle. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleRotation;

/**
 The random variance about the starting z-rotation for each particle. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleRotationRange;

/**
 The rate at which to modify the z-rotation for each particle. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleRotationSpeed;

/**
 The starting size for each particle. If set to CGSizeZero (the default) the particles will start at the size of the texture assigned to particleTexture. Note that particleScale and particleScaleRange will also have an effect on the effective size of each new particle.
 */
@property (SK_NONATOMIC_IOSONLY) CGSize particleSize;

/**
 The starting scale for each particle. Defaults to 1.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleScale;

/**
 The random variance about the starting scale for each particle. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleScaleRange;

/**
 The rate at which to modify the scale for each particle. Defaults to 0.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleScaleSpeed;

@property (SK_NONATOMIC_IOSONLY, retain) SKKeyframeSequence *particleScaleSequence;


/**
 The starting alpha for each particle. Defaults to 1.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleAlpha;

/**
 The random variance about the starting alpha for each particle. Defaults to 1.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleAlphaRange;

/**
 The rate at which to modify the alpha for each particle. Defaults to 1.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat particleAlphaSpeed;

@property (SK_NONATOMIC_IOSONLY, retain) SKKeyframeSequence *particleAlphaSequence;

/**
 The rate at which to modify the alpha for each particle. Defaults to 1.0.
 */
@property (SK_NONATOMIC_IOSONLY, copy) SKAction *particleAction;


/**
 Normally the particles are rendered as if they were a child of the SKEmitterNode, they can also be rendered as if they were a child of any other node in the scene by setting the targetNode property. Defaults to nil (standard behavior).
 */
@property (SK_NONATOMIC_IOSONLY, weak) SKNode *targetNode;

@end