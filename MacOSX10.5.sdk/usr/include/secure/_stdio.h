/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _STDIO_H_
 #error error "Never use <secure/_stdio.h> directly; include <stdio.h> instead."
#endif

#ifndef _SECURE__STDIO_H_
#define _SECURE__STDIO_H_

#include <secure/_common.h>

#if _USE_FORTIFY_LEVEL > 0

#undef sprintf
#undef vsprintf
#undef snprintf
#undef vsnprintf

/* sprintf, vsprintf, snprintf, vsnprintf */

extern int __sprintf_chk (char * __restrict, int, size_t,
			  const char * __restrict, ...)
  __DARWIN_LDBL_COMPAT (__sprintf_chk);

#define sprintf(str, ...) \
  __builtin___sprintf_chk (str, 0, __darwin_obsz(str), __VA_ARGS__)

extern int __snprintf_chk (char * __restrict, size_t, int, size_t,
			   const char * __restrict, ...)
  __DARWIN_LDBL_COMPAT (__snprintf_chk);

#define snprintf(str, len, ...) \
  __builtin___snprintf_chk (str, len, 0, __darwin_obsz(str), __VA_ARGS__)

extern int __vsprintf_chk (char * __restrict, int, size_t,
			   const char * __restrict, va_list arg)
  __DARWIN_LDBL_COMPAT (__vsprintf_chk);

#define vsprintf(str, format, ap) \
  __builtin___vsprintf_chk (str, 0, __darwin_obsz(str), format, ap)

extern int __vsnprintf_chk (char * __restrict, size_t, int, size_t,
			    const char * __restrict, va_list arg)
  __DARWIN_LDBL_COMPAT (__vsnprintf_chk);

#define vsnprintf(str, len, format, ap) \
  __builtin___vsnprintf_chk (str, len, 0, __darwin_obsz(str), format, ap)


#endif

#endif
