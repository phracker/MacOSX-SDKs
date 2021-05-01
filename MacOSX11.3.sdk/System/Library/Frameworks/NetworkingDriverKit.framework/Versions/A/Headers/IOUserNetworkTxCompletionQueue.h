/* iig(DriverKit-107.100.6) generated from IOUserNetworkTxCompletionQueue.iig */

/* IOUserNetworkTxCompletionQueue.iig:1-35 */
/*
 * Copyright (c) 2019-2020 Apple, Inc. All rights reserved.
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

#ifndef _IOUSERNETWORKTXCOMPLETIONQUEUE_IIG
#define _IOUSERNETWORKTXCOMPLETIONQUEUE_IIG

#include <DriverKit/IODispatchQueue.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacketBufferPool.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacketQueue.h>  /* .iig include */

/* source class IOUserNetworkTxCompletionQueue IOUserNetworkTxCompletionQueue.iig:36-65 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
*/

class KERNEL IOUserNetworkTxCompletionQueue : public IOUserNetworkPacketQueue
{
public:
    static kern_return_t
    Create(
        IOUserNetworkPacketBufferPool *         pool,
        OSObject *                          owner,
        uint32_t                            capacity,
        uint32_t                            queueId,
        IODispatchQueue *                   dispatchQueue,
        IOUserNetworkTxCompletionQueue **   queue) LOCAL;

    virtual bool
    init() override;

    virtual void
    free() override;

    virtual kern_return_t
    SetEnable(bool isEnable) override LOCAL;
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOUserNetworkTxCompletionQueue IOUserNetworkTxCompletionQueue.iig:36-65 */

#define IOUserNetworkTxCompletionQueue_Create_ID            0xdc494f5b33a98185ULL

#define IOUserNetworkTxCompletionQueue_Create_Args \
        IOUserNetworkPacketBufferPool * pool, \
        OSObject * owner, \
        uint32_t capacity, \
        uint32_t queueId, \
        IODispatchQueue * dispatchQueue, \
        IOUserNetworkTxCompletionQueue ** queue

#define IOUserNetworkTxCompletionQueue_SetEnable_Args \
        bool isEnable

#define IOUserNetworkTxCompletionQueue_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOUserNetworkTxCompletionQueue * self, const IORPC rpc);\
\
    static kern_return_t\
    Create(\
        IOUserNetworkPacketBufferPool * pool,\
        OSObject * owner,\
        uint32_t capacity,\
        uint32_t queueId,\
        IODispatchQueue * dispatchQueue,\
        IOUserNetworkTxCompletionQueue ** queue);\
\
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    Create_Call(IOUserNetworkTxCompletionQueue_Create_Args);\
\
    kern_return_t\
    SetEnable_Impl(IOUserNetworkPacketQueue_SetEnable_Args);\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*Create_Handler)(IOUserNetworkTxCompletionQueue_Create_Args);\
    static kern_return_t\
    Create_Invoke(const IORPC rpc,\
        Create_Handler func);\
\


#define IOUserNetworkTxCompletionQueue_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    Create_Impl(IOUserNetworkTxCompletionQueue_Create_Args);\
\


#define IOUserNetworkTxCompletionQueue_VirtualMethods \
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


#if !KERNEL

extern OSMetaClass          * gIOUserNetworkTxCompletionQueueMetaClass;
extern const OSClassLoadInformation IOUserNetworkTxCompletionQueue_Class;

class IOUserNetworkTxCompletionQueueMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOUserNetworkTxCompletionQueueInterface : public OSInterface
{
public:
};

struct IOUserNetworkTxCompletionQueue_IVars;
struct IOUserNetworkTxCompletionQueue_LocalIVars;

class IOUserNetworkTxCompletionQueue : public IOUserNetworkPacketQueue, public IOUserNetworkTxCompletionQueueInterface
{
#if !KERNEL
    friend class IOUserNetworkTxCompletionQueueMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOUserNetworkTxCompletionQueue_IVars * ivars;
        IOUserNetworkTxCompletionQueue_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = IOUserNetworkPacketQueue;

#if !KERNEL
    IOUserNetworkTxCompletionQueue_Methods
    IOUserNetworkTxCompletionQueue_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* IOUserNetworkTxCompletionQueue.iig:67- */

#endif /* ! _IOUSERNETWORKTXCOMPLETIONQUEUE_IIG */
