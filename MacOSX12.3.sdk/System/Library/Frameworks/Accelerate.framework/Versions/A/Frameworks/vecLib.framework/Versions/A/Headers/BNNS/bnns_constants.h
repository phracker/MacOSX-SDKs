//
//  bnns_constants.h
//  BasicNeuralNetworkSubroutines
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#ifndef __BNNS_CONSTANTS_HEADER__
#define __BNNS_CONSTANTS_HEADER__

#include <stdint.h>

#if __has_feature(objc_fixed_enum) || __has_extension(cxx_strong_enums)
#define BNNS_ENUM(_name, _type, ...) \
        typedef enum : _type { __VA_ARGS__ } _name
#else
#define BNNS_ENUM(_name, _type, ...) \
        enum { __VA_ARGS__ }; typedef _type _name
#endif

#if __has_include( <Availability.h> )
#include <Availability.h>
#else
#define __API_AVAILABLE(...)
#define __API_DEPRECATED_WITH_REPLACEMENT(...)
#define __API_AVAILABLE(...)
#endif

/*!

 @abstract Storage data type

 @constant BNNSDataTypeFloatBit
 Common bit to floating point types, this constant is not a valid type

 @constant BNNSDataTypeFloat16
 16-bit half precision floating point

 @constant BNNSDataTypeFloat32
 32-bit single precision floating point

 @constant BNNSDataTypeBFloat16
 16-bit brain floating Point

 @constant BNNSDataTypeIntBit
 Common bit to signed integer types, this constant is not a valid type

 @constant BNNSDataTypeInt8
 8-bit signed integer

 @constant BNNSDataTypeInt16
 16-bit signed integer

 @constant BNNSDataTypeInt32
 32-bit signed integer

 @constant BNNSDataTypeInt64
 64-bit signed integer

 @constant BNNSDataTypeUIntBit
 Common bit to unsigned integer types, this constant is not a valid type

 @constant BNNSDataTypeUInt8
 8-bit unsigned integer

 @constant BNNSDataTypeUInt16
 16-bit unsigned integer

 @constant BNNSDataTypeUInt32
 32-bit unsigned integer

 @constant BNNSDataTypeUInt64
 64-bit unsigned integer

 @constant BNNSDataTypeIndexedBit
 Common bit to indexed floating point types, this constant is not a valid type

 @constant BNNSDataTypeIndexed2
 2-bit unsigned indices into a floating point conversion table (4 values)

 @constant BNNSDataTypeIndexed4
 4-bit unsigned indices into a floating point conversion table (16 values)

 @constant BNNSDataTypeIndexed8
 8-bit unsigned indices into a floating point conversion table (256 values)

 @constant BNNSDataTypeMiscellaneousBit
 Common bit to miscellaneous types, this constant is not a valid type

 @constant BNNSDataTypeBoolean
 bool value

*/
BNNS_ENUM(BNNSDataType, uint32_t,

  BNNSDataTypeFloatBit         __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = 0x10000,
  BNNSDataTypeFloat16          __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = BNNSDataTypeFloatBit | 16,
  BNNSDataTypeFloat32          __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = BNNSDataTypeFloatBit | 32,
  BNNSDataTypeBFloat16         __API_AVAILABLE(macos(12.0),  ios(15.0), watchos(8.0), tvos(15.0)) = BNNSDataTypeFloatBit | 0x8000 | 16,

  BNNSDataTypeIntBit           __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = 0x20000,
  BNNSDataTypeInt1             __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = BNNSDataTypeIntBit | 1,
  BNNSDataTypeInt2             __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = BNNSDataTypeIntBit | 2,
  BNNSDataTypeInt4             __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = BNNSDataTypeIntBit | 4,
  BNNSDataTypeInt8             __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = BNNSDataTypeIntBit | 8,
  BNNSDataTypeInt16            __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = BNNSDataTypeIntBit | 16,
  BNNSDataTypeInt32            __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = BNNSDataTypeIntBit | 32,
  BNNSDataTypeInt64            __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = BNNSDataTypeIntBit | 64,

  BNNSDataTypeUIntBit          __API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) = 0x40000,
  BNNSDataTypeUInt1            __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = BNNSDataTypeUIntBit | 1,
  BNNSDataTypeUInt2            __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = BNNSDataTypeUIntBit | 2,
  BNNSDataTypeUInt4            __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = BNNSDataTypeUIntBit | 4,
  BNNSDataTypeUInt8            __API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) = BNNSDataTypeUIntBit | 8,
  BNNSDataTypeUInt16           __API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) = BNNSDataTypeUIntBit | 16,
  BNNSDataTypeUInt32           __API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) = BNNSDataTypeUIntBit | 32,
  BNNSDataTypeUInt64           __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = BNNSDataTypeUIntBit | 64,

  BNNSDataTypeIndexedBit       __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = 0x80000,
  BNNSDataTypeIndexed1         __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = BNNSDataTypeIndexedBit | 1,
  BNNSDataTypeIndexed2         __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = BNNSDataTypeIndexedBit | 2,
  BNNSDataTypeIndexed4         __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = BNNSDataTypeIndexedBit | 4,
  BNNSDataTypeIndexed8         __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = BNNSDataTypeIndexedBit | 8,

  BNNSDataTypeMiscellaneousBit __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x100000,
  BNNSDataTypeBoolean          __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = BNNSDataTypeMiscellaneousBit | 8,
);

/*!

 @abstract Pooling layer function

 @discussion
 In the definitions below, the input sample is <tt>X<sub>i</sub></tt> and has <tt>N</tt> elements.

 @constant BNNSPoolingFunctionMax
 max(X<sub>i</sub>)

 @constant BNNSPoolingFunctionAverageCountIncludePadding
 &sum;<sub>i</sub> X<sub>i</sub> / N

 @constant BNNSPoolingFunctionAverageCountExcludePadding
 &sum;<sub>i</sub> X<sub>i</sub> / n
 - n is number of elements that weren't zero padded

 @constant BNNSPoolingFunctionUnMax
 partial inverse of max(X<sub>i</sub>) in which all non-maximal values are set to zero

 @constant BNNSPoolingFunctionL2Norm
 <math><msqrt><mi>&sum;<sub>i</sub> X<sub>i</sub><sup>2</sup></mi></msqrt></math>

*/
BNNS_ENUM(BNNSPoolingFunction, uint32_t,

  BNNSPoolingFunctionMax                        __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = 0,
  BNNSPoolingFunctionAverageCountIncludePadding __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 1,
  BNNSPoolingFunctionAverageCountExcludePadding __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 2,
  BNNSPoolingFunctionUnMax                      __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 3,
  BNNSPoolingFunctionL2Norm                     __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 4,

  BNNSPoolingFunctionAverage  __API_DEPRECATED_WITH_REPLACEMENT("BNNSPoolingFunctionAverageCountIncludePadding", macos(10.12, 11.0), ios(10.0, 14.0), watchos(3.0, 7.0), tvos(10.0, 14.0)) = BNNSPoolingFunctionAverageCountIncludePadding,

);

