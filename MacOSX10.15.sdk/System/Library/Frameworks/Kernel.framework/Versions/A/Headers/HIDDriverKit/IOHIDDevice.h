/* iig(DriverKit-73.0.1) generated from IOHIDDevice.iig */

/* IOHIDDevice.iig:1-44 */
/*
 * Copyright (c) 2018-2019 Apple Inc. All rights reserved.
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

#if !__IIG
#if KERNEL
#include <IOKit/hid/IOHIDDevice.h>
#endif
#endif

#ifndef _HIDDRIVERKIT_IOHIDDEVICE_H
#define _HIDDRIVERKIT_IOHIDDEVICE_H

#include <DriverKit/OSAction.h>  /* .iig include */
#include <DriverKit/IOService.h>  /* .iig include */
#include <HIDDriverKit/IOHIDDeviceTypes.h>
#include <DriverKit/IOTypes.h>

class IOMemoryDescriptor;

/* class IOHIDDevice IOHIDDevice.iig:45-134 */

#define IOHIDDevice_KernelStart_ID            0xff0b791163823830ULL
#define IOHIDDevice_KernelCompleteReport_ID            0xdb01a9b43a5e9a30ULL
#define IOHIDDevice__ProcessReport_ID            0xd539b835ea14880fULL
#define IOHIDDevice__HandleReport_ID            0xad138a788e1f3247ULL
#define IOHIDDevice__SetProperty_ID            0xa6ee936a6065f6baULL
#define IOHIDDevice_CompleteReport_ID            0xf2d80ecf6d8c6cb5ULL

#define IOHIDDevice_KernelStart_Args \
        IOService * provider

#define IOHIDDevice_KernelCompleteReport_Args \
        OSAction * action, \
        IOReturn status, \
        uint32_t actualByteCount

#define IOHIDDevice__ProcessReport_Args \
        HIDReportCommandType command, \
        IOMemoryDescriptor * report, \
        IOHIDReportType reportType, \
        IOOptionBits options, \
        uint32_t completionTimeout, \
        OSAction * action

#define IOHIDDevice__HandleReport_Args \
        uint64_t timestamp, \
        IOMemoryDescriptor * report, \
        uint32_t reportLength, \
        IOHIDReportType reportType, \
        IOOptionBits options

#define IOHIDDevice__SetProperty_Args \
        IOBufferMemoryDescriptor * serialization

#define IOHIDDevice_CompleteReport_Args \
        OSAction * action, \
        IOReturn status, \
        uint32_t actualByteCount

#define IOHIDDevice_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOHIDDevice * self, const IORPC rpc);\
\
    kern_return_t\
    KernelStart(\
        IOService * provider,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    CreateActionKernelCompleteReport(size_t referenceSize, OSAction ** action);\
\
    void\
    _ProcessReport(\
        HIDReportCommandType command,\
        IOMemoryDescriptor * report,\
        IOHIDReportType reportType,\
        IOOptionBits options,\
        uint32_t completionTimeout,\
        OSAction * action,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    _HandleReport(\
        uint64_t timestamp,\
        IOMemoryDescriptor * report,\
        uint32_t reportLength,\
        IOHIDReportType reportType,\
        IOOptionBits options,\
        OSDispatchMethod supermethod = NULL);\
\
    void\
    _SetProperty(\
        IOBufferMemoryDescriptor * serialization,\
        OSDispatchMethod supermethod = NULL);\
\
    void\
    CompleteReport(\
        OSAction * action,\
        IOReturn status,\
        uint32_t actualByteCount,\
        OSDispatchMethod supermethod = NULL);\
\
\
protected:\
    /* _Impl methods */\
\
    void\
    _ProcessReport_Impl(IOHIDDevice__ProcessReport_Args);\
\
    void\
    _SetProperty_Impl(IOHIDDevice__SetProperty_Args);\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*KernelStart_Handler)(OSMetaClassBase * target, IOHIDDevice_KernelStart_Args);\
    static kern_return_t\
    KernelStart_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        KernelStart_Handler func);\
\
    typedef void (*_ProcessReport_Handler)(OSMetaClassBase * target, IOHIDDevice__ProcessReport_Args);\
    static kern_return_t\
    _ProcessReport_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        _ProcessReport_Handler func);\
\
    typedef kern_return_t (*_HandleReport_Handler)(OSMetaClassBase * target, IOHIDDevice__HandleReport_Args);\
    static kern_return_t\
    _HandleReport_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        _HandleReport_Handler func);\
\
    typedef void (*_SetProperty_Handler)(OSMetaClassBase * target, IOHIDDevice__SetProperty_Args);\
    static kern_return_t\
    _SetProperty_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        _SetProperty_Handler func);\
\
    typedef void (*CompleteReport_Handler)(OSMetaClassBase * target, IOHIDDevice_CompleteReport_Args);\
    static kern_return_t\
    CompleteReport_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        CompleteReport_Handler func);\
\


#define IOHIDDevice_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    kern_return_t\
    KernelStart_Impl(IOHIDDevice_KernelStart_Args);\
\
    void\
    KernelCompleteReport_Impl(IOHIDDevice_KernelCompleteReport_Args);\
\
    kern_return_t\
    _HandleReport_Impl(IOHIDDevice__HandleReport_Args);\
\


#define IOHIDDevice_VirtualMethods \
\
public:\
\
    virtual kern_return_t\
    handleReport(\
        uint64_t timestamp,\
        IOMemoryDescriptor * report,\
        uint32_t reportLength,\
        IOHIDReportType reportType,\
        IOOptionBits options) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    getReport(\
        IOMemoryDescriptor * report,\
        IOHIDReportType reportType,\
        IOOptionBits options,\
        uint32_t completionTimeout,\
        OSAction * action) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    setReport(\
        IOMemoryDescriptor * report,\
        IOHIDReportType reportType,\
        IOOptionBits options,\
        uint32_t completionTimeout,\
        OSAction * action) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    setProperty(\
        OSObject * key,\
        OSObject * value) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gIOHIDDeviceMetaClass;
extern const OSClassLoadInformation IOHIDDevice_Class;

class IOHIDDeviceMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOHIDDeviceInterface : public OSInterface
{
public:
    virtual kern_return_t
    handleReport(uint64_t timestamp,
        IOMemoryDescriptor * report,
        uint32_t reportLength,
        IOHIDReportType reportType,
        IOOptionBits options) = 0;

    virtual kern_return_t
    getReport(IOMemoryDescriptor * report,
        IOHIDReportType reportType,
        IOOptionBits options,
        uint32_t completionTimeout,
        OSAction * action) = 0;

    virtual kern_return_t
    setReport(IOMemoryDescriptor * report,
        IOHIDReportType reportType,
        IOOptionBits options,
        uint32_t completionTimeout,
        OSAction * action) = 0;

    virtual void
    setProperty(OSObject * key,
        OSObject * value) = 0;

};

struct IOHIDDevice_IVars;
struct IOHIDDevice_LocalIVars;

class IOHIDDevice : public IOService, public IOHIDDeviceInterface
{
#if !KERNEL
    friend class IOHIDDeviceMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOHIDDevice_IVars * ivars;
        IOHIDDevice_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = IOService;

#if !KERNEL
    IOHIDDevice_Methods
    IOHIDDevice_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


/* IOHIDDevice.iig:191- */


#endif /* ! _HIDDRIVERKIT_IOHIDDEVICE_H */
