/*
 * Copyright (c) 2025 Apple Inc. All rights reserved.
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

#ifndef __OS_SECURITY_CONFIG__
#define __OS_SECURITY_CONFIG__

#include <Availability.h>
#include <os/base.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <mach/mach_types.h>

__BEGIN_DECLS

/*!
 * @enum os_security_config_t
 *
 * @discussion
 * Supported security configurations that a process/task can have.
 * This is a bitmask type, allowing multiple configurations to be active.
 *
 * @constant OS_SECURITY_CONFIG_NONE
 * No security config flags set.
 *
 * @constant OS_SECURITY_CONFIG_HARDENED_HEAP
 * Indicates that the Hardened Heap configuration is enabled for the process/task.
 * This implies security-critical settings for the system memory allocator.
 *
 * @constant OS_SECURITY_CONFIG_TPRO
 * Indicates that Trusted Path Read-Only (TPRO) is enabled for the process/task.
 *
 * @constant OS_SECURITY_CONFIG_GUARD_OBJECTS
 * Indicates that the Guard Objects configuration is enabled for the process/task.
 */
__API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0), driverkit(25.0))
OS_OPTIONS(os_security_config, uint64_t,
  OS_SECURITY_CONFIG_NONE = 0x0,
  OS_SECURITY_CONFIG_HARDENED_HEAP OS_SWIFT_NAME(hardenedHeap) = 0x1,
  OS_SECURITY_CONFIG_TPRO OS_SWIFT_NAME(trustedPathReadOnly) = 0x2,
  OS_SECURITY_CONFIG_MTE OS_SWIFT_NAME(memoryTaggingExtension) = 0x4,

  OS_SECURITY_CONFIG_GUARD_OBJECTS OS_SWIFT_NAME(guardObjects) = 0x100,
);

/*!
 * @function os_security_config_get
 *
 * @abstract
 * Retrieves the security configuration bitmask for the current process.
 *
 * @discussion
 * This function inspects the value passed by the kernel to the current process.
 *
 * @result
 * An os_security_config_t value representing the active security flags.
 * This function is not expected to fail for the current process.
 */
__API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0), driverkit(25.0))
OS_EXPORT OS_NOTHROW
os_security_config_t
os_security_config_get(void);

/*!
 * @function os_security_config_get_for_proc
 *
 * @abstract
 * Retrieves the security configuration bitmask for a target process, identified by its PID.
 *
 * @discussion
 * This function queries the kernel for the set of security properties
 * active for the specified process.
 *
 * @param pid
 * The process identifier (pid_t) of the target process.
 *
 * @param config
 * A pointer to an os_security_config_t variable where the resulting security
 * configuration will be stored if the function succeeds. This parameter must not be NULL.
 *
 * @result
 * Returns 0 on success, in which case `*config` is populated, or -1 on failure.
 */
__API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0), driverkit(25.0))
OS_EXPORT OS_NOTHROW OS_NONNULL_ALL
int
os_security_config_get_for_proc(pid_t pid, os_security_config_t *config);

/*!
 * @function os_security_config_get_for_task
 *
 * @abstract
 * Retrieves the security configuration bitmask for a target Mach task.
 *
 * @discussion
 * This function queries the kernel for the set of security properties
 * active for the specified Mach task.
 *
 * @param task
 * The Mach task port (task_t) of the target task.
 *
 * @param config
 * A pointer to an os_security_config_t variable where the resulting security
 * configuration will be stored if the function succeeds. This parameter must not be NULL.
 *
 * @result
 * Returns 0 on success, in which case `*config` is populated, or -1 on failure.
 */
__API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0), driverkit(25.0))
OS_EXPORT OS_NOTHROW OS_NONNULL_ALL
int
os_security_config_get_for_task(task_t task, os_security_config_t *config);

__END_DECLS

#endif // __OS_SECURITY_CONFIG__
