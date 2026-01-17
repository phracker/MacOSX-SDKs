/* iig(DriverKit-107.100.6) generated from IOUserNetworkPacket.iig */

/* IOUserNetworkPacket.iig:1-55 */
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

#ifndef _IOUSERNETWORKPACKET_IIG
#define _IOUSERNETWORKPACKET_IIG

#include <DriverKit/OSObject.h>  /* .iig include */

class IOUserNetworkPacketQueue;
class IOUserNetworkPacketBufferPool;

typedef uint32_t IOUserNetworkPacketDirection;
enum {
    kIOUserNetworkPacketDirectionNone = 0x00000000,
    kIOUserNetworkPacketDirectionTx   = 0x00000001,
    kIOUserNetworkPacketDirectionRx   = 0x00000002
};

struct IOUserNetworkPacketState {
    uint64_t memoryOffset;
    uint64_t dataDKVA;
    uint64_t dataIOVA;
    uint32_t packetIndex;
    uint32_t dataLength;
    uint16_t dataOffset;
    uint8_t  direction;
    uint8_t  linkHeaderLength;
    uint8_t  __reserved[4];
} __attribute__((packed, aligned(8)));

/* source class IOUserNetworkPacket IOUserNetworkPacket.iig:56-142 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
*/

class KERNEL IOUserNetworkPacket : public OSObject
{
public:
    virtual bool
    init() override;

    virtual void
    free() override;

    /** @deprecated, use  setDataLength instead */
    virtual kern_return_t
    SetDataLength(uint32_t length) LOCALONLY;

    /** @deprecated use  getDataLength instead */
    virtual kern_return_t
    GetDataLength(uint32_t * length) const LOCALONLY;

    /** @deprecated use  setDataOffset instead */
    virtual kern_return_t
    SetDataOffset(uint16_t offset) LOCALONLY;

    /** @deprecated use  getDataOffset instead */
    virtual kern_return_t
    GetDataOffset(uint16_t * offset) const LOCALONLY;

    /** @deprecated */
    virtual kern_return_t
    SetHeadroom(uint8_t headroom) LOCALONLY;

    /** @deprecated */
    virtual kern_return_t
    GetHeadroom(uint8_t * headroom) const LOCALONLY;

    /** @deprecated*/
    virtual kern_return_t
    SetLinkHeaderLength(uint8_t length) LOCALONLY;

    /** @deprecated */
    virtual kern_return_t
    GetLinkHeaderLength(uint8_t * length) const LOCALONLY;

    /** @deprecated use getMemorySegmentOffset instead */
    virtual kern_return_t
    GetMemorySegmentOffset(uint64_t * offset) const LOCALONLY;

    /** @deprecated use getPacketBufferPool instead */
    virtual kern_return_t
    GetPacketBufferPool(
        IOUserNetworkPacketBufferPool ** pool) const LOCALONLY;

    virtual uint64_t
    getDataVirtualAddress() const LOCALONLY;

    virtual uint64_t
    getDataIOVirtualAddress() const LOCALONLY;

    virtual IOUserNetworkPacketBufferPool *
    getPacketBufferPool() const LOCALONLY;

    virtual uint64_t
    getMemorySegmentOffset() const LOCALONLY;

    virtual kern_return_t
    setDataLength(uint32_t length) LOCALONLY final;

    virtual uint32_t
    getDataLength() const LOCALONLY final;

    virtual kern_return_t
    setDataOffset(uint16_t offset) LOCALONLY final;

    virtual uint16_t
    getDataOffset() const LOCALONLY final;

