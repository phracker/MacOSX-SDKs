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
 *  IOFireWireFamilyCommon.h
 *  IOFireWireUserClient/IOFireWireFamily
 *
 *  Created by NWG on Fri Apr 28 2000.
 *  Copyright (c) 2000-2001 Apple Computer, Inc. All rights reserved.
 *
 */

/*! @header IOFireWireFamilyCommon.h
This file contains useful definitions for working with FireWire
for both in-kernel and user-space use
*/

#ifndef __IOFireWireFamilyCommon_H__
#define __IOFireWireFamilyCommon_H__

//#include <IOKit/OSTypes.h>

//#ifdef KERNEL
	#ifndef __IOKIT_IOTYPES_H
		#include <IOKit/IOTypes.h>
	#endif
//#else
//	#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>
//	#include <CarbonCore.framework/Headers/MacTypes.h>
//#endif

#define FWBitRange(start, end)						\
(													\
	((((UInt32) 0xFFFFFFFF) << (start)) >>			\
	 ((start) + (31 - (end)))) <<					\
	(31 - (end))									\
)

#define FWBitRangePhase(start, end)					\
	(31 - end)

// FireWire messages
#define	iokit_fw_err(return) (sys_iokit|sub_iokit_firewire|return)
#define kIOFireWireResponseBase iokit_fw_err(0x10)	/* Base of Response error codes  */
#define kIOFireWireBusReset	(kIOFireWireResponseBase+kFWResponseBusResetError)
							/* Bus reset during command execution  */
#define kIOConfigNoEntry	iokit_fw_err(1)		/* Can't find requested entry in ROM */
#define kIOFireWirePending	iokit_fw_err(2)		/* In pending queue waiting to execute */

#define kIOFWMessageServiceIsRequestingClose (UInt32)iokit_fw_err(2000)

// 8 quadlets
#define kFWUserCommandSubmitWithCopyMaxBufferBytes	32

////////////////////////////////////////////////////////////////////////////////
//
// Useful FireWire types
//

//
// Flags to be set on IOFireWireLib command objects
// Passed to SetFlags()
//
enum
{
	kFWCommandNoFlags					= 0 ,
	kFWCommandInterfaceForceNoCopy		= (1 << 0) ,
	kFWCommandInterfaceForceCopyAlways	= (1 << 1) ,
	kFWCommandInterfaceSyncExecute		= (1 << 2)
} ;


//
// Flags for creating pseudo address spaces
//
typedef enum
{
	kFWAddressSpaceNoFlags			= 0,
	kFWAddressSpaceNoWriteAccess 	= (1 << 0) ,
	kFWAddressSpaceNoReadAccess 	= (1 << 1) ,
	kFWAddressSpaceAutoWriteReply	= (1 << 2) ,
	kFWAddressSpaceAutoReadReply	= (1 << 3) ,
	kFWAddressSpaceAutoCopyOnWrite	= (1 << 4)
} FWAddressSpaceFlags ;

//
// Pseudo address space response codes
//
enum
{
	kFWResponseComplete			= 0,	// OK!
	kFWResponseConflictError	= 4,	// Resource conflict, may retry
	kFWResponseDataError		= 5,	// Data not available
	kFWResponseTypeError		= 6,	// Operation not supported
	kFWResponseAddressError		= 7,	// Address not valid in target device
	kFWResponseBusResetError	= 16,	// Pseudo response generated locally
	kFWResponsePending			= 17	// Pseudo response, real response sent later.
};

//
// Pseudo address space response codes
//
enum
{
	kFWAckTimeout				= -1,	// Pseudo ack generated locally
	kFWAckComplete				= 1,
	kFWAckPending				= 2,
	kFWAckBusyX					= 4,
	kFWAckBusyA					= 5,
	kFWAckBusyB					= 6,
	kFWAckDataError				= 13,
	kFWAckTypeError				= 14
};


//
// FireWire bus speed numbers
//

typedef enum
{
	kFWSpeed100MBit				= 0,
	kFWSpeed200MBit				= 1,
	kFWSpeed400MBit				= 2,
	kFWSpeedMaximum				= 0x7FFFFFFF,	//zzz what are the best numbers???
	kFWSpeedInvalid				= 0x80000000
} IOFWSpeed;

