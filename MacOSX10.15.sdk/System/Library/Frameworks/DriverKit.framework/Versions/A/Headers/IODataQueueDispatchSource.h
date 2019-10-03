/* iig(DriverKit-73.0.1) generated from IODataQueueDispatchSource.iig */

/* IODataQueueDispatchSource.iig:1-37 */
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

#ifndef _IOKIT_UIODATAQUEUEDISPATCHSOURCE_H
#define _IOKIT_UIODATAQUEUEDISPATCHSOURCE_H

#include <DriverKit/IODispatchQueue.h>  /* .iig include */
#include <DriverKit/IOMemoryDescriptor.h>  /* .iig include */

typedef void (^IODataQueueClientEnqueueEntryBlock)(void *data, size_t dataSize);
typedef void (^IODataQueueClientDequeueEntryBlock)(const void *data, size_t dataSize);

/* class IODataQueueDispatchSource IODataQueueDispatchSource.iig:38-207 */

#define IODataQueueDispatchSource_Create_ID            0xe8544306a54d09e0ULL
#define IODataQueueDispatchSource_SetDataAvailableHandler_ID            0xd2c1d8cc6ec3a591ULL
#define IODataQueueDispatchSource_SetDataServicedHandler_ID            0xd0aac29bba67b644ULL
#define IODataQueueDispatchSource_CopyMemory_ID            0x9be617ec7d8cd728ULL
#define IODataQueueDispatchSource_CopyDataAvailableHandler_ID            0xc856b17471f65d99ULL
#define IODataQueueDispatchSource_CopyDataServicedHandler_ID            0xd8759c8da406b3fcULL
#define IODataQueueDispatchSource_DataAvailable_ID            0xf799c876baf566f3ULL
#define IODataQueueDispatchSource_DataServiced_ID            0x8daa79f78047d8d8ULL

#define IODataQueueDispatchSource_Create_Args \
        uint64_t queueByteCount, \
        IODispatchQueue * queue, \
        IODataQueueDispatchSource ** source

#define IODataQueueDispatchSource_SetDataAvailableHandler_Args \
        OSAction * action

#define IODataQueueDispatchSource_SetDataServicedHandler_Args \
        OSAction * action

#define IODataQueueDispatchSource_SetEnableWithCompletion_Args \
        bool enable, \
        IODispatchSourceCancelHandler handler

#define IODataQueueDispatchSource_Cancel_Args \
        IODispatchSourceCancelHandler handler

#define IODataQueueDispatchSource_CopyMemory_Args \
        IOMemoryDescriptor ** memory

#define IODataQueueDispatchSource_CopyDataAvailableHandler_Args \
        OSAction ** action

#define IODataQueueDispatchSource_CopyDataServicedHandler_Args \
        OSAction ** action

#define IODataQueueDispatchSource_CheckForWork_Args \
        const IORPC rpc, \
        bool synchronous

#define IODataQueueDispatchSource_DataAvailable_Args \
        OSAction * action

#define IODataQueueDispatchSource_DataServiced_Args \
        OSAction * action

#define IODataQueueDispatchSource_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IODataQueueDispatchSource * self, const IORPC rpc);\
\
    static kern_return_t\
    Create(\
        uint64_t queueByteCount,\
        IODispatchQueue * queue,\
        IODataQueueDispatchSource ** source);\
\
    kern_return_t\
    SetDataAvailableHandler(\
        OSAction * action,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    SetDataServicedHandler(\
        OSAction * action,\
        OSDispatchMethod supermethod = NULL);\
\
    bool\
    IsDataAvailable(\
);\
\
    kern_return_t\
    Peek(\
        IODataQueueClientDequeueEntryBlock callback);\
\
    kern_return_t\
    Dequeue(\
        IODataQueueClientDequeueEntryBlock callback);\
\
    kern_return_t\
    Enqueue(\
        uint32_t dataSize,\
        IODataQueueClientEnqueueEntryBlock callback);\
\
    kern_return_t\
    DequeueWithCoalesce(\
        bool * sendDataServiced,\
        IODataQueueClientDequeueEntryBlock callback);\
\
    kern_return_t\
    EnqueueWithCoalesce(\
        uint32_t dataSize,\
        bool * sendDataAvailable,\
        IODataQueueClientEnqueueEntryBlock callback);\
\
    void\
    SendDataServiced(\
);\
\
    void\
    SendDataAvailable(\
);\
\
    kern_return_t\
    CopyMemory(\
        IOMemoryDescriptor ** memory,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    CopyDataAvailableHandler(\
        OSAction ** action,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    CopyDataServicedHandler(\
        OSAction ** action,\
        OSDispatchMethod supermethod = NULL);\
\
    void\
    DataAvailable(\
        OSAction * action,\
        OSDispatchMethod supermethod = NULL);\
\
    void\
    DataServiced(\
        OSAction * action,\
        OSDispatchMethod supermethod = NULL);\
\
\
protected:\
    /* _Impl methods */\
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
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*Create_Handler)(IODataQueueDispatchSource_Create_Args);\
    static kern_return_t\
    Create_Invoke(const IORPC rpc,\
        Create_Handler func);\
\
    typedef kern_return_t (*SetDataAvailableHandler_Handler)(OSMetaClassBase * target, IODataQueueDispatchSource_SetDataAvailableHandler_Args);\
    static kern_return_t\
    SetDataAvailableHandler_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SetDataAvailableHandler_Handler func);\
\
    typedef kern_return_t (*SetDataServicedHandler_Handler)(OSMetaClassBase * target, IODataQueueDispatchSource_SetDataServicedHandler_Args);\
    static kern_return_t\
    SetDataServicedHandler_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SetDataServicedHandler_Handler func);\
