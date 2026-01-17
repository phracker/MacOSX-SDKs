//
//  SCNNode.h
//  SceneKit
//
//  Copyright © 2012-2019 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNBoundingVolume.h>
#import <SceneKit/SCNAction.h>
#import <AvailabilityMacros.h>

NS_ASSUME_NONNULL_BEGIN

@class CIFilter;
@class SCNLight;
@class SCNCamera;
@class SCNGeometry;
@class SCNSkinner;
@class SCNMorpher;
@class SCNConstraint;
@class SCNPhysicsBody;
@class SCNPhysicsField;
@class SCNPhysicsBody;
@class SCNHitTestResult;
@class SCNRenderer;
@protocol SCNNodeRendererDelegate;
@protocol UIFocusItem;

/*! @group Rendering arguments
    @discussion These keys are used for the 'semantic' argument of -[SCNProgram setSemantic:forSymbol:options:]
                Transforms are SCNMatrix4 wrapped in NSValues.
 */
SCN_EXPORT NSString * const SCNModelTransform;
SCN_EXPORT NSString * const SCNViewTransform;
SCN_EXPORT NSString * const SCNProjectionTransform;
SCN_EXPORT NSString * const SCNNormalTransform;
SCN_EXPORT NSString * const SCNModelViewTransform;
SCN_EXPORT NSString * const SCNModelViewProjectionTransform;

/*! @enum SCNMovabilityHint
 @abstract The available modes of movability.
 @discussion Movable nodes are not captured when computing light probes.
 */
typedef NS_ENUM(NSInteger, SCNMovabilityHint) {
    SCNMovabilityHintFixed,
    SCNMovabilityHintMovable,
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*! @enum SCNNodeFocusBehavior
 @abstract Control the focus (UIFocus) behavior.
 */
typedef NS_ENUM(NSInteger, SCNNodeFocusBehavior) {
    SCNNodeFocusBehaviorNone = 0,    // Not focusable and node has no impact on other nodes that have focus interaction enabled.
    SCNNodeFocusBehaviorOccluding,   // Not focusable, but will prevent other focusable nodes that this node visually obscures from being focusable.
    SCNNodeFocusBehaviorFocusable    // Focusable and will also prevent other focusable nodes that this node visually obscures from being focusable.
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @class SCNNode
 @abstract SCNNode is the model class for node-tree objects.
 @discussion It encapsulates the position, rotations, and other transforms of a node, which define a coordinate system.
		     The coordinate systems of all the sub-nodes are relative to the one of their parent node.
 */
SCN_EXPORT
@interface SCNNode : NSObject <NSCopying, NSSecureCoding, SCNAnimatable, SCNActionable, SCNBoundingVolume, UIFocusItem>

#pragma mark - Creating a Node

/*! 
 @method node
 @abstract Creates and initializes a node instance.
 */
+ (instancetype)node;

/*! 
 @method nodeWithGeometry:
 @abstract Creates and initializes a node instance with the specified geometry attached.
 @param geometry The geometry to attach.
 */
+ (SCNNode *)nodeWithGeometry:(nullable SCNGeometry *)geometry;



#pragma mark - Copying the Node

/*!
 @method clone
 @abstract Returns a copy of the receiver. The returned instance is autoreleased.
 @discussion The copy is recursive: every child node will be cloned, too. For a non-recursive copy, use copy instead.
 The copied nodes will share their attached objects (light, geometry, camera, ...) with the original instances;
 if you want, for example, to change the materials of the copy independently of the original object, you'll
 have to copy the geometry of the node separately.
 */
- (instancetype)clone;

/*
 @method flattenedClone
 @abstract Returns a clone of the node containing a geometry that concatenates all the geometries contained in the node hierarchy.
 The returned clone is autoreleased.
 */
- (instancetype)flattenedClone API_AVAILABLE(macos(10.9));



#pragma mark - Managing the Node Attributes

/*!
 @property name
 @abstract Determines the name of the receiver.
 */
@property(nonatomic, copy, nullable) NSString *name;

/*!
 @property light
 @abstract Determines the light attached to the receiver.
 */
@property(nonatomic, retain, nullable) SCNLight *light;

/*!
 @property camera
 @abstract Determines the camera attached to the receiver.
 */

@property(nonatomic, retain, nullable) SCNCamera *camera;

/*!
 @property geometry
 @abstract Returns the geometry attached to the receiver.
 */
@property(nonatomic, retain, nullable) SCNGeometry *geometry;

/*!
 @property skinner
 @abstract Returns the skinner attached to the receiver.
 */
@property(nonatomic, retain, nullable) SCNSkinner *skinner API_AVAILABLE(macos(10.9));

/*!
 @property morpher
 @abstract Returns the morpher attached to the receiver.
 */
@property(nonatomic, retain, nullable) SCNMorpher *morpher API_AVAILABLE(macos(10.9));



#pragma mark - Modifying the Node′s Transform

/*! 
 @property transform
 @abstract Determines the receiver's transform. Animatable.
 @discussion The transform is the combination of the position, rotation and scale defined below. So when the transform is set, the receiver's position, rotation and scale are changed to match the new transform.
 */
@property(nonatomic) SCNMatrix4 transform;

/*!
 @property worldTransform
 @abstract Determines the receiver's transform in world space (relative to the scene's root node). Animatable.
 */
@property(nonatomic, readonly) SCNMatrix4 worldTransform;
- (void)setWorldTransform:(SCNMatrix4)worldTransform API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*! 
 @property position
 @abstract Determines the receiver's position. Animatable.
 */
@property(nonatomic) SCNVector3 position;

/*!
 @property worldPosition
 @abstract Determines the receiver's position in world space (relative to the scene's root node).
 */
@property(nonatomic) SCNVector3 worldPosition API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*! 
 @property rotation
 @abstract Determines the receiver's rotation. Animatable.
 @discussion The rotation is axis angle rotation. The three first components are the axis, the fourth one is the rotation (in radian).
 */
@property(nonatomic) SCNVector4 rotation;

/*!
 @property orientation
 @abstract Determines the receiver's orientation as a unit quaternion. Animatable.
 */
@property(nonatomic) SCNQuaternion orientation API_AVAILABLE(macos(10.10));

/*!
 @property worldOrientation
 @abstract Determines the receiver's orientation in world space (relative to the scene's root node). Animatable.
 */
@property(nonatomic) SCNQuaternion worldOrientation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));


