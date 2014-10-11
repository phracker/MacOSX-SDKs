/*
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
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
 *  IOFWUserClientPhysAddrSpace.h
 *  IOFireWireFamily
 *
 *  Created by NWG on Fri Dec 08 2000.
 *  Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef _IOKIT_IOFWUserClientPhysAddrSpace_H_
#define _IOKIT_IOFWUserClientPhysAddrSpace_H_

#include <IOKit/firewire/IOFWAddressSpace.h>

class IOFWUserClientPhysicalAddressSpace: public IOFWPhysicalAddressSpace
{
	OSDeclareDefaultStructors(IOFWUserClientPhysicalAddressSpace)

 public:
 	virtual void		free() ;
    virtual bool 		initWithDesc(
    							IOFireWireBus *			bus,
								IOMemoryDescriptor*		mem);

	// getters
	UInt32				getSegmentCount() ;
	IOReturn			getSegments(
								UInt32*					ioMaxPages,
								IOPhysicalAddress		outPages[],
								IOByteCount				outLengths[]) ;

 protected:
	UInt32				mSegmentCount ;
} ;

#endif //_IOKIT_IOFWUserClientPhysAddrSpace_H_