//
//  SCNSceneRenderer.h
//  SceneKit
//
//  Copyright © 2012-2020 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNHitTest.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;
@class SCNScene;
@protocol SCNSceneRendererDelegate;
@class SKScene;
@class SKTransition;
@class MTLRenderPassDescriptor;
@protocol MTLRenderCommandEncoder;
@protocol MTLCommandBuffer;
@class AVAudioEngine;
@class AVAudioEnvironmentNode;

/*!
 @enum SCNAntialiasingMode
 @abstract antialiasing modes for scene renderers
 */
typedef NS_ENUM(NSUInteger, SCNAntialiasingMode) {
    SCNAntialiasingModeNone,
    SCNAntialiasingModeMultisampling2X,
    SCNAntialiasingModeMultisampling4X,
    SCNAntialiasingModeMultisampling8X,
    SCNAntialiasingModeMultisampling16X
} API_AVAILABLE(macos(10.10));

/*!
 @enum SCNRenderingAPI
 @abstract rendering API used by SCNView and SCNRenderer.
 @discussion Default preferred API is SCNRenderingAPIMetal on iOS and it depends on the configuration on macOS.
 If Metal is requested but not available then it fallbacks to SCNRenderingAPIOpenGLES2 on iOS and to SCNRenderingAPIOpenGLLegacy on macOS.
 */
typedef NS_ENUM(NSUInteger, SCNRenderingAPI) {
    SCNRenderingAPIMetal,
    SCNRenderingAPIOpenGLLegacy,
    SCNRenderingAPIOpenGLCore32,
    SCNRenderingAPIOpenGLCore41
} API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @enum SCNDebugOptions
 @abstract Debug options.
 */
typedef NS_OPTIONS(NSUInteger, SCNDebugOptions) {
    SCNDebugOptionNone                                                                               = 0,
    SCNDebugOptionShowPhysicsShapes                                                                  = 1 << 0, //show physics shape
    SCNDebugOptionShowBoundingBoxes                                                                  = 1 << 1, //show object bounding boxes
    SCNDebugOptionShowLightInfluences                                                                = 1 << 2, //show objects's light influences
    SCNDebugOptionShowLightExtents                                                                   = 1 << 3, //show light extents
    SCNDebugOptionShowPhysicsFields                                                                  = 1 << 4, //show SCNPhysicsFields forces and extents
    SCNDebugOptionShowWireframe                                                                      = 1 << 5, //show wireframe on top of objects
    SCNDebugOptionRenderAsWireframe API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 1 << 6, //render objects as wireframe
    SCNDebugOptionShowSkeletons     API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 1 << 7, //show skinning bones
    SCNDebugOptionShowCreases       API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 1 << 8, //show subdivision creases
    SCNDebugOptionShowConstraints   API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 1 << 9, //show slider constraint
    SCNDebugOptionShowCameras       API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 1 << 10, //show cameras
} API_AVAILABLE(macos(10.11), ios(9.0));

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
- (void)presentScene:(SCNScene *)scene withTransition:(SKTransition *)transition incomingPointOfView:(nullable SCNNode *)pointOfView completionHandler:(nullable void (^)(void))completionHandler API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property sceneTime
 @abstract Specifies the current "scene time" to display the scene.
 @discussion The scene time only affect scene time based animations (see SCNAnimation.h "usesSceneTimeBase" and SCNSceneSource.h "SCNSceneSourceAnimationImportPolicyKey" for how to create scene time based animations). Scene time based animations and this property are typically used by tools and viewer to ease seeking in time while previewing a scene.
 */
@property(nonatomic) NSTimeInterval sceneTime API_AVAILABLE(macos(10.10));

/*! 
 @property delegate
 @abstract Specifies the renderer delegate.
 */
@property(nonatomic, weak, nullable) id <SCNSceneRendererDelegate> delegate;

/*!
 @method hitTest:options:
 @abstract Returns an array of SCNHitTestResult for each node that contains a specified point.
 @param point A point in the coordinate system of the receiver.
 @param options Optional parameters (see the "Hit test options" group for the available options).
 */
- (NSArray<SCNHitTestResult *> *)hitTest:(CGPoint)point options:(nullable NSDictionary<SCNHitTestOption, id> *)options;

/*!
 @method isNodeInsideFrustum:withPointOfView:
 @abstract Test whether node is visible from the specified point of view.
 @param node The node to test the visibility of.
 @param pointOfView The point of view used to test the visibility.
 @discussion Return YES if the node is inside or intersects the clipping planes of the point of view. This method doesn't test if 'node' is occluded by another node.
 */
- (BOOL)isNodeInsideFrustum:(SCNNode *)node withPointOfView:(SCNNode *)pointOfView API_AVAILABLE(macos(10.9));

