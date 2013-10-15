/*
 * Copyright (c) 1993-1995, 1999-2008 Apple Inc. All rights reserved.
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
/*
 * Declarations for thread-based callouts.
 */

#ifndef _KERN_THREAD_CALL_H_
#define _KERN_THREAD_CALL_H_

#include <mach/mach_types.h>

#include <kern/clock.h>

#include <sys/cdefs.h>

typedef struct call_entry	*thread_call_t;
typedef void				*thread_call_param_t;
typedef void				(*thread_call_func_t)(
									thread_call_param_t		param0,
									thread_call_param_t		param1);
__BEGIN_DECLS

extern boolean_t	thread_call_enter(
						thread_call_t		call);

extern boolean_t	thread_call_enter1(
						thread_call_t			call,
						thread_call_param_t		param1);

extern boolean_t	thread_call_enter_delayed(
						thread_call_t		call,
						uint64_t			deadline);

extern boolean_t	thread_call_enter1_delayed(
						thread_call_t			call,
						thread_call_param_t		param1,
						uint64_t				deadline);

extern boolean_t	thread_call_cancel(
						thread_call_t		call);

extern thread_call_t	thread_call_allocate(
							thread_call_func_t		func,
							thread_call_param_t		param0);

extern boolean_t		thread_call_free(
							thread_call_t		call);

__END_DECLS



#endif	/* _KERN_THREAD_CALL_H_ */
