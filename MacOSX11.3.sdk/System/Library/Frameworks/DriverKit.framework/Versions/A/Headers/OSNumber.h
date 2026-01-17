/* iig(DriverKit-107.100.6) generated from OSNumber.iig */

/* OSNumber.iig:1-36 */
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

/* source class OSNumber OSNumber.iig:37-137 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

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

class LOCALONLY OSNumber : public OSContainer
{
public:

	// OSObject

	virtual void
	free() override;

    /*!
     * @brief       Compares the string with an OSObject
     * @discussion  If the object is of class OSNumber, the result of isEqualTo(const OSNumber * aDataObj) is returned.
     *              Otherwise false is returned.
     * @param       anObject The object to compare with.
     * @result      true iff the object is of class OSNumber isEqualTo() returns true.
     */
	bool
	isEqualTo(const OSMetaClassBase * anObject) const override;

	// OSNumber

    /*!
     * @brief       Allocates an OSNumber object with value and size.
     * @discussion  Allocates an OSNumber object with value and size.
     * @param       value Value the OSNumber holds.
     * @param       numberOfBits Size of the value. Only 8, 16, 32, or 64 are valid sizes.
     * @return      NULL on failure, otherwise the allocated OSNumber with reference count 1 to be released by the caller.
     */
	static OSNumberPtr
	withNumber(
		uint64_t value,
		size_t   numberOfBits);

    /*!
     * @brief       Allocates an OSNumber object with value from a c-string and size.
     * @discussion  Allocates an OSNumber object with value from a c-string and size.
     * @param       valueString A c-string which will be parsed with strtoll(,,0).
     * @param       numberOfBits Size of the value. Only 8, 16, 32, or 64 are valid sizes.
     * @return      NULL on failure, otherwise the allocated OSNumber with reference count 1 to be released by the caller.
     */
	static OSNumberPtr
	withNumber(
		const char   * valueString,
		size_t         numberOfBits);

    /*!
     * @brief       Returns the number of bits the OSNumber was created with.
     * @return      Returns the number of bits the OSNumber was created with.
     */
	size_t
	numberOfBits() const;

    /*!
     * @brief       Returns the value of the OSNumber as a uint8_t value.
     * @return      Returns the value of the OSNumber as a uint8_t value.
     */
	uint8_t
	unsigned8BitValue() const;

    /*!
     * @brief       Returns the value of the OSNumber as a uint16_t value.
     * @return      Returns the value of the OSNumber as a uint16_t value.
     */
	uint16_t
	unsigned16BitValue() const;

    /*!
     * @brief       Returns the value of the OSNumber as a uint32_t value.
     * @return      Returns the value of the OSNumber as a uint32_t value.
     */
	uint32_t
	unsigned32BitValue() const;

    /*!
     * @brief       Returns the value of the OSNumber as a uint64_t value.
     * @return      Returns the value of the OSNumber as a uint64_t value.
     */
	uint64_t
	unsigned64BitValue() const;

    /*!
     * @brief       Compares the number with an OSNumber.
     * @discussion  If the passed OSNumber object has the same value, regardless of size, true is returned.
     *              Otherwise false is returned.
     * @param       aNumber The OSNumber to compare with.
     * @result      true iff the two numbers have the same value.
     */
	bool
	isEqualTo(const OSNumber * aNumber) const;
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class OSNumber OSNumber.iig:37-137 */


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


#endif /* !__DOCUMENTATION__ */

/* OSNumber.iig:139- */

#endif /* ! _IOKIT_OSNUMBER_H */
