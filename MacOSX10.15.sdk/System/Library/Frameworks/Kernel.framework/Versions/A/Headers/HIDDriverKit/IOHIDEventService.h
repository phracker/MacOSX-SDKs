/* iig(DriverKit-73.0.1) generated from IOHIDEventService.iig */

/* IOHIDEventService.iig:1-47 */
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
#include <IOKit/hidevent/IOHIDEventService.h>
#endif
#endif

#ifndef _HIDDRIVERKIT_IOHIDEVENTSERVICE_H
#define _HIDDRIVERKIT_IOHIDEVENTSERVICE_H

#include <DriverKit/OSAction.h>  /* .iig include */
#include <DriverKit/IOService.h>  /* .iig include */
#include <DriverKit/IOTypes.h>

class IOBufferMemoryDescriptor;
class IOHIDEvent;

typedef struct IOHIDDigitizerStylusData IOHIDDigitizerStylusData;
typedef struct IOHIDDigitizerTouchData IOHIDDigitizerTouchData;

/* class IOHIDEventService IOHIDEventService.iig:48-263 */

#define IOHIDEventService_EventAvailable_ID            0xb6d3212b1068148aULL
#define IOHIDEventService_SetEventMemory_ID            0xed62c58e8d2f64e7ULL
#define IOHIDEventService__DispatchRelativeScrollWheelEvent_ID            0xe5902a0b51ed22ffULL
#define IOHIDEventService__DispatchAbsolutePointerEvent_ID            0xa89e9153d54a8eb1ULL
#define IOHIDEventService__DispatchRelativePointerEvent_ID            0xdfb3b21fdb3ea3b4ULL
#define IOHIDEventService__DispatchKeyboardEvent_ID            0xd8dc8ce69e15f7d3ULL
#define IOHIDEventService_KernelStart_ID            0xae2fd4b5293ad02aULL
#define IOHIDEventService_SetLED_ID            0xfee475ac1384bab8ULL

#define IOHIDEventService_EventAvailable_Args \
        uint32_t length

#define IOHIDEventService_SetEventMemory_Args \
        IOBufferMemoryDescriptor * memory

#define IOHIDEventService__DispatchRelativeScrollWheelEvent_Args \
        uint64_t timeStamp, \
        IOFixed dx, \
        IOFixed dy, \
        IOFixed dz, \
        IOOptionBits options, \
        bool accelerate

#define IOHIDEventService__DispatchAbsolutePointerEvent_Args \
        uint64_t timeStamp, \
        IOFixed x, \
        IOFixed y, \
        uint32_t buttonState, \
        IOOptionBits options, \
        bool accelerate

#define IOHIDEventService__DispatchRelativePointerEvent_Args \
        uint64_t timeStamp, \
        IOFixed dx, \
        IOFixed dy, \
        uint32_t buttonState, \
        IOOptionBits options, \
        bool accelerate

#define IOHIDEventService__DispatchKeyboardEvent_Args \
        uint64_t timeStamp, \
        uint32_t usagePage, \
        uint32_t usage, \
        uint32_t value, \
        IOOptionBits options, \
        bool repeat

#define IOHIDEventService_KernelStart_Args \
        IOService * provider

#define IOHIDEventService_SetLED_Args \
        uint32_t usage, \
        bool on

#define IOHIDEventService_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOHIDEventService * self, const IORPC rpc);\
\
    kern_return_t\
    EventAvailable(\
        uint32_t length,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    SetEventMemory(\
        IOBufferMemoryDescriptor * memory,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    _DispatchRelativeScrollWheelEvent(\
        uint64_t timeStamp,\
        IOFixed dx,\
        IOFixed dy,\
        IOFixed dz,\
        IOOptionBits options,\
        bool accelerate,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    _DispatchAbsolutePointerEvent(\
        uint64_t timeStamp,\
        IOFixed x,\
        IOFixed y,\
        uint32_t buttonState,\
        IOOptionBits options,\
        bool accelerate,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    _DispatchRelativePointerEvent(\
        uint64_t timeStamp,\
        IOFixed dx,\
        IOFixed dy,\
        uint32_t buttonState,\
        IOOptionBits options,\
        bool accelerate,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    _DispatchKeyboardEvent(\
        uint64_t timeStamp,\
        uint32_t usagePage,\
        uint32_t usage,\
        uint32_t value,\
        IOOptionBits options,\
        bool repeat,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    KernelStart(\
        IOService * provider,\
        OSDispatchMethod supermethod = NULL);\
\
    void\
    SetLED(\
        uint32_t usage,\
        bool on,\
        OSDispatchMethod supermethod = NULL);\
\
\
protected:\
    /* _Impl methods */\
\
    void\
    SetLED_Impl(IOHIDEventService_SetLED_Args);\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*EventAvailable_Handler)(OSMetaClassBase * target, IOHIDEventService_EventAvailable_Args);\
    static kern_return_t\
    EventAvailable_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        EventAvailable_Handler func);\
\
    typedef kern_return_t (*SetEventMemory_Handler)(OSMetaClassBase * target, IOHIDEventService_SetEventMemory_Args);\
    static kern_return_t\
    SetEventMemory_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SetEventMemory_Handler func);\
\
    typedef kern_return_t (*_DispatchRelativeScrollWheelEvent_Handler)(OSMetaClassBase * target, IOHIDEventService__DispatchRelativeScrollWheelEvent_Args);\
    static kern_return_t\
    _DispatchRelativeScrollWheelEvent_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        _DispatchRelativeScrollWheelEvent_Handler func);\
\
    typedef kern_return_t (*_DispatchAbsolutePointerEvent_Handler)(OSMetaClassBase * target, IOHIDEventService__DispatchAbsolutePointerEvent_Args);\
    static kern_return_t\
    _DispatchAbsolutePointerEvent_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        _DispatchAbsolutePointerEvent_Handler func);\
\
    typedef kern_return_t (*_DispatchRelativePointerEvent_Handler)(OSMetaClassBase * target, IOHIDEventService__DispatchRelativePointerEvent_Args);\
    static kern_return_t\
    _DispatchRelativePointerEvent_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        _DispatchRelativePointerEvent_Handler func);\
