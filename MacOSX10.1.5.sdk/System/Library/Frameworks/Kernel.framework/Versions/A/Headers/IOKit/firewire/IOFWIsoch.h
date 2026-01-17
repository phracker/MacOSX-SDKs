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
	File:		IOFWIsoch.h

	Contains:	Definitions for FireWire isochronous transfers.

	Version:	1.0

	Copyright:	© 1996-1999 by Apple Computer, Inc., all rights reserved.

*/

#ifndef __IOFWISOCH_H__
#define __IOFWISOCH_H__

//#ifndef	__IOFWREGS_H__
//#include <IOKit/firewire/IOFWRegs.h>
//#endif

#include <IOKit/firewire/IOFireWireFamilyCommon.h>

////////////////////////////////////////////////////////////////////////////////
//
// DCL opcode defs.
//

enum
{
	kFWDCLImmediateEvent		= 0,
	kFWDCLCycleEvent		= 1,
	kFWDCLSyBitsEvent		= 2
};

enum
{
	kFWDCLInvalidNotification	= 0,
	kFWDCLUpdateNotification	= 1,
	kFWDCLModifyNotification	= 2
};

enum
{
	kFWDCLOpDynamicFlag		= (1 << 16),
	kFWDCLOpVendorDefinedFlag	= (1 << 17),
	kFWDCLOpFlagMask		= BitRange (16, 31),
	kFWDCLOpFlagPhase		= BitRangePhase (16, 31)
};

enum
{
	kDCLInvalidOp						= 0,
	kDCLSendPacketStartOp				= 1,
	kDCLSendPacketWithHeaderStartOp		= 2,
	kDCLSendPacketOp					= 3,
	kDCLSendBufferOp					= 4,
	kDCLReceivePacketStartOp			= 5,
	kDCLReceivePacketOp					= 6,
	kDCLReceiveBufferOp					= 7,
	kDCLCallProcOp						= 8,
	kDCLLabelOp							= 9,
	kDCLJumpOp							= 10,
	kDCLSetTagSyncBitsOp				= 11,
	kDCLUpdateDCLListOp					= 12,
	kDCLTimeStampOp						= 13,
	kDCLPtrTimeStampOp					= 14
};

typedef struct DCLCommandStruct DCLCommand, *DCLCommandPtr;

struct DCLCommandStruct
{
	DCLCommandPtr			pNextDCLCommand;		// Next DCL command.
	UInt32					compilerData;			// Data for use by DCL compiler.
	UInt32					opcode;					// DCL opcode.
	UInt32					operands[1];			// DCL operands (size varies)
};


struct DCLTransferPacketStruct
{
	DCLCommandPtr			pNextDCLCommand;		// Next DCL command.
	UInt32					compilerData;			// Data for use by DCL compiler.
	UInt32					opcode;					// DCL opcode.
	void *					buffer;					// Packet buffer.
	UInt32					size;					// Buffer size.
};
typedef struct DCLTransferPacketStruct DCLTransferPacket, *DCLTransferPacketPtr;

struct DCLTransferBufferStruct
{
	DCLCommandPtr			pNextDCLCommand;		// Next DCL command.
	UInt32					compilerData;			// Data for use by DCL compiler.
	UInt32					opcode;					// DCL opcode.
	void *					buffer;					// Buffer.
	UInt32					size;					// Buffer size.
	UInt16					packetSize;				// Size of packets to send.
	UInt16					reserved;
	UInt32					bufferOffset;			// Current offset into buffer.
};
typedef struct DCLTransferBufferStruct DCLTransferBuffer, *DCLTransferBufferPtr;

typedef void	(DCLCallCommandProc) (DCLCommandPtr pDCLCommand);
typedef DCLCallCommandProc *DCLCallCommandProcPtr;

struct DCLCallProcStruct
{
	DCLCommandPtr			pNextDCLCommand;	// Next DCL command.
	UInt32					compilerData;		// Data for use by DCL compiler.
	UInt32					opcode;				// DCL opcode.
	DCLCallCommandProcPtr	proc;				// Procedure to call.
	UInt32					procData;			// Data for use by called procedure.
};
typedef struct DCLCallProcStruct DCLCallProc, *DCLCallProcPtr;

struct DCLLabelStruct
{
	DCLCommandPtr			pNextDCLCommand;	// Next DCL command.
	UInt32					compilerData;		// Data for use by DCL compiler.
	UInt32					opcode;				// DCL opcode.
};
typedef struct DCLLabelStruct DCLLabel, *DCLLabelPtr;

struct DCLJumpStruct
{
	DCLCommandPtr			pNextDCLCommand;	// Next DCL command.
	UInt32					compilerData;		// Data for use by DCL compiler.
	UInt32					opcode;				// DCL opcode.
	DCLLabelPtr				pJumpDCLLabel;		// DCL label to jump to.
};
typedef struct DCLJumpStruct DCLJump, *DCLJumpPtr;

struct DCLSetTagSyncBitsStruct
{
	DCLCommandPtr			pNextDCLCommand;	// Next DCL command.
	UInt32					compilerData;		// Data for use by DCL compiler.
	UInt32					opcode;				// DCL opcode.
	UInt16					tagBits;			// Tag bits for following packets.
	UInt16					syncBits;			// Sync bits for following packets.
};
typedef struct DCLSetTagSyncBitsStruct DCLSetTagSyncBits, *DCLSetTagSyncBitsPtr;

struct DCLUpdateDCLListStruct
{
	DCLCommandPtr			pNextDCLCommand;	// Next DCL command.
	UInt32					compilerData;		// Data for use by DCL compiler.
	UInt32					opcode;				// DCL opcode.
	DCLCommandPtr			*dclCommandList;	// List of DCL commands to update.
	UInt32					numDCLCommands;		// Number of DCL commands in list.
};
typedef struct DCLUpdateDCLListStruct DCLUpdateDCLList, *DCLUpdateDCLListPtr;

struct DCLTimeStampStruct
{
	DCLCommandPtr			pNextDCLCommand;	// Next DCL command.
	UInt32					compilerData;		// Data for use by DCL compiler.
	UInt32					opcode;				// DCL opcode.
	UInt32					timeStamp;			// Time stamp.
};
typedef struct DCLTimeStampStruct DCLTimeStamp, *DCLTimeStampPtr;

struct DCLPtrTimeStampStruct
{
	DCLCommandPtr			pNextDCLCommand;	// Next DCL command.
	UInt32					compilerData;		// Data for use by DCL compiler.
	UInt32					opcode;				// DCL opcode.
	UInt32					*timeStampPtr;		// Where to store the time stamp.
};
typedef struct DCLPtrTimeStampStruct DCLPtrTimeStamp, *DCLPtrTimeStampPtr;

#endif /* __IOFWISOCH_H */

