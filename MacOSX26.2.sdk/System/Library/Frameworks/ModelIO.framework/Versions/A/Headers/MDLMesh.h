/*!
 @header MDLMesh.h
 @framework ModelIO
 @abstract Structures for describing meshes for rendering
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLLight.h>
#import <ModelIO/MDLTransform.h>
#import <ModelIO/MDLSubmesh.h>
#import <ModelIO/MDLMeshBuffer.h>
#import <ModelIO/MDLVertexDescriptor.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class MDLVertexAttributeData
 @abstract convenience object to quickly access vertex attribute data
 @discussion created by MDLMesh's vertexAttributeData selector
             Setting values on this object has no effect on the
             underlying objects.
 */

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLVertexAttributeData : NSObject

@property (nonatomic, retain) MDLMeshBufferMap *map;
@property (nonatomic) void *dataStart;
@property (nonatomic) NSUInteger stride;
@property (nonatomic) MDLVertexFormat format;
@property (nonatomic) NSUInteger bufferSize API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

@end


/*!
 @class MDLMesh
 @abstract A vertex buffer with info to interpret vertex data
 @discussion Includes a collection of submeshs which have indexbuffer and
             material information
 */
API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLMesh : MDLObject

/*!
 @method initWithAllocator:
 @abstract Initialize a mesh with an allocator
 @return An empty mesh
*/

- (instancetype)initWithBufferAllocator:(nullable id<MDLMeshBufferAllocator>)bufferAllocator;

/*!
 @method initWithVertexBuffer:vertexCount:descriptor:submeshes:
 @abstract Initialize object with a vertex buffer and a collection of submeshes
 @return Initialized mesh or nil if descriptor's layout array does not describe
         a single buffer
 @param vertexBuffer MDLMeshBuffer object containing all vertex data for the mesh
 @param vertexCount Number of vertices in the vertexBuffer
 @param descriptor VertexDescriptor specifying how to interpret vertex data
 @param submeshes Array of submeshes with index buffers referencing vertex data
        and/or materials to be applied to mesh
 */
- (instancetype)initWithVertexBuffer:(id<MDLMeshBuffer>)vertexBuffer
                         vertexCount:(NSUInteger)vertexCount
                          descriptor:(MDLVertexDescriptor *)descriptor
                           submeshes:(NSArray<MDLSubmesh*> *)submeshes;

/*!
 @method initWithVertexBuffer:vertexCount:descriptor:submeshes:
 @abstract Initialize object with an array of vertex buffers (Structure of
           Arrays) and a collection of submeshes
 @return Initialized mesh or nil if descriptor's layout array is incompatible
         with vertexBuffers array
 @param vertexCount Number of vertices in vertexBuffers
 @param descriptor VertexDescriptor specifying how to interpret vertex data
 @param submeshes Array of submeshes with index buffers referencing vertex data
        and/or materials to be applied to mesh
 @discussion Allows initialization with the layout of the vertexBuffers in a
        structure-of-arrays form, in other words, non-interleaved vertex attributes
 */
- (instancetype)initWithVertexBuffers:(NSArray<id<MDLMeshBuffer>> *)vertexBuffers
                          vertexCount:(NSUInteger)vertexCount
                           descriptor:(MDLVertexDescriptor *)descriptor
                            submeshes:(NSArray<MDLSubmesh*> *)submeshes;

/*!
 @method vertexAttributeDataForAttributeNamed:
 @abstract convenience selector to get quick access to vertex attribute data
 @discussion the vertex buffer will remain mapped until the MDLVertexAttributeData
             is freed.
 */
- (nullable MDLVertexAttributeData*)vertexAttributeDataForAttributeNamed:(NSString*)name;

/*!
 @method vertexAttributeDataForAttributeNamed:asFormat
 @abstract convenience selector to get quick access to vertex attribute data
           reformatted to the requested format if necessary.
 @discussion If the desired format has less elements than the source attribute
             elements, excess elements will be discarded. If the desired format
             has more elements than the source attribute, then the destination
             elements will be set to zero.
             The vertex buffer will remain mapped until the MDLVertexAttributeData
             is freed.
 */
