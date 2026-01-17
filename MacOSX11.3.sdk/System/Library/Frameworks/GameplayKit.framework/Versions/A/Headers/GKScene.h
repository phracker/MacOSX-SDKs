//
//  GKScene.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

@class GKEntity, GKGraph;

NS_ASSUME_NONNULL_BEGIN

/**
 Protocol that specifies the type of objects that can be used as root nodes of a GKScene.
 
 @see GKScene.rootNode
 */
@protocol GKSceneRootNodeType <NSObject>

@end

/**
 A scene stores and handles loading of data related to a particular scene.
 */
GK_BASE_AVAILABILITY_2 @interface GKScene : NSObject <NSCopying, NSSecureCoding>

/**
 Loads a scene from a file contained within the bundle.
 */
+ (nullable instancetype)sceneWithFileNamed:(NSString *)filename;

/**
 Loads a scene from a file contained within the bundle and link with the specified rootNode.
 */
+ (nullable instancetype)sceneWithFileNamed:(NSString *)filename rootNode:(id <GKSceneRootNodeType>) rootNode;

/**
 The entities of this scene.
 */
@property (nonatomic, readonly) NSArray<GKEntity *> *entities;

/**
 The root node for the scene.
 
 @see GKSceneRootNodeType
 */
@property (nonatomic, nullable) id <GKSceneRootNodeType> rootNode;

/**
 The navigational graphs of this scene.
 */
@property (nonatomic, readonly) NSDictionary<NSString*, GKGraph *> *graphs;

/**
 Adds an entity to the scene's list of entities.
 
 @param entity the entity to add.
 */
- (void)addEntity:(GKEntity *)entity;

/**
 Removes an entity from the scene's list of entities.
 
 @param entity the entity to remove.
 */
- (void)removeEntity:(GKEntity *)entity;

/**
 Adds a graph to the scene's list of graphs.
 
 @param graph the graph to add.
 */
- (void)addGraph:(GKGraph *)graph name:(NSString*)name;

/**
 Removes a graph from the scene's list of graphs.
 
 @param name the name of the corresponding graph as added via addGraph:
 */
- (void)removeGraph:(NSString*)name;

@end

NS_ASSUME_NONNULL_END
