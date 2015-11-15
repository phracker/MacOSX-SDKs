//
//  GKGraph.m
//  GameLogic
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import "GameplayKit.h"

NS_ASSUME_NONNULL_BEGIN

@class GKPolygonObstacle, GKGraphNode, GKGraphNode2D, GKGridGraphNode;

/**
 * Representation of a directed graph of GKGraphNodes
 */
GK_BASE_AVAILABILITY @interface GKGraph : NSObject

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


/**
 * A collection of GKGraphNodes that are governed by a set of extruded GKPolygonObstacles
 */
GK_BASE_AVAILABILITY @interface GKObstacleGraph : GKGraph

/*
 * Array of the extruded obstacles currently represented by this graph
 */
@property (nonatomic, readonly) NSArray<GKPolygonObstacle *> *obstacles;

/*
 * The distance by which all obstacles are extruded.
 * This is most commonly the spatial bounding radius of a potential traveler on this path
 */
@property (nonatomic, readonly) float bufferRadius;

/**
 * Creates an optimal bidirectional graph based on a list of obstacles.
 * Each vertex of each obstacle is extruded and a connection is made between each vertex that does not intersect an obstacle
 * Guaranteed not to have any edges which intersect obstacles.
 * Same effect as [[GKObstacleGraph alloc] init], setting bufferRadius, and then calling addObstacles.
 * @param obstacles a list of obstacles to create the graph from
 * @param bufferRadius the circular radius of a potential agent that will navigate this graph.  Obstacles are extruded by this amount to create the graph.  Must be positive.  Negative values are clipped to 0.0f
 */
+ (instancetype)graphWithObstacles:(NSArray<GKPolygonObstacle *> *)obstacles bufferRadius:(float)bufferRadius;
- (instancetype)initWithObstacles:(NSArray<GKPolygonObstacle *> *)obstacles  bufferRadius:(float)bufferRadius;


/**
 * Connects the node to this graph by testing edge intersection with existing obstacles.
 * Same behavior as if this node had been present during initWithObstacles.
 * @param node the node to connect
 */
- (void)connectNodeUsingObstacles:(GKGraphNode2D *)node;

/**
 * Same behavior as connectNodeUsingObstacles: except you can optionally ignore certain obstacles from being tested for intersection.
 */
- (void)connectNodeUsingObstacles:(GKGraphNode2D *)node ignoringObstacles:(NSArray<GKPolygonObstacle *> *)obstaclesToIgnore;

/**
 * Same behavior as connectNodeUsingObstacles: except you can optionally ignore the bounding radius of certain obstacles from being tested for intersection
 */
- (void)connectNodeUsingObstacles:(GKGraphNode2D *)node ignoringBufferRadiusOfObstacles:(NSArray<GKPolygonObstacle *> *)obstaclesBufferRadiusToIgnore;

/**
 * Adds obstacles to this graph.
 * Obstacle is extruded and graph nodes are generated from its vertices and then connected to this graph
 * Nothing is done if an obstacle is already present in this graph
 * Any existing connections that intersect the new obstacles are destroyed unless they are protected with [GKObstacleGraph lockConnection:]
 * @param obstacles an array of obstacles to be added
 * @see lockConnection
 */
- (void)addObstacles:(NSArray<GKPolygonObstacle *> *)obstacles;

/**
 * Removes obstacles from this graph.
 * All associated graph nodes are removed and their connections are bidirectionally removed.
 * Connections between obstacle nodes that were previously invalidated by any of these obstacles are restored.
 * Nothing is done if an obstacle is already present in this graph
 * @param obstacles an array of obstacles to be removed
 */
- (void)removeObstacles:(NSArray<GKPolygonObstacle *> *) obstacles;

/**
 * Removes all obstacles from this graph.
 */
- (void)removeAllObstacles;

/**
 * Returns an array of the graph nodes associated with a given obstacle
 * @param obstacle the obstacle who's nodes are to be retrieved
 */
