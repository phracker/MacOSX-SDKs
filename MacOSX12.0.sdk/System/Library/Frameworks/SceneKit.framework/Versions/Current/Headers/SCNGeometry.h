//
//  SCNGeometry.h
//  SceneKit
//
//  Copyright © 2012-2021 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNBoundingVolume.h>
#import <SceneKit/SCNShadable.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNGeometrySource;
@class SCNGeometryElement;
@class SCNGeometryTessellator;
@class SCNLevelOfDetail;
@protocol MTLBuffer;

typedef NS_ENUM(NSInteger, SCNGeometryPrimitiveType) {
	SCNGeometryPrimitiveTypeTriangles                                                  = 0,
	SCNGeometryPrimitiveTypeTriangleStrip                                              = 1,
	SCNGeometryPrimitiveTypeLine                                                       = 2,
	SCNGeometryPrimitiveTypePoint                                                      = 3,
    SCNGeometryPrimitiveTypePolygon API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 4
};

typedef NSString * SCNGeometrySourceSemantic NS_EXTENSIBLE_STRING_ENUM;

SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticVertex;
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticNormal;
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticColor;
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticTexcoord;
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticTangent API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticVertexCrease API_AVAILABLE(macos(10.10));
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticEdgeCrease API_AVAILABLE(macos(10.10));
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticBoneWeights API_AVAILABLE(macos(10.10));
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticBoneIndices API_AVAILABLE(macos(10.10));

// MARK: -

/*!
 @class SCNGeometry
 @abstract SCNGeometry is an abstract class that represents the geometry that can be attached to a SCNNode. 
 */

SCN_EXPORT
@interface SCNGeometry : NSObject <SCNAnimatable, SCNBoundingVolume, SCNShadable, NSCopying, NSSecureCoding>

/*!
 @method geometry
 @abstract Creates and returns an empty geometry object.
 @discussion An empty geometry may be used as the lowest level of detail of a geometry.
 */
+ (instancetype)geometry API_AVAILABLE(macos(10.9));

/*!
 @property name
 @abstract Determines the name of the receiver.
 */
@property(nonatomic, copy, nullable) NSString *name;

/*! 
 @property materials
 @abstract Specifies the receiver's materials array.
 @discussion Each geometry element can be rendered using a different material. The index of the material used for a geometry element is equal to the index of that element modulo the number of materials.
 */
@property(nonatomic, copy) NSArray<SCNMaterial *> *materials;

/*!
 @property firstMaterial
 @abstract Determines the first material of the geometry. Returns nil if the geometry has no material.
 @discussion This method is here for convenience. It is equivalent to the first object in the "materials" array above.
 */
@property(nonatomic, retain, nullable) SCNMaterial *firstMaterial;

/*! 
 @method insertMaterial:atIndex:
 @abstract Insert a material in the materials array at the specified index.
 @param material The material to insert.
 @param index Index in the materials array to insert the new material.
 */
- (void)insertMaterial:(SCNMaterial *)material atIndex:(NSUInteger)index;

/*! 
 @method removeMaterialAtIndex:
 @abstract Remove the material at the specified index from the materials array.
 @param index The index of the material to remove from the 'materials' array.
 */
- (void)removeMaterialAtIndex:(NSUInteger)index;

/*! 
 @method replaceMaterialAtIndex:withMaterial:
 @abstract Remove the material at the index 'index' from the materials array of the receiver and insert 'material' in its position.
 @param index The index of the material to replace in the materials array.
 @param material The new material that will replace the previous one.
 */
- (void)replaceMaterialAtIndex:(NSUInteger)index withMaterial:(SCNMaterial *)material;

/*! 
 @method materialWithName:
 @abstract Return the first material from the materials array of the receiver with the specified name.
 @param name The name of the material to retrieve.
 */
- (nullable SCNMaterial *)materialWithName:(NSString *)name;

