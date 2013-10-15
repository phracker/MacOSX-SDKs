/*
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
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

#ifndef _OSATOMIC_H_
#define _OSATOMIC_H_

#include    <stddef.h>
#include    <sys/cdefs.h>
#include    <stdint.h>
#include    <stdbool.h>

/* These are the preferred versions of the atomic and synchronization operations.
 * Their implementation is customized at boot time for the platform, including
 * late-breaking errata fixes as necessary.   They are thread safe.
 *
 * WARNING: all addresses passed to these functions must be "naturally aligned", ie
 * int32_t's must be 32-bit aligned (low 2 bits of address zero), and int64_t's
 * must be 64-bit aligned (low 3 bits of address zero.)
 *
 * Note that some versions of the atomic functions incorporate memory barriers,
 * and some do not.  Barriers strictly order memory access on a weakly-ordered
 * architecture such as PPC.  All loads and stores executed in sequential program
 * order before the barrier will complete before any load or store executed after
 * the barrier.  On a uniprocessor, the barrier operation is typically a nop.
 * On a multiprocessor, the barrier can be quite expensive.
 *
 * Most code will want to use the barrier functions to insure that memory shared
 * between threads is properly synchronized.  For example, if you want to initialize
 * a shared data structure and then atomically increment a variable to indicate
 * that the initialization is complete, then you MUST use OSAtomicIncrement32Barrier()
 * to ensure that the stores to your data structure complete before the atomic add.
 * Likewise, the consumer of that data structure MUST use OSAtomicDecrement32Barrier(),
 * in order to ensure that their loads of the structure are not executed before
 * the atomic decrement.  On the other hand, if you are simply incrementing a global
 * counter, then it is safe and potentially faster to use OSAtomicIncrement32().
 *
 * If you are unsure which version to use, prefer the barrier variants as they are
 * safer.
 *
 * The spinlock and queue operations always incorporate a barrier.
 */ 
__BEGIN_DECLS


/* Arithmetic functions.  They return the new value.  All the "or", "and", and "xor"
 * operations, and the barrier forms of add, are layered on top of compare-and-swap.
 */
int32_t	OSAtomicAdd32( int32_t theAmount, int32_t *theValue );
int32_t	OSAtomicAdd32Barrier( int32_t theAmount, int32_t *theValue );

inline static
int32_t	OSAtomicIncrement32( int32_t *theValue )
            { return OSAtomicAdd32(  1, theValue); }
inline static
int32_t	OSAtomicIncrement32Barrier( int32_t *theValue )
            { return OSAtomicAdd32Barrier(  1, theValue); }

inline static
int32_t	OSAtomicDecrement32( int32_t *theValue )
            { return OSAtomicAdd32( -1, theValue); }
inline static
int32_t	OSAtomicDecrement32Barrier( int32_t *theValue )
            { return OSAtomicAdd32Barrier( -1, theValue); }

int32_t	OSAtomicOr32( uint32_t theMask, uint32_t *theValue );
int32_t	OSAtomicOr32Barrier( uint32_t theMask, uint32_t *theValue );

int32_t	OSAtomicAnd32( uint32_t theMask, uint32_t *theValue ); 
int32_t	OSAtomicAnd32Barrier( uint32_t theMask, uint32_t *theValue ); 

int32_t	OSAtomicXor32( uint32_t theMask, uint32_t *theValue );
int32_t	OSAtomicXor32Barrier( uint32_t theMask, uint32_t *theValue );

#if defined(__ppc64__) || defined(__i386__) || defined(__x86_64__)

int64_t	OSAtomicAdd64( int64_t theAmount, int64_t *theValue );
int64_t	OSAtomicAdd64Barrier( int64_t theAmount, int64_t *theValue );

inline static
int64_t	OSAtomicIncrement64( int64_t *theValue )
            { return OSAtomicAdd64(  1, theValue); }
inline static
int64_t	OSAtomicIncrement64Barrier( int64_t *theValue )
            { return OSAtomicAdd64Barrier(  1, theValue); }

inline static
int64_t	OSAtomicDecrement64( int64_t *theValue )
            { return OSAtomicAdd64( -1, theValue); }
inline static
int64_t	OSAtomicDecrement64Barrier( int64_t *theValue )
            { return OSAtomicAdd64Barrier( -1, theValue); }

#endif  /* defined(__ppc64__) || defined(__i386__) || defined(__x86_64__) */


/* Compare and swap.  They return true if the swap occured.
 */
bool    OSAtomicCompareAndSwap32( int32_t oldValue, int32_t newValue, int32_t *theValue );
bool    OSAtomicCompareAndSwap32Barrier( int32_t oldValue, int32_t newValue, int32_t *theValue );

#if defined(__ppc64__) || defined(__i386__) || defined(__x86_64__)

bool    OSAtomicCompareAndSwap64( int64_t oldValue, int64_t newValue, int64_t *theValue );
bool    OSAtomicCompareAndSwap64Barrier( int64_t oldValue, int64_t newValue, int64_t *theValue );

#endif  /* defined(__ppc64__) || defined(__i386__) || defined(__x86_64__) */


/* Test and set.  They return the original value of the bit, and operate on bit (0x80>>(n&7))
 * in byte ((char*)theAddress + (n>>3)).  They are layered on top of the compare-and-swap
 * operation.
 */
bool    OSAtomicTestAndSet( uint32_t n, void *theAddress );
bool    OSAtomicTestAndSetBarrier( uint32_t n, void *theAddress );
bool    OSAtomicTestAndClear( uint32_t n, void *theAddress );
bool    OSAtomicTestAndClearBarrier( uint32_t n, void *theAddress );
 
/* Spinlocks.  These use memory barriers as required to synchronize access to shared
 * memory protected by the lock.  The lock operation spins, but employs various strategies
 * to back off if the lock is held, making it immune to most priority-inversion livelocks.
 * The try operation immediately returns false if the lock was held, true if it took the
 * lock.  The convention is that unlocked is zero, locked is nonzero.
 */
#define	OS_SPINLOCK_INIT    0

typedef	int32_t OSSpinLock;

bool    OSSpinLockTry( OSSpinLock *lock );
void    OSSpinLockLock( OSSpinLock *lock );
void    OSSpinLockUnlock( OSSpinLock *lock );


/* Memory barrier.  It is both a read and write barrier.
 */
void    OSMemoryBarrier( void );

__END_DECLS

#endif /* _OSATOMIC_H_ */
