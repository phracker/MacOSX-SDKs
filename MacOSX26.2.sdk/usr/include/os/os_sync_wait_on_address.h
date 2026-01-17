/*
 * Copyright (c) 2016 Apple Inc. All rights reserved.
 *
 * @APPLE_APACHE_LICENSE_HEADER_START@
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @APPLE_APACHE_LICENSE_HEADER_END@
 */

#ifndef __OS_SYNC_WAIT_ON_ADDRESS__
#define __OS_SYNC_WAIT_ON_ADDRESS__

#include <Availability.h>
#include <stddef.h>
#include <stdint.h>
#include <os/base.h>
#include <os/clock.h>

OS_ASSUME_NONNULL_BEGIN

/*! @header
 * Low-level Darwin's futex style APIs.
 */

__BEGIN_DECLS

#define OS_WAIT_ON_ADDR_AVAILABILITY \
	__API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), watchos(10.4))

/*!
 * @typedef os_sync_wait_on_address_flags_t
 *
 * @const OS_SYNC_WAIT_ON_ADDRESS_NONE
 * This flag should be used as a default flag when no other flags listed below
 * are required.
 *
 * @const OS_SYNC_WAIT_ON_ADDRESS_SHARED
 * This flag should be used when synchronizing among multiple processes by
 * placing the @addr passed to os_sync_wait_on_address and its variants
 * in a shared memory region.
 *
 * When using this flag, it is important to pass OS_SYNC_WAKE_BY_ADDRESS_SHARED
 * flag along with the exact same @addr to os_sync_wake_by_address_any and
 * its variants to correctly find and wake up blocked waiters on the @addr.
 *
 * This flag should not be used when synchronizing among multiple threads of
 * a single process. It allows the kernel to perform performance optimizations
 * as the @addr is local to the calling process.
 */
OS_OPTIONS(os_sync_wait_on_address_flags, uint32_t,
	OS_SYNC_WAIT_ON_ADDRESS_NONE
		OS_WAIT_ON_ADDR_AVAILABILITY = 0x00000000,
	OS_SYNC_WAIT_ON_ADDRESS_SHARED
		OS_WAIT_ON_ADDR_AVAILABILITY = 0x00000001,
);

/*!
 * @function os_sync_wait_on_address
 *
 * This function provides an atomic compare-and-wait functionality that
 * can be used to implement other higher level synchronization primitives.
 *
 * It reads a value from @addr, compares it to expected @value and blocks
 * the calling thread if they are equal. This sequence of operations is
 * done atomically with respect to other concurrent operations that can
 * be performed on this @addr by other threads using this same function
 * or os_sync_wake_by_addr variants. At this point, the blocked calling
 * thread is considered to be a waiter on this @addr, waiting to be woken
 * up by a call to os_sync_wake_by_addr variants. If the value at @addr
 * turns out to be different than expected, the calling thread returns
 * immediately without blocking.
 *
 * This function is expected to be used for implementing synchronization
 * primitives that do not have a sense of ownership (e.g. condition
 * variables, semaphores) as it does not provide priority inversion avoidance.
 * For locking primitives, it is recommended that you use existing OS
 * primitives such as os_unfair_lock API family / pthread mutex or
 * std::mutex.
 *
 * @param addr
 * The userspace address to be used for atomic compare-and-wait.
 * This address must be aligned to @size.
 *
 * @param value
 * The value expected at @addr.
 *
 * @param size
 * The size of @value, in bytes. This can be either 4 or 8 today.
 * For @value of @size 4 bytes, the upper 4 bytes of @value are ignored.
 *
 * @param flags
 * Flags to alter behavior of os_sync_wait_on_address.
 * See os_sync_wait_on_address_flags_t.
 *
 * @return
 * If the calling thread is woken up by a call to os_sync_wake_by_addr
 * variants or the value at @addr is different than expected, this function
 * returns successfully and the return value indicates the number
 * of outstanding waiters blocked on this address.
 * In the event of an error, returns -1 with errno set to indicate the error.
 *
 * EINVAL	:	Invalid flags or size.
 * EINVAL	:	The @addr passed is NULL or misaligned.
 * EINVAL	:	The operation associated with existing kernel state
 *				at this @addr is inconsistent with what the caller
 *				has requested.
 *				It is important to make sure consistent values are
 *				passed across wait and wake APIs for @addr, @size
 *				and the shared memory specification
 *				(See os_sync_wait_on_address_flags_t).
 *
 * It is possible for the os_sync_wait_on_address and its variants to perform
 * an early return in the event of following errors where user may want to
 * re-try the wait operation. E.g. low memory conditions could cause such early
 * return.
 * It is important to read the current value at the @addr before re-trying
 * to ensure that the new value still requires waiting on @addr.
 *
 * ENOMEM	:	Unable to allocate memory for kernel internal data
 *				structures.
 * EINTR	:	The syscall was interrupted / spurious wake up.
 * EFAULT	:	Unable to read value from the @addr. Kernel copyin failed.
 *				It is possible to receive EFAULT error in following cases:
 *				1. The @addr is an invalid address. This is a programmer error.
 *				2. The @addr is valid; but, this is a transient error such as
 *				due to low memory conditions. User may want to re-try the wait
 *				operation.
 * Following code snippet illustrates a possible re-try loop.
 * <code>
 * retry:
 *	current = atomic_load_explicit(addr, memory_order_relaxed);
 *	if (current != expected) {
 *		int ret = os_sync_wait_on_address(addr, current, size, flags);
 *		if ((ret < 0) && ((errno == EINTR) || (errno == EFAULT))) {
 *			goto retry;
 *		}
 * }
 * </code>
 */
