/* iig(DriverKit-73.0.1) generated from IOUserNetworkTxSubmissionQueue.iig */

/* IOUserNetworkTxSubmissionQueue.iig:1-17 */
#ifndef _IOUSERNETWORKTXSUBMISSIONQUEUE_IIG
#define _IOUSERNETWORKTXSUBMISSIONQUEUE_IIG

#include <DriverKit/IODispatchQueue.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacketBufferPool.h>  /* .iig include */
#include <NetworkingDriverKit/IOUserNetworkPacketQueue.h>  /* .iig include */

/*!
@iig implementation
#if KERNEL
#include <NetworkingDriverKit/IOUserNetworkPacketQueue_kext.h>
#include <NetworkingDriverKit/IOUserNetworkPacketBufferPool_kext.h>
#include <NetworkingDriverKit/IOUserNetworkTxSubmissionQueue_kext.h>
#endif
@iig end
*/

/* class IOUserNetworkTxSubmissionQueue IOUserNetworkTxSubmissionQueue.iig:18-37 */

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

/* IOUserNetworkTxSubmissionQueue.iig:39- */

#endif /* ! _IOUSERNETWORKTXSUBMISSIONQUEUE_IIG */
