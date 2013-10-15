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
/*	$NetBSD: msg.h,v 1.4 1994/06/29 06:44:43 cgd Exp $	*/

/*
 * SVID compatible msg.h file
 *
 * Author:  Daniel Boulet
 *
 * Copyright 1993 Daniel Boulet and RTMX Inc.
 *
 * This system call was implemented by Daniel Boulet under contract from RTMX.
 *
 * Redistribution and use in source forms, with and without modification,
 * are permitted provided that this entire comment appears intact.
 *
 * Redistribution in binary form may occur without any restrictions.
 * Obviously, it would be nice if you gave credit where credit is due
 * but requiring it would be too onerous.
 *
 * This software is provided ``AS IS'' without any warranties of any kind.
 */

#ifndef _SYS_MSG_H_
#define _SYS_MSG_H_

#include <sys/appleapiopts.h>

#include <sys/_types.h>
#include <sys/cdefs.h>

/*
 * [XSI] All of the symbols from <sys/ipc.h> SHALL be defined when this
 * header is included
 */
#include <sys/ipc.h>


/*
 * [XSI] The pid_t, time_t, key_t, size_t, and ssize_t types shall be
 * defined as described in <sys/types.h>.
 *
 * NOTE:	The definition of the key_t type is implicit from the
 *		inclusion of <sys/ipc.h>
 */
#ifndef _PID_T
typedef __darwin_pid_t		pid_t;
#define _PID_T
#endif

#ifndef	_TIME_T
#define	_TIME_T
typedef	__darwin_time_t		time_t;
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef __darwin_size_t		size_t;
#endif

#ifndef	_SSIZE_T
#define	_SSIZE_T
typedef	__darwin_ssize_t	ssize_t;
#endif

/* [XSI] Used for the number of messages in the message queue */
typedef unsigned long		msgqnum_t;

/* [XSI] Used for the number of bytes allowed in a message queue */
typedef unsigned long		msglen_t;


/*
 * Possible values for the fifth parameter to msgrcv(), in addition to the
 * IPC_NOWAIT flag, which is permitted.
 */
#define MSG_NOERROR	010000		/* [XSI] No error if big message */


/*
 * Technically, we should force all code references to the new structure
 * definition, not in just the standards conformance case, and leave the
 * legacy interface there for binary compatibility only.  Currently, we
 * are only forcing this for programs requesting standards conformance.
 */
#if defined(__POSIX_C_SOURCE) || defined(kernel) || defined(__LP64__)
/*
 * Structure used internally.
 * 
 * Structure whose address is passed as the third parameter to msgctl()
 * when the second parameter is IPC_SET or IPC_STAT.  In the case of the
 * IPC_SET command, only the msg_perm.{uid|gid|perm} and msg_qbytes are
 * honored.  In the case of IPC_STAT, only the fields indicated as [XSI]
 * mandated fields are guaranteed to meaningful: DO NOT depend on the
 * contents of the other fields.
 *
 * NOTES:	Reserved fields are not preserved across IPC_SET/IPC_STAT.
 */
struct __msqid_ds_new {
	struct __ipc_perm_new	msg_perm; /* [XSI] msg queue permissions */
	__int32_t	msg_first;	/* RESERVED: kernel use only */
	__int32_t	msg_last;	/* RESERVED: kernel use only */
	msglen_t	msg_cbytes;	/* # of bytes on the queue */
	msgqnum_t	msg_qnum;	/* [XSI] number of msgs on the queue */
	msglen_t	msg_qbytes;	/* [XSI] max bytes on the queue */
	pid_t		msg_lspid;	/* [XSI] pid of last msgsnd() */
	pid_t		msg_lrpid;	/* [XSI] pid of last msgrcv() */
	time_t		msg_stime;	/* [XSI] time of last msgsnd() */
	__int32_t	msg_pad1;	/* RESERVED: DO NOT USE */
	time_t		msg_rtime;	/* [XSI] time of last msgrcv() */
	__int32_t	msg_pad2;	/* RESERVED: DO NOT USE */
	time_t		msg_ctime;	/* [XSI] time of last msgctl() */
	__int32_t	msg_pad3;	/* RESERVED: DO NOT USE */
	__int32_t	msg_pad4[4];	/* RESERVED: DO NOT USE */
};
#define	msqid_ds	__msqid_ds_new
#else	/* !_POSIX_C_SOURCE */
#define	msqid_ds	__msqid_ds_old
#endif	/* !_POSIX_C_SOURCE */

