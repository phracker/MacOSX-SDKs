//
//  SCNSceneRenderer.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@class SCNScene;
@class SCNNode;
@class SKScene;
@class SKTransition;
@protocol SCNSceneRendererDelegate;
@protocol MTLRenderCommandEncoder;
@protocol MTLCommandBuffer;
@class MTLRenderPassDescriptor;
@class AVAudioEngine;
@class AVAudioEnvironmentNode;

/*! @group Hit test options */

/*! If set to YES, returns the first object found. This object is not necessarily the nearest. Defaults to NO. */
SCN_EXTERN NSString * const SCNHitTestFirstFoundOnlyKey;
/*! Determines whether the results should be sorted. If set to YES sorts nearest objects first. Defaults to YES. */
SCN_EXTERN NSString * const SCNHitTestSortResultsKey;
/*! If set to YES ignores the objects clipped by the zNear/zFar range of the current point of view. Defaults to YES. */
SCN_EXTERN NSString * const SCNHitTestClipToZRangeKey;
/*! If set to YES ignores the faces not facing to the camera. Defaults to YES. */
SCN_EXTERN NSString * const SCNHitTestBackFaceCullingKey;
/*!  If set to YES only tests the bounding boxes of the 3D objects. Defaults to NO. */
SCN_EXTERN NSString * const SCNHitTestBoundingBoxOnlyKey;
/*! Determines whether the child nodes are ignored. Defaults to NO. */
SCN_EXTERN NSString * const SCNHitTestIgnoreChildNodesKey;
/*! Specifies the root node to use for the hit test. Defaults to the root node of the scene. */
SCN_EXTERN NSString * const SCNHitTestRootNodeKey;
/*! Determines whether hidden nodes should be ignored. Defaults to YES. */
SCN_EXTERN NSString * const SCNHitTestIgnoreHiddenNodesKey NS_AVAILABLE(10_9, 8_0);

/*!
 @enum SCNRenderingAPI
 @abstract rendering API used by SCNView and SCNRenderer.
 @discussion Default preferred API is SCNRenderingAPIMetal on iOS and it depends on the configuration on OS X.
 If Metal is requested but not available then it fallbacks to SCNRenderingAPIOpenGLES2 on iOS and to SCNRenderingAPIOpenGLLegacy on OS X.
 */
typedef NS_ENUM(NSUInteger, SCNRenderingAPI) {
    SCNRenderingAPIMetal,
    SCNRenderingAPIOpenGLLegacy,
    SCNRenderingAPIOpenGLCore32,
    SCNRenderingAPIOpenGLCore41
} NS_ENUM_AVAILABLE(10_11, 9_0);

/*!
 @enum SCNDebugOptions
 @abstract Debug options.
 */
typedef NS_OPTIONS(NSUInteger, SCNDebugOptions) {
    SCNDebugOptionNone = 0,
    SCNDebugOptionShowPhysicsShapes   = 1 << 0,
    SCNDebugOptionShowBoundingBoxes   = 1 << 1,
    SCNDebugOptionShowLightInfluences = 1 << 2,
    SCNDebugOptionShowLightExtents    = 1 << 3,
    SCNDebugOptionShowPhysicsFields   = 1 << 4,
    SCNDebugOptionShowWireframe       = 1 << 5
} NS_ENUM_AVAILABLE(10_11, 9_0);


/*! @class SCNHitTestResult
    @abstract Results returned by the hit test methods.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNHitTestResult : NSObject

/*! The node hit. */
@property(nonatomic, readonly) SCNNode *node;

/*! Index of the geometry hit. */
@property(nonatomic, readonly) NSInteger geometryIndex;

/*! Index of the face hit. */
@property(nonatomic, readonly) NSInteger faceIndex;

/*! Intersection point in the node local coordinate system. */
@property(nonatomic, readonly) SCNVector3 localCoordinates;

/*! Intersection point in the world coordinate system. */
@property(nonatomic, readonly) SCNVector3 worldCoordinates;

/*! Intersection normal in the node local coordinate system. */
@property(nonatomic, readonly) SCNVector3 localNormal;

/*! Intersection normal in the world coordinate system. */
@property(nonatomic, readonly) SCNVector3 worldNormal;

/*! World transform of the node intersected. */
@property(nonatomic, readonly) SCNMatrix4 modelTransform;

