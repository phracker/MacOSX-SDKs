/*!
 @header MTKModel.h
 @framework MetalKit
 @abstract MetalKit helper functionality for using Model I/O with Metal
 @discussion Provides utilities to efficiently load Model assets using Model I/O directly into metal buffers and textures.  Provides container structures for renderable meshes and submeshes.
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <MetalKit/MTKDefines.h>

#import <ModelIO/ModelIO.h>
#import <Metal/Metal.h>
#import <simd/simd.h>


/*!
 @group MTKModelErrors
 */

/*!
 @constant MTKModelErrorDomain
 */
MTK_EXTERN NSString * __nonnull const MTKModelErrorDomain NS_AVAILABLE(10_11, 9_0);
/*!
 @constant MTKModelErrorKey
 */
MTK_EXTERN NSString * __nonnull const MTKModelErrorKey NS_AVAILABLE(10_11, 9_0);


/*!
 @class MTKMeshBufferAllocator
 @abstract Allocator passed to MDLAsset init method to load vertex and index data directly into Metal buffers.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKMeshBufferAllocator : NSObject<MDLMeshBufferAllocator>

/*!
 @method init
 @abstract Must initialize with device
 */
- (nonnull instancetype)init NS_UNAVAILABLE;

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
 @abstract Mesh buffer created by MTKMeshBufferAllocator when Model I/O needs to memory for vertex or index data backing.
 @discussion Memory backing these buffer are Metal buffers.  Model I/O will load index and vertex data from from a model asset directly in to the Metal buffer.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKMeshBuffer : NSObject <MDLMeshBuffer>

/*!
 @method init
 @abstract Only an MTKMeshBufferAllocator object can initilize a MTKMeshBuffer object
 */
- (nonnull instancetype)init NS_UNAVAILABLE;

/*!
 @method length
 @abstract Size in bytes of the buffer allocation.
 */
@property (nonatomic, readonly) NSUInteger length;

/*!
 @property allocator
 @abstract Allocator object used to create this buffer.
 @discussion This allcoator is stored so that it can be used by Model I/O for copy and relayout operations (such as when a new vertex descriptor is applied to a vertex buffer).
 */
@property (nonatomic, readonly,  nonnull)  MTKMeshBufferAllocator *allocator;

/*!
 @property zone
 @abstract Zone from which this buffer was created (if it was created from a zone).
 @discussion A single MetalBuffer is allocated for each zone.  Each zone could have many MTKMeshBuffers, each with it's own offset.  If a MTKMeshBufferAllocator is used, Model I/O will attempt to load all vertex and index data of a single mesh into a single zone.  This allows the GPU to achieve a higher cache hit rate when drawing the mesh.  So although there maybe many MTKMeshBuffers for a model they will be backed with the same contigous MetalBuffer.
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
 @abstract A segment of a mesh and properties to render the segement.
 @discussion Container for data that can be rendered in a single draw call. 1:1 mapping to MDLSubmesh.  Each submesh contains an index Buffer with which the parents mesh data can be rendered.  Actual vertex data resides in the submesh's parent MTKMesh object.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKSubmesh : NSObject

/*!
 @method init
 @abstract Applicatiohs must not explicity allocate or initialize.  Must initialize as part of MTKMesh object.
 */
- (nonnull instancetype)init NS_UNAVAILABLE;

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
@property (nonatomic, nonnull) NSString *name;

@end

/*!
 @class MTKMesh
 @abstract Container for vertex data of a mesh and submeshes to render it.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKMesh : NSObject

/*!
 @method init
 @abstract Cannot use default init.  Must initialize with mesh and metal device.
 */
- (nonnull instancetype)init NS_UNAVAILABLE;

/*!
 @method initWithMesh:device:error:
 @abstract Initialize the mesh and the mesh's submeshes.
 @param mesh Model I/O Mesh from which to create this MetalKit mesh
 @param device Metal device on which to create mesh resources
 @param error Pointer to an NSError object set if an error occurred
 @discussion The designated initializer for this class.  This does NOT initialize any meshes that are children of the Model I/O mesh, only submeshes that are part of the given mesh.  An exceiption is raise if vertexBuffer objects in the given mesh and the indexBuffer of any submesh in this mesh have not been created with a MTKMeshBufferAllocator object.  If a Submesh using MDLGeometryTypeQuads or MDLGeometryTypeTopology is used, that submesh will be copied, and recreated to use MDLGeometryTypeTriangles, before this routine creates the MTKSubmesh.
 */
- (nullable instancetype)initWithMesh:(nonnull MDLMesh *)mesh
                               device:(nonnull id<MTLDevice>)device
                                error:(NSError * __nullable * __nullable)error;

