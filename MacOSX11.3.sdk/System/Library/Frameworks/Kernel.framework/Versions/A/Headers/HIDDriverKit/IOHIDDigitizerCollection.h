/* iig(DriverKit-107.100.6) generated from IOHIDDigitizerCollection.iig */

/* IOHIDDigitizerCollection.iig:1-44 */
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

#ifndef _HIDDRIVERKIT_IOHIDDIGITIZERCOLLECTION_H
#define _HIDDRIVERKIT_IOHIDDIGITIZERCOLLECTION_H

#include <DriverKit/OSContainer.h>  /* .iig include */
#include <DriverKit/IOTypes.h>

class IOHIDElement;
class OSArray;

typedef enum {
    kIOHIDDigitizerCollectionTypeStylus = 0,
    kIOHIDDigitizerCollectionTypePuck,
    kIOHIDDigitizerCollectionTypeFinger,
    kIOHIDDigitizerCollectionTypeHand
} IOHIDDigitizerCollectionType;

/* source class IOHIDDigitizerCollection IOHIDDigitizerCollection.iig:45-77 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

class LOCALONLY IOHIDDigitizerCollection : public OSContainer
{
private:
    bool initWithType(IOHIDDigitizerCollectionType type,
                      IOHIDElement *parentCollection);
    
public:
    virtual void free(void) override;
    
    static IOHIDDigitizerCollection *withType(IOHIDDigitizerCollectionType type,
                                              IOHIDElement *parentCollection);
    
    void addElement(IOHIDElement *element);
    OSArray *getElements();
    
    IOHIDElement *getParentCollection();

    IOHIDDigitizerCollectionType getType();
    
    bool getTouch();
    void setTouch(bool touch);
    
    bool getInRange();
    void setInRange(bool inRange);
    
    IOFixed getX();
    void setX(IOFixed x);
    
    IOFixed getY();
    void setY(IOFixed y);
    
    IOFixed getZ();
    void setZ(IOFixed z);
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOHIDDigitizerCollection IOHIDDigitizerCollection.iig:45-77 */


#define IOHIDDigitizerCollection_Methods \
\
public:\
\
    bool\
    initWithType(\
        IOHIDDigitizerCollectionType type,\
        IOHIDElement * parentCollection);\
\
    static IOHIDDigitizerCollection *\
    withType(\
        IOHIDDigitizerCollectionType type,\
        IOHIDElement * parentCollection);\
\
    void\
    addElement(\
        IOHIDElement * element);\
\
    OSArray *\
    getElements(\
);\
\
    IOHIDElement *\
    getParentCollection(\
);\
\
    IOHIDDigitizerCollectionType\
    getType(\
);\
\
    bool\
    getTouch(\
);\
\
    void\
    setTouch(\
        bool touch);\
\
    bool\
    getInRange(\
);\
\
    void\
    setInRange(\
        bool inRange);\
\
    IOFixed\
    getX(\
);\
\
    void\
    setX(\
        IOFixed x);\
\
    IOFixed\
    getY(\
);\
\
    void\
    setY(\
        IOFixed y);\
\
    IOFixed\
    getZ(\
);\
\
    void\
    setZ(\
        IOFixed z);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define IOHIDDigitizerCollection_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define IOHIDDigitizerCollection_VirtualMethods \
\
public:\
\
    virtual void\
    free(\
) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gIOHIDDigitizerCollectionMetaClass;
extern const OSClassLoadInformation IOHIDDigitizerCollection_Class;

class IOHIDDigitizerCollectionMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOHIDDigitizerCollectionInterface : public OSInterface
{
public:
};

struct IOHIDDigitizerCollection_IVars;
struct IOHIDDigitizerCollection_LocalIVars;

class IOHIDDigitizerCollection : public OSContainer, public IOHIDDigitizerCollectionInterface
{
#if !KERNEL
    friend class IOHIDDigitizerCollectionMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
    union
    {
        IOHIDDigitizerCollection_IVars * ivars;
        IOHIDDigitizerCollection_LocalIVars * lvars;
    };
#endif /* !KERNEL */

    using super = OSContainer;

#if !KERNEL
    IOHIDDigitizerCollection_Methods
    IOHIDDigitizerCollection_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* IOHIDDigitizerCollection.iig:79- */

#endif /* _HIDDRIVERKIT_IOHIDDIGITIZERCOLLECTION_H */