/*! 
 @method textureCoordinatesWithMappingChannel:
 @abstract Returns the texture coordinates at the point of intersection, for a given mapping channel.
 @param channel The texture coordinates source index of the geometry to use. The channel must exists on the geometry otherwise {0,0} will be returned.
 */
- (CGPoint)textureCoordinatesWithMappingChannel:(NSInteger)channel;

@end



/*! @protocol SCNSceneRenderer
    @abstract Protocol adopted by the various renderers (SCNView, SCNLayer, SCNRenderer)
 */
@protocol SCNSceneRenderer <NSObject>
@required

/*!
 @property scene
 @abstract Specifies the scene of the receiver.
 */
@property(nonatomic, retain, nullable) SCNScene *scene;

/*!
 @method presentScene:withTransition:incomingPointOfView:
 @abstract Present a SCNScene in the receiver, replacing the current scene.
 @param scene The new scene to present.
 @param transition the transition to use when presenting the scene.
 @param pointOfView the point of view to use to render the new scene.
 @param completionHandler the block invoked on completion.
 */
- (void)presentScene:(SCNScene *)scene withTransition:(SKTransition *)transition incomingPointOfView:(nullable SCNNode *)pointOfView completionHandler:(nullable void (^)())completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 @property sceneTime
 @abstract Specifies the current "scene time" to display the scene.
 @discussion The scene time only affect scene time based animations (see SCNAnimation.h "usesSceneTimeBase" and SCNSceneSource.h "SCNSceneSourceAnimationImportPolicyKey" for how to create scene time based animations). Scene time based animations and this property are typically used by tools and viewer to ease seeking in time while previewing a scene.
 */
@property(nonatomic) NSTimeInterval sceneTime NS_AVAILABLE(10_10, 8_0);

/*! 
 @property delegate
 @abstract Specifies the renderer delegate.
 */
@property(nonatomic, assign, nullable) id <SCNSceneRendererDelegate> delegate;

/*!
 @method hitTest:options:
 @abstract Returns an array of SCNHitTestResult for each node that contains a specified point.
 @param point A point in the coordinate system of the receiver.
 @param options Optional parameters (see the "Hit test options" group for the available options).
 */
- (NSArray<SCNHitTestResult *> *)hitTest:(CGPoint)point options:(nullable NSDictionary<NSString *, id> *)options;

/*!
 @method isNodeInsideFrustum:withPointOfView:
 @abstract Test whether node is visible from the specified point of view.
 @param node The node to test the visibility of.
 @param pointOfView The point of view used to test the visibility.
 @discussion Return YES if the node is inside or intersects the clipping planes of the point of view. This method doesn't test if 'node' is occluded by another node.
 */
- (BOOL)isNodeInsideFrustum:(SCNNode *)node withPointOfView:(SCNNode *)pointOfView NS_AVAILABLE(10_9, 8_0);

/*!
 @method nodesInsideFrustumWithPointOfView:
 @abstract Returns an array containing the nodes visible from the specified point of view.
 @param pointOfView The point of view used to test the visibility.
 @discussion Returns an array of all the nodes that are inside or intersects the clipping planes of the point of view.
 */
- (NSArray<SCNNode *> *)nodesInsideFrustumWithPointOfView:(SCNNode *)pointOfView NS_AVAILABLE(10_11, 9_0);

/*!
 @method projectPoint
 @abstract Projects a point in the world coordinate system using the receiver's current point of view and viewport.
 @param point The world position to be projected.
 @discussion A point projected from the near (resp. far) clip plane will have a z component of 0 (resp. 1).
 */
- (SCNVector3)projectPoint:(SCNVector3)point NS_AVAILABLE(10_9, 8_0);

/*!
 @method unprojectPoint
 @abstract Unprojects a screenspace 2D point with depth info using the receiver's current point of view and viewport.
 @param point The screenspace position to be unprojected.
 @discussion A point whose z component is 0 (resp. 1) is unprojected on the near (resp. far) clip plane.
 */
- (SCNVector3)unprojectPoint:(SCNVector3)point NS_AVAILABLE(10_9, 8_0);

/*! 
 @property playing
 @abstract Returns YES if the scene is playing, NO otherwise.
 */
@property(getter=isPlaying) BOOL playing;

/*! 
 @property loops
 @abstract Indicates whether the receiver restarts playback when it reaches the end of its content. Default: YES.
 @discussion YES when the receiver restarts playback when it finishes, NO otherwise.
 */
@property(nonatomic) BOOL loops;

