#ifndef _PTHREAD_IMPL_H_
#define _PTHREAD_IMPL_H_
/*
 * Internal implementation details
 */

/* This whole header file will disappear, so don't depend on it... */

#ifndef __POSIX_LIB__

/*
 * [Internal] data structure signatures
 */
#define _PTHREAD_MUTEX_SIG_init		0x32AAABA7
#define _PTHREAD_COND_SIG_init		0x3CB0B1BB
#define _PTHREAD_ONCE_SIG_init		0x30B1BCBA
/*
 * POSIX scheduling policies
 */
#define SCHED_OTHER                1
#define SCHED_FIFO                 4
#define SCHED_RR                   2

#define __SCHED_PARAM_SIZE__       4

#endif /* __POSIX_LIB__ */

#endif /* _PTHREAD_IMPL_H_ */
