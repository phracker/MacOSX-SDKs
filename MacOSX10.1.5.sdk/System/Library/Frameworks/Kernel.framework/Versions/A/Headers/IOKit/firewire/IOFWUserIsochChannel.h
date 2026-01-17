/*
 * Copyright (c) 1998-2001 Apple Computer, Inc. All rights reserved.
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
 *  IOFWUserIsochChannel.h
 *  IOFireWireFamily
 *
 *  Created by noggin on Tue May 15 2001.
 *  Copyright (c) 2001 Apple Computer, Inc. All rights reserved.
 *
 */

#include <IOKit/firewire/IOFWIsochChannel.h>

class IOFWUserIsochChannel: public IOFWIsochChannel
{
	OSDeclareDefaultStructors(IOFWUserIsochChannel)
	
 public:
    virtual IOReturn allocateChannel();
    virtual IOReturn releaseChannel();
    virtual IOReturn start();
    virtual IOReturn stop();
	
 public:
	virtual IOReturn	userAllocateChannelBegin(
								IOFWSpeed	inSpeed,
//								UInt32		inAllowedChansHi,
//								UInt32		inAllowedChansLo,
								UInt64		inAllowedChans,
								IOFWSpeed*	outActualSpeed,
								UInt32*		outActualChannel) ;
	virtual IOReturn	userReleaseChannelComplete() ;
	virtual IOReturn	allocateListenerPorts() ;
	virtual IOReturn	allocateTalkerPort() ;
	
 protected:
	Boolean			fBandwidthAllocated ;
} ;