/*!

 @abstract Activation layer function

 @constant BNNSActivationFunctionIdentity
 x

 @constant BNNSActivationFunctionRectifiedLinear
 0 if x<0, and x if x>=0

 @constant BNNSActivationFunctionLeakyRectifiedLinear
 alpha*x if x<0, and x if x>=0
 A pointer to the alpha value can be obtained via a BNNSGetPointer() call, and the delta with respect to alpha
 is obtained via the weights_delta field in a call to BNNSApplyBackward() or BNNSApplyBackwardBatch() of a standalone
 Activation layer (the delta is not available in situations where the activation is fused with another layer).

 @constant BNNSActivationFunctionSigmoid
 sigmoid(x)

 @constant BNNSActivationFunctionLogSigmoid
 log(sigmoid(x))

 @constant BNNSActivationFunctionTanh
 tanh(x)

 @constant BNNSActivationFunctionScaledTanh
 alpha*tanh(x*beta)

 @constant BNNSActivationFunctionAbs
 abs(x)

 @constant BNNSActivationFunctionLinear
 alpha*x

 @constant BNNSActivationFunctionClamp
 min(max(x, alpha), beta)

 @constant BNNSActivationFunctionIntegerLinearSaturate
 Saturate<output_type>((iscale * x + ioffset) >> ishift)
 This is an arithmetic shift, preserving sign.

 @constant BNNSActivationFunctionIntegerLinearSaturatePerChannel
 Saturate<output_type>((iscale_per_channel[channel] * x + ioffset_per_channel[channel]) >> ishift_per_channel[channel]) for each channel
 This is an arithmetic shift, preserving sign.

 @constant BNNSActivationFunctionSoftmax
 softmax(x)_i = exp(x_i) / ( sum_i exp(x_i) ).

 @constant BNNSActivationFunctionGELUApproximation
 GELUApproximation(x)_i = 0.5f * x * (1.0f + tanh(alpha*(x + beta * x * x * x))).

 @constant BNNSActivationFunctionGumbel
 Gumbel_i =  −log(−log(alpha*Uniform(0,1)+beta)+beta)

 @constant BNNSActivationFunctionGumbelMax
 GumbelMax(X)_i = MAX(−log(−log(alpha*Uniform(0,1)+beta)+beta) + Xj)

 @constant BNNSActivationFunctionHardSigmoid
 HardSigmoid(x) = max(0, min(1, alpha*x + beta))

 @constant BNNSActivationFunctionSoftplus
 Softplus(x) = alpha * log( 1 + exp(beta*x) )

 @constant BNNSActivationFunctionSoftsign
 Softsign(x) = x / (1 + |x| )

 @constant BNNSActivationFunctionELU
 ELU(x) = alpha*(exp(x) - 1) if x < 0, and x if x >= 0

 @constant BNNSActivationFunctionSELU
 SELU(x) = 1.0507009873554804934193349852946*(1.6732632423543772848170429916717*(exp(x) - 1)) if x < 0,
         and 1.0507009873554804934193349852946*x if x >= 0

 @constant BNNSActivationFunctionCELU
 ELU(x) = alpha*(exp(x/alpha) - 1) if x < 0, and x if x >= 0

 @constant BNNSActivationFunctionClampedLeakyRectifiedLinear
 CLReLU(x) = min( alpha*x, beta) if x < 0, and min(x, beta) if  x >= 0

 @constant BNNSActivationFunctionLinearWithBias
 alpha*x + beta

 @constant BNNSActivationFunctionLogSoftmax
 log_softmax(x)_i = log( exp(x_i) / ( sum_i exp(x_i) ) ).

 @constant BNNSActivationFunctionHardShrink
 0 if abs(x) < abs(alpha), and x otherwise

 @constant BNNSActivationFunctionSoftShrink
 0 if abs(x) < abs(alpha), and x-copysign(alpha, x) otherwise

 @constant BNNSActivationFunctionTanhShrink
 TanhShrink(x) = x − tanh(x)

 @constant BNNSActivationFunctionThreshold
 beta if x <= alpha, and x otherwise

 @constant BNNSActivationFunctionPReLUPerChannel
 alpha_c*x if x<0, and x if x>=0      (i.e. Leaky ReLU with per-channel alpha values)
 This activation is only valid for use with layouts of type BNNSDataLayoutImageCHW.
 The provided alpha value is used to initialize an array of alpha_c values, one per channel: if a PReLU with a shared alpha
 across all channels is required, use BNNSActivationFunctionLeakyRectifiedLinear with BNNSGetPointer().
 These values can then be updated (i.e. trained) individually using pointers obtained via BNNSGetPointer() calls.
 The delta vector with respect to alpha_c is obtained via the weights_delta field in a call to BNNSApplyBackward() or
 BNNSApplyBackwardBatch() of a standalone Activation layer (the delta is not available if situations where the activation is fused with another layer).

 @constant BNNSActivationFunctionGELUApproximation2
 GELUApproximation2(x) = x*(ReLU6(x + 3.0) * 1.0/6.0)

 @constant BNNSActivationFunctionHardSwish
 Same as BNNSActivationFunctionGELUApproximation2.
 HardSwish(x) = GELUApproximation2(x) = x*(ReLU6(x + 3.0) * 1.0/6.0)

 @constant BNNSActivationFunctionSiLU
 SiLU(x) = x*sigmoid(x)

*/
BNNS_ENUM(BNNSActivationFunction, uint32_t,

  BNNSActivationFunctionIdentity                         __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) =  0,
  BNNSActivationFunctionRectifiedLinear                  __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) =  1,
  BNNSActivationFunctionLeakyRectifiedLinear             __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) =  2,
  BNNSActivationFunctionSigmoid                          __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) =  3,
  BNNSActivationFunctionTanh                             __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) =  4,
  BNNSActivationFunctionScaledTanh                       __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) =  5,
  BNNSActivationFunctionAbs                              __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) =  6,
  BNNSActivationFunctionLinear                           __API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) =  7,
  BNNSActivationFunctionClamp                            __API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) =  8,
  BNNSActivationFunctionIntegerLinearSaturate            __API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) =  9,
  BNNSActivationFunctionIntegerLinearSaturatePerChannel  __API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) = 10,
  BNNSActivationFunctionSoftmax                          __API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) = 11,
  BNNSActivationFunctionGELUApproximation                __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 12,
  BNNSActivationFunctionGumbel                           __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 13,
  BNNSActivationFunctionGumbelMax                        __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 14,
  BNNSActivationFunctionHardSigmoid                      __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 15,
  BNNSActivationFunctionSoftplus                         __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 16,
  BNNSActivationFunctionSoftsign                         __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 17,
  BNNSActivationFunctionELU                              __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 18,
  BNNSActivationFunctionClampedLeakyRectifiedLinear      __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 19,
  BNNSActivationFunctionLinearWithBias                   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 20,
  BNNSActivationFunctionLogSoftmax                       __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 21,
  BNNSActivationFunctionLogSigmoid                       __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 22,
  BNNSActivationFunctionSELU                             __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 23,
  BNNSActivationFunctionCELU                             __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 24,
  BNNSActivationFunctionHardShrink                       __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 25,
  BNNSActivationFunctionSoftShrink                       __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 26,
  BNNSActivationFunctionTanhShrink                       __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 27,
  BNNSActivationFunctionThreshold                        __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 28,
  BNNSActivationFunctionPReLUPerChannel                  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 29,
  BNNSActivationFunctionGELUApproximation2               __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 30,
  BNNSActivationFunctionHardSwish                        __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = BNNSActivationFunctionGELUApproximation2,
  BNNSActivationFunctionSiLU                             __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 31,

);

/*!

  @abstract Filter flags

  @constant BNNSFlagsUseClientPtr

  Instructs the filter to keep the pointers provided by the client at creation time (weights, bias), and work directly from this data. In that
  case, the client must ensure these pointers remain valid through the entire lifetime of the filter.

  If not set, the filter creation function must allocate buffers, and keep an internal copy of the data. In that case, the client doesn't have
  to keep the pointers valid after the filter is created.

*/
BNNS_ENUM(BNNSFlags, uint32_t,

          BNNSFlagsUseClientPtr  __API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = 0x0001,
          );