/*! 
 @property pointOfView
 @abstract Specifies the point of view used to render the scene. 
 @discussion A point of view must have either a camera or a spot light attached.
 */
@property(nonatomic, retain, nullable) SCNNode *pointOfView;

/*! 
 @property autoenablesDefaultLighting
 @abstract Specifies whether the receiver should automatically light up scenes that have no light source. The default is NO.
 @discussion When enabled, a diffuse light is automatically added and placed while rendering scenes that have no light or only ambient lights.
 */
@property(nonatomic) BOOL autoenablesDefaultLighting;

/*! 
 @property jitteringEnabled
 @abstract Specifies whether the receiver should jitter the rendered scene to reduce aliasing artifacts. 
 @discussion When enabled, the jittering is performed asynchronously and automatically by SCNView and SCNLayer. It is done synchronously by SCNRenderer.
 */
@property(nonatomic, getter=isJitteringEnabled) BOOL jitteringEnabled;

/*!
 @method prepareObject:shouldAbortBlock:
 @abstract Prepare the specified object for drawing.
 @param object The object to prepare. It can be an instance of SCNScene, SCNNode, SCNGeometry, or SCNMaterial
 @param block This block will be called repeatedly while the object is prepared. Return YES if you want the operation to abort.
 @discussion Returns YES if the object was prepared successfully, NO if it was canceled. This method may be triggered from a secondary thread. This method is observable using NSProgress.
 */
- (BOOL)prepareObject:(id)object shouldAbortBlock:(nullable BOOL (^)())block NS_AVAILABLE(10_9, 8_0);

/*!
 @method prepareObjects:withCompletionHandler:
 @abstract Prepare the specified objects for drawing on the background.
 @param objects The objects to prepare. It can be one or more instances of SCNScene, SCNNode, SCNGeometry, or SCNMaterial
 @param completionHandler This block will be called when all objects has been prepared, or on failure.
 @discussion This method is observable using NSProgress.
 */
- (void)prepareObjects:(NSArray *)objects withCompletionHandler:(nullable void (^)(BOOL success))completionHandler NS_AVAILABLE(10_10, 8_0);

/*!
 @property showsStatistics
 @abstract Determines whether the receiver should display statistics info like FPS. Defaults to NO.
 @discussion  When set to YES, statistics are displayed in a overlay on top of the rendered scene.
 */
@property(nonatomic) BOOL showsStatistics NS_AVAILABLE(10_9, 8_0);

/*!
 @property debugOptions
 @abstract Specifies the debug options of the receiver. Defaults to SCNDebugOptionNone.
 */
@property(nonatomic) SCNDebugOptions debugOptions NS_AVAILABLE(10_11, 9_0);

/*!
 @property overlaySKScene
 @abstract Specifies the overlay of the receiver as a SpriteKit scene instance. Defaults to nil.
 */
@property(nonatomic, retain, nullable) SKScene *overlaySKScene NS_AVAILABLE(10_10, 8_0);

/*!
 @property renderingAPI
 @abstract Specifies the rendering API associated to the receiver.
 @discussion This is the rendering API effectively used by the receiver. You can specify a preferred rendering API when initializing a view programmatically (see SCNPreferredRenderingAPI in SCNSceneRenderer.h) or using Interface Builder's SCNView inspector.
 */
@property(nonatomic, readonly) SCNRenderingAPI renderingAPI NS_AVAILABLE(10_11, 9_0);

/*!
 @property context
 @abstract A Core OpenGL render context that is used as the render target (a CGLContextObj on OS X, an EAGLContext on iOS).
 */
@property(nonatomic, readonly, nullable) void *context;

#if SCN_ENABLE_METAL

/*!
 @property currentRenderCommandEncoder
 @abstract The current render command encoder if any. This property is only valid within the SCNSceneRendererDelegate methods and when renderering with Metal. Otherwise it is set to nil.
 */
@property(nonatomic, readonly, nullable) id <MTLRenderCommandEncoder> currentRenderCommandEncoder NS_AVAILABLE(10_11, 9_0);

/*!
 @property device
 @abstract The metal device of the renderer. This property is only valid on a renderer created with a Metal device. Otherwise it is set to nil.
 */
@property(nonatomic, readonly, nullable) id <MTLDevice> device NS_AVAILABLE(10_11, 9_0);

/*!
 @property colorPixelFormat
 @abstract The pixel format of the color attachment 0 of the renderer. This property is only valid on a renderer created with a Metal device.
 */