- (nullable MDLVertexAttributeData*)vertexAttributeDataForAttributeNamed:(NSString*)name
                                                                asFormat:(MDLVertexFormat)format;

/*!
 @property boundingBox
 @abstract Bounding box encompasing the mesh
 @discussion Calculated by iterating through MDLVertexAttributePosition to find
             min and max bounds. If no attribute is named MDLVertexAttributePosition
             this will be a invalid bounds where maxBounds is less than minBounds.
 */
@property (nonatomic, readonly) MDLAxisAlignedBoundingBox boundingBox;

/*!
 @property vertexDescriptor
 @abstract Immutable vertex descriptor for interpreting data in vertexBuffers
 @discussion Setting this applies the new layout in 'vertexBuffers' thus is a
             heavyweight operation as structured copies of almost all vertex
             buffer data could be made.  Additionally, if the new vertexDescriptor
             does not have an attribute in the original vertexDescriptor, that
             attribute will be deleted.  If the original vertexDescriptor does
             not have an attribute in the new vertexDescriptor, the data for the
             added attribute set as the added attribute's initializationValue
             property.

             The allocator associated with each original meshbuffer is used to
             reallocate the corresponding resultant meshbuffer.
 */
@property (nonatomic, readwrite, copy) MDLVertexDescriptor *vertexDescriptor;

/*!
 @property vertexCount
 @abstract Number of vertices in the vertexBuffers
 @discussion The size of vertex data in each buffer can be computed by multiplying
             this value with the stride of the buffer in the vertexDescriptor's
             layout
 */
@property (nonatomic, readwrite) NSUInteger vertexCount;

/*!
 @property vertexBuffers
 @abstract Array of buffers containing vertex data
 @discussion The vertex buffers in this array are indexed by the vertex descriptor.
 */
@property (nonatomic, readwrite, retain) NSArray<id<MDLMeshBuffer>> *vertexBuffers;

/*!
 @property submeshes
 @abstract Array of submeshes containing an indexbuffer referencing the vertex
           data and material to be applied when the mesh is rendered
 */
@property (nonatomic, copy, nullable) NSMutableArray<MDLSubmesh*> *submeshes;

/*!
 @property allocator
 @abstract allocator used to allocate contained mesh buffers
 */
@property (nonatomic, readonly, retain) id<MDLMeshBufferAllocator> allocator;

@end


@interface MDLMesh (Modifiers)

/*!
 @method addAttributeWithName:format
 @abstract Convenience method to add an attribute
 @discussion The mesh's allocator will be used to create storage for the new
             attribute.
 */
- (void)addAttributeWithName:(NSString*)name
                      format:(MDLVertexFormat)format;

/*!
 @method addAttributeWithName:format:type:data:stride
 @abstract Create a new vertex attribute including an associated buffer with
           a copy of the supplied data, and update the vertex descriptor accordingly
 @param name The name the attribute can be found by
 @param format Format of the data, such as MDLVertexFormatFloat3
 @param type The usage of the attribute, such as MDLVertexAttributePosition
 @param data Object containing the data to be used in the new vertex buffer
 @param stride The increment in bytes from the start of one data entry to
        the next.
 */
-(void)addAttributeWithName:(NSString *)name
                     format:(MDLVertexFormat)format
                       type:(NSString *)type
                       data:(NSData *)data
                     stride:(NSInteger)stride;

/*!
 @method addAttributeWithName:format:type:data:stride:time
 @abstract Create a new vertex attribute including an associated buffer with
           a copy of the supplied data, and update the vertex descriptor accordingly
 @param name The name the attribute can be found by
 @param format Format of the data, such as MDLVertexFormatFloat3
 @param type The usage of the attribute, such as MDLVertexAttributePosition
 @param data Object containing the data to be used in the new vertex buffer
 @param stride The increment in bytes from the start of one data entry to
        the next.
 @param time The time the attribute is to be invoked at.
 @discussion Adding an attribute, such as position data, at multiple times will
             result in attributes being created for each of those times.
             Attributes corresponding to multiple times can be retrieved from
             the vertex descriptor.
 */
