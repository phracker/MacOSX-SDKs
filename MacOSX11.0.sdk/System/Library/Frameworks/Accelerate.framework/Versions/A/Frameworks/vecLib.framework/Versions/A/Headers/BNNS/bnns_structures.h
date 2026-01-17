//
//  bnns_structures.h
//  BasicNeuralNetworkSubroutines
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#ifndef __BNNS_STRUCTURES_HEADER__
#define __BNNS_STRUCTURES_HEADER__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "bnns_constants.h"

#if __has_include( <Availability.h> )
# include <Availability.h>
#else
# define __API_DEPRECATED_WITH_REPLACEMENT(...)
# define __API_DEPRECATED(...)
#endif

#if __has_feature(assume_nonnull)
  _Pragma("clang assume_nonnull begin")
#else
# define _Null_unspecified
# define _Nullable
# define _Nonnull
#endif

#pragma mark - User-provided memory functions

/*!

@abstract Type for user-provided memory allocation function

@discussion Should conform to posix_memalign(), and must be compatible with the memory deallocation function.

@param memptr Pointer to a <tt>(void *)</tt> receiving the address of the allocated memory.
@param alignment Requested alignment, must be a power of 2, and at least <tt>sizeof(void *)</tt>.
@param size Number of bytes to allocate.

@return 0 on success, or an error value on failure.

*/
typedef int (*BNNSAlloc)(void * _Nullable * _Nullable memptr, size_t alignment, size_t size);

/*!

 @abstract Type for user-provided memory deallocation function

 @discussion Should conform to free(), and must be compatible with the memory allocation function.

 @param ptr Address of the block to release.

 */
typedef void (*BNNSFree)(void * _Null_unspecified ptr);

#pragma mark - Data formats

/*!

 @abstract Common activation function parameters

 @field function Activation function
 @field alpha Parameter to the activation function
 @field beta Parameter to the activation function

 @field iscale Scale for integer functions (macOS 10.13, iOS 11, tvOS 11, watchOS 4)
 @field ioffset Offset for integer functions (macOS 10.13, iOS 11, tvOS 11, watchOS 4)
 @field ishift Shift for integer functions (macOS 10.13, iOS 11, tvOS 11, watchOS 4)

 @field iscale_per_channel Scale per channel for integer functions (macOS 10.13, iOS 11, tvOS 11, watchOS 4)
 @field ioffset_per_channel Offset per channel for integer functions (macOS 10.13, iOS 11, tvOS 11, watchOS 4)
 @field ishift_per_channel Shift per channel for integer functions (macOS 10.13, iOS 11, tvOS 11, watchOS 4)

*/
typedef struct {

  BNNSActivationFunction function;
  float alpha;
  float beta;

  // The following fields are available in macOS 10.13, iOS 11, tvOS 11, watchOS 4

  int32_t iscale;
  int32_t ioffset;
  int32_t ishift;

  const int32_t * _Nullable iscale_per_channel;
  const int32_t * _Nullable ioffset_per_channel;
  const int32_t * _Nullable ishift_per_channel;

} BNNSActivation;

#define BNNS_MAX_TENSOR_DIMENSION 8

/*!

 @abstract Generic N-dimensional array

 @discussion This type  is used to represent an N-dimensional array of values (N=1,2,3,4).
 The nature and dimension of the data is determined by the layout field.
 Introduced in macOS 10.15, iOS 13, tvOS 13, watchOS 6.

 @field flags is used to control some behaviors of the NDArray
 @field layout defines the dimension (n) of the array, and how data is stored
 @field size is the number of values in each dimension; only the first n values are used
 @field stride is the increment (in values) between a value and the next in each dimension; only the first n values are used
        A stride value of 0 is interpreted to mean that values are contiguous in this axis (i.e. is treated as stride[i] = size[i-1]*stride[i-1],
        or stride[0] = 1 for the first dimension).

 @field data points to the data; can be NULL
 @field data_type defines the size and type of the values stored in data

 @field table_data points to the lookup table; used only when data_type is Indexed<N>
 @field table_data_type defines the size and type of the values stored in table_data; used only when data_type is Indexed<K>

 @field data_scale is used in the conversion of integer values to floating point; used only when data_type is Int<K> or UInt<K>
 @field data_bias is used in the conversion of integer values to floating point; used only when data_type is Int<K> or UInt<K>

 */
typedef struct {

  BNNSNDArrayFlags flags;
  BNNSDataLayout layout;

  size_t size[BNNS_MAX_TENSOR_DIMENSION];
  size_t stride[BNNS_MAX_TENSOR_DIMENSION];

  void * _Nullable data;
  BNNSDataType data_type;

  void * _Nullable table_data;
  BNNSDataType table_data_type;

  float data_scale;
  float data_bias;

} BNNSNDArrayDescriptor;

#pragma mark - Sub Layers Parameters

/*!
 @abstract LSTM Gate Layer Descriptor
 @discussion
 gate layer is a building block of LSTM layers
 example of float output
 in - 1D array of iw_desc.size[0] elements
 hidden - 1D array of hw_desc.size[0] elements
 cell - 1D array of cw_desc.size[0] elements
 out - 1D array of iw_desc.size[1] elements
 input_weights - 2D arrary of iw_desc.size[1] X iw_desc.size[0]  elements (iw_desc.data points to data)
 hidden_weights - 2D arrary of hw_desc.size[1] X hw_desc.size[0]  elements (hw_desc.data points to data)
 cell_weights - 2D arrary of cw_desc.size[1] X cw_desc.size[0]  elements (cw_desc.data points to data)
 for (size_t o = 0; o < iw_desc.size[1]; o++)
 {
  float res = bias[o]; // init with bias value
  for (size_t i = 0; i < iw_desc.size[0]; i++) // matrix vector multiply
   res += input[i] * input_weights[o][i];
  for (size_t i = 0; i < hw_desc.size[0]; i++) // matrix vector multiply
   res += hidden[i] * hidden_weights[o][i];
  for (size_t i = 0; i < cw_desc.size[0]; i++) // matrix vector multiply
   res += cell[i] * cell_weights[o][i];
  out[i] = activation.func(res); // apply activation function
 }

 - num_directions == 1 for unidirectional and 2 for bidirectional
 @field iw_desc input weights descriptor , weights are ordered as [num_layers][num_directions][hidden_size][input_size] (C style multi array notation)
        - iw_desc is duplicated for the case where num_layers > 1 && input_size != hidden_size
 @field hw_desc hidden weights descriptor , weights are ordered as [num_layers][num_directions][hidden_size][hidden_size] (C style multi array notation)
 @field cw_desc cell weights descriptor, weights are ordered as [num_layers][num_directions][hidden_size][hidden_size] (C style multi array notation)
 @field b_desc bias descriptor, bias is ordered as [num_layers][num_directions][hidden_size] (C style multi array notation)
 @field activation activation function
 */
typedef struct {
  BNNSNDArrayDescriptor iw_desc[2];
  BNNSNDArrayDescriptor hw_desc;
  BNNSNDArrayDescriptor cw_desc;
  BNNSNDArrayDescriptor b_desc;
  BNNSActivation activation;
} BNNSLSTMGateDescriptor;

/*!
 @abstract contains NDarrat descriptors for inputs and outputs of LSTM
 @field data_desc - input / output
 @field hidden_desc - hidden input / output
 @field cell_state_desc - cell state input / output
*/
typedef struct {
  BNNSNDArrayDescriptor data_desc;
  BNNSNDArrayDescriptor hidden_desc;
  BNNSNDArrayDescriptor cell_state_desc;
} BNNSLSTMDataDescriptor;

/*!
 @abstract Arithmetic struct that hold 1 input and an output descriptor
 @discussion
 @field in input descriptor
 @field in_type input descriptor type
 @field out output descriptor
 @field out_type output descriptor type

 */
typedef struct {
  BNNSNDArrayDescriptor in;
  BNNSDescriptorType in_type;
  BNNSNDArrayDescriptor out;
  BNNSDescriptorType out_type;
} BNNSArithmeticUnary;

/*!
 @abstract Arithmetic struct that holds 2 input descriptors and an output descriptor
 @discussion
 @field in1 input1 descriptor
 @field in1_type  input1 descriptor type
 @field in2 descriptor
 @field in2_type input2 descriptor type
 @field out output descriptor
 @field out_type output descriptor type

 */
typedef struct {
  BNNSNDArrayDescriptor in1;
  BNNSDescriptorType in1_type;
  BNNSNDArrayDescriptor in2;
  BNNSDescriptorType in2_type;
  BNNSNDArrayDescriptor out;
  BNNSDescriptorType out_type;
} BNNSArithmeticBinary;

/*! @abstract Multihead Attention Projection Parameters
 *
 *  @description
 *  Each of the Query, Key and Value inputs and the output get their own version of this struct.
 *  In the backpropagation call, the _delta output reuses this structure to hold partial differentials.
 *  See BNNSLayerParametersMultiheadAttention for a full description of the layer.
 *
 *  @seealso BNNSLayerParametersMultiheadAttention
 *
 *  @field target_desc Descriptor of the main target of the operation - either an input (i.e. query, key or value) or an output (output)
 *  @field weights The weights to be used by the initial projection (i.e. Wᴷ)
 *  @field bias The bias to be used by the initial projection (i.e. pᴷ). If no bias is required, set bias.data = NULL.
 */
