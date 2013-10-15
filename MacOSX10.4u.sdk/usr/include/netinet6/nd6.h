/*	$FreeBSD: src/sys/netinet6/nd6.h,v 1.2.2.3 2001/08/13 01:10:49 simokawa Exp $	*/
/*	$KAME: nd6.h,v 1.55 2001/04/27 15:09:49 itojun Exp $	*/

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _NETINET6_ND6_H_
#define _NETINET6_ND6_H_
#include <sys/appleapiopts.h>

/* see net/route.h, or net/if_inarp.h */
#ifndef RTF_ANNOUNCE
#define RTF_ANNOUNCE	RTF_PROTO2
#endif

#include <sys/queue.h>


#define ND6_LLINFO_NOSTATE	-2
/*
 * We don't need the WAITDELETE state any more, but we keep the definition
 * in a comment line instead of removing it. This is necessary to avoid
 * unintentionally reusing the value for another purpose, which might
 * affect backward compatibility with old applications.
 * (20000711 jinmei@kame.net)
 */
/* #define ND6_LLINFO_WAITDELETE	-1 */
#define ND6_LLINFO_INCOMPLETE	0
#define ND6_LLINFO_REACHABLE	1
#define ND6_LLINFO_STALE	2
#define ND6_LLINFO_DELAY	3
#define ND6_LLINFO_PROBE	4

#define ND6_IS_LLINFO_PROBREACH(n) ((n)->ln_state > ND6_LLINFO_INCOMPLETE)

struct nd_ifinfo {
	u_int32_t linkmtu;		/* LinkMTU */
	u_int32_t maxmtu;		/* Upper bound of LinkMTU */
	u_int32_t basereachable;	/* BaseReachableTime */
	u_int32_t reachable;		/* Reachable Time */
	u_int32_t retrans;		/* Retrans Timer */
	u_int32_t flags;		/* Flags */
	int recalctm;			/* BaseReacable re-calculation timer */
	u_int8_t chlim;			/* CurHopLimit */
	u_int8_t receivedra;
	/* the following 3 members are for privacy extension for addrconf */
	u_int8_t randomseed0[8]; /* upper 64 bits of MD5 digest */
	u_int8_t randomseed1[8]; /* lower 64 bits (usually the EUI64 IFID) */
	u_int8_t randomid[8];	/* current random ID */
};

#define ND6_IFF_PERFORMNUD	0x1

struct in6_nbrinfo {
	char ifname[IFNAMSIZ];	/* if name, e.g. "en0" */
	struct in6_addr addr;	/* IPv6 address of the neighbor */
	long	asked;		/* number of queries already sent for this addr */
	int	isrouter;	/* if it acts as a router */
	int	state;		/* reachability state */
	int	expire;		/* lifetime for NDP state transition */
};

#define DRLSTSIZ 10
#define PRLSTSIZ 10
struct	in6_drlist {
	char ifname[IFNAMSIZ];
	struct {
		struct	in6_addr rtaddr;
		u_char	flags;
		u_short	rtlifetime;
		u_long	expire;
		u_short if_index;
	} defrouter[DRLSTSIZ];
};

struct	in6_defrouter {
	struct	sockaddr_in6 rtaddr;
	u_char	flags;
	u_short	rtlifetime;
	u_long	expire;
	u_short if_index;
};

struct	in6_prlist {
	char ifname[IFNAMSIZ];
	struct {
		struct	in6_addr prefix;
		struct prf_ra raflags;
		u_char	prefixlen;
		u_char	origin;
		u_long	vltime;
		u_long	pltime;
		u_long	expire;
		u_short if_index;
		u_short advrtrs; /* number of advertisement routers */
		struct	in6_addr advrtr[DRLSTSIZ]; /* XXX: explicit limit */
	} prefix[PRLSTSIZ];
};

struct in6_prefix {
	struct	sockaddr_in6 prefix;
	struct prf_ra raflags;
	u_char	prefixlen;
	u_char	origin;
	u_long	vltime;
	u_long	pltime;
	u_long	expire;
	u_int32_t flags;
	int refcnt;
	u_short if_index;
	u_short advrtrs; /* number of advertisement routers */
	/* struct sockaddr_in6 advrtr[] */
};

struct	in6_ondireq {
	char ifname[IFNAMSIZ];
	struct {
		u_int32_t linkmtu;	/* LinkMTU */
		u_int32_t maxmtu;	/* Upper bound of LinkMTU */
		u_int32_t basereachable; /* BaseReachableTime */
		u_int32_t reachable;	/* Reachable Time */
		u_int32_t retrans;	/* Retrans Timer */
		u_int32_t flags;	/* Flags */
		int recalctm;		/* BaseReacable re-calculation timer */
		u_int8_t chlim;		/* CurHopLimit */
		u_int8_t receivedra;
	} ndi;
};

struct	in6_ndireq {
	char ifname[IFNAMSIZ];
	struct nd_ifinfo ndi;
};

struct	in6_ndifreq {
	char ifname[IFNAMSIZ];
	u_long ifindex;
};

/* Prefix status */
#define NDPRF_ONLINK		0x1
#define NDPRF_DETACHED		0x2

/* protocol constants */
#define MAX_RTR_SOLICITATION_DELAY	1	/*1sec*/
#define RTR_SOLICITATION_INTERVAL	4	/*4sec*/
#define MAX_RTR_SOLICITATIONS		3

#define ND6_INFINITE_LIFETIME		0xffffffff


#endif /* _NETINET6_ND6_H_ */