-(void)addAttributeWithName:(NSString *)name
                     format:(MDLVertexFormat)format
                       type:(NSString *)type
                       data:(NSData *)data
                     stride:(NSInteger)stride
                       time:(NSTimeInterval)time;

/*!
 @method addNormalsWithAttributeNamed:creaseThreshold:
 @abstract Calculate and add vertex normal data
 @param attributeName Name is the attribute name of vertex normal attribute.  If nil, vertex normals
        will be added with the MDLVertexAttributeNormal name string
 @param creaseThreshold Threshold of the dot product between the 2 triangles after which
                        their face normal will be smoothed out. Therefore, a threshold of 0 will
                        smooth everything and a threshold of 1 won't smooth anything.
 @discussion Uses the attribute named MDLVertexAttributePosition to calculate
             vertex normals. If the mesh does not have an attribute with
             'attributeName', it will be added, otherwise the attribute name will
             be overwritten with vertex normal data. 'vertexDescriptor' will be
             updated to reflect the new attribute.
 */
- (void)addNormalsWithAttributeNamed:(nullable NSString *)attributeName
                     creaseThreshold:(float)creaseThreshold;


/*!
 @method addTangentBasisForTextureCoordinateAttributeNamed:tangentAttributeNamed:bitangentAttributeNamed
 @abstract Create a shader basis where the tangent and bitangent span the uv -> object space transform
 @param textureCoordinateAttributeName Name of texture coordinates to use in calculations
 @param tangentAttributeName Name of vertex tangent attribute.
 @param bitangentAttributeName Name of vertex bitangent attribute.
 @discussion Uses the attribute named MDLVertexAttributePosition and
             textureCoordinateAttributeName to calculate tangent and bitangent
             attributes. The mesh's vertexDescriptor will be updated to reflect
             the new attributes if necessary. The basis may not be orthogonal; to gaurantee an orthogonal
              tangent basis please use addOrthTanBasisForTextureCoordinateAttibuteNamed selector.
 */
- (void)addTangentBasisForTextureCoordinateAttributeNamed:(NSString*)textureCoordinateAttributeName
                                    tangentAttributeNamed:(NSString *)tangentAttributeName
                                  bitangentAttributeNamed:(nullable NSString *)bitangentAttributeName;

/*!
 @method addTangentBasisForTextureCoordinateAttributeNamed:normalAttributeNamed:tangentAttributeNamed
 @abstract Create tangents which are orthogonal to the normal
 @param textureCoordinateAttributeName texture coordinates to use in calculations
 @param normalAttributeName normals to use in calculations
 @param tangentAttributeName Name of a four component vertex tangent attribute.
 @discussion Uses the attribute named MDLVertexAttributePosition and
             textureCoordinateAttributeName and the specified normals to calculate
             tangent information. The mesh's vertexDescriptor will be updated to
             reflect the new attribute if necessary.
             Note that this method does NOT produce a T.w component which is used in B = (N x T) * T.w
             Please use addOrthTanBasisForTextureCoordinateAttributeNamed.
 */
- (void)addTangentBasisForTextureCoordinateAttributeNamed:(NSString*)textureCoordinateAttributeName
                                     normalAttributeNamed:(NSString*)normalAttributeName
                                    tangentAttributeNamed:(NSString *)tangentAttributeName;

