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
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLVertexAttributeData : NSObject

@property (nonatomic, retain) NSData *mappedData;
@property (nonatomic) void *dataStart;
@property (nonatomic) NSUInteger stride;
@property (nonatomic) MDLVertexFormat format;

@end


/*!
 @class MDLMesh
 @abstract A vertex buffer with info to interpret vertex data
 @discussion Includes a collection of submeshs which have indexbuffer and
             material information
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLMesh : MDLObject

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
 @param vertexBuffer An array of MDLMeshBuffer objects containing vertex data 
         for the mesh
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
             property.  As this property implements the copy attribute, a copy
             is always made on acces, thus change attributes and buffer layouts
             from in property will have no affect.
 */
@property (nonatomic, readwrite, copy) MDLVertexDescriptor *vertexDescriptor;

/*!
 @property vertexCount
 @abstract Number of vertices in the vertexBuffers
 @discussion The size of vertex data in each buffer can be compute by multiplying 
             this value with the stride of the buffer in the vertexDescriptor's 
             layout
 */
@property (nonatomic, readonly) NSUInteger vertexCount;

/*!
 @property vertexBuffers
 @abstract Array of buffers containing vertex data
 */
@property (nonatomic, readonly, retain) NSMutableArray<id<MDLMeshBuffer>> *vertexBuffers;

/*!
 @property submeshes
 @abstract Array of submeshes containing an indexbuffer referencing the vertex 
           data and material to be applied when the mesh is rendered
 */
@property (nonatomic, readonly, retain) NSMutableArray<MDLSubmesh*> *submeshes;

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
 @method addNormalsWithAttributeNamed:bufferIndex:
 @abstract Calculate and add vertex normal data
 @param attributeName Name of vertex normal attribute.  If nil, vertex normals 
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
 @abstract Create tangent basis data
 @param textureCoordinateAttributeName texture coordinates to use in calculations
 @param tangentAttributeName Name of vertex tangent attribute.
 @param bitangentAttributeNamed Name of vertex bitangent attribute.
 @discussion Uses the attribute named MDLVertexAttributePosition and
             textureCoordinateAttributeName to calculate tangent and bitangent
             attributes. The mesh's vertexDescriptor will be updated to reflect 
             the new attributes if necessary.
 */
- (void)addTangentBasisForTextureCoordinateAttributeNamed:(NSString*)textureCoordinateAttributeName
                                    tangentAttributeNamed:(NSString *)tangentAttributeName
                                  bitangentAttributeNamed:(nullable NSString *)bitangentAttributeName;

/*!
 @method addTangentBasisForTextureCoordinateAttributeNamed:normalAttributeNamed:tangentAttributeNamed
 @abstract Create tangent basis data
 @param textureCoordinateAttributeName texture coordinates to use in calculations
 @param normalAttributeNamed normals to use in calculations
 @param tangentAttributeName Name of a four component vertex tangent attribute.
 @discussion Uses the attribute named MDLVertexAttributePosition and
             textureCoordinateAttributeName and the specified normals to calculate 
             tangent information. The mesh's vertexDescriptor will be updated to 
             reflect the new attribute if necessary.
             Note that the bitangent can be calculated from the normal and 
             tangent by B = (N x T) * T.w
 */
- (void)addTangentBasisForTextureCoordinateAttributeNamed:(NSString*)textureCoordinateAttributeName
                                     normalAttributeNamed:(NSString*)normalAttributeName
                                    tangentAttributeNamed:(NSString *)tangentAttributeName;

/*!
 @method makeVerticesUnique:
 @abstract Deindexes the vertex array
 @discussion If any vertices are shared on multiple faces, duplicate those 
             vertices so faces do not share vertices. The vertex buffer and index 
             buffers on submeshes may grow to accomadate any vertices added.
 */
- (void)makeVerticesUnique;


@end






@interface MDLMesh (Generators)

/*!
 @method newBox:segments:inwardNormals:geometryType:allocator:
 @abstract Factory method for generating a mesh with a cube shape
 @return Mesh with desired attributes.  nil if geometryType is not triangles or quads.
 @param dimensions Width, height, and depth of the box
 @param segments Number of slices in each dimension
 @param inwardNormals Generated Normal point inward
 @param geometryType Can be either quads or triangles
 @param allocator A mesh buffer allocator used to allocate memory to back buffers 
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Assembled with triangle or quad primitives.  Specifying inward 
             normals is useful for generating a skybox. The center of the box 
             is at 0, 0, 0.
 */
+ (instancetype)newBox:(vector_float3)dimensions
              segments:(vector_uint3)segments
         inwardNormals:(BOOL)inwardNormals
          geometryType:(MDLGeometryKind)geometryType
             allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method newEllipsoid:radialSegments:verticalSegments:inwardNormals:hemisphere:allocator:
 @abstract Factory method for generating a mesh with an ellipsoid shape
 @param radii Width, height, and depth of ellipsoid. To generate a sphere all
        values should be equal.
 @param radialSegments Number of pie slices :)
 @param verticalSegments Number of slices in the vertical direction
 @param geometryType Must be MDLGeometryKindTriangles
 @param inwardNormals If true, generated normals will face inwards. Useful for 
        generating a skydome.
 @param geometryType Can be either quads or triangles
 @param hemisphere If true, only top half of elipsoid will be generated. The 
        actual nubmer of vertical slices will be half of 'vertical' segments
 @param allocator A mesh buffer allocator used to allocate memory to back buffers 
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Assembled with triangle primitives.  Specifying inward normals and 
             hemisphere is useful for generating a skydome.  Will return nil if
             radialSegments is < 3 and verticalSegments is < 3.
 */
