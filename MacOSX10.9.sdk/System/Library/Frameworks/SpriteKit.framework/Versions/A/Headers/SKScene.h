//
//  SKScene.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <SpriteKit/SKEffectNode.h>
#import <SpriteKit/SpriteKitBase.h>

@class SKView, SKPhysicsWorld;

typedef NS_ENUM(NSInteger, SKSceneScaleMode) {
    SKSceneScaleModeFill,           /* Scale the SKScene to fill the entire SKView. */
    SKSceneScaleModeAspectFill,     /* Scale the SKScene to fill the SKView while preserving the scene's aspect ratio. Some cropping may occur if the view has a different aspect ratio. */
    SKSceneScaleModeAspectFit,      /* Scale the SKScene to fit within the SKView while preserving the scene's aspect ratio. Some letterboxing may occur if the view has a different aspect ratio. */
    SKSceneScaleModeResizeFill      /* Modify the SKScene's actual size to exactly match the SKView. */
} NS_ENUM_AVAILABLE(10_9, 7_0);

/**
 A scene is the root node of your content. It is used to display SpriteKit content on an SKView.
 
 @see SKView
 */
SK_EXPORT @interface SKScene : SKEffectNode

/**
 Called once when the scene is created, do your one-time setup here.
 
 A scene is infinitely large, but it has a viewport that is the frame through which you present the content of the scene.
 The passed in size defines the size of this viewport that you use to present the scene.
 To display different portions of your scene, move the contents relative to the viewport. One way to do that is to create a SKNode to function as a viewport transformation. That node should have all visible conents parented under it.
 
 @param size a size in points that signifies the viewport into the scene that defines your framing of the scene.
 */
- (instancetype)initWithSize:(CGSize)size;

+ (instancetype)sceneWithSize:(CGSize)size;

@property (SK_NONATOMIC_IOSONLY) CGSize size;

/**
 Used to determine how to scale the scene to match the SKView it is being displayed in.
 */
@property (SK_NONATOMIC_IOSONLY) SKSceneScaleMode scaleMode;

/* Background color, defaults to gray */
@property (SK_NONATOMIC_IOSONLY, retain) SKColor *backgroundColor;

/**
 Used to choose the origin of the scene's coordinate system
 */
@property (SK_NONATOMIC_IOSONLY) CGPoint anchorPoint;

/**
 Physics simulation functionality
 */
@property (SK_NONATOMIC_IOSONLY, readonly) SKPhysicsWorld *physicsWorld;

- (CGPoint)convertPointFromView:(CGPoint)point;
- (CGPoint)convertPointToView:(CGPoint)point;

/**
 The SKView this scene is currently presented in, or nil if it is not being presented.
 */
@property (SK_NONATOMIC_IOSONLY, weak, readonly) SKView *view;

/**
 Override this to perform per-frame game logic. Called exactly once per frame before any actions are evaluated and any physics are simulated.
 
 @param currentTime the current time in the app. This must be monotonically increasing.
 */
- (void)update:(NSTimeInterval)currentTime;

/**
 Override this to perform game logic. Called exactly once per frame after any actions have been evaluated but before any physics are simulated. Any additional actions applied is not evaluated until the next update.
 */
- (void)didEvaluateActions;

/**
 Override this to perform game logic. Called exactly once per frame after any actions have been evaluated and any physics have been simulated. Any additional actions applied is not evaluated until the next update. Any changes to physics bodies is not simulated until the next update.
 */
- (void)didSimulatePhysics;

- (void)didMoveToView:(SKView *)view;
- (void)willMoveFromView:(SKView *)view;
- (void)didChangeSize:(CGSize)oldSize;

@end
