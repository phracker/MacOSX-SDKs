/* iig(DriverKit-73.0.1) generated from IOHIDElement.iig */

/* IOHIDElement.iig:1-39 */
/*
 * Copyright (c) 2018-2019 Apple Inc. All rights reserved.
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

#ifndef _HIDDRIVERKIT_IOHIDELEMENT_H
#define _HIDDRIVERKIT_IOHIDELEMENT_H

#include <DriverKit/OSContainer.h>  /* .iig include */
#include <HIDDriverKit/IOHIDDeviceTypes.h>
#include <DriverKit/IOTypes.h>

class OSArray;
class OSData;
class IOHIDElement;

/* class IOHIDElement IOHIDElement.iig:40-280 */


#define IOHIDElement_Methods \
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


#define IOHIDElement_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define IOHIDElement_VirtualMethods \
\
public:\
\


#if !KERNEL

extern OSMetaClass          * gIOHIDElementMetaClass;
extern const OSClassLoadInformation IOHIDElement_Class;

class IOHIDElementMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOHIDElementInterface : public OSInterface
{
public:
    virtual IOHIDElementCookie
    getCookie() = 0;

    virtual IOHIDElement *
    getParentElement() = 0;

    virtual OSArray *
    getChildElements() = 0;

    virtual IOHIDElementType
    getType() = 0;

    virtual IOHIDElementCollectionType
    getCollectionType() = 0;

    virtual uint32_t
    getUsagePage() = 0;

    virtual uint32_t
    getUsage() = 0;

    virtual uint32_t
    getLogicalMin() = 0;

    virtual uint32_t
    getLogicalMax() = 0;

    virtual uint32_t
    getPhysicalMin() = 0;

    virtual uint32_t
    getPhysicalMax() = 0;

    virtual uint32_t
    getUnitExponent() = 0;

    virtual uint32_t
    getUnit() = 0;

    virtual uint32_t
    getReportSize() = 0;

    virtual uint32_t
    getReportCount() = 0;

    virtual uint32_t
    getReportID() = 0;

    virtual uint32_t
    getFlags() = 0;

    virtual uint64_t
    getTimeStamp() = 0;

    virtual void
    setValue(uint32_t value) = 0;

    virtual void
    setDataValue(OSData * value) = 0;

    virtual uint32_t
    getScaledValue(IOHIDValueScaleType type) = 0;

    virtual IOFixed
    getScaledFixedValue(IOHIDValueScaleType type) = 0;

    virtual uint32_t
    getValue(IOOptionBits options) = 0;

    virtual OSData *
    getDataValue(IOOptionBits options) = 0;

    virtual IOReturn
    commit(IOHIDElementCommitDirection direction) = 0;

};

struct IOHIDElement_IVars;
struct IOHIDElement_LocalIVars;

class IOHIDElement : public OSContainer, public IOHIDElementInterface
{
#if !KERNEL
    friend class IOHIDElementMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOHIDElement_IVars * ivars;
        IOHIDElement_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = OSContainer;

#if !KERNEL
    IOHIDElement_Methods
    IOHIDElement_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */

/* IOHIDElement.iig:282- */

#endif /* _HIDDRIVERKIT_IOHIDELEMENT_H */
