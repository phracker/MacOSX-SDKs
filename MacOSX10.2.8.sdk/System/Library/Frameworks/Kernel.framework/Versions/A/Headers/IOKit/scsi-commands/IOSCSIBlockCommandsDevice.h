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


#ifndef _IOKIT_IO_SCSI_BLOCK_COMMANDS_DEVICE_H_
#define _IOKIT_IO_SCSI_BLOCK_COMMANDS_DEVICE_H_

#if defined(KERNEL) && defined(__cplusplus)

//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Constants
//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ

// SBC power states as defined in T10:996D SCSI Block Commands - 3 (SBC-3)
// Revision 8c, November 13, 1997, pages 10-11.
enum
{
	kSBCPowerStateSystemSleep 	= 0,
	kSBCPowerStateSleep 		= 1,
	kSBCPowerStateStandby 		= 2,
	kSBCPowerStateIdle			= 3,
	kSBCPowerStateActive		= 4,
	kSBCNumPowerStates			= 5
};

enum
{
	kMediaStateUnlocked	= 0,
	kMediaStateLocked 	= 1
};

// Write cache bits
enum
{	
	kWriteCacheEnabledBit	= 2,
	kWriteCacheEnabledMask	= (1 << kWriteCacheEnabledBit)
};

enum
{
	kCachingModePageCode = 0x08,
	kCachingModePageSize = 128
};


//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Includes
//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ

// General IOKit headers
#include <IOKit/IOLib.h>
#include <IOKit/IOMemoryDescriptor.h>

// Generic IOKit storage related headers
#include <IOKit/storage/IOStorage.h>

// SCSI Architecture Model Family includes
#include <IOKit/scsi-commands/IOSCSIPrimaryCommandsDevice.h>


// Forward declaration for the SCSIBlockCommands that is used internally by the
// IOSCSIBlockCommandsDevice class.
class SCSIBlockCommands;

//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Class Declaration
//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ

class IOSCSIBlockCommandsDevice : public IOSCSIPrimaryCommandsDevice
{
	
	OSDeclareAbstractStructors ( IOSCSIBlockCommandsDevice )
	
private:
	
	SCSIBlockCommands *		fSCSIBlockCommandObject;
	SCSIBlockCommands *		GetSCSIBlockCommandObject ( void );
	
	static void				AsyncReadWriteComplete ( SCSITaskIdentifier	completedTask );
	
protected:
	
	// Reserve space for future expansion.
    struct IOSCSIBlockCommandsDeviceExpansionData
	{
		IONotifier *		fPowerDownNotifier;
		bool				fWriteCacheEnabled;
		bool				fDeviceIsShared;
	};
    IOSCSIBlockCommandsDeviceExpansionData * fIOSCSIBlockCommandsDeviceReserved;
	
	#define fPowerDownNotifier	fIOSCSIBlockCommandsDeviceReserved->fPowerDownNotifier
	#define fWriteCacheEnabled	fIOSCSIBlockCommandsDeviceReserved->fWriteCacheEnabled

	// The fDeviceIsShared is used to indicate whether this device exists on a Physical
	// Interconnect that allows multiple initiators to access it.  This is used mainly
	// by the power management code to not send power state related START_STOP_UNIT
	// commands to the device.
	#define fDeviceIsShared	fIOSCSIBlockCommandsDeviceReserved->fDeviceIsShared
	
	// ---- Device Characteristics ----
	UInt8				fANSIVersion;		/* DEPRECATED. Use IOSCSIPrimaryCommandsDevice::Get/SetANSIVersion */
	bool				fMediaIsRemovable;
	
	// ---- Medium Characteristics ----
	bool				fMediumPresent;
	
	// The byte count of each physical block on the medium.
	UInt32				fMediumBlockSize;
	
	// The total number of blocks of fMediumBlockSize on the medium.
	UInt32				fMediumBlockCount;
	
	// Whether the installed medium is protected from writes
	bool				fMediumIsWriteProtected;
	
	// Whether user removal of medium has been prevented	
	bool				fMediumRemovalPrevented;
	
	// Indicates whether this is a known manual eject device
	bool				fKnownManualEject;
	
	// Polling thread variables
	thread_call_t		fPollingThread;
	UInt32				fPollingMode;
	enum
	{
		kPollingMode_Suspended		= 0,
		kPollingMode_NewMedia 		= 1,
		kPollingMode_MediaRemoval	= 2
	};
	
