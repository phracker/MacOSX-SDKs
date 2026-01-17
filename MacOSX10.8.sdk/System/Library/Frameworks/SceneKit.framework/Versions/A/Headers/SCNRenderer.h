//
//  SCNRenderer.h
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNSceneRenderer.h>

/*! @class SCNRenderer
	@abstract SCNRenderer lets you use the SceneKit renderer in an OpenGL context of your own.
 */

SCENEKIT_AVAILABLE(10_7, NA)
@interface SCNRenderer : NSObject <SCNSceneRenderer>
{
@private
	id _reserved;
}

/*! 
 @method rendererWithContext:options:
 @abstract Creates a new renderer object. Its render target is the specified Core OpenGL context.
 @param context A Core OpenGL render context that is used as the render target (usually a CGLContextObj).
 @param options An optional dictionary for future extensions.
 */
+ (SCNRenderer *)rendererWithContext:(void *)context options:(NSDictionary *)options;

/*! 
 @property scene
 @abstract Specifies the scene of the receiver
 */
@property(nonatomic, retain) SCNScene *scene;

/*! 
 @method render
 @abstract renders the current scene at the current time.
 */
- (void) render;

@end


