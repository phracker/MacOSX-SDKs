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

#define PTHREAD_MUTEX_INITIALIZER {_PTHREAD_MUTEX_SIG_init, {}}

/*
 * Condition variable attributes
 */

/*
 * Condition variables
 */

#define PTHREAD_COND_INITIALIZER {_PTHREAD_COND_SIG_init, {}}

/*
 * Initialization control (once) variables
 */

#define PTHREAD_ONCE_INIT {_PTHREAD_ONCE_SIG_init, {}}

/*
 * Thread Specific Data - keys
 */

#include <sys/time.h>

/*
 * Prototypes for all PTHREAD interfaces
 */
int       pthread_attr_destroy __P((pthread_attr_t *attr));
int       pthread_attr_getdetachstate __P((const pthread_attr_t *attr,
				      int *detachstate));
int       pthread_attr_getinheritsched __P((const pthread_attr_t *attr, 
				       int *inheritsched));
int       pthread_attr_getschedparam __P((const pthread_attr_t *attr, 
                                     struct sched_param *param));
int       pthread_attr_getschedpolicy __P((const pthread_attr_t *attr, 
				      int *policy));
int       pthread_attr_getstackaddr __P((const pthread_attr_t *attr,
                                      void **stackaddr));
int       pthread_attr_getstacksize __P((const pthread_attr_t *attr,
                                      size_t *stacksize));
int       pthread_attr_getstack __P((const pthread_attr_t *attr,
                                      void **stackaddr, size_t *stacksize));
int       pthread_attr_init __P((pthread_attr_t *attr));
int       pthread_attr_setdetachstate __P((pthread_attr_t *attr, 
				      int detachstate));
int       pthread_attr_setinheritsched __P((pthread_attr_t *attr, 
				       int inheritsched));
int       pthread_attr_setschedparam __P((pthread_attr_t *attr, 
                                     const struct sched_param *param));
int       pthread_attr_setschedpolicy __P((pthread_attr_t *attr, 
				      int policy));
int       pthread_attr_setstackaddr __P((pthread_attr_t *attr,
                                      void *stackaddr));
int       pthread_attr_setstacksize __P((pthread_attr_t *attr,
                                      size_t stacksize));
int       pthread_attr_setstack __P((pthread_attr_t *attr,
                                      void *stackaddr, size_t stacksize));
int       pthread_cancel __P((pthread_t thread));
int       pthread_setcancelstate __P((int state, int *oldstate));
int       pthread_setcanceltype __P((int type, int *oldtype));
void      pthread_testcancel __P((void));
int       pthread_cond_broadcast __P((pthread_cond_t *cond));
int       pthread_cond_destroy __P((pthread_cond_t *cond));
int       pthread_cond_init __P((pthread_cond_t *cond,
                            const pthread_condattr_t *attr));
int       pthread_cond_signal __P((pthread_cond_t *cond));
int       pthread_cond_wait __P((pthread_cond_t *cond, 
			    pthread_mutex_t *mutex));
int       pthread_cond_timedwait __P((pthread_cond_t *cond, 
				 pthread_mutex_t *mutex,
				 const struct timespec *abstime));
int       pthread_condattr_init __P((pthread_condattr_t *attr));
int       pthread_condattr_destroy __P((pthread_condattr_t *attr));
int       pthread_condattr_getpshared __P((const pthread_condattr_t *attr, 
			int *pshared));
int       pthread_condattr_setpshared __P((pthread_condattr_t *attr, 
			int pshared));
int       pthread_create __P((pthread_t *thread, 
                         const pthread_attr_t *attr,
                         void *(*start_routine)(void *), 
                         void *arg));
int       pthread_detach __P((pthread_t thread));
int       pthread_equal __P((pthread_t t1, 
			pthread_t t2));
void      pthread_exit __P((void *value_ptr));
int       pthread_kill __P((pthread_t, int));
int       pthread_sigmask __P((int, const sigset_t *, sigset_t *));
int       sigwait __P((const sigset_t *, int *));
int       pthread_getschedparam __P((pthread_t thread, 
				int *policy,
                                struct sched_param *param));
int       pthread_join __P((pthread_t thread, 
		       void **value_ptr));
int       pthread_mutex_destroy __P((pthread_mutex_t *mutex));
int       pthread_mutex_getprioceiling __P((const pthread_mutex_t *mutex, 
                                       int *prioceiling));
int       pthread_mutex_init __P((pthread_mutex_t *mutex, 
			     const pthread_mutexattr_t *attr));
int       pthread_mutex_lock __P((pthread_mutex_t *mutex));
int       pthread_mutex_setprioceiling __P((pthread_mutex_t *mutex, 
                                       int prioceiling, 
                                       int *old_prioceiling));
int       pthread_mutex_trylock __P((pthread_mutex_t *mutex));
int       pthread_mutex_unlock __P((pthread_mutex_t *mutex));
int       pthread_mutexattr_destroy __P((pthread_mutexattr_t *attr));
int       pthread_mutexattr_getprioceiling __P((const pthread_mutexattr_t *attr, 
                                           int *prioceiling));
int       pthread_mutexattr_getprotocol __P((const pthread_mutexattr_t *attr, 
                                        int *protocol));
int       pthread_mutexattr_getpshared __P((const pthread_mutexattr_t *attr, 
                                        int *pshared));
int       pthread_mutexattr_gettype __P((const pthread_mutexattr_t *attr, 
                                        int *type));
int       pthread_mutexattr_init __P((pthread_mutexattr_t *attr));
int       pthread_mutexattr_setprioceiling __P((pthread_mutexattr_t *attr, 
                                           int prioceiling));
int       pthread_mutexattr_setprotocol __P((pthread_mutexattr_t *attr, 
                                        int protocol));
int       pthread_mutexattr_settype __P((pthread_mutexattr_t *attr, 
                                        int type));
int       pthread_mutexattr_setpshared __P((pthread_mutexattr_t *attr, 
                                        int pshared));
int       pthread_once __P((pthread_once_t *once_control, 
		       void (*init_routine)(void)));
pthread_t pthread_self __P((void));
int       pthread_setschedparam __P((pthread_t thread, 
				int policy,
                                const struct sched_param *param));
int       pthread_key_create __P((pthread_key_t *key,
			     void (*destructor)(void *)));
int       pthread_key_delete __P((pthread_key_t key));
int       pthread_setspecific __P((pthread_key_t key,
			      const void *value));
void     *pthread_getspecific __P((pthread_key_t key));
int       pthread_attr_getscope __P((pthread_attr_t *, int *));
int       pthread_attr_setscope __P((pthread_attr_t *, int));
int       pthread_getconcurrency __P((void));
int       pthread_setconcurrency __P((int));
int       pthread_rwlock_destroy __P((pthread_rwlock_t * rwlock));
int       pthread_rwlock_init __P((pthread_rwlock_t * rwlock, 
			     const pthread_rwlockattr_t *attr));
int       pthread_rwlock_rdlock __P((pthread_rwlock_t *rwlock));
int       pthread_rwlock_tryrdlock __P((pthread_rwlock_t *rwlock));
int       pthread_rwlock_wrlock __P((pthread_rwlock_t *rwlock));
int       pthread_rwlock_trywrlock __P((pthread_rwlock_t *rwlock));
int       pthread_rwlock_unlock __P((pthread_rwlock_t *rwlock));
int       pthread_rwlockattr_init __P((pthread_rwlockattr_t *attr));
int       pthread_rwlockattr_destroy __P((pthread_rwlockattr_t *attr));
int       pthread_rwlockattr_getpshared __P((const pthread_rwlockattr_t *attr, 
			int *pshared));
int       pthread_rwlockattr_setpshared __P((pthread_rwlockattr_t *attr, 
			int pshared));

#ifndef _POSIX_C_SOURCE
/* returns non-zero if pthread_create or cthread_fork have been called */
int		pthread_is_threaded_np __P((void));

/* returns non-zero if the current thread is the main thread */
int		pthread_main_np __P((void));

/* return the mach thread bound to the pthread */
mach_port_t 	pthread_mach_thread_np __P((pthread_t));
size_t	 	pthread_get_stacksize_np __P((pthread_t));
void *		pthread_get_stackaddr_np __P((pthread_t));

/* Like pthread_cond_signal(), but only wake up the specified pthread */
int		pthread_cond_signal_thread_np __P((pthread_cond_t *, pthread_t));

/* Like pthread_cond_timedwait, but use a relative timeout */
int		pthread_cond_timedwait_relative_np __P((pthread_cond_t *cond, 
				 pthread_mutex_t *mutex,
				 const struct timespec *reltime));

/* Like pthread_create(), but leaves the thread suspended */
int       pthread_create_suspended_np __P((pthread_t *thread, 
                         const pthread_attr_t *attr,
                         void *(*start_routine)(void *), 
                         void *arg));
void pthread_yield_np __P((void));
#endif /* ! _POSIX_C_SOURCE */
__END_DECLS
#endif /* _POSIX_PTHREAD_H */
