//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___NEW_GLOBAL_TYPED_NEW_DELETE_H
#define _LIBCPP___NEW_GLOBAL_TYPED_NEW_DELETE_H

#include <__config>
#include <__cstddef/size_t.h>
#include <__new/align_val_t.h>
#include <__new/exceptions.h>
#include <__new/global_new_delete.h>
#include <__new/nothrow_t.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

// Enable the typed operator declarations if the compiler wants to use the rewriting, or if
// we're building the library.
#if __has_feature(typed_cxx_new_delete) || defined(_LIBCPP_BUILDING_LIBRARY)
// On some platforms, we provide additional versions of the most common `operator new` overloads.
// Those operators take an additional type descriptor, which allows the implementation to pass type
// information down to malloc.
//
// Those are called automatically by the compiler when typed allocation rewriting is enabled via
// `-ftyped-cxx-new-delete`.
namespace std { // purposefully not versioned, like align_val_t
// We need 64 bits to represent this. We use `unsigned long long` instead of `uint64_t`
// to avoid taking a dependency on <cstdint>.
enum class __type_descriptor_t : unsigned long long;
} // namespace std

// new(size)
[[__nodiscard__]] _LIBCPP_OVERRIDABLE_FUNC_VIS void*
operator new(std::size_t __sz, std::__type_descriptor_t) _THROW_BAD_ALLOC;
[[__nodiscard__]] _LIBCPP_OVERRIDABLE_FUNC_VIS void*
operator new[](std::size_t __sz, std::__type_descriptor_t) _THROW_BAD_ALLOC;

// delete(ptr)
_LIBCPP_OVERRIDABLE_FUNC_VIS void operator delete(void* __p, std::__type_descriptor_t) _NOEXCEPT;
_LIBCPP_OVERRIDABLE_FUNC_VIS void operator delete[](void* __p, std::__type_descriptor_t) _NOEXCEPT;

#endif // __has_feature(typed_cxx_new_delete) || defined(_LIBCPP_BUILDING_LIBRARY)

#endif // _LIBCPP___NEW_GLOBAL_TYPED_NEW_DELETE_H
