/*
 * Copyright (c) 1998-2002 Apple Computer, Inc. All rights reserved.
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
 *  Created on Mon Mar 19 2001.
 *  Copyright (c) 2001-2002 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __IOFireWireLibIsoch_H__
#define __IOFireWireLibIsoch_H__

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOCFPlugIn.h>

#include <IOKit/firewire/IOFireWireFamilyCommon.h>
#include <IOKit/firewire/IOFireWireFamilyCommon.h>
#include <IOKit/firewire/IOFireWireLib.h>

// === [CFPlugIn support constants] ========================================

//
//	v3 interfaces
//

//  uuid string: A0AD095E-6D2F-11D6-AC82-0003933F84F0
#define kIOFireWireLocalIsochPortInterfaceID_v3 CFUUIDGetConstantUUIDWithBytes(kCFAllocatorDefault,\
											0xA0, 0xAD, 0x09, 0x5E, 0x6D, 0x2F, 0x11, 0xD6,\
											0xAC, 0x82, 0x00, 0x03, 0x93, 0x3F, 0x84, 0xF0 )

//
//	v2 interfaces
//
//	Availability: Mac OS X "Jaguar" and later
//

//  uuid string: 73C76D09-6D2F-11D6-AF7F-0003933F84F0
#define kIOFireWireLocalIsochPortInterfaceID_v2 CFUUIDGetConstantUUIDWithBytes(kCFAllocatorDefault,\
											0x73, 0xC7, 0x6D, 0x09, 0x6D, 0x2F, 0x11, 0xD6,\
											0xAF, 0x7F, 0x00, 0x03, 0x93, 0x3F, 0x84, 0xF0 )

//
//	v1 interfaces
//

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
// IOFireWireIsochPort
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

#if HEADERDOC_COMMENT_ONLY
	// this class declaration is for headerdoc purposes only...
	// these methods are actually specified in a macro inserted into port subclass
	// COM interface structs

	/*!	@class IOFireWireIsochPortInterface
		@abstract FireWire user client isochronous port interface
		@discussion Isochronous ports represent talkers or listeners on an
			FireWire isochronous channel. This is a base class containing all
			isochronous port functionality not specific to any type of port.
			Ports are added to channel interfaces
			(IOFireWireIsochChannelInterface) which coordinate the start and
			stop of isochronous traffic on a FireWire bus isochronous channel.
			*/
class IOFireWireIsochPortInterface {
	/*!	@function GetSupported
		@abstract The method is called to determine which FireWire isochronous
			channels and speed this port supports.
		@discussion This method is called by the channel object to which a port
			has been added. Subclasses of IOFireWireIsochPortInterface override
			this method to support specific hardware. Do not call this method
			directly.
		@param self The isoch port interface to use.
		@param maxSpeed A pointer to an IOFWSpeed which should be filled with
			the maximum speed this port can talk or listen.
		@param chanSupported A pointer to a UInt64 which should be filled with
			a bitmask representing the FireWire bus isochonous channels on
			which the port can talk or listen. Set '1' for supported, '0' for
			unsupported.
		@result Return kIOReturnSuccess on success, other return any other
			IOReturn error code.*/
	IOReturn (*GetSupported)( IOFireWireLibIsochPortRef self, IOFWSpeed* maxSpeed, UInt64* chanSupported ) ;

	/*!	@function AllocatePort
		@abstract The method is called when the port should configure its
			associated hardware to prepare to send or receive isochronous data
			on the channel number and at the speed specified.
		@discussion This method is called by the channel object to which a port
			has been added. Subclasses of IOFireWireIsochPortInterface override
			this method to support specific hardware. Do not call this method
			directly.
		@param self The isoch port interface to use.
		@param speed Channel speed
		@param chan Channel number (0-63)
		@result Return kIOReturnSuccess on success, other return any other
			IOReturn error code.*/
	IOReturn (*AllocatePort)( IOFireWireLibIsochPortRef self, IOFWSpeed speed, UInt32 chan ) ;

	/*!	@function ReleasePort
		@abstract The method is called to release the hardware after the
			channel has been stopped.
		@discussion This method is called by the channel object to which a port
			has been added. Subclasses of IOFireWireIsochPortInterface override
			this method to support specific hardware. Do not call this method
			directly.
		@param self The isoch port interface to use.
		@result Return kIOReturnSuccess on success, other return any other IOReturn error code.*/
	IOReturn (*ReleasePort)( IOFireWireLibIsochPortRef self ) ;