//
// The venerable FWAddress structure. This is the standard
// struct to use for passing FireWire addresses.
//

typedef struct FWAddressStruct
{
    UInt16	nodeID;		// bus/node
    UInt16	addressHi;	// Top 16 bits of node address.
    UInt32	addressLo;	// Bottom 32 bits of node address
	
	//
	// Useful C++ only constructors
	//
	#ifdef __cplusplus
	FWAddressStruct(const FWAddressStruct & a): 
			nodeID(a.nodeID), addressHi(a.addressHi), addressLo(a.addressLo) {};
    FWAddressStruct(UInt16 h=0xdead, UInt32 l=0xcafebabe) : 
			nodeID(0), addressHi(h), addressLo(l) {};
	FWAddressStruct(UInt16 h, UInt32 l, UInt16 n) :
			nodeID(n), addressHi(h), addressLo(l) {};
	#endif
} FWAddress, *FWAddressPtr ;

//
// Key types.
//
typedef enum
{
	kCSRImmediateKeyType		= 0,
	kCSROffsetKeyType			= 1,
	kCSRLeafKeyType				= 2,
	kCSRDirectoryKeyType		= 3,
    kInvalidCSRROMEntryType		= 0xff
} IOCSRKeyType;

//
// Key types.
//

typedef enum
{
	kConfigImmediateKeyType		= 0,
	kConfigOffsetKeyType		= 1,
	kConfigLeafKeyType		= 2,
	kConfigDirectoryKeyType		= 3,
	kInvalidConfigROMEntryType	= 0xff
} IOConfigKeyType;

////////////////////////////////////////////////////////////////////////////////
//
// Useful FireWire constants
//

//
// Key values.
//

enum
{
	kConfigTextualDescriptorKey	= 0x01,
	kConfigBusDependentInfoKey	= 0x02,
	kConfigModuleVendorIdKey	= 0x03,
	kConfigModuleHwVersionKey	= 0x04,
	kConfigModuleSpecIdKey		= 0x05,
	kConfigModuleSwVersionKey	= 0x06,
	kConfigModuleDependentInfoKey	= 0x07,
	kConfigNodeVendorIdKey		= 0x08,
	kConfigNodeHwVersionKey		= 0x09,
	kConfigNodeSpecIdKey		= 0x0A,
	kConfigNodeSwVersionKey		= 0x0B,
	kConfigNodeCapabilitiesKey	= 0x0C,
	kConfigNodeUniqueIdKey		= 0x0D,
	kConfigNodeUnitsExtentKey	= 0x0E,
	kConfigNodeMemoryExtentKey	= 0x0F,
	kConfigNodeDependentInfoKey	= 0x10,
	kConfigUnitDirectoryKey		= 0x11,
	kConfigUnitSpecIdKey		= 0x12,
	kConfigUnitSwVersionKey		= 0x13,
	kConfigUnitDependentInfoKey	= 0x14,
	kConfigUnitLocationKey		= 0x15,
	kConfigUnitPollMaskKey		= 0x16,
	kConfigModelIdKey			= 0x17,
	kConfigGenerationKey		= 0x38,		// Apple-specific

        kConfigRootDirectoryKey		= 0xffff	// Not a real key
};

//
// Passed when calling/creating read/write commands
//

enum {
	kFWDontFailOnReset = false,
	kFWFailOnReset = true
} ;

//
// isoch defines
//
enum
{
	kFWIsochDataLength		= FWBitRange (0, 15),
	kFWIsochDataLengthPhase	= FWBitRangePhase (0, 15),
	
	kFWIsochTag				= FWBitRange (16, 17),
	kFWIsochTagPhase		= FWBitRangePhase (16, 17),

	kFWIsochChanNum			= FWBitRange (18, 23),
	kFWIsochChanNumPhase	= FWBitRangePhase (18, 23),

	kFWIsochTCode			= FWBitRange (24, 27),
	kFWIsochTCodePhase		= FWBitRangePhase (24, 27),

	kFWIsochSy				= FWBitRange (28, 31),
	kFWIsochSyPhase			= FWBitRangePhase (28, 31)
};


////////////////////////////////////////////////////////////////////////////////
//
// Useful FireWire utility functions.
//

