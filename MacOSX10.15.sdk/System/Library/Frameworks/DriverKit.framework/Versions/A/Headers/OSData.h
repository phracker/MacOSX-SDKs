/* iig(DriverKit-73.0.1) generated from OSData.iig */

/* OSData.iig:1-53 */
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

#ifndef _IOKIT_OSDATA_H
#define _IOKIT_OSDATA_H

#include <DriverKit/OSContainer.h>  /* .iig include */

class OSData;
typedef OSData * OSDataPtr;
class OSString;

/*!
 * @class OSData
 *
 * @abstract
 * OSData provides a container for untyped data.
 *
 * @discussion
 * OSData represents an array of bytes as a container object.
 * OSData objects are mutable:
 * You can add bytes to them and
 * overwrite portions of the byte array.
 *
 * OSData provides no concurrency protection;
 * it's up to the usage context to provide any protection necessary.
 */

/* class OSData OSData.iig:54-211 */


#define OSData_Methods \
\
public:\
\
    static OSDataPtr\
    withCapacity(\
        uint32_t capacity);\
\
    static OSDataPtr\
    withBytes(\
        const void * bytes,\
        size_t numBytes);\
\
    static OSDataPtr\
    withBytesNoCopy(\
        void * bytes,\
        size_t numBytes);\
\
    static OSDataPtr\
    withData(\
        const OSData * inData);\
\
    static OSDataPtr\
    withData(\
        const OSData * inData,\
        size_t start,\
        size_t numBytes);\
\
    size_t\
    getLength(\
) const;\
\
    size_t\
    getCapacity(\
) const;\
\
    bool\
    appendBytes(\
        const void * bytes,\
        size_t numBytes);\
\
    bool\
    appendBytes(\
        const OSData * aDataObj);\
\
    const void *\
    getBytesNoCopy(\
) const;\
\
    const void *\
    getBytesNoCopy(\
        size_t start,\
        size_t numBytes) const;\
\
    bool\
    isEqualTo(\
        const OSData * aDataObj) const;\
\
    bool\
    isEqualTo(\
        const OSString * aString) const;\
\
    bool\
    isEqualTo(\
        const void * bytes,\
        size_t numBytes) const;\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define OSData_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define OSData_VirtualMethods \
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

extern OSMetaClass          * gOSDataMetaClass;
extern const OSClassLoadInformation OSData_Class;

class OSDataMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class OSDataInterface : public OSInterface
{
public:
};

struct OSData_IVars;
struct OSData_LocalIVars;

class OSData : public OSContainer, public OSDataInterface
{
#if !KERNEL
    friend class OSDataMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        OSData_IVars * ivars;
        OSData_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = OSContainer;

#if !KERNEL
    OSData_Methods
    OSData_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */

/* OSData.iig:213- */

#endif /* ! _IOKIT_OSDATA_H */
