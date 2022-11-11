/*
 *  hv_vm_allocate.h
 *  Hypervisor Framework
 *
 *  Copyright (c) 2021 Apple Inc. All rights reserved.
 */

#pragma once

#if __arm64__
#include <arm64/hv/hv_kern_types.h>
#include <Hypervisor/hv_vm_types.h>
#define __HV_API_AVAILABLE API_AVAILABLE(macos(12.1)) API_UNAVAILABLE(ios)
#elif __x86_64__
#include <Hypervisor/hv_error.h>
#include <Hypervisor/hv_types.h>
#define __HV_API_AVAILABLE API_AVAILABLE(macos(12.0))
#else
#error "unknown architecture"
#endif

#include <os/availability.h>
#include <os/base.h>
#include <sys/types.h>

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @enum       hv_allocate_flags_t
 * @abstract   Memory allocation flags
 */
enum {
    HV_ALLOCATE_DEFAULT = 0,
};

typedef uint64_t hv_allocate_flags_t;

/*!
 * @function   hv_vm_allocate
 * @abstract   Allocate anonymous memory suitable to be mapped as guest memory
 * @param      uvap   Returned virtual address of the allocated memory
 * @param      size   Size in bytes of the region to be allocated
 * @param      flags  Memory allocation flags
 * @result     0 on success or error code
 * @discussion
 *             The memory is allocated with VM_PROT_DEFAULT permissions
 *             This API enables accurate memory accounting of the allocations
 *             it creates
 *             Size must be a multiple of PAGE_SIZE
 *             Memory returned by this API should be deallocated with
 *             hv_vm_deallocate
 */
__HV_API_AVAILABLE
OS_EXPORT
hv_return_t hv_vm_allocate(void * _Nullable * _Nonnull uvap,
    size_t size, hv_allocate_flags_t flags);

/*!
 * @function   hv_vm_deallocate
 * @abstract   Deallocate memory previously allocated by hv_vm_allocate
 * @param      uva    Virtual address of the allocated memory
 * @param      size   Size in bytes of the region to be deallocated
 * @result     0 on success or error code
 */
__HV_API_AVAILABLE
OS_EXPORT
hv_return_t hv_vm_deallocate(void *uva, size_t size);

__END_DECLS

OS_ASSUME_NONNULL_END

#undef __HV_API_AVAILABLE
