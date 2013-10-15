/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
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
 *	Copyright (c) 1996 Apple Computer, Inc. 
 *
 *		Created April 23, 1996, by Justin C. Walker
 *
 *	File: aurp.h
 */

#ifdef AURP_SUPPORT

#ifndef _NETAT_AURP_H_
#define	_NETAT_AURP_H_
#include <sys/appleapiopts.h>

#ifdef __APPLE_API_OBSOLETE

/*
 * AURP device ioctl (I_STR) 'subcommands'
 */
#define AUC_CFGTNL	0	/* Configure Tunnels */
#define AUC_SHTDOWN	1	/* Shutdown AURP */
#define AUC_EXPNET	2	/* Configure exported networks */
#define AUC_HIDENET	3	/* Configure hidden netowrks */
#define AUC_UDPPORT	4	/* UPD Port number */
#define AUC_NETLIST	5	/* List of remote endpoints */
#define AUC_TIMER	6	/* Configured update interval timer */
#define AUC_ADDNET      7       /* Add remote endpoints */
#define AUC_ACCEPTALL   8       /* Accept all nets */
#define AUC_MAX         9       /* Maximun numbers of access nets */

/* Default AURP-over-UDP port */
#define AURP_SOCKNUM      387
#define AURP_MAXNETACCESS 64

#endif /* __APPLE_API_OBSOLETE */
#endif /* _NETAT_AURP_H_ */

#endif  /* AURP_SUPPORT */