/*!

 @abstract Loss layer function

 @constant BNNSLossFunctionSoftmaxCrossEntropy
 perform softmax on input logits and compute cross entropy loss with one hot encoded labels.
 labels can be smoothed according to smoothing factor, loss can be scaled with scalar or vector weight and reduced according to reduction function
 for each sample in the batch:
    p = softmax(in sample)
    labels = one hot encoded lables for in sample
    weight = scaling factor
    sample loss = (1/number_of_classes)*(-1*sum_over_all_classes_i(labels[i]*log(p[i])*weight)

 @constant BNNSLossFunctionSigmoidCrossEntropy
 perform sigmoid on input logits and compute cross entropy loss for each class independently.
 labels can be smoothed according to smoothing factor, loss can be scaled with scalar or weight matrix (matrix size = number_of_classes*batch_size) and reduced according to reduction function
 for each class in each sample in the batch:
    weight = scaling factor
    sample class loss[i] = weight*(-label[i]*log(sigmoid(logit[i])) - (1-label[i])*log(1-sigmoid(logit[i])))

 loss = reduction(all batch sample class loss)

 @constant BNNSLossFunctionMeanSquareError
 performs mean square error (MSE) computation between input logits and one hot encoded labels.
 loss can be scaled with scalar or weight matrix (matrix size = number_of_classes*batch_size) and reduced according to reduction function
 for each class in each sample in the batch:
    weight = scaling factor
    sample class mse[i] = weight * (logit[i] - label[i]) * (logit[i] - label[i])

 loss = reduction(all batch sample class loss)

 @constant BNNSLossFunctionHuber
 performs huber loss computation between input logits and one hot encoded labels.
 loss can be scaled with scalar or weight matrix (matrix size = number_of_classes*batch_size) and reduced according to reduction function
 for each class in each sample in the batch:
    weight = scaling factor
    error[i] = logit[i] - label[i]
    abs(error[i]) <= delta : huber[i] = weight * 0.5 * error[i] * error[i]
    abs(error[i]) > delta :  huber[i] = weight * delta * (abs(error) - 0.5 * delta)

 loss = reduction(all batch sample loss)

 @constant BNNSLossFunctionYolo
 performs yolo loss computation between prediction and ground truth labels
 Implementation is based on yolo papers, such as the following:
 You Only Look Once: Unified, Real-Time Object Detection: https://arxiv.org/abs/1506.02640
 SSD: Single Shot MultiBox Detector: https://arxiv.org/abs/1512.02325
 YOLO9000: Better, Faster, Stronger:  https://arxiv.org/abs/1612.08242

 prediction represented as: |x,y,w,h,conf,c1,c2...cn| * number of anchors * number of cells in grid
 ground_truth represented as: |x,y,w,h,conf,c1,c2...cn| * number of anchors * number of cells in grid
 It is assumed that ground truth confidence is 0 if there is no object in the current cell, or 1 if there is an object  in the current cell
 It is also assumed that ground truth is duplicated for all anchors in a given cell.

 The loss function is a hybrid of the following functions:
 x,y: MSE
 w,h: Huber
 confidence: Sigmoid Cross Entropy
 classification: Softmax Cross Entropy

 loss = sum of all loss componenets (x,y,w,h,conf,class)

 @constant BNNSLossFunctionLog
 performs log loss computation between labels (ground truth output tensor) and predictions (predicted outputs).
 loss can be scaled with scalar or weight matrix (matrix size = number_of_classes*batch_size) and reduced according to reduction function
 for each class in each sample in the batch:
    weight = scaling factor
    p_i = predictions[i] + epsilon;
    pm1_i = 1 - predictions[i] + epsilon;
    t_i = labels[i];
    log_loss[i] = -t_i *log( p_i ) - (1 - t_i) * log( pm1_i );
    in_delta[i] = (p_i - t_i)/(p_i*pm1_i);

 loss = reduction(all batch sample class loss)

 @constant BNNSLossFunctionCosineDistance
 performs cosine distance loss computation between labels (ground truth output tensor) and predictions (predicted outputs).
 both labels and predictions SHOULD be unit-normalized.
 loss can be scaled with scalar or weight matrix (matrix size = number_of_classes*batch_size) and reduced according to reduction function
 for each class in each sample in the batch:
    weight = scaling factor
    p_i = predictions[i];
    t_i = labels[i];
    loss = 1. - SUM (weight * t_i * p_i );
    in_delta[i] = -t_i + (1-loss)) * p_i;

 loss = reduction(all batch sample class loss)

 @constant BNNSLossFunctionHinge
 performs Hinge loss computation between labels (ground truth output tensor, 0 or 1) and logits (unbpunded 0-centered binary predictions).
 loss can be scaled with scalar or weight matrix (matrix size = number_of_classes*batch_size) and reduced according to reduction function
 for each class in each sample in the batch:
    weight = scaling factor
    t_i = 2*labels[i] - 1;  // convert 0 or 1 to -1 or 1
    loss = max(0, 1 - t_i * logits_i;

    in_delta[i] = -1 if logits_i <= 1 and t_i == 1
                   0 if logits_i > 1 and t_i == 1
                   1 if logits_i >= -1 and t_i == -1
                   0 if logits_i < -1 and t_i == -1


 loss = reduction(all batch sample class loss)

 @constant BNNSLossFunctionMeanAbsoluteError
 performs mean absolute error (MAE) computation between input prediction and labels.
 loss can be scaled with scalar or weight matrix (matrix size = number_of_classes*batch_size) and reduced according to reduction function
 for each class in each sample in the batch:
    weight = scaling factor
    sample class mae[i] = weight * absolute(prediction[i] - label[i]);

    in_delta[i] = 1 if prediction_i >= label_i
                 -1 otherwisze

 loss = reduction(all batch sample class loss)

 @constant BNNSLossFunctionCategoricalCrossEntropy
 performs categorical cross entropy (softmax activation plus a cross entropy loss) computation between input prediction and labels.
 loss can be scaled with scalar or weight matrix (matrix size = number_of_classes*batch_size) and reduced according to reduction function
 for each class in each sample in the batch:
    weight = scaling factor
    numM = number of nonzero labels;
    scale_factor = 1/numM;
    logprobs = 0;
    for each element c in labels
       if (labels[r,c] != 0) logprobs += -log(probs[c]) * labels[c] * weight[c] * scale_factor;

       if (labels[r,c] != 0)
          in_delta[r,c] = weight[c] * (probs[c] - scale_factor);
       else
          in_delta[r,c] = probs[c];

 loss = reduction(all batch sample class loss)

 */
BNNS_ENUM(BNNSLossFunction, uint32_t,

          BNNSLossFunctionSoftmaxCrossEntropy      __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  1,
          BNNSLossFunctionSigmoidCrossEntropy      __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  2,
          BNNSLossFunctionMeanSquareError          __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  3,
          BNNSLossFunctionHuber                    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  4,
          BNNSLossFunctionYolo                     __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  5,
          BNNSLossFunctionLog                      __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  6,
          BNNSLossFunctionCosineDistance           __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  7,
          BNNSLossFunctionHinge                    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  8,
          BNNSLossFunctionMeanAbsoluteError        __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  9,
          BNNSLossFunctionCategoricalCrossEntropy  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 10,
          );

