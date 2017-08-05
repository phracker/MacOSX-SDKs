/*
 * Copyright (c) 2015-2016 Apple, Inc. All rights reserved.
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
#ifndef __IOSKYWALKSUPPORT_H
#define __IOSKYWALKSUPPORT_H

#include <sys/cdefs.h>

extern int sk_verbose;

__BEGIN_DECLS

#ifdef __cplusplus
class IOMemoryDescriptor;
class IOMemoryMap;

typedef IOMemoryDescriptor *        IOSKMemoryRef;
typedef IOMemoryMap *               IOSKMemoryMapRef;
#else
typedef struct IOMemoryDescriptor * IOSKMemoryRef;
typedef struct IOMemoryMap *        IOSKMemoryMapRef;
#endif

typedef IOSKMemoryRef   IOSKMemoryArrayRef;
typedef IOSKMemoryRef   IOSKMemoryBufferRef;
typedef IOSKMemoryRef   IOSKMemoryDescriptor;

typedef struct
{
    boolean_t writable;
    boolean_t purgeable;
} IOSKMemoryBufferSpec;

IOSKMemoryBufferRef IOSKMemoryBufferCreate( mach_vm_size_t capacity,
                                            const IOSKMemoryBufferSpec * spec,
                                            mach_vm_address_t * kvaddr );

IOSKMemoryArrayRef  IOSKMemoryArrayCreate( const IOSKMemoryRef refs[],
                                           uint32_t count );

void                IOSKMemoryDestroy( IOSKMemoryRef reference );

IOSKMemoryMapRef    IOSKMemoryMapToTask( IOSKMemoryRef reference,
                                         task_t intoTask,
                                         mach_vm_address_t * mapAddr,
                                         mach_vm_size_t * mapSize );

void                IOSKMemoryMapDestroy( IOSKMemoryMapRef reference );

IOSKMemoryDescriptor IOSKMemoryGetIOMD( IOSKMemoryRef reference );

int                 IOSKMemoryReclaim( IOSKMemoryRef reference );
int                 IOSKMemoryDiscard( IOSKMemoryRef reference );

__END_DECLS

#endif /* __IOSKYWALKSUPPORT_H */
