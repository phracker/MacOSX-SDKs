/*
 * Copyright (c) 2000-2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * Copyright 1996 1995 by Open Software Foundation, Inc. 1997 1996 1995 1994 1993 1992 1991  
 *              All Rights Reserved 
 *  
 * Permission to use, copy, modify, and distribute this software and 
 * its documentation for any purpose and without fee is hereby granted, 
 * provided that the above copyright notice appears in all copies and 
 * that both the copyright notice and this permission notice appear in 
 * supporting documentation. 
 *  
 * OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE 
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE. 
 *  
 * IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR 
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM 
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT, 
 * NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION 
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. 
 * 
 */
/*
 * MkLinux
 */

/*
 * POSIX Threads - IEEE 1003.1c
 */

#ifndef _POSIX_PTHREAD_H
#define _POSIX_PTHREAD_H

#ifndef __POSIX_LIB__
#include <pthread_impl.h>
#endif
#include <errno.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>

#ifndef _POSIX_C_SOURCE
#include <mach/mach_types.h>
#endif /* ! _POSIX_C_SOURCE */

/*
 * These symbols indicate which [optional] features are available
 * They can be tested at compile time via '#ifdef XXX'
 * The way to check for pthreads is like so:
 
 * #include <unistd.h>
 * #ifdef _POSIX_THREADS
 * #include <pthread.h>
 * #endif

 */

/* These will be moved to unistd.h */


/* These two should be defined also */
#undef  _POSIX_THREAD_PROCESS_SHARED
#undef  _POSIX_THREAD_SAFE_FUNCTIONS

/*
 * Note: These data structures are meant to be opaque.  Only enough
 * structure is exposed to support initializers.
 * All of the typedefs will be moved to <sys/types.h>
 */

#include <sys/cdefs.h>

__BEGIN_DECLS
/*
 * Threads
 */


/*
 * Cancel cleanup handler management.  Note, since these are implemented as macros,
 * they *MUST* occur in matched pairs!
 */

#define pthread_cleanup_push(func, val) \
   { \
	     struct _pthread_handler_rec __handler; \
	     pthread_t __self = pthread_self(); \
	     __handler.routine = func; \
	     __handler.arg = val; \
	     __handler.next = __self->cleanup_stack; \
	     __self->cleanup_stack = &__handler;

#define pthread_cleanup_pop(execute) \
	     /* Note: 'handler' must be in this same lexical context! */ \
	     __self->cleanup_stack = __handler.next; \
	     if (execute) (__handler.routine)(__handler.arg); \
   }
	
/*
 * Thread attributes
 */

#define PTHREAD_CREATE_JOINABLE      1
#define PTHREAD_CREATE_DETACHED      2

#define PTHREAD_INHERIT_SCHED        1
#define PTHREAD_EXPLICIT_SCHED       2

#define PTHREAD_CANCEL_ENABLE        0x01  /* Cancel takes place at next cancellation point */
#define PTHREAD_CANCEL_DISABLE       0x00  /* Cancel postponed */
#define PTHREAD_CANCEL_DEFERRED      0x02  /* Cancel waits until cancellation point */
#define PTHREAD_CANCEL_ASYNCHRONOUS  0x00  /* Cancel occurs immediately */

/* We only support PTHREAD_SCOPE_SYSTEM */
#define PTHREAD_SCOPE_SYSTEM         1
#define PTHREAD_SCOPE_PROCESS        2

/* We only support PTHREAD_PROCESS_PRIVATE */
#define PTHREAD_PROCESS_SHARED         1
#define PTHREAD_PROCESS_PRIVATE        2

/* Who defines this? */

#if !defined(ENOTSUP)
#define ENOTSUP 89
#endif
/*
 * Mutex protocol attributes
 */
#define PTHREAD_PRIO_NONE            0
#define PTHREAD_PRIO_INHERIT         1
#define PTHREAD_PRIO_PROTECT         2

/*
 * Mutex type attributes
 */
