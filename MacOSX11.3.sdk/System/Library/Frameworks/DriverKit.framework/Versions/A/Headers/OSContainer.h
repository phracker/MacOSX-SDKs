/* iig(DriverKit-107.100.6) generated from OSContainer.iig */

/* OSContainer.iig:1-37 */
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

#ifndef _IOKIT_OSCONTAINER_H
#define _IOKIT_OSCONTAINER_H

#include <DriverKit/OSObject.h>  /* .iig include */


class OSContainer;
typedef OSContainer * OSContainerPtr;

/* source class OSContainer OSContainer.iig:38-46 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
 * @class OSContainer
 *
 * @discussion
 * Base class for DriverKit container objects.
 */

class LOCALONLY OSContainer : public OSObject
{
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class OSContainer OSContainer.iig:38-46 */


#define OSContainer_Methods \
\
public:\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define OSContainer_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define OSContainer_VirtualMethods \
\
public:\
\


#if !KERNEL

extern OSMetaClass          * gOSContainerMetaClass;
extern const OSClassLoadInformation OSContainer_Class;

class OSContainerMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class OSContainerInterface : public OSInterface
{
public:
};

struct OSContainer_IVars;
struct OSContainer_LocalIVars;

class OSContainer : public OSObject, public OSContainerInterface
{
#if !KERNEL
    friend class OSContainerMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        OSContainer_IVars * ivars;
        OSContainer_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = OSObject;

#if !KERNEL
    OSContainer_Methods
    OSContainer_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* OSContainer.iig:48- */

#endif /* ! _IOKIT_OSCONTAINER_H */
