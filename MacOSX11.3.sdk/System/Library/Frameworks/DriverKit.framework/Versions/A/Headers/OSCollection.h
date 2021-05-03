/* iig(DriverKit-107.100.6) generated from OSCollection.iig */

/* OSCollection.iig:1-42 */
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

#ifndef _IOKIT_OSCOLLECTION_H
#define _IOKIT_OSCOLLECTION_H

#include <DriverKit/OSObject.h>  /* .iig include */
#include <DriverKit/OSContainer.h>  /* .iig include */


class OSCollection;
typedef OSCollection * OSCollectionPtr;

class OSDictionary;

typedef bool (^OSCollectionIterateObjectsBlock)(OSObject * object);

/* source class OSCollection OSCollection.iig:43-70 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
 * @class OSCollection
 *
 * @discussion
 * Base class for DriverKit collection objects.
 */

class LOCALONLY OSCollection : public OSContainer
{
public:

	virtual uint32_t
	getCount() const = 0;

	virtual uint32_t
	getCapacity() const = 0;

	virtual uint32_t
	ensureCapacity(uint32_t newCapacity) = 0;

	virtual void
	flushCollection() = 0;

	virtual bool
	iterateObjects(OSCollectionIterateObjectsBlock block) const;

	virtual
	OSCollectionPtr copyCollection(OSDictionary * cycleDict) const;
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class OSCollection OSCollection.iig:43-70 */


#define OSCollection_Methods \
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


#define OSCollection_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define OSCollection_VirtualMethods \
\
public:\
\
    virtual bool\
    iterateObjects(\
        OSCollectionIterateObjectsBlock block) const APPLE_KEXT_OVERRIDE;\
\
    virtual OSCollectionPtr\
    copyCollection(\
        OSDictionary * cycleDict) const APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gOSCollectionMetaClass;
extern const OSClassLoadInformation OSCollection_Class;

class OSCollectionMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class OSCollectionInterface : public OSInterface
{
public:
    virtual uint32_t
    getCount() const = 0;

    virtual uint32_t
    getCapacity() const = 0;

    virtual uint32_t
    ensureCapacity(uint32_t newCapacity) = 0;

    virtual void
    flushCollection() = 0;

    virtual bool
    iterateObjects(OSCollectionIterateObjectsBlock block) const = 0;

    virtual OSCollectionPtr
    copyCollection(OSDictionary * cycleDict) const = 0;

};

struct OSCollection_IVars;
struct OSCollection_LocalIVars;

class OSCollection : public OSContainer, public OSCollectionInterface
{
#if !KERNEL
    friend class OSCollectionMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        OSCollection_IVars * ivars;
        OSCollection_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = OSContainer;

#if !KERNEL
    OSCollection_Methods
    OSCollection_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* OSCollection.iig:72- */

#endif /* ! _IOKIT_OSCOLLECTION_H */
