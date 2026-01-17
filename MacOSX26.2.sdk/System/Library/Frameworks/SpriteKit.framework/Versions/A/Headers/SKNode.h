/**
 @header
 
 
 Nodes are the base scene graph nodes used in the SpriteKit scene graph.
 
 
 @copyright 2011 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKitBase.h>

NS_ASSUME_NONNULL_BEGIN

@class SKAction, SKScene, SKTexture, SKPhysicsBody, SKFieldNode;
@class SKReachConstraints, SKConstraint, SKAttributeValue, SKWarpGeometry;
@protocol UIFocusItem;

/**
 Blend modes that the SKNode uses to compose with the framebuffer to produce blended colors.
 */
typedef NS_ENUM(NSInteger, SKBlendMode) {
    SKBlendModeAlpha         = 0,    // Blends the source and destination colors by multiplying the source alpha value.
    SKBlendModeAdd           = 1,    // Blends the source and destination colors by adding them up.
    SKBlendModeSubtract      = 2,    // Blends the source and destination colors by subtracting the source from the destination.
    SKBlendModeMultiply      = 3,    // Blends the source and destination colors by multiplying them.
    SKBlendModeMultiplyX2    = 4,    // Blends the source and destination colors by multiplying them and doubling the result.
    SKBlendModeScreen        = 5,    // Blends the source and destination colors by multiplying one minus the source with the destination and adding the source.
    SKBlendModeReplace       = 6,    // Replaces the destination with the source (ignores alpha).
    SKBlendModeMultiplyAlpha = 7     // Blends the source and destination colors by multiplying them (with alpha).
} NS_ENUM_AVAILABLE(10_9, 7_0);

typedef NS_ENUM(NSInteger, SKNodeFocusBehavior) {
    SKNodeFocusBehaviorNone = 0,    // Not focusable and node has no impact on other nodes that have focus interaction enabled.  This is the default.
    SKNodeFocusBehaviorOccluding,   // Not focusable, but will prevent other focusable nodes that this node visually obscures from being focusable.
    SKNodeFocusBehaviorFocusable    // Focusable and will also prevent other focusable nodes that this node visually obscures from being focusable.
} API_AVAILABLE(ios(11.0), tvos(11.0), watchos(9.0)) API_UNAVAILABLE(macos);

/**
 A SpriteKit scene graph node. These are the branch nodes that together with geometric leaf nodes make up the directed acyclic graph that is the SpriteKit scene graph tree.
 
 All nodes have one and exactly one parent unless they are the root node of a graph tree. Leaf nodes have no children and contain some sort of sharable data that guarantee the DAG condition.
 */
#if TARGET_OS_IPHONE
#if SKVIEW_AVAILABLE
SK_EXPORT @interface SKNode : UIResponder <NSCopying, NSSecureCoding, UIFocusItem, UIFocusItemContainer, UICoordinateSpace>
#else
SK_EXPORT @interface SKNode : NSObject <NSCopying, NSSecureCoding>
#endif
#else
SK_EXPORT @interface SKNode : NSResponder <NSCopying, NSSecureCoding>
#endif

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 Support coding and decoding via NSKeyedArchiver.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

+ (instancetype)node;

+ (nullable instancetype)nodeWithFileNamed:(NSString*)filename;

+ (nullable instancetype)nodeWithFileNamed:(NSString *)filename securelyWithClasses:(NSSet<Class> *)classes andError:(NSError **)error API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

@property (nonatomic, readonly) CGRect frame;


/**
 Calculates the bounding box including all child nodes in parents coordinate system.
 */
- (CGRect)calculateAccumulatedFrame;

/**
 The position of the node in the parent's coordinate system
 */
@property (nonatomic) CGPoint position;

/**
 The z-order of the node (used for ordering). Negative z is "into" the screen, Positive z is "out" of the screen. A greater zPosition will sort in front of a lesser zPosition.
 */
@property (nonatomic) CGFloat zPosition;

/**
 The Euler rotation about the z axis (in radians)
 */
@property (nonatomic) CGFloat zRotation;

/**
 The scaling in the X axis
 */
@property (nonatomic) CGFloat xScale;
/**
 The scaling in the Y axis
 */
@property (nonatomic) CGFloat yScale;

/**
 The speed multiplier applied to all actions run on this node. Inherited by its children.
 */
@property (nonatomic) CGFloat speed;

/**
 Alpha of this node (multiplied by the output color to give the final result)
 */
@property (nonatomic) CGFloat alpha;

/**
 Controls whether or not the node's actions is updated or paused.
 */
@property (nonatomic, getter = isPaused) BOOL paused;

/**
 Controls whether or not the node and its children are rendered.
 */
@property (nonatomic, getter = isHidden) BOOL hidden;

/**
 Controls whether or not the node receives touch events
 */
@property (nonatomic, getter=isUserInteractionEnabled) BOOL userInteractionEnabled;

/**
 Determines how this node participates in the focus system.  The default is SKNodeFocusBehaviorNone.
 */
@property (nonatomic) SKNodeFocusBehavior focusBehavior API_AVAILABLE(ios(11.0), tvos(11.0), watchos(9.0)) API_UNAVAILABLE(macos);

