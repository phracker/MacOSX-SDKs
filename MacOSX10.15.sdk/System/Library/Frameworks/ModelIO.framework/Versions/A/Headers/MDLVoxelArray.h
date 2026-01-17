//
//  MDLVoxelArray.h
// @framework ModelIO
//
// @copyright © 2015 Apple Inc. All rights reserved.
//

/*!
 @header MDLVoxelArray.h
 @framework ModelIO
 @abstract Structures for describing volumetric data obtained from 3d assets
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLMeshBuffer.h>
#import <ModelIO/MDLObject.h>
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

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLVoxelArray : MDLObject

/**
 Initialize a voxel grid from an MDLAsset. Attempts to create a closed volume
 model by applying "patches" of radius patchRadius to any holes found in the
 orginal mesh. Choose a patch radius that will be large enough to fill in the largest
 hole in the model.
 */
- (instancetype)initWithAsset:(MDLAsset*)asset divisions:(int)divisions patchRadius:(float)patchRadius;

/**
 Initialize a voxel grid from an NSData containing an array of MDLVoxelIndex values.
 
 @param boundingBox The bounds defining the extent of the volume model in Cartesian space
 @param voxelExtent The extent of a single voxel
 */
- (instancetype)initWithData:(NSData*)voxelData
                 boundingBox:(MDLAxisAlignedBoundingBox)boundingBox
                 voxelExtent:(float)voxelExtent;

/**
 Initialize a voxel grid from an MDLAsset and dilate the resulting voxels by
 a number of interior and exterior shells.
 Routine will attempt to create a closed volume model by applying patches of
 a given radius to any holes it may find in the asset.
 
 @param divisions The number of divisions to divide the vertical extent of the
 model by.
 @param interiorShells The number of shells to compute inside the surface shell
 @param exteriorShells The number of shells to compute outside the surface shell
 @param patchRadius The radius of the largest model mending patch in world space units
 */
- (instancetype)initWithAsset:(MDLAsset*)asset
                    divisions:(int)divisions
               interiorShells:(int)interiorShells
               exteriorShells:(int)exteriorShells
                  patchRadius:(float)patchRadius NS_DEPRECATED(10_11, 10_12, NA, NA);

/**
 Initialize a voxel grid from an MDLAsset and dilate the resulting voxels by
 a spatial distance in the interior and exterior directions.
 Routine will attempt to create a closed volume model by applying "patches" of
 a given radius to any holes it may find in the asset.
 
 @param divisions The number of divisions to divide the vertical extent of the
 model by.
 @param interiorNBWidth The interior narrow band width in world space units
 @param exteriorNBWidth The exterior narrow band width in world space units
 @param patchRadius The radius of the largest model mending patch in world space units
 */
- (instancetype)initWithAsset:(MDLAsset*)asset
                    divisions:(int)divisions
              interiorNBWidth:(float)interiorNBWidth
              exteriorNBWidth:(float)exteriorNBWidth
                  patchRadius:(float)patchRadius NS_DEPRECATED(10_11, 10_12, NA, NA);

/**
 The number of voxels in the grid
 */
@property (nonatomic, readonly) NSUInteger count;

/**
 The extent of the voxel grid in index space
 */
@property (nonatomic, readonly) MDLVoxelIndexExtent voxelIndexExtent;

/**
 Determine if a sample exists at the specified index
 @discussion the allowAny parameters can be used to wildcard any dimensions. This
 is useful to perform queries such as determining if any voxel
 exists on the XY plane at a certain Z, or if any voxel exists at
 any X, Y, Z, or a particular shell, and so on.
 */
- (BOOL)voxelExistsAtIndex:(MDLVoxelIndex)index
                 allowAnyX:(BOOL)allowAnyX allowAnyY:(BOOL)allowAnyY allowAnyZ:(BOOL)allowAnyZ
             allowAnyShell:(BOOL)allowAnyShell;

/**
 Returns an NSData containing the indices of all voxels found in the extent
 */
- (nullable NSData *)voxelsWithinExtent:(MDLVoxelIndexExtent)extent;

/**
 Returns an NSData containing the indices of all voxels in the voxel grid
 */
- (nullable NSData *)voxelIndices;

/**
 Set a sample at the specified index
 @discussion the extent, bounds, and shell properties may be modified
 */
- (void)setVoxelAtIndex:(MDLVoxelIndex)index;

/**
 Set voxels corresponding to a mesh.
 Routine will attempt to create a closed volume model by applying "patches" of
 a given radius to any holes it may find in the mesh.
 */
