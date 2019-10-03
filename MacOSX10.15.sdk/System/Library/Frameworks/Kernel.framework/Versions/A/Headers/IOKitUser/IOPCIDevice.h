/* iig(DriverKit-) generated from IOPCIDevice.iig */

/* IOPCIDevice.iig:1-48 */
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

#ifndef _IOKIT_UIOPCIDEVICE_H
#define _IOKIT_UIOPCIDEVICE_H

#include <DriverKit/IOService.h>  /* .iig include */
#include <DriverKit/IOMemoryDescriptor.h>  /* .iig include */

enum {
    kIOPCIMemoryApertureAccessReadDevice   = 0x00000100,
    kIOPCIMemoryApertureAccessWriteDevice  = 0x00000200,
    kIOPCIMemoryApertureAccessApertureMask = 0x000000FF,

    kIOPCIMemoryConfigAccessReadDevice     = 0x00000300,
    kIOPCIMemoryConfigAccessWriteDevice    = 0x00000400,

    kIOPCIMemoryAccess8Bit                 = 0x00080000,
    kIOPCIMemoryAccess16Bit                = 0x00100000,
    kIOPCIMemoryAccess32Bit                = 0x00200000,
    kIOPCIMemoryAccess64Bit                = 0x00400000,
};

/* class IOPCIDevice IOPCIDevice.iig:49-64 */

#define IOPCIDevice_MemoryAccess_ID            0x9d3d9c1d611e2483ULL
#define IOPCIDevice_CopyMemoryDescriptor_ID            0xc6f0a79ac2e3c858ULL

#define IOPCIDevice_MemoryAccess_Args \
        uint64_t operation, \
        uint64_t space, \
        uint64_t address, \
        uint64_t data, \
        uint64_t * returnData

#define IOPCIDevice_CopyMemoryDescriptor_Args \
        uint64_t index, \
        IOMemoryDescriptor ** memory

#define IOPCIDevice_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOPCIDevice * self, const IORPC rpc);\
\
    kern_return_t\
    MemoryAccess(\
        uint64_t operation,\
        uint64_t space,\
        uint64_t address,\
        uint64_t data,\
        uint64_t * returnData,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    CopyMemoryDescriptor(\
        uint64_t index,\
        IOMemoryDescriptor ** memory,\
        OSDispatchMethod supermethod = NULL);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*MemoryAccess_Handler)(OSMetaClassBase * target, IOPCIDevice_MemoryAccess_Args);\
    static kern_return_t\
    MemoryAccess_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        MemoryAccess_Handler func);\
\
    typedef kern_return_t (*CopyMemoryDescriptor_Handler)(OSMetaClassBase * target, IOPCIDevice_CopyMemoryDescriptor_Args);\
    static kern_return_t\
    CopyMemoryDescriptor_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        CopyMemoryDescriptor_Handler func);\
\


#define IOPCIDevice_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    kern_return_t\
    MemoryAccess_Impl(IOPCIDevice_MemoryAccess_Args);\
\
    kern_return_t\
    CopyMemoryDescriptor_Impl(IOPCIDevice_CopyMemoryDescriptor_Args);\
\


#define IOPCIDevice_VirtualMethods \
\
public:\
\


#if !KERNEL

extern OSMetaClass          * gIOPCIDeviceMetaClass;
extern const OSClassLoadInformation IOPCIDevice_Class;

class IOPCIDeviceMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOPCIDeviceInterface : public OSInterface
{
public:
};

struct IOPCIDevice_IVars;
struct IOPCIDevice_LocalIVars;

class IOPCIDevice : public IOService, public IOPCIDeviceInterface
{
#if !KERNEL
    friend class IOPCIDeviceMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOPCIDevice_IVars * ivars;
        IOPCIDevice_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = IOService;

#if !KERNEL
    IOPCIDevice_Methods
    IOPCIDevice_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */

/* IOPCIDevice.iig:66- */

#endif /* ! _IOKIT_UIOPCIDEVICE_H */