typedef struct {
  BNNSNDArrayDescriptor target_desc;
  BNNSNDArrayDescriptor weights;
  BNNSNDArrayDescriptor bias;
} BNNSMHAProjectionParameters;

#pragma mark - Layer parameters

/*!

 @abstract Convolution parameters

 @discussion
 The convolution product Output = Weights &times; Input is defined as follows.  Pixel <tt>Output(o,x,y)</tt> of the output image stack receives:
 <br><tt>Output(o,x,y) = &sum;<sub>i,kx,ky</sub> Weight(o,i,kx,ky) * Input(i,x_stride * x + kx,y_stride * y + ky)</tt> with
 <tt>kx=0..k_width-1</tt>, <tt>ky=0..k_height-1</tt>,
 <tt>i=0..in_channels-1</tt>, <tt>o=0..out_channels-1</tt>,
 <tt>x=0..out_width-1</tt>, <tt>y=0..out_height-1</tt>.

 After the convolution is applied, the output is updated with bias and/or activation function as follows:
 <br><tt>Output(o,x,y) = ActivationFunction( Bias(o) + Output(o,x,y) )</tt>.

 Dimensions must satisfy:
 <br><tt>in_width + 2 * x_padding = x_stride * ( out_width - 1 ) + k_width</tt>, and <tt>in_height + 2 * y_padding = y_stride * ( out_height - 1 ) + k_height</tt>.
 <br>A common use case is <tt>x_stride=y_stride=1</tt>, and <tt>x_padding=y_padding=0</tt>. In that case, <tt>in_width = out_width + k_width - 1</tt>, and <tt>in_height = out_height + k_height - 1</tt>.

 Padding is a border of 0 values virtually added to the input image.

 Coefficient <tt>Weight(o,i,kx,ky)</tt> for output image <tt>o=0..out_channels-1</tt>, input image <tt>i=0..in_channels-1</tt>, and kernel point (kx,ky) is
 stored in <tt>weights[kx + k_width * (ky + k_height * (i + in_channels * o))]</tt>, where
 the convolution kernel dimensions are <tt>k_width,k_height</tt>.

 @field bias Layer bias, <tt>out_channels</tt> values, one for each output channel
 @field activation Layer activation function
 @field weights_layout option to choose a different layout in memory for the weights Matrix
 @field x_stride width increment in the input image
 @field y_stride height increment in the input image
 @field x_dilation_stride width increment in the input image while convolving with the kernel. ignored if x_dilation_stride<=1.
 @field y_dilation_stride height increment in the input image while convolving with the kernel. ignored if y_dilation_stride<=1.
 @field x_padding width padding, virtual 0 values added to the left and right of each channel of the input stack
 @field y_padding height padding, virtual 0 values added to the top and bottom of each channel of the input stack
 @field groups convolution group size, ignored if groups <= 1.
 - if groups > 1:
 - input, output, weights and bias will be used for a set of convolutions.
 - input and output channels must be divisible by groups.
 - weight layout must be BNNSDataLayoutConvolutionWeightsOIHW
 - weights descriptor size[2] = in_channels/groups and weights descriptor size[3]=output channels, such that for each consecutive convolutions i and i+1 in the group, convolution i weights and convolution i+1 weights are separated by total_weights_size/groups elements
 - when calling apply forward and backward functions, in_stride, out_stride and gradient strides should be the strides for the entire convolution group.
 - not supported in transposed convolution.
 @field pad left, right, up, down zero padding. used for asymmetric padding.
 - ignored if pad is all 0, or if x_padding>0 or y_padding>0.
 - left,up are adjucent to image position 0,0.
 */
typedef struct {

  BNNSNDArrayDescriptor i_desc;
  BNNSNDArrayDescriptor w_desc;
  BNNSNDArrayDescriptor o_desc;

  BNNSNDArrayDescriptor bias;
  BNNSActivation activation;

  size_t x_stride;
  size_t y_stride;
  size_t x_dilation_stride;
  size_t y_dilation_stride;
  size_t x_padding;
  size_t y_padding;
  size_t groups;
  size_t pad[4];
} BNNSLayerParametersConvolution;

/*!

 @abstract Fully connected layer parameters

 @discussion
 The output of a fully connected layer is the result of a matrix-vector product.
 The output vector is defined by <tt>Output(o) = &sum;<sub>i</sub> Weight(o,i) * Input(i)</tt> for <tt>i=0..in_size-1</tt>, <tt>o=0..out_size-1</tt>.

 Coefficient <tt>Weight(o,i)</tt> is stored in <tt>weights[i + o * in_size]</tt>.

 After the matrix product, the output is updated with bias and/or activation function as follows:
 <br><tt>Output(o) = ActivationFunction( Bias(o) + Output(o) )</tt>.

 @field i_desc descriptor of input vector
 @field w_desc weights Matrix coefficients, <tt>in_size * out_size</tt> values, with the layout described in the discussion
 @field o_desc descriptor of output vector

 @field bias Layer bias, <tt>out_size</tt> values, one for each output component
 @field activation Layer activation function

 */
typedef struct {

  BNNSNDArrayDescriptor i_desc;
  BNNSNDArrayDescriptor w_desc;
  BNNSNDArrayDescriptor o_desc;

  BNNSNDArrayDescriptor bias;
  BNNSActivation activation;

} BNNSLayerParametersFullyConnected;

/*!

 @abstract Pooling layer parameters

 @discussion
 The pooling is defined as follows.  Pixel <tt>Output(o,x,y)</tt> of the output image stack receives:
 <br><tt>Output(o,x,y) = PoolingFunction( Input(o,x_stride * x + kx * x_dilation_stride, y_stride * y + ky * y_dilation_stride) )</tt> with <tt>kx=0..k_width-1</tt>, <tt>ky=0..k_height-1</tt>,
 <tt>o=0..out_channels-1</tt>, <tt>x=0..out_width-1</tt>, <tt>y=0..out_height-1</tt>.

 After the pooling is applied, the output is updated with bias and/or activation function as follows:
 <br><tt>Output(o,x,y) = ActivationFunction( Bias(o) + Output(o,x,y) )</tt>.

 Dimensions must satisfy:
 <br><tt>in_width + 2 * x_padding >= x_stride * (out_width - 1) + 1</tt>,
 <br><tt>iin_height + 2 * y_padding >= p->y_stride * (o->height - 1) + 1</tt>.

 Padding is a border of 0 values virtually added to the input image.

 @field bias Layer bias, <tt>out_channels</tt> values
 @field activation Layer activation function

 @field pooling_function Selects the pooling function to apply to each sample

 @field x_stride width increment in the input image
 @field y_stride height increment in the input image
 @field x_dilation_stride width increment in the input image while convolving with the kernel
 @field y_dilation_stride height increment in the input image while convolving with the kernel
 @field x_padding width padding, virtual 0 values added to the left and right of each channel of the input stack
 @field y_padding height padding, virtual 0 values added to the top and bottom of each channel of the input stack
 @field pad left, right, up, down padding. used for asymmetric padding
 - ignored if pad is all 0, or if x_padding>0 or y_padding>0.
 - left,up are adjucent to image position 0,0.
 */
typedef struct {

  BNNSNDArrayDescriptor i_desc;
  BNNSNDArrayDescriptor o_desc;

  BNNSNDArrayDescriptor bias;
  BNNSActivation activation;

  BNNSPoolingFunction pooling_function;

  size_t k_width;
  size_t k_height;
  size_t x_stride;
  size_t y_stride;
  size_t x_dilation_stride;
  size_t y_dilation_stride;
  size_t x_padding;
  size_t y_padding;
  size_t pad[4];
} BNNSLayerParametersPooling;

/*!

 @abstract Activation/Conversion layer parameters

 @discussion
 The output of a activation layer is the result of applying activation operation on input data
 Also supports conversion of data types when activation.function ==  BNNSActivationFunctionIdentity
 and i_desc.data_type != o_desc.data_type

 @field i_desc descriptor of input
 @field o_desc descriptor of output
 @field activation Layer activation function
 @field axis_flags Flags indicating axes on which to conduct certain activation functions applications (e.g. softmax).
        A value of 0 is interpreted to mean the axis corresponding to i_desc.size[0].

 */
typedef struct {

  BNNSNDArrayDescriptor i_desc;
  BNNSNDArrayDescriptor o_desc;

  BNNSActivation activation;
  uint32_t axis_flags;

} BNNSLayerParametersActivation;