/*!
 @property eulerAngles
 @abstract Determines the receiver's euler angles. Animatable.
 @dicussion The order of components in this vector matches the axes of rotation:
               1. Pitch (the x component) is the rotation about the node's x-axis (in radians)
               2. Yaw   (the y component) is the rotation about the node's y-axis (in radians)
               3. Roll  (the z component) is the rotation about the node's z-axis (in radians)
            SceneKit applies these rotations in the reverse order of the components:
               1. first roll
               2. then yaw
               3. then pitch
 */
@property(nonatomic) SCNVector3 eulerAngles API_AVAILABLE(macos(10.10));

/*! 
 @property scale
 @abstract Determines the receiver's scale. Animatable.
 */
@property(nonatomic) SCNVector3 scale;

/*! 
 @property pivot
 @abstract Determines the receiver's pivot. Animatable.
 */
@property(nonatomic) SCNMatrix4 pivot;

#pragma mark - Modifying the Node′s Visibility

/*! 
 @property hidden
 @abstract Determines whether the receiver is displayed. Defaults to NO. Animatable.
 */
@property(nonatomic, getter=isHidden) BOOL hidden;

/*! 
 @property opacity
 @abstract Determines the opacity of the receiver. Default is 1. Animatable.
 */
@property(nonatomic) CGFloat opacity;

/*!
 @property renderingOrder
 @abstract Determines the rendering order of the receiver.
 @discussion Nodes with greater rendering orders are rendered last. Defaults to 0.
 */
@property(nonatomic) NSInteger renderingOrder;

/*!
 @property castsShadow
 @abstract Determines if the node is rendered in shadow maps. Defaults to YES.
 */
@property(nonatomic) BOOL castsShadow API_AVAILABLE(macos(10.10));

/*!
 @property movabilityHint
 @abstract Communicates to SceneKit’s rendering system about how you want to move content in your scene; it does not affect your ability to change the node’s position or add animations or physics to the node. Defaults to SCNMovabilityHintFixed.
 */
@property(nonatomic) SCNMovabilityHint movabilityHint API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));


#pragma mark - Managing the Node Hierarchy

