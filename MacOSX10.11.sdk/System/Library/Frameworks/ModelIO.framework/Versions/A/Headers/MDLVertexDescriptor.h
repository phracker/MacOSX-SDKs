/*!
 @header MDLVertexDescriptor.h
 @framework ModelIO
 @abstract Structures for describing layout of vertex data in buffers
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */
#import <Foundation/Foundation.h>
#import "ModelIOExports.h"
#import "MDLMeshBuffer.h"
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @group Default MDLVertexAttribute Names
 @abstract Default names for common vertex attribute types
 @discussion 

 These are names that are created during 3d asset file loading to correspond
 to data found in those files.
 */

/*! The degree of shading anisotropy encoded at a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeAnisotropy;

/*! The normal to a curve at a vertex position */
MDL_EXPORT NSString * const MDLVertexAttributeBinormal;

/*! The vector completing a tangent basis at a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeBitangent;

/*! Color of a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeColor;

/*! A crease value along an edge to be applied during subdivision */
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

/*! A create value at a vertex to be applied during subdivision */
MDL_EXPORT NSString * const MDLVertexAttributeVertexCrease;

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
    
    MDLVertexFormatUChar  = 0x10001,
    MDLVertexFormatUChar2 = 0x10002,
    MDLVertexFormatUChar3 = 0x10003,
    MDLVertexFormatUChar4 = 0x10004,

    MDLVertexFormatChar =  0x20001,
    MDLVertexFormatChar2 = 0x20002,
    MDLVertexFormatChar3 = 0x20003,
    MDLVertexFormatChar4 = 0x20004,

    MDLVertexFormatUCharNormalized  = 0x30001,
    MDLVertexFormatUChar2Normalized = 0x30002,
    MDLVertexFormatUChar3Normalized = 0x30003,
    MDLVertexFormatUChar4Normalized = 0x30004,

    MDLVertexFormatCharNormalized = 0x40001,
    MDLVertexFormatChar2Normalized = 0x40002,
    MDLVertexFormatChar3Normalized = 0x40003,
    MDLVertexFormatChar4Normalized = 0x40004,

    MDLVertexFormatUShort = 0x50001,
    MDLVertexFormatUShort2 = 0x50002,
    MDLVertexFormatUShort3 = 0x50003,
    MDLVertexFormatUShort4 = 0x50004,

    MDLVertexFormatShort = 0x60001,
    MDLVertexFormatShort2 = 0x60002,
    MDLVertexFormatShort3 = 0x60003,
    MDLVertexFormatShort4 = 0x60004,

    MDLVertexFormatUShortNormalized = 0x70001,
    MDLVertexFormatUShort2Normalized = 0x70002,
    MDLVertexFormatUShort3Normalized = 0x70003,
    MDLVertexFormatUShort4Normalized = 0x70004,

    MDLVertexFormatShortNormalized = 0x80001,
    MDLVertexFormatShort2Normalized = 0x80002,
    MDLVertexFormatShort3Normalized = 0x80003,
    MDLVertexFormatShort4Normalized = 0x80004,

    MDLVertexFormatUInt = 0x90001,
    MDLVertexFormatUInt2 = 0x90002,
    MDLVertexFormatUInt3 = 0x90003,
    MDLVertexFormatUInt4 = 0x90004,

    MDLVertexFormatInt = 0xA0001,
    MDLVertexFormatInt2 = 0xA0002,
    MDLVertexFormatInt3 = 0xA0003,
    MDLVertexFormatInt4 = 0xA0004,

    MDLVertexFormatHalf = 0xB0001,
    MDLVertexFormatHalf2 = 0xB0002,
    MDLVertexFormatHalf3 = 0xB0003,
    MDLVertexFormatHalf4 = 0xB0004,

    MDLVertexFormatFloat = 0xC0001,
    MDLVertexFormatFloat2 = 0xC0002,
    MDLVertexFormatFloat3 = 0xC0003,
    MDLVertexFormatFloat4 = 0xC0004,

    // Packed type should all have values < 0x10000
    MDLVertexFormatInt1010102Normalized = 0x1004,
    MDLVertexFormatUInt1010102Normalized = 0x2004,
};




/*!
 @class MDLVertexBufferLayout
 @abstract Describes a vertex buffer's layout
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLVertexBufferLayout : NSObject <NSCopying>

/*!
 @property stride
 @abstract stride in bytes of each vertex element of in the buffer
 */
@property (nonatomic, readwrite) NSUInteger stride;
@end





/*!
 @class MDLVertexAttribute
 @abstract Structure with properties of a vertex attribute
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
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
 @discussion 
 
 This object is a property of MDLMesh describing the current state of
 attributes and buffer layouts of the vertex buffers in the mesh. This must be 
 immutable otherwise even small changes could cause the buffers to be out of sync 
 with the layout described here.
 
 Designed to be very similar to MTLVertexDescriptor to ease creation of one from 
 the other
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
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
 @abstract Replace any attribute with the same name, or add it if it does not
           already exist.
 */
- (void)addOrReplaceAttribute:(nonnull MDLVertexAttribute*)attribute;

/*! 
 @property attributes
 @abstract An array of MDLVertexAttribute objects
 @discussion An array describing the current attribute state of vertex buffers in an
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