/*!
@abstract Loss layer parameters (basic version)
@discussion
If loss function is SoftmaxCrossEntropy, use BNNSLayerParametersLossSoftmaxCrossEntropy instead of this structure.
If loss function is SigmoidCrossEntropy, use BNNSLayerParametersLossSigmoidCrossEntropy instead of this structure.
If loss function is Huber, use BNNSLayerParametersLossHuber instead of this structure.
If loss function is Yolo, use BNNSLayerParametersLossYolo instead of this structure.

compute loss according to loss function and its parameters and reduce loss according to reduction

@field i_desc descriptor of input
@field o_desc descriptor of output
@field function Loss function
       If SoftmaxCrossEntropy, SigmoidCrossEntropy, Huber or Yolo loss is required, use the specific structures for those loss functions.
@field reduction loss reduction function to be used.
*/
typedef struct {
  BNNSLossFunction function;
  BNNSNDArrayDescriptor i_desc;
  BNNSNDArrayDescriptor o_desc;
  BNNSLossReductionFunction reduction;
} BNNSLayerParametersLossBase;

/*!
 @abstract Loss layer parameters (Softmax Cross Entropy version)
 @discussion
 compute loss according to loss function and its parameters and reduce loss according to reduction

 @field i_desc descriptor of input
 @field o_desc descriptor of output
 @field function Loss function
 @field reduction loss reduction function to be used.
 @field label_smooth smooth n labels. smoothing may not be supported for all loss functions.
        smoothed_labels[i] = labels[i]*(1-label_smooth) + label_smooth/n
 */
typedef struct {
    // Fields layout compatible with BNNSLayerParametersLoseBase
    BNNSLossFunction function;
    BNNSNDArrayDescriptor i_desc;
    BNNSNDArrayDescriptor o_desc;
    BNNSLossReductionFunction reduction;

    // Fields specific to Softmax Cross Entropy
    float label_smooth;
} BNNSLayerParametersLossSoftmaxCrossEntropy;

/*!
 @abstract Loss layer parameters (Sigmoid Cross Entropy version)
 @discussion
 compute loss according to loss function and its parameters and reduce loss according to reduction

 @field i_desc descriptor of input
 @field o_desc descriptor of output
 @field function Loss function
 @field reduction loss reduction function to be used.
 @field label_smooth smooth n labels. smoothing may not be supported for all loss functions.
        smoothed_labels[i] = labels[i]*(1-label_smooth) + label_smooth/2
 */
typedef struct {
    // Fields layout compatible with BNNSLayerParametersLoseBase
    BNNSLossFunction function;
    BNNSNDArrayDescriptor i_desc;
    BNNSNDArrayDescriptor o_desc;
    BNNSLossReductionFunction reduction;

    // Fields specific to Softmax Cross Entropy
    float label_smooth;
} BNNSLayerParametersLossSigmoidCrossEntropy;

/*!
 @abstract Loss layer parameters (Huber version)
 @discussion
 compute loss according to loss function and its parameters and reduce loss according to reduction

 @field i_desc descriptor of input
 @field o_desc descriptor of output
 @field function Loss function
 @field reduction loss reduction function to be used.
 @field huber_delta huber delta
 */
typedef struct {
    // Fields layout compatible with BNNSLayerParametersLoseBase
    BNNSLossFunction function;
    BNNSNDArrayDescriptor i_desc;
    BNNSNDArrayDescriptor o_desc;
    BNNSLossReductionFunction reduction;

    // Fields specific to Huber Loss
    float huber_delta;
} BNNSLayerParametersLossHuber;

/*!
 @abstract Loss layer parameters (YoLo version)
 @discussion
 compute loss according to loss function and its parameters and reduce loss according to reduction
 Yolo loss input and ground truth labels data layout expected to be (batch size)x(grid height)x(grid width)x(anchors)x(x,y,w,h,confidence,classes)

 @field i_desc descriptor of input
 @field o_desc descriptor of output
 @field function Loss function
 @field reduction loss reduction function to be used.
 - reduction must be BNNSLossReductionSum for loss function BNNSLossFunctionYolo
 @field huber_delta huber delta
 - ignored if loss function is not huber or yolo
 - for yolo loss, huber is used for w,h loss. yolo loss huber delta is assumed to be 1 if set to 0
 @field number_of_grid_columns number of columns in grid
 @field number_of_grid_rows number of rows in grid
 @field number_of_anchor_boxes number of anchor boxes in each cell
 @field anchor_box_size anchor box size, should be 5+number of classes
 @field rescore rescore confidence according to prediction vs. ground truth Intersection Over Union (IOU)
 @field scale_xy x,y loss scaling factor
 @field scale_wh w,h loss scaling factor
 @field scale_object confidence (object) loss scaling factor
 @field scale_no_object confidence (no object) scaling factor
 @field scale_classification classification scaling factor
 @field object_minimum_iou minimum iou for treating as object
 @field object_minimum_iou maximum iou for treating as no object
 @field anchors_data anchors data
 -must be consecutive float array: w0,h0,w1,h1, ... w_n,h_n, where n is number_of_anchor_boxes
 */
typedef struct {
    // Fields layout compatible with BNNSLayerParametersLoseBase
    BNNSLossFunction function;
    BNNSNDArrayDescriptor i_desc;
    BNNSNDArrayDescriptor o_desc;
    BNNSLossReductionFunction reduction;

    // Fields specific to YoLo Loss
    float huber_delta;
    size_t number_of_grid_columns;
    size_t number_of_grid_rows;
    size_t number_of_anchor_boxes;
    size_t anchor_box_size;
    bool rescore;
    float scale_xy;
    float scale_wh;
    float scale_object;
    float scale_no_object;
    float scale_classification;
    float object_minimum_iou;
    float no_object_maximum_iou;
    float* anchors_data;
} BNNSLayerParametersLossYolo;

/*!
 @abstract SGD with Momentum Optimizer Fields
 @discussion
 BNNSOptimizerSGDMomentumFields structure should be pointed to by OptimizerAlgFields when using an Optimizer filter with optimization function BNNSOptimizerFunctionSGDMomentum.
 The structure will not be cached internally and must be valid when calling the optimizer apply, therefore, values such as learning_rate can be modified between optimizer filter apply calls.

 The error function E = L + R(W) where L is the loss function and R(W) is the regularization term.
 The gradient g is dE/dW = dL/dW + dR(W)/dW
 dL/dW could be clipped using clip_gradients and scaled using gradient_scale
 dR(W)/dW could be scaled using regularization_scale

 The SGD with momentum optimizer will calculate the parameter W at time t+1 using accumulator V, gradient g, learning rate lr and momentum m according to sgd_momentum_variant.

 @field learning_rate learning rate
 @field momentum momentum. setting momentum to 0 will result in vanilla sgd, the accumulation term V will not be computed and associated scratch buffer can be NULL
 @field gradient_scale gradient scaling factor
 @field regularization_scale regularization scaling factor
 @field clip_gradients clip gradient between min and max values
 @field clip_gradients_min minimum gradient values. ignored if clip_gradients is false
 @field clip_gradients_max maximum gradient values. ignored if clip_gradients is false
 @field nesterov nesterov momentum update
 @field regularization_func regularization function
 @field sgd_momentum_variant sgd momentum variant

 */
typedef struct {
  float learning_rate;
  float momentum;
  float gradient_scale;
  float regularization_scale;
  bool clip_gradients;
  float clip_gradients_min;
  float clip_gradients_max;
  bool nesterov;
  BNNSOptimizerRegularizationFunction regularization_func;
  BNNSOptimizerSGDMomentumVariant sgd_momentum_variant;
} BNNSOptimizerSGDMomentumFields;

/*!
 @abstract Adam Fields
 @discussion
 BNNSOptimizerAdamFields structure should be pointed to by OptimizerAlgFields when using an Optimizer filter with optimization function BNNSOptimizerFunctionAdam.
 The structure will not be cached internally and must be valid when calling the optimizer apply, therefore, values such as learning_rate can be modified between optimizer filter apply calls.

 The error function E = L + R(W) where L is the loss function and R(W) is the regularization term.
 The gradient g is dE/dW = dL/dW + dR(W)/dW
 dL/dW could be clipped using clip_gradients and scaled using gradient_scale
 dR(W)/dW could be scaled using regularization_scale

 Implementation according to ADAM: A METHOD FOR STOCHASTIC OPTIMIZATION by Diederik P. Kingma, Jimmy Lei Ba (https://arxiv.org/pdf/1412.6980.pdf)

 @field learning_rate learning rate
 @field beta1 first moment constant. must be in [0,1)
 @field beta2 second moment constant. must be in [0,1)
 @field time_step time step. time step is maintained by user since optimizer is called for multiple layers with same time step. initial value must be 1, increase by 1 after optimizing all the layer paramers in the network.
 @field epsilon epsilon addition for the division in the parameter update stage, similar to epsilon hat in the end of section 2 of the paper.
 @field gradient_scale gradient scaling factor
 @field regularization_scale regularization scaling factor
 @field clip_gradients clip gradient between min and max values
 @field clip_gradients_min minimum gradient values. ignored if clip_gradients is false
 @field clip_gradients_max maximum gradient values. ignored if clip_gradients is false
 @field regularization_func regularization function
 */
typedef struct {
  float learning_rate;
  float beta1;
  float beta2;
  float time_step;
  float epsilon;
  float gradient_scale;
  float regularization_scale;
  bool clip_gradients;
  float clip_gradients_min;
  float clip_gradients_max;
  BNNSOptimizerRegularizationFunction regularization_func;
} BNNSOptimizerAdamFields;