/*!

 @abstract Loss layer reduction function

 @constant BNNSLossReductionNone
 No reduction. Output loss size equal to input size.

 @constant BNNSLossReductionSum
 Sum the loss of all samples in the batch.

 @constant BNNSLossReductionWeightedMean
 Sum the loss of all samples in the batch and divide by the sum of all weights.
 0 is returned if the sum of all weights is 0.

 @constant BNNSLossReductionMean
 Sum the loss of all samples in the batch and divide by number of samples.

 @constant  BNNSLossReductionNonZeroWeightMean
 Sum the loss of all samples in the batch and divide by number of non zero weights.
 0 is returned in case all weights are zero.

 */
BNNS_ENUM(BNNSLossReductionFunction, uint32_t,

          BNNSLossReductionNone               __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0,
          BNNSLossReductionSum                __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 1,
          BNNSLossReductionWeightedMean       __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 2,
          BNNSLossReductionMean               __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 3,
          BNNSLossReductionNonZeroWeightMean  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 4,
          );

/*!

 @abstract Arithmetic function

 @constant BNNSArithmeticAdd
 Arithmetic function add
 element-wise computation of out = in1+in2
 in-place computation is supported for forward and gradient
 arithmetic_function_fields must point to BNNSArithmeticBinary structure

 @constant BNNSArithmeticSubtract
 Arithmetic function subtract
 element-wise computation of out = in1-in2
 in-place computation is supported for forward and gradient
 arithmetic_function_fields must point to BNNSArithmeticBinary structure

 @constant BNNSArithmeticMultiply
 Arithmetic function multiply
 element-wise computation of out = in1*in2
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticBinary structure

 @constant BNNSArithmeticDivide
 Arithmetic function divide
 element-wise computation of out = in1/in2
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticBinary structure

 @constant BNNSArithmeticSquareRoot
 Arithmetic function square root
 element-wise computation of out = √in
 in-place computation is supported for inference
 in-place computation is supported for gradient if activation function is identity
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticReciprocalSquareRoot
 Arithmetic function reciprocal square root
 element-wise computation of out = 1/√in
 in-place computation is supported for inference
 in-place computation is supported for gradient if activation function is identity
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticCeil
 Arithmetic function ceil
 element-wise computation of out = ceil(in)
 in-place computation is supported for forward and gradient
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticFloor
 Arithmetic function floor
 element-wise computation of out = floor(in)
 in-place computation is supported for forward and gradient
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticRound
 Arithmetic function round
 element-wise computation of out = round(in)
 in-place computation is supported for forward and gradient
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticSin
 Arithmetic function sine
 element-wise computation of out = sin(in)
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticCos
 Arithmetic function cosine
 element-wise computation of out = cos(in)
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticTan
 Arithmetic function tangent
 element-wise computation of out = tan(in)
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticAsin
 Arithmetic function inverse sine
 element-wise computation of out = asin(in)
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticAcos
 Arithmetic function inverse cosine
 element-wise computation of out = acos(in)
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticAtan
 Arithmetic function inverse tangent
 element-wise computation of out = atan(in)
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticSinh
 Arithmetic function hyperbolic sine
 element-wise computation of out = sinh(in)
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticCosh
 Arithmetic function hyperbolic cosine
 element-wise computation of out = cosh(in)
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticTanh
 Arithmetic function hyperbolic tangent
 element-wise computation of out = tanh(in)
 in-place computation is supported for inference
 in-place computation is supported for gradient if activation function is identity
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticAsinh
 Arithmetic function inverse hyperbolic sine
 element-wise computation of out = asinh(in)
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticAcosh
 Arithmetic function inverse hyperbolic cosine
 element-wise computation of out = acosh(in)
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticAtanh
 Arithmetic function inverse hyperbolic tangent
 element-wise computation of out = atanh(in)
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticPow
 Arithmetic function power
 element-wise computation of out = in1**in2
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticBinary structure

 @constant BNNSArithmeticExp
 Arithmetic function exp
 element-wise computation of e raised to the power of x. out = e^x
 in-place computation is supported for inference
 in-place computation is supported for gradient if activation function is identity
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticExp2
 Arithmetic function exp2
 element-wise computation of 2 raised to the power of x. out = 2^x
 in-place computation is supported for inference
 in-place computation is supported for gradient if activation function is identity
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticLog
 Arithmetic function log
 element-wise computation of the natural logarithm of x. out = log(x)
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticLog2
 Arithmetic function log2
 element-wise computation of the base 2 logarithm of x. out = log2(x)
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticUnary structure

 @constant BNNSArithmeticMultiplyNoNaN
 Arithmetic function multiply, returns 0 if the in2 is zero, even if in1 is NaN or infinite
 element-wise computation of out = in1*in2
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticBinary structure

 @constant BNNSArithmeticDivideNoNaN
 Arithmetic function divide, returns 0 if the in2 is zero.
 element-wise computation of out = in1/in2
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticBinary structure

 @constant BNNSArithmeticMultiplyAdd
 Arithmetic function multiply-add
 element-wise computation of out = in1*in2 + in3
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticTernary structure

 @constant BNNSArithmeticMinimum
 Arithmetic function minimum
 element-wise computation of out = min(in1, in2)
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticBinary structure

 @constant BNNSArithmeticMaximum
 Arithmetic function maximum
 element-wise computation of out = max(in1, in2)
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticBinary structure

 @constant BNNSArithmeticSelect
 Arithmetic function select
 element-wise computation of out = in1 ? in2 : in3
 in-place computation is supported for inference only
 arithmetic_function_fields must point to BNNSArithmeticTernary structure

 */
BNNS_ENUM(BNNSArithmeticFunction, uint32_t,

          BNNSArithmeticAdd                   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  0,
          BNNSArithmeticSubtract              __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  1,
          BNNSArithmeticMultiply              __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  2,
          BNNSArithmeticDivide                __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  3,
          BNNSArithmeticSquareRoot            __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  4,
          BNNSArithmeticReciprocalSquareRoot  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  5,
          BNNSArithmeticCeil                  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  6,
          BNNSArithmeticFloor                 __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  7,
          BNNSArithmeticRound                 __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  8,
          BNNSArithmeticSin                   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  9,
          BNNSArithmeticCos                   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 10,
          BNNSArithmeticTan                   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 11,
          BNNSArithmeticAsin                  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 12,
          BNNSArithmeticAcos                  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 13,
          BNNSArithmeticAtan                  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 14,
          BNNSArithmeticSinh                  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 15,
          BNNSArithmeticCosh                  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 16,
          BNNSArithmeticTanh                  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 17,
          BNNSArithmeticAsinh                 __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 18,
          BNNSArithmeticAcosh                 __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 19,
          BNNSArithmeticAtanh                 __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 20,
          BNNSArithmeticPow                   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 21,
          BNNSArithmeticExp                   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 22,
          BNNSArithmeticExp2                  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 23,
          BNNSArithmeticLog                   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 24,
          BNNSArithmeticLog2                  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 25,
          BNNSArithmeticMultiplyNoNaN         __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 26,
          BNNSArithmeticDivideNoNaN           __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 27,
          BNNSArithmeticMultiplyAdd           __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 28,
          BNNSArithmeticMinimum               __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 29,
          BNNSArithmeticMaximum               __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 30,
          BNNSArithmeticSelect                __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 31,
          );

/*!

 @abstract BNNS Descriptor Data type

 @constant BNNSConstant
 A constant that does not have a gradient.
 the constant is broadcasted across batch samples if batch size > 1

 @constant BNNSSample
 A sample such as input or output.
 batch size is taken into account and it has a different gradient for each sample in the batch.

 @constant BNNSParameter
 A trainable parameter such as weights or bias.
 the parameter is broadcasted across batch samples if batch size > 1
 the parameter gradient is summed across the batch samples

 */