-(NSArray<GKGraphNode2D *> *)nodesForObstacle:(GKPolygonObstacle *)obstacle;

/**
 * Marks a connection as "locked", preventing this connection from being destroyed when you add obstacles that would intersect it
 * @param startNode startNode of the connection to lock
 * @param endNode endNode of the connection to lock
 */
- (void)lockConnectionFromNode:(GKGraphNode2D *)startNode toNode:(GKGraphNode2D *)endNode;

/**
 * "Unlocks" a connection, removing its protection from being destroyed when you add obstacles that would intersect it
 * @param startNode startNode of the connection to unlock
 * @param endNode endNode of the connection to unlock
 * @see lockConnection
 */
- (void)unlockConnectionFromNode:(GKGraphNode2D *)startNode toNode:(GKGraphNode2D *)endNode;

/**
 * Query if a given connection is locked
 * @param startNode startNode of the connection to query
 * @param endNode endNode of the connection to query
 * @see lockConnection
 * @see unlockConnection
 * @return YES if the connection was locked with lockConnection, NO if it was never locked or was unlocked via unlockConnection
 */
- (BOOL)isConnectionLockedFromNode:(GKGraphNode2D *)startNode toNode:(GKGraphNode2D *)endNode;

@end



/*
 * A collection of GKGraphNodes that are governed by a 2D Cartesian grid
 */
GK_BASE_AVAILABILITY @interface GKGridGraph : GKGraph

/*
 * The minimum X and Y coordinates of the 2D Cartesian grid this graph represents
 */
@property (nonatomic, readonly) vector_int2 gridOrigin;

/*
 * The width of the 2D Cartesian grid this graph represents
 */
@property (nonatomic, readonly) NSUInteger gridWidth;

/*
 * The height of the 2D Cartesian grid this graph represents
 */
@property (nonatomic, readonly) NSUInteger gridHeight;

/*
 * Returns YES if this grid is also connected via it's diagonal directions rather than only it's cardinal directions
 */
@property (nonatomic, readonly) BOOL diagonalsAllowed;

/**
 * Creates a bidirectional graph connecting all of the points on a 2D grid
 * @param x starting x value of the grid
 * @param y starting y value of the grid
 * @param width how wide the grid will be; the grid will continue along the positive X axis from the starting x value
 * @param height how high the grid will be; the grid will continue along the positive Y axis from the starting y value
 * @param diagonalsAllowed should diagonal connections between nodes be made?  If not, only cardinal directions will be connected.
 */
+ (instancetype)graphFromGridStartingAt:(vector_int2)position width:(int)width height:(int)height diagonalsAllowed:(BOOL)diagonalsAllowed;

/**
 * Creates a bidirectional graph connecting all of the points on a 2D grid
 * @param x starting x value of the grid
 * @param y starting y value of the grid
 * @param width how wide the grid will be; the grid will continue along the positive X axis from the starting x value
 * @param height how high the grid will be; the grid will continue along the positive Y axis from the starting y value
 * @param diagonalsAllowed should diagonal connections between nodes be made?  If not, only cardinal directions will be connected.
 */
- (instancetype)initFromGridStartingAt:(vector_int2)position width:(int)width height:(int)height diagonalsAllowed:(BOOL)diagonalsAllowed;

/**
 * Returns the GKGridGraphNode at the indicated X and Y coordinate
 * Returns nil if it is outside the bounds of minCoordinates and maxCoordinates
 * @param x x coordinate of the grid node to return
 * @param y y coordinate of the grid node to return
 */
- (nullable GKGridGraphNode *)nodeAtGridPosition:(vector_int2)position;

/**
 * Connects the given GKGridGraphNode to this graph by connecting it to it's adjacent nodes on the grid
 * Input node must have coordinates within the rectangle specified by minCoordinates and maxCoordinates
 * @param node the node to be connected
 */
- (void)connectNodeToAdjacentNodes:(GKGridGraphNode *)node;

@end

NS_ASSUME_NONNULL_END
