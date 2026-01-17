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
	File:		IOFWRegs.h

	Contains:	Definitions of standard FireWire CSR registers.

	Version:	1.0

	Copyright:	© 1996-1999 by Apple Computer, Inc., all rights reserved.

*/

#ifndef __IOFWREGS_H__
#define __IOFWREGS_H__

#ifndef	__IOKIT_IOTYPES_H
#include <IOKit/IOTypes.h>
#endif

#include <IOKit/firewire/IOFireWireFamilyCommon.h>

// Something we should add to IOTypes?
//typedef SInt8 *	Ptr;
//typedef UInt8 Boolean;

// moved to IOFireWireFamilyCommon.h:
/*
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

#define BitRange(start, end)						\
(													\
	((((UInt32) 0xFFFFFFFF) << (31 - (end))) >>		\
	 ((31 - (end)) + (start))) <<					\
	(start)											\
)

#define BitRangePhase(start, end)					\
	(start)
*/

////////////////////////////////////////////////////////////////////////////////
//
// Standard FireWire defs.
//

// FireWire bit defs.

enum
{
	kFWBit0						= (1 << 31),
	kFWBit1						= (1 << 30),
	kFWBit2						= (1 << 29),
	kFWBit3						= (1 << 28),
	kFWBit4						= (1 << 27),
	kFWBit5						= (1 << 26),
	kFWBit6						= (1 << 25),
	kFWBit7						= (1 << 24),
	kFWBit8						= (1 << 23),
	kFWBit9						= (1 << 22),
	kFWBit10					= (1 << 21),
	kFWBit11					= (1 << 20),
	kFWBit12					= (1 << 19),
	kFWBit13					= (1 << 18),
	kFWBit14					= (1 << 17),
	kFWBit15					= (1 << 16),
	kFWBit16					= (1 << 15),
	kFWBit17					= (1 << 14),
	kFWBit18					= (1 << 13),
	kFWBit19					= (1 << 12),
	kFWBit20					= (1 << 11),
	kFWBit21					= (1 << 10),
	kFWBit22					= (1 << 9),
	kFWBit23					= (1 << 8),
	kFWBit24					= (1 << 7),
	kFWBit25					= (1 << 6),
	kFWBit26					= (1 << 5),
	kFWBit27					= (1 << 4),
	kFWBit28					= (1 << 3),
	kFWBit29					= (1 << 2),
	kFWBit30					= (1 << 1),
	kFWBit31					= (1 << 0)
};


/*zzz Put in IEEE1212.h */
////////////////////////////////////////////////////////////////////////////////
//
// Define some CSR stuff.
//

// CSR bit defs.

enum
{
	kCSRBit0					= (1 << 31),
	kCSRBit1					= (1 << 30),
	kCSRBit2					= (1 << 29),
	kCSRBit3					= (1 << 28),
	kCSRBit4					= (1 << 27),
	kCSRBit5					= (1 << 26),
	kCSRBit6					= (1 << 25),
	kCSRBit7					= (1 << 24),
	kCSRBit8					= (1 << 23),
	kCSRBit9					= (1 << 22),
	kCSRBit10					= (1 << 21),
	kCSRBit11					= (1 << 20),
	kCSRBit12					= (1 << 19),
	kCSRBit13					= (1 << 18),
	kCSRBit14					= (1 << 17),
	kCSRBit15					= (1 << 16),
	kCSRBit16					= (1 << 15),
	kCSRBit17					= (1 << 14),
	kCSRBit18					= (1 << 13),
	kCSRBit19					= (1 << 12),
	kCSRBit20					= (1 << 11),
	kCSRBit21					= (1 << 10),
	kCSRBit22					= (1 << 9),
	kCSRBit23					= (1 << 8),
	kCSRBit24					= (1 << 7),
	kCSRBit25					= (1 << 6),
	kCSRBit26					= (1 << 5),
	kCSRBit27					= (1 << 4),
	kCSRBit28					= (1 << 3),
	kCSRBit29					= (1 << 2),
	kCSRBit30					= (1 << 1),
	kCSRBit31					= (1 << 0)
};

#define CSRBitRange(start, end)						\
(													\
	((((UInt32) 0xFFFFFFFF) << (start)) >>			\
	 ((start) + (31 - (end)))) <<					\
	(31 - (end))									\
)

#define CSRBitRangePhase(start, end)				\
	(31 - end)