/*
@method addOrthTanBasisForTextureCoordinateAttributeNamed:normalAttributeNamed:tangentAttributeNamed
@abstract Create an orthonormal tangent basis with tangent specified
@param textureCoordinateAttributeName texture coordinates to use in calculations
@param normalAttributeName normals to use in calculations
@param tangentAttributeName Name of a three/four component vertex tangent attribute.
@discussion Uses the attribute named MDLVertexAttributePosition and
            textureCoordinateAttributeName and the specified normals to calculate
            tangent information. The mesh's vertexDescriptor will be updated to
            reflect the new attribute if necessary.
            Note that the bitangent can be calculated from the normal and
            tangent by B = (N x T) * T.w
*/
- (void)addOrthTanBasisForTextureCoordinateAttributeNamed:(NSString *)textureCoordinateAttributeName
                                     normalAttributeNamed:(NSString *)normalAttributeName
                                    tangentAttributeNamed:(NSString *)tangentAttributeName API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/*!
 @method addTextureCoordinatesForAttributeNamed:textureCoordinateAttributeName
 @abstract Creates texture coordinates by unwrapping the mesh
 @param textureCoordinateAttributeName texture coordinates to modify or create
 @discussion Uses the attribute named MDLVertexAttributePosition and if available,
             the attribute named MDLVertexAttributeNormal to calculate texture coordinates
 */
- (void)addUnwrappedTextureCoordinatesForAttributeNamed:(NSString*)textureCoordinateAttributeName;


/*!
 @method flipTextureCoordinatesInAttributeNamed:
 @abstract Flips texture coordinates by performing the operation (u,v) = (u, 1-v)
 @param textureCoordinateAttributeName texture coordinates to modify
 @discussion Many application generate model files with texture coordinate mapping
             assuming a bottom left bitmap origin. It can be more convenient to
             have texture coordinates corresponding to an upper left bitmap origin.
             This selector will perform the flip operation if the requested texture
             coordinate attribute exists on the mesh. An exception will be raised if
             the attribute cannot be found
 */
- (void)flipTextureCoordinatesInAttributeNamed:(NSString*)textureCoordinateAttributeName API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/*!
 @method makeVerticesUnique:
 @abstract Deindexes the vertex array
 @discussion If any vertices are shared on multiple faces, duplicate those
             vertices so faces do not share vertices. The vertex buffer and index
             buffers on submeshes may grow to accomadate any vertices added.
 */
- (void)makeVerticesUnique NS_DEPRECATED(10.11,10.13,9.0,11.0);


/*!
 @method makeVerticesUniqueAndReturnError:
 @abstract Deindexes the vertex array
 @discussion If any vertices are shared on multiple faces, duplicate those
 vertices so faces do not share vertices. The vertex buffer and index
 buffers on submeshes may grow to accomadate any vertices added.
 */
- (BOOL)makeVerticesUniqueAndReturnError:(NSError **)error API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/*!
 @method replaceAttributeNamed:withData
 @abstract replace existing attribute data with new attribute data retaining
 the format of the replacement data.
 @discussion If the specified attribute does not already exist, it will be
 created.
 */
- (void)replaceAttributeNamed:(NSString*)name
                     withData:(nonnull MDLVertexAttributeData*)newData;

/*!
 @method updateAttributeNamed:withData
 @abstract update existing attribute data with new attribute data retaining
 the format of the existing data.
 @discussion If the specified attribute does not already exist, it will be
 created with the same format as the newData.
 */
- (void)updateAttributeNamed:(NSString*)name
                    withData:(nonnull MDLVertexAttributeData*)newData;

/*! 
 @method removeAttributeNamed:
 @abstract remove an attribute
 @discussion if the named attribute does not exist, nothing happens.
 */
- (void)removeAttributeNamed:(NSString*)name;


@end



@interface MDLMesh (Generators)

/*!
 @method initBoxMeshWithExtent:segments:inwardNormals:geometryType:allocator:
 @abstract Factory method for generating a mesh with a cube shape
 @return MDLMesh box with desired attributes
 @param extent size of the box in each dimension
 @param segments Number of slices in each dimension
 @param inwardNormals Generated Normal point inward
 @param geometryType Can be MDLGeometryTypeLines, MDLGeometryTypeQuads, or MDLGeometryTypeTriangles
 @param allocator A mesh buffer allocator used to allocate memory to back buffers
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Assembled with triangle or quad primitives.  Specifying inward
             normals is useful for generating a skybox. The center of the box
             is at(0, 0, 0).
             Will raise an exception if an unsupported geometry type is passed in.
 */
