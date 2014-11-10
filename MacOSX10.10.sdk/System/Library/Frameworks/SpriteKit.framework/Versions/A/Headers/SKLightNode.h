/**
 @header
 
 Light Nodes are used to light or shadow a scene.
 
 @copyright 2013 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SKSpriteNode.h>
#import <SpriteKit/SpriteKitBase.h>

SK_EXPORT NS_AVAILABLE(10_10, 8_0) @interface SKLightNode : SKNode

/**
 Enables or disables lighting contribution from this light node.
 
 Set to YES; sprites using this light will be lit with the ambient color and
 the light color, with a falloff in intensity according to the falloff property.
 
 Set to NO; this light does not contribute any lighting.
 
 If no lights are active on a sprite it will be drawn normally, as if not lit.
 
 The default value is YES.
 
 @see lightColor
 @see falloff
 @see categoryBitMask
 */
@property (nonatomic, getter = isEnabled) BOOL enabled;

/**
 Diffuse and Specular color of the light source, defaults to opaque white.
 
 The alpha component of the color is ignored.
 
 If using shaders bind a uniform to this property to use scene based custom lighting.
 
 @see SKUniform
 @see falloff
 */
@property (nonatomic) SKColor *lightColor;

/**
 Ambient color of the light source, defaults to black.
 
 If you had only a single light in the scene with an ambient color
 of opaque white and a light color of black,
 it would appear as if the scene was rendered without lighting.
 
 The alpha component of the color is ignored. The color is not
 affected by falloff or surface normals.
 
 @see lightColor
 */
@property (nonatomic) SKColor *ambientColor;

/**
 Color of the shadow casted on occluded objects, defaults to half opacity black.
 
 The alpha component of the color is used for blending with the regions that are in shadow.
 
 @see SKSpriteNode.shadowCastBitMask
 @see SKSpriteNode.shadowedBitMask
 */
@property (nonatomic) SKColor *shadowColor;

/**
 Falloff in intensity of the light over distance, defaults to 1.
 The falloff does not affect the ambient color nor the shadow color.
 
 @see lightColor
 */
@property (nonatomic) CGFloat falloff;

/**
 The category of the light, which determines the group(s) a light belongs to.
 Any node that has its corresponding light and shadow bitmasks set to an overlapping value
 will be lit, shadow casting or shadowed by this light.

 @see SKSpriteNode.lightingBitMask
 @see SKSpriteNode.shadowCastBitMask
 @see SKSpriteNode.shadowedBitMask
 */
@property (nonatomic) uint32_t categoryBitMask;


@end
