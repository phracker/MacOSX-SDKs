//
//  SKView.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <SpriteKit/SpriteKitBase.h>

@class SKScene, SKTransition, SKTexture, SKNode;

/**
 The view to present your SKScene nodes in.
 
 Present your scenes using the presentScene: and presentScene:transition:
 
 NOTE: Subclassing of SKView is not allowed.
 */

#if TARGET_OS_IPHONE
SK_EXPORT @interface SKView : UIView
#else
SK_EXPORT @interface SKView : NSView
#endif

/**
 Pause the entire view
 */
@property (SK_NONATOMIC_IOSONLY, getter = isPaused) BOOL paused;

/**
 Toggles display of performance stats in the view. All default to false.
 */
@property (SK_NONATOMIC_IOSONLY) BOOL showsFPS;
@property (SK_NONATOMIC_IOSONLY) BOOL showsDrawCount;
@property (SK_NONATOMIC_IOSONLY) BOOL showsNodeCount;


/**
 Toggles whether the view updates is rendered asynchronously or aligned with Core Animation updates. Defaults to true.
 */
@property (SK_NONATOMIC_IOSONLY, getter=isAsynchronous) BOOL asynchronous;

/**
 Ignores sibling and traversal order to sort the rendered contents of a scene into the most efficient batching possible.
 This will require zPosition to be used in the scenes to properly guarantee elements are in front or behind each other.
 
 This defaults to NO, meaning that sibling order overrides efficiency heuristics in the rendering of the scenes in the view.
 
 Setting this to YES for a complex scene may substantially increase performance, but care must be taken as only zPosition
 determines render order before the efficiency heuristics are used.
 */
@property (SK_NONATOMIC_IOSONLY) BOOL ignoresSiblingOrder;

/* Number of hardware vsycs between callbacks, same behaviour as CADisplayLink. Defualts to 1 (render every vsync) */
@property (SK_NONATOMIC_IOSONLY) NSInteger frameInterval;

/**
 Present an SKScene in the view, replacing the current scene.
 
 @param scene the scene to present.
 */
- (void)presentScene:(SKScene *)scene;

/**
 Present an SKScene in the view, replacing the current scene.
 
 If there is currently a scene being presented in the view, the transition is used to swap between them.
 
 @param scene the scene to present.
 @param transition the transition to use when presenting the scene.
 */
- (void)presentScene:(SKScene *)scene transition:(SKTransition *)transition;

/**
 The currently presented scene, otherwise nil. If in a transition, the 'incoming' scene is returned.
 */
@property (SK_NONATOMIC_IOSONLY, readonly) SKScene *scene;

/**
 Create an SKTexture containing a snapshot of how it would have been rendered in this view.
 @param node the node subtree to render to the texture.
 */
- (SKTexture *)textureFromNode:(SKNode *)node;

/**
 Converts a point from view space to scene space.
 
 @param point the point to convert.
 @param scene the scene to convert the point into.
 */
- (CGPoint)convertPoint:(CGPoint)point toScene:(SKScene *)scene;

/**
 Converts a point from scene space to view space.
 
 @param point the point to convert.
 @param scene the scene to convert the point into.
 */
- (CGPoint)convertPoint:(CGPoint)point fromScene:(SKScene *)scene;


@end
