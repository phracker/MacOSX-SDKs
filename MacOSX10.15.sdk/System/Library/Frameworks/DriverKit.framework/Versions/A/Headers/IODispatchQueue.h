/* iig(DriverKit-73.0.1) generated from IODispatchQueue.iig */

/* IODispatchQueue.iig:1-52 */
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

#ifndef _IOKIT_UIODISPATCHQUEUE_H
#define _IOKIT_UIODISPATCHQUEUE_H

#include <DriverKit/OSObject.h>  /* .iig include */
#include <DriverKit/OSAction.h>  /* .iig include */
#include <DriverKit/IODispatchSource.h>  /* .iig include */

typedef int (*IODispatchLogFunction)(const char *format, ...);
typedef void (^IODispatchBlock)(void);
typedef void (*IODispatchFunction)(void * context);
typedef void (^IODispatchQueueCancelHandler)(void);


/*!
 * @class IODispatchQueue
 *
 * @abstract
 * IODispatchQueue provides a queue for ordered execution of blocks.
 *
 * @discussion
 * All blocks submitted to dispatch queues are dequeued in FIFO order.
 * By default the queue is serial and will execute one block at a time.
 */

/* class IODispatchQueue IODispatchQueue.iig:53-134 */

#define IODispatchQueue_SetPort_ID            0xc437e970b5609767ULL
#define IODispatchQueue_Create_ID            0xac000428df2a91d0ULL

#define IODispatchQueue_SetPort_Args \
        mach_port_t port

#define IODispatchQueue_Create_Args \
        const char * name, \
        uint64_t options, \
        uint64_t priority, \
        IODispatchQueue ** queue

#define IODispatchQueue_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IODispatchQueue * self, const IORPC rpc);\
\
    kern_return_t\
    SetPort(\
        mach_port_t port,\
        OSDispatchMethod supermethod = NULL);\
\
    static kern_return_t\
    Create(\
        const IODispatchQueueName name,\
        uint64_t options,\
        uint64_t priority,\
        IODispatchQueue ** queue);\
\
    bool\
    OnQueue(\
);\
\
    const char *\
    GetName(\
);\
\
    kern_return_t\
    Cancel(\
        IODispatchQueueCancelHandler handler);\
\
    void\
    DispatchAsync(\
        IODispatchBlock block);\
\
    void\
    DispatchAsync_f(\
        void * context,\
        IODispatchFunction function);\
\
    void\
    DispatchSync(\
        IODispatchBlock block);\
\
    void\
    DispatchSync_f(\
        void * context,\
        IODispatchFunction function);\
\
    static void\
    Log(\
        const char * message,\
        IODispatchLogFunction output);\
\
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    Create_Call(IODispatchQueue_Create_Args);\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*SetPort_Handler)(OSMetaClassBase * target, IODispatchQueue_SetPort_Args);\
    static kern_return_t\
    SetPort_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SetPort_Handler func);\
\
    typedef kern_return_t (*Create_Handler)(IODispatchQueue_Create_Args);\
    static kern_return_t\
    Create_Invoke(const IORPC rpc,\
        Create_Handler func);\
\


#define IODispatchQueue_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    kern_return_t\
    SetPort_Impl(IODispatchQueue_SetPort_Args);\
\
    static kern_return_t\
    Create_Impl(IODispatchQueue_Create_Args);\
\


#define IODispatchQueue_VirtualMethods \
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



extern OSMetaClass          * gIODispatchQueueMetaClass;
extern const OSClassLoadInformation IODispatchQueue_Class;

class IODispatchQueueMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};


class IODispatchQueueInterface : public OSInterface
{
public:
};

struct IODispatchQueue_IVars;
struct IODispatchQueue_LocalIVars;

class IODispatchQueue : public OSObject, public IODispatchQueueInterface
{

    friend class IODispatchQueueMetaClass;

public:
    union
    {
        IODispatchQueue_IVars * ivars;
        IODispatchQueue_LocalIVars * lvars;
    };
    virtual const OSMetaClass *
    getMetaClass() const APPLE_KEXT_OVERRIDE { return OSTypeID(IODispatchQueue); };

    using super = OSObject;

    IODispatchQueue_Methods

    IODispatchQueue_VirtualMethods
};
/* IODispatchQueue.iig:136-137 */

#if DRIVERKIT_PRIVATE
/* IODispatchQueue.iig:144- */
#endif

#endif /* ! _IOKIT_UIODISPATCH_H */
