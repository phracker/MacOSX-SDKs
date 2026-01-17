/* iig(DriverKit-107.100.6) generated from IOUserNetworkPacketBufferPool.iig */

/* IOUserNetworkPacketBufferPool.iig:1-59 */
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

#ifndef _IOUSERNETWORKPACKETBUFFERPOOL_IIG
#define _IOUSERNETWORKPACKETBUFFERPOOL_IIG

#include <DriverKit/IOMemoryDescriptor.h>  /* .iig include */
#include <DriverKit/IODMACommand.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacket.h>  /* .iig include */

/*! @enum PoolFlags
    @abstract Flags for PoolOptions::poolFlags.
    @constant PoolFlagSingleMemorySegment The pool will be constucted with single memory segment of buffers.
    @constant PoolFlagPersistentMemory The pool memory will be persistently wired.
*/
enum IOUserNetworkPacketBufferPoolFlags {
    PoolFlagSingleMemorySegment = 0x00000002,
    PoolFlagPersistentMemory    = 0x00000004,
    PoolFlagMapToDext           = 0x10000000,
    PoolFlagMapToDevice         = 0x20000000,
    PoolFlagMask = PoolFlagSingleMemorySegment | PoolFlagPersistentMemory | PoolFlagMapToDext | PoolFlagMapToDevice,
};

struct IOUserNetworkPacketBufferPoolOptions {
    uint32_t packetCount;
    uint32_t bufferCount;
    uint32_t bufferSize;
    uint32_t maxBuffersPerPacket;
    uint32_t memorySegmentSize;
    uint32_t poolFlags;
    IODMACommandSpecification dmaSpecification;
    uint32_t _resv[16];
};

/* source class IOUserNetworkPacketBufferPool IOUserNetworkPacketBufferPool.iig:60-114 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
*/

class KERNEL IOUserNetworkPacketBufferPool : public OSObject
{
public:
    virtual bool
    init() override;

    virtual void
    free() override;

    /** @deprecated, use CreateWithOptions instead */
    static kern_return_t
    Create(
        OSObject * poolOwner,
        const char name[1024],
        uint32_t packetCount,
        uint32_t bufferCount,
        uint32_t bufferSize,
        IOUserNetworkPacketBufferPool ** pool) LOCALONLY;

    static kern_return_t
    CreateWithOptions(
        IOService * device,
        const char name[1024],
        const IOUserNetworkPacketBufferPoolOptions * options,
        IOUserNetworkPacketBufferPool ** pool) LOCALONLY;

    virtual kern_return_t
    DeallocatePacket(
        IOUserNetworkPacket * packet) LOCALONLY;

    virtual kern_return_t
    DeallocatePackets(
        IOUserNetworkPacket ** packets,
        uint32_t packetsCount) LOCALONLY;

    virtual kern_return_t
    CopyMemoryDescriptor(
        IOMemoryDescriptor ** memory);

    virtual kern_return_t
    GetPacketCount(uint32_t * count) LOCAL;

    virtual kern_return_t
    GetBufferCount(uint32_t * count) LOCAL;
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOUserNetworkPacketBufferPool IOUserNetworkPacketBufferPool.iig:60-114 */

#define IOUserNetworkPacketBufferPool__DeallocatePacket_ID            0x96e008792b9286b5ULL
#define IOUserNetworkPacketBufferPool__CopyPacketWithIndex_ID            0xf0165b114d39c9f8ULL
#define IOUserNetworkPacketBufferPool__Create_ID            0x8e2ec93abf72f427ULL
#define IOUserNetworkPacketBufferPool_CopyMemoryDescriptor_ID            0xc9a7388ad62f5737ULL
#define IOUserNetworkPacketBufferPool_GetPacketCount_ID            0xf4aae455ba1082ebULL
#define IOUserNetworkPacketBufferPool_GetBufferCount_ID            0xe922d59c37bf3bbeULL

#define IOUserNetworkPacketBufferPool__DeallocatePacket_Args \
        uint32_t packetIndex

#define IOUserNetworkPacketBufferPool__CopyPacketWithIndex_Args \
        uint32_t index, \
        IOUserNetworkPacket ** packet

#define IOUserNetworkPacketBufferPool__Create_Args \
        IOService * device, \
        const char * name, \
        const IOUserNetworkPacketBufferPoolOptions * options, \
        IOUserNetworkPacketBufferPool ** pool

#define IOUserNetworkPacketBufferPool_CopyMemoryDescriptor_Args \
        IOMemoryDescriptor ** memory

#define IOUserNetworkPacketBufferPool_GetPacketCount_Args \
        uint32_t * count

#define IOUserNetworkPacketBufferPool_GetBufferCount_Args \
        uint32_t * count

#define IOUserNetworkPacketBufferPool_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOUserNetworkPacketBufferPool * self, const IORPC rpc);\
\
    kern_return_t\
    _DeallocatePacket(\
        uint32_t packetIndex,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    _CopyPacketWithIndex(\
        uint32_t index,\
        IOUserNetworkPacket ** packet,\
        OSDispatchMethod supermethod = NULL);\
\
    static kern_return_t\
    _Create(\
        IOService * device,\
        const char * name,\
        const IOUserNetworkPacketBufferPoolOptions * options,\
        IOUserNetworkPacketBufferPool ** pool);\
\
    static kern_return_t\
    Create(\
        OSObject * poolOwner,\
        const char * name,\
        uint32_t packetCount,\
        uint32_t bufferCount,\
        uint32_t bufferSize,\
        IOUserNetworkPacketBufferPool ** pool);\
\
    static kern_return_t\
    CreateWithOptions(\
        IOService * device,\
        const char * name,\
        const IOUserNetworkPacketBufferPoolOptions * options,\
        IOUserNetworkPacketBufferPool ** pool);\
\
    kern_return_t\
    CopyMemoryDescriptor(\
        IOMemoryDescriptor ** memory,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    GetPacketCount(\
        uint32_t * count,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    GetBufferCount(\
        uint32_t * count,\
        OSDispatchMethod supermethod = NULL);\
\
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    _Create_Call(IOUserNetworkPacketBufferPool__Create_Args);\
\
    kern_return_t\
    GetPacketCount_Impl(IOUserNetworkPacketBufferPool_GetPacketCount_Args);\
\
    kern_return_t\
    GetBufferCount_Impl(IOUserNetworkPacketBufferPool_GetBufferCount_Args);\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*_DeallocatePacket_Handler)(OSMetaClassBase * target, IOUserNetworkPacketBufferPool__DeallocatePacket_Args);\
    static kern_return_t\
    _DeallocatePacket_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        _DeallocatePacket_Handler func);\
\
    typedef kern_return_t (*_CopyPacketWithIndex_Handler)(OSMetaClassBase * target, IOUserNetworkPacketBufferPool__CopyPacketWithIndex_Args);\
    static kern_return_t\
    _CopyPacketWithIndex_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        _CopyPacketWithIndex_Handler func);\
\
    typedef kern_return_t (*_Create_Handler)(IOUserNetworkPacketBufferPool__Create_Args);\
    static kern_return_t\
    _Create_Invoke(const IORPC rpc,\
        _Create_Handler func);\
\
    typedef kern_return_t (*CopyMemoryDescriptor_Handler)(OSMetaClassBase * target, IOUserNetworkPacketBufferPool_CopyMemoryDescriptor_Args);\
    static kern_return_t\
    CopyMemoryDescriptor_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        CopyMemoryDescriptor_Handler func);\