/*! 
 @property parentNode
 @abstract Returns the parent node of the receiver.
 */
@property(nonatomic, readonly, nullable) SCNNode *parentNode;

/*! 
 @property childNodes
 @abstract Returns the child node array of the receiver.
 */
@property(nonatomic, readonly) NSArray<SCNNode *> *childNodes;

/*!
 @method addChildNode:
 @abstract Appends the node to the receiver’s childNodes array.
 @param child The node to be added to the receiver’s childNodes array.
 */
- (void)addChildNode:(SCNNode *)child;

/*!
 @method insertChildNode:atIndex:
 @abstract Insert a node in the childNodes array at the specified index.
 @param child The node to insert.
 @param index Index in the childNodes array to insert the node.
 */
- (void)insertChildNode:(SCNNode *)child atIndex:(NSUInteger)index;

/*!
 @method removeFromParentNode
 @abstract Removes the node from the childNodes array of the receiver’s parentNode.
 */
- (void)removeFromParentNode;

/*!
 @method replaceChildNode:with:
 @abstract Remove `child' from the childNode array of the receiver and insert 'child2' if non-nil in its position.
 @discussion If the parentNode of `child' is not the receiver, the behavior is undefined.
 @param oldChild The node to replace in the childNodes array.
 @param newChild The new node that will replace the previous one.
 */
- (void)replaceChildNode:(SCNNode *)oldChild with:(SCNNode *)newChild;



#pragma mark - Searching the Node Hierarchy

/*!
 @method childNodeWithName:recursively:
 @abstract Returns the first node found in the node tree with the specified name.
 @discussion The search uses a pre-order tree traversal.
 @param name The name of the node you are searching for.
 @param recursively Set to YES if you want the search to look through the sub-nodes recursively.
 */
- (nullable SCNNode *)childNodeWithName:(NSString *)name recursively:(BOOL)recursively;

/*!
 @method childNodesPassingTest:
 @abstract Returns the child nodes of the receiver that passes a test in a given Block.
 @discussion The search is recursive and uses a pre-order tree traversal.
 @param predicate The block to apply to child nodes of the receiver. The block takes two arguments: "child" is a child node and "stop" is a reference to a Boolean value. The block can set the value to YES to stop further processing of the node hierarchy. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block. The Block returns a Boolean value that indicates whether "child" passed the test.
 */
- (NSArray<SCNNode *> *)childNodesPassingTest:(NS_NOESCAPE BOOL (^)(SCNNode *child, BOOL *stop))predicate;

/*!
 @method enumerateChildNodesUsingBlock:
 @abstract Executes a given block on each child node under the receiver.
 @discussion The search is recursive and uses a pre-order tree traversal.
 @param block The block to apply to child nodes of the receiver. The block takes two arguments: "child" is a child node and "stop" is a reference to a Boolean value. The block can set the value to YES to stop further processing of the node hierarchy. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 */
- (void)enumerateChildNodesUsingBlock:(NS_NOESCAPE void (^)(SCNNode *child, BOOL *stop))block API_AVAILABLE(macos(10.10));

/*!
 @method enumerateHierarchyUsingBlock:
 @abstract Executes a given block on the receiver and its child nodes.
 @discussion The search is recursive and uses a pre-order tree traversal.
 @param block The block to apply to the receiver and its child nodes. The block takes two arguments: "node" is a node in the hierarchy of the receiver (including the receiver) and "stop" is a reference to a Boolean value. The block can set the value to YES to stop further processing of the node hierarchy. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 */
- (void)enumerateHierarchyUsingBlock:(NS_NOESCAPE void (^)(SCNNode *node, BOOL *stop))block API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));


#pragma mark - Converting Between Node Coordinate Systems

/*!
 @method convertPosition:toNode:
 @abstract Converts a position from the receiver’s coordinate system to that of the specified node.
 @param position A position specified in the local coordinate system of the receiver.
 @param node The node into whose coordinate system "position" is to be converted. If "node" is nil, this method instead converts to world coordinates.
 */
- (SCNVector3)convertPosition:(SCNVector3)position toNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.9));

/*!
 @method convertPosition:fromNode:
 @abstract Converts a position from the coordinate system of a given node to that of the receiver.
 @param position A position specified in the local coordinate system of "node".
 @param node The node from whose coordinate system "position" is to be converted. If "node" is nil, this method instead converts from world coordinates.
 */