/*! 
 @method geometryWithSources:elements:
 @abstract Creates and returns a new geometry built from geometry sources and geometry elements.
 @param sources An array of geometry sources. If several geometry sources have the same semantic, only the first one is taken into account.
 @param elements An array of geometry elements. The sort order in the array determines the mapping between materials and geometry elements.
 @discussion A geometry is made of geometry sources (at least vertices) and at least one geometry element. Multiple sources for texture coordinates are accepted. In that case the mappingChannel is implicitly set based on the order of the texture sources, starting at index 0.
*/
+ (instancetype)geometryWithSources:(NSArray<SCNGeometrySource *> *)sources elements:(nullable NSArray<SCNGeometryElement *> *)elements;

/*!
 @property geometrySources
 @abstract The array of geometry sources of the receiver.
 */
@property(nonatomic, readonly) NSArray<SCNGeometrySource *> *geometrySources API_AVAILABLE(macos(10.10));

/*! 
 @method geometrySourcesForSemantic:
 @abstract Returns the geometry sources for a given semantic.
 @param semantic The semantic of the geometry sources that should be retrieved.
 @discussion Returns nil if no geometry source is found for the given semantic. May return more than one source, typically for multiple texture coordinate sources.
 */
- (NSArray<SCNGeometrySource *> *)geometrySourcesForSemantic:(SCNGeometrySourceSemantic)semantic;

/*!
 @property geometryElements
 @abstract The array of geometry elements of the receiver.
 */
@property(nonatomic, readonly) NSArray<SCNGeometryElement *> *geometryElements API_AVAILABLE(macos(10.10));

/*!
 @property geometryElementCount
 @abstract Returns the number of geometry elements owned by the geometry.
 */
@property(nonatomic, readonly) NSInteger geometryElementCount;

/*!
 @method geometryElementAtIndex:
 @abstract Returns the geometry element at a given index.
 @param elementIndex The index of the geometry element.
 */
- (SCNGeometryElement *)geometryElementAtIndex:(NSInteger)elementIndex;

/*!
 @property levelsOfDetail
 @abstract Determines the receiver's levels of detail. Defaults to nil.
 */
@property(nonatomic, copy, nullable) NSArray<SCNLevelOfDetail *> *levelsOfDetail API_AVAILABLE(macos(10.9));

/*!
 @property tessellator
 @abstract Specifies how the geometry should be tessellated at render time on the GPU. Defaults to nil.
 */
#if SCN_ENABLE_METAL
@property(nonatomic, retain, nullable) SCNGeometryTessellator *tessellator API_AVAILABLE(macos(10.13), ios(11.0), tvos(12.0)) API_UNAVAILABLE(watchos);
#endif

/*!
 @property subdivisionLevel
 @abstract Specifies the subdivision level of the receiver. Defaults to 0.
 @discussion A subdivision level of 0 means no subdivision. When the `tessellator` property of the receiver is not nil, the refinement is done on the GPU.
 */
@property(nonatomic) NSUInteger subdivisionLevel API_AVAILABLE(macos(10.10));

/*!
 @property wantsAdaptiveSubdivision
 @abstract Specifies if the subdivision is adaptive or uniform. Defaults to YES.
 @discussion Adaptive subdivision requires that the `tessellator` property of the receiver is not nil.
 */
@property(nonatomic) BOOL wantsAdaptiveSubdivision API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property edgeCreasesElement
 @abstract Specifies the edges creases that control the subdivision. Defaults to nil.
 @discussion The primitive type of this geometry element must be SCNGeometryPrimitiveTypeLine. See subdivisionLevel above to control the level of subdivision. See edgeCreasesSource below to specify sharpness of the creases.
 */
@property(nonatomic, retain, nullable) SCNGeometryElement *edgeCreasesElement API_AVAILABLE(macos(10.10));

/*!
 @property edgeCreasesSource
 @abstract Specifies the crease value of the edges specified by edgeCreasesElement. Defaults to nil.
 @discussion The semantic of this geometry source must be "SCNGeometrySourceSemanticEdgeCrease". The creases values are floating values between 0 and 10, where 0 means smooth and 10 means infinitely sharp. See subdivisionLevel above to control the level of subdivision. See edgeCreasesElement above to specify edges for edge creases.
 */
