/* iig(DriverKit-73.0.1) generated from IOUserHIDEventService.iig */

/* IOUserHIDEventService.iig:1-38 */
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

#ifndef _HIDDRIVERKIT_IOUSERHIDEVENTSERVICE_H
#define _HIDDRIVERKIT_IOUSERHIDEVENTSERVICE_H

#include <DriverKit/OSAction.h>  /* .iig include */
#include <DriverKit/IOService.h>  /* .iig include */
#include <HIDDriverKit/IOHIDInterface.h>  /* .iig include */
#include <HIDDriverKit/IOHIDEventService.h>  /* .iig include */

class OSArray;

/* class IOUserHIDEventService IOUserHIDEventService.iig:39-244 */

#define IOUserHIDEventService_ReportAvailable_ID            0x64b213ea6ab88649ULL

#define IOUserHIDEventService_Start_Args \
        IOService * provider

#define IOUserHIDEventService_Stop_Args \
        IOService * provider

#define IOUserHIDEventService_ReportAvailable_Args \
        uint64_t timestamp, \
        uint32_t reportID, \
        uint32_t reportLength, \
        IOHIDReportType type, \
        IOMemoryDescriptor * report, \
        OSAction * action

#define IOUserHIDEventService_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOUserHIDEventService * self, const IORPC rpc);\
\
    bool\
    createReportPool(\
);\
\
    kern_return_t\
    CreateActionReportAvailable(size_t referenceSize, OSAction ** action);\
\
\
protected:\
    /* _Impl methods */\
\
    kern_return_t\
    Start_Impl(IOService_Start_Args);\
\
    kern_return_t\
    Stop_Impl(IOService_Stop_Args);\
\
    void\
    ReportAvailable_Impl(IOUserHIDEventService_ReportAvailable_Args);\
\
\
public:\
    /* _Invoke methods */\
\


#define IOUserHIDEventService_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define IOUserHIDEventService_VirtualMethods \
\
public:\
\
    virtual bool\
    init(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    free(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    conformsTo(\
        uint32_t usagePage,\
        uint32_t usage) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    dispatchDigitizerStylusEvent(\
        uint64_t timeStamp,\
        IOHIDDigitizerStylusData * stylusData) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    dispatchDigitizerTouchEvent(\
        uint64_t timeStamp,\
        IOHIDDigitizerTouchData * touchData,\
        uint32_t touchDataCount) APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    handleStart(\
        IOService * provider) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    handleReport(\
        uint64_t timestamp,\
        uint8_t * report,\
        uint32_t reportLength,\
        IOHIDReportType type,\
        uint32_t reportID) APPLE_KEXT_OVERRIDE;\
\
    virtual OSArray *\
    getElements(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    dispatchEvent(\
        IOHIDEvent * event) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gIOUserHIDEventServiceMetaClass;
extern const OSClassLoadInformation IOUserHIDEventService_Class;

class IOUserHIDEventServiceMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOUserHIDEventServiceInterface : public OSInterface
{
public:
    virtual bool
    conformsTo(uint32_t usagePage,
        uint32_t usage) = 0;

    virtual bool
    handleStart(IOService * provider) = 0;

    virtual void
    handleReport(uint64_t timestamp,
        uint8_t * report,
        uint32_t reportLength,
        IOHIDReportType type,
        uint32_t reportID) = 0;

    virtual OSArray *
    getElements() = 0;

};

struct IOUserHIDEventService_IVars;
struct IOUserHIDEventService_LocalIVars;

class IOUserHIDEventService : public IOHIDEventService, public IOUserHIDEventServiceInterface
{
#if !KERNEL
    friend class IOUserHIDEventServiceMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOUserHIDEventService_IVars * ivars;
        IOUserHIDEventService_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = IOHIDEventService;

#if !KERNEL
    IOUserHIDEventService_Methods
    IOUserHIDEventService_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */

/* IOUserHIDEventService.iig:246- */

#endif /* ! _HIDDRIVERKIT_IOUSERHIDEVENTSERVICE_H */
