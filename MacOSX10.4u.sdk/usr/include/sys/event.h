/*
 * Copyright (c) 2003-2005 Apple Computer, Inc. All rights reserved.
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
/*-
 * Copyright (c) 1999,2000,2001 Jonathan Lemon <jlemon@FreeBSD.org>
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
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	$FreeBSD: src/sys/sys/event.h,v 1.5.2.5 2001/12/14 19:21:22 jlemon Exp $
 */

#ifndef _SYS_EVENT_H_
#define _SYS_EVENT_H_

#include <machine/types.h>
#include <sys/cdefs.h>
#include <stdint.h>

#define EVFILT_READ		(-1)
#define EVFILT_WRITE		(-2)
#define EVFILT_AIO		(-3)	/* attached to aio requests */
#define EVFILT_VNODE		(-4)	/* attached to vnodes */
#define EVFILT_PROC		(-5)	/* attached to struct proc */
#define EVFILT_SIGNAL		(-6)	/* attached to struct proc */
#define EVFILT_TIMER		(-7)	/* timers */
#define EVFILT_MACHPORT		(-8)	/* Mach ports */
#define EVFILT_FS		(-9)	/* Filesystem events */

#define EVFILT_SYSCOUNT		9
#define EVFILT_THREADMARKER	EVFILT_SYSCOUNT /* Internal use only */

#pragma pack(4)

struct kevent {
	uintptr_t	ident;		/* identifier for this event */
	short		filter;		/* filter for event */
	unsigned short	flags;		/* general flags */
	unsigned int	fflags;		/* filter-specific flags */
	intptr_t	data;		/* filter-specific data */
	void		*udata;		/* opaque user data identifier */
};


#pragma pack()

#define EV_SET(kevp, a, b, c, d, e, f) do {	\
	struct kevent *__kevp__ = (kevp);	\
	__kevp__->ident = (a);			\
	__kevp__->filter = (b);			\
	__kevp__->flags = (c);			\
	__kevp__->fflags = (d);			\
	__kevp__->data = (e);			\
	__kevp__->udata = (f);			\
} while(0)

/* actions */
#define EV_ADD		0x0001		/* add event to kq (implies enable) */
#define EV_DELETE	0x0002		/* delete event from kq */
#define EV_ENABLE	0x0004		/* enable event */
#define EV_DISABLE	0x0008		/* disable event (not reported) */

/* flags */
#define EV_ONESHOT	0x0010		/* only report one occurrence */
#define EV_CLEAR	0x0020		/* clear event state after reporting */

#define EV_SYSFLAGS	0xF000		/* reserved by system */
#define EV_FLAG0	0x1000		/* filter-specific flag */
#define EV_FLAG1	0x2000		/* filter-specific flag */

/* returned values */
#define EV_EOF		0x8000		/* EOF detected */
#define EV_ERROR	0x4000		/* error, data contains errno */

/*
 * Filter specific flags for EVFILT_READ
 *
 * The default behavior for EVFILT_READ is to make the "read" determination
 * relative to the current file descriptor read pointer. The EV_POLL
 * flag indicates the determination should be made via poll(2) semantics
 * (which always returns true for regular files - regardless of the amount
 * of unread data in the file).
 *
 * On input, EV_OOBAND specifies that only OOB data should be looked for.
 * The returned data count is the number of bytes beyond the current OOB marker.
 *
 * On output, EV_OOBAND indicates that OOB data is present
 * If it was not specified as an input parameter, then the data count is the
 * number of bytes before the current OOB marker. If at the marker, the
 * data count indicates the number of bytes available after it.  In either
 * case, it's the amount of data one could expect to receive next.
 */
#define EV_POLL	EV_FLAG0
#define EV_OOBAND	EV_FLAG1

/*
 * data/hint fflags for EVFILT_{READ|WRITE}, shared with userspace
 *
 * The default behavior for EVFILT_READ is to make the determination
 * realtive to the current file descriptor read pointer.
 */
#define NOTE_LOWAT	0x00000001		/* low water mark */
/*
 * data/hint fflags for EVFILT_VNODE, shared with userspace
 */
#define	NOTE_DELETE	0x00000001		/* vnode was removed */
#define	NOTE_WRITE	0x00000002		/* data contents changed */
#define	NOTE_EXTEND	0x00000004		/* size increased */
#define	NOTE_ATTRIB	0x00000008		/* attributes changed */
#define	NOTE_LINK	0x00000010		/* link count changed */
#define	NOTE_RENAME	0x00000020		/* vnode was renamed */
#define	NOTE_REVOKE	0x00000040		/* vnode access was revoked */

/*
 * data/hint fflags for EVFILT_PROC, shared with userspace
 */
#define	NOTE_EXIT	0x80000000		/* process exited */
#define	NOTE_FORK	0x40000000		/* process forked */
#define	NOTE_EXEC	0x20000000		/* process exec'd */
#define	NOTE_PCTRLMASK	0xf0000000		/* mask for hint bits */
#define	NOTE_PDATAMASK	0x000fffff		/* mask for pid */

/*
 * data/hint fflags for EVFILT_TIMER, shared with userspace.
 * The default is a (repeating) interval timer with the data
 * specifying the timeout interval in milliseconds.
 *
 * All timeouts are implicitly EV_CLEAR events.
 */
#define NOTE_SECONDS	0x00000001		/* data is seconds         */
#define NOTE_USECONDS	0x00000002		/* data is microseconds    */
#define NOTE_NSECONDS	0x00000004		/* data is nanoseconds     */
#define NOTE_ABSOLUTE	0x00000008		/* absolute timeout        */
						/* ... implicit EV_ONESHOT */
 
/* additional flags for EVFILT_PROC */
#define	NOTE_TRACK	0x00000001		/* follow across forks */
#define	NOTE_TRACKERR	0x00000002		/* could not track child */
#define	NOTE_CHILD	0x00000004		/* am a child process */



/* Temporay solution for BootX to use inode.h till kqueue moves to vfs layer */
#include <sys/queue.h> 
struct knote;
SLIST_HEAD(klist, knote);



struct timespec;

__BEGIN_DECLS
int     kqueue(void);
int     kevent(int kq, const struct kevent *changelist, int nchanges,
		    struct kevent *eventlist, int nevents,
		    const struct timespec *timeout);
__END_DECLS





#endif /* !_SYS_EVENT_H_ */