BNNS_ENUM(BNNSDescriptorType, uint32_t,

          BNNSConstant   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0,
          BNNSSample     __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 1,
          BNNSParameter  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 2
          );

/*!

 @abstract Optimizer layer function

 @constant BNNSOptimizerFunctionSGDMomentum
 Update parameters according to Stochastic Gradient Descent (SGD) with momentum algorithm.

 @constant BNNSOptimizerFunctionAdam
 Update parameters according to Adam algorithm.

 @constant BNNSOptimizerFunctionRMSProp
 Update parameters according to RMSProp algorithm.

 @constant BNNSOptimizerFunctionAdamW
 Update parameters according to AdamW algorithm.

 @constant BNNSOptimizerFunctionAdamAMSGrad
 Update parameters according to AMSGrad variant of the Adam algorithm.

 @constant BNNSOptimizerFunctionAdamWAMSGrad
 Update parameters according to AMSGrad variant of the AdamW algorithm.

 @constant BNNSOptimizerFunctionSGDMomentumWithClipping
 Update parameters according to Stochastic Gradient Descent (SGD) with momentum algorithm using clipped gradient.

 @constant BNNSOptimizerFunctionAdamWithClipping
 Update parameters according to Adam algorithm using clipped gradient.

 @constant BNNSOptimizerFunctionRMSPropWithClipping
 Update parameters according to RMSProp algorithm using clipped gradient.

 @constant BNNSOptimizerFunctionAdamWWithClipping
 Update parameters according to AdamW algorithm using clipped gradient.

 @constant BNNSOptimizerFunctionAdamAMSGradWithClipping
 Update parameters according to AMSGrad variant of the Adam algorithm using clipped gradient.

 @constant BNNSOptimizerFunctionAdamWAMSGradWithClipping
 Update parameters according to AMSGrad variant of the AdamW algorithm using clipped gradient.

 */
BNNS_ENUM(BNNSOptimizerFunction, uint32_t,

          BNNSOptimizerFunctionSGDMomentum  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 1,
          BNNSOptimizerFunctionAdam         __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 2,
          BNNSOptimizerFunctionRMSProp      __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 3,
          BNNSOptimizerFunctionAdamW        __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 4,
          BNNSOptimizerFunctionAdamAMSGrad  __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 5,
          BNNSOptimizerFunctionAdamWAMSGrad __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 6,

          BNNSOptimizerFunctionSGDMomentumWithClipping  __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 7,
          BNNSOptimizerFunctionAdamWithClipping         __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 8,
          BNNSOptimizerFunctionRMSPropWithClipping      __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 9,
          BNNSOptimizerFunctionAdamWWithClipping        __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 10,
          BNNSOptimizerFunctionAdamAMSGradWithClipping  __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 11,
          BNNSOptimizerFunctionAdamWAMSGradWithClipping __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 12,
          );

/*!

 @abstract Optimizer regularization function

 @constant BNNSOptimizerRegularizationNone
 No Regularization

 @constant BNNSOptimizerRegularizationL1
 L1 Regularization

 @constant BNNSOptimizerRegularizationL2
 L2 Regularization

 */
BNNS_ENUM(BNNSOptimizerRegularizationFunction, uint32_t,

          BNNSOptimizerRegularizationNone  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0,
          BNNSOptimizerRegularizationL1    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 1,
          BNNSOptimizerRegularizationL2    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 2,

          );

/*!

 @abstract Optimizer SGD with momentum variant

 @constant BNNSSGDMomentumVariant0
 V[t+1] = m*V[t] - g*lr
 Nesterov diabled: W[t+1] += V[t+1]
 Nesterov enabled: W[t+1] += V[t+1]+m*(V[t+1]-V[t])

 @constant BNNSSGDMomentumVariant1
 V[t+1] = m*V[t]+g
 Nesterov disabled: W[t+1] -= V[t+1]*lr
 Nesterov enabled: W[t+1] -= (m*V[t+1]+g)*lr

 @constant BNNSSGDMomentumVariant2
 Nesterov disabled:
 V[t+1] = m*V[t] + lr*g
 W[t+1] -= V[t+1]
 Nesterov enabled:
 V[t+1] = m*V[t]+g
 W[t+1] -= lr*(g+V[t+1]*m)
 */
BNNS_ENUM(BNNSOptimizerSGDMomentumVariant, uint32_t,

          BNNSSGDMomentumVariant0  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0,
          BNNSSGDMomentumVariant1  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 1,
          BNNSSGDMomentumVariant2  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 2,

          );

/*!

 @abstract Optimizer clipping function

 @constant BNNSOptimizerClippingNone
 No clipping

 @constant BNNSOptimizerClippingByValue
 Clipping gradient values to specified min and max

 @constant BNNSOptimizerClippingByNorm
 Clipping gradient values to a maximum L2-norm

 @constant BNNSOptimizerClippingByGlobalNorm
 Clipping gradient values by the ratio of the specified L2-norm and the global L2-norm

 */
BNNS_ENUM(BNNSOptimizerClippingFunction, uint32_t,

          BNNSOptimizerClippingNone         __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 0,
          BNNSOptimizerClippingByValue      __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 1,
          BNNSOptimizerClippingByNorm       __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 2,
          BNNSOptimizerClippingByGlobalNorm __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 3,
          );

/*!

 @abstract Type of norm

 @constant BNNSL2Norm L-2 norm

 */
BNNS_ENUM(BNNSNormType, uint32_t,

          BNNSL2Norm        __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 1,
);

/*!

 @abstract filter type

 @constant BNNSConvolution
 Convolution filter

 @constant BNNSFullyConnected
 Fully connected filter

 @constant BNNSBatchNorm
 Batchnorm filter

 @constant BNNSInstanceNorm
 Instance normalization filter

 @constant BNNSLayerNorm
 Layer normalization filter

 @constant BNNSGroupNorm
 Group normalization filter
 
 @constant BNNSTransposedConvolution
 Transposed Convolution filter
 
 @constant BNNSQuantization
 Quantization filter
 
 @constant BNNSArithmetic
 Arithmetic filter

 */
BNNS_ENUM(BNNSFilterType, uint32_t,

          BNNSConvolution            __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0,
          BNNSFullyConnected         __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 1,
          BNNSBatchNorm              __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 2,
          BNNSInstanceNorm           __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 3,
          BNNSLayerNorm              __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 4,
          BNNSGroupNorm              __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 5,
          BNNSTransposedConvolution  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 6,
          BNNSQuantization           __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 7,
          BNNSArithmetic             __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 8,
          );

/*!

 @abstract Reduction layer functions

 @constant BNNSReduceFunctionMax
 max(X)

 @constant BNNSReduceFunctionMin
 min(X)

 @constant BNNSReduceFunctionArgMax
 arg max(X)
 i.e. the index of the maximum value

 @constant BNNSReduceFunctionArgMin
 arg min(X)
 i.e. the index of the minimum value

 @constant BNNSReduceFunctionMean
 mean(X) = sum(X) / size(X)

 @constant BNNSReduceFunctionMeanNonZero
 Y = {X_i such as Weight_i != 0}
 MeanNonZero(X) = sum(Y) / size(Y)

 @constant BNNSReduceFunctionSum
 sum(X)

 @constant BNNSReduceFunctionSumSquare
 sum(X_i * X_i)

 @constant BNNSReduceFunctionSumLog
 SumLog(X) = sum log(X_i + epsilon)

 @constant BNNSReduceFunctionL1Norm
 L1Norm(X) = sum | X_i |
 i.e. sum of the absolute value of each element

 @constant BNNSReduceFunctionLogicalOr
  AnyOf(X) = X_0 || X_1 || ... X_n

 @constant BNNSReduceFunctionLogicalAnd
  AllOf(X) = X_0 && X_1 && ... X_n

 @constant BNNSReduceFunctionAny
  Alias of BNNSReduceFunctionLogicalOr

 @constant BNNSReduceFunctionAll
  Alias of BNNSReduceFunctionLogicalAnd
 */
