//
//  SCNParametricGeometry.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNGeometry;

/*!
 @class SCNPlane
 @abstract SCNPlane represents a rectangle with controllable width and height. The plane has one visible side.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNPlane : SCNGeometry

/*!
 @method planeWithWidth:height:
 @abstract Creates and returns a plane with given width and height.
 @param width The width of the plane.
 @param height The height of the plane.
 */
+ (instancetype)planeWithWidth:(CGFloat)width height:(CGFloat)height;

/*! 
 @property width
 @abstract The plane extent along the X axis. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat width;

/*! 
 @property height
 @abstract The plane extent along the Y axis. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat height;

/*! 
 @property widthSegmentCount
 @abstract The number of subdivisions along the X axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger widthSegmentCount;

/*! 
 @property heightSegmentCount
 @abstract The number of subdivisions along the Y axis. The default value is 1. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger heightSegmentCount;

/*!
 @property cornerRadius
 @abstract The corner radius. Animatable.
 @discussion If the value is strictly less than 0, the geometry is empty. The default value is 0.
 */
@property(nonatomic) CGFloat cornerRadius NS_AVAILABLE(10_9, 8_0);

/*!
 @property cornerSegmentCount
 @abstract The number of subdivisions for the rounded corners. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 10.
 */
@property(nonatomic) NSInteger cornerSegmentCount NS_AVAILABLE(10_9, 8_0);

@end


/*!
 @class SCNBox
 @abstract SCNBox represents a box with rectangular sides and optional chamfers.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNBox : SCNGeometry

/*!
 @method boxWithWidth:height:length:chamferRadius:
 @abstract Creates and returns a box with given width, height, length and chamfer radius.
 @param width The width of the box.
 @param height The height of the box.
 @param length The length of the box.
 @param chamferRadius The chamfer radius of the box.
 */
+ (instancetype)boxWithWidth:(CGFloat)width height:(CGFloat)height length:(CGFloat)length chamferRadius:(CGFloat)chamferRadius;

/*! 
 @property width
 @abstract The width of the box. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat width;

/*! 
 @property height
 @abstract The height of the box. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat height;

/*! 
 @property length
 @abstract The length of the box. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat length;

/*! 
 @property chamferRadius
 @abstract The chamfer radius. Animatable.
 @discussion If the value is strictly less than 0, the geometry is empty. The default value is 0.
 */
@property(nonatomic) CGFloat chamferRadius;

/*! 
 @property widthSegmentCount
 @abstract The number of subdivisions along the X axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger widthSegmentCount;

/*! 
 @property heightSegmentCount
 @abstract The number of subdivisions along the Y axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger heightSegmentCount;

/*! 
 @property lengthSegmentCount
 @abstract The number of subdivisions along the Z axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger lengthSegmentCount;

/*!
 @property chamferSegmentCount
 @abstract The number of chamfer subdivisions. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 10.
 */
@property(nonatomic) NSInteger chamferSegmentCount;

@end


/*!
 @class SCNPyramid
 @abstract SCNPyramid represents a right pyramid with a rectangular base.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNPyramid : SCNGeometry

/*!
 @method pyramidWithWidth:height:length:
 @abstract Creates and returns a pyramid with given width, height, and length.
 @param width The width of the pyramid.
 @param height The height of the pyramid.
 @param length The length of the pyramid.
 */
+ (instancetype)pyramidWithWidth:(CGFloat)width height:(CGFloat)height length:(CGFloat)length;

/*! 
 @property width
 @abstract The width of the pyramid base. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat width;

/*! 
 @property height
 @abstract The height of the pyramid. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat height;

/*! 
 @property length
 @abstract The length of the pyramid base. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat length;

/*! 
 @property widthSegmentCount
 @abstract The number of subdivisions along the X axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1. 
 */
@property(nonatomic) NSInteger widthSegmentCount;

