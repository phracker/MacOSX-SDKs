/* iig(DriverKit-73.0.1) generated from IOUserNetworkPacketBufferPool.iig */

/* IOUserNetworkPacketBufferPool.iig:1-16 */
#ifndef _IOUSERNETWORKPACKETBUFFERPOOL_IIG
#define _IOUSERNETWORKPACKETBUFFERPOOL_IIG

#include <DriverKit/IOMemoryDescriptor.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacket.h>  /* .iig include */

/*!
@iig implementation
#if KERNEL
#include <IOSkywalkFamily/IOSkywalkPacketBufferPool.h>
#include <NetworkingDriverKit/IOUserNetworkPacket_kext.h>
#include <NetworkingDriverKit/IOUserNetworkPacketBufferPool_kext.h>
#endif
@iig end
*/

/* class IOUserNetworkPacketBufferPool IOUserNetworkPacketBufferPool.iig:17-52 */

#define IOUserNetworkPacketBufferPool__DeallocatePacket_ID            0x96e008792b9286b5ULL
#define IOUserNetworkPacketBufferPool__CopyPacketWithIndex_ID            0xf0165b114d39c9f8ULL
#define IOUserNetworkPacketBufferPool_Create_ID            0xc44414cb258d0a15ULL
#define IOUserNetworkPacketBufferPool_CopyMemoryDescriptor_ID            0xc9a7388ad62f5737ULL
#define IOUserNetworkPacketBufferPool_GetPacketCount_ID            0xf4aae455ba1082ebULL
#define IOUserNetworkPacketBufferPool_GetBufferCount_ID            0xe922d59c37bf3bbeULL

#define IOUserNetworkPacketBufferPool__DeallocatePacket_Args \
        uint32_t packetIndex

#define IOUserNetworkPacketBufferPool__CopyPacketWithIndex_Args \
        uint32_t index, \
        IOUserNetworkPacket ** packet

#define IOUserNetworkPacketBufferPool_Create_Args \
        OSObject * poolOwner, \
        const char * name, \
        uint32_t packetCount, \
        uint32_t bufferCount, \
        uint32_t bufferSize, \
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
    Create(\
        OSObject * poolOwner,\
        const char * name,\
        uint32_t packetCount,\
        uint32_t bufferCount,\
        uint32_t bufferSize,\
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
    Create_Call(IOUserNetworkPacketBufferPool_Create_Args);\
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
    typedef kern_return_t (*Create_Handler)(IOUserNetworkPacketBufferPool_Create_Args);\
    static kern_return_t\
    Create_Invoke(const IORPC rpc,\
        Create_Handler func);\
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
    Create_Impl(IOUserNetworkPacketBufferPool_Create_Args);\
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


/* IOUserNetworkPacketBufferPool.iig:71- */

#endif /* ! _IOUSERNETWORKPACKETBUFFERPOOL_IIG */
