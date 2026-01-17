/* iig(DriverKit-73.0.1) generated from IOUserNetworkTxCompletionQueue.iig */

/* IOUserNetworkTxCompletionQueue.iig:1-17 */
#ifndef _IOUSERNETWORKTXCOMPLETIONQUEUE_IIG
#define _IOUSERNETWORKTXCOMPLETIONQUEUE_IIG

#include <DriverKit/IODispatchQueue.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacketBufferPool.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacketQueue.h>  /* .iig include */

/*!
@iig implementation
#if KERNEL
#include <NetworkingDriverKit/IOUserNetworkPacketQueue_kext.h>
#include <NetworkingDriverKit/IOUserNetworkPacketBufferPool_kext.h>
#include <NetworkingDriverKit/IOUserNetworkTxCompletionQueue_kext.h>
#endif
@iig end
*/

/* class IOUserNetworkTxCompletionQueue IOUserNetworkTxCompletionQueue.iig:18-37 */

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

/* IOUserNetworkTxCompletionQueue.iig:39- */

#endif /* ! _IOUSERNETWORKTXCOMPLETIONQUEUE_IIG */
