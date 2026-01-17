// Basic Neural Network Subroutines (BNNS)

#ifndef __BNNS_HEADER__
#define __BNNS_HEADER__

#if __has_include( <TargetConditionals.h> )
#include <TargetConditionals.h>
#endif // __has_include( <TargetConditionals.h> )

#include "bnns_constants.h"
#include "bnns_structures.h"
#include "bnns_graph.h"

#include <sys/types.h>

#if __has_include( <Availability.h> )
#include <Availability.h>
#else // __has_include( <Availability.h> )
#define __API_AVAILABLE(...)
#define __API_DEPRECATED(...)
#define __API_DEPRECATED_WITH_REPLACEMENT(...)
#endif // __has_include( <Availability.h> )

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
typedef void * _Nullable BNNSFilter
__API_DEPRECATED("Use BNNSGraph* APIs", macos(10.12, 15.0), ios(10.0, 18.0), watchos(3.0, 11.0), tvos(10.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

#if !0

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

#endif 

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

#if !0

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

#endif 

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

#if !0

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

#endif 

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

#if !0

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

/*!

  @abstract Create a fused filter

  @discussion
  Create an N layer fused filter that process input in the following way: input -> filter0 -> filter1 -> ... -> filter N-1 -> output
  first N-1 filters must have activation function BNNSActivationFunctionIdentity in training.
  last filter may have a different activation function. gradient computation restrictions on last activation function are the same as in BNNSFilterApplyBackwardBatch.
  For K between 0 and N-2, the K filter output descriptor and the K+1 filter input descriptor  must have the same sizes, strides and data type.

  Initial implementation support fusing 2 filters in the following configurations:
  Configuration 1: Convolution -> Normalization
  filter0 is convolution and filter1 is normalization. for example, the filter_type and layer_params arrays when using batchnorm should be as follows:
  filter_type: [BNNSConvolution, BNNSBatchNorm]
  layer_params: [pointer to BNNSLayerParametersConvolution, pointer to BNNSLayerParametersNormalization]

  Configuration 2: FullyConnected -> Normalization
  filter0 is fully connected and filter1 is normalization. for example, the filter_type and layer_params arrays when using batchnorm should be as follows:
  filter_type: [BNNSFullyConnected, BNNSBatchNorm]
  layer_params: [pointer to BNNSLayerParametersFullyConnected, pointer to BNNSLayerParametersNormalization]

  Configuration 3: Transposed Convolution -> Normalization
  filter0 is transposed convolution and filter1 is normalization. for example, the filter_type and layer_params arrays when using batchnorm should be as follows:
  filter_type: [BNNSTransposedConvolution, BNNSBatchNorm]
  layer_params: [pointer to BNNSLayerParametersConvolution, pointer to BNNSLayerParametersNormalization]

  Configuration 4: Convolution -> Quantization
  filter0 is convolution and filter1 is quantization. The filter_type and layer_params arrays should be as follows:
  filter_type: [BNNSConvolution, BNNSQuantization]
  layer_params: [pointer to BNNSLayerParametersConvolution, pointer to BNNSLayerParametersQuantization]
  input and output descriptor data pointers in BNNSLayerParametersQuantization are ignored
  Note that if the quantization layer uses batch as an axis with scale and/or bias, the batch size is encoded in the quantization layer parameters. In this case, if the batch size changes, the filter must be destroyed and recreated.
 
  Configuration 5: FullyConnected -> Quantization
  filter0 is fully connected and filter1 is quantization. The filter_type and layer_params arrays should be as follows:
  filter_type: [BNNSFullyConnected, BNNSQuantization]
  layer_params: [pointer to BNNSLayerParametersFullyConnected, pointer to BNNSLayerParametersQuantization]
  input and output descriptor data pointers in BNNSLayerParametersQuantization are ignored
  Note that if the quantization layer uses batch as an axis with scale and/or bias, the batch size is encoded in the quantization layer parameters. In this case, if the batch size changes, the filter must be destroyed and recreated.
 
  Configuration 6: Transposed Convolution -> Quantization
  filter0 is transposed convolution and filter1 is quantization. The filter_type and layer_params arrays should be as follows:
  filter_type: [BNNSTransposedConvolution, BNNSQuantization]
  layer_params: [pointer to BNNSLayerParametersConvolution, pointer to BNNSLayerParametersQuantization]
  input and output descriptor data pointers in BNNSLayerParametersQuantization are ignored
  Note that if the quantization layer uses batch as an axis with scale and/or bias, the batch size is encoded in the quantization layer parameters. In this case, if the batch size changes, the filter must be destroyed and recreated.
 
  Configuration 7: Arithmetic -> Normalization
  filter0 is arithmetic and filter1 is normalization. for example, the filter_type and layer_params arrays when using batchnorm should be as follows:
  filter_type: [BNNSArithmetic, BNNSBatchNorm]
  layer_params: [pointer to BNNSLayerParametersArithmetic, pointer to BNNSLayerParametersNormalization]

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

/*! @abstract Create an embedding layer
 *
 *  @discussion
 *  See the description of BNNSLayerParametersEmbedding for a full explanation of this layer.
 *
 *  @seealso BNNSLayerParametersEmbedding
 *
 *  @param layer_params layer description
 *  @param filter_params Filter runtime parameters, may be NULL for default parameters
 *  @return A new non-NULL filter on success, and NULL on failure.
 */
BNNSFilter BNNSFilterCreateLayerEmbedding(const BNNSLayerParametersEmbedding * layer_params,
                                          const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(12.0, 15.0), ios(15.0, 18.0), watchos(8.0, 11.0), tvos(15.0, 18.0));

#endif 

#pragma mark - Inference

/*!
  @abstract Apply a filter

  @param filter Filter to apply
  @param in Pointer to the input data
  @param out Pointer to the output data

  @return 0 on success, and -1 on failure.
 */
int BNNSFilterApply(BNNSFilter filter, const void * in, void * out)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(10.12, 15.0), ios(10.0, 18.0), watchos(3.0, 11.0), tvos(10.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(10.12, 15.0), ios(10.0, 18.0), watchos(3.0, 11.0), tvos(10.0, 18.0));

#if !0

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

/*!
 @abstract Applies a previously created pooling layer filter, supporting multiple index data types

 @discussion
 The only difference between this function and BNNSPoolingFilterApplyBatch is that
 BNNSPoolingFilterApplyBatch requires indices to be size_t,
 while BNNSPoolingFilterApplyBatchEx allows indices to have various types.
 Currently, only uint64_t and uint32_t are allowed for indices.
 
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
int BNNSPoolingFilterApplyBatchEx(BNNSFilter filter, size_t batch_size,
                                  const void * _Nonnull in, size_t in_stride,
                                  void * _Nonnull out, size_t out_stride,
                                  const BNNSDataType indices_data_type, void * _Nullable indices, size_t idx_stride)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));

#endif 

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

#if !0

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
 -see training flag information in BNNSNormalizationFilterApplyBatch

 @return 0 on success, and -1 on failure.

 */

int BNNSFusedFilterApplyBatch(BNNSFilter filter,
                              size_t batch_size,
                              const void * in,
                              size_t in_stride,
                              void * out,
                              size_t out_stride,
                              bool training)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

/*!

 @abstract Apply a fused filter to several pairs of (input set, output) data

 @discussion
 The filter is applied for each of the <tt>batch_size</tt> input set, and produces <tt>batch_size</tt> outputs.
 <tt>in</tt> (resp. <tt>out</tt>) is expected to point to <tt>batch_size</tt> times the input (resp. output) object size defined when the filter was created.

 Currently only fused arithmetic -> normalization configuration is supported.

 @param filter Filter to apply
 @param batch_size Number of (input sets, output) pairs to process
 @param number_of_inputs number of inputs for the arithmetic operation
 @param in pointer to an array of input pointers. in array size must be number_of_inputs.
 @param in_stride pointer to an array of input strides, each stride is an Increment (in values) between inputs in the batch for a corresponding input in the in array.
 @param out Pointer to the output data
 @param out_stride Increment (in values) between outputs
 @param training true if training, false if inference
 -ignored if none of the filters is batchnorm
 -see training flag information in BNNSNormalizationFilterApplyBatch

 @return 0 on success, and -1 on failure.

 */

int BNNSFusedFilterApplyMultiInputBatch(BNNSFilter filter,
                                        size_t batch_size,
                                        size_t number_of_inputs,
                                        const void * _Nonnull * _Nonnull in,
                                        const size_t *_Nonnull in_stride,
                                        void * _Nonnull out,
                                        size_t out_stride,
                                        bool training)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(12.0, 15.0), ios(15.0, 18.0), watchos(8.0, 11.0), tvos(15.0, 18.0));

#endif 

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

#if !0

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
 *  @param add_to_attention Optional, one of:
 *         1) a 2D tensor of shape target_length x source_length; or
 *         2) a 3D tensor of shape num_heads x target_length x source_length; or
 *         3) a 4D tensor of shape batch_size x num_heads x target_length x source_length.
 *         This is used as part of the mask function prior to softmax in the attention calculation (the matrix X in the layer description).
 *         If the data type is BNNSDataTypeBoolean, true is treated as adding -inf, and false as adding zero (that is to say attention
 *         is not permitted in locations indicated by the the mask).
 *         No matrix is added if this pointer is NULL.
 *         Note: The 3D, 4D and BNNSDataTypeBoolean variants of this parameter are only supported in macOS 12.0, iOS 15.0,
 *         watchOS 8.0, tvOS 15.0 and later.
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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