@property(nonatomic, readonly) MTLPixelFormat colorPixelFormat NS_AVAILABLE(10_11, 9_0);

/*!
 @property depthPixelFormat
 @abstract The pixel format of the depth attachment of the renderer. This property is only valid on a renderer created with a Metal device.
 */
@property(nonatomic, readonly) MTLPixelFormat depthPixelFormat NS_AVAILABLE(10_11, 9_0);

/*!
 @property stencilPixelFormat
 @abstract The pixel format of the stencil attachment of the renderer. This property is only valid on a renderer created with a Metal device.
 */
@property(nonatomic, readonly) MTLPixelFormat stencilPixelFormat NS_AVAILABLE(10_11, 9_0);

/*!
 @property commandQueue
 @abstract The command queue of the renderer. This property is only valid on a renderer created with a Metal device. Otherwise it is set to nil.
 */
@property(nonatomic, readonly, nullable) id <MTLCommandQueue> commandQueue NS_AVAILABLE(10_11, 9_0);

#endif

/*!
 @property audioEngine
 @abstract Contains the instance of audio engine used by the scene.
 @discussion The audio engine can be used to add custom nodes to the audio graph.
 */
@property(nonatomic, readonly) AVAudioEngine *audioEngine NS_AVAILABLE(10_11, 9_0);

/*!
 @property audioEnvironmentNode
 @abstract Contains the instance of audio environment node used by the scene to spacialize sounds.
 */
@property(nonatomic, readonly) AVAudioEnvironmentNode *audioEnvironmentNode NS_AVAILABLE(10_11, 9_0);

/*!
 @property audioListener
 @abstract Use this property to set the audio node to use as the listener position and orientation when rendering positional audio for this scene. The default is nil which means that the current point of view will be used dynamically.
 */
@property(nonatomic, retain, nullable) SCNNode *audioListener NS_AVAILABLE(10_11, 9_0);


#pragma mark Deprecated

/*!
 @property currentTime
 @abstract Specifies the current time to display the scene.
 @discussion Deprecated, use "sceneTime" instead.
 */
@property(nonatomic) NSTimeInterval currentTime NS_DEPRECATED(10_8, 10_10, NA, NA);

@end



/*!
 @protocol SCNSceneRendererDelegate
 @abstract Implement this protocol to perform operations at various times during the rendering
 */
@protocol SCNSceneRendererDelegate <NSObject>
@optional

/*!
 @method renderer:updateAtTime:
 @abstract Implement this to perform per-frame game logic. Called exactly once per frame before any animation and actions are evaluated and any physics are simulated.
 @param aRenderer The renderer that will render the scene.
 @param time The time at which to update the scene.
 @discussion All modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer updateAtTime:(NSTimeInterval)time NS_AVAILABLE(10_10, 8_0);

/*!
 @method renderer:didApplyAnimationsAtTime:
 @abstract Invoked on the delegate once the scene renderer did apply the animations.
 @param aRenderer The renderer that did render the scene.
 @param time The time at which the animations were applied.
 @discussion All modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didApplyAnimationsAtTime:(NSTimeInterval)time NS_AVAILABLE(10_10, 8_0);

/*!
 @method renderer:didSimulatePhysicsAtTime:
 @abstract Invoked on the delegate once the scene renderer did simulate the physics.
 @param aRenderer The renderer that did render the scene.
 @param time The time at which the physics were simulated.
 @discussion All modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didSimulatePhysicsAtTime:(NSTimeInterval)time NS_AVAILABLE(10_10, 8_0);

/*!
 @method renderer:willRenderScene:atTime:
 @abstract Invoked on the delegate before the scene renderer renders the scene. At this point the openGL context and the destination framebuffer are bound.
 @param aRenderer The renderer that will render the scene.
 @param scene The scene to be rendered.
 @param time The time at which the scene is to be rendered.
 @discussion Starting in 10.10 all modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer willRenderScene:(SCNScene *)scene atTime:(NSTimeInterval)time;

/*!
 @method renderer:didRenderScene:atTime:
 @abstract Invoked on the delegate once the scene renderer did render the scene.
 @param aRenderer The renderer that did render the scene.
 @param scene The rendered scene.
 @param time The time at which the scene was rendered.
 @discussion Starting in 10.10 all modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didRenderScene:(SCNScene *)scene atTime:(NSTimeInterval)time;

@end
    
NS_ASSUME_NONNULL_END
