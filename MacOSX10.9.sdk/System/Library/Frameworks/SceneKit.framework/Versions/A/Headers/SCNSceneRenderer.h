//
//  SCNSceneRenderer.h
//
//  Copyright (c) 2012-2013 Apple Inc. All rights reserved.
//

@class SCNScene;
@class SCNNode;
@protocol SCNSceneRendererDelegate;


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
SCN_EXTERN NSString * const SCNHitTestIgnoreHiddenNodesKey SCENEKIT_AVAILABLE(10_9, NA);


/*! @class SCNHitTestResult
    @abstract Results returned by the hit test methods.
 */

SCENEKIT_CLASS_AVAILABLE(10_8, NA)
@interface SCNHitTestResult : NSObject
{	
@private
	id _reserved;
}

/*! The node hit. */
@property(nonatomic, readonly) SCNNode*      node;
/*! Index of the geometry hit. */
@property(nonatomic, readonly) NSInteger     geometryIndex;
/*! Index of the face hit. */
@property(nonatomic, readonly) NSInteger     faceIndex;
/*! Intersection point in the node local coordinate system. */
@property(nonatomic, readonly) SCNVector3    localCoordinates;
/*! Intersection point in the world coordinate system. */
@property(nonatomic, readonly) SCNVector3    worldCoordinates;
/*! Intersection normal in the node local coordinate system. */
@property(nonatomic, readonly) SCNVector3    localNormal;
/*! Intersection normal in the world coordinate system. */
@property(nonatomic, readonly) SCNVector3    worldNormal;
/*! World transform of the node intersected. */
@property(nonatomic, readonly) CATransform3D modelTransform;

/*! 
 @method textureCoordinatesWithMappingChannel:
 @abstract Returns the texture coordinates at the point of intersection, for a given mapping channel.
 @param channel The texture coordinates source index of the geometry to use. The channel must exists on the geometry otherwise {0,0} will be returned.
 */
- (CGPoint) textureCoordinatesWithMappingChannel:(NSInteger) channel;

@end



/*! @protocol SCNSceneRenderer
    @abstract Protocol adopted by the various renderers (SCNView, SCNLayer, SCNRenderer)
 */
@protocol SCNSceneRenderer <NSObject>
@required

/*! 
 @property currentTime
 @abstract Specifies the current time to display the scene.
 */
@property(nonatomic) NSTimeInterval currentTime;

/*! 
 @property delegate
 @abstract Specifies the renderer delegate.
 */
@property(nonatomic, assign) id <SCNSceneRendererDelegate> delegate;

/*!
 @method hitTest:options:
 @abstract Returns an array of SCNHitTestResult for each node that contains a specified point.
 @param thePoint A point in the coordinate system of the receiver.
 @param options Optional parameters (see the "Hit test options" group for the available options).
 */
- (NSArray *)hitTest:(CGPoint)thePoint options:(NSDictionary *)options;

/*!
 @method isNodeInsideFrustum:withPointOfView:
 @abstract Test whether node is visible from the specified point of view.
 @param node The node to test the visibility of.
 @param pointOfView The point of view used to test the visibility.
 @discussion Return YES if the node is inside or interest the clipping planes of the point of view. This method doesn't test if 'node' is occluded by another node.
 */
- (BOOL)isNodeInsideFrustum:(SCNNode *)node withPointOfView:(SCNNode *)pointOfView SCENEKIT_AVAILABLE(10_9, NA);

/*!
 @method projectPoint
 @abstract Projects a point in the world coordinate system using the receiver's current point of view and viewport.
 @param point The world position to be projected.
 @discussion A point projected from the near (resp. far) clip plane will have a z component of 0 (resp. 1).
 */
- (SCNVector3)projectPoint:(SCNVector3)point SCENEKIT_AVAILABLE(10_9, NA);

/*!
 @method unprojectPoint
 @abstract Unprojects a screenspace 2D point with depth info using the receiver's current point of view and viewport.
 @param point The screenspace position to be unprojected.
 @discussion A point whose z component is 0 (resp. 1) is unprojected on the near (resp. far) clip plane.
 */
- (SCNVector3)unprojectPoint:(SCNVector3)point SCENEKIT_AVAILABLE(10_9, NA);

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
@property(nonatomic, retain) SCNNode *pointOfView;

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
 @discussion Returns YES if the object was prepared successfully, NO if it was canceled. This method may be triggered from a secondary thread.
 */
- (BOOL)prepareObject:(id)object shouldAbortBlock:(BOOL (^)())block SCENEKIT_AVAILABLE(10_9, NA);

/*!
 @property showsStatistics
 @abstract Determines whether the receiver should display statistics info like FPS. Defaults to NO.
 @discussion  When set to YES, statistics are displayed in a overlay on top of the rendered scene.
 */
@property(nonatomic) BOOL showsStatistics SCENEKIT_AVAILABLE(10_9, NA);

/*! 
 @property context
 @abstract A Core OpenGL render context that is used as the render target (usually a CGLContextObj).
 */
@property(nonatomic, readonly) void *context;

@end






/*!
 @protocol SCNSceneRendererDelegate
 @abstract Implement this protocol to perform operations at various times during the rendering
 */
@protocol SCNSceneRendererDelegate <NSObject>

@optional

/*! 
 @method renderer:willRenderScene:atTime:
 @abstract Invoked on the delegate before the scene renderer renders the scene.
 @param aRenderer The renderer that will render the scene.
 @param scene The scene to be rendered.
 @param time The time at which the scene is to be rendered.
 */
- (void)renderer:(id <SCNSceneRenderer>)aRenderer willRenderScene:(SCNScene *)scene atTime:(NSTimeInterval)time;

/*! 
 @method renderer:didRenderScene:atTime:
 @abstract Invoked on the delegate once the scene renderer did render the scene.
 @param aRenderer The renderer that did render the scene.
 @param scene The rendered scene.
 @param time The time at which the scene was rendered.
 */
- (void)renderer:(id <SCNSceneRenderer>)aRenderer didRenderScene:(SCNScene *)scene atTime:(NSTimeInterval)time;

@end


