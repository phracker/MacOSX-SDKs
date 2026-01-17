/**
 @header
 
 
 Nodes are the base scene graph nodes used in the SpriteKit scene graph.
 

 @copyright 2011 Apple, Inc. All rights reserve.

*/

#import <SpriteKit/SpriteKitBase.h>

@class SKView, SKAction, SKScene, SKTexture, SKPhysicsBody;

/**
 Blend modes that the SKNode uses to compose with the framebuffer to produce blended colors.
 */
typedef NS_ENUM(NSInteger, SKBlendMode) {
    SKBlendModeAlpha        = 0,    // Blends the source and destination colors by multiplying the source alpha value.
    SKBlendModeAdd          = 1,    // Blends the source and destination colors by adding them up.
    SKBlendModeSubtract     = 2,    // Blends the source and destination colors by subtracting the source from the destination.
    SKBlendModeMultiply     = 3,    // Blends the source and destination colors by multiplying them.
    SKBlendModeMultiplyX2   = 4,    // Blends the source and destination colors by multiplying them and doubling the result.
    SKBlendModeScreen       = 5,    // FIXME: Description needed
    SKBlendModeReplace      = 6     // Replaces the destination with the source (ignores alpha).
} NS_ENUM_AVAILABLE(10_9, 7_0);

/**
 A SpriteKit scene graph node. These are the branch nodes that together with geometric leaf nodes make up the directed acyclic graph that is the SpriteKit scene graph tree.
 
 All nodes have one and exactly one parent unless they are the root node of a graph tree. Leaf nodes have no children and contain some sort of sharable data that guarantee the DAG condition.
 */
#if TARGET_OS_IPHONE
SK_EXPORT @interface SKNode : UIResponder <NSCopying, NSCoding>
#else
SK_EXPORT @interface SKNode : NSResponder <NSCopying, NSCoding>
#endif

+ (instancetype)node;

@property (SK_NONATOMIC_IOSONLY, readonly) CGRect frame;

/**
 Calculates the bounding box including all child nodes in parents coordinate system.
 */
- (CGRect)calculateAccumulatedFrame;

/**
 The position of the node in the parent's coordinate system
 */
@property (SK_NONATOMIC_IOSONLY) CGPoint position;

/**
 The z-order of the node (used for ordering). Negative z is "into" the screen, Positive z is "out" of the screen. A greater zPosition will sort in front of a lesser zPosition.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat zPosition;

/**
 The Euler rotation about the z axis (in radians)
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat zRotation;

/**
 The scaling in the X axis
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat xScale;
/**
 The scaling in the Y axis
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat yScale;

/**
 The speed multiplier applied to all actions run on this node. Inherited by its children.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat speed;

/**
 Alpha of this node (multiplied by the output color to give the final result)
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat alpha;

/**
 Controls whether or not the node's actions is updated or paused.
 */
@property (SK_NONATOMIC_IOSONLY, getter = isPaused) BOOL paused;

/**
 Controls whether or not the node and its children are rendered.
 */
@property (SK_NONATOMIC_IOSONLY, getter = isHidden) BOOL hidden;

/**
 Controls whether or not the node receives touch events
 */
@property(getter=isUserInteractionEnabled) BOOL userInteractionEnabled;

/**
 The parent of the node.
 
 If this is nil the node has not been added to another group and is thus the root node of its own graph.
 */
@property (SK_NONATOMIC_IOSONLY, readonly) SKNode *parent;


/**
 The children of this node.
 
 */
@property (SK_NONATOMIC_IOSONLY, readonly) NSArray *children;


/**
 The client assignable name.
 
 In general, this should be unique among peers in the scene graph.
 */
@property (SK_NONATOMIC_IOSONLY, copy) NSString *name;

/**
 The scene that the node is currently in.
 */
@property (SK_NONATOMIC_IOSONLY, readonly) SKScene* scene;

@property (SK_NONATOMIC_IOSONLY, retain) SKPhysicsBody *physicsBody;

/**
 An optional dictionary that can be used to hold user data pretaining to the node. Defaults to nil. 
 */
@property (SK_NONATOMIC_IOSONLY, retain) NSMutableDictionary *userData;

/**
 Sets both the x & y scale
 
 @param scale the uniform scale to set.
 */
- (void)setScale:(CGFloat)scale;

/**
 Adds a node as a child node of this node
 
 The added node must not have a parent.
 
 @param node the child node to add.
 */
- (void)addChild:(SKNode *)node;

- (void)insertChild:(SKNode *)node atIndex:(NSInteger)index;

- (void)removeChildrenInArray:(NSArray *)nodes;
- (void)removeAllChildren;

- (void)removeFromParent;

- (SKNode *)childNodeWithName:(NSString *)name;
- (void)enumerateChildNodesWithName:(NSString *)name usingBlock:(void (^)(SKNode *node, BOOL *stop))block;

/* Returns true if the specified parent is in this node's chain of parents */

- (BOOL)inParentHierarchy:(SKNode *)parent;

- (void)runAction:(SKAction *)action;
- (void)runAction:(SKAction *)action completion:(void (^)())block;
- (void)runAction:(SKAction *)action withKey:(NSString *)key;

- (BOOL)hasActions;
- (SKAction *)actionForKey:(NSString *)key;

- (void)removeActionForKey:(NSString *)key;
- (void)removeAllActions;

- (BOOL)containsPoint:(CGPoint)p;
- (SKNode *)nodeAtPoint:(CGPoint)p;
- (NSArray *)nodesAtPoint:(CGPoint)p;

- (CGPoint)convertPoint:(CGPoint)point fromNode:(SKNode *)node;
- (CGPoint)convertPoint:(CGPoint)point toNode:(SKNode *)node;

/* Returns true if the bounds of this node intersects with the transformed bounds of the other node, otherwise false */

- (BOOL)intersectsNode:(SKNode *)node;

@end


/**
 Provided for easy transformation of UITouches coordinates to SKNode coordinates should you choose to handle touch events natively.
 */
#if TARGET_OS_IPHONE
//Allow conversion of UITouch coordinates to scene-space
@interface UITouch (SKNodeTouches)
- (CGPoint)locationInNode:(SKNode *)node;
- (CGPoint)previousLocationInNode:(SKNode *)node;
@end
#else
@interface NSEvent (SKNodeEvent)
- (CGPoint)locationInNode:(SKNode *)node;
@end
#endif