//
//  hv_vm_allocate.h
//  Hypervisor
//
//  Copyright © 2021-2024 Apple Inc. All rights reserved.
//

#pragma once

#include <Hypervisor/hv_base.h>
#include <os/availability.h>
#include <os/base.h>
#include <sys/types.h>

#if defined(__arm64__)
#include <Hypervisor/hv_vm_types.h>
#include <arm64/hv/hv_kern_types.h>
#elif defined(__x86_64__)
#include <Hypervisor/hv_error.h>
#include <Hypervisor/hv_types.h>
#endif

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 @abstract Memory allocation flags
 */
enum {
    HV_ALLOCATE_DEFAULT = 0,
};

typedef uint64_t hv_allocate_flags_t;

/*!
 @abstract Allocate anonymous memory suitable to be mapped as guest memory
 @param uvap Returned virtual address of the allocated memory
 @param size Size in bytes of the region to be allocated
 @param flags Memory allocation flags
 @result 0 on success or error code
 @discussion
    The memory is allocated with VM_PROT_DEFAULT permissions
    This API enables accurate memory accounting of the allocations
    it creates
    Size must be a multiple of PAGE_SIZE
    Memory returned by this API should be deallocated with
    hv_vm_deallocate
 */
OS_EXPORT HV_API_AVAILABLE_ARM64(macos(12.1)) HV_API_AVAILABLE_X86_64(macos(12.0))
hv_return_t hv_vm_allocate(void * _Nullable * _Nonnull uvap, size_t size, hv_allocate_flags_t flags);

/*!
 @abstract Deallocate memory previously allocated by hv_vm_allocate
 @param uva Virtual address of the allocated memory
 @param size Size in bytes of the region to be deallocated
 @result 0 on success or error code
 */
OS_EXPORT HV_API_AVAILABLE_ARM64(macos(12.1)) HV_API_AVAILABLE_X86_64(macos(12.0))
hv_return_t hv_vm_deallocate(void *uva, size_t size);

__END_DECLS

OS_ASSUME_NONNULL_END
