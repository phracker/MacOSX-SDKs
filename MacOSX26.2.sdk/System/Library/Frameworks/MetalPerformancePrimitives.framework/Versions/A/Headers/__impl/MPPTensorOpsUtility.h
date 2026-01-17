
// -*- Metal -*-
//===-- MetalTensorOpsUtility ------------------------------------------------------===//
// Copyright (c) 2025 Apple Inc. All rights reserved
//===----------------------------------------------------------------------===//

#ifndef __MetalTensorOpsUtility__
#define __MetalTensorOpsUtility__

#if defined(__METAL_VERSION__) && defined(__HAVE_TENSOR__)

#include "MPPTensorOpsTypes.h"

namespace mpp
{
namespace tensor_ops
{

namespace __tensor_ops_detail
{

template <typename T>
T __MIN(T x, T y)
{
  return ((x) < (y) ? (x) : (y));
}
template <typename T>
T __MAX(T x, T y)
{
  return ((x) > (y) ? (x) : (y));
}

template <typename T>
struct __type_to_tensor_ops_datatype
{
    static_assert(__tensor_ops_detail::__assert_false_v<T>,
                  "unsupported data type");
};
template <>
struct __type_to_tensor_ops_datatype<float>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_float32;
};
template <>
struct __type_to_tensor_ops_datatype<half>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_float16;
};
#if __HAVE_BFLOAT__
template <>
struct __type_to_tensor_ops_datatype<bfloat>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_bfloat16;
};
#endif
template <>
struct __type_to_tensor_ops_datatype<int8_t>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_int8;
};
template <>
struct __type_to_tensor_ops_datatype<uint8_t>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_uint8;
};
template <>
struct __type_to_tensor_ops_datatype<int16_t>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_int16;
};
template <>
struct __type_to_tensor_ops_datatype<uint16_t>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_uint16;
};
template <>
struct __type_to_tensor_ops_datatype<int>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_int32;
};
template <>
struct __type_to_tensor_ops_datatype<uint>
{
  static constant __tensor_ops_datatype value = __tensor_ops_datatype_uint32;
};

} // namespace __tensor_ops_detail

} // namespace tensor_ops
} // namespace mpp

#endif

#endif // __TensorOpsUtility__
