/* iig(DriverKit-107.100.6) generated from OSBoolean.iig */

/* OSBoolean.iig:1-64 */
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

#ifndef _IOKIT_OSBOOLEAN_H
#define _IOKIT_OSBOOLEAN_H

#include <DriverKit/OSCollection.h>  /* .iig include */

class OSBoolean;
typedef OSBoolean * OSBooleanPtr;

/*!
 * @const kOSBooleanTrue
 *
 * @abstract
 * The OSBoolean constant for <code>true</code>.
 *
 * @discussion
 * kOSBooleanTrue is the OSBoolean constant for <code>true</code>.
 * This object does not need to be retained or released (but it can be).
 * Comparisons should be of the form
 * <code>booleanObject == kOSBooleanTrue</code>
 */
extern OSBooleanPtr kOSBooleanTrue;

/*!
 * @const kOSBooleanFalse
 *
 * @abstract
 * The OSBoolean constant for <code>false</code>.
 *
 * @discussion
 * kOSBooleanFalse is the OSBoolean constant for <code>true</code>.
 * This object does not need to be retained or released (but it can be).
 * Comparisons should be of the form
 * <code>booleanObject == kOSBooleanFalse</code>
 */
extern OSBooleanPtr kOSBooleanFalse;

/* source class OSBoolean OSBoolean.iig:65-89 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
 * @class OSBoolean
 *
 * @abstract
 * Represents a true or false value.
 *
 * @discussion
 * Only two static immutable instances of OSBoolean exist, kOSBooleanFalse & kOSBooleanTrue.
 */

class LOCALONLY OSBoolean : public OSContainer
{
public:
	// OSObject

    virtual void
    free() override;

    virtual void
    retain() const override;

    virtual void
    release() const override;

	// OSBoolean
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class OSBoolean OSBoolean.iig:65-89 */


#define OSBoolean_Methods \
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


#define OSBoolean_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define OSBoolean_VirtualMethods \
\
public:\
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


#if !KERNEL

extern OSMetaClass          * gOSBooleanMetaClass;
extern const OSClassLoadInformation OSBoolean_Class;

class OSBooleanMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class OSBooleanInterface : public OSInterface
{
public:
};

struct OSBoolean_IVars;
struct OSBoolean_LocalIVars;

class OSBoolean : public OSContainer, public OSBooleanInterface
{
#if !KERNEL
    friend class OSBooleanMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        OSBoolean_IVars * ivars;
        OSBoolean_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = OSContainer;

#if !KERNEL
    OSBoolean_Methods
    OSBoolean_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* OSBoolean.iig:91- */

#endif /* ! _IOKIT_OSBOOLEAN_H */
