/* iig(DriverKit-73.0.1) generated from OSString.iig */

/* OSString.iig:1-59 */
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

#ifndef _IOKIT_OSSTRING_H
#define _IOKIT_OSSTRING_H

#include <DriverKit/OSContainer.h>  /* .iig include */

class OSString;
typedef OSString * OSStringPtr;
typedef OSString OSSymbol;

class OSData;


/*!
 * @class OSString
 *
 * @abstract
 * OSString wraps a C string in a C++ object for use in DriverKit collections.
 *
 * @discussion
 * OSString is a container class for managing arrays of characters.
 *
 * <b>Encodings</b>
 *
 * OSString makes no provisions for different character encodings and
 * assumes that a string is a nul-terminated sequence of single-byte characters.
 * User-space code must either assume an encoding (typically ASCII or UTF-8)
 * or determine it in some other way (such as an IORegistryEntry property).
 * 
 * OSString is immutable.
 */

/* class OSString OSString.iig:60-161 */


#define OSString_Methods \
\
public:\
\
    static OSStringPtr\
    withCString(\
        const char * cString);\
\
    static OSStringPtr\
    withCString(\
        const char * cString,\
        size_t length);\
\
    static OSStringPtr\
    withCStringNoCopy(\
        const char * cString);\
\
    static OSStringPtr\
    withString(\
        const OSString * aString);\
\
    size_t\
    getLength(\
) const;\
\
    const char *\
    getCStringNoCopy(\
) const;\
\
    bool\
    isEqualTo(\
        const OSString * aString) const;\
\
    bool\
    isEqualTo(\
        const char * cString) const;\
\
    bool\
    isEqualTo(\
        const OSData * aDataObject) const;\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define OSString_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define OSString_VirtualMethods \
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

extern OSMetaClass          * gOSStringMetaClass;
extern const OSClassLoadInformation OSString_Class;

class OSStringMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class OSStringInterface : public OSInterface
{
public:
};

struct OSString_IVars;
struct OSString_LocalIVars;

class OSString : public OSContainer, public OSStringInterface
{
#if !KERNEL
    friend class OSStringMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        OSString_IVars * ivars;
        OSString_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = OSContainer;

#if !KERNEL
    OSString_Methods
    OSString_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */

/* OSString.iig:163- */

#endif /* ! _IOKIT_OSSTRING_H */