+ (instancetype)newEllipsoid:(vector_float3)radii
              radialSegments:(NSUInteger)radialSegments
            verticalSegments:(NSUInteger)verticalSegments
                geometryType:(MDLGeometryKind)geometryType
               inwardNormals:(BOOL)inwardNormals
                  hemisphere:(BOOL)hemisphere
                   allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method generateCylindroid:radii:radialSegments:verticalSegments:inwardNormals:allocator:
 @abstract Factory method for generating a mesh with an cylindroid shape
 @param height Height of cylindoid.
 @param radii Radii of cylindroid in X and Z directions.  Values of vector should 
        be equal to create a true cylinder
 @param radialSegments Number of pie slices :)
 @param verticalSegments Number of slices along Y axis
 @param geometryType Must be MDLGeometryKindTriangles
 @param inwardNormals Normals point toward center of cylindroid
 @param allocator A mesh buffer allocator used to allocate memory to back buffers 
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Assembled with triangle primitives.  Center of cylindroid at (0, 0, 0) 
             with a top at +Y and bottom at -Y.  Will return nil if 
             radialSegments is < 3 and verticalSegments is < 1.
 */
+ (instancetype)newCylindroid:(float)height
                        radii:(vector_float2)radii
               radialSegments:(NSUInteger)radialSegments
             verticalSegments:(NSUInteger)verticalSegments
                 geometryType:(MDLGeometryKind)geometryType
                inwardNormals:(BOOL)inwardNormals
                    allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method generateEllipticalCone::radii:radialSegments:verticalSegments:inwardNormals:allocator:
 @abstract Factory method for generating a mesh with an elipticalCone shape.
 @param height Height of elipticalCone from point to base.
 @param radii Radii of base in X and Z directions.  Values of vector should be 
        equal to create a true cone.
 @param radialSegments Number of pie slices :)
 @param verticalSegments Number of slices along Y axis
 @param geometryType Must be MDLGeometryKindTriangles
 @param inwardNormals Normals point toward center of elipticalCone
 @param allocator A mesh buffer allocator used to allocate memory to back buffers 
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Assembled with triangle primitives.  Point of cone at (0, 0, 0) 
             while base of cone is -Y. Will return nil if radialSegments is < 3 
             and verticalSegments is < 1.
 */
+ (instancetype)newEllipticalCone:(float)height
                            radii:(vector_float2)radii
                   radialSegments:(NSUInteger)radialSegments
                 verticalSegments:(NSUInteger)verticalSegments
                     geometryType:(MDLGeometryKind)geometryType
                    inwardNormals:(BOOL)inwardNormals
                        allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method generatePlane:segments:geometryType:allocator:
 @abstract Factory method for generating a mesh with an planar shape
 @return Mesh with desired attributes.  nil if geometryType is not triangles or quads
 @param dimensions Dimensions of  of elipticalCone in X and Z directions.
 @param segments Number of segements in the X and Y dimensions
 @param geometryType Can be MDLGeometryKindQuads or MDLGeometryKindTriangles.
 @param allocator A mesh buffer allocator used to allocate memory to back buffers 
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Assembled with triangle or quad primitives. Creates a plane along 
             the X/Z axis. Center of plane at (0, 0, 0). All normals point up,
             towards positive Y
 */
+ (instancetype)newPlane:(vector_float2)dimensions
                segments:(vector_uint2)segments
            geometryType:(MDLGeometryKind)geometryType
               allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method generateIcosahedron:inwardNormals:allocator:
 @abstract Factory method for generating a mesh icosahedron
 @param radius Distance from the center to the outermost point of the mesh
 @param inwardNormals Generated normals will face towards the center of the mesh
 @param allocator A mesh buffer allocator used to allocate memory to back buffers 
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Assembled with triangles. Creates an icosahedron with center at 0,0,0
 */
+ (instancetype)newIcosahedron:(float)radius
                 inwardNormals:(BOOL)inwardNormals
                     allocator:(nullable id<MDLMeshBufferAllocator>)allocator;


/*!
 @method generateSubdividedMesh:subdivisionLevels:allocator:
 @abstract Factory method that generates a subdivided mesh from a source mesh
 @param mesh Mesh from which to generate a subdivided mesh
 @param submeshIndex Index of submesh in Mesh's submesh array from which to
        generate a subdivided mesh
 @param subdivisionLevels The number of levels to subdivide mesh
 @discussion Subdivision levels over four are likely to generate more triangles 
             than can be reasonably displayed. Index and vertex data will use 
             the same allocator used for the source mesh.
 @return Returns a mesh subdividied to index level, unless subdivision is 
         impossible.  Only triangle and quadrilateral meshes can be subdivided.
 */
+ (nullable instancetype)newSubdividedMesh:(MDLMesh*)mesh
                              submeshIndex:(NSUInteger)submeshIndex
                         subdivisionLevels:(NSUInteger)subdivisionLevels;

@end



@interface MDLMesh (MDLLightBaking)

/*!
 @method generateAmbientOcclusionTextureWithSize:
 @abstract Creates an Ambient Occlusion texture, returns true upon success, false 
           upon failure
 @param size  Texture Size in which to bake the ambient occlusion
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
 @param quality Float between 0 and 1 that defines quality of the bake process.
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
