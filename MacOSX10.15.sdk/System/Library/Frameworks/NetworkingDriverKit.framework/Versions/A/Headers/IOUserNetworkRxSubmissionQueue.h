/* iig(DriverKit-73.0.1) generated from IOUserNetworkRxSubmissionQueue.iig */

/* IOUserNetworkRxSubmissionQueue.iig:1-17 */
#ifndef _IOUSERNETWORKRXSUBMISSIONQUEUE_IIG
#define _IOUSERNETWORKRXSUBMISSIONQUEUE_IIG

#include <DriverKit/IODispatchQueue.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacketBufferPool.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacketQueue.h>  /* .iig include */

/*!
@iig implementation
#if KERNEL
#include <NetworkingDriverKit/IOUserNetworkPacketQueue_kext.h>
#include <NetworkingDriverKit/IOUserNetworkPacketBufferPool_kext.h>
#include <NetworkingDriverKit/IOUserNetworkRxSubmissionQueue_kext.h>
#endif
@iig end
*/

/* class IOUserNetworkRxSubmissionQueue IOUserNetworkRxSubmissionQueue.iig:18-37 */

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

/* IOUserNetworkRxSubmissionQueue.iig:39- */

#endif /* ! _IOUSERNETWORKRXSUBMISSIONQUEUE_IIG */
