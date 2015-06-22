/**
 @header
 
 
 Shape Nodes are used to stroke or fill a CGPath
 

 @copyright 2011 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SKNode.h>
#import <SpriteKit/SKShader.h>
#import <SpriteKit/SpriteKitBase.h>


NS_ASSUME_NONNULL_BEGIN

/**
 A SpriteKit Node used to stroke or fill a shape. CGPaths are used to supply the path.
 
 See CGPath <a href="http://developer.apple.com/library/mac/#documentation/GraphicsImaging/Reference/CGPath/Reference/reference.html">reference pages</a> for details on how to construct a CGPath.
 */
SK_EXPORT @interface SKShapeNode : SKNode

/* Create a Shape Node using a CGPathRef, optionally centered at the Node's origin. */
+ (instancetype)shapeNodeWithPath:(CGPathRef)path NS_AVAILABLE(10_10, 8_0);
+ (instancetype)shapeNodeWithPath:(CGPathRef)path centered:(BOOL)centered NS_AVAILABLE(10_10, 8_0);

/* Create a Shape Node representing a Rect. */
+ (instancetype)shapeNodeWithRect:(CGRect)rect NS_AVAILABLE(10_10, 8_0);

/* Create a Shape Node representing a rect centered at the Node's origin. */
+ (instancetype)shapeNodeWithRectOfSize:(CGSize)size NS_AVAILABLE(10_10, 8_0);


/* Create a Shape Node representing a rounded rect with a corner radius */
+ (instancetype)shapeNodeWithRect:(CGRect)rect cornerRadius:(CGFloat)cornerRadius NS_AVAILABLE(10_10, 8_0);

/* Create a Shape Node representing a rounded rect with a corner radius centered at the Node's origin. */
+ (instancetype)shapeNodeWithRectOfSize:(CGSize)size cornerRadius:(CGFloat)cornerRadius NS_AVAILABLE(10_10, 8_0);


/* Create a Shape Node representing an circle centered at the Node's origin. */
+ (instancetype)shapeNodeWithCircleOfRadius:(CGFloat)radius NS_AVAILABLE(10_10, 8_0);


/* Create a Shape Node representing an Ellipse inscribed within a Rect */
+ (instancetype)shapeNodeWithEllipseInRect:(CGRect)rect NS_AVAILABLE(10_10, 8_0);

/* Create a Shape Node representing an Ellipse inscribed within a Rect centered at the Node's origin. */
+ (instancetype)shapeNodeWithEllipseOfSize:(CGSize)size NS_AVAILABLE(10_10, 8_0);


/* Create a Shape Node representing an a series of Points interpreted as line segments */
+ (instancetype)shapeNodeWithPoints:(CGPoint *)points count:(size_t)numPoints NS_AVAILABLE(10_10, 8_0);

/* Create a Shape Node representing a smoothed spline that passes through a series of Points */
+ (instancetype)shapeNodeWithSplinePoints:(CGPoint *)points count:(size_t)numPoints NS_AVAILABLE(10_10, 8_0);

/**
 The CGPath to be drawn (in the Node's coordinate space)
 */
@property (nonatomic, nullable) CGPathRef path;

/**
 The color to draw the path with. (for no stroke use [SKColor clearColor]). Defaults to [SKColor whiteColor].
 */
@property (nonatomic, retain) SKColor *strokeColor;

/**
 The color to fill the path with. Defaults to [SKColor clearColor] (no fill).
 */
@property (nonatomic, retain) SKColor *fillColor;

/**
 Sets the blend mode to use when composing the shape with the final framebuffer.
 @see SKNode.SKBlendMode
 */
@property (nonatomic) SKBlendMode blendMode;

/**
 If set to YES, the path stroke edges and caps is smoothed (antialiased) when drawn.
 */
@property (nonatomic, getter = isAntialiased) BOOL antialiased;

/**
 The width used to stroke the path. Widths larger than 2.0 may result in artifacts. Defaults to 1.0.
 */
@property (nonatomic) CGFloat lineWidth;

/**
 Add a glow to the path stroke of the specified width. Defaults to 0.0 (no glow)
 */
@property (nonatomic) CGFloat glowWidth;

/**
 The cap type that should be used when stroking a non-closed path
 */
@property (nonatomic) CGLineCap lineCap;

/**
 The join type that should be used when stroking a path
 */
@property (nonatomic) CGLineJoin lineJoin;

/**
 When a miter join is used, the maximum ratio of miter length to line with to be used
 */
@property (nonatomic) CGFloat miterLimit;

/**
 The length of the node's path if it were to be stroked
 */
@property (nonatomic, readonly) CGFloat lineLength;

/* An optional Texture used for the filling the Shape */
@property (nonatomic, retain, nullable) SKTexture *fillTexture NS_AVAILABLE(10_10, 8_0);

/* An optional SKShader used for the filling the Shape */
@property (nonatomic, retain, nullable) SKShader *fillShader NS_AVAILABLE(10_10, 8_0);


/* An optional Texture used for the Shape's stroke. */
@property (nonatomic, retain, nullable) SKTexture *strokeTexture NS_AVAILABLE(10_10, 8_0);

/* An optional SKShader used for the Shape's Stroke. */
@property (nonatomic, retain, nullable) SKShader *strokeShader NS_AVAILABLE(10_10, 8_0);

@end

NS_ASSUME_NONNULL_END
