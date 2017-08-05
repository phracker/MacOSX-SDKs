//
//  GLKModel.h
//
//  Copyright (c) 2014 Apple. All rights reserved.
//
#import <Availability.h>
#import <ModelIO/ModelIO.h>
#import <GLKit/GLKitBase.h>
#if TARGET_OS_IPHONE
#import <OpenGLES/gltypes.h>
#else // !TARGET_OS_IPHONE
#import <OpenGL/gltypes.h>
#endif // !TARGET_OS_IPHONE


/*!
 @group GLKModelErrors
 */

/*!
 @constant kGLKModelErrorDomain
 */
GLK_EXTERN NSString * __nonnull const kGLKModelErrorDomain NS_AVAILABLE(10_11, 9_0);
/*!
 @constant kGLKModelErrorKey
 */
GLK_EXTERN NSString * __nonnull const kGLKModelErrorKey NS_AVAILABLE(10_11, 9_0);



/*!
 @class GLKMeshBufferAllocator
 @abstract Allocator passed to MDLAsset init method to load vertex and index data directly into OpenGL buffer object
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface GLKMeshBufferAllocator : NSObject<MDLMeshBufferAllocator>

@end

/*!
 @class GLKMeshBuffer
 @abstract Mesh buffers created when  needs to allocate memory to back vertex or index data
 @discussion Memory backing these buffer are OpenGL buffers. Model I/O will load index and vertex data from from a model asset directly in to the OpenGL buffer object.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface GLKMeshBuffer : NSObject <MDLMeshBuffer>

/*!
 @method length
 @abstract Size in bytes of the buffer allocation
 */
@property (nonatomic, readonly) NSUInteger length;

/*!
 @property allocator
 @abstract Allocator object used to create this buffer.
 @discussion This allcoator used for copy and relayout operations (such as when a new vertex descriptor is applied to a vertex buffer)
 */
@property (nonatomic, readonly, nonnull) GLKMeshBufferAllocator *allocator;

/*!
 @property glBufferName
 @abstract glBufferName for buffer object backing vertex/index data
 @discussion Many GLKMeshBuffers may reference the same OpenGL buffer object, but each with its own offset.  (i.e. Many GLKMeshBuffers may be suballocated from a single OpenGL buffer object)
 */
@property (nonatomic, readonly) GLuint glBufferName;

/*!
 @property offset
 @abstract Byte offset of the data within the OpenGL buffer
 */
@property (nonatomic, readonly) NSUInteger offset;


/*!
 @property zone
 @abstract Zone from which this buffer was created (if it was created witha zone)
 @discussion A single GL buffer is allocated for each zone.  Each zone could have many GLKMeshBuffers, each with it's own offset.  If a GLKMeshBufferAllocator is used, Model I/O will attempt to load all vertex and indexData of a single model into a single zone.  So although there maybe many GLKMeshBuffers for a model they will be backed with the same contigous GL buffer.
 */
@property (nonatomic, readonly, nullable) id <MDLMeshBufferZone> zone;

/*!
 @property type
 @abstract the intended type of the buffer
 */
@property (nonatomic, readonly) MDLMeshBufferType type;

@end

@class GLKMesh;

NS_CLASS_AVAILABLE(10_11, 9_0)
@interface GLKSubmesh : NSObject

/*!
 @method init
 @abstract Must be initialized by a GLKMesh object
 */
- (nullable instancetype)init NS_UNAVAILABLE;

/*!
 @property type
 @abstract Type of data in the elementBuffer (aka indexBuffer)
 @discussion This value should be used for the type parameter of glDrawElements
 */
@property (nonatomic, readonly) GLenum type;

/*!
 @property mode
 @abstract Primitive type mode value of data in the elementBuffer (aka indexBuffer)
 @discussion This value should be used for the mode parameter in glDrawElements
 */
@property (nonatomic, readonly) GLenum mode;

/*!
 @property elementCount
 @abstract Number of elements (aka indicies) in the elementBuffer (aka indexBuffer)
 @discussion This value should be used for the count parameter in glDrawElements
*/
@property (nonatomic, readonly) GLsizei elementCount;

/*!
 @property elementBuffer
 @abstract Name of buffer object with index data
 @discussion The buffer name to be used with DrawElements
 */
