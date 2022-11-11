//
//  ARMeshGeometry.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/Metal.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A container for vector data of a geometry.
 */
API_AVAILABLE(ios(13.4))
@interface ARGeometrySource : NSObject<NSSecureCoding>

/**
 A Metal buffer containing per-vector data for the source.
 */
@property (nonatomic, strong, readonly) id<MTLBuffer> buffer;

/**
 The number of vectors in the source.
 */
@property (nonatomic, assign, readonly) NSInteger count;

/**
 The type of per-vector data in the buffer.
 */
@property (nonatomic, assign, readonly) MTLVertexFormat format;

/**
 The number of scalar components in each vector.
 */
@property (nonatomic, assign, readonly) NSInteger componentsPerVector;

/**
 The offset (in bytes) from the beginning of the buffer.
 */
@property (nonatomic, assign, readonly) NSInteger offset;

/**
 The number of bytes from a vector to the next one in the buffer.
 */
@property (nonatomic, assign, readonly) NSInteger stride;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
The primitive that defines how vertices are connected.
*/
API_AVAILABLE(ios(13.4))
typedef NS_ENUM(NSInteger, ARGeometryPrimitiveType) {
    /// The geometry element is a sequence of line segments, where each line segment is described by two new vertices.
    ARGeometryPrimitiveTypeLine,
    /// The geometry element is a sequence of triangles, where each triangle is described by three new vertices.
    ARGeometryPrimitiveTypeTriangle
};

/**
 A container for index data describing how vertices connect to define a geometry.
 */
API_AVAILABLE(ios(13.4))
@interface ARGeometryElement : NSObject<NSSecureCoding>

/**
 A Metal buffer containing index data that defines the geometry.
 */
@property (nonatomic, strong, readonly) id<MTLBuffer> buffer;

/**
 The number of primitives in the buffer.
 */
@property (nonatomic, assign, readonly) NSInteger count;

/**
 The number of bytes that represent an index value.
 */
@property (nonatomic, assign, readonly) NSInteger bytesPerIndex;

/**
 The number of indices for each primitive.
 @see ARGeometryPrimitiveType
 @discussion This is based on the primitiveType. For ARGeometryPrimitiveTypeTriangle the value is 3.
 */
@property (nonatomic, assign, readonly) NSInteger indexCountPerPrimitive;

/**
 The type of the geometry element.
 */
@property(nonatomic, assign, readonly) ARGeometryPrimitiveType primitiveType;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 A value describing the classification of a mesh face.
 */
API_AVAILABLE(ios(13.4))
typedef NS_ENUM(NSInteger, ARMeshClassification) {
    ARMeshClassificationNone = 0,
    ARMeshClassificationWall,
    ARMeshClassificationFloor,
    ARMeshClassificationCeiling,
    ARMeshClassificationTable,
    ARMeshClassificationSeat,
    ARMeshClassificationWindow,
    ARMeshClassificationDoor,
};


/**
A three-dimensional shape that represents the geometry of a mesh.
*/
API_AVAILABLE(ios(13.4))
@interface ARMeshGeometry : NSObject<NSSecureCoding>

/*
 The vertices of the mesh.
 */
@property (nonatomic, strong, readonly) ARGeometrySource *vertices;

/*
 Normal of each vertex in the mesh.
 */
@property (nonatomic, strong, readonly) ARGeometrySource *normals;

/*
 A list of all faces in the mesh.
 */
@property (nonatomic, strong, readonly) ARGeometryElement *faces;

/*
 Classification for each face in the mesh.
 */
@property (nonatomic, strong, readonly, nullable) ARGeometrySource *classification;


/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
