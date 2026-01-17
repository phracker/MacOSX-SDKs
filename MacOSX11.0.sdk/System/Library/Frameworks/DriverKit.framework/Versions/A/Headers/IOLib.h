/*
 * Copyright (c) 2019-2019 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#include <DriverKit/IOReturn.h>
#include <DriverKit/IOTypes.h>
#include <sys/cdefs.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <os/overflow.h>
#include <os/log.h>
#include <TargetConditionals.h>

#ifndef DRIVERKIT_IOLIB_H
#define DRIVERKIT_IOLIB_H

__BEGIN_DECLS

void 
IOLogBuffer(const char * title, const void * buffer, size_t size);
uint32_t
crc32(uint32_t crc, const void *buf, size_t size);


/*! @function IOLog
 *   @abstract Log a message to console in text mode, and os_log.
 *   @discussion This function allows a driver to log diagnostic information to the screen during verbose boots, and to os_log.
 *   @param format A printf() style format string (see printf(3) documentation).
 */

int IOLog(const char *format, ...)
__attribute__((format(printf, 1, 2)));

/*! @function IOLogv
 *   @abstract Log a message to console in text mode, and os_log.
 *   @discussion This function allows a driver to log diagnostic information to the screen during verbose boots, and to os_log.
 *   @param format A printf() style format string (see printf(3) documentation).
 *   @param ap stdarg(3) style variable arguments. */

int IOLogv(const char *format, va_list ap)
__attribute__((format(printf, 1, 0)));

/*! @function IOMalloc
 *   @abstract Allocates general purpose memory.
 *   @discussion This is a general purpose utility to allocate memory. There are no alignment guarantees given on the returned memory, and alignment may vary depending on the configuration. To allocate memory for I/O, use IOBufferMemoryDescriptor::Create()
 *   @param length Size of the memory requested.
 *   @result Pointer to the allocated memory, or zero on failure.
 */
void *
IOMalloc(size_t length)
__attribute__((alloc_size(1)));

/*! @function IOMallocZero
 *   @abstract Allocates general purpose memory, initialized to zero.
 *   @discussion This is a general purpose utility to allocate memory, initialized to zero.. There are no alignment guarantees given on the returned memory, and alignment may vary depending on the configuration. To allocate memory for I/O, use IOBufferMemoryDescriptor::Create()
 *   @param length Size of the memory requested.
 *   @result Pointer to the allocated memory, or zero on failure.
 */
void * 
IOMallocZero(size_t length)
__attribute__((alloc_size(1)));

/*! @function IOFree
 *   @abstract Frees memory allocated with IOMalloc or IOMallocZero.
 *   @discussion This function frees memory allocated with IOMalloc.
 *   @param address Pointer to the allocated memory. Must be identical to result of a prior IOMalloc.
 *   @param length Size of the memory allocated. Must be identical to size of the corresponding IOMalloc
 */
void
IOFree(void * address, size_t length);

/*! @function IOSleep
 *   @abstract Sleep the calling thread for a number of milliseconds.
 *   @discussion This function blocks the calling thread for at least the number of specified milliseconds, giving time to other processes.
 *   @param ms The integer number of milliseconds to wait.
 */
void
IOSleep(uint64_t ms);

/*! @function IOSleep
 *   @abstract Sleep the calling thread for a number of microseconds.
 *   @discussion This function blocks the calling thread for at least the number of specified microseconds, giving time to other processes.
 *   @param us The integer number of microseconds to wait.
 */
void
IODelay(uint64_t us);

#if TARGET_OS_DRIVERKIT && !DRIVERKIT_PRIVATE

/*!
 * @group Raw Mach Time API
 * In general prefer to use the <time.h> API clock_gettime_nsec_np(3), which
 * deals in the same clocks (and more) in ns units.
 * Conversion of ns to (resp. from) tick units as returned by the mach time APIs
 * is performed by division (resp. multiplication) with the fraction returned by
 * mach_timebase_info().
 */