/*! 
 @property heightSegmentCount
 @abstract The number of subdivisions along the Y axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1. 
 */
@property(nonatomic) NSInteger heightSegmentCount;

/*! 
 @property lengthSegmentCount
 @abstract The number of subdivisions along the Z axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1. 
 */
@property(nonatomic) NSInteger lengthSegmentCount;

@end


/*!
 @class SCNSphere
 @abstract SCNSphere represents a sphere with controllable radius
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNSphere : SCNGeometry

/*!
 @method sphereWithRadius:
 @abstract Creates and returns a sphere with given radius.
 @param radius The radius of the sphere.
 */
+ (instancetype)sphereWithRadius:(CGFloat)radius;

/*! 
 @property radius
 @abstract The sphere radius. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 0.5.
 */
@property(nonatomic) CGFloat radius;

/*! 
 @property geodesic
 @abstract Indicate if the geometry is a geosphere.
 @discussion The default value is NO.
 */
@property(nonatomic, getter=isGeodesic) BOOL geodesic;

/*!
 @property segmentCount
 @abstract The number of segments along both spherical coordinates. Animatable.
 @discussion If the value is less than 3, the behavior is undefined. The default value is 48.
 */
@property(nonatomic) NSInteger segmentCount;

@end


/*!
 @class SCNCylinder
 @abstract SCNCylinder represents a cylinder with controllable height and radius.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNCylinder : SCNGeometry

/*!
 @method cylinderWithRadius:height:
 @abstract Creates and returns a cylinder with given radius and height.
 @param radius The radius of the cylinder.
 @param height The height of the cylinder. 
 */
+ (instancetype)cylinderWithRadius:(CGFloat)radius height:(CGFloat)height;

/*! 
 @property radius
 @abstract The radius of the cylinder. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 0.5.
 */
@property(nonatomic) CGFloat radius;

/*! 
 @property height
 @abstract The height of the cylinder. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat height;

/*! 
 @property radialSegmentCount
 @abstract The number of subdivisions along the radial coordinate. Animatable.
 @discussion If the value is less than 3, the behavior is undefined. The default value is 48.
 */
@property(nonatomic) NSInteger radialSegmentCount;

/*! 
 @property heightSegmentCount
 @abstract The number of subdivisions along the Y axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger heightSegmentCount;

@end


/*!
 @class SCNCone
 @abstract SCNCone represents a cone with controllable height, top radius and bottom radius.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNCone : SCNGeometry

/*!
 @method coneWithTopRadius:bottomRadius:height:
 @abstract Creates and returns a cone with given top radius, bottom radius and height.
 @param topRadius The radius at the top of the cone.
 @param bottomRadius The radius at the bottom of the cone.
 @param height The height of the cone.
 */
+ (instancetype)coneWithTopRadius:(CGFloat)topRadius bottomRadius:(CGFloat)bottomRadius height:(CGFloat)height;

/*! 
 @property topRadius
 @abstract The radius at the top of the cone. Animatable.
 @discussion If the value is less than 0, the geometry is empty. The default value is 0.
 */
@property(nonatomic) CGFloat topRadius;

/*! 
 @property bottomRadius
 @abstract The radius at the bottom of the cone. Animatable.
 @discussion If the value is less than 0, the geometry is empty. The default value is 0.5.
 */
@property(nonatomic) CGFloat bottomRadius;

/*! 
 @property height
 @abstract The height of the cone. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat height;

/*! 
 @property radialSegmentCount
 @abstract The number of subdivisions along the radial coordinate. Animatable.
 @discussion If the value is less than 3, the behavior is undefined. The default value is 48.
 */
@property(nonatomic) NSInteger radialSegmentCount;