// Core CSR registers.

enum
{
	kCSRStateUnitDepend			= CSRBitRange (0, 15),
	kCSRStateUnitDependPhase	= CSRBitRangePhase (0, 15),

	kCSRStateBusDepend			= CSRBitRange (16, 23),
	kCSRStateBusDependPhase		= CSRBitRangePhase (16, 23),

	kCSRStateLost				= kCSRBit24,
	kCSRStateDReq				= kCSRBit25,
	kCSRStateELog				= kCSRBit27,
	kCSRStateAtn				= kCSRBit28,
	kCSRStateOff				= kCSRBit29,

	kCSRStateState				= CSRBitRange (30, 31),
	kCSRStateStatePhase			= CSRBitRangePhase (30, 31),
	kCSRStateStateRunning		= 0,
	kCSRStateStateInitializing	= 1,
	kCSRStateStateTesting		= 2,
	kCSRStateStateDead			= 3
};


// Config ROM entry bit locations.

enum
{
	kConfigBusInfoBlockLength	= CSRBitRange (0, 7),
	kConfigBusInfoBlockLengthPhase	= CSRBitRangePhase (0, 7),

	kConfigROMCRCLength		= CSRBitRange (8, 15),
	kConfigROMCRCLengthPhase	= CSRBitRangePhase (8, 15),

	kConfigROMCRCValue		= CSRBitRange (16, 31),
	kConfigROMCRCValuePhase		= CSRBitRangePhase (16, 31),

	kConfigEntryKeyType		= CSRBitRange (0, 1),
	kConfigEntryKeyTypePhase	= CSRBitRangePhase (0, 1),

	kConfigEntryKeyValue		= CSRBitRange (2, 7),
	kConfigEntryKeyValuePhase	= CSRBitRangePhase (2, 7),

	kConfigEntryValue		= CSRBitRange (8, 31),
	kConfigEntryValuePhase		= CSRBitRangePhase (8, 31),

	kConfigLeafDirLength		= CSRBitRange (0, 15),
	kConfigLeafDirLengthPhase	= CSRBitRangePhase (0, 15),

	kConfigLeafDirCRC		= CSRBitRange (16, 31),
	kConfigLeafDirCRCPhase		= CSRBitRangePhase (16, 31)
};

// CSR 64-bit fixed address defs.

enum
{
    kCSRNodeID				= CSRBitRange (0, 15),
    kCSRNodeIDPhase			= CSRBitRangePhase (0, 15),

    kCSRInitialMemorySpaceBaseAddressHi	= 0x00000000,
    kCSRInitialMemorySpaceBaseAddressLo	= 0x00000000,

    kCSRPrivateSpaceBaseAddressHi	= 0x0000FFFF,
    kCSRPrivateSpaceBaseAddressLo	= 0xE0000000,

    kCSRRegisterSpaceBaseAddressHi	= 0x0000FFFF,
    kCSRRegisterSpaceBaseAddressLo	= 0xF0000000,

