//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___NEW_ALLOCATE_H
#define _LIBCPP___NEW_ALLOCATE_H

#include <__config>
#include <__cstddef/max_align_t.h>
#include <__cstddef/size_t.h>
#include <__new/align_val_t.h>
#include <__new/global_new_delete.h> // for _LIBCPP_HAS_SIZED_DEALLOCATION
#include <__type_traits/type_identity.h>
#include <__utility/element_count.h>

#include <__configuration/availability.h>
#include <__new/global_typed_new_delete.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

_LIBCPP_CONSTEXPR inline _LIBCPP_HIDE_FROM_ABI bool __is_overaligned_for_new(size_t __align) _NOEXCEPT {
#ifdef __STDCPP_DEFAULT_NEW_ALIGNMENT__
  return __align > __STDCPP_DEFAULT_NEW_ALIGNMENT__;
#else
  return __align > _LIBCPP_ALIGNOF(max_align_t);
#endif
}

#if __has_feature(typed_cxx_new_delete)
template <class _Tp>
_LIBCPP_HIDE_FROM_ABI std::__type_descriptor_t __compute_type_descriptor() {
  // Construct the type descriptor for the given type. We also set a bit in the
  // type_kind part of the summary indicating this is generated from C++.
  auto __descriptor = __builtin_tmo_get_type_descriptor(_Tp);
  auto __from_cxx   = 0x00000c0000000000 | __descriptor;
  return std::__type_descriptor_t(__from_cxx);
}

#  define _LIBCPP_ADD_TYPE_DESCRIPTOR(_Type) , ::std::__compute_type_descriptor<_Type>()
#else
#  define _LIBCPP_ADD_TYPE_DESCRIPTOR(_Type) /* nothing */
#endif

template <class _Tp>
_LIBCPP_HIDE_FROM_ABI void* __libcpp_operator_new(size_t __n) {
#if __has_builtin(__builtin_operator_new) && __has_builtin(__builtin_operator_delete)
  return __builtin_operator_new(__n _LIBCPP_ADD_TYPE_DESCRIPTOR(_Tp));
#else
  return ::operator new(__n _LIBCPP_ADD_TYPE_DESCRIPTOR(_Tp));
#endif
}

template <class _Tp, class... _Args>
_LIBCPP_HIDE_FROM_ABI void* __libcpp_operator_new(_Args... __args) {
#if __has_builtin(__builtin_operator_new) && __has_builtin(__builtin_operator_delete)
  return __builtin_operator_new(__args...);
#else
  return ::operator new(__args...);
#endif
}

template <class... _Args>
_LIBCPP_HIDE_FROM_ABI void __libcpp_operator_delete(_Args... __args) _NOEXCEPT {
#if __has_builtin(__builtin_operator_new) && __has_builtin(__builtin_operator_delete)
  __builtin_operator_delete(__args...);
#else
  ::operator delete(__args...);
#endif
}

template <class _Tp>
inline _LIBCPP_HIDE_FROM_ABI _LIBCPP_NO_CFI _Tp*
__libcpp_allocate(__element_count __n, size_t __align = _LIBCPP_ALIGNOF(_Tp)) {
  size_t __size = static_cast<size_t>(__n) * sizeof(_Tp);
#if _LIBCPP_HAS_ALIGNED_ALLOCATION
  if (__is_overaligned_for_new(__align)) {
    const align_val_t __align_val = static_cast<align_val_t>(__align);
    return static_cast<_Tp*>(std::__libcpp_operator_new<_Tp>(__size, __align_val));
  }
#endif

  (void)__align;
  return static_cast<_Tp*>(std::__libcpp_operator_new<_Tp>(__size));
}

#if _LIBCPP_HAS_SIZED_DEALLOCATION
#  define _LIBCPP_ONLY_IF_SIZED_DEALLOCATION(...) __VA_ARGS__
#else
#  define _LIBCPP_ONLY_IF_SIZED_DEALLOCATION(...) /* nothing */
#endif

template <class _Tp>
inline _LIBCPP_HIDE_FROM_ABI void __libcpp_deallocate(
    __type_identity_t<_Tp>* __ptr, __element_count __n, size_t __align = _LIBCPP_ALIGNOF(_Tp)) _NOEXCEPT {
  size_t __size = static_cast<size_t>(__n) * sizeof(_Tp);
  (void)__size;
#if !_LIBCPP_HAS_ALIGNED_ALLOCATION
  (void)__align;
  return std::__libcpp_operator_delete(__ptr _LIBCPP_ONLY_IF_SIZED_DEALLOCATION(, __size));
#else
  if (__is_overaligned_for_new(__align)) {
    const align_val_t __align_val = static_cast<align_val_t>(__align);
    return std::__libcpp_operator_delete(__ptr _LIBCPP_ONLY_IF_SIZED_DEALLOCATION(, __size), __align_val);
  } else {
    return std::__libcpp_operator_delete(__ptr _LIBCPP_ONLY_IF_SIZED_DEALLOCATION(, __size));
  }
#endif
}

#undef _LIBCPP_ONLY_IF_SIZED_DEALLOCATION

template <class _Tp>
inline _LIBCPP_HIDE_FROM_ABI void
__libcpp_deallocate_unsized(__type_identity_t<_Tp>* __ptr, size_t __align = _LIBCPP_ALIGNOF(_Tp)) _NOEXCEPT {
#if !_LIBCPP_HAS_ALIGNED_ALLOCATION
  (void)__align;
  return std::__libcpp_operator_delete(__ptr);
#else
  if (__is_overaligned_for_new(__align)) {
    const align_val_t __align_val = static_cast<align_val_t>(__align);
    return std::__libcpp_operator_delete(__ptr, __align_val);
  } else {
    return std::__libcpp_operator_delete(__ptr);
  }
#endif
}
_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___NEW_ALLOCATE_H
