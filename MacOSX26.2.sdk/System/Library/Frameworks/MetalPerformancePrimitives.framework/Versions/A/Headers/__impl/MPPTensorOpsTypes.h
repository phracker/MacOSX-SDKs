
// -*- Metal -*-
//===-- MetalTensorOpsTypes ------------------------------------------------------===//
// Copyright (c) 2025 Apple Inc. All rights reserved
//===----------------------------------------------------------------------===//

#ifndef __MetalTensorOpsTypes__
#define __MetalTensorOpsTypes__

#if defined(__METAL_VERSION__) && defined(__HAVE_TENSOR__)

#include "MPPTensorOpsTraits.h"
#include <metal_numeric>

namespace mpp
{
namespace tensor_ops
{

namespace __tensor_ops_detail
{

template <typename T>
constexpr inline int __get_rank()
{
  return T::get_rank();
}

using __rank_t = ushort;

static constant ushort __tensor_ops_reserved_index = USHRT_MAX;

using __thread_void_t = thread void *;
using __const_thread_void_t = const thread void *;

enum __tensor_ops_datatype
{
  __tensor_ops_datatype_invalid = 0,

  __tensor_ops_datatype_float_bit = 0x10000000,
  __tensor_ops_datatype_float32 = __tensor_ops_datatype_float_bit | 32,
  __tensor_ops_datatype_float16 = __tensor_ops_datatype_float_bit | 16,

  __tensor_ops_datatype_signed_bit = 0x20000000,
  __tensor_ops_datatype_int4 = __tensor_ops_datatype_signed_bit | 4,
  __tensor_ops_datatype_int8 = __tensor_ops_datatype_signed_bit | 8,
  __tensor_ops_datatype_int16 = __tensor_ops_datatype_signed_bit | 16,
  __tensor_ops_datatype_int32 = __tensor_ops_datatype_signed_bit | 32,

  __tensor_ops_datatype_uint4 = 4,
  __tensor_ops_datatype_uint8 = 8,
  __tensor_ops_datatype_uint16 = 16,
  __tensor_ops_datatype_uint32 = 32,

  __tensor_ops_datatype_alternate_encoding_bit = 0x80000000,
  __tensor_ops_datatype_bfloat16 = __tensor_ops_datatype_alternate_encoding_bit | __tensor_ops_datatype_float16,
};

enum __tensor_ops_address_space
{
  __tensor_ops_address_space_invalid,
  __tensor_ops_address_space_device,
  __tensor_ops_address_space_threadgroup,
  __tensor_ops_address_space_thread_private,
};

enum __tensor_ops_tensor_descriptor_type
{
  __tensor_ops_tensor_descriptor_type_handle,
  __tensor_ops_tensor_descriptor_type_offset,
  __tensor_ops_tensor_descriptor_type_inline,
};

template <typename PointerType>
constexpr __tensor_ops_address_space __pointer_type_to_tensorps_address_space()
{
  if constexpr (__is_device_addrspace_v<PointerType>)
    return __tensor_ops_address_space_device;
  else if constexpr (__is_threadgroup_addrspace_v<PointerType>)
    return __tensor_ops_address_space_threadgroup;
  else if constexpr (__is_thread_addrspace_v<PointerType>)
    return __tensor_ops_address_space_thread_private;
  else
    static_assert(__assert_false_v<PointerType>, "unsupported address space");
}

template <typename TensorType>
constexpr __tensor_ops_tensor_descriptor_type __tensor_type_to_tensor_descriptor_type()
{
  if constexpr (__is_tensor_offset_v<TensorType>)
    return __tensor_ops_tensor_descriptor_type_offset;
  else if constexpr (__is_tensor_handle_v<TensorType>)
    return __tensor_ops_tensor_descriptor_type_handle;
  else if constexpr (__is_tensor_inline_v<TensorType>)
    return __tensor_ops_tensor_descriptor_type_inline;
  else
    static_assert(__assert_false_v<TensorType>, "unsupported tensor descriptor");
}

template <typename ElementType>
constexpr __tensor_ops_datatype __element_type_to_tensor_ops_datatype()
{
  if constexpr (__is_same_v<ElementType, float>)
    return __tensor_ops_datatype_float32;
#if __HAVE_BFLOAT__
  else if constexpr (__is_same_v<ElementType, bfloat>)
    return __tensor_ops_datatype_bfloat16;
#endif
  else if constexpr (__is_same_v<ElementType, half>)
    return __tensor_ops_datatype_float16;
  else if constexpr (__is_same_v<ElementType, int8_t>)
    return __tensor_ops_datatype_int8;
  else if constexpr (__is_same_v<ElementType, uint8_t>)
    return __tensor_ops_datatype_uint8;
  else if constexpr (__is_same_v<ElementType, int32_t>)
    return __tensor_ops_datatype_int32;
  else if constexpr (__is_same_v<ElementType, uint32_t>)
    return __tensor_ops_datatype_uint32;
  else
    static_assert(__assert_false_v<ElementType>, "unsupported data type");
}

inline uint16_t __sizeof_tensorops_datatype(__tensor_ops_datatype dataType)
{
  return (dataType & 0xFFFF) >> 3;
}

} // namespace __tensor_ops_detail

template <typename T, typename U = __tensor_ops_detail::__enable_if_t<__tensor_ops_detail::__is_integral_v<T>>>
struct dynamic_length
{
    static constexpr constant T value = metal::numeric_limits<T>::max();
};

template <typename T, typename U = __tensor_ops_detail::__enable_if_t<__tensor_ops_detail::__is_integral_v<T>>>
constexpr constant T dynamic_length_v = dynamic_length<T>::value;

} // namespace tensor_ops
} // namespace mpp
#endif // (__METAL_VERSION__)

#endif