	// ---- Methods for controlling the current state of device support ----
	virtual bool		InitializeDeviceSupport ( void );
	virtual void		StartDeviceSupport ( void );
	virtual void		SuspendDeviceSupport ( void );
	virtual void		ResumeDeviceSupport ( void );
	virtual void		StopDeviceSupport ( void );
	virtual void		TerminateDeviceSupport ( void );
	
	// This method will retrieve the SCSI Primary Command Set object for
	// the class.  For subclasses, this will be overridden using a
	// dynamic cast on the subclasses base command set object.
	virtual SCSIPrimaryCommands *	GetSCSIPrimaryCommandObject ( void );
	
	// ---- Methods used for   ----
	virtual bool		CreateCommandSetObjects ( void );
	virtual void		FreeCommandSetObjects ( void );
	virtual bool		ClearNotReadyStatus ( void );
	virtual void 		CreateStorageServiceNub ( void );
	virtual bool		DetermineDeviceCharacteristics ( void );
	
	// ---- Methods used for controlling the polling thread ----
	virtual void		ProcessPoll ( void );
	virtual void		EnablePolling ( void );
	virtual void		DisablePolling ( void );
	
	// Main and support methods for polling for new Media
	virtual void		PollForNewMedia ( void );
	virtual bool		DetermineMediaPresence ( void );
	virtual bool		PreventMediumRemoval ( void );
	virtual bool		DetermineMediumCapacity (
							UInt64 * 				blockSize,
							UInt64 * 				blockCount );
	virtual bool		DetermineMediumWriteProtectState ( void );
	
	// Main and support methods for polling for Media removal
	virtual void		PollForMediaRemoval ( void );
	
	// ---- Methods used for handling medium characteristics ----
	virtual void		SetMediumCharacteristics (
							UInt32 					blockSize,
							UInt32 					blockCount );
	
	virtual void		ResetMediumCharacteristics ( void );

	virtual IOReturn	IssueRead (
							IOMemoryDescriptor *	buffer,
						 	UInt64					startBlock,
					 		UInt64					blockCount );
	
	virtual IOReturn	IssueRead (
							IOMemoryDescriptor *	buffer,
					  		UInt64					startBlock,
					 		UInt64					blockCount,
					   		void * 					clientData );
	
	virtual IOReturn	IssueWrite (
							IOMemoryDescriptor *	buffer,
							UInt64					startBlock,
					   		UInt64					blockCount );
	
	virtual IOReturn	IssueWrite (
							IOMemoryDescriptor *	buffer,
						 	UInt64					startBlock,
					  		UInt64					blockCount,
							void * 					clientData );
	
	// ----- Power Management Support ------
	
	// We override this method to set our power states and register ourselves
	// as a power policy maker.
	virtual void 		InitializePowerManagement ( IOService * provider );
	
	// We override this method so that when we register for power management,
	// we go to our active power state (which the drive is definitely in
	// at startup time).
	virtual UInt32		GetInitialPowerState ( void );
	
	// We override this method in order to provide the number of transitions
	// from Fully active to Sleep state so that the idle timer can be adjusted
	// to the appropriate time period based on the disk spindown time set in
	// the Energy Saver prefs panel.
	virtual UInt32		GetNumberOfPowerStateTransitions ( void );
	
	// The TicklePowerManager method is called to tell the power manager that
	// the device needs to be in a certain power state to handle requests.
	virtual void		TicklePowerManager ( void );
	
	// The HandlePowerChange method is the state machine for power management.
	// It is guaranteed to be on its own thread of execution (different from
	// the power manager thread AND the workloop thread. This routine can
	// send sync or async calls to the drive without worrying about threading
	// issues.
	virtual void		HandlePowerChange ( void );
	
	// The HandleCheckPowerState (void) method is on the serialized side of the
	// command gate and can change member variables safely without
	// multi-threading issues. It's main purpose is to call the superclass'
	// HandleCheckPowerState ( UInt32 maxPowerState ) with the max power state
	// the class registered with.
	virtual void		HandleCheckPowerState ( void );
	
	// The VerifyMediumPresence method is called to see if the medium which we
	// anticipated being there is still there.
	virtual bool		VerifyMediumPresence ( void );
	
public:
	
