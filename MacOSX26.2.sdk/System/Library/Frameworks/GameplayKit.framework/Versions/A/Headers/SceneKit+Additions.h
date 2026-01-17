/**
 @header
 
 
 SceneKit framework category additions related to GameplayKit integration.
 
 
 @copyright 2017 Apple, Inc. All rights reserve.
 
 */

#import <SceneKit/SceneKit.h>

#import <GameplayKit/GKEntity.h>
#import <GameplayKit/GKScene.h>

NS_ASSUME_NONNULL_BEGIN

@interface SCNNode (GameplayKit)

/**
 * The GKEntity associated with the node via a GKSCNNodeComponent.
 *
 * @see GKEntity
 */
@property (nonatomic, weak) GKEntity *entity NS_AVAILABLE(10_13, 11_0);

@end

/**
 * Adds conformance to GKSceneRootNodeType for usage as rootNode of GKScene 
 */
@interface SCNScene (GameplayKit) <GKSceneRootNodeType>

@end

NS_ASSUME_NONNULL_END
