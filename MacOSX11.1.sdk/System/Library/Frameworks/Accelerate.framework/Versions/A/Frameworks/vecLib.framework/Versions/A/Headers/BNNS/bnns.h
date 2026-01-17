// Basic Neural Network Subroutines (BNNS)

#ifndef __BNNS_HEADER__
#define __BNNS_HEADER__

#include "bnns_constants.h"
#include "bnns_structures.h"

#if __has_include( <Availability.h> )
#include <Availability.h>
#else
#define __API_AVAILABLE(...)
#define __API_DEPRECATED_WITH_REPLACEMENT(...)
#endif

#if __has_feature(assume_nonnull)
_Pragma("clang assume_nonnull begin")
#else
#define _Null_unspecified
#define _Nullable
#define _Nonnull
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*

 Logging

 When a parameter is invalid or an internal error occurs, an error message will be logged.
 Some combinations of parameters may not be supported. In that case, an info message will be logged.

 */

#pragma mark - Filter creation

/*!

 @abstract Filter object

 */
typedef void * _Nullable BNNSFilter;

/*!

 @abstract Create a convolution layer filter

 @discussion
 Creates a filter applying the convolution described in <tt>layer_params</tt>.
 Some combinations of the parameters may not be supported, in which case the call will fail.

 @param layer_params Layer parameters and input, weights, output, bias and activation descriptors
 @param filter_params Filter runtime parameters, may be NULL for default parameters

 @return A new non-NULL filter on success, and NULL on failure.

 */
