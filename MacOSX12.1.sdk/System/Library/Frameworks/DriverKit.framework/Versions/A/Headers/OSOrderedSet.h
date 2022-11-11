/* iig(DriverKit-191.60.3) generated from OSOrderedSet.iig */

/* OSOrderedSet.iig:1-69 */
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

#ifndef _IOKIT_OSORDEREDSET_H
#define _IOKIT_OSORDEREDSET_H

#include <DriverKit/OSSet.h>  /* .iig include */

class OSOrderedSet;
typedef OSOrderedSet * OSOrderedSetPtr;


/*!
 * @typedef OSOrderFunction
 *
 * @abstract
 * The sorting function used by an OSOrderedSet to order objects.
 *
 * @param obj1     An object from the ordered set. May be <code>NULL</code>.
 * @param obj2     The object being ordered within the ordered set.
 *                 May be <code>NULL</code>.
 *
 * @result
 * A comparison result of the object:
 * <ul>
 *   <li>a negative value if obj2 should precede obj1,</li>
 *   <li>a positive value if obj1 should precede obj2,</li>
 *   <li>and 0 if obj1 and obj2 have an equivalent ordering.</li>
 * </ul>
 */

/*!
 * @brief       The sorting function used by an OSOrderedSet to order objects.
 * @param       obj1 An object from the ordered set. May be NULL.
 * @param       obj2 The object being ordered within the ordered set. May be NULL.
 * @return      A comparison result of the object:
 *           	a negative value if obj2 should precede obj1,
 *              a positive value if obj1 should precede obj2,
 *              0 if obj1 and obj2 have an equivalent ordering.
 */
typedef int32_t (^OSOrderBlock)(
	const OSMetaClassBase * obj1,
	const OSMetaClassBase * obj2);

/* source class OSOrderedSet OSOrderedSet.iig:70-191 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
 * @class OSOrderedSet
 *
 * @abstract
 * OSOrderedSet provides an ordered set store of objects.
 *
 * @discussion
 * OSOrderedSet is a collection class for objects derived from OSObject.
 * Storage and access follow ordered set logic.
 * A given object is stored in the set only once, but you can:
 *    Define a sorting function for automated ordering
 *    (upon addition only)
 *    Manually insert new objects in the set (overriding sorting)
 *    Add and remove objects in the set
 *    Test whether the set contains a particular object
 *    Get the object stored at a particular index.
 *
 * Note that automated ordering is performed only upon addition of objects
 * and depends on the existing objects being properly sorted.
 * There is no function to re-sort the contents of an OSOrderedSet
 * or to change the ordering function.
 * In general, you should either use the one ordered-insertion function,
 * or the indexed-insertion functions, and not mix the two.
 *
 * You must generally cast retrieved objects from
 * OSObject to the desired class using the OSDynamicCast macro.
 * This macro returns the object cast to the desired class,
 * or <code>NULL</code> if the object isn't derived from that class.
 *
 * As with all DriverKit collection classes,
 * OSOrderedSet retains objects added to it,
 * and releases objects removed from it (or replaced).
 * An OSOrderedSet also grows as necessary to accommodate new objects.
 *
 * OSOrderedSet provides no concurrency protection;
 * it's up to the usage context to provide any protection necessary.
 */

class LOCALONLY OSOrderedSet : public OSSet
{
public:
	// OSObject
	bool
	init() override;
	void
	free() override;

	// OSOrderedSet

    /*!
     * @brief       Allocates an OSOrderedSet object with preallocated capacity.
     * @param       capacity Count of allocated capacity for members in array.
     * @param       orderBlock  If non-NULL, it is used by setObject() to determine where
     *              to insert a new object. Other object-setting functions ignore ordering.
     * @return      NULL on failure, otherwise the allocated OSOrderedSet with reference count 1 to be released by the caller.
     */
	static OSOrderedSetPtr withCapacity(
		uint32_t           capacity,
		OSOrderBlock       orderBlock);

    /*!
     * @brief       Adds an object to the set if it is not already present.
     * @dicussion   Adds an object to the set if it is not already present,
     *              storing it in sorted order if there is an order function.
     * @param       anObject  The OSMetaClassBase-derived object to be added
     *              to the ordered set.
     * @return      true if the object was added to the set, false if already present.
     */
	bool setObject(const OSMetaClassBase * anObject);