\
    typedef kern_return_t (*_DispatchKeyboardEvent_Handler)(OSMetaClassBase * target, IOHIDEventService__DispatchKeyboardEvent_Args);\
    static kern_return_t\
    _DispatchKeyboardEvent_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        _DispatchKeyboardEvent_Handler func);\
\
    typedef kern_return_t (*KernelStart_Handler)(OSMetaClassBase * target, IOHIDEventService_KernelStart_Args);\
    static kern_return_t\
    KernelStart_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        KernelStart_Handler func);\
\
    typedef void (*SetLED_Handler)(OSMetaClassBase * target, IOHIDEventService_SetLED_Args);\
    static kern_return_t\
    SetLED_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SetLED_Handler func);\
\


#define IOHIDEventService_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    kern_return_t\
    EventAvailable_Impl(IOHIDEventService_EventAvailable_Args);\
\
    kern_return_t\
    SetEventMemory_Impl(IOHIDEventService_SetEventMemory_Args);\
\
    kern_return_t\
    _DispatchRelativeScrollWheelEvent_Impl(IOHIDEventService__DispatchRelativeScrollWheelEvent_Args);\
\
    kern_return_t\
    _DispatchAbsolutePointerEvent_Impl(IOHIDEventService__DispatchAbsolutePointerEvent_Args);\
\
    kern_return_t\
    _DispatchRelativePointerEvent_Impl(IOHIDEventService__DispatchRelativePointerEvent_Args);\
\
    kern_return_t\
    _DispatchKeyboardEvent_Impl(IOHIDEventService__DispatchKeyboardEvent_Args);\
\
    kern_return_t\
    KernelStart_Impl(IOHIDEventService_KernelStart_Args);\
\


#define IOHIDEventService_VirtualMethods \
\
public:\
\
    virtual kern_return_t\
    dispatchKeyboardEvent(\
        uint64_t timeStamp,\
        uint32_t usagePage,\
        uint32_t usage,\
        uint32_t value,\
        IOOptionBits options,\
        bool repeat) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    dispatchRelativePointerEvent(\
        uint64_t timeStamp,\
        IOFixed dx,\
        IOFixed dy,\
        uint32_t buttonState,\
        IOOptionBits options,\
        bool accelerate) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    dispatchAbsolutePointerEvent(\
        uint64_t timeStamp,\
        IOFixed x,\
        IOFixed y,\
        uint32_t buttonState,\
        IOOptionBits options,\
        bool accelerate) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    dispatchRelativeScrollWheelEvent(\
        uint64_t timeStamp,\
        IOFixed dx,\
        IOFixed dy,\
        IOFixed dz,\
        IOOptionBits options,\
        bool accelerate) APPLE_KEXT_OVERRIDE;\
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
    virtual void\
    dispatchEvent(\
        IOHIDEvent * event) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gIOHIDEventServiceMetaClass;
extern const OSClassLoadInformation IOHIDEventService_Class;

class IOHIDEventServiceMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOHIDEventServiceInterface : public OSInterface
{
public:
    virtual kern_return_t
    dispatchKeyboardEvent(uint64_t timeStamp,
        uint32_t usagePage,
        uint32_t usage,
        uint32_t value,
        IOOptionBits options,
        bool repeat) = 0;

    virtual kern_return_t
    dispatchRelativePointerEvent(uint64_t timeStamp,
        IOFixed dx,
        IOFixed dy,
        uint32_t buttonState,
        IOOptionBits options,
        bool accelerate) = 0;

    virtual kern_return_t
    dispatchAbsolutePointerEvent(uint64_t timeStamp,
        IOFixed x,
        IOFixed y,
        uint32_t buttonState,
        IOOptionBits options,
        bool accelerate) = 0;

    virtual kern_return_t
    dispatchRelativeScrollWheelEvent(uint64_t timeStamp,
        IOFixed dx,
        IOFixed dy,
        IOFixed dz,
        IOOptionBits options,
        bool accelerate) = 0;

    virtual kern_return_t
    dispatchDigitizerStylusEvent(uint64_t timeStamp,
        IOHIDDigitizerStylusData * stylusData) = 0;

    virtual kern_return_t
    dispatchDigitizerTouchEvent(uint64_t timeStamp,
        IOHIDDigitizerTouchData * touchData,
        uint32_t touchDataCount) = 0;

    virtual void
    dispatchEvent(IOHIDEvent * event) = 0;

};

struct IOHIDEventService_IVars;
struct IOHIDEventService_LocalIVars;

class IOHIDEventService : public IOService, public IOHIDEventServiceInterface
{
#if !KERNEL
    friend class IOHIDEventServiceMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOHIDEventService_IVars * ivars;
        IOHIDEventService_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = IOService;

#if !KERNEL
    IOHIDEventService_Methods
    IOHIDEventService_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


/* IOHIDEventService.iig:300- */

#endif /* ! _HIDDRIVERKIT_IOHIDEVENTSERVICE_H */