/*!
 @abstract Direct Apply a Quantization filter

 @discussion
 The Quantization layer converts higher precision tensors to lower precision tensors (Quantize) or lower precision tensors to higher precision tensors (Dequantize)
 
 @param layer_params Quantizer layer parameters
 @param filter_params Filter runtime parameters, may be NULL for default parameters
 @param batch_size Number of (input, output) pairs to process
 @param input_stride Increment (in values) between inputs
 @param output_stride Increment (in values) between outputs
 @return Zero on success, nonzero on failure.
 */
int BNNSDirectApplyQuantizer(const BNNSLayerParametersQuantization * layer_params,
                             const BNNSFilterParameters * _Nullable filter_params,
                             size_t batch_size,
                             size_t input_stride,
                             size_t output_stride)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(12.0, 15.0), ios(15.0, 18.0), watchos(8.0, 11.0), tvos(15.0, 18.0));

#endif 

#pragma mark - Filter destruction

/*!

  @abstract Destroy filter

  @discussion Releases all resources allocated for this filter.

  @param filter Filter to destroy

*/
void BNNSFilterDestroy(BNNSFilter filter)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(10.12, 15.0), ios(10.0, 18.0), watchos(3.0, 11.0), tvos(10.0, 18.0));

#pragma mark - Training

#if !0

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

  BNNSOptimizerFunctionAdamAMSGrad
  ===============================
  Set to a size 3*number_of_parameters array.
  The first number_of_parameters pointers are used for the first momentum descriptors, the second number_of_parameters pointers are used for the second  momentum descriptors, and the third number_of_parameters pointers are used for the second momentum maxima descriptors.

  BNNSOptimizerFunctionAdamW
  ========================
  Set to a size 2*number_of_parameters array.
  The first number_of_parameters pointers are used for the first momentum descriptors, and the subsequent number_of_parameters ointers are used for the second  momentum descriptors.

  BNNSOptimizerFunctionAdamWAMSGrad
  ===============================
  Set to a size 3*number_of_parameters array.
  The first number_of_parameters pointers are used for the first momentum descriptors, the second number_of_parameters pointers are used for the second  momentum descriptors, and the third number_of_parameters pointers are used for the second momentum maxima descriptors.

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

  @returns 0 on success, nonzero on failure
*/
int BNNSOptimizerStep(BNNSOptimizerFunction function, const void *OptimizerAlgFields,
                      size_t number_of_parameters,
                      BNNSNDArrayDescriptor *_Nonnull *_Nonnull parameters,
                      const BNNSNDArrayDescriptor *_Nonnull *_Nonnull gradients,
                      BNNSNDArrayDescriptor * _Nullable * _Nullable accumulators,
                      const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

/*!

 @abstract Clip tensor values to a specified min and max

 @discussion
 Given a tensor src, this operation writes to a tensor dest of the same type and shape as src with its values clipped to min_val and max_val.

 @param dest descriptor for the destination tensor
 @param src descriptor for the source tensor, must be of the same type and shape as the dest descriptor.
 @param min_val The minimum value.
 @param max_val The maximum value.

 @returns 0 on success, nonzero on failure
 */
int BNNSClipByValue(BNNSNDArrayDescriptor * _Nonnull dest,
                    const BNNSNDArrayDescriptor * _Nonnull src,
                    float min_val, float max_val)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(12.0, 15.0), ios(15.0, 18.0), watchos(8.0, 11.0), tvos(15.0, 18.0));

/*!

 @abstract Clip tensor values to a maximum L2-norm.

 @discussion
 Given a tensor src, this operation writes to a tensor dest of the same type and shape as src with its values clipped such that the L2-norm does not
 exceed max_norm.

 @param dest descriptor for the destination tensor
 @param src descriptor for the source tensor, must be of the same type and shape as the dest descriptor.
 @param max_norm The maximum L2-norm.
 @param axis_flags The dimensions to use for computing the L2-norm. If 0, uses all dimensions.

 @returns 0 on success, nonzero on failure
 */
int BNNSClipByNorm(BNNSNDArrayDescriptor * _Nonnull dest,
                   const BNNSNDArrayDescriptor * _Nonnull src,
                   float max_norm,
                   uint32_t axis_flags)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(12.0, 15.0), ios(15.0, 18.0), watchos(8.0, 11.0), tvos(15.0, 18.0));

/*!

 @abstract Clip values of a list of tensors by a maximum global L2-norm.

 @discussion
 Given a list of tensors src, and a maximum global L2-norm, max_norm, this operation computes a list of clipped tensors.
 If you already know the global norm of src, you can specify the global norm to use with use_norm.

 @param dest array of destination tensor descriptors
 @param src array of source tensor descriptors. Each descriptor data in the array must be the same size as its matching dest descriptor in the dest array.
 @param count number of descriptors in the dest and src arrays
 @param max_norm maximum global L2-norm
 @param use_norm The global norm to use. If zero, global norm is computed based on src.

 @returns 0 on success, nonzero on failure
 */
