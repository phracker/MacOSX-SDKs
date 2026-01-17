//
//  MPSGraphQuantizationOps.h
//  MPSGraphQuantizationOps
//
//  Created on 9/30/21.
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef MPSGraphQuantizationOps_h
#define MPSGraphQuantizationOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

@interface MPSGraph(MPSGraphQuantizationOps)

/// Creates a Quantize operation and returns the result tensor.
///
/// Convert the float `tensor` to an i8 or u8 tensor by applying a scale + bias transform: 
/// result = (tensor / scale) + zeroPoint
///
/// - Parameters:
///   - tensor: Input tensor to be quantized
///   - scale: Scale scalar parameter
///   - zeroPoint: Bias scalar parameter (converted to dataType of resultTensor)
///   - dataType: Integer data type of the result tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of datatype dataType
-(MPSGraphTensor*) quantizeTensor:(MPSGraphTensor*)tensor
                            scale:(double)scale
                        zeroPoint:(double)zeroPoint
                         dataType:(MPSDataType)dataType
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( quantize(_:scale:zeroPoint:dataType:name:) );

/// Creates Dequantize operation and returns the result tensor.
///
/// Convert the i8 or u8 `tensor` to a float tensor by applying a scale + bias transform: 
/// result = scale(tensor - zeroPoint)
///
/// - Parameters:
///   - tensor: Input tensor to be dequantized
///   - scale: Scale scalar parameter
///   - zeroPoint: Bias scalar parameter (converted to dataType of tensor)
///   - dataType: Float data type of the result tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of datatype dataType
-(MPSGraphTensor*) dequantizeTensor:(MPSGraphTensor*)tensor
                              scale:(double)scale
                          zeroPoint:(double)zeroPoint
                           dataType:(MPSDataType)dataType
                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( dequantize(_:scale:zeroPoint:dataType:name:) );

/// Creates a Quantize operation and returns the result tensor.
///
/// Convert the float `tensor` to an i8 or u8 tensor by applying a scale + bias transform: 
/// result = (tensor / scaleTensor) + zeroPoint
///
/// - Parameters:
///   - tensor: Input tensor to be quantized
///   - scaleTensor: Scale 1D Tensor parameter with size == tensor.shape[axis]
///   - zeroPoint: Bias scalar parameter (converted to dataType of resultTensor)
///   - dataType: Integer data type of the result tensor.
///   - axis: Axis on which the scale 1D value is being broadcasted
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of datatype dataType
-(MPSGraphTensor*) quantizeTensor:(MPSGraphTensor*)tensor
                      scaleTensor:(MPSGraphTensor*)scaleTensor
                        zeroPoint:(double)zeroPoint
                         dataType:(MPSDataType)dataType
                             axis:(NSInteger)axis
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( quantize(_:scaleTensor:zeroPoint:dataType:axis:name:) );

/// Creates Dequantize operation and returns the result tensor.
///
/// Convert the i8 or u8 `tensor` to a float tensor by applying a scale + bias transform: 
/// result = scaleTensor(tensor - zeroPoint)
///
/// - Parameters:
///   - tensor: Input tensor to be dequantized
///   - scaleTensor: Scale scalar or 1D Tensor parameter with size == tensor.shape[axis]
///   - zeroPoint: Bias scalar parameter (converted to dataType of tensor)
///   - dataType: Float data type of the result tensor.
///   - axis: Axis on which the scale 1D value is being broadcasted
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of datatype dataType
-(MPSGraphTensor*) dequantizeTensor:(MPSGraphTensor*)tensor
                        scaleTensor:(MPSGraphTensor*)scaleTensor
                          zeroPoint:(double)zeroPoint
                           dataType:(MPSDataType)dataType
                               axis:(NSInteger)axis
                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( dequantize(_:scaleTensor:zeroPoint:dataType:axis:name:) );

/// Creates a Quantize operation and returns the result tensor.
///
/// Convert the float `tensor` to an i8 or u8 tensor by applying a scale + bias transform: 
/// result = (tensor / scaleTensor) + zeroPointTensor
///
/// - Parameters:
///   - tensor: Input tensor to be quantized
///   - scaleTensor: Scale scalar or 1D Tensor parameter with size == tensor.shape[axis]
///   - zeroPointTensor: Bias scalar or 1D Tensor parameter with size == tensor.shape[axis]
///   - dataType: Integer data type of the result tensor.
///   - axis: Axis on which the scale 1D value is being broadcasted
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of datatype dataType
-(MPSGraphTensor*) quantizeTensor:(MPSGraphTensor*)tensor
                      scaleTensor:(MPSGraphTensor*)scaleTensor
                  zeroPointTensor:(MPSGraphTensor*)zeroPointTensor
                         dataType:(MPSDataType)dataType
                             axis:(NSInteger)axis
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( quantize(_:scaleTensor:zeroPointTensor:dataType:axis:name:) );