	/*!	@function Start
		@abstract The method is called when the port is to begin talking or listening.
		@discussion This method is called by the channel object to which a port
			has been added. Subclasses of IOFireWireIsochPortInterface override
			this method to support specific hardware. Do not call this method
			directly.
		@param self The isoch port interface to use.
		@result Return kIOReturnSuccess on success, other return any other IOReturn error code.*/
	IOReturn (*Start)( IOFireWireLibIsochPortRef self ) ;

	/*!	@function Stop
		@abstract The method is called when the port is to stop talking or listening.
		@discussion This method is called by the channel object to which a port
			has been added. Subclasses of IOFireWireIsochPortInterface override
			this method to support specific hardware. Do not call this method
			directly.
		@param self The isoch port interface to use.
		@result Return kIOReturnSuccess on success, other return any
			other IOReturn error code.*/
	IOReturn (*Stop)( IOFireWireLibIsochPortRef self ) ;

	/*!	@function SetRefCon
		@abstract Set reference value associated with this port.
		@discussion Retrieve the reference value with GetRefCon()
		@param self The isoch port interface to use.
		@param inRefCon The new reference value.*/
	void (*SetRefCon)( IOFireWireLibIsochPortRef self, void* inRefCon) ;

	/*!	@function GetRefCon
		@abstract Get reference value associated with this port.
		@discussion Set the reference value with SetRefCon()
		@param self The isoch port interface to use.
		@result The port refcon value.*/
	void* (*GetRefCon)( IOFireWireLibIsochPortRef self)
} ;
#endif

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

typedef struct IOFireWireLocalIsochPortInterface_t {

/*!	@class IOFireWireLocalIsochPortInterface
	@abstract FireWire user client local isochronous port object.
	@discussion Represents a FireWire isochronous talker or listener
		within the local machine. Isochronous transfer is controlled by
		an associated DCL (Data Stream Control Language) program, which
		is similar to a hardware DMA program but is hardware agnostic.
		DCL programs can be written using the
		IOFireWireDCLCommandPoolInterface object.

	This interface contains all methods of IOFireWireIsochPortInterface
		and IOFireWireLocalIsochPortInterface. This interface will
		contain all v2 methods of IOFireWireLocalIsochPortInterface when
		instantiated as v2 or newer. */
/* headerdoc parse workaround	
class IOFireWireLocalIsochPortInterface {
public:
*/
	IUNKNOWN_C_GUTS ;
	UInt32 revision, version ;
	IOFIREWIRELIBISOCHPORT_C_GUTS ;
	
	/*!	@function ModifyJumpDCL
		@abstract Change the jump target label of a jump DCL.
		@discussion Use this function to change the flow of a DCL
			program. Works whether the DCL program is currently running
			or not.
		@param self The local isoch port interface to use.
		@param inJump The jump DCL to modify.
		@param inLabel The label to jump to.
		@result kIOReturnSuccess on success. Will return an error if 'inJump'
			does not point to a valid jump DCL or 'inLabel' does not point to a
			valid label DCL.*/
	IOReturn 	(*ModifyJumpDCL)( IOFireWireLibLocalIsochPortRef self, DCLJump* inJump, DCLLabel* inLabel) ;
	
	// --- utility functions ----------
	/*!	@function PrintDCLProgram
		@abstract Display the contents of a DCL program.
		@param self The local isoch port interface to use.
		@param inProgram A pointer to the first DCL of the program to display.
		@param inLength The length (in DCLs) of the program.*/
	void 		(*PrintDCLProgram)( IOFireWireLibLocalIsochPortRef self, const DCLCommand* inProgram, UInt32 inLength) ;

	//
	// --- v2
	//
	
	/*!	@function ModifyTransferPacketDCLSize
		@abstract Modify the transfer size of a transfer packet DCL (send or
			receive)
		@discussion Allows you to modify transfer packet DCLs after they have
			been compiled and while the DCL program is still running. The
			transfer size can be set to any size less than or equal to the size
			set when the DCL program was compiled (including 0).

		Availability: IOFireWireLocalIsochPortInterface_v2 and newer.

		@param self The local isoch port interface to use.
		@param inDCL A pointer to the DCL to modify.
		@param size The new size of data to be transferred.
		@result Returns kIOReturnSuccess on success. Will return an
			error if 'size' is too large for this program.*/
	IOReturn	(*ModifyTransferPacketDCLSize)( IOFireWireLibLocalIsochPortRef self, DCLTransferPacket* inDCL, IOByteCount size ) ;

	//
	// --- v3
	//
	
	/*!	@function ModifyTransferPacketDCLBuffer
		@abstract NOT IMPLEMENTED. Modify the transfer size of a
			transfer packet DCL (send or receive)
		@discussion NOT IMPLEMENTED. Allows you to modify transfer packet DCLs
			after they have been compiled and while the DCL program is still
			running. The buffer can be set to be any location within the range
			of buffers specified when the DCL program was compiled (including
			0).

		Availability: IOFireWireLocalIsochPortInterface_v3 and newer.

		@param self The local isoch port interface to use.
		@param inDCL A pointer to the DCL to modify.
		@param buffer The new buffer to or from data will be transferred.
		@result Returns kIOReturnSuccess on success. Will return an
			error if the range specified by [buffer, buffer+size] is not
			in the range of memory locked down for this program.*/
	IOReturn	(*ModifyTransferPacketDCLBuffer)( IOFireWireLibLocalIsochPortRef self, DCLTransferPacket* inDCL, void* buffer ) ;

	/*!	@function ModifyTransferPacketDCL
		@abstract Modify the transfer size of a transfer packet DCL (send or receive)
		@discussion Allows you to modify transfer packet DCLs after they
			have been compiled and while the DCL program is still
			running. The transfer size can be set to any size less than
			or equal to the size set when the DCL program was compiled
			(including 0).
			
			Availability: IOFireWireLocalIsochPortInterface_v3 and newer.
			
		@param self The local isoch port interface to use.
		@param inDCL A pointer to the DCL to modify.
		@param buffer The new buffer to or from data will be transferred.
		@param size The new size of data to be transferred.
		@result Returns kIOReturnSuccess on success. Will return an
			error if 'size' is too large or 'inDCL' does not point to a
			valid transfer packet DCL, or the range specified by
			[buffer, buffer+size] is not in the range of memory locked
			down for this program.*/
	IOReturn	(*ModifyTransferPacketDCL)( IOFireWireLibLocalIsochPortRef self, DCLTransferPacket* inDCL, void* buffer, IOByteCount size ) ;
} IOFireWireLocalIsochPortInterface ;

