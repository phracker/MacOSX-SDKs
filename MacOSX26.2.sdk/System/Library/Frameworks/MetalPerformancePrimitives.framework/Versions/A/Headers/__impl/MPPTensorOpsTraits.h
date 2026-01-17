
// -*- Metal -*-
//===-- MetalTensorOpsTraits ------------------------------------------------------===//
// Copyright (c) 2025 Apple Inc. All rights reserved
//===----------------------------------------------------------------------===//

#ifndef __MetalTensorOpsTraits__
#define __MetalTensorOpsTraits__

#if defined(__METAL_VERSION__) && defined(__HAVE_TENSOR__)

#include <__exec/units.h>
#include <metal_cooperative_tensor>
#include <metal_tensor>
#include <metal_type_traits>

#pragma METAL internals : enable

namespace mpp
{
namespace tensor_ops
{

namespace __tensor_ops_detail
{

template <bool B, typename T = void>
using __enable_if_t = metal::enable_if_t<B, T>;

template <typename T>
using __remove_addrspace_t = metal::remove_addrspace_t<T>;

template <typename T>
using __remove_pointer_t = metal::remove_pointer_t<T>;

template <typename T>
using __remove_reference_t = metal::remove_reference_t<T>;

template <typename U, typename V>
constant auto __is_same_v = metal::is_same_v<U, V>;

template <typename T>
constant auto __is_integral_v = metal::is_integral_v<T>;

using __false_type = metal::false_type;

using __true_type = metal::true_type;

template <typename T>
using __remove_cv_t = metal::remove_cv_t<T>;

template <typename T>
using __remove_ref_ptr_t = __remove_reference_t<__remove_pointer_t<T>>;

template <typename T>
constant auto __is_ui8_v = __is_same_v<T, uint8_t> || __is_same_v<T, unsigned char>;

template <typename T>
constant auto __is_i8_v = __is_same_v<T, int8_t> || __is_same_v<T, char> || __is_same_v<T, signed char>;

template <typename T>
constant auto __is_i32_v = __is_integral_v<T> && sizeof(T) == 4;

template <typename T>
constant auto __is_fp16_v = __is_same_v<T, half>;

#if __HAVE_BFLOAT__
template <typename T>
constant auto __is_bf16_v = __is_same_v<T, bfloat>;
#endif

template <typename T>
constant auto __is_fp32_v = __is_same_v<T, float>;

template <typename T>
constant auto __is_device_addrspace_v = metal::__tensor_detail::__is_device_addrspace_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
constant auto __is_threadgroup_addrspace_v = metal::__tensor_detail::__is_threadgroup_addrspace_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
constant auto __is_constant_addrspace_v = metal::__tensor_detail::__is_constant_addrspace_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
constant auto __is_thread_addrspace_v = metal::__tensor_detail::__is_thread_addrspace_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
struct __assert_false : __false_type
{
};

template <typename T>
constexpr constant bool __assert_false_v = __assert_false<T>::value;

template <class T>
struct __is_cooperative_tensor_type : __false_type
{
};

template <class ElementType, class Extents, class Layout>
struct __is_cooperative_tensor_type<metal::cooperative_tensor<ElementType, Extents, Layout>> : __true_type
{
};

template <class T>
constant auto __is_cooperative_tensor_type_v = __is_cooperative_tensor_type<__remove_cv_t<__remove_ref_ptr_t<T>>>::value;

template <typename T>
constant bool __is_tensor_handle_v = metal::is_tensor_handle_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
constant bool __is_tensor_offset_v = metal::has_tensor_offset_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
constant bool __is_tensor_inline_v = metal::is_tensor_inline_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
constant bool __is_tensor_type_v = __is_tensor_handle_v<T> || __is_tensor_offset_v<T> || __is_tensor_inline_v<T>;

template <typename T>
constexpr constant bool __is_tensorops_execution_scope_v = metal::is_execution_thread_v<__remove_cv_t<__remove_ref_ptr_t<T>>> ||
                                                           metal::is_execution_simdgroups_v<__remove_cv_t<__remove_ref_ptr_t<T>>>;

template <typename T>
using __remove_cvref_t = __remove_cv_t<__remove_reference_t<T>>;

} // namespace __tensor_ops_detail
} // namespace tensor_ops
} // namespace mpp

#pragma METAL internals : disable

#endif

#endif // __TensorOpsTraits__
