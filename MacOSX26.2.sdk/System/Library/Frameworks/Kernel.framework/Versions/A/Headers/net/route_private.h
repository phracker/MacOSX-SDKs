/*
 * Copyright (c) 2000-2022 Apple Inc. All rights reserved.
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
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)route.h	8.3 (Berkeley) 4/19/94
 * $FreeBSD: src/sys/net/route.h,v 1.36.2.1 2000/08/16 06:14:23 jayanth Exp $
 */

#ifndef _NET_ROUTE_PRIVATE_H_
#define _NET_ROUTE_PRIVATE_H_
#include <net/route.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <uuid/uuid.h>

struct route_old {
	void            *ro_rt;
	uint32_t        ro_flags;
	struct sockaddr ro_dst;
};


struct kev_netevent_apnfallbk_data {
	pid_t           epid;           /* effective PID */
	uuid_t          euuid;          /* effective UUID */
};

/*
 * Route reachability info.
 */
struct rt_reach_info {
	u_int32_t       ri_refcnt;      /* reference count */
	u_int32_t       ri_probes;      /* total # of probes */
	u_int64_t       ri_snd_expire;  /* tx expiration (calendar) time */
	u_int64_t       ri_rcv_expire;  /* rx expiration (calendar) time */
	int32_t         ri_rssi;        /* received signal strength */
	int32_t         ri_lqm;         /* link quality metric */
	int32_t         ri_npm;         /* node proximity metric */
};


/*
 * Route address information with extra space for "tiny" socket addresses
 * from the user space. A "tiny" socket address has the `sa_len' field
 * smaller than the canonical sockaddr structure.
 * To preserve the type and the bounds safety, such "tiny" addresses
 * are copied to the `rtix_tiny_addr' field.
 */
struct rt_addrinfo_ext {
	struct rt_addrinfo rtix_info;                    /* addr info containing sockaddr array */
	struct sockaddr    rtix_tiny_addr[RTAX_MAX];     /* storage for the "tiny" sockaddr addresss */
	uint8_t            rtix_next_tiny;               /* offset of the next "tiny" address */
};

/*
 * The following is used internally when parsing routing
 * messages to avoid potential boundary issues when
 * using shorter structures.
 */
struct rt_msghdr_common {
	u_short rtm_msglen;     /* to skip over non-understood messages */
	u_char  rtm_version;    /* future binary compatibility */
	u_char  rtm_type;       /* message type */
	u_short rtm_index;      /* index for associated ifp */
	int     rtm_flags;      /* flags, incl. kern & message, e.g. DONE */
	int     rtm_addrs;      /* bitmask identifying sockaddrs in msg */
	pid_t   rtm_pid;        /* identify sender */
	int     rtm_seq;        /* for sender to identify action */
	int     rtm_errno;      /* why failed */
	int     rtm_use;        /* from rtentry */
};

/*
 * Extended routing message header (private).
 */
struct rt_msghdr_ext {
	u_short rtm_msglen;     /* to skip over non-understood messages */
	u_char  rtm_version;    /* future binary compatibility */
	u_char  rtm_type;       /* message type */
	u_int32_t rtm_index;    /* index for associated ifp */
	u_int32_t rtm_flags;    /* flags, incl. kern & message, e.g. DONE */
	u_int32_t rtm_reserved; /* for future use */
	u_int32_t rtm_addrs;    /* bitmask identifying sockaddrs in msg */
	pid_t   rtm_pid;        /* identify sender */
	int     rtm_seq;        /* for sender to identify action */
	int     rtm_errno;      /* why failed */
	u_int32_t rtm_use;      /* from rtentry */
	u_int32_t rtm_inits;    /* which metrics we are initializing */
	struct rt_metrics rtm_rmx;      /* metrics themselves */
	struct rt_reach_info rtm_ri;    /* route reachability info */
};

/*
 * Message types.
 */
#define RTM_GET_SILENT  0x11
#define RTM_GET_EXT     0x15

/*
 * Bitmask values for rtm_inits and rmx_locks.
 */
#define RTV_REFRESH_HOST        0x100   /* init host route to expedite refresh */

/*
 * For scoped routing; a zero interface scope value means nil/no scope.
 */
#define IFSCOPE_NONE    0
#define IFSCOPE_UNKNOWN IFSCOPE_NONE

/*
 * Routing statistics.
 */
struct rtstat_64 {
	uint64_t        rts_badredirect;        /* bogus redirect calls */
	uint64_t        rts_dynamic;            /* routes created by redirects */
	uint64_t        rts_newgateway;         /* routes modified by redirects */
	uint64_t        rts_unreach;            /* lookups which failed */
	uint64_t        rts_wildcard;           /* lookups satisfied by a wildcard */
	uint64_t        rts_badrtgwroute;       /* route to gateway is not direct */
};

#endif /* _NET_ROUTE_PRIVATE_H_ */
