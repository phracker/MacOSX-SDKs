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
/*
 *
 * ORIGINS: 82
 *
 * (C) COPYRIGHT Apple Computer, Inc. 1992-1996
 * All Rights Reserved
 *
 */                                                                   

/* Definitions for ATP protocol and streams module, per 
 * AppleTalk Transaction Protocol documentation from
 * `Inside AppleTalk', July 14, 1986.
 */

/*
 *	Copyright (c) 1988, 1989 Apple Computer, Inc. 
 *
 *	The information contained herein is subject to change without
 *	notice and  should not be  construed as a commitment by Apple
 *	Computer, Inc. Apple Computer, Inc. assumes no responsibility
 *	for any errors that may appear.
 *
 *	Confidential and Proprietary to Apple Computer, Inc.
 */

#ifndef _NETAT_ATP_H_
#define _NETAT_ATP_H_
#include <sys/appleapiopts.h>

#ifdef __APPLE_API_OBSOLETE

/* ATP function codes */

#define ATP_CMD_TREQ		0x01	/* TRequest packet  */
#define ATP_CMD_TRESP		0x02	/* TResponse packet */
#define ATP_CMD_TREL		0x03	/* TRelease packet  */

/* Miscellaneous definitions */

#define	ATP_DEF_RETRIES     8	/* Default for maximum retry count */
#define	ATP_DEF_INTERVAL    2	/* Default for retry interval in seconds */

#define ATP_TRESP_MAX       8	/* Maximum number of Tresp pkts */

#define ATP_HDR_SIZE        8  	/* Size of the ATP header */
#define ATP_DATA_SIZE       578  	/* Maximum size of the ATP data area */

/* Consts for asynch support */
#define	ATP_ASYNCH_REQ	1
#define	ATP_ASYNCH_RESP	2

/* Timer values for XO release timers */
#define	ATP_XO_DEF_REL_TIME	0
#define	ATP_XO_30SEC		0
#define	ATP_XO_1MIN		1
#define	ATP_XO_2MIN		2
#define	ATP_XO_4MIN		3
#define	ATP_XO_8MIN		4

typedef struct {
#if BYTE_ORDER == BIG_ENDIAN
        unsigned       cmd : 2,
                       xo : 1,
                       eom : 1,
                       sts : 1,
                       xo_relt : 3;
#endif
#if BYTE_ORDER == LITTLE_ENDIAN
		unsigned		xo_relt : 3,
						sts : 1,
						eom : 1,
						xo : 1,
						cmd : 2;
#endif
        u_char         bitmap;
		ua_short       tid;
        ua_long        user_bytes;
        u_char         data[ATP_DATA_SIZE];
} at_atp_t;

#define ATP_ATP_HDR(c) ((at_atp_t *)(&((at_ddp_t *)(c))->data[0]))

#define TOTAL_ATP_HDR_SIZE    (ATP_HDR_SIZE+DDP_X_HDR_SIZE)
#define ATP_CLEAR_CONTROL(c)  (*(char *)(c) = 0)

/* ATP ioctl interface */

/* Structure for the atp_set_default call */

#define	ATP_INFINITE_RETRIES	0xffffffff	/* means retry forever
						 * in the def_retries field
					 	 */

struct atp_set_default {
	u_int	def_retries;		/* number of retries for a request */
	u_int	def_rate;		/* retry rate (in seconds/100) NB: the
					 * system may not be able to resolve
					 * delays of 100th of a second but will
					 * instead make a 'best effort'
					 */
	struct atpBDS *def_bdsp; /*  BDS structure associated with this req */
	u_int	def_BDSlen;	/* size of BDS structure */
};


/* Return header from requests */

struct atp_result {
	u_short		count;		/* the number of packets */
	u_short		hdr;		/* offset to header in buffer */
	u_short 	offset[8];	/* offset to the Nth packet in the buffer */
	u_short		len[8];		/* length of the Nth packet */
};

struct atpBDS {
	ua_short	bdsBuffSz;
	ua_long		bdsBuffAddr;
	ua_short	bdsDataSz;
	unsigned char	bdsUserData[4];
};


typedef struct {
        u_short        at_atpreq_type;
        at_inet_t      at_atpreq_to;
        u_char         at_atpreq_treq_user_bytes[4];
        u_char         *at_atpreq_treq_data;
        u_short        at_atpreq_treq_length;
        u_char         at_atpreq_treq_bitmap;
        u_char         at_atpreq_xo;
        u_char         at_atpreq_xo_relt;
        u_short        at_atpreq_retry_timeout;
        u_short        at_atpreq_maximum_retries;
        u_char         at_atpreq_tresp_user_bytes[ATP_TRESP_MAX][4];
        u_char         *at_atpreq_tresp_data[ATP_TRESP_MAX];
        u_short        at_atpreq_tresp_lengths[ATP_TRESP_MAX];
        u_long         at_atpreq_debug[4];
        u_short        at_atpreq_tid;
        u_char         at_atpreq_tresp_bitmap;
        u_char         at_atpreq_tresp_eom_seqno;
        u_char         at_atpreq_got_trel;
} at_atpreq;


/* The ATP module ioctl commands */

#define AT_ATP_CANCEL_REQUEST		(('|'<<8)|1)
#define AT_ATP_ISSUE_REQUEST		(('|'<<8)|2) /* ALO */
#define AT_ATP_ISSUE_REQUEST_DEF	(('|'<<8)|3) /* XO */
#define AT_ATP_ISSUE_REQUEST_DEF_NOTE	(('|'<<8)|4) /* XO & nowait -- not needed*/
#define AT_ATP_ISSUE_REQUEST_NOTE	(('|'<<8)|5) /* ALO & nowait */
#define AT_ATP_GET_POLL			(('|'<<8)|6)
#define AT_ATP_RELEASE_RESPONSE		(('|'<<8)|7)
#define AT_ATP_REQUEST_COMPLETE		(('|'<<8)|8)
#define AT_ATP_SEND_FULL_RESPONSE	(('|'<<8)|9) /* not used */
#define AT_ATP_BIND_REQ			(('|'<<8)|10)
#define AT_ATP_GET_CHANID		(('|'<<8)|11)
#define AT_ATP_PEEK			(('|'<<8)|12)
#define AT_ATP_ISSUE_REQUEST_TICKLE 	(('|'<<8)|13) /* ALO & nowait */

/* These macros don't really depend here, but since they're used only by the
 * old ATP and old PAP, they're put here.  Unisoft PAP includes this file.
 */
#define	R16(x)		UAS_VALUE(x)
#define	W16(x,v)	UAS_ASSIGN(x, v)
#define	C16(x,v)	UAS_UAS(x, v)

/*
 * these are the dispatch codes for
 * the new atp_control system call
 */
#define ATP_SENDREQUEST  0
#define ATP_GETRESPONSE  1
#define ATP_SENDRESPONSE 2
#define ATP_GETREQUEST   3

#endif /* __APPLE_API_OBSOLETE */
#endif /* _NETAT_ATP_H_ */