#define PTHREAD_MUTEX_NORMAL		0
#define PTHREAD_MUTEX_ERRORCHECK	1 
#define PTHREAD_MUTEX_RECURSIVE		2
#define PTHREAD_MUTEX_DEFAULT		PTHREAD_MUTEX_NORMAL
/*
 * Mutex variables
 */

#define PTHREAD_MUTEX_INITIALIZER {_PTHREAD_MUTEX_SIG_init, {0}}

/*
 * Condition variable attributes
 */

/*
 * Condition variables
 */

#define PTHREAD_COND_INITIALIZER {_PTHREAD_COND_SIG_init, {0}}

/*
 * Initialization control (once) variables
 */

#define PTHREAD_ONCE_INIT {_PTHREAD_ONCE_SIG_init, {0}}

/*
 * Thread Specific Data - keys
 */

#include <sys/time.h>

/*
 * Prototypes for all PTHREAD interfaces
 */
int       pthread_attr_destroy(pthread_attr_t *attr);
int       pthread_attr_getdetachstate(const pthread_attr_t *attr,
				      int *detachstate);
int       pthread_attr_getinheritsched(const pthread_attr_t *attr, 
				       int *inheritsched);
int       pthread_attr_getschedparam(const pthread_attr_t *attr, 
                                     struct sched_param *param);
int       pthread_attr_getschedpolicy(const pthread_attr_t *attr, 
				      int *policy);
int       pthread_attr_getstackaddr(const pthread_attr_t *attr,
                                      void **stackaddr);
int       pthread_attr_getstacksize(const pthread_attr_t *attr,
                                      size_t *stacksize);
int       pthread_attr_getstack(const pthread_attr_t *attr,
                                      void **stackaddr, size_t *stacksize);
int       pthread_attr_getguardsize(const pthread_attr_t *attr,
                                      size_t *guardsize);
int       pthread_attr_init(pthread_attr_t *attr);
int       pthread_attr_setdetachstate(pthread_attr_t *attr, 
				      int detachstate);
int       pthread_attr_setinheritsched(pthread_attr_t *attr, 
				       int inheritsched);
int       pthread_attr_setschedparam(pthread_attr_t *attr, 
                                     const struct sched_param *param);
int       pthread_attr_setschedpolicy(pthread_attr_t *attr, 
				      int policy);
int       pthread_attr_setstackaddr(pthread_attr_t *attr,
                                      void *stackaddr);
int       pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
int       pthread_attr_setguardsize(pthread_attr_t *attr, size_t guardsize);
int       pthread_attr_setstack(pthread_attr_t *attr,
                                      void *stackaddr, size_t stacksize);
int       pthread_cancel(pthread_t thread);
int       pthread_setcancelstate(int state, int *oldstate);
int       pthread_setcanceltype(int type, int *oldtype);
void      pthread_testcancel(void);
int       pthread_cond_broadcast(pthread_cond_t *cond);
int       pthread_cond_destroy(pthread_cond_t *cond);
int       pthread_cond_init(pthread_cond_t *cond,
                            const pthread_condattr_t *attr);
int       pthread_cond_signal(pthread_cond_t *cond);
int       pthread_cond_wait(pthread_cond_t *cond, 
			    pthread_mutex_t *mutex);
int       pthread_cond_timedwait(pthread_cond_t *cond, 
				 pthread_mutex_t *mutex,
				 const struct timespec *abstime);
int       pthread_condattr_init(pthread_condattr_t *attr);
int       pthread_condattr_destroy(pthread_condattr_t *attr);
int       pthread_condattr_getpshared(const pthread_condattr_t *attr, 
			int *pshared);
int       pthread_condattr_setpshared(pthread_condattr_t *attr, 
			int pshared);
int       pthread_create(pthread_t *thread, 
                         const pthread_attr_t *attr,
                         void *(*start_routine)(void *), 
                         void *arg);
int       pthread_detach(pthread_t thread);
int       pthread_equal(pthread_t t1, 
			pthread_t t2);
void      pthread_exit(void *value_ptr) __dead2;
int       pthread_kill(pthread_t, int);
int       pthread_sigmask(int, const sigset_t *, sigset_t *);
int       pthread_getschedparam(pthread_t thread, 
				int *policy,
                                struct sched_param *param);