	static 	void		sProcessPoll ( void * pdtDriver, void * refCon );
	
	// ---- Methods for controlling the device ----
	virtual IOReturn	SyncReadWrite (
							IOMemoryDescriptor *	buffer,
							UInt64					startBlock,
							UInt64					blockCount,
							UInt64					blockSize );
	
	virtual IOReturn	AsyncReadWrite (
							IOMemoryDescriptor *	buffer,
							UInt64					startBlock,
							UInt64					blockCount,
							UInt64					blockSize,
							void * 					clientData );
	
	// ---- Methods for controlling medium state ----
	virtual IOReturn	EjectTheMedium ( void );
	virtual IOReturn	LockUnlockMedium ( bool doLock );
	virtual IOReturn	SynchronizeCache ( void );
	
	// ---- Methods for controlling media format ----
	virtual IOReturn	FormatMedium (
							UInt64 					blockCount,
							UInt64 					blockSize );
	virtual UInt32		GetFormatCapacities (
							UInt64 * 				capacities,
			 				UInt32   				capacitiesMaxCount ) const;
	
	// ---- Query methods to report device characteristics ----
	
	// Report the maximum number of blocks that the device can handle per
	// read or write.  A value of 0 (zero) indicates there is no limit aside
	// from the size of the method's return parameter.
	virtual UInt64		ReportDeviceMaxBlocksReadTransfer ( void );
	virtual UInt64		ReportDeviceMaxBlocksWriteTransfer ( void );
	
	// Report whether the device supports removal of the media.
	virtual bool		ReportDeviceMediaRemovability ( void );
	