- (instancetype)initBoxWithExtent:(vector_float3)extent
                             segments:(vector_uint3)segments
                        inwardNormals:(BOOL)inwardNormals
                         geometryType:(MDLGeometryType)geometryType
                            allocator:(nullable id<MDLMeshBufferAllocator>)allocator;


/*!
 @method initSphereWithExtent:segments:inwardNormals:geometryType:allocator
 @abstract Factory method for generating a mesh with an ellipsoid shape
 @return MDLMesh epllipsoid with desired attributes
 @param geometryType Must be MDLGeometryTypeTriangles or MDLGeometryTypeLines
 @param inwardNormals If true, generated normals will face inwards. Useful for
        generating a skydome.
        actual nubmer of vertical slices will be half of 'vertical' segments
 @param allocator A mesh buffer allocator used to allocate memory to back buffers
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Specifying inward normals and hemisphere is useful for generating a skydome.
             Specifying equal X, Y, and Z radii will generate a sphere.
             Specifying a y radius of 0.0 will generate a disc.
             Will raise an exception if radialSegments is < 3, verticalSegments is < 2,
             or an unsupported geometry type is passed in.
 */
- (instancetype)initSphereWithExtent:(vector_float3)extent
                            segments:(vector_uint2)segments
                       inwardNormals:(BOOL)inwardNormals
                        geometryType:(MDLGeometryType)geometryType
                           allocator:(nullable id<MDLMeshBufferAllocator>)allocator;
- (instancetype)initHemisphereWithExtent:(vector_float3)extent
                                segments:(vector_uint2)segments
                           inwardNormals:(BOOL)inwardNormals
                                     cap:(BOOL)cap
                            geometryType:(MDLGeometryType)geometryType
                               allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method initCylinderWithExtent:segments:inwardNormals:topCap:bottomCap:geometryType:allocator
 @abstract Factory method for generating a mesh with a cylindrical shape
 @return MDLMesh cylinder with desired attributes
 @param geometryType Must be MDLGeometryTypeTriangles or MDLGeometryTypeLines
 @param inwardNormals Normals point toward center of cylinder
 @param allocator A mesh buffer allocator used to allocate memory to back buffers
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Center of cylinder at (0, 0, 0) with a top at +Y and bottom at -Y.
             Specifying equal X and Z radia will generate a true cylinder.
             Specifying a height of 0.0 and verticalSegments of 0 will generate
             a disc.
             Will raise an exception if radialSegments is < 3 or if an unsupported
             geometry type is passed in.
             Generated texture coordinates are laid out as follows:
                                                      ___
                                                     /   \   <- T texcoord = 0.0
                 Texture for top of cylinder   ---> [     ]
                                                     \___/
                                                    [     ]  <- T texcoord = 0.3333
                                                    [     ]
                 Texture for sides of cylinder ---> [     ]
                                                    [_____]  <- T texcoord = 0.6666
                                                     /   \
                 Texture for base of cylinder  ---> [     ]
                                                     \___/   <- T texcoord = 1.0
 */
