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
 *  IOFWUserIsochPortProxy.h
 *  IOFireWireFamily
 *
 *  Created by NWG on Tue Mar 20 2001.
 *  Copyright (c) 2001 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef _IOKIT_IOFWUserIsochPortProxy_H
#define _IOKIT_IOFWUserIsochPortProxy_H

//#include <libkern/c++/OSObject.h>
//#include <IOKit/IOReturn.h>
//#include <IOKit/IOTypes.h>
#include <IOKit/firewire/IOFWLocalIsochPort.h>
#include <IOKit/firewire/IOFireWireUserClient.h>

class IOFWUserIsochPort: public IOFWIsochPort
{
	OSDeclareDefaultStructors(IOFWUserIsochPort)

 public:	
	virtual bool	init() ;

	// Return maximum speed and channels supported
	// (bit n set = chan n supported)
    virtual IOReturn getSupported(IOFWSpeed &maxSpeed, UInt64 &chanSupported) ;

	// Allocate hardware resources for port
    virtual IOReturn allocatePort(IOFWSpeed speed, UInt32 chan) ;
    virtual IOReturn releasePort() ;	// Free hardware resources
    virtual IOReturn start() ;			// Start port processing packets
    virtual IOReturn stop() ;			// Stop processing packets

 protected:
	IOFWSpeed	fMaxSpeed ;
	UInt32		fChanSupported ;
} ;

class IOFWUserIsochPortProxy: public OSObject
{
	OSDeclareDefaultStructors(IOFWUserIsochPortProxy)
	
 public:
	virtual Boolean				init(
										IOFireWireUserClient*	inUserClient) ;

    virtual IOReturn getSupported(IOFWSpeed &maxSpeed, UInt64 &chanSupported) ;

    virtual IOReturn allocatePort(IOFWSpeed speed, UInt32 chan) ;
    virtual IOReturn releasePort() ;	// Free hardware resources
    virtual IOReturn start() ;			// Start port processing packets
    virtual IOReturn stop() ;			// Stop processing packets

	virtual const IOFWIsochPort* getPort() const { return fPort; }
	
 protected:
	IOFireWireUserClient*	fUserClient ;
	IOFWIsochPort*			fPort ;
	Boolean					fPortStarted ;
	Boolean					fPortAllocated ;
	
	virtual void				free() ;

} ;

class IOFWUserLocalIsochPortProxy: public IOFWUserIsochPortProxy
{
	OSDeclareDefaultStructors(IOFWUserLocalIsochPortProxy)
	
 public:

	virtual Boolean				initWithUserDCLProgram(
										FWLocalIsochPortAllocateParams*	inParams,
										IOFireWireUserClient*		inUserClient) ;

    virtual IOReturn getSupported(IOFWSpeed &maxSpeed, UInt64 &chanSupported) ;
    virtual IOReturn allocatePort(IOFWSpeed speed, UInt32 chan) ;
	virtual	IOReturn			releasePort() ;

	// --- utility functions ----------
	static Boolean				getDCLDataBuffer(
										const DCLCommandStruct*		inDCL,
										IOVirtualAddress*			outDataBuffer,
										IOByteCount*				outDataLength) ;
	static void					setDCLDataBuffer(
										DCLCommandStruct*			inDCL,
										IOVirtualAddress			inDataBuffer,
										IOByteCount					inDataLength) ;
	static IOByteCount			getDCLSize(
										DCLCommandStruct*			inDCL) ;
	static void					printDCLProgram(
										const DCLCommandStruct*		inDCL,
										UInt32						inDCLCount) ;
	virtual IOReturn			convertToKernelDCL(
										DCLUpdateDCLListStruct*	inDCLCommand,
										DCLCommandStruct*		inUserDCLTable[],
										DCLCommandStruct*		inUserToKernelDCLLookupTable[],
										UInt32					inLookupTableLength ) ;
	virtual IOReturn			convertToKernelDCL(
										DCLJumpStruct*			inDCLCommand,
										DCLCommandStruct*		inUserDCLTable[],
										DCLCommandStruct*		inUserToKernelDCLLookupTable[],
										UInt32					inLookupTableLength ) ;
	virtual IOReturn			convertToKernelDCL(
										DCLPtrTimeStampStruct*	inDCLCommand,
										IOVirtualRange			inBufferRanges[],
										UInt32					inBufferRangeCount,
										IOMemoryDescriptor*		inBufferMem) ;
	virtual IOReturn			convertToKernelDCL(
										DCLCallProcStruct*		inDCLCommand,
										DCLCommandStruct*		inUserDCL) ;
	static	Boolean				findOffsetInRanges(
										IOVirtualAddress		inAddress,
										IOVirtualRange			inRanges[],
										UInt32					inRangeCount,
										IOByteCount*			outOffset) ;
	static Boolean				userToKernLookup(
										DCLCommandStruct*	inDCLCommand,
										DCLCommandStruct*	inUserDCLList[],
										DCLCommandStruct*	inKernDCLList[],
										UInt32				inTableLength,
										DCLCommandStruct**	outDCLCommand) ;
	static	void				dclCallProcHandler(
										DCLCommandStruct*		pDCLCommand) ;
	virtual IOReturn			setAsyncRef_DCLCallProc(
										OSAsyncReference		asyncRef,
										DCLCallCommandProcPtr	inProc) ;
	virtual IOReturn			modifyJumpDCL(
										UInt32				inJumpDCLCompilerData,
										UInt32				inLabelDCLCompilerData) ;

 protected:
//	IOFWLocalIsochPort*		fLocalPort ;
	IOMemoryDescriptor*		fUserDCLProgramMem ;
	IOByteCount				fDCLProgramBytes ;
	IOMemoryDescriptor*		fUserBufferMem ;
	Boolean					fUserBufferMemPrepared ;
	Boolean					fUserDCLProgramMemPrepared ;
	
	UInt8*					fKernDCLProgramBuffer ;
	DCLCommandStruct*		fKernDCLProgramStart ;
	
	Boolean					fTalking ;
	UInt32					fStartState ;
	UInt32					fStartMask ;
	UInt32					fStartEvent ;

	// lookup table
	UInt32					fUserToKernelDCLLookupTableLength ;
	DCLCommandStruct**		fUserToKernelDCLLookupTable ;
	OSAsyncReference		fDCLCallProcAsyncNotificationRef ;
	
	virtual void			free() ;
	virtual IOReturn		createPort() ;
} ;


#endif //_IOKIT_IOFWUserIsochPortProxy_H