	// ---- Query methods to report installed medium characteristics ----
	virtual UInt64		ReportMediumBlockSize ( void );
	virtual UInt64		ReportMediumTotalBlockCount ( void );
	virtual bool		ReportMediumWriteProtection ( void );
	
	
protected:
	
	
	// Command methods to access all commands available to SBC based devices.
	virtual bool ERASE_10 (
						SCSITaskIdentifier			request,
						SCSICmdField1Bit 			ERA,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool ERASE_12 (
						SCSITaskIdentifier			request,
						SCSICmdField1Bit 			ERA,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField4Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool FORMAT_UNIT (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						IOByteCount					defectListSize,
						SCSICmdField1Bit 			FMTDATA,
						SCSICmdField1Bit 			CMPLST,
						SCSICmdField3Bit 			DEFECT_LIST_FORMAT,
						SCSICmdField1Byte 			VENDOR_SPECIFIC,
						SCSICmdField2Byte 			INTERLEAVE,
						SCSICmdField1Byte 			CONTROL );

	virtual bool LOCK_UNLOCK_CACHE (
						SCSITaskIdentifier			request,
						SCSICmdField1Bit 			LOCK,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			NUMBER_OF_BLOCKS,
						SCSICmdField1Byte 			CONTROL );


	virtual bool MEDIUM_SCAN (
						SCSITaskIdentifier			request,
			 			IOMemoryDescriptor *		dataBuffer,
		   				SCSICmdField1Bit 			WBS,
		   				SCSICmdField1Bit 			ASA,
		   				SCSICmdField1Bit 			PSD,
		   				SCSICmdField1Bit 			PRA,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			PARAMETER_LIST_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool PREFETCH (
						SCSITaskIdentifier			request,
						SCSICmdField1Bit 			IMMED,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool READ_6 (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						UInt32						blockSize,
						SCSICmdField21Bit 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField1Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool READ_10 (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						UInt32						blockSize,
						SCSICmdField1Bit 			DPO,
						SCSICmdField1Bit 			FUA,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool READ_12 (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						UInt32						blockSize,
						SCSICmdField1Bit 			DPO,
						SCSICmdField1Bit 			FUA,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField4Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool READ_CAPACITY (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField1Bit 			PMI,
						SCSICmdField1Byte 			CONTROL );

	virtual bool READ_DEFECT_DATA_10 (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			PLIST,
						SCSICmdField1Bit 			GLIST,
						SCSICmdField3Bit 			DEFECT_LIST_FORMAT,
						SCSICmdField2Byte 			ALLOCATION_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool READ_DEFECT_DATA_12 (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			PLIST,
						SCSICmdField1Bit 			GLIST,
						SCSICmdField3Bit 			DEFECT_LIST_FORMAT,
						SCSICmdField4Byte 			ALLOCATION_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool READ_GENERATION (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField1Byte 			ALLOCATION_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool READ_LONG (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			CORRCT,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			BYTE_TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool READ_UPDATED_BLOCK_10 (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			DPO,
						SCSICmdField1Bit 			FUA,
					 	SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField1Bit 			LATEST,
					 	SCSICmdField15Bit 			GENERATION_ADDRESS,
						SCSICmdField1Byte 			CONTROL );

	virtual bool REASSIGN_BLOCKS (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Byte 			CONTROL );
	
	virtual bool REBUILD (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			DPO,
						SCSICmdField1Bit 			FUA,
					 	SCSICmdField1Bit 			INTDATA,
						SCSICmdField2Bit 			PORT_CONTROL,
					 	SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField4Byte 			REBUILD_LENGTH,
						SCSICmdField4Byte 			PARAMETER_LIST_LENGTH,
						SCSICmdField1Byte 			CONTROL );
	
	virtual bool REGENERATE (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit			DPO,
						SCSICmdField1Bit 			FUA,
					 	SCSICmdField1Bit 			INTDATA,
					 	SCSICmdField2Bit 			PORT_CONTROL,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField4Byte 			REBUILD_LENGTH,
						SCSICmdField4Byte 			PARAMETER_LIST_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool REZERO_UNIT (
						SCSITaskIdentifier			request,
						SCSICmdField1Byte 			CONTROL );

	virtual bool SEARCH_DATA_EQUAL_10 (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			INVERT,
						SCSICmdField1Bit 			SPNDAT,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			NUMBER_OF_BLOCKS_TO_SEARCH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool SEARCH_DATA_HIGH_10 (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			INVERT,
						SCSICmdField1Bit 			SPNDAT,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			NUMBER_OF_BLOCKS_TO_SEARCH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool SEARCH_DATA_LOW_10 (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			INVERT,
						SCSICmdField1Bit 			SPNDAT,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			NUMBER_OF_BLOCKS_TO_SEARCH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool SEEK_6 (
						SCSITaskIdentifier			request,
						SCSICmdField21Bit 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField1Byte 			CONTROL );

	virtual bool SEEK_10 (
						SCSITaskIdentifier			request,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField1Byte 			CONTROL );

	virtual bool SET_LIMITS_10 (
						SCSITaskIdentifier			request,
						SCSICmdField1Bit 			RDINH,
						SCSICmdField1Bit 			WRINH,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			NUMBER_OF_BLOCKS,
						SCSICmdField1Byte 			CONTROL );

	virtual bool SET_LIMITS_12 (
						SCSITaskIdentifier			request,
						SCSICmdField1Bit 			RDINH,
						SCSICmdField1Bit 			WRINH,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField4Byte 			NUMBER_OF_BLOCKS,
						SCSICmdField1Byte 			CONTROL );

	virtual bool START_STOP_UNIT (
						SCSITaskIdentifier			request,
						SCSICmdField1Bit 			IMMED,
						SCSICmdField4Bit 			POWER_CONDITIONS,
						SCSICmdField1Bit 			LOEJ,
						SCSICmdField1Bit 			START,
						SCSICmdField1Byte 			CONTROL );

	virtual bool SYNCHRONIZE_CACHE (
						SCSITaskIdentifier			request,
						SCSICmdField1Bit 			IMMED,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			NUMBER_OF_BLOCKS,
						SCSICmdField1Byte 			CONTROL );

	virtual bool UPDATE_BLOCK (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField1Byte 			CONTROL );

	virtual bool VERIFY_10 (
						SCSITaskIdentifier			request,
						SCSICmdField1Bit 			DPO,
						SCSICmdField1Bit 			BLKVFY,
						SCSICmdField1Bit 			BYTCHK,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			VERIFICATION_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool VERIFY_12 (
						SCSITaskIdentifier			request,
						SCSICmdField1Bit 			DPO,
						SCSICmdField1Bit 			BLKVFY,
						SCSICmdField1Bit 			BYTCHK,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField4Byte 			VERIFICATION_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool WRITE_6 (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						UInt32						blockSize,
						SCSICmdField2Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField1Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool WRITE_10 (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						UInt32						blockSize,
						SCSICmdField1Bit 			DPO,
						SCSICmdField1Bit 			FUA,
						SCSICmdField1Bit 			EBP,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool WRITE_12 (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						UInt32						blockSize,
						SCSICmdField1Bit 			DPO,
						SCSICmdField1Bit 			FUA,
						SCSICmdField1Bit 			EBP,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField4Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool WRITE_AND_VERIFY_10 (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						UInt32						blockSize,
						SCSICmdField1Bit 			DPO,
						SCSICmdField1Bit 			EBP,
						SCSICmdField1Bit 			BYTCHK,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool WRITE_AND_VERIFY_12 (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						UInt32						blockSize,
						SCSICmdField1Bit 			DPO,
						SCSICmdField1Bit 			EBP,
						SCSICmdField1Bit 			BYTCHK,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField4Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool WRITE_LONG (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool WRITE_SAME (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			PBDATA,
						SCSICmdField1Bit 			LBDATA,
						SCSICmdField1Bit 			RELADR,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool XDREAD (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );
	
	virtual bool XDWRITE (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			DPO,
						SCSICmdField1Bit 			FUA,
						SCSICmdField1Bit 			DISABLE_WRITE,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );

	virtual bool XDWRITE_EXTENDED (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			TABLE_ADDRESS,
						SCSICmdField1Bit 			DPO,
						SCSICmdField1Bit 			FUA,
						SCSICmdField1Bit 			DISABLE_WRITE,
						SCSICmdField2Bit 			PORT_CONTROL,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField4Byte 			SECONDARY_BLOCK_ADDRESS,
						SCSICmdField4Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			SECONDARY_ADDRESS,
						SCSICmdField1Byte 			CONTROL );

	virtual bool XPWRITE (
						SCSITaskIdentifier			request,
						IOMemoryDescriptor *		dataBuffer,
						SCSICmdField1Bit 			DPO,
						SCSICmdField1Bit 			FUA,
						SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS,
						SCSICmdField2Byte 			TRANSFER_LENGTH,
						SCSICmdField1Byte 			CONTROL );
	
	OSMetaClassDeclareReservedUsed ( IOSCSIBlockCommandsDevice, 1 );
	
public:
	
	virtual IOReturn	PowerDownHandler (	void * 			refCon,
											UInt32 			messageType,
											IOService * 	provider,
											void * 			messageArgument,
											vm_size_t 		argSize );
	
	
	OSMetaClassDeclareReservedUsed ( IOSCSIBlockCommandsDevice, 2 );
	
protected:
	
	virtual	void		SetMediumIcon ( void );
	
		
private:
	
	// Space reserved for future expansion.
	OSMetaClassDeclareReservedUnused ( IOSCSIBlockCommandsDevice, 3 );
	OSMetaClassDeclareReservedUnused ( IOSCSIBlockCommandsDevice, 4 );
	OSMetaClassDeclareReservedUnused ( IOSCSIBlockCommandsDevice, 5 );
	OSMetaClassDeclareReservedUnused ( IOSCSIBlockCommandsDevice, 6 );
	OSMetaClassDeclareReservedUnused ( IOSCSIBlockCommandsDevice, 7 );
	OSMetaClassDeclareReservedUnused ( IOSCSIBlockCommandsDevice, 8 );
	OSMetaClassDeclareReservedUnused ( IOSCSIBlockCommandsDevice, 9 );
	OSMetaClassDeclareReservedUnused ( IOSCSIBlockCommandsDevice, 10 );
	OSMetaClassDeclareReservedUnused ( IOSCSIBlockCommandsDevice, 11 );
	OSMetaClassDeclareReservedUnused ( IOSCSIBlockCommandsDevice, 12 );
	OSMetaClassDeclareReservedUnused ( IOSCSIBlockCommandsDevice, 13 );
	OSMetaClassDeclareReservedUnused ( IOSCSIBlockCommandsDevice, 14 );
	OSMetaClassDeclareReservedUnused ( IOSCSIBlockCommandsDevice, 15 );
	OSMetaClassDeclareReservedUnused ( IOSCSIBlockCommandsDevice, 16 );
	
};

#endif	/* defined(KERNEL) && defined(__cplusplus) */

#endif /* _IOKIT_IO_SCSI_BLOCK_COMMANDS_DEVICE_H_ */