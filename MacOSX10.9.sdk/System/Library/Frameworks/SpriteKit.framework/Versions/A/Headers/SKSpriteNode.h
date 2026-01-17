/**
 @header
 
 
 Sprites display textured rectangles in the SpriteKit scene graph.
 
 A Sprite as defined in this Framework is a textured and colored rectangle. It is a quick and easy way to display 2D images on screen and includes the basic components needed to allow many of these to interact on screen at once.
 
 A SpriteNode is a node that displays a Sprite. As it is a Node it can be transformed, be included as a child in another node and have child nodes of its own.
 

 
 @copyright 2011 Apple, Inc. All rights reserve.
 
 */

#import <SpriteKit/SKNode.h>
#import <SpriteKit/SpriteKitBase.h>

/**
 A Sprite is a textured 2D node. It can be placed, rotated, scaled and animated like any other node except it draws a textured rectangle specified by the bounds and anchor point.
 
 Sprites are used to define quad primitives with color and/or textures applied to them.
 See <a href="http://en.wikipedia.org/wiki/Sprite_(computer_graphics)">wiki</a> for a definition of a Sprite.
 
 */
SK_EXPORT @interface SKSpriteNode : SKNode

/**
 Create a sprite with an SKTexture and the specified size.
 @param texture the texture to reference for size and content
 @param size the size of the sprite in points
 */
+ (instancetype)spriteNodeWithTexture:(SKTexture *)texture size:(CGSize)size;

/**
 Create a sprite with an SKTexture and set its size to the SKTexture's pixel width/height.
 @param texture the texture to reference for size and content
 */
+ (instancetype)spriteNodeWithTexture:(SKTexture *)texture;

/**
 Create a sprite with an image from your app bundle (An SKTexture is created for the image and set on the sprite. Its size is set to the SKTexture's pixel width/height)
 The position of the sprite is (0, 0) and the texture anchored at (0.5, 0.5), so that it is offset by half the width and half the height.
 Thus the sprite has the texture centered about the position. If you wish to have the texture anchored at a different offset set the anchorPoint to another pair of values in the interval from 0.0 up to and including 1.0.
 @param name the name that can be used to find the sprite in later queries
 */
+ (instancetype)spriteNodeWithImageNamed:(NSString *)name;

/**
 Create a sprite with a color and the specified bounds.
 @param color the color to use for tinting the sprite.
 @param size the size of the sprite in points
 */
+ (instancetype)spriteNodeWithColor:(SKColor *)color size:(CGSize)size;

/**
 Designated Initializer
 Initialize a sprite with a color and the specified bounds.
 @param texture the texture to use (can be nil for colored sprite)
 @param color the color to use for tinting the sprite.
 @param size the size of the sprite in points
 */
- (instancetype)initWithTexture:(SKTexture *)texture color:(SKColor *)color size:(CGSize)size;

/**
 Initialize a sprite with an SKTexture and set its size to the SKTexture's width/height.
 @param texture the texture to reference for size and content
 */
- (instancetype)initWithTexture:(SKTexture *)texture;

/**
 Initialize a sprite with an image from your app bundle (An SKTexture is created for the image and set on the sprite. Its size is set to the SKTexture's pixel width/height)
 The position of the sprite is (0, 0) and the texture anchored at (0.5, 0.5), so that it is offset by half the width and half the height.
 Thus the sprite has the texture centered about the position. If you wish to have the texture anchored at a different offset set the anchorPoint to another pair of values in the interval from 0.0 up to and including 1.0.
 @param name the name or path of the image to load.
 */
- (instancetype)initWithImageNamed:(NSString *)name;

/**
 Initialize a sprite with a color and the specified bounds.
 @param color the color to use for tinting the sprite.
 @param size the size of the sprite in points
 */
- (instancetype)initWithColor:(SKColor *)color size:(CGSize)size;

/**
 Texture to be drawn (is stretched to fill the sprite)
 */
@property (SK_NONATOMIC_IOSONLY, retain) SKTexture *texture;

/**
 Controls how the texture is stretched to fill the SKSpriteNode. Stretching is performed via a 9-part algorithm where the upper & lower middle parts are scaled horizontally, the left and right middle parts are scaled vertically, the center is scaled in both directions, and the corners are preserved. The centerRect defines the center region in a (0.0 - 1.0) coordinate space. Defaults to {(0,0) (1,1)} (the entire texture is stretched).
*/
@property (SK_NONATOMIC_IOSONLY) CGRect centerRect;

/**
 Controls the blending between the texture and the sprite's color. The valid interval of values is from 0.0 up to and including 1.0. A value above or below that interval is clamped to the minimum (0.0) if below or the maximum (1.0) if above.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat colorBlendFactor;

/**
 Base color for the sprite (If no texture is present, the color still is drawn)
 */
@property (SK_NONATOMIC_IOSONLY, retain) SKColor *color;

/**
 Sets the blend mode to use when composing the sprite with the final framebuffer.
 @see SKNode.SKBlendMode
 */
@property (SK_NONATOMIC_IOSONLY) SKBlendMode blendMode;

/**
 Used to choose the location in the sprite that maps to its 'position' in the parent's coordinate space. The valid interval for each input is from 0.0 up to and including 1.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGPoint anchorPoint;

/**
 Set the size of the sprite (in parent's coordinate space)
 */
@property (SK_NONATOMIC_IOSONLY) CGSize size;

@end