- (SCNVector3)convertPosition:(SCNVector3)position fromNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.9));


/**
 @abstract Converts a vector from the coordinate system of a given node to that of the receiver.

 @param vector A vector specified in the local coordinate system the receiver.
 @param node The node defining the space from which the vector should be transformed. If "node" is nil, this method instead converts from world coordinates.

 @return vector transformed from receiver local space to node local space.
 */
- (SCNVector3)convertVector:(SCNVector3)vector toNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));


/**
 @abstract Converts a vector from the coordinate system of a given node to that of the receiver.

 @param vector A vector specified in the local coordinate system of "node".
 @param node The node defining the space to which the vector should be transformed to. If "node" is nil, this method instead converts from world coordinates.

 @return vector transformed from node space to reveiver local space.
 */
- (SCNVector3)convertVector:(SCNVector3)vector fromNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));


/*!
 @method convertTransform:toNode:
 @abstract Converts a transform from the receiver’s coordinate system to that of the specified node.
 @param transform A transform specified in the local coordinate system of the receiver.
 @param node The node into whose coordinate system "transform" is to be converted. If "node" is nil, this method instead converts to world coordinates.
 */
- (SCNMatrix4)convertTransform:(SCNMatrix4)transform toNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.9));

/*!
 @method convertTransform:fromNode:
 @abstract Converts a transform from the coordinate system of a given node to that of the receiver.
 @param transform A transform specified in the local coordinate system of "node".
 @param node The node from whose coordinate system "transform" is to be converted. If "node" is nil, this method instead converts from world coordinates.
 */
- (SCNMatrix4)convertTransform:(SCNMatrix4)transform fromNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.9));


#pragma mark - Managing the SCNNode′s physics body

/*!
 @property physicsBody
 @abstract The description of the physics body of the receiver.
 @discussion Default is nil.
 */
@property(nonatomic, retain, nullable) SCNPhysicsBody *physicsBody API_AVAILABLE(macos(10.10));


#pragma mark - Managing the Node′s Physics Field

/*!
 @property physicsField
 @abstract The description of the physics field of the receiver.
 @discussion Default is nil.
 */
@property(nonatomic, retain, nullable) SCNPhysicsField *physicsField API_AVAILABLE(macos(10.10));


#pragma mark - Managing the Node′s Constraints

/*!
 @property constraints
 @abstract An array of SCNConstraint that are applied to the receiver.
 @discussion Adding or removing a constraint can be implicitly animated based on the current transaction.
 */
@property(copy, nullable) NSArray<SCNConstraint *> *constraints API_AVAILABLE(macos(10.9));


#pragma mark - Accessing the Node′s Filters

/*!
 @property filters
 @abstract An array of Core Image filters that are applied to the rendering of the receiver and its child nodes. Animatable.
 @discussion Defaults to nil. Filter properties should be modified by calling setValue:forKeyPath: on each node that the filter is attached to. If the inputs of the filter are modified directly after the filter is attached to a node, the behavior is undefined.
 */
@property(nonatomic, copy, nullable) NSArray<CIFilter *> *filters API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(watchos);


#pragma mark - Accessing the Presentation Node

/*!
 @property presentationNode
 @abstract Returns the presentation node.
 @discussion Returns a copy of the node containing all the properties as they were at the start of the current transaction, with any active animations applied.
             This gives a close approximation to the version of the node that is currently displayed.
             The effect of attempting to modify the returned node in any way is undefined. The returned node has no parent and no child nodes.
 */
@property(nonatomic, readonly) SCNNode *presentationNode;


#pragma mark - Pause

/*!
 @property paused
 @abstract Controls whether or not the node's actions and animations are updated or paused. Defaults to NO.
 */
@property(nonatomic, getter=isPaused) BOOL paused API_AVAILABLE(macos(10.10));


#pragma mark - Overriding the Rendering with Custom OpenGL Code

/*!
 @property rendererDelegate
 @abstract Specifies the receiver's renderer delegate object.
 @discussion Setting a renderer delegate prevents the SceneKit renderer from drawing the node and lets you use custom OpenGL code instead.
             The preferred way to customize the rendering is to tweak the material properties of the different materials of the node's geometry. SCNMaterial conforms to the SCNShadable protocol and allows for more advanced rendering using GLSL.
             You would typically use a renderer delegate with a node that has no geometry and only serves as a location in space. An example would be attaching a particle system to that node and render it with custom OpenGL code.
 */