    kCSRCoreRegistersBaseAddress	= kCSRRegisterSpaceBaseAddressLo,
    kCSRStateClearAddress		= kCSRCoreRegistersBaseAddress + 0x0000,
    kCSRStateSetAddress			= kCSRCoreRegistersBaseAddress + 0x0004,
    kCSRNodeIDsAddress			= kCSRCoreRegistersBaseAddress + 0x0008,
    kCSRResetStartAddress		= kCSRCoreRegistersBaseAddress + 0x000C,
    kCSRIndirectAddressAddress		= kCSRCoreRegistersBaseAddress + 0x0010,
    kCSRIndirectDataAddress		= kCSRCoreRegistersBaseAddress + 0x0014,
    kCSRSplitTimeoutHiAddress		= kCSRCoreRegistersBaseAddress + 0x0018,
    kCSRSplitTimeoutLoAddress		= kCSRCoreRegistersBaseAddress + 0x001C,
    kCSRArgumentHiAddress		= kCSRCoreRegistersBaseAddress + 0x0020,
    kCSRArgumentLoAddress		= kCSRCoreRegistersBaseAddress + 0x0024,
    kCSRTestStartAddress		= kCSRCoreRegistersBaseAddress + 0x0028,
    kCSRTestStatusAddress		= kCSRCoreRegistersBaseAddress + 0x002C,
    kCSRUnitsBaseHiAddress		= kCSRCoreRegistersBaseAddress + 0x0030,
    kCSRUnitsBaseLoAddress		= kCSRCoreRegistersBaseAddress + 0x0034,
    kCSRUnitsBoundHiAddress		= kCSRCoreRegistersBaseAddress + 0x0038,
    kCSRUnitsBoundLoAddress		= kCSRCoreRegistersBaseAddress + 0x003C,
    kCSRMemoryBaseHiAddress		= kCSRCoreRegistersBaseAddress + 0x0040,
    kCSRMemoryBaseLoAddress		= kCSRCoreRegistersBaseAddress + 0x0044,
    kCSRMemoryBoundHiAddress		= kCSRCoreRegistersBaseAddress + 0x0048,
    kCSRMemoryBoundLoAddress		= kCSRCoreRegistersBaseAddress + 0x004C,
    kCSRInterruptTargetAddress		= kCSRCoreRegistersBaseAddress + 0x0050,
    kCSRInterruptMaskAddress		= kCSRCoreRegistersBaseAddress + 0x0054,
    kCSRClockValueHiAddress		= kCSRCoreRegistersBaseAddress + 0x0058,
    kCSRClockValueMidAddress		= kCSRCoreRegistersBaseAddress + 0x005C,
    kCSRClockTickPeriodMidAddress	= kCSRCoreRegistersBaseAddress + 0x0060,
    kCSRClockTickPeriodLoAddress	= kCSRCoreRegistersBaseAddress + 0x0064,
    kCSRClockStrobeArrivedHiAddress	= kCSRCoreRegistersBaseAddress + 0x0068,
    kCSRClockStrobeArrivedMidAddress	= kCSRCoreRegistersBaseAddress + 0x006C,
    kCSRClockInfo0Address		= kCSRCoreRegistersBaseAddress + 0x0070,
    kCSRClockInfo1Address		= kCSRCoreRegistersBaseAddress + 0x0074,
    kCSRClockInfo2Address		= kCSRCoreRegistersBaseAddress + 0x0078,
    kCSRClockInfo3Address		= kCSRCoreRegistersBaseAddress + 0x007C,
    kCSRMessageRequestAddress		= kCSRCoreRegistersBaseAddress + 0x0080,
    kCSRMessageResponseAddress		= kCSRCoreRegistersBaseAddress + 0x00C0,
    kCSRErrorLogBufferAddress		= kCSRCoreRegistersBaseAddress + 0x0180,

    kCSRBusDependentRegistersBaseAddress
					= kCSRRegisterSpaceBaseAddressLo + 0x0200,
    kCSRBusyTimeout			= kCSRRegisterSpaceBaseAddressLo + 0x0210,
    kCSRBusManagerID			= kCSRRegisterSpaceBaseAddressLo + 0x021C,
    kCSRBandwidthAvailable		= kCSRRegisterSpaceBaseAddressLo + 0x0220,
    kCSRChannelsAvailable31_0		= kCSRRegisterSpaceBaseAddressLo + 0x0224,
    kCSRChannelsAvailable63_32		= kCSRRegisterSpaceBaseAddressLo + 0x0228,
    kConfigROMBaseAddress		= kCSRRegisterSpaceBaseAddressLo + 0x0400,
    kConfigBIBHeaderAddress		= kConfigROMBaseAddress,
    kConfigBIBBusNameAddress		= kConfigROMBaseAddress + 4,
    
    kPCRBaseAddress				= kCSRRegisterSpaceBaseAddressLo + 0x900,
    kFCPCommandAddress			= kCSRRegisterSpaceBaseAddressLo + 0xb00,
    kFCPResponseAddress			= kCSRRegisterSpaceBaseAddressLo + 0xd00
};


// CSR defined 64 bit unique ID.

typedef UInt64 CSRNodeUniqueID;
typedef CSRNodeUniqueID *CSRNodeUniqueIDPtr;

/*zzz End put in IEEE1212.h */


////////////////////////////////////////////////////////////////////////////////
//
// FireWire CSR defs.
//

// FireWire core CSR registers.

enum
{
	kFWCSRStateGone				= kFWBit16,
	kFWCSRStateLinkOff			= kFWBit22,
	kFWCSRStateCMstr			= kFWBit23
};

// FireWire bus/nodeID address defs.