/// Creates a dequantize operation and returns the result tensor.
///
/// Convert the i8 or u8 `tensor` to a float tensor by applying a scale + bias transform: 
/// result = scaleTensor(tensor - zeroPointTensor)
///
/// - Parameters:
///   - tensor: Input tensor to be dequantized
///   - scaleTensor: Scale scalar or 1D Tensor parameter with size == tensor.shape[axis]
///   - zeroPointTensor: Bias scalar or 1D Tensor parameter with size == tensor.shape[axis]
///   - dataType: Float data type of the result tensor.
///   - axis: Axis on which the scale 1D value is being broadcasted
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of datatype dataType
-(MPSGraphTensor*) dequantizeTensor:(MPSGraphTensor*)tensor
                        scaleTensor:(MPSGraphTensor*)scaleTensor
                    zeroPointTensor:(MPSGraphTensor*)zeroPointTensor
                           dataType:(MPSDataType)dataType
                               axis:(NSInteger)axis
                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( dequantize(_:scaleTensor:zeroPointTensor:dataType:axis:name:) );


/// Creates a dequantize operation and returns the result tensor.
///
/// Convert the i8, u8, i4 or u4 `tensor` to a float tensor by applying a scale and bias transform:
/// ```md
/// result = scaleTensor(tensor - zeroPointTensor).
/// ```
///
/// - Parameters:
///   - tensor: Input tensor to be dequantized.
///   - scaleTensor: The scale tensor with groups support.
///   - zeroPointTensor: The bias tensor with groups support.
///   - dataType: Float data type of the result tensor.
///   - name: The name for the operation.
/// - Returns: A valid ``MPSGraphTensor`` array of datatype `dataType`.
-(MPSGraphTensor*) dequantizeTensor:(MPSGraphTensor*)tensor
                        scaleTensor:(MPSGraphTensor*)scaleTensor
                    zeroPointTensor:(MPSGraphTensor*)zeroPointTensor
                           dataType:(MPSDataType)dataType
                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0))
MPS_SWIFT_NAME( dequantize(_:scaleTensor:zeroPointTensor:dataType:name:) );


/// Creates a dequantize operation and returns the result tensor.
///
/// Converts the i8, u8, i4 or u4 `tensor` to a float tensor by applying a scale and bias transform:
/// ```md
/// result = scaleTensor * tensor.
/// ```
///
/// - Parameters:
///   - tensor: Input tensor to be dequantized.
///   - scaleTensor: Scale Tensor parameter with groups support.
///   - dataType: Float data type of the result tensor.
///   - name: The name for the operation.
/// - Returns: A valid ``MPSGraphTensor`` array of datatype `dataType`.
-(MPSGraphTensor*) dequantizeTensor:(MPSGraphTensor*)tensor
                        scaleTensor:(MPSGraphTensor*)scaleTensor
                           dataType:(MPSDataType)dataType
                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0))
MPS_SWIFT_NAME( dequantize(_:scaleTensor:dataType:name:) );

/// Creates a lookup-table based quantization operation and returns the result tensor.
///
/// Converts a u8 or u4 `tensor` to a float tensor by applying a lookup operation:
/// ```md
/// result[i1,...,in] = LUTTensor[i1',...,in',tensor[i1,...,in]].
/// ```
/// Note: The operation supports LUT groups up to the last 3 dimensions for `tensor`.
///
/// - Parameters:
///   - tensor: Input tensor to be dequantized.
///   - LUTTensor: The lookup table to use - for u4 the last dimension should have 16 elements, and for u8 256 elements.
///   - name: The name for the operation.
/// - Returns: A valid ``MPSGraphTensor`` object.
-(MPSGraphTensor *) dequantizeTensor:(MPSGraphTensor *) tensor
                           LUTTensor:(MPSGraphTensor *) LUTTensor
                                name:(NSString * _Nullable) name
MPS_SWIFT_NAME( dequantize(_:LUTTensor:name:) )
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0));

/// Creates a vector lookup-table based quantization operation and returns the result tensor.
///
/// Converts a u8 or u4 `tensor` to a float tensor by applying a lookup operation, where each
/// input index defines a vector of values. The operation reads the vector values from the last dimension of the lookup table
/// tensor and stores them into the dimension defined by `axis` on the result tensor.
/// ```md
/// result[i1, ... , i_axis, ..., in] = LUTTensor[i1', ..., in', tensor[i1, ..., in], i_axis]
/// ```
/// Note: The operation supports LUT groups up to the last 2 dimensions for `tensor`.
///
/// - Parameters:
///   - tensor: Input tensor to be dequantized.
///   - LUTTensor: The lookup table to use - for u4 the second to last dimension should have 16 elements, and for u8 256 elements.
///   - axis: Axis on which the scale 1D value is being broadcasted.
///   - name: The name for the operation.
/// - Returns: A valid ``MPSGraphTensor`` object.
-(MPSGraphTensor *) dequantizeTensor:(MPSGraphTensor *) tensor
                           LUTTensor:(MPSGraphTensor *) LUTTensor
                                axis:(NSInteger) axis
                                name:(NSString * _Nullable) name
MPS_SWIFT_NAME( dequantize(_:LUTTensor:axis:name:) )
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0));

@end


NS_ASSUME_NONNULL_END

#endif /* MPSGraphQuantizationOps_h */