#ifdef __cplusplus
extern "C" {
#endif

UInt16 FWComputeCRC16(const UInt32 *pQuads, UInt32 numQuads);
UInt16 FWUpdateCRC16(UInt16 crc16, UInt32 quad);

UInt32 AddFWCycleTimeToFWCycleTime( UInt32 cycleTime1, UInt32 cycleTime2 );
UInt32 SubtractFWCycleTimeFromFWCycleTime( UInt32 cycleTime1, UInt32 cycleTime2);

#ifdef __cplusplus
}
#endif

// ============================================================
//
//	(INTERNAL USE ONLY)
//
// ============================================================

typedef enum IOFireWireFamilyUserClientSelector_t {
	// --- open/close ----------------------------
	kFireWireOpen = 0,
	kFireWireOpenWithSessionRef,
	kFireWireClose,
	
	// --- user client general methods -----------
	kFireWireReadQuad,
	kFireWireReadQuadAbsolute,
	kFireWireRead,
	kFireWireReadAbsolute,
	kFireWireWriteQuad,
	kFireWireWriteQuadAbsolute,
	kFireWireWrite,
	kFireWireWriteAbsolute,
	kFireWireCompareSwap,
	kFireWireCompareSwapAbsolute,
	kFireWireBusReset,
	kFireWireCycleTime,
	kFireWireGetGenerationAndNodeID,
	kFireWireGetLocalNodeID,
	kFireWireGetResetTime,
	
	//	// --- DCL methods ---------------------------
	//	kFireWireCompileDCL,
	//	kFireWireStopDCL,
	
	// --- debugging -----------------------------
	kFireWireFireBugMsg,
	
	// --- conversion helpers --------------------
	kFWGetOSStringData,
	kFWGetOSDataData,
	
	// --- user unit directory methods -----------
	kFWUnitDirCreate,
	kFWUnitDirRelease,
	kFWUnitDirAddEntry_Buffer,
	kFWUnitDirAddEntry_UInt32,
	kFWUnitDirAddEntry_FWAddr,
	kFWUnitDirAddEntry_UnitDir,
	kFWUnitDirPublish,
	kFWUnitDirUnpublish,
	
	// --- pseudo address space methods ----------
	kFWPseudoAddrSpace_Allocate,
	kFWPseudoAddrSpace_Release,
	kFWPseudoAddrSpace_GetFWAddrInfo,
	kFWPseudoAddrSpace_ClientCommandIsComplete,
	
	// --- physical address space methods ----------
	kFWPhysicalAddrSpace_Allocate,
	kFWPhysicalAddrSpace_Release,
	kFWPhysicalAddrSpace_GetSegmentCount,
	kFWPhysicalAddrSpace_GetSegments,
	
	// --- command completion --------------------
	kFWClientCommandIsComplete,
	
	// --- config directory ----------------------
	kFWConfigDirectoryCreate,
	kFWConfigDirectoryUpdate,
	kFWConfigDirectoryGetKeyType,
	
	kFWConfigDirectoryGetKeyValue_UInt32,
	kFWConfigDirectoryGetKeyValue_Data,
	kFWConfigDirectoryGetKeyValue_ConfigDirectory,
	
	kFWConfigDirectoryGetKeyOffset_FWAddress,	
	
	kFWConfigDirectoryGetIndexType,
	kFWConfigDirectoryGetIndexKey,
	
	kFWConfigDirectoryGetIndexValue_UInt32,
	kFWConfigDirectoryGetIndexValue_Data,
	kFWConfigDirectoryGetIndexValue_String,
	kFWConfigDirectoryGetIndexValue_ConfigDirectory,
	
	kFWConfigDirectoryGetIndexOffset_FWAddress,
	kFWConfigDirectoryGetIndexOffset_UInt32,
	
	kFWConfigDirectoryGetIndexEntry,
	kFWConfigDirectoryGetSubdirectories,
	
	kFWConfigDirectoryGetKeySubdirectories,
	kFWConfigDirectoryGetType,
	kFWConfigDirectoryGetNumEntries,
	kFWConfigDirectoryRelease,
	
	// --- isoch port methods ----------------------------
	kFWIsochPort_Allocate,
	kFWIsochPort_Release,
	kFWIsochPort_GetSupported,
	kFWIsochPort_AllocatePort,
	kFWIsochPort_ReleasePort,
	kFWIsochPort_Start,
	kFWIsochPort_Stop,
	kFWIsochPort_SetSupported,
	
	// --- local isoch port methods ----------------------
	kFWLocalIsochPort_Allocate,
	kFWLocalIsochPort_ModifyJumpDCL,
	
	// --- isoch channel methods -------------------------
	kFWIsochChannel_Allocate,
	kFWIsochChannel_Release,
	kFWIsochChannel_UserAllocateChannelBegin,
	kFWIsochChannel_UserReleaseChannelComplete,
	
	// --- firewire command objects ----------------------
	kFWCommand_Allocate,
	kFWCommand_Release,
	kFWCommand_Cancel,
	
	// -------------------------------------------
	kNumFireWireMethods
} IOFireWireFamilyUserClientMethodSelector ;


