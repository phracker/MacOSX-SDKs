/*!
 @header MDLVertexDescriptor.h
 @framework ModelIO
 @abstract Structures for describing layout of vertex data in buffers
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */
#import <Foundation/Foundation.h>
#import <ModelIO/ModelIOExports.h>
#import <ModelIO/MDLMeshBuffer.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @group Default MDLVertexAttribute Names
 @abstract Default names for common vertex attribute types
 @discussion 

 These are names that are created during 3d asset file loading to correspond
 to data found in those files.
 */

/*! The attribute data describes the degree to which a surface’s appearance 
    changes in appearance when rotated about its normal vector. */
MDL_EXPORT NSString * const MDLVertexAttributeAnisotropy;

/*! The normal to a curve at a vertex position */
MDL_EXPORT NSString * const MDLVertexAttributeBinormal;

/*! The vector completing a tangent basis at a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeBitangent;

/*! Color of a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeColor;

/*! A crease value along an edge to be applied during subdivision.
    A zero value indicates an edge is smooth, one is sharply creased. */
MDL_EXPORT NSString * const MDLVertexAttributeEdgeCrease;

/*! Indices of joints in an animation rig corresponding to weighting information */
MDL_EXPORT NSString * const MDLVertexAttributeJointIndices;

/*! Weights corresponding to joints for the purpose of blending animation */
MDL_EXPORT NSString * const MDLVertexAttributeJointWeights;

/*! The direction of a normal at a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeNormal;

/*! A value indicating the degree to which a vertex is occluded by surrounding geometry */
MDL_EXPORT NSString * const MDLVertexAttributeOcclusionValue;

/*! The position of a vertex */
MDL_EXPORT NSString * const MDLVertexAttributePosition;

/*! The u direction of a shading basis at a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeShadingBasisU;

/*! The v direction of a shading basis at a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeShadingBasisV;

/*! Stencil values for subdivision at a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeSubdivisionStencil;

/*! A vector tangent to a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeTangent;

/*! Texture coordinate mapping at a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeTextureCoordinate;


/*!
 @enum MDLVertexFormat
 @abstract Describes the format of a an attribute in a vertex buffer
 @discussion Designed to be very similar to MTLVertexDescriptor to ease the 
             translation from one to the other. Values are chosen such that 
             packed types would all be less than 0x1000 and the bottom 5 bits 
             can be used to determine the number of channels/components in the 
             format.
 */
