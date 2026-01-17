//
//  MPSNDArrayQuantizedMatrixMultiplication.h
//  MPSNDArray
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef MPSNDArrayQuantizedMatrixMultiplication_h
#define MPSNDArrayQuantizedMatrixMultiplication_h

#import <MPSNDArray/MPSNDArrayMatrixMultiplication.h>
#import <MPSNDArray/MPSNDArrayQuantization.h>

/*!
 *  @class      MPSNDArrayQuantizedMatrixMultiplication
 *
 *  @dependency This depends on Metal.framework.
 *  @abstract   A quantized matrix multiplication kernel: C = AB, where each input A and B can be quantized.
 *  @discussion The kernel works with 2-8 inputs, order of inputs: First all LHS inputs, then all RHS inputs.
 *              The order of inputs for LUT based LHS or RHS: 1) quantized input 2) Lookup Table.
 *              The order of inputs for affine LHS or RHS: 1) quantized input 2) scale 3) zeropoint 4) minValue.
 *              The full order of inputs for the encode methods is:
 *                   `[LHS, RHS, <LHS quantization inputs>, <RHS quantization inputs>]`,
 *              where `LHS` is the left input (quantized or float) `RHS` is the right input (quantized or float) and
 *              `<LHS quantization inputs>` are the auxiliary quantization inputs for the LHS array (scales, zeropoints etc).
 *              and `<RHS quantization inputs>` are the auxiliary quantization input for the RHS array.
 *              The inputs are provided as a compacted `NSArray<MPSNDArray *>`, for example for computing
 *              `C = A * B^T` where `A` is quantized with a LUT and `B` is quantized with affine quantization that
 *              uses scale and minValue the array of inputs is:
 *              ` [ Aq, Bq^T, ALUT, BScale^T, BMin^T ] `.
 *              NOTE: For affine scale, zeropoint and minValue must have same transposes as quantized input.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0), visionos(2.0) )
@interface MPSNDArrayQuantizedMatrixMultiplication : MPSNDArrayMatrixMultiplication

-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device
                           sourceCount:(NSUInteger) sourceCount NS_UNAVAILABLE;

/*! @abstract   Initializes a quantized matrix multiplication kernel.
 *  @param      leftQuantizationDescriptor    The quantization definition for the LHS input.
 *  @param      rightQuantizationDescriptor    The quantization definition for the RHS input.
 *  @result     A new valid quantized matrix multiplication kernel.
 *   */
- (nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>) device
             leftQuantizationDescriptor: (MPSNDArrayQuantizationDescriptor* _Nullable) leftQuantizationDescriptor
            rightQuantizationDescriptor: (MPSNDArrayQuantizationDescriptor* _Nullable) rightQuantizationDescriptor;

@end

/*!
 *  @class      MPSNDArrayLUTDequantize
 *
 *  @dependency This depends on Metal.framework.
 *  @abstract   A kernel which dequantizes a lookup-table based NDArray.
 *  @discussion The kernel works with 2 inputs: 1) The quantized input, 2) The LookUp table array.
 *
 */

MPS_CLASS_AVAILABLE_STARTING( macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0), visionos(2.0) )
@interface MPSNDArrayLUTDequantize : MPSNDArrayMultiaryKernel

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
NS_DESIGNATED_INITIALIZER;

-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device
                           sourceCount:(NSUInteger) sourceCount NS_UNAVAILABLE;

@end

/*!
 *  @class      MPSNDArrayVectorLUTDequantize
 *
 *  @dependency This depends on Metal.framework.
 *  @abstract   A kernel which dequantizes a lookup-table based NDArray with vector LUT support.
 *  @discussion The kernel works with 2 inputs: 1) The quantized input, 2) The LookUp table array.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0), visionos(2.0) )
@interface MPSNDArrayVectorLUTDequantize : MPSNDArrayMultiaryKernel

/*! @property  vectorAxis
 *  @abstract  Which axis in the destination will receive the vector component, must be less than 4.
 */
@property(readwrite, nonatomic) NSUInteger vectorAxis;

/*! @abstract   Initializes a kernel for vector-based LUT dequantization.
 *  @param      device    The Metal device to be used with this kernel.
 *  @param      axis        The vector axis in the output.
 *  @result     A new vector LUT dequantization kernel.
 *   */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                  axis: (NSUInteger) axis
NS_DESIGNATED_INITIALIZER;

-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device
                           sourceCount:(NSUInteger) sourceCount NS_UNAVAILABLE;

@end

/*!
 *  @class      MPSNDArrayAffineInt4Dequantize
 *
 *  @dependency This depends on Metal.framework.
 *  @abstract   A kernel which dequantizes an input with affine quantization scheme.
 *  @discussion The kernel works with 2-4 inputs, order of inputs: 1) quantized input, 2) scale, 3) zeropoint, 4) minValue
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0), visionos(2.0) )
@interface MPSNDArrayAffineInt4Dequantize : MPSNDArrayMultiaryKernel

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*! @abstract   Initializes a kernel for 4-bit affine dequantization.
 *  @param      device    The Metal device to be used with this kernel.
 *  @param      quantizationDescriptor        Describes the quantization scheme.
 *  @result     A new vector LUT dequantization kernel.
 *   */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device
                quantizationDescriptor:(MPSNDArrayAffineQuantizationDescriptor* __nonnull) quantizationDescriptor;

-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device
                           sourceCount:(NSUInteger) sourceCount NS_UNAVAILABLE;

@end

#endif /* MPSNDArrayQuantizedMatrixMultiplication_h */