@property(nonatomic, assign, nullable) id <SCNNodeRendererDelegate> rendererDelegate;



#pragma mark - Hit Testing in the Node

/*!
 @method hitTestWithSegmentFromPoint:toPoint:options:
 @abstract Returns an array of SCNHitTestResult for each node in the receiver's sub tree that intersects the specified segment.
 @param pointA The first point of the segment relative to the receiver.
 @param pointB The second point of the segment relative to the receiver.
 @param options Optional parameters (see the "Hit test options" section in SCNSceneRenderer.h for the available options).
 @discussion See SCNSceneRenderer.h for a screen-space hit testing method.
 */
- (NSArray<SCNHitTestResult *> *)hitTestWithSegmentFromPoint:(SCNVector3)pointA toPoint:(SCNVector3)pointB options:(nullable NSDictionary<NSString *, id> *)options API_AVAILABLE(macos(10.9));


#pragma mark - Categories

/*!
 @property categoryBitMask
 @abstract Defines what logical 'categories' the receiver belongs too. Defaults to 1.
 @discussion Categories can be used to
                1. exclude nodes from the influence of a given light (see SCNLight.categoryBitMask)
                2. include/exclude nodes from render passes (see SCNTechnique.h)
                3. specify which nodes to use when hit-testing (see SCNHitTestOptionCategoryBitMask)
 */
@property(nonatomic) NSUInteger categoryBitMask API_AVAILABLE(macos(10.10));

#pragma mark - UIFocus support

/*!
 @property focusBehavior
 @abstract Controls the behavior of the receiver regarding the UIFocus system. Defaults to SCNNodeFocusBehaviorNone.
 */
@property(nonatomic) SCNNodeFocusBehavior focusBehavior API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@end

@interface SCNNode (Transforms)

/*!
 @property localUp
 @abstract The local unit Y axis (0, 1, 0).
 */
@property(class, readonly, nonatomic) SCNVector3 localUp API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property localRight
 @abstract The local unit X axis (1, 0, 0).
 */
@property(class, readonly, nonatomic) SCNVector3 localRight API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property localFront
 @abstract The local unit -Z axis (0, 0, -1).
 */
@property(class, readonly, nonatomic) SCNVector3 localFront API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property worldUp
 @abstract The local unit Y axis (0, 1, 0) in world space.
 */
@property(readonly, nonatomic) SCNVector3 worldUp API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property worldRight
 @abstract The local unit X axis (1, 0, 0) in world space.
 */
@property(readonly, nonatomic) SCNVector3 worldRight API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property worldFront
 @abstract The local unit -Z axis (0, 0, -1) in world space.
 */
@property(readonly, nonatomic) SCNVector3 worldFront API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/**
 Convenience for calling lookAt:up:localFront: with worldUp set to `self.worldUp`
 and localFront [SCNNode localFront].
 @param worldTarget target position in world space.
 */
- (void)lookAt:(SCNVector3)worldTarget API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/**
 Set the orientation of the node so its front vector is pointing toward a given
 target. Using a reference up vector in world space and a front vector in
 local space.

 @param worldTarget position in world space.
 @param worldUp the up vector in world space.
 @param localFront the front vector in local space.
 */
- (void)lookAt:(SCNVector3)worldTarget up:(SCNVector3)worldUp localFront:(SCNVector3)localFront API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/**
 Translate the current node position along the given vector in local space.

 @param translation the translation in local space.
 */
- (void)localTranslateBy:(SCNVector3)translation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/**
 Apply a the given rotation to the current one.

 @param rotation rotation in local space.
 */
- (void)localRotateBy:(SCNQuaternion)rotation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/**
 Apply a rotation relative to a target point in parent space.

 @param worldRotation rotation to apply in world space.
 @param worldTarget position of the target in world space.
 */
- (void)rotateBy:(SCNQuaternion)worldRotation aroundTarget:(SCNVector3)worldTarget API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@end

/*!
 @category NSObject (SCNNodeRendererDelegate)
 @abstract The SCNNodeRendererDelegate protocol declares the methods that an instance of SCNNode invokes to let a delegate customize its rendering.
 */
