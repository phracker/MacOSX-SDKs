//
//  MDLVoxelArray.h
// @framework ModelIO
//
// @copyright © 2015 Apple Inc. All rights reserved.
//

/*!
 @header MDLVoxelArray.h
 @framework ModelIO
 @abstract Structures for describing volumetric data obtained from 3d assetsb2
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLMeshBuffer.h>
#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

@class MDLAsset;
@class MDLMesh;

/**
 MDLVoxelIndex is a four component voxel index.
 @discussion The index's x, y, and z components correspond to the voxel grid's
             x, y, and z indices. The w component corresponds to the voxel grid shell level.
             A shell level of zero corresponds to a voxel on the surface of an object.
             A positive shell index corresponds to a shell on the exterior of the object,
             and a negative index corresponds to a shell on the interior. A shell index of
             one is immediately adjacent to the zero shell, two is immediately adjacent 
             one, and so on.
 */
typedef vector_int4 MDLVoxelIndex;

/**
 MDLVoxelIndexExtent is the index space bounds of the voxel grid.
 */
typedef struct {
    MDLVoxelIndex minimumExtent;
    MDLVoxelIndex maximumExtent;
} MDLVoxelIndexExtent;

/**
 @class MDLVoxelArray
 @summary Voxel data represented on a three dimensional grid. Voxel data can
          include voxels considered to be on the surface of an object, and a 
          series of shells on the outside and inside of the surface.
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLVoxelArray : NSObject

/**
 Initialize a voxel grid from an MDLAsset
 @param divisions The number of divisions to divide the vertical extent of the 
        model by.
 @param interiorShells The number of shells to compute inside the surface shell
 @param exteriorShells The number of shells to compute outside the surface shell
 */
- (instancetype)initWithAsset:(MDLAsset*)asset
                    divisions:(int)divisions
               interiorShells:(float)interiorShells
               exteriorShells:(float)exteriorShells;

/**
 Initialize a voxel grid from an NSData containing an array of MDLVoxelIndex values.
 @param interiorShells The number of shells to compute inside the surface shell
 @param exteriorShells The number of shells to compute outside the surface shell
 */
- (instancetype)initWithData:(NSData*)voxelData;

/**
 Create a mesh from the voxel grid
 */
- (nullable MDLMesh*)meshUsingAllocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/**
 Determine if a sample exists at the specified index
 @discussion the allowAny parameters can be used to wildcard any dimensions. This 
             is useful to perform queries such as determining if any voxel 
             exists on the XY plane at a certain Z, or if any voxel exists at 
             any X, Y, Z, but a particular shell, and so on.
 */
- (BOOL)voxelExistsAtIndex:(MDLVoxelIndex)index
                 allowAnyX:(BOOL)allowAnyX allowAnyY:(BOOL)allowAnyY allowAnyZ:(BOOL)allowAnyZ
             allowAnyShell:(BOOL)allowAnyShell;

/**
 Set a sample at the specified index
 @discussion the extent, bounds, and shell properties may be modified
 */
- (void)setVoxelAtIndex:(MDLVoxelIndex)index;

/**
 Returns an NSData containing the indices of all voxels found in the extent
 */
- (nullable NSData *)voxelsWithinExtent:(MDLVoxelIndexExtent)extent;

/**
 Union modifies the voxel grid to be the merger with the supplied voxel grid
 */
- (void)unionWithVoxels:(MDLVoxelArray*)voxels;

/**
 Difference modifies the voxel grid so that voxels also in the supplied voxel 
 grid are removed
 */
- (void)differenceWithVoxels:(MDLVoxelArray*)voxels;

/**
 Intersections modifies the voxel grid so that only voxels that are also in the
 supplied voxel grid are retained
 */
- (void)intersectWithVoxels:(MDLVoxelArray*)voxels;

/**
 Return the voxel index corresponding to a point in space
 */
- (MDLVoxelIndex)indexOfSpatialLocation:(vector_float3)location;

/**
 Return the spatial location of the center of the indexed voxel
 */
- (vector_float3)spatialLocationOfIndex:(MDLVoxelIndex)index;

/**
 The bounding box of an indexed voxel
 */
- (MDLAxisAlignedBoundingBox)voxelBoundingBoxAtIndex:(MDLVoxelIndex)index;

/**
 The number of voxels in the grid
 */
@property (nonatomic, readonly) NSUInteger count;

/**
 The extent of the voxel grid in index space
 */
@property (nonatomic, readonly) MDLVoxelIndexExtent voxelIndexExtent;

/**
 The extent of the voxel grid in Cartesian space
 */
@property (nonatomic, readonly) MDLAxisAlignedBoundingBox boundingBox;

@end

NS_ASSUME_NONNULL_END
