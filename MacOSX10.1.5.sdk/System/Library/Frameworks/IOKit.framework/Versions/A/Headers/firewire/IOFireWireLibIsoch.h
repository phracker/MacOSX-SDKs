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
 *  IOFireWireLibIsoch.h
 *  IOFireWireFamily
 *
 *  Created by NWG on Mon Mar 19 2001.
 *  Copyright (c) 2001 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __IOFireWireLibIsoch_H__
#define __IOFireWireLibIsoch_H__

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOCFPlugIn.h>

#include <IOKit/firewire/IOFireWireFamilyCommon.h>
#include <IOKit/firewire/IOFWIsoch.h>
#include <IOKit/firewire/IOFireWireLib.h>

// === [CFPlugIn support constants] ========================================

//	uuid string: AAFDBDB0-489F-11D5-BC9B-003065423456
#define kIOFireWireRemoteIsochPortInterfaceID CFUUIDGetConstantUUIDWithBytes(kCFAllocatorDefault,\
											0xAA, 0xFD, 0xBD, 0xB0, 0x48, 0x9F, 0x11, 0xD5,\
											0xBC, 0x9B, 0x00, 0x30, 0x65, 0x42, 0x34, 0x56)

//  uuid string: 0F5E33C8-1350-11D5-9BE7-003065AF75CC
#define kIOFireWireLocalIsochPortInterfaceID CFUUIDGetConstantUUIDWithBytes(kCFAllocatorDefault,\
											0x0F, 0x5E, 0x33, 0xC8, 0x13, 0x50, 0x11, 0xD5,\
											0x9B, 0xE7, 0x00, 0x30, 0x65, 0xAF, 0x75, 0xCC)

//  uuid string: 2EC1E404-1350-11D5-89B5-003065AF75CC
#define kIOFireWireIsochChannelInterfaceID CFUUIDGetConstantUUIDWithBytes(kCFAllocatorDefault,\
											0x2E, 0xC1, 0xE4, 0x04, 0x13, 0x50, 0x11, 0xD5,\
											0x89, 0xB5, 0x00, 0x30, 0x65, 0xAF, 0x75, 0xCC)

//  uuid string: 4A4B1710-1350-11D5-9B12-003065AF75CC
#define kIOFireWireDCLCommandPoolInterfaceID CFUUIDGetConstantUUIDWithBytes(kCFAllocatorDefault,\
											0x4A, 0x4B, 0x17, 0x10, 0x13, 0x50, 0x11, 0xD5,\
											0x9B, 0x12, 0x00, 0x30, 0x65, 0xAF, 0x75, 0xCC)

typedef void	(*IOFireWireIsochChannelForceStopHandler)(
	IOFireWireLibIsochChannelRef	interface, 
	UInt32							stopCondition);

typedef IOReturn	(*IOFireWireLibIsochPortCallback)(
	IOFireWireLibIsochPortRef		interface) ;
	
typedef IOReturn	(*IOFireWireLibIsochPortAllocateCallback)(
	IOFireWireLibIsochPortRef		interface,
	IOFWSpeed						maxSpeed,
	UInt32							channel) ;

typedef IOReturn	(*IOFireWireLibIsochPortGetSupportedCallback)(
	IOFireWireLibIsochPortRef		interface,
	IOFWSpeed*						outMaxSpeed,
	UInt64*							outChanSupported) ;

// ============================================================
//
// IOFireWireLocalIsochPort
//
// ============================================================

#define IOFIREWIRELIBISOCHPORT_C_GUTS	\
	IOReturn	(*GetSupported)	( IOFireWireLibIsochPortRef self, IOFWSpeed* maxSpeed, UInt64* chanSupported ) ;	\
	IOReturn	(*AllocatePort)	( IOFireWireLibIsochPortRef self, IOFWSpeed speed, UInt32 chan ) ;	\
	IOReturn 	(*ReleasePort)	( IOFireWireLibIsochPortRef self ) ;	\
	IOReturn	(*Start)		( IOFireWireLibIsochPortRef self ) ;	\
	IOReturn	(*Stop)			( IOFireWireLibIsochPortRef self ) ;	\
	void 		(*SetRefCon)	( IOFireWireLibIsochPortRef self, void* inRefCon) ;	\
	void*		(*GetRefCon)	( IOFireWireLibIsochPortRef self)

