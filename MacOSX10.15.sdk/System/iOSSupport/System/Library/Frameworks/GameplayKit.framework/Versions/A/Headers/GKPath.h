//
//  GKPath.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import "GameplayKitBase.h"
#import <Foundation/Foundation.h>
#import <simd/simd.h>

@class GKGraphNode;

NS_ASSUME_NONNULL_BEGIN

GK_BASE_AVAILABILITY @interface GKPath : NSObject

/**
 * Radius of the pathway.  Defines a spatial area that the path occupies.
 * This can be though of as the union between rectangles between all points, and circles at each point
 */
@property (nonatomic, assign) float radius;

/**
 * Number of points in this path
 */
@property (readonly) NSUInteger numPoints;

/**
 * Does this path loop back on itself, creating a cycle?
 */
@property (nonatomic, assign, getter=isCyclical) BOOL cyclical;

/**
 * Creates a path from an array of points
 * @param points an array of points to make a path from
 * @param radius radius of the path to create
 * @param cyclical is the path a cycle that loops back on itself?
 */
#if (defined(SWIFT_SDK_OVERLAY_GAMEPLAYKIT_EPOCH) && SWIFT_SDK_OVERLAY_GAMEPLAYKIT_EPOCH >= 1)
+ (instancetype)pathWithPoints:(vector_float2 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical NS_REFINED_FOR_SWIFT;
- (instancetype)initWithPoints:(vector_float2 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical NS_REFINED_FOR_SWIFT;
+ (instancetype)pathWithFloat3Points:(vector_float3 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical NS_AVAILABLE(10_12, 10_0) NS_REFINED_FOR_SWIFT;
- (instancetype)initWithFloat3Points:(vector_float3 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical NS_AVAILABLE(10_12, 10_0) NS_REFINED_FOR_SWIFT;
#else
+ (instancetype)pathWithPoints:(vector_float2 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical;
- (instancetype)initWithPoints:(vector_float2 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical;
+ (instancetype)pathWithFloat3Points:(vector_float3 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical NS_AVAILABLE(10_12, 10_0);
- (instancetype)initWithFloat3Points:(vector_float3 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical NS_AVAILABLE(10_12, 10_0);
#endif

/**
 * Creates a path from an array of graph nodes (often a result of pathfinding)
 * Accepts GKGraphNode2D and GKGraphNode3D
 * Cyclical is set to NO
 * @param graphNodes an array of graph nodes to make a path from
 * @param radius radius of the path to create
 * @see GKGraphNode
 */
+ (instancetype)pathWithGraphNodes:(NSArray<GKGraphNode*> *)graphNodes radius:(float)radius;
- (instancetype)initWithGraphNodes:(NSArray<GKGraphNode*> *)graphNodes radius:(float)radius;

/*
 * Returns the 2D point at the given index.  Returns (x,y,0) if the underlying points are (x,y)
 */
-(vector_float2)pointAtIndex:(NSUInteger)index NS_DEPRECATED(10_11, 10_12, 9_0, 10_0);
-(vector_float2)float2AtIndex:(NSUInteger)index NS_AVAILABLE(10_12, 10_0);

/*
 * Returns the 3D point at the given index.  Returns (x,y,0) if the underlying points are (x,y)
 */
-(vector_float3)float3AtIndex:(NSUInteger)index NS_AVAILABLE(10_12, 10_0);

@end

NS_ASSUME_NONNULL_END

