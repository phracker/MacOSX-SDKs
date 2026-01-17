//
//  MPSGraphFourierTransformOps.h
//  MPSGraph
//
//  Created on 2/27/23.
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#ifndef MPSGraphFourierTransformOps_h
#define MPSGraphFourierTransformOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

/// The scaling modes for Fourier transform operations.
typedef NS_ENUM(NSUInteger, MPSGraphFFTScalingMode)
{
    /// Computes the FFT result with no scaling.
    MPSGraphFFTScalingModeNone          MPS_ENUM_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0)) MPS_SWIFT_NAME(none)   =  0L,
    /// Scales the FFT result with reciprocal of the total FFT size over all transformed dimensions.
    MPSGraphFFTScalingModeSize          MPS_ENUM_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0)),
    /// Scales the FFT result with reciprocal square root of the total FFT size over all transformed dimensions, resulting in signal strength conserving transformation.
    MPSGraphFFTScalingModeUnitary       MPS_ENUM_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
};

/// The class that defines the parameters for a fast Fourier transform (FFT) operation.
///
/// Use this descriptor with ``MPSGraph/fastFourierTransformWithTensor:axes:descriptor:name:``,
/// ``MPSGraph/realToHermiteanFFTWithTensor:axesTensor:descriptor:name:``, and
/// ``MPSGraph/HermiteanToRealFFTWithTensor:axesTensor:descriptor:name:`` methods.
MPS_CLASS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
@interface MPSGraphFFTDescriptor : MPSGraphObject<NSCopying>

/// A Boolean-valued parameter that defines the phase factor sign for Fourier transforms.
///
/// When set to `YES` graph uses the positive phase factor: `exp(+i 2Pi mu nu / n)`, when computing the (inverse) Fourier transform.
/// Otherwise MPSGraph uses the negative phase factor: `exp(-i 2Pi mu nu / n)`, when computing the Fourier transform.
/// Default value: `NO`.
@property (readwrite, nonatomic) BOOL inverse;

/// The scaling mode of the fast fourier transform (FFT) operation.
///
/// Note that the scaling mode is independent from the phase factor. Default value: `MPSGraphFFTScalingModeNone`.
@property (readwrite, nonatomic) MPSGraphFFTScalingMode scalingMode;

/// A parameter which controls how graph rounds the output tensor size for a Hermitean-to-real Fourier transform.
///
/// If set to `YES` then MPSGraph rounds the last output dimension of the result tensor in
/// ``MPSGraph/HermiteanToRealFFTWithTensor:axesTensor:descriptor:name:`` to an odd value.
/// Has no effect in the other Fourier transform operations.
/// Default value: `NO`.
@property (readwrite, nonatomic) BOOL roundToOddHermitean;

/// Creates a fast Fourier transform descriptor with default parameter values.
+(nullable instancetype) descriptor;

@end


MPS_CLASS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
@interface MPSGraph(MPSGraphFourierTransformOps)

/// Creates a fast Fourier transform operation and returns the result tensor.
///
/// This operation computes the fast Fourier transform of the input tensor according to the following formulae.
/// ```md
///     output[mu] = scale * sum_nu exp( +/- i * 2Pi * mu * nu / n ) input[nu], where
/// ```
/// `scale = 1` for `scaling_mode = none`,
/// `scale = 1/V_f` for `scaling_mode = size`,
/// `scale = 1/sqrt(V_f)` for `scaling_mode = unitary`, where
/// `V_f` is the volume of the transformation defined by the dimensions included in `axes`
/// (`V_f = prod_{i \in axes} shape(input)[i]`) (see ``MPSGraphFFTDescriptor/scalingMode``),
/// `+` is selected in `+/-` when `inverse` is specified, otherwise `-` is used
/// and the sum is done separately over each dimension in `axes` and `n` is the
/// dimension length of that axis.
///
///  > Tip: Currently MPSGraph supports the transformation only within the last four dimensions of the input tensor. In case
///  you need to transform higher dimensions than the last four, you can tranpose the higher dimensions of the input
///  with ``MPSGraph/transposeTensor:permutation:name:``  to be within that last four and then transpose
///  the result tensor back with the inverse of the input transpose.
///
/// - Parameters:
///   - tensor: A complex or real-valued input tensor.
///   - axes: An array of numbers that specifies over which axes MPSGraph performs the Fourier transform - all axes must be contained within last four dimensions of the input tensor.
///   - descriptor: A descriptor that defines the parameters of the Fourier transform operation - see ``MPSGraphFFTDescriptor``.
///   - name: The name for the operation.
/// - Returns: A valid complex-valued MPSGraphTensor of the same shape as `tensor`.
-(MPSGraphTensor *) fastFourierTransformWithTensor:(MPSGraphTensor *) tensor
                                              axes:(NSArray<NSNumber *> *) axes
                                        descriptor:(MPSGraphFFTDescriptor *) descriptor
                                              name:(NSString * _Nullable) name