- (void)setVoxelsForMesh:(nonnull MDLMesh*)mesh divisions:(int)divisions patchRadius:(float)patchRadius;

/**
 Set voxels corresponding to a mesh
 Routine will attempt to create a closed volume model by applying "patches" of
 a given radius to any holes it may find in the mesh.
 
 @param divisions The number of divisions to divide the vertical extent of the
 model by.
 @param interiorShells The number of shells to compute inside the surface shell
 @param exteriorShells The number of shells to compute outside the surface shell
 @param patchRadius The radius of the largest model mending patch in world space units
 */
- (void)setVoxelsForMesh:(nonnull MDLMesh*)mesh
               divisions:(int)divisions
          interiorShells:(int)interiorShells
          exteriorShells:(int)exteriorShells
             patchRadius:(float)patchRadius NS_DEPRECATED(10_11, 10_12, NA, NA);


/**
 Set voxels corresponding to a mesh
 Routine will attempt to create a closed volume model by applying "patches" of
 a given radius to any holes it may find in the mesh.
 
 @param divisions The number of divisions to divide the vertical extent of the
 model by.
 @param interiorNBWidth The interior narrow band width in world space units
 @param exteriorNBWidth The exterior narrow band width in world space units
 @param patchRadius The radius of the largest model mending patch in world space units
 */
- (void)setVoxelsForMesh:(nonnull MDLMesh*)mesh
               divisions:(int)divisions
         interiorNBWidth:(float)interiorNBWidth
         exteriorNBWidth:(float)exteriorNBWidth
             patchRadius:(float)patchRadius NS_DEPRECATED(10_11, 10_12, NA, NA);

/**
 Union modifies the voxel grid to be the merger with the supplied voxel grid.
 It is assumed that the spatial voxel extent of one voxel in the supplied grid is the same as that of the voxel grid.
 Note that the shell level data will be cleared.
 */
- (void)unionWithVoxels:(MDLVoxelArray*)voxels;

/**
 Intersection modifies the voxel grid so that only voxels that are also in the supplied voxel grid are retained.
 It is assumed that the spatial voxel extent of one voxel in the supplied grid is the same as that of the voxel grid.
 Note that the shell level data will be cleared.
 */
- (void)intersectWithVoxels:(MDLVoxelArray*)voxels;

/**
 Difference modifies the voxel grid so that voxels also in the supplied voxel grid are removed.
 It is assumed that the spatial voxel extent of one voxel in the supplied grid is the same as that of the voxel grid.
 Note that the shell level data will be cleared.
 */
- (void)differenceWithVoxels:(MDLVoxelArray*)voxels;

/**
 The extent of the voxel grid in Cartesian space
 */
@property (nonatomic, readonly) MDLAxisAlignedBoundingBox boundingBox;

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
 Converts volume grid into a signed shell field by surrounding the surface voxels, which have shell 
 level values of zero, by an inner layer of voxels with shell level values of negative one and an 
 outer layer of voxels with shell level values of positive one.
 
 The volume model must be closed in order to generate a signed shell field.
 */
- (void)convertToSignedShellField;

/**
 Returns whether or not the volume grid is in a valid signed shell field form.
 
 This property will be set to YES after calling generateSignedShellField. All other 
 methods that modify the voxel grid will cause this property to be set to NO. Setting
 shellFieldInteriorThickness and shellFieldExteriorThickness will not affect the value
 of this property.
 */
@property (nonatomic, readonly) BOOL isValidSignedShellField;

/**
 If voxel grid is in a valid signed shell field form, sets the interior thickness to the desired width,
 as measured from the model surface. If the voxel grid is not in a valid signed shell field form, the
 value of this property is zero.
 */
@property (nonatomic) float shellFieldInteriorThickness;

/**
 If voxel grid is in a valid signed shell field form, sets the exterior thickness to the desired width,
 as measured from the model surface. If the voxel grid is not in a valid signed shell field form, the
 value of this property is zero.
 */
@property (nonatomic) float shellFieldExteriorThickness;

/**
 Creates a coarse mesh from the voxel grid
 */
- (nullable MDLMesh*)coarseMesh;
- (nullable MDLMesh*)coarseMeshUsingAllocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/**
 Creates a smooth mesh from the voxel grid
 */
- (nullable MDLMesh*)meshUsingAllocator:(nullable id<MDLMeshBufferAllocator>)allocator;


@end

NS_ASSUME_NONNULL_END
