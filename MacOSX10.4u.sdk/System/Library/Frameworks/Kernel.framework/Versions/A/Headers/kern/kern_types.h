/*
 * Copyright (c) 2000-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * @OSF_COPYRIGHT@
 */

#ifndef	_KERN_KERN_TYPES_H_
#define	_KERN_KERN_TYPES_H_

#include <stdint.h>
#include <mach/mach_types.h>
#include <mach/machine/vm_types.h>


typedef	void *event_t;		/* wait event */
#define		NO_EVENT			((event_t) 0)

typedef uint64_t event64_t;		/* 64 bit wait event */
#define		NO_EVENT64		((event64_t) 0)

/*
 *	Possible wait_result_t values.
 */
typedef int wait_result_t;
#define THREAD_WAITING		-1		/* thread is waiting */
#define THREAD_AWAKENED		0		/* normal wakeup */
#define THREAD_TIMED_OUT	1		/* timeout expired */
#define THREAD_INTERRUPTED	2		/* aborted/interrupted */
#define THREAD_RESTART		3		/* restart operation entirely */


typedef	void (*thread_continue_t)(void *, wait_result_t);
#define	THREAD_CONTINUE_NULL	((thread_continue_t) 0)

/*
 * Interruptible flag for waits.
 */
typedef int wait_interrupt_t;
#define THREAD_UNINT			0		/* not interruptible      */
#define THREAD_INTERRUPTIBLE	1		/* may not be restartable */
#define THREAD_ABORTSAFE		2		/* abortable safely       */


#endif	/* _KERN_KERN_TYPES_H_ */