/*!
 @abstract RMSProp Fields
 @discussion
 Implements the RMSProp method as described in [1] (centered version) and [2] (original, non-centred version).

 Weight w_i is updated using one of the formulae
 Uncentered:
    n_i = ɑ n_i + (1 - ɑ) (dL/dw_i)**2
    Δ_i = γ Δ_i - η dL/dw_i / ( sqrt( n_i ) + ε )
    w_i = w_i + Δ_i
 Centered:
    n_i = ɑ n_i + (1 - ɑ) (dL/dw_i)**2
    g_i = ɑ g_i + (1 - ɑ) (dL/dw_i)
    Δ_i = γ Δ_i - η dL/dw_i / ( sqrt( n_i - g_i**2 ) + ε )
    w_i = w_i + Δ_i
 The gradients dL/dw_i may optionally be clipped to a given range.

 [1] "Generating Sequences With Recurrent Neural Networks", A. Graves, https://arxiv.org/pdf/1308.0850v5.pdf
 [2] "Neural Networks for Machine Learning", Leacture 6a, G. Hinton, http://www.cs.toronto.edu/~tijmen/csc321/slides/lecture_slides_lec6.pdf

 @field learning_rate the scheduled learning rate, which will be adjusted by the algorithm (η above)
 @field alpha smoothing constant (ɑ above)
 @field epsilon term added to denominator (ε above)
 @field centered use the centered variant if true
 @field momentum momentum decay rate (γ above) (set to 0 to disable momentum)
 */
typedef struct {
  float learning_rate;
  float alpha;
  float epsilon;
  bool centered;
  float momentum;
  float gradient_scale;
  float regularization_scale;
  bool clip_gradients;
  float clip_gradients_min;
  float clip_gradients_max;
  BNNSOptimizerRegularizationFunction regularization_func;
} BNNSOptimizerRMSPropFields;

/*!
 @abstract Normalization layer parameters
 @discussion
 normalize inputs by using mean, variance, beta and gamma.
 beta and gamma are trainable parameters.
 input and output descriptor must have the same dimensions.
 Except for layer norm, beta, gamma, moving mean and moving variance width (descriptor size[0]) must be equal to number of input channels (descriptor size[2]).
 For layer norm, beta and gamma currently must have the same dimensions as the input (normalization_axis = 0).
 momentum is used to update the moving mean and moving variance during training and must be between 0 and 1
 epsilon is used in the computation of 1/sqrt(variance + epsilon)

 @field i_desc input descriptor
 @field o_desc output descriptor
 @field beta_desc beta parameter descriptor
 -ignored if pointer is NULL
 @field gamma_desc gamma parameter descriptor
 -ignored if pointer is NULL
 @field moving_mean pointer to the moving mean
 - Only applicable to batch norm and instance norm. Ignored in layer norm and group norm.
 If pointer is NULL, it means moving mean is not tracked in training or not used in inference.
 @field moving_variance pointer to the moving variance
 - Only applicable to batch norm and instance norm. Ignored in layer norm and group norm.
 If pointer is NULL, it means moving variance is not tracked in training or not used in inference.
 @field momentum momentum.
 -must be between 0 and 1.
 @field epsilon epsilon
 @field activation fused activation layer to follow the batch normalization layer.
 @field num_groups Divide the channels into this number of groups over which normalization statistics are computed.
 The number of channels in i_desc must be divisible by the number of groups. This is only used in group norm.
 @field normalization_axis The starting axis over which normalization applies. This is only used in layer norm.
 normalization_axis = 0 means normalize over CHW.
 normalization_axis = 1 means normalize over HW.
 normalization_axis = 2 means normalize over W.
 */
typedef struct {
  BNNSNDArrayDescriptor i_desc;
  BNNSNDArrayDescriptor o_desc;
  BNNSNDArrayDescriptor beta_desc;
  BNNSNDArrayDescriptor gamma_desc;
  BNNSNDArrayDescriptor moving_mean_desc;
  BNNSNDArrayDescriptor moving_variance_desc;
  float momentum;
  float epsilon;
  BNNSActivation activation;
  size_t num_groups;
  size_t normalization_axis;
} BNNSLayerParametersNormalization;

/*!
 @abstract Dropout Layer Fields

 @field i_desc - array descriptor for input
 @field o_desc - array descriptor for output
 @field rate dropout rate is the probability of an element or a group of elements is dropped out.  Range in [0, 1)
 @field seed the seed for the random number generator - ignored if 0
 @field control 8-bit bit mask indicating along which dimension the dropout decision is grouped(kept/dropped altogether) - for now only 4 LSBs have effects.
 */
typedef struct {
  BNNSNDArrayDescriptor  i_desc;
  BNNSNDArrayDescriptor  o_desc;
  float                  rate;
  uint32_t               seed;
  uint8_t                control;
} BNNSLayerParametersDropout;

