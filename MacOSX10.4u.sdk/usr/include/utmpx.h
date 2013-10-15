/*	$NetBSD: utmpx.h,v 1.11 2003/08/26 16:48:32 wiz Exp $	 */

/*-
 * Copyright (c) 2002 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Christos Zoulas.
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
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef	_UTMPX_H_
#define	_UTMPX_H_

#include <_types.h>
#include <sys/time.h>

#ifndef _PID_T
#define _PID_T
typedef __darwin_pid_t     pid_t;
#endif

#define	_PATH_UTMPX		"/var/run/utmpx"
#define	_PATH_UTMP_UPDATE	"/usr/libexec/utmp_update"

#ifndef _POSIX_C_SOURCE
#define	UTMPX_FILE	_PATH_UTMPX
#endif /* _POSIX_C_SOURCE */

#define _UTX_USERSIZE	32
#define _UTX_LINESIZE	32
#define	_UTX_IDSIZE	4
#define _UTX_HOSTSIZE	256

#define EMPTY		0
#define RUN_LVL		1
#define BOOT_TIME	2
#define OLD_TIME	3
#define NEW_TIME	4
#define INIT_PROCESS	5
#define LOGIN_PROCESS	6
#define USER_PROCESS	7
#define DEAD_PROCESS	8
#define ACCOUNTING	9
#define SIGNATURE	10

/*
 * The following structure describes the fields of the utmpx entries
 * stored in _PATH_UTMPX. This is not the format the
 * entries are stored in the files, and application should only access
 * entries using routines described in getutxent(3).
 */

struct utmpx {
	char ut_user[_UTX_USERSIZE];	/* login name */
	char ut_id[_UTX_IDSIZE];	/* id */
	char ut_line[_UTX_LINESIZE];	/* tty name */
	pid_t ut_pid;			/* process id creating the entry */
	short ut_type;			/* type of this entry */
	struct timeval ut_tv;		/* time entry was created */
	char ut_host[_UTX_HOSTSIZE];	/* host name */
	__uint32_t ut_pad[16];		/* reserved for future use */
};

__BEGIN_DECLS

void setutxent(void);
void endutxent(void);
struct utmpx *getutxent(void);
struct utmpx *getutxid(const struct utmpx *);
struct utmpx *getutxline(const struct utmpx *);
struct utmpx *pututxline(const struct utmpx *);

__END_DECLS

#endif /* !_UTMPX_H_ */