struct mach_timebase_info {
	uint32_t numer;
	uint32_t denom;
};

typedef struct mach_timebase_info *mach_timebase_info_t;
typedef struct mach_timebase_info  mach_timebase_info_data_t;

/*!
 * @function mach_timebase_info
 * Returns fraction to multiply a value in mach tick units with to convert it
 * to nanoseconds.
 *
 * @param info	Timebase fraction out parameter.
 * @result		KERN_SUCCESS if `info` was filled in.
 */
kern_return_t
mach_timebase_info(mach_timebase_info_t info);

/*!
 * @function mach_absolute_time
 * Returns current value of a clock that increments monotonically in tick units
 * (starting at an arbitrary point), this clock does not increment while the
 * system is asleep.
 *
 * Prefer to use the equivalent clock_gettime_nsec_np(CLOCK_UPTIME_RAW) in
 * nanoseconds.
 *
 * @result		Value of mach absolute time clock.
 */
uint64_t
mach_absolute_time(void);

/*!
 * @function mach_continuous_time
 * Returns current value of a clock that increments monotonically in tick units
 * (starting at an arbitrary point), including while the system is asleep.
 *
 * Prefer to use the equivalent clock_gettime_nsec_np(CLOCK_MONOTONIC_RAW) in
 * nanoseconds.
 *
 * @result		Value of mach continous time clock.
 */
uint64_t
mach_continuous_time(void);

#ifndef NSEC_PER_SEC
#define NSEC_PER_SEC    1000000000ull   /* nanoseconds per second */

/*! @enum Scale Factors
 *   @discussion Used when a scale_factor parameter is required to define a unit of time.
 *   @constant kNanosecondScale Scale factor for nanosecond based times.
 *   @constant kMicrosecondScale Scale factor for microsecond based times.
 *   @constant kMillisecondScale Scale factor for millisecond based times.
 *   @constant kSecondScale Scale factor for second based times. */

enum {
	kNanosecondScale  = 1,
	kMicrosecondScale = 1000,
	kMillisecondScale = 1000 * 1000,
	kSecondScale      = 1000 * 1000 * 1000,
};

#endif /* NSEC_PER_SEC */

#endif // TARGET_OS_DRIVERKIT && !DRIVERKIT_PRIVATE

/*!
 * @function OSSynchronizeIO
 * Performs an mfence instruction on an Intel-based Mac computer.
 */
void
OSSynchronizeIO(void);


/*! @function IOFixedMultiply
 *   @abstract Multiplies two 16.16 fixed point numbers.
 */
static inline IOFixed
IOFixedMultiply(IOFixed a, IOFixed b)
{
	return (IOFixed)((((int64_t) a) * ((int64_t) b)) >> 16);
}

/*! @function IOFixedMultiply
 *   @abstract Divides two 16.16 fixed point numbers.
 */
static inline IOFixed
IOFixedDivide(IOFixed a, IOFixed b)
{
	return (IOFixed)((((int64_t) a) << 16) / ((int64_t) b));
}

/*! @function IOParseBootArgNumber
 *   @abstract Parses any boot arguments in the macOS kernel boot-args.
 *   @discussion If the named argument is present in the kernel boot-args, return its value as an integer.
 *   @param arg_string C-string name of the argument.
 *   @param arg_ptr Pointer to variable to received parsed value.
 *   @param max_len Size in bytes of the argument pointed to by arg_ptr.
 *   @result True if the argument was found and parsed successfully to arg_ptr.
 */
bool
IOParseBootArgNumber(
	const char      *arg_string,
	void            *arg_ptr,
	int                     max_len);

/*! @function IOParseBootArgNumber
 *   @abstract Parses any boot arguments in the macOS kernel boot-args.
 *   @discussion If the named argument is present in the kernel boot-args, return its value as a c-string.
 *   @param arg_string C-string name of the argument.
 *   @param arg_ptr Pointer to char array to received parsed value.
 *   @param strlen Size in bytes of the char array pointed to by arg_ptr.
 *   @result True if the argument was found and parsed successfully to arg_ptr.
 */
