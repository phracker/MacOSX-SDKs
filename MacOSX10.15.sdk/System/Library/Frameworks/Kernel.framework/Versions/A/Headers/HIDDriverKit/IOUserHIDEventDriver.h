/* iig(DriverKit-73.0.1) generated from IOUserHIDEventDriver.iig */

/* IOUserHIDEventDriver.iig:1-37 */
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

#ifndef _HIDDRIVERKIT_IOUSERHIDEVENTDRIVER_H
#define _HIDDRIVERKIT_IOUSERHIDEVENTDRIVER_H

#include <HIDDriverKit/IOUserHIDEventService.h>  /* .iig include */

class IOHIDElement;
class IOHIDEvent;
class IOHIDDigitizerCollection;

/* class IOUserHIDEventDriver IOUserHIDEventDriver.iig:38-310 */


#define IOUserHIDEventDriver_Start_Args \
        IOService * provider

#define IOUserHIDEventDriver_SetLED_Args \
        uint32_t usage, \
        bool on

#define IOUserHIDEventDriver_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOUserHIDEventDriver * self, const IORPC rpc);\
\
    void\
    setAccelerationProperties(\
);\
\
    void\
    setSurfaceDimensions(\
);\
\
    IOHIDEvent *\
    createEventForDigitizerCollection(\
        IOHIDDigitizerCollection * collection,\
        uint64_t timestamp,\
        uint32_t reportID);\
\
\
protected:\
    /* _Impl methods */\
\
    kern_return_t\
    Start_Impl(IOService_Start_Args);\
\
    void\
    SetLED_Impl(IOHIDEventService_SetLED_Args);\
\
\
public:\
    /* _Invoke methods */\
\


#define IOUserHIDEventDriver_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define IOUserHIDEventDriver_VirtualMethods \
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
    virtual void\
    handleReport(\
        uint64_t timestamp,\
        uint8_t * report,\
        uint32_t reportLength,\
        IOHIDReportType type,\
        uint32_t reportID) APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    parseElements(\
        OSArray * elements) APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    parseKeyboardElement(\
        IOHIDElement * element) APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    parsePointerElement(\
        IOHIDElement * element) APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    parseScrollElement(\
        IOHIDElement * element) APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    parseLEDElement(\
        IOHIDElement * element) APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    parseDigitizerElement(\
        IOHIDElement * element) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    handleKeyboardReport(\
        uint64_t timestamp,\
        uint32_t reportID) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    handleRelativePointerReport(\
        uint64_t timestamp,\
        uint32_t reportID) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    handleAbsolutePointerReport(\
        uint64_t timestamp,\
        uint32_t reportID) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    handleScrollReport(\
        uint64_t timestamp,\
        uint32_t reportID) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    handleDigitizerReport(\
        uint64_t timestamp,\
        uint32_t reportID) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gIOUserHIDEventDriverMetaClass;
extern const OSClassLoadInformation IOUserHIDEventDriver_Class;

class IOUserHIDEventDriverMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOUserHIDEventDriverInterface : public OSInterface
{
public:
    virtual bool
    parseElements(OSArray * elements) = 0;

    virtual bool
    parseKeyboardElement(IOHIDElement * element) = 0;

    virtual bool
    parsePointerElement(IOHIDElement * element) = 0;

    virtual bool
    parseScrollElement(IOHIDElement * element) = 0;

    virtual bool
    parseLEDElement(IOHIDElement * element) = 0;

    virtual bool
    parseDigitizerElement(IOHIDElement * element) = 0;

    virtual void
    handleKeyboardReport(uint64_t timestamp,
        uint32_t reportID) = 0;

    virtual void
    handleRelativePointerReport(uint64_t timestamp,
        uint32_t reportID) = 0;

    virtual void
    handleAbsolutePointerReport(uint64_t timestamp,
        uint32_t reportID) = 0;

    virtual void
    handleScrollReport(uint64_t timestamp,
        uint32_t reportID) = 0;

    virtual void
    handleDigitizerReport(uint64_t timestamp,
        uint32_t reportID) = 0;

};

struct IOUserHIDEventDriver_IVars;
struct IOUserHIDEventDriver_LocalIVars;

class IOUserHIDEventDriver : public IOUserHIDEventService, public IOUserHIDEventDriverInterface
{
#if !KERNEL
    friend class IOUserHIDEventDriverMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOUserHIDEventDriver_IVars * ivars;
        IOUserHIDEventDriver_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = IOUserHIDEventService;

#if !KERNEL
    IOUserHIDEventDriver_Methods
    IOUserHIDEventDriver_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */

/* IOUserHIDEventDriver.iig:312- */

#endif /* _HIDDRIVERKIT_IOUSERHIDEVENTDRIVER_H */
