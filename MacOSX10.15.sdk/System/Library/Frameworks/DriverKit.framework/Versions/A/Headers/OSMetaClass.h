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

#ifndef _IOKIT_UOSMETACLASS_H
#define _IOKIT_UOSMETACLASS_H

#include <stddef.h>
#include <DriverKit/IORPC.h>

struct OSMetaClassBasePrivate;
class IODispatchQueue;
class OSMetaClass;
class OSObject;

struct OSClassLoadInformation
{
    const OSClassDescription * description;
	OSMetaClass **             metaPointer;
    uint32_t                   version;
    uint32_t                   instanceSize;
    uint64_t                   resv2[8];

    kern_return_t (*New)(OSMetaClass * instance);
    uint64_t                   resv3[8];
};


/*!
 * @class OSMetaClassBase
 *
 * @discussion
 * Base class for DriverKit objects.
 */
class OSMetaClassBase
{
public:
    _Atomic mutable int32_t  refcount;
    int32_t                  reserved;
    OSMetaClass            * meta;

public:
    inline void * operator new(size_t sz, void * placed) { return (placed); }

    /*!
     * @brief       Internal helper for OSDynamicCast. Not to be called directly.
	 */
    static OSMetaClassBase *
    safeMetaCast(const OSMetaClassBase * anObject,
                 const OSMetaClass     * toMeta);

    /*!
     * @brief       Internal helper for OSRequiredCast. Not to be called directly.
	 */
    static OSMetaClassBase *
    requiredMetaCast(const OSMetaClassBase * anObject,
                     const OSMetaClass     * toMeta);

    bool
    IsRemote();

    /*!
     * @brief       Internal helper for GetClassName. Not to be called directly.
	 */
    const OSMetaClass *
    GetClass();

    /*!
     * @brief       Returns the name of the class given an OSObject pointer.
     * @return      C-string class name, valid while the object is retained.
     */
    const char *
    GetClassName();

    /*!
     * @brief       Internal helper for GetClassName. Not to be called directly.
	 */
	virtual const OSMetaClass *
	getMetaClass() const;

    /*!
     * @brief       Retains the OSObject instance
     * @discussion  Increases the retain count of the instance by one.
     */
    virtual void
    retain() const;

    /*!
     * @brief       Releases the OSObject instance
     * @discussion  Decreases the retain count of the instance by one. If the count is then zero, frees the object.
     */
    virtual void
    release() const;

    /*!
     * @brief       Compares two objects
     * @discussion  The default implementation only compares the object pointers, however many container classes override to provide deeper comparison.
     */
	virtual bool
    isEqualTo(const OSMetaClassBase * anObject) const;

    /*!
     * @brief       Runtime internals
     */
    virtual kern_return_t
    Dispatch(IORPC invoke);

    /*!
     * @brief       Runtime internals
     */
    kern_return_t
    Invoke(IORPC invoke);

#if DRIVERKIT_PRIVATE
    OSMetaClassBasePrivate *
    Private() const;
    IODispatchQueue *
    QueueForObject(uint64_t msgid);
#endif
};

struct OSMetaClassPrivate;

/*!
 * @class OSMetaClassBase
 * @discussion
 * Base class for DriverKit runtime class system. Not called directly.
 */
class OSMetaClass : public OSMetaClassBase
{
public:
    OSMetaClassPrivate * metaClassPrivate;

    virtual kern_return_t
    New(OSObject * instance) = 0;
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class OSInterface
{
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define SUPERDISPATCH ((OSDispatchMethod) &super::_Dispatch)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*!
 * @brief       Helper function for OSTypeAlloc(). Not to be called directly.
 */
extern kern_return_t
OSObjectAllocate(
    OSMetaClass * meta,
    OSObject ** pObject);

/*!
 * @brief       Helper functions for OSDynamicCast(). Not to be called directly.
 */
#define OSTypeID(type)     g ## type ## MetaClass
#define OSTypeIDInst(inst) (inst)->GetClass()
#define OSMTypeID(type)    OSTypeID(type)

/*!
 * @define OSDynamicCast
 * @hidecontents
 *
 * @abstract
 * Safe type-casting for DriverKit C++ objects.
 *
 * @param type    The name of the desired class type, as a raw token,
 *                <i>not</i> a string or macro.
 * @param inst    A pointer to the object instance to be cast.
 *                May be <code>NULL</code>.
 *
 * @result
 * <code>inst</code> if it is non-<code>NULL</code>
 * and derived from <code>type</code>;
 * otherwise <code>NULL</code>.
 *
 * @discussion
 * <code>OSDynamicCast</code> is a rough equivalent
 * to the standard C++ RTTI <code>dynamic_cast&lt;T&gt;</code> operator.
 * Your code should use this instead of raw C type-casting,
 * and check the resulting value.
 * If the result is non-<code>NULL</code>,
 * the object is safe to use as the type-cast class;
 * if the result is <code>NULL</code>,
 * the object does not derive from the type-cast class
 * and your code should take appropriate steps to handle this case.
 */
#define OSDynamicCast(type, inst)   \
    (inst ? ((type *) OSMetaClassBase::safeMetaCast((inst), OSTypeID(type))) : NULL)

/*!
 * @define OSRequiredCast
 * @hidecontents
 *
 * @abstract
 * Safe type-casting for DriverKit C++ objects; aborts on failure.
 * The input parameters are the same as for the {@code OSDynamicCast} macro.
 *
 * @result {@code inst} if it is NULL or derived from {@code type};
 * otherwise triggers an abort.
 *
 * @discussion
 * This macro should be used in place of C-style casts or
 * <code>@link OSDynamicCast OSDynamicCast@/link</code>.
 * when the caller is absolutely sure that the passed
 * argument is a subclass of a required type.
 * It is equivalent to using {@code OSDynamicCast} and crashing with an abort on cast failure.
 */
#define OSRequiredCast(type, inst)   \
    (inst ? ((type *) OSMetaClassBase::requiredMetaCast((inst), OSTypeID(type))) : NULL)

/*!
 * @define OSTypeAlloc
 * @hidecontents
 *
 * @abstract
 * Allocates an instance of the named object class.
 *
 * @param type    The name of the desired class to be created,
 *                as a raw token, <i>not</i> a string or macro.
 *
 * @result
 * A pointer to the new, uninitialized object on success;
 * <code>NULL</code> on failure.
 *
 * @discussion
 *
 * The OSTypeAlloc macro is used to avoid binary compatibility difficulties
 * presented by the C++ <code>new</code> operator.
 */
#define OSTypeAlloc(type) \
({ \
    kern_return_t ret; \
    type * inst; \
    ret = OSObjectAllocate(OSTypeID(type), (OSObject **) &inst); \
    if (kIOReturnSuccess != ret) inst = NULL; \
    inst; \
})

#define APPLE_KEXT_OVERRIDE override

#endif  /* _IOKIT_UOSMETACLASS_H */
