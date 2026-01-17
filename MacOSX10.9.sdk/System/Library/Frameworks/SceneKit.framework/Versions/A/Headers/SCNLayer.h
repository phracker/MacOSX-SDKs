//
//  SCNLayer.h
//
//  Copyright (c) 2012-2013 Apple Inc. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import <SceneKit/SCNSceneRenderer.h>

/*!
 @class SCNLayer
 @abstract A SCNLayer is a layer that can display a SCNScene. 
 */

SCENEKIT_CLASS_AVAILABLE(10_8, NA)
@interface SCNLayer : CAOpenGLLayer  <SCNSceneRenderer>
{	
@private
	id _reserved;
}

/*! 
 @property scene
 @abstract Specifies the scene of the receiver
 */
@property(nonatomic, retain) SCNScene *scene;

@end
