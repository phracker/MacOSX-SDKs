/*
 * Copyright (c) 2002-2004 Apple Computer, Inc. All rights reserved.
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
/*!
 @header CHUD Tools API Utility functions: 
 @discussion In the CHUD Tools API, the utility functions are a low-level "catch all."
 the functions in this module deal primarily with process marking, system memory 
 configuration, processor cache settings, and the Amber instruction tracing toggle routine.
 
*/
#ifdef __cplusplus
extern "C" {
#endif

#define chudUmarkPID			chudMarkPID
#define chudUisPIDmarked		chudIsPIDmarked
#define chudUmarkCurrentThread		chudMarkCurrentThread
#define chudUisCurrentThreadMarked	chudIsCurrentThreadMarked
#define chudUisPIDprivileged		chudIsPIDprivileged

/*!
 @function chudMarkPID
 @discussion Walk all the thread in a given Process ID (pid) and set the mark bit in each state struct
 @param pid Target pid
 @param markflag Value to set mark bit to
 @result chudSuccess , chudCheckPIDFailure , chudCheckTaskFailure , chudCheckThreadFailure
 */
int	chudMarkPID( pid_t pid, int markflag );
/*!
 @function chudIsPIDmarked
 @discussion Walk all the threads in a given Process ID (pid) and check the mark bit in each state struct. Every thread that exists in the process at the time of marking, will have its mark bit flipped. But if the process creates new threads they will not inherit the mark bit state. They must be marked explicitly...or the process must be marked again.
 @param pid Target pid
 @param *marked_thread_count Storage for marked thread count
 @result chudSuccess , chudCheckPidFailure , chudCheckTaskFailure , chudCheckThreadFailure
 */
int	chudIsPIDmarked( pid_t a_pid, int *marked_thread_count );
/*!
 @function chudMarkCurrentThread
 @discussion Set the mark bit for the current thread. The only entity that can set the mark bit for a thread is the thread itself.
 @param markflag Value to set the mark bit to
 @result chudSuccess
 */
int	chudMarkCurrentThread( int markflag );
/*!
 @function chudIsCurrentThreadmarked
 @discussion Check the mark bit for the current thread
 @param marked Storage for mark bit contents
 @result chudSuccess
 */
int	chudIsCurrentThreadMarked( int *marked );
/*!
 @function chudIsPIDprivileged
 @discussion Walk all the thread in a given Process ID (pid) and check the PR bit in each state struct
 @param a_pid Target pid
 @param *priv_thread_count Storage for privileged thread count
 @result TRUE || FALSE
*/
int	chudIsPIDprivileged( pid_t a_pid, int *priv_thread_count );

/*!
 @function chudMapBlizBuffer
 @discussion Maps physical memory that has been hidden from the system with the maxmem=#MB boot arg into the calling task.  BlizBuffer memory is wired and marked cache inhibited so accessing it will not perturb system caches nor will pagefaults ever be generated.  Note that this memory is a shared resource, so multiple tasks mapping in the BlizBuffer will be accessing the same memory.
 
 To set the amount of hidden memory in the system use the following command from the Terminal:
   sudo nvram boot-args="maxmem=N"
 where N is the number of MB the system will be aware of.  Any remaining phsyical RAM will be available as the BlizBuffer.
 @param *avail Storage for number of bytes available
 @result pointer to buffer or NULL upon failure
 */
void *	chudMapBlizBuffer( uint64_t *avail );

/*!
 @function chudEnableProcessorCacheLevel
 @discussion Enable or disable an available level of processor cache.
 NOTE: L1 caches can never be disabled.
 @param level Cache level to be modified
 @param enable Set to 1 to enable, 0 to disable
 @result chudSuccess , chudInvalidIndex , chudIOKitFailure , chudFailure
 */
int	chudEnableProcessorCacheLevel(int level, int enable);
/*!
 @function chudFlushProcessorCaches
 @discussion Flushes the caches on all processors
 @param void
 @result chudSuccess , chudFailure
 */
int	chudFlushProcessorCaches(void);
/*!
 @function chudSetNumProcessors
 @discussion Set the number of processors available to the system. Use this routine in conjunction with chudProcessorCount, and chudPhysicalProcessorCount found in the chudInfo.h section.
 @param count Number of processors (must be <= number of physical processors)
 @result chudSuccess , chudInvalidIndex , chudIOKitFailure
 */
int	chudSetNumProcessors(int count);
/*!
 @function chudEnableProcessorPowerSaving
 @discussion Enable or diable power saving features of the processor
 @param napEnable Enable or disable napping
 @param dozeEnable Enable or dozing
 @result chudSuccess , chudIOKitFailure , chudFailure
 */
int	chudEnableProcessorPowerSaving(int napEnable);

/*!
 @function chudStartStopAmber
 @discussion Toggle amber tracing when used with the -i option
 @param void
 @result void
 */
void	chudStartStopAmber(void);

#ifdef __cplusplus
}
#endif

#endif /* CHUD_UTIL_H */
