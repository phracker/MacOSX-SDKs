/*
 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
															   * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 *
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

/*
 *
 *	IOFireWireAVCLocalNode.h
 *
 * Class to initialize the Local node's AVC Target mode support
 *
 */

#include <IOKit/IOService.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOMessage.h>

#include <IOKit/firewire/IOFireWireNub.h>
#include <IOKit/firewire/IOFireWireBus.h>
#include <IOKit/firewire/IOFWAddressSpace.h>

#include <IOKit/avc/IOFireWirePCRSpace.h>
#include <IOKit/avc/IOFireWireAVCTargetSpace.h>

class IOFireWireAVCLocalNode : public IOService
{
    OSDeclareDefaultStructors(IOFireWireAVCLocalNode)

protected:
	bool						fStarted;	
    IOFireWireNub *				fDevice;
    IOFireWirePCRSpace *		fPCRSpace;
    IOFireWireAVCTargetSpace *	fAVCTargetSpace;
	
public:

	// IOService overrides
    virtual bool		start(IOService *provider);
	virtual void		stop(IOService *provider);
	virtual void		free();
    virtual bool		finalize(IOOptionBits options);
    virtual IOReturn	message(UInt32 type, IOService *provider, void *argument);
};
	