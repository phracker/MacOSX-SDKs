//
//  SKScene.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <SpriteKit/SKCameraNode.h>
#import <SpriteKit/SKEffectNode.h>
#import <SpriteKit/SpriteKitBase.h>

#if SKVIEW_AVAILABLE
@class SKView;
#endif

@class SKPhysicsWorld, AVAudioEngine;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SKSceneScaleMode) {
    SKSceneScaleModeFill,           /* Scale the SKScene to fill the entire SKView. */
    SKSceneScaleModeAspectFill,     /* Scale the SKScene to fill the SKView while preserving the scene's aspect ratio. Some cropping may occur if the view has a different aspect ratio. */
    SKSceneScaleModeAspectFit,      /* Scale the SKScene to fit within the SKView while preserving the scene's aspect ratio. Some letterboxing may occur if the view has a different aspect ratio. */
    SKSceneScaleModeResizeFill      /* Modify the SKScene's actual size to exactly match the SKView. */
} NS_ENUM_AVAILABLE(10_9, 7_0);

API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10)) @protocol SKSceneDelegate <NSObject>
@optional
- (void)update:(NSTimeInterval)currentTime forScene:(SKScene *)scene;
- (void)didEvaluateActionsForScene:(SKScene *)scene;
- (void)didSimulatePhysicsForScene:(SKScene *)scene;

- (void)didApplyConstraintsForScene:(SKScene *)scene;
- (void)didFinishUpdateForScene:(SKScene *)scene;
@end

/**
 A scene is the root node of your content. It is used to display SpriteKit content on an SKView.
 
 @see SKView
 */
SK_EXPORT @interface SKScene : SKEffectNode

/**
 A scene is infinitely large, but it has a viewport that is the frame through which you present the content of the scene.
 The passed in size defines the size of this viewport that you use to present the scene.
 
 @param size a size in points that signifies the viewport into the scene that defines your framing of the scene.
 */
- (instancetype)initWithSize:(CGSize)size;

+ (instancetype)sceneWithSize:(CGSize)size;

/* This is called once after the scene has been initialized or decoded,
 this is the recommended place to perform one-time setup */
- (void)sceneDidLoad API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

@property (nonatomic) CGSize size;

/**
 Used to determine how to scale the scene to match the SKView it is being displayed in.
 */
@property (nonatomic) SKSceneScaleMode scaleMode;

/**
 The camera that is used to obtain the view scale and translation based on where the camera is in relation to the scene.
 */
@property (nonatomic, weak, nullable) SKCameraNode *camera API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/**
 The node that is currently the listener for positional audio coming from SKAudioNodes
 @see SKAudioNode
 */
@property (nonatomic, weak, nullable) SKNode *listener API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/**
 The audio engine that the listener and the scene's audio nodes use to process their sound through.
 */
#if __has_include(<AVFoundation/AVAudioEngine.h>)
@property (nonatomic, retain, readonly) AVAudioEngine *audioEngine API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
#endif

/**
 Background color, defaults to gray
 */
@property (nonatomic, retain) SKColor *backgroundColor;

@property (nonatomic, weak, nullable) id<SKSceneDelegate> delegate API_AVAILABLE(ios(8.0), tvos(9.0), watchos(2.0), macos(10.10));

/**
 Used to choose the origin of the scene's coordinate system
 */
@property (nonatomic) CGPoint anchorPoint;

/**
 Physics simulation functionality
 */
@property (nonatomic, readonly) SKPhysicsWorld *physicsWorld;


#if SKVIEW_AVAILABLE
/**
 The SKView this scene is currently presented in, or nil if it is not being presented.
 */
@property (nonatomic, weak, readonly, nullable) SKView *view;

- (CGPoint)convertPointFromView:(CGPoint)point;
- (CGPoint)convertPointToView:(CGPoint)point;
#endif

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

/**
 Override this to perform game logic. Called exactly once per frame after any enabled constraints have been applied. Any additional actions applied is not evaluated until the next update. Any changes to physics bodies is not simulated until the next update. Any changes to constarints will not be applied until the next update.
 */
- (void)didApplyConstraints API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/**
 Override this to perform game logic. Called after all update logic has been completed. Any additional actions applied are not evaluated until the next update. Any changes to physics bodies are not simulated until the next update. Any changes to constarints will not be applied until the next update.
 
 No futher update logic will be applied to the scene after this call. Any values set on nodes here will be used when the scene is rendered for the current frame.
 */
- (void)didFinishUpdate API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

#if SKVIEW_AVAILABLE
- (void)didMoveToView:(SKView *)view;
- (void)willMoveFromView:(SKView *)view;
#endif

- (void)didChangeSize:(CGSize)oldSize;

@end

NS_ASSUME_NONNULL_END