@property(nonatomic, retain, nullable) SCNGeometrySource *edgeCreasesSource API_AVAILABLE(macos(10.10));

@end

// MARK: -

/*!
 @class SCNGeometrySource
 @abstract A geometry source contains geometry data for a specific semantic. The data format is described by properties.
 */

SCN_EXPORT
@interface SCNGeometrySource : NSObject <NSSecureCoding>

/*! 
 @method geometrySourceWithData:semantic:vectorCount:floatComponents:componentsPerVector:bytesPerComponent:dataOffset:dataStride:
 @abstract Creates and returns a geometry source from the given data and parameters.
 @param data The geometry data.
 @param semantic The semantic of the geometry source.
 @param vectorCount The number of geometry source vectors.
 @param floatComponents A flag that indicates if vector components are floating point values.
 @param componentsPerVector The number of scalar components in a vector.
 @param bytesPerComponent The number of bytes that represent a vector component.
 @param offset The offset from the beginning of the data. In bytes.
 @param stride The number of bytes from a vector to the next one in the data.
 */
+ (instancetype)geometrySourceWithData:(NSData *)data semantic:(SCNGeometrySourceSemantic)semantic vectorCount:(NSInteger)vectorCount floatComponents:(BOOL)floatComponents componentsPerVector:(NSInteger)componentsPerVector bytesPerComponent:(NSInteger)bytesPerComponent dataOffset:(NSInteger)offset dataStride:(NSInteger)stride;

/*!
 @method geometrySourceWithVertices:count:
 @abstract Creates and returns a geometry source from vertices stored in a buffer of SCNVector3 values.
 @param vertices The buffer of vertices.
 @param count The number of vertices.
 @discussion Input vertices are copied to an optimized data format. The actual format is described by the properties of the resulting instance.
 */
+ (instancetype)geometrySourceWithVertices:(const SCNVector3 *)vertices count:(NSInteger)count;

/*!
 @method geometrySourceWithNormals:count:
 @abstract Creates and returns a geometry source from normals stored in a buffer of SCNVector3 values.
 @param normals The buffer of normals.
 @param count The number of normals.
 @discussion Input normals are copied to an optimized data format. The actual format is described by the properties of the resulting instance.
 */
+ (instancetype)geometrySourceWithNormals:(const SCNVector3 *)normals count:(NSInteger)count;

/*!
 @method geometrySourceWithTextureCoordinates:count:
 @abstract Creates and returns a geometry source from texture coordinates stored in a buffer of CGPoint values.
 @param texcoord The buffer of texture coordinates.
 @param count The number of texture coordinate points.
 @discussion Input texture coordinates are copied to an optimized data format. The actual format is described by the properties of the resulting instance.
 */
+ (instancetype)geometrySourceWithTextureCoordinates:(const CGPoint *)texcoord count:(NSInteger)count;

#if SCN_ENABLE_METAL
/*!
 @method geometrySourceWithBuffer:semantic:vectorCount:floatComponents:componentsPerVector:bytesPerComponent:dataOffset:dataStride:
 @abstract Creates and returns a geometry source from the given data and parameters.
 @param buffer A Metal buffer.
 @param vertexFormat The vertex format.
 @param semantic The semantic of the geometry source.
 @param vertexCount The number of vertex.
 @param offset The offset from the beginning of the data. In bytes.
 @param stride The number of bytes from a vector to the next one in the data.
 @discussion Attempting to modify the Metal buffer outside the SCNSceneRenderer delegate callbacks is undefined.
 The typical usage it to modify the MTLBuffer within the willRenderScene callback, using a compute kernel or a vertex function in the user own command buffer. So something like:

 - (void)renderer:(id <SCNSceneRenderer>)aRenderer willRenderScene:(SCNScene *)scene atTime:(NSTimeInterval)time
 {
     // ask for a new command buffer
     id <MTLCommandBuffer> myCommandBuffer = [aRenderer.commandQueue commandBuffer];

     // get a compute command encoder
     id <MTLComputeCommandEncoder> myComputeCommandEncoder = [myCommandBuffer computeCommandEncoder];

     // configure the compute command encoder's pipeline state, buffer inputs etc...
     //...

     // dispatch the
     [myComputeCommandEncoder dispatchThreadgroups:numberOfWorkingGroups threadsPerThreadgroup:numberOfThreads];
     [myComputeCommandEncoder endEncoding];

     [myCommandBuffer commit];
 }
 
 */