/*! 
 @property heightSegmentCount
 @abstract The number of subdivisions along the Y axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger heightSegmentCount;

@end


/*!
 @class SCNTube
 @abstract SCNTube represents a tube with controllable height, inner radius and outer radius.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNTube : SCNGeometry

/*!
 @method tubeWithInnerRadius:outerRadius:height:
 @abstract Creates and returns a tube with given inner radius, outer radius and height.
 @param innerRadius The inner radius of the tube.
 @param outerRadius The outer radius of the tube.
 @param height The height of the tube.
 */
+ (instancetype)tubeWithInnerRadius:(CGFloat)innerRadius outerRadius:(CGFloat)outerRadius height:(CGFloat)height;

/*! 
 @property innerRadius
 @abstract The inner radius of the tube. Animatable.
 @discussion If the value is less than or equal to 0, or if it is greater than or equal to the outer radius, then the geometry is empty. The default value is 0.25.
 */
@property(nonatomic) CGFloat innerRadius;

/*! 
 @property outerRadius
 @abstract The outer radius of the tube. Animatable.
 @discussion If the value is less than or equal to 0, or if it is less than or equal to the inner radius, then the geometry is empty. The default value is 0.5.
 */
@property(nonatomic) CGFloat outerRadius;

/*! 
 @property height
 @abstract The height of the tube. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat height;

/*! 
 @property radialSegmentCount
 @abstract The number of subdivisions along the radial coordinate. Animatable.
 @discussion If the value is less than 3, the behavior is undefined. The default value is 48.
 */
@property(nonatomic) NSInteger radialSegmentCount;

/*! 
 @property heightSegmentCount
 @abstract The number of subdivisions along the Y axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger heightSegmentCount;

@end


/*!
 @class SCNCapsule
 @abstract SCNCapsule represents a capsule with controllable height and cap radius.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNCapsule : SCNGeometry

/*!
 @method capsuleWithCapRadius:height:
 @abstract Creates and returns a capsule with given radius and height.
 @param capRadius The radius of the capsule.
 @param height The height of the capsule.
 */
+ (instancetype)capsuleWithCapRadius:(CGFloat)capRadius height:(CGFloat)height;

/*! 
 @property capRadius
 @abstract The cap radius of the capsule. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 0.5.
 */
@property(nonatomic) CGFloat capRadius;

/*! 
 @property height
 @abstract The height of the capsule. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 2.
 */
@property(nonatomic) CGFloat height;

/*! 
 @property radialSegmentCount
 @abstract The number of subdivisions along the radial coordinate. Animatable.
 @discussion If the value is less than 3, the behavior is undefined. The default value is 48.
 */
@property(nonatomic) NSInteger radialSegmentCount;

/*! 
 @property heightSegmentCount
 @abstract The number of subdivisions along the Y axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger heightSegmentCount;

/*! 
 @property capSegmentCount
 @abstract The number of subdivisions in the cap. Animatable.
 @discussion If the value is less than 2, the behavior is undefined. The default value is 24.
 */
@property(nonatomic) NSInteger capSegmentCount;

@end


/*!
 @class SCNTorus
 @abstract SCNTorus represents a torus with controllable ring radius and pipe radius.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNTorus : SCNGeometry

/*!
 @method torusWithRingRadius:pipeRadius:
 @abstract Creates and returns a torus with given ring radius and pipe radius.
 @param ringRadius The radius of the ring.
 @param pipeRadius The radius of the pipe.
 */
+ (instancetype)torusWithRingRadius:(CGFloat)ringRadius pipeRadius:(CGFloat)pipeRadius;

/*! 
 @property ringRadius
 @abstract The radius of the torus ring. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 0.5.
 */
@property(nonatomic) CGFloat ringRadius;

/*! 
 @property pipeRadius
 @abstract The radius of the torus pipe. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 0.25.
 */
@property(nonatomic) CGFloat pipeRadius;

/*! 
 @property ringSegmentCount
 @abstract The number of subdivisions of the ring. Animatable.
 @discussion If the value is less than 3, the behavior is undefined. The default value is 48.
 */
@property(nonatomic) NSInteger ringSegmentCount;