enum
{
	kFWAddressBusID				= FWBitRange (16, 25) << kCSRNodeIDPhase,
	kFWAddressBusIDPhase		= FWBitRangePhase (16, 25) + kCSRNodeIDPhase,

	kFWAddressNodeID			= FWBitRange (26, 31) << kCSRNodeIDPhase,
	kFWAddressNodeIDPhase		= FWBitRangePhase (26, 31) + kCSRNodeIDPhase,

	kFWLocalBusID				= 1023,
	kFWBroadcastNodeID			= 63,
    kFWBadNodeID				= 0xffff,

	kFWLocalBusAddress			= kFWLocalBusID << kFWAddressBusIDPhase,
	kFWBroadcastAddress			= kFWBroadcastNodeID << kFWAddressNodeIDPhase
};

#define FWNodeBaseAddress(busID, nodeID)												\
(																						\
	(busID << kFWAddressBusIDPhase) |													\
	(nodeID << kFWAddressNodeIDPhase)													\
)

#define FWNodeRegisterSpaceBaseAddressHi(busID, nodeID)									\
(																						\
	FWNodeBaseAddress (busID, nodeID) |													\
	kCSRRegisterSpaceBaseAddressHi														\
)


// FireWire CSR bus info block defs.

enum
{
	kFWBIBHeaderAddress		= kConfigBIBHeaderAddress,
	kFWBIBBusNameAddress		= kConfigBIBBusNameAddress,
        kFWBIBNodeCapabilitiesAddress	= kConfigROMBaseAddress + 8,
        kFWBIBNodeUniqueIDHiAddress	= kConfigROMBaseAddress + 12,
        kFWBIBNodeUniqueIDLoAddress	= kConfigROMBaseAddress + 16,

	kFWBIBBusName				= 0x31333934, //'1394'

	kFWBIBIrmc					= kFWBit0,
	kFWBIBCmc					= kFWBit1,
	kFWBIBIsc					= kFWBit2,
	kFWBIBBmc					= kFWBit3,
	kFWBIBCycClkAcc				= FWBitRange (8, 15),
	kFWBIBCycClkAccPhase		= FWBitRangePhase (8, 15),
	kFWBIBMaxRec				= FWBitRange (16, 19),
	kFWBIBMaxRecPhase			= FWBitRangePhase (16, 19),
	kFWBIBMaxROM				= FWBitRange (20, 21),
	kFWBIBMaxROMPhase			= FWBitRangePhase (20, 21),
        kFWBIBGeneration			= FWBitRange (24, 27),
        kFWBIBGenerationPhase			= FWBitRangePhase (24, 27),
        kFWBIBLinkSpeed			= FWBitRange (29, 31),
        kFWBIBLinkSpeedPhase			= FWBitRangePhase (29, 31),
};


////////////////////////////////////////////////////////////////////////////////
//
// Define some bus management constants.
//
enum
{
	kFWBusManagerArbitrationTimeoutDuration	= 625 // durationMillisecond
};

////////////////////////////////////////////////////////////////////////////////
//
// Define some bus characteristics.
//

enum
{
	kFWMaxBusses				= 1023,
	kFWMaxNodesPerBus			= 63,
	kFWMaxNodeHops				= 16
};


////////////////////////////////////////////////////////////////////////////////
//
// Packet defs.
//

// Phy packet defs.

enum
{
	kFWPhyPacketID				= FWBitRange (0, 1),
	kFWPhyPacketIDPhase			= FWBitRangePhase (0, 1),

	kFWPhyPacketPhyID			= FWBitRange (2, 7),
	kFWPhyPacketPhyIDPhase		= FWBitRangePhase (2, 7)
};

enum
{
    kSelfIDPacketSize	= 8,
    kMaxSelfIDs		= 4	// SelfID 0,1,3,8
};

enum
{
    kFWConfigurationPacketID	= 0,
    kFWLinkOnPacketID		= 1,
    kFWSelfIDPacketID		= 2
};

enum
{
	kFWPhyConfigurationR		= kFWBit8,
	kFWPhyConfigurationT		= kFWBit9,
	kFWPhyConfigurationGapCnt	= FWBitRange (10, 15),
	kFWPhyConfigurationGapCntPhase
								= FWBitRangePhase (10, 15)
};

