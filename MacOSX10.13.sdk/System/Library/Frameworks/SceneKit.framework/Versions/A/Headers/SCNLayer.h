//
//  SCNLayer.h
//
//  Copyright (c) 2012-2017 Apple Inc. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import <SceneKit/SCNSceneRenderer.h>
#import <SceneKit/SCNTechnique.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 @class SCNLayer
 @abstract A SCNLayer is a layer that can display a SCNScene. 
 */

API_UNAVAILABLE(ios, tvos, watchos)
@interface SCNLayer : CAOpenGLLayer <SCNSceneRenderer, SCNTechniqueSupport>

/*! 
 @property scene
 @abstract Specifies the scene of the receiver
 */
@property(nonatomic, retain, nullable) SCNScene *scene;

@end


NS_ASSUME_NONNULL_END