/*! 
 @property pipeSegmentCount
 @abstract The number of subdivisions of the pipe. Animatable.
 @discussion If the value is less than 3, the behavior is undefined. The default value is 24.
 */
@property(nonatomic) NSInteger pipeSegmentCount;

@end


/*!
 @class SCNFloor
 @abstract SCNFloor represents an infinite plane geometry. 
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNFloor : SCNGeometry 

/*!
 @method floor
 @abstract Creates and returns a floor.
 @discussion A floor is an infinite plane.
 */
+ (instancetype)floor;

/*! 
 @property reflectivity
 @abstract Specifies the reflectivity of the floor. Animatable.
 @discussion If the value is greater than zero then the surface will reflect other objects in the scene. The default value is 0.25.
 */
@property(nonatomic) CGFloat reflectivity;

/*! 
 @property reflectionFalloffStart
 @abstract Specifies the distance from the floor where the falloff begins. Animatable.
 @discussion The default value is 0.
 */
@property(nonatomic) CGFloat reflectionFalloffStart;

/*! 
 @property reflectionFalloffEnd
 @abstract Specifies the distance from the floor where the falloff finishes. Animatable.
 @discussion If the value is 0 then there is no falloff. The default value is 0.
 */
@property(nonatomic) CGFloat reflectionFalloffEnd;

/*!
 @property reflectionResolutionScaleFactor
 @abstract Specifies the resolution scale factor of the buffer used to render the reflection.
 @discussion Defaults to 1.0.
*/
@property(nonatomic) CGFloat reflectionResolutionScaleFactor NS_AVAILABLE(10_10, 8_0);

@end

/*!
 @class SCNText
 @abstract SCNText represents a block of text that has been extruded
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNText : SCNGeometry 

/*!
 @method textWithString:extrusionDepth:
 @abstract Creates and returns a 3D representation of given text with given extrusion depth.
 @param string The text to be represented.
 @param extrusionDepth The extrusion depth.
 */
+ (instancetype)textWithString:(nullable id)string extrusionDepth:(CGFloat)extrusionDepth;

/*! 
 @property extrusionDepth
 @abstract The extrusion depth. Animatable.
 @discussion If the value is 0, we get a mono-sided, 2D version of the text.
 */
@property(nonatomic) CGFloat extrusionDepth;

/*! 
 @property string
 @abstract The text to be represented. The text must be an instance of NSString or NSAttributedString.
 @discussion The default value is nil.
 */
@property(nonatomic, copy, nullable) id string;

/*! 
 @property font
 @abstract The font used to represent the text.
 @discussion The font property is only used when the string property is not an NSAttributedString. The default value is Helvetica size 36.
 */
@property(nonatomic, retain, null_resettable) NSFont *font;

/*!
 @property wrapped
 @abstract Determines whether the text is wrapped to fit within the bounds.
 @discussion For the text to be wrapped you first need to set its bounds, otherwise the text is not wrapped. The default value is NO.
 */
@property(nonatomic, getter=isWrapped) BOOL wrapped;

/*!
 @property containerFrame
 @abstract A container within which the text may be wrapped or truncated.
 @discussion The text will start at the top-left corner of the rect. You need to set this property for text truncation or alignment to work. Getting this property when it has never been set returns CGRectZero.
 */
@property(nonatomic) CGRect containerFrame;

/*!
 @property textSize
 @abstract Returns the bounding box size the receiver occupies.
 */
@property(nonatomic, readonly) CGSize textSize;

/*!
 @property truncationMode
 @abstract Describes how the text is truncated to fit within the bounds.
 @discussion For the text to be truncated you first need to set its bounds, otherwise the text is not truncated. The default value is kCATruncationNone. See truncation modes in CATextLayer.h.
 */
@property(nonatomic, copy) NSString *truncationMode;

