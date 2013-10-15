//
//  SCNCamera.h
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>

/*!
 @class SCNCamera
 @abstract SCNCamera represents a camera that can be attached to a SCNNode. 
 @discussion A node with a camera can be used as a point of view to visualize a 3D scene.
 */

SCENEKIT_AVAILABLE(10_7, NA)
@interface SCNCamera : NSObject <SCNAnimatable, NSCopying>
{	
@private
	id _reserved;
}

/*! 
 @method camera
 @abstract Creates and returns a camera instance.
 */

+ (SCNCamera *)camera;

/*! 
 @property name
 @abstract Determines the name of the receiver.
 */
@property(nonatomic, copy) NSString *name;

/*! 
 @property xFov
 @abstract Determines the receiver's field of view on the X axis (in degree). Animatable.
 */
@property(nonatomic) double xFov;

/*! 
 @property yFov
 @abstract Determines the receiver's field of view on the Y axis (in degree). Animatable.
 */
@property(nonatomic) double yFov;

/*! 
 @property zNear
 @abstract Determines the receiver's near value. Animatable.
 @discussion The near value determines the minimal distance between the camera and a visible surface. If a surface is closer to the camera than this minimal distance, then the surface is clipped. The near value must be different than zero.
 */
@property(nonatomic) double zNear;

/*! 
 @property zFar
 @abstract Determines the receiver's far value. Animatable.
 @discussion The far value determines the maximal distance between the camera and a visible surface. If a surface is further from the camera than this maximal distance, then the surface is clipped.
 */
@property(nonatomic) double zFar;

/*! 
 @property usesOrthographicProjection
 @abstract Determines whether the receiver uses an orthographic projection or not. Defaults to NO.
 */
@property(nonatomic) BOOL usesOrthographicProjection;

/*! 
 @method projectionTransform
 @abstract Returns the projection transform used by the camera to project the world onscreen. 
 */
- (CATransform3D)projectionTransform;

@end
