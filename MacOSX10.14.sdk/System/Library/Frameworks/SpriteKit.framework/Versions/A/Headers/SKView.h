//
//  SKView.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//


#import <SpriteKit/SpriteKitBase.h>


/* SKView is not available on WatchOS, please see WKInterfaceSpriteKit */
#if SKVIEW_AVAILABLE

@class SKScene, SKTransition, SKTexture, SKNode;
@protocol SKViewDelegate;

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
SK_EXPORT @interface SKView : NSView <NSSecureCoding>

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


/* Defines the desired rate for this SKView to it's content. 
 Actual rate maybe be limited by hardware or other software. */
@property (nonatomic) NSInteger preferredFramesPerSecond NS_AVAILABLE(10_12, 10_0);


/**
 Optional view delegate, see SKViewDelegate.
 */
@property (nonatomic, weak, nullable) NSObject<SKViewDelegate> *delegate NS_AVAILABLE(10_12, 10_0);


/* Deprecated, please use preferredFramesPerSecond.
 Number of frames to skip between renders, defaults to 1 (render every frame)
 Actual requested rate will be preferredFramesPerSecond / frameInterval.  */
@property (nonatomic) NSInteger frameInterval NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);

/* Deprecated, please use preferredFramesPerSecond. */
/* FIXME: remove from public headers once all clinets adopt preferredFramesPerSecond. */
@property(nonatomic) float preferredFrameRate NS_DEPRECATED(10_12, 10_12, 10_0, 10_0);


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



SK_EXPORT NS_AVAILABLE(10_12, 10_0) @protocol SKViewDelegate <NSObject>
@optional
/**
 Allows the client to dynamically control the render rate.
 
 return YES to initiate an update and render for the target time.
 return NO to skip update and render for this target time.
 */
- (BOOL)view:(SKView *)view shouldRenderAtTime:(NSTimeInterval)time;
@end


NS_ASSUME_NONNULL_END

#endif