/*!
 @abstract LSTM layer parameters
 @discussion
 LSTM layers parameters include:
 - sequence descriptor to support different batch size for the sequence
 - 3 input descriptors (input, hidden_input, cell_state_input)
 - 3 output descriptors (output, hidden_output, cell_state_output)
 - 4 compute gates (each gate has "extra input weights descriptor" (iw_desc) for the case where num of layers is > 1 and input size != hidden size
 - activation gate for the hidden output
 - dropout value
 - sequence length, number of layers, batch size and bidirectional corresponds to various size fields in the parameters (see details below)
  it is sufficient to set these values, "0" size in the NDArray descriptors will be treated as these values. non-zero size in the NDArray descriptors that don't match these values will result in BNNS Error
 - to enable peepholes, set weights pointer in the gates descriptor (for example, set input_gate_layer[0].cw_desc.data)
 - to enable bias, set bias pointer in the gates descriptor (for example, set forget_gate_layer[0].bias.data)
 - input_hidden_descriptor will be treated as array's filled with 0 when input_hidden_descriptor.data is null
 - input_cell_state_descriptor will be treated as array's filled with 0 when input_cell_state_descriptor.data is null
 example LSTM computation
 {
  // input 1D array
  const float x_0 = input_descriptor.data_desc;
  const float h_0 = input_hidden_descriptor.data;
  const float c_0 = input_cell_state_descriptor.data;

  // output 1D array
  float h_t = output_hidden_descriptor.data;
  float c_t = output_cell_state_descriptor.data;

  // temporary 1D array
  float f_t[output_cell_state_descriptor.size[0]];
  float i_t[output_cell_state_descriptor.size[0]];
  float g_t[output_cell_state_descriptor.size[0]];
  float o_t[output_hidden_descriptor.size[0]];

  f_t = forget_gate_result(x_0, h_0, c_0); // see description in BNNSGateDescriptor
  i_t = input_gate_result(x_0, h_0, c_0);; // see description in BNNSGateDescriptor
  g_t = candidate_gate_result(x_0, h_0, c_0);; // see description in BNNSGateDescriptor

  for (size_t o = 0; o < output_cell_state_descriptor.size[0]; o++)
   c_t[o] = f_t[o] * C_t1[o] + i_t[o] * g_t[o];

  o_t = output_gate_result(x_0, h_0, c_t);; // see description in BNNSGateDescriptor

  for (size_t o = 0; o < output_hidden_descriptor.size[0]; o++)
   h_t[o] = o_t[o] * hidden_activation.func(c_t[o]);
 }

 example of STACKED LSTM computation (multiple LSTMCell layers, num_layers > 1)
 {
  // input 1D array
  const float x_0[input_size]; //  = input_descriptor.data_desc;

  // input 2D arrays
  const float h_0[num_layers][hidden_size]; //  = input_hidden_descriptor.data;
  const float c_0[num_layers][hidden_size]; //  = input_cell_state_descriptor.data;

  // output 1D array
  float h_t = output_hidden_descriptor.data;
  float c_t = output_cell_state_descriptor.data;

  (h_t, c_t) = LASTMCell[0](x_0, h_0[0], c_0[0]); // compute first layer with x_0 as input
  for (size_t l = 1; l < num_layers; l++) (h_t, c_t) = LASTMCell[1](h_t, h_0[l], c_0[l]); // compute remaining layers with h_t as input
 }

 example of sequence LSTM computation (seq_len > 1)
 {
  // input 2D array
  const float x_0[seq_len][input_size]; //  = input_descriptor.data_desc;

  // input 1D array
  const float h_0 = input_hidden_descriptor.data;
  const float c_0 = input_cell_state_descriptor.data;

  // output 2D array
  float output[seq_len][hidden_size]; // = output_descriptor.data_desc

  // output 1D array
  float h_t = output_hidden_descriptor.data;
  float c_t = output_cell_state_descriptor.data;

  (h_t, c_t) = LASTMCell[0](x_0[0], h_0, c_0); // compute first input with h_0 and c_0 as inputs
  for (size_t s = 1; s < seq_len; s++)
  {
   output[s-1] = h_t; // store previous hidden output
   (h_t, c_t) = LASTMCell[0](x_0[s], h_t, c_t); // compute remaining inputs with h_t and c_t as inputs
  }
  output[seq_len-1] = h_t; // store last hidden output
 }

 example of sequence bidirectional LSTM computation (seq_len > 1, batch_size > 1,  is_bidirectional == true)
 {
  // input 2D array
  const float x_0[seq_len][batch_size][input_size]; //  = input_descriptor.data_desc;
  const float h_0[2][batch_size][hidden size]; // = input_hidden_descriptor.data;
  const float c_0[2][batch_size][hidden size]; // = input_cell_state_descriptor.data;

  // output 4D array
  float output[sequence length][batch_size][2][hidden size]; // = output_descriptor.data_desc

  // output 3D array
  float h_t[2][batch_size][hidden size]; // = output_hidden_descriptor.data;
  float c_t[2][batch_size][hidden size]; // = output_cell_state_descriptor.data;

  (h_t[0], c_t[0]) = LASTMCell[0](x_0[0], h_0[0], c_0[0]); // compute first input with h_0 and c_0 of the forward direction as inputs
  for (size_t s = 1; s < seq_len; s++)
  {
   output[s-1][batch_size][0] = h_t; // store previous hidden output for the first direction
   (h_t[0], c_t[0]) = LASTMCell[0](x_0[s], h_t[0], c_t[0]); // compute remaining inputs with h_t and c_t as inputs
  }
  output[seq_len-1][batch_size][0] = h_t; // store last hidden output of the forward direction

  if (is_bidirectional)
  {
   (h_t[1], c_t[1]) = LASTMCell[0](x_0[seq_len-1], h_0[1], c_0[1]); // compute last input with h_0 and c_0 of the backward direction as inputs
   for (size_t s = 1; s < seq_len; s++)
   {
    output[s-1][batch_size][1] = h_t; // store previous hidden output for the first direction
    (h_t[1], c_t[1]) = LASTMCell[0](x_0[seq_len-s], h_t[1], c_t[1]); // compute remaining inputs in reverse order with h_t and c_t as inputs
   }
   output[0][batch_size][1] = h_t; // store last hidden output of the backward direction
  }
 }

 @field input_size - number of elements in input
 @field hidden_size - number of elements in hidden and cell state
 @field num_layers - number of LSTM layers stacked together
 @field seq_len - size of the sequential input
 @field dropout - dropout ratio to apply between LSTM layers. doesn't apply to the last stacked layer, ignoerd when num_layers == 1
 @field lstm_flags - bit control flags (see BNNSLayerFlagsLSTM)
 @field batch_size - number of input & output samples
 @field sequence_descriptor - 1D array of sequence length elements (uint) to determine the batch size for each step
        (seq_len] > 1) and (sequence_descriptor.data == null) same batch_size will be used for all the sequence

 - num_directions == 1 for unidirectional and 2 for bidirectional
 @field input_descriptor - contain the descriptors of the input, hidden input and cell state input data
        input_descriptor.data_desc - the hierarchy of the data should be [seq_len][batch_size][input_size] (C style multi array notation, seq_len X 2D array of batch_size X 1D array of  input_size elements)
        input_descriptor.hidden_desc - the hierarchy of the data should be [num_layers][num_directions][batch_size][hidden_size] (C style multi array notation)
        input_descriptor.cell_state_desc - the hierarchy of the data should be [num_layers][num_directions][batch_size][hidden_size] (C style multi array notation)
 @field output_descriptor - contain the descriptors of the output, hidden output and cell state output data
        output_descriptor.data_desc - output of all the sequence hidden output. the hierarchy of the data should be [seq_len][batch_size][num_directions][hidden_size] (C style multi array notation)
        output_descriptor.hidden_desc - the last sequence hidden output. the hierarchy of the data should be [num_layers][num_directions][batch_size][hidden_size] (C style multi array notation)
        output_descriptor.cell_state_desc - the last sequence cell state output. the hierarchy of the data should be [num_layers][num_directions][batch_size][hidden_size] (C style multi array notation)
 @field forget_gate - forget descriptor (default activation is sigmoid), memory pointers ordered as [num_layers][num_directions][hidden_size][input_size/hidden_size] (C style multi array notation)
 @field input_gate - input descriptor (default activation is sigmoid), memory pointers ordered as  [num_layers][num_directions][hidden_size][input_size/hidden_size] (C style multi array notation)
 @field candidate_gate - candidate descriptor (default activation is tanh), memory pointers ordered as  [num_layers][num_directions][hidden_size][input_size/hidden_size] (C style multi array notation)
 @field output_gate - output descriptor (default activation is sigmoid), memory pointers ordered as [num_layers][num_directions][hidden_size][input_size/hidden_size] (C style multi array notation)
 @field hidden_activation - hidden activation layer to compute hidden output (default actviation tanh)
 */
typedef struct {
  size_t input_size;
  size_t hidden_size;
  size_t batch_size;
  size_t num_layers;
  size_t seq_len;
  float  dropout;
  uint32_t lstm_flags;
  BNNSNDArrayDescriptor sequence_descriptor;
  BNNSLSTMDataDescriptor input_descriptor;
  BNNSLSTMDataDescriptor output_descriptor;
  BNNSLSTMGateDescriptor input_gate;
  BNNSLSTMGateDescriptor forget_gate;
  BNNSLSTMGateDescriptor candidate_gate;
  BNNSLSTMGateDescriptor output_gate;
  BNNSActivation hidden_activation;
} BNNSLayerParametersLSTM;

/*!
 @abstract Arithmetic layer parameters
 @discussion
 Compute an arithmetic operation described by arithmetic_function.
 Descriptors are assumed to represent the same data if their descriptors data pointer are the same in which case the descriptor type and descriptor sizes, strides and data type must match.
 if input descriptors represent the same data, so should their gradient descriptors.
 For example, for a multiplication operation y=x*x, in1 and in2 are both pointing to x. in1_delta and in2_delta should both be pointing to the same gradient dx.

 @field arithmetic_function arithmetic function
 @field arithmetic_function_fields a pointer to an arithmetic function field structure as described in BNNSArithmeticFunction, such as BNNSArithmeticBinary for arithmetic function BNNSArithmeticAdd
 @field activation Layer activation function
 */
typedef struct {
  BNNSArithmeticFunction arithmetic_function;
  void* _Nonnull arithmetic_function_fields;
  BNNSActivation activation;
} BNNSLayerParametersArithmetic;

/*! @abstract Permute Layer Parameters
 *
 *  @description
 *  This layer copies one tensor to another whilst permuting the order of the axes.
 *  It is assumed input and output axes are numbered as 0,1, ...N-1, where N is the dimension of the data layout.
 *  the permutation array specifies the input axis source for each output axis, such that the K'th element in the permutation array specify the input axis source for the K'th axis in the output descriptor
 *  for example, a permutation array [2,1,0] applied on a BNNSDataLayoutImageCHW tensor will result in axis reverse such that output axis 0 is input axis 2, output axis 1 is input axis 1, and output axis 2 is input axis 0.

 *  notice:
 *  input and output data layout dimensions and data type must match
 *  output tensor sizes must be reordered according to the permutation specified in the permutation array
 *  permutation array values in indexes equal or beyond tenor dimension are being ignored
 *
 *  @field i_desc input descriptor
 *  @field o_desc output descriptor
 *  @field permutation permutation array
 */
typedef struct {
  BNNSNDArrayDescriptor i_desc;
  BNNSNDArrayDescriptor o_desc;
  size_t permutation[BNNS_MAX_TENSOR_DIMENSION];
} BNNSLayerParametersPermute;

/*! @abstract Tensor Contraction Layer Parameters
 *
 *  @discussion
 *  This layer performs an arbitrary tensor contraction.
 *  A tensor contraction is a summation of the elements of two tensors over one or more indices. We represent this
 *  in the operation argument as a string using Einstein's summation convention.
 *  For example, the string
 *      "a_ijp, b_ijq -> o_pq"
 *  would represent the operation
 *      o_pq = alpha * \sum_{i,j} a_ijp * b_ijq.
 *  Inputs may be either trained parameters or inputs.
 *  If the name preceding the underscore is 'w' the tensor is assumed to be a trained parameter (weights), otherwise it is
 *  assumed to be an input (the letter has no other effect and may be whatever the user wishes). At most one of the inputs
 *  may be a trained parameter.
 *  If the names of the left-hand side inputs match, the operation is assumed to be the contraction of a tensor with itself (to e.g.
 *  calculate the Gram matrix or a dot product).
 *  In the case of one of the inputs being a weight or the operation is contraction of a tensor with itself, the regular BNNSFilterApply
 *  and BNNSFilterApplyBatch functions may be used with the resulting layer.
 *  If the operation has two inputs, the BNNSFilterApplyTwoInput or BNNSFilterApplyTwoInputBatch functions must be used instead.
 *
 *  This layer may also be used to copy from one layer to another with a permutation of indices.
 *  For example, the string
 *      "a_ij -> c_ji"
 *  would represent the operation
 *      C = alpha * A^T.
 *
 *  Broadcasting is supported by using '*' as the final index, e.g. "a_ij*, b_ij -> c_*" would match additional indices of a and c. * only
 *  ever represents indices that occur on both sides of the operation, and never an index over which summation is performed. A *
 *  on one side will only match indices represent by a * on the other side, and never indices represented by a letter. The wildcard may
 *  occur at either the start or end of the index sequence, however it must occur in the same position (start or end) for all operands.
 *
 *  Note that where index letters are matched, the sizes of the corresponding dimensions for the tensors must also match, unless one
 *  tensor has size 1, in which case it will be repeated (broadcast) to match the corresponding dimension.
 *
 *  @field operation string as described above
 *  @field alpha Scaling to be applied to result
 *  @field beta Scaling to be applied to output before adding result. Must be 0.0 or 1.0.
 *  @field iA_desc Descriptor of the A input matrix
 *  @field iB_desc Descriptor of the B input matrix
 *  @field o_desc Descriptor of the output matrix
 */