#if !defined(__POSIX_C_SOURCE) && !defined(__LP64__)
struct __msqid_ds_old {
	struct __ipc_perm_old	msg_perm; /* [XSI] msg queue permissions */
	__int32_t	msg_first;	/* RESERVED: kernel use only */
	__int32_t	msg_last;	/* RESERVED: kernel use only */
	msglen_t	msg_cbytes;	/* # of bytes on the queue */
	msgqnum_t	msg_qnum;	/* [XSI] number of msgs on the queue */
	msglen_t	msg_qbytes;	/* [XSI] max bytes on the queue */
	pid_t		msg_lspid;	/* [XSI] pid of last msgsnd() */
	pid_t		msg_lrpid;	/* [XSI] pid of last msgrcv() */
	time_t		msg_stime;	/* [XSI] time of last msgsnd() */
	__int32_t	msg_pad1;	/* RESERVED: DO NOT USE */
	time_t		msg_rtime;	/* [XSI] time of last msgrcv() */
	__int32_t	msg_pad2;	/* RESERVED: DO NOT USE */
	time_t		msg_ctime;	/* [XSI] time of last msgctl() */
	__int32_t	msg_pad3;	/* RESERVED: DO NOT USE */
	__int32_t	msg_pad4[4];	/* RESERVED: DO NOT USE */
};
#endif	/* !_POSIX_C_SOURCE */



#ifndef _POSIX_C_SOURCE
#ifdef __APPLE_API_UNSTABLE
/* XXX kernel only; protect with macro later */

struct msg {
	struct msg	*msg_next;	/* next msg in the chain */
	long		msg_type;	/* type of this message */
    					/* >0 -> type of this message */
    					/* 0 -> free header */
	unsigned short	msg_ts;		/* size of this message */
	short		msg_spot;	/* location of msg start in buffer */
};

/*
 * Example structure describing a message whose address is to be passed as
 * the second argument to the functions msgrcv() and msgsnd().  The only
 * actual hard requirement is that the first field be of type long, and
 * contain the message type.  The user is encouraged to define their own
 * application specific structure; this definition is included solely for
 * backward compatability with existing source code.
 */
struct mymsg {
	long	mtype;		/* message type (+ve integer) */
	char	mtext[1];	/* message body */
};

/*
 * Based on the configuration parameters described in an SVR2 (yes, two)
 * config(1m) man page.
 *
 * Each message is broken up and stored in segments that are msgssz bytes
 * long.  For efficiency reasons, this should be a power of two.  Also,
 * it doesn't make sense if it is less than 8 or greater than about 256.
 * Consequently, msginit in kern/sysv_msg.c checks that msgssz is a power of
 * two between 8 and 1024 inclusive (and panic's if it isn't).
 */
struct msginfo {
	int	msgmax,		/* max chars in a message */
		msgmni,		/* max message queue identifiers */
		msgmnb,		/* max chars in a queue */
		msgtql,		/* max messages in system */
		msgssz,		/* size of a message segment (see notes above) */
		msgseg;		/* number of message segments */
};
#endif	/* __APPLE_API_UNSTABLE */
#endif	/* !_POSIX_C_SOURCE */


__BEGIN_DECLS
#ifndef _POSIX_C_SOURCE
int msgsys(int, ...);
#endif	/* !_POSIX_C_SOURCE */
int msgctl(int, int, struct msqid_ds *) __DARWIN_ALIAS(msgctl);
int msgget(key_t, int);
ssize_t msgrcv(int, void *, size_t, long, int);
int msgsnd(int, const void *, size_t, int);
__END_DECLS


#endif /* !_SYS_MSG_H_ */