@protocol SCNNodeRendererDelegate <NSObject>
@optional

/*! 
 @method renderNode:renderer:arguments:
 @abstract Invoked when a node is rendered.
 @discussion The preferred way to customize the rendering is to tweak the material properties of the different materials of the node's geometry. SCNMaterial conforms to the SCNShadable protocol and allows for more advanced rendering using GLSL.
             You would typically use a renderer delegate with a node that has no geometry and only serves as a location in space. An example would be attaching a particle system to that node and render it with custom OpenGL code.
             Only drawing calls and the means to achieve them are supposed to be performed during the renderer delegate callback, any changes in the model (nodes, geometry...) would involve unexpected results.
 @param node The node to render.
 @param renderer The scene renderer to render into.
 @param arguments A dictionary whose values are SCNMatrix4 matrices wrapped in NSValue objects.
 */
- (void)renderNode:(SCNNode *)node renderer:(SCNRenderer *)renderer arguments:(NSDictionary<NSString *, id> *)arguments;

@end

@interface SCNNode (SIMD)

/*!
 @abstract Determines the receiver's transform. Animatable.
 @discussion The transform is the combination of the position, rotation and scale defined below. So when the transform is set, the receiver's position, rotation and scale are changed to match the new transform.
 */
@property(nonatomic) simd_float4x4 simdTransform API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's position. Animatable.
 */
@property(nonatomic) simd_float3 simdPosition API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's rotation. Animatable.
 @discussion The rotation is axis angle rotation. The three first components are the axis, the fourth one is the rotation (in radian).
 */
@property(nonatomic) simd_float4 simdRotation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's orientation as a unit quaternion. Animatable.
 */
@property(nonatomic) simd_quatf simdOrientation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's euler angles. Animatable.
 @dicussion The order of components in this vector matches the axes of rotation:
 1. Pitch (the x component) is the rotation about the node's x-axis (in radians)
 2. Yaw   (the y component) is the rotation about the node's y-axis (in radians)
 3. Roll  (the z component) is the rotation about the node's z-axis (in radians)
 SceneKit applies these rotations in the reverse order of the components:
 1. first roll
 2. then yaw
 3. then pitch
 */
@property(nonatomic) simd_float3 simdEulerAngles API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's scale. Animatable.
 */
@property(nonatomic) simd_float3 simdScale API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's pivot. Animatable.
 */
@property(nonatomic) simd_float4x4 simdPivot API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's position in world space (relative to the scene's root node).
 */
@property(nonatomic) simd_float3 simdWorldPosition API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's orientation in world space (relative to the scene's root node). Animatable.
 */
@property(nonatomic) simd_quatf simdWorldOrientation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's transform in world space (relative to the scene's root node). Animatable.
 */
@property(nonatomic) simd_float4x4 simdWorldTransform API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

- (simd_float3)simdConvertPosition:(simd_float3)position toNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
- (simd_float3)simdConvertPosition:(simd_float3)position fromNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

- (simd_float3)simdConvertVector:(simd_float3)vector toNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
- (simd_float3)simdConvertVector:(simd_float3)vector fromNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

- (simd_float4x4)simdConvertTransform:(simd_float4x4)transform toNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
- (simd_float4x4)simdConvertTransform:(simd_float4x4)transform fromNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@property(class, readonly, nonatomic) simd_float3 simdLocalUp API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
@property(class, readonly, nonatomic) simd_float3 simdLocalRight API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
@property(class, readonly, nonatomic) simd_float3 simdLocalFront API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@property(readonly, nonatomic) simd_float3 simdWorldUp API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
@property(readonly, nonatomic) simd_float3 simdWorldRight API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
@property(readonly, nonatomic) simd_float3 simdWorldFront API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

- (void)simdLookAt:(simd_float3)worldTarget API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
- (void)simdLookAt:(simd_float3)worldTarget up:(simd_float3)worldUp localFront:(simd_float3)localFront API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
- (void)simdLocalTranslateBy:(simd_float3)translation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

- (void)simdLocalRotateBy:(simd_quatf)rotation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
- (void)simdRotateBy:(simd_quatf)worldRotation aroundTarget:(simd_float3)worldTarget API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@end

NS_ASSUME_NONNULL_END
