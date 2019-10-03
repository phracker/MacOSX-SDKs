/* iig(DriverKit-73.0.1) generated from IOUserNetworkRxCompletionQueue.iig */

/* IOUserNetworkRxCompletionQueue.iig:1-17 */
#ifndef _IOUSERNETWORKRXCOMPLETIONQUEUE_IIG
#define _IOUSERNETWORKRXCOMPLETIONQUEUE_IIG

#include <DriverKit/IODispatchQueue.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacketBufferPool.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacketQueue.h>  /* .iig include */

/*!
@iig implementation
#if KERNEL
#include <NetworkingDriverKit/IOUserNetworkPacketBufferPool_kext.h>
#include <NetworkingDriverKit/IOUserNetworkPacketQueue_kext.h>
#include <NetworkingDriverKit/IOUserNetworkRxCompletionQueue_kext.h>
#endif
@iig end
*/

/* class IOUserNetworkRxCompletionQueue IOUserNetworkRxCompletionQueue.iig:18-37 */

#define IOUserNetworkRxCompletionQueue_Create_ID            0xf8300e5138b8e424ULL

#define IOUserNetworkRxCompletionQueue_Create_Args \
        IOUserNetworkPacketBufferPool * pool, \
        OSObject * owner, \
        uint32_t capacity, \
        uint32_t queueId, \
        IODispatchQueue * dispatchQueue, \
        IOUserNetworkRxCompletionQueue ** queue

#define IOUserNetworkRxCompletionQueue_SetEnable_Args \
        bool isEnable

#define IOUserNetworkRxCompletionQueue_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOUserNetworkRxCompletionQueue * self, const IORPC rpc);\
\
    static kern_return_t\
    Create(\
        IOUserNetworkPacketBufferPool * pool,\
        OSObject * owner,\
        uint32_t capacity,\
        uint32_t queueId,\
        IODispatchQueue * dispatchQueue,\
        IOUserNetworkRxCompletionQueue ** queue);\
\
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    Create_Call(IOUserNetworkRxCompletionQueue_Create_Args);\
\
    kern_return_t\
    SetEnable_Impl(IOUserNetworkPacketQueue_SetEnable_Args);\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*Create_Handler)(IOUserNetworkRxCompletionQueue_Create_Args);\
    static kern_return_t\
    Create_Invoke(const IORPC rpc,\
        Create_Handler func);\
\


#define IOUserNetworkRxCompletionQueue_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    Create_Impl(IOUserNetworkRxCompletionQueue_Create_Args);\
\


#define IOUserNetworkRxCompletionQueue_VirtualMethods \
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

extern OSMetaClass          * gIOUserNetworkRxCompletionQueueMetaClass;
extern const OSClassLoadInformation IOUserNetworkRxCompletionQueue_Class;

class IOUserNetworkRxCompletionQueueMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOUserNetworkRxCompletionQueueInterface : public OSInterface
{
public:
};

struct IOUserNetworkRxCompletionQueue_IVars;
struct IOUserNetworkRxCompletionQueue_LocalIVars;

class IOUserNetworkRxCompletionQueue : public IOUserNetworkPacketQueue, public IOUserNetworkRxCompletionQueueInterface
{
#if !KERNEL
    friend class IOUserNetworkRxCompletionQueueMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOUserNetworkRxCompletionQueue_IVars * ivars;
        IOUserNetworkRxCompletionQueue_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = IOUserNetworkPacketQueue;

#if !KERNEL
    IOUserNetworkRxCompletionQueue_Methods
    IOUserNetworkRxCompletionQueue_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */

/* IOUserNetworkRxCompletionQueue.iig:39- */

#endif /* ! _IOUSERNETWORKRXCOMPLETIONQUEUE_IIG */