- (instancetype)initCylinderWithExtent:(vector_float3)extent
                              segments:(vector_uint2)segments
                         inwardNormals:(BOOL)inwardNormals
                                topCap:(BOOL)topCap
                             bottomCap:(BOOL)bottomCap
                          geometryType:(MDLGeometryType)geometryType
                             allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method initCapsuleWithExtent:cylinderSegments:hemisphereSegments:inwardNormals:geometryType:allocator
 @abstract Factory method for generating a mesh with a capsule shape; a cylinder
           with hemispheres for caps.
 @return MDLMesh capsule with desired attributes
 @param extent Dimension of bounding box for capsule.
 @param hemisphereSegments Number of slices through hemisphere caps along Y axis
 @param geometryType Must be MDLGeometryTypeTriangles or MDLGeometryTypeLines
 @param inwardNormals Normals point toward center of cylinder
 @param allocator A mesh buffer allocator used to allocate memory to back buffers
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Center of capsule at (0, 0, 0) with a top at +Y and bottom at -Y.
             The height of hemisphere cap is specified by the minimum of X and Z
             Specifying equal X and Z radii will generate a true capsule.
             Specifying a height that is less than the twice of min of the X and Z 
             radii or verticalSegments of 0 will generate a sphere. The full height
             of the capsule will also incorporate the hemisphere caps.
             Will raise an exception if radialSegments is < 3 or if hemisphereSegments < 1
             or if an unsupported geometry type is specified.
             Generated texture coordinates for top and bottom caps are wrapped 
             in a similar manner as for asphere, laid out as follows:
                                      ___
                                     /   \   <- T texcoord = 0.0
 Texture for top of cylinder   ---> [-----]
                                    [     ]  <- T texcoord = extent.x/extent.y
                                    [     ]
 Texture for sides of cylinder ---> [     ]
                                    [_____]  <- T texcoord = 1.0 - extent.x/extent.y
 Texture for base of cylinder  ---> [     ]
                                     \___/   <- T texcoord = 1.0
*/
- (instancetype)initCapsuleWithExtent:(vector_float3)extent
                     cylinderSegments:(vector_uint2)segments
                   hemisphereSegments:(int)hemisphereSegments
                        inwardNormals:(BOOL)inwardNormals
                         geometryType:(MDLGeometryType)geometryType
                            allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method initConeWithExtent:segments:inwardNormals:cap:geometryType:allocator
 @abstract Factory method for generating a mesh with an ellipticalCone shape.
 @return MDLMesh cone with desired attributes
 @param geometryType Must be MDLGeometryTypeTriangles or MDLGeometryTypeLines
 @param inwardNormals Normals point toward center of ellipticalCone
 @param allocator A mesh buffer allocator used to allocate memory to back buffers
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Point of cone at (0, 0, 0) while base of cone is -Y.
             Will raise an exception if radialSegments is < 3, or verticalSegments is < 1,
             or if an unsupported geometry type is passed in.
             Generated texture coordinates are laid out as follows:
                                                 _____
                                                [     ]  <- T texcoord = 0.0
                                                [     ]
                 Texture for sides of cone ---> [     ]
                                                [     ]
                                                [_____]  <- T texcoord = 0.6666
                                                 /   \
                 Texture for base of cone  ---> [     ]
                                                 \___/   <- T texcoord = 1.0
 */
- (instancetype)initConeWithExtent:(vector_float3)extent
                          segments:(vector_uint2)segments
                     inwardNormals:(BOOL)inwardNormals
                               cap:(BOOL)cap
                      geometryType:(MDLGeometryType)geometryType
                         allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method initPlaneWithExtent:segments:geometryType:allocator
 @abstract Factory method for generating a mesh with an planar shape
 @return MDLMesh plane with desired attributes
 @param extent extent of the plane
 @param segments Number of segements in the X and Y dimensions
 @param geometryType Can be MDLGeometryTypeLines, MDLGeometryTypeQuads, or MDLGeometryTypeTriangles
 @param allocator A mesh buffer allocator used to allocate memory to back buffers
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Creates a plane spanning the greatest dimensions of extent.
             Will raise an exception if an unsupported geometry type is passed in.
 */
- (instancetype)initPlaneWithExtent:(vector_float3)extent
                           segments:(vector_uint2)segments
                       geometryType:(MDLGeometryType)geometryType
                          allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method initIcosahedronWithExtent:inwardNormals:geometryType:allocator
 @abstract Factory method for generating a mesh icosahedron
 @return MDLMesh icosahedron with desired attributes
 @param inwardNormals Generated normals will face towards the center of the mesh
 @param allocator A mesh buffer allocator used to allocate memory to back buffers
        for the returned mesh.  If nil, a default allocator will be used
 @discussion  Creates an icosahedron with center at (0, 0, 0).
 */
