//
//  GKGraph.h
//  GameLogic
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameplayKit.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A node in a directed graph. Edges are directed and can have variable costs.
 */
GK_BASE_AVAILABILITY @interface GKGraphNode : NSObject

/**
 * List of other graph nodes that this node has an edge leading to.
 */
@property (nonatomic,readonly) NSArray<GKGraphNode *> *connectedNodes;

/**
 * Add a connection to a group of other nodes indicating those nodes can be reached from this node.
 * A new connection is not created if it already exists.
 * @param array of nodes that are end points for their respective connections
 * @param bidirectional should a connection also be added connecting the destination node back to this node?
 */
- (void)addConnectionsToNodes:(NSArray<GKGraphNode *> *)nodes bidirectional:(BOOL)bidirectional;

/**
 * Removes connections to a group of other nodes indicating those nodes can no longer be reached from this node.
 * Nothing happens if a particular connection does not exist.
 * @param node the end point of the edge to be removed
  * @param bidirectional should the connection also be added the destination node back to this node also be removed if it exists?
 */
- (void)removeConnectionsToNodes:(NSArray<GKGraphNode *> *)nodes bidirectional:(BOOL)bidirectional;

/**
 * Returns the estimated heuristic cost to reach the indicated node from this node
 * @param the end point of the edge who's cost is to be estimated
 */
- (float)estimatedCostToNode:(GKGraphNode *)node;

/**
 * Returns the actual cost to reach the indicated node from this node
 */
- (float)costToNode:(GKGraphNode *)node;

/**
 * Attempts to find the optimal path between this node and the indicated goal node.
 * If such a path exists, it is returned in start to end order.
 * If it doesn't exist, the array returned will be empty.
 * @param goalNode the goal node of the pathfinding attempt
 */
- (NSArray<__kindof GKGraphNode *> *)findPathToNode:(GKGraphNode*)goalNode;

/**
 * As with findPathToNode: except this node is the goal node and a startNode is specified
 * @param startNode the start node of the pathfinding attempt
 */
- (NSArray<__kindof GKGraphNode *> *)findPathFromNode:(GKGraphNode*)startNode;

@end


/**
 * GKGraphNode coupled with a 2D position
 */
GK_BASE_AVAILABILITY @interface GKGraphNode2D : GKGraphNode

@property (nonatomic) vector_float2 position;

+ (instancetype)nodeWithPoint:(vector_float2)point;
- (instancetype)initWithPoint:(vector_float2)point NS_DESIGNATED_INITIALIZER;

@end


/**
 * GKGraphNode coupled with a position on a 2D grid
 */
GK_BASE_AVAILABILITY @interface GKGridGraphNode : GKGraphNode

@property (nonatomic) vector_int2 gridPosition;

+ (instancetype)nodeWithGridPosition:(vector_int2)gridPosition;
- (instancetype)initWithGridPosition:(vector_int2)gridPosition NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
