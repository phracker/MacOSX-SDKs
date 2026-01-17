/* iig(DriverKit-107.100.6) generated from IOUserNetworkRxSubmissionQueue.iig */

/* IOUserNetworkRxSubmissionQueue.iig:1-35 */
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

#ifndef _IOUSERNETWORKRXSUBMISSIONQUEUE_IIG
#define _IOUSERNETWORKRXSUBMISSIONQUEUE_IIG

#include <DriverKit/IODispatchQueue.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacketBufferPool.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacketQueue.h>  /* .iig include */

/* source class IOUserNetworkRxSubmissionQueue IOUserNetworkRxSubmissionQueue.iig:36-65 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
*/

class KERNEL IOUserNetworkRxSubmissionQueue : public IOUserNetworkPacketQueue
{
public:
    static kern_return_t
    Create(
        IOUserNetworkPacketBufferPool *     pool,
        OSObject *                          owner,
        uint32_t                            capacity,
        uint32_t                            queueId,
        IODispatchQueue *                   dispatchQueue,
        IOUserNetworkRxSubmissionQueue **   queue) LOCAL;

    virtual bool
    init() override;

    virtual void
    free() override;

    virtual kern_return_t
    SetEnable(bool isEnable) override LOCAL;
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOUserNetworkRxSubmissionQueue IOUserNetworkRxSubmissionQueue.iig:36-65 */

#define IOUserNetworkRxSubmissionQueue_Create_ID            0x9267f6a275193b57ULL

#define IOUserNetworkRxSubmissionQueue_Create_Args \
        IOUserNetworkPacketBufferPool * pool, \
        OSObject * owner, \
        uint32_t capacity, \
        uint32_t queueId, \
        IODispatchQueue * dispatchQueue, \
        IOUserNetworkRxSubmissionQueue ** queue

#define IOUserNetworkRxSubmissionQueue_SetEnable_Args \
        bool isEnable

#define IOUserNetworkRxSubmissionQueue_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOUserNetworkRxSubmissionQueue * self, const IORPC rpc);\
\
    static kern_return_t\
    Create(\
        IOUserNetworkPacketBufferPool * pool,\
        OSObject * owner,\
        uint32_t capacity,\
        uint32_t queueId,\
        IODispatchQueue * dispatchQueue,\
        IOUserNetworkRxSubmissionQueue ** queue);\
\
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    Create_Call(IOUserNetworkRxSubmissionQueue_Create_Args);\
\
    kern_return_t\
    SetEnable_Impl(IOUserNetworkPacketQueue_SetEnable_Args);\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*Create_Handler)(IOUserNetworkRxSubmissionQueue_Create_Args);\
    static kern_return_t\
    Create_Invoke(const IORPC rpc,\
        Create_Handler func);\
\


#define IOUserNetworkRxSubmissionQueue_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    Create_Impl(IOUserNetworkRxSubmissionQueue_Create_Args);\
\


#define IOUserNetworkRxSubmissionQueue_VirtualMethods \
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

extern OSMetaClass          * gIOUserNetworkRxSubmissionQueueMetaClass;
extern const OSClassLoadInformation IOUserNetworkRxSubmissionQueue_Class;

class IOUserNetworkRxSubmissionQueueMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOUserNetworkRxSubmissionQueueInterface : public OSInterface
{
public:
};

struct IOUserNetworkRxSubmissionQueue_IVars;
struct IOUserNetworkRxSubmissionQueue_LocalIVars;

class IOUserNetworkRxSubmissionQueue : public IOUserNetworkPacketQueue, public IOUserNetworkRxSubmissionQueueInterface
{
#if !KERNEL
    friend class IOUserNetworkRxSubmissionQueueMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOUserNetworkRxSubmissionQueue_IVars * ivars;
        IOUserNetworkRxSubmissionQueue_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = IOUserNetworkPacketQueue;

#if !KERNEL
    IOUserNetworkRxSubmissionQueue_Methods
    IOUserNetworkRxSubmissionQueue_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* IOUserNetworkRxSubmissionQueue.iig:67- */

#endif /* ! _IOUSERNETWORKRXSUBMISSIONQUEUE_IIG */
