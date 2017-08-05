//
//  GKGraph.m
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN

@class GKPolygonObstacle, GKGraphNode, GKGraphNode2D, GKGridGraphNode;

/**
 * Representation of a directed graph of GKGraphNodes
 */
GK_BASE_AVAILABILITY @interface GKGraph : NSObject <NSCopying, NSCoding>

/**
 * The list of nodes in this graph
 */
@property (nullable, nonatomic, readonly) NSArray<GKGraphNode *> *nodes;

/**
 * Creates a graph with the provided array of nodes.
 * @params nodes the nodes to create the graph with
 */
+ (instancetype)graphWithNodes:(NSArray<GKGraphNode *> *)nodes;
- (instancetype)initWithNodes:(NSArray<GKGraphNode *> *)nodes;

/**
 * Connects the node to this graph via the lowest cost node to reach in this graph
 * @param node the node to connect
 * @param bidirectional should the connection be bidirectional? Otherwise it is one way connected into the graph
 */
- (void)connectNodeToLowestCostNode:(GKGraphNode *)node bidirectional:(BOOL)bidirectional;

/**
 * Removes nodes from this graph.  
 * All connections starting and/or ending with this node are removed.
 * @param nodes an array of nodes to be removed
 */
- (void)removeNodes:(NSArray<GKGraphNode *> *)nodes;

/**
 * Adds nodes to this graph.  No new connections are added.
 * If the node already exists in this graph this does nothing.
 * @param nodes and array of nodes to be added
 */
- (void)addNodes:(NSArray<GKGraphNode *> *)nodes;

/**
 * Attempts to find the optimal path between the two nodes indicated.
 * If such a path exists, it is returned in start to end order.
 * If it doesn't exist, the array returned will be empty.
 * Asserts if neither of these nodes are in this graph.  Use [GKGraphNode findPathFromNode:] instead.
 * @param startNode node to start pathing from
 * @param toNode goal node of the pathfinding attempt
 */
- (NSArray<__kindof GKGraphNode *> *)findPathFromNode:(GKGraphNode*)startNode toNode:(GKGraphNode*)endNode;

@end

NS_ASSUME_NONNULL_END
