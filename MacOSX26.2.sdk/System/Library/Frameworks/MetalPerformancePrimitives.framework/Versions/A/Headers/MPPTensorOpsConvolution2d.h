
// -*- Metal -*-
//===-- MetalTensorOpsConvolution2d
//------------------------------------------------------===//
// Copyright (c) 2025 Apple Inc. All rights reserved
//===----------------------------------------------------------------------===//

#ifndef __MetalTensorOpsConvolution2d__
#define __MetalTensorOpsConvolution2d__

#if defined(__METAL_VERSION__) && defined(__HAVE_TENSOR__)

#include "__impl/MPPTensorOpsBase.h"
#include "__impl/MPPTensorOpsUtility.h"

#pragma METAL internals : enable

namespace mpp
{
namespace tensor_ops
{

// This API performs 2d-convolution that occur in convolutional neural network.
// 2d stands here for two spatial dimensions width x height even though tensors
// consumed by this op are 4D. Source/inputs to the op run method are
//      Activation tensor with named NHWC layout
//           N = batch (slowest moving dimension)
//           H = height
//           W = width
//           C = input channels (fastest moving dimension)
//      Weights tensor with named HWCO layout
//           H = kernel height
//           W = kernel width
//           C = input channels
//           O = output channels
// Destination tesnor is NHWO layout
//           N = batch (slowest moving dimension)
//           H = height
//           W = width
//           O = output channels (fastest moving dimension)
//
// Destination can also be cooperative tensor. See TensorOpsMatMul2d.h for
// details on how to use cooperative tensor for example, for bias add and
// applying activation before writing out the result. Currently only scope
// supported by convolution2d op is full threadgroup. See TensorOpsMatMul2d.h
// for details on scopes supported by tensor ops.

enum class convolution2d_activation_layout
{
  nhwc,
};

enum class convolution2d_weights_layout
{
  hwio,
};

struct convolution2d_descriptor
{
  enum class mode
  {
    multiply,
    multiply_accumulate,
  };

  // for nhwc, .x = output channel, .y = destination width, .z = destination
  // height, .w = batch size
  int4 destination_dimensions;
  int4 source_dimensions;
  int2 kernel_dimensions;
  convolution2d_activation_layout activation_layout;
  convolution2d_weights_layout weights_layout;
  int2 strides;
  int2 dilations;
  int groups;
  bool relaxed_precision;
  mode conv2d_mode;

  constexpr convolution2d_descriptor(
      int4 _destination_dimensions, int4 _source_dimensions,
      int2 _kernel_dimensions,
      convolution2d_activation_layout _activation_layout =
          convolution2d_activation_layout::nhwc,
      convolution2d_weights_layout _weights_layout =
          convolution2d_weights_layout::hwio,
      int2 _strides = int2(1, 1), int2 _dilations = int2(1, 1), int _groups = 1,
      bool _relaxed_precision = false,
      mode _convolution2d_mode = mode::multiply) thread
      : destination_dimensions(_destination_dimensions),
        source_dimensions(_source_dimensions),
        kernel_dimensions(_kernel_dimensions),
        activation_layout(_activation_layout),
        weights_layout(_weights_layout),
        strides(_strides),
        dilations(_dilations),
        groups(_groups),
        relaxed_precision(_relaxed_precision),
        conv2d_mode(_convolution2d_mode)
  {
  }
};

enum class convolution2d_cooperative_operand
{
  destination,
};

#include "__impl/MPPTensorOpsConvolution2dImpl.h"

template <convolution2d_descriptor Descriptor, typename Scope,
          typename... ConvArgs>
class convolution2d : __tensor_ops_detail::op
{
  static_assert(Descriptor.activation_layout ==
                    convolution2d_activation_layout::nhwc,
                "only nhwc activation layout supported currently");
  static_assert(Descriptor.weights_layout == convolution2d_weights_layout::hwio,
                "only hwio weights layout supported currently");
  static_assert(Descriptor.groups == 1,
                "only group size 1 supported currently");

private:
  thread int2 __offset;

public:
  convolution2d() thread : __offset(0)
  {
  }

  void set_offsets(int2 o) thread
  {
    __offset = o;
  }

  template <typename ActivationTensorType, typename WeightsTensorType,
            typename DestinationTensorType, typename... RunArgs>
  INLINE void run(thread ActivationTensorType &activation,
                  thread WeightsTensorType &weights,
                  thread DestinationTensorType &destination) const thread
  {
    convolution2d_descriptor d = Descriptor;
    __convolution2d_detail::__run<Scope, ActivationTensorType,
                                  WeightsTensorType, DestinationTensorType,
                                  RunArgs...>(activation, weights, destination,
                                              d, __offset);
  }

  template <typename ActivationOperandType, typename WeightsOperandType,
            typename ElementType, typename CoordType = int,
            typename... CoopArgs>
  using cooperative_tensor_destination_t =
      __convolution2d_detail::__cooperative_tensor_destination_t<
          Descriptor, Scope, ActivationOperandType, WeightsOperandType,
          ElementType, CoordType, CoopArgs...>;

  template <typename ActivationOperandType, typename WeightsOperandType,
            typename ElementType, typename CoordType = int,
            typename... CoopArgs>
  INLINE cooperative_tensor_destination_t<ActivationOperandType,
                                          WeightsOperandType, ElementType,
                                          CoordType, CoopArgs...>
  get_destination_cooperative_tensor() const thread
  {
    return __convolution2d_detail::__get_destination_cooperative_tensor<
        Descriptor, Scope, ActivationOperandType, WeightsOperandType,
        ElementType, CoordType, CoopArgs...>();
  }
};

} // namespace tensor_ops
} // namespace mpp

#pragma METAL internals : disable

#endif

#endif // __TensorOpsConvolution2D__
