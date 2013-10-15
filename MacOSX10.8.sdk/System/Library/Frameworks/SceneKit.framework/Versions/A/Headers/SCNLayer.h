//
//  SCNLayer.h
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import <SceneKit/SCNSceneRenderer.h>


/*!
 @class SCNLayer
 @abstract A SCNLayer is a layer that can display a SCNScene. 
 */

SCENEKIT_AVAILABLE(10_7, NA)
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
