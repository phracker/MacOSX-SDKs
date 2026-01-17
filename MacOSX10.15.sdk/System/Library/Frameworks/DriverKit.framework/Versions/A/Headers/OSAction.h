/* iig(DriverKit-73.0.1) generated from OSAction.iig */

/* OSAction.iig:1-49 */
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

#ifndef _IOKIT_OSACTION_H
#define _IOKIT_OSACTION_H

#include <DriverKit/OSObject.h>  /* .iig include */

typedef void (^OSActionCancelHandler)(void);
typedef void (^OSActionAbortedHandler)(void);

/*!
 * @class OSAction
 *
 * @abstract
 * OSAction is an object that represents a callback to be be invoked.
 *
 * @discussion
 * The callback is specified as a method and object pair.
 * State associated with the callback may be allocated and stored for the creator of the object.
 * Methods to allocate an OSAction instance are generated for each method defined in a class with
 * a TYPE attribute, so there should not be any need to directly call OSAction::Create().
 */

/* class OSAction OSAction.iig:50-109 */

#define OSAction_Create_ID            0xaa1fc3ce85ce5497ULL
#define OSAction_Aborted_ID            0xbfb95094c657d68fULL

#define OSAction_Create_Args \
        OSObject * target, \
        uint64_t targetmsgid, \
        uint64_t msgid, \
        size_t referenceSize, \
        OSAction ** action

#define OSAction_Aborted_Args \


#define OSAction_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(OSAction * self, const IORPC rpc);\
\
    static kern_return_t\
    Create(\
        OSObject * target,\
        uint64_t targetmsgid,\
        uint64_t msgid,\
        size_t referenceSize,\
        OSAction ** action);\
\
    void *\
    GetReference(\
);\
\
    kern_return_t\
    Cancel(\
        OSActionCancelHandler handler);\
\
    kern_return_t\
    SetAbortedHandler(\
        OSActionAbortedHandler handler);\
\
    void\
    Aborted(\
        OSDispatchMethod supermethod = NULL);\
\
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    Create_Call(OSAction_Create_Args);\
\
    void\
    Aborted_Impl(OSAction_Aborted_Args);\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*Create_Handler)(OSAction_Create_Args);\
    static kern_return_t\
    Create_Invoke(const IORPC rpc,\
        Create_Handler func);\
\
    typedef void (*Aborted_Handler)(OSMetaClassBase * targetOSAction_Aborted_Args);\
    static kern_return_t\
    Aborted_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        Aborted_Handler func);\
\


#define OSAction_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    static kern_return_t\
    Create_Impl(OSAction_Create_Args);\
\


#define OSAction_VirtualMethods \
\
public:\
\
    virtual void\
    free(\
) APPLE_KEXT_OVERRIDE;\
\



extern OSMetaClass          * gOSActionMetaClass;
extern const OSClassLoadInformation OSAction_Class;

class OSActionMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};


class OSActionInterface : public OSInterface
{
public:
};

struct OSAction_IVars;
struct OSAction_LocalIVars;

class OSAction : public OSObject, public OSActionInterface
{

    friend class OSActionMetaClass;

public:
    union
    {
        OSAction_IVars * ivars;
        OSAction_LocalIVars * lvars;
    };
    virtual const OSMetaClass *
    getMetaClass() const APPLE_KEXT_OVERRIDE { return OSTypeID(OSAction); };

    using super = OSObject;

    OSAction_Methods

    OSAction_VirtualMethods
};
/* OSAction.iig:111- */

#endif /* ! _IOKIT_OSACTION_H */