int BNNSClipByGlobalNorm(BNNSNDArrayDescriptor * _Nonnull * _Nonnull dest,
                         const BNNSNDArrayDescriptor * _Nonnull * _Nonnull src,
                         size_t count,
                         float max_norm,
                         float use_norm)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(12.0, 15.0), ios(15.0, 18.0), watchos(8.0, 11.0), tvos(15.0, 18.0));

/*!

 @abstract Compute the norm of the input tensor.

 @discussion
 Given a tensor src, this operation compute its specified norm along the specified axes.

 @param dest descriptor for the destination tensor. The dimensions in axis_flags are removed from the destination shape.
        If axis_flags specifies all dimensions, destination descriptor must be BNNSDataLayoutVector with size[0] = 1.
 @param src descriptor for the source tensor.
 @param norm_type Type of the norm. Currently only L2-norm is supported.
 @param axis_flags The dimensions to use for computing the L2-norm. If 0, uses all dimensions.

 @returns 0 on success, nonzero on failure
 */
int BNNSComputeNorm(BNNSNDArrayDescriptor * _Nonnull dest,
                    const BNNSNDArrayDescriptor * _Nonnull src,
                    BNNSNormType norm_type,
                    uint32_t axis_flags)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(12.0, 15.0), ios(15.0, 18.0), watchos(8.0, 11.0), tvos(15.0, 18.0));

/*!

 @abstract Backward path of norm computation to generate input delta.

 @discussion
 The backward computation uses the output delta (dy) and the forward pass input (x) and output (y) to generate the input delta (dx).

 @param in Pointer to the forward pass input data
 @param in_delta Pointer to the input delta descriptor
 @param out Pointer to the forward pass output data
 @param out_delta Pointer to the output delta descriptor
 @param norm_type Type of the norm. Currently only L2-norm is supported.
 @param axis_flags The dimensions to use for computing the L2-norm. If 0, uses all dimensions.

 @returns 0 on success, nonzero on failure
 */
int BNNSComputeNormBackward(const void * _Nonnull in,
                            BNNSNDArrayDescriptor * _Nonnull in_delta,
                            const void * _Nonnull out,
                            const BNNSNDArrayDescriptor * _Nonnull out_delta,
                            BNNSNormType norm_type,
                            uint32_t axis_flags)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(12.0, 15.0), ios(15.0, 18.0), watchos(8.0, 11.0), tvos(15.0, 18.0));

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
 BNNSActivationFunctionGELUApproximationSigmoid

 The activation functions above can be fused with computation in training, only if the forward pass output y is provided in backward apply.

 Other activation functions require forward pass input and does not support fusing computation with activation, such as:
 BNNSActivationFunctionAbs
 BNNSActivationFunctionGELUApproximation
 BNNSActivationFunctionGELUApproximation2
 BNNSActivationFunctionSiLU

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

/*!

 @abstract Apply pooling filter backward to generate input delta and bias delta, supporting multiple index data types

 @discussion
 The only difference between this function and BNNSPoolingFilterApplyBackwardBatch is that
 BNNSPoolingFilterApplyBackwardBatch requires indices to be size_t,
 while BNNSPoolingFilterApplyBackwardBatchEx allows indices to have various types.
 Currently, only uint64_t and uint32_t are allowed for indices.

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
 @param indices_data_type Data type of indices data
 @param indices Pointer to the forward pass indices data generated by max pooling.
 - max pooling could use indices to reduce computation if not null. indices must have the same dimension and stride as the output data.
 - max unpooling requires a valid pointer. indices must have the same dimension and stride as the input data.
 - ignored for other pooling functions
 @param idx_stride Increment (in values) between indices
 @return 0 on success, and -1 on failure.
 */
int BNNSPoolingFilterApplyBackwardBatchEx(BNNSFilter filter,
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
                                          const BNNSDataType indices_data_type,
                                          const void * _Nullable indices,
                                          size_t idx_stride)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));

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
 BNNSActivationFunctionGELUApproximationSigmoid

 The activation functions above can be fused with computation in training, only if the forward pass output y is provided in backward apply.

 Other activation functions require forward pass input and does not support fusing computation with activation, such as:
 BNNSActivationFunctionAbs
 BNNSActivationFunctionGELUApproximation
 BNNSActivationFunctionGELUApproximation2
 BNNSActivationFunctionSiLU

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

/*!

 @abstract Apply a normalization filter backward to generate input delta, beta delta and gamma delta

 @discussion
 similar to BNNSFilterApplyBackwardBatch, but computing input delta, beta delta and gamma delta
 It is mandatory to compute all active gradients in a single function call. computation of input delta is not required in case the filter is the first layer in the network

 @param filter Filter to apply backward
 @param batch_size Number of (input, output) pairs to process
 @param in_delta Pointer to the input delta descriptor
 - not produced if null
 - must be in BNNSDataTypeFloat32 or BNNSDataTypeBFloat16
 @param in_delta_stride Increment (in values) between input deltas
 @param out Pointer to the forward pass output data (y)
 - out is ignored if activation is BNNSActivationFunctionIdentity
 - forward pass output must be provided in case of fused instance normalization and activation
 @param out_stride Increment (in values) between outputs
 @param out_delta Pointer to the output delta descriptor (dy)
 - out delta may be modified in order to save memory allocations when computing fused activation backward
 - must be in BNNSDataTypeFloat32 or BNNSDataTypeBFloat16
 @param out_delta_stride Increment (in values) between output deltas
 @param beta_delta Pointer to the beta delta descriptor
 - not produced if null
 - must be in BNNSDataTypeFloat32 or BNNSDataTypeBFloat16
 @param gamma_delta Pointer to the gamma delta descriptor
 - not produced if null
 - must be in BNNSDataTypeFloat32 or BNNSDataTypeBFloat16
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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
  BNNSNDArrayDescriptor* beta_delta = delta_parameters[2]; //first batchnorm parameter in BNNSNormalizationFilterApplyBackwardBatch
  BNNSNDArrayDescriptor* gamma_delta = delta_parameters[3]; //second batchnorm parameter in BNNSNormalizationFilterApplyBackwardBatch

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

/*!

 @abstract Apply a fused filter backward to generate gradients.

 @discussion
 similar to BNNSFilterApplyBackwardBatch, but computing gradients of a fused filter.
 It is mandatory to compute all active parameter delta in a single function call. computation of input delta is not required in case the fused filter is the first layer in the network

 Currently only fused arithmetic -> normalization configuration is supported.

 @param filter Filter to apply backward
 @param batch_size Number of (input sets, output) pairs to process
 @param number_of_inputs number of inputs for the arithmetic operation
 @param in pointer to an array of input pointers. in array size must be number_of_inputs.
 @param in_stride pointer to an array of input strides, each stride is an Increment (in values) between inputs in the batch for a corresponding input in the in array.
 @param in_delta pointer to an array of input delta pointers. in array size must be number_of_inputs.
 @param in_delta_stride pointer to an array of input delta strides, each stride is an Increment (in values) between inputs deltas in the batch for a corresponding input in the in_delta array.
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
 for example, if first filter is arithmetic and second filter is batchnorm, parameters could be extracted in the following way:
 BNNSNDArrayDescriptor* beta_delta = delta_parameters[0]; //first batchnorm parameter in BNNSNormalizationFilterApplyBackwardBatch
 BNNSNDArrayDescriptor* gamma_delta = delta_parameters[1]; //second batchnorm parameter in BNNSNormalizationFilterApplyBackwardBatch

 @return 0 on success, and -1 on failure.
 */