/*!
 @method nodesInsideFrustumWithPointOfView:
 @abstract Returns an array containing the nodes visible from the specified point of view.
 @param pointOfView The point of view used to test the visibility.
 @discussion Returns an array of all the nodes that are inside or intersects the clipping planes of the point of view. Starting in macOS10.13/iOS11 this method work with the presentation tree.
 */
- (NSArray<SCNNode *> *)nodesInsideFrustumWithPointOfView:(SCNNode *)pointOfView API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method projectPoint
 @abstract Projects a point in the world coordinate system using the receiver's current point of view and viewport.
 @param point The world position to be projected.
 @discussion A point projected from the near (resp. far) clip plane will have a z component of 0 (resp. 1). Starting in macOS 11.0, iOS 14, tvOS 14 and watchOS 7 the range of z component will be reversed (from 1 to 0) if the receiver uses 'reverseZ'.
 */
- (SCNVector3)projectPoint:(SCNVector3)point API_AVAILABLE(macos(10.9));

/*!
 @method unprojectPoint
 @abstract Unprojects a screenspace 2D point with depth info using the receiver's current point of view and viewport.
 @param point The screenspace position to be unprojected.
 @discussion A point whose z component is 0 (resp. 1) is unprojected on the near (resp. far) clip plane. Starting in macOS 11.0, iOS 14, tvOS 14 and watchOS 7 the range of the z component will be reversed (from 1 to 0) if the receiver uses 'reverseZ'.
 */
- (SCNVector3)unprojectPoint:(SCNVector3)point API_AVAILABLE(macos(10.9));

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
 @property temporalAntialiasingEnabled
 @abstract Specifies whether the receiver should reduce aliasing artifacts in real time based on temporal coherency. Defaults to NO.
 */
@property(nonatomic, getter=isTemporalAntialiasingEnabled) BOOL temporalAntialiasingEnabled API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @method prepareObject:shouldAbortBlock:
 @abstract Prepare the specified object for drawing.
 @param object The object to prepare. It can be an instance of SCNScene, SCNNode, SCNGeometry, or SCNMaterial
 @param block This block will be called repeatedly while the object is prepared. Return YES if you want the operation to abort.
 @discussion Returns YES if the object was prepared successfully, NO if it was canceled. This method may be triggered from a secondary thread. This method is observable using NSProgress.
 */
- (BOOL)prepareObject:(id)object shouldAbortBlock:(nullable NS_NOESCAPE BOOL (^)(void))block API_AVAILABLE(macos(10.9));

/*!
 @method prepareObjects:withCompletionHandler:
 @abstract Prepare the specified objects for drawing on the background.
 @param objects The objects to prepare. It can be one or more instances of SCNScene, SCNNode, SCNGeometry, or SCNMaterial
 @param completionHandler This block will be called when all objects has been prepared, or on failure.
 @discussion This method is observable using NSProgress.
 */
- (void)prepareObjects:(NSArray *)objects withCompletionHandler:(nullable void (^)(BOOL success))completionHandler API_AVAILABLE(macos(10.10));

/*!
 @property showsStatistics
 @abstract Determines whether the receiver should display statistics info like FPS. Defaults to NO.
 @discussion  When set to YES, statistics are displayed in a overlay on top of the rendered scene.
 */
@property(nonatomic) BOOL showsStatistics API_AVAILABLE(macos(10.9));

/*!
 @property debugOptions
 @abstract Specifies the debug options of the receiver. Defaults to SCNDebugOptionNone.
 */
@property(nonatomic) SCNDebugOptions debugOptions API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property overlaySKScene
 @abstract Specifies the overlay of the receiver as a SpriteKit scene instance. Defaults to nil.
 */
@property(nonatomic, retain, nullable) SKScene *overlaySKScene API_AVAILABLE(macos(10.10));

/*!
 @property renderingAPI
 @abstract Specifies the rendering API associated to the receiver.
 @discussion This is the rendering API effectively used by the receiver. You can specify a preferred rendering API when initializing a view programmatically (see SCNPreferredRenderingAPI in SCNSceneRenderer.h) or using Interface Builder's SCNView inspector.
 */
@property(nonatomic, readonly) SCNRenderingAPI renderingAPI API_AVAILABLE(macos(10.11), ios(9.0));

#if SCN_ENABLE_OPENGL

/*!
 @property context
 @abstract A Core OpenGL render context that is used as the render target (a CGLContextObj on macOS, an EAGLContext on iOS).
 */
@property(nonatomic, readonly, nullable) void *context;

#endif

#if SCN_ENABLE_METAL

/*!
 @property currentRenderCommandEncoder
 @abstract The current render command encoder if any. This property is only valid within the SCNSceneRendererDelegate methods and when rendering with Metal. Otherwise it is set to nil.
 */
@property(nonatomic, readonly, nullable) id <MTLRenderCommandEncoder> currentRenderCommandEncoder API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property currentRenderPassDescriptor
 @abstract The render pass descriptor of the receiver. This property is only valid within the SCNSceneRendererDelegate methods and when rendering with Metal. Otherwise it is set to nil.
 */
