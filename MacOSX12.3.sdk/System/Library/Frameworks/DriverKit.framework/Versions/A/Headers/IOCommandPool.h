/* iig(DriverKit-192.100.7) generated from IOCommandPool.iig */

/* IOCommandPool.iig:1-41 */
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

#ifndef _IOKIT_UIOCOMMANDPOOL_H
#define _IOKIT_UIOCOMMANDPOOL_H

#include <DriverKit/IOCommand.h>  /* .iig include */


#define LIBKERN_CONSUMED
#define LIBKERN_RETURNS_NOT_RETAINED


class IOCommandPool;
typedef IOCommandPool * IOCommandPoolPtr;

/* source class IOCommandPool IOCommandPool.iig:42-128 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
 * @class IOCommandPool
 * @abstract Manipulates a pool of commands which inherit from IOCommand.
 * @discussion
 * The IOCommandPool class is used to manipulate a pool of commands which
 * inherit from IOCommand. The caller must put commands in the pool by creating
 * the command (via the controller's factory method or a memory allocation)
 * and calling the returnCommand method with the newly created command as its
 * argument.
 */

class LOCALONLY IOCommandPool : public OSObject
{
public:

	// OSObject

	virtual bool
	init() override;

	virtual void
	free() override;

	/*!
	 * @abstract Primary initializer for an IOCommandPool object.
	 * @discussion Primary initializer for an IOCommandPool.
	 *             Should probably use IOCommandPool::withQueue() as it is easier to use.
	 * @param queue The IODispatchQueue that this command pool should synchronize with.
	 *              This queue must have been allocated with the kIODispatchQueueReentrant
     *              option.
	 * @result Returns true if command pool was successfully initialized.
	 */
	virtual bool initWithQueue(IODispatchQueue * queue);

	/*!
	* @abstract Primary factory method for the IOCommandPool class
	* @discussion The withQueue method is what is known as a factory method. It creates
	*             a new instance of an IOCommandPool and returns a pointer to that object.
	* @param queue The IODispatchQueue that this command pool should synchronize with.
	 *              This queue must have been allocated with the kIODispatchQueueReentrant
     *              option.
	* Returns a pointer to an instance of IOCommandPool if successful,
	* otherwise NULL.
	*/
	static IOCommandPoolPtr
	withQueue(IODispatchQueue * queue);

	/*!
	 * @discussion The getCommand method is used to get a pointer to an object of type IOCommand from the pool.
	 * @param blockForCommand If the caller would like to have its thread slept until a command is
	 *                         available, it should pass true, else false.
	 * @result If the caller passes true in blockForCommand, getCommand guarantees that
	 * the result will be a pointer to an IOCommand object from the pool. If
	 * the caller passes false, s/he is responsible for checking whether a non-NULL
	 * pointer was returned.
	 */
	virtual IOCommandPtr getCommand(
		bool blockForCommand = true);

	/*!
	 * @discussion The returnCommand method is used to place an object of type IOCommand
	 *             into the pool, whether it be the first time, or the 1000th time.
	 * @param command The command to place in the pool.
	 */
	virtual void returnCommand(LIBKERN_CONSUMED IOCommand *command);

	/*!
	 * @discussion The gatedGetCommand method is used to serialize the extraction of a
	 *             command from the pool synchronized with the pool's queue.
	 * @param command A pointer to a pointer to an IOCommand object where the returned
	 *                command will be stored.
	 * @param blockForCommand A bool that indicates whether to block the request until a command
	 *                        becomes available.
	 * @result kIOReturnNoResources if no command is available and the client
	 *         doesn't wish to block until one does become available.
	 *         kIOReturnSuccess if the vCommand argument is valid.
	 */
	virtual kern_return_t gatedGetCommand(
		LIBKERN_RETURNS_NOT_RETAINED IOCommand **command, bool blockForCommand);

	/*!
	 * @discussion The gatedReturnCommand method is used to serialize the return of a
	 *             command to the pool synchronized with the pool's queue.
	 * @param command A pointer to the IOCommand object to be returned to the pool.
     * @result        kIOReturnSuccess on success. See IOReturn.h for error codes.
	 */
	virtual kern_return_t gatedReturnCommand(IOCommand *command);
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOCommandPool IOCommandPool.iig:42-128 */


#define IOCommandPool_Methods \
\
public:\
\
    static IOCommandPoolPtr\
    withQueue(\
        IODispatchQueue * queue);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define IOCommandPool_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define IOCommandPool_VirtualMethods \
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
    virtual bool\
    initWithQueue(\
        IODispatchQueue * queue) APPLE_KEXT_OVERRIDE;\
\
    virtual IOCommandPtr\
    getCommand(\
        bool blockForCommand = true) APPLE_KEXT_OVERRIDE;\
\
    virtual void\
    returnCommand(\
        IOCommand * command) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    gatedGetCommand(\
        IOCommand ** command,\
        bool blockForCommand) APPLE_KEXT_OVERRIDE;\
\
    virtual kern_return_t\
    gatedReturnCommand(\
        IOCommand * command) APPLE_KEXT_OVERRIDE;\
\


#if !KERNEL

extern OSMetaClass          * gIOCommandPoolMetaClass;
extern const OSClassLoadInformation IOCommandPool_Class;

class IOCommandPoolMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOCommandPoolInterface : public OSInterface
{
public:
    virtual bool
    initWithQueue(IODispatchQueue * queue) = 0;

    virtual IOCommandPtr
    getCommand(bool blockForCommand) = 0;

    virtual void
    returnCommand(IOCommand * command) = 0;

    virtual kern_return_t
    gatedGetCommand(IOCommand ** command,
        bool blockForCommand) = 0;

    virtual kern_return_t
    gatedReturnCommand(IOCommand * command) = 0;

    bool
    initWithQueue_Call(IODispatchQueue * queue)  { return initWithQueue(queue); };\

    IOCommandPtr
    getCommand_Call(bool blockForCommand)  { return getCommand(blockForCommand); };\

    void
    returnCommand_Call(IOCommand * command)  { return returnCommand(command); };\

    kern_return_t
    gatedGetCommand_Call(IOCommand ** command,
        bool blockForCommand)  { return gatedGetCommand(command, blockForCommand); };\

    kern_return_t
    gatedReturnCommand_Call(IOCommand * command)  { return gatedReturnCommand(command); };\

};

struct IOCommandPool_IVars;
struct IOCommandPool_LocalIVars;

class IOCommandPool : public OSObject, public IOCommandPoolInterface
{
#if !KERNEL
    friend class IOCommandPoolMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
#ifdef IOCommandPool_DECLARE_IVARS
IOCommandPool_DECLARE_IVARS
#else /* IOCommandPool_DECLARE_IVARS */
    union
    {
        IOCommandPool_IVars * ivars;
        IOCommandPool_LocalIVars * lvars;
    };
#endif /* IOCommandPool_DECLARE_IVARS */
#endif /* !KERNEL */

#if !KERNEL
    static OSMetaClass *
    sGetMetaClass() { return gIOCommandPoolMetaClass; };
#endif /* KERNEL */

    using super = OSObject;

#if !KERNEL
    IOCommandPool_Methods
    IOCommandPool_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* IOCommandPool.iig:130- */

#endif /* ! _IOKIT_UIOCOMMANDPOOL_H */
