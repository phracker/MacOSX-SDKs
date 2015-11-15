/*!
 @header MTKModel.h
 @framework MetalKit
 @abstract MetalKit helper functionality for using ModelIO with Metal
 @discussion Provides utilities to efficiently load Model assets using ModelIO directly into metal buffers and textures.  Provides container structures for renderable meshes and submeshes.
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <MetalKit/MTKDefines.h>

#import <ModelIO/ModelIO.h>
#import <Metal/Metal.h>
#import <simd/simd.h>

/*!
 @class MTKMeshBufferAllocator
 @abstract Allocator passed to MDLAsset init method to load vertex and index data directly into metal buffers
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKMeshBufferAllocator : NSObject<MDLMeshBufferAllocator>

/*!
 @method initWithDevice
 @abstract Initialize the allocator with a device to be used to create buffers.
 @discussion The designated initializer for this class.
 */
- (nonnull instancetype)initWithDevice:(nonnull id<MTLDevice>) device;

/*!
 @property device
 @abstract Device used to create buffers.
 */
@property (nonatomic, readonly, nonnull) id<MTLDevice> device;

@end

/*!
 @class MTKMeshBuffer
 @abstract Mesh buffers created when ModelIO needs to allocate memory to back vertex or index data.
 @discussion Memory backing these buffer are Metal buffers.  ModelIO will load index and vertex data from from a model asset directly in to the Metal buffer.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKMeshBuffer : NSObject <MDLMeshBuffer>

/*!
 @method length
 @abstract Size in bytes of the buffer allocation.
 */
@property (nonatomic, readonly) NSUInteger length;

/*!
 @property allocator
 @abstract Allocator object used to create this buffer.
 @discussion This allcoator is stored so that it can be used by ModelIO for copy and relayout operations (such as when a new vertex descriptor is applied to a vertex buffer).
 */
@property (nonatomic, readonly,  nonnull)  MTKMeshBufferAllocator *allocator;

/*!
 @property zone
 @abstract Zone from which this buffer was created (if it was created from a zone).
 @discussion A single MetalBuffer is allocated for each zone.  Each zone could have many MTKMeshBuffers, each with it's own offset.  If a MTKMeshBufferAllocator is used, ModelIO will attempt to load all vertex and index data of a single mesh into a single zone.  This allows the GPU to achieve a higher cache hit rate when drawing the mesh.  So although there maybe many MTKMeshBuffers for a model they will be backed with the same contigous MetalBuffer.
 */
@property (nonatomic, readonly, nullable)  id<MDLMeshBufferZone> zone;

/*!
 @property buffer
 @abstract Metal Buffer backing vertex/index data.
 @discussion Many MTKMeshBuffers may reference the same buffer, but each with it's own offset.  (i.e. Many MTKMeshBuffers may be suballocated from a single buffer)
 */
@property (nonatomic, readonly, nonnull) id<MTLBuffer> buffer;

/*!
 @property offset
 @abstract Byte offset of the data within the metal buffer.
 */
@property (nonatomic, readonly) NSUInteger offset;

/*!
 @property type
 @abstract the intended type of the buffer
 */
@property (nonatomic, readonly) MDLMeshBufferType type;

@end

@class MTKMesh;

/*!
 @class MTKSubmesh
 @abstract A segment of a mesh.
 @discussion Container for data that can be rendered in a single draw call. 1:1 mapping to MDLSubmesh.  Each submesh contains an index Buffer and/or material textures to be used with that index buffer.  Actual vertex data resides in the submesh's parent MTKMesh object.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKSubmesh : NSObject

/*!
 @method initWithMesh:submesh:device:
 @abstract Initialize this object with the parent's mesh and the ModelIO mesh
 @param mesh Parent MetalKit mesh
 @param submesh ModelIO mesh from which to generate metal data
 @param device Device with which to generate metal buffers
 */
- (nonnull instancetype)initWithMesh: (nonnull MTKMesh *)mesh
                             submesh: (nonnull MDLSubmesh *)submesh
                              device: (nonnull id<MTLDevice>)device;

/*!
 @property primitiveType
 @abstract Metal primitive type with which to draw this object.
 @discussion Value to use for primitiveType parameter in a [MTLRenderCommandEncoder drawIndexedPrimitives] call.
 */
@property (nonatomic, readonly) MTLPrimitiveType primitiveType;

/*!
 @property indexType
 @abstract Metal index type of data in indexBuffer.
 @discussion Value to use for indexType parameter in a [MTLRenderCommandEncoder drawIndexedPrimitives] call.

 */
@property (nonatomic, readonly) MTLIndexType indexType;

/*!
 @property indexBuffer
 @abstract IndexBuffer (including indexCount) to render the object.
 @discussion The MTLBuffer to use for indexBuffer parameter in a [MTLRenderCommandEncoder drawIndexedPrimitives] call.
 */
@property (nonatomic, readonly, nonnull) MTKMeshBuffer *indexBuffer;

/*!
 @property indexCount
 @abstract Number of indicies in indexBuffer.
 @discussion Value to use for indexCount parameter in a [MTLRenderCommandEncoder drawIndexedPrimitives] call.

 */
@property (nonatomic, readonly) NSUInteger indexCount;

/*!
 @property mesh
 @abstract Parent MTKMesh object containing vertex data of this object.
 @discussion The buffer of this parent mesh should be set in the encoder before a drawIndexedPrimitives call is made.
 */