int BNNSFusedFilterApplyBackwardMultiInputBatch(BNNSFilter filter,
                                                size_t batch_size,
                                                size_t number_of_inputs,
                                                const void * _Nullable * _Nullable in,
                                                const size_t * _Nullable in_stride,
                                                BNNSNDArrayDescriptor * _Nonnull * _Nonnull in_delta,
                                                const size_t * _Nonnull in_delta_stride,
                                                const void * _Nullable out,
                                                const size_t out_stride,
                                                BNNSNDArrayDescriptor * _Nonnull out_delta,
                                                size_t out_delta_stride,
                                                BNNSNDArrayDescriptor * _Nullable * _Nullable delta_parameters)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(12.0, 15.0), ios(15.0, 18.0), watchos(8.0, 11.0), tvos(15.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

#pragma mark - Direct inference

/*!
 @abstract return the minimum bytes capacity of the training cache buffer (used to store intermediate results during the forward pass)
 @return minimum bytes capacity of the training cache buffer
 */
size_t BNNSComputeLSTMTrainingCacheCapacity(const BNNSLayerParametersLSTM * layer_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

#endif 

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

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

#if !0

/*!
 * @abstract Returns required workspace size for a call to BNNSMatMul() with the given paramters.
 *
 * @discussion
 * This routine does not access the data pointers on the array descriptors, so they need not point to actual data.
 *
 * @param transA - if true, transposes the last two dimensions of A
 * @param transB - if true, transposes the last two dimensions of B
 * @param alpha - scalar by which to scale the result
 * @param inputA - descriptor for tensor A
 * @param inputB - descriptor for tensor B
 * @param output - descriptor for tensor C
 * @param filter_params - filter runtime parameters, may be NULL for default parameters
 *
 * @returns Required allocation size for workspace paramter to BNNSMatMul, in bytes.
 *          If parameters are invalid, a negative value is returned.
 */
ssize_t BNNSMatMulWorkspaceSize(const bool transA,
                                const bool transB,
                                const float alpha,
                                const BNNSNDArrayDescriptor * inputA,
                                const BNNSNDArrayDescriptor * inputB,
                                const BNNSNDArrayDescriptor * output,
                                const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));

/*!
 * @abstract Directly apply a broadcast matrix multiplication layer.
 *
 * @discussion
 * This routine performs to operation C = alpha * op(A) * op(B), with approriate broadcasting if dimensions are absent on one
 * or more matrices. Matrix multiplication is always on the final two indices of each operand. For example, if we have
 * A is 4x5x6
 * B is 6x7
 * C is 4x5x7
 * Then the operation performed (if transA=transB=false) is:
 *  c_pij = sum_k a_pik * b_kj
 * Noting that the matrix B has been broadcast in the p dimension
 *
 * Performs the same action as a broadcast matrix multiplication layer without instantiating a BNNSFilter.
 * This function replaces the deprecated BNNSDirectApplyBroadcastMatMul and allows explicit provision
 * of workspace memory. If workspace is not null, no allocation is performed internally.
 *
 * @param transA - if true, transposes the last two dimensions of A
 * @param transB - if true, transposes the last two dimensions of B
 * @param alpha - scalar by which to scale the result
 * @param inputA - descriptor for tensor A
 * @param inputB - descriptor for tensor B
 * @param output - descriptor for tensor C; on output only the data values are changed
 * @param workspace - pointer to memory region to be used as scratch. Must have size no less than
 *        the value returned by BNNSMatMulWorkspaceSize
 * @param filter_params - filter runtime parameters, may be NULL for default parameters
 *
 * @returns 0 on success, non-zero on failure
 */
int BNNSMatMul(const bool transA,
               const bool transB,
               const float alpha,
               const BNNSNDArrayDescriptor * inputA,
               const BNNSNDArrayDescriptor * inputB,
               const BNNSNDArrayDescriptor * output,
               void * _Nullable workspace,
               const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));

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
__API_DEPRECATED_WITH_REPLACEMENT("BNNSMatMul", macos(11.0, 13.0), ios(14.0, 16.0), watchos(7.0, 9.0), tvos(14.0, 16.0));

#endif 

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

#if !0

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

/*!
 @abstract return a new tensor by replicating the input tensor multiple times
 
 @discussion
   The size of output tensor along each dimension should be a multiple of input tensor,
   and the multiple is the number of repetition.

 @param input Pointer to the input tensor descriptor
 @param output Pointer to the output tensor descriptor
 @param filter_params Filter runtime parameters, may be NULL for default parameters
 @return Zero on success, nonzero on failure.
 */
int BNNSTile(const BNNSNDArrayDescriptor *_Nonnull input,
             BNNSNDArrayDescriptor *_Nonnull output,
             const BNNSFilterParameters *_Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));


/*!
 @abstract Returns top K values
 @discussion
   Returns a sparse vector of the top K entries from the input.
   In the case of ties that span the top-K boundary, only the lexigraphically first entries will be returned.
   Nullability of best_indices is changed to allow passing null pointer.
 @param K Number of entries to find
 @param axis Axis along which to find top K entries
 @param batch_size Number of batches
 @param input The input tensor
 @param input_batch_stride The batch stride for input.data
 @param best_values Descriptor of a K-length vector. On return contains the K best values in descending order.
 @param best_values_batch_stride The batch stride for best_values
 @param best_indices Descriptor of a K-length vector. On return contains the indices of the K best values in descending order.  (set to NULL if not needed)
 @param best_indices_batch_stride The batch stride in size_t elements for best_indices
 @param filter_params Filter runtime parameters, may be NULL for default parameters
 @return Zero on success, nonzero on failure.
 */
