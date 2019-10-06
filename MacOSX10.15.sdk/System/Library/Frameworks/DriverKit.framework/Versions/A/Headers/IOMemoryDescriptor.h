/* iig(DriverKit-73.0.1) generated from IOMemoryDescriptor.iig */

/* IOMemoryDescriptor.iig:1-87 */
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

#if !__IIG
#endif

#ifndef _IOKIT_UIOMEMORYDESCRIPTOR_H
#define _IOKIT_UIOMEMORYDESCRIPTOR_H

#include <DriverKit/OSObject.h>  /* .iig include */

class IOService;
class IOMemoryMap;


// IOMemoryDescriptor Create options
enum {
	kIOMemoryDirectionIn    = 0x00000001,
	kIOMemoryDirectionOut   = 0x00000002,
	kIOMemoryDirectionOutIn = kIOMemoryDirectionIn | kIOMemoryDirectionOut,
	kIOMemoryDirectionInOut = kIOMemoryDirectionOutIn,
};

// IOMemoryDescriptor CreateMapping options
enum {
	kIOMemoryMapFixedAddress          = 0x00000001,
	kIOMemoryMapReadOnly              = 0x00000002,
	kIOMemoryMapCacheModeDefault      = 0x00000000,
	kIOMemoryMapCacheModeInhibit      = 0x00000100,
	kIOMemoryMapCacheModeCopyback     = 0x00000200,
	kIOMemoryMapCacheModeWriteThrough = 0x00000400,
};

struct IOAddressSegment {
	uint64_t address;
	uint64_t length;
};

struct IOMDPrivateState {
	uint64_t length;
	uint64_t options;
};

/*!
 * @class IOMemoryDescriptor
 *
 * @abstract
 * IOMemoryDescriptor describes a memory buffer. 
 *
 * @discussion
 * To allocate memory for I/O or sharing, use IOBufferMemoryDescriptor::Create()
 * Methods in this class are used for memory that was supplied as a parameter.
 *

@iig implementation
#include <DriverKit/IOService.h>
@iig end
*/

/* class IOMemoryDescriptor IOMemoryDescriptor.iig:88-155 */

#define IOMemoryDescriptor__CopyState_ID            0xa2c0861d4118ce5eULL
#define IOMemoryDescriptor_CreateMapping_ID            0xc5e69b0414ff6ee5ULL
#define IOMemoryDescriptor_PrepareForDMA_ID            0xfd78519a57b70575ULL

#define IOMemoryDescriptor__CopyState_Args \
        IOMDPrivateState * state

#define IOMemoryDescriptor_CreateMapping_Args \
        uint64_t options, \
        uint64_t address, \
        uint64_t offset, \
        uint64_t length, \
        uint64_t alignment, \
        IOMemoryMap ** map

#define IOMemoryDescriptor_PrepareForDMA_Args \
        uint64_t options, \
        IOService * device, \
        uint64_t offset, \
        uint64_t length, \
        uint64_t * flags, \
        uint64_t * returnLength, \
        uint32_t * segmentsCount, \
        IOAddressSegment * segments

#define IOMemoryDescriptor_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOMemoryDescriptor * self, const IORPC rpc);\
\
    kern_return_t\
    _CopyState(\
        IOMDPrivateState * state,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    GetLength(\
        uint64_t * returnLength);\
\
    kern_return_t\
    CreateMapping(\
        uint64_t options,\
        uint64_t address,\
        uint64_t offset,\
        uint64_t length,\
        uint64_t alignment,\
        IOMemoryMap ** map,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    PrepareForDMA(\
        uint64_t options,\
        IOService * device,\
        uint64_t offset,\
        uint64_t length,\
        uint64_t * flags,\
        uint64_t * returnLength,\
        uint32_t * segmentsCount,\
        IOAddressSegment * segments,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    Map(\
        uint64_t options,\
        uint64_t address,\
        uint64_t length,\
        uint64_t alignment,\
        uint64_t * returnAddress,\
        uint64_t * returnLength);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\
    typedef kern_return_t (*_CopyState_Handler)(OSMetaClassBase * target, IOMemoryDescriptor__CopyState_Args);\
    static kern_return_t\
    _CopyState_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        _CopyState_Handler func);\
\
    typedef kern_return_t (*CreateMapping_Handler)(OSMetaClassBase * target, IOMemoryDescriptor_CreateMapping_Args);\
    static kern_return_t\
    CreateMapping_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        CreateMapping_Handler func);\
\
    typedef kern_return_t (*PrepareForDMA_Handler)(OSMetaClassBase * target, IOMemoryDescriptor_PrepareForDMA_Args);\
    static kern_return_t\
    PrepareForDMA_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        PrepareForDMA_Handler func);\
\


#define IOMemoryDescriptor_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    kern_return_t\
    _CopyState_Impl(IOMemoryDescriptor__CopyState_Args);\
\
    kern_return_t\
    CreateMapping_Impl(IOMemoryDescriptor_CreateMapping_Args);\
\
    kern_return_t\
    PrepareForDMA_Impl(IOMemoryDescriptor_PrepareForDMA_Args);\
\


#define IOMemoryDescriptor_VirtualMethods \
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



extern OSMetaClass          * gIOMemoryDescriptorMetaClass;
extern const OSClassLoadInformation IOMemoryDescriptor_Class;

class IOMemoryDescriptorMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
    virtual kern_return_t
    Dispatch(const IORPC rpc) override;
};



class IOMemoryDescriptorInterface : public OSInterface
{
public:
};

struct IOMemoryDescriptor_IVars;
struct IOMemoryDescriptor_LocalIVars;

class IOMemoryDescriptor : public OSObject, public IOMemoryDescriptorInterface
{
    friend class IOMemoryDescriptorMetaClass;

public:
    union
    {
        IOMemoryDescriptor_IVars * ivars;
        IOMemoryDescriptor_LocalIVars * lvars;
    };

    using super = OSObject;

    IOMemoryDescriptor_Methods
    IOMemoryDescriptor_VirtualMethods

};


/* IOMemoryDescriptor.iig:164- */



#endif /* ! _IOKIT_UIOMEMORYDESCRIPTOR_H */