OS_WAIT_ON_ADDR_AVAILABILITY
OS_EXPORT OS_NOTHROW OS_NONNULL_ALL
int
os_sync_wait_on_address(void *addr,
						uint64_t value,
						size_t size,
						os_sync_wait_on_address_flags_t flags);

/*!
 * @function os_sync_wait_on_address_with_deadline
 *
 * This function is a variant of os_sync_wait_on_address that
 * allows the calling thread to specify a deadline
 * until which it is willing to block.
 *
 * @param addr
 * The userspace address to be used for atomic compare-and-wait.
 * This address must be aligned to @size.
 *
 * @param value
 * The value expected at @addr.
 *
 * @param size
 * The size of @value, in bytes. This can be either 4 or 8 today.
 * For @value of @size 4 bytes, the upper 4 bytes of @value are ignored.
 *
 * @param flags
 * Flags to alter behavior of os_sync_wait_on_address_with_deadline.
 * See os_sync_wait_on_address_flags_t.
 *
 * @param clockid
 * This value anchors @deadline argument to a specific clock id.
 * See os_clockid_t.
 *
 * @param deadline
 * This value is used to specify a deadline until which the calling
 * thread is willing to block.
 * Passing zero for the @deadline results in an error being returned.
 * It is recommended to use os_sync_wait_on_address API to block
 * indefinitely until woken up by a call to os_sync_wake_by_address_any
 * or os_sync_wake_by_address_all APIs.
 *
 * @return
 * If the calling thread is woken up by a call to os_sync_wake_by_addr
 * variants or the value at @addr is different than expected, this function
 * returns successfully and the return value indicates the number
 * of outstanding waiters blocked on this address.
 * In the event of an error, returns -1 with errno set to indicate the error.
 *
 * In addition to errors returned by os_sync_wait_on_address, this function
 * can return the following additional error codes.
 *
 * EINVAL		:	Invalid clock id.
 * EINVAL		:	The @deadline passed is 0.
 * ETIMEDOUT	:	Deadline expired.
 */
OS_WAIT_ON_ADDR_AVAILABILITY
OS_EXPORT OS_NOTHROW OS_NONNULL_ALL
int
os_sync_wait_on_address_with_deadline(void *addr,
									  uint64_t value,
									  size_t size,
									  os_sync_wait_on_address_flags_t flags,
									  os_clockid_t clockid,
									  uint64_t deadline);

/*!
 * @function os_sync_wait_on_address_with_timeout
 *
 * This function is a variant of os_sync_wait_on_address that
 * allows the calling thread to specify a timeout
 * until which it is willing to block.
 *
 * @param addr
 * The userspace address to be used for atomic compare-and-wait.
 * This address must be aligned to @size.
 *
 * @param value
 * The value expected at @addr.
 *
 * @param size
 * The size of @value, in bytes. This can be either 4 or 8 today.
 * For @value of @size 4 bytes, the upper 4 bytes of @value are ignored.
 *
 * @param flags
 * Flags to alter behavior of os_sync_wait_on_address_with_timeout.
 * See os_sync_wait_on_address_flags_t.
 *
 * @param clockid
 * This value anchors @timeout_ns argument to a specific clock id.
 * See os_clockid_t.
 *
 * @param timeout_ns
 * This value is used to specify a timeout in nanoseconds until which
 * the calling thread is willing to block.
 * Passing zero for the @timeout_ns results in an error being returned.
 * It is recommended to use os_sync_wait_on_address API to block
 * indefinitely until woken up by a call to os_sync_wake_by_address_any
 * or os_sync_wake_by_address_all APIs.
 *
 * @return
 * If the calling thread is woken up by a call to os_sync_wake_by_address
 * variants or the value at @addr is different than expected, this function
 * returns successfully and the return value indicates the number
 * of outstanding waiters blocked on this address.
 * In the event of an error, returns -1 with errno set to indicate the error.
 *
 * In addition to errors returned by os_sync_wait_on_address, this function
 * can return the following additional error codes.
 *
 * EINVAL		:	Invalid clock id.
 * EINVAL		:	The @timeout_ns passed is 0.
 * ETIMEDOUT	:	Timeout expired.
 */