/*!	@class IOFireWireIsochPortInterface
	@abstract An interface which represents a talker or listener 
		on an isochronous channel. This is a superclass containing all isochronous
		port functionality not specific to any kind of bus transaction. */
typedef struct IOFireWireIsochPortInterface_t
{
	IUNKNOWN_C_GUTS ;
	UInt32 revision, version ;
	IOFIREWIRELIBISOCHPORT_C_GUTS ;

} IOFireWireIsochPortInterface ;

typedef struct IOFireWireRemoteIsochPortInterface_t
{
	IUNKNOWN_C_GUTS ;
	UInt32 revision, version ;
	IOFIREWIRELIBISOCHPORT_C_GUTS ;

	IOFireWireLibIsochPortGetSupportedCallback (*SetGetSupportedHandler) ( IOFireWireLibRemoteIsochPortRef self, IOFireWireLibIsochPortGetSupportedCallback inHandler) ;
	IOFireWireLibIsochPortAllocateCallback	   (*SetAllocatePortHandler) ( IOFireWireLibRemoteIsochPortRef self, IOFireWireLibIsochPortAllocateCallback inHandler) ;
	IOFireWireLibIsochPortCallback	(*SetReleasePortHandler)( IOFireWireLibRemoteIsochPortRef self, IOFireWireLibIsochPortCallback inHandler) ;
	IOFireWireLibIsochPortCallback	(*SetStartHandler)( IOFireWireLibRemoteIsochPortRef self, IOFireWireLibIsochPortCallback inHandler) ;
	IOFireWireLibIsochPortCallback	(*SetStopHandler)( IOFireWireLibRemoteIsochPortRef self, IOFireWireLibIsochPortCallback inHandler) ;

} IOFireWireRemoteIsochPortInterface ;

typedef struct IOFireWireLocalIsochPortInterface_t
{
	IUNKNOWN_C_GUTS ;
	UInt32 revision, version ;
	IOFIREWIRELIBISOCHPORT_C_GUTS ;
	
IOReturn (*ModifyJumpDCL)	( IOFireWireLibLocalIsochPortRef self, DCLJump* inJump, DCLLabel* inLabel) ;
	
	// --- utility functions ----------
	void (*PrintDCLProgram)		( IOFireWireLibLocalIsochPortRef self, const DCLCommand* inProgram, UInt32 inLength) ;

} IOFireWireLocalIsochPortInterface ;

// ============================================================
//
// IOFireWireIsochChannelInterface
//
// ============================================================

typedef struct IOFireWireIsochChannelInterface_t
{
	IUNKNOWN_C_GUTS ;
	UInt32 revision, version ;

	IOReturn 			(*SetTalker)		( IOFireWireLibIsochChannelRef self, IOFireWireLibIsochPortRef talker ) ;
	IOReturn			(*AddListener)		( IOFireWireLibIsochChannelRef self, IOFireWireLibIsochPortRef listener ) ;
	
	IOReturn			(*AllocateChannel)	( IOFireWireLibIsochChannelRef self ) ;
	IOReturn			(*ReleaseChannel)	( IOFireWireLibIsochChannelRef self ) ;
	IOReturn			(*Start)			( IOFireWireLibIsochChannelRef self ) ;
	IOReturn			(*Stop)				( IOFireWireLibIsochChannelRef self ) ;
	
	// --- notification
	IOFireWireIsochChannelForceStopHandler (*SetChannelForceStopHandler)
													( IOFireWireLibIsochChannelRef self, IOFireWireIsochChannelForceStopHandler stopProc) ;
	void 				(*SetRefCon)				( IOFireWireLibIsochChannelRef self, void* stopProcRefCon) ;
	void*				(*GetRefCon)				( IOFireWireLibIsochChannelRef self) ;
	Boolean				(*NotificationIsOn) 		( IOFireWireLibIsochChannelRef self) ;
	Boolean				(*TurnOnNotification) 		( IOFireWireLibIsochChannelRef self) ;
	void				(*TurnOffNotification) 		( IOFireWireLibIsochChannelRef self) ;	
	void				(*ClientCommandIsComplete)	( IOFireWireLibIsochChannelRef self, FWClientCommandID commandID, IOReturn status) ;

} IOFireWireIsochChannelInterface ;