int BNNSDirectApplyTopK(size_t K, size_t axis, size_t batch_size,
                        const BNNSNDArrayDescriptor *input, size_t input_batch_stride,
                        BNNSNDArrayDescriptor *best_values, size_t best_values_batch_stride,
#if       __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_13_0   || \
        __IPHONE_OS_VERSION_MIN_REQUIRED >= __IPHONE_16_0 || \
         __WATCH_OS_VERSION_MIN_REQUIRED >= __WATCHOS_9_0 || \
            __TV_OS_VERSION_MIN_REQUIRED >= __TVOS_16_0
                        BNNSNDArrayDescriptor *_Nullable best_indices, size_t best_indices_batch_stride,
#else
                        BNNSNDArrayDescriptor *best_indices, size_t best_indices_batch_stride,
#endif
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
 @return Zero on success, nonzero on failure.
 */
int BNNSDirectApplyInTopK(size_t K, size_t axis, size_t batch_size,
                          const BNNSNDArrayDescriptor *input, size_t input_batch_stride,
                          const BNNSNDArrayDescriptor *test_indices, size_t test_indices_batch_stride,
                          BNNSNDArrayDescriptor *output, size_t output_batch_stride,
                          const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/*!
 @abstract Gather elements along a single axis

 @discussion
 Maps one n dimensional tensor to another n dimensional tensor, only with indices along the
 given axis gathered as according to the given indices tensor.
   output[i_0, ... i_axis, ... i_{n-1}] = input[i_0, ... idx_axis, ... i_{n-1}]
 where the value idx_axis is drawn from the indices tensor as follows:
 1) If indices is a 1d vector, idx_axis = indices[i_axis]
 2) If indices shape matches output shape, idx_axis = indices[i_0, ... i_axis, ... i_{n-1}]
 (Note that in the degeneate case where output is a 1d vector the two definitions are equivalent)

 In both cases, if any indices value is out of range, an error is generated.

 @param axis Axis along which indices are gathered
 @param input Tensor from which values are gathered
 @param indices 1D tensor containing indices to gather
 @param output Tensor in which to store output. Must have shape consistent with input and indices as described above.
 @param filter_params Filter runtime parameters, may be NULL for default parameters
 */
int BNNSGather(size_t axis,
               const BNNSNDArrayDescriptor *input,
               const BNNSNDArrayDescriptor *indices,
               BNNSNDArrayDescriptor *output,
               const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));

/*!
 @abstract Scatter elements along a single axis

 @discussion
 Given a set of input indices along the given axis, we modify the output tensor setting
   output[i_0, ... idx_axis, ... i_{n-1}] = input[i_0, ... i_axis, ... i_{n-1}]
 where the value idx_axis is drawn from the indices tensor as follows:
 1) If indices is a 1d vector, idx_axis = indices[i_axis]
 2) If indices shape matches input shape, idx_axis = indices[i_0, ... i_axis, ... i_{n-1}]
 (Note that in the degeneate case where input is a 1d vector the two definitions are equivalent)

 If any indices value is out of range, an error is generated.

 Output values that are scattered to reduced with the existing value as
   output[output_idx] = op(output[output_idx], input[input_idx]).
 If multiple input values update the same output element, the order of update operations is undefined.
 In particular, if op == BNNSReduceFunctionNone there is no guarantee any particular value will result.

 @param axis Axis along which indices are scattered
 @param op Reduction op used to reduce existing output value with scattered value.
        At present only BNNSReduceFunctionNone and BNNSReduceFunctionSum are supported.
 @param input Tensor from which values are scattered
 @param indices 1D tensor containing indices to gather. Must have the same size as the axis-th dimension of input.
 @param output Tensor into which indices are scattered
 @param filter_params Filter runtime parameters, may be NULL for default parameters
 */
int BNNSScatter(size_t axis,
                BNNSReduceFunction op,
                const BNNSNDArrayDescriptor *input,
                const BNNSNDArrayDescriptor *indices,
                BNNSNDArrayDescriptor *output,
                const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));

/*!
 @abstract Gathers a (k-1)-dimensional set of slices or elements from the input array

 @discussion
 This provides a more comprehensive version of BNNSGather that allows gathering slices of the input array.

 The indices array is interpreted as a (k-1) dimensional set of 1d lookup vectors (thus the indices tensor has (k-1) + 1 = k dimensions total).
 If the 1d lookup vectors do not give a full set of indices, the remaining indices are treated as a slice.
 e.g. If the input array is 3 dimensional, then:
    indices[i] = {1} would gather the 2d slice input[1, :, :]
    indices[i] = {3,2} would gather the 1d slice input[3, 2, :]
    indices[i] = {2,1,3} would gather the element input[2, 1, 3]
 As such, the shape of the output is given by the concatenation of the shape for the first k-1 dimensions of indices and the
 shape of the slice gathered (which is itself given by the shape of the last p dimensions of the input tensor, where
 p=ndim(input)-indices.size[k-1]).

 If any indices value are out of range, an error is generated.

 @param input Tensor from which values are gathered
 @param indices Tensor containing indices to gather
 @param output Tensor in which to store output. Must have shape consistent with input and indices as described above.
 @param filter_params Filter runtime parameters, may be NULL for default parameters
 */
int BNNSGatherND(const BNNSNDArrayDescriptor *input,
                 const BNNSNDArrayDescriptor *indices,
                 BNNSNDArrayDescriptor *output,
                 const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));

/*!
 @abstract Scatters a (k-1)-dimensional set of slices or elements across the output array

 @discussion
 This is the inverse of the BNNSGatherND operation.

 The indices array is interpreted as a (k-1) dimensional set of 1d lookup vectors (thus the indices tensor has (k-1) + 1 = k dimensions total).
 If the 1d lookup vectors do not give a full set of indices, the remaining indices are treated as a slice.
 e.g. If the output array is 3 dimensional, then:
    indices[i] = {1} would refer to the 2d slice output[1, :, :]
    indices[i] = {3,2} would refer to the 1d slice output[3, 2, :]
    indices[i] = {2,1,3} would refer to the output[2, 1, 3]
 As such, the shape of the input is given by the concatenation of the shape for the first k-1 dimensions of indices and the
 shape of the slice gathered (which is itself given by the shape of the last p dimensions of the output tensor, where
 p=ndim(output)-indices.size[k-1]).

 If any indices value are out of range, an error is generated.

 Output values that are scattered to reduced with the existing value as
   output[output_idx] = op(output[output_idx], input[input_idx]).
 If multiple input values update the same output element, the order of update operations is undefined.
 In particular, if op == BNNSReduceFunctionNone there is no guarantee any particular value will result.

 @param op Reduction op used to reduce existing output value with scattered value.
        At present only BNNSReduceFunctionNone and BNNSReduceFunctionSum are supported.
 @param input Tensor from which values are scattered
 @param indices Tensor containing indices to scatter
 @param output Tensor into which indices are scattered
 @param filter_params Filter runtime parameters, may be NULL for default parameters
 */
int BNNSScatterND(BNNSReduceFunction op,
                  const BNNSNDArrayDescriptor *input,
                  const BNNSNDArrayDescriptor *indices,
                  BNNSNDArrayDescriptor *output,
                  const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));

/*!
 @abstract Rearranges elements in a tensor according to shuffle type
 
 @param type Type of shuffle to perform
 @param input Pointer to the input tensor descriptor
 @param output Pointer to the output tensor descriptor
 @param filter_params Filter runtime parameters, may be NULL for default parameters
 @return Zero on success, nonzero on failure.
 */
int BNNSShuffle(const BNNSShuffleType type,
                const BNNSNDArrayDescriptor *input,
                BNNSNDArrayDescriptor *output,
                const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));

/*!
 @abstract Set elements outside a center band to zeros for the innermost matrix (the two dimensions with
 the lowest stride values)
 @discussion
   Currently only works on contiguous input and output

 @param num_lower The number of subdiagonals that the function copies. Set to a negative value to copy the entire lower triangle
 @param num_upper The number of superdiagonals that the function copies. Set to a negative value to copy the entire upper triangle
 @param input Pointer to the input tensor descriptor
 @param output Pointer to the output tensor descriptor
 @param filter_params Filter runtime parameters, may be NULL for default parameters
 @return Zero on success, nonzero on failure.
 */
int BNNSBandPart(const int num_lower,
                 const int num_upper,
                 const BNNSNDArrayDescriptor *input,
                 BNNSNDArrayDescriptor *output,
                 const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));

/*!
 @abstract Resize the spatial dimensions (two dimensions with the smallest strides) of the first input
 according to the bounding boxes and box indices specified in the second input.
 
 @discussion
   Only works on contiguous tensors

 @param layer_params Pointer to layer parameter
 @param input Pointer to the input tensor descriptor
 @param roi Pointer to regions of interest tensor descriptor
 @param output Pointer to the output tensor descriptor
 @param filter_params Filter runtime parameters, may be NULL for default parameters
 @return Zero on success, nonzero on failure.
 */
