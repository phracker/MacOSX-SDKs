/* iig(DriverKit-451) generated from OSSet.iig */

/* OSSet.iig:1-36 */
/*
 * Copyright (c) 2020-2020 Apple Inc. All rights reserved.
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

#ifndef _IOKIT_OSSET_H
#define _IOKIT_OSSET_H

#include <DriverKit/OSArray.h>  /* .iig include */

class OSSet;
typedef OSSet * OSSetPtr;

/* source class OSSet OSSet.iig:37-147 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
 * @class OSSet
 *
 * @abstract
 * OSSet provides an unordered set store of objects.
 *
 * @discussion
 * OSSet is a collection class for objects derived from OSObject.
 * Storage and access follow basic set logic: you can add or remove an object,
 * and test whether the set contains a particular object.
 * A given object is only stored in the set once,
 * and there is no ordering of objects in the set.
 *
 * You must generally cast retrieved objects from
 * OSObject to the desired class using the OSDynamicCast macro.
 * This macro returns the object cast to the desired class,
 * or <code>NULL</code> if the object isn't derived from that class.
 *
 * As with all DriverKit collection classes,
 * OSSet retains objects added to it,
 * and releases objects removed from it (or replaced).
 * An OSSet also grows as necessary to accommodate new objects.
 *
 * OSSet provides no concurrency protection;
 * it's up to the usage context to provide any protection necessary.
 */

class LOCALONLY OSSet : public OSArray
{
public:
	// OSObject

	bool
	init() override;

	// OSSet

    /*!
     * @brief       Allocates an OSSet object with preallocated capacity.
     * @param       capacity Count of allocated capacity for members in array.
     * @return      NULL on failure, otherwise the allocated OSSet with reference count 1 to be released by the caller.
     */
	static OSSetPtr withCapacity(uint32_t capacity);

    /*!
     * @brief       Allocates an OSSet object with given members and preallocated capacity.
     * @param       values C-array pointer to members for the set.
     * @param       count Count of members being added to the set.
     * @param       capacity Count of allocated capacity for members in array.
     * @return      NULL on failure, otherwise the allocated OSSet with reference count 1 to be released by the caller.
     */
	static OSSetPtr withObjects(
		const OSObject ** values,
		uint32_t     count,
		uint32_t     capacity);

    /*!
     * @brief       Allocates an OSSet object with given members and preallocated capacity.
     * @param       array Array object containing members for the new set. Since OSSet is an OSArray subclass, it may be passed.
     * @param       capacity Count of allocated capacity for members in set.
     * @return      NULL on failure, otherwise the allocated OSSet with reference count 1 to be released by the caller.
     */
	static OSSetPtr withArray(
		const OSArray * array,
		uint32_t    capacity);

    /*!
     * @brief       Adds an object to the OSSet if it is not already present.
     * @discussion  Adds an object to the OSSet if it is not already present. The capacity will be grown if necessary.
     * @param       anObject Object to be added as the last member of the array.
     * @return      true on success, which retains the object, or false on failure which does not retain the object.
     */
	bool
	setObject(const OSMetaClassBase * anObject);

    /*!
     * @brief       Adds all members of an array or set to this set.
     * @discussion  Adds all members of an array or set to this set. The set capacity will be grown if necessary.
     * @param       otherArray All members of the array or set will be appended to the set.
     * @return      true on success, which retains all the added objects, or false on failure which does not retain the objects.
     */
	bool
	merge(const OSArray * otherArray);

    /*!
     * @brief       Removes an object from the set.
     * @discussion  Removes an object from the set.
     * @param       anObject The OSMetaClassBase-derived object to be removed from the set.
     */
	void removeObject(const OSMetaClassBase * anObject);

    /*!
     * @brief       Checks the set for the presence of an object.
     * @discussion  Checks the set for the presence of an object.
     * @param       anObject The OSMetaClassBase-derived object to check for in the set.
     * @return      if anObject is non-NULL and present within the set, false otherwise.
     */
	bool containsObject(const OSMetaClassBase * anObject) const;
    /*!
     * @brief       Synonym for containsObject().
     */
	bool member(const OSMetaClassBase * anObject) const { return containsObject(anObject); };

    /*!
     * @brief       Returns an arbitrary (not random) object from the set.
     * @discussion  Returns an arbitrary (not random) object from the set.
	 *              The returned object will be released if removed later from the set;
	 *              if you plan to store the reference, you should call retain() on that object.
     * @return      An arbitrary (not random) object if one exists within the set.
     */
	OSObject * getAnyObject() const;
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class OSSet OSSet.iig:37-147 */


#define OSSet_Methods \
\
public:\
\
    static OSSetPtr\
    withCapacity(\
        uint32_t capacity);\
\
    static OSSetPtr\
    withObjects(\
        const OSObject ** values,\
        uint32_t count,\
        uint32_t capacity);\
\
    static OSSetPtr\
    withArray(\
        const OSArray * array,\
        uint32_t capacity);\
\
    bool\
    setObject(\
        const OSMetaClassBase * anObject);\
\
    bool\
    merge(\
        const OSArray * otherArray);\
\
    void\
    removeObject(\
        const OSMetaClassBase * anObject);\
\
    bool\
    containsObject(\
        const OSMetaClassBase * anObject) const;\
\
    bool\
    member(\
        const OSMetaClassBase * anObject) const;\
\
    OSObject *\
    getAnyObject(\
) const;\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define OSSet_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define OSSet_VirtualMethods \
\
public:\
\
    virtual bool\
    init(\
) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gOSSetMetaClass;
extern const OSClassLoadInformation OSSet_Class;

class OSSetMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class  OSSetInterface : public OSInterface
{
public:
};

struct OSSet_IVars;
struct OSSet_LocalIVars;

class OSSet : public OSArray, public OSSetInterface
{
#if !KERNEL
    friend class OSSetMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
#ifdef OSSet_DECLARE_IVARS
OSSet_DECLARE_IVARS
#else /* OSSet_DECLARE_IVARS */
    union
    {
        OSSet_IVars * ivars;
        OSSet_LocalIVars * lvars;
    };
#endif /* OSSet_DECLARE_IVARS */
#endif /* !KERNEL */

#if !KERNEL
    static OSMetaClass *
    sGetMetaClass() { return gOSSetMetaClass; };
#endif /* KERNEL */

    using super = OSArray;

#if !KERNEL
    OSSet_Methods
    OSSet_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* OSSet.iig:149- */

#endif /* ! _IOKIT_OSSET_H */