typedef NS_ENUM(NSUInteger, MDLVertexFormat)
{
    MDLVertexFormatInvalid = 0,
    
    MDLVertexFormatPackedBit = 0x1000,

    MDLVertexFormatUCharBits = 0x10000,
    MDLVertexFormatCharBits = 0x20000,
    MDLVertexFormatUCharNormalizedBits = 0x30000,
    MDLVertexFormatCharNormalizedBits = 0x40000,
    MDLVertexFormatUShortBits = 0x50000,
    MDLVertexFormatShortBits = 0x60000,
    MDLVertexFormatUShortNormalizedBits = 0x70000,
    MDLVertexFormatShortNormalizedBits = 0x80000,
    MDLVertexFormatUIntBits = 0x90000,
    MDLVertexFormatIntBits = 0xA0000,
    MDLVertexFormatHalfBits = 0xB0000,
    MDLVertexFormatFloatBits = 0xC0000,
    
    MDLVertexFormatUChar =  MDLVertexFormatUCharBits | 1,
    MDLVertexFormatUChar2 = MDLVertexFormatUCharBits | 2,
    MDLVertexFormatUChar3 = MDLVertexFormatUCharBits | 3,
    MDLVertexFormatUChar4 = MDLVertexFormatUCharBits | 4,

    MDLVertexFormatChar =  MDLVertexFormatCharBits | 1,
    MDLVertexFormatChar2 = MDLVertexFormatCharBits | 2,
    MDLVertexFormatChar3 = MDLVertexFormatCharBits | 3,
    MDLVertexFormatChar4 = MDLVertexFormatCharBits | 4,

    MDLVertexFormatUCharNormalized =  MDLVertexFormatUCharNormalizedBits | 1,
    MDLVertexFormatUChar2Normalized = MDLVertexFormatUCharNormalizedBits | 2,
    MDLVertexFormatUChar3Normalized = MDLVertexFormatUCharNormalizedBits | 3,
    MDLVertexFormatUChar4Normalized = MDLVertexFormatUCharNormalizedBits | 4,

    MDLVertexFormatCharNormalized =  MDLVertexFormatCharNormalizedBits | 1,
    MDLVertexFormatChar2Normalized = MDLVertexFormatCharNormalizedBits | 2,
    MDLVertexFormatChar3Normalized = MDLVertexFormatCharNormalizedBits | 3,
    MDLVertexFormatChar4Normalized = MDLVertexFormatCharNormalizedBits | 4,

    MDLVertexFormatUShort =  MDLVertexFormatUShortBits | 1,
    MDLVertexFormatUShort2 = MDLVertexFormatUShortBits | 2,
    MDLVertexFormatUShort3 = MDLVertexFormatUShortBits | 3,
    MDLVertexFormatUShort4 = MDLVertexFormatUShortBits | 4,

    MDLVertexFormatShort =  MDLVertexFormatShortBits | 1,
    MDLVertexFormatShort2 = MDLVertexFormatShortBits | 2,
    MDLVertexFormatShort3 = MDLVertexFormatShortBits | 3,
    MDLVertexFormatShort4 = MDLVertexFormatShortBits | 4,

    MDLVertexFormatUShortNormalized =  MDLVertexFormatUShortNormalizedBits | 1,
    MDLVertexFormatUShort2Normalized = MDLVertexFormatUShortNormalizedBits | 2,
    MDLVertexFormatUShort3Normalized = MDLVertexFormatUShortNormalizedBits | 3,
    MDLVertexFormatUShort4Normalized = MDLVertexFormatUShortNormalizedBits | 4,

    MDLVertexFormatShortNormalized =  MDLVertexFormatShortNormalizedBits | 1,
    MDLVertexFormatShort2Normalized = MDLVertexFormatShortNormalizedBits | 2,
    MDLVertexFormatShort3Normalized = MDLVertexFormatShortNormalizedBits | 3,
    MDLVertexFormatShort4Normalized = MDLVertexFormatShortNormalizedBits | 4,

    MDLVertexFormatUInt =  MDLVertexFormatUIntBits | 1,
    MDLVertexFormatUInt2 = MDLVertexFormatUIntBits | 2,
    MDLVertexFormatUInt3 = MDLVertexFormatUIntBits | 3,
    MDLVertexFormatUInt4 = MDLVertexFormatUIntBits | 4,

    MDLVertexFormatInt =  MDLVertexFormatIntBits | 1,
    MDLVertexFormatInt2 = MDLVertexFormatIntBits | 2,
    MDLVertexFormatInt3 = MDLVertexFormatIntBits | 3,
    MDLVertexFormatInt4 = MDLVertexFormatIntBits | 4,

    MDLVertexFormatHalf =  MDLVertexFormatHalfBits | 1,
    MDLVertexFormatHalf2 = MDLVertexFormatHalfBits | 2,
    MDLVertexFormatHalf3 = MDLVertexFormatHalfBits | 3,
    MDLVertexFormatHalf4 = MDLVertexFormatHalfBits | 4,

    MDLVertexFormatFloat =  MDLVertexFormatFloatBits | 1,
    MDLVertexFormatFloat2 = MDLVertexFormatFloatBits | 2,
    MDLVertexFormatFloat3 = MDLVertexFormatFloatBits | 3,
    MDLVertexFormatFloat4 = MDLVertexFormatFloatBits | 4,

    MDLVertexFormatInt1010102Normalized =  MDLVertexFormatIntBits  | MDLVertexFormatPackedBit | 4,
    MDLVertexFormatUInt1010102Normalized = MDLVertexFormatUIntBits | MDLVertexFormatPackedBit | 4
};




/*!
 @class MDLVertexBufferLayout
 @abstract Describes a vertex buffer's layout
 */
API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLVertexBufferLayout : NSObject <NSCopying>

- (instancetype) initWithStride:(NSUInteger) stride;

/*!
 @property stride
 @abstract stride in bytes of each vertex element in the buffer. 
 @discussion - If you store multiple attributes interleaved in the vertex
               buffer, the stride will be the sum of sizes of each attribute (and any padding).
             - If you store multiple attributes non-interleaved (back to back),
               the stride will be the size of an attribute (and all attributes are
               required to have the same size).
 */
@property (nonatomic, readwrite) NSUInteger stride;
@end





/*!
 @class MDLVertexAttribute
 @abstract Structure with properties of a vertex attribute
 */
API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLVertexAttribute : NSObject <NSCopying>

