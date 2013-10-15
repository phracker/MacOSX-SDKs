//
//  SCNNode.h
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNBoundingVolume.h>



@class SCNLight;
@class SCNCamera;
@class SCNGeometry;
@protocol SCNNodeRendererDelegate;



/*! @group Rendering arguments
    @discussion These keys are used in the `arguments' dictionary of renderNode:renderer:arguments:
				and in the `semantic' argument of -[SCNProgram setSemantic:forSymbol:options:].
                Transforms are CATransform3Ds wrapped in NSValues.
 */
SCENEKIT_EXTERN NSString *const SCNModelTransform SCENEKIT_AVAILABLE(10_7, NA);
SCENEKIT_EXTERN NSString *const SCNViewTransform SCENEKIT_AVAILABLE(10_7, NA);
SCENEKIT_EXTERN NSString *const SCNProjectionTransform SCENEKIT_AVAILABLE(10_7, NA);
SCENEKIT_EXTERN NSString *const SCNNormalTransform SCENEKIT_AVAILABLE(10_7, NA);
SCENEKIT_EXTERN NSString *const SCNModelViewTransform SCENEKIT_AVAILABLE(10_7, NA);
SCENEKIT_EXTERN NSString *const SCNModelViewProjectionTransform SCENEKIT_AVAILABLE(10_7, NA);           


/*!
 @class SCNNode
 @abstract SCNNode is the model class for node-tree objects.
 @discussion It encapsulates the position, rotations, and other transforms of a node, which define a coordinate system.
		     The coordinate systems of all the sub-nodes are relative to the one of their parent node.
 */

SCENEKIT_AVAILABLE(10_7, NA)
@interface SCNNode : NSObject <NSCopying, SCNAnimatable, SCNBoundingVolume> 
{
@private
	id _reserved;
}

/*! 
 @method node
 @abstract Creates and intialize a node instance.
 */
+ (SCNNode *)node;

/*! 
 @method nodeWithGeometry:
 @abstract Creates and intialize a node instance with the specified geometry attached.
 @param geometry The geometry to attach.
 */
+ (SCNNode *)nodeWithGeometry:(SCNGeometry *)geometry;

/*! 
 @functiongroup modifying a node
 */

/*! 
 @property transform
 @abstract Determines the receiver's transform. Animatable.
 @discussion The transform is the combination of the position, rotation and scale defined below. So when the transform is set, the receiver's position, rotation and scale are changed to match the new transform.
 */
@property(nonatomic) CATransform3D transform;

/*! 
 @property position
 @abstract Determines the receiver's position. Animatable.
 */
@property(nonatomic) SCNVector3 position;

/*! 
 @property rotation
 @abstract Determines the receiver's rotation. Animatable.
 @discussion The rotation is axis angle rotation. The three first components are the axis, the fourth one is the rotation (in radian).
 */
@property(nonatomic) SCNVector4 rotation;

/*! 
 @property scale
 @abstract Determines the receiver's scale. Animatable.
 */
@property(nonatomic) SCNVector3 scale;

/*! 
 @property pivot
 @abstract Determines the receiver's pivot. Animatable.
 */
@property(nonatomic) CATransform3D pivot;

/*! 
 @property worldTransform
 @abstract Returns the receiver's world transform.
 @discussion A world transform is the transform relative to the scene. 
 */
@property(nonatomic, readonly) CATransform3D worldTransform;

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
@functiongroup hierarchy
 */

/*! 
 @property parentNode
 @abstract Returns the parent node of the receiver.
 */
@property(nonatomic, readonly) SCNNode *parentNode;

/*! 
 @property childNodes
 @abstract Returns the child node array of the receiver.
 */
@property(nonatomic, readonly, copy) NSArray *childNodes;


/*! 
 @functiongroup node attributes
 */

/*! 
 @property light
 @abstract Determines the light attached to the receiver.
 */
@property(nonatomic, retain) SCNLight *light;

/*! 
 @property camera
 @abstract Determines the camera attached to the receiver.
 */

@property(nonatomic, retain) SCNCamera *camera;

/*! 
 @property Determines
 @abstract Returns the geometry attached to the receiver.
 */