/**
 The parent of the node.
 
 If this is nil the node has not been added to another group and is thus the root node of its own graph.
 */
@property (nonatomic, readonly, nullable) SKNode *parent;

/**
 The children of this node.
 
 */
@property (nonatomic, readonly) NSArray<SKNode*> *children;


/**
 The client assignable name.
 
 In general, this should be unique among peers in the scene graph.
 */
@property (nonatomic, copy, nullable) NSString *name;

/**
 The scene that the node is currently in.
 */
@property (nonatomic, readonly, nullable) SKScene* scene;

/**
 Physics body attached to the node, with synchronized scale, rotation, and position
 */
@property (nonatomic, retain, nullable) SKPhysicsBody *physicsBody;

/**
 An optional dictionary that can be used to store your own data in a node. Defaults to nil.
 */
@property (nonatomic, retain, nullable) NSMutableDictionary *userData;

/**
 Kinematic constraints, used in IK solving
 */
@property (nonatomic, copy, nullable) SKReachConstraints *reachConstraints;


/**
 Optional array of SKConstraints
 Constraints are evaluated each frame after actions and physics.
 The node's transform will be changed to satisfy the constraint.
 */
@property (nonatomic, copy, nullable) NSArray<SKConstraint*> *constraints;

/**
 Optional dictionary of SKAttributeValues
 Attributes can be used with custom SKShaders.
 DEPRECATED: Attributes are only available for node classes supporting SKShader (see SKSpriteNode etc.).
 */
@property (nonatomic, nonnull, copy) NSDictionary<NSString *, SKAttributeValue *> *attributeValues NS_DEPRECATED(10_12, 10_12, 10_0, 10_0);

- (nullable SKAttributeValue*)valueForAttributeNamed:(nonnull NSString *)key NS_DEPRECATED(10_12, 10_12, 10_0, 10_0);
- (void)setValue:(SKAttributeValue*)value forAttributeNamed:(nonnull NSString *)key NS_SWIFT_NAME(setValue(_:forAttribute:)) NS_DEPRECATED(10_12, 10_12, 10_0, 10_0);

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

- (void)removeChildrenInArray:(NSArray<SKNode*> *)nodes;
- (void)removeAllChildren;

- (void)removeFromParent;
- (void)moveToParent:(SKNode *)parent API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

- (nullable SKNode *)childNodeWithName:(NSString *)name;

- (void)enumerateChildNodesWithName:(NSString *)name usingBlock:(void (^)(SKNode *node, BOOL *stop))block;

/**
 * Simplified shorthand for enumerateChildNodesWithName that returns an array of the matching nodes.
 * This allows subscripting of the form:
 *      NSArray *childrenMatchingName = node[@"name"]
 *
 * or even complex like:
 *      NSArray *siblingsBeginningWithA = node[@"../a*"]
 *
 * @param name An Xpath style path that can include simple regular expressions for matching node names.
 * @see enumerateChildNodesWithName:usingBlock:
 */
- (NSArray<SKNode*> *)objectForKeyedSubscript:(NSString *)name API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/* Returns true if the specified parent is in this node's chain of parents */

- (BOOL)inParentHierarchy:(SKNode *)parent;

- (void)runAction:(SKAction *)action;
- (void)runAction:(SKAction *)action completion:(void (^)(void))block;
- (void)runAction:(SKAction *)action withKey:(NSString *)key;

- (BOOL)hasActions;
- (nullable SKAction *)actionForKey:(NSString *)key;

- (void)removeActionForKey:(NSString *)key;
- (void)removeAllActions;

- (BOOL)containsPoint:(CGPoint)p;

/**Returns the node itself or a child node at the point given.
 * If the receiver is returned there is no child node at the given point.
 * @return a child node or self at the given location.
 */
- (SKNode *)nodeAtPoint:(CGPoint)p;

- (NSArray<SKNode*> *)nodesAtPoint:(CGPoint)p;

- (CGPoint)convertPoint:(CGPoint)point fromNode:(SKNode *)node;
- (CGPoint)convertPoint:(CGPoint)point toNode:(SKNode *)node;

/* Returns true if the bounds of this node intersects with the transformed bounds of the other node, otherwise false */

- (BOOL)intersectsNode:(SKNode *)node;

/* Returns true if this node has equivalent content to the other object, otherwise false */

- (BOOL)isEqualToNode:(SKNode *)node;

@end


/**
 Provided for easy transformation of UITouches coordinates to SKNode coordinates should you choose to handle touch events natively.
 */
#if TARGET_OS_IPHONE
#if __has_include(<UIKit/UITouch.h>)
//Allow conversion of UITouch coordinates to scene-space
@interface UITouch (SKNodeTouches)
- (CGPoint)locationInNode:(SKNode *)node;
- (CGPoint)previousLocationInNode:(SKNode *)node;
@end
#endif
#else
@interface NSEvent (SKNodeEvent)
- (CGPoint)locationInNode:(SKNode *)node;
@end
#endif

NS_ASSUME_NONNULL_END
