//
//  GKGridGraph.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#include <GameplayKit/GKGraph.h>

NS_ASSUME_NONNULL_BEGIN


@class GKGridGraphNode;

/*
 * A collection of GKGraphNodes that are governed by a 2D Cartesian grid
 */
GK_BASE_AVAILABILITY @interface GKGridGraph<NodeType : GKGridGraphNode *>  : GKGraph

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
 * @param position starting position in the grid
 * @param width how wide the grid will be; the grid will continue along the positive X axis from the starting x value
 * @param height how high the grid will be; the grid will continue along the positive Y axis from the starting y value
 * @param diagonalsAllowed should diagonal connections between nodes be made?  If not, only cardinal directions will be connected.
 */
+ (instancetype)graphFromGridStartingAt:(vector_int2)position width:(int)width height:(int)height diagonalsAllowed:(BOOL)diagonalsAllowed;
- (instancetype)initFromGridStartingAt:(vector_int2)position width:(int)width height:(int)height diagonalsAllowed:(BOOL)diagonalsAllowed;

/**
 * Creates a bidirectional graph connecting all of the points on a 2D grid
 * @param position starting position in the grid
 * @param width how wide the grid will be; the grid will continue along the positive X axis from the starting x value
 * @param height how high the grid will be; the grid will continue along the positive Y axis from the starting y value
 * @param diagonalsAllowed should diagonal connections between nodes be made?  If not, only cardinal directions will be connected.
 * @param nodeClass the class of the nodes that this graph should create.  Must descend from GKGridGraphNode
 */
+ (instancetype)graphFromGridStartingAt:(vector_int2)position width:(int)width height:(int)height diagonalsAllowed:(BOOL)diagonalsAllowed nodeClass:(Class)nodeClass;
- (instancetype)initFromGridStartingAt:(vector_int2)position width:(int)width height:(int)height diagonalsAllowed:(BOOL)diagonalsAllowed nodeClass:(Class)nodeClass;

/**
 * Returns the GKGridGraphNode at the indicated X and Y coordinate
 * Returns nil if it is outside the bounds of minCoordinates and maxCoordinates
 * @param position starting position in the grid
 */
- (nullable NodeType)nodeAtGridPosition:(vector_int2)position;

/**
 * Connects the given GKGridGraphNode to this graph by connecting it to it's adjacent nodes on the grid
 * Input node must have coordinates within the rectangle specified by minCoordinates and maxCoordinates
 * @param node the node to be connected
 */
- (void)connectNodeToAdjacentNodes:(GKGridGraphNode *)node;

/**
 * Returns the class of the specified generic index
 */
- (nonnull Class)classForGenericArgumentAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
