/**
 @header
 
 
 3D Nodes are used to display 3D content in a SKScene.
 
 
 @copyright 2011 Apple, Inc. All rights reserve.
 
 */

#import <SpriteKit/SKSpriteNode.h>
#import <SpriteKit/SpriteKitBase.h>

@class SCNScene;
@class SCNNode;
@class SCNHitTestResult;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_10, 8_0)
SK_EXPORT @interface SK3DNode : SKNode


/**
 Designated initializer.
 Initialize a 3D Node with the viewport size the 3D content will be rendered with.
*/
- (instancetype)initWithViewportSize:(CGSize)viewportSize NS_DESIGNATED_INITIALIZER;

/**
 Support coding and decoding via NSKeyedArchiver.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/**
 Create a 3D Node with the viewport size the 3D content will be rendered with.
 */
+ (instancetype)nodeWithViewportSize:(CGSize)viewportSize;


/** The viewport size that the 3D content will be rendered with */
@property CGSize viewportSize;

/** A SceneKit scene  */
@property (nonatomic, retain, nullable) SCNScene *scnScene;

/** 
 @property sceneTime
 @abstract Specifies the current time to display the scene.
*/
@property(nonatomic) NSTimeInterval sceneTime;

/**
 @method hitTest:options:
 @abstract Returns an array of SCNHitTestResult for each node that contains a specified point.
 @param thePoint A point in the coordinate system of the receiver.
 @param options Optional parameters (see the "Hit test options" group for the available options).
*/
- (NSArray<SCNHitTestResult *> *)hitTest:(CGPoint)point options:(nullable NSDictionary<NSString *, id> *)options;

/**
 @method projectPoint
 @abstract Projects a point in the world coordinate system using the receiver's current point of view and viewport.
 @param point The world position to be projected.
 @discussion A point projected from the near (resp. far) clip plane will have a z component of 0 (resp. 1).
*/
- (vector_float3)projectPoint:(vector_float3)point;

/**
 @method unprojectPoint
 @abstract Unprojects a screenspace 2D point with depth info using the receiver's current point of view and viewport.
 @param point The screenspace position to be unprojected.
 @discussion A point whose z component is 0 (resp. 1) is unprojected on the near (resp. far) clip plane.
*/
- (vector_float3)unprojectPoint:(vector_float3)point;

 /**
 @property playing
 @abstract Returns YES if the scene is playing, NO otherwise.
  */
@property(getter=isPlaying) BOOL playing;

/**
 @property loops
 @abstract Indicates whether the receiver restarts playback when it reaches the end of its content. Default: YES.
 @discussion YES when the receiver restarts playback when it finishes, NO otherwise.
*/
@property(nonatomic) BOOL loops;

/**
 @property pointOfView
 @abstract Specifies the point of view used to render the scene.
 @discussion A point of view must have either a camera or a spot light attached.
 */
@property(nonatomic, retain, nullable) SCNNode *pointOfView;

/**
 @property autoenablesDefaultLighting
 @abstract Specifies whether the receiver should automatically light up scenes that have no light source. The default is NO.
 @discussion When enabled, a diffuse light is automatically added and placed while rendering scenes that have no light or only ambient lights.
 */
@property(nonatomic) BOOL autoenablesDefaultLighting;


@end

NS_ASSUME_NONNULL_END