typedef enum IOFireWireFamilyUserClientAsyncMethodSelector_t {

	kFWSetAsyncRef_BusReset,
	kFWSetAsyncRef_BusResetDone,

	//
	// pseudo address space
	//
	kFWSetAsyncRef_Packet,
	kFWSetAsyncRef_SkippedPacket,
	kFWSetAsyncRef_Read,

	//
	// user command objects
	//
	kFWCommand_Submit,
	kFWCommand_SubmitAbsolute,
	
	//
	// isoch channel
	//
	kFWSetAsyncRef_IsochChannelForceStop,

	//
	// isoch port
	//
	kFWSetAsyncRef_DCLCallProc,
	
	kNumFireWireAsyncMethods

} IOFireWireFamilyUserClientAsyncMethodSelector ;

typedef enum IOFireWireCommandType_t {
	kFireWireCommandType_Read,
	kFireWireCommandType_ReadQuadlet,
	kFireWireCommandType_Write,
	kFireWireCommandType_WriteQuadlet,
	kFireWireCommandType_CompareSwap
} IOFireWireCommandType ;

enum {
	kFireWireCommandStale				= (1 << 0),
	kFireWireCommandStale_Buffer		= (1 << 1),
	kFireWireCommandStale_MaxPacket		= (1 << 2)
} ;

enum {
	kFireWireCommandUseCopy				= (1 << 16)
} ;

#define kFireWireCommandUserFlagsMask (0x0000FFFF)

#ifdef KERNEL
	class IOFWUserClientPseudoAddrSpace ;
	class IOFWUserClientPhysicalAddressSpace ;
	class IOConfigDirectory ;
	class IOLocalConfigDirectory ;
	class OSString ;
	class OSData ;
	class IOFWUserIsochPortProxy ;
	class IOFWUserIsochChannel ;
	class IOFWUserCommand ;
	
	typedef IOFWUserClientPseudoAddrSpace*		FWKernAddrSpaceRef ;
	typedef IOFWUserClientPhysicalAddressSpace*	FWKernPhysicalAddrSpaceRef ;
	typedef IOConfigDirectory* 					FWKernConfigDirectoryRef ;
	typedef IOLocalConfigDirectory*				FWKernUnitDirRef ;
	typedef OSString*							FWKernOSStringRef ;
	typedef OSData*								FWKernOSDataRef ;
	typedef IOFWUserIsochPortProxy*				FWKernIsochPortRef ;
	typedef IOFWUserIsochChannel*				FWKernIsochChannelRef ;
	typedef IOFWUserCommand*					FWKernCommandRef ;
	
#else
	typedef struct FWKernAddrSpaceOpaqueStruct* 		FWKernAddrSpaceRef ;
	typedef struct FWKernPhysicalAddrSpaceOpaqueStruct*	FWKernPhysicalAddrSpaceRef ;
	typedef struct FWKernConfigDirectoryOpaqueStruct*	FWKernConfigDirectoryRef ;
	typedef struct FWKernUnitDirOpaqueStruct*			FWKernUnitDirRef ;
	typedef struct FWKernOSStringOpaqueStruct*			FWKernOSStringRef ;
	typedef struct FWKernOSDataOpqaueStruct*			FWKernOSDataRef ;
	typedef struct FWKernIsochPortOpaqueStruct*			FWKernIsochPortRef ;
	typedef struct FWKernIsochChannelOpaqueStruct*		FWKernIsochChannelRef ;
	typedef struct FWKernCommandOpaqueStruct*			FWKernCommandRef ;
#endif // KERNEL

typedef void* FWUserPacketQueueRef ;
typedef void* FWClientCommandID ;

