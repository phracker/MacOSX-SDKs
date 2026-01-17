/* iig(DriverKit-73.0.1) generated from IOUserUSBHostHIDDevice.iig */

/* IOUserUSBHostHIDDevice.iig:1-41 */
/*
 * Copyright (c) 1998-2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _HIDDRIVERKIT_IOUSERUSBHOSTHIDDEVICE_H
#define _HIDDRIVERKIT_IOUSERUSBHOSTHIDDEVICE_H

#include <USBDriverKit/IOUSBHostInterface.h>  /* .iig include */
#include <USBDriverKit/IOUSBHostPipe.h>  /* .iig include */
#include <DriverKit/OSAction.h>  /* .iig include */
#include <DriverKit/IOService.h>  /* .iig include */
#include <DriverKit/IOTimerDispatchSource.h>  /* .iig include */
#include <HIDDriverKit/IOUserHIDDevice.h>  /* .iig include */

class  OSString;
struct IOUSBHostHIDDescriptorInfo;

typedef enum {
    USBIdlePolicyTypeInterface,
    USBIdlePolicyTypePipe,
} USBIdlePolicyType;

/* class IOUserUSBHostHIDDevice IOUserUSBHostHIDDevice.iig:42-333 */

#define IOUserUSBHostHIDDevice_CompleteInputReport_ID            0x40e1addf867de565ULL
#define IOUserUSBHostHIDDevice_TimerOccurred_ID            0x2a91ee629fd82a2dULL
#define IOUserUSBHostHIDDevice_CompleteZLP_ID            0x6b7467ea496a70d2ULL

#define IOUserUSBHostHIDDevice_Start_Args \
        IOService * provider

#define IOUserUSBHostHIDDevice_Stop_Args \
        IOService * provider

#define IOUserUSBHostHIDDevice_CompleteInputReport_Args \
        OSAction * action, \
        IOReturn status, \
        uint32_t actualByteCount, \
        uint64_t completionTimestamp

#define IOUserUSBHostHIDDevice_TimerOccurred_Args \
        OSAction * action, \
        uint64_t time

#define IOUserUSBHostHIDDevice_CompleteZLP_Args \
        OSAction * action, \
        IOReturn status, \
        uint32_t actualByteCount, \
        uint64_t completionTimestamp

#define IOUserUSBHostHIDDevice_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOUserUSBHostHIDDevice * self, const IORPC rpc);\
\
    kern_return_t\
    CreateActionCompleteInputReport(size_t referenceSize, OSAction ** action);\
\
    kern_return_t\
    CreateActionTimerOccurred(size_t referenceSize, OSAction ** action);\
\
    kern_return_t\
    getReport(\
        IOMemoryDescriptor * report,\
        IOHIDReportType reportType,\
        IOOptionBits options,\
        uint32_t completionTimeout,\
        uint32_t * bytesTransferred);\
\
    kern_return_t\
    setReport(\
        IOMemoryDescriptor * report,\
        IOHIDReportType reportType,\
        IOOptionBits options,\
        uint32_t completionTimeout);\
\
    kern_return_t\
    initPipes(\
);\
\
    kern_return_t\
    getHIDDescriptorInfo(\
        uint8_t type,\
        const IOUSBHostHIDDescriptorInfo ** info,\
        uint8_t * index);\
\
    OSString *\
    copyStringAtIndex(\
        uint8_t index,\
        uint16_t lang);\
\
    kern_return_t\
    CreateActionCompleteZLP(size_t referenceSize, OSAction ** action);\
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
    CompleteInputReport_Impl(IOUserUSBHostHIDDevice_CompleteInputReport_Args);\
\
    void\
    TimerOccurred_Impl(IOUserUSBHostHIDDevice_TimerOccurred_Args);\
\
    void\
    CompleteZLP_Impl(IOUserUSBHostHIDDevice_CompleteZLP_Args);\
\
\
public:\
    /* _Invoke methods */\
\


#define IOUserUSBHostHIDDevice_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define IOUserUSBHostHIDDevice_VirtualMethods \
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
    handleStart(\
        IOService * provider) APPLE_KEXT_OVERRIDE;\
\
    virtual OSDictionary *\
    newDeviceDescription(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual OSData *\
    newReportDescriptor(\
) APPLE_KEXT_OVERRIDE;\
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
    virtual kern_return_t\
    setProtocol(\
        uint16_t protocol) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    initInputReport(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    scheduleInputReportRetry(\
        kern_return_t reason) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    cancelInputReportRetry(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    setIdle(\
        uint16_t idleTimeMs) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    setIdlePolicy(\
        USBIdlePolicyType type,\
        uint16_t idleTimeMs) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    reset(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    setProperty(\
        OSObject * key,\
        OSObject * value) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gIOUserUSBHostHIDDeviceMetaClass;
extern const OSClassLoadInformation IOUserUSBHostHIDDevice_Class;

class IOUserUSBHostHIDDeviceMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOUserUSBHostHIDDeviceInterface : public OSInterface
{
public:
    virtual kern_return_t
    setProtocol(uint16_t protocol) = 0;

    virtual kern_return_t
    initInputReport() = 0;

    virtual void
    scheduleInputReportRetry(kern_return_t reason) = 0;

    virtual void
    cancelInputReportRetry() = 0;

    virtual kern_return_t
    setIdle(uint16_t idleTimeMs) = 0;

    virtual kern_return_t
    setIdlePolicy(USBIdlePolicyType type,
        uint16_t idleTimeMs) = 0;

    virtual void
    reset() = 0;

};

struct IOUserUSBHostHIDDevice_IVars;
struct IOUserUSBHostHIDDevice_LocalIVars;

class IOUserUSBHostHIDDevice : public IOUserHIDDevice, public IOUserUSBHostHIDDeviceInterface
{
#if !KERNEL
    friend class IOUserUSBHostHIDDeviceMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOUserUSBHostHIDDevice_IVars * ivars;
        IOUserUSBHostHIDDevice_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = IOUserHIDDevice;

#if !KERNEL
    IOUserUSBHostHIDDevice_Methods
    IOUserUSBHostHIDDevice_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */

/* IOUserUSBHostHIDDevice.iig:335- */

#endif	// _HIDDRIVERKIT_IOUSERUSBHOSTHIDDEVICE_H