BNNS_ENUM(BNNSReduceFunction, uint32_t,

          BNNSReduceFunctionMax          __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0,
          BNNSReduceFunctionMin          __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 1,
          BNNSReduceFunctionArgMax       __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 2,
          BNNSReduceFunctionArgMin       __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 3,
          BNNSReduceFunctionMean         __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 4,
          BNNSReduceFunctionMeanNonZero  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 5,
          BNNSReduceFunctionSum          __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 6,
          BNNSReduceFunctionSumSquare    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 7,
          BNNSReduceFunctionSumLog       __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 8,
          BNNSReduceFunctionL1Norm       __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 9,
          BNNSReduceFunctionLogicalOr    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 10,
          BNNSReduceFunctionLogicalAnd   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 11,

          // Friendly aliases
          BNNSReduceFunctionAny           __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = BNNSReduceFunctionLogicalOr,
          BNNSReduceFunctionAll           __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = BNNSReduceFunctionLogicalAnd,
          );

/*!
 @discussion LSTM layer flags
 @constant BNNSLayerFlagsLSTMBidirectional - enable bidirectional LSTM
 @constant BNNSLayerFlagsLSTMDefaultActivations - ignore forget_gate_layer.activation, input_gate_layer.activation, candidate_gate_layer.activation, output_gate_layer.activation and hidden_activation and use default activations (see BNNSLayerParametersLSTM)
 */
BNNS_ENUM(BNNSLayerFlags, uint32_t,

          BNNSLayerFlagsLSTMBidirectional       __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x0001,
          BNNSLayerFlagsLSTMDefaultActivations  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x0002,
          );

