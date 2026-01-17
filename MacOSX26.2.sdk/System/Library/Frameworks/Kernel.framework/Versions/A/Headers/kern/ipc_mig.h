/*
 * Copyright (c) 2000-2005 Apple Computer, Inc. All rights reserved.
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
 * @OSF_COPYRIGHT@
 */

#ifndef _KERN_IPC_MIG_H_
#define _KERN_IPC_MIG_H_

#include <mach/mig.h>
#include <mach/mach_types.h>
#include <mach/message.h>
#include <kern/kern_types.h>

#include <sys/cdefs.h>


__BEGIN_DECLS

/* Send a message from the kernel */

extern mach_msg_return_t mach_msg_send_from_kernel_proper(
	mach_msg_header_t       *msg,
	mach_msg_size_t         send_size);

#define mach_msg_send_from_kernel mach_msg_send_from_kernel_proper

/*
 * Allocate kernel message buffer(s) large enough to fit the message,
 * and accept a block that populates the message content.
 *
 *     - descriptor_count: Descriptor count in the outgoing message. If non-zero,
 *       kernel expects a complex message, and vice-versa.
 *
 *     - payload_size: Size of data not processed by kernel (i.e. size of data
 *       following the header, or last descriptor if the message is complex).
 *       This is NOT the total size of the outgoing message.
 *
 * For memory safety the kmsg buffers allocated may occupy non-contiguous memory
 * and it is the caller's responsibility to correctly set up the message
 * based on content's offset from the mach message header, as follows:
 *
 * void (^builder)(mach_msg_header_t *header, mach_msg_descriptor_t *descs, void *payload))
 *
 *            header* ───────► ┌─────────────────────────┐
 *                             │                         │
 *                             │    mach_msg_header_t    │
 *                             │                         │
 *                             ├─────────────────────────┤
 *                             │(optional)mach_msg_body_t│
 *             descs* ───────► ├─────────────────────────┤
 *                             │                         │
 *                             │                         │
 *                             │                         │
 *                             │  (optional)descriptors  │
 *                             │                         │
 *                             │                         │
 *                             │                         │
 *                             └─────────────────────────┘
 *                              ~~~~~~~~void space~~~~~~~
 *           payload* ───────► ┌─────────────────────────┐
 *                             │                         │
 *                             │                         │
 *                             │    other data in msg    │
 *                             │                         │
 *                             │                         │
 *                             └─────────────────────────┘
 *
 *     header: Points to the start of the message, caller should populate this
 *          with the mach message header.
 *
 *     descs: Pointers to the start of kernel descriptors region, if caller requested
 *          a non-zero descriptor_count. Or NULL if descriptor_count is 0 (meaning
 *          the messsage is not complex). Caller should populate this with descriptors.
 *
 *     payload: Points to the start of data not processed by kernel, which is after
 *          the last descriptor, if caller requested a non-zero payload_size. Or
 *          NULL if payload_size is 0.
 *
 *     Mach message body (descriptor count) will be set after the builder accordingly.
 */

extern mach_msg_return_t kernel_mach_msg_send_with_builder(
	mach_msg_size_t         descriptor_count,
	mach_msg_size_t         payload_size,    /* Warning: NOT total send size */
	void                  (^builder)(mach_msg_header_t *header,
	mach_msg_descriptor_t  *__counted_by(descriptor_count)descs, /* Nullable */
	void                   *__sized_by(payload_size)payload));   /* Nullable */


extern mach_msg_return_t mach_msg_rpc_from_kernel_proper(
	mach_msg_header_t      *msg,
	mach_msg_size_t         send_size,
	mach_msg_size_t         rcv_size);

extern void mach_msg_destroy_from_kernel_proper(
	mach_msg_header_t      *msg);

#define mach_msg_rpc_from_kernel    mach_msg_rpc_from_kernel_proper
#define mach_msg_destroy_from_kernel mach_msg_destroy_from_kernel_proper



__END_DECLS

#endif  /* _KERN_IPC_MIG_H_ */
