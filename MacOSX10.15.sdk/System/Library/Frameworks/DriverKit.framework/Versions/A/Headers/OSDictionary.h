/* iig(DriverKit-73.0.1) generated from OSDictionary.iig */

/* OSDictionary.iig:1-71 */
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

#ifndef _IOKIT_OSDICTIONARY_H
#define _IOKIT_OSDICTIONARY_H

#include <DriverKit/OSCollection.h>  /* .iig include */

class OSDictionary;
typedef OSDictionary * OSDictionaryPtr;

class OSString;

typedef bool (^OSDictionaryIterateObjectsBlock)(OSObject * key, OSObject * value);
typedef bool (*OSDictionaryIterateObjectsCallback)(void * refcon, OSObject * key, OSObject * value);


/*!
 * @class OSDictionary
 *
 * @abstract
 * OSDictionary provides an associative store using strings for keys.
 *
 * @discussion
 * OSDictionary is a collection class for objects derived from OSObject.
 * Storage and access are associative, based on keys that are uniqued OSObjects.
 * OSString is commonly used as a key since it is uniqued.
 * When adding an object to an OSDictionary, you provide a string identifier,
 * which can then used to retrieve that object or remove it from the dictionary.
 * Setting an object with a key that already has an associated object
 * replaces the original object.
 *
 * You must generally cast retrieved objects from
 * OSObject to the desired class using the OSDynamicCast macro.
 * This macro returns the object cast to the desired class,
 * or <code>NULL</code> if the object isn't derived from that class.
 *
 * As with all DriverKit collection classes,
 * OSDictionary retains objects added to it,
 * and releases objects removed from it (or replaced).
 * An OSDictionary also grows as necessary to accommodate new objects.
 *
 * OSArray provides no concurrency protection;
 * it's up to the usage context to provide any protection necessary.
 */

/* class OSDictionary OSDictionary.iig:72-264 */


#define OSDictionary_Methods \
\
public:\
\
    static OSDictionaryPtr\
    withCapacity(\
        uint32_t capacity);\
\
    static OSDictionaryPtr\
    withObjects(\
        const OSObject ** values,\
        const OSObject ** keys,\
        uint32_t count,\
        uint32_t capacity);\
\
    static OSDictionaryPtr\
    withDictionary(\
        const OSDictionary * dictionary,\
        uint32_t capacity);\
\
    bool\
    setObject(\
        const OSObject * aKey,\
        const OSMetaClassBase * anObject);\
\
    bool\
    setObject(\
        const char * aKey,\
        const OSMetaClassBase * anObject);\
\
    void\
    removeObject(\
        const OSObject * aKey);\
\
    void\
    removeObject(\
        const char * aKey);\
\
    bool\
    merge(\
        const OSDictionary * otherDictionary);\
\
    OSObject *\
    getObject(\
        const OSObject * aKey) const;\
\
    OSObject *\
    getObject(\
        const char * aKey) const;\
\
    bool\
    isEqualTo(\
        const OSDictionary * aDictionary,\
        const OSCollection * keys) const;\
\
    bool\
    isEqualTo(\
        const OSDictionary * aDictionary) const;\
\
    bool\
    iterateObjects(\
        OSDictionaryIterateObjectsBlock block) const;\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define OSDictionary_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define OSDictionary_VirtualMethods \
\
public:\
\
    virtual void\
    free(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual uint32_t\
    getCount(\
) const APPLE_KEXT_OVERRIDE;\
\
    virtual uint32_t\
    getCapacity(\
) const APPLE_KEXT_OVERRIDE;\
\
    virtual uint32_t\
    ensureCapacity(\
        uint32_t newCapacity) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    flushCollection(\
) APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    iterateObjects(\
        OSCollectionIterateObjectsBlock block) const APPLE_KEXT_OVERRIDE;\
\
    virtual bool\
    isEqualTo(\
        const OSMetaClassBase * anObject) const APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gOSDictionaryMetaClass;
extern const OSClassLoadInformation OSDictionary_Class;

class OSDictionaryMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class OSDictionaryInterface : public OSInterface
{
public:
};

struct OSDictionary_IVars;
struct OSDictionary_LocalIVars;

class OSDictionary : public OSCollection, public OSDictionaryInterface
{
#if !KERNEL
    friend class OSDictionaryMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        OSDictionary_IVars * ivars;
        OSDictionary_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = OSCollection;

#if !KERNEL
    OSDictionary_Methods
    OSDictionary_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */

/* OSDictionary.iig:266- */

#endif /* ! _IOKIT_OSDICTIONARY_H */