enum
{
	kFWSelfIDPortStatusChild	= 3,
	kFWSelfIDPortStatusParent	= 2,
	kFWSelfIDPortStatusNotConnected	= 1,
	kFWSelfIDPortStatusNotPresent	= 0,

	kFWSelfIDNoPower			= 0,
	kFWSelfIDSelfPowered15W		= 1,
	kFWSelfIDSelfPowered30W		= 2,
	kFWSelfIDSelfPowered45W		= 3,
	kFWSelfIDBusPowered1W		= 4,
	kFWSelfIDBusPowered3W		= 5,
	kFWSelfIDBusPowered6W		= 6,
	kFWSelfIDBusPowered10W		= 7,

	kFWSelfIDPhyID				= kFWPhyPacketPhyID,//zzz do we need or want this?
	kFWSelfIDPhyIDPhase			= kFWPhyPacketPhyIDPhase,
	kFWSelfIDM					= kFWBit31,

	kFWSelfID0L					= kFWBit9,
	kFWSelfID0GapCnt			= FWBitRange (10, 15),
	kFWSelfID0GapCntPhase		= FWBitRangePhase (10, 15),
	kFWSelfID0SP				= FWBitRange (16, 17),
	kFWSelfID0SPPhase			= FWBitRangePhase (16, 17),
	kFWSelfID0Del				= FWBitRange (18, 19),
	kFWSelfID0DelPhase			= FWBitRangePhase (18, 19),
	kFWSelfID0C					= kFWBit20,
	kFWSelfID0Pwr				= FWBitRange (21, 23),
	kFWSelfID0PwrPhase			= FWBitRangePhase (21, 23),
	kFWSelfID0P0				= FWBitRange (24, 25),
	kFWSelfID0P0Phase			= FWBitRangePhase (24, 25),
	kFWSelfID0P1				= FWBitRange (26, 27),
	kFWSelfID0P1Phase			= FWBitRangePhase (26, 27),
	kFWSelfID0P2				= FWBitRange (28, 29),
	kFWSelfID0P2Phase			= FWBitRangePhase (28, 29),
	kFWSelfID0I					= kFWBit30,

	kFWSelfIDPacketType			= kFWBit8,
	kFWSelfIDNN					= FWBitRange (9, 11),
	kFWSelfIDNNPhase			= FWBitRangePhase (9, 11),
	kFWSelfIDNPa				= FWBitRange (14, 15),
	kFWSelfIDNPaPhase			= FWBitRangePhase (14, 15),
	kFWSelfIDNPb				= FWBitRange (16, 17),
	kFWSelfIDNPbPhase			= FWBitRangePhase (16, 17),
	kFWSelfIDNPc				= FWBitRange (18, 19),
	kFWSelfIDNPcPhase			= FWBitRangePhase (18, 19),
	kFWSelfIDNPd				= FWBitRange (20, 21),
	kFWSelfIDNPdPhase			= FWBitRangePhase (20, 21),
	kFWSelfIDNPe				= FWBitRange (22, 23),
	kFWSelfIDNPePhase			= FWBitRangePhase (22, 23),
	kFWSelfIDNPf				= FWBitRange (24, 25),
	kFWSelfIDNPfPhase			= FWBitRangePhase (24, 25),
	kFWSelfIDNPg				= FWBitRange (26, 27),
	kFWSelfIDNPgPhase			= FWBitRangePhase (26, 27),
	kFWSelfIDNPh				= FWBitRange (28, 29),
	kFWSelfIDNPhPhase			= FWBitRangePhase (28, 29),
	kFWSelfIDMore				= kFWBit31
};

// Primary packet defs.
enum
{
	kFWPacketTCode				= FWBitRange (24, 27),
	kFWPacketTCodePhase			= FWBitRangePhase (24, 27)
};


enum
{
	kFWAsynchSpd				= FWBitRange (14, 15),
	kFWAsynchSpdPhase			= FWBitRangePhase (14, 15),

	kFWAsynchTLabel				= FWBitRange (16, 21),
	kFWAsynchTLabelPhase		= FWBitRangePhase (16, 21),
        kFWAsynchTTotal 	= ((0xffffffff & kFWAsynchTLabel) >> kFWAsynchTLabelPhase)+1,
	kFWAsynchRt					= FWBitRange (22, 23),
	kFWAsynchRtPhase			= FWBitRangePhase (22, 23),
	kFWAsynchNew				= 0,
	kFWAsynchRetryA				= 2,
	kTIAsycnhRetryB				= 3,

