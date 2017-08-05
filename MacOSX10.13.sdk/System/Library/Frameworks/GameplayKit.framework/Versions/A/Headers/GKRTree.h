//
//  GKRTree.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>
#import <GameplayKit/GKPrimitives.h>

NS_ASSUME_NONNULL_BEGIN

/** Used to adjust the way in which RTree nodes are split when they grow too large.
 
 @enum GKRTreeSplitStrategyHalve Specifies that nodes should be split in half based on insert order.
 @enum GKRTreeSplitStrategyLinear Specifies that nodes should be split along the best dividing axis.
 @enum GKRTreeSplitStrategyQuadratic Specifies that nodes should be split into groups with the least area.
 @enum GKRTreeSplitStrategyReduceOverlap Specifies that nodes should be split as to reduce overlap.
 */
typedef NS_ENUM(NSInteger, GKRTreeSplitStrategy) {
    GKRTreeSplitStrategyHalve = 0,
    GKRTreeSplitStrategyLinear = 1,
    GKRTreeSplitStrategyQuadratic = 2,
    GKRTreeSplitStrategyReduceOverlap = 3
};


/**
 * An R-tree is a data structure that partitions axis aligned bounding rectangles into groups spatially.
 * When a group goes to large, it is split according to its split strategy into two new groups.
 * Fast queries can be made on these partition bounding rectangles.
 */
GK_BASE_AVAILABILITY_2 @interface GKRTree <ElementType : NSObject*>: NSObject

/**
 * Amount of array items to reserve before a query.
 * This improves query performance at the cost of memory
 */
@property NSUInteger queryReserve;

/**
 * Creates an RTree with a given maximum number of children per node.  Nodes that grow beyond this number of children will be split.
 *
 * @param maxNumberOfChildren the maximum number of children per node before splitting
 */
+(instancetype)treeWithMaxNumberOfChildren:(NSUInteger)maxNumberOfChildren;
-(instancetype)initWithMaxNumberOfChildren:(NSUInteger)maxNumberOfChildren NS_DESIGNATED_INITIALIZER;

/**
 * Adds an element with the specified bounding rect to this RTree.  The supplied splitting strategy is used if the node this element would be added to needs to be split.
 *
 * @param element the element to be added
 * @param boundingRectMin the min point (lower left) on the bounding rect of the element to be added
 * @param boundingRectMax the min point (upper right) on the bounding rect of the element to be added
 * @param splitStrategy the splitting strategy to be used if the node this element would be added to needs to be split
 */
-(void)addElement:(ElementType)element boundingRectMin:(vector_float2)boundingRectMin boundingRectMax:(vector_float2)boundingRectMax splitStrategy:(GKRTreeSplitStrategy)splitStrategy;

/**
 * Removes an element with the specified bounding rect from this RTree.
 *
 * @param element the element to be removed
 * @param boundingRectMin the min point (lower left) on the bounding rect of the element to be removed
 * @param boundingRectMax the min point (upper right) on the bounding rect of the element to be removed
 */
-(void)removeElement:(ElementType)element boundingRectMin:(vector_float2)boundingRectMin boundingRectMax:(vector_float2)boundingRectMax;

/**
 * Queries all the elements that are in this RTree within the given bounding rect.
 *
 * @param min the min point (lower left) of the rect to query
 * @param rectMax the max point (upper right) of the rect to query
 *
 * @return an NSArray of all of the elements that fall within the query rect
 */
-(NSArray<ElementType>*)elementsInBoundingRectMin:(vector_float2)rectMin rectMax:(vector_float2)rectMax;

@end

NS_ASSUME_NONNULL_END