// ============================================================
//
// IOFireWireDCLCommandPoolInterface
//
// ============================================================

typedef struct IOFireWireDCLCommandPoolInterface_t
{
	IUNKNOWN_C_GUTS ;
	UInt32 revision, version ;

	DCLCommand*			(*Allocate)						( IOFireWireLibDCLCommandPoolRef self, IOByteCount inSize ) ;
	IOReturn			(*AllocateWithOpcode)			( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, DCLCommand** outDCL, UInt32 opcode, ... ) ;
	
	DCLCommand*			(*AllocateTransferPacketDCL)	( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, UInt32 inOpcode, void* inBuffer, IOByteCount inSize) ;
	DCLCommand*			(*AllocateTransferBufferDCL)	( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, UInt32 inOpcode, void* inBuffer, IOByteCount inSize, IOByteCount inPacketSize, UInt32 inBufferOffset) ;

	DCLCommand*			(*AllocateSendPacketStartDCL)	( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, void* inBuffer, IOByteCount inSize) ;
	DCLCommand*			(*AllocateSendPacketWithHeaderStartDCL)( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, void* inBuffer, IOByteCount inSize) ;
	DCLCommand*			(*AllocateSendBufferDCL)		( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, void* inBuffer, IOByteCount inSize, IOByteCount inPacketSize, UInt32 inBufferOffset) ;
	DCLCommand*			(*AllocateSendPacketDCL)		( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, void* inBuffer, IOByteCount inSize) ;

	DCLCommand*			(*AllocateReceivePacketStartDCL)( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, void* inBuffer, IOByteCount inSize) ;
	DCLCommand*			(*AllocateReceivePacketDCL)		( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, void* inBuffer, IOByteCount inSize) ;
	DCLCommand*			(*AllocateReceiveBufferDCL)		( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, void* inBuffer, IOByteCount inSize, IOByteCount inPacketSize, UInt32 inBufferOffset) ;

	DCLCommand*			(*AllocateCallProcDCL)			( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, DCLCallCommandProcPtr inProc, UInt32 inProcData) ;
	DCLCommand*			(*AllocateLabelDCL)				( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL) ;
	DCLCommand*			(*AllocateJumpDCL)				( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, DCLLabelPtr pInJumpDCLLabel) ;
	DCLCommand*			(*AllocateSetTagSyncBitsDCL)	( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, UInt16 inTagBits, UInt16 inSyncBits) ;
	DCLCommand*			(*AllocateUpdateDCLListDCL)		( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, DCLCommandPtr*inDCLCommandList, UInt32 inNumCommands) ;
	DCLCommand*			(*AllocatePtrTimeStampDCL)		( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, UInt32* inTimeStampPtr) ;

	void 				(*Free)							( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL ) ;
	
	IOByteCount			(*GetSize)						( IOFireWireLibDCLCommandPoolRef self ) ;
	Boolean				(*SetSize)						( IOFireWireLibDCLCommandPoolRef self, IOByteCount inSize ) ;
	IOByteCount			(*GetBytesRemaining)			( IOFireWireLibDCLCommandPoolRef self ) ;
} IOFireWireDCLCommandPoolInterface ;

#endif //__IOFireWireLibIsoch_H__