+ (instancetype)geometrySourceWithBuffer:(id <MTLBuffer>)buffer vertexFormat:(MTLVertexFormat)vertexFormat semantic:(SCNGeometrySourceSemantic)semantic vertexCount:(NSInteger)vertexCount dataOffset:(NSInteger)offset dataStride:(NSInteger)stride API_AVAILABLE(macos(10.11), ios(9.0));
#endif

/*! 
 @property data
 @abstract The data for the geometry source
 */
@property(nonatomic, readonly) NSData *data;

/*! 
 @property semantic
 @abstract The semantic of the geometry source
 */
@property(nonatomic, readonly) SCNGeometrySourceSemantic semantic;

/*! 
 @property vectorCount
 @abstract The number of vectors in the data.
 */
@property(nonatomic, readonly) NSInteger vectorCount;

/*! 
 @property floatComponents
 @abstract A flag that indicates if vector components are floating point values.
 */
@property(nonatomic, readonly) BOOL floatComponents;

/*! 
 @property componentsPerVector
 @abstract The number of scalar components in each vector.
 */
@property(nonatomic, readonly) NSInteger componentsPerVector;

/*! 
 @property bytesPerComponent
 @abstract The size of a vector component in bytes.
 */
@property(nonatomic, readonly) NSInteger bytesPerComponent;

/*! 
 @property dataOffset
 @abstract The offset from the beginning of the data. In bytes.
 */
@property(nonatomic, readonly) NSInteger dataOffset;

/*! 
 @property dataStride
 @abstract The number of bytes from a vector to the next one in the data.
 */
@property(nonatomic, readonly) NSInteger dataStride;

@end

// MARK: -

/*!
 @class SCNGeometryElement
 @abstract A geometry element describes how vertices from a geometry source are connected together.
 */

SCN_EXPORT
@interface SCNGeometryElement : NSObject <NSSecureCoding>

/*!
 @method geometryElementWithData:primitiveType:primitiveCount:bytesPerIndex:
 @abstract Creates and returns a geometry element from the given data and data format info.
 @param data The data that contains element indexes. You can pass nil to use an implicit vertex ordering (0,1,2...).
 @param primitiveType The primitive type, as listed in the SCNGeometryPrimitiveType enumeration.
 @param primitiveCount The number of primitives in the data.
 @param bytesPerIndex The number of bytes that represent a single index value in the data.
 */
+ (instancetype)geometryElementWithData:(nullable NSData *)data primitiveType:(SCNGeometryPrimitiveType)primitiveType primitiveCount:(NSInteger)primitiveCount bytesPerIndex:(NSInteger)bytesPerIndex;

#if SCN_ENABLE_METAL
/*!
@method geometryElementWithBuffer:primitiveType:primitiveCount:bytesPerIndex
@abstract Creates and returns a geometry element from the given Metal buffer and parameters.
@param buffer The buffer that contains element indexes.
@param primitiveType The primitive type, as listed in the SCNGeometryPrimitiveType enumeration.
@param primitiveCount The number of primitives in the data.
@param bytesPerIndex The number of bytes that represent a single index value in the data.
*/
+ (instancetype)geometryElementWithBuffer:(id <MTLBuffer>)buffer
                            primitiveType:(SCNGeometryPrimitiveType)primitiveType
                           primitiveCount:(NSInteger)primitiveCount
                            bytesPerIndex:(NSInteger)bytesPerIndex API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0));
#endif

/*!
 @property data
 @abstract The data for the geometry element
 */
