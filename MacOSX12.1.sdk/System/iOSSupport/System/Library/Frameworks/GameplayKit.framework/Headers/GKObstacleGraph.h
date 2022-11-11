//
//  GKObstacleGraph.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <GameplayKit/GKGraph.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A collection of GKGraphNodes that are governed by a set of extruded GKPolygonObstacles
 */
GK_BASE_AVAILABILITY @interface GKObstacleGraph<NodeType : GKGraphNode2D*> : GKGraph

/*
 * Array of the extruded obstacles currently represented by this graph
 */
@property (nonatomic, readonly, nonnull) NSArray<GKPolygonObstacle *> *obstacles;

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
 * Creates an optimal bidirectional graph based on a list of obstacles.
 * Each vertex of each obstacle is extruded and a connection is made between each vertex that does not intersect an obstacle
 * Guaranteed not to have any edges which intersect obstacles.
 * Same effect as [[GKObstacleGraph alloc] init], setting bufferRadius, and then calling addObstacles.
 * @param obstacles a list of obstacles to create the graph from
 * @param bufferRadius the circular radius of a potential agent that will navigate this graph.  Obstacles are extruded by this amount to create the graph.  Must be positive.  Negative values are clipped to 0.0f
 * @param nodeClass the class of the nodes that this graph should create.  Must descend from GKGraphNode2D
 */
+ (instancetype)graphWithObstacles:(NSArray<GKPolygonObstacle *> *)obstacles bufferRadius:(float)bufferRadius nodeClass:(Class)nodeClass;
- (instancetype)initWithObstacles:(NSArray<GKPolygonObstacle *> *)obstacles  bufferRadius:(float)bufferRadius nodeClass:(Class)nodeClass;


/**
 * Connects the node to this graph by testing edge intersection with existing obstacles.
 * Same behavior as if this node had been present during initWithObstacles.
 * @param node the node to connect
 */
- (void)connectNodeUsingObstacles:(NodeType)node;

/**
 * Same behavior as connectNodeUsingObstacles: except you can optionally ignore certain obstacles from being tested for intersection.
 */
- (void)connectNodeUsingObstacles:(NodeType)node ignoringObstacles:(NSArray<GKPolygonObstacle *> *)obstaclesToIgnore;

/**
 * Same behavior as connectNodeUsingObstacles: except you can optionally ignore the bounding radius of certain obstacles from being tested for intersection
 */
- (void)connectNodeUsingObstacles:(NodeType)node ignoringBufferRadiusOfObstacles:(NSArray<GKPolygonObstacle *> *)obstaclesBufferRadiusToIgnore;

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
-(NSArray<NodeType> *)nodesForObstacle:(GKPolygonObstacle *)obstacle;

/**
 * Marks a connection as "locked", preventing this connection from being destroyed when you add obstacles that would intersect it
 * @param startNode startNode of the connection to lock
 * @param endNode endNode of the connection to lock
 */
- (void)lockConnectionFromNode:(NodeType)startNode toNode:(NodeType)endNode;

/**
 * "Unlocks" a connection, removing its protection from being destroyed when you add obstacles that would intersect it
 * @param startNode startNode of the connection to unlock
 * @param endNode endNode of the connection to unlock
 * @see lockConnection
 */
- (void)unlockConnectionFromNode:(NodeType)startNode toNode:(NodeType)endNode;

/**
 * Query if a given connection is locked
 * @param startNode startNode of the connection to query
 * @param endNode endNode of the connection to query
 * @see lockConnection
 * @see unlockConnection
 * @return YES if the connection was locked with lockConnection, NO if it was never locked or was unlocked via unlockConnection
 */
- (BOOL)isConnectionLockedFromNode:(NodeType)startNode toNode:(NodeType)endNode;

/**
 * Returns the class of the specified generic index
 */
- (nonnull Class)classForGenericArgumentAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