int BNNSCropResize(const BNNSLayerParametersCropResize * layer_params,
                   const BNNSNDArrayDescriptor *input,
                   const BNNSNDArrayDescriptor *roi,
                   BNNSNDArrayDescriptor *output,
                   const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

/*!
 @abstract backward path of BNNSTile to calculate input delta from output delta
 
 @discussion
   The size of output tensor along each dimension should be a multiple of input tensor,
   and the multiple is the number of repetition.

 @param in_delta Pointer to the input delta tensor descriptor
 @param out_delta Pointer to the output delta tensor descriptor
 @param filter_params Filter runtime parameters, may be NULL for default parameters
 @return Zero on success, nonzero on failure.
 */
int BNNSTileBackward(BNNSNDArrayDescriptor *_Nonnull in_delta,
                     const BNNSNDArrayDescriptor *_Nonnull out_delta,
                     const BNNSFilterParameters *_Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));

/*!
 @abstract backward path of BNNSCropResize to calculate input delta from output delta
 
 @discussion
   Only works on contiguous tensors

 @param layer_params Pointer to layer parameter
 @param in_delta Pointer to the input delta tensor descriptor
 @param roi Pointer to regions of interest tensor descriptor
 @param out_delta Pointer to the output delta tensor descriptor
 @param filter_params Filter runtime parameters, may be NULL for default parameters
 @return Zero on success, nonzero on failure.
 */
int BNNSCropResizeBackward(const BNNSLayerParametersCropResize * layer_params,
                           BNNSNDArrayDescriptor *in_delta,
                           const BNNSNDArrayDescriptor *roi,
                           const BNNSNDArrayDescriptor *out_delta,
                           const BNNSFilterParameters * _Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));

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
__API_DEPRECATED("Use BNNSGraph* APIs", macos(11.0, 15.0), ios(14.0, 18.0), watchos(7.0, 11.0), tvos(14.0, 18.0));

#endif 

/*!
 @abstract calculate the size in bytes of the array data
 @return 0 if unable to determine the size (or array->data is null)
 */
size_t BNNSNDArrayGetDataSize(const BNNSNDArrayDescriptor *_Nonnull array)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract calculate the minimum size in bytes of the array data given the shape and stride
 @return size of allocation sufficient to hold the tensor data, or `SIZE_T_MAX` if unable to
         determine the size (e.g. due to dynamic shape or overflow)
 */
size_t BNNSTensorGetAllocationSize(const BNNSTensor *_Nonnull tensor)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/*!
 @abstract Determine the rank of the given layout
 @return The number of dimensions represented by `layout`, or `SIZE_T_MAX` if unable to determine
 */
size_t BNNSDataLayoutGetRank(BNNSDataLayout layout)
__API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4), tvos(17.4));

#if !0

/*!
 @abstract Converts sparse tensor from the standardized COO layout to a device specific sparse layout used by FullyConnected
 @discussion The COO format is similar to that used in tensorflow and described at  https://www.tensorflow.org/guide/sparse_tensor
 - If the developer preallocates the workspace, it must be at least twice the size of the dense input.
 - BNNS will allocate scratch memory if workspace is NULL
 - the developer may pre allocate out->data to equal to the memory size of the dense input.
 - BNNS will allocate the memory for the sparse NDArray given by out if out->data is NULL, it will be the developer's responsibility to free this memory allocated by BNNS
 - if out->data was allocated to be >= size of input->data, we recommend query the output actual data size using BNNSNDArrayGeteDataSize after sparsify operation has been completed and reallocate to the smaller size
 - the size of dense input can be obtained by calling BNNSNDArrayGetDataSize
 - sparse_params are optional for the user to hint the attributes of the sparsity in the input. specifying pattern that doesn't match the sparse weights could result in failure to Sparsify the weights for Sparse Fully Connected
 @param in_dense_shape - describe the dense shape of the sparse 2D array. developer should set sizes and layout.
 @param in_indices - A 2D NDArray with shape [NNZ, rank], that contains the interleaved indices of the nonzero values. For row-major ordering, the even elements are the column indices and the odd elements are the row indices. For column-major ordering, the even element are the row indices and the odd elements are the column indices.
 @param in_values -  A 1D NDArray with shape [NNZ] containing all nonzero values.
 @param out - nd array descriptor of device optimized BNNS Sparse Fully Connected weights. use it when setting BNNSLayerParametersFullyConnected for BNNSDirectApplyFullyConnectedBatch or BNNSFilterCreateLayerFullyConnected
 @param sparse_params - optional data structure to hint the sparsify function. this could help identifying specialized patterns that can be accelerated compared to unstructured sparsity. see BNNSSparsityType for pattern types.
 @param batch_size - the expected batch_size when calling BNNSFilterCreateLayerFullyConnected or BNNSFilterApplyBatch with device optimized BNNS Sparse Fully Connected weights. this is important in the decision of how to pack the weights. when set to 0, assuming it will be set to 1 during inference
 @param workspace - scratch memory to use while generating the opaque BNNS Sparse Fully Connected weights. it is recommended that the size of this buffer should be equal to the memory size of the dense input. if set to NULL, BNNS will allocate and free during the run of BNNSNDArrayFullyConnectedSparsify.
 @param workspace_size - size in bytes of workspace when preallocated by the developer. Will be ignored if workspace is NULL.
 @return 0 for success, non 0 on failure (failure reason will reported in os logs)
 */
int BNNSNDArrayFullyConnectedSparsifySparseCOO(const BNNSNDArrayDescriptor * _Nonnull in_dense_shape,
                                               const BNNSNDArrayDescriptor * _Nonnull in_indices,
                                               const BNNSNDArrayDescriptor * _Nonnull in_values,
                                               BNNSNDArrayDescriptor * _Nonnull out,
                                               const BNNSSparsityParameters * _Nullable sparse_params,
                                               const size_t batch_size,
                                               void * _Nullable workspace,
                                               const size_t workspace_size,
                                               const BNNSFilterParameters *_Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));