/*!
 @property alignmentMode
 @abstract Determines how individual lines of text are horizontally aligned within the bounds.
 @discussion For the text to be aligned you first need to set its bounds, otherwise the text is not aligned. The default value is kCAAlignmentNatural. See alignments in CATextLayer.h.
 */
@property(nonatomic, copy) NSString *alignmentMode;

/*! 
 @property chamferRadius
 @abstract The chamfer radius. Animatable.
 @discussion Values are clamped to the range [0, extrusionDepth / 2]. The actual chamfer radius might be different to the one here specified: large values are clipped to a per-glyph max value. The default value is 0.
 */
@property(nonatomic) CGFloat chamferRadius;

/*! 
 @property chamferSegmentCount
 @abstract The number of chamfer subdivisions. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 10.
 */
@property(nonatomic) NSInteger chamferSegmentCount NS_DEPRECATED(10_8, 10_9, NA, NA);

/*!
 @property chamferProfile
 @abstract Describes the profile used to when "chamferRadius" is not nil. When "chamferProfile" is nil we fallback on a path representing a quadrant.
 @discussion The profile should be a 2D curve beginning at (0,1) and ending at (1,0). The "flatness" property is also used to flatten this path. The default value is nil.
 */
@property(nonatomic, copy, nullable) NSBezierPath *chamferProfile NS_AVAILABLE(10_9, 8_0);

/*!
 @property flatness
 @abstract Specifies the accuracy (or smoothness) with which fonts are rendered.
 @discussion Smaller numbers give smoother curves at the expense of more computation and heavier geometries in terms of vertices. The default value is 0.6, which yields smooth curves.
 */
@property(nonatomic) CGFloat flatness NS_AVAILABLE(10_9, 8_0);

@end

/*!
 @class SCNShape
 @abstract SCNShape represents a 2D shape (cubic Bezier spline) than can be extruded.
 */

typedef NS_ENUM(NSInteger, SCNChamferMode) {
    SCNChamferModeBoth,
    SCNChamferModeFront,
    SCNChamferModeBack
} NS_ENUM_AVAILABLE(10_9, 8_0);

NS_CLASS_AVAILABLE(10_9, 8_0)
@interface SCNShape : SCNGeometry

/*!
 @method shapeWithPath:extrusionDepth:
 @abstract Creates and returns a 3D representation of the given shape with the given extrusion depth.
 @param path The cubic Bezier spline to extrude.
 @param extrusionDepth The extrusion depth.
 */
+ (instancetype)shapeWithPath:(nullable NSBezierPath *)path extrusionDepth:(CGFloat)extrusionDepth;

/*!
 @property path
 @abstract The path defining the shape to be rendered.
 @discussion The path defines the outline of the shape. The path is filled using the even-odd rule. If the path is self-intersecting, the behavior is undefined.
 */
@property(nonatomic, copy, nullable) NSBezierPath *path;

/*!
 @property extrusionDepth
 @abstract The extrusion depth. Animatable.
 @discussion If the value is 0, we get a mono-sided, 2D version of the shape.
 */
@property(nonatomic) CGFloat extrusionDepth;

/*!
 @property chamferMode
 @abstract The sides of the text that are chamfered.
 @discussion The default value is SCNChamferModeBoth.
 */
@property(nonatomic) SCNChamferMode chamferMode;

/*!
 @property chamferRadius
 @abstract The chamfer radius. Animatable.
 @discussion Values are clamped to the range [0, extrusionDepth / 2]. The default value is 0.
 */
@property(nonatomic) CGFloat chamferRadius;

/*!
 @property chamferProfile
 @abstract Describes the profile used to when "chamferRadius" is not nil. When "chamferProfile" is nil we fallback on a path representing a quadrant.
 @discussion The profile should be a 2D curve beginning at (0,1) and ending at (1,0). The "flatness" property is also used to flatten this path. The default value is nil.
 */
@property(nonatomic, copy, nullable) NSBezierPath *chamferProfile;

@end

NS_ASSUME_NONNULL_END
