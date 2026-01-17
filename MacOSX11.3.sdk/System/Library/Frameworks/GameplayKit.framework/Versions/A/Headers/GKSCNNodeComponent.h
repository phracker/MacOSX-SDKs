//
//  GKSCNNodeComponent.h
//  GameplayKit
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <GameplayKit/GKComponent.h>
#import <GameplayKit/GKAgent.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;

/**
 A component that encapsulates a SceneKit node.
 */
GK_BASE_AVAILABILITY_3 @interface GKSCNNodeComponent : GKComponent <GKAgentDelegate>

/**
 * Creates a component that encapsulate the given SceneKit node. When the component is
 * added to an entity, the SCNNode's entity property will be set.
 *
 * @param node Node to associate with the component.
 * @see SCNNode.entity
 */
+ (instancetype)componentWithNode:(SCNNode *)node;

/**
 * Initializes component to encapsulate the given SceneKit node. When the component is
 * added to an entity, the SCNNode's entity property will be set.
 *
 * @param node Node to associate with the component.
 * @see SCNNode.entity
 */
- (instancetype)initWithNode:(SCNNode *)node;

/**
 * The SceneKit node this component encapsulates.
 */
@property (nonatomic, readonly) SCNNode *node;

@end

NS_ASSUME_NONNULL_END
