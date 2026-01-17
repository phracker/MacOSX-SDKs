//
//  SCNGeometry.h
//
//  Copyright (c) 2012-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNBoundingVolume.h>
#import <SceneKit/SCNShadable.h>

@class SCNGeometrySource;
@class SCNGeometryElement;

typedef NS_ENUM(NSInteger, SCNGeometryPrimitiveType) {
	SCNGeometryPrimitiveTypeTriangles     = 0,
	SCNGeometryPrimitiveTypeTriangleStrip = 1,
	SCNGeometryPrimitiveTypeLine          = 2,
	SCNGeometryPrimitiveTypePoint         = 3
};

SCN_EXTERN NSString * const SCNGeometrySourceSemanticVertex;
SCN_EXTERN NSString * const SCNGeometrySourceSemanticNormal;
SCN_EXTERN NSString * const SCNGeometrySourceSemanticColor;
SCN_EXTERN NSString * const SCNGeometrySourceSemanticTexcoord;
SCN_EXTERN NSString * const SCNGeometrySourceSemanticVertexCrease SCENEKIT_AVAILABLE(10_10, 8_0);
SCN_EXTERN NSString * const SCNGeometrySourceSemanticEdgeCrease SCENEKIT_AVAILABLE(10_10, 8_0);
SCN_EXTERN NSString * const SCNGeometrySourceSemanticBoneWeights SCENEKIT_AVAILABLE(10_10, 8_0);
SCN_EXTERN NSString * const SCNGeometrySourceSemanticBoneIndices SCENEKIT_AVAILABLE(10_10, 8_0);

/*!
 @class SCNGeometry
 @abstract SCNGeometry is an abstract class that represents the geometry that can be attached to a SCNNode. 
 */

SCENEKIT_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNGeometry : NSObject <SCNAnimatable, SCNBoundingVolume, SCNShadable, NSCopying, NSSecureCoding>
{
@private
	id _geometryReserved;
}

/*!
 @method geometry
 @abstract Creates and returns an empty geometry object.
 @discussion An empty geometry may be used as the lowest level of detail of a geometry.
 */
+ (instancetype)geometry SCENEKIT_AVAILABLE(10_9, 8_0);

/*! 
 @property name
 @abstract Determines the name of the receiver.
 */
@property(nonatomic, copy) NSString *name;

/*! 
 @property materials
 @abstract Specifies the receiver's materials array.
 @discussion Each geometry element can be rendered using a different material. The index of the material used for a geometry element is equal to the index of that element modulo the number of materials.
 */
@property(nonatomic, copy) NSArray *materials;

/*!
 @property firstMaterial
 @abstract Determines the first material of the geometry. Returns nil if the geometry has no material.
 @discussion This method is here for convenience. It is equivalent to the first object in the "materials" array above.
 */
@property(nonatomic, retain) SCNMaterial *firstMaterial;

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
- (SCNMaterial *)materialWithName:(NSString *)name;

/*! 
 @method geometryWithSources:elements:
 @abstract Creates and returns a new geometry built from geometry sources and geometry elements.
 @param sources An array of geometry sources. If several geometry sources have the same semantic, only the first one is taken into account.
 @param elements An array of geometry elements. The sort order in the array determines the mapping between materials and geometry elements.
 @discussion A geometry is made of geometry sources (at least vertices) and at least one geometry element. Multiple sources for texture coordinates are accepted. In that case the mappingChannel is implicitly set based on the order of the texture sources, starting at index 0.
*/
+ (instancetype)geometryWithSources:(NSArray *)sources elements:(NSArray *)elements;

/*! 
 @method geometrySourcesForSemantic:
 @abstract Returns the geometry sources for a given semantic.
 @param semantic The semantic of the geometry sources that should be retrieved.
 @discussion Returns nil if no geometry source is found for the given semantic. May return more than one source, typically for multiple texture coordinate sources.
 */
- (NSArray *)geometrySourcesForSemantic:(NSString *)semantic;

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
 @discussion levelsOfDetail is an array of SCNLevelOfDetail instance.
 */
@property(nonatomic, copy) NSArray *levelsOfDetail SCENEKIT_AVAILABLE(10_9, 8_0);

/*!
 @property subdivisionLevel
 @abstract Specifies the subdivision level of the receiver. Defaults to 0.
 @discussion A subdivision level of 0 means no subdivision.
 */
@property(nonatomic) NSUInteger subdivisionLevel SCENEKIT_AVAILABLE(10_10, 8_0);

/*!
 @property edgeCreasesElement
 @abstract Specifies the edges creases that control the subdivision. Defaults to nil.
 @discussion The primitive type of this geometry element must be SCNGeometryPrimitiveTypeLine. See subdivisionLevel above to control the level of subdivision. See edgeCreasesElement above to specify edges for edge creases.
 */
@property(nonatomic, retain) SCNGeometryElement *edgeCreasesElement SCENEKIT_AVAILABLE(10_10, 8_0);

/*!
 @property edgeCreasesSource
 @abstract Specifies the crease value of the edges specified by edgeCreasesElement. Defaults to nil.
 @discussion The semantic of this geometry source must be "SCNGeometrySourceSemanticEdgeCrease". The creases values are floating values between 0 and 10, where 0 means smooth and 10 means infinitely sharp. See subdivisionLevel above to control the level of subdivision. See edgeCreasesElement above to specify edges for edge creases.
 */
@property(nonatomic, retain) SCNGeometrySource *edgeCreasesSource SCENEKIT_AVAILABLE(10_10, 8_0);

@end


/*!
 @class SCNGeometrySource
 @abstract A geometry source contains geometry data for a specific semantic. The data format is described by properties.
 */

SCENEKIT_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNGeometrySource : NSObject <NSSecureCoding>
{
@private
	id _reserved;
}

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
+ (instancetype)geometrySourceWithData:(NSData *)data semantic:(NSString *)semantic vectorCount:(NSInteger)vectorCount floatComponents:(BOOL)floatComponents componentsPerVector:(NSInteger)componentsPerVector bytesPerComponent:(NSInteger)bytesPerComponent dataOffset:(NSInteger)offset dataStride:(NSInteger)stride;

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

/*! 
 @property data
 @abstract The data for the geometry source
 */
@property(nonatomic, readonly) NSData *data;

/*! 
 @property semantic
 @abstract The semantic of the geometry source
 */
@property(nonatomic, readonly) NSString *semantic;

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


/*!
 @class SCNGeometryElement
 @abstract A geometry element describes how vertices from a geometry source are connected together.
 */

SCENEKIT_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNGeometryElement : NSObject <NSSecureCoding>
{
@private
	id _reserved;
}

/*!
 @method geometryElementWithData:primitiveType:primitiveCount:bytesPerIndex:
 @abstract Creates and returns a geometry element from the given data and data format info.
 @param data The data that contains element indexes.
 @param primitiveType The primitive type, as listed in the SCNGeometryPrimitiveType enumeration.
 @param primitiveCount The number of primitives in the data.
 @param bytesPerIndex The number of bytes that represent a single index value in the data.
 */
+ (instancetype)geometryElementWithData:(NSData *)data primitiveType:(SCNGeometryPrimitiveType)primitiveType primitiveCount:(NSInteger)primitiveCount bytesPerIndex:(NSInteger)bytesPerIndex;

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
 @property bytesPerIndex
 @abstract The number of bytes that represent an index value
 */
@property(nonatomic, readonly) NSInteger bytesPerIndex;

@end