    /*!
     * @brief       Adds an object to the set at index 0, if it is not already present.
     * @dicussion   Adds an object to the set at index 0, if it is not already present.
     *              This function ignores any ordering function of the ordered set,
     *              and can disrupt the automatic sorting mechanism.
     *              Only call this function if you are managing the ordered set directly.
     * @param       anObject  The OSMetaClassBase-derived object to be added
     *              to the ordered set.
     * @return      true if the object was added to the set, false if already present.
     */
	bool setFirstObject(const OSMetaClassBase * anObject);

    /*!
     * @brief       Adds an object to the set at the last index, if it is not already present.
     * @dicussion   Adds an object to the set at the last index, if it is not already present.
     *              This function ignores any ordering function of the ordered set,
     *              and can disrupt the automatic sorting mechanism.
     *              Only call this function if you are managing the ordered set directly.
     * @param       anObject  The OSMetaClassBase-derived object to be added
     *              to the ordered set.
     * @return      true if the object was added to the set, false if already present.
     */
	bool setLastObject(const OSMetaClassBase * anObject);

    /*!
     * @brief       Returns the object at index 0 in the ordered set.
     * @dicussion   Returns the object at index 0 in the ordered set, or NULL if the set
     *              is empty.
     * @return      the first object in the set or NULL.
     *              The returned object will be released if later removed from the set;
     *              if you plan to store the reference, you should call retain() on it.
     */
	OSObject * getFirstObject() const;

    /*!
     * @brief       Returns the object at the last index in the ordered set.
     * @dicussion   Returns the object at the last index in the ordered set, or NULL if the set
     *              is empty.
     * @return      the last object in the set or NULL.
     *              The returned object will be released if later removed from the set;
     *              if you plan to store the reference, you should call retain() on it.
     */
	OSObject * getLastObject() const;

    /*!
     * @brief       Calls the ordered set's order function against a NULL object.
     * @dicussion   This function calls the ordered set's OSOrderBlock  order function
     *              with anObject, NULL, and returns the result of that function.
     * @param       anObject  The OSMetaClassBase-derived object to be ordered.
     * @return      The ordering value for the object.
     */
	int32_t orderObject(const OSMetaClassBase * anObject);
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class OSOrderedSet OSOrderedSet.iig:70-191 */


#define OSOrderedSet_Methods \
\
public:\
\
    static OSOrderedSetPtr\
    withCapacity(\
        uint32_t capacity,\
        OSOrderBlock orderBlock);\
\
    bool\
    setObject(\
        const OSMetaClassBase * anObject);\
\
    bool\
    setFirstObject(\
        const OSMetaClassBase * anObject);\
\
    bool\
    setLastObject(\
        const OSMetaClassBase * anObject);\
\
    OSObject *\
    getFirstObject(\
) const;\
\
    OSObject *\
    getLastObject(\
) const;\
\
    int32_t\
    orderObject(\
        const OSMetaClassBase * anObject);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define OSOrderedSet_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define OSOrderedSet_VirtualMethods \
\
public:\
\
    virtual bool\
    init(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    free(\
) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gOSOrderedSetMetaClass;
extern const OSClassLoadInformation OSOrderedSet_Class;

class OSOrderedSetMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class OSOrderedSetInterface : public OSInterface
{
public:
};

struct OSOrderedSet_IVars;
struct OSOrderedSet_LocalIVars;

class OSOrderedSet : public OSSet, public OSOrderedSetInterface
{
#if !KERNEL
    friend class OSOrderedSetMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
#ifdef OSOrderedSet_DECLARE_IVARS
OSOrderedSet_DECLARE_IVARS
#else /* OSOrderedSet_DECLARE_IVARS */
    union
    {
        OSOrderedSet_IVars * ivars;
        OSOrderedSet_LocalIVars * lvars;
    };
#endif /* OSOrderedSet_DECLARE_IVARS */
#endif /* !KERNEL */

#if !KERNEL
    static OSMetaClass *
    sGetMetaClass() { return gOSOrderedSetMetaClass; };
#endif /* KERNEL */

    using super = OSSet;

#if !KERNEL
    OSOrderedSet_Methods
    OSOrderedSet_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* OSOrderedSet.iig:193- */

#endif /* ! _IOKIT_OSORDEREDSET_H */