typedef struct {
  const char *operation;
  float alpha;
  float beta;
  BNNSNDArrayDescriptor iA_desc;
  BNNSNDArrayDescriptor iB_desc;
  BNNSNDArrayDescriptor o_desc;
} BNNSLayerParametersTensorContraction;

/*! @abstract Gram Matrix Layer Parameters
 *
 *  @discussion
 *  The Gram matrix is calculated as:
 *    G[ f, c ] = alpha * sum_{i,j} x[ i, j, f ] * x[ i, j, c ]
 *
 *  Any additional dimensions are broadcast.
 *  This operation is equivalent to using the TensorContraction layer with operation string "x_*ijf, x_*ijc -> G_*fc".
 *
 *  @field alpha Scaling to be applied to the result
 *  @field i_desc The tensor x.
 *  @field o_desc The tensor G.
 */
typedef struct {
  float alpha;
  BNNSNDArrayDescriptor i_desc;
  BNNSNDArrayDescriptor o_desc;
} BNNSLayerParametersGram;

/*! @abstract Resize Layer Parameters
 *
 *  @discussion
 *  Resize from between differently sized tensor using the specified method.
 *
 *  Resize is only performed in dimensions where tensor sizes differ between input and output.
 *  Resized dimensions must all either upsample or downsample. A mixture of the two is not permitted.
 *
 *  @field method - The interpolation method to use
 *  @field i_desc - NDArray descriptor for the input tensor.
 *  @field o_desc - NDArray descriptor for the output tensor. Dimensions must be an integral
 *                  multiple of those used for i_desc.
 *  @field align_corners - If true, aligns the corners of the upscaling grid to the centre of
 *                         scaling dimensions rather than the edges.
 */
typedef struct {
  BNNSInterpolationMethod method;
  BNNSNDArrayDescriptor i_desc;
  BNNSNDArrayDescriptor o_desc;
  bool align_corners;
} BNNSLayerParametersResize;

/*! @abstract Broadcast Matrix Multiplication Layer Parameters
 *
 *  @description
 *  Given two tensors calculate the tensor that results from performing the matrix
 *  multiplication on the last two indices. Indices other than the last two are matched
 *  from the back. If one tensor has higher dimension than the other, the lower rank matrix
 *  is broadcast in the missing dimensions. If a tensor has size 1 in a dimensions, then it
 *  is broadcast to match the size in the matching dimension of the other tensor.
 *  The output tensor may optionally be scaled by a scalar α, and the last two indices of
 *  each tensor may be transposed.
 *
 *  For example, if we have A_ijk and B_pqrkt, then indices i and r are matched and must
 *  have the same size. The following multiplications are performed:
 *  for p = 0:size(B,0)-1
 *    for q = 0:size(B,1)-1
 *      for r = 0:size(B,2)-1
 *        // Matrix multiplication on last two indices
 *        for j = 0:size(A,1)-1
 *          for t = 0:size(B,4)-1
 *            c_pqrjt = β c_pqrjt  + α \sum_k a_rjk b_pqrkt
 *  where alpha is scalar scaling factor.
 *  If dimension i of A had size 1, then we would broadcast in that dimension, with the final
 *  line of pseudocode above becoming
 *            c_pqrjt = β c_pqrjt  + α \sum_k a_1jk b_pqrkt
 *
 *  This layer is equivalent to the tensor contraction layer with one of the operation strings:
 *      transA    transB    operation
 *        F           F        "a_*ik, b_*kj -> c_*ij"
 *        F           T        "a_*ik, b_*jk -> c_*ij"
 *        T           F        "a_*ki, b_*kj -> c_*ij"
 *        T           T        "a_*ki, b_*jk -> c_*ij"
 *
 *  @field alpha - scalar by which to scale the result
 *  @field beta - scalar by which to scale output before adding result. Must be 0.0 or 1.0.
 *  @field transA - if true, transposes the last two dimensions of A
 *  @field transB - if true, transposes the last two dimensions of B
 *  @field quadratic - if true, it is assumed that this operation the multiplication of the matrix with itself, and inputB is ignored.
 *         This will make no difference on inference (except that higher performance may be achieved if quadratic=true),
 *         however the backward gradient calculation will be incorrect (or rather the desired gradient will otherwise be the sum
 *         of inputA_delta and inputB_delta if quadratic=false).
 *  @field a_is_weights - if true, the matrix A is treated as weights (i.e. fixed across all matrices in a batch on inference,
 *         accumulates gradients across a batch during training)
 *  @field b_is_weights - if true, the matrix A is treated as weights (i.e. fixed across all matrices in a batch on inference,
 *         accumulates gradients across a batch during training)
 *  @field iA_desc - descriptor for tensor A
 *  @field iB_desc - descriptor for tensor B
 *  @field o_desc - descriptor for tensor C
 */
typedef struct {
  float alpha;
  float beta;
  bool transA;
  bool transB;
  bool quadratic;
  bool a_is_weights;
  bool b_is_weights;
  BNNSNDArrayDescriptor iA_desc;
  BNNSNDArrayDescriptor iB_desc;
  BNNSNDArrayDescriptor o_desc;
} BNNSLayerParametersBroadcastMatMul;

/*! @abstract Multihead Attention Parameters
 *
 *  @discussion
 *  This layer implements the multihead attention layer as described in the paper
 *  "Attention is All You Need" by A. Vaswani, N. Shazeer, N.Parmar, J. Uszkoreit, L. Jones, A. Gomez, L.Kaiser and I. Polosukhin.
 *
 *  Each input Q, K, V is projected num_head times and an attention calculation performed on each result, before the concatenated
 *  results are projected down to obtain an output. An optional dropout may be applied to the final result.
 *
 *  MultiheadAttention(Q, K, V) = concat(head_1, ... head_h) Wᴼ + epᴼᵀ                     where e is the vector of all 1s, and pᴼ is a bias vector
 *  head_i = Attention(QWᴾ_i + epᴾᵀ, KWᴷ_i + epᴷᵀ, VWⱽ_i + epⱽᵀ)                              where e is the vector of all 1s, and pᴾ, pᴷ and pⱽ are bias vectors
 *  Attention(Q, K, V) = dropout( softmax( mask( 1/sqrt(d_key) * Q [K; bᴷ; 0]ᵀ ) ) ) [V; bⱽ; 0]        where bᴷ and bⱽ are optional bias vectors and 0 row is added iff add_zero_attn is true.
 *  mask(R) = { r_ij + x_ij      if key_mask[ j ] is false, where X is the matrix described by the add_to_attention parameter
 *          { -inf                if key_mask[ j ] is true
 *
 *  The following are optional:
 *  - The use of projection bias vectors pᴾ, pᴷ, pⱽ, and pᴼ.
 *  - The use of attention bias vectors bᴷ and bⱽ.
 *  - The addition of the zero attention row.
 *  - The use of a key_mask.
 *  - The addition of X to the attention (this can be controlled on a per-apply call basis).
 *
 *  The following values are inferred from the input descriptors:
 *  num_heads - number of heads in the model, inferred from query.weights->size[2]
 *  target_length - target sequence length, inferred from query.target_desc->size[0]
 *  source_length - source sequence length, inferred from key.target_desc->size[0]
 *  d_model - dimension of model, inferred from query.target_desc->size[1]
 *  d_key - dimension of key space, inferred from key.weights->size[1]
 *  d_value - dimension of value space, inferred from output.target_desc->size[1]
 *
 *  Typical usage would be to set d_key = d_value = d_model / num_heads such that the total work
 *  involved is similar to that of a single headed attention layer of d_model dimension.
 *
 *  @field query describes the query-related input parameters and projection:
 *         .target_desc - a 2D tensor of shape target_length x d_model used as an input (Q above)
 *         .weights - a 3D tensor of shape d_model x d_key x num_heads giving a projection for each head from Q
 *                    to a d_key size space (Wᴾ above)
 *         .bias - a 2D tensor of shape d_key x num_heads added as a bias during the projection from Q (pᴾ above)
 *  @field key describes the key-related input parameters and projection:
 *         .target_desc - a 2D tensor of shape source_length x d_model used as an input (K above)
 *         .weights - a 3D tensor of shape d_model x d_key x num_heads giving a projection for each head from K
 *                    to a d_key size space (Wᴷ above)
 *         .bias - a 2D tensor of shape d_key x num_heads added as a bias during the projection from K (pᴷ above)
 *  @field value describes the value-related input parameters and projection:
 *         .target_desc - a 2D tensor of shape source_length x d_model used as an input (V above)
 *         .weights - a 3D tensor of shape d_model x d_value x num_heads giving a projection for each head from V
 *                    to a d_value size space (Wⱽ above)
 *         .bias - a 2D tensor of shape d_value x num_heads added as a bias during the projection from V (pⱽ above)
 *  @field add_zero_attn If true, a row of zeroes is added to the projected K and to V inputs to the Attention calculation
 *  @field key_attn_bias Optional, a 2D tensor of shape d_key x num_heads that is added as part of the attention calculation (bᴷ above)
 *         If not required, set key_attn_bias.data=NULL. If present, value_attn_bias must also be present.
 *  @field value_attn_bias Optional, a 2D tensor of shape d_value x num_heads that is added as part of the attention calculation (bⱽ above)
 *         If not required, set value_attn_bias.data=NULL. If present, key_attn_bias must also be present.
 *  @field output describes the output tensor and associated projection:
 *         .target_desc - a 2D tensor of shape target_length x d_model used for output of the result
 *         .weights - a 2D tensor of shape num_heads*d_value x d_model used to combine all heads into a single output (Wᴼ above)
 *         .bias - a 1D tensor of shape d_model added to the final result (pᴼ above)
 *  @field dropout the dropout probability (no dropout is performed if dropout is outside the range (0, 1)
 *  @field seed random seed used for dropout layer
 */