BNNSFilter BNNSFilterCreateLayerConvolution(const BNNSLayerParametersConvolution * layer_params,
                                            const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Create a transposed convolution layer filter (also known as deconvolution)

 @discussion
 Creates a filter applying the transposed convolution described in <tt>layer_params</tt>.
 Some combinations of the parameters may not be supported, in which case the call will fail.
 Currently only BNNSDataTypeFloat32 data type is supported.
 @param layer_params Layer parameters and input, weights, output, bias and activation descriptors
 @param filter_params Filter runtime parameters, may be NULL for default parameters

 @return A new non-NULL filter on success, and NULL on failure.

 */
BNNSFilter BNNSFilterCreateLayerTransposedConvolution(const BNNSLayerParametersConvolution * layer_params,
                                                      const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Create a fully connected layer filter

 @discussion
 Creates a filter applying the fully connected layer described in <tt>layer_params</tt>.
 Some combinations of the parameters may not be supported, in which case the call will fail.

 @param layer_params  input, weights, output, bias and activation descriptors
 @param filter_params Filter runtime parameters, may be NULL for default parameters

 @return A new non-NULL filter on success, and NULL on failure.

 */
BNNSFilter BNNSFilterCreateLayerFullyConnected(const BNNSLayerParametersFullyConnected * layer_params,
                                               const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Create a pooling layer filter

 @discussion
 Creates a filter applying the pooling layer described in <tt>layer_params</tt>
 Some combinations of the parameters may not be supported, in which case the call will fail.

 @param layer_params Layer parameters and input, weights, output, bias and activation descriptors
 @param filter_params Filter runtime parameters, may be NULL for default parameters

 @return A new non-NULL filter on success, and NULL on failure.

 */
BNNSFilter BNNSFilterCreateLayerPooling(const BNNSLayerParametersPooling * layer_params,
                                        const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Create a Activation/Conversion layer filter

 @discussion
 Creates a filter applying the given activation function or conversions.
 Input and output must have the same number of elements.

 @param layer_params  input, output and activation descriptors
 @param filter_params Filter runtime parameters, may be NULL for default parameters

 @return A new non-NULL filter on success, and NULL on failure.

 */
BNNSFilter BNNSFilterCreateLayerActivation(const BNNSLayerParametersActivation * layer_params,
                                           const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Create a Loss layer filter

 @discussion
 Creates a filter applying loss function and loss reduction.

 @param layer_params  input, output and loss description
 @param filter_params Filter runtime parameters, may be NULL for default parameters

 @return A new non-NULL filter on success, and NULL on failure.

 */
BNNSFilter BNNSFilterCreateLayerLoss(const void * _Nonnull layer_params,
                                     const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Create a Normalization layer filter

 @discussion
 Creates a normalization filter that normalize inputs based on mean, variance and trainable parameters beta and gamma.

 @param normType type of normalization, currently supporting batch, instance, layer and group norm.
 @param layer_params  normalization layer parameters pointer.
 @param filter_params Filter runtime parameters, may be NULL for default parameters.

 @return A new non-NULL filter on success, and NULL on failure.

 */
BNNSFilter BNNSFilterCreateLayerNormalization(BNNSFilterType normType,
                                              const BNNSLayerParametersNormalization * layer_params,
                                              const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Create an Arithmetic layer filter

 @discussion
 Creates an Arithmetic filter such as add, subtract, multiply.

 @param layer_params  Arithmetic layer parameters pointer.
 @param filter_params Filter runtime parameters, may be NULL for default parameters.

 @return A new non-NULL filter on success, and NULL on failure.

 */
BNNSFilter BNNSFilterCreateLayerArithmetic(const BNNSLayerParametersArithmetic * layer_params,
                                           const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Create a Permute layer filter

 @discussion
 Creates a permute layer filter that copies one tensor to another whilst permuting the order of the axes

 @param layer_params  Permute layer parameters pointer.
 @param filter_params Filter runtime parameters, may be NULL for default parameters.

 @return A new non-NULL filter on success, and NULL on failure.

 */
BNNSFilter BNNSFilterCreateLayerPermute(const BNNSLayerParametersPermute * layer_params,
                                        const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*
 @abstract Create a dropout filter

 @discussion
 The function will:
     validate correctness of the parameters
     create a new dropout filter

 @param layer_params dropout layer parameters
 @param filter_params filter parameters
 @return A new non-NULL filter on success, and NULL on failure.

 */
BNNSFilter BNNSFilterCreateLayerDropout(const BNNSLayerParametersDropout * layer_params,
                                        const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!
 @abstract Create a padding filter

@discussion
The function will:
   validate correctness of the filter parameters
   create a new padding filter

@param layer_params padding layer parameters
@param filter_params filter parameters
@return A new non-NULL filter on success, and NULL on failure.

*/

BNNSFilter _Nullable BNNSFilterCreateLayerPadding(const BNNSLayerParametersPadding * layer_params,
                                        const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*! @abstract Create a layer representing a broadcast matrix multiplication
 *
 *  @discussion See BNNSLayerParametersBroadcastMatMul for a full description of this layer.
 *
 *  @seealso BNNSLayerParametersBroadcastMatMul
 *
 *  @param layer_params layer description
 *  @param filter_params Filter runtime parameters, may be NULL for default parameters
 *  @return A new non-NULL filter on success, and NULL on failure.
 */
BNNSFilter BNNSFilterCreateLayerBroadcastMatMul(const BNNSLayerParametersBroadcastMatMul *layer_params,
                                                const BNNSFilterParameters  * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*! @abstract Creates a layer representing an arbitrary tensor contraction
 *
 *  @discussion
 *  For a full discussion of this layer, see BNNSLayerParametersTensorContraction.
 *
 *  @seealso BNNSLayerParametersTensorContraction
 *
 *  @param layer_params layer description
 *  @param filter_params Filter runtime parameters, may be NULL for default parameters
 *  @return A new non-NULL filter on success, and NULL on failure.
 */
BNNSFilter BNNSFilterCreateLayerTensorContraction(const BNNSLayerParametersTensorContraction *layer_params,
                                                  const BNNSFilterParameters  * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*! @abstract Create a layer representing a Gram matrix calculation
 *
 *  @discussion
 *  Performs the Gram matrix calculation:
 *    y[ f, c ] = alpha * sum_{i,j} x[ i, j, f ] * x[ i, j, c ]
 *
 *  @seealso BNNSLayerParametersGram
 *
 *  @param layer_params layer description
 *  @param filter_params Filter runtime parameters, may be NULL for default parameters
 *  @return A new non-NULL filter on success, and NULL on failure.
 */
BNNSFilter BNNSFilterCreateLayerGram(const BNNSLayerParametersGram *layer_params,
                                     const BNNSFilterParameters  * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*! @abstract Create a layer representing a resizing in one or more dimensions
 *
 *  @discussion See BNNSLayerParametersResize for a full description of this layer.
 *
 *  @seealso BNNSLayerParametersResize
 *
 *  @param layer_params layer description
 *  @param filter_params Filter runtime parameters, may be NULL for default parameters
 *  @return A new non-NULL filter on success, and NULL on failure.
*/
BNNSFilter BNNSFilterCreateLayerResize(const BNNSLayerParametersResize *layer_params,
                                       const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*! @abstract Create a multiheaded attention layer
 *
 *  @discussion See BNNSLayerParametersMultiheadAttention for a full description of this layer.
 *
 *  @seealso BNNSLayerParametersMultiheadAttention
 *
 *  @param layer_params layer description
 *  @param filter_params Filter runtime parameters, may be NULL for default parameters
 *  @return A new non-NULL filter on success, and NULL on failure.
 */
BNNSFilter BNNSFilterCreateLayerMultiheadAttention(const BNNSLayerParametersMultiheadAttention * layer_params,
                                                   const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*! @abstract Create a reduction layer
 *
 *  @discussion See BNNSLayerParametersReduction for a full description of this layer.
 *
 *  @seealso BNNSLayerParametersReduction
 *
 *  @param layer_params layer description
 *  @param filter_params Filter runtime parameters, may be NULL for default parameters
 *  @return A new non-NULL filter on success, and NULL on failure.
 */
BNNSFilter BNNSFilterCreateLayerReduction(const BNNSLayerParametersReduction * layer_params,
                                          const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

  @abstract Create a fused filter

  @discussion
  Create an N layer fused filter that process input in the following way: input -> filter0 -> filter1 -> ... -> filter N-1 -> output
  first N-1 filters must have activation function BNNSActivationFunctionIdentity
  last filter may have a different activation function. gradient computation restrictions on last activation function are the same as in BNNSFilterApplyBackwardBatch.

  For K between 0 and N-2, the K filter output descriptor and the K+1 filter input descriptor  must have the same sizes, strides and data type.

  Initial implementation support fusing 2 filters in the following configurations:
 
  Configuration 1: Convolution -> Normalization+Activation
  filter0 is convolution and filter1 is normalization. for example, the filter_type and layer_params arrays when using batchnorm should be as follows:
  filter_type: [BNNSConvolution, BNNSBatchNorm]
  layer_params: [pointer to BNNSLayerParametersConvolution, pointer to BNNSLayerParametersNormalization]
  convolution must have activation function BNNSActivationFunctionIdentity, normalization can have any activation function as long as it comply with fused activation restrictions described in BNNSFilterApplyBackwardBatch

  Configuration 2: FullyConnected -> Normalization+Activation
  filter0 is fully connected and filter1 is normalization. for example, the filter_type and layer_params arrays when using batchnorm should be as follows:
  filter_type: [BNNSFullyConnected, BNNSBatchNorm]
  layer_params: [pointer to BNNSLayerParametersFullyConnected, pointer to BNNSLayerParametersNormalization]
  fully connected must have activation function BNNSActivationFunctionIdentity, normalization can have any activation function as long as it comply with fused activation restrictions described in BNNSFilterApplyBackwardBatch

  Configuration 3: Transposed Convolution -> Normalization+Activation
  filter0 is tranposed convolution and filter1 is normalization. for example, the filter_type and layer_params arrays when using batchnorm should be as follows:
  filter_type: [BNNSTransposedConvolution, BNNSBatchNorm]
  layer_params: [pointer to BNNSLayerParametersConvolution, pointer to BNNSLayerParametersNormalization]
  transposed convolution must have activation function BNNSActivationFunctionIdentity, normalization can have any activation function as long as it comply with fused activation restrictions described in BNNSFilterApplyBackwardBatch

  @param number_of_fused_filters number of filters to fuse
  @param filter_type pointer to an array of filter type, array size must be number_of_fused_filters
  @param layer_params pointer to an array of layer parameter pointers. layer_params array size must be number_of_fused_filters
  every layer parameter structure must be valid and match the type specified in filter_type array, such that layer parameter at index i of layer_params can be used to create a stand-alone filter of the type specified by the filter type in filter_type array at index i.
  @param filter_params Filter runtime parameters, may be NULL for default parameters.

  @return A new non-NULL filter on success, and NULL on failure.

 */
BNNSFilter BNNSFilterCreateFusedLayer(const size_t number_of_fused_filters,
                                      const BNNSFilterType * filter_type,
                                      const void *_Nonnull *_Nonnull layer_params,
                                      const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

#pragma mark - Inference

/*!
  @abstract Apply a filter

  @param filter Filter to apply
  @param in Pointer to the input data
  @param out Pointer to the output data

  @return 0 on success, and -1 on failure.
 */
int BNNSFilterApply(BNNSFilter filter, const void * in, void * out)
__API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!

  @abstract Apply a filter to several pairs of (input, output) data

  @discussion
  The filter is applied for each of the <tt>batch_size</tt> inputs, and produces <tt>batch_size</tt> outputs.
  <tt>in</tt> (resp. <tt>out</tt>) is expected to point to <tt>batch_size</tt> times the input (resp. output) object size defined when the filter was created.

  @param filter Filter to apply
  @param batch_size Number of (input, output) pairs to process
  @param in Pointer to the input data
  @param in_stride Increment (in values) between inputs
  @param out Pointer to the output data
  @param out_stride Increment (in values) between outputs

  @return 0 on success, and -1 on failure.

 */

int BNNSFilterApplyBatch(BNNSFilter filter,
                         size_t batch_size,
                         const void * in,
                         size_t in_stride,
                         void * out,
                         size_t out_stride)
__API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!
 @abstract Applies a previously created pooling layer filter

 @discussion
 Pooling layer filter is applied for each of the batch_size inputs, and produces batch_size outputs. indices is optional.
 in (resp. out) is expected to point to batch_size times the input (resp. output) object size defined when the filter was created.
 indices has the same size as output if not null.

 @param filter Filter to apply
 @param batch_size Number of (input, output, indices)  to process
 @param in Pointer to the input data
 @param in_stride Increment (in values) between inputs
 @param out  Pointer to the output data
 @param out_stride Increment (in values) between outputs
 @param indices  Pointer to the indices data generated by max pooling.
 - max pooling produces indices if not null. indices must have the same dimension and stride as the output data.
 - max unpooling requires a valid pointer. indices must have the same dimension and stride as the input data.
 - ignored for other pooling functions
 @param idx_stride Increment (in values) between indices
 */
int BNNSPoolingFilterApplyBatch(BNNSFilter filter, size_t batch_size,
                                const void * _Nonnull in, size_t in_stride,
                                void * _Nonnull out, size_t out_stride,
                                size_t * _Nullable indices, size_t idx_stride)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

  @abstract Apply a filter

  @param filter Filter to apply
  @param inA Pointer to the first input tensor
  @param inB Pointer to the second input tensor
  @param out Pointer to the output data

  @return 0 on success, and -1 on failure.
*/
int BNNSFilterApplyTwoInput(BNNSFilter filter,
                            const void * inA,
                            const void * inB,
                            void * out)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

  @abstract Apply a filter to a several pairs of (input, output) data

  @discussion
  The filter is applied for each of the <tt>batch_size</tt> inputs, and produces <tt>batch_size</tt> outputs.
  <tt>in</tt> (resp. <tt>out</tt>) is expected to point to <tt>batch_size</tt> times the input (resp. output) object size defined when the filter was created.

  @param filter Filter to apply
  @param batch_size Number of (input, output) pairs to process
  @param inA Pointer to the first input tensor
  @param inA_stride Increment (in values) between inputs in the first tensor
  @param inB Pointer to the second input tensor
  @param inB_stride Increment (in values) between inputs in the second tensor
  @param out Pointer to the output data
  @param out_stride Increment (in values) between outputs

  @return 0 on success, and -1 on failure.

*/
int BNNSFilterApplyTwoInputBatch(BNNSFilter filter,
                                 size_t batch_size,
                                 const void * inA,
                                 size_t inA_stride,
                                 const void * inB,
                                 size_t inB_stride,
                                 void * out,
                                 size_t out_stride)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Apply a normalization filter to several pairs of (input, output) data

 @discussion
 The filter is applied for each of the <tt>batch_size</tt> inputs, and produces <tt>batch_size</tt> outputs.
 <tt>in</tt> (resp. <tt>out</tt>) is expected to point to <tt>batch_size</tt> times the input (resp. output) object size defined when the filter was created.

 Normalization filter supports two different modes - training and inference.
 In training mode, only current batch/instance/layer/group statistics are used to normalize the input.
 In addition, training mode may store information internally to be used during backward computation.
 For batch norm and instance norm, moving mean and moving variance are computed during training
 so they can be later used during inference, ignored if null.
 For layer norm and group norm, moving mean and moving variance are not supported and ignored.

 For batch norm and instance norm,  moving mean and moving variance are used to normalize the input during inference if not null.
 Otherwise, current batch/instance/layer/group statistics are used to normalize the input.

 output address equal to input address (in-place) is supported for both training and inference

 @param filter Filter to apply
 @param batch_size Number of (input, output) pairs to process
 @param in Pointer to the input data
 @param in_stride Increment (in values) between inputs
 @param out Pointer to the output data
 @param out_stride Increment (in values) between outputs
 @param training true if training, false if inference

 @return 0 on success, and -1 on failure.

 */

int BNNSNormalizationFilterApplyBatch(BNNSFilter filter,
                                      size_t batch_size,
                                      const void * in,
                                      size_t in_stride,
                                      void * out,
                                      size_t out_stride,
                                      bool training)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Apply a fused filter to several pairs of (input, output) data

 @discussion
 The filter is applied for each of the <tt>batch_size</tt> inputs, and produces <tt>batch_size</tt> outputs.
 <tt>in</tt> (resp. <tt>out</tt>) is expected to point to <tt>batch_size</tt> times the input (resp. output) object size defined when the filter was created.

 @param filter Filter to apply
 @param batch_size Number of (input, output) pairs to process
 @param in Pointer to the input data
 @param in_stride Increment (in values) between inputs
 @param out  Pointer to the output data
 @param out_stride Increment (in values) between outputs
 @param training true if training, false if inference
 -ignored if none of the filters is batchnorm
 -see training flag information in BNNSBatchNormFilterApplyBatch

 @return 0 on success, and -1 on failure.

 */

int BNNSFusedFilterApplyBatch(BNNSFilter filter,
                              size_t batch_size,
                              const void * in,
                              size_t in_stride,
                              void * out,
                              size_t out_stride,
                              bool training)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Apply an arithmetic filter to several pairs of (input set, output) data

 @discussion
 an input set is composed of the inputs necessary to compute a given arithmetic operation.

 The filter is applied for each of the <tt>batch_size</tt> inputs, and produces <tt>batch_size</tt> outputs.
 <tt>batch_size</tt> is ignored for an input or output if its type is BNNSConstant or BNNSParameter.

 <tt>in</tt> is expected to point to an array of arithmetic operation inputs as required by the given arithmetic operation.
 Inputs and output must have the same data layout. Input support broadcasting such that two descriptors are compatible if for every dimension descriptors sizes are equal or one of them is 1.
 for example, a valid addition operation could have input1 size [1,3,4], input2 size [2,3,1] and output size [2,3,4]
 unless specified otherwise, each input size should be equal to output size or be broadcast compatible.
 inputs are allowed to point to a common address (same input), in which case gradients in backward compute must also point to a common address (same gradient).

 for example, an addition arithmetic operation require two inputs, and therefore the in array size and the in_stride array size is 2.
 each pointer in the in array should point to a valid input.
 in case input1, input2 and output types are all BNNSSample, the output for each output sample in the batch will be the addition of the corresponding batch sample in input1 and in input2.
 if output and input1 are BNNSSample and input2 is BNNSConstant or BNNSParameter, the output for each output sample in the batch will be the addition of the corresponding batch sample in input1 and input2 where batch is ignored for input2.

 Some arithmetic functions support in-place processing for forward and backward apply operations. That is the input and output (or output_delta and input_delta) may use the same pointer and descriptor in order to save memory (if the layer has multiple inputs, the user may choose which to use in-place).
 The input data is destroyed in the process, thus care must be taken during the forward pass to ensure all required inputs to the backward pass are preserved (noting that this layer’s input is normally the preceding layer’s output).
 In addition, descriptors for input being processed in-place and output must exactly match. in-place descriptor types must also match in case batch size > 1.

 @param filter Filter to apply
 @param batch_size Number of (input sets, output) pairs to process
 @param number_of_inputs number of inputs for the arithmetic operation
 @param in pointer to an array of input pointers. in array size must be number_of_inputs.
 @param in_stride pointer to an array of input strides, each stride is an Increment (in values) between inputs in the batch for a corresponding input in the in array.
 @param out Pointer to the output data
 @param out_stride Increment (in values) between outputs

 @return 0 on success, and -1 on failure.

 */
int BNNSArithmeticFilterApplyBatch(BNNSFilter filter,
                                   size_t batch_size,
                                   size_t number_of_inputs,
                                   const void *_Nonnull *_Nonnull in,
                                   const size_t * in_stride,
                                   void * out,
                                   size_t out_stride)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));


/*! @abstract Applies a previously created multihead attention layer
 *
 *  @discussion
 *  When training, the backward pass can be accelerated by caching intermediate values from the forward pass.
 *  This is done by providing a memory buffer backprop_cache. The recommended size for this buffer may be obtained by calling
 *  the function with the pointer backprop_cache_size set to non-NULL, and backprop_cache set to NULL. The recommended size
 *  will be stored in *backprop_cache_size (the layer application will not be perfomed).
 *  The user may optionally provide a scratch workspace. The required size will depend the size of backprop_cache provided, and
 *  if no scratch workspace is provided one will be allocated internally. The size of required workspace can be obtained by calling
 *  the routine with a non-NULL workspace_size parameter and a NULL workspace pointer, and the required size will be returned
 *  in *workspace_size (the layer application will not be perfomed).
 *  If both backprop_cache_size and workspace_size are queried simulateneously, the returned workspace size will assume that
 *  the full backprop_cache_size is provided.
 *
 *  @param F Filter to apply created by a previous call to BNNSFilterCreateLayerMultiheadAttention()
 *  @param batch_size Number of inputs in batch
 *  @param query Pointer to data for query input matrix, layout as described by layer_params->query.target_desc
 *  @param query_stride Batch stride for query
 *  @param key Pointer to data for key input matrix, layout as described by layer_params->key.target_desc
 *  @param key_stride Batch stride for key
 *  @param key_mask Mask applied to key for ignoring entries. A 1D tensor of type BNNSDataTypeBoolean and shape
 *         source_length. Where this tensor evalautes to true, the corresponding elements of the key matrix are
 *         ignored in the attention operation. No key mask is applied if NULL is passed.
 *  @param key_mask_stride Batch stride for key_mask
 *  @param value Pointer to data for value input matrix, layout as described by layer_params->value.target_desc
 *  @param value_stride Batch stride for value
 *  @param output Pointer to data for output matrix, layout as described by layer_params->output.target_desc
 *  @param output_stride Batch stride for output
 *  @param add_to_attention Optional, a 2D tensor of shape target_length x source_length that is used as part of the mask function prior
 *         to softmax in the attention calculation (the matrix X in the layer description). No matrix is added if this pointer is NULL.
 *  @param backprop_cache_size Specifies the size of the array backprop_cache, in bytes.
 *         If backprop_cache_size is not-NULL but backprop_cache is NULL, the recommended size for backprop_cache_size
 *         will be set, but not other calculations will be performed (except to set workspace_size if requested).
 *  @param backprop_cache Is used to store intermediate results that can be used to accelerate a future call to
 *         BNNSApplyMultiheadAttentionBackward.
 *  @param workspace_size Specifies the size of the array workspace, in bytes.
 *         If workspace_size is not-NULL but workspace is NULL, the recommended size for workspace_size
 *         will be set, but not other calculations will be performed (except to set backprop_cache_size if requested).
 *  @param workspace Is used as a scratch buffer during the calculation.
 */
int BNNSApplyMultiheadAttention(BNNSFilter F, size_t batch_size,
                                void const* query, size_t query_stride,
                                void const* key, size_t key_stride,
                                BNNSNDArrayDescriptor const* _Nullable key_mask, size_t key_mask_stride,
                                void const* value, size_t value_stride,
                                void *output, size_t output_stride,
                                BNNSNDArrayDescriptor const* _Nullable add_to_attention,
                                size_t * _Nullable backprop_cache_size, void * _Nullable backprop_cache,
                                size_t * _Nullable workspace_size, void * _Nullable workspace)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

#pragma mark - Filter destruction

/*!

  @abstract Destroy filter

  @discussion Releases all resources allocated for this filter.

  @param filter Filter to destroy

*/

void BNNSFilterDestroy(BNNSFilter filter)
__API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

#pragma mark - Training

/*!

  @abstract Apply a single step of optimization to one or more parameters

  @discussion
  The optimizer will use the specified optimization algorithm to update a set of parameters such as weights and bias.
  Data layout in memory of parameters, gradients and accumulators arrays must be contiguous, such that stride[0]=1 and for every N>0 stride[N]=stride[N-1]*size[N-1]. strides   in the descriptors may be provided as zeros.
  accumulators must be allocated by caller and have the same size as a matching parameter. accumulator descriptor data must be set to zero the first time the filter is   applied.
  OptimizerAlgFields pointer is saved internally, changes to the struct fields such as learning_rate for BNNSOptimizerSGDMomentumFields structure are allowed between   filter apply calls.

  Accumulator requirements depend on the optimzation algorithm and its parameters:

  BNNSOptimzerFunctionSGDMomentum
  ===============================
  Set to NULL for vanilla SGD (indicating momentum is 0).
  Set to a size number_of_parameters array if use of momentum is desired.

  BNNSOptimizerFunctionAdam
  =======================
  Set to a size 2*number_of_parameters array.
  The first number_of_parameters pointers are used for the first momentum descriptors, and the subsequent number_of_parameters pointers are used for the second  momentum descriptors.

  BNNSOptimizerFunctionRMSProp
  ==========================
  Should be of size k*number_of_parameters, where
    k = 1  +  (OptimizerAlgFields.centered ? 1 : 0)  + (OptimizerAlgFields.momentum != 0.0).
  That is to say a base of one accumulator per parameter, with one extra accumulator required for each of centering and momentum if they are enabled.
  Using the notation used in the description of BNNSOptimizerRMSPropFields, the first number_of_parameters pointers are used for n_i, the next
  set are used for g_i (iff centering is used) and the next set are used for the momentum Δ_i (iff momentum γ != 0.0).

  @param function Optimization function (algorithm) to use
  @param OptimizerAlgFields Parameters for optimization function, pointer to a struct whose type is determined by the value of function.
  @param number_of_parameters number of parameters to update
  @param parameters array of parameter descriptors
  @param gradients array of gradient descriptors. Each gradient descriptor data in the array must be the same size as its matching parameter descriptor in the  parameters array.
  @param accumulators array of accumulator descriptors. Required number of accumulators varies depending on optimization algorithm and parameters - see function description. In all cases, accumulators must be allocated and initialized to zero by the user prior to the first call optimization step.
  @param filter_params Filter runtime parameters, may be NULL for default parameters.

  @returns 0 on success, non-zero on failure
*/
int BNNSOptimizerStep(BNNSOptimizerFunction function, const void *OptimizerAlgFields,
                      size_t number_of_parameters,
                      BNNSNDArrayDescriptor *_Nonnull *_Nonnull parameters,
                      const BNNSNDArrayDescriptor *_Nonnull *_Nonnull gradients,
                      BNNSNDArrayDescriptor * _Nullable * _Nullable accumulators,
                      const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Apply filter backward to generate input delta, weights delta and bias delta

 @discussion
 For a general filter f that computes output y by using weights w and bias b
 The forward pass filter computation can be described as:
 y = f(x,w,b)
 for example, the output y of a convolution filter f can be described as
 y = f(x,w,b) = w*x+b

 The backward computation uses the output delta (dy) to generate the input delta (dx), weight delta (dw) and bias delta (db)
 In some cases the backward computation function also requires the forward pass input (x) and the forward pass output (y).

 The following arguments are required for the backward computation:
 out_delta descriptor (dy) are the gradients arriving from the following filter and must be provided.
 in pointer is the forward pass input (x) and should be provided if not specified it is ignored
 out pointer is the forward pass output (y) and should be provided if not specified it is ignored

 For dropout processing, it only needs delta of input/output, and the result is independent of forward input/output.  So backward apply will ignore input/output.

 The following gradients are generated by the backward computation.
 in_delta  - the input delta (dx)
 weights_delta - the weight delta (dw)
 bias_delta - the bias delta (db)
 NULL descriptor pointers will not be computed. data field of a valid descriptor must point to the delta buffer to be produced.

 Important activation information:
 For any general activation function, when computing activation layer backward, the forward pass input (x) to the activation is required.
 However, in most activation functions, it is possible and faster to compute the activation backward from the forward pass output y.
 In the case of fused computation and activation layers, it is mandatory to provide the forward pass output y.
 Notice that some activation functions cannot be fused with the computation filters.

 Activation backward functions that can accept either forward pass input or forward pass output (output is prefered):
 BNNSActivationFunctionIdentity
 BNNSActivationFunctionRectifiedLinear
 BNNSActivationFunctionLeakyRectifiedLinear   (if alpha > 0.0 and weights_delta is not present)
 BNNSActivationFunctionSigmoid
 BNNSActivationFunctionLogSigmoid
 BNNSActivationFunctionTanh
 BNNSActivationFunctionLinear
 BNNSActivationFunctionClamp
 BNNSActivationFunctionSoftmax
 BNNSActivationFunctionHardSigmoid
 BNNSActivationFunctionSoftplus
 BNNSActivationFunctionSoftsign
 BNNSActivationFunctionELU
 BNNSActivationFunctionSELU
 BNNSActivationFunctionCELU
 BNNSActivationFunctionClampedLeakyRectifiedLinear  (if alpha > 0.0)
 BNNSActivationFunctionLinearWithBias
 BNNSActivationFunctionLogSoftmax
 BNNSActivationFunctionHardShrink
 BNNSActivationFunctionSoftShrink
 BNNSActivationFunctionTanhShrink
 BNNSActivationFunctionThreshold

 The activation functions above can be fused with computation in training, only if the forward pass output y is provided in backward apply.

 Other activation functions require forward pass input and does not support fusing computation with activation, such as:
 BNNSActivationFunctionAbs
 BNNSActivationFunctionGELUApproximation
 BNNSActivationFunctionGELUApproximation2

 Additional requirements:
 BNNSFlagsUseClientPtr flag must be enabled when creating the filter.
 data_type of all descriptors must be BNNSDataTypeFloat32.

 @param filter Filter to apply backward
 @param batch_size Number of (input, output) pairs to process
 @param in Pointer to the forward pass input data (x)
 - ignored when computing input delta and bias delta unless filter is pooling or filter is activation and backpropagation from output is supported.
 @param in_stride Increment (in values) between inputs
 - ignored when computing input delta or bias delta if the filter is not pooling
 @param in_delta Pointer to the input delta descriptor
 - not produced if null
 @param in_delta_stride Increment (in values) between input deltas
 @param out Pointer to the forward pass output data (y)
 - out is ignored in all filters if activation is BNNSActivationFunctionIdentity
 - some activation function backward computation can run faster if provided with the forward output
 - fused computation and activation filters such as convolution with activation must provide the forward pass output
 @param out_stride Increment (in values) between outputs
 @param out_delta Pointer to the output delta descriptor (dy)
 @param out_delta_stride Increment (in values) between output deltas
 @param weights_delta Pointer to the weights delta descriptor
 - delta is aggregated across batch
 - not produced if null
 - computed weights_delta layout will match the filter weight layout that was provided at the creation of the filter
 @param bias_delta Pointer to the bias delta descriptor
 - not produced if null
 @return 0 on success, and -1 on failure.
 */
int BNNSFilterApplyBackwardBatch(BNNSFilter filter,
                                 size_t batch_size,
                                 const void * _Nullable in,
                                 size_t in_stride,
                                 BNNSNDArrayDescriptor * _Nullable in_delta,
                                 size_t in_delta_stride,
                                 const void * _Nullable out,
                                 size_t out_stride,
                                 const BNNSNDArrayDescriptor * out_delta,
                                 size_t out_delta_stride,
                                 BNNSNDArrayDescriptor * _Nullable weights_delta,
                                 BNNSNDArrayDescriptor * _Nullable bias_delta)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Apply pooling filter backward to generate input delta and bias delta

 @discussion
 This is similar to BNNSFilterApplyBackwardBatch, but takes indices as an optional input.
 It is mandatory to compute all active gradients in a single function call. computation of input delta is not required in case the filter is the first layer in the network

 @param filter Filter to apply backward
 @param batch_size Number of (input, output, indices) to process
 @param in Pointer to the forward pass input data (x)
 @param in_stride Increment (in values) between inputs
 @param in_delta Pointer to the input delta descriptor
 - not produced if null
 @param in_delta_stride Increment (in values) between input deltas
 @param out Pointer to the forward pass output data (y)
 - out is ignored if activation is BNNSActivationFunctionIdentity
 - fused pooling and activation filters  must provide the forward pass output
 @param out_stride Increment (in values) between outputs
 @param out_delta Pointer to the output delta descriptor (dy)
 @param out_delta_stride Increment (in values) between output deltas
 @param bias_delta Pointer to the bias delta descriptor
 - not produced if null
 @param indices Pointer to the forward pass indices data generated by max pooling.
 - max pooling could use indices to reduce computation if not null. indices must have the same dimension and stride as the output data.
 - max unpooling requires a valid pointer. indices must have the same dimension and stride as the input data.
 - ignored for other pooling functions
 @param idx_stride Increment (in values) between indices
 @return 0 on success, and -1 on failure.
 */
int BNNSPoolingFilterApplyBackwardBatch(BNNSFilter filter,
                                        size_t batch_size,
                                        const void * _Nullable in,
                                        size_t in_stride,
                                        BNNSNDArrayDescriptor * _Nullable in_delta,
                                        size_t in_delta_stride,
                                        const void * _Nullable out,
                                        size_t out_stride,
                                        BNNSNDArrayDescriptor * _Nonnull out_delta,
                                        size_t out_delta_stride,
                                        BNNSNDArrayDescriptor * _Nullable bias_delta,
                                        const size_t * _Nullable indices,
                                        size_t idx_stride)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Apply filter backward to generate input deltas, weights delta and bias delta (two input version)

 @discussion
 For a general filter f that computes output y by using weights w and bias b
 The forward pass filter computation can be described as:
 y = f(x,w,b)
 for example, the output y of a convolution filter f can be described as
 y = f(x,w,b) = w*x+b

 The backward computation uses the output delta (dy) to generate the input deltas (dxA, dxB), weight delta (dw) and bias delta (db) [as applicable]
 In some cases the backward computation function also requires the forward pass input (x) and the forward pass output (y).

 The following arguments are required for the backward computation:
 out_delta descriptor (dy) are the gradients arriving from the following filter and must be provided.
 in pointer is the forward pass input (x) and should be provided if not specified it is ignored
 out pointer is the forward pass output (y) and should be provided if not specified it is ignored

 The following gradients are generated by the backward computation.
 in_delta  - the input delta (dx)
 weights_delta - the weight delta (dw)
 bias_delta - the bias delta (db)
 NULL descriptor pointers will not be computed. data field of a valid descriptor must point to the delta buffer to be produced.

 Important activation information:
 For any general activation function, when computing activation layer backward, the forward pass input (x) to the activation is required.
 However, in most activation functions, it is possible and faster to compute the activation backward from the forward pass output y.
 In the case of fused computation and activation layers, it is mandatory to provide the forward pass output y.
 Notice that some activation functions cannot be fused with the computation filters.

 Activation backward functions that can accept either forward pass input or forward pass output (output is prefered):
 BNNSActivationFunctionIdentity
 BNNSActivationFunctionRectifiedLinear
 BNNSActivationFunctionLeakyRectifiedLinear (if alpha >= 0.0)
 BNNSActivationFunctionSigmoid
 BNNSActivationFunctionLogSigmoid
 BNNSActivationFunctionTanh
 BNNSActivationFunctionLinear
 BNNSActivationFunctionClamp
 BNNSActivationFunctionSoftmax
 BNNSActivationFunctionHardSigmoid
 BNNSActivationFunctionSoftplus
 BNNSActivationFunctionSoftsign
 BNNSActivationFunctionELU
 BNNSActivationFunctionSELU
 BNNSActivationFunctionCELU
 BNNSActivationFunctionClampedLeakyRectifiedLinear (if alpha >= 0.0)
 BNNSActivationFunctionLinearWithBias
 BNNSActivationFunctionLogSoftmax
 BNNSActivationFunctionHardShrink
 BNNSActivationFunctionSoftShrink
 BNNSActivationFunctionTanhShrink
 BNNSActivationFunctionThreshold

 The activation functions above can be fused with computation in training, only if the forward pass output y is provided in backward apply.

 Other activation functions require forward pass input and does not support fusing computation with activation, such as:
 BNNSActivationFunctionAbs
 BNNSActivationFunctionGELUApproximation
 BNNSActivationFunctionGELUApproximation2

 Additional requirements:
 BNNSFlagsUseClientPtr flag must be enabled when creating the filter.
 data_type of all descriptors must be BNNSDataTypeFloat32.

 @param filter Filter to apply backward
 @param batch_size Number of (input, output) pairs to process
 @param inA Pointer to the forward pass input data (x)
 @param inA_stride Increment (in values) between inputs
 @param inA_delta Pointer to the input delta descriptor
 - not produced if null
 @param inA_delta_stride Increment (in values) between input deltas
 @param inB Pointer to the forward pass input data (x)
 @param inB_stride Increment (in values) between inputs
 @param inB_delta Pointer to the input delta descriptor
 - not produced if null
 @param inB_delta_stride Increment (in values) between input deltas
 @param out Pointer to the forward pass output data (y)
 @param out_stride Increment (in values) between outputs
 @param out_delta Pointer to the output delta descriptor (dy)
 @param out_delta_stride Increment (in values) between output deltas
 @param weights_delta Pointer to the weights delta descriptor
 - delta is aggregated across batch
 - not produced if null
 - computed weights_delta layout will match the filter weight layout that was provided at the creation of the filter
 @param bias_delta Pointer to the bias delta descriptor
 - not produced if null
 @return 0 on success, and -1 on failure.
*/
int BNNSFilterApplyBackwardTwoInputBatch(BNNSFilter filter,
                                         size_t batch_size,
                                         const void * _Nullable inA,
                                         size_t inA_stride,
                                         BNNSNDArrayDescriptor * _Nullable inA_delta,
                                         size_t inA_delta_stride,
                                         const void * _Nullable inB,
                                         size_t inB_stride,
                                         BNNSNDArrayDescriptor * _Nullable inB_delta,
                                         size_t inB_delta_stride,
                                         const void * _Nullable out,
                                         size_t out_stride,
                                         const BNNSNDArrayDescriptor * out_delta,
                                         size_t out_delta_stride,
                                         BNNSNDArrayDescriptor * _Nullable weights_delta,
                                         BNNSNDArrayDescriptor * _Nullable bias_delta)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Apply a normalization filter backward to generate input delta, beta delta and gamma delta

 @discussion
 similar to BNNSFilterApplyBackwardBatch, but computing input delta, beta delta and gamma delta
 It is mandatory to compute all active gradients in a single function call. computation of input delta is not required in case the filter is the first layer in the network

 @param filter Filter to apply backward
 @param batch_size Number of (input, output) pairs to process
 @param in_delta Pointer to the input delta descriptor
 - not produced if null
 @param in_delta_stride Increment (in values) between input deltas
 @param out Pointer to the forward pass output data (y)
 - out is ignored if activation is BNNSActivationFunctionIdentity
 - forward pass output must be provided in case of fused instance normalization and activation
 @param out_stride Increment (in values) between outputs
 @param out_delta Pointer to the output delta descriptor (dy)
 - out delta may be modified in order to save memory allocations when computing fused activation backward
 @param out_delta_stride Increment (in values) between output deltas
 @param beta_delta Pointer to the beta delta descriptor
 - not produced if null
 @param gamma_delta Pointer to the gamma delta descriptor
 - not produced if null
 @return 0 on success, and -1 on failure.
 */
int BNNSNormalizationFilterApplyBackwardBatch(BNNSFilter filter,
                                              size_t batch_size,
                                              BNNSNDArrayDescriptor * _Nullable in_delta,
                                              size_t in_delta_stride,
                                              const void * _Nullable out,
                                              size_t out_stride,
                                              BNNSNDArrayDescriptor * out_delta,
                                              size_t out_delta_stride,
                                              BNNSNDArrayDescriptor * _Nullable beta_delta,
                                              BNNSNDArrayDescriptor * _Nullable gamma_delta)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

  @abstract Apply a fused filter backward to generate gradients.

  @discussion
  similar to BNNSFilterApplyBackwardBatch, but computing gradients of an N layer fused filter.
  It is mandatory to compute all active parameter delta in a single function call. computation of input delta is not required in case the fused filter is the first layer in the network

  @param filter Filter to apply backward
  @param batch_size Number of (input, output) pairs to process
  @param in Pointer to the forward pass computation input data (x)
  @param in_stride Increment (in values) between inputs
  - ignored when computing input delta or bias delta if the filter is not pooling
  @param in_delta Pointer to the computation input delta descriptor
  - not produced if null
  @param in_delta_stride Increment (in values) between input deltas
  @param out Pointer to the forward pass output data (y)
  - out is ignored if last filter activation is BNNSActivationFunctionIdentity
  @param out_stride Increment (in values) between outputs
  @param out_delta Pointer to the last filter output delta descriptor (dy)
  - out delta may be modified to save memory when computing fused activation backward
  @param out_delta_stride Increment (in values) between output deltas
  @param delta_parameters
  a pointer to an array of parameter delta pointers
  order of parameter must be first filter parameters followed by second filter parameters until reaching the last filter parameters
  for each filter parameters, the parameter order must follow the same order as in the stand-alone filter backward apply api
  all filter parameters must be provided, excluding input delta and output delta which are provided separately
  null pointer must be used for each non active parameter
  for example, if first filter is convolution and second filter is batchnorm, parameters could be extracted in the following way:
  BNNSNDArrayDescriptor* weights_delta = delta_parameters[0]; //weight delta is the first convolution parameter in BNNSFilterApplyBackwardBatch
  BNNSNDArrayDescriptor* bias_delta = delta_parameters[1];  //bias delta is the second convolution parameter in BNNSFilterApplyBackwardBatch
  BNNSNDArrayDescriptor* beta_delta = delta_parameters[2]; //first batchnorm parameter in BNNSBatchNormFilterApplyBackwardBatch
  BNNSNDArrayDescriptor* gamma_delta = delta_parameters[3]; //second batchnorm parameter in BNNSBatchNormFilterApplyBackwardBatch

  @return 0 on success, and -1 on failure.
 */
int BNNSFusedFilterApplyBackwardBatch(BNNSFilter filter,
                                      size_t batch_size,
                                      const void * _Nullable in,
                                      size_t in_stride,
                                      BNNSNDArrayDescriptor * _Nullable in_delta,
                                      size_t in_delta_stride,
                                      const void * _Nullable out,
                                      size_t out_stride,
                                      BNNSNDArrayDescriptor * out_delta,
                                      size_t out_delta_stride,
                                      BNNSNDArrayDescriptor * _Nullable * _Nullable delta_parameters)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Apply an arithmetic filter backward to generate input gradients

 @discussion
 Compute gradients for all arithmetic operation inputs
 It is mandatory to compute all input gradients in a single function call.
 if inputs were pointing to a common address during forward computation (same input), gradients should also point to a common address (same gradient)
 descriptors for output delta and input delta that are being processed in-place must exactly match. in-place descriptor types must also match in case batch size > 1.

 @param filter Filter to apply
 @param batch_size Number of (input sets, output) pairs to process
 @param number_of_inputs number of inputs for the arithmetic operation
 @param in pointer to an array of input pointers. in array size must be number_of_inputs.
 - in may be NULL for arithmetic layers that support forward in-place processing
 @param in_stride pointer to an array of input strides, each stride is an Increment (in values) between inputs in the batch for a corresponding input in the in array.
 @param in_delta pointer to an array of input delta pointers. in array size must be number_of_inputs.
 @param in_delta_stride pointer to an array of input delta strides, each stride is an Increment (in values) between inputs deltas in the batch for a corresponding input in the in_delta array.
 @param out Pointer to the forward pass output data (y)
 - forward pass output must be provided in case of fused arithmetic and activation
 - out may not be provided when activation is BNNSActivationFunctionIdentity, but in some arithmetic functions, providing the forward output may speedup the backward compute.
 @param out_stride Increment (in values) between outputs
 @param out_delta Pointer to the output delta descriptor (dy)
 @param out_delta_stride Increment (in values) between output deltas

 @return 0 on success, and -1 on failure.

 */
int BNNSArithmeticFilterApplyBackwardBatch(BNNSFilter filter,
                                           size_t batch_size,
                                           size_t number_of_inputs,
                                           const void * _Nullable * _Nullable in,
                                           const size_t * _Nullable in_stride,
                                           BNNSNDArrayDescriptor *_Nonnull *_Nonnull in_delta,
                                           const size_t * in_delta_stride,
                                           const void * _Nullable out,
                                           const size_t out_stride,
                                           BNNSNDArrayDescriptor * out_delta,
                                           const size_t out_delta_stride)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Apply permute filter backward to generate input gradient

 @discussion
 similar to BNNSFilterApplyBackwardBatch with only the necessary argument subset for permute.

 @param filter Filter to apply
 @param batch_size Number of (input, output) pairs to process
 @param in_delta Pointer to the input delta descriptor
 @param in_delta_stride Increment (in values) between input deltas
 @param out_delta Pointer to the output delta descriptor
 @param out_delta_stride Increment (in values) between output deltas

 */
int BNNSPermuteFilterApplyBackwardBatch(BNNSFilter filter,
                                        size_t batch_size,
                                        BNNSNDArrayDescriptor * in_delta,
                                        size_t in_delta_stride,
                                        const BNNSNDArrayDescriptor * out_delta,
                                        size_t out_delta_stride)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Apply a loss filter to compute forward loss and loss gradient on a batch with several pairs of (input, labels)

 @discussion
 The filter is applied for each of the <tt>batch_size</tt> inputs,labels and computes reduced loss and an optional loss gradient.
 <tt>in</tt> (resp. <tt>out</tt>) is expected to point to <tt>batch_size</tt> times the input (resp. output) object size defined when the filter was created.
 The function supports forward loss computation, and also backward loss without back propagation from output delta.
 Input delta computation is an optimization that can be used if the loss layer is the last layer in the network.

 @param filter Loss filter to apply
 @param batch_size Number of (input, labels) pairs to compute
 @param in Pointer to the input data
 @param in_stride Increment (in values) between inputs
 @param labels Pointer to the labels
 @param labels_stride Increment (in values) between labels
 @param weights optional loss computation weight
 @param weights_size weight size must be one of:
 for softmax cross entropy:
    0 results in no weight loss scaling.
    1 results in same weight scaling for all samples in the batch.
    batch_size results in different weight per each sample in the batch
 for sigmoid cross enrtopy, mse and huber loss, weights_size must be one of:
    0 results in no weight loss scaling.
    1 results in same weight scaling for all samples in the batch.
    batch_size*input_width results in different weight per each sample in the batch
 @param out Pointer to the computed loss. output size depand on loss function and reduction function.
 Loss array expected to be consecutive in memory (in case loss is unreduced), such that the stride between loss of consecutive samples in the batch is 1.
 if loss is reduced, out will be a single result.
 for softmax cross entropy, if loss is unreduced, out should be large enough to contain batch_size consecutive loss results.
 for sigmoid cross entropy unreduced loss, mse unreduced loss and huber unreduced loss, out should be large enough to contain batch_size*input_width consecutive loss results, where input_width is size[0] of the input descriptor.

 @param in_delta Pointer to the input delta descriptor
 - not produced if null
 @param in_delta_stride Increment (in values) between input deltas

 @return 0 on success, and -1 on failure.

 */
int BNNSLossFilterApplyBatch(BNNSFilter filter,
                             size_t batch_size,
                             const void * in,
                             size_t in_stride,
                             const void * labels,
                             size_t labels_stride,
                             const void * _Nullable weights,
                             size_t weights_size,
                             void * out,
                             BNNSNDArrayDescriptor * _Nullable in_delta,
                             size_t in_delta_stride)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Apply a loss filter backward to generate gradients.

 @discussion
 The filter is applied for each of the <tt>batch_size</tt> inputs,labels and computes the backward loss gradient.
 <tt>in</tt> (resp. <tt>out</tt>) is expected to point to <tt>batch_size</tt> times the input (resp. output) object size defined when the filter was created.
 Note that if the loss layer is the last layer in the network, the BNNSLossFilterApplyBatch can be used to compute both forward and backward without back propagation from output delta.

 @param filter Loss filter to apply
 @param batch_size Number of (input, labels) pairs to compute
 @param in Pointer to the input data
 @param in_stride Increment (in values) between inputs
 @param in_delta Pointer to the input delta descriptor
 @param in_delta_stride Increment (in values) between input deltas
 @param labels Pointer to the labels
 @param labels_stride Increment (in values) between labels
 @param weights optional loss computation weight
 @param weights_size weight size must be one of:
 for softmax cross entropy:
    0 results in no weight loss scaling.
    1 results in same weight scaling for all samples in the batch.
    batch_size results in different weight per each sample in the batch
 for sigmoid cross enrtopy, mse and huber loss, weights_size must be one of:
    0 results in no weight loss scaling.
    1 results in same weight scaling for all samples in the batch.
    batch_size*input_width results in different weight per each sample in the batch
 @param out_delta Pointer to the output delta descriptor
 @param out_delta_stride Increment (in values) between output deltas

 @return 0 on success, and -1 on failure.
*/
int BNNSLossFilterApplyBackwardBatch(BNNSFilter filter,
                                     size_t batch_size,
                                     const void * in,
                                     size_t in_stride,
                                     BNNSNDArrayDescriptor * in_delta,
                                     size_t in_delta_stride,
                                     const void * labels,
                                     size_t labels_stride,
                                     const void * _Nullable weights,
                                     size_t weights_size,
                                     const BNNSNDArrayDescriptor * out_delta,
                                     size_t out_delta_stride)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*! @abstract Applies a previously created multihead attention layer backwards to obtain gradients
 *
 *  @discussion
 *  Two common cases are that query=key=value or query=key. In these cases the backpropogated gradient for these parameters
 *  the gradient calculation is then the sum of the individual deltas. If any the pointers query_param_delta.target_desc.data,
 *  key_param_delta.target_desc.data or value_param_delta.target_desc.data are equal to each other, the returned tensor will
 *  be set correctly to the sum of the components.
 *
 *  @param F Filter to apply created by a previous call to BNNSFilterCreateLayerMultiheadAttention()
 *  @param batch_size Number of inputs in batch
 *  @param query Pointer to data for query input matrix, layout as described by layer_params->query.target_desc
 *  @param query_stride Batch stride for query
 *  @param query_param_delta Pointer to data structure used to hold deltas for corresponding components. A NULL value
 *         in a member's data component indicates that it should not be computed.
 *         The value query_param_delta.target_desc.stride[2] is used as the batch stride for query_param_delta.target_desc.
 *  @param key Pointer to data for key input matrix, layout as described by layer_params->key.target_desc
 *  @param key_stride Batch stride for key
 *  @param key_mask Mask applied to key for ignoring entries, layout as described in forward call.
 *         No mask is applied if this pointer is NULL.
 *  @param key_mask_stride Batch stride for key_mask
 *  @param key_param_delta Pointer to data structure used to hold deltas for corresponding components. A NULL value
 *         in a member's data component indicates that it should not be computed.
 *         The value key_param_delta.target_desc.stride[2] is used as the batch stride for key_param_delta.target_desc.
 *  @param value Pointer to data for value input matrix, layout as described by layer_params->value.target_desc
 *  @param value_stride Batch stride for value
 *  @param value_param_delta Pointer to data structure used to hold deltas for corresponding components. A NULL value
 *         in a member's data component indicates that it should not be computed.
 *         The value value_param_delta.target_desc.stride[2] is used as the batch stride for value_param_delta.target_desc.
 *  @param add_to_attention Optional, a 2D tensor of shape target_length x source_length that is used as part of the mask function prior
 *         to softmax in the attention calculation (the matrix X in the layer description). No matrix is added if this pointer is NULL.
 *  @param output Pointer to data for output matrix, , layout as described by layer_params->output.target_desc
 *  @param output_stride Batch stride for output.
 *  @param output_param_delta Pointer to data structure used to hold deltas for corresponding components. A NULL value
 *         in a member's data component indicates that it should not be computed.
 *         The value output_param_delta.target_desc.stride[2] is used as the batch stride for output_param_delta.target_desc.
 *  @param backprop_cache_size Specifies the size of the array backprop_cache, in bytes. If 0, or backprop_cache is NULL,
 *         backprop_cache is not accessed.
 *  @param backprop_cache Is used to store intermediate results that can be used to accelerate a future call to
 *         BNNSApplyMultiheadAttentionBackward.
 *  @param workspace_size Specifies the size of the array workspace, in bytes.
 *         If workspace_size is not-NULL but workspace is NULL, the recommended size for workspace_size
 *         will be set, but not other calculations will be performed (except to set backprop_cache_size if requested).
 *  @param workspace Is used as a scratch buffer during the calculation.
 */
int BNNSApplyMultiheadAttentionBackward(BNNSFilter F, size_t batch_size,
                                        void const * _Nullable query, size_t query_stride,
                                        BNNSMHAProjectionParameters * _Nullable query_param_delta,
                                        void const * _Nullable key, size_t key_stride,
                                        BNNSNDArrayDescriptor const* _Nullable key_mask, size_t key_mask_stride,
                                        BNNSMHAProjectionParameters * _Nullable key_param_delta,
                                        void const * _Nullable value, size_t value_stride,
                                        BNNSMHAProjectionParameters * _Nullable value_param_delta,
                                        BNNSNDArrayDescriptor const* _Nullable add_to_attention,
                                        BNNSNDArrayDescriptor * _Nullable key_attn_bias_delta,
                                        BNNSNDArrayDescriptor * _Nullable value_attn_bias_delta,
                                        void const * _Nullable output, size_t output_stride,
                                        BNNSMHAProjectionParameters * output_param_delta,
                                        size_t backprop_cache_size, void * _Nullable backprop_cache,
                                        size_t * _Nullable workspace_size, void * _Nullable workspace
                                        )
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

#pragma mark - Direct inference

/*!
 @abstract return the minimum bytes capacity of the training cache buffer (used to store intermediate results during the forward pass)
 @return minimum bytes capacity of the training cache buffer
 */
size_t BNNSComputeLSTMTrainingCacheCapacity(const BNNSLayerParametersLSTM * layer_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

 @abstract Direct Apply LSTM with training caching
 @discussion compute LSTM forward and cache intermediate results to accelerate backward computation
 - the user can query the minimum buffer size for training cache using BNNSComputeLSTMTrainingCacheCapacity
 - training_cache_ptr == NULL means not to cache
 - BNNS will return failure when training_cache_capacity is lower than the minimum bytes capacity of the training cache buffer that BNNSComputeLSTMTrainingCacheCapacity returned
 @param layer_params - layer parameters
 @param filter_params - filter parameters
 @param training_cache_ptr - buffer to store intermediate results to accelerate backward computation. if Null, intermediate results aren't cached
 @param training_cache_capacity - size in bytes of training_cache_ptr
 @return 0 on success, and -1 on failure.

 */
int BNNSDirectApplyLSTMBatchTrainingCaching(const BNNSLayerParametersLSTM * layer_params,
                                            const BNNSFilterParameters * _Nullable filter_params,
                                            void * _Nullable training_cache_ptr,
                                            const size_t training_cache_capacity)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

  @abstract Direct Apply an Activation/Conversion filter to several pairs of (input, output) data

  @discussion
  equal to calling BNNSCreateActivation & BNNSFilterApplyBatch & BNNSDestroy

  @param layer_params Layer parameters and input, weights, output, bias and activation descriptors
  should set i_desc.data pointing to input data and o_desc.data pointing to output data

  @param filter_params Filter runtime parameters, may be NULL for default parameters
  @param batch_size Number of (input, output) pairs to process
  @param in_stride Increment (in values) between inputs
  @param out_stride Increment (in values) between outputs

  @return 0 on success, and -1 on failure.

 */
int BNNSDirectApplyActivationBatch(const BNNSLayerParametersActivation * layer_params,
                                   const BNNSFilterParameters * _Nullable filter_params,
                                   size_t batch_size,
                                   size_t in_stride,
                                   size_t out_stride)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!

  @abstract Copies the contents of one BNNSNDArrayDescriptor to another of the same shape.
  @discussion
  Equivalent to using a contraction layer with opstring "src_* -> dest_*"

  @param dest The destination tensor
  @param src The source tensor - must not overlap in memory with the destination tensor

 */
int BNNSCopy(BNNSNDArrayDescriptor * dest,
             BNNSNDArrayDescriptor const * src,
             const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!
 * @abstract Directly apply a broadcast matrix multiplication layer.
 *
 * @description
 * Performs the same action as a broadcast matrix multiplication layer without instantiating a BNNSFilter.
 *
 * @param transA - if true, transposes the last two dimensions of A
 * @param transB - if true, transposes the last two dimensions of B
 * @param alpha - scalar by which to scale the result
 * @param inputA - descriptor for tensor A
 * @param inputB - descriptor for tensor B
 * @param output - descriptor for tensor C; on output only the data values are changed
 * @param filter_params - filter runtime parameters, may be NULL for default parameters
 */
void BNNSDirectApplyBroadcastMatMul(const bool transA,
                                    const bool transB,
                                    const float alpha,
                                    const BNNSNDArrayDescriptor * inputA,
                                    const BNNSNDArrayDescriptor * inputB,
                                    const BNNSNDArrayDescriptor * output,
                                    const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*! @abstract Transposes a tensor by swapping two of its dimensions.
 *
 *  @discussion
 *  Users should consider whether a data transposition with memory copy (i.e. this operation) is required, or if the same effect can be
 *  achieved by just switching layout in the descriptor of the same memory (e.g. for a 2D matrix can switching from row major to column
 *  major storage satsify the requirements). Consideration will be needed for both whether individual layers support alternative data
 *  layouts, and runtime performance.
 *
 *  This routine is not presented as a layer, but as a data manipulation. If deployed in a training scenario, observe that backpropagation
 *  can be achieved by applying exactly the same operation to the output delta as was applied to the original input.
 *
 *  This operation is equivalent to using the TensorContraction layer with operation string similar to "x_*ij -> y_*ji", only with the appropriate
 *  axes represented for the transposition.
 *
 *  In place operation is NOT supported.
 *
 *  @param dest Descriptor for the destination tensor
 *  @param src Descriptor for the source tensor
 *  @param axis0 First axis of transposition
 *  @param axis1 Second axis of transposition
 *  @param filter_params Filter runtime parameters, may be NULL for default parameters
 */
int BNNSTranspose(BNNSNDArrayDescriptor *dest,
                  const BNNSNDArrayDescriptor *src,
                  size_t axis0, size_t axis1,
                  const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!
  @abstract Apply Reduction on selected axis
 @param layer_params  Layer parameters: input descriptor, output descriptor, reduce function and epsilon
                      need to set the pointers:
                      layer_params.i_desc.data - pointer to input buffer
                      layer_params.o_desc.data - pointer to output buffer
                      layer_params.w_desc.data - pointer to weights buffer (set to NULL if not needed)
  @param filter_params Filter runtime parameters, may be NULL for default parameters
  @return 0 on success, and -1 on failure.
*/
int BNNSDirectApplyReduction(const BNNSLayerParametersReduction * layer_params,
                             const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!
 @abstract create and return a new tensor of bool type by comparing two input tensors

 @discussion
       compare two input tensors and generate a tensor of bool type containing the results of element-by-element comparison

 @param  in0  pointer to the tensor descriptor of type BNNSNDArrayDescriptor for comparison/logical operations - left side of the operator
 @param  in1  pointer to the tensor descriptor of type BNNSNDArrayDescriptor for comparison/logical operations - right side of the operator
 @param  op   type of comparison in BNNSRelationalOperator type
 @param  out  pointer to the tensor descriptor of type BNNSNDArrayDescriptor for the output of comparison.
             The active dimensions should match those of inA/inB, and the type should be BNNSDataTypeBoolean8.
 @return the error code of the processing - error only if I/O tensor descriptors have invalid or mismatching information
 */
int BNNSCompareTensor(const BNNSNDArrayDescriptor * in0, const BNNSNDArrayDescriptor * in1, BNNSRelationalOperator op, BNNSNDArrayDescriptor * out)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!
 @abstract Returns top K values
 @discussion
   Returns a sparse vector of the top K entries from the input.
   In the case of ties that span the top-K boundary, only the lexigraphically first entries will be returned.
 @param K Number of entries to find
 @param axis Axis along which to find top K entries
 @param batch_size Number of batches
 @param input The input tensor
 @param input_batch_stride The batch stride for input.data
 @param best_values Descriptor of a K-length vector. On return contains the K best values in descending order.
 @param best_values_batch_stride The batch stride for best_values
 @param best_indices Descriptor of a K-length vector. On return contains the indices of the K best values in descending order.
 @param best_indices_batch_stride The batch stride in size_t elements for best_indices
 @param filter_params Filter runtime parameters, may be NULL for default parameters
 @return Zero on success, non-zero on failure.
 */
int BNNSDirectApplyTopK(size_t K, size_t axis, size_t batch_size,
                        const BNNSNDArrayDescriptor *input, size_t input_batch_stride,
                        BNNSNDArrayDescriptor *best_values, size_t best_values_batch_stride,
                        BNNSNDArrayDescriptor *best_indices, size_t best_indices_batch_stride,
                        const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!
 @abstract Given a tensor index for each member of a batch, returns a boolean vector indicating whether each index
            corresponds to a top-k value of the input.
 @discussion
  Consider the 4x4 tensor in a batch size of 3:
    X(:,:,0) = [ 1 3 5 7 ]         X(:,:,1) = [ 1 8 3 4 ]         X(:,:,2) = [ 4 8 7 7 ]
           [ 2 5 1 9 ]                       [ 8 1 3 5 ]                        [ 4 3 8 5 ]
           [ 1 5 3 2 ]                       [ 1 7 2 3 ]                        [ 5 7 3 1 ]
  and the test indices:
    T(:, 0) = (0, 3, 1)
    T(:, 1) = (2, 2, 0)
    T(:, 2) = (3, 2, 1)
  with K= 2 and axis=1, the result would be:
     (F, F, T)      from comparing values (1, 1, 5) against the top K sets (5, 7), (5, 9), (3,5) in the first batch
     (F, F, F)      from comparing values (3, 3, 1) against the top K set (4, 8), (5, 8), (3,7) in the second batch
     (T, T, T)      from comparing values (7, 8, 7) against the top K set (7, 8), (5, 8), (5, 7) in the third batch
  Observe that in the case of ties, all possible entries are included in the top K.
 @param K Number of entries to find
 @param axis Axis along which to find top K entries
 @param batch_size Number of batches
 @param input The input tensor
 @param input_batch_stride The batch stride for input.data
 @param test_indices Test index tensor, shape must match that of input, with the given axis removed
 @param test_indices_batch_stride The batch stride for test_indices.data
 @param output The boolean output tensor
 @param output_batch_stride The batch stride for output.data, of shape matching test_indices
 @param filter_params Filter runtime parameters, may be NULL for default parameters
 @return Zero on success, non-zero on failure.
 */
int BNNSDirectApplyInTopK(size_t K, size_t axis, size_t batch_size,
                          const BNNSNDArrayDescriptor *input, size_t input_batch_stride,
                          const BNNSNDArrayDescriptor *test_indices, size_t test_indices_batch_stride,
                          BNNSNDArrayDescriptor *output, size_t output_batch_stride,
                          const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));


#pragma mark - Direct Apply Backward

/*!
 @abstract Direct Apply LSTM with training caching
 @discussion compute LSTM backward
 @param layer_params - layer parameters
 @param layer_delta_params - layer delta parameters (include inputs & outputs for backward)
 @param filter_params - filter parameters
 @param training_cache_ptr - buffer with intermediate results to accelerate backward computation. if Null, intermediate results weren't cached and forward pass will be recomupted
 @param training_cache_capacity - size in bytes of training_cache_ptr. return failure when training_cache_capacity is lower than the minimum bytes capacity of the training cache
 @return 0 on success, and -1 on failure.
*/
int BNNSDirectApplyLSTMBatchBackward(const BNNSLayerParametersLSTM * layer_params,
                                     const BNNSLayerParametersLSTM * layer_delta_params,
                                     const BNNSFilterParameters * _Nullable filter_params,
                                     const void * _Nullable training_cache_ptr,
                                     const size_t training_cache_capacity)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

#pragma mark - Utility

/*!
 @abstract Get NDArray descriptor containing reference to filter data member

 @discussion
 Some filters have potentially trainiable parameters embedded in the filter structure (for example activation layers often have an alpha or beta parameter).
 To facilitate training or otherwise modifying these parameters after layer creation, we provide the following function.
 Note that the pointer is only valid until the BNNSFilter is destroyed, and that care must be taken if the filter is used on multiple threads.

 @param filter Filter to obtain pointer into
 @param target enum specifying what a pointer is required to

 @returns On success, a BNNSNDArrayDescriptor describing the requested parameter.
          On failure, a BNNSNDArrayDescriptor with data member set to NULL.
 */
BNNSNDArrayDescriptor BNNSGetPointer(BNNSFilter filter, BNNSPointerSpecifier target)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

#pragma mark - Deprecated Filter Creation Functions

/*!

 @abstract Create a convolution layer filter (DEPRECATED,  Use BNNSFilterCreateLayerConvolution)

 @discussion
 Creates a filter applying the convolution described in <tt>layer_params</tt>.
 Some combinations of the parameters may not be supported, in which case the call will fail.

 @param in_desc Input image stack descriptor
 @param out_desc Output image stack descriptor
 @param layer_params Layer parameters and weights
 @param filter_params Filter runtime parameters, may be NULL for default parameters

 @return A new non-NULL filter on success, and NULL on failure.

 */
BNNSFilter BNNSFilterCreateConvolutionLayer(const BNNSImageStackDescriptor * in_desc,
                                            const BNNSImageStackDescriptor * out_desc,
                                            const BNNSConvolutionLayerParameters * layer_params,
                                            const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED_WITH_REPLACEMENT("BNNSFilterCreateLayerConvolution", macos(10.12, 11.0), ios(10.0, 14.0), watchos(3.0, 7.0), tvos(10.0, 14.0));

/*!

 @abstract Create a fully connected layer filter (DEPRECATED,  Use BNNSFilterCreateLayerFullyConnected)

 @discussion
 Creates a filter applying the fully connected layer described in <tt>layer_params</tt>.
 Some combinations of the parameters may not be supported, in which case the call will fail.

 @param in_desc Input vector descriptor
 @param out_desc Output vector descriptor
 @param layer_params Layer parameters and weights
 @param filter_params Filter runtime parameters, may be NULL for default parameters

 @return A new non-NULL filter on success, and NULL on failure.

 */
BNNSFilter BNNSFilterCreateFullyConnectedLayer(const BNNSVectorDescriptor * in_desc,
                                               const BNNSVectorDescriptor * out_desc,
                                               const BNNSFullyConnectedLayerParameters * layer_params,
                                               const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED_WITH_REPLACEMENT("BNNSFilterCreateLayerFullyConnected", macos(10.12, 11.0), ios(10.0, 14.0), watchos(3.0, 7.0), tvos(10.0, 14.0));

/*!

 @abstract Create a pooling layer filter (DEPRECATED,  Use BNNSFilterCreateLayerPooling)

 @discussion
 Creates a filter applying the pooling layer described in <tt>layer_params</tt>
 Some combinations of the parameters may not be supported, in which case the call will fail.

 @param in_desc Input image stack descriptor
 @param out_desc Output image stack descriptor
 @param layer_params Layer parameters and weights
 @param filter_params Filter runtime parameters, may be NULL for default parameters

 @return A new non-NULL filter on success, and NULL on failure.

 */
BNNSFilter BNNSFilterCreatePoolingLayer(const BNNSImageStackDescriptor * in_desc,
                                        const BNNSImageStackDescriptor * out_desc,
                                        const BNNSPoolingLayerParameters * layer_params,
                                        const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED_WITH_REPLACEMENT("BNNSFilterCreateLayerPooling", macos(10.12, 11.0), ios(10.0, 14.0), watchos(3.0, 7.0), tvos(10.0, 14.0));

/*!

 @abstract Create a vector conversion/activation layer filter (DEPRECATED,  Use BNNSFilterCreateLayerActivation)

 @discussion
 Creates a filter applying the given activation function and conversions to vectors. Input and output vectors must have the same size.

 @param in_desc Input vector descriptor
 @param out_desc Output vector descriptor
 @param activation Activation function to apply and its parameters
 @param filter_params Filter runtime parameters, may be NULL for default parameters

 @return A new non-NULL filter on success, and NULL on failure.

 */
BNNSFilter BNNSFilterCreateVectorActivationLayer(const BNNSVectorDescriptor * in_desc,
                                                 const BNNSVectorDescriptor * out_desc,
                                                 const BNNSActivation * activation,
                                                 const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED_WITH_REPLACEMENT("BNNSFilterCreateLayerActivation", macos(10.13, 11.0), ios(11.0, 14.0), watchos(4.0, 7.0), tvos(11.0, 14.0));

#if !__has_include( <Availability.h> )
#undef __API_AVAILABLE
#undef __API_DEPRECATED_WITH_REPLACEMENT
#endif

#if __has_feature(assume_nonnull)
  _Pragma("clang assume_nonnull end")
#else
#undef _Nullable
#undef _Null_unspecified
#undef _Nonnull
#endif

#ifdef __cplusplus
}
#endif


#endif // __BNNS_HEADER__
