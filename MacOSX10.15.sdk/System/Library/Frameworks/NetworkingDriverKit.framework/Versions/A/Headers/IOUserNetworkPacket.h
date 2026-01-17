/* iig(DriverKit-73.0.1) generated from IOUserNetworkPacket.iig */

/* IOUserNetworkPacket.iig:1-35 */
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
    uint32_t packetIndex;
    uint8_t  direction;
    uint8_t  __reserved[3];
    uint64_t memoryOffset;
    uint32_t dataLength;
    uint16_t dataOffset;
    uint8_t  headroom;
    uint8_t  linkHeaderLength;
} __attribute__((packed));

/*!
@iig implementation
#if KERNEL
#include <IOSkywalkFamily/IOSkywalkNetworkPacket.h>
#include <NetworkingDriverKit/IOUserNetworkPacket_kext.h>
#endif
@iig end
*/

/* class IOUserNetworkPacket IOUserNetworkPacket.iig:36-86 */


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
    virtual kern_return_t\
    PrepareWithQueue(\
        IOUserNetworkPacketQueue * queue,\
        IOUserNetworkPacketDirection direction,\
        const IOUserNetworkPacketState * state) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    CompleteWithQueue(\
        IOUserNetworkPacketQueue * queue,\
        IOUserNetworkPacketDirection direction,\
        IOUserNetworkPacketState * state) APPLE_KEXT_OVERRIDE;\
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

    virtual kern_return_t
    PrepareWithQueue(IOUserNetworkPacketQueue * queue,
        IOUserNetworkPacketDirection direction,
        const IOUserNetworkPacketState * state) = 0;

    virtual kern_return_t
    CompleteWithQueue(IOUserNetworkPacketQueue * queue,
        IOUserNetworkPacketDirection direction,
        IOUserNetworkPacketState * state) = 0;

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


/* IOUserNetworkPacket.iig:104- */

#endif /* ! _IOUSERNETWORKPACKET_IIG */