typedef struct {
  BNNSMHAProjectionParameters query;
  BNNSMHAProjectionParameters key;
  BNNSMHAProjectionParameters value;
  bool add_zero_attn;
  BNNSNDArrayDescriptor key_attn_bias;
  BNNSNDArrayDescriptor value_attn_bias;
  BNNSMHAProjectionParameters output;
  float dropout;
  uint32_t seed;
} BNNSLayerParametersMultiheadAttention;

/*!
 @discussion computing reduction function across selected dimensions
 specify the reduction axis by setting the o_desc.size[i] =1 (other dimensions must be similar to the input size)
 example:
 input [3][2][3], output [3][2][1] would be reduction on the width
 input [3][2][4], output [1][2][4] would be reduction on the channel
 input [3][2][4], output [1][2][1] would be reduction on the channel and width

 - support only fp16/fp32 input and output (for now)
 - reduction function will be computed in fp32
 - when w_desc.data is set reduction is weighted (for each dimension, w_desc.size[i] == i_desc.size[i])
 - for SumLog operation, epsilon is added for each log operation

 Sum reduction on channel example:
 input [3][2][4], output [1][2][4]
 for (size_t h = 0; h < 2; h++)
 {
  for (size_t w = 0; w < 4; w++)
  {
    float sum = 0.0f;
    for (size_t c = 0; c < 3; c++)
    {
      float w_val = 1.0f;
      if (weights.data) w_val = weights.data[c*2*4 + h*4 + w];
      sum += input.data[c*2*4 + h*4 + w] * w_val;
    }
    output.data[h*4 + w] = sum;
  }
 }

 Mean by Non Zero weights on width example
 input [3][2][4], output [3][2][1], weights[3][2][4]
 for (size_t c = 0; c < 3; c++)
 {
  for (size_t h = 0; h < 2; h++)
  {
    float sum = 0.0f;
    float count = 0.0f;
    for (size_t w = 0; w < 4; w++)
    {
      if ((weights.data) && (weights.data[c*2*4 + h*4 + w] != 0.0f)
      {
        w_val = weights.data[c*2*4 + h*4 + w];
        count += 1.0f;
        sum += input.data[c*2*4 + h*4 + w] * w_val;
      }
    }
    output.data[c*2*4 + h] = sum / count;
  }
 }

 @field i_desc - input descriptor (pointer, data type, dimensions, dimension stride)
 @field o_desc - output descriptor (pointer, data type, dimensions, dimension stride)
 @field w_desc - weights descriptor when needed (pointer, data type, dimensions, dimension stride)
 @field reduce_func - reduction function across chosen axis
 @field epsilon - value added to SumLog reduction
 */
typedef struct {
  BNNSNDArrayDescriptor i_desc;
  BNNSNDArrayDescriptor o_desc;
  BNNSNDArrayDescriptor w_desc;
  BNNSReduceFunction    reduce_func;
  float                 epsilon;
} BNNSLayerParametersReduction;

/*!
 @abstract Padding Layer Fields

 @field i_desc                tensor descriptor for input
 @field o_desc               tensor descriptor for output.  For each dimension of the tensor ‘dim', the output size should  equal to i_desc.size[dim] + padding[dim][0] + padding[dim][1].
 @field padding_size     number of padding elements to add before and after the original data.
                    padding[d][0] gives the number of elements before, and padding[d][1] the number of elements after the data in dimension d.
                    Elements of the array that do not correspond to dimensions included in the tensor layout are not accessed.
 @field padding_mode   padding mode
 @field padding_value    the value to fill the padding area if BNNSPaddingModeConstant is used.  Up to 4 bytes can be stored, and first 'size' bytes are used depending on the data type.
 */

typedef struct {
    BNNSNDArrayDescriptor   i_desc;
    BNNSNDArrayDescriptor   o_desc;
    size_t                  padding_size[BNNS_MAX_TENSOR_DIMENSION][2];
    BNNSPaddingMode         padding_mode;
    uint32_t                padding_value;
} BNNSLayerParametersPadding;

#pragma mark - Deprecated

/*!

 @abstract Image stack descriptor (DEPRECATED, Use BNNSNDArrayDescriptor)

 @discussion
 An image stack is a sequence of images with the same width and height. Each image in the sequence is called a channel.
 For example, a RGB image will be stored as three separate channels. A pixel has only one scalar value, stored using the type
 described by <tt>data_type</tt>.

 Pixel <tt>P(c,x,y)</tt> at position <tt>(x,y)</tt> in channel <tt>c</tt> is stored in
 <tt>data[x + row_stride * y + image_stride * c]</tt>, with
 <tt>x=0..width-1</tt>,
 <tt>y=0..height-1</tt>,
 <tt>c=0..channels-1</tt>. <tt>row_stride &geq; width</tt>, <tt>image_stride &geq; row_stride * height</tt>.

 Int<n> types are converted to floating point using float Y = DATA_SCALE * (float)X + DATA_BIAS, and back to integer using Int<n> X = convert_and_saturate(Y / DATA_SCALE - DATA_BIAS)

 @field width Image width
 @field height Image height
 @field channels Number of images in stack
 @field row_stride Increment (in values) between image rows
 @field image_stride Increment (in values) between image channels
 @field data_type Storage data type for image values. INDEXED data types are not allowed here.
 @field data_scale Conversion scale for image values, used for INT,UINT data types only
 @field data_bias Conversion bias for image values, used for INT,UINT data types only

 */
typedef struct {

  size_t width;
  size_t height;
  size_t channels;
  size_t row_stride;
  size_t image_stride;

  BNNSDataType data_type;
  float        data_scale;
  float        data_bias;

} BNNSImageStackDescriptor
__API_DEPRECATED("BNNS switched to new Layer Parameters data structures",macos(10.12, 11.0), ios(10.0, 14.0), watchos(3.0, 7.0), tvos(10.0, 14.0));

/*!

 @abstract Vector format descriptor (DEPRECATED, Use BNNSNDArrayDescriptor)

 @discussion
 Represents a vector of dimension <tt>size</tt>.
 Each vector element is a scalar value, stored using the type specified in <tt>data_type</tt>.

 Component <tt>V(i)</tt> at index <tt>i</tt> is stored in <tt>data[i]</tt>, with <tt>i=0..size-1</tt>.

 Int<n> types are converted to floating point using float Y = DATA_SCALE * (float)X + DATA_BIAS, and back to integer using Int<n> X = convert_and_saturate(Y / DATA_SCALE - DATA_BIAS)

 @field size Vector dimension
 @field data_type Storage data type for vector values. INDEXED data types are not allowed here.
 @field data_scale Conversion scale for vector values, used for INT,UINT data types only
 @field data_bias Conversion bias for vector values, used for INT,UINT data types only

 */
typedef struct {

  size_t size;

  BNNSDataType data_type;
  float        data_scale;
  float        data_bias;

} BNNSVectorDescriptor
__API_DEPRECATED("BNNS switched to new Layer Parameters data structures", macos(10.12, 11.0), ios(10.0, 14.0), watchos(3.0, 7.0), tvos(10.0, 14.0));

/*!

 @abstract Common layer parameters (DEPRECATED, Use BNNSNDArrayDescriptor)

 @discussion Int<n> types are converted to floating point using float Y = DATA_SCALE * (float)X + DATA_BIAS, and back to integer using Int<n> X = convert_and_saturate(Y / DATA_SCALE - DATA_BIAS)

 @field data Pointer to layer values (weights, bias), layout and size are specific to each layer
 @field data_type Storage data type for the values stored in <tt>data</tt>
 @field data_scale Conversion scale for values, used for INT data types only, ignored for INDEXED and FLOAT data types
 @field data_bias Conversion bias for values, used for INT data types only, ignored for INDEXED and FLOAT data types
 @field data_table Conversion table (256 values) for indexed floating point data, used for INDEXED data types only

 */