@property (nonatomic, readonly, nonnull) GLKMeshBuffer *elementBuffer;

/*!
 @property mesh
 @abstract Parent GLKit mesh containing vertex data of this object
 @discussion Buffer of this parent mesh should be set in the encoder before a drawIndexedPrimitives call is made
 */
@property (nonatomic, readonly, weak, nullable) GLKMesh *mesh;

/*!
 @property name
 @abstract Name from the original MDLSubmesh object.
 @discussion Although not directly used by this object, the application may use this to identify the submesh in it renderer/scene/world.
 */
@property (nonatomic, readonly, nonnull) NSString *name;

@end

NS_CLASS_AVAILABLE(10_11, 9_0)
@interface GLKMesh : NSObject

/*!
 @method init
 @abstract Must initialize with a mesh
 */
- (nullable instancetype)init NS_UNAVAILABLE;

/*!
 @method initWithMesh:error:
 @abstract Initialize the mesh and the mesh's submeshes
 @discussion This does NOT initialize any meshes that are children of the Model I/O mesh
 @error Pointer to an NSError object which will be set if an error occurred
 @param mesh Model I/O Mesh from which to create this GLKit mesh
 */
- (nullable instancetype)initWithMesh:(nonnull MDLMesh*)mesh
                                error:(NSError * __nullable * __nullable)error;

/*!
 @method newMeshesFromAsset:sourceMeshes:error:
 @abstract Initialize all meshes in a Model I/O asset.
 @result An array of GLKit meshes built an asset
 @param asset Model I/O asset from which to create GLKit meshes
 @param sourceMeshes Model I/O meshes corresponding the newly created GLKMeshes
 @param error Pointer to an NSError object set if an error occurred
 @param return GLKit meshes created from the Model I/O asset
 @dicussion A convenience method to create GLKit meshes from each mesh in a Model/IO asset.  Resulting meshes are returned while Model I/O meshes from which they were generated will appear in the sourceMeshes array.
 */
+ (nullable NSArray<GLKMesh*>*) newMeshesFromAsset:(nonnull MDLAsset *)asset
                                      sourceMeshes:(NSArray<MDLMesh*>* __nullable * __nullable)sourceMeshes
                                             error:(NSError * __nullable * __nullable)error;

/*!
 @property vertexCount
 @abstract Number of verticies in the vertexBuffers
 */
@property (nonatomic, readonly) NSUInteger vertexCount;

/*!
 @property vertexBuffers
 @abstract Array of buffers in which mesh vertex data resides
 */
@property (nonatomic, readonly, nonnull) NSArray<GLKMeshBuffer*> *vertexBuffers;

/*!
 @property vertexDescriptor
 @abstract Model I/O vertex descriptor specifying the layout of data in vertexBuffers
 @discussion This is not directly used by this object, but the application can use this information to determine rendering state or setup a vertex attribute object.
 */
@property (nonatomic, readonly, nonnull) MDLVertexDescriptor *vertexDescriptor;

/*!
 @property submeshes
 @abstract Submeshes containing index buffers to rendering mesh verticies.
 @discussion Submeshes may also contain texture materials to apply when rendering this object
 */
@property (nonatomic, readonly, nonnull) NSArray<GLKSubmesh *> *submeshes;

/*!
 @property name
 @abstract Name of the mesh copies from the originating Model I/O mesh
 @discussion Can be used by the app to identiry the mesh in it's scene/world/renderer etc.
 */
@property (nonatomic, readonly, nonnull) NSString* name;

@end

/*!
 @struct GLKVertexAttributeParameters
 @abstract Structure for parameters to use in glVertexAttribPointer given a MDLVertexForamt
 */
struct _GLKVertexAttributeParameters{
    GLenum    type;
    GLint     size;
    GLboolean normalized;
};
typedef struct _GLKVertexAttributeParameters GLKVertexAttributeParameters;

/*!
 @struct GLKVertexAttributeParametersFromModelIO
 @abstract Returns parameters to use in a call to glVertexAttribPointer given a MDLVertexFormat
 */
GLK_EXTERN
GLKVertexAttributeParameters GLKVertexAttributeParametersFromModelIO(MDLVertexFormat vertexFormat);