/*!
 @method newMeshesFromAsset:device:sourceMeshes:error:
 @abstract Initialize all meshes in a Model I/O asset.
 @param asset Model I/O asset from which to create MetalKit meshes
 @param device Metal device on which to create mesh resources
 @param sourceMeshes Array built by this method containing MDLMesh objects corresponding the returned MTKMesh objects
 @param error Pointer to an NSError object set if an error occurred
 @return MetalKit Meshes created from the Model I/O asset
 @discussion A convenience method to create MetalKit meshes from each mesh in a Model/IO asset.  Resulting meshes are returned while the Model I/O meshes from which they were generated will appear in the sourceMeshes array.  All vertexBuffer objects in each MDLMesh object in the asset and the indexBuffer of each submesh within each of these meshes must have been created using a MTKMeshBufferAllocator object.
 */
+ (nullable NSArray<MTKMesh*>*)newMeshesFromAsset:(nonnull MDLAsset *)asset
                                           device:(nonnull id<MTLDevice>)device
                                     sourceMeshes:(NSArray<MDLMesh*>* __nullable * __nullable)sourceMeshes
                                            error:(NSError * __nullable * __nullable)error;

/*!
 @property vertexBuffers
 @abstract Array of buffers in which mesh vertex data resides.
 */
@property (nonatomic, readonly, nonnull) NSArray<MTKMeshBuffer *> *vertexBuffers;

/*!
 @property vertexDescriptor
 @abstract Model I/O vertex descriptor specifying the layout of data in vertexBuffers.
 @discussion This is not directly used by this object, but the application can use this information to determine rendering state or create a Metal vertex descriptor to build a RenderPipelineState object capable of interpreting data in 'vertexBuffers'.
 */
@property (nonatomic, readonly, nonnull) MDLVertexDescriptor *vertexDescriptor;

/*!
 @property submeshes
 @abstract Submeshes containing index buffers to rendering mesh vertices.
 */
@property (nonatomic, readonly, nonnull) NSArray<MTKSubmesh *> *submeshes;

/*!
 @property vertexCount
 @abstract Number of vertices in the vertexBuffers.
 */
@property (nonatomic, readonly) NSUInteger vertexCount;

/*!
 @property name
 @abstract Name of the mesh copies from the originating Model I/O mesh.
 @discussion Can be used by the app to identiry the mesh in its scene/world/renderer etc.
 */
@property (nonatomic, nonnull) NSString *name;

@end


/*!
 @group MTKModelFunctions
 */


/*!
 @function MTKModelIOVertexDescriptorFromMetal
 @abstract Partially converts a Metal vertex descriptor to a Model I/O vertex descriptor
 @discussion This method can only set vertex format, offset, bufferIndex, and stride information in the produced Model I/O vertex descriptor.  It does not add any semantic information such at attributes names.  Names must be set in the returned Model I/O vertex descriptor before it can be applied to a a Model I/O mesh.
 */
MTK_EXTERN MDLVertexDescriptor* __nonnull MTKModelIOVertexDescriptorFromMetal(MTLVertexDescriptor* __nonnull metalDescriptor);

/*!
 @function MTKMetalVertexDescriptorFromModelIO
 @abstract Partially converts a Model I/O vertex descriptor to a Metal vertex descriptor
 @discussion This method can only set vertex format, offset, bufferIndex, and stride information in the produced Metal vertex descriptor. It simply copies attributes 1 for 1. Thus attributes in the given Model I/O vertex descriptor must be arranged in the correct order for the resulting descriptor to properly map mesh data to vertex shader inputs.  Layout stepFunction and stepRates for the resulting MTLVertexDescriptor must also be set by application.
 */
MTK_EXTERN MTLVertexDescriptor* __nonnull MTKMetalVertexDescriptorFromModelIO(MDLVertexDescriptor* __nonnull modelIODescriptor);

/*!
 @function MTKModelIOVertexFormatFromMetal
 @abstract Converts a Metal vertex format to a Model I/O vertex format
 @return A Model I/O vertexformat correspoinding to the given Metal vertex format.  Returns MDLVertexFormatInvalid if no matching Model I/O vertex format exists.
 */
MTK_EXTERN MDLVertexFormat MTKModelIOVertexFormatFromMetal(MTLVertexFormat vertexFormat);

/*!
@function MTKMetalVertexFormatFromModelIO
@abstract Converts a Model I/O vertex format to a Metal vertex format
@return A Metal vertexformat correspoinding to the given Model I/O vertex format.  Returns MTLVertexFormatInvalid if no matching Metal vertex format exists.
*/
MTK_EXTERN MTLVertexFormat MTKMetalVertexFormatFromModelIO(MDLVertexFormat vertexFormat);

