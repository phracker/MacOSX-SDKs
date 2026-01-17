/*
 * Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
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
 
#ifndef CHUD_UTIL_H
#define CHUD_UTIL_H

#include <sys/types.h> /* pid_t, size_t */

#ifdef __cplusplus
extern "C" {
#endif

#define chudUtimebaseGetUptime		chudTimebaseGetUptime 
#define chudUmarkPID			chudMarkPID
#define chudUisPIDmarked		chudIsPIDmarked
#define chudUmarkCurrentThread		chudMarkCurrentThread
#define chudUisCurrentThreadMarked	chudIsCurrentThreadMarked
#define chudUisPIDprivileged		chudIsPIDprivileged

void	chudTimebaseGetUptime( uint64_t *result );
int	chudMarkPID( pid_t pid, int markflag );
int	chudIsPIDmarked( pid_t a_pid, int *marked_thread_count );
int	chudMarkCurrentThread( int markflag );
int	chudIsCurrentThreadMarked( int *marked );
int	chudIsPIDprivileged( pid_t a_pid, int *priv_thread_count );

void *	chudMapBlizBuffer( uint64_t *avail );

int	chudEnableProcessorCacheLevel(int level, int enable);
int	chudFlushProcessorCaches(void);
int	chudSetNumProcessors(int count);
int	chudEnableProcessorPowerSaving(int napEnable);

void	chudStartStopAmber(void);

#ifdef __cplusplus
}
#endif

#endif /* CHUD_UTIL_H */
