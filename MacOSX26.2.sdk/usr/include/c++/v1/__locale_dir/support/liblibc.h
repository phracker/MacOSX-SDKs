//===-----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___LOCALE_DIR_SUPPORT_LIBLIBC_H
#define _LIBCPP___LOCALE_DIR_SUPPORT_LIBLIBC_H

#include <__config>
#include <__cstddef/size_t.h>
#include <__std_mbstate_t.h>
#include <__utility/forward.h>
#include <climits> // CHAR_MAX
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD
namespace __locale {

//
// Locale management
//
#define _LIBCPP_COLLATE_MASK (1 << 1)
#define _LIBCPP_CTYPE_MASK (1 << 2)
#define _LIBCPP_MONETARY_MASK (1 << 3)
#define _LIBCPP_NUMERIC_MASK (1 << 4)
#define _LIBCPP_TIME_MASK (1 << 5)
#define _LIBCPP_MESSAGES_MASK (1 << 6)
#define _LIBCPP_ALL_MASK                                                                                               \
  (_LIBCPP_COLLATE_MASK | _LIBCPP_CTYPE_MASK | _LIBCPP_MONETARY_MASK | _LIBCPP_NUMERIC_MASK | _LIBCPP_TIME_MASK |      \
   _LIBCPP_MESSAGES_MASK)
#define _LIBCPP_LC_ALL 0

using __locale_t = void*;

struct __lconv_t {
  char* decimal_point;
  char* thousands_sep;
  char* grouping;
  char* int_curr_symbol;
  char* currency_symbol;
  char* mon_decimal_point;
  char* mon_thousands_sep;
  char* mon_grouping;
  char* positive_sign;
  char* negative_sign;
  char int_frac_digits;
  char frac_digits;
  char p_cs_precedes;
  char p_sep_by_space;
  char n_cs_precedes;
  char n_sep_by_space;
  char p_sign_posn;
  char n_sign_posn;
  char int_p_cs_precedes;
  char int_n_cs_precedes;
  char int_p_sep_by_space;
  char int_n_sep_by_space;
  char int_p_sign_posn;
  char int_n_sign_posn;
};

inline constexpr char* __empty_string     = "";
inline _LIBCPP_CONSTINIT __lconv_t __unique_lconv = {
    .decimal_point      = __empty_string,
    .thousands_sep      = __empty_string,
    .grouping           = __empty_string,
    .int_curr_symbol    = __empty_string,
    .currency_symbol    = __empty_string,
    .mon_decimal_point  = __empty_string,
    .mon_thousands_sep  = __empty_string,
    .mon_grouping       = __empty_string,
    .positive_sign      = __empty_string,
    .negative_sign      = __empty_string,
    .int_frac_digits    = CHAR_MAX,
    .frac_digits        = CHAR_MAX,
    .p_cs_precedes      = CHAR_MAX,
    .p_sep_by_space     = CHAR_MAX,
    .n_cs_precedes      = CHAR_MAX,
    .n_sep_by_space     = CHAR_MAX,
    .p_sign_posn        = CHAR_MAX,
    .n_sign_posn        = CHAR_MAX,
    .int_p_cs_precedes  = CHAR_MAX,
    .int_n_cs_precedes  = CHAR_MAX,
    .int_p_sep_by_space = CHAR_MAX,
    .int_n_sep_by_space = CHAR_MAX,
    .int_p_sign_posn    = CHAR_MAX,
    .int_n_sign_posn    = CHAR_MAX,
};

inline _LIBCPP_HIDE_FROM_ABI __locale_t __uselocale(__locale_t) { return nullptr; }

inline _LIBCPP_HIDE_FROM_ABI __locale_t __newlocale(int, const char*, __locale_t) { return nullptr; }

inline _LIBCPP_HIDE_FROM_ABI char* __setlocale(int, char const*) {
  static _LIBCPP_CONSTINIT char __c_locale[] = "C";
  return __c_locale;
}

inline _LIBCPP_HIDE_FROM_ABI void __freelocale(__locale_t) {}

inline _LIBCPP_HIDE_FROM_ABI __lconv_t* __localeconv(__locale_t&) { return &__unique_lconv; }

//
// Strtonum functions
//
inline _LIBCPP_HIDE_FROM_ABI float __strtof(const char* __nptr, char** __endptr, __locale_t) {
  return ::strtof(__nptr, __endptr);
}

inline _LIBCPP_HIDE_FROM_ABI double __strtod(const char* __nptr, char** __endptr, __locale_t) {
  return ::strtod(__nptr, __endptr);
}

inline _LIBCPP_HIDE_FROM_ABI long double __strtold(const char* __nptr, char** __endptr, __locale_t) {
  return ::strtold(__nptr, __endptr);
}

inline _LIBCPP_HIDE_FROM_ABI long long __strtoll(const char* __nptr, char** __endptr, int __base, __locale_t) {
  return ::strtoll(__nptr, __endptr, __base);
}

inline _LIBCPP_HIDE_FROM_ABI unsigned long long
__strtoull(const char* __nptr, char** __endptr, int __base, __locale_t) {
  return ::strtoull(__nptr, __endptr, __base);
}

//
// Character manipulation functions
//
inline _LIBCPP_HIDE_FROM_ABI int __islower(int __c, __locale_t) { return ::islower(__c); }

inline _LIBCPP_HIDE_FROM_ABI int __isupper(int __c, __locale_t) { return ::isupper(__c); }

inline _LIBCPP_HIDE_FROM_ABI int __isdigit(int __c, __locale_t) { return ::isdigit(__c); }

inline _LIBCPP_HIDE_FROM_ABI int __isxdigit(int __c, __locale_t) { return ::isxdigit(__c); }

inline _LIBCPP_HIDE_FROM_ABI int __toupper(int __c, __locale_t) { return ::toupper(__c); }

inline _LIBCPP_HIDE_FROM_ABI int __tolower(int __c, __locale_t) { return ::tolower(__c); }

inline _LIBCPP_HIDE_FROM_ABI int __strcoll(const char* __s1, const char* __s2, __locale_t) {
  return ::strcoll(__s1, __s2);
}

inline _LIBCPP_HIDE_FROM_ABI size_t __strxfrm(char* __dest, const char* __src, size_t __n, __locale_t) {
  return ::strxfrm(__dest, __src, __n);
}

// Wide character manipulation functions are not provided

inline _LIBCPP_HIDE_FROM_ABI size_t
__strftime(char* __s, size_t __max, const char* __format, const struct tm* __tm, __locale_t) {
  return ::strftime(__s, __max, __format, __tm);
}

//
// Other functions
//
inline _LIBCPP_HIDE_FROM_ABI decltype(MB_CUR_MAX) __mb_len_max(__locale_t) { return MB_CUR_MAX; }

// Wide character misc functions are not provided

_LIBCPP_DIAGNOSTIC_PUSH
_LIBCPP_CLANG_DIAGNOSTIC_IGNORED("-Wgcc-compat") // GCC doesn't support [[gnu::format]] on variadic templates
template <class... _Args>
_LIBCPP_HIDE_FROM_ABI _LIBCPP_ATTRIBUTE_FORMAT(__printf__, 4, 5) int __snprintf(
    char* __s, size_t __n, __locale_t, const char* __format, _Args&&... __args) {
  return ::snprintf(__s, __n, __format, std::forward<_Args>(__args)...);
}

template <class... _Args>
_LIBCPP_HIDE_FROM_ABI _LIBCPP_ATTRIBUTE_FORMAT(__printf__, 3, 4) int __asprintf(
    char** __s, __locale_t, const char* __format, _Args&&... __args) {
  return ::asprintf(__s, __format, std::forward<_Args>(__args)...);
}

template <class... _Args>
_LIBCPP_HIDE_FROM_ABI _LIBCPP_ATTRIBUTE_FORMAT(__scanf__, 3, 4) int __sscanf(
    const char* __s, __locale_t, const char* __format, _Args&&... __args) {
  return ::sscanf(__s, __format, std::forward<_Args>(__args)...);
}
_LIBCPP_DIAGNOSTIC_POP

} // namespace __locale
_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___LOCALE_DIR_SUPPORT_LIBLIBC_H
