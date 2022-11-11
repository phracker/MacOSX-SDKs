/*
 * Copyright (c) 1999-2013 Apple Inc. All rights reserved.
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
 * Support for socket filter kernel extensions
 */

#ifndef NET_KEXT_NET_H
#define NET_KEXT_NET_H

#include <sys/appleapiopts.h>

#include <sys/queue.h>
#include <sys/cdefs.h>
#include <sys/types.h>


#define NFF_BEFORE              0x01
#define NFF_AFTER               0x02

#define NKE_OK                  0
#define NKE_REMOVE              (-1)

/*
 * Interface structure for inserting an installed socket NKE into an
 *  existing socket.
 * 'handle' is the NKE to be inserted, 'where' is an insertion point,
 *  and flags dictate the position of the to-be-inserted NKE relative to
 *  the 'where' NKE.  If the latter is NULL, the flags indicate "first"
 *  or "last"
 */
#pragma pack(4)

struct so_nke {
	unsigned int nke_handle;
	unsigned int nke_where;
	int nke_flags; /* NFF_BEFORE, NFF_AFTER: net/kext_net.h */
	u_int32_t reserved[4];  /* for future use */
};

#pragma pack()
#endif /* NET_KEXT_NET_H */
