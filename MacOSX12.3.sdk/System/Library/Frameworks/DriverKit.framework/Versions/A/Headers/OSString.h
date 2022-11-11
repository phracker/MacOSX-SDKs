/* iig(DriverKit-192.100.7) generated from OSString.iig */

/* OSString.iig:1-40 */
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


/* source class OSString OSString.iig:41-161 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

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

class LOCALONLY OSString : public OSContainer
{
public:

	// OSObject

	virtual void
	free() override;

    /*!
     * @brief       Compares the string with an OSObject
     * @discussion  If the object is of class OSString, the result of isEqualTo(const OSString * aDataObj) is returned.
     *              If the object is of class OSData, the result of isEqualTo(const OSData * aDataObj) is returned.
     *              Otherwise false is returned.
     * @param       anObject The object to compare with.
     * @result      true iff the object is of class OSData or OSString and isEqualTo() returns true.
     */
	bool
	isEqualTo(const OSMetaClassBase * anObject) const override;

	// OSString

    /*!
     * @brief       Allocates an OSString object with a copy of a c-string.
     * @param       cString Pointer to null terminated c-string. The string will be copied at the time of the call.
     * @return      NULL on failure, otherwise the allocated OSString with reference count 1 to be released by the caller.
     */
	static OSStringPtr
	withCString(const char * cString);

    /*!
     * @brief       Allocates an OSString object with a copy of a c-string, up to a given length.
     * @param       cString Pointer to null terminated c-string. The string will be copied at the time of the call.
     * @param       length Maximum length of the string to copy.
     * @return      NULL on failure, otherwise the allocated OSString with reference count 1 to be released by the caller.
     */
	static OSStringPtr
	withCString(const char * cString, size_t length);

    /*!
     * @brief       Allocates an OSString object with a copy of a c-string.
     * @discussion  Allocates an OSString object with a copy of a c-string. A synonym for OSString::withCString() for compatibility with kernel code.
     * @param       cString Pointer to null terminated c-string. The string will be copied at the time of the call.
     * @return      NULL on failure, otherwise the allocated OSString with reference count 1 to be released by the caller.
     */
	static OSStringPtr
	withCStringNoCopy(const char * cString);

    /*!
     * @brief       Allocates an OSString object with a copy of an OString object.
     * @discussion  Allocates an OSString object with a copy of an OString object.
     * @param       aString OSString object to copy from. The string will be copied at the time of the call.
     * @return      NULL on failure, otherwise the allocated OSString with reference count 1 to be released by the caller.
     */
	static OSStringPtr
	withString(const OSString * aString);

    /*!
     * @brief       Returns length of string not including null terminator.
     * @return      length of data present.
     */
	size_t
	getLength() const;

    /*!
     * @brief       Returns a pointer to the OSString object's internal data buffer.
     * @return      A pointer to the string or NULL if the OSString has zero length. The string will be null terminated.
     */
	const char *
	getCStringNoCopy() const;

    /*!
     * @brief       Compares the string with an OSString.
     * @discussion  If the passed OSString object has the same length and all characters are identical, true is returned.
     *              Otherwise false is returned.
     * @param       aString The OSString to compare with.
     * @result      true iff the two strings have the same length and characters.
     */
	bool
	isEqualTo(const OSString * aString) const;

    /*!
     * @brief       Compares the string with a c-string.
     * @discussion  If the passed c-string has the same length and all characters are identical to those in the OSString, true is returned.
     *              Otherwise false is returned.
     * @param       cString The c-string to compare with.
     * @result      true iff the two strings have the same length and characters.
     */
	bool
	isEqualTo(const char * cString) const;

    /*!
     * @brief       Compares the string with an OSData.
     * @discussion  If the passed OSData object has the same length and all bytes are identical, true is returned.
     *              If the passed OSData object has a length one byte greater than the OSString, all bytes are identical, and the last byte of the OSData is zero, true is returned.
     *              Otherwise false is returned.
     * @param       aDataObject The OSData to compare with.
     * @result      true if the OSData and OSString contain the same c-string.
     */
	bool
	isEqualTo(const OSData * aDataObject) const;

};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class OSString OSString.iig:41-161 */


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
#ifdef OSString_DECLARE_IVARS
OSString_DECLARE_IVARS
#else /* OSString_DECLARE_IVARS */
    union
    {
        OSString_IVars * ivars;
        OSString_LocalIVars * lvars;
    };
#endif /* OSString_DECLARE_IVARS */
#endif /* !KERNEL */

#if !KERNEL
    static OSMetaClass *
    sGetMetaClass() { return gOSStringMetaClass; };
#endif /* KERNEL */

    using super = OSContainer;

#if !KERNEL
    OSString_Methods
    OSString_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* OSString.iig:163- */

#endif /* ! _IOKIT_OSSTRING_H */