@property(nonatomic, readonly) NSData *data;

/*!
 @property primitiveType
 @abstract The type of the geometry element. Possible values are listed in the SCNGeometryPrimitiveType enumeration.
 */
@property(nonatomic, readonly) SCNGeometryPrimitiveType primitiveType;

/*!
 @property primitiveCount
 @abstract The number of primitives in the data.
 */
@property(nonatomic, readonly) NSInteger primitiveCount;

/*!
 @property primitiveRange
 @abstract Specifies the subrange of primitves to render within NSMakeRange(0, primitiveCount). Defaults to NSMakeRange(NSNotFound, 0).
 @discussion When the location of the range is set to NSNotFound, the entire geometry element is rendered.
 */
@property(nonatomic) NSRange primitiveRange API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property bytesPerIndex
 @abstract The number of bytes that represent an index value
 */
@property(nonatomic, readonly) NSInteger bytesPerIndex;

/*!
 @property pointSize
 @abstract Specifies the size of the point in local space. Defaults to 1
 */
@property(nonatomic) CGFloat pointSize API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property minimumPointScreenSpaceRadius
 @abstract Specifies the minimum size in screen-space (in pixel). Defaults to 1
 */
@property(nonatomic) CGFloat minimumPointScreenSpaceRadius API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property maximumPointScreenSpaceRadius
 @abstract Specifies the maximum size in screen-space (in pixel). Defaults to 1
 */
@property(nonatomic) CGFloat maximumPointScreenSpaceRadius API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@end

// MARK: -

#if SCN_ENABLE_METAL

typedef NS_ENUM(NSInteger, SCNTessellationSmoothingMode) {
    SCNTessellationSmoothingModeNone = 0,
    SCNTessellationSmoothingModePNTriangles,
    SCNTessellationSmoothingModePhong
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(12.0)) API_UNAVAILABLE(watchos);

/*!
 @class SCNGeometryTessellator
 @abstract A geometry tessellator describes how a more detailed surface is calculated from the geometry's initial surface.
 */

SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(12.0)) API_UNAVAILABLE(watchos)
@interface SCNGeometryTessellator : NSObject <NSCopying, NSSecureCoding>

/*!
 @property tessellationFactorScale
 @abstract Specifies the scale factor applied to the per-patch tessellation factors. Defaults to 1.
 */
@property(nonatomic) CGFloat tessellationFactorScale;

/*!
 @property tessellationPartitionMode
 @abstract Specifies the tessellation partition mode. Defaults to MTLTessellationPartitionModeInteger.
 */
@property(nonatomic) MTLTessellationPartitionMode tessellationPartitionMode;

/*!
 @property adaptive
 @abstract Specifies if the tessellation should be uniform or adaptive. Defaults to NO.
 */
@property(nonatomic, getter=isAdaptive) BOOL adaptive;

/*!
 @property screenspace
 @abstract Specifies if the level of tessellation should be adapted in screenSpace. Defaults to NO.
 */
@property(nonatomic, getter=isScreenSpace) BOOL screenSpace;

/*!
 @property edgeTessellationFactor
 @abstract Specifies the edge tessellation factor. Defaults to 1.
 @discussion This has no effect for adaptive subdivision
 */
@property(nonatomic) CGFloat edgeTessellationFactor;

/*!
 @property insideTessellationFactor
 @abstract Specifies the inside tessellation factor. Defaults to 1.
 @discussion This has no effect for adaptive subdivision
 */
@property(nonatomic) CGFloat insideTessellationFactor;

/*!
 @property maximumEdgeLength
 @abstract Specifies the maximum edge length. Defaults to 1.
 @discussion This has no effect for non-adaptive subdivision
 */
@property(nonatomic) CGFloat maximumEdgeLength;

/*!
 @property smoothingMode
 @abstract Defaults to SCNTessellationSmoothingModeNone.
 */
@property(nonatomic) SCNTessellationSmoothingMode smoothingMode;

@end

#endif

NS_ASSUME_NONNULL_END
