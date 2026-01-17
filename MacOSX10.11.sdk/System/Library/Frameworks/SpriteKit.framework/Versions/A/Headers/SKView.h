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

#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN
SK_EXPORT @interface SKView : UIView

#else

#import <Cocoa/Cocoa.h>
NS_ASSUME_NONNULL_BEGIN
SK_EXPORT @interface SKView : NSView

#endif

/**
 Pause the entire view
 */
@property (nonatomic, getter = isPaused) BOOL paused;

/**
 Toggles display of performance stats in the view. All default to false.
 */
@property (nonatomic) BOOL showsFPS;
@property (nonatomic) BOOL showsDrawCount;
@property (nonatomic) BOOL showsNodeCount;
@property (nonatomic) BOOL showsQuadCount NS_AVAILABLE(10_10, 8_0);
@property (nonatomic) BOOL showsPhysics NS_AVAILABLE(10_10, 8_0);
@property (nonatomic) BOOL showsFields NS_AVAILABLE(10_10, 8_0);


/**
 Toggles whether the view updates is rendered asynchronously or aligned with Core Animation updates. Defaults to YES.
 */
@property (nonatomic, getter=isAsynchronous) BOOL asynchronous;

/**
 Toggles whether the view allows transparent rendering. This allows content under the view to show through if
 a non-opaque backgroundColor is set on the scene. Defaults to NO.
 */
@property (nonatomic) BOOL allowsTransparency NS_AVAILABLE(10_10, 8_0);

/**
 Ignores sibling and traversal order to sort the rendered contents of a scene into the most efficient batching possible.
 This will require zPosition to be used in the scenes to properly guarantee elements are in front or behind each other.
 
 This defaults to NO, meaning that sibling order overrides efficiency heuristics in the rendering of the scenes in the view.
 
 Setting this to YES for a complex scene may substantially increase performance, but care must be taken as only zPosition
 determines render order before the efficiency heuristics are used.
 */
@property (nonatomic) BOOL ignoresSiblingOrder;

@property (nonatomic) BOOL shouldCullNonVisibleNodes NS_AVAILABLE(10_10, 8_0);

/* Number of hardware vsyncs between callbacks, same behaviour as CADisplayLink. Defaults to 1 (render every vsync) */
@property (nonatomic) NSInteger frameInterval;

/**
 Present an SKScene in the view, replacing the current scene.
 
 @param scene the scene to present.
 */
- (void)presentScene:(nullable SKScene *)scene;

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
@property (nonatomic, readonly, nullable) SKScene *scene;

/**
 Create an SKTexture containing a snapshot of how it would have been rendered in this view.
 The texture is tightly cropped to the size of the node.
 @param node the node subtree to render to the texture.
 */
- (nullable SKTexture *)textureFromNode:(SKNode *)node;

/**
 Create an SKTexture containing a snapshot of how it would have been rendered in this view.
 The texture is cropped to the specified rectangle
 @param node the node subtree to render to the texture.
 @param rect the crop
 */
- (nullable SKTexture *)textureFromNode:(SKNode *)node crop:(CGRect)crop;

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

NS_ASSUME_NONNULL_END