bool
IOParseBootArgString(
	const char      *arg_string,
	char            *arg_ptr,
	int                     strlen);

/*! @function OSReportWithBacktrace
 *   @abstract Generates a backtrace and message for debugging.
 *   @discussion Generates a backtrace and message for debugging. May be inoperative on release OS builds.
 *   @param str printf-like arguments to be logged, along with the backtrace of the caller.
 */
void __attribute__((noinline, not_tail_called))
OSReportWithBacktrace(const char *str, ...);

/*! @function OSSafeReleaseNULL
 *  @abstract Release an object if not <code>NULL</code>, then set it to <code>NULL</code>.
 *  @param    inst  Instance of an OSObject, may be <code>NULL</code>.
 */
#define OSSafeReleaseNULL(inst) { if (NULL != (inst)) { (inst)->release(); (inst) = NULL; } }

/*! @macro IONew
 *   @abstract Calls IOMalloc with the size of an array of types.
 *   @param type C-type of the type to allocate
 *   @param count  Count of the types to allocate.
 *   @result A pointer to the allocated memory or NULL on failure. Deallocate with IODelete().
 */
#define IONew(type, count)                              \
({                                                      \
    size_t __size;                                      \
    (os_mul_overflow(sizeof(type), (count), &__size)    \
    ? ((type *) NULL)                                   \
    : ((type *) IOMalloc(__size)));                     \
})

/*! @macro IONewZero
 *   @abstract Calls IOMallocZero with the size of an array of types.
 *   @param type C-type of the type to allocate
 *   @param count  Count of the types to allocate.
 *   @result A pointer to the allocated memory or NULL on failure. Deallocate with IODelete().
 */
#define IONewZero(type, count)                          \
({                                                      \
    size_t __size;                                      \
    (os_mul_overflow(sizeof(type), (count), &__size)    \
    ? ((type *) NULL)                                   \
    : ((type *) IOMallocZero(__size)));                 \
})

/*! @macro IODelete
 *   @abstract Calls IOFree with the size of an array of types.
 *   @param ptr Previously allocated pointer returned by IOMalloc/IOMallocZero().
 *   @param type C-type of the type to deallocate
 *   @param count  Count of the types to deallocate.
 */
#define IODelete(ptr, type, count)                          \
({                                                          \
    size_t __size;                                          \
    if (!os_mul_overflow(sizeof(type), (count), &__size)) { \
        IOFree(ptr, __size);                                \
    }                                                       \
})

/*! @macro IODelete
 *   @abstract If the pointer is non-zero, calls IOFree with the size of an array of types, and sets the pointer to zero.
 *   @param ptr Previously allocated pointer returned by IOMalloc/IOMallocZero(), or NULL. The ptr will be set to zero.
 *   @param type C-type of the type to deallocate
 *   @param count  Count of the types to deallocate.
 */
#define IOSafeDeleteNULL(ptr, type, count)              \
    do {                                                \
        if (NULL != (ptr)) {                            \
            IODelete((ptr), type, count);               \
            (ptr) = NULL;                               \
        }                                               \
    } while (0)                                         \

/*! @extern IOVMPageSize
 *   @abstract Containes the page size of the VM paging system in bytes.
 */
extern uint64_t IOVMPageSize;


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

struct IOLock;

/*! @function IOLockAlloc
 *   @abstract Allocates and initializes a mutex.
 *   @discussion Allocates a mutex in general purpose memory, and initializes it.
 *   @result Pointer to the allocated lock, or zero on failure. */

struct IOLock * IOLockAlloc( void );

/*! @function IOLockFree
 *   @abstract Frees a mutex.
 *   @discussion Frees a lock allocated with IOLockAlloc. Mutex should be unlocked with no waiters.
 *   @param lock Pointer to the allocated lock. */

