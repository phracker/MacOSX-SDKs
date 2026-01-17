/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 */
/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _MACH_MACHINE_SYS_SDT_H
#define	_MACH_MACHINE_SYS_SDT_H

#include <mach/machine/sdt_isa.h>

/*
 * The following macros are used to create static probes. The argument types
 * should be no greater than uintptr_t in size each. The behavior of larger
 * types is undefined.
 */

#define DTRACE_PROBE(provider, name) {								\
	DTRACE_CALL0ARGS(provider, name)							\
}

#define DTRACE_PROBE1(provider, name, arg0) {							\
	uintptr_t __dtrace_args[ARG1_EXTENT] __attribute__ ((aligned (16)));			\
	__dtrace_args[0] = (uintptr_t)arg0;								\
	DTRACE_CALL1ARG(provider, name)								\
}

#define DTRACE_PROBE2(provider, name, arg0, arg1) {						\
	uintptr_t __dtrace_args[ARGS2_EXTENT] __attribute__ ((aligned (16)));			\
	__dtrace_args[0] = (uintptr_t)arg0;								\
	__dtrace_args[1] = (uintptr_t)arg1;								\
	DTRACE_CALL2ARGS(provider, name)							\
}

#define DTRACE_PROBE3(provider, name, arg0, arg1, arg2) {					\
	uintptr_t __dtrace_args[ARGS3_EXTENT] __attribute__ ((aligned (16)));			\
	__dtrace_args[0] = (uintptr_t)arg0;								\
	__dtrace_args[1] = (uintptr_t)arg1;								\
	__dtrace_args[2] = (uintptr_t)arg2;								\
	DTRACE_CALL3ARGS(provider, name)							\
}

#define DTRACE_PROBE4(provider, name, arg0, arg1, arg2, arg3) {					\
	uintptr_t __dtrace_args[ARGS4_EXTENT] __attribute__ ((aligned (16)));			\
	__dtrace_args[0] = (uintptr_t)arg0;								\
	__dtrace_args[1] = (uintptr_t)arg1;								\
	__dtrace_args[2] = (uintptr_t)arg2;								\
	__dtrace_args[3] = (uintptr_t)arg3;								\
	DTRACE_CALL4ARGS(provider, name)							\
}

#define DTRACE_PROBE5(provider, name, arg0, arg1, arg2, arg3, arg4) {				\
	uintptr_t __dtrace_args[ARGS5_EXTENT] __attribute__ ((aligned (16)));			\
	__dtrace_args[0] = (uintptr_t)arg0;								\
	__dtrace_args[1] = (uintptr_t)arg1;								\
	__dtrace_args[2] = (uintptr_t)arg2;								\
	__dtrace_args[3] = (uintptr_t)arg3;								\
	__dtrace_args[4] = (uintptr_t)arg4;								\
	DTRACE_CALL5ARGS(provider, name)							\
}

#define DTRACE_PROBE6(provider, name, arg0, arg1, arg2, arg3, arg4, arg5) {			\
	uintptr_t __dtrace_args[ARGS6_EXTENT] __attribute__ ((aligned (16)));			\
	__dtrace_args[0] = (uintptr_t)arg0;								\
	__dtrace_args[1] = (uintptr_t)arg1;								\
	__dtrace_args[2] = (uintptr_t)arg2;								\
	__dtrace_args[3] = (uintptr_t)arg3;								\
	__dtrace_args[4] = (uintptr_t)arg4;								\
	__dtrace_args[5] = (uintptr_t)arg5;								\
	DTRACE_CALL6ARGS(provider, name)							\
}

#define DTRACE_PROBE7(provider, name, arg0, arg1, arg2, arg3, arg4, arg5, arg6) {		\
	uintptr_t __dtrace_args[ARGS7_EXTENT] __attribute__ ((aligned (16)));			\
	__dtrace_args[0] = (uintptr_t)arg0;								\
	__dtrace_args[1] = (uintptr_t)arg1;								\
	__dtrace_args[2] = (uintptr_t)arg2;								\
	__dtrace_args[3] = (uintptr_t)arg3;								\
	__dtrace_args[4] = (uintptr_t)arg4;								\
	__dtrace_args[5] = (uintptr_t)arg5;								\
	__dtrace_args[6] = (uintptr_t)arg6;								\
	DTRACE_CALL7ARGS(provider, name)							\
}

#define DTRACE_PROBE8(provider, name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) {		\
	uintptr_t __dtrace_args[ARGS8_EXTENT] __attribute__ ((aligned (16)));			\
	__dtrace_args[0] = (uintptr_t)arg0;								\
	__dtrace_args[1] = (uintptr_t)arg1;								\
	__dtrace_args[2] = (uintptr_t)arg2;								\
	__dtrace_args[3] = (uintptr_t)arg3;								\
	__dtrace_args[4] = (uintptr_t)arg4;								\
	__dtrace_args[5] = (uintptr_t)arg5;								\
	__dtrace_args[6] = (uintptr_t)arg6;								\
	__dtrace_args[7] = (uintptr_t)arg7;								\
	DTRACE_CALL8ARGS(provider, name)							\
}

#define DTRACE_PROBE9(provider, name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) {	\
	uintptr_t __dtrace_args[ARGS9_EXTENT] __attribute__ ((aligned (16)));			\
	__dtrace_args[0] = (uintptr_t)arg0;								\
	__dtrace_args[1] = (uintptr_t)arg1;								\
	__dtrace_args[2] = (uintptr_t)arg2;								\
	__dtrace_args[3] = (uintptr_t)arg3;								\
	__dtrace_args[4] = (uintptr_t)arg4;								\
	__dtrace_args[5] = (uintptr_t)arg5;								\
	__dtrace_args[6] = (uintptr_t)arg6;								\
	__dtrace_args[7] = (uintptr_t)arg7;								\
	__dtrace_args[8] = (uintptr_t)arg8;								\
	DTRACE_CALL9ARGS(provider, name)							\
}

#define DTRACE_PROBE10(provider, name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) {	\
	uintptr_t __dtrace_args[ARGS10_EXTENT] __attribute__ ((aligned (16)));				\
	__dtrace_args[0] = (uintptr_t)arg0;									\
	__dtrace_args[1] = (uintptr_t)arg1;									\
	__dtrace_args[2] = (uintptr_t)arg2;									\
	__dtrace_args[3] = (uintptr_t)arg3;									\
	__dtrace_args[4] = (uintptr_t)arg4;									\
	__dtrace_args[5] = (uintptr_t)arg5;									\
	__dtrace_args[6] = (uintptr_t)arg6;									\
	__dtrace_args[7] = (uintptr_t)arg7;									\
	__dtrace_args[8] = (uintptr_t)arg8;									\
	__dtrace_args[9] = (uintptr_t)arg9;									\
	DTRACE_CALL10ARGS(provider, name)								\
}



#endif	/* _MACH_MACHINE_SYS_SDT_H */
