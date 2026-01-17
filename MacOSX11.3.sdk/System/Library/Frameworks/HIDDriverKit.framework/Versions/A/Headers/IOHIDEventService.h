/* iig(DriverKit-107.100.6) generated from IOHIDEventService.iig */

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

/* source class IOHIDEventService IOHIDEventService.iig:48-249 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

class KERNEL IOHIDEventService : public IOService
{

public:

    /*!
     * @function DispatchKeyboardEvent
     *
     * @abstract
     * Dispatches a keyboard event with the provided usage page, usage, and
     * value.
     *
     * @param timestamp
     * The timestamp of the event.
     *
     * @param usagePage
     * The usage page. Usage pages are defined in
     * <IOKit/hid/IOHIDUsageTables.h>.
     *
     * @param usage
     * The usage. Usages are defined in <IOKit/hid/IOHIDUsageTables.h>.
     *
     * @param value
     * The value.
     *
     * @param options
     * Optional option bits. Options are defined in the IOHIDKeyboardEventOptions
     * enumerator in <IOKit/hid/IOHIDKeys.h>
     *
     * @param repeat
     * Default behavior for keyboard events is to repeat keys if the key has been
     * held down for a certain amount of time defined in system preferences. Pass
     * in false to not apply key repeat logic to this event.
     */
    virtual kern_return_t dispatchKeyboardEvent(uint64_t timeStamp,
                                                uint32_t usagePage,
                                                uint32_t usage,
                                                uint32_t value,
                                                IOOptionBits options,
                                                bool repeat = true) LOCALONLY;

    /*!
     * @function DispatchRelativePointerEvent
     *
     * @abstract
     * Dispatches a relative pointer event.
     *
     * @param timestamp
     * The timestamp of the event.
     *
     * @param dx
     * The delta X value.
     *
     * @param dy
     * The delta Y value.
     *
     * @param buttonState
     * Current state of the buttons, if any.
     *
     * @param options
     * Optional option bits.
     *
     * @param accelerate
     * Pointer events are subject to an acceleration algorithm. Pass in false
     * if you do not wish to have acceleration logic applied to the pointer event.
     */
    virtual kern_return_t dispatchRelativePointerEvent(uint64_t timeStamp,
                                                       IOFixed dx,
                                                       IOFixed dy,
                                                       uint32_t buttonState,
                                                       IOOptionBits options,
                                                       bool accelerate = true) LOCALONLY;
    
    /*!
     * @function DispatchAbsolutePointerEvent
     *
     * @abstract
     * Dispatches an absolute pointer event.
     *
     * @param timeStamp
     * The timestamp of the event.
     *
     * @param x
     * An X value between 0 and 1.
     *
     * @param dy
     * A Y value between 0 and 1.
     *
     * @param buttonState
     * Current state of the buttons, if any.
     *
     * @param options
     * Optional option bits.
     *
     * @param accelerate
     * Pointer events are subject to an acceleration algorithm. Pass in false
     * if you do not wish to have acceleration logic applied to the pointer event.
     */
    virtual kern_return_t dispatchAbsolutePointerEvent(uint64_t timeStamp,
                                                       IOFixed x,
                                                       IOFixed y,
                                                       uint32_t buttonState,
                                                       IOOptionBits options,
                                                       bool accelerate = true) LOCALONLY;
    
    /*!
     * @function DispatchRelativeScrollWheelEvent
     *
     * @abstract
     * Dispatches a relative scroll wheel event.
     *
     * @param timestamp
     * The timestamp of the event.
     *
     * @param dx
     * The delta X value.
     *
     * @param dy
     * The delta Y value.
     *
     * @param dz
     * The delta Z value.
     *
     * @param options
     * Optional option bits.
     *
     * @param accelerate
     * Scroll events are subject to an acceleration algorithm. Pass in false
     * if you do not wish to have acceleration logic applied to the scroll event.
     */
    virtual kern_return_t dispatchRelativeScrollWheelEvent(uint64_t timeStamp,
                                                           IOFixed dx,
                                                           IOFixed dy,
                                                           IOFixed dz,
                                                           IOOptionBits options,
                                                           bool accelerate = true) LOCALONLY;
    
    /*!
     * @function dispatchDigitizerStylusEvent
     *
     * @abstract
     * Dispatches a digitizer stylus event.
     *
     * @param timestamp
     * The timestamp of the event.
     *
     * @param stylusData
     * A struct containing the stylus data. See IOHIDDigtizerStructs.h for more 
     * info.
     */
    virtual kern_return_t dispatchDigitizerStylusEvent(
                                        uint64_t timeStamp,
                                        IOHIDDigitizerStylusData *stylusData) LOCALONLY;
    
    /*!
     * @function dispatchDigitizerTouchEvent
     *
     * @abstract
     * Dispatches a digitizer touch pad event.
     *
     * @param timestamp
     * The timestamp of the event.
     *
     * @param touchData
     * An array of touch data, where each struct represents a surface contact. 
     * See IOHIDDigtizerStructs.h for more info.
     *
     * @param touchDataCount
     * The touchData array count.
     */
    virtual kern_return_t dispatchDigitizerTouchEvent(
                                            uint64_t timeStamp,
                                            IOHIDDigitizerTouchData *touchData,
                                            uint32_t touchDataCount) LOCALONLY;

protected:

    /*!
     * @function SetLED
     *
     * @abstract
     * Sets an LED on the service.
     *
     * @param usage
     * The LED usage to set. LED usages can be found in
     * <IOKit/hid/IOHIDUsageTables.h>.
     *
     * @param on
     * Turn on or off the LED.
     */
    virtual void SetLED(uint32_t usage, bool on) LOCAL;
    
    /*!
     * @function dispatchEvent
     *
     * @abstract
     * Dispatches an event.
     *
     * @param event
     * The IOHIDEvent to dispatch.
     */
    virtual void dispatchEvent(IOHIDEvent *event) LOCALONLY;
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOHIDEventService IOHIDEventService.iig:48-249 */

#define IOHIDEventService__Start_ID            0xb7aeaf00ae079615ULL
#define IOHIDEventService_EventAvailable_ID            0xb6d3212b1068148aULL
#define IOHIDEventService_SetEventMemory_ID            0xed62c58e8d2f64e7ULL
#define IOHIDEventService__DispatchRelativeScrollWheelEvent_ID            0xe5902a0b51ed22ffULL
#define IOHIDEventService__DispatchAbsolutePointerEvent_ID            0xa89e9153d54a8eb1ULL
#define IOHIDEventService__DispatchRelativePointerEvent_ID            0xdfb3b21fdb3ea3b4ULL
#define IOHIDEventService__DispatchKeyboardEvent_ID            0xd8dc8ce69e15f7d3ULL
#define IOHIDEventService_SetLED_ID            0xfee475ac1384bab8ULL

#define IOHIDEventService__Start_Args \
        IOService * provider

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
    _Start(\
        IOService * provider,\
        OSDispatchMethod supermethod = NULL);\
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
    typedef kern_return_t (*_Start_Handler)(OSMetaClassBase * target, IOHIDEventService__Start_Args);\
    static kern_return_t\
    _Start_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        _Start_Handler func);\
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
    _Start_Impl(IOHIDEventService__Start_Args);\
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


#endif /* !__DOCUMENTATION__ */


/* IOHIDEventService.iig:301- */

#endif /* ! _HIDDRIVERKIT_IOHIDEVENTSERVICE_H */