typedef struct {

  const void * _Nullable  data;
  BNNSDataType            data_type;
  float                   data_scale;
  float                   data_bias;
  const float * _Nullable data_table;

} BNNSLayerData
__API_DEPRECATED("BNNS switched to new Layer Parameters data structures", macos(10.12, 11.0), ios(10.0, 14.0), watchos(3.0, 7.0), tvos(10.0, 14.0));

/*!

 @abstract Convolution parameters (DEPRECATED, Use BNNSLayerParametersConvolution)

 @discussion
 The convolution product Output = Weights &times; Input is defined as follows.  Pixel <tt>Output(o,x,y)</tt> of the output image stack receives:
 <br><tt>Output(o,x,y) = &sum;<sub>i,kx,ky</sub> Weight(o,i,kx,ky) * Input(i,x_stride * x + kx,y_stride * y + ky)</tt> with
 <tt>kx=0..k_width-1</tt>, <tt>ky=0..k_height-1</tt>,
 <tt>i=0..in_channels-1</tt>, <tt>o=0..out_channels-1</tt>,
 <tt>x=0..out_width-1</tt>, <tt>y=0..out_height-1</tt>.

 After the convolution is applied, the output is updated with bias and/or activation function as follows:
 <br><tt>Output(o,x,y) = ActivationFunction( Bias(o) + Output(o,x,y) )</tt>.

 Dimensions must satisfy:
 <br><tt>in_width + 2 * x_padding = x_stride * ( out_width - 1 ) + k_width</tt>, and <tt>in_height + 2 * y_padding = y_stride * ( out_height - 1 ) + k_height</tt>.
 <br>A common use case is <tt>x_stride=y_stride=1</tt>, and <tt>x_padding=y_padding=0</tt>. In that case, <tt>in_width = out_width + k_width - 1</tt>, and <tt>in_height = out_height + k_height - 1</tt>.

 Padding is a border of 0 values virtually added to the input image.

 Coefficient <tt>Weight(o,i,kx,ky)</tt> for output image <tt>o=0..out_channels-1</tt>, input image <tt>i=0..in_channels-1</tt>, and kernel point (kx,ky) is
 stored in <tt>weights[kx + k_width * (ky + k_height * (i + in_channels * o))]</tt>, where
 the convolution kernel dimensions are <tt>k_width,k_height</tt>.

 @field x_stride X increment in the input image
 @field y_stride Y increment in the input image
 @field x_padding X padding, virtual 0 values added to the left and right of each channel of the input stack
 @field y_padding Y padding, virtual 0 values added to the top and bottom of each channel of the input stack
 @field k_width Width of the convolution kernel
 @field k_height Height of the convolution kernel
 @field in_channels Number of input channels
 @field out_channels Number of output channels
 @field weights Convolution weights, <tt>k_width * k_height * in_channels * out_channels</tt> values, with the layout described in the discussion
 @field bias Layer bias, <tt>out_channels</tt> values, one for each output channel
 @field activation Layer activation function

*/
typedef struct __API_DEPRECATED_WITH_REPLACEMENT("BNNSLayerParametersConvolution", macos(10.12, 11.0), ios(10.0, 14.0), watchos(3.0, 7.0), tvos(10.0, 14.0)) {

  size_t x_stride;
  size_t y_stride;
  size_t x_padding;
  size_t y_padding;
  size_t k_width;
  size_t k_height;
  size_t in_channels;
  size_t out_channels;

  BNNSLayerData weights;
  BNNSLayerData bias;
  BNNSActivation activation;

} BNNSConvolutionLayerParameters
__API_DEPRECATED_WITH_REPLACEMENT("BNNSLayerParametersConvolution", macos(10.12, 11.0), ios(10.0, 14.0), watchos(3.0, 7.0), tvos(10.0, 14.0));

/*!

 @abstract Fully connected layer parameters (DEPRECATED, Use BNNSLayerParametersFullyConnected)

 @discussion
 The output of a fully connected layer is the result of a matrix-vector product.
 The output vector is defined by <tt>Output(o) = &sum;<sub>i</sub> Weight(o,i) * Input(i)</tt> for <tt>i=0..in_size-1</tt>, <tt>o=0..out_size-1</tt>.

 Coefficient <tt>Weight(o,i)</tt> is stored in <tt>weights[i + o * in_size]</tt>.

 After the matrix product, the output is updated with bias and/or activation function as follows:
 <br><tt>Output(o) = ActivationFunction( Bias(o) + Output(o) )</tt>.

 @field in_size Size of input vector
 @field out_size Size of output vector
 @field weights Matrix coefficients, <tt>in_size * out_size</tt> values, with the layout described in the discussion
 @field bias Layer bias, <tt>out_size</tt> values, one for each output component
 @field activation Layer activation function

*/
typedef struct __API_DEPRECATED_WITH_REPLACEMENT("BNNSLayerParametersFullyConnected", macos(10.12, 11.0), ios(10.0, 14.0), watchos(3.0, 7.0), tvos(10.0, 14.0)) {
  size_t in_size;
  size_t out_size;

  BNNSLayerData weights;
  BNNSLayerData bias;
  BNNSActivation activation;

} BNNSFullyConnectedLayerParameters
__API_DEPRECATED_WITH_REPLACEMENT("BNNSLayerParametersFullyConnected", macos(10.12, 11.0), ios(10.0, 14.0), watchos(3.0, 7.0), tvos(10.0, 14.0));

/*!
 @abstract Pooling layer parameters (DEPRECATED, Use BNNSLayerParametersPooling)

 @discussion
 The pooling is defined as follows.  Pixel <tt>Output(o,x,y)</tt> of the output image stack receives:
 <br><tt>Output(o,x,y) = PoolingFunction( Input(o,x_stride * x + kx,y_stride * y + ky) )</tt> with <tt>kx=0..k_width-1</tt>, <tt>ky=0..k_height-1</tt>,
 <tt>o=0..out_channels-1</tt>, <tt>x=0..out_width-1</tt>, <tt>y=0..out_height-1</tt>.

 After the pooling is applied, the output is updated with bias and/or activation function as follows:
 <br><tt>Output(o,x,y) = ActivationFunction( Bias(o) + Output(o,x,y) )</tt>.

 Dimensions must satisfy:
 <br><tt>in_width + 2 * x_padding >= x_stride * (out_width - 1) + 1</tt>,
 <br><tt>iin_height + 2 * y_padding >= p->y_stride * (o->height - 1) + 1</tt>.

 Padding is a border of 0 values virtually added to the input image.

 @field x_stride X increment in the input image
 @field y_stride Y increment in the input image
 @field x_padding X padding, virtual 0 values added to the left and right of each channel of the input stack
 @field y_padding Y padding, virtual 0 values added to the top and bottom of each channel of the input stack
 @field k_width Width of the pooling kernel
 @field k_height Height of the pooling kernel
 @field in_channels Number of input channels
 @field out_channels Number of output channels
 @field pooling_function Selects the pooling function to apply to each sample
 @field bias Layer bias, <tt>out_channels</tt> values
 @field activation Layer activation function
 */

typedef struct __API_DEPRECATED_WITH_REPLACEMENT("BNNSLayerParametersPooling", macos(10.12, 11.0), ios(10.0, 14.0), watchos(3.0, 7.0), tvos(10.0, 14.0)) {
  size_t x_stride;
  size_t y_stride;
  size_t x_padding;
  size_t y_padding;
  size_t k_width;
  size_t k_height;
  size_t in_channels;
  size_t out_channels;

  BNNSPoolingFunction pooling_function;
  BNNSLayerData bias;
  BNNSActivation activation;

} BNNSPoolingLayerParameters
__API_DEPRECATED_WITH_REPLACEMENT("BNNSLayerParametersPooling", macos(10.12, 11.0), ios(10.0, 14.0), watchos(3.0, 7.0), tvos(10.0, 14.0));

#pragma mark - Filter parameters

/*!

 @abstract Common filter parameters

 @field flags
 A logical OR of zero or more values from BNNSFlags.

 @field n_threads
 If 0, use the best number of threads for the current machine.
 Otherwise, specifies the number of worker threads to execute.

 @field alloc_memory
 If not NULL, will be called to allocate memory. Otherwise, posix_memalign() will be called.
 Must be compatible with the free_memory function.

 @field free_memory
 If not NULL, will be called to deallocate memory. Otherwise, free() will be called.
 Must be compatible with the alloc_memory function.

 */
typedef struct {

  uint32_t flags;
  size_t n_threads;
  BNNSAlloc _Nullable alloc_memory;
  BNNSFree _Nullable free_memory;

} BNNSFilterParameters;

#if !__has_include( <Availability.h> )
# undef __API_DEPRECATED_WITH_REPLACEMENT
# undef __API_DEPRECATED
#endif

#if __has_feature(assume_nonnull)
  _Pragma("clang assume_nonnull end")
#else
# undef _Nullable
# undef _Null_unspecified
# undef _Nonnull
#endif

#endif /* __BNNS_STRUCTURES_HEADER__ */
