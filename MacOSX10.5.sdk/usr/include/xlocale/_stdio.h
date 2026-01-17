/*
 * Copyright (c) 2005 Apple Computer, Inc. All rights reserved.
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

#ifndef _XLOCALE__STDIO_H_
#define _XLOCALE__STDIO_H_

__BEGIN_DECLS
int	 asprintf_l(char **, locale_t, const char *, ...)
		__DARWIN_LDBL_COMPAT2(asprintf_l);
int	 fprintf_l(FILE * __restrict, locale_t, const char * __restrict, ...)
		__DARWIN_LDBL_COMPAT2(fprintf_l);
int	 fscanf_l(FILE * __restrict, locale_t, const char * __restrict, ...)
		__DARWIN_LDBL_COMPAT2(fscanf_l);
int	 printf_l(locale_t, const char * __restrict, ...)
		__DARWIN_LDBL_COMPAT2(printf_l);
int	 scanf_l(locale_t, const char * __restrict, ...)
		__DARWIN_LDBL_COMPAT2(scanf_l);
int	 snprintf_l(char * __restrict, size_t, locale_t,
		const char * __restrict, ...) __DARWIN_LDBL_COMPAT2(snprintf_l);
int	 sprintf_l(char * __restrict, locale_t, const char * __restrict, ...)
		__DARWIN_LDBL_COMPAT2(sprintf_l);
int	 sscanf_l(const char * __restrict, locale_t, const char * __restrict,
		...) __DARWIN_LDBL_COMPAT2(sscanf_l);
int	 vasprintf_l(char **, locale_t, const char *, va_list)
		__DARWIN_LDBL_COMPAT2(vasprintf_l);
int	 vfprintf_l(FILE * __restrict, locale_t, const char * __restrict,
		va_list) __DARWIN_LDBL_COMPAT2(vfprintf_l);
int	 vfscanf_l(FILE * __restrict, locale_t, const char * __restrict,
		va_list) __DARWIN_LDBL_COMPAT2(vfscanf_l);
int	 vprintf_l(locale_t, const char * __restrict, va_list)
		__DARWIN_LDBL_COMPAT2(vprintf_l);
int	 vscanf_l(locale_t, const char * __restrict, va_list)
		__DARWIN_LDBL_COMPAT2(vscanf_l);
int	 vsnprintf_l(char * __restrict, size_t, locale_t,
		const char * __restrict, va_list)
		__DARWIN_LDBL_COMPAT2(vsnprintf_l);
int	 vsprintf_l(char * __restrict, locale_t, const char * __restrict,
		va_list) __DARWIN_LDBL_COMPAT2(vsprintf_l);
int	 vsscanf_l(const char * __restrict, locale_t, const char * __restrict,
		va_list) __DARWIN_LDBL_COMPAT2(vsscanf_l);
__END_DECLS

#endif /* _XLOCALE__STDIO_H_ */
