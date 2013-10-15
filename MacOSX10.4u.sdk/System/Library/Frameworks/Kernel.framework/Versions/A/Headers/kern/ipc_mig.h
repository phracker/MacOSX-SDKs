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

#ifndef	_KERN_IPC_MIG_H_
#define	_KERN_IPC_MIG_H_

#include <mach/mig.h>
#include <mach/mach_types.h>
#include <mach/message.h>
#include <kern/kern_types.h>

#include <sys/cdefs.h>


__BEGIN_DECLS

/* Send a message from the kernel */
extern mach_msg_return_t mach_msg_send_from_kernel(
	mach_msg_header_t	*msg,
	mach_msg_size_t		send_size);


extern mach_msg_return_t mach_msg_rpc_from_kernel(
	mach_msg_header_t	*msg,
	mach_msg_size_t		send_size,
	mach_msg_size_t		rcv_size);

__END_DECLS


#endif	/* _KERN_IPC_MIG_H_ */
