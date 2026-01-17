//
//  MPSNDArrayQuantization.h
//  MPSNDArray
//
//  Created by Saharsh Oza on 4/24/23.
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef MPSNDArrayQuantization_h
#define MPSNDArrayQuantization_h

#import <MPSCore/MPSCoreTypes.h>
#import <MPSCore/MPSKernel.h>
#import <MPSCore/MPSNDArray.h>

/*! @enum       MPSNDArrayQuantizationScheme
 *  @discussion  Which quantization mode is applied to an MPSNDArray
 *
 *  @constant   MPSNDArrayQuantizationTypeNone              No quantization - inputs are read and outputs are produced in the original datatype.
 *  @constant   MPSNDArrayQuantizationTypeAffine           Dequantization with: y = scale( input - zeroPoint) + minValue
 *  @constant   MPSNDArrayQuantizationTypeLUT           Dequantization with y = lookuptable[ input ]
 */

#if defined(DOXYGEN)
    typedef enum MPSNDArrayQuantizationScheme
#else
    typedef NS_OPTIONS(NSUInteger, MPSNDArrayQuantizationScheme)
#endif
{
    MPSNDArrayQuantizationTypeNone MPS_ENUM_AVAILABLE_STARTING( macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0), visionos(2.0) ) MPS_SWIFT_NAME( none ) = 0,
    MPSNDArrayQuantizationTypeAffine MPS_ENUM_AVAILABLE_STARTING( macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0), visionos(2.0) ),
    MPSNDArrayQuantizationTypeLUT MPS_ENUM_AVAILABLE_STARTING( macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0), visionos(2.0) ),
}
#if defined(DOXYGEN)
    MPSNDArrayQuantizationScheme
#endif
;


/*!
 *  @class      MPSNDArrayQuantizationDescriptor
 *
 *  @dependency This depends on Metal.framework.
 *  @abstract   Common methods for quantization descriptors
 *
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0), visionos(2.0) )
@interface MPSNDArrayQuantizationDescriptor : NSObject <NSCopying>

/*! @property  quantizationDataType
 *  @abstract  The datatype to use with quantization - the default is MPSDataTypeUint8
 */
@property (readonly, nonatomic) MPSDataType quantizationDataType;

/*! @property  quantizationScheme
 *  @abstract  The quantization scheme for this descriptor. The default is MPSNDArrayQuantizationTypeNone.
 */
@property (readonly, nonatomic) MPSNDArrayQuantizationScheme quantizationScheme;

@end

/*!
 *  @class      MPSNDArrayAffineQuantizationDescriptor
 *
 *  @dependency This depends on Metal.framework.
 *  @abstract   Describes an affine quantization scheme
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0), visionos(2.0) )
@interface MPSNDArrayAffineQuantizationDescriptor : MPSNDArrayQuantizationDescriptor

/*! @property  hasZeroPoint
 *  @abstract  If yes then asymmetric quantization is used. See MPSNDArrayQuantizationScheme.
 */
@property (readwrite, nonatomic) BOOL hasZeroPoint;

/*! @property  hasMinValue
 *  @abstract  If yes then offset is used. See MPSNDArrayQuantizationScheme.
 */
@property (readwrite, nonatomic) BOOL hasMinValue;

/*! @property implicitZeroPoint
 *  @abstract If true and quantized values are signed, these are assumed to be stored with an
 *            implicit offset or zero-point of 2^(quantizationBitWidth-1) added to bring signed values into unsigned range.
 *            e.g. Int4 values are in range [-8,7]. If we add 8 to it values are in range
 *            [0,15] and can be encoded/stored as UInt4.
 *            Default is false. Its only currently applicable to Int4.
 *            Implementation will generate error for any other data type;
 */
@property (readwrite, nonatomic) bool implicitZeroPoint;



- (nonnull instancetype) init;

/*! @abstract   Initializes an affine quantization descriptor.
 *  @param      quantizationDataType    Which quantized datatype is used.
 *  @param      hasZeroPoint        A flag indicating that a zero-point input is expected.
 *  @param      hasMinValue        A flag indicating that a minimum value input is expected.
 *  @result     A new quantization descriptor.
 *   */
- (nonnull instancetype) initWithDataType: (MPSDataType) quantizationDataType
                             hasZeroPoint: (BOOL) hasZeroPoint
                              hasMinValue: (BOOL) hasMinValue;

@end


/*!
 *  @class      MPSNDArrayLUTQuantizationDescriptor
 *
 *  @dependency This depends on Metal.framework.
 *  @abstract   Describes a lookup-table based quantization scheme
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0), visionos(2.0) )
@interface MPSNDArrayLUTQuantizationDescriptor : MPSNDArrayQuantizationDescriptor

/*! @abstract   Initializes a scalar lookup-table quantization descriptor.
 *  @param      quantizationDataType    Which quantized datatype is used.
 *  @result     A new quantization descriptor.
 *   */
- (nonnull instancetype) initWithDataType: (MPSDataType) quantizationDataType;

/*! @abstract   Initializes a vector lookup-table quantization descriptor.
 *  @param      quantizationDataType    Which quantized datatype is used.
 *  @param      vectorAxis        The quantization vector axis - this axis will receive the vector component in the destination.
 *  @result     A new quantization descriptor.
 *   */
- (nonnull instancetype) initWithDataType: (MPSDataType) quantizationDataType
                               vectorAxis: (NSUInteger) vectorAxis;

@end

#endif /* MPSNDArrayQuantization_h */
