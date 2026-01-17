//
//  GKOctree.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>
#import <GameplayKit/GKPrimitives.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The individual node(s) that make up a GKOctree.
 * Used as a hint for faster removal via [GKOctree removeData:WithNode:]
 */
GK_BASE_AVAILABILITY_2 @interface GKOctreeNode : NSObject

/* The box associated with this octree node*/
@property (readonly) struct GKBox box;

@end


/**
 * A tree data structure where each level has 8 children that subdivide a given space into the eight octants.
 * Stores arbitrary NSObject elements via points and boxes.
 */
GK_BASE_AVAILABILITY_2 @interface GKOctree <ElementType: NSObject*> : NSObject

/**
 * Creates a octree with a given bounding box and minimum allowed cell size
 *
 * @param box the bounding box of this octree.  all elements bounding boxes must be within this space.
 * @param minCellSize the minimum allowed cell size.  The octree will not create octants that have a width,height or depth smaller than this size.
 */
+(instancetype)octreeWithBoundingBox:(GKBox)box minimumCellSize:(float)minCellSize;
-(instancetype)initWithBoundingBox:(GKBox)box minimumCellSize:(float)minCellSize;

/**
 * Adds an NSObject to this octree with a given point.
 * This element will always reside in the leaf node its point is in.
 *
 * @param element the element to be stored
 * @param point the point associated with the element you want to store
 * @return the node the element was added to
 */
-(GKOctreeNode*)addElement:(ElementType)element withPoint:(vector_float3)point;

/**
 * Adds an NSObject to this octtree with a given axis-aligned box
 * This element will reside in the lowest node that it's box fits in completely.
 *
 * @param element the element to be stored
 * @param box the box associated with the element to be stored
 * @return the node that the element was added to
 */
-(GKOctreeNode*)addElement:(ElementType)element withBox:(GKBox)box;

/**
 * Returns all of the elements in the node this point would be placed in
 *
 * @param point the point to query
 * @return an NSArray of all the element found at the node this point would be placed in
 */
-(NSArray<ElementType>*)elementsAtPoint:(vector_float3)point;

/**
 * Returns all of the elements that resides in nodes which intersect the given box
 *
 * @param box the box tha specifies which elements you would like to retrieve
 * @return an NSArray of all the elements in all of the nodes that intersect the given box
 *
 */
-(NSArray<ElementType>*)elementsInBox:(GKBox)box;

/**
 * Removes the given NSObject from this octree
 * Note that this is an exhaustive search and is can be slow for larger trees.
 * Cache the relevant GKOctreeNode and use removeElement:WithNode: for better performance.
 *
 * @param element the element to be removed
 * @return returns YES if the data was removed, NO otherwise
 */
-(BOOL)removeElement:(ElementType)element;

/**
 * Removes the given NSObject from the given node
 * Note that this is not an exhaustive search and is faster than removeData:
 *
 * @param element the element to be removed
 * @param node the node in which this data resides
 * @return returns YES if the element was removed, NO otherwise
 */
-(BOOL)removeElement:(ElementType)element withNode:(GKOctreeNode*)node;

@end

NS_ASSUME_NONNULL_END
