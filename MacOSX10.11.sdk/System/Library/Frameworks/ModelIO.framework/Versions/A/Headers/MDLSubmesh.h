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
                geometryType:(MDLGeometryKind)geometryType
                    material:(nullable MDLMaterial *)material;
/*!
 @method initWithIndexBuffer:indexCount:indexType:geometryType:material:
 @abstract Initialize submesh with all data necessary to make properties valid
 */
- (instancetype)initWithIndexBuffer:(id<MDLMeshBuffer>)indexBuffer
                         indexCount:(NSUInteger)indexCount
                          indexType:(MDLIndexBitDepth)indexType
                       geometryType:(MDLGeometryKind)geometryType
                           material:(nullable MDLMaterial *)material;
/*!
 @property indexBuffer
 @abstract Index data referencing vertex data in parent mesh
 */
@property (nonatomic, readonly, retain) id<MDLMeshBuffer> indexBuffer;

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
@property (nonatomic, readonly) MDLGeometryKind geometryType;

/*!
 @property material
 @abstract Material to apply when rendering this object
 */
@property (nonatomic, retain, nullable) MDLMaterial *material;

/*!
 @property name
 @abstract Identifying name for this object
 */
@property (nonatomic, copy) NSString *name;

@end

NS_ASSUME_NONNULL_END