int       pthread_join(pthread_t thread, 
		       void **value_ptr);
int       pthread_mutex_destroy(pthread_mutex_t *mutex);
int       pthread_mutex_getprioceiling(const pthread_mutex_t *mutex, 
                                       int *prioceiling);
int       pthread_mutex_init(pthread_mutex_t *mutex, 
			     const pthread_mutexattr_t *attr);
int       pthread_mutex_lock(pthread_mutex_t *mutex);
int       pthread_mutex_setprioceiling(pthread_mutex_t *mutex, 
                                       int prioceiling, 
                                       int *old_prioceiling);
int       pthread_mutex_trylock(pthread_mutex_t *mutex);
int       pthread_mutex_unlock(pthread_mutex_t *mutex);
int       pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
int       pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *attr, 
                                           int *prioceiling);
int       pthread_mutexattr_getprotocol(const pthread_mutexattr_t *attr, 
                                        int *protocol);
int       pthread_mutexattr_getpshared(const pthread_mutexattr_t *attr, 
                                        int *pshared);
int       pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, 
                                        int *type);
int       pthread_mutexattr_init(pthread_mutexattr_t *attr);
int       pthread_mutexattr_setprioceiling(pthread_mutexattr_t *attr, 
                                           int prioceiling);
int       pthread_mutexattr_setprotocol(pthread_mutexattr_t *attr, 
                                        int protocol);
int       pthread_mutexattr_settype(pthread_mutexattr_t *attr, 
                                        int type);
int       pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, 
                                        int pshared);
int       pthread_once(pthread_once_t *once_control, 
		       void (*init_routine)(void));
pthread_t pthread_self(void);
int       pthread_setschedparam(pthread_t thread, 
				int policy,
                                const struct sched_param *param);
int       pthread_key_create(pthread_key_t *key,
			     void (*destructor)(void *));
int       pthread_key_delete(pthread_key_t key);
int       pthread_setspecific(pthread_key_t key,
			      const void *value);
void     *pthread_getspecific(pthread_key_t key);
int       pthread_attr_getscope(pthread_attr_t *, int *);
int       pthread_attr_setscope(pthread_attr_t *, int);
int       pthread_getconcurrency(void);
int       pthread_setconcurrency(int);
int       pthread_rwlock_destroy(pthread_rwlock_t * rwlock);
int       pthread_rwlock_init(pthread_rwlock_t * rwlock, 
			     const pthread_rwlockattr_t *attr);
int       pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int       pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
int       pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int       pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
int       pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
int       pthread_rwlockattr_init(pthread_rwlockattr_t *attr);
int       pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr);
int       pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *attr, 
			int *pshared);
int       pthread_rwlockattr_setpshared(pthread_rwlockattr_t *attr, 
			int pshared);

#ifndef _POSIX_C_SOURCE
/* returns non-zero if pthread_create or cthread_fork have been called */
int		pthread_is_threaded_np(void);

/* returns non-zero if the current thread is the main thread */
int		pthread_main_np(void);

/* return the mach thread bound to the pthread */
mach_port_t 	pthread_mach_thread_np(pthread_t);
size_t	 	pthread_get_stacksize_np(pthread_t);
void *		pthread_get_stackaddr_np(pthread_t);

/* Like pthread_cond_signal(), but only wake up the specified pthread */
int		pthread_cond_signal_thread_np(pthread_cond_t *, pthread_t);

/* Like pthread_cond_timedwait, but use a relative timeout */
int		pthread_cond_timedwait_relative_np(pthread_cond_t *cond, 
				 pthread_mutex_t *mutex,
				 const struct timespec *reltime);

/* Like pthread_create(), but leaves the thread suspended */
int       pthread_create_suspended_np(pthread_t *thread, 
                         const pthread_attr_t *attr,
                         void *(*start_routine)(void *), 
                         void *arg);
void pthread_yield_np(void);
#endif /* ! _POSIX_C_SOURCE */
__END_DECLS
#endif /* _POSIX_PTHREAD_H */
