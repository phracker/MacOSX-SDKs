//
//  GKPath.h
//  GameLogic
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import "GameplayKitBase.h"
#import <Foundation/Foundation.h>
#import <simd/simd.h>

@class GKGraphNode2D;

NS_ASSUME_NONNULL_BEGIN

/**
 * Represents a simple polygonal chain in 2D space.
 * Followable by GKAgent's steering functions.
 */
NS_CLASS_AVAILABLE(10_11, 9_0) @interface GKPath : NSObject

/**
 * Radius of the pathway.  Defines a spatial area that the path occupies.
 * This can be though of as the union between rectangles between all points, and circles at each point
 */
@property (nonatomic, assign) float radius;

/**
 * Does this path loop back on itself, creating a cycle?
 */
@property (nonatomic, assign, getter=isCyclical) BOOL cyclical;

/**
 * Number of points in this path
 */
@property (readonly) NSUInteger numPoints;

+ (instancetype)pathWithPoints:(vector_float2 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical;
- (instancetype)initWithPoints:(vector_float2 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical NS_DESIGNATED_INITIALIZER;

/**
 * Creates a path from an array of GKGraphNode2D (often a result of pathfinding)
 * Cyclical is set to NO
 * @param graphNodes an array of graph nodes to make a path from
 * @param radius radius of the path to create
 * @see GKGraphNode
 */
+ (instancetype)pathWithGraphNodes:(NSArray<GKGraphNode2D *> *)graphNodes radius:(float)radius;
- (instancetype)initWithGraphNodes:(NSArray<GKGraphNode2D *> *)graphNodes radius:(float)radius;

/**
 * Returns the point at the given index
 */
-(vector_float2)pointAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END