\
    typedef kern_return_t (*GetPacketCount_Handler)(OSMetaClassBase * target, IOUserNetworkPacketBufferPool_GetPacketCount_Args);\
    static kern_return_t\
    GetPacketCount_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        GetPacketCount_Handler func);\
\
    typedef kern_return_t (*GetBufferCount_Handler)(OSMetaClassBase * target, IOUserNetworkPacketBufferPool_GetBufferCount_Args);\
    static kern_return_t\
    GetBufferCount_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        GetBufferCount_Handler func);\
\


#define IOUserNetworkPacketBufferPool_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    kern_return_t\
    _DeallocatePacket_Impl(IOUserNetworkPacketBufferPool__DeallocatePacket_Args);\
\
    kern_return_t\
    _CopyPacketWithIndex_Impl(IOUserNetworkPacketBufferPool__CopyPacketWithIndex_Args);\
\
    static kern_return_t\
    _Create_Impl(IOUserNetworkPacketBufferPool__Create_Args);\
\
    kern_return_t\
    CopyMemoryDescriptor_Impl(IOUserNetworkPacketBufferPool_CopyMemoryDescriptor_Args);\
\


#define IOUserNetworkPacketBufferPool_VirtualMethods \
\
public:\
\
    virtual kern_return_t\
    GetPacketWithState(\
        const IOUserNetworkPacketState * state,\
        IOUserNetworkPacket ** packet) APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    init(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    free(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    DeallocatePacket(\
        IOUserNetworkPacket * packet) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    DeallocatePackets(\
        IOUserNetworkPacket ** packets,\
        uint32_t packetsCount) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gIOUserNetworkPacketBufferPoolMetaClass;
extern const OSClassLoadInformation IOUserNetworkPacketBufferPool_Class;

class IOUserNetworkPacketBufferPoolMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOUserNetworkPacketBufferPoolInterface : public OSInterface
{
public:
    virtual kern_return_t
    GetPacketWithState(const IOUserNetworkPacketState * state,
        IOUserNetworkPacket ** packet) = 0;

    virtual kern_return_t
    DeallocatePacket(IOUserNetworkPacket * packet) = 0;

    virtual kern_return_t
    DeallocatePackets(IOUserNetworkPacket ** packets,
        uint32_t packetsCount) = 0;

};

struct IOUserNetworkPacketBufferPool_IVars;
struct IOUserNetworkPacketBufferPool_LocalIVars;

class IOUserNetworkPacketBufferPool : public OSObject, public IOUserNetworkPacketBufferPoolInterface
{
#if !KERNEL
    friend class IOUserNetworkPacketBufferPoolMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOUserNetworkPacketBufferPool_IVars * ivars;
        IOUserNetworkPacketBufferPool_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = OSObject;

#if !KERNEL
    IOUserNetworkPacketBufferPool_Methods
    IOUserNetworkPacketBufferPool_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */


/* IOUserNetworkPacketBufferPool.iig:140- */

#endif /* ! _IOUSERNETWORKPACKETBUFFERPOOL_IIG */