    virtual kern_return_t
    setDataOffsetAndLength(
        uint16_t offset,
        uint32_t length) LOCALONLY final;
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOUserNetworkPacket IOUserNetworkPacket.iig:56-142 */


#define IOUserNetworkPacket_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOUserNetworkPacket * self, const IORPC rpc);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define IOUserNetworkPacket_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define IOUserNetworkPacket_VirtualMethods \
\
public:\
\
    virtual kern_return_t\
    _Print(\
        uint64_t mappedPoolAddress) const APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    _GetPacketIndex(\
        uint32_t * index) const APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    _SetPacketIndex(\
        uint32_t index) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    _SetPacketBufferPool(\
        IOUserNetworkPacketBufferPool * pool) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    _CompleteWithQueue(\
        IOUserNetworkPacketQueue * queue,\
        IOUserNetworkPacketDirection direction,\
        IOUserNetworkPacketState * state) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    _PrepareWithQueue(\
        IOUserNetworkPacketQueue * queue,\
        IOUserNetworkPacketDirection direction,\
        const IOUserNetworkPacketState * state) APPLE_KEXT_OVERRIDE;\
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
    SetDataLength(\
        uint32_t length) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    GetDataLength(\
        uint32_t * length) const APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    SetDataOffset(\
        uint16_t offset) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    GetDataOffset(\
        uint16_t * offset) const APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    SetHeadroom(\
        uint8_t headroom) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    GetHeadroom(\
        uint8_t * headroom) const APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    SetLinkHeaderLength(\
        uint8_t length) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    GetLinkHeaderLength(\
        uint8_t * length) const APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    GetMemorySegmentOffset(\
        uint64_t * offset) const APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    GetPacketBufferPool(\
        IOUserNetworkPacketBufferPool ** pool) const APPLE_KEXT_OVERRIDE;\
\
    virtual uint64_t\
    getDataVirtualAddress(\
) const APPLE_KEXT_OVERRIDE;\
\
    virtual uint64_t\
    getDataIOVirtualAddress(\
) const APPLE_KEXT_OVERRIDE;\
\
    virtual IOUserNetworkPacketBufferPool *\
    getPacketBufferPool(\
) const APPLE_KEXT_OVERRIDE;\
\
    virtual uint64_t\
    getMemorySegmentOffset(\
) const APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    setDataLength(\
        uint32_t length) APPLE_KEXT_OVERRIDE;\
\
    virtual uint32_t\
    getDataLength(\
) const APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    setDataOffset(\
        uint16_t offset) APPLE_KEXT_OVERRIDE;\
\
    virtual uint16_t\
    getDataOffset(\
) const APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    setDataOffsetAndLength(\
        uint16_t offset,\
        uint32_t length) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gIOUserNetworkPacketMetaClass;
extern const OSClassLoadInformation IOUserNetworkPacket_Class;

class IOUserNetworkPacketMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOUserNetworkPacketInterface : public OSInterface
{
public:
    virtual kern_return_t
    _Print(uint64_t mappedPoolAddress) const = 0;

    virtual kern_return_t
    _GetPacketIndex(uint32_t * index) const = 0;

    virtual kern_return_t
    _SetPacketIndex(uint32_t index) = 0;

    virtual kern_return_t
    _SetPacketBufferPool(IOUserNetworkPacketBufferPool * pool) = 0;

    virtual kern_return_t
    _CompleteWithQueue(IOUserNetworkPacketQueue * queue,
        IOUserNetworkPacketDirection direction,
        IOUserNetworkPacketState * state) = 0;

    virtual kern_return_t
    _PrepareWithQueue(IOUserNetworkPacketQueue * queue,
        IOUserNetworkPacketDirection direction,
        const IOUserNetworkPacketState * state) = 0;

    virtual kern_return_t
    SetDataLength(uint32_t length) = 0;

    virtual kern_return_t
    GetDataLength(uint32_t * length) const = 0;

    virtual kern_return_t
    SetDataOffset(uint16_t offset) = 0;

    virtual kern_return_t
    GetDataOffset(uint16_t * offset) const = 0;

    virtual kern_return_t
    SetHeadroom(uint8_t headroom) = 0;

    virtual kern_return_t
    GetHeadroom(uint8_t * headroom) const = 0;

    virtual kern_return_t
    SetLinkHeaderLength(uint8_t length) = 0;

    virtual kern_return_t
    GetLinkHeaderLength(uint8_t * length) const = 0;

    virtual kern_return_t
    GetMemorySegmentOffset(uint64_t * offset) const = 0;

    virtual kern_return_t
    GetPacketBufferPool(IOUserNetworkPacketBufferPool ** pool) const = 0;

    virtual uint64_t
    getDataVirtualAddress() const = 0;

    virtual uint64_t
    getDataIOVirtualAddress() const = 0;

    virtual IOUserNetworkPacketBufferPool *
    getPacketBufferPool() const = 0;

    virtual uint64_t
    getMemorySegmentOffset() const = 0;

    virtual kern_return_t
    setDataLength(uint32_t length) = 0;

    virtual uint32_t
    getDataLength() const = 0;

    virtual kern_return_t
    setDataOffset(uint16_t offset) = 0;

    virtual uint16_t
    getDataOffset() const = 0;

    virtual kern_return_t
    setDataOffsetAndLength(uint16_t offset,
        uint32_t length) = 0;

};

struct IOUserNetworkPacket_IVars;
struct IOUserNetworkPacket_LocalIVars;

class IOUserNetworkPacket : public OSObject, public IOUserNetworkPacketInterface
{
#if !KERNEL
    friend class IOUserNetworkPacketMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOUserNetworkPacket_IVars * ivars;
        IOUserNetworkPacket_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = OSObject;

#if !KERNEL
    IOUserNetworkPacket_Methods
    IOUserNetworkPacket_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */


/* IOUserNetworkPacket.iig:172- */

#endif /* ! _IOUSERNETWORKPACKET_IIG */
