/* iig(DriverKit-73.0.1) generated from OSSerialization.iig */

/* OSSerialization.iig:1-53 */
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

#ifndef _IOKIT_OSSERIALIZATION_H
#define _IOKIT_OSSERIALIZATION_H

#include <DriverKit/OSContainer.h>  /* .iig include */

class OSSerialization;
typedef OSSerialization * OSSerializationPtr;

typedef void (^OSSerializationFreeBufferHandler)(const void * buffer, size_t length);

/*!
 * @class OSSerialization
 *
 * @abstract
 * OSSerialization provides methods to serialize an object to binary data.
 *
 * @discussion
 * OSSerialization provides methods to serialize an object to binary data suitable for messaging.
 * Only certain DriverKit classes may be serialized:
 * OSData, OSString, OSNumber, OSBoolean, OSArray, OSDictionary.
 *
 * OSSerialization provides no concurrency protection;
 * it's up to the usage context to provide any protection necessary.
 */

/* class OSSerialization OSSerialization.iig:54-101 */


#define OSSerialization_Methods \
\
public:\
\
    static OSSerializationPtr\
    createFromObject(\
        const OSObjectPtr object);\
\
    static OSSerializationPtr\
    createFromBytes(\
        const void * bytes,\
        size_t length,\
        OSSerializationFreeBufferHandler freeBuffer);\
\
    OSObjectPtr\
    copyObject(\
);\
\
    const void *\
    finalizeBuffer(\
        size_t * length);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define OSSerialization_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define OSSerialization_VirtualMethods \
\
public:\
\
    virtual void\
    free(\
) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gOSSerializationMetaClass;
extern const OSClassLoadInformation OSSerialization_Class;

class OSSerializationMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class OSSerializationInterface : public OSInterface
{
public:
};

struct OSSerialization_IVars;
struct OSSerialization_LocalIVars;

class OSSerialization : public OSContainer, public OSSerializationInterface
{
#if !KERNEL
    friend class OSSerializationMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        OSSerialization_IVars * ivars;
        OSSerialization_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = OSContainer;

#if !KERNEL
    OSSerialization_Methods
    OSSerialization_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */

/* OSSerialization.iig:103- */

#endif /* ! _IOKIT_OSSERIALIZATION_H */
