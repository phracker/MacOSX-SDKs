//
//  GKSKNodeComponent.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GKComponent.h>
#import <GameplayKit/GKAgent.h>

NS_ASSUME_NONNULL_BEGIN

@class SKNode;

/**
 A component that encapsulates a SpriteKit node.
 */
GK_BASE_AVAILABILITY_2 @interface GKSKNodeComponent : GKComponent <GKAgentDelegate>

/**
 * Creates a component that encapsulate the given SpriteKit node. When the component is 
 * added to an entity, the SKNode's entity property will be set.
 *
 * @param node Node to associate with the component.
 * @see SKNode.entity
 */
+ (instancetype)componentWithNode:(SKNode *)node;

/**
 * Initializes component to encapsulate the given SpriteKit node. When the component is
 * added to an entity, the SKNode's entity property will be set.
 *
 * @param node Node to associate with the component.
 * @see SKNode.entity
 */
- (instancetype)initWithNode:(SKNode *)node;

/**
 * The SpriteKit node this component encapsulates.
 */
@property (nonatomic, strong) SKNode *node;

@end

NS_ASSUME_NONNULL_END