OS_WAIT_ON_ADDR_AVAILABILITY
OS_EXPORT OS_NOTHROW OS_NONNULL_ALL
int
os_sync_wait_on_address_with_timeout(void *addr,
									 uint64_t value,
									 size_t size,
									 os_sync_wait_on_address_flags_t flags,
									 os_clockid_t clockid,
									 uint64_t timeout_ns);

/*!
 * @typedef os_sync_wake_by_address_flags_t
 *
 * @const OS_SYNC_WAKE_BY_ADDRESS_NONE
 * This flag should be used as a default flag when no other flags listed below
 * are required.
 *
 * @const OS_SYNC_WAKE_BY_ADDRESS_SHARED
 * This flag should be used when synchronizing among multiple processes by
 * placing the @addr passed to os_sync_wake_by_address_any and its variants
 * in a shared memory region.
 *
 * When using this flag, it is important to pass OS_SYNC_WAIT_ON_ADDRESS_SHARED
 * flag along with the exact same @addr to os_sync_wait_on_address and
 * its variants to correctly find and wake up blocked waiters on the @addr.
 *
 * This flag should not be used when synchronizing among multiple threads of
 * a single process. It allows the kernel to perform performance optimizations
 * as the @addr is local the calling process.
 */
OS_OPTIONS(os_sync_wake_by_address_flags, uint32_t,
	OS_SYNC_WAKE_BY_ADDRESS_NONE
		OS_WAIT_ON_ADDR_AVAILABILITY = 0x00000000,
	OS_SYNC_WAKE_BY_ADDRESS_SHARED
		   OS_WAIT_ON_ADDR_AVAILABILITY = 0x00000001,
);

/*!
 * @function os_sync_wake_by_address_any
 *
 * This function wakes up one waiter out of all those blocked in os_sync_wait_on_address
 * or its variants on the @addr. No guarantee is provided about which
 * specific waiter is woken up.
 *
 * @param addr
 * The userspace address to be used for waking up the blocked waiter.
 * It should be same as what is passed to os_sync_wait_on_address or its variants.
 *
 * @param size
 * The size of lock value, in bytes. This can be either 4 or 8 today.
 * It should be same as what is passed to os_sync_wait_on_address or its variants.
 *
 * @param flags
 * Flags to alter behavior of os_sync_wake_by_address_any.
 * See os_sync_wake_by_address_flags_t.
 *
 * @return
 * Returns 0 on success.
 * In the event of an error, returns -1 with errno set to indicate the error.
 *
 * EINVAL	:	Invalid flags or size.
 * EINVAL	:	The @addr passed is NULL.
 * EINVAL	:	The operation associated with existing kernel state
 *				at this @addr is inconsistent with what caller
 *				has requested.
 *				It is important to make sure consistent values are
 *				passed across wait and wake APIs for @addr, @size
 *				and the shared memory specification
 *				(See os_sync_wake_by_address_flags_t).
 * ENOENT	:	No waiter(s) found waiting on the @addr.
 */
OS_WAIT_ON_ADDR_AVAILABILITY
OS_EXPORT OS_NOTHROW OS_NONNULL_ALL
int
os_sync_wake_by_address_any(void *addr,
							size_t size,
							os_sync_wake_by_address_flags_t flags);

/*!
 * @function os_sync_wake_by_address_all
 *
 * This function is a variant of os_sync_wake_by_address_any that wakes up all waiters
 * blocked in os_sync_wait_on_address or its variants.
 *
 * @param addr
 * The userspace address to be used for waking up the blocked waiters.
 * It should be same as what is passed to os_sync_wait_on_address or its variants.
 *
 * @param size
 * The size of lock value, in bytes. This can be either 4 or 8 today.
 * It should be same as what is passed to os_sync_wait_on_address or its variants.
 *
 * @param flags
 * Flags to alter behavior of os_sync_wake_by_address_all.
 * See os_sync_wake_by_address_flags_t.
 *
 * @return
 * Returns 0 on success.
 * In the event of an error, returns -1 with errno set to indicate the error.
 *
 * This function returns same error codes as returned by os_sync_wait_on_address.
 */
OS_WAIT_ON_ADDR_AVAILABILITY
OS_EXPORT OS_NOTHROW OS_NONNULL_ALL
int
os_sync_wake_by_address_all(void *addr,
							size_t size,
							os_sync_wake_by_address_flags_t flags);

__END_DECLS

OS_ASSUME_NONNULL_END

#endif // __OS_SYNC_WAIT_ON_ADDRESS__