MPS_SWIFT_NAME(fastFourierTransform(_:axes:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

/// Creates a fast Fourier transform operation and returns the result tensor.
///
/// This operation computes the fast Fourier transform of the input tensor according to the following formulae.
/// ```md
///     output[mu] = scale * sum_nu exp( +/- i * 2Pi * mu * nu / n ) input[nu], where
/// ```
/// `scale = 1` for `scaling_mode = none`,
/// `scale = 1/V_f` for `scaling_mode = size`,
/// `scale = 1/sqrt(V_f)` for `scaling_mode = unitary`, where
/// `V_f` is the volume of the transformation defined by the dimensions included in `axes`
/// (`V_f = prod_{i \in axes} shape(input)[i]`) (see ``MPSGraphFFTDescriptor/scalingMode``),
/// `+` is selected in `+/-` when `inverse` is specified, otherwise `-` is used
/// and the sum is done separately over each dimension in `axes` and `n` is the
/// dimension length of that axis.
///
///  > Tip: Currently MPSGraph supports the transformation only within the last four dimensions of the input tensor. In case
///  you need to transform higher dimensions than the last four, you can tranpose the higher dimensions of the input
///  with ``MPSGraph/transposeTensor:permutation:name:``  to be within that last four and then transpose
///  the result tensor back with the inverse of the input transpose.
///
/// - Parameters:
///   - tensor: A complex or real-valued input tensor.
///   - axesTensor: A tensor of rank one containing the axes over which MPSGraph performs the transformation. See ``MPSGraph/fastFourierTransformWithTensor:axes:descriptor:name:``.
///   - descriptor: A descriptor that defines the parameters of the Fourier transform operation - see ``MPSGraphFFTDescriptor``.
///   - name: The name for the operation.
/// - Returns: A valid complex-valued MPSGraphTensor of the same shape as `tensor`.
-(MPSGraphTensor *) fastFourierTransformWithTensor:(MPSGraphTensor *) tensor
                                        axesTensor:(MPSGraphTensor *) axesTensor
                                        descriptor:(MPSGraphFFTDescriptor *) descriptor
                                              name:(NSString * _Nullable) name
MPS_SWIFT_NAME(fastFourierTransform(_:axesTensor:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

/// Creates a Real-to-Hermitean fast Fourier transform operation and returns the result tensor.
///
/// This operation computes the fast Fourier transform of a real-valued input tensor according to the following formulae.
/// ```md
///     output[mu] = scale * sum_nu exp( +/- i * 2Pi * mu * nu / n ) input[nu], where
/// ```
/// `scale = 1` for `scaling_mode = none`,
/// `scale = 1/V_f` for `scaling_mode = size`,
/// `scale = 1/sqrt(V_f)` for `scaling_mode = unitary`, where
/// `V_f` is the volume of the transformation defined by the dimensions included in `axes`
/// (`V_f = prod_{i \in axes} shape(input)[i]`) (see ``MPSGraphFFTDescriptor/scalingMode``),
/// `+` is selected in `+/-` when `inverse` is specified, otherwise `-` is used
/// and the sum is done separately over each dimension in `axes` and `n` is the
/// dimension length of that axis. With this API MPSGraph writes out only the results for the unique
/// frequencies, resulting in a tensor which has size `(n/2)+1` in the last dimension defined by `axes`.
///
///  > Tip: Currently MPSGraph supports the transformation only within the last four dimensions of the input tensor. In case
///  you need to transform higher dimensions than the last four, you can tranpose the higher dimensions of the input
///  with ``MPSGraph/transposeTensor:permutation:name:``  to be within that last four and then transpose
///  the result tensor back with the inverse of the input transpose.
///
/// - Parameters:
///   - tensor: A Real-valued input tensor. Must have datatype `MPSDataTypeFloat32` or `MPSDatatypeFloat16`.
///   - axes: An array of numbers that specifies over which axes MPSGraph performs the Fourier transform - all axes must be contained within last four dimensions of the input tensor.
///   - descriptor: A descriptor that defines the parameters of the Fourier transform operation - see ``MPSGraphFFTDescriptor``.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor of type `MPSDataTypeComplexFloat32` or `MPSDataTypeComplexFloat16` with reduced size (see Discussion).
-(MPSGraphTensor *) realToHermiteanFFTWithTensor:(MPSGraphTensor *) tensor
                                            axes:(NSArray<NSNumber *> *) axes
                                      descriptor:(MPSGraphFFTDescriptor *) descriptor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME(realToHermiteanFFT(_:axes:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));


/// Creates a Real-to-Hermitean fast Fourier transform operation and returns the result tensor.
///
/// This operation computes the fast Fourier transform of a real-valued input tensor according to the following formulae.
/// ```md
///     output[mu] = scale * sum_nu exp( +/- i * 2Pi * mu * nu / n ) input[nu], where
/// ```
/// `scale = 1` for `scaling_mode = none`,
/// `scale = 1/V_f` for `scaling_mode = size`,
/// `scale = 1/sqrt(V_f)` for `scaling_mode = unitary`, where
/// `V_f` is the volume of the transformation defined by the dimensions included in `axes`
/// (`V_f = prod_{i \in axes} shape(input)[i]`) (see ``MPSGraphFFTDescriptor/scalingMode``),
/// `+` is selected in `+/-` when `inverse` is specified, otherwise `-` is used
/// and the sum is done separately over each dimension in `axes` and `n` is the
/// dimension length of that axis. With this API MPSGraph writes out only the results for the unique
/// frequencies, resulting in a tensor which has size `(n/2)+1` in the last dimension defined by `axes`.
///
///  > Tip: Currently MPSGraph supports the transformation only within the last four dimensions of the input tensor. In case
///  you need to transform higher dimensions than the last four, you can tranpose the higher dimensions of the input
///  with ``MPSGraph/transposeTensor:permutation:name:``  to be within that last four and then transpose
///  the result tensor back with the inverse of the input transpose.
///
/// - Parameters:
///   - tensor: A real-valued input tensor. Must have datatype `MPSDataTypeFloat32` or `MPSDatatypeFloat16`.
///   - axesTensor: A tensor of rank one containing the axes over which MPSGraph performs the transformation. See ``MPSGraph/fastFourierTransformWithTensor:axes:descriptor:name:``.
///   - descriptor: A descriptor that defines the parameters of the Fourier transform operation - see ``MPSGraphFFTDescriptor``.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor of type `MPSDataTypeComplexFloat32` or `MPSDataTypeComplexFloat16`  with reduced size (see Discussion).
-(MPSGraphTensor *) realToHermiteanFFTWithTensor:(MPSGraphTensor *) tensor
                                      axesTensor:(MPSGraphTensor *) axesTensor
                                      descriptor:(MPSGraphFFTDescriptor *) descriptor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME(realToHermiteanFFT(_:axesTensor:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

/// Creates a Hermitean-to-real fast Fourier transform operation and returns the result tensor.
///
/// This operation computes the fast Fourier transform of a complex-valued input tensor according to the following formulae.
/// ```md
///     output[mu] = scale * sum_nu exp( +/- i * 2Pi * mu * nu / n ) in'[nu], where
/// ```
/// `in'[nu] = conjugate(in[n - nu])`, for the last dimension defined by `axes` when `nu` is out of range of the input dimension.
/// `scale = 1` for `scaling_mode = none`,
/// `scale = 1/V_f` for `scaling_mode = size`,
/// `scale = 1/sqrt(V_f)` for `scaling_mode = unitary`, where
/// `V_f` is the volume of the transformation defined by the dimensions included in `axes`
/// (`V_f = prod_{i \in axes} shape(input)[i]`) (see ``MPSGraphFFTDescriptor/scalingMode``),
/// `+` is selected in `+/-` when `inverse` is specified, otherwise `-` is used
/// and the sum is done separately over each dimension in `axes` and `n` is the
/// dimension length of that axis. With this API MPSGraph treats the input tensor to have only the unique
/// frequencies, which means that the resulting tensor has size `(inSize-1)*2 + x` in the last dimension defined by `axes`,
/// where `inSize = shape(input)[axis] ( = (n/2)+1 )` is the size of the input `tensor` in the last transformed dimension and
/// `x = 1` when ``MPSGraphFFTDescriptor/roundToOddHermitean`` = `YES` and `x = 0` otherwise.
///
///  > Tip: Currently transformation is supported only within the last four dimensions of the input tensor. In case
///  you need to transform higher dimensions than the last four, you can tranpose the higher dimensions of the input
///  with ``MPSGraph/transposeTensor:permutation:name:``  to be within that last four and then transpose
///  the result tensor back with the inverse of the input transpose.
///
/// - Parameters:
///   - tensor: A complex-valued input tensor with reduced size (see Discussion). Must have datatype `MPSDataTypeComplexFloat32` or `MPSDataTypeComplexFloat16`.
///   - axes: An array of numbers that specifies over which axes MPSGraph performs the Fourier transform - all axes must be contained within last four dimensions of the input tensor.
///   - descriptor: A descriptor that defines the parameters of the Fourier transform operation - see ``MPSGraphFFTDescriptor``.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor of type `MPSDataTypeFloat32` or `MPSDataTypeFloat16` (full size).
-(MPSGraphTensor *) HermiteanToRealFFTWithTensor:(MPSGraphTensor *) tensor
                                            axes:(NSArray<NSNumber *> *) axes
                                      descriptor:(MPSGraphFFTDescriptor *) descriptor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME(HermiteanToRealFFT(_:axes:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));


/// Creates a Hermitean-to-real fast Fourier transform operation and returns the result tensor.
///
/// This operation computes the fast Fourier transform of a complex-valued input tensor according to the following formulae.
/// ```md
///     output[mu] = scale * sum_nu exp( +/- i * 2Pi * mu * nu / n ) in'[nu], where
/// ```
/// `in'[nu] = conjugate(in[n - nu])`, for the last dimension defined by `axes` when `nu` is out of range of the input dimension.
/// `scale = 1` for `scaling_mode = none`,
/// `scale = 1/V_f` for `scaling_mode = size`,
/// `scale = 1/sqrt(V_f)` for `scaling_mode = unitary`, where
/// `V_f` is the volume of the transformation defined by the dimensions included in `axes`
/// (`V_f = prod_{i \in axes} shape(input)[i]`) (see ``MPSGraphFFTDescriptor/scalingMode``),
/// `+` is selected in `+/-` when `inverse` is specified, otherwise `-` is used
/// and the sum is done separately over each dimension in `axes` and `n` is the
/// dimension length of that axis. With this API MPSGraph treats the input tensor to have only the unique
/// frequencies, which means that the resulting tensor has size `(inSize-1)*2 + x` in the last dimension defined by `axes`,
/// where `inSize = shape(input)[axis] ( = (n/2)+1 )` is the size of the input `tensor` in the last transformed dimension and
/// `x = 1` when ``MPSGraphFFTDescriptor/roundToOddHermitean`` = `YES` and `x = 0` otherwise.
///
///  > Tip: Currently MPSGraph supports the transformation only within the last four dimensions of the input tensor. In case
///  you need to transform higher dimensions than the last four, you can tranpose the higher dimensions of the input
///  with ``MPSGraph/transposeTensor:permutation:name:``  to be within that last four and then transpose
///  the result tensor back with the inverse of the input transpose.
///
/// - Parameters:
///   - tensor: A complex-valued input tensor with reduced size (see Discussion). Must have datatype `MPSDataTypeComplexFloat32` or `MPSDataTypeComplexFloat16`.
///   - axesTensor: A tensor of rank one containing the axes over which MPSGraph performs the transformation. See ``MPSGraph/fastFourierTransformWithTensor:axes:descriptor:name:``.
///   - descriptor: A descriptor that defines the parameters of the Fourier transform operation - see ``MPSGraphFFTDescriptor``.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor of type `MPSDataTypeFloat32` or `MPSDataTypeFloat16` (full size).
-(MPSGraphTensor *) HermiteanToRealFFTWithTensor:(MPSGraphTensor *) tensor
                                      axesTensor:(MPSGraphTensor *) axesTensor
                                      descriptor:(MPSGraphFFTDescriptor *) descriptor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME(HermiteanToRealFFT(_:axesTensor:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphFourierTransformOps_h */