/*!
 @abstract Converts sparse tensor from the standardized CSR layout to a device specific sparse layout used by FullyConnected
 @discussion
 - If the developer preallocate the workspace, it must be at least twice the size of the dense input.
 - BNNS will allocate scratch memory if workspace is NULL
 - the developer may pre allocate out->data to equal to the memory size of the dense input.
 - BNNS will allocate the memory for the sparse NDArray given by out if out->data is NULL, it will be the developer's responsibility to free this memory allocated by BNNS
 - if out->data was allocated to be >= size of input->data, we recommend query the output actual data size using BNNSNDArrayGeteDataSize after sparsify operation has been completed and reallocate to the smaller size
 - the size of dense input can be obtained by calling BNNSNDArrayGetDataSize
 - sparse_params are optional for the user to hint the attributes of the sparsity in the input. specifying pattern that doesn't match the sparse weights could result in failure to Sparsify the weights for Sparse Fully Connected
 @param in_dense_shape - describe the dense shape of the sparse 2D array. developer should set sizes and layout.
 @param in_column_indices - A 1D NDArray with shape [NNZ], containing the column indices of the nonzero values
 @param in_row_starts - A 1D NDArray with shape [row_size+1], containing pointers to the start of each row. (expected value 0 in location [0])
 @param in_values -  A 1D NDArray with shape [NNZ] containing all nonzero values.
 @param out - nd array descriptor of device optimized BNNS Sparse Fully Connected weights. use it when setting BNNSLayerParametersFullyConnected for BNNSDirectApplyFullyConnectedBatch or BNNSFilterCreateLayerFullyConnected
 @param sparse_params - optional data structure to hint the sparsify function. this could help identifying specialized patterns that can be accelerated compared to unstructured sparsity. see BNNSSparsityType for pattern types.
 @param batch_size - the expected batch_size when calling BNNSFilterCreateLayerFullyConnected or BNNSFilterApplyBatch with device optimized BNNS Sparse Fully Connected weights. this is important in the decision of how to pack the weights. when set to 0, assuming it will be set to 1 during inference
 @param workspace - scratch memory to use while generating the opaque BNNS Sparse Fully Connected weights. it is recommended that the size of this buffer should be equal to the memory size of the dense input. if set to NULL, BNNS will allocate and free during the run of BNNSNDArrayFullyConnectedSparsify.
 @param workspace_size - size in bytes of workspace when preallocated by the developer. Will be ignored if workspace is NULL.
 @return 0 for success, non 0 on failure (failure reason will reported in os logs)
 */
int BNNSNDArrayFullyConnectedSparsifySparseCSR(const BNNSNDArrayDescriptor * _Nonnull in_dense_shape,
                                               const BNNSNDArrayDescriptor * _Nonnull in_column_indices,
                                               const BNNSNDArrayDescriptor * _Nonnull in_row_starts,
                                               const BNNSNDArrayDescriptor * _Nonnull in_values,
                                               BNNSNDArrayDescriptor * _Nonnull out,
                                               const BNNSSparsityParameters * _Nullable sparse_params,
                                               const size_t batch_size,
                                               void * _Nullable workspace,
                                               const size_t workspace_size,
                                               const BNNSFilterParameters *_Nullable filter_params)
__API_DEPRECATED("Use BNNSGraph* APIs", macos(13.0, 15.0), ios(16.0, 18.0), watchos(9.0, 11.0), tvos(16.0, 18.0));

#endif 

#pragma mark - Random number generation

/*!

 @abstract Random number generator object

 */
typedef void * _Nullable BNNSRandomGenerator;

/*!
 @abstract Create a random number generator

 @discussion
 Creates a BNNSRandomGenerator object that can be used to generate a stream of random numbers.
 The generator will be intialized using an interally generated seed that will vary from call to call.

 @param method - method to be used for random number generation.

 @param filter_params - options structure, if NULL, defaults are used.

 @returns On success, an BNNSRandomGenerator object describing the RNG state.
 On failure, returns NULL.

 @seealso BNNSCreateRandomGeneratorWithSeed
 */
BNNSRandomGenerator BNNSCreateRandomGenerator(BNNSRandomGeneratorMethod method, const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/*!
 @abstract Create a random number generator using the given seed

 @discussion
 Creates a BNNSRandomGenerator object that can be used to generate a stream of random numbers.

 @param method - method to be used for random number generation.

 @param seed - random seed to be used when initializing generator.

 @param filter_params - options structure, if NULL, defaults are used.

 @returns On success, an BNNSRandomGenerator object describing the RNG state.
          On failure, returns NULL.

 @seealso BNNSCreateRandomGenerator
 */
BNNSRandomGenerator BNNSCreateRandomGeneratorWithSeed(BNNSRandomGeneratorMethod method, uint64_t seed, const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/*! @abstract Destroys a random number generator object
 *
 *  @discussion
 *  Frees memory allocated by BNNSCreateRandomGenerator
 *
 *  @param generator - generator to be destroyed
 */
void BNNSDestroyRandomGenerator(BNNSRandomGenerator generator)
__API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/*! @abstract Get the state size in bytes for a RandomGenerator
 *
 *  @discussion
 *  This captures the state from a random generator object such that it can be copied or stored and used to restore the
 *  generator at a later point.
 *
 *  @param generator - generator to be queried
 *
 *  @returns State size in bytes (0 on failure).
 */
size_t BNNSRandomGeneratorStateSize(BNNSRandomGenerator generator)
__API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/*! @abstract Get the state for a RandomGenerator
 *
 *  @discussion
 *  This captures the state from a random generator object such that it can be copied or stored and used to restore the
 *  generator at a later point.
 *  Note that if generator is used on multiple threads, usage is serialized through an internal lock. In this scenario we recommend
 *  users create a different BNNSRandomGenerator object with a different seed for each thread to ensure consistency of output
 *  on any replay usingBNNSRandomGeneratorGetState/ BNNSRandomGeneratorSetState.
 *
 *  @param generator - generator to be queried
 *
 *  @param state_size - size of state buffer in bytes, must be at least as large as the value returned by BNNSRandomGeneratorStateSize.
 *
 *  @param state - pointer to space of size returned by call to BNNSRandomGeneratorStateSize(generator)
 *
 *  @returns 0 on success, nonzero on error.
 */
int BNNSRandomGeneratorGetState(BNNSRandomGenerator generator, size_t state_size, void* state)
__API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/*! @abstract Set the state for a RandomGenerator
 *
 *  @discussion
 *  Restores the state for a RandomGenerator from one captured by a previous call to BNNSRandomGeneratorGetState().
 *  Note that if generator is used on multiple threads, usage is serialized through an internal lock. In this scenario we recommend
 *  users create a different BNNSRandomGenerator object with a different seed for each thread to ensure consistency of output
 *  on any replay using BNNSRandomGeneratorGetState/BNNSRandomGeneratorSetState.
 *
 *  @param generator - generator to be updated
 *
 *  @param state_size - size of state buffer in bytes, only the first BNNSRandomGeneratorStateSize() bytes are copied.
 *
 *  @param state - pointer to space of size returned by call to BNNSRandomGeneratorStateSize(generator)
 *
 *  @returns 0 on success, nonzero on error.
 */
int BNNSRandomGeneratorSetState(BNNSRandomGenerator generator, size_t state_size, void* state)
__API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/*! @abstract Fill the supplied tensor with random float data using the supplied generator mapped to the Unif(a, b) distribution
 *
 *  @discussion
 *  We generate pseudo-random values from Unif(a, b).
 *  Note that if generator is used on multiple threads, usage is serialized through an internal lock. In this scenario we recommend
 *  users create a different BNNSRandomGenerator object with a different seed for each thread to ensure consistency of output
 *  on any replay using BNNSRandomGeneratorGetState/BNNSRandomGeneratorSetState and to eliminate contention.
 *  Should a or b be outside the range of representable values for the output descriptor's data type, they will be capped at the
 *  closest finite value that is representable.
 *
 *  @param generator - random generator to be used
 *
 *  @param desc - tensor descriptor to be filled with random values, data type must be floating point
 *
 *  @param a - lower bound of distribution (if desc.data_type is not BNNSDataTypeFloat32, a must be exact exactly representable in the requested precision)
 *
 *  @param b - upper bound of distribution (if desc.data_type is not BNNSDataTypeFloat32, b must be exact exactly representable in the requested precision)
 *
 *  @returns 0 on success, nonzero on error.
 */
int BNNSRandomFillUniformFloat(BNNSRandomGenerator generator, BNNSNDArrayDescriptor *desc, float a, float b)
__API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/*! @abstract Fill the supplied tensor with random integer data using the supplied generator mapped to the Unif(a, b) distribution
 *
 *  @discussion
 *  We generate pseudo-random values from Unif(mean-variance, mean+variance).
 *  Note that if generator is used on multiple threads, usage is serialized through an internal lock. In this scenario we recommend
 *  users create a different BNNSRandomGenerator object with a different seed for each thread to ensure consistency of output
 *  on any replay using BNNSRandomGeneratorGetState/BNNSRandomGeneratorSetState and to eliminate contention.
 *  Should a or b be outside the range of representable values for the output descriptor's data type, they will be capped at the
 *  closest value that is representable.
 *
 *  @param generator - random generator to be used
 *
 *  @param desc - tensor descriptor to be filled with random values, data type must be integer
 *
 *  @param a - lower bound of distribution
 *
 *  @param b - upper bound of distribution
 *
 *  @returns 0 on success, nonzero on error.
*/
int BNNSRandomFillUniformInt(BNNSRandomGenerator generator, BNNSNDArrayDescriptor *desc, int64_t a, int64_t b)
__API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));


