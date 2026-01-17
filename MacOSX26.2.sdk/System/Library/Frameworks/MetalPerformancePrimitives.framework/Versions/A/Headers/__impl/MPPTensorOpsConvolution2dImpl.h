

// -*- Metal -*-
//===-- MetalTensorOpsConvolution2dImpl
//------------------------------------------------------===//
// Copyright (c) 2025 Apple Inc. All rights reserved
//===----------------------------------------------------------------------===//

#ifndef __MetalTensorOpsConvolution2dImpl__
#define __MetalTensorOpsConvolution2dImpl__

#if defined(__METAL_VERSION__) && defined(__HAVE_TENSOR__)

namespace __convolution2d_detail
{

#ifndef EXTERNALLY_DEFINED_ATTR
#define EXTERNALLY_DEFINED_ATTR \
  __attribute__((section("air.externally_defined")))
#endif

#define TENSOROPS_EXPORT [[gnu::visibility("default")]]
#define INLINE __attribute__((__always_inline__))

extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_f16_dv_f16_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_f16_dv_f16_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_f16_tg_f16_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_f16_tg_f16_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_f16_dv_f16_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_f16_dv_f16_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_f16_tg_f16_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_f16_tg_f16_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_f16_dv_f16_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_f16_dv_f16_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_f16_tg_f16_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_f16_tg_f16_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_f16_dv_f16_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_f16_dv_f16_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_f16_tg_f16_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_f16_tg_f16_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_f32_dv_f32_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_f32_dv_f32_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_f32_tg_f32_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_f32_tg_f32_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_f32_dv_f32_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_f32_dv_f32_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_f32_tg_f32_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_f32_tg_f32_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_dv_i8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_dv_i8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_tg_i8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_tg_i8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_dv_i8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_dv_i8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_tg_i8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_tg_i8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_dv_i8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_dv_i8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_tg_i8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_tg_i8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_dv_i8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_dv_i8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_tg_i8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_tg_i8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_dv_i8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_dv_i8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_tg_i8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_tg_i8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_dv_i8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_dv_i8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_tg_i8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_tg_i8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_dv_ui8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_dv_ui8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_tg_ui8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_tg_ui8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_dv_ui8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_dv_ui8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_tg_ui8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_tg_ui8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_dv_ui8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_dv_ui8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_tg_ui8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_tg_ui8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_dv_ui8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_dv_ui8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_tg_ui8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_tg_ui8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_dv_ui8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_dv_ui8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_tg_ui8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_i8_tg_ui8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_dv_ui8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_dv_ui8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_tg_ui8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_i8_tg_ui8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_dv_i8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_dv_i8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_tg_i8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_tg_i8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_dv_i8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_dv_i8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_tg_i8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_tg_i8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_dv_i8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_dv_i8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_tg_i8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_tg_i8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_dv_i8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_dv_i8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_tg_i8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_tg_i8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_dv_i8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_dv_i8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_tg_i8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_tg_i8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_dv_i8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_dv_i8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_tg_i8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_tg_i8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_dv_ui8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_dv_ui8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_tg_ui8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_tg_ui8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_dv_ui8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_dv_ui8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_tg_ui8_dv_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_tg_ui8_tg_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_dv_ui8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_dv_ui8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_tg_ui8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_tg_ui8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_dv_ui8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_dv_ui8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_tg_ui8_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_tg_ui8_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_dv_ui8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_dv_ui8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_tg_ui8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_ui8_tg_ui8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_dv_ui8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_dv_ui8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_tg_ui8_dv_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_ui8_tg_ui8_tg_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_bf_dv_bf_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_bf_dv_bf_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_bf_tg_bf_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_bf_tg_bf_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_bf_dv_bf_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_bf_dv_bf_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_bf_tg_bf_dv_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_bf_tg_bf_tg_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_bf_dv_bf_dv_bf(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_bf_dv_bf_tg_bf(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_bf_tg_bf_dv_bf(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_dv_bf_tg_bf_tg_bf(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_bf_dv_bf_dv_bf(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_bf_dv_bf_tg_bf(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_bf_tg_bf_dv_bf(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_tg_bf_tg_bf_tg_bf(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type,
    int threads, thread int2 &offset);

extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_f16_dv_f16_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_f16_tg_f16_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_f16_dv_f16_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_f16_tg_f16_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_f16_dv_f16_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_f16_tg_f16_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_f16_dv_f16_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_f16_tg_f16_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_f32_dv_f32_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_f32_tg_f32_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_f32_dv_f32_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_f32_tg_f32_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_i8_dv_i8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_i8_tg_i8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_i8_dv_i8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_i8_tg_i8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_i8_dv_i8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_i8_tg_i8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_i8_dv_i8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_i8_tg_i8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_i8_dv_i8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_i8_tg_i8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_i8_dv_i8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_i8_tg_i8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_i8_dv_ui8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_i8_tg_ui8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_i8_dv_ui8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_i8_tg_ui8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_i8_dv_ui8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_i8_tg_ui8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_i8_dv_ui8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_i8_tg_ui8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_i8_dv_ui8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_i8_tg_ui8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_i8_dv_ui8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_i8_tg_ui8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_dv_i8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_tg_i8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_dv_i8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_tg_i8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_dv_i8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_tg_i8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_dv_i8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_tg_i8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_dv_i8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_tg_i8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_dv_i8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_tg_i8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_dv_ui8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_tg_ui8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_dv_ui8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_tg_ui8_f16(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_dv_ui8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_tg_ui8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_dv_ui8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_tg_ui8_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_dv_ui8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_tg_ui8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_dv_ui8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_tg_ui8_i32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_bf_dv_bf_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_bf_tg_bf_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_bf_dv_bf_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_bf_tg_bf_f32(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_bf_dv_bf_bf(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_dv_bf_tg_bf_bf(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_bf_dv_bf_bf(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_run_cooperative_tg_bf_tg_bf_bf(
    thread convolution2d_descriptor &desc, thread void *activation,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        activation_desc_type,
    thread void *weights,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type weights_desc_type,
    thread void *destination, int threads, thread int2 &offset);

template <typename scope, typename activation_type, typename weights_type,
          typename destination_type, typename... run_args>
void __run(thread activation_type &activation_tensor,
           thread weights_type &weights_tensor,
           thread destination_type &destination_tensor,
           thread convolution2d_descriptor &__descriptor, int2 __offset)
{
  using activation_tensor_type = __tensor_ops_detail::__remove_addrspace_t<
      __tensor_ops_detail::__remove_reference_t<decltype(activation_tensor)>>;
  using weights_tensor_type = __tensor_ops_detail::__remove_addrspace_t<
      __tensor_ops_detail::__remove_reference_t<decltype(weights_tensor)>>;
  using destination_tensor_type = __tensor_ops_detail::__remove_addrspace_t<
      __tensor_ops_detail::__remove_reference_t<decltype(destination_tensor)>>;

  metal::execution_threads t = scope();
  int threads = t.size();

  static_assert(__tensor_ops_detail::__is_tensor_type_v<activation_tensor_type>,
                "Activation must be a tensor");
  static_assert(__tensor_ops_detail::__is_tensor_type_v<weights_tensor_type>,
                "Weights must be a tensor");
  static_assert(
      __tensor_ops_detail::__is_tensor_type_v<destination_tensor_type> ||
          __tensor_ops_detail::__is_cooperative_tensor_type_v<
              destination_tensor_type>,
      "Destination must be a tensor or cooperative tensor");

  static_assert(__tensor_ops_detail::__get_rank<activation_tensor_type>() == 4,
                "Activation must be rank 4");
  static_assert(__tensor_ops_detail::__get_rank<weights_tensor_type>() == 4,
                "Weights must be rank 4");
  static_assert(__tensor_ops_detail::__get_rank<destination_tensor_type>() == 4,
                "Destination must be rank 4");

  static_assert(__tensor_ops_detail::__is_same_v<
                    typename activation_tensor_type::index_type, int>,
                "Index type must be int");
  static_assert(
      __tensor_ops_detail::__is_same_v<typename weights_tensor_type::index_type,
                                       int>,
      "Index type must be int");
  static_assert(__tensor_ops_detail::__is_same_v<
                    typename destination_tensor_type::index_type, int>,
                "Index type must be int");

  using activation_ptr_type = typename activation_tensor_type::data_handle_type;
  using weights_ptr_type = typename weights_tensor_type::data_handle_type;
  using destination_ptr_type =
      typename destination_tensor_type::data_handle_type;

  using activation_value_type = typename activation_tensor_type::value_type;
  using weights_value_type = typename weights_tensor_type::value_type;
  using destination_value_type = typename destination_tensor_type::value_type;

  auto activation = (thread void *)(&activation_tensor);
  auto weights = (thread void *)(&weights_tensor);
  auto offset = __offset;

  const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
      activation_desc_type =
          __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<
              activation_tensor_type>();
  const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
      weights_desc_type =
          __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<
              weights_tensor_type>();

  convolution2d_descriptor desc = __descriptor;

  if constexpr (__tensor_ops_detail::__is_cooperative_tensor_type_v<
                    destination_tensor_type>)
  {
    thread void *destination =
        &destination_tensor[__tensor_ops_detail::__tensor_ops_reserved_index];

    if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                   int8_t> &&
                  __tensor_ops_detail::__is_same_v<weights_value_type,
                                                   int8_t> &&
                  __tensor_ops_detail::__is_same_v<destination_value_type,
                                                   half>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_i8_dv_i8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_i8_dv_i8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_i8_tg_i8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_i8_tg_i8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, float>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_i8_dv_i8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_i8_dv_i8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_i8_tg_i8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_i8_tg_i8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, int32_t>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_i8_dv_i8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_i8_dv_i8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_i8_tg_i8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_i8_tg_i8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, half>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_dv_i8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_dv_i8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_tg_i8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_tg_i8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, float>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_dv_i8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_dv_i8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_tg_i8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_tg_i8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, int32_t>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_dv_i8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_dv_i8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_tg_i8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_tg_i8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, half>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_i8_dv_ui8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_i8_dv_ui8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_i8_tg_ui8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_i8_tg_ui8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, float>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_i8_dv_ui8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_i8_dv_ui8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_i8_tg_ui8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_i8_tg_ui8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, int32_t>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_i8_dv_ui8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_i8_dv_ui8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_i8_tg_ui8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_i8_tg_ui8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, half>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_dv_ui8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_dv_ui8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_tg_ui8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_tg_ui8_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, float>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_dv_ui8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_dv_ui8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_tg_ui8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_tg_ui8_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, int32_t>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_dv_ui8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_dv_ui8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_ui8_tg_ui8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_ui8_tg_ui8_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        half> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        half> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, half>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_f16_dv_f16_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_f16_dv_f16_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_f16_tg_f16_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_f16_tg_f16_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        half> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        half> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, float>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_f16_dv_f16_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_f16_dv_f16_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_f16_tg_f16_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_f16_tg_f16_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
#if __HAVE_BFLOAT__
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        bfloat> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        bfloat> &&
                       __tensor_ops_detail::__is_same_v<destination_value_type,
                                                        bfloat>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_bf_dv_bf_bf(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_bf_dv_bf_bf(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_bf_tg_bf_bf(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_bf_tg_bf_bf(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        bfloat> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        bfloat> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, float>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_bf_dv_bf_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_bf_dv_bf_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_bf_tg_bf_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_bf_tg_bf_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
#endif
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        float> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        float> &&
                       __tensor_ops_detail::__is_same_v<destination_value_type,
                                                        float>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        activation_ptr_type> &&
                    __tensor_ops_detail::__is_device_addrspace_v<
                        weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_f32_dv_f32_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_f32_dv_f32_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_dv_f32_tg_f32_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type>)
        __tensorops_impl_convolution2d_op_run_cooperative_tg_f32_tg_f32_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else
      static_assert(
          __tensor_ops_detail::__assert_false_v<destination_value_type>,
          "Unsupported type");
  }
  else
  {
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type =
            __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<
                destination_tensor_type>();

    thread void *destination = (thread void *)(&destination_tensor);

    if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                   int8_t> &&
                  __tensor_ops_detail::__is_same_v<weights_value_type,
                                                   int8_t> &&
                  __tensor_ops_detail::__is_same_v<destination_value_type,
                                                   half>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_dv_i8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_dv_i8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_tg_i8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_tg_i8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_dv_i8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_dv_i8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_tg_i8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_tg_i8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, float>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_dv_i8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_dv_i8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_tg_i8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_tg_i8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_dv_i8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_dv_i8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_tg_i8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_tg_i8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, int32_t>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_dv_i8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_dv_i8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_tg_i8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_tg_i8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_dv_i8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_dv_i8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_tg_i8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_tg_i8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, half>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_dv_i8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_dv_i8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_tg_i8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_tg_i8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_dv_i8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_dv_i8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_tg_i8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_tg_i8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, float>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_dv_i8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_dv_i8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_tg_i8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_tg_i8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_dv_i8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_dv_i8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_tg_i8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_tg_i8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, int32_t>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_dv_i8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_dv_i8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_tg_i8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_tg_i8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_dv_i8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_dv_i8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_tg_i8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_tg_i8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, half>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_dv_ui8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_dv_ui8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_tg_ui8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_tg_ui8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_dv_ui8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_dv_ui8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_tg_ui8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_tg_ui8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, float>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_dv_ui8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_dv_ui8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_tg_ui8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_tg_ui8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_dv_ui8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_dv_ui8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_tg_ui8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_tg_ui8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        int8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, int32_t>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_dv_ui8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_dv_ui8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_tg_ui8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_tg_ui8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_dv_ui8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_dv_ui8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_i8_tg_ui8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_i8_tg_ui8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, half>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_dv_ui8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_dv_ui8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_tg_ui8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_tg_ui8_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_dv_ui8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_dv_ui8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_tg_ui8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_tg_ui8_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, float>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_dv_ui8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_dv_ui8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_tg_ui8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_tg_ui8_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_dv_ui8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_dv_ui8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_tg_ui8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_tg_ui8_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        uint8_t> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, int32_t>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_dv_ui8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_dv_ui8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_tg_ui8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_tg_ui8_dv_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_dv_ui8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_dv_ui8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_ui8_tg_ui8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_ui8_tg_ui8_tg_i32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        half> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        half> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, half>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_f16_dv_f16_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_f16_dv_f16_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_f16_tg_f16_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_f16_tg_f16_dv_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_f16_dv_f16_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_f16_dv_f16_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_f16_tg_f16_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_f16_tg_f16_tg_f16(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        half> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        half> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, float>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_f16_dv_f16_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_f16_dv_f16_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_f16_tg_f16_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_f16_tg_f16_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_f16_dv_f16_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_f16_dv_f16_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_f16_tg_f16_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_f16_tg_f16_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
#if __HAVE_BFLOAT__
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        bfloat> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        bfloat> &&
                       __tensor_ops_detail::__is_same_v<destination_value_type,
                                                        bfloat>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_bf_dv_bf_dv_bf(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_bf_dv_bf_dv_bf(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_bf_tg_bf_dv_bf(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_bf_tg_bf_dv_bf(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_bf_dv_bf_tg_bf(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_bf_dv_bf_tg_bf(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_bf_tg_bf_tg_bf(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_bf_tg_bf_tg_bf(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        bfloat> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        bfloat> &&
                       __tensor_ops_detail::__is_same_v<
                           destination_value_type, float>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_bf_dv_bf_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_bf_dv_bf_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_bf_tg_bf_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_bf_tg_bf_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_bf_dv_bf_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_bf_dv_bf_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_bf_tg_bf_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_bf_tg_bf_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
#endif
    else if constexpr (__tensor_ops_detail::__is_same_v<activation_value_type,
                                                        float> &&
                       __tensor_ops_detail::__is_same_v<weights_value_type,
                                                        float> &&
                       __tensor_ops_detail::__is_same_v<destination_value_type,
                                                        float>)
    {
      if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_f32_dv_f32_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_f32_dv_f32_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (
          __tensor_ops_detail::__is_device_addrspace_v<activation_ptr_type> &&
          __tensor_ops_detail::__is_threadgroup_addrspace_v<weights_ptr_type> &&
          __tensor_ops_detail::__is_device_addrspace_v<destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_f32_tg_f32_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_f32_tg_f32_dv_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_f32_dv_f32_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_device_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_f32_dv_f32_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_dv_f32_tg_f32_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             activation_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             weights_ptr_type> &&
                         __tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_run_tg_f32_tg_f32_tg_f32(
            desc, activation, activation_desc_type, weights, weights_desc_type,
            destination, destination_desc_type, threads, offset);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else
      static_assert(
          __tensor_ops_detail::__assert_false_v<destination_value_type>,
          "Unsupported type");
  }
}

extern "C" TENSOROPS_EXPORT EXTERNALLY_DEFINED_ATTR size_t
__tensorops_impl_conv2d_cooperative_destination_data_size(
    const thread convolution2d_descriptor &descriptor,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype, int threads);
extern "C" TENSOROPS_EXPORT EXTERNALLY_DEFINED_ATTR uint16_t
__tensorops_impl_conv2d_cooperative_destination_tensor_num_elements(
    const thread convolution2d_descriptor &descriptor,
    __tensor_ops_detail::__const_thread_void_t, int threads);
extern "C" TENSOROPS_EXPORT
    EXTERNALLY_DEFINED_ATTR __tensor_ops_detail::__thread_void_t
    __tensorops_impl_conv2d_cooperative_destination_tensor_elements(
        __tensor_ops_detail::__thread_void_t, uint16_t,
        __tensor_ops_detail::__tensor_ops_datatype, int threads);
extern "C" TENSOROPS_EXPORT EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_conv2d_cooperative_destination_tensor_get_coordinate(
    const thread convolution2d_descriptor &descriptor,
    __tensor_ops_detail::__thread_void_t, uint16_t,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__tensor_ops_datatype, int threads);
extern "C" TENSOROPS_EXPORT EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_conv2d_cooperative_destination_tensor_init(
    __tensor_ops_detail::__thread_void_t,
    const thread convolution2d_descriptor &,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype, int threads);
extern "C" TENSOROPS_EXPORT EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_conv2d_cooperative_destination_tensor_copy(
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    const thread convolution2d_descriptor &,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype, int threads);
extern "C" TENSOROPS_EXPORT EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_conv2d_cooperative_destination_tensor_move(
    __tensor_ops_detail::__thread_void_t, __tensor_ops_detail::__thread_void_t,
    const thread convolution2d_descriptor &,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype, int threads);
extern "C" TENSOROPS_EXPORT EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_conv2d_cooperative_destination_tensor_destory(
    __tensor_ops_detail::__thread_void_t,
    const thread convolution2d_descriptor &, int threads);
extern "C" TENSOROPS_EXPORT EXTERNALLY_DEFINED_ATTR bool
__tensorops_impl_conv2d_cooperative_destination_tensor_is_valid_element(
    const thread convolution2d_descriptor &,
    __tensor_ops_detail::__thread_void_t, uint16_t,
    __tensor_ops_detail::__tensor_ops_datatype, int threads);
extern "C" TENSOROPS_EXPORT EXTERNALLY_DEFINED_ATTR uint16_t
__tensorops_impl_conv2d_cooperative_destination_tensor_get_element_index(
    const thread convolution2d_descriptor &, __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t, __tensor_ops_detail::__tensor_ops_datatype, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_dv_f32(
    thread convolution2d_descriptor &desc, thread void *storage,
    const thread void *source,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type sourceDescType,
    int sourceRank, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_tg_f32(
    thread convolution2d_descriptor &desc, thread void *storage,
    const thread void *source,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type sourceDescType,
    int sourceRank, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_dv_i32(
    thread convolution2d_descriptor &desc, thread void *storage,
    const thread void *source,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type sourceDescType,
    int sourceRank, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_tg_i32(
    thread convolution2d_descriptor &desc, thread void *storage,
    const thread void *source,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type sourceDescType,
    int sourceRank, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_dv_f16(
    thread convolution2d_descriptor &desc, thread void *storage,
    const thread void *source,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type sourceDescType,
    int sourceRank, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_tg_f16(
    thread convolution2d_descriptor &desc, thread void *storage,
    const thread void *source,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type sourceDescType,
    int sourceRank, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_dv_bf(
    thread convolution2d_descriptor &desc, thread void *storage,
    const thread void *source,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type sourceDescType,
    int sourceRank, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_tg_bf(
    thread convolution2d_descriptor &desc, thread void *storage,
    const thread void *source,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type sourceDescType,
    int sourceRank, int threads);

extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_dv_f32(
    thread convolution2d_descriptor &desc, const thread void *storage,
    const thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destDescType,
    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_tg_f32(
    thread convolution2d_descriptor &desc, const thread void *storage,
    const thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destDescType,
    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_dv_i32(
    thread convolution2d_descriptor &desc, const thread void *storage,
    const thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destDescType,
    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_tg_i32(
    thread convolution2d_descriptor &desc, const thread void *storage,
    const thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destDescType,
    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_dv_f16(
    thread convolution2d_descriptor &desc, const thread void *storage,
    const thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destDescType,
    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_tg_f16(
    thread convolution2d_descriptor &desc, const thread void *storage,
    const thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destDescType,
    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_dv_bf(
    thread convolution2d_descriptor &desc, const thread void *storage,
    const thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destDescType,
    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_tg_bf(
    thread convolution2d_descriptor &desc, const thread void *storage,
    const thread void *destination,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destDescType,
    int threads);

template <convolution2d_descriptor descriptor,
          convolution2d_cooperative_operand operand, typename scope,
          typename activation_operand_type, typename weights_operand_type,
          typename element_type, typename coord_type, typename... coop_args>
struct __operand_layout
{
  static_assert(operand == convolution2d_cooperative_operand::destination,
                "only destination can be cooperative tensor");
  static_assert(__tensor_ops_detail::__is_same_v<element_type, float> ||
                    __tensor_ops_detail::__is_same_v<element_type, half> ||
#if __HAVE_BFLOAT__
                    __tensor_ops_detail::__is_same_v<element_type, bfloat> ||
#endif
                    __tensor_ops_detail::__is_same_v<element_type, int32_t>,
                "cooperative tensor data type can only be one of "
                "float/half/bfloat/int32_t");

  static constant constexpr __tensor_ops_detail::__rank_t rank = 4;
  using element_t = element_type;
  using coord_t = coord_type;
  using extent_t = metal::dextents<coord_t, rank>;
  using thread_storage_t = thread void *;
  using const_thread_storage_t = const thread void *;
  using index_t = uint16_t;
  using operand_layout_t =
      __operand_layout<descriptor, operand, scope, activation_operand_type,
                       weights_operand_type, element_type, coord_type,
                       coop_args...>;
  using cooperative_tensor_t =
      metal::cooperative_tensor<element_type, extent_t, operand_layout_t>;

  using a_type = __tensor_ops_detail::__remove_addrspace_t<
      __tensor_ops_detail::__remove_reference_t<activation_operand_type>>;
  using w_type = __tensor_ops_detail::__remove_addrspace_t<
      __tensor_ops_detail::__remove_reference_t<weights_operand_type>>;

  using a_elem_type = typename a_type::element_type;
  using w_elem_type = typename w_type::element_type;

  using a_value_type = typename a_type::value_type;
  using w_value_type = typename w_type::value_type;

  static size_t thread_storage_size()
  {
    metal::execution_threads t = scope();
    int threads = t.size();
    __tensor_ops_detail::__tensor_ops_datatype d_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype a_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<a_value_type>::value;
    __tensor_ops_detail::__tensor_ops_datatype w_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<w_value_type>::value;
    return __tensorops_impl_conv2d_cooperative_destination_data_size(
        descriptor, d_data_type, a_data_type, w_data_type, threads);
  }

  static constexpr size_t thread_storage_align()
  {
    return alignof(element_t);
  };

  static uint16_t get_capacity(const_thread_storage_t storage)
  {
    metal::execution_threads t = scope();
    int threads = t.size();
    return __tensorops_impl_conv2d_cooperative_destination_tensor_num_elements(
        descriptor, storage, threads);
  }

  static void construct(thread void *this_)
  {
    metal::execution_threads t = scope();
    int threads = t.size();
    __tensor_ops_detail::__tensor_ops_datatype d_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype a_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<a_value_type>::value;
    __tensor_ops_detail::__tensor_ops_datatype w_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<w_value_type>::value;

    __tensorops_impl_conv2d_cooperative_destination_tensor_init(
        this_, descriptor, d_data_type, a_data_type, w_data_type, threads);
  }

  static void copy_construct(thread void *this_, thread void *other)
  {
    metal::execution_threads t = scope();
    int threads = t.size();
    __tensor_ops_detail::__tensor_ops_datatype d_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype a_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<a_value_type>::value;
    __tensor_ops_detail::__tensor_ops_datatype w_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<w_value_type>::value;

    __tensorops_impl_conv2d_cooperative_destination_tensor_copy(
        this_, other, descriptor, d_data_type, a_data_type, w_data_type,
        threads);
  };

  static void move_construct(thread void *this_, thread void *other)
  {
    metal::execution_threads t = scope();
    int threads = t.size();
    __tensor_ops_detail::__tensor_ops_datatype d_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype a_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<a_value_type>::value;
    __tensor_ops_detail::__tensor_ops_datatype w_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<w_value_type>::value;

    __tensorops_impl_conv2d_cooperative_destination_tensor_move(
        this_, other, descriptor, d_data_type, a_data_type, w_data_type,
        threads);
  };

  static void copy_assign(thread void *this_, thread void *other)
  {
    metal::execution_threads t = scope();
    int threads = t.size();
    __tensor_ops_detail::__tensor_ops_datatype d_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype a_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<a_value_type>::value;
    __tensor_ops_detail::__tensor_ops_datatype w_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<w_value_type>::value;

    __tensorops_impl_conv2d_cooperative_destination_tensor_copy(
        this_, other, descriptor, d_data_type, a_data_type, w_data_type,
        threads);
  };

  static void move_assign(thread void *this_, thread void *other)
  {
    metal::execution_threads t = scope();
    int threads = t.size();
    __tensor_ops_detail::__tensor_ops_datatype d_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype a_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<a_value_type>::value;
    __tensor_ops_detail::__tensor_ops_datatype w_data_type =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<w_value_type>::value;

    __tensorops_impl_conv2d_cooperative_destination_tensor_move(
        this_, other, descriptor, d_data_type, a_data_type, w_data_type,
        threads);
  };

  // Destroys the per-thread object.
  static void destroy(thread void *this_)
  {
    metal::execution_threads t = scope();
    int threads = t.size();
    __tensorops_impl_conv2d_cooperative_destination_tensor_destory(
        this_, descriptor, threads);
  }

  template <class ElemType, class Extents, class Descriptor, class... Tags>
  static void load(thread_storage_t storage,
                   const thread metal::tensor<ElemType, Extents, Descriptor,
                                              Tags...> &sourceT)
  {
    using elem_t = __tensor_ops_detail::__remove_addrspace_t<ElemType>;

    metal::execution_threads t = scope();
    int threads = t.size();

    static_assert(__tensor_ops_detail::__is_same_v<elem_t, element_type>,
                  "Source tensor datatype does not match cooperative tensor");
    static_assert(Extents::rank() == 1 || Extents::rank() == 4,
                  "Source tensor must be rank 1 or 4");

    int sourceRank = Extents::rank();

    convolution2d_descriptor desc = descriptor;

    using tensorType = metal::tensor<ElemType, Extents, Descriptor, Tags...>;

    using sourcePtrType = typename tensorType::data_handle_type;

    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type sourceDescType =
        __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<
            tensorType>();

    const thread void *source = (const thread void *)(&sourceT);

    if constexpr (__tensor_ops_detail::__is_same_v<elem_t, half>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<sourcePtrType>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_dv_f16(
            desc, storage, source, sourceDescType, sourceRank, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             sourcePtrType>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_tg_f16(
            desc, storage, source, sourceDescType, sourceRank, threads);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<sourcePtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, int32_t>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<sourcePtrType>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_dv_i32(
            desc, storage, source, sourceDescType, sourceRank, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             sourcePtrType>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_tg_i32(
            desc, storage, source, sourceDescType, sourceRank, threads);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<sourcePtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, float>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<sourcePtrType>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_dv_f32(
            desc, storage, source, sourceDescType, sourceRank, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             sourcePtrType>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_tg_f32(
            desc, storage, source, sourceDescType, sourceRank, threads);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<sourcePtrType>,
                      "Unsupported address space");
    }
#if __HAVE_BFLOAT__
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, bfloat>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<sourcePtrType>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_dv_bf(
            desc, storage, source, sourceDescType, sourceRank, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             sourcePtrType>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_load_tg_bf(
            desc, storage, source, sourceDescType, sourceRank, threads);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<sourcePtrType>,
                      "Unsupported address space");
    }
#endif
    else
      static_assert(__tensor_ops_detail::__assert_false_v<elem_t>,
                    "Unsupported type");
  };

  template <class ElemType, class Extents, class Descriptor, class... Tags>
  static void store(const_thread_storage_t storage,
                    const thread metal::tensor<ElemType, Extents, Descriptor,
                                               Tags...> &destinationT)
  {
    using elem_t = __tensor_ops_detail::__remove_addrspace_t<ElemType>;

    metal::execution_threads t = scope();
    int threads = t.size();

    static_assert(__tensor_ops_detail::__is_same_v<elem_t, element_type>,
                  "Tensor datatype does not match cooperative tensor");
    static_assert(Extents::rank() == 1 || Extents::rank() == rank,
                  "Tensor must be rank 1 or 4");

    convolution2d_descriptor desc = descriptor;

    using tensorType = metal::tensor<ElemType, Extents, Descriptor, Tags...>;

    using destination_ptr_type = typename tensorType::data_handle_type;

    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destination_desc_type =
            __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<
                tensorType>();

    const thread void *destination = (const thread void *)(&destinationT);

    if constexpr (__tensor_ops_detail::__is_same_v<elem_t, half>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        destination_ptr_type>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_dv_f16(
            desc, storage, destination, destination_desc_type, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_tg_f16(
            desc, storage, destination, destination_desc_type, threads);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, int32_t>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        destination_ptr_type>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_dv_i32(
            desc, storage, destination, destination_desc_type, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_tg_i32(
            desc, storage, destination, destination_desc_type, threads);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, float>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        destination_ptr_type>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_dv_f32(
            desc, storage, destination, destination_desc_type, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_tg_f32(
            desc, storage, destination, destination_desc_type, threads);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
#if __HAVE_BFLOAT__
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, bfloat>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        destination_ptr_type>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_dv_bf(
            desc, storage, destination, destination_desc_type, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destination_ptr_type>)
        __tensorops_impl_convolution2d_op_cooperative_destination_tensor_store_tg_bf(
            desc, storage, destination, destination_desc_type, threads);
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destination_ptr_type>,
            "Unsupported address space");
    }
#endif
    else
      static_assert(__tensor_ops_detail::__assert_false_v<elem_t>,
                    "Unsupported type");
  };

  static thread element_t *get_element_pointer(const_thread_storage_t storage,
                                               index_t idx)
  {
    metal::execution_threads t = scope();
    int threads = t.size();
    __tensor_ops_detail::__tensor_ops_datatype dataType = __tensor_ops_detail::__type_to_tensor_ops_datatype<element_t>::value;

    return (thread element_t *)
        __tensorops_impl_conv2d_cooperative_destination_tensor_elements(
            (thread_storage_t)storage, idx, dataType, threads);
  }

  static index_t get_element_index(thread_storage_t storage,
                                   const thread element_type *element) {
      
    metal::execution_threads t = scope();
    int threads = t.size();
    __tensor_ops_detail::__tensor_ops_datatype dataType = __tensor_ops_detail::__type_to_tensor_ops_datatype<element_t>::value;
    return __tensorops_impl_conv2d_cooperative_destination_tensor_get_element_index(descriptor, (__tensor_ops_detail::__thread_void_t)storage, (const thread void*)element, dataType, threads);
  }

  static bool is_valid_element(const_thread_storage_t storage, index_t idx)
  {
    metal::execution_threads t = scope();
    int threads = t.size();
    __tensor_ops_detail::__tensor_ops_datatype dataType = __tensor_ops_detail::__type_to_tensor_ops_datatype<element_t>::value;

    return __tensorops_impl_conv2d_cooperative_destination_tensor_is_valid_element(
        descriptor, (__tensor_ops_detail::__thread_void_t)storage, idx,
        dataType, threads);
  }

  template <typename index_t, __tensor_ops_detail::__rank_t rank>
  static metal::array<index_t, rank>
  get_multidimensional_index(const_thread_storage_t storage, index_t idx)
  {

    metal::execution_threads t = scope();
    int threads = t.size();

    static_assert(rank == 4, "multidimensional_indices returns 4D indices");

    __tensor_ops_detail::__tensor_ops_datatype dataType = __tensor_ops_detail::__type_to_tensor_ops_datatype<element_t>::value;
    if constexpr (__tensor_ops_detail::__is_same_v<coord_t, ushort>)
    {
      ushort coords[4];
      __tensorops_impl_conv2d_cooperative_destination_tensor_get_coordinate(
          descriptor, (__tensor_ops_detail::__thread_void_t)storage, idx,
          dataType, coords, __tensor_ops_detail::__tensor_ops_datatype_uint16,
          threads);
      return {coords[0], coords[1], coords[2], coords[3]};
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<coord_t, short>)
    {
      short coords[4];
      __tensorops_impl_conv2d_cooperative_destination_tensor_get_coordinate(
          descriptor, (__tensor_ops_detail::__thread_void_t)storage, idx,
          dataType, coords, __tensor_ops_detail::__tensor_ops_datatype_int16,
          threads);
      return {coords[0], coords[1], coords[2], coords[3]};
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<coord_t, uint>)
    {
      uint coords[4];
      __tensorops_impl_conv2d_cooperative_destination_tensor_get_coordinate(
          descriptor, (__tensor_ops_detail::__thread_void_t)storage, idx,
          dataType, coords, __tensor_ops_detail::__tensor_ops_datatype_uint32,
          threads);
      return {coords[0], coords[1], coords[2], coords[3]};
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<coord_t, int>)
    {
      int coords[4];
      __tensorops_impl_conv2d_cooperative_destination_tensor_get_coordinate(
          descriptor, (__tensor_ops_detail::__thread_void_t)storage, idx,
          dataType, coords, __tensor_ops_detail::__tensor_ops_datatype_int32,
          threads);
      return {coords[0], coords[1], coords[2], coords[3]};
    }
  }
};

template <convolution2d_descriptor descriptor,
          convolution2d_cooperative_operand operand, typename scope,
          typename activation_operand_type, typename weights_operand_type,
          typename element_type, typename coord_type, typename... coop_args>
using __cooperative_tensor_t = typename __operand_layout<
    descriptor, operand, scope, activation_operand_type, weights_operand_type,
    element_type, coord_type, coop_args...>::cooperative_tensor_t;

template <convolution2d_descriptor descriptor, typename scope,
          typename activation_operand_type, typename weights_operand_type,
          typename element_type, typename coord_type, typename... coop_args>
using __cooperative_tensor_destination_t =
    __cooperative_tensor_t<descriptor,
                           convolution2d_cooperative_operand::destination,
                           scope, activation_operand_type, weights_operand_type,
                           element_type, coord_type, coop_args...>;

template <convolution2d_descriptor descriptor, typename scope,
          typename activation_operand_type, typename weights_operand_type,
          typename element_type, typename coord_type, typename... coop_args>
__cooperative_tensor_destination_t<descriptor, scope, activation_operand_type,
                                   weights_operand_type, element_type,
                                   coord_type, coop_args...>
__get_destination_cooperative_tensor()
{
  return __cooperative_tensor_destination_t<
      descriptor, scope, activation_operand_type, weights_operand_type,
      element_type, coord_type, coop_args...>();
}

#undef EXTERNALLY_DEFINED_ATTR

} // namespace __convolution2d_detail

#endif

#endif // __TensorOpsConvolution2D__