void    IOLockFree(struct IOLock * lock);

/*! @function IOLockFreeZero
 *   @abstract Frees a mutex and zeroes pointer.
 *   @discussion Frees a lock allocated with IOLockAlloc. Mutex should be unlocked with no waiters.
 *   @param lock Pointer to the allocated lock. */

#define IOLockFreeZero(l)	do { if (l) { IOLockFree(l); l = NULL; } } while (0);


/*! @function IOLockLock
 *   @abstract Lock a mutex.
 *   @discussion Lock the mutex. If the lock is held by any thread, block waiting for its unlock. Locking the mutex recursively from one thread will result in deadlock.
 *   @param lock Pointer to the allocated lock. */

void    IOLockLock(struct IOLock * lock);


/*! @function IOLockUnlock
 *   @abstract Unlock a mutex.
 *  @discussion Unlock the mutex and wake any blocked waiters. Results are undefined if the caller has not locked the mutex.
 *   @param lock Pointer to the allocated lock. */

void    IOLockUnlock(struct IOLock * lock);


/*! @function IOLockTryLock
 *   @abstract Attempt to lock a mutex.
 *   @discussion Lock the mutex if it is currently unlocked, and return true. If the lock is held by any thread, return false.
 *   @param lock Pointer to the allocated lock.
 *   @result True if the mutex was unlocked and is now locked by the caller, otherwise false. */

bool IOLockTryLock(struct IOLock * lock);

typedef enum {
	kIOLockAssertOwned    = 1,
	kIOLockAssertNotOwned = 2
} IOLockAssertState;

/*! @function   IOLockAssert
 *  @abstract   Assert that lock is either held or not held by current thread.
 *  @discussion Call with either kIOLockAssertOwned or kIOLockAssertNotOwned.
 *  Panics the kernel if the lock is not owned if called with kIOLockAssertOwned,
 *  and vice-versa.
 */
void
IOLockAssert(struct IOLock * lock, IOLockAssertState type);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

struct IORecursiveLock;


/*! @function IORecursiveLockAlloc
 *   @abstract Allocates and initializes an recursive lock.
 *   @discussion Allocates a recursive lock in general purpose memory, and initializes it. Recursive locks function identically to mutexes but allow one thread to lock more than once, with balanced unlocks.
 *   @result Pointer to the allocated lock, or zero on failure. */

struct IORecursiveLock * IORecursiveLockAlloc( void );

/*! @function IORecursiveLockFree
 *   @abstract Frees a recursive lock.
 *   @discussion Frees a lock allocated with IORecursiveLockAlloc. Lock should be unlocked with no waiters.
 *   @param lock Pointer to the allocated lock. */

void IORecursiveLockFree(struct IORecursiveLock * lock);

/*! @function IORecursiveLockFreeZero
 *   @abstract Frees a recursive lock and zeroes pointer.
 *   @discussion Frees a lock allocated with IORecursiveLockAlloc. Lock should be unlocked with no waiters.
 *   @param lock Pointer to the allocated lock. */

#define IORecursiveLockFreeZero(l)	do { if (l) { IORecursiveLockFree(l); l = NULL; } } while (0);

/*! @function IORecursiveLockLock
 *   @abstract Lock a recursive lock.
 *   @discussion Lock the recursive lock. If the lock is held by another thread, block waiting for its unlock. The lock may be taken recursively by the same thread, with a balanced number of calls to IORecursiveLockUnlock.
 *   @param lock Pointer to the allocated lock. */

void            IORecursiveLockLock(struct IORecursiveLock * lock);

/*! @function IORecursiveLockTryLock
 *   @abstract Attempt to lock a recursive lock.
 *   @discussion Lock the lock if it is currently unlocked, or held by the calling thread, and return true. If the lock is held by another thread, return false. Successful calls to IORecursiveLockTryLock should be balanced with calls to IORecursiveLockUnlock.
 *   @param lock Pointer to the allocated lock.
 *   @result True if the lock is now locked by the caller, otherwise false. */