typedef struct FWReadParamsStruct_t
{	
	FWAddress					addr ;
	const void*  			 	buf ;
	UInt32						size ;
	Boolean						failOnReset ;
	UInt32						generation ;
} FWReadWriteParams ;

typedef struct FWUserCommandSubmitParamsStruct_t
{
	FWKernCommandRef			kernCommandRef ;
	IOFireWireCommandType		type ;
	void*						callback ;
	void*						refCon ;
	UInt32						flags ;
	
	UInt32						staleFlags ;
	FWAddress					newTarget ;
	void*						newBuffer ;
	IOByteCount					newBufferSize ;	// note: means numQuads for quadlet commands!
	Boolean						newFailOnReset ;
	UInt32						newGeneration ;
	IOByteCount					newMaxPacket ;
} FWUserCommandSubmitParams ;

typedef struct FWUserCommandSubmitResult_t
{
	FWKernCommandRef			kernCommandRef ;
	IOReturn					result ;
	IOByteCount					bytesTransferred ;
} FWUserCommandSubmitResult ;

typedef struct FWAddrSpaceCreateParams_t {
	UInt32		size ;
	void*		backingStore ;
	UInt32		queueSize ;
	void*		queueBuffer ;
	UInt32		flags ;
	UInt32		refCon ;
} FWAddrSpaceCreateParams ;

typedef struct FWIsochPortAllocateParams_t
{
	UInt32		reserved ;
} FWIsochPortAllocateParams ;

typedef struct FWLocalIsochPortAllocateParams_t
{
	Boolean				talking ;
	
	struct DCLCommandStruct*	userDCLProgram ;
	UInt32						userDCLProgramDCLCount ;

	IOVirtualRange*		userDCLProgramRanges ;
	UInt32				userDCLProgramRangeCount ;
	IOVirtualRange*		userDCLBufferRanges ;
	UInt32				userDCLBufferRangeCount ;
	
	UInt32				startEvent ;
	UInt32				startState ;
	UInt32				startMask ;
} FWLocalIsochPortAllocateParams ;

typedef struct FWAddrSpaceCreateResult
{
	FWKernAddrSpaceRef	kernAddrSpaceRef ;
} FWAddrSpaceCreateResult ;

typedef struct FWPhysicalAddrSpaceCreateParams_t
{
	UInt32		size ;
	void*		backingStore ;
	UInt32		flags ;
} FWPhysicalAddrSpaceCreateParams ;

typedef struct IOFireWireSessionRefOpaqueStuct* IOFireWireSessionRef ;

// Generic bit defs.

enum
{
	kBit0						= (1 << 0),
	kBit1						= (1 << 1),
	kBit2						= (1 << 2),
	kBit3						= (1 << 3),
	kBit4						= (1 << 4),
	kBit5						= (1 << 5),
	kBit6						= (1 << 6),
	kBit7						= (1 << 7),
	kBit8						= (1 << 8),
	kBit9						= (1 << 9),
	kBit10						= (1 << 10),
	kBit11						= (1 << 11),
	kBit12						= (1 << 12),
	kBit13						= (1 << 13),
	kBit14						= (1 << 14),
	kBit15						= (1 << 15),
	kBit16						= (1 << 16),
	kBit17						= (1 << 17),
	kBit18						= (1 << 18),
	kBit19						= (1 << 19),
	kBit20						= (1 << 20),
	kBit21						= (1 << 21),
	kBit22						= (1 << 22),
	kBit23						= (1 << 23),
	kBit24						= (1 << 24),
	kBit25						= (1 << 25),
	kBit26						= (1 << 26),
	kBit27						= (1 << 27),
	kBit28						= (1 << 28),
	kBit29						= (1 << 29),
	kBit30						= (1 << 30),
	kBit31						= (1 << 31)
};

enum
{
    kIOFWDisablePhysicalAccess = (1 << 0),
	kIOFWDisableAllPhysicalAccess = (1 << 1)
};

#define BitRange(start, end)						\
(													\
	((((UInt32) 0xFFFFFFFF) << (31 - (end))) >>		\
	 ((31 - (end)) + (start))) <<					\
	(start)											\
)

#define BitRangePhase(start, end)					\
	(start)

#endif //__IOFireWireFamilyCommon_H__