/*!

 @abstract Data layout and dimension

 @discussion The layout defines the nature of the data stored in a N-dimensional array
 Introduced in macOS 10.15, iOS 13, tvOS 13, watchOS 6.

 Note that we require that stride is always increasing, i.e. stride[i+1] >= stride[i].
 As such, the formulae given below for the location of an element uniquely determine what each stride value shuold be
 for a given memory layout.

 if stride[k] is 0, it's replaced by the default value corresponding to contiguous memory. If size[k] corresponds to stride[k], as
 is true for most (but not all) of the layouts below, these would be:
 stride[k] = 1 for k = 0
 stride[k] = size[k-1] * stride[k-1] for k > 0

 @constant BNNSDataLayoutVector
 One-dimensional vector.
 size[0] is the dimension of the vector. Value (i) is at index i * stride[0]

 @constant BNNSDataLayoutRowMajorMatrix
 Two-dimensional matrix. Value (row, col) is at index col * stride[0] + row * stride[1]
 size[0] is the number of columns.
 size[1] is the number of rows.

 @constant BNNSDataLayoutColumnMajorMatrix
 Two-dimensional matrix. Value (row, col) is at index row * stride[0] + col * stride[1]
 size[0] is the number of rows.
 size[1] is the number of columns.

 @constant BNNSDataLayoutImageCHW
 Three-dimensional image stack. Value (x,y,channel) is at index x * stride[0] + y * stride[1] + channel * stride[2]
 size[0] is the image width (pixels).
 size[1] is the image height (pixels).
 size[2] is the number of channels.

 @constant BNNSDataLayoutSNE
 Three dimensional tensor. Value (e, n, s) is at index e * stride[0] + n * stride[1] + s * stride[2].
 size[0] is E, the embedding dimension
 size[1] is N, the batch size
 size[2] is S, the sequence length

 @constant BNNSDataLayoutNSE
 Three dimensional tensor. Value (e, s, n) is at index e * stride[0] + s * stride[1] + n * stride[2].
 size[0] is E, the embedding dimension
 size[1] is S, the sequence length
 size[2] is N, the batch size

 @constant BNNSDataLayoutConvolutionWeightsOIHW
 Four-dimensional array of convolution weights.
 Value (kx,ky,InChannel,OutChannel) is at index kx * stride[0] + ky * stride[1] + InChannel * stride[2] + OutChannel * stride[3]
 size[0] is the convolution kernel width (pixels).
 size[1] is the convolution kernel height (pixels).
 size[2] is the number of input channels.
 size[3] is the number of output channels.

 @constant BNNSDataLayoutConvolutionWeightsOIHrWr
 Four-dimensional array of rotated convolution weights.
 Value (kx,ky,InChannel,OutChannel) is at index (kw - 1 - kx) * stride[0] + (kh - 1 - ky) * stride[1] +  InChannel * stride[2] + OutChannel * stride[3]
 size[0] is the convolution kernel width (pixels).
 size[1] is the convolution kernel height (pixels).
 size[2] is the number of input channels.
 size[3] is the number of output channels.
 kw is size[0] and kx is between 0 to kw-1.
 kh is size[1] and ky is between 0 to kh-1.

 @constant BNNSDataLayoutConvolutionWeightsIOHrWr
 Four-dimensional array of rotated convolution weights.
 Value (kx,ky,InChannel,OutChannel) is at index (kw - 1 - kx) * stride[0] + (kh - 1 - ky) * stride[1] + OutChannel * stride[2] + InChannel * stride[3]
 size[0] is the convolution kernel width (pixels).
 size[1] is the convolution kernel height (pixels).
 size[2] is the number of output channels.
 size[3] is the number of input channels.
 kw is size[0] and kx is between 0 to kw-1.
 kh is size[1] and ky is between 0 to kh-1.

 @constant BNNSDataLayoutConvolutionWeightsOIHW_Pack32
 Four-dimensional array of packed convolution weights with 32 output channel packing and 128 Byte array address alignment.

 A value position in the packed array can be determined in the following way:
 kernel_width is the kernel width
 kernel_height is the kernel height
 input_channels is the number of input channels
 output_channels is the number of output channels
 OutChannelGroup = OutChannel/32
 OutChannelPositionInGroup = OutChannel%32
 Value (kx,ky,InChannel,OutChannel) is at index OutChannelPositionInGroup + kw * 32 + ky * kernel_width * 32 + InChannel * kernel_height * kernel_width * 32 + OutChannelGroup * input_channels * kernel_height * kernel_width * 32

 The inner most output channel packing must alway have a size of 32 elements, even in the last OutChannelGroup where number of output channels may be less than 32.
 The minimal weight array size in bytes is: 32*kernel_width*kernel_height*input_channels*((output_channels+31)/32)*(weight element size in bytes)
 Failing to allocate the minimal weight array size may result in runtime error.
 size and stride structures must match BNNSDataLayoutConvolutionWeightsOIYX layout.
 memory layout must be contiguous, such that stride[0] is either 1 or 0.

 @constant BNNSDataLayout2DLastMajor
 Two-dimensional matrix. Value (i, j) is at index i * stride[0] + j * stride[1]
 size[0] is the size of the first dimension (i).
 size[1] is the size of the second dimension (j).
 (This is the BLAS/LAPACK column major equivalent - this layout matches BNNSDataLayoutColumnMajorMatrix)

 @constant BNNSDataLayout2DFirstMajor
 Two-dimensional matrix. Value (i, j) is at index j * stride[0] + i * stride[1]
 size[0] is the size of the first dimension (i).
 size[1] is the size of the second dimension (j).
 (This is the BLAS/LAPACK row major equivalent - note that BNNSDataLayoutRowMajorMatrix uses different ordering of size[])

 @constant BNNSDataLayout3DLastMajor
 Three-dimensional tensor. Value (i, j, k) is at index i * stride[0] + j * stride[1] + k * stride[2]
 size[0] is the size of the first dimension (i).
 size[1] is the size of the second dimension (j).
 size[2] is the size of the third dimension (k).

 @constant BNNSDataLayout3DFirstMajor
 Three-dimensional tensor. Value (i, j, k) is at index k * stride[0] + j * stride[1] + i * stride[2]
 size[0] is the size of the first dimension (i).
 size[1] is the size of the second dimension (j).
 size[2] is the size of the third dimension (k).

 @constant BNNSDataLayout4DLastMajor
 Four-dimensional tensor. Value (i, j, k, l) is at index i * stride[0] + j * stride[1] +
     k * stride[2] + l * stride[3]
 size[0] is the size of the first dimension (i).
 size[1] is the size of the second dimension (j).
 size[2] is the size of the third dimension (k).
 size[3] is the size of the fourth dimension (l).

 @constant BNNSDataLayout4DFirstMajor
 Four-dimensional tensor. Value (i, j, k, l) is at index l * stride[0] + k * stride[1] +
     j * stride[2] + i * stride[3]
 size[0] is the size of the first dimension (i).
 size[1] is the size of the second dimension (j).
 size[2] is the size of the third dimension (k).
 size[3] is the size of the fourth dimension (l).

 @constant BNNSDataLayout5DLastMajor
 Five-dimensional tensor. Value (i, j, k, l, m) is at index i * stride[0] + j * stride[1] +
     k * stride[2] + l * stride[3] + m * stride[4]
 size[0] is the size of the first dimension (i).
 size[1] is the size of the second dimension (j).
 size[2] is the size of the third dimension (k).
 size[3] is the size of the fourth dimension (l).
 size[4] is the size of the fifth dimension (m).

 @constant BNNSDataLayout5DFirstMajor
 Five-dimensional tensor. Value (i, j, k, l, m) is at index m * stride[0] + l * stride[1] +
     k * stride[2] + j * stride[3] + i * stride[4]
 size[0] is the size of the first dimension (i).
 size[1] is the size of the second dimension (j).
 size[2] is the size of the third dimension (k).
 size[3] is the size of the fourth dimension (l).
 size[4] is the size of the fifth dimension (m).

 @constant BNNSDataLayout6DLastMajor
 Six-dimensional tensor. Value (i, j, k, l, m, n) is at index i * stride[0] + j * stride[1] +
     k * stride[2] + l * stride[3] + m * stride[4] + n * stride[5]
 size[0] is the size of the first dimension (i).
 size[1] is the size of the second dimension (j).
 size[2] is the size of the third dimension (k).
 size[3] is the size of the fourth dimension (l).
 size[4] is the size of the fifth dimension (m).
 size[5] is the size of the sixth dimension (n).

 @constant BNNSDataLayout6DFirstMajor
 Six-dimensional tensor. Value (i, j, k, l, m, n) is at index n * stride[0] + m * stride[1] +
     l * stride[2] + k * stride[3] + j * stride[4] + i * stride[5]
 size[0] is the size of the first dimension (i).
 size[1] is the size of the second dimension (j).
 size[2] is the size of the third dimension (k).
 size[3] is the size of the fourth dimension (l).
 size[4] is the size of the fifth dimension (m).
 size[5] is the size of the sixth dimension (n).

 @constant BNNSDataLayout7DLastMajor
 Seven-dimensional tensor. Value (i, j, k, l, m, n, o) is at index i * stride[0] + j * stride[1] +
     k * stride[2] + l * stride[3] + m * stride[4] + n * stride[5] + o * stride[6]
 size[0] is the size of the first dimension (i).
 size[1] is the size of the second dimension (j).
 size[2] is the size of the third dimension (k).
 size[3] is the size of the fourth dimension (l).
 size[4] is the size of the fifth dimension (m).
 size[5] is the size of the sixth dimension (n).
 size[6] is the size of the seventh dimension (o).

 @constant BNNSDataLayout7DFirstMajor
 Seven-dimensional tensor. Value (i, j, k, l, m, n, o) is at index o * stride[0] + n * stride[1] +
     m * stride[2] + l * stride[3] + k * stride[4] + j * stride[5] + i * stride[6]
 size[0] is the size of the first dimension (i).
 size[1] is the size of the second dimension (j).
 size[2] is the size of the third dimension (k).
 size[3] is the size of the fourth dimension (l).
 size[4] is the size of the fifth dimension (m).
 size[5] is the size of the sixth dimension (n).
 size[6] is the size of the seventh dimension (o).

 @constant BNNSDataLayout8DLastMajor
 Eight-dimensional tensor. Value (i, j, k, l, m, n, o, p) is at index
     i * stride[0] + j * stride[1] + k * stride[2] + l * stride[3] +
     m * stride[4] + n * stride[5] + o * stride[6] + p * stride[7]
 size[0] is the size of the first   dimension (i).
 size[1] is the size of the second  dimension (j).
 size[2] is the size of the third   dimension (k).
 size[3] is the size of the fourth  dimension (l).
 size[4] is the size of the fifth   dimension (m).
 size[5] is the size of the sixth   dimension (n).
 size[6] is the size of the seventh dimension (o).
 size[7] is the size of the eighth  dimension (p).

 @constant BNNSDataLayout8DFirstMajor
 Eight-dimensional tensor. Value (i, j, k, l, m, n, o, p) is at index
     p * stride[0] + o * stride[1] + n * stride[2] + m * stride[3] +
     l * stride[4] + k * stride[5] + j * stride[6] + i * stride[7]
 size[0] is the size of the first   dimension (i).
 size[1] is the size of the second  dimension (j).
 size[2] is the size of the third   dimension (k).
 size[3] is the size of the fourth  dimension (l).
 size[4] is the size of the fifth   dimension (m).
 size[5] is the size of the sixth   dimension (n).
 size[6] is the size of the seventh dimension (o).
 size[7] is the size of the eighth  dimension (p).

 */
BNNS_ENUM(BNNSDataLayout, uint32_t,

  // 1-dimensional layouts (are identical and only included for ease of use and consistent numbering)
  BNNSDataLayoutVector                         __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x10000,
  BNNSDataLayout1DLastMajor                    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x18000,
  BNNSDataLayout1DFirstMajor                   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x18001,

  // 2-dimensional layouts
  BNNSDataLayoutRowMajorMatrix                 __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x20000,
  BNNSDataLayoutColumnMajorMatrix              __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x20001,
  BNNSDataLayout2DLastMajor                    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x28000,
  BNNSDataLayout2DFirstMajor                   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x28001,

  // 3-dimensional layouts
  BNNSDataLayoutImageCHW                       __API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) = 0x30000,
  BNNSDataLayoutSNE                            __API_AVAILABLE(macos(12.0),  ios(15.0), watchos(8.0), tvos(15.0)) = 0x30001,
  BNNSDataLayoutNSE                            __API_AVAILABLE(macos(12.0),  ios(15.0), watchos(8.0), tvos(15.0)) = 0x30002,
  BNNSDataLayout3DLastMajor                    __API_AVAILABLE(macos(11.0),  ios(14.0), watchos(7.0), tvos(14.0)) = 0x38000,
  BNNSDataLayout3DFirstMajor                   __API_AVAILABLE(macos(11.0),  ios(14.0), watchos(7.0), tvos(14.0)) = 0x38001,

  // 4-dimensional layouts
  BNNSDataLayoutConvolutionWeightsOIHW         __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x40000,
  BNNSDataLayoutConvolutionWeightsOIHrWr       __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x40001,
  BNNSDataLayoutConvolutionWeightsIOHrWr       __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x40002,
  BNNSDataLayoutConvolutionWeightsOIHW_Pack32  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x40010,
  BNNSDataLayout4DLastMajor                    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x48000,
  BNNSDataLayout4DFirstMajor                   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x48001,

  // 5-dimensional layouts
  BNNSDataLayout5DLastMajor                    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x58000,
  BNNSDataLayout5DFirstMajor                   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x58001,

  // 6-dimensional layouts
  BNNSDataLayout6DLastMajor                    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x68000,
  BNNSDataLayout6DFirstMajor                   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x68001,

  // 7-dimensional layouts
  BNNSDataLayout7DLastMajor                    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x78000,
  BNNSDataLayout7DFirstMajor                   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x78001,

  // 8-dimensional layouts
  BNNSDataLayout8DLastMajor                    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x88000,
  BNNSDataLayout8DFirstMajor                   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x88001,
);