bool       IORecursiveLockTryLock(struct IORecursiveLock * lock);

/*! @function IORecursiveLockUnlock
 *   @abstract Unlock a recursive lock.
 *  @discussion Undo one call to IORecursiveLockLock, if the lock is now unlocked wake any blocked waiters. Results are undefined if the caller does not balance calls to IORecursiveLockLock with IORecursiveLockUnlock.
 *   @param lock Pointer to the allocated lock. */

void            IORecursiveLockUnlock(struct IORecursiveLock * lock);

/*! @function IORecursiveLockHaveLock
 *   @abstract Check if a recursive lock is held by the calling thread.
 *   @discussion If the lock is held by the calling thread, return true, otherwise the lock is unlocked, or held by another thread and false is returned.
 *   @param lock Pointer to the allocated lock.
 *   @result True if the calling thread holds the lock otherwise false. */

bool       IORecursiveLockHaveLock(struct IORecursiveLock * lock);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

struct IORWLock;

/*! @function IORWLockAlloc
 *   @abstract Allocates and initializes a read/write lock.
 *   @discussion Allocates and initializes a read/write lock in general purpose memory. Read/write locks provide for multiple readers, one exclusive writer.
 *   @result Pointer to the allocated lock, or zero on failure. */

struct IORWLock * IORWLockAlloc(void);

/*! @function IORWLockFree
 *  @abstract Frees a read/write lock.
 *  @discussion Frees a lock allocated with IORWLockAlloc. Lock should be unlocked with no waiters.
 *   @param lock Pointer to the allocated lock. */

void    IORWLockFree(struct IORWLock * lock);

/*! @function IORWLockFree
 *  @abstract Frees a read/write lock and zeroes pointer.
 *  @discussion Frees a lock allocated with IORWLockAlloc. Lock should be unlocked with no waiters.
 *   @param lock Pointer to the allocated lock. */

#define IORWLockFreeZero(l)	do { if (l) { IORWLockFree(l); l = NULL; } } while (0);

/*! @function IORWLockRead
 *   @abstract Lock a read/write lock for read.
 *  @discussion Lock the lock for read, allowing multiple readers when there are no writers. If the lock is held for write, block waiting for its unlock. Locking the lock recursively from one thread, for read or write, can result in deadlock.
 *   @param lock Pointer to the allocated lock. */
void    IORWLockRead(struct IORWLock * lock);

/*! @function IORWLockWrite
 *   @abstract Lock a read/write lock for write.
 *   @discussion Lock the lock for write, allowing one writer exlusive access. If the lock is held for read or write, block waiting for its unlock. Locking the lock recursively from one thread, for read or write, can result in deadlock.
 *   @param lock Pointer to the allocated lock. */
void    IORWLockWrite(struct IORWLock * lock);

/*! @function IORWLockUnlock
 *   @abstract Unlock a read/write lock.
 *   @discussion Undo one call to IORWLockRead or IORWLockWrite. Results are undefined if the caller has not locked the lock.
 *   @param lock Pointer to the allocated lock. */
void    IORWLockUnlock(struct IORWLock * lock);

/*! @enum     IORWLockAssertState
 *  @abstract Used with IORWLockAssert to assert the state of a lock.
 */
typedef enum {
	kIORWLockAssertRead    = 1,
	kIORWLockAssertWrite   = 2,
	kIORWLockAssertHeld    = 3,
	kIORWLockAssertNotHeld = 4
} IORWLockAssertState;

/*! @function   IORWLockAssert
 *  @abstract   Assert that a reader-writer lock is either held or not held
 *  by the current thread.
 *  @discussion Call with a value defined by the IORWLockAssertState type.
 *  If the specified lock is not in the state specified by the type argument,
 *  then the kernel will panic.
 */
