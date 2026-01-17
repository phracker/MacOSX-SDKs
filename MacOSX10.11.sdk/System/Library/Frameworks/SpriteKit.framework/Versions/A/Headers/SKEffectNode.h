/**
 @header
 
 
 Node that can apply an effect to its children
 
 
 @copyright 2011 Apple, Inc. All rights reserve.
 
 */

#import <SpriteKit/SKNode.h>
#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKShader.h>

NS_ASSUME_NONNULL_BEGIN
/**
 A SpriteKit node that applies frame buffer effects to the rendered results of its child nodes. This is done continuously on live content and is not a simple snapshot of the rendered result at one instant of time.
 */
SK_EXPORT @interface SKEffectNode : SKNode

/**
 A CIFilter to be used as an effect
 
 Any CIFilter that requires only a single "inputImage" and produces an "outputImage" is allowed. The filter is applied to all children of the SKEffectNode. If the filter is nil, the children of this node is flattened before being drawn as long as the SKEffectNode is enabled.
 */
@property (nonatomic, retain, nullable) CIFilter *filter;

/* Controls whether the filter's "inputCenter" (if it exists) should automatically be set to the center of the effect area. Defaults to YES. */
@property (nonatomic) BOOL shouldCenterFilter;

/**
 Enable the SKEffectNode.
 
 The SKEffectNode has no effect when appliesEffects is not enabled, this is useful for setting up an effect to use later on. Defaults to YES.
 */
@property (nonatomic) BOOL shouldEnableEffects;

/**
 Enable the rasterization on the SKEffectNode.
 
 The SKEffectNode's output is rasterized and cached internally. This cache is reused when rendering. When the SKEffectNode's children change, the cache is updated, but changing properties on the CIFilter does *not* cause an update (you must disable rasterization and then re-enable it for the changes to apply). This is more expensive than not rasterizing if the node's children change frequently, only enable this option if you know the children is largely static.
 */
@property (nonatomic) BOOL shouldRasterize;

/**
 Sets the blend mode to use when composing the effect with the final framebuffer.
 @see SKNode.SKBlendMode
 */
@property (nonatomic) SKBlendMode blendMode;

@property (nonatomic, retain, nullable) SKShader *shader;

@end

NS_ASSUME_NONNULL_END