// ============================================================
//
// IOFireWireIsochChannelInterface
//
// ============================================================

typedef struct IOFireWireIsochChannelInterface_t
{
	/*!	@class IOFireWireIsochChannelInterface
		@abstract FireWire user client isochronous channel object.
		@discussion IOFireWireIsochChannelInterface is an abstract
			representataion of a FireWire bus isochronous channel. This
			interface coordinates the start of stop traffic on a
			FireWire bus isochronous channel and can optionally
			communicate with the IRM to automatically allocate bandwidth
			and channel numbers. When using automatic IRM allocation,
			the channel interface reallocates its bandwidth and channel
			reservation after each bus reset.

		Isochronous port interfaces representing FireWire isochronous talkers
			and listeners must be added to the channel using SetTalker() and
			AddListener()
	*/
/* headerdoc parse workaround	
class IOFireWireLocalIsochPortInterface: public IUnknown {
public:
*/
	IUNKNOWN_C_GUTS ;
	UInt32 revision, version ;

	/*!	@function SetTalker
		@abstract Set the talker port for this channel.
		@param self The local isoch port interface to use.
		@param talker The new talker.
		@result Returns kIOReturnSuccess on success. Returns on IOReturn error
			code on failure.*/
	IOReturn 			(*SetTalker)		( IOFireWireLibIsochChannelRef self, IOFireWireLibIsochPortRef talker ) ;

	/*!	@function AddListener
		@abstract Modify the transfer size of a transfer packet DCL (send or receive)
		@discussion Allows you to modify transfer packet DCLs after they have
			been compiled and while the DCL program is still running. The
			transfer size can be set to any size less than or equal to the size
			set when the DCL program was compiled (including 0).

		Availability: IOFireWireLocalIsochPortInterface_v3 and newer.

		@param self The local isoch port interface to use.
		@param inDCL A pointer to the DCL to modify.
		@param buffer The new buffer to or from data will be transferred.
		@param size The new size of data to be transferred.
		@result Returns kIOReturnSuccess on success. Will return an
			error if 'size' is too large or 'inDCL' does not point to a
			valid transfer packet DCL, or the range specified by
			[buffer, buffer+size] is not in the range of memory locked
			down for this program.*/
	IOReturn			(*AddListener)		( IOFireWireLibIsochChannelRef self, IOFireWireLibIsochPortRef listener ) ;
	
	/*!	@function AllocateChannel
		@abstract Prepare all hardware to begin sending or receiving isochronous data.
		@discussion Calling this function will result in all listener and talker ports on this 
			isochronous channel having their AllocatePort method called.
		@param self The local isoch channel interface to use.
		@result Returns kIOReturnSuccess on success, other IOReturn error code on failure.*/
	IOReturn			(*AllocateChannel)	( IOFireWireLibIsochChannelRef self ) ;

	/*!	@function ReleaseChannel
		@abstract Release all hardware after stopping the isochronous channel.
		@discussion Calling this function will result in all listener and talker ports on this 
			isochronous channel having their ReleasePort method called.
		@param self The local isoch channel interface to use.
		@result Returns kIOReturnSuccess on success, other IOReturn error code on failure.*/
	IOReturn			(*ReleaseChannel)	( IOFireWireLibIsochChannelRef self ) ;

	/*!	@function Start
		@abstract Start the channel.
		@discussion Calling this function will result in all listener and talker ports on this 
			isochronous channel having their Start method called.
		@param self The local isoch channel interface to use.
		@result Returns kIOReturnSuccess on success, other IOReturn error code on failure.*/
	IOReturn			(*Start)			( IOFireWireLibIsochChannelRef self ) ;

	/*!	@function Stop
		@abstract Stop the channel.
		@discussion Calling this function will result in all listener and talker ports on this 
			isochronous channel having their Stop method called.
		@param self The local isoch channel interface to use.
		@result Returns kIOReturnSuccess on success, other IOReturn error code on failure.*/
	IOReturn			(*Stop)				( IOFireWireLibIsochChannelRef self ) ;
	
	// --- notification
	/*!	@function SetChannelForceStopHandler
		@abstract Set the channel force stop handler.
		@discussion The specified callback is called when the channel is stopped and cannot be 
			restarted automatically.
		@param self The local isoch channel interface to use.
		@param stopProc The handler to set.
		@result Returns the previously set handler or NULL is no handler was set.*/
	IOFireWireIsochChannelForceStopHandler (*SetChannelForceStopHandler)
													( IOFireWireLibIsochChannelRef self, IOFireWireIsochChannelForceStopHandler stopProc) ;

	/*!	@function SetRefCon
		@abstract Set reference value associated with this channel.
		@discussion Retrieve the reference value with GetRefCon()
		@param self The isoch channel interface to use.
		@param inRefCon The new reference value.*/
	void 				(*SetRefCon)				( IOFireWireLibIsochChannelRef self, void* stopProcRefCon) ;

	/*!	@function GetRefCon
		@abstract Set reference value associated with this channel.
		@discussion Retrieve the reference value with SetRefCon()
		@param self The isoch channel interface to use.
		@param inRefCon The new reference value.*/
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
/*!	@class IOFireWireDCLCommandPoolInterface
*/
/* headerdoc parse workaround	
class IOFireWireDCLCommandPoolInterface {
public:
*/
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

	DCLCommand*			(*AllocateCallProcDCL)			( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, DCLCallCommandProc* inProc, UInt32 inProcData) ;
	DCLCommand*			(*AllocateLabelDCL)				( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL) ;
	DCLCommand*			(*AllocateJumpDCL)				( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, DCLLabel* pInJumpDCLLabel) ;
	DCLCommand*			(*AllocateSetTagSyncBitsDCL)	( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, UInt16 inTagBits, UInt16 inSyncBits) ;
	DCLCommand*			(*AllocateUpdateDCLListDCL)		( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, DCLCommand** inDCLCommandList, UInt32 inNumCommands) ;
	DCLCommand*			(*AllocatePtrTimeStampDCL)		( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL, UInt32* inTimeStampPtr) ;

	void 				(*Free)							( IOFireWireLibDCLCommandPoolRef self, DCLCommand* inDCL ) ;
	
	IOByteCount			(*GetSize)						( IOFireWireLibDCLCommandPoolRef self ) ;
	Boolean				(*SetSize)						( IOFireWireLibDCLCommandPoolRef self, IOByteCount inSize ) ;
	IOByteCount			(*GetBytesRemaining)			( IOFireWireLibDCLCommandPoolRef self ) ;
} IOFireWireDCLCommandPoolInterface ;

#endif //__IOFireWireLibIsoch_H__