\
    typedef kern_return_t (*CopyMemory_Handler)(OSMetaClassBase * target, IODataQueueDispatchSource_CopyMemory_Args);\
    static kern_return_t\
    CopyMemory_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        CopyMemory_Handler func);\
\
    typedef kern_return_t (*CopyDataAvailableHandler_Handler)(OSMetaClassBase * target, IODataQueueDispatchSource_CopyDataAvailableHandler_Args);\
    static kern_return_t\
    CopyDataAvailableHandler_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        CopyDataAvailableHandler_Handler func);\
\
    typedef kern_return_t (*CopyDataServicedHandler_Handler)(OSMetaClassBase * target, IODataQueueDispatchSource_CopyDataServicedHandler_Args);\
    static kern_return_t\
    CopyDataServicedHandler_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        CopyDataServicedHandler_Handler func);\
\
    typedef void (*DataAvailable_Handler)(OSMetaClassBase * target, IODataQueueDispatchSource_DataAvailable_Args);\
    static kern_return_t\
    DataAvailable_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        DataAvailable_Handler func);\
\
    typedef void (*DataServiced_Handler)(OSMetaClassBase * target, IODataQueueDispatchSource_DataServiced_Args);\
    static kern_return_t\
    DataServiced_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        DataServiced_Handler func);\
\


#define IODataQueueDispatchSource_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    Create_Impl(IODataQueueDispatchSource_Create_Args);\
\
    kern_return_t\
    SetDataAvailableHandler_Impl(IODataQueueDispatchSource_SetDataAvailableHandler_Args);\
\
    kern_return_t\
    SetDataServicedHandler_Impl(IODataQueueDispatchSource_SetDataServicedHandler_Args);\
\
    kern_return_t\
    CopyMemory_Impl(IODataQueueDispatchSource_CopyMemory_Args);\
\
    kern_return_t\
    CopyDataAvailableHandler_Impl(IODataQueueDispatchSource_CopyDataAvailableHandler_Args);\
\
    kern_return_t\
    CopyDataServicedHandler_Impl(IODataQueueDispatchSource_CopyDataServicedHandler_Args);\
\


#define IODataQueueDispatchSource_VirtualMethods \
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



extern OSMetaClass          * gIODataQueueDispatchSourceMetaClass;
extern const OSClassLoadInformation IODataQueueDispatchSource_Class;

class IODataQueueDispatchSourceMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};


class IODataQueueDispatchSourceInterface : public OSInterface
{
public:
};

struct IODataQueueDispatchSource_IVars;
struct IODataQueueDispatchSource_LocalIVars;

class IODataQueueDispatchSource : public IODispatchSource, public IODataQueueDispatchSourceInterface
{

    friend class IODataQueueDispatchSourceMetaClass;

public:
    union
    {
        IODataQueueDispatchSource_IVars * ivars;
        IODataQueueDispatchSource_LocalIVars * lvars;
    };
    virtual const OSMetaClass *
    getMetaClass() const APPLE_KEXT_OVERRIDE { return OSTypeID(IODataQueueDispatchSource); };

    using super = IODispatchSource;

    IODataQueueDispatchSource_Methods

    IODataQueueDispatchSource_VirtualMethods
};
/* IODataQueueDispatchSource.iig:209- */

#endif /* ! _IOKIT_UIODATAQUEUEDISPATCHSOURCE_H */
