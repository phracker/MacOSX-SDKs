/* iig(DriverKit-107.100.6) generated from IOUserNetworkTxSubmissionQueue.iig */

/* IOUserNetworkTxSubmissionQueue.iig:1-35 */
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

#ifndef _IOUSERNETWORKTXSUBMISSIONQUEUE_IIG
#define _IOUSERNETWORKTXSUBMISSIONQUEUE_IIG

#include <DriverKit/IODispatchQueue.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacketBufferPool.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacketQueue.h>  /* .iig include */

/* source class IOUserNetworkTxSubmissionQueue IOUserNetworkTxSubmissionQueue.iig:36-65 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
*/

class KERNEL IOUserNetworkTxSubmissionQueue : public IOUserNetworkPacketQueue
{
public:
    static kern_return_t
    Create(
        IOUserNetworkPacketBufferPool *         pool,
        OSObject *                          owner,
        uint32_t                            capacity,
        uint32_t                            queueId,
        IODispatchQueue *                   dispatchQueue,
        IOUserNetworkTxSubmissionQueue **   queue) LOCAL;

    virtual bool
    init() override;

    virtual void
    free() override;

    virtual kern_return_t
    SetEnable(bool isEnable) override LOCAL;
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOUserNetworkTxSubmissionQueue IOUserNetworkTxSubmissionQueue.iig:36-65 */

#define IOUserNetworkTxSubmissionQueue_Create_ID            0xc2859ee3e17376d3ULL

#define IOUserNetworkTxSubmissionQueue_Create_Args \
        IOUserNetworkPacketBufferPool * pool, \
        OSObject * owner, \
        uint32_t capacity, \
        uint32_t queueId, \
        IODispatchQueue * dispatchQueue, \
        IOUserNetworkTxSubmissionQueue ** queue

#define IOUserNetworkTxSubmissionQueue_SetEnable_Args \
        bool isEnable

#define IOUserNetworkTxSubmissionQueue_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOUserNetworkTxSubmissionQueue * self, const IORPC rpc);\
\
    static kern_return_t\
    Create(\
        IOUserNetworkPacketBufferPool * pool,\
        OSObject * owner,\
        uint32_t capacity,\
        uint32_t queueId,\
        IODispatchQueue * dispatchQueue,\
        IOUserNetworkTxSubmissionQueue ** queue);\
\
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    Create_Call(IOUserNetworkTxSubmissionQueue_Create_Args);\
\
    kern_return_t\
    SetEnable_Impl(IOUserNetworkPacketQueue_SetEnable_Args);\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*Create_Handler)(IOUserNetworkTxSubmissionQueue_Create_Args);\
    static kern_return_t\
    Create_Invoke(const IORPC rpc,\
        Create_Handler func);\
\


#define IOUserNetworkTxSubmissionQueue_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    Create_Impl(IOUserNetworkTxSubmissionQueue_Create_Args);\
\


#define IOUserNetworkTxSubmissionQueue_VirtualMethods \
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

extern OSMetaClass          * gIOUserNetworkTxSubmissionQueueMetaClass;
extern const OSClassLoadInformation IOUserNetworkTxSubmissionQueue_Class;

class IOUserNetworkTxSubmissionQueueMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOUserNetworkTxSubmissionQueueInterface : public OSInterface
{
public:
};

struct IOUserNetworkTxSubmissionQueue_IVars;
struct IOUserNetworkTxSubmissionQueue_LocalIVars;

class IOUserNetworkTxSubmissionQueue : public IOUserNetworkPacketQueue, public IOUserNetworkTxSubmissionQueueInterface
{
#if !KERNEL
    friend class IOUserNetworkTxSubmissionQueueMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOUserNetworkTxSubmissionQueue_IVars * ivars;
        IOUserNetworkTxSubmissionQueue_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = IOUserNetworkPacketQueue;

#if !KERNEL
    IOUserNetworkTxSubmissionQueue_Methods
    IOUserNetworkTxSubmissionQueue_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* IOUserNetworkTxSubmissionQueue.iig:67- */

#endif /* ! _IOUSERNETWORKTXSUBMISSIONQUEUE_IIG */
