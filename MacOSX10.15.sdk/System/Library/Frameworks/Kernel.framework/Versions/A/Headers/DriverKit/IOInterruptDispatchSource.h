/* iig(DriverKit-73.0.1) generated from IOInterruptDispatchSource.iig */

/* IOInterruptDispatchSource.iig:1-51 */
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

#ifndef _IOKIT_UIOINTERRUPTDISPATCHSOURCE_H
#define _IOKIT_UIOINTERRUPTDISPATCHSOURCE_H

#include <DriverKit/IODispatchQueue.h>  /* .iig include */
#include <DriverKit/IOService.h>  /* .iig include */

struct IOInterruptDispatchSourcePayload {
	uint64_t time;
	uint64_t count;
};

/*!
 * @class IOInterruptDispatchSource
 *
 * @abstract
 * IOInterruptDispatchSource delivers interrupts to a handler block on a dispatch queue.
 *
 * @discussion
 * A driver can run code in response to an interrupt from a device, specified as an IOService
 * and index. The code runs at normal thread level, but is notified with the mach_absolute_time
 * the primary interrupt fired. For IOPCIDevices, only MSI interrupt sources are supported.
 */
 
/* class IOInterruptDispatchSource IOInterruptDispatchSource.iig:52-115 */

#define IOInterruptDispatchSource_Create_ID            0xb6a948b1585fc259ULL
#define IOInterruptDispatchSource_SetHandler_ID            0xfcc79b0928501bb1ULL
#define IOInterruptDispatchSource_InterruptOccurred_ID            0xce0513291cfa1ee1ULL

#define IOInterruptDispatchSource_Create_Args \
        IOService * provider, \
        uint32_t index, \
        IODispatchQueue * queue, \
        IOInterruptDispatchSource ** source

#define IOInterruptDispatchSource_SetHandler_Args \
        OSAction * action

#define IOInterruptDispatchSource_SetEnableWithCompletion_Args \
        bool enable, \
        IODispatchSourceCancelHandler handler

#define IOInterruptDispatchSource_Cancel_Args \
        IODispatchSourceCancelHandler handler

#define IOInterruptDispatchSource_CheckForWork_Args \
        const IORPC rpc, \
        bool synchronous

#define IOInterruptDispatchSource_InterruptOccurred_Args \
        OSAction * action, \
        uint64_t count, \
        uint64_t time

#define IOInterruptDispatchSource_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOInterruptDispatchSource * self, const IORPC rpc);\
\
    static kern_return_t\
    Create(\
        IOService * provider,\
        uint32_t index,\
        IODispatchQueue * queue,\
        IOInterruptDispatchSource ** source);\
\
    kern_return_t\
    SetHandler(\
        OSAction * action,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    InterruptOccurred(\
        IORPC rpc,\
        OSAction * action,\
        uint64_t count,\
        uint64_t time,\
        OSDispatchMethod supermethod = NULL);\
\
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    Create_Call(IOInterruptDispatchSource_Create_Args);\
\
    kern_return_t\
    SetHandler_Impl(IOInterruptDispatchSource_SetHandler_Args);\
\
    kern_return_t\
    SetEnableWithCompletion_Impl(IODispatchSource_SetEnableWithCompletion_Args);\
\
    kern_return_t\
    Cancel_Impl(IODispatchSource_Cancel_Args);\
\
    kern_return_t\
    CheckForWork_Impl(IODispatchSource_CheckForWork_Args);\
\
    void\
    InterruptOccurred_Impl(IOInterruptDispatchSource_InterruptOccurred_Args);\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*Create_Handler)(IOInterruptDispatchSource_Create_Args);\
    static kern_return_t\
    Create_Invoke(const IORPC rpc,\
        Create_Handler func);\
\
    typedef kern_return_t (*SetHandler_Handler)(OSMetaClassBase * target, IOInterruptDispatchSource_SetHandler_Args);\
    static kern_return_t\
    SetHandler_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SetHandler_Handler func);\
\
    typedef void (*InterruptOccurred_Handler)(OSMetaClassBase * target, IOInterruptDispatchSource_InterruptOccurred_Args);\
    static kern_return_t\
    InterruptOccurred_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        InterruptOccurred_Handler func);\
\


#define IOInterruptDispatchSource_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    Create_Impl(IOInterruptDispatchSource_Create_Args);\
\


#define IOInterruptDispatchSource_VirtualMethods \
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



class IOInterruptDispatchSourceInterface : public OSInterface
{
public:
};

struct IOInterruptDispatchSource_IVars;
struct IOInterruptDispatchSource_LocalIVars;

class IOInterruptDispatchSource : public IODispatchSource, public IOInterruptDispatchSourceInterface
{
    OSDeclareDefaultStructorsWithDispatch(IOInterruptDispatchSource);


public:
    union
    {
        IOInterruptDispatchSource_IVars * ivars;
        IOInterruptDispatchSource_LocalIVars * lvars;
    };

    using super = IODispatchSource;


    IOInterruptDispatchSource_VirtualMethods
};
/* IOInterruptDispatchSource.iig:117- */

#endif /* ! _IOKIT_UIOINTERRUPTDISPATCHSOURCE_H */