	kFWAsynchPriority			= FWBitRange (28, 31),
	kFWAsynchPriorityPhase		= FWBitRangePhase (28, 31),

	kFWAsynchDestinationID		= FWBitRange (0, 15),
	kFWAsynchDestinationIDPhase	= FWBitRangePhase (0, 15),

	kFWAsynchSourceID			= FWBitRange (0, 15),
	kFWAsynchSourceIDPhase		= FWBitRangePhase (0, 15),

	kFWAsynchDestinationOffsetHigh	= FWBitRange (16, 31),
	kFWAsynchDestinationOffsetHighPhase	= FWBitRangePhase (16, 31),

	kFWAsynchDestinationOffsetLow	= FWBitRange (0, 31),
	kFWAsynchDestinationOffsetLowPhase	= FWBitRangePhase (0, 31),

	kFWAsynchDataLength			= FWBitRange (0, 15),
	kFWAsynchDataLengthPhase	= FWBitRangePhase (0, 15),

	kFWAsynchExtendedTCode		= FWBitRange (16, 31),
	kFWAsynchExtendedTCodePhase	= FWBitRangePhase (16, 31),

	kFWAsynchAckSent			= FWBitRange (28, 31),
	kFWAsynchAckSentPhase		= FWBitRangePhase (28, 31),

	kFWAsynchRCode				= FWBitRange (16, 19),
	kFWAsynchRCodePhase			= FWBitRangePhase (16, 19)
};

enum
{
	kFWTCodeWriteQuadlet		= 0,
	kFWTCodeWriteBlock			= 1,
	kFWTCodeWriteResponse		= 2,
	kFWTCodeReadQuadlet			= 4,
	kFWTCodeReadBlock			= 5,
	kFWTCodeReadQuadletResponse	= 6,
	kFWTCodeReadBlockResponse	= 7,
	kFWTCodeCycleStart			= 8,
	kFWTCodeLock				= 9,
	kFWTCodeIsochronousBlock	= 10,
	kFWTCodeLockResponse		= 11,
	kFWTCodePHYPacket			= 14
};

enum
{
	kFWExtendedTCodeMaskSwap	= 1,
	kFWExtendedTCodeCompareSwap	= 2,
	kFWExtendedTCodeFetchAdd	= 3,
	kFWExtendedTCodeLittleAdd	= 4,
	kFWExtendedTCodeBoundedAdd	= 5,
	kFWExtendedTCodeWrapAdd		= 6,
	kFWExtendedTCodeVendorDependent	= 7
};


//zzz Put in Errors.h

enum {
	inUseErr					= -4160,				// Item already in use
	notFoundErr					= -4161,				// Item not found
	timeoutErr					= -4162,				// Something timed out
	busReconfiguredErr			= -4163,				// Bus was reconfigured
	invalidIDTypeErr			= -4166,				// Given ID is of an invalid type for the requested operation.
	alreadyRegisteredErr		= -4168,			// Item has already been registered.
	disconnectedErr				= -4169,		// Target of request has been disconnected.
	retryExceededErr			= -4170,		// Retry limit was exceeded.
	addressRangeErr				= -4171,		// Address is not in range.
	addressAlignmentErr			= -4172,		// Address is not of proper alignment.

	multipleTalkerErr			= -4180,		// Tried to install multiple talkers
	channelActiveErr			= -4181,		// Operation not permitted when channel is active
	noListenerOrTalkerErr		= -4182,			// Every isochronous channel must have one talker and at least
									// one listener
	noChannelsAvailableErr		= -4183,			// No supported isochronous channels are available
	channelNotAvailableErr		= -4184,			// Required channel was not available.
	invalidIsochPortIDErr		= -4185,			// An isochronous port ID is invalid.
	invalidFWReferenceTypeErr	= -4186,			// Operation does not support type of given reference ID
	separateBusErr				= -4187,		// Two or more entities are on two or more busses and cannot be associated with eachother.
	badSelfIDsErr				= -4188,		// Received self IDs are bad.

//zzz Do we own these next ID numbers?
	cableVoltageTooLowErr		= -4190,			// Cable power below device's minimum voltage
	cablePowerInsufficientErr	= -4191				// Can't grant power request at this time
};

// end - Put in Errors.h

#endif /* __IOFWREGS_H */