/*! @abstract Fill the supplied tensor with random float data using the supplied generator mapped to a normal distribution
 *
 *  @discussion
 *  We generate a standard normal distribution for a specified mean and standard deviation.
 *  Note that if generator is used on multiple threads, usage is serialized through an internal lock. In this scenario we recommend
 *  users create a different BNNSRandomGenerator object with a different seed for each thread to ensure consistency of output
 *  on any replay using BNNSRandomGeneratorGetState/BNNSRandomGeneratorSetState and to eliminate contention.
 *  Should a or b be outside the range of representable values for the output descriptor's data type, they will be capped at the
 *  closest finite value that is representable.
 *
 *  @param generator - random generator to be used
 *
 *  @param desc - tensor descriptor to be filled with random values, data type must be floating point
 *
 *  @param mean - mean of distribution
 *
 *  @param stddev - standard deviation of distribution
 *
 *  @returns 0 on success, nonzero on error.
 */
int BNNSRandomFillNormalFloat(BNNSRandomGenerator generator, BNNSNDArrayDescriptor *desc, float mean, float stddev)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));


/*! @abstract Fill the supplied tensor with random float data using the supplied generator mapped to
 *  categorical distributions with the given event (log) probabilities.
 *
 *  @discussion
 *  We generate  random values from a categorical distribution with specified event probabilities or event log probabilities.
 *  Note that if generator is used on multiple threads, usage is serialized through an internal lock. In this scenario we recommend
 *  users create a different BNNSRandomGenerator object with a different seed for each thread to ensure consistency of output
 *  on any replay using BNNSRandomGeneratorGetState/BNNSRandomGeneratorSetState and to eliminate contention.
 *  Assume r is the rank of the probabilities tensor, and K is the inner most dimension of probabilities tensor, i.e., probabilities.size[r-1].
 *  Then, desc must be a rank r tensor with the first r-1 dimensions having the same size as the first r-1 dimensions of probabilities, where
 *  the first r-1 dimensions are treated as batch sizes and each desc [i_0, ..., i_r-2, i_r-1] will be an integer in 0,1,..., K-1 drawn from the
 *  categorical distribution from the corresponding probabilities slice [i_0, ..., i_r-2, :]. That is to say desc.size[r-1] samples are drawn from
 *  a categorical distribution, such that P(desc[i_0, ..., i_r-2, i_r-1] == k) = probabilities[i0, ..., i_r-2, k].
 *  The probabilities data is assumed to be nonnegative and finite, which will be normalized to sum one along the inner most dimension.
 *  The log probabilities data will be normalized, so their exponentials sum to one along the inner most dimension.
 *
 *  @param generator - random generator to be used
 *
 *  @param desc - tensor descriptor to be filled with random values, data type must be floating point
 *
 *  @param probabilities - probabilities or log probabilities, data type must be the same as desc
 *
 *  @param log_probabilities - true if log probabilities is provided, otherwise probabilities data is provided
 *
 *  @returns 0 on success, nonzero on error.
 */
int BNNSRandomFillCategoricalFloat(BNNSRandomGenerator generator,
                                   const BNNSNDArrayDescriptor *desc,
                                   const BNNSNDArrayDescriptor *probabilities,
                                   bool log_probabilities)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

#if !0

#pragma mark - K-Nearest Neighbors

/*!

 @abstract K-nearest neighbors container object

 */
typedef void * _Nullable BNNSNearestNeighbors;

/**
 @abstract Create a BNNSNearestNeighbors object, that is used to calculate k nearest neighbors of data points
 based on Euclidean distance

 @param max_n_samples - maximum number of data points
 @param n_features - number of features (dimensions) of each data point
 @param n_neighbors - number of nearest neighbors
 @param data_type - data type of the features, only fp32 and fp16 is supported by now
 @param filter_params - filter runtime parameters, may be NULL for default parameters

 @return On success, a BNNSNearestNeighbors object is created. On failure, returns NULL.
 */
BNNSNearestNeighbors BNNSCreateNearestNeighbors(const unsigned int max_n_samples,
                                                const unsigned int n_features,
                                                const unsigned int n_neighbors,
                                                const BNNSDataType data_type,
                                                const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

/**
 @abstract Destroy a BNNSNearestNeighbors object

 @param knn - the BNNSNearestNeighbors object to be destroyed
 */
void BNNSDestroyNearestNeighbors(BNNSNearestNeighbors knn)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

/**
 @abstract Add new sample data to BNNSNearestNeighbors

 @param knn - the BNNSNearestNeighbors object used for calculation and storage
 @param n_new_samples - number of new data points to be added
 @param data_ptr - pointer to the new data array of size [n_new_samples, n_features]

 @return 0 for success, nonzero on failure (failure reason will reported in os logs)
 */
int BNNSNearestNeighborsLoad(BNNSNearestNeighbors knn,
                             const unsigned int n_new_samples,
                             const void* data_ptr)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

/**
 @abstract Return the sorted indices and distances of the k nearest neighbors to certain sample point

 @param knn -  the BNNSNearestNeighbors object used for calculation and storage
 @param sample_number - sample number to return the k nearest neighbors, if negative return all of them
 @param indices - sorted indices of the k nearest neighbors to the sample point (sample_number), if not null.
  If sample_number is negative, indices is an array of [n_samples, n_neighbors], otherwise indices is an array of [n_neighbors].
  Return -1 for n_neighbors larger than n_samples.
 @param distances - sorted distances of the k nearest neighbors to the sample point (sample_number), if not null.
  If sample_number is negative, distances is an array of [n_samples, n_neighbors], otherwise distances is an array of [n_neighbors].
  Return INFINITY for n_neighbors larger than n_samples.

 @return 0 for success, nonzero on failure (failure reason will reported in os logs)
 */
int BNNSNearestNeighborsGetInfo(const BNNSNearestNeighbors knn,
                                const int sample_number,
                                int * _Nullable indices,
                                void * _Nullable distances)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

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

#endif 

#if !__has_include( <Availability.h> )
#undef __API_AVAILABLE
#undef __API_DEPRECATED
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