- (instancetype)initIcosahedronWithExtent:(vector_float3)extent
                            inwardNormals:(BOOL)inwardNormals
                             geometryType:(MDLGeometryType)geometryType
                                allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method initMeshBySubdividingMesh:submeshIndex:subdivisionLevels:allocator
 @abstract Factory method that generates a subdivided mesh from a source mesh
 @param mesh Mesh from which to generate a subdivided mesh
 @param submeshIndex Index of submesh in Mesh's submesh array from which to
        generate a subdivided mesh
 @param subdivisionLevels The number of levels to subdivide mesh
 @discussion Subdivision levels over four are likely to generate more triangles
             than can be reasonably displayed. Index and vertex data will use
             the same allocator used for the source mesh. Loading an asset
             using the topology preservation flag set to YES will result in the
             best subdivision results.
 @return Returns a mesh subdivided to index level, unless subdivision is
         impossible.
 */
- (instancetype)initMeshBySubdividingMesh:(MDLMesh*)mesh
                             submeshIndex:(int)submeshIndex
                        subdivisionLevels:(unsigned int)subdivisionLevels
                                allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

+ (instancetype)newBoxWithDimensions:(vector_float3)dimensions
                            segments:(vector_uint3)segments
                        geometryType:(MDLGeometryType)geometryType
                       inwardNormals:(BOOL)inwardNormals
                           allocator:(nullable id<MDLMeshBufferAllocator>)allocator;
+ (instancetype)newEllipsoidWithRadii:(vector_float3)radii
                       radialSegments:(NSUInteger)radialSegments
                     verticalSegments:(NSUInteger)verticalSegments
                         geometryType:(MDLGeometryType)geometryType
                        inwardNormals:(BOOL)inwardNormals
                           hemisphere:(BOOL)hemisphere
                            allocator:(nullable id<MDLMeshBufferAllocator>)allocator;
+ (instancetype)newCylinderWithHeight:(float)height
                                radii:(vector_float2)radii
                       radialSegments:(NSUInteger)radialSegments
                     verticalSegments:(NSUInteger)verticalSegments
                         geometryType:(MDLGeometryType)geometryType
                        inwardNormals:(BOOL)inwardNormals
                            allocator:(nullable id<MDLMeshBufferAllocator>)allocator;
+ (instancetype)newCapsuleWithHeight:(float)height
                               radii:(vector_float2)radii
                      radialSegments:(NSUInteger)radialSegments
                    verticalSegments:(NSUInteger)verticalSegments
                  hemisphereSegments:(NSUInteger)hemisphereSegments
                        geometryType:(MDLGeometryType)geometryType
                       inwardNormals:(BOOL)inwardNormals
                           allocator:(nullable id<MDLMeshBufferAllocator>)allocator API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
+ (instancetype)newEllipticalConeWithHeight:(float)height
                                      radii:(vector_float2)radii
                             radialSegments:(NSUInteger)radialSegments
                           verticalSegments:(NSUInteger)verticalSegments
                               geometryType:(MDLGeometryType)geometryType
                              inwardNormals:(BOOL)inwardNormals
                                  allocator:(nullable id<MDLMeshBufferAllocator>)allocator;
+ (instancetype)newPlaneWithDimensions:(vector_float2)dimensions
                              segments:(vector_uint2)segments
                          geometryType:(MDLGeometryType)geometryType
                             allocator:(nullable id<MDLMeshBufferAllocator>)allocator;
+ (instancetype)newIcosahedronWithRadius:(float)radius
                           inwardNormals:(BOOL)inwardNormals
                            geometryType:(MDLGeometryType)geometryType
                               allocator:(nullable id<MDLMeshBufferAllocator>)allocator API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
+ (instancetype)newIcosahedronWithRadius:(float)radius
                           inwardNormals:(BOOL)inwardNormals
                               allocator:(nullable id<MDLMeshBufferAllocator>)allocator;
+ (nullable instancetype)newSubdividedMesh:(MDLMesh*)mesh
                              submeshIndex:(NSUInteger)submeshIndex
                         subdivisionLevels:(NSUInteger)subdivisionLevels;

@end


