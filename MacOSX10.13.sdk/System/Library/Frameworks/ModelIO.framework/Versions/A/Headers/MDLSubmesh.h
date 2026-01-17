/*!
 @header MDLSubmesh.h
 @framework ModelIO
 @abstract Structures for describing renderable elements of a mesh
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */


#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLMaterial.h>
#import <ModelIO/MDLMeshBuffer.h>

NS_ASSUME_NONNULL_BEGIN

@class MDLSubmesh;

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLSubmeshTopology : NSObject

/*! 
 @method initWithSubmesh:
 @abstract create a topology object corresponding to the topology in the submesh
 */
- (instancetype) initWithSubmesh:(MDLSubmesh*)submesh;

/*!
 @property faceTopologyBuffer
 @abstract A buffer of 8 bit unsigned integer values, where each entry corresponds
 to the number of vertices making up a face.
 
 @discussion A submesh containing two triangles, a four sided polygon, and a
 line, would contain the data 3 3 4 2.
 If geometryType is of a fixed type, such as triangles, the buffer
 is optional, and will be created on demand if read.
 
 Indices to the vertex buffer will be stored in the index buffer
 correspondingly. In the example above, the indices would be stored
 in order, three indices for the first triangle, followed by three
 for the second, followed by four for the polygon, and finally two
 indices for the line.
 */
@property (nonatomic, retain, nullable) id<MDLMeshBuffer> faceTopology;

/*!
 @property faceCount
 @abstract The number of faces encoded in faceTopologyBuffer
 */
@property (nonatomic) NSUInteger faceCount;

/*! A crease value at a vertex to be applied during subdivision. Vertex creases
 A zero value is smooth, a one value is peaked. It is intended to be used
 with an index buffer, where the index buffer entries are vertex indices.
 The corresponding values in the corner sharpness attribute indicate the
 corner sharpness of those vertices. The index buffer is sparse. If a mesh
 has three sharp vertices, then the index buffer will have three entries.
 Since the number of entries in this vertex buffer is likely to be different
 than the number of entries in any other vertex buffer, it shouldn't be
 interleaved with other data.
 */
@property (nonatomic, retain, nullable) id<MDLMeshBuffer> vertexCreaseIndices;
@property (nonatomic, retain, nullable) id<MDLMeshBuffer> vertexCreases;

/*!
 @property vertexCreaseCount
 @abstract The number of vertex creases encoded in vertexCreases
 */
@property (nonatomic) NSUInteger vertexCreaseCount;

/*! A crease value at an edge to be applied during subdivision. Edge creases
 A zero value is smooth, a one value is peaked. It is intended to be used
 with an index buffer, where the index buffer entries are edge index pairs.
 Accordingly, there will be two index entries for each edge sharpness entry,
 and the sharpness entry corresponds to the edge itself.
 The corresponding values in the edge sharpness attribute indicate the
 edge sharpness of those edges.  The index buffer is sparse. If a mesh
 has three sharp edges, then the index buffer will have six entries.
 Since the number of entries in this vertex buffer is likely to be different
 than the number of entries in any other vertex buffer, it shouldn't be
 interleaved with other data.
 */
@property (nonatomic, retain, nullable) id<MDLMeshBuffer> edgeCreaseIndices;
@property (nonatomic, retain, nullable) id<MDLMeshBuffer> edgeCreases;

/*!
 @property edgeCreaseCount
 @abstract The number of edge creases encoded in edgeCreases
 */
@property (nonatomic) NSUInteger edgeCreaseCount;

/*! The hole attribute is a vertex attribute of single integer values where
 each integer is an index of a face that is to be used as a hole. If there
 are two holes in a mesh, then the vertex buffer will have two entries.
 Since the number of entries in this vertex buffer is likely to be different
 than the number of entries in any other vertex buffer, it shouldn't be
 interleaved with other data.
 */
@property (nonatomic, retain, nullable) id<MDLMeshBuffer> holes;

/*!
 @property holeCount
 @abstract The number of holes encoded in holes
 */
