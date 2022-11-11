//
//  GKQuadTree.h
//  GKQuadTreeTest
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>
#import <GameplayKit/GKPrimitives.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The individual node(s) that make up a GKQuadtree.
 * Used as a hint for faster removal via [GKQuadtree removeData:WithNode:]
 */
GK_BASE_AVAILABILITY_2 @interface GKQuadtreeNode : NSObject

/* The quad associated with this quad tree node */
@property (nonatomic, readonly) GKQuad quad;

@end


/**
 * A tree data structure where each level has 4 children that subdivide a given space into the four quadrants.
 * Stores arbitrary NSObject data via points and quads.
 */
GK_BASE_AVAILABILITY_2 @interface GKQuadtree <ElementType : NSObject*>: NSObject

/**
 * Creates a quadtree with a bounding quad and minimum allowed cell size
 *
 * @param quad the quad that specifies of the bounds of this quadtree. Elements must only be within these bounds.
 * @param minCellSize the minimum allowed cell size.  The quadtree will not create quadrants that have a width or height smaller than this size.
 */
+(instancetype)quadtreeWithBoundingQuad:(GKQuad)quad minimumCellSize:(float)minCellSize;
-(instancetype)initWithBoundingQuad:(GKQuad)quad minimumCellSize:(float)minCellSize NS_DESIGNATED_INITIALIZER;

/**
 * Adds an NSObject to this quadtree with a given point.
 * This data will always reside in the leaf node its point is in.
 *
 * @param element the element to store
 * @param point the point associated with the element you want to store
 * @return the quadtree node the element was added to
 */
-(GKQuadtreeNode*)addElement:(ElementType)element withPoint:(vector_float2)point;

/**
 * Adds an NSObject to this quadtree with a given quad.
 * This data will reside in the lowest node that its quad fits in completely.
 *
 * @param element the element to store
 * @param quad the quad associated with the element you want to store
 * @return the quad tree node the element was added to
 */
-(GKQuadtreeNode*)addElement:(ElementType)element withQuad:(GKQuad)quad;

/**
 * Returns all of the elements in the quadtree node this point would be placed in
 *
 * @param point the point to query
 * @return an NSArray of all the data found at the quad tree node this point would be placed in
 */
-(NSArray<ElementType>*)elementsAtPoint:(vector_float2)point;

/**
 * Returns all of the elements that resides in quad tree nodes which intersect the given quad
 *
 * @param quad the quad you want to test
 * @return an NSArray of all the elements in all of the nodes that intersect the given quad
 *
 */
-(NSArray<ElementType>*)elementsInQuad:(GKQuad)quad;

/**
 * Removes the given NSObject from this quad tree.
 * Note that this is an exhaustive search and is slow.
 * Cache the relevant GKQuadTreeNode and use removeElement:WithNode: for better performance.
 *
 * @param element the data to be removed
 * @return returns YES if the data was removed, NO otherwise
 */
-(BOOL)removeElement:(ElementType)element;

/**
 * Removes the given NSObject from the given quadtree node
 * Note that this is not an exhaustive search and is faster than removeData:
 *
 * @param data the data to be removed
 * @param node the node in which this data resides
 * @return returns YES if the data was removed, NO otherwise
 */
-(BOOL)removeElement:(ElementType)data withNode:(GKQuadtreeNode*)node;

@end

NS_ASSUME_NONNULL_END
