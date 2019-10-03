/* iig(DriverKit-73.0.1) generated from IOUserClient.iig */

/* IOUserClient.iig:1-172 */
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
#include <IOKit/IOUserClient.h>
#endif

#ifndef _IOKIT_UIOUSERCLIENT_H
#define _IOKIT_UIOUSERCLIENT_H

#include <DriverKit/OSAction.h>  /* .iig include */
#include <DriverKit/IOService.h>  /* .iig include */

class IOMemoryDescriptor;
class IOBufferMemoryDescriptor;

enum {
	kIOUserClientScalarArrayCountMax  = 16,
};
typedef uint64_t IOUserClientScalarArray[kIOUserClientScalarArrayCountMax];

enum {
	kIOUserClientAsyncReferenceCountMax  = 16,
};
typedef uint64_t IOUserClientAsyncReferenceArray[kIOUserClientAsyncReferenceCountMax];

enum {
	kIOUserClientAsyncArgumentsCountMax  = 16,
};
typedef uint64_t IOUserClientAsyncArgumentsArray[kIOUserClientAsyncArgumentsCountMax];

// CopyClientMemoryForType options
enum {
	kIOUserClientMemoryReadOnly  = 0x00000001,
};


/*! @enum
 *   @abstract Constant to denote a variable length structure argument to IOUserClient.
 *   @constant kIOUserClientVariableStructureSize Use in the structures IOUserClientMethodDispatch to specify the size of the structure is variable.
 */
enum {
	kIOUserClientVariableStructureSize = 0xffffffff
};


enum {
#define IO_USER_CLIENT_METHOD_ARGUMENTS_CURRENT_VERSION    2
	kIOUserClientMethodArgumentsCurrentVersion = IO_USER_CLIENT_METHOD_ARGUMENTS_CURRENT_VERSION
};

/*!
 * @struct      IOUserClientMethodArguments
 * @brief       Holds arguments from IOKit.framework IOConnectMethod calls.
 * @discussion  Any argument may be passed as NULL if not passed by the caller.
 * @field       selector Selector argument to IOConnectMethod.
 * @field       scalarInput Array of scalars from caller.
 * @field       scalarInputCount Count of valid scalars in scalarInput.
 * @field       structureInput OSData object containing structure input from IOConnectMethod.
 * @field       structureInputDescriptor IOMemoryDescriptor containing structure input from IOConnectMethod.
 *				This parameter is only set for large structures, and if set structureInput will be NULL.
 * @field       scalarOutput Array of scalars to return to the caller.
 * @field       scalarOutputCount Count of scalars to return to the caller in scalarOutput.
 * @field       structureOutput An OSData to be returned to the caller as structure output.
 *				A reference will be consumed by the caller. It is an error to set this field if
 *              structureOutputDescriptor was passed in
 * @field       structureOutputDescriptor A IOMemoryDescriptor specified by the caller for structure output.
 * @field       structureOutputMaximumSize Maximum size of structure output specified by caller
 *              or kIOUserClientVariableStructureSize.
 * @field       completion For IOConnectAsyncMethod, an OSAction used to deliver async data to the caller.
 *              It is only retained during the invocation of ExternalMethod and should be retained if
 *              used beyond then.
 */

struct IOUserClientMethodArguments {
	uint64_t            			version;
	uint64_t                        selector;
	OSAction                      * completion;
    const uint64_t			      * scalarInput;
	uint32_t						scalarInputCount;
	OSData 						  * structureInput;
	IOMemoryDescriptor            * structureInputDescriptor;
	uint64_t                      * scalarOutput;
	uint32_t                        scalarOutputCount;
	OSData                        * structureOutput;
	IOMemoryDescriptor            * structureOutputDescriptor;
	uint64_t                        structureOutputMaximumSize;
	uint64_t                        __reserved[30];
};

typedef kern_return_t (*IOUserClientMethodFunction)(
	OSObject * target,
	void * reference,
    IOUserClientMethodArguments * arguments);

/*!
 * @struct      IOUserClientMethodDispatch
 * @brief       Used to check fields in IOUserClientMethodArguments
 * @field       function to invoke after making the checks specified below. If NULL and all checks pass,
 *              kIOReturnNoCompletion will be returned for the caller to implement the method.
 * @field       checkCompletionExists
 *              if true completion field must be set,
 *              if false must be zero,
 *              if -1U don't care
 * @field       checkScalarInputCount
 *              if has value kIOUserClientVariableStructureSize don't care,
 *              otherwise must equal args->scalarInputCount
 * @field       checkStructureInputSize
 *              if has value kIOUserClientVariableStructureSize don't care,
 *              otherwise must equal length of structureInput or structureInputDescriptor
 * @field       checkScalarOutputCount
 *              if has value kIOUserClientVariableStructureSize don't care,
 *              otherwise must equal args->scalarOutputCount
 * @field       checkStructureOutputSize
 *              if has value kIOUserClientVariableStructureSize don't care,
 *              otherwise must equal length of structureOutputMaximumSize
 */

struct IOUserClientMethodDispatch {
	IOUserClientMethodFunction function;
	uint32_t			       checkCompletionExists;
	uint32_t			       checkScalarInputCount;
	uint32_t			       checkStructureInputSize;
	uint32_t			       checkScalarOutputCount;
	uint32_t			       checkStructureOutputSize;
};