@property (nonatomic) NSUInteger holeCount;

@end

/*!
 @class MDLSubmesh
 @abstract A drawable subset of an MDLMesh, with its own material
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLSubmesh : NSObject<MDLNamed>

/*!
 @method initWithName:indexBuffer:indexCount:indexType:geometryType:material:
 @abstract Initialize submesh with all data necessary to make properties valid
 */
- (instancetype)initWithName:(NSString *)name
                 indexBuffer:(id<MDLMeshBuffer>)indexBuffer
                  indexCount:(NSUInteger)indexCount
                   indexType:(MDLIndexBitDepth)indexType
                geometryType:(MDLGeometryType)geometryType
                    material:(nullable MDLMaterial *)material;

/*!
 @method initWithIndexBuffer:indexCount:indexType:geometryType:material:
 @abstract Initialize submesh with all data necessary to make properties valid
 */
- (instancetype)initWithIndexBuffer:(id<MDLMeshBuffer>)indexBuffer
                         indexCount:(NSUInteger)indexCount
                          indexType:(MDLIndexBitDepth)indexType
                       geometryType:(MDLGeometryType)geometryType
                           material:(nullable MDLMaterial *)material;

/*!
 @method initWithIndexBuffer:indexCount:indexType:faceTopologyBuffer:geometryType:material:
 @abstract Initialize submesh with all data necessary to make properties valid
 
 @discussion The geometry type will typically be MDLGeometryTypeVariableTopology,
             if other types are used the faceTopologyBuffer contents should
             reflect that.
 */
- (instancetype)initWithName:(NSString *)name
                 indexBuffer:(id<MDLMeshBuffer>)indexBuffer
                  indexCount:(NSUInteger)indexCount
                   indexType:(MDLIndexBitDepth)indexType
                geometryType:(MDLGeometryType)geometryType
                    material:(nullable MDLMaterial *)material
                    topology:(nullable MDLSubmeshTopology *)topology;

/*!
 @method initWithMDLSubmesh:indexType:geometryType:
 @abstract Initialize submesh using another submesh as input.
 @discussion the resulting submesh will have a new index type if necessary.
  If a conversion from the source submesh's geometry type to the requested
  geometry type is possible, conversion will be performed. Otherwise nil will
  be returned.
 */
- (nullable instancetype)initWithMDLSubmesh:(nonnull MDLSubmesh*)submesh
                                  indexType:(MDLIndexBitDepth)indexType
                               geometryType:(MDLGeometryType)geometryType;

/*!
 @property indexBuffer
 @abstract Index data referencing vertex data in parent mesh
 */
@property (nonatomic, readonly, retain) id<MDLMeshBuffer> indexBuffer;

- (id<MDLMeshBuffer>)indexBufferAsIndexType:(MDLIndexBitDepth)indexType;

/*!
 @property indexCount
 @abstract Number of indices in the indexBuffer
 */
@property (nonatomic, readonly) NSUInteger indexCount;

/*!
 @property indexType
 @abstract Data type of indices in indexBuffer
 @discussion Support 8, 16, and 32 bit unsigned integer values
 */
@property (nonatomic, readonly) MDLIndexBitDepth indexType;

/*!
 @property geometryType
 @abstract Type of primitive that vertices referenced by the indexBuffer are 
           assembled into
 */
@property (nonatomic, readonly) MDLGeometryType geometryType;

/*!
 @property material
 @abstract Material to apply when rendering this object
 */
@property (nonatomic, retain, nullable) MDLMaterial *material;

/*!
 @property topology
 @abstract Topology data structure for use with MDLGeometryTypeVariableTopology
 
 @discussion ignored for geometry types other than MDLGeometryTypeVariableTopology.
             A submesh of type MDLGeometryTypeVariableTopology with no topology
             data is an empty submesh.
*/
@property (nonatomic, retain, nullable) MDLSubmeshTopology *topology;

/*!
 @property name
 @abstract Identifying name for this object
 */
@property (nonatomic, copy) NSString *name;

@end

NS_ASSUME_NONNULL_END
