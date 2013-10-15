/**
 @header
 
 
 Shape Nodes are used to stroke or fill a CGPath
 

 @copyright 2011 Apple, Inc. All rights reserve.
 
 */

#import <SpriteKit/SKNode.h>
#import <SpriteKit/SpriteKitBase.h>

/**
 A SpriteKit Node used to stroke or fill a shape. CGPaths are used to supply the path.
 
 See CGPath <a href="http://developer.apple.com/library/mac/#documentation/GraphicsImaging/Reference/CGPath/Reference/reference.html">reference pages</a> for details on how to construct a CGPath.
 */
SK_EXPORT @interface SKShapeNode : SKNode

/**
 The CGPath to be drawn (in the Node's coordinate space)
 */
@property (SK_NONATOMIC_IOSONLY) CGPathRef path;

/**
 The color to draw the path with. (for no stroke use [SKColor clearColor]). Defaults to [SKColor whiteColor].
 */
@property (SK_NONATOMIC_IOSONLY, retain) SKColor *strokeColor;

/**
 The color to fill the path with. Defaults to [SKColor clearColor] (no fill).
 */
@property (SK_NONATOMIC_IOSONLY, retain) SKColor *fillColor;

/**
 Sets the blend mode to use when composing the shape with the final framebuffer.
 @see SKNode.SKBlendMode
 */
@property (SK_NONATOMIC_IOSONLY) SKBlendMode blendMode;

/**
 If set to YES, the path stroke edges and caps is smoothed (antialiased) when drawn.
 */
@property (SK_NONATOMIC_IOSONLY, getter = isAntialiased) BOOL antialiased;

/**
 The width used to stroke the path. Widths larger than 2.0 may result in artifacts. Defaults to 1.0.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat lineWidth;

/**
 Add a glow to the path stroke of the specified width. Defaults to 0.0 (no glow)
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat glowWidth;

@end