/*! @abstract Interpolation methods for resize.
 *
 * @constant BNNSInterpolationMethodNearest - Use nearest neighbor interpolation, suitable for any number of interpolation dimensions.
 * @constant BNNSInterpolationMethodLinear - Use linear or bilinear interpolation depending on number of resized dimensions. Requires that we are interpolating in at most two dimensions.
 */
BNNS_ENUM(BNNSInterpolationMethod, uint32_t,

          BNNSInterpolationMethodNearest  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0,
          BNNSInterpolationMethodLinear   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 1,
          );

/*! @abstract padding modes for padding.
 *
 * @constant BNNSPaddingModeConstant    - padded area is filled with constant value specified by the user
 * @constant BNNSPaddingModeReflect       - padded area is filled up so that the padded area and the adjacent area with input data form an odd-symmetric pattern:  x x  A B C ->  C B A  B C
 * @constant BNNSPaddingModeSymmetric - padded area is filled up so that the padded area and the adjacent area with input data form an even-symmetric pattern: x x A B -> B A A B
*/
BNNS_ENUM(BNNSPaddingMode, uint32_t,
    BNNSPaddingModeConstant   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0,
    BNNSPaddingModeReflect    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 1,
    BNNSPaddingModeSymmetric  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 2,
);

/*!

@abstract Relational layer operation type

@constant BNNSRelationalOperatorEqual
Perform element-by-element comparison of A == B

@constant BNNSRelationalOperatorLess
Perform element-by-element comparison of A < B

@constant BNNSRelationalOperatorLessEqual
Perform element-by-element comparison of A <= B

@constant BNNSRelationalOperatorGreater
Perform element-by-element comparison of A > B

@constant BNNSRelationalOperatorGreaterEqual
Perform element-by-element comparison of A >= B

@constant BNNSRelationalOperatorNotEqual
Perform element-by-element comparison of A != B

@constant BNNSRelationalOperatorLogicalAND
Perform element-by-element A && B

@constant BNNSRelationalOperatorLogicalOR
Perform element-by-element A || B

@constant BNNSRelationalOperatorLogicalNOT
Perform element-by-element  !A

@constant BNNSRelationalOperatorLogicalNAND
Perform element-by-element !(A && B)

@constant BNNSRelationalOperatorLogicalNOR
Perform element-by-element !(A || B)

@constant BNNSRelationalOperatorLogicalXOR
Perform element-by-element A ^ B

*/
BNNS_ENUM(BNNSRelationalOperator, uint32_t,
    BNNSRelationalOperatorEqual         __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  0,
    BNNSRelationalOperatorLess          __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  1,
    BNNSRelationalOperatorLessEqual     __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  2,
    BNNSRelationalOperatorGreater       __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  3,
    BNNSRelationalOperatorGreaterEqual  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  4,
    BNNSRelationalOperatorNotEqual      __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  5,
    BNNSRelationalOperatorLogicalAND    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  6,
    BNNSRelationalOperatorLogicalOR     __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  7,
    BNNSRelationalOperatorLogicalNOT    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  8,
    BNNSRelationalOperatorLogicalNAND   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) =  9,
    BNNSRelationalOperatorLogicalNOR    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 10,
    BNNSRelationalOperatorLogicalXOR    __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 11,
);

/*! @abstract Pointer extraction specifiers
 *
 *  @discussion
 *  These enums are passed to BNNSGetPointer() to specify what pointer should be returned.
 *
 *  @constant BNNSPointerSpecifierAlpha - alpha parameter associated with layer (supported by: activation)
 *  @constant BNNSPointerSpecifierBeta - beta parameter associated with layer (supported by: activation)
 */
BNNS_ENUM(BNNSPointerSpecifier, uint32_t,

          BNNSPointerSpecifierAlpha  __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0,
          BNNSPointerSpecifierBeta   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 1
          );

/*! @abstract Flags to control behaviors on BNNSNDArrayDescriptors
 *
 *  @constant BNNSNDArrayFlagBackpropSet - During back propogation, the elements of this ndarray are overwritten by the jacobian.
 *            If the NDArray does not represent a backpropgation gradient calculated by the function, this variable is ignored (i.e. this will typically
 *            only be used for output variables with names ending _delta).
 *  @constant BNNSNDArrayFlagBackpropAccumulate - During back propogation, the value of the jacobian is added to the elements of this ndarray
 *            (i.e. if the value is input_delta on entry to the function and dL/dx is the jacobian, then on exit it will be input_delta + dL/dx).
 *            If the NDArray does not represent a backpropgation gradient calculated by the function, this variable is ignored (i.e. this will typically
 *            only be used for output variables with names ending _delta).
 */
BNNS_ENUM(BNNSNDArrayFlags, uint32_t,

          BNNSNDArrayFlagBackpropSet          __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0,
          BNNSNDArrayFlagBackpropAccumulate   __API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 1,
          );

/*! @abstract Flags to control behavior of Embedding layers
 *
 *  @constant BNNSEmbeddingFlagScaleGradientByFrequency - If true, gradients calculated during the backward pass are scaled
 *            based on the number of occurrence of the corresponding index in the input.
 */
BNNS_ENUM(BNNSEmbeddingFlags, uint32_t,

          BNNSEmbeddingFlagScaleGradientByFrequency     __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 1,
          );

/*!

 @abstract Quantizer function

 @constant BNNSQuantizerFunctionQuantize
 y = scale*x + bias

 @constant BNNSQuantizerFunctionDequantize
 y = (x-bias)/scale

 */
BNNS_ENUM(BNNSQuantizerFunction, uint32_t,
          BNNSQuantizerFunctionQuantize               __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 0,
          BNNSQuantizerFunctionDequantize             __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 1
          );


/*! @abstract Random number generation methods
 *
 *  @discussion
 *  This method should not be used for cryptographic applications.
 *
 *  @constant BNNSRandomGeneratorMethodAES_CTR
 *  Implementation based on the AES hash of a counter.
 */
BNNS_ENUM(BNNSRandomGeneratorMethod, uint32_t,
          BNNSRandomGeneratorMethodAES_CTR      __API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 0,
);

#if !__has_include( <Availability.h> )
#undef __API_AVAILABLE
#undef __API_DEPRECATED_WITH_REPLACEMENT
#undef __API_AVAILABLE
#endif

#undef BNNS_ENUM // remove local defintion of BNNS_ENUM

#endif /* __BNNS_CONSTANTS_HEADER__ */
