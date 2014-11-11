//
//  SCNRenderer.h
//
//  Copyright (c) 2012-2014 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNSceneRenderer.h>
#import <SceneKit/SCNTechnique.h>

/*! @class SCNRenderer
	@abstract SCNRenderer lets you use the SceneKit renderer in an OpenGL context of your own.
 */

SCENEKIT_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNRenderer : NSObject <SCNSceneRenderer, SCNTechniqueSupport>
{
@protected
	id _reserved;
}

/*! 
 @method rendererWithContext:options:
 @abstract Creates a new renderer object. Its render target is the specified Core OpenGL context.
 @param context A Core OpenGL render context that is used as the render target (usually a CGLContextObj).
 @param options An optional dictionary for future extensions.
 */
+ (instancetype)rendererWithContext:(void *)context options:(NSDictionary *)options;

/*! 
 @property scene
 @abstract Specifies the scene of the receiver
 */
@property(nonatomic, retain) SCNScene *scene;

/*! 
 @method render
 @abstract renders the receiver's scene at the current system time.
 */
- (void)render;

/*!
 @method render
 @abstract renders the receiver's scene at the specified time (system time).
 */
- (void)renderAtTime:(CFTimeInterval) time SCENEKIT_AVAILABLE(10_10, 8_0);

/*!
 @property nextFrameTime
 @abstract Returns the time at which the next update should happen. If infinite no update needs to be scheduled yet. If the current frame time, a continuous animation is running and an update should be scheduled after a "natural" delay.
 */
@property(nonatomic, readonly) CFTimeInterval nextFrameTime SCENEKIT_AVAILABLE(10_10, 8_0);

@end


