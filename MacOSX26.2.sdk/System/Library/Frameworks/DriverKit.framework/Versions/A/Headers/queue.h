/*
 * Copyright (c) 2020-2020 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#define DRIVERKIT_FRAMEWORK_INCLUDE	1

__BEGIN_DECLS
__abortlike __printflike(1, 2)
extern void panic(const char *string, ...);
__END_DECLS

#if !defined(__improbable)
#   define __improbable(...) __builtin_expect((__VA_ARGS__), 0)
#endif

#include <DriverKit/queue_implementation.h>

#if !defined(__container_of)
#if defined(__cplusplus)
#define __container_of(ptr, type, field) __extension__({ \
	        const __typeof__(((type *)nullptr)->field) *__ptr = (ptr); \
	        (type *)((uintptr_t)__ptr - offsetof(type, field)); \
	})
#else
#define __container_of(ptr, type, field) __extension__({ \
	        const __typeof__(((type *)NULL)->field) *__ptr = (ptr); \
	        (type *)((uintptr_t)__ptr - offsetof(type, field)); \
	})
#endif
#endif /* !defined(__container_of) */