@property (nonatomic, readonly, weak, nullable) MTKMesh *mesh;


/*!
 @property name
 @abstract Name from the original MDLSubmesh object.
 @discussion Although not directly used by this object, the application may use this to identify the submesh in the renderer/scene/world.
 */
@property (nonatomic, readonly, nonnull) NSString *name;

/*!
 @property material
 @abstract Material from the original MDLSubmesh object.
 @discussion Although not directly used by this object, the application can use this to determine rendering state to set before rendering this object.
 */
@property (nonatomic, nullable) MDLMaterial *material;

@end

/*!
 @class MTKMesh
 @abstract Container for vertex data of a mesh and submeshes to render it.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKMesh : NSObject

/*!
 @method initWithMesh:device:
 @abstract Initialize the mesh and the mesh's submeshes.
 @discussion This does NOT initialize any meshes that are children of the ModelIO mesh.
 @param mesh ModelIO Mesh from which to create this MetalKit mesh
 @param device Device on which to create mesh resources
 */
- (nonnull instancetype) initWithMesh:(nonnull MDLMesh *)mesh
                               device:(nonnull id<MTLDevice>)device;

/*!
 @method meshesFromAsset:device:
 @abstract Initialize all meshes in a ModelIO asset.
 @result An array of MetalKit meshes built an asset
 @param asset ModelIO asset from which to create MetalKit meshes
 @param device Device on which to create mesh resources
 */
+ (nonnull NSArray<MTKMesh*>*) meshesFromAsset:(nonnull MDLAsset *)asset
                                        device:(nonnull id<MTLDevice>)device;

/*!
 @property vertexBuffers
 @abstract Array of buffers in which mesh vertex data resides.
 */
@property (nonatomic, readonly, nonnull) NSArray<MTKMeshBuffer *> *vertexBuffers;

/*!
 @property vertexDescriptor
 @abstract ModelIO vertex descriptor specifying the layout of data in vertexBuffers.
 @discussion This is not directly used by this object, but the application can use this information to determine rendering state or create a Metal vertex descriptor to build a RenderPipelineState object capable of interpreting data in 'vertexBuffers'.
 */
@property (nonatomic, readonly, nonnull) MDLVertexDescriptor *vertexDescriptor;

/*!
 @property submeshes
 @abstract Submeshes containing index buffers to rendering mesh vertices.
 @discussion Submeshes may also contain texture materials to apply when rendering this object.
 */
@property (nonatomic, readonly, nonnull) NSArray<MTKSubmesh *> *submeshes;

/*!
 @property vertexCount
 @abstract Number of vertices in the vertexBuffers.
 */
@property (nonatomic, readonly) NSUInteger vertexCount;

/*!
 @property matrix
 @abstract Global space matrix derived from ModelIO mesh.
 @discussion This is the global transform of originating ModelIO tranform at time 0.
 */
@property (nonatomic, readonly) matrix_float4x4 matrix;

/*!
 @property name
 @abstract Name of the mesh copies from the originating ModelIO mesh.
 @discussion Can be used by the app to identiry the mesh in it's scene/world/renderer etc.
 */
@property (nonatomic, readonly, nonnull) NSString *name;

@end

/*!
 @function MTKModelIOVertexDescriptorFromMetal
 @abstract Partially converts a Metal vertex descriptor to a ModelIO vertex descriptor
 @discussion This method can only set vertex format, offset, bufferIndex, and stride information in the produced ModelIO vertex descriptor.  It does not add any semantic information such at attributes names.  Names must be set in the returned ModelIO vertex descriptor before it can be applied to a a ModelIO mesh.
 */
MTK_EXTERN MDLVertexDescriptor* __nonnull MTKModelIOVertexDescriptorFromMetal(MTLVertexDescriptor* __nonnull metalDescriptor);

/*!
 @function MTKMetalVertexDescriptorFromModelIO
 @abstract Partially converts a ModelIO vertex descriptor to a Metal vertex descriptor
 @discussion This method can only set vertex format, offset, bufferIndex, and stride information in the produced Metal vertex descriptor. It simply copies attributes 1 for 1. Thus attributes in the given ModelIO vertex descriptor must be arranged in the correct order for the resulting descriptor to properly map mesh data to vertex shader inputs.  Layout stepFunction and stepRates for the resulting MTLVertexDescriptor must also be set by application.
 */
MTK_EXTERN MTLVertexDescriptor* __nonnull MTKMetalVertexDescriptorFromModelIO(MDLVertexDescriptor* __nonnull modelIODescriptor);

/*!
 @function MTKModelIOVertexFormatFromMetal
 @abstract Converts a Metal vertex format to a ModelIO vertex format
 @return A ModelIO vertexformat correspoinding to the given Metal vertex format.  Returns MDLVertexFormatInvalid if no matching ModelIO vertex format exists.
 */
MTK_EXTERN MDLVertexFormat MTKModelIOVertexFormatFromMetal(MTLVertexFormat vertexFormat);

/*!
@function MTKMetalVertexFormatFromModelIO
@abstract Converts a ModelIO vertex format to a Metal vertex format
@return A Metal vertexformat correspoinding to the given ModelIO vertex format.  Returns MTLVertexFormatInvalid if no matching Metal vertex format exists.
*/
MTK_EXTERN MTLVertexFormat MTKMetalVertexFormatFromModelIO(MDLVertexFormat vertexFormat);
