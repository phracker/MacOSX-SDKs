/* iig(DriverKit-73.0.1) generated from OSObject.iig */

/* OSObject.iig:1-112 */
/*
 * Copyright (c) 2019-2019 Apple Inc. All rights reserved.
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

#if !__IIG
#endif

#ifndef _IOKIT_UOSOBJECT_H
#define _IOKIT_UOSOBJECT_H

#include <stddef.h>
#include <stdint.h>
#include <DriverKit/IOReturn.h>
#if DRIVERKIT_PRIVATE
#include <mach/port.h>
#endif
#if !__IIG
#include <string.h>
#include <DriverKit/OSMetaClass.h>
#endif
class OSObject;
typedef OSObject * OSObjectPtr;

#if __IIG && !__IIG_ATTRIBUTES_DEFINED__

#define __IIG_ATTRIBUTES_DEFINED__	1

#define KERNEL       __attribute__((annotate("kernel")))
#define NATIVE       __attribute__((annotate("native")))
#define LOCAL        __attribute__((annotate("local")))
#define LOCALONLY    __attribute__((annotate("localonly")))
#define REMOTE       __attribute__((annotate("remote")))

#define LOCALHOST    __attribute__((annotate("localhost")))

#define INVOKEREPLY  __attribute__((annotate("invokereply")))
#define REPLY        __attribute__((annotate("reply")))

#define PORTMAKESEND __attribute__((annotate("MACH_MSG_TYPE_MAKE_SEND")))
#define PORTCOPYSEND __attribute__((annotate("MACH_MSG_TYPE_COPY_SEND")))

#define TARGET       __attribute__((annotate("target")))
#define TYPE(p)      __attribute__((annotate("type=" # p)))

//#define ARRAY(maxcount) __attribute__((annotate(# maxcount), annotate("array")))
#define EXTENDS(cls) __attribute__((annotate("extends=" # cls)))

//#define INTERFACE    __attribute__((annotate("interface")))
//#define IMPLEMENTS(i)   void implements(i *);

#define QUEUENAME(name) __attribute__((annotate("queuename=" # name)))

#define IIG_SERIALIZABLE __attribute__((annotate("serializable")))

#else

#define IIG_SERIALIZABLE

#endif /* __IIG */


#if !__IIG
class IIG_SERIALIZABLE OSContainer;
#else
class IIG_SERIALIZABLE OSContainer;
#endif

class IIG_SERIALIZABLE OSData;
class IIG_SERIALIZABLE OSNumber;
class IIG_SERIALIZABLE OSString;
class IIG_SERIALIZABLE OSBoolean;
class IIG_SERIALIZABLE OSDictionary;
class IIG_SERIALIZABLE OSArray;

class OSMetaClass;
class IODispatchQueue;
typedef char IODispatchQueueName[256];

#if __IIG
/* OSObject.iig:127-135 */
#endif /* __IIG */


/*!
@iig implementation
#include <DriverKit/IODispatchQueue.h>
@iig end
*/

/* class OSObject OSObject.iig:136-160 */

#define OSObject_SetDispatchQueue_ID            0xe608ae8273dae1bcULL
#define OSObject_CopyDispatchQueue_ID            0x95115b48fd29f7c9ULL

#define OSObject_SetDispatchQueue_Args \
        const char * name, \
        IODispatchQueue * queue

#define OSObject_CopyDispatchQueue_Args \
        const char * name, \
        IODispatchQueue ** queue

#define OSObject_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(OSObject * self, const IORPC rpc);\
\
    kern_return_t\
    SetDispatchQueue(\
        const IODispatchQueueName name,\
        IODispatchQueue * queue,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    CopyDispatchQueue(\
        const IODispatchQueueName name,\
        IODispatchQueue ** queue,\
        OSDispatchMethod supermethod = NULL);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*SetDispatchQueue_Handler)(OSMetaClassBase * target, OSObject_SetDispatchQueue_Args);\
    static kern_return_t\
    SetDispatchQueue_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        SetDispatchQueue_Handler func);\
\
    typedef kern_return_t (*CopyDispatchQueue_Handler)(OSMetaClassBase * target, OSObject_CopyDispatchQueue_Args);\
    static kern_return_t\
    CopyDispatchQueue_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        CopyDispatchQueue_Handler func);\
\


#define OSObject_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define OSObject_VirtualMethods \
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
    virtual void\
    retain(\
) const APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    release(\
) const APPLE_KEXT_OVERRIDE;\
\



extern OSMetaClass          * gOSObjectMetaClass;
extern const OSClassLoadInformation OSObject_Class;

class OSObjectMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};



class OSObjectInterface : public OSInterface
{
public:
    virtual bool
    init() = 0;

    virtual void
    free() = 0;

};

struct OSObject_IVars;
struct OSObject_LocalIVars;

class OSObject : public OSMetaClassBase, public OSObjectInterface
{
    friend class OSObjectMetaClass;

public:
    union
    {
        OSObject_IVars * ivars;
        OSObject_LocalIVars * lvars;
    };

    using super = OSMetaClassBase;

    OSObject_Methods
    OSObject_VirtualMethods

};

/* OSObject.iig:162- */

#define DEFN(classname, name)                                       \
name ## _Impl(classname ## _ ## name ## _Args)

#define IMPL(classname, name)                                       \
classname :: DEFN(classname, name)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#endif /* ! _IOKIT_UOSOBJECT_H */
