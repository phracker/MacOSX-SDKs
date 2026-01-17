/*
 * Copyright (c) 2022 Apple Inc. All rights reserved.
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

#ifndef _KERN_EXT_PANICLOG_H_
#define _KERN_EXT_PANICLOG_H_

#include <sys/queue.h>
#include <uuid/uuid.h>
#include <os/base.h>

#define EXT_PANICLOG_ENABLE     1

#define EXT_PANICLOG_VERSION    2

#define MAX_DATA_ID_SIZE    32

#define MAX_EXT_PANICLOG_SIZE   32 * 1024

#define MAX_EXT_PANICLOG_LOGS   100

/*
 * From the panic log metrics, we estimate that the paniclog takes up
 * ~15K bytes and other log takes ~1K bytes. This 64K bytes ensures that
 * we have enough space for other log and nested panics
 */
#define OTHER_LOG_REQUIRED_SIZE (64 * 1024)

#define PANIC_WITH_DATA_UUID "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
#define PANIC_WITH_DATA_MAX_LEN 2048
#define PANIC_WITH_DATA_DATA_ID "Panic with Data Buffer"

#define EXTPANICLOG_ENTITLEMENT         "com.apple.private.allow-ext_paniclog"

/*
 * These flags are set internally and are passed along with each handle in
 * the extensible paniclog to be processed by DumpPanic.
 */
OS_CLOSED_OPTIONS(ext_paniclog_flags, uint32_t,
    EXT_PANICLOG_FLAGS_NONE = 0x0,
    EXT_PANICLOG_FLAGS_ADD_SEPARATE_KEY = 0x1);

OS_CLOSED_OPTIONS(ext_paniclog_create_options, uint32_t,
    EXT_PANICLOG_OPTIONS_NONE = 0x0,
    EXT_PANICLOG_OPTIONS_WITH_BUFFER = 0x1,
    /* Adds the 'data ID' as a key and handle data as its value directly
     * in the paniclog instead of within the 'ExtensiblePaniclog' field
     */
    EXT_PANICLOG_OPTIONS_ADD_SEPARATE_KEY = 0x2);


#endif // _KERN_EXT_PANICLOG_H_
