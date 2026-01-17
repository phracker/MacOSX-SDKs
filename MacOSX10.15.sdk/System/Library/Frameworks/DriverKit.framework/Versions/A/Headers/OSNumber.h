/* iig(DriverKit-73.0.1) generated from OSNumber.iig */

/* OSNumber.iig:1-48 */
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

#ifndef _IOKIT_OSNUMBER_H
#define _IOKIT_OSNUMBER_H

#include <DriverKit/OSContainer.h>  /* .iig include */

class OSNumber;
typedef OSNumber * OSNumberPtr;

/*!
 * @class OSNumber
 *
 * @abstract
 * OSNumber provides a container for an integer value.
 *
 * @discussion
 * OSNumber represents an integer of 8, 16, 32, or 64 bits
 * as a DriverKit container object.
 * OSNumber objects are immutable.
 */

/* class OSNumber OSNumber.iig:49-137 */


#define OSNumber_Methods \
\
public:\
\
    static OSNumberPtr\
    withNumber(\
        uint64_t value,\
        size_t numberOfBits);\
\
    static OSNumberPtr\
    withNumber(\
        const char * valueString,\
        size_t numberOfBits);\
\
    size_t\
    numberOfBits(\
) const;\
\
    uint8_t\
    unsigned8BitValue(\
) const;\
\
    uint16_t\
    unsigned16BitValue(\
) const;\
\
    uint32_t\
    unsigned32BitValue(\
) const;\
\
    uint64_t\
    unsigned64BitValue(\
) const;\
\
    bool\
    isEqualTo(\
        const OSNumber * aNumber) const;\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define OSNumber_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define OSNumber_VirtualMethods \
\
public:\
\
    virtual void\
    free(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    isEqualTo(\
        const OSMetaClassBase * anObject) const APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gOSNumberMetaClass;
extern const OSClassLoadInformation OSNumber_Class;

class OSNumberMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class OSNumberInterface : public OSInterface
{
public:
};

struct OSNumber_IVars;
struct OSNumber_LocalIVars;

class OSNumber : public OSContainer, public OSNumberInterface
{
#if !KERNEL
    friend class OSNumberMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        OSNumber_IVars * ivars;
        OSNumber_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = OSContainer;

#if !KERNEL
    OSNumber_Methods
    OSNumber_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */

/* OSNumber.iig:139- */

#endif /* ! _IOKIT_OSNUMBER_H */
