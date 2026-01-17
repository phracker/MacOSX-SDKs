/*
 *  hv_vm_types.h
 *  Hypervisor Framework
 *
 *  Copyright (c) 2018-2020 Apple Inc. All rights reserved.
 */

#pragma once

#ifdef __arm64__

#include <Hypervisor/hv_base.h>
#include <arm64/hv/hv_kern_types.h>
#include <os/object.h>

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
* @typedef hv_vm_config_t
*
* @abstract
* Configuration for hv_vm_create().
*/
#if OS_OBJECT_USE_OBJC
OS_OBJECT_DECL(hv_vm_config);
#else // OS_OBJECT_USE_OBJC
typedef struct hv_vm_config_s *hv_vm_config_t;
#endif // OS_OBJECT_USE_OBJC

/*!
 * @typedef    hv_ipa_t
 * @abstract   Type of an Intermediate Physical Address (a guest physical address)
 */
typedef uint64_t hv_ipa_t;

/*!
 * @enum       hv_memory_flags_t
 * @abstract   Guest physical memory region permissions for hv_vm_map()
 *             and hv_vm_protect()
 */
typedef uint64_t hv_memory_flags_t;

__END_DECLS

OS_ASSUME_NONNULL_END

#endif
