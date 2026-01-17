
/**
 SKWarpGeometry.h
 
 Nodes that conform to the SKWarpable protocol can be warped and animated by defining distortions via a SKWarpGeometry objects.

  @copyright 2016 Apple, Inc. All rights reserved.
 */

#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKAction.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

@class SKTexture, SKShader, SKWarpGeometry, SKWarpGeometryGrid;


SK_EXPORT NS_AVAILABLE(10_12, 10_0) @protocol SKWarpable <NSObject>

/* Warp geometry used to define the distortion */
@property (nonatomic, nullable) SKWarpGeometry *warpGeometry;

/* maximum number of subdivision iterations used to generate the final vertices */
@property (nonatomic) NSInteger subdivisionLevels;

@end




/* Base class for future expansion */
SK_EXPORT NS_AVAILABLE(10_12, 10_0) @interface SKWarpGeometry : NSObject <NSCopying, NSCoding>
@end

SK_EXPORT NS_AVAILABLE(10_12, 10_0) @interface SKWarpGeometryGrid : SKWarpGeometry <NSCoding>

- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/* 1x1 grid with no distortion */
+ (instancetype)grid;

/* grid of the specified dimensions and no distortion */
+ (instancetype)gridWithColumns:(NSInteger)cols
                           rows:(NSInteger)rows;

/*
 Create a grid of the specified dimensions, source and dest positions.
 
 Grid dimensions (cols and rows) refer to the number of faces in each dimension. The
 number of vertices required for a given dimension is equal to (cols + 1) * (rows + 1).
 
 SourcePositions are normalized (0.0 - 1.0) coordinates to determine the source content.
 
 DestPositions are normalized (0.0 - 1.0) positional coordinates with respect to
 the node's native size. Values outside the (0.0-1.0) range are perfectly valid and
 correspond to positions outside of the native undistorted bounds.
 
 Source and dest positions are provided in row-major order staring from the top-left.
 For example the indices for a 2x2 grid would be as follows:
 
 [0]---[1]---[2]
  |     |     |
 [3]---[4]---[5]
  |     |     |
 [6]---[7]---[8]
 
 */
#if (defined(SWIFT_SDK_OVERLAY_SPRITEKIT_EPOCH) && SWIFT_SDK_OVERLAY_SPRITEKIT_EPOCH >= 1)
+ (instancetype)gridWithColumns:(NSInteger)cols
                           rows:(NSInteger)rows
                sourcePositions:(nullable const vector_float2 *)sourcePositions
                  destPositions:(nullable const vector_float2 *)destPositions NS_REFINED_FOR_SWIFT;

/* init with the specified dimensions, source and dest positions. */
- (instancetype)initWithColumns:(NSInteger)cols
                           rows:(NSInteger)rows
                sourcePositions:(nullable const vector_float2 *)sourcePositions
                  destPositions:(nullable const vector_float2 *)destPositions NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;
#else
+ (instancetype)gridWithColumns:(NSInteger)cols
                           rows:(NSInteger)rows
                sourcePositions:(nullable const vector_float2 *)sourcePositions
                  destPositions:(nullable const vector_float2 *)destPositions;

/* init with the specified dimensions, source and dest positions. */
- (instancetype)initWithColumns:(NSInteger)cols
                           rows:(NSInteger)rows
                sourcePositions:(nullable const vector_float2 *)sourcePositions
                  destPositions:(nullable const vector_float2 *)destPositions NS_DESIGNATED_INITIALIZER;
#endif

/* the number of columns in this grid */
@property (nonatomic, readonly) NSInteger numberOfColumns;

/* the number of rows in this grid */
@property (nonatomic, readonly) NSInteger numberOfRows;


/* the total number of (sourcePosition + destPosition) pairs that define this grid.
 For a given dimension this is equal to (numberOfColumns + 1) * (numberOfRows + 1). */
@property (nonatomic, readonly) NSInteger vertexCount;

- (vector_float2)sourcePositionAtIndex:(NSInteger)index;
- (vector_float2)destPositionAtIndex:(NSInteger)index;

#if (defined(SWIFT_SDK_OVERLAY_SPRITEKIT_EPOCH) && SWIFT_SDK_OVERLAY_SPRITEKIT_EPOCH >= 1)
- (instancetype)gridByReplacingSourcePositions:(const vector_float2 *)sourcePositions NS_REFINED_FOR_SWIFT;
- (instancetype)gridByReplacingDestPositions:(const vector_float2 *)destPositions NS_REFINED_FOR_SWIFT;
#else
- (instancetype)gridByReplacingSourcePositions:(const vector_float2 *)sourcePositions;
- (instancetype)gridByReplacingDestPositions:(const vector_float2 *)destPositions;
#endif
@end




@interface SKAction (SKWarpable)

/* Animate from the node's current warpGeometry to a new one over the specified duration.
 
 If the numberOfColumns and numberOfRows match, a smooth interpolation will be performed
 from the node current warp.
 */
+ (nullable SKAction *)warpTo:(SKWarpGeometry *)warp
                     duration:(NSTimeInterval)duration NS_AVAILABLE(10_12, 10_0);

/* Animate through an array of warps
 
 The numberOfColumns and numberOfRows must match for all warps.
 Times are specified in seconds and must be increasing values.
 */
+ (nullable SKAction *)animateWithWarps:(NSArray<SKWarpGeometry *> *)warps
                                  times:(NSArray<NSNumber *> *)times NS_AVAILABLE(10_12, 10_0);

/* Animate through an array of warps
 
 The numberOfColumns and numberOfRows must match for all warps.
 Times are specified in seconds and must be increasing values.
 Optionally restore the original node's warpGeometry from before the action.
 */
+ (nullable SKAction *)animateWithWarps:(NSArray<SKWarpGeometry *> *)warps
                                  times:(NSArray<NSNumber *> *)times
                                restore:(BOOL)restore NS_AVAILABLE(10_12, 10_0);
@end

NS_ASSUME_NONNULL_END