@property(nonatomic, retain) SCNGeometry *geometry;

/*! 
 @property name
 @abstract Determines the name of the receiver.
 */
@property(nonatomic, copy) NSString *name;

/*! 
 @method presentationNode
 @abstract Returns the presentation node.
 @discussion Returns a copy of the node containing all properties as they were
   at the start of the current transaction, with any active animations
   applied. This gives a close approximation to the version of the node
   that is currently displayed. 
 
   The effect of attempting to modify the returned node in any way is
   undefined.

   The returned node has no parent and no child nodes. 
*/
- (SCNNode *)presentationNode;


/*! 
 @functiongroup Managing the node hierarchy 
 */

/*! 
 @method insertChildNode:atIndex:
 @abstract Insert a node in the childNodes array at the specified index.
 @param child The node to insert.
 @param index Index in the childNodes array to insert the node.
 */
- (void)insertChildNode:(SCNNode*)child atIndex:(NSUInteger)index;

/*! 
 @method replaceChildNode:with:
 @abstract Remove `child' from the childNode array of the receiver and insert 'child2' if non-nil in its position.
 @discussion If the parentNode of `child' is not the receiver, the behavior is undefined.
 @param child The node to replace in the childNodes array.
 @param child2 The new node that will replace the previous one.
 */
- (void)replaceChildNode:(SCNNode *)child with:(SCNNode*)child2;

/*! 
 @method removeFromParentNode
 @abstract Removes the node from the childNodes array of the receiver’s parentNode.
 */
- (void)removeFromParentNode;

/*! 
 @method addChildNode:
 @abstract Appends the node to the receiver’s childNodes array.
 @param child The node to be added to the receiver’s childNodes array.
 */
- (void)addChildNode:(SCNNode *) child;


/*! 
 @functiongroup Searching for nodes in the hierarchy 
 */

/*! 
 @method childNodeWithName:recursively:
 @abstract Returns the first node found in the node tree with the specified name.
 @discussion The search uses a pre-order tree traversal.
 @param name The name of the node you are searching for.
 @param recursively Set to YES if you want the search to look through the sub-nodes recursively.
 */
- (SCNNode *)childNodeWithName:(NSString *)name recursively:(BOOL)recursively;

/*! 
 @method childNodesPassingTest:
 @abstract Returns the child nodes of the receiver that passes a test in a given Block.
 @discussion The search is recursive and uses a pre-order tree traversal.
 @param predicate The block to apply to child nodes of the receiver. The block takes two arguments: "child" is a child node or the receiver and "stop" is a reference to a Boolean value.  The block can set the value to YES to stop further processing of the node hierarchy. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block. The Block returns a Boolean value that indicates whether "child" passed the test.
 */
- (NSArray*)childNodesPassingTest:(BOOL (^)(SCNNode * child, BOOL *stop))predicate;


/*! 
 @functiongroup Rendering delegate
 */

/*! 
 @property rendererDelegate
 @abstract Specifies the receiver’s renderer delegate object.
 @discussion The render delegate has to implements the required methods of the SCNNodeRendererDelegate informal protocol.
 */
@property(nonatomic, assign) id <SCNNodeRendererDelegate> rendererDelegate;

/*! 
 @functiongroup Copying
 */
/*! 
 @method clone
 @abstract Returns a copy of the receiver. The returned instance is autoreleased.
 @discussion The copy is recursive: every child node will be cloned, too. For a non-recursive copy, use copy instead.
			 The copied nodes will share their attached objects (light, geometry, camera, ...) with the original instances;
             if you want, for example, to change the materials of the copy independently of the original object, you'll
             have to copy the geometry of the node separately.
 */
- (id)clone;

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
 @discussion	This method is required. 
				Only drawing calls and the means to achieve them are supposed to be performed during the renderer delegate callback, 
				any changes in the model (nodes,geometry...) would involve unexpected results.
 @param node The node to render.
 @param renderer The scene renderer to render into.
 @param arguments A dictionary that can have any of the entries described at the beginning of this file.
 */
- (void)renderNode:(SCNNode *)node renderer:(SCNRenderer *)renderer arguments:(NSDictionary *)arguments;

@end