#if NOT_YET_56378490
void    IORWLockAssert(struct IORWLock * lock, IORWLockAssertState type);
#endif

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if TARGET_OS_DRIVERKIT && !DRIVERKIT_PRIVATE

/*!
 * @functiongroup OSByteOrder Macros
 * Subset of historical OSByteOrder macros that may still be in use by driver
 * projects. Should be considered as deprecated.
 */

#if defined(__BIG_ENDIAN__)

#define OSSwapLittleToHostInt16(x) __builtin_bswap16((uint16_t)(x))
#define OSSwapHostToLittleInt16(x) __builtin_bswap16((uint16_t)(x))
#define OSSwapLittleToHostInt32(x) __builtin_bswap32((uint32_t)(x))
#define OSSwapHostToLittleInt32(x) __builtin_bswap32((uint32_t)(x))
#define OSSwapLittleToHostInt64(x) __builtin_bswap64((uint64_t)(x))
#define OSSwapHostToLittleInt64(x) __builtin_bswap64((uint64_t)(x))

#define OSSwapBigToHostInt16(x) ((uint16_t)(x))
#define OSSwapHostToBigInt16(x) ((uint16_t)(x))
#define OSSwapBigToHostInt32(x) ((uint32_t)(x))
#define OSSwapHostToBigInt32(x) ((uint32_t)(x))
#define OSSwapBigToHostInt64(x) ((uint64_t)(x))
#define OSSwapHostToBigInt64(x) ((uint64_t)(x))

#elif defined(__LITTLE_ENDIAN__)

#define OSSwapLittleToHostInt16(x) ((uint16_t)(x))
#define OSSwapHostToLittleInt16(x) ((uint16_t)(x))
#define OSSwapLittleToHostInt32(x) ((uint32_t)(x))
#define OSSwapHostToLittleInt32(x) ((uint32_t)(x))
#define OSSwapLittleToHostInt64(x) ((uint64_t)(x))
#define OSSwapHostToLittleInt64(x) ((uint64_t)(x))

#define OSSwapBigToHostInt16(x) __builtin_bswap16((uint16_t)(x))
#define OSSwapHostToBigInt16(x) __builtin_bswap16((uint16_t)(x))
#define OSSwapBigToHostInt32(x) __builtin_bswap32((uint32_t)(x))
#define OSSwapHostToBigInt32(x) __builtin_bswap32((uint32_t)(x))
#define OSSwapBigToHostInt64(x) __builtin_bswap64((uint64_t)(x))
#define OSSwapHostToBigInt64(x) __builtin_bswap64((uint64_t)(x))

#else
#error Unknown endianess.
#endif

#endif // TARGET_OS_DRIVERKIT && !DRIVERKIT_PRIVATE

#if DRIVERKIT_TEST || DRIVERKIT_PRIVATE

extern kern_return_t
IODriverKitTest(int options);

#endif

#if DRIVERKIT_PRIVATE

extern void
__assert_rtn(
	const char *func,
	const char *file,
	int line,
	const char *failedexpr);

#if !TARGET_OS_DRIVERKIT
extern kern_return_t
IOUserServerMain(const char * serverName, const char * serverTagStr, uint32_t bundleCount, const char * bundles[]);
extern int
DriverExecutableMain(int argc, char * argv[]);
#endif // TARGET_OS_DRIVERKIT

enum {
	kIODKEnable            = 0x00000001ULL,
	kIODKLogSetup          = 0x00000002ULL,
	kIODKLogIPC            = 0x00000004ULL,
	kIODKLogPM             = 0x00000008ULL,
	kIODKLogMessages       = 0x00000010ULL,
//	kIODKLogX              = 0x00000800ULL,
	kIODKDisableDextLaunch = 0x00001000ULL,
	kIODKDisableDextTag    = 0x00002000ULL,
};

extern int64_t gIODKDebug;

#endif /* DRIVERKIT_PRIVATE */

__END_DECLS

#endif /* DRIVERKIT_IOLIB_H */
