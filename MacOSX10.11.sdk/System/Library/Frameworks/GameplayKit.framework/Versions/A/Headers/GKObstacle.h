//
//  GKObstacle.h
//  GameLogic
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN


/**
 * Represents an impassible area in 2D space.
 * Able to be avoided by GKAgent's steering functions
 * GKGraph can generate navigation graphs from a list of obstacles
 */
GK_BASE_AVAILABILITY @interface GKObstacle : NSObject

@end


/**
 * An obstacle with an impassible radius
 */
GK_BASE_AVAILABILITY @interface GKCircleObstacle : GKObstacle

/**
 * Radius of the impassible circle
 */
@property (nonatomic, assign) float radius;

/**
 * Position of the center of the circle in 2D space.
 */
@property (nonatomic, assign) vector_float2 position;

+ (instancetype)obstacleWithRadius:(float)radius;
- (instancetype)initWithRadius:(float)radius NS_DESIGNATED_INITIALIZER;

@end


/**
 * An obstacle with an impassible closed polygon
 */
GK_BASE_AVAILABILITY @interface GKPolygonObstacle : GKObstacle

/**
 * Number of vertices on this polygon
 */
@property (nonatomic,readonly) NSUInteger vertexCount;

/**
 * Creates a polygon obstacle with an array of points.
 * @param points array of points in counter-clockwise order that are the vertices of a convex polygon
 * @param numPoints the number of points in the array
 */
+ (instancetype)obstacleWithPoints:(vector_float2 *)points count:(size_t)numPoints;
- (instancetype)initWithPoints:(vector_float2 *)points count:(size_t)numPoints NS_DESIGNATED_INITIALIZER;;

/**
 * Returns the vertex at the indicated index
 * @param index index of the vertex to retrieve
 */
- (vector_float2)vertexAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END

