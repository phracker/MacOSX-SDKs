/* iig(DriverKit-192.100.7) generated from IOCommand.iig */

/* IOCommand.iig:1-38 */
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


#ifndef _IOKIT_UIOCOMMAND_H
#define _IOKIT_UIOCOMMAND_H

#include <DriverKit/OSObject.h>  /* .iig include */
#include <DriverKit/queue.h>

class IOCommand;
typedef IOCommand * IOCommandPtr;

/* source class IOCommand IOCommand.iig:39-76 */

#if __DOCUMENTATION__
#define KERNEL IIG_KERNEL

/*!
 * @class IOCommand
 *
 * @abstract
 * This class is an abstract class which represents an I/O command.
 *
 * @discussion
 * This class is an abstract class which represents an I/O command passed
 * from a device driver to a controller. All controller commands (e.g. IOATACommand)
 * should inherit from this class.
 */

class LOCALONLY IOCommand : public OSObject
{
public:

	// OSObject

	virtual bool
	init() override;
	virtual void
	free() override;

	// IOCommand

    /*!
     * @brief       Accessor to queue chain structure used to queue commands.
     * @return      Queue chain structure used to queue commands.
     */
	queue_chain_t *
	CommandChain();    /* used to queue commands */

    /*!
     * @brief       Given the queue_chain_t from CommandChain, return the IOCommand instance.
     * @return      Queue used to queue commands.
     */
	static IOCommand *
	FromChain(queue_chain_t * link);
};

#undef KERNEL
#else /* __DOCUMENTATION__ */

/* generated class IOCommand IOCommand.iig:39-76 */


#define IOCommand_Methods \
\
public:\
\
    queue_chain_t *\
    CommandChain(\
);\
\
    static IOCommand *\
    FromChain(\
        queue_chain_t * link);\
\
\
protected:\
    /* _Impl methods */\
\
\
public:\
    /* _Invoke methods */\
\


#define IOCommand_KernelMethods \
\
protected:\
    /* _Impl methods */\
\


#define IOCommand_VirtualMethods \
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

extern OSMetaClass          * gIOCommandMetaClass;
extern const OSClassLoadInformation IOCommand_Class;

class IOCommandMetaClass : public OSMetaClass
{
public:
    virtual kern_return_t
    New(OSObject * instance) override;
};

#endif /* !KERNEL */

#if !KERNEL

class IOCommandInterface : public OSInterface
{
public:
};

struct IOCommand_IVars;
struct IOCommand_LocalIVars;

class IOCommand : public OSObject, public IOCommandInterface
{
#if !KERNEL
    friend class IOCommandMetaClass;
#endif /* !KERNEL */

#if !KERNEL
public:
#ifdef IOCommand_DECLARE_IVARS
IOCommand_DECLARE_IVARS
#else /* IOCommand_DECLARE_IVARS */
    union
    {
        IOCommand_IVars * ivars;
        IOCommand_LocalIVars * lvars;
    };
#endif /* IOCommand_DECLARE_IVARS */
#endif /* !KERNEL */

#if !KERNEL
    static OSMetaClass *
    sGetMetaClass() { return gIOCommandMetaClass; };
#endif /* KERNEL */

    using super = OSObject;

#if !KERNEL
    IOCommand_Methods
    IOCommand_VirtualMethods
#endif /* !KERNEL */

};
#endif /* !KERNEL */


#endif /* !__DOCUMENTATION__ */

/* IOCommand.iig:78- */

#endif /* ! _IOKIT_UIOCOMMAND_H */
