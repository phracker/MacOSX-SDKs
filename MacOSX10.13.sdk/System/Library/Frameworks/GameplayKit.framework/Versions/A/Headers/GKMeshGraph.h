//
//  GKMeshGraph.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GKGraph.h>
#import <GameplayKit/GKPrimitives.h>

NS_ASSUME_NONNULL_BEGIN

/** Adjusts how graph nodes are created when you triangulate a GKMeshGrapk
 
 @enum GKMeshGraphTriangulationModeVertices Graph nodes will be made at all triangle vertices
 @enum GKMeshGraphTriangulationModeCenters Graph nodes will be made at all triangle centers
 @enum GKMeshGraphTriangulationModeEdgeMidpoints Graph nodes will be made at midpoint of all triangle edges
 */
typedef NS_OPTIONS(NSUInteger, GKMeshGraphTriangulationMode) {
    GKMeshGraphTriangulationModeVertices = 1 << 0,
    GKMeshGraphTriangulationModeCenters = 1 << 1,
    GKMeshGraphTriangulationModeEdgeMidpoints = 1 << 2
};

/**
 * A collection of GKGraphNodes that are governed by a mesh formed by the space between a set of GKPolygonObstacles
 */
GK_BASE_AVAILABILITY_2 @interface GKMeshGraph<NodeType : GKGraphNode2D*> : GKGraph

/**
 *  Array of the extruded obstacles currently represented by this graph
 */
@property (nonatomic, readonly, nonnull) NSArray<GKPolygonObstacle *> *obstacles;

/**
 * The distance by which all obstacles are extruded.
 * This is most commonly the spatial bounding radius of a potential traveler on this path 
 */
@property (nonatomic, readonly) float bufferRadius;

/**
 * Specifies how graph nodes are generated when you triangulate this graph.
 * You can combine triangulation modes using the | (OR) operator
 *
 * @see GKMeshGraphTriangulationMode
 */
@property (nonatomic) GKMeshGraphTriangulationMode triangulationMode;

/**
 * The number of triangles currently in this mesh graph
 */
@property (nonatomic, readonly) NSUInteger triangleCount;

/**
 * Creates a graph with a given buffer radius
 * Obstacles can then be added to this graph prior to a call to [GKMeshGraph trianglulate]
 * @param bufferRadius the circular radius of a potential agent that will navigate this graph.  Obstacles are extruded by this amount to create the graph.  Must be positive.  Negative values are clipped to 0.0f
 * @param minCoordinate the minimum coordinate (lower left corner) of the bounding box that will encapsulate this graph.  No obstacles should fall outside this bounding box.
 * @param maxCoordinate the maximum coordinate (upper right corner) of the bounding box that will encapsulate this graph.  No obstacles should fall outside this bounding box.
 * @param nodeClass the class of the nodes that this graph should create.  Must descend from GKGraphNode2D
 */
+ (instancetype)graphWithBufferRadius:(float)bufferRadius minCoordinate:(vector_float2)min maxCoordinate:(vector_float2)max nodeClass:(Class)nodeClass;
- (instancetype)initWithBufferRadius:(float)bufferRadius minCoordinate:(vector_float2)min maxCoordinate:(vector_float2)max nodeClass:(Class)nodeClass;

/**
 * Same as [GKMeshGraph graphWithBufferRadius:minCoordinate:maxCoordinate:nodeClass:] where custom node class defaults to GKGraphNode2D
 */
+ (instancetype)graphWithBufferRadius:(float)bufferRadius minCoordinate:(vector_float2)min maxCoordinate:(vector_float2)max;
- (instancetype)initWithBufferRadius:(float)bufferRadius minCoordinate:(vector_float2)min maxCoordinate:(vector_float2)max;

/**
 * Adds obstacles to this mesh graph.  Only reflected after the next triangulate call.
 */
-(void)addObstacles:(NSArray<GKPolygonObstacle*>*)obstacles;

/**
 * Removes obstacles from this graph.  Only reflected after the next triangulate call.
 */
-(void)removeObstacles:(NSArray<GKPolygonObstacle*>*)obstacles;

/**
 * Connects the node to this graph by inserting it into an existing triangle and making the appropriate connections
 * Node must be in the space defined by the min and max coordinates of this graph.
 * @param node the node to connect
 */
- (void)connectNodeUsingObstacles:(NodeType)node;

/**
 * Generates a new triangle mesh for the given obstacles.  
 * This should be called after some number of calls to addObstacle
 * The negative space between all input obstacles are triangulated to create a mesh
 * This mesh is turned into a set of connected graph nodes based on
 */
-(void)triangulate;


/**
 * Returns the triangle at the given index
 * @see numTriangles
 * @param index the index of the triangle to be returned
 * @return the triangle at the given index
 */
-(GKTriangle)triangleAtIndex:(NSUInteger)index;

/**
 * Returns the class of the specified generic index
 */
- (nonnull Class)classForGenericArgumentAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