/*!
 * @class IOUserClient
 *
 * @abstract
 * IOUserClient represents a connection opened by IOServiceOpen in the IOKit.framework.
 *
 * @discussion
 * An application may open an IOUserClient by calling IOServiceOpen(). This results in a call
 * to the IOService::NewUserClient API to create an instance representing the connection.
 * and to receive untyped data via IOConnectMethod/IOConnectAsyncMethod.
 * As an IOService subclass, IOUserClient receives the normal Start()/Stop() lifecyle calls.
 *

@iig implementation
#include <DriverKit/IOBufferMemoryDescriptor.h>
@iig end
*/

/* class IOUserClient IOUserClient.iig:173-268 */

#define IOUserClient_AsyncCompletion_ID            0xdbc5b2e5d2b446f4ULL
#define IOUserClient_CopyClientMemoryForType_ID            0x8399bdb3d0b4f474ULL
#define IOUserClient__ExternalMethod_ID            0xcfe0c99e739d92f9ULL
#define IOUserClient_KernelCompletion_ID            0xf609f134c9046444ULL

#define IOUserClient_AsyncCompletion_Args \
        OSAction * action, \
        IOReturn status, \
        const unsigned long long * asyncData, \
        uint32_t asyncDataCount

#define IOUserClient_CopyClientMemoryForType_Args \
        uint64_t type, \
        uint64_t * options, \
        IOMemoryDescriptor ** memory

#define IOUserClient__ExternalMethod_Args \
        uint64_t selector, \
        const unsigned long long * scalarInput, \
        uint32_t scalarInputCount, \
        OSData * structureInput, \
        IOMemoryDescriptor * structureInputDescriptor, \
        unsigned long long * scalarOutput, \
        uint32_t * scalarOutputCount, \
        uint64_t structureOutputMaximumSize, \
        OSData ** structureOutput, \
        IOMemoryDescriptor * structureOutputDescriptor, \
        OSAction * completion

#define IOUserClient_KernelCompletion_Args \
        OSAction * action, \
        IOReturn status, \
        const unsigned long long * asyncData, \
        uint32_t asyncDataCount

#define IOUserClient_Methods \
\
public:\
\
    virtual kern_return_t\
    Dispatch(const IORPC rpc) APPLE_KEXT_OVERRIDE;\
\
    static kern_return_t\
    _Dispatch(IOUserClient * self, const IORPC rpc);\
\
    void\
    AsyncCompletion(\
        OSAction * action,\
        IOReturn status,\
        const IOUserClientAsyncArgumentsArray asyncData,\
        uint32_t asyncDataCount,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    CopyClientMemoryForType(\
        uint64_t type,\
        uint64_t * options,\
        IOMemoryDescriptor ** memory,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    _ExternalMethod(\
        uint64_t selector,\
        const IOUserClientScalarArray scalarInput,\
        uint32_t scalarInputCount,\
        OSData * structureInput,\
        IOMemoryDescriptor * structureInputDescriptor,\
        IOUserClientScalarArray scalarOutput,\
        uint32_t * scalarOutputCount,\
        uint64_t structureOutputMaximumSize,\
        OSData ** structureOutput,\
        IOMemoryDescriptor * structureOutputDescriptor,\
        OSAction * completion,\
        OSDispatchMethod supermethod = NULL);\
\
    kern_return_t\
    CreateActionKernelCompletion(size_t referenceSize, OSAction ** action);\
\
\
protected:\
    /* _Impl methods */\
\
    kern_return_t\
    _ExternalMethod_Impl(IOUserClient__ExternalMethod_Args);\
\
\
public:\
    /* _Invoke methods */\
\
    typedef void (*AsyncCompletion_Handler)(OSMetaClassBase * target, IOUserClient_AsyncCompletion_Args);\
    static kern_return_t\
    AsyncCompletion_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        AsyncCompletion_Handler func);\
\
    typedef kern_return_t (*CopyClientMemoryForType_Handler)(OSMetaClassBase * target, IOUserClient_CopyClientMemoryForType_Args);\
    static kern_return_t\
    CopyClientMemoryForType_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        CopyClientMemoryForType_Handler func);\
\
    typedef kern_return_t (*_ExternalMethod_Handler)(OSMetaClassBase * target, IOUserClient__ExternalMethod_Args);\
    static kern_return_t\
    _ExternalMethod_Invoke(const IORPC rpc,\
        OSMetaClassBase * target,\
        _ExternalMethod_Handler func);\
\


#define IOUserClient_KernelMethods \
\
protected:\
    /* _Impl methods */\
\
    void\
    KernelCompletion_Impl(IOUserClient_KernelCompletion_Args);\
\


#define IOUserClient_VirtualMethods \
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
    virtual kern_return_t\
    ExternalMethod(\
        uint64_t selector,\
        IOUserClientMethodArguments * arguments,\
        const IOUserClientMethodDispatch * dispatch,\
        OSObject * target,\
        void * reference) APPLE_KEXT_OVERRIDE;\
\




/* IOUserClient.iig:270- */

#endif /* ! _IOKIT_UIOUSERCLIENT_H */