@property(nonatomic, readonly) MTLRenderPassDescriptor *currentRenderPassDescriptor API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @property device
 @abstract The metal device of the renderer. This property is only valid on a renderer created with a Metal device. Otherwise it is set to nil.
 */
@property(nonatomic, readonly, nullable) id <MTLDevice> device API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property colorPixelFormat
 @abstract The pixel format of the color attachment 0 of the renderer. This property is only valid on a renderer created with a Metal device.
 */
@property(nonatomic, readonly) MTLPixelFormat colorPixelFormat API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property depthPixelFormat
 @abstract The pixel format of the depth attachment of the renderer. This property is only valid on a renderer created with a Metal device.
 */
@property(nonatomic, readonly) MTLPixelFormat depthPixelFormat API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property stencilPixelFormat
 @abstract The pixel format of the stencil attachment of the renderer. This property is only valid on a renderer created with a Metal device.
 */
@property(nonatomic, readonly) MTLPixelFormat stencilPixelFormat API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property commandQueue
 @abstract The command queue of the renderer. This property is only valid on a renderer created with a Metal device. Otherwise it is set to nil.
 */
@property(nonatomic, readonly, nullable) id <MTLCommandQueue> commandQueue API_AVAILABLE(macos(10.11), ios(9.0));

#endif

/*!
 @property audioEngine
 @abstract Contains the instance of audio engine used by the scene.
 @discussion The audio engine can be used to add custom nodes to the audio graph.
 */
@property(nonatomic, readonly) AVAudioEngine *audioEngine API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property audioEnvironmentNode
 @abstract Contains the instance of audio environment node used by the scene to spacialize sounds.
 */
@property(nonatomic, readonly) AVAudioEnvironmentNode *audioEnvironmentNode API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos);

/*!
 @property audioListener
 @abstract Use this property to set the audio node to use as the listener position and orientation when rendering positional audio for this scene. The default is nil which means that the current point of view will be used dynamically.
 */
@property(nonatomic, retain, nullable) SCNNode *audioListener API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property currentViewport
 @abstract Returns the current viewport for this renderer, can be used to get the actual viewport from within the delegate callback during a live resize.
 */
@property(nonatomic, readonly) CGRect currentViewport API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));


#pragma mark Deprecated

/*!
 @property currentTime
 @abstract Specifies the current time to display the scene.
 @discussion Deprecated, use "sceneTime" instead.
 */
@property(nonatomic) NSTimeInterval currentTime API_DEPRECATED_WITH_REPLACEMENT("sceneTime", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
 @property usesReverseZ
 @abstract Specifies if the renderer should use the reverse Z technique. Defaults to YES.
 @discussion This property is only valid on a renderer created with a Metal device.
 */
@property (nonatomic) BOOL usesReverseZ API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

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
 @param renderer The renderer that will render the scene.
 @param time The time at which to update the scene.
 @discussion All modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer updateAtTime:(NSTimeInterval)time API_AVAILABLE(macos(10.10));

/*!
 @method renderer:didApplyAnimationsAtTime:
 @abstract Invoked on the delegate once the scene renderer did apply the animations.
 @param renderer The renderer that did render the scene.
 @param time The time at which the animations were applied.
 @discussion All modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didApplyAnimationsAtTime:(NSTimeInterval)time API_AVAILABLE(macos(10.10));

/*!
 @method renderer:didSimulatePhysicsAtTime:
 @abstract Invoked on the delegate once the scene renderer did simulate the physics.
 @param renderer The renderer that did render the scene.
 @param time The time at which the physics were simulated.
 @discussion All modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didSimulatePhysicsAtTime:(NSTimeInterval)time API_AVAILABLE(macos(10.10));

/*!
 @method renderer:didApplyConstraintsAtTime:
 @abstract Invoked on the delegate once the scene renderer did apply the constraints.
 @param renderer The renderer that did render the scene.
 @param time The time at which the constraints were simulated.
 @discussion All modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didApplyConstraintsAtTime:(NSTimeInterval)time API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @method renderer:willRenderScene:atTime:
 @abstract Invoked on the delegate before the scene renderer renders the scene. At this point the openGL context and the destination framebuffer are bound.
 @param renderer The renderer that will render the scene.
 @param scene The scene to be rendered.
 @param time The time at which the scene is to be rendered.
 @discussion Starting in 10.10 all modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer willRenderScene:(SCNScene *)scene atTime:(NSTimeInterval)time;

/*!
 @method renderer:didRenderScene:atTime:
 @abstract Invoked on the delegate once the scene renderer did render the scene.
 @param renderer The renderer that did render the scene.
 @param scene The rendered scene.
 @param time The time at which the scene was rendered.
 @discussion Starting in 10.10 all modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didRenderScene:(SCNScene *)scene atTime:(NSTimeInterval)time;

@end
    
NS_ASSUME_NONNULL_END