@interface MDLMesh (MDLLightBaking)

/*!
 @method generateAmbientOcclusionTextureWithSize:
 @abstract Creates an Ambient Occlusion texture, returns true upon success, false
           upon failure
 @param textureSize Texture Size in which to bake the ambient occlusion
 @param raysPerSample Number of rays to be sent out of every texture texel against
        the object for potential occlusion.
 @param attenuationFactor Float between 0 to 1 that defines how to attenuate the
        AO value. 0 doesn't change it, and at 1, all AO values are white except
        if they are originally completely black. Quadratic attenuation in between.
 @param objectsToConsider NSArray of MDLMeshes containing the objects to raytrace against
 @param vertexAttributeName NSString of the MDLVertexAttribute where the vertex
        texture UVs will be stored. Creates it if it doesn't exist, otherwise
        overwrites current values.
 @param materialPropertyName NSString of the MDLMaterialProperty that will store
        the texture in the Mesh.
 @result Success or failure of the baking process.
 */
- (BOOL)generateAmbientOcclusionTextureWithSize:(vector_int2)textureSize
                                  raysPerSample:(NSInteger)raysPerSample
                              attenuationFactor:(float)attenuationFactor
                              objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                           vertexAttributeNamed:(NSString *)vertexAttributeName
                          materialPropertyNamed:(NSString *)materialPropertyName;

/*!
 @method generateAmbientOcclusionTextureWithQuality:
 @abstract Creates an Ambient Occlusion texture, returns true upon success, false
           upon failure
 @param bakeQuality Float between 0 and 1 that defines quality of the bake process.
        0 is of lower quality but bakes faster and uses less memory, where 1 is
        of higher quality.
 @param attenuationFactor Float between 0 to 1 that defines how to attenuate the
        AO value. 0 doesn't change it, and at 1, all AO values are white except
        if they are originally completely black. Quadratic attenuation in between.
 @param objectsToConsider NSArray of MDLMeshes containing the objects to raytrace
        against
 @param vertexAttributeName NSString of the MDLVertexAttribute where the vertex
        texture UVs will be stored. Creates it if it doesn't exist, otherwise
        overwrites current values.
 @param materialPropertyName NSString of the MDLMaterialProperty that will store
        the texture in the Mesh.
 @result Success or failure of the baking process.
  */
- (BOOL)generateAmbientOcclusionTextureWithQuality:(float)bakeQuality
                                 attenuationFactor:(float)attenuationFactor
                                 objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                              vertexAttributeNamed:(NSString *)vertexAttributeName
                             materialPropertyNamed:(NSString *)materialPropertyName;

- (BOOL)generateAmbientOcclusionVertexColorsWithRaysPerSample:(NSInteger)raysPerSample
                                            attenuationFactor:(float)attenuationFactor
                                            objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                                         vertexAttributeNamed:(NSString *)vertexAttributeName;

- (BOOL)generateAmbientOcclusionVertexColorsWithQuality:(float)bakeQuality
                                      attenuationFactor:(float)attenuationFactor
                                      objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                                   vertexAttributeNamed:(NSString *)vertexAttributeName;

- (BOOL)generateLightMapTextureWithTextureSize:(vector_int2)textureSize
                              lightsToConsider:(NSArray<MDLLight*>*)lightsToConsider
                             objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                          vertexAttributeNamed:(NSString *)vertexAttributeName
                         materialPropertyNamed:(NSString *)materialPropertyName;

- (BOOL)generateLightMapTextureWithQuality:(float)bakeQuality
                          lightsToConsider:(NSArray<MDLLight*>*)lightsToConsider
                         objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                      vertexAttributeNamed:(NSString *)vertexAttributeName
                     materialPropertyNamed:(NSString *)materialPropertyName;

- (BOOL)generateLightMapVertexColorsWithLightsToConsider:(NSArray<MDLLight*>*)lightsToConsider
                                       objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                                    vertexAttributeNamed:(NSString *)vertexAttributeName;

@end

NS_ASSUME_NONNULL_END
