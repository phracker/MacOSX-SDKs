/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
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
#ifndef _NETAT_AT_AARP_H_
#define _NETAT_AT_AARP_H_
#include <sys/appleapiopts.h>

#ifdef __APPLE_API_OBSOLETE

/*
 *	Copyright (c) 1988, 1989 Apple Computer, Inc. 
 */

/* "@(#)at_aarp.h: 2.0, 1.6; 10/4/93; Copyright 1988-89, Apple Computer, Inc." */

/* This is a header file for AARP. 
 *
 * Author: R. C. Venkatraman
 * Date  : 3/2/88
 *
 */

/* AARP packet */

typedef struct {
	u_short			hardware_type;
	u_short			stack_type;	/* indicates appletalk or xns*/
	u_char			hw_addr_len; 	/* len of hardware addr, e.g
						 * ethernet addr len, in bytes
						 */
	u_char 			stack_addr_len;	/* protocol stack addr len,
						 * e.g., appletalk addr len
						 * in bytes
						 */
	u_short			aarp_cmd;
	struct etalk_addr	src_addr;
	struct atalk_addr	src_at_addr;
	struct etalk_addr	dest_addr;
	struct atalk_addr	dest_at_addr;	/* desired or dest. at addr */
} aarp_pkt_t;


/* Constants currently defined in AARP */

#define AARP_AT_TYPE			0x80F3	/* indicates aarp packet */
#define AARP_ETHER_HW_TYPE		0x1
#define AARP_AT_PROTO			0x809B	/* indicates stack type */
#define AARP_ETHER_ADDR_LEN		6	/* in bytes */
#define AARP_AT_ADDR_LEN		4 	/* in bytes */

/* AARP cmd definitions */

#define AARP_REQ_CMD			0x1	/* address lookup request */
#define AARP_RESP_CMD			0x2	/* address match response */
#define AARP_PROBE_CMD			0x3	/* new kid probing...     */

/* AARP timer and retry counts */

#define	AARP_MAX_PROBE_RETRIES		20
#define AARP_PROBE_TIMER_INT		HZ/30	/* HZ defines in param.h */
#define AARP_MAX_REQ_RETRIES		10
#define AARP_REQ_TIMER_INT              HZ/30
#define	AARP_MAX_NODES_TRIED		200	/* max no. of addresses tried */
						/* on the same net before     */
						/* giving up on the net#      */
#define	AARP_MAX_NETS_TRIED		10	/* max no. of net nos tried   */
						/* before giving up on startup*/

/* Probe states */

#define PROBE_IDLE			0x1	/* There is no node addr */
#define PROBE_TENTATIVE			0x2	/* probing */
#define PROBE_DONE			0x3	/* an appletalk addr has been */
						/* assigned for the given node*/
/* Errors returned by AARP routines */
#define AARP_ERR_NOT_OURS		1	/* not our appletalk address */


#endif /* __APPLE_API_OBSOLETE */
#endif /* _NETAT_AT_AARP_H_ */
