
// -*- Metal -*-
//===-- MetalTensorOpsMatMul2dImpl
//------------------------------------------------------===//
// Copyright (c) 2025 Apple Inc. All rights reserved
//===----------------------------------------------------------------------===//

#ifndef __MetalTensorOpsMatMul2dImpl__
#define __MetalTensorOpsMatMul2dImpl__

#if defined(__METAL_VERSION__) && defined(__HAVE_TENSOR__)

namespace __mutmul2d_detail
{

#ifndef EXTERNALLY_DEFINED_ATTR
#define EXTERNALLY_DEFINED_ATTR \
  __attribute__((section("air.externally_defined")))
#endif

#define TENSOROPS_EXPORT [[gnu::visibility("default")]]
#define INLINE __attribute__((__always_inline__))

using __matmul2d_descriptor = matmul2d_descriptor;

using __reduction_operation = reduction_operation;

enum class __matmul2d_cooperative_operand_index
{
  left,
  right,
  destination,
};

constexpr bool matmul2d_descriptor_is_equal(matmul2d_descriptor a, matmul2d_descriptor b) {
  return a.m == b.m &&
         a.n == b.n &&
         a.k == b.k &&
         a.transpose_left == b.transpose_left &&
         a.transpose_right == b.transpose_right &&
         a.relaxed_precision == b.relaxed_precision &&
         a.matmul_mode == b.matmul_mode;
}

extern "C" EXTERNALLY_DEFINED_ATTR size_t
__tensorops_impl_matmul2d_op_cooperative_tensor_data_size(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor descriptor,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR uint16_t
__tensorops_impl_matmul2d_op_cooperative_tensor_num_elements(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR thread void *
__tensorops_impl_matmul2d_op_cooperative_tensor_get_element_pointer(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor descriptor,
    __tensor_ops_detail::__thread_void_t,
    uint16_t,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);
extern "C" EXTERNALLY_DEFINED_ATTR thread uint16_t
__tensorops_impl_matmul2d_op_cooperative_tensor_get_element_index(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_get_coordinate(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    uint16_t,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__tensor_ops_datatype,
    int,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_init(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR bool
__tensorops_impl_matmul2d_op_cooperative_tensor_is_valid_element(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    uint16_t,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_copy(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR bool
__tensorops_impl_matmul2d_op_cooperative_tensor_is_compatible_as_input(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);

extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_load_dv_f16(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_load_tg_f16(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_load_dv_i32(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_load_tg_i32(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_load_dv_i8(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_load_tg_i8(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_load_dv_f32(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_load_tg_f32(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_load_dv_b16(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_load_tg_b16(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);

extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_store_dv_f16(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_store_tg_f16(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_store_dv_i32(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_store_tg_i32(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_store_dv_i8(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_store_tg_i8(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_store_dv_f32(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_store_tg_f32(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,

    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_store_dv_b16(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_tensor_store_tg_b16(
    __matmul2d_cooperative_operand_index,
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int threads);

extern "C" EXTERNALLY_DEFINED_ATTR size_t
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_data_size(
    __matmul2d_descriptor,
    int,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR uint16_t
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_num_elements(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    int,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR thread void *
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_get_element_pointer(
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    uint16_t,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);
extern "C" EXTERNALLY_DEFINED_ATTR thread uint16_t
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_get_element_index(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_get_coordinate(
    __matmul2d_descriptor,
    int,
    __tensor_ops_detail::__const_thread_void_t,
    uint16_t,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__tensor_ops_datatype,
    int,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_init(
    __tensor_ops_detail::__thread_void_t,
    __matmul2d_descriptor,
    int,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR bool
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_is_valid_element(
    __matmul2d_descriptor descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    int,
    uint16_t,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    int);
extern "C" EXTERNALLY_DEFINED_ATTR uint16_t
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_map_index(
    __tensor_ops_detail::__const_thread_void_t,
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __matmul2d_descriptor,
    int,
    int,
    uint16_t,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);
extern "C" EXTERNALLY_DEFINED_ATTR bool
__tensorops_impl_matmul2d_op_cooperative_destination_is_iterator_compatible(
    __matmul2d_descriptor,
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);

extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_dv_f16(
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_tg_f16(
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_dv_i32(
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_tg_i32(
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_dv_f32(
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_tg_f32(
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_dv_b16(
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_tg_b16(
    __matmul2d_descriptor,
    __tensor_ops_detail::__thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);

extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_dv_f16(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_tg_f16(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_dv_i32(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_tg_i32(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_dv_f32(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_tg_f32(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_dv_b16(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_tg_b16(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type,
    int,
    int,
    __tensor_ops_detail::__tensor_ops_datatype leftDataType,
    __tensor_ops_detail::__tensor_ops_datatype rightDataType);

extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_destination_reduce_rows_f16(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__thread_void_t,
    half,
    __reduction_operation,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_destination_reduce_rows_f32(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__thread_void_t,
    float,
    __reduction_operation,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_destination_reduce_rows_i32(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__thread_void_t,
    int,
    __reduction_operation,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_destination_reduce_rows_b16(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__thread_void_t,
    bfloat,
    __reduction_operation,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);

extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_destination_reduce_columns_f16(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__thread_void_t,
    half,
    __reduction_operation,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_destination_reduce_columns_f32(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__thread_void_t,
    float,
    __reduction_operation,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_destination_reduce_columns_i32(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__thread_void_t,
    int,
    __reduction_operation,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);
extern "C" EXTERNALLY_DEFINED_ATTR void
__tensorops_impl_matmul2d_op_cooperative_destination_reduce_columns_b16(
    __matmul2d_descriptor,
    __tensor_ops_detail::__const_thread_void_t,
    __tensor_ops_detail::__thread_void_t,
    bfloat,
    __reduction_operation,
    __tensor_ops_detail::__tensor_ops_datatype,
    __tensor_ops_detail::__tensor_ops_datatype);

extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f16_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f16_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_f16_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_i8_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_i8_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_i8_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_i8_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_i8_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_i8_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_i8_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_i8_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_i8_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_i8_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_i8_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_i8_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_i8_tg_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_i8_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_i8_tg_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_i8_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_i8_tg_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_i8_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_dv_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_dv_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_tg_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_tg_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_tg_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_dv_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_dv_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_tg_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_tg_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_tg_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f16_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f16_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_f16_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_f16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f32_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f32_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_f32_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_i8_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_i8_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_i8_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_dv_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_tg_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_dv_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_tg_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_f16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_f16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_f16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_dv_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_tg_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_dv_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_tg_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_f32_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_f32_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_f32_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_dv_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_dv_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_tg_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_tg_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_tg_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_dv_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_dv_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_tg_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_tg_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_tg_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_i8_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_i8_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_i8_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_dv_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_tg_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_dv_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_tg_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_f16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_dv_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_tg_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_dv_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_tg_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f32_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f32_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_f32_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_dv_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_dv_i8_tg_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_dv_i8_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_tg_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_tg_i8_tg_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_tg_i8_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_i8_tg_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_i8_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_dv_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_dv_i8_tg_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_dv_i8_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_tg_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_tg_i8_tg_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_tg_i8_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_i8_tg_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_i8_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_i8_tg_i32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_i8_i32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_i8_tg_i32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_i8_i32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_i8_tg_i32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_i8_i32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_b16_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_b16_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_b16_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_b16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_b16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_b16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f32_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f32_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f32_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_f32_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_i8_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_i8_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_i8_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_i8_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_i8_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_i8_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_i8_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_i8_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_i8_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_i8_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_i8_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_i8_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_i8_tg_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_i8_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_i8_tg_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_i8_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_i8_tg_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_i8_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_i8_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_i8_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_i8_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_i8_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_dv_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f32_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_tg_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_dv_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f32_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_tg_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_b16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_b16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f32_b16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_dv_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_dv_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_tg_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_tg_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_tg_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_dv_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_dv_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_tg_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_tg_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_tg_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_b16_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_b16_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_b16_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_dv_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_i8_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_tg_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_dv_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_i8_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_tg_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_b16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_b16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_i8_b16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_f16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_f16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_f16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_f16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_f16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_f16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_f16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_f16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_b16_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_b16_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_b16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_b16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_b16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_b16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_b16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_b16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_b16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_b16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_b16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_f16(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_dv_f16_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_tg_f16_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_f32(thread matmul2d_descriptor & desc, thread void *left, thread void *right, thread void *destination, int threads);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_f16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_f16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_f16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_f16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_i8_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_i8_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_i8_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_i8_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_i8_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_i8_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_i8_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_i8_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_i8_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_tg_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_tg_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_dv_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_tg_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_tg_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_f16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_f16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_f16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_f16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_i8_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_i8_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_i8_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_i8_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_tg_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_tg_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_dv_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_tg_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_tg_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_i8_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_i8_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_i8_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_i8_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_i8_tg_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_tg_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_tg_i8_tg_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_dv_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_dv_i8_tg_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_tg_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_tg_i8_tg_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_i8_th_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_i8_th_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_i8_th_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_i8_dv_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_i8_th_i32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_b16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_b16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_b16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_b16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_f32_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f32_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f32_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_i8_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_i8_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_i8_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_i8_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_i8_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_i8_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_i8_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_i8_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_i8_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_i8_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_i8_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_i8_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_i8_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_i8_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_i8_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f32_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_tg_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_tg_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_dv_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_tg_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_tg_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_b16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_b16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_b16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_b16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_i8_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_f16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_f16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_f16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_f16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_dv_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_b16_tg_f16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_b16_tg_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_b16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_b16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_b16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_b16_dv_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_b16_th_b16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_b16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_b16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_b16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_b16_tg_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_b16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_b16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_b16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_b16_dv_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_b16_th_f16(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_dv_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_tg_f16_tg_b16_tg_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_b16_dv_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);
extern "C" EXTERNALLY_DEFINED_ATTR void __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_b16_th_f32(thread matmul2d_descriptor & desc, thread void *left, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType, thread void *right, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType, thread void *destination, __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType);

template <__matmul2d_descriptor descriptor,
          __matmul2d_cooperative_operand_index operand_index,
          typename scope,
          typename left_element_type,
          typename right_element_type,
          typename destination_element_type,
          typename coord_type,
          typename... args>
struct __operand_layout
{
    static_assert(__tensor_ops_detail::__is_same_v<left_element_type, int8_t> ||
                  __tensor_ops_detail::__is_same_v<left_element_type, float> ||
#if __HAVE_BFLOAT__
                  __tensor_ops_detail::__is_same_v<left_element_type, bfloat> ||
#endif
                  __tensor_ops_detail::__is_same_v<left_element_type, half>,
                  "cooperative tensor source data type can only be one of "
                  "int8_t/float/half/bfloat");

    static_assert(__tensor_ops_detail::__is_same_v<right_element_type, int8_t> ||
                  __tensor_ops_detail::__is_same_v<right_element_type, float> ||
#if __HAVE_BFLOAT__
                  __tensor_ops_detail::__is_same_v<right_element_type, bfloat> ||
#endif
                  __tensor_ops_detail::__is_same_v<right_element_type, half>,
                  "cooperative tensor source data type can only be one of "
                  "int8_t/float/half/bfloat");

    static_assert(__tensor_ops_detail::__is_same_v<destination_element_type, float> ||
                  __tensor_ops_detail::__is_same_v<destination_element_type, half> ||
#if __HAVE_BFLOAT__
                  __tensor_ops_detail::__is_same_v<destination_element_type, bfloat> ||
#endif
                  __tensor_ops_detail::__is_same_v<destination_element_type, int32_t>,
                  "cooperative tensor destination data type can only be one of "
                  "float/half/bfloat/int32_t");

  static constant constexpr __tensor_ops_detail::__rank_t rank = 2;
  using element_t = metal::conditional_t<operand_index == __matmul2d_cooperative_operand_index::left, left_element_type,
                        metal::conditional_t<operand_index == __matmul2d_cooperative_operand_index::right, right_element_type,
                        destination_element_type>>;
  using destination_element_t = destination_element_type;
  using coord_t = coord_type;
  using extent_t = metal::dextents<coord_t, rank>;
  using thread_storage_t = thread void *;
  using const_thread_storage_t = const thread void *;
  using index_t = uint16_t;
  using operand_layout_t =
      __operand_layout<descriptor, operand_index, scope, left_element_type, right_element_type, destination_element_type, coord_t>;
  using cooperative_tensor_t =
      metal::cooperative_tensor<element_t, extent_t, operand_layout_t>;
  using scope_t = scope;

  using left_element_t = left_element_type;
  using right_element_t = right_element_type;

  static_assert(__tensor_ops_detail::__is_tensorops_execution_scope_v<scope>,
                "scope should be of type __tensorops_scope");

  static constexpr constant __matmul2d_cooperative_operand_index __operand_index = operand_index;
  static constexpr constant bool __is_matmul2d_cooperative_tensor_layout = true;

  static constexpr constant __matmul2d_descriptor matmul2d_desc = descriptor;

  // Returns the alignment of the storage allocated in each thread
  // for this cooperative_tensor.
  static constexpr size_t thread_storage_align()
  {
    return alignof(element_t);
  };

  // Copy-constructs from the cooperative_tensor `other`.
  static void copy_construct(thread void *this_, thread void *other)
  {
    thread element_t *this_e = (thread element_t *)(this_);
    thread element_t *other_e = (thread element_t *)(other);
    for (size_t i = 0, e = get_capacity(this_); i != e; ++i)
    {
      other_e[i] = this_e[i];
    }
  };

  // Move-constructs from the cooperative_tensor `other`.
  static void move_construct(thread void *this_, thread void *other)
  {
    thread element_t *this_e = (thread element_t *)(this_);
    thread element_t *other_e = this_e;
  };

  // Copy-assigns from the cooperative_tensor `other`.
  static void copy_assign(thread void *this_, thread void *other)
  {
    thread element_t *this_e = (thread element_t *)(this_);
    thread element_t *other_e = (thread element_t *)(other);
    for (size_t i = 0, e = get_capacity(this_); i != e; ++i)
    {
      other_e[i] = this_e[i];
    }
  };

  // Move-assigns from the cooperative_tensor `other`.
  static void move_assign(thread void *this_, thread void *other)
  {
    thread element_t *this_e = (thread element_t *)(this_);
    thread element_t *other_e = this_e;
  };

  // Destroys the per-thread object.
  static void destroy(thread void *) {};

  static size_t thread_storage_size()
  {
    metal::execution_threads t = scope();
    int threads = t.size();

    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype destinationDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<destination_element_t>::value;

    return __tensorops_impl_matmul2d_op_cooperative_tensor_data_size(
        operand_index, descriptor, leftDataType, rightDataType, destinationDataType, threads);
  }

  template <class ElemType, class Extents, class Descriptor, class... Tags>
  static void load(thread_storage_t storage,
                   const thread metal::tensor<ElemType, Extents, Descriptor,
                                              Tags...> &sourceT)
  {
    using elem_t = __tensor_ops_detail::__remove_addrspace_t<ElemType>;

    static_assert(__tensor_ops_detail::__is_same_v<elem_t, element_t>,
                  "Source tensor datatype does not match cooperative tensor");
    static_assert(Extents::rank() == 1 || Extents::rank() == 2,
                  "Source tensor must be rank 1 or 2");

    int sourceRank = Extents::rank();

    metal::execution_threads t = scope();
    int threads = t.size();

    __matmul2d_descriptor desc = descriptor;

    using tensorType = metal::tensor<ElemType, Extents, Descriptor, Tags...>;

    using sourcePtrType = typename tensorType::data_handle_type;

    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type sourceDescType =
        __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<
            tensorType>();

    const thread void *source = (const thread void *)(&sourceT);

    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype destinationDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<destination_element_t>::value;

    if constexpr (__tensor_ops_detail::__is_same_v<elem_t, half>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_load_dv_f16(
            operand_index, desc, storage, source, sourceDescType, sourceRank, leftDataType,
            rightDataType, destinationDataType, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_load_tg_f16(
            operand_index, desc, storage, source, sourceDescType, sourceRank, leftDataType,
            rightDataType, destinationDataType, threads);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<sourcePtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, int32_t>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_load_dv_i32(
            operand_index, desc, storage, source, sourceDescType, sourceRank, leftDataType,
            rightDataType, destinationDataType, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_load_tg_i32(
            operand_index, desc, storage, source, sourceDescType, sourceRank, leftDataType,
            rightDataType, destinationDataType, threads);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<sourcePtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, float>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_load_dv_f32(
            operand_index, desc, storage, source, sourceDescType, sourceRank, leftDataType,
            rightDataType, destinationDataType, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_load_tg_f32(
            operand_index, desc, storage, source, sourceDescType, sourceRank, leftDataType,
            rightDataType, destinationDataType, threads);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<sourcePtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, bfloat>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_load_dv_b16(
            operand_index, desc, storage, source, sourceDescType, sourceRank, leftDataType,
            rightDataType, destinationDataType, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_load_tg_b16(
            operand_index, desc, storage, source, sourceDescType, sourceRank, leftDataType,
            rightDataType, destinationDataType, threads);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<sourcePtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, int8_t>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_load_dv_i8(
            operand_index, desc, storage, source, sourceDescType, sourceRank, leftDataType,
            rightDataType, destinationDataType, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_load_tg_i8(
            operand_index, desc, storage, source, sourceDescType, sourceRank, leftDataType,
            rightDataType, destinationDataType, threads);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<sourcePtrType>,
                      "Unsupported address space");
    }
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

    static_assert(__tensor_ops_detail::__is_same_v<elem_t, element_t>,
                  "Tensor datatype does not match cooperative tensor");
    static_assert(Extents::rank() == 1 || Extents::rank() == rank,
                  "Tensor must be rank 1 or 2");

    __matmul2d_descriptor desc = descriptor;

    metal::execution_threads t = scope();
    int threads = t.size();

    using tensorType = metal::tensor<ElemType, Extents, Descriptor, Tags...>;

    using destinationPtrType = typename tensorType::data_handle_type;

    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destinationDescType =
            __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<
                tensorType>();

    const thread void *destination = (const thread void *)(&destinationT);

    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype destinationDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<destination_element_t>::value;

    if constexpr (__tensor_ops_detail::__is_same_v<elem_t, half>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_store_dv_f16(
            operand_index, desc, storage, destination, destinationDescType, leftDataType,
            rightDataType, destinationDataType, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_store_tg_f16(
            operand_index, desc, storage, destination, destinationDescType, leftDataType,
            rightDataType, destinationDataType, threads);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, int32_t>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_store_dv_i32(
            operand_index, desc, storage, destination, destinationDescType, leftDataType,
            rightDataType, destinationDataType, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_store_tg_i32(
            operand_index, desc, storage, destination, destinationDescType, leftDataType,
            rightDataType, destinationDataType, threads);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, float>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_store_dv_f32(
            operand_index, desc, storage, destination, destinationDescType, leftDataType,
            rightDataType, destinationDataType, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_store_tg_f32(
            operand_index, desc, storage, destination, destinationDescType, leftDataType,
            rightDataType, destinationDataType, threads);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, bfloat>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_store_dv_b16(
            operand_index, desc, storage, destination, destinationDescType, leftDataType,
            rightDataType, destinationDataType, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_store_tg_b16(
            operand_index, desc, storage, destination, destinationDescType, leftDataType,
            rightDataType, destinationDataType, threads);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, int8_t>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_store_dv_i8(
            operand_index, desc, storage, destination, destinationDescType, leftDataType,
            rightDataType, destinationDataType, threads);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_tensor_store_tg_i8(
            operand_index, desc, storage, destination, destinationDescType, leftDataType,
            rightDataType, destinationDataType, threads);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>,
                      "Unsupported address space");
    }
    else
      static_assert(__tensor_ops_detail::__assert_false_v<elem_t>,
                    "Unsupported type");
  };

  static uint16_t get_capacity(const_thread_storage_t storage)
  {
    metal::execution_threads t = scope();
    int threads = t.size();

    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_element_t>::value;

    return __tensorops_impl_matmul2d_op_cooperative_tensor_num_elements(
        operand_index, descriptor, storage, leftDataType, rightDataType, threads);
  }

  static thread element_t *get_element_pointer(const_thread_storage_t storage,
                                               index_t idx)
  {
    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype destinationDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<destination_element_t>::value;

    return (thread element_t *)
        __tensorops_impl_matmul2d_op_cooperative_tensor_get_element_pointer(
            operand_index, descriptor, (thread_storage_t)storage, idx, leftDataType,
            rightDataType, destinationDataType);
  }

  static index_t get_element_index(const_thread_storage_t storage,
                                   const thread element_t *element)
  {
    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype destinationDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<destination_element_t>::value;

    return (index_t)
        __tensorops_impl_matmul2d_op_cooperative_tensor_get_element_index(
            operand_index, descriptor, (thread_storage_t)storage, element, leftDataType,
            rightDataType, destinationDataType);
  }

  static bool is_valid_element(const_thread_storage_t storage, index_t idx)
  {
    metal::execution_threads t = scope();
    int threads = t.size();

    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype destinationDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<destination_element_t>::value;

    return __tensorops_impl_matmul2d_op_cooperative_tensor_is_valid_element(
        operand_index, descriptor, (__tensor_ops_detail::__thread_void_t)storage, idx,
        leftDataType, rightDataType, destinationDataType, threads);
  }

  template <typename index_t, __tensor_ops_detail::__rank_t rank = 2>
  static metal::array<index_t, rank>
  get_multidimensional_index(const_thread_storage_t storage, index_t idx)
  {
    metal::execution_threads t = scope();
    int threads = t.size();

    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype destinationDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<destination_element_t>::value;

    if constexpr (__tensor_ops_detail::__is_same_v<coord_t, ushort>)
    {
      ushort coords[2];
      __tensorops_impl_matmul2d_op_cooperative_tensor_get_coordinate(
          operand_index, descriptor, (__tensor_ops_detail::__const_thread_void_t)storage, idx,
          coords, __tensor_ops_detail::__tensor_ops_datatype_uint16,
          threads, leftDataType, rightDataType, destinationDataType);
      return {coords[0], coords[1]};
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<coord_t, short>)
    {
      short coords[2];
      __tensorops_impl_matmul2d_op_cooperative_tensor_get_coordinate(
          operand_index, descriptor, (__tensor_ops_detail::__const_thread_void_t)storage, idx,
          coords, __tensor_ops_detail::__tensor_ops_datatype_int16,
          threads, leftDataType, rightDataType, destinationDataType);
      return {coords[0], coords[1]};
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<coord_t, uint>)
    {
      uint coords[2];
      __tensorops_impl_matmul2d_op_cooperative_tensor_get_coordinate(
          operand_index, descriptor, (__tensor_ops_detail::__const_thread_void_t)storage, idx,
          coords, __tensor_ops_detail::__tensor_ops_datatype_uint32,
          threads, leftDataType, rightDataType, destinationDataType);
      return {coords[0], coords[1]};
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<coord_t, int>)
    {
      int coords[2];
      __tensorops_impl_matmul2d_op_cooperative_tensor_get_coordinate(
          operand_index, descriptor, (__tensor_ops_detail::__const_thread_void_t)storage, idx,
          coords, __tensor_ops_detail::__tensor_ops_datatype_int32,
          threads, leftDataType, rightDataType, destinationDataType);
      return {coords[0], coords[1]};
    }
    else {
        static_assert(__tensor_ops_detail::__assert_false_v<coord_t>,
                    "unsupported coordinate data type");
    }
  }

  static void construct(thread_storage_t storage)
  {
    metal::execution_threads t = scope();
    int threads = t.size();

    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype destinationDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<destination_element_t>::value;

    __tensorops_impl_matmul2d_op_cooperative_tensor_init(
        operand_index, descriptor, (__tensor_ops_detail::__thread_void_t)storage, leftDataType,
        rightDataType, destinationDataType, threads);
  }
};

template <__matmul2d_descriptor descriptor,
          __matmul2d_cooperative_operand_index operand_index, typename scope,
          typename left_element_type, typename right_element_type, typename element_type, typename coord_type, typename... args>
using __cooperative_tensor_t =
    typename __operand_layout<descriptor, operand_index, scope, left_element_type, right_element_type, element_type,
                              coord_type, args...>::cooperative_tensor_t;

template <__matmul2d_descriptor descriptor, typename scope, typename left_operand, typename right_operand,
          typename element_type, typename coord_type, typename... args>
using __cooperative_tensor_destination_t =
    __cooperative_tensor_t<descriptor,
                           __matmul2d_cooperative_operand_index::destination,
                           scope,
                           typename __tensor_ops_detail::__remove_addrspace_t<__tensor_ops_detail::__remove_reference_t<left_operand>>::value_type,
                           typename __tensor_ops_detail::__remove_addrspace_t<__tensor_ops_detail::__remove_reference_t<right_operand>>::value_type,
                           element_type, coord_type, args...>;

template <__matmul2d_descriptor descriptor, typename scope,
          typename left_operand, typename right_operand, typename element_type, typename coord_type,  typename... args>
__cooperative_tensor_destination_t<descriptor, scope, left_operand, right_operand, element_type, coord_type,
                                   args...>
__get_destination_cooperative_tensor()
{
  static_assert(__tensor_ops_detail::__is_tensorops_execution_scope_v<scope>,
                "scope should be of type __tensorops_scope");
  return __cooperative_tensor_destination_t<descriptor, scope, left_operand, right_operand, element_type,
                                            coord_type, args...>();
}

template <__matmul2d_descriptor descriptor, typename scope, typename left_element_type, typename right_element_type,
          typename element_type, typename coord_type, typename... args>
using __cooperative_tensor_left_input_t =
    __cooperative_tensor_t<descriptor,
                           __matmul2d_cooperative_operand_index::left,
                           scope,
                           left_element_type,
                           right_element_type,
                           element_type, coord_type, args...>;

template <__matmul2d_descriptor descriptor, typename scope, typename left_element_type, typename right_element_type,
          typename element_type, typename coord_type, typename... args>
__cooperative_tensor_left_input_t<descriptor, scope, left_element_type, right_element_type, element_type, coord_type, args...>
__get_left_input_cooperative_tensor()
{
    static_assert(__tensor_ops_detail::__is_same_v<scope, metal::execution_simdgroup>,
                  "Input cooperative tensors require a single SIMD group");
    static_assert(__tensor_ops_detail::__is_same_v<coord_type, int>, "coord_type must be int");

  return __cooperative_tensor_left_input_t<descriptor, scope, left_element_type, right_element_type,
                                     element_type, coord_type, args...>();
}

template <typename src_elem_type, class src_extents, class src_layout, __matmul2d_descriptor descriptor, typename scope, typename left_element_type, typename right_element_type,
          typename element_type, typename coord_type, typename... args>
__cooperative_tensor_left_input_t<descriptor, scope, left_element_type, right_element_type, element_type, coord_type, args...>
__get_left_input_cooperative_tensor(const thread metal::cooperative_tensor<src_elem_type, src_extents, src_layout> & src)
{
    static_assert(__tensor_ops_detail::__is_same_v<typename src_layout::scope_t, metal::execution_simdgroup>,
                  "Input cooperative tensors require a single SIMD group");

    static_assert(src_layout::__is_matmul2d_cooperative_tensor_layout,
                  "Source must be matmul2d cooperative destination tensor");
    static_assert(src_layout::__operand_index == __matmul2d_cooperative_operand_index::destination,
                  "Source must be matmul2d cooperative destination tensor");
    static_assert(__tensor_ops_detail::__is_same_v<typename src_layout::scope_t, metal::execution_simdgroup>,
                  "Input cooperative tensors require a single SIMD group");
    static_assert(__tensor_ops_detail::__is_same_v<scope, metal::execution_simdgroup>,
                  "Input cooperative tensors require a single SIMD group");
    static_assert(src_extents::rank() == 2, "Source rank must be 2");
    static_assert(__tensor_ops_detail::__is_same_v<typename src_extents::index_type, int>, "src_extents::index_type must be int");
    static_assert(__tensor_ops_detail::__is_same_v<coord_type, int>, "coord_type must be int");

    static_assert(__tensor_ops_detail::__is_same_v<src_elem_type, left_element_type>,
                  "Source cooperative tensor element type must match matmul2d left input element type");
    
    constexpr __matmul2d_descriptor dstDesc = descriptor;
    constexpr __matmul2d_descriptor srcDesc = src_layout::matmul2d_desc;

    static_assert(dstDesc.k != static_cast<int>(metal::dynamic_extent) && dstDesc.k != dynamic_length_v<int>,
                  "Inner dimension cannot be dynamic with input cooperative tensors");

    static_assert(dstDesc.transpose_left ? (srcDesc.n == dstDesc.m) : (srcDesc.m == dstDesc.m), "Source height must match matmul2d op height");
    static_assert(dstDesc.transpose_left ? (srcDesc.m == dstDesc.k) : (srcDesc.n == dstDesc.k), "Source width must match matmul2d op inner dimension");

    static_assert(!dstDesc.transpose_left, "Input cooperative tensor cannot be transposed");

    auto dst = __cooperative_tensor_left_input_t<descriptor, scope, left_element_type, right_element_type,
                                                   element_type, coord_type, args...>();

    thread void *dstStorage = (thread void *)&dst[__tensor_ops_detail::__tensor_ops_reserved_index];
    const thread void *srcStorage = (const thread void *)&src[__tensor_ops_detail::__tensor_ops_reserved_index];

    __tensor_ops_detail::__tensor_ops_datatype dstLeftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_element_type>::value;
    __tensor_ops_detail::__tensor_ops_datatype dstRightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_element_type>::value;
    __tensor_ops_detail::__tensor_ops_datatype dstElementDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<element_type>::value;

    __tensor_ops_detail::__tensor_ops_datatype srcLeftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename src_layout::left_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype srcRightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename src_layout::right_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype srcElementDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<src_elem_type>::value;

    __tensorops_impl_matmul2d_op_cooperative_tensor_copy(
        __matmul2d_cooperative_operand_index::left,
        dstDesc,
        srcDesc,
        dstStorage,
        srcStorage,
        dstLeftDataType,
        dstRightDataType,
        dstElementDataType,
        srcLeftDataType,
        srcRightDataType,
        srcElementDataType,
        32);

    return dst;
}

template <__matmul2d_descriptor descriptor, typename scope, typename left_element_type, typename right_element_type,
          typename element_type, typename coord_type, typename... args>
using __cooperative_tensor_right_input_t =
    __cooperative_tensor_t<descriptor,
                           __matmul2d_cooperative_operand_index::right,
                           scope,
                           left_element_type,
                           right_element_type,
                           element_type, coord_type, args...>;

template <__matmul2d_descriptor descriptor, typename scope, typename left_element_type, typename right_element_type,
          typename element_type, typename coord_type, typename... args>
__cooperative_tensor_right_input_t<descriptor, scope, left_element_type, right_element_type, element_type, coord_type, args...>
__get_right_input_cooperative_tensor()
{
  static_assert(__tensor_ops_detail::__is_same_v<scope, metal::execution_simdgroup>,
                "Input cooperative tensors require a single SIMD group");
  static_assert(__tensor_ops_detail::__is_same_v<coord_type, int>, "coord_type must be int");
  
  return __cooperative_tensor_right_input_t<descriptor, scope, left_element_type, right_element_type,
                                     element_type, coord_type, args...>();
}

template <typename src_elem_type, class src_extents, class src_layout, __matmul2d_descriptor descriptor, typename scope, typename left_element_type, typename right_element_type,
          typename element_type, typename coord_type, typename... args>
__cooperative_tensor_right_input_t<descriptor, scope, left_element_type, right_element_type, element_type, coord_type, args...>
__get_right_input_cooperative_tensor(const thread metal::cooperative_tensor<src_elem_type, src_extents, src_layout> & src)
{
    static_assert(src_layout::__is_matmul2d_cooperative_tensor_layout,
                  "Source must be matmul2d cooperative destination tensor");
    static_assert(src_layout::__operand_index == __matmul2d_cooperative_operand_index::destination,
                  "Source must be matmul2d cooperative destination tensor");
    static_assert(__tensor_ops_detail::__is_same_v<typename src_layout::scope_t, metal::execution_simdgroup>,
                  "Input cooperative tensors require a single SIMD group");
    static_assert(__tensor_ops_detail::__is_same_v<scope, metal::execution_simdgroup>,
                  "Input cooperative tensors require a single SIMD group");
    static_assert(src_extents::rank() == 2, "Source rank must be 2");
    static_assert(__tensor_ops_detail::__is_same_v<src_elem_type, right_element_type>,
                  "Source cooperative tensor element type must match matmul2d right input element type");
    static_assert(__tensor_ops_detail::__is_same_v<typename src_extents::index_type, int>, "src_extents::index_type must be int");
    static_assert(__tensor_ops_detail::__is_same_v<coord_type, int>, "coord_type must be int");
    
    constexpr __matmul2d_descriptor dstDesc = descriptor;
    constexpr __matmul2d_descriptor srcDesc = src_layout::matmul2d_desc;

    static_assert(dstDesc.k != static_cast<int>(metal::dynamic_extent) && dstDesc.k != dynamic_length_v<int>,
                  "Inner dimension cannot be dynamic with input cooperative tensors");

    static_assert(dstDesc.transpose_right ? (srcDesc.n == dstDesc.k) : (srcDesc.m == dstDesc.k), "Source height must match matmul2d op inner dimension");
    static_assert(dstDesc.transpose_right ? (srcDesc.m == dstDesc.n) : (srcDesc.n == dstDesc.n), "Source width must match matmul2d op width");

    static_assert(!dstDesc.transpose_right, "Input cooperative tensor cannot be transposed");

    auto dst = __cooperative_tensor_right_input_t<descriptor, scope, left_element_type, right_element_type,
                                                element_type, coord_type, args...>();

    thread void *dstStorage = (thread void *)&dst[__tensor_ops_detail::__tensor_ops_reserved_index];
    const thread void *srcStorage = (const thread void *)&src[__tensor_ops_detail::__tensor_ops_reserved_index];

    __tensor_ops_detail::__tensor_ops_datatype dstLeftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_element_type>::value;
    __tensor_ops_detail::__tensor_ops_datatype dstRightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_element_type>::value;
    __tensor_ops_detail::__tensor_ops_datatype dstElementDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<element_type>::value;

    __tensor_ops_detail::__tensor_ops_datatype srcLeftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename src_layout::left_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype srcRightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename src_layout::right_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype srcElementDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<src_elem_type>::value;

    __tensorops_impl_matmul2d_op_cooperative_tensor_copy(
        __matmul2d_cooperative_operand_index::right,
        dstDesc,
        srcDesc,
        dstStorage,
        srcStorage,
        dstLeftDataType,
        dstRightDataType,
        dstElementDataType,
        srcLeftDataType,
        srcRightDataType,
        srcElementDataType,
        32);

    return dst;
}

template <typename left_element_type, typename right_element_type, typename element_type,
          __matmul2d_descriptor descriptor, typename scope, class src_elem_type, class src_extents, class src_layout>
inline bool __is_compatible_as_left_input(
    const thread metal::cooperative_tensor<src_elem_type, src_extents, src_layout> & src)
{
    static_assert(src_layout::__is_matmul2d_cooperative_tensor_layout,
                  "Source must be matmul2d cooperative destination tensor");
    static_assert(src_layout::__operand_index == __matmul2d_cooperative_operand_index::destination,
                  "Source must be matmul2d cooperative destination tensor");
    static_assert(__tensor_ops_detail::__is_same_v<typename src_layout::scope_t, metal::execution_simdgroup>,
                  "Input cooperative tensors require a single SIMD group");
    static_assert(__tensor_ops_detail::__is_same_v<scope, metal::execution_simdgroup>,
                  "Input cooperative tensors require a single SIMD group");
    static_assert(src_extents::rank() == 2, "Source rank must be 2");
    static_assert(__tensor_ops_detail::__is_same_v<src_elem_type, left_element_type>,
                  "Source cooperative tensor element type must match matmul2d left input element type");
    static_assert(__tensor_ops_detail::__is_same_v<typename src_extents::index_type, int>, "src_extents::index_type must be int");
    
    constexpr __matmul2d_descriptor dstDesc = descriptor;
    constexpr __matmul2d_descriptor srcDesc = src_layout::matmul2d_desc;

    static_assert(dstDesc.k != static_cast<int>(metal::dynamic_extent) && dstDesc.k != dynamic_length_v<int>,
                  "Inner dimension cannot be dynamic with input cooperative tensors");

    static_assert(dstDesc.transpose_left ? (srcDesc.n == dstDesc.m) : (srcDesc.m == dstDesc.m), "Source height must match matmul2d op height");
    static_assert(dstDesc.transpose_left ? (srcDesc.m == dstDesc.k) : (srcDesc.n == dstDesc.k), "Source width must match matmul2d op inner dimension");

    static_assert(!dstDesc.transpose_left, "Input cooperative tensor cannot be transposed");

    const thread void *srcStorage = (const thread void *)&src[__tensor_ops_detail::__tensor_ops_reserved_index];

    __tensor_ops_detail::__tensor_ops_datatype dstLeftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_element_type>::value;
    __tensor_ops_detail::__tensor_ops_datatype dstRightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_element_type>::value;
    __tensor_ops_detail::__tensor_ops_datatype dstElementDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<element_type>::value;

    __tensor_ops_detail::__tensor_ops_datatype srcLeftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename src_layout::left_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype srcRightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename src_layout::right_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype srcElementDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<src_elem_type>::value;

    return __tensorops_impl_matmul2d_op_cooperative_tensor_is_compatible_as_input(
        __matmul2d_cooperative_operand_index::left,
        dstDesc,
        srcDesc,
        srcStorage,
        dstLeftDataType,
        dstRightDataType,
        dstElementDataType,
        srcLeftDataType,
        srcRightDataType,
        srcElementDataType,
        32);
}

template <typename left_element_type, typename right_element_type, typename element_type,
          __matmul2d_descriptor descriptor, typename scope, class src_elem_type, class src_extents, class src_layout>
inline bool __is_compatible_as_right_input(
    const thread metal::cooperative_tensor<src_elem_type, src_extents, src_layout> & src)
{
    static_assert(src_layout::__is_matmul2d_cooperative_tensor_layout,
                  "Source must be matmul2d cooperative destination tensor");
    static_assert(src_layout::__operand_index == __matmul2d_cooperative_operand_index::destination,
                  "Source must be matmul2d cooperative destination tensor");
    static_assert(__tensor_ops_detail::__is_same_v<typename src_layout::scope_t, metal::execution_simdgroup>,
                  "Input cooperative tensors require a single SIMD group");
    static_assert(__tensor_ops_detail::__is_same_v<scope, metal::execution_simdgroup>,
                  "Input cooperative tensors require a single SIMD group");
    static_assert(src_extents::rank() == 2, "Source rank must be 2");
    static_assert(__tensor_ops_detail::__is_same_v<src_elem_type, right_element_type>,
                  "Source cooperative tensor element type must match matmul2d right input element type");
    static_assert(__tensor_ops_detail::__is_same_v<typename src_extents::index_type, int>, "src_extents::index_type must be int");
    
    constexpr __matmul2d_descriptor dstDesc = descriptor;
    constexpr __matmul2d_descriptor srcDesc = src_layout::matmul2d_desc;

    static_assert(dstDesc.k != static_cast<int>(metal::dynamic_extent) && dstDesc.k != dynamic_length_v<int>,
                  "Inner dimension cannot be dynamic with input cooperative tensors");

    static_assert(dstDesc.transpose_right ? (srcDesc.n == dstDesc.k) : (srcDesc.m == dstDesc.k), "Source height must match matmul2d op inner dimension");
    static_assert(dstDesc.transpose_right ? (srcDesc.m == dstDesc.n) : (srcDesc.n == dstDesc.n), "Source width must match matmul2d op width");

    static_assert(!dstDesc.transpose_right, "Input cooperative tensor cannot be transposed");

    const thread void *srcStorage = (const thread void *)&src[__tensor_ops_detail::__tensor_ops_reserved_index];

    __tensor_ops_detail::__tensor_ops_datatype dstLeftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_element_type>::value;
    __tensor_ops_detail::__tensor_ops_datatype dstRightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_element_type>::value;
    __tensor_ops_detail::__tensor_ops_datatype dstElementDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<element_type>::value;

    __tensor_ops_detail::__tensor_ops_datatype srcLeftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename src_layout::left_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype srcRightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename src_layout::right_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype srcElementDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<src_elem_type>::value;

    return __tensorops_impl_matmul2d_op_cooperative_tensor_is_compatible_as_input(
        __matmul2d_cooperative_operand_index::right,
        dstDesc,
        srcDesc,
        srcStorage,
        dstLeftDataType,
        dstRightDataType,
        dstElementDataType,
        srcLeftDataType,
        srcRightDataType,
        srcElementDataType,
        32);
}

template <__matmul2d_descriptor descriptor, int reduction_dim, typename scope,
          typename left_operand, typename right_operand,
          typename element_type, typename coord_type, typename... args>
struct __reduction_operand_layout
{
  static_assert(__tensor_ops_detail::__is_same_v<element_type, float> ||
                    __tensor_ops_detail::__is_same_v<element_type, half> ||
                    __tensor_ops_detail::__is_same_v<element_type, bfloat> ||
                    __tensor_ops_detail::__is_same_v<element_type, int32_t>,
                "cooperative tensor data type can only be one of "
                "float/half/bfloat/int32_t");

  static constant constexpr __tensor_ops_detail::__rank_t rank = 1;
  using element_t = element_type;
  using coord_t = coord_type;
  using extent_t = metal::dextents<coord_t, rank>;
  using thread_storage_t = thread void *;
  using const_thread_storage_t = const thread void *;
  using index_t = uint16_t;
  using operand_layout_t =
      __reduction_operand_layout<descriptor, reduction_dim, scope, left_operand,
                                 right_operand, element_t, coord_t>;
  using cooperative_tensor_t =
      metal::cooperative_tensor<element_t, extent_t, operand_layout_t>;
  using scope_t = scope;

  using left_t  = __tensor_ops_detail::__remove_addrspace_t<__tensor_ops_detail::__remove_reference_t<left_operand>>;
  using right_t = __tensor_ops_detail::__remove_addrspace_t<__tensor_ops_detail::__remove_reference_t<right_operand>>;

  using left_elem_t  = typename left_t::element_type;
  using right_elem_t = typename right_t::element_type;

  using left_value_t  = typename left_t::value_type;
  using right_value_t = typename right_t::value_type;

  static_assert(__tensor_ops_detail::__is_tensorops_execution_scope_v<scope>,
                "scope should be of type __tensorops_scope");
  static_assert(reduction_dim == 0 || reduction_dim == 1, "Reduction dimension must be 0 or 1");

  static constexpr constant bool is_matmul2d_reduction_cooperative_destination_layout =
      true;
  static constexpr constant int __reduction_dim = reduction_dim;

  static constexpr constant __matmul2d_descriptor matmul2d_desc = descriptor;

  // Returns the alignment of the storage allocated in each thread
  // for this cooperative_tensor.
  static constexpr size_t thread_storage_align()
  {
    return alignof(element_t);
  };

  // Copy-constructs from the cooperative_tensor `other`.
  static void copy_construct(thread void *this_, thread void *other)
  {
    thread element_t *this_e = (thread element_t *)(this_);
    thread element_t *other_e = (thread element_t *)(other);
    for (size_t i = 0, e = get_capacity(this_); i != e; ++i)
    {
      other_e[i] = this_e[i];
    }
  };

  // Move-constructs from the cooperative_tensor `other`.
  static void move_construct(thread void *this_, thread void *other)
  {
    thread element_t *this_e = (thread element_t *)(this_);
    thread element_t *other_e = this_e;
  };

  // Copy-assigns from the cooperative_tensor `other`.
  static void copy_assign(thread void *this_, thread void *other)
  {
    thread element_t *this_e = (thread element_t *)(this_);
    thread element_t *other_e = (thread element_t *)(other);
    for (size_t i = 0, e = get_capacity(this_); i != e; ++i)
    {
      other_e[i] = this_e[i];
    }
  };

  // Move-assigns from the cooperative_tensor `other`.
  static void move_assign(thread void *this_, thread void *other)
  {
    thread element_t *this_e = (thread element_t *)(this_);
    thread element_t *other_e = this_e;
  };

  // Destroys the per-thread object.
  static void destroy(thread void *) {};

  static size_t thread_storage_size()
  {
    metal::execution_threads t = scope();
    int threads = t.size();
    
    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_value_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_value_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype elementDataType =
        __tensor_ops_detail::__element_type_to_tensor_ops_datatype<element_type>();

    return __tensorops_impl_matmul2d_op_cooperative_reduction_destination_data_size(
        descriptor, reduction_dim, leftDataType, rightDataType, elementDataType, threads);
  }

  template <class ElemType, class Extents, class Descriptor, class... Tags>
  static void load(thread_storage_t storage,
                   const thread metal::tensor<ElemType, Extents, Descriptor,
                                              Tags...> &sourceT)
  {
    using elem_t = __tensor_ops_detail::__remove_addrspace_t<ElemType>;

    static_assert(__tensor_ops_detail::__is_same_v<elem_t, element_t>,
                  "Source tensor datatype does not match cooperative tensor");
    static_assert(Extents::rank() == 1,
                  "Source tensor must be rank 1");

    metal::execution_threads t = scope();
    int threads = t.size();

    __matmul2d_descriptor desc = descriptor;

    using tensorType = metal::tensor<ElemType, Extents, Descriptor, Tags...>;

    using sourcePtrType = typename tensorType::data_handle_type;

    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type sourceDescType =
        __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<
            tensorType>();

    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_value_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_value_t>::value;

    const thread void *source = (const thread void *)(&sourceT);

    if constexpr (__tensor_ops_detail::__is_same_v<elem_t, half>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_dv_f16(
            desc, storage, source, sourceDescType, reduction_dim, threads, leftDataType, rightDataType);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_tg_f16(
            desc, storage, source, sourceDescType, reduction_dim, threads, leftDataType, rightDataType);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<sourcePtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, int32_t>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_dv_i32(
            desc, storage, source, sourceDescType, reduction_dim, threads, leftDataType, rightDataType);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_tg_i32(
            desc, storage, source, sourceDescType, reduction_dim, threads, leftDataType, rightDataType);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<sourcePtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, float>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_dv_f32(
            desc, storage, source, sourceDescType, reduction_dim, threads, leftDataType, rightDataType);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_tg_f32(
            desc, storage, source, sourceDescType, reduction_dim, threads, leftDataType, rightDataType);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<sourcePtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, bfloat>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_dv_b16(
            desc, storage, source, sourceDescType, reduction_dim, threads, leftDataType, rightDataType);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             sourcePtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_load_tg_b16(
            desc, storage, source, sourceDescType, reduction_dim, threads, leftDataType, rightDataType);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<sourcePtrType>,
                      "Unsupported address space");
    }
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

    static_assert(__tensor_ops_detail::__is_same_v<elem_t, element_t>,
                  "Tensor datatype does not match cooperative tensor");
    static_assert(Extents::rank() == 1,
                  "Tensor must be rank 1");

    __matmul2d_descriptor desc = descriptor;

    metal::execution_threads t = scope();
    int threads = t.size();

    using tensorType = metal::tensor<ElemType, Extents, Descriptor, Tags...>;

    using destinationPtrType = typename tensorType::data_handle_type;

    __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
        destinationDescType =
            __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<
                tensorType>();

    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_value_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_value_t>::value;

    const thread void *destination = (const thread void *)(&destinationT);

    if constexpr (__tensor_ops_detail::__is_same_v<elem_t, half>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_dv_f16(
            desc, storage, destination, destinationDescType, reduction_dim, threads, leftDataType, rightDataType);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_tg_f16(
            desc, storage, destination, destinationDescType, reduction_dim, threads, leftDataType, rightDataType);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, int32_t>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_dv_i32(
            desc, storage, destination, destinationDescType, reduction_dim, threads, leftDataType, rightDataType);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_tg_i32(
            desc, storage, destination, destinationDescType, reduction_dim, threads, leftDataType, rightDataType);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, float>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_dv_f32(
            desc, storage, destination, destinationDescType, reduction_dim, threads, leftDataType, rightDataType);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_tg_f32(
            desc, storage, destination, destinationDescType, reduction_dim, threads, leftDataType, rightDataType);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>,
                      "Unsupported address space");
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<elem_t, bfloat>)
    {
      if constexpr (__tensor_ops_detail::__is_device_addrspace_v<
                        destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_dv_b16(
            desc, storage, destination, destinationDescType, reduction_dim, threads, leftDataType, rightDataType);
      else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<
                             destinationPtrType>)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_store_tg_b16(
            desc, storage, destination, destinationDescType, reduction_dim, threads, leftDataType, rightDataType);
      else
        static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>,
                      "Unsupported address space");
    }
    else
      static_assert(__tensor_ops_detail::__assert_false_v<elem_t>,
                    "Unsupported type");
  };

  static uint16_t get_capacity(const_thread_storage_t storage)
  {
    metal::execution_threads t = scope();
    int threads = t.size();

    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_value_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_value_t>::value;

    return __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_num_elements(
        descriptor, storage, reduction_dim, leftDataType, rightDataType, threads);
  }

  static thread element_t *get_element_pointer(const_thread_storage_t storage,
                                               index_t idx)
  {
    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_value_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_value_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype dataType =
        __tensor_ops_detail::__element_type_to_tensor_ops_datatype<element_type>();

    return (thread element_t *)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_get_element_pointer(
            descriptor, (thread_storage_t)storage, idx, leftDataType, rightDataType, dataType);
  }

  static index_t get_element_index(const_thread_storage_t storage,
                                   const thread element_type *element)
  {
    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_value_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_value_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype dataType =
        __tensor_ops_detail::__element_type_to_tensor_ops_datatype<element_type>();

    return (index_t)
        __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_get_element_index(
            descriptor, (thread_storage_t)storage, element, leftDataType, rightDataType, dataType);
  }

  static bool is_valid_element(const_thread_storage_t storage, index_t idx)
  {
    metal::execution_threads t = scope();
    int threads = t.size();

    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_value_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_value_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype dataType =
        __tensor_ops_detail::__element_type_to_tensor_ops_datatype<element_type>();

    return __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_is_valid_element(
        descriptor, (__tensor_ops_detail::__thread_void_t)storage, reduction_dim, idx,
        leftDataType, rightDataType, dataType, threads);
  }

  template <typename index_t, __tensor_ops_detail::__rank_t rank = 1>
  static metal::array<index_t, rank>
  get_multidimensional_index(const_thread_storage_t storage, index_t idx)
  {
    metal::execution_threads t = scope();
    int threads = t.size();

    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_value_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_value_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype elementDataType =
        __tensor_ops_detail::__element_type_to_tensor_ops_datatype<element_type>();

    if constexpr (__tensor_ops_detail::__is_same_v<coord_t, ushort>)
    {
      ushort coords[1];
      __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_get_coordinate(
          descriptor, reduction_dim, (__tensor_ops_detail::__thread_void_t)storage, idx,
          coords, __tensor_ops_detail::__tensor_ops_datatype_uint16,
          threads, leftDataType, rightDataType, elementDataType);
      return { coords[0] };
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<coord_t, short>)
    {
      short coords[1];
      __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_get_coordinate(
          descriptor, reduction_dim, (__tensor_ops_detail::__thread_void_t)storage, idx,
          coords, __tensor_ops_detail::__tensor_ops_datatype_int16,
          threads, leftDataType, rightDataType, elementDataType);
      return { coords[0] };
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<coord_t, uint>)
    {
      uint coords[1];
      __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_get_coordinate(
          descriptor, reduction_dim, (__tensor_ops_detail::__thread_void_t)storage, idx,
          coords, __tensor_ops_detail::__tensor_ops_datatype_uint32,
          threads, leftDataType, rightDataType, elementDataType);
      ;
      return { coords[0] };
    }
    else if constexpr (__tensor_ops_detail::__is_same_v<coord_t, int>)
    {
      int coords[1];
      __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_get_coordinate(
          descriptor, reduction_dim, (__tensor_ops_detail::__thread_void_t)storage, idx,
          coords, __tensor_ops_detail::__tensor_ops_datatype_int32,
          threads, leftDataType, rightDataType, elementDataType);
      return { coords[0] };
    }
    else {
        static_assert(__tensor_ops_detail::__assert_false_v<coord_t>,
                    "unsupported coordinate data type");
    }
  }

  static void construct(thread_storage_t storage)
  {
    metal::execution_threads t = scope();
    int threads = t.size();

    __tensor_ops_detail::__tensor_ops_datatype elementDataType =
        __tensor_ops_detail::__element_type_to_tensor_ops_datatype<element_t>();
    __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<left_value_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<right_value_t>::value;

    __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_init(
        (__tensor_ops_detail::__thread_void_t)storage, descriptor, 
        reduction_dim, leftDataType, rightDataType, elementDataType, threads);
  }

  template <class FromIterator, class ToIterator>
  static uint16_t map_index(const thread void *from_storage, uint16_t from_idx,
                            const thread void *to_storage)
  {
    using sourceLayout = typename FromIterator::layout;
    using destLayout = typename ToIterator::layout;

    static_assert(sourceLayout::__is_matmul2d_cooperative_tensor_layout,
                  "Source must be a matmul2d destination cooperative tensor");
    static_assert(sourceLayout::__operand_index == __matmul2d_cooperative_operand_index::destination,
                  "Source must be a matmul2d destination cooperative tensor");
    static_assert(destLayout::is_matmul2d_reduction_cooperative_destination_layout,
                  "Destination must be a matmul2d reduction destination cooperative tensor");
    static_assert(__tensor_ops_detail::__is_same_v<typename sourceLayout::scope_t, metal::execution_simdgroup>,
                  "map_index requires a single SIMD group");
    static_assert(__tensor_ops_detail::__is_same_v<typename destLayout::scope_t, metal::execution_simdgroup>,
                  "map_index requires a single SIMD group");

    metal::execution_threads t = scope();
    int threads = t.size();

    constexpr __matmul2d_descriptor sourceDesc = sourceLayout::matmul2d_desc;
    constexpr __matmul2d_descriptor destDesc = destLayout::matmul2d_desc;

    static_assert(reduction_dim == 0 || sourceDesc.n == destDesc.n, "Source and destination must have matching N dimension if reduction_dim = 1");
    static_assert(reduction_dim == 1 || sourceDesc.m == destDesc.m, "Source and destination must have matching M dimension if reduction_dim = 0");
    
    static_assert(__tensor_ops_detail::__is_same_v<typename sourceLayout::element_t, typename destLayout::element_t>, "Source and destination element types must match");

    __tensor_ops_detail::__tensor_ops_datatype srcLeftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename sourceLayout::left_element_t>::value;
    __tensor_ops_detail::__tensor_ops_datatype srcRightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename sourceLayout::right_element_t>::value;

    return __tensorops_impl_matmul2d_op_cooperative_reduction_destination_tensor_map_index(
        from_storage, sourceDesc,
        to_storage, destDesc,
        reduction_dim, threads, from_idx,
        srcLeftDataType, srcRightDataType);
  }
};

template <__matmul2d_descriptor descriptor, typename scope,
          typename left_operand, typename right_operand,
          typename element_type, typename coord_type, typename... args>
using __cooperative_tensor_row_reduction_destination_t =
    typename __reduction_operand_layout<descriptor, 0, scope, left_operand, right_operand,
                              element_type, coord_type, args...>::cooperative_tensor_t;

template <__matmul2d_descriptor descriptor, typename scope,
          typename left_operand, typename right_operand,
          typename element_type, typename coord_type, typename... args>
using __cooperative_tensor_column_reduction_destination_t =
    typename __reduction_operand_layout<descriptor, 1, scope, left_operand, right_operand,
                              element_type, coord_type, args...>::cooperative_tensor_t;

template <__matmul2d_descriptor descriptor, typename scope,
          typename left_operand, typename right_operand,
          typename element_type, typename coord_type, typename... args>
__cooperative_tensor_row_reduction_destination_t<descriptor, scope, left_operand, right_operand,
                                                 element_type, coord_type, args...>
__get_row_reduction_destination_cooperative_tensor()
{
  static_assert(__tensor_ops_detail::__is_tensorops_execution_scope_v<scope>,
                "scope should be of type __tensorops_scope");
  return __cooperative_tensor_row_reduction_destination_t<descriptor, scope, left_operand, right_operand,
                                                          element_type, coord_type, args...>();
}

template <__matmul2d_descriptor descriptor, typename scope,
          typename left_operand, typename right_operand,
          typename element_type, typename coord_type, typename... args>
__cooperative_tensor_column_reduction_destination_t<descriptor, scope, left_operand, right_operand,
                                                    element_type, coord_type, args...>
__get_column_reduction_destination_cooperative_tensor()
{
  static_assert(__tensor_ops_detail::__is_tensorops_execution_scope_v<scope>,
                "scope should be of type __tensorops_scope");
  return __cooperative_tensor_column_reduction_destination_t<descriptor, scope, left_operand, right_operand,
                                                             element_type, coord_type, args...>();
}

template<class T>
struct __cooperative_tensor_layout;

template<class T, class E, class L>
struct __cooperative_tensor_layout<metal::cooperative_tensor<T, E, L>> {
    using layout = L;
};

template<class T>
struct __cooperative_tensor_left_elem_type;

template<class T, class E, class L>
struct __cooperative_tensor_left_elem_type<metal::cooperative_tensor<T, E, L>> {
    using type = typename L::left_element_t;
};

template<class T>
struct __cooperative_tensor_right_elem_type;

template<class T, class E, class L>
struct __cooperative_tensor_right_elem_type<metal::cooperative_tensor<T, E, L>> {
    using type = typename L::right_element_t;
};

template<class T>
struct __cooperative_tensor_destination_elem_type;

template<class T, class E, class L>
struct __cooperative_tensor_destination_elem_type<metal::cooperative_tensor<T, E, L>> {
    using type = typename L::destination_element_t;
};

template<__matmul2d_cooperative_operand_index operand_index, class T>
constexpr bool __is_cooperative_tensor_operand() {
    if constexpr (__tensor_ops_detail::__is_cooperative_tensor_type_v<T>) {
        using layout = typename __cooperative_tensor_layout<T>::layout;

        return layout::__is_matmul2d_cooperative_tensor_layout && layout::__operand_index == operand_index;
    }
    else
        return false;
}

template <__matmul2d_descriptor descriptor, typename scope,
          typename left_operand, typename right_operand,
          typename destination_operand, typename... args>
void __run(thread left_operand &leftIn, thread right_operand &rightIn,
           thread destination_operand &destinationT)
{
  using leftTensorType = __tensor_ops_detail::__remove_addrspace_t<
      __tensor_ops_detail::__remove_reference_t<decltype(leftIn)>>;
  using rightTensorType = __tensor_ops_detail::__remove_addrspace_t<
      __tensor_ops_detail::__remove_reference_t<decltype(rightIn)>>;
  using destinationTensorType = __tensor_ops_detail::__remove_addrspace_t<
      __tensor_ops_detail::__remove_reference_t<decltype(destinationT)>>;

  metal::execution_threads t = scope();
  int threads = t.size();

  static_assert(__tensor_ops_detail::__is_tensor_type_v<leftTensorType> ||
                __is_cooperative_tensor_operand<__matmul2d_cooperative_operand_index::left, leftTensorType>(),
                "Left operand must be a tensor or matmul2d left input cooperative tensor");
  static_assert(__tensor_ops_detail::__is_tensor_type_v<rightTensorType> ||
                __is_cooperative_tensor_operand<__matmul2d_cooperative_operand_index::right, rightTensorType>(),
                "Right operand must be a tensor or matmul2d right input cooperative tensor");
  static_assert(__tensor_ops_detail::__is_tensor_type_v<destinationTensorType> ||
                __is_cooperative_tensor_operand<__matmul2d_cooperative_operand_index::destination, destinationTensorType>(),
                "Destination operand must be a tensor or matmul2d destination cooperative tensor");

  static_assert(__tensor_ops_detail::__is_tensorops_execution_scope_v<scope>,
                "scope should be of type __tensorops_scope");

  static_assert(__tensor_ops_detail::__get_rank<leftTensorType>() == 2,
                "Operand must have rank 2");
  static_assert(__tensor_ops_detail::__get_rank<rightTensorType>() == 2,
                "Operand must have rank 2");
  static_assert(__tensor_ops_detail::__get_rank<destinationTensorType>() == 2,
                "Operand must have rank 2");

  static_assert(
      __tensor_ops_detail::__is_same_v<typename leftTensorType::index_type,
                                       int>,
      "Index type must be int");
  static_assert(
      __tensor_ops_detail::__is_same_v<typename rightTensorType::index_type,
                                       int>,
      "Index type must be int");
  static_assert(__tensor_ops_detail::__is_same_v<
                    typename destinationTensorType::index_type, int>,
                "Index type must be int");

  using leftPtrType = typename leftTensorType::data_handle_type;
  using rightPtrType = typename rightTensorType::data_handle_type;
  using destinationPtrType = typename destinationTensorType::data_handle_type;

  using leftValueType = __tensor_ops_detail::__remove_addrspace_t<
      __tensor_ops_detail::__remove_reference_t<
          typename leftTensorType::element_type>>;
  using rightValueType = __tensor_ops_detail::__remove_addrspace_t<
      __tensor_ops_detail::__remove_reference_t<
          typename rightTensorType::element_type>>;
  using destinationValueType = __tensor_ops_detail::__remove_addrspace_t<
      __tensor_ops_detail::__remove_reference_t<
          typename destinationTensorType::element_type>>;

  if constexpr (__tensor_ops_detail::__is_cooperative_tensor_type_v<leftTensorType> ||
                __tensor_ops_detail::__is_cooperative_tensor_type_v<rightTensorType>)
  {
    static_assert(__tensor_ops_detail::__is_same_v<scope, metal::execution_simdgroup>,
                  "Input cooperative tensors require a single SIMD group");
    static_assert(descriptor.k != static_cast<int>(metal::dynamic_extent) && descriptor.k != dynamic_length_v<int>,
                  "Inner dimension cannot be dynamic with input cooperative tensors");
  }

  __matmul2d_descriptor desc = descriptor;

  // Check types declared on cooperative tensors match actual inputs to run()
  if constexpr (__tensor_ops_detail::__is_cooperative_tensor_type_v<leftTensorType>) {
    using _leftType = typename __cooperative_tensor_left_elem_type<leftTensorType>::type;
    using _rightType = typename __cooperative_tensor_right_elem_type<leftTensorType>::type;
    using _destinationType = typename __cooperative_tensor_destination_elem_type<leftTensorType>::type;

    static_assert(__tensor_ops_detail::__is_same_v<_leftType, leftValueType>, "Input types must match cooperative tensor types");
    static_assert(__tensor_ops_detail::__is_same_v<_rightType, rightValueType>, "Input types must match cooperative tensor types");
    static_assert(__tensor_ops_detail::__is_same_v<_destinationType, destinationValueType>, "Input types must match cooperative tensor types");
  }

  if constexpr (__tensor_ops_detail::__is_cooperative_tensor_type_v<rightTensorType>) {
    using _leftType = typename __cooperative_tensor_left_elem_type<rightTensorType>::type;
    using _rightType = typename __cooperative_tensor_right_elem_type<rightTensorType>::type;
    using _destinationType = typename __cooperative_tensor_destination_elem_type<rightTensorType>::type;

    static_assert(__tensor_ops_detail::__is_same_v<_leftType, leftValueType>, "Input types must match cooperative tensor types");
    static_assert(__tensor_ops_detail::__is_same_v<_rightType, rightValueType>, "Input types must match cooperative tensor types");
    static_assert(__tensor_ops_detail::__is_same_v<_destinationType, destinationValueType>, "Input types must match cooperative tensor types");
  }

  if constexpr (__tensor_ops_detail::__is_cooperative_tensor_type_v<destinationTensorType>) {
    using _leftType = typename __cooperative_tensor_left_elem_type<destinationTensorType>::type;
    using _rightType = typename __cooperative_tensor_right_elem_type<destinationTensorType>::type;
    using _destinationType = typename __cooperative_tensor_destination_elem_type<destinationTensorType>::type;

    static_assert(__tensor_ops_detail::__is_same_v<_leftType, leftValueType>, "Input types must match cooperative tensor types");
    static_assert(__tensor_ops_detail::__is_same_v<_rightType, rightValueType>, "Input types must match cooperative tensor types");
    static_assert(__tensor_ops_detail::__is_same_v<_destinationType, destinationValueType>, "Input types must match cooperative tensor types");
  }

  if constexpr (__tensor_ops_detail::__is_cooperative_tensor_type_v<leftTensorType> &&
                __tensor_ops_detail::__is_cooperative_tensor_type_v<rightTensorType>)
  {
    static_assert(descriptor.m == 32 || descriptor.n == 32 || descriptor.k == 32, "At least one of M, N, or K must be 32 if both inputs are cooperative tensors");
    static_assert(descriptor.m == 16 || descriptor.m == 32, "M must be 16 or 32 if both inputs are cooperative tensors");
    static_assert(descriptor.n == 16 || descriptor.n == 32, "N must be 16 or 32 if both inputs are cooperative tensors");
    static_assert(descriptor.k == 16 || descriptor.k == 32, "K must be 16 or 32 if both inputs are cooperative tensors");
  }

  // single thread
  if constexpr (__tensor_ops_detail::__is_same_v<scope, metal::execution_thread>)
  {
    if constexpr (!__tensor_ops_detail::__is_cooperative_tensor_type_v<
                      leftTensorType> &&
                  !__tensor_ops_detail::__is_cooperative_tensor_type_v<
                      rightTensorType> &&
                  !__tensor_ops_detail::__is_cooperative_tensor_type_v<
                      destinationTensorType>)
    {
      thread void *left = (thread void *)(&leftIn);
      thread void *right = (thread void *)(&rightIn);
      thread void *destination = (thread void *)(&destinationT);

      const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType =
          __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<
              leftTensorType>();
      const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType =
          __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<
              rightTensorType>();
      const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type
          destinationDescType =
              __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<
                  destinationTensorType>();

      if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> &&
                    __tensor_ops_detail::__is_same_v<rightValueType, half> &&
                    __tensor_ops_detail::__is_same_v<destinationValueType,
                                                     half>)
      {
        if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_f16_dv_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_f16_dv_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_f16_dv_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_f16_dv_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_f16_th_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_f16_th_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_f16_th_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_f16_th_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else
          static_assert(
              __tensor_ops_detail::__assert_false_v<destinationPtrType>,
              "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType,
                                                          half> &&
                         __tensor_ops_detail::__is_same_v<rightValueType,
                                                          int8_t> &&
                         __tensor_ops_detail::__is_same_v<
                             destinationValueType, half>)
      {
        if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_i8_dv_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_i8_dv_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_i8_dv_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_i8_dv_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_i8_th_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_i8_th_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_i8_th_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_i8_th_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else
          static_assert(
              __tensor_ops_detail::__assert_false_v<destinationPtrType>,
              "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType,
                                                          int8_t> &&
                         __tensor_ops_detail::__is_same_v<rightValueType,
                                                          half> &&
                         __tensor_ops_detail::__is_same_v<
                             destinationValueType, half>)
      {
        if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_f16_dv_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_f16_dv_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_f16_dv_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_f16_dv_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_f16_th_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_f16_th_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_f16_th_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_f16_th_f16(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else
          static_assert(
              __tensor_ops_detail::__assert_false_v<destinationPtrType>,
              "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType,
                                                          half> &&
                         __tensor_ops_detail::__is_same_v<rightValueType,
                                                          half> &&
                         __tensor_ops_detail::__is_same_v<
                             destinationValueType, float>)
      {
        if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_f16_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_f16_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_f16_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_f16_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_f16_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_f16_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_f16_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_f16_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else
          static_assert(
              __tensor_ops_detail::__assert_false_v<destinationPtrType>,
              "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType,
                                                          half> &&
                         __tensor_ops_detail::__is_same_v<rightValueType,
                                                          float> &&
                         __tensor_ops_detail::__is_same_v<
                             destinationValueType, float>)
      {
        if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_f32_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_f32_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_f32_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_f32_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_f32_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_f32_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_f32_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_f32_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else
          static_assert(
              __tensor_ops_detail::__assert_false_v<destinationPtrType>,
              "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType,
                                                          half> &&
                         __tensor_ops_detail::__is_same_v<rightValueType,
                                                          int8_t> &&
                         __tensor_ops_detail::__is_same_v<
                             destinationValueType, float>)
      {
        if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_i8_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_i8_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_i8_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_i8_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_i8_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_i8_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_i8_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_i8_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else
          static_assert(
              __tensor_ops_detail::__assert_false_v<destinationPtrType>,
              "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType,
                                                          float> &&
                         __tensor_ops_detail::__is_same_v<rightValueType,
                                                          half> &&
                         __tensor_ops_detail::__is_same_v<
                             destinationValueType, float>)
      {
        if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_f16_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_f16_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_f16_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_f16_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_f16_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_f16_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_f16_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_f16_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else
          static_assert(
              __tensor_ops_detail::__assert_false_v<destinationPtrType>,
              "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType,
                                                          float> &&
                         __tensor_ops_detail::__is_same_v<rightValueType,
                                                          float> &&
                         __tensor_ops_detail::__is_same_v<
                             destinationValueType, float>)
      {
        if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_f32_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_f32_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_f32_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_f32_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_f32_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_f32_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_f32_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_f32_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else
          static_assert(
              __tensor_ops_detail::__assert_false_v<destinationPtrType>,
              "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType,
                                                          float> &&
                         __tensor_ops_detail::__is_same_v<rightValueType,
                                                          int8_t> &&
                         __tensor_ops_detail::__is_same_v<
                             destinationValueType, float>)
      {
        if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_i8_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_i8_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_i8_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_i8_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_i8_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_i8_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_i8_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_i8_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else
          static_assert(
              __tensor_ops_detail::__assert_false_v<destinationPtrType>,
              "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType,
                                                          int8_t> &&
                         __tensor_ops_detail::__is_same_v<rightValueType,
                                                          half> &&
                         __tensor_ops_detail::__is_same_v<
                             destinationValueType, float>)
      {
        if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_f16_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_f16_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_f16_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_f16_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_f16_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_f16_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_f16_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_f16_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else
          static_assert(
              __tensor_ops_detail::__assert_false_v<destinationPtrType>,
              "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType,
                                                          int8_t> &&
                         __tensor_ops_detail::__is_same_v<rightValueType,
                                                          float> &&
                         __tensor_ops_detail::__is_same_v<
                             destinationValueType, float>)
      {
        if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_f32_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_f32_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_f32_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_f32_dv_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_f32_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_f32_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_f32_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_f32_th_f32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else
          static_assert(
              __tensor_ops_detail::__assert_false_v<destinationPtrType>,
              "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType,
                                                          int8_t> &&
                         __tensor_ops_detail::__is_same_v<rightValueType,
                                                          int8_t> &&
                         __tensor_ops_detail::__is_same_v<
                             destinationValueType, int32_t>)
      {
        if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_i8_dv_i32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_i8_dv_i32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_i8_dv_i32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_i8_dv_i32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_i8_th_i32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_i8_th_i32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_i8_th_i32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else if constexpr (
            __tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
            __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_i8_th_i32(
              desc, left, leftDescType, right, rightDescType, destination,
              destinationDescType);
        else
          static_assert(
              __tensor_ops_detail::__assert_false_v<destinationPtrType>,
              "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<rightValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>)
      {
        if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_b16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_b16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_b16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_b16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else
          static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<rightValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<destinationValueType, float>)
      {
        if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else
          static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<rightValueType, float> &&
                         __tensor_ops_detail::__is_same_v<destinationValueType, float>)
      {
        if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f32_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f32_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f32_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f32_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else
          static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<rightValueType, int8_t> &&
                         __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>)
      {
        if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_i8_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_i8_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_i8_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_i8_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_i8_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_i8_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_i8_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_i8_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else
          static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<rightValueType, int8_t> &&
                         __tensor_ops_detail::__is_same_v<destinationValueType, float>)
      {
        if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_i8_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_i8_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_i8_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_i8_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else
          static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> &&
                         __tensor_ops_detail::__is_same_v<rightValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<destinationValueType, float>)
      {
        if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_dv_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_dv_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f32_th_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f32_th_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else
          static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> &&
                         __tensor_ops_detail::__is_same_v<rightValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>)
      {
        if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_b16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_b16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_b16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_b16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else
          static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> &&
                         __tensor_ops_detail::__is_same_v<rightValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<destinationValueType, float>)
      {
        if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_dv_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_dv_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_i8_th_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_i8_th_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else
          static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<rightValueType, half> &&
                         __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>)
      {
        if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else
          static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<rightValueType, half> &&
                         __tensor_ops_detail::__is_same_v<destinationValueType, half>)
      {
        if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f16_th_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f16_th_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f16_th_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f16_th_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else
          static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<rightValueType, half> &&
                         __tensor_ops_detail::__is_same_v<destinationValueType, float>)
      {
        if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_dv_f16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_dv_f16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_b16_th_f16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_b16_th_f16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else
          static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> &&
                         __tensor_ops_detail::__is_same_v<rightValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>)
      {
        if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_b16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_b16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_b16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_b16_th_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else
          static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> &&
                         __tensor_ops_detail::__is_same_v<rightValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<destinationValueType, half>)
      {
        if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_b16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_b16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_b16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_b16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_b16_th_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_b16_th_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_b16_th_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_b16_th_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else
          static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
      }
      else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> &&
                         __tensor_ops_detail::__is_same_v<rightValueType, bfloat> &&
                         __tensor_ops_detail::__is_same_v<destinationValueType, float>)
      {
        if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                      __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_dv_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_dv_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_dv_f16_th_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else if constexpr (__tensor_ops_detail::__is_thread_addrspace_v<leftPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<rightPtrType> &&
                           __tensor_ops_detail::__is_thread_addrspace_v<destinationPtrType>)
          __tensorops_impl_matmul2d_op_run_single_thread_th_f16_th_b16_th_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType);
        else
          static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
      }
      else
        static_assert(
            __tensor_ops_detail::__assert_false_v<destinationValueType>,
            "Unsupported type");
    }
    else
      static_assert(
          __tensor_ops_detail::__assert_false_v<destinationTensorType>,
          "operands cannot be cooperative tensor with cooperative group of "
          "size 1");
  }
  else
  {
    // multiple threads
    if constexpr (!__tensor_ops_detail::__is_cooperative_tensor_type_v<leftTensorType> && !__tensor_ops_detail::__is_cooperative_tensor_type_v<rightTensorType> && !__tensor_ops_detail::__is_cooperative_tensor_type_v<destinationTensorType>)
    {
        const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType = __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<leftTensorType>();
        const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType = __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<rightTensorType>();
        const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType = __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<destinationTensorType>();
        
        thread void *left = (thread void *)(&leftIn);
        thread void *right = (thread void *)(&rightIn);
        thread void *destination = (thread void *)(&destinationT);
        
        if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_f16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_f16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_f16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_f16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_i8_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_i8_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_i8_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_i8_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_i8_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_i8_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_i8_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_i8_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_dv_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_dv_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_tg_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_tg_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_dv_f16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_dv_f16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_tg_f16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_tg_f16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_i8_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_i8_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_i8_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_i8_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_dv_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_dv_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_tg_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_tg_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_dv_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_dv_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_tg_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_tg_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_dv_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_dv_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_tg_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_tg_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_dv_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_dv_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_tg_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_tg_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_dv_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_dv_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_tg_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_tg_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_dv_i8_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_dv_i8_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_tg_i8_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_tg_i8_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_dv_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_dv_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_tg_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_tg_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_dv_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_dv_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_tg_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_tg_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_dv_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_dv_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_tg_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_tg_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_dv_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_dv_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_tg_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_tg_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, int32_t>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_dv_i8_dv_i32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_dv_i8_dv_i32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_tg_i8_dv_i32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_tg_i8_dv_i32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_dv_i8_tg_i32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_dv_i8_tg_i32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_tg_i8_tg_i32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_tg_i8_tg_i32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_b16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_b16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_b16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_b16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_f32_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_f32_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_i8_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_i8_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_i8_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_i8_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_i8_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_i8_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_i8_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_i8_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_i8_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_i8_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_i8_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_i8_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_i8_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_tg_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_tg_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_dv_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_dv_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f32_tg_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f32_tg_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_dv_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_dv_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_tg_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_tg_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_dv_b16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_dv_b16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_tg_b16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_tg_b16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_tg_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_tg_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_dv_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_dv_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_i8_tg_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_i8_tg_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_f16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_f16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_f16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_f16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_f16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_f16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_f16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_f16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_f16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_f16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_f16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_f16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_f16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_f16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_dv_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_dv_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_b16_tg_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_b16_tg_f16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_b16_dv_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_b16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_b16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_b16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_b16_tg_b16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_b16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_b16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_b16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_b16_dv_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_b16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_b16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_b16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_b16_tg_f16(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_b16_dv_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_dv_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_dv_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_dv_f16_tg_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_tg_f16_tg_b16_tg_f32(desc, left, leftDescType, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else
            static_assert(__tensor_ops_detail::__assert_false_v<destinationValueType>, "Unsupported type");
      }
      else if constexpr (!__tensor_ops_detail::__is_cooperative_tensor_type_v<leftTensorType> && !__tensor_ops_detail::__is_cooperative_tensor_type_v<rightTensorType> && __tensor_ops_detail::__is_cooperative_tensor_type_v<destinationTensorType>)
      {
        const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType = __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<leftTensorType>();
        const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType = __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<rightTensorType>();
        
        thread void *left = (thread void *)(&leftIn);
        thread void *right = (thread void *)(&rightIn);
        thread void *destination = (thread void *)&destinationT[__tensor_ops_detail::__tensor_ops_reserved_index];
        
        if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_f16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_f16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_f16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_f16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_i8_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_i8_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_i8_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_i8_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_dv_f16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_dv_f16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_tg_f16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_tg_f16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_i8_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_i8_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_i8_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_i8_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_dv_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_dv_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_tg_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_tg_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_dv_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_dv_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_tg_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_tg_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_dv_i8_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_dv_i8_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_tg_i8_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_tg_i8_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_dv_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_dv_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_tg_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_tg_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_dv_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_dv_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_tg_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_tg_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, int32_t>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_dv_i8_i32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_dv_i8_i32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_tg_i8_i32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_tg_i8_i32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_b16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_b16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_b16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_b16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_f32_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_i8_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_i8_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_i8_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_i8_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_i8_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_i8_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_i8_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_i8_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_dv_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_dv_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_tg_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_tg_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_dv_b16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_dv_b16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_tg_b16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_tg_b16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_dv_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_dv_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_tg_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_tg_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_f16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_f16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_f16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_f16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_f16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_f16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_f16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_f16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_dv_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_dv_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_tg_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_tg_f16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_b16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_b16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_b16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_b16_b16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_b16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_b16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_b16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_b16_f16(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_dv_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_dv_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_tg_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_tg_b16_f32(desc, left, leftDescType, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else
            static_assert(__tensor_ops_detail::__assert_false_v<destinationValueType>, "Unsupported type");
      }
      else if constexpr (!__tensor_ops_detail::__is_cooperative_tensor_type_v<leftTensorType> && __tensor_ops_detail::__is_cooperative_tensor_type_v<rightTensorType> && !__tensor_ops_detail::__is_cooperative_tensor_type_v<destinationTensorType>)
      {
        const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType = __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<leftTensorType>();
        const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType = __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<destinationTensorType>();
        
        thread void *left = (thread void *)(&leftIn);
        thread void *right = (thread void *)&rightIn[__tensor_ops_detail::__tensor_ops_reserved_index];
        thread void *destination = (thread void *)(&destinationT);
        
        if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f16_dv_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f16_dv_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f16_tg_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f16_tg_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_i8_dv_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_i8_dv_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_i8_tg_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_i8_tg_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f16_dv_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f16_dv_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f16_tg_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f16_tg_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f32_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f32_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f32_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f32_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_i8_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_i8_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_i8_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_i8_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_f16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_f16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_f16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_f16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_f32_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_f32_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_f32_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_f32_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_i8_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_i8_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_i8_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_i8_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f32_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f32_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f32_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f32_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, int32_t>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_i8_dv_i32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_i8_dv_i32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_i8_tg_i32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_i8_tg_i32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_b16_dv_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_b16_dv_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_b16_tg_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_b16_tg_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_b16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_b16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_b16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_b16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f32_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f32_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f32_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f32_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_i8_dv_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_i8_dv_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_i8_tg_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_i8_tg_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_i8_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_i8_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_i8_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_i8_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_b16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_b16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_b16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_b16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_b16_dv_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_b16_dv_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_b16_tg_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_b16_tg_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_b16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_b16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_b16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_b16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_dv_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_dv_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_tg_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_tg_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_dv_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_dv_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_tg_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_tg_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_dv_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_dv_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_tg_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_tg_b16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_dv_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_dv_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_tg_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_tg_f16(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_dv_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_tg_f32(desc, left, leftDescType, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else
            static_assert(__tensor_ops_detail::__assert_false_v<destinationValueType>, "Unsupported type");
      }
      else if constexpr (!__tensor_ops_detail::__is_cooperative_tensor_type_v<leftTensorType> && __tensor_ops_detail::__is_cooperative_tensor_type_v<rightTensorType> && __tensor_ops_detail::__is_cooperative_tensor_type_v<destinationTensorType>)
      {
        const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type leftDescType = __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<leftTensorType>();
        
        thread void *left = (thread void *)(&leftIn);
        thread void *right = (thread void *)&rightIn[__tensor_ops_detail::__tensor_ops_reserved_index];
        thread void *destination = (thread void *)&destinationT[__tensor_ops_detail::__tensor_ops_reserved_index];
        
        if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f16_f16(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f16_f16(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_i8_f16(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_i8_f16(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f16_f16(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f16_f16(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f16_f32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f16_f32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_f32_f32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_f32_f32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_i8_f32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_i8_f32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_f16_f32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_f16_f32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_f32_f32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_f32_f32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_i8_f32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_i8_f32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f16_f32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f16_f32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_f32_f32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_f32_f32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, int32_t>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_i8_i32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_i8_i32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_b16_b16(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_b16_b16(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_b16_f32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_b16_f32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f32_f32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f32_f32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_i8_b16(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_i8_b16(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_i8_f32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_i8_f32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f32_b16_f32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f32_b16_f32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_b16_b16(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_b16_b16(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_i8_b16_f32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_i8_b16_f32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_b16(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_b16(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_f16(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_f16(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_b16_f16_f32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_b16_f16_f32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_b16(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_b16(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_f16(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_f16(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_dv_f16_b16_f32(desc, left, leftDescType, right, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<leftPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_tg_f16_b16_f32(desc, left, leftDescType, right, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else
            static_assert(__tensor_ops_detail::__assert_false_v<destinationValueType>, "Unsupported type");
      }
      else if constexpr (__tensor_ops_detail::__is_cooperative_tensor_type_v<leftTensorType> && !__tensor_ops_detail::__is_cooperative_tensor_type_v<rightTensorType> && !__tensor_ops_detail::__is_cooperative_tensor_type_v<destinationTensorType>)
      {
        const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType = __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<rightTensorType>();
        const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType = __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<destinationTensorType>();
        
        thread void *left = (thread void *)&leftIn[__tensor_ops_detail::__tensor_ops_reserved_index];
        thread void *right = (thread void *)(&rightIn);
        thread void *destination = (thread void *)(&destinationT);
        
        if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f16_dv_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f16_dv_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f16_tg_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f16_tg_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_i8_dv_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_i8_dv_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_i8_tg_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_i8_tg_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f16_dv_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f16_dv_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f16_tg_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f16_tg_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f32_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f32_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f32_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f32_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_i8_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_i8_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_i8_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_i8_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_f16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_f16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_f16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_f16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_f32_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_f32_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_f32_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_f32_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_i8_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_i8_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_i8_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_i8_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f32_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f32_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f32_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f32_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, int32_t>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_i8_dv_i32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_i8_dv_i32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_i8_tg_i32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_i8_tg_i32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_b16_dv_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_b16_dv_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_b16_tg_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_b16_tg_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_b16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_b16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_b16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_b16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f32_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f32_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f32_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f32_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_i8_dv_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_i8_dv_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_i8_tg_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_i8_tg_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_i8_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_i8_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_i8_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_i8_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_b16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_b16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_b16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_b16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_b16_dv_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_b16_dv_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_b16_tg_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_b16_tg_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_b16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_b16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_b16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_b16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_dv_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_dv_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_tg_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_tg_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_dv_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_dv_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_tg_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_tg_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_dv_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_dv_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_tg_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_tg_b16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_dv_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_dv_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_tg_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_tg_f16(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_dv_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType> && __tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_tg_f32(desc, left, right, rightDescType, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else
            static_assert(__tensor_ops_detail::__assert_false_v<destinationValueType>, "Unsupported type");
      }
      else if constexpr (__tensor_ops_detail::__is_cooperative_tensor_type_v<leftTensorType> && !__tensor_ops_detail::__is_cooperative_tensor_type_v<rightTensorType> && __tensor_ops_detail::__is_cooperative_tensor_type_v<destinationTensorType>)
      {
        const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type rightDescType = __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<rightTensorType>();
        
        thread void *left = (thread void *)&leftIn[__tensor_ops_detail::__tensor_ops_reserved_index];
        thread void *right = (thread void *)(&rightIn);
        thread void *destination = (thread void *)&destinationT[__tensor_ops_detail::__tensor_ops_reserved_index];
        
        if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f16_f16(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f16_f16(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_i8_f16(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_i8_f16(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f16_f16(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f16_f16(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f16_f32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f16_f32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_f32_f32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_f32_f32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_i8_f32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_i8_f32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_f16_f32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_f16_f32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_f32_f32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_f32_f32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_i8_f32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_i8_f32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f16_f32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f16_f32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_f32_f32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_f32_f32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, int32_t>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_i8_i32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_i8_i32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_b16_b16(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_b16_b16(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_b16_f32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_b16_f32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f32_f32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f32_f32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_i8_b16(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_i8_b16(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_i8_f32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_i8_f32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_dv_b16_f32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_tg_b16_f32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_b16_b16(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_b16_b16(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_dv_b16_f32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_tg_b16_f32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_b16(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_b16(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_f16(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_f16(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_dv_f16_f32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_tg_f16_f32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_b16(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_b16(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_f16(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_f16(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_dv_b16_f32(desc, left, right, rightDescType, destination, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<rightPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_tg_b16_f32(desc, left, right, rightDescType, destination, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else
            static_assert(__tensor_ops_detail::__assert_false_v<destinationValueType>, "Unsupported type");
      }
      else if constexpr (__tensor_ops_detail::__is_cooperative_tensor_type_v<leftTensorType> && __tensor_ops_detail::__is_cooperative_tensor_type_v<rightTensorType> && !__tensor_ops_detail::__is_cooperative_tensor_type_v<destinationTensorType>)
      {
        const __tensor_ops_detail::__tensor_ops_tensor_descriptor_type destinationDescType = __tensor_ops_detail::__tensor_type_to_tensor_descriptor_type<destinationTensorType>();
        
        thread void *left = (thread void *)&leftIn[__tensor_ops_detail::__tensor_ops_reserved_index];
        thread void *right = (thread void *)&rightIn[__tensor_ops_detail::__tensor_ops_reserved_index];
        thread void *destination = (thread void *)(&destinationT);
        
        if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_f16_dv_f16(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_f16_tg_f16(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_i8_dv_f16(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_i8_tg_f16(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_f16_dv_f16(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_f16_tg_f16(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_f16_dv_f32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_f16_tg_f32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_f32_dv_f32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_f32_tg_f32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_i8_dv_f32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_i8_tg_f32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_f16_dv_f32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_f16_tg_f32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_f32_dv_f32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_f32_tg_f32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_i8_dv_f32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_i8_tg_f32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_f16_dv_f32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_f16_tg_f32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_f32_dv_f32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_f32_tg_f32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, int32_t>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_i8_dv_i32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_i8_tg_i32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_b16_dv_b16(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_b16_tg_b16(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_b16_dv_f32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_b16_tg_f32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_f32_dv_f32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_f32_tg_f32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_i8_dv_b16(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_i8_tg_b16(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_i8_dv_f32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_i8_tg_f32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_b16_dv_f32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f32_b16_tg_f32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_b16_dv_b16(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_b16_tg_b16(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_b16_dv_f32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_i8_b16_tg_f32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_dv_b16(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_tg_b16(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_dv_f16(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_tg_f16(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_dv_f32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_tg_f32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_dv_b16(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_tg_b16(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, half>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_dv_f16(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_tg_f16(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>) {
            if constexpr (__tensor_ops_detail::__is_device_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_dv_f32(desc, left, right, destination, destinationDescType, threads);
            else if constexpr (__tensor_ops_detail::__is_threadgroup_addrspace_v<destinationPtrType>)
                __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_tg_f32(desc, left, right, destination, destinationDescType, threads);
            else
                static_assert(__tensor_ops_detail::__assert_false_v<destinationPtrType>, "Unsupported address space");
        }
        else
            static_assert(__tensor_ops_detail::__assert_false_v<destinationValueType>, "Unsupported type");
      }
      else if constexpr (__tensor_ops_detail::__is_cooperative_tensor_type_v<leftTensorType> && __tensor_ops_detail::__is_cooperative_tensor_type_v<rightTensorType> && __tensor_ops_detail::__is_cooperative_tensor_type_v<destinationTensorType>)
      {
        thread void *left = (thread void *)&leftIn[__tensor_ops_detail::__tensor_ops_reserved_index];
        thread void *right = (thread void *)&rightIn[__tensor_ops_detail::__tensor_ops_reserved_index];
        thread void *destination = (thread void *)&destinationT[__tensor_ops_detail::__tensor_ops_reserved_index];
        
        if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>)
            __tensorops_impl_matmul2d_op_run_cooperative_f16_f16_f16(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, half>)
            __tensorops_impl_matmul2d_op_run_cooperative_f16_i8_f16(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>)
            __tensorops_impl_matmul2d_op_run_cooperative_i8_f16_f16(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>)
            __tensorops_impl_matmul2d_op_run_cooperative_f16_f16_f32(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>)
            __tensorops_impl_matmul2d_op_run_cooperative_f16_f32_f32(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>)
            __tensorops_impl_matmul2d_op_run_cooperative_f16_i8_f32(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>)
            __tensorops_impl_matmul2d_op_run_cooperative_f32_f16_f32(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>)
            __tensorops_impl_matmul2d_op_run_cooperative_f32_f32_f32(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>)
            __tensorops_impl_matmul2d_op_run_cooperative_f32_i8_f32(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>)
            __tensorops_impl_matmul2d_op_run_cooperative_i8_f16_f32(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>)
            __tensorops_impl_matmul2d_op_run_cooperative_i8_f32_f32(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, int32_t>)
            __tensorops_impl_matmul2d_op_run_cooperative_i8_i8_i32(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>)
            __tensorops_impl_matmul2d_op_run_cooperative_b16_b16_b16(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>)
            __tensorops_impl_matmul2d_op_run_cooperative_b16_b16_f32(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, float> && __tensor_ops_detail::__is_same_v<destinationValueType, float>)
            __tensorops_impl_matmul2d_op_run_cooperative_b16_f32_f32(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>)
            __tensorops_impl_matmul2d_op_run_cooperative_b16_i8_b16(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, int8_t> && __tensor_ops_detail::__is_same_v<destinationValueType, float>)
            __tensorops_impl_matmul2d_op_run_cooperative_b16_i8_f32(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, float> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>)
            __tensorops_impl_matmul2d_op_run_cooperative_f32_b16_f32(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>)
            __tensorops_impl_matmul2d_op_run_cooperative_i8_b16_b16(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, int8_t> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>)
            __tensorops_impl_matmul2d_op_run_cooperative_i8_b16_f32(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>)
            __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_b16(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, half>)
            __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_f16(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, bfloat> && __tensor_ops_detail::__is_same_v<rightValueType, half> && __tensor_ops_detail::__is_same_v<destinationValueType, float>)
            __tensorops_impl_matmul2d_op_run_cooperative_b16_f16_f32(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, bfloat>)
            __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_b16(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, half>)
            __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_f16(desc, left, right, destination, threads);
        else if constexpr (__tensor_ops_detail::__is_same_v<leftValueType, half> && __tensor_ops_detail::__is_same_v<rightValueType, bfloat> && __tensor_ops_detail::__is_same_v<destinationValueType, float>)
            __tensorops_impl_matmul2d_op_run_cooperative_f16_b16_f32(desc, left, right, destination, threads);
        else
            static_assert(__tensor_ops_detail::__assert_false_v<destinationValueType>, "Unsupported type");
    }
  }
}

template <class ElementType, class SrcExtents, class DstExtents, class SrcLayout, class DstLayout>
inline void __reduce_rows(
    thread metal::cooperative_tensor<ElementType, SrcExtents, SrcLayout> &sourceT,
    thread metal::cooperative_tensor<ElementType, DstExtents, DstLayout> &destT,
    ElementType identity = (ElementType)0,
    __reduction_operation op = reduction_operation::sum)
{
  static_assert(SrcLayout::__is_matmul2d_cooperative_tensor_layout,
                "Source must be matmul2d cooperative destination tensor");
  static_assert(SrcLayout::__operand_index == __matmul2d_cooperative_operand_index::destination,
                "Source must be matmul2d cooperative destination tensor");
  static_assert(DstLayout::is_matmul2d_reduction_cooperative_destination_layout,
                "Destination must be matmul2d row reduction cooperative destination tensor");
  static_assert(DstLayout::__reduction_dim == 0,
                "Destination must be matmul2d row reduction cooperative destination tensor");
  static_assert(__tensor_ops_detail::__is_same_v<typename SrcLayout::scope_t,
                                                 metal::execution_simdgroup>,
                "reduce_rows requires a single SIMD group");
  static_assert(__tensor_ops_detail::__is_same_v<typename DstLayout::scope_t,
                                                 metal::execution_simdgroup>,
                "reduce_rows requires a single SIMD group");
  static_assert(SrcExtents::rank() == 2, "Source rank must be 2");
  static_assert(DstExtents::rank() == 1, "Destination rank must be 1");

  constexpr __matmul2d_descriptor sourceDesc = SrcLayout::matmul2d_desc;
  constexpr __matmul2d_descriptor destDesc = DstLayout::matmul2d_desc;

  using dstLeftValueType = __tensor_ops_detail::__remove_addrspace_t<
      __tensor_ops_detail::__remove_reference_t<
          typename DstLayout::left_elem_t>>;
  using dstRightValueType = __tensor_ops_detail::__remove_addrspace_t<
      __tensor_ops_detail::__remove_reference_t<
          typename DstLayout::right_elem_t>>;

  static_assert(matmul2d_descriptor_is_equal(sourceDesc, destDesc), "Source and destination matmul2d descriptor must match");
  static_assert(__tensor_ops_detail::__is_same_v<typename SrcLayout::left_element_t, dstLeftValueType>, "Source and destination operand types must match");
  static_assert(__tensor_ops_detail::__is_same_v<typename SrcLayout::right_element_t, dstRightValueType>, "Source and destination operand types must match");
  static_assert(__tensor_ops_detail::__is_same_v<typename SrcLayout::destination_element_t, typename DstLayout::element_t>, "Source and destination element types must match");

  __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename SrcLayout::left_element_t>::value;
  __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename SrcLayout::right_element_t>::value;

  thread void *src = (thread void *)&sourceT[__tensor_ops_detail::__tensor_ops_reserved_index];
  thread void *dst = (thread void *)&destT[__tensor_ops_detail::__tensor_ops_reserved_index];

  __matmul2d_descriptor desc = SrcLayout::matmul2d_desc;

  if constexpr (__tensor_ops_detail::__is_same_v<ElementType, half>)
    __tensorops_impl_matmul2d_op_cooperative_destination_reduce_rows_f16(
        desc, src, dst, identity, op, leftDataType, rightDataType);
  else if constexpr (__tensor_ops_detail::__is_same_v<ElementType, int32_t>)
    __tensorops_impl_matmul2d_op_cooperative_destination_reduce_rows_i32(
        desc, src, dst, identity, op, leftDataType, rightDataType);
  else if constexpr (__tensor_ops_detail::__is_same_v<ElementType, float>)
    __tensorops_impl_matmul2d_op_cooperative_destination_reduce_rows_f32(
        desc, src, dst, identity, op, leftDataType, rightDataType);
  else if constexpr (__tensor_ops_detail::__is_same_v<ElementType, bfloat>)
    __tensorops_impl_matmul2d_op_cooperative_destination_reduce_rows_b16(
        desc, src, dst, identity, op, leftDataType, rightDataType);
  else
    static_assert(__tensor_ops_detail::__assert_false_v<ElementType>,
                  "Unsupported type");
}

template <class ElementType, class SrcExtents, class DstExtents, class SrcLayout, class DstLayout>
inline void __reduce_columns(
    thread metal::cooperative_tensor<ElementType, SrcExtents, SrcLayout> &sourceT,
    thread metal::cooperative_tensor<ElementType, DstExtents, DstLayout> &destT,
    ElementType identity = (ElementType)0,
    __reduction_operation op = reduction_operation::sum)
{
  static_assert(SrcLayout::__is_matmul2d_cooperative_tensor_layout,
                "Source must be matmul2d cooperative destination tensor");
  static_assert(SrcLayout::__operand_index == __matmul2d_cooperative_operand_index::destination,
                "Source must be matmul2d cooperative destination tensor");
  static_assert(DstLayout::__reduction_dim == 1,
                "Destination must be matmul2d column reduction cooperative destination tensor");
  static_assert(__tensor_ops_detail::__is_same_v<typename SrcLayout::scope_t,
                                                 metal::execution_simdgroup>,
                "reduce_columns requires a single SIMD group");
  static_assert(__tensor_ops_detail::__is_same_v<typename DstLayout::scope_t,
                                                 metal::execution_simdgroup>,
                "reduce_columns requires a single SIMD group");
  static_assert(SrcExtents::rank() == 2, "Source rank must be 2");
  static_assert(DstExtents::rank() == 1, "Destination rank must be 1");

  constexpr __matmul2d_descriptor sourceDesc = SrcLayout::matmul2d_desc;
  constexpr __matmul2d_descriptor destDesc = DstLayout::matmul2d_desc;

  using dstLeftValueType = __tensor_ops_detail::__remove_addrspace_t<
      __tensor_ops_detail::__remove_reference_t<
          typename DstLayout::left_elem_t>>;
  using dstRightValueType = __tensor_ops_detail::__remove_addrspace_t<
      __tensor_ops_detail::__remove_reference_t<
          typename DstLayout::right_elem_t>>;

  static_assert(matmul2d_descriptor_is_equal(sourceDesc, destDesc), "Source and destination matmul2d descriptor must match");
  static_assert(__tensor_ops_detail::__is_same_v<typename SrcLayout::left_element_t, dstLeftValueType>, "Source and destination operand types must match");
  static_assert(__tensor_ops_detail::__is_same_v<typename SrcLayout::right_element_t, dstRightValueType>, "Source and destination operand types must match");
  static_assert(__tensor_ops_detail::__is_same_v<typename SrcLayout::destination_element_t, typename DstLayout::element_t>, "Source and destination element types must match");

  __tensor_ops_detail::__tensor_ops_datatype leftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename SrcLayout::left_element_t>::value;
  __tensor_ops_detail::__tensor_ops_datatype rightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename SrcLayout::right_element_t>::value;

  thread void *src = (thread void *)&sourceT[__tensor_ops_detail::__tensor_ops_reserved_index];
  thread void *dst = (thread void *)&destT[__tensor_ops_detail::__tensor_ops_reserved_index];

  __matmul2d_descriptor desc = SrcLayout::matmul2d_desc;

  if constexpr (__tensor_ops_detail::__is_same_v<ElementType, half>)
    __tensorops_impl_matmul2d_op_cooperative_destination_reduce_columns_f16(
        desc, src, dst, identity, op, leftDataType, rightDataType);
  else if constexpr (__tensor_ops_detail::__is_same_v<ElementType, int32_t>)
    __tensorops_impl_matmul2d_op_cooperative_destination_reduce_columns_i32(
        desc, src, dst, identity, op, leftDataType, rightDataType);
  else if constexpr (__tensor_ops_detail::__is_same_v<ElementType, float>)
    __tensorops_impl_matmul2d_op_cooperative_destination_reduce_columns_f32(
        desc, src, dst, identity, op, leftDataType, rightDataType);
  else if constexpr (__tensor_ops_detail::__is_same_v<ElementType, bfloat>)
    __tensorops_impl_matmul2d_op_cooperative_destination_reduce_columns_b16(
        desc, src, dst, identity, op, leftDataType, rightDataType);
  else
    static_assert(__tensor_ops_detail::__assert_false_v<ElementType>,
                  "Unsupported type");
}

template <class SrcElementType, class DstElementType, class SrcExtents, class DstExtents, class SrcLayout, class DstLayout>
inline bool __is_iterator_compatible(
    const thread metal::cooperative_tensor<SrcElementType, SrcExtents, SrcLayout> &sourceT,
    const thread metal::cooperative_tensor<DstElementType, DstExtents, DstLayout> &destT)
{
  if (!SrcLayout::__is_matmul2d_cooperative_tensor_layout ||
       SrcLayout::__operand_index != __matmul2d_cooperative_operand_index::destination ||
      !DstLayout::is_matmul2d_reduction_cooperative_destination_layout ||
      !__tensor_ops_detail::__is_same_v<typename SrcLayout::scope_t, metal::execution_simdgroup> ||
      !__tensor_ops_detail::__is_same_v<typename DstLayout::scope_t, metal::execution_simdgroup> ||
      !__tensor_ops_detail::__is_same_v<SrcElementType, DstElementType> ||
      SrcExtents::rank() != 2 || DstExtents::rank() != 1)
  {
    return false;
  }

  constexpr __matmul2d_descriptor sourceDesc = SrcLayout::matmul2d_desc;
  constexpr __matmul2d_descriptor destDesc = DstLayout::matmul2d_desc;

  constexpr int reduction_dim = DstLayout::__reduction_dim;

  if ((reduction_dim == 0 && sourceDesc.m != destDesc.m) ||
      (reduction_dim == 1 && sourceDesc.n == destDesc.n))
  {
    return false;
  }

  thread void *src = (thread void *)&sourceT[__tensor_ops_detail::__tensor_ops_reserved_index];
  thread void *dst = (thread void *)&destT[__tensor_ops_detail::__tensor_ops_reserved_index];

  __tensor_ops_detail::__tensor_ops_datatype srcLeftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename SrcLayout::left_element_t>::value;
  __tensor_ops_detail::__tensor_ops_datatype srcRightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename SrcLayout::right_element_t>::value;
  __tensor_ops_detail::__tensor_ops_datatype srcElemDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<SrcElementType>::value;
  __tensor_ops_detail::__tensor_ops_datatype dstLeftDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename DstLayout::left_value_t>::value;
  __tensor_ops_detail::__tensor_ops_datatype dstRightDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<typename DstLayout::right_value_t>::value;
  __tensor_ops_detail::__tensor_ops_datatype dstElemDataType =
        __tensor_ops_detail::__type_to_tensor_ops_datatype<DstElementType>::value;

  return __tensorops_impl_matmul2d_op_cooperative_destination_is_iterator_compatible(
         sourceDesc, destDesc, src, dst, srcLeftDataType, srcRightDataType,
        srcElemDataType, dstLeftDataType, dstRightDataType, dstElemDataType);
}

#undef EXTERNALLY_DEFINED_ATTR

} // namespace __mutmul2d_detail

#endif

#endif // __TensorOpsMatMul2DImpl__
