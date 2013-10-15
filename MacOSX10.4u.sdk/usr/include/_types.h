/*
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
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

#ifndef __TYPES_H_
#define __TYPES_H_

#include <sys/_types.h>

typedef	int		__darwin_nl_item;
typedef	int		__darwin_wctrans_t;
#ifdef __LP64__
typedef	__uint32_t	__darwin_wctype_t;
#else /* !__LP64__ */
typedef	unsigned long	__darwin_wctype_t;
#endif /* __LP64__ */

#ifdef __WCHAR_MAX__
#define __DARWIN_WCHAR_MAX	__WCHAR_MAX__
#else /* ! __WCHAR_MAX__ */
#define __DARWIN_WCHAR_MAX	0x7fffffff
#endif /* __WCHAR_MAX__ */

#if __DARWIN_WCHAR_MAX > 0xffffU
#define __DARWIN_WCHAR_MIN	(-0x7fffffff - 1)
#else
#define __DARWIN_WCHAR_MIN	0
#endif
#define	__DARWIN_WEOF 	((__darwin_wint_t)-1)

#endif /* __TYPES_H_ */