/*!
 @method initWithName:format:offset:bufferIndex
 @abstract Initialize attribute object with all properties
 */
- (instancetype) initWithName:(NSString *)name
                       format:(MDLVertexFormat)format
                       offset:(NSUInteger)offset
                  bufferIndex:(NSUInteger)bufferIndex;
/*!
 @property name
 @abstract Identifying name of the attribute derived from model file, or one of 
           the predefined MDLVertexAttribute strings
 */
@property (nonatomic, copy) NSString *name;

/*!
 @property format
 @abstract Format (including number of components) of the attribute
 @discussion If the value is MDLVertexFormatInvalid.   Other values of this 
             object will be ignored when setting the MDLVertexDescriptor object 
             in a Mesh. The initial value is MDLVertexFormatInvalid.
 */
@property (nonatomic, readwrite) MDLVertexFormat format;

/*!
 @property offset
 @abstract offset in bytes of the attrbute in each element of the vertex buffer
 */
@property (nonatomic, readwrite)  NSUInteger offset;

/*!
 @property bufferIndex
 @abstract index of the buffer in mesh's vertexBuffer array in which this 
           attribute resides
 */
@property (nonatomic, readwrite) NSUInteger bufferIndex;

/*!
 @property time
 @abstract the time the attribute is intended for.
 @discussion morph targets would store their times here
 */
@property (nonatomic, readwrite) NSTimeInterval time;

/*!
 @property initializationValue
 @abstract Value to initialize the attribute to in the vertex buffer if no values
 @discussion This values of this vector will be set in attribute in the vertex
 attribute if the attribute did not previously exist in the mesh when
 setting the MDLVertexDescriptor in the mesh.  Components of this
 vector will also be set in The initial value of initializationValue
 is (0, 0, 0, 1).
 */
@property (nonatomic, readwrite) vector_float4 initializationValue;

@end




/*!
 @class MDLVertexDescriptor
 @abstract Describes the layout of vertex buffers in MDLMesh objects
 @discussion This object is a property of MDLMesh describing the current state of
 attributes and buffer layouts of the vertex buffers in the mesh. This must be 
 immutable otherwise even small changes could cause the buffers to be out of sync 
 with the layout described here.
 
 Designed to be very similar to MTLVertexDescriptor to ease creation of one from 
 the other
 */
API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLVertexDescriptor : NSObject <NSCopying>

/*!
 @method initVertexDescriptor:
 @abstract Initializes the object with values from supplied vertexDescriptor
 @discussion This performs a deep copy of all data in the supplied descriptor.
 */
-(instancetype) initWithVertexDescriptor:(MDLVertexDescriptor *)vertexDescriptor;

/*!
 @method attributeNamed:
 @abstract Retrieves the attribute with the given name
 @return The attribute with the supplied name or nil if attribute with the given 
         name does not exist in the descriptor object
 */
-(nullable MDLVertexAttribute *)attributeNamed:(NSString*)name;

/*!
 @method addOrReplaceAttribute:
 @abstract Replace any attribute with the same name and time, or add it if it does not
           already exist.
 */
- (void)addOrReplaceAttribute:(nonnull MDLVertexAttribute*)attribute;

/*!
 @method removeAttributeNamed:
 @abstract Remove the named attribute if it exists
 */
- (void)removeAttributeNamed:(NSString*)name;

/*! 
 @property attributes
 @abstract An array of MDLVertexAttribute objects
 @discussion ay describing the current attribute state of vertex buffers in an
             MDLMesh mesh
 */
@property (nonatomic, retain) NSMutableArray<MDLVertexAttribute*> *attributes;

/*!
 @property layouts
 @abstract An array of MDLVertexBufferLayout
 @discussion An array describing the current layout state of vertex buffers in an 
             MDLMesh mesh
 */
@property (nonatomic, retain) NSMutableArray<MDLVertexBufferLayout*> *layouts;

/*!
 @method reset
 @abstract Tesets the descriptor to initial values
 */
- (void)reset;

/*!
 @method setPackedStrides
 @abstract Sets the stride in each VertexBufferLout in the layouts array to the 
           minimum value encompassing all attributes in the vertex buffer
 */
- (void)setPackedStrides;

/*!
  @method setPackedOffsets
  @abstract Sets the stride in each VertexAttribute in the attributes array to 
            the minimum value to pack each attribute next to each other in its 
            vertexbuffer
  */
- (void)setPackedOffsets;

@end

NS_ASSUME_NONNULL_END
