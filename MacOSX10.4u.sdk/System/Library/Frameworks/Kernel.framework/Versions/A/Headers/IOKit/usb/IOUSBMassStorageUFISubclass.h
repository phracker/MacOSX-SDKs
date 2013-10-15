/*
 * Copyright (c) 1998-2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _IOKIT_IOUSBMASSSTORAGEUFISUBCLASS_H
#define _IOKIT_IOUSBMASSSTORAGEUFISUBCLASS_H

// This class' header file
#include <IOKit/usb/IOUSBMassStorageClass.h>
#include <IOKit/scsi-commands/IOSCSIPrimaryCommandsDevice.h>

#pragma mark -
#pragma mark IOUSBMassStorageUFIDevice declaration

class IOUSBMassStorageUFIDevice : public IOSCSIPrimaryCommandsDevice
{
    OSDeclareDefaultStructors(IOUSBMassStorageUFIDevice)

private:
	static void			AsyncReadWriteComplete( SCSITaskIdentifier	completedTask );
	
protected:
    // Reserve space for future expansion.
    struct IOUSBMassStorageUFIDeviceExpansionData
	{
	};
    IOUSBMassStorageUFIDeviceExpansionData *fIOUSBMassStorageUFIDeviceReserved;
		
	// ---- Medium Characteristics ----
	bool				fMediumPresent;

	// The byte count of each physical block on the medium.
	UInt32				fMediumBlockSize;

	// The total number of blocks of fMediumBlockSize on the medium.
	UInt32				fMediumBlockCount;

	// Whether the installed medium is protected from writes
	bool				fMediumIsWriteProtected;

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
	virtual bool		InitializeDeviceSupport( void );
	virtual void 		StartDeviceSupport ( void );
	virtual void		SuspendDeviceSupport( void );
	virtual void		ResumeDeviceSupport( void );
	virtual void 		StopDeviceSupport ( void );
	virtual void		TerminateDeviceSupport( void );

	// ---- Methods used for misc  ----
	virtual bool		ClearNotReadyStatus( void );
	virtual void 		CreateStorageServiceNub( void );
	virtual bool		DetermineDeviceCharacteristics( void );

	// ---- Methods used for controlling the polling thread ----
	virtual void		ProcessPoll( void );
	virtual void		EnablePolling( void );
	virtual void		DisablePolling( void );

	// ---- Main and support methods for polling for new Media ----
	virtual void		PollForNewMedia( void );
	virtual bool		DetermineMediaPresence( void );
	virtual bool		DetermineMediumCapacity( 
							UInt64 * 				blockSize, 
							UInt64 * 				blockCount );
	virtual bool		DetermineMediumWriteProtectState( void );

	// ---- Main and support methods for polling for Media removal ----
	virtual void		PollForMediaRemoval( void );
	
	// ---- Methods used for power managment ----
	virtual UInt32		GetInitialPowerState ( void );
	virtual void		HandlePowerChange ( void );
	virtual void		HandleCheckPowerState ( void );
	virtual void		TicklePowerManager ( void );
	virtual UInt32		GetNumberOfPowerStateTransitions ( void );

	// ---- Methods used for handling medium characteristics ----
    virtual void		SetMediumCharacteristics( 
    						UInt32 					blockSize, 
    						UInt32 					blockCount );
	
	virtual void		ResetMediumCharacteristics( void );

	virtual IOReturn	IssueRead( 	
							IOMemoryDescriptor *	buffer,
                         	UInt64					startBlock,
                     		UInt64					blockCount );
	
	virtual IOReturn	IssueRead(	
							IOMemoryDescriptor *	buffer,
                      		UInt64					startBlock,
                     		UInt64					blockCount,
                       		void * 					clientData );


	virtual IOReturn	IssueWrite( 
							IOMemoryDescriptor *	buffer,
                    		UInt64					startBlock,
                       		UInt64					blockCount );

	virtual IOReturn	IssueWrite(	
							IOMemoryDescriptor *	buffer,
                         	UInt64					startBlock,
                      		UInt64					blockCount,
							void * 					clientData );

public:
		
	static 	void		sProcessPoll( void * pdtDriver, void * refCon );

	// Interface to the UFI Storage Services Driver
	// ---- Methods for controlling the device ----
	virtual IOReturn	SyncReadWrite(
							IOMemoryDescriptor *	buffer,
							UInt64					startBlock,
							UInt64					blockCount,
							UInt64					blockSize );

	virtual IOReturn	AsyncReadWrite(
							IOMemoryDescriptor *	buffer,
							UInt64					startBlock,
							UInt64					blockCount,
							UInt64					blockSize,
							void * 					clientData );

	// ---- Methods for controlling medium state ----
	virtual IOReturn	EjectTheMedium( void );

	// ---- Methods for controlling media format ----
	virtual IOReturn	FormatMedium( 
							UInt64 					blockCount, 
							UInt64 					blockSize );
	virtual UInt32		GetFormatCapacities( 	
							UInt64 * 				capacities,
             				UInt32   				capacitiesMaxCount ) const;

	// ---- Query methods to report device characteristics ----
	// Report the maximum number of blocks that the device can handle per
	// read or write.  A value of 0 (zero) indicates there is no limit aside
	// from the size of the method's return parameter.
	virtual UInt64		ReportDeviceMaxBlocksReadTransfer( void );
	virtual UInt64		ReportDeviceMaxBlocksWriteTransfer( void );
	
	// ---- Query methods to report installed medium characteristics ----
	virtual UInt64		ReportMediumBlockSize( void );
	virtual UInt64		ReportMediumTotalBlockCount( void );
	virtual bool		ReportMediumWriteProtection( void );
        
	// Methods for getting device information strings
	virtual char *		GetVendorString( void );
	virtual char *		GetProductString( void );
	virtual char *		GetRevisionString( void );
	OSDictionary *		GetProtocolCharacteristicsDictionary ( void );
	OSDictionary *		GetDeviceCharacteristicsDictionary ( void );	
	
protected:
	// Utility methods used by all SCSI Command Set objects
	
	// isParameterValid methods are used to validate that the parameter passed into
	// the command methods are of the correct value.
	
	// Validate Parameter used for 1 bit to 1 byte paramaters
    bool		 	IsParameterValid( 
							SCSICmdField1Byte 			param,
							SCSICmdField1Byte 			mask );
	
	// Validate Parameter used for 9 bit to 2 byte paramaters
	bool		 	IsParameterValid( 
							SCSICmdField2Byte 			param,
							SCSICmdField2Byte 			mask );
	
	// Validate Parameter used for 17 bit to 4 byte paramaters
	bool		 	IsParameterValid( 
							SCSICmdField4Byte 			param,
							SCSICmdField4Byte 			mask );
	
	// UFI Required Commands
	virtual bool 	FORMAT_UNIT(
							SCSITaskIdentifier			request,
			    			IOMemoryDescriptor *		dataBuffer,
			    			IOByteCount					defectListSize,
			    			SCSICmdField1Byte 			TRACK_NUMBER, 
			    			SCSICmdField2Byte 			INTERLEAVE );

	virtual bool	INQUIRY(
							SCSITaskIdentifier			request,
    						IOMemoryDescriptor 			*dataBuffer,
    						SCSICmdField1Byte 			PAGE_OR_OPERATION_CODE,
    						SCSICmdField1Byte 			ALLOCATION_LENGTH );

   	virtual bool	MODE_SELECT_10(
							SCSITaskIdentifier			request,
    						IOMemoryDescriptor 			*dataBuffer,
    						SCSICmdField1Bit 			PF,
    						SCSICmdField1Bit 			SP,
    						SCSICmdField2Byte 			PARAMETER_LIST_LENGTH );  

   	virtual bool	MODE_SENSE_10(
							SCSITaskIdentifier			request,
    						IOMemoryDescriptor 			*dataBuffer,
    						SCSICmdField1Bit 			DBD,
	   						SCSICmdField2Bit 			PC,
	   						SCSICmdField6Bit 			PAGE_CODE,
	   						SCSICmdField2Byte 			PARAMETER_LIST_LENGTH );

    virtual bool	PREVENT_ALLOW_MEDIUM_REMOVAL( 
							SCSITaskIdentifier			request,
	     					SCSICmdField1Bit 			PREVENT );

	virtual bool 	READ_10(
							SCSITaskIdentifier			request,
			    			IOMemoryDescriptor *		dataBuffer, 
			    			UInt32						blockSize,
			    			SCSICmdField1Bit 			DPO, 
			    			SCSICmdField1Bit 			FUA,
							SCSICmdField1Bit 			RELADR, 
							SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS, 
							SCSICmdField2Byte 			TRANSFER_LENGTH );

	virtual bool 	READ_12(
							SCSITaskIdentifier			request,
			    			IOMemoryDescriptor *		dataBuffer, 
			    			UInt32						blockSize,
			    			SCSICmdField1Bit 			DPO, 
			    			SCSICmdField1Bit 			FUA,
							SCSICmdField1Bit 			RELADR, 
							SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS, 
							SCSICmdField4Byte 			TRANSFER_LENGTH );

	virtual bool 	READ_CAPACITY(
							SCSITaskIdentifier			request,
			    			IOMemoryDescriptor *		dataBuffer, 
			    			SCSICmdField1Bit 			RELADR,
							SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS, 
							SCSICmdField1Bit 			PMI );

	virtual bool 	READ_FORMAT_CAPACITIES(
							SCSITaskIdentifier			request,
			    			IOMemoryDescriptor *		dataBuffer, 
			    			SCSICmdField2Byte 			ALLOCATION_LENGTH );

	virtual bool 	REQUEST_SENSE(
							SCSITaskIdentifier			request,
   							IOMemoryDescriptor 			*dataBuffer,
			    			SCSICmdField1Byte 			ALLOCATION_LENGTH );
 	
	virtual bool 	REZERO_UNIT( 
							SCSITaskIdentifier			request );

	virtual bool 	SEEK( 
							SCSITaskIdentifier			request,
			    			SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS );

	virtual bool 	SEND_DIAGNOSTICS( 
							SCSITaskIdentifier			request,
							SCSICmdField1Bit 			PF, 
							SCSICmdField1Bit 			SELF_TEST, 
							SCSICmdField1Bit 			DEF_OFL, 
							SCSICmdField1Bit 			UNIT_OFL );

	virtual bool 	START_STOP_UNIT( 
							SCSITaskIdentifier			request,
							SCSICmdField1Bit 			IMMED, 
							SCSICmdField1Bit 			LOEJ, 
							SCSICmdField1Bit 			START );

    virtual bool 	TEST_UNIT_READY(  
							SCSITaskIdentifier			request );
 
	virtual bool 	VERIFY( 
							SCSITaskIdentifier			request,
							SCSICmdField1Bit 			DPO, 
							SCSICmdField1Bit 			BYTCHK, 
							SCSICmdField1Bit 			RELADR,
							SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS, 
							SCSICmdField2Byte 			VERIFICATION_LENGTH );

	virtual bool 	WRITE_10(
							SCSITaskIdentifier			request,
			    			IOMemoryDescriptor *		dataBuffer, 
			    			UInt32						blockSize,
			    			SCSICmdField1Bit 			DPO, 
			    			SCSICmdField1Bit 			FUA,
							SCSICmdField1Bit 			RELADR, 
							SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS, 
							SCSICmdField2Byte 			TRANSFER_LENGTH );

	virtual bool 	WRITE_12(
							SCSITaskIdentifier			request,
							IOMemoryDescriptor *		dataBuffer, 
			    			UInt32						blockSize,
			    			SCSICmdField1Bit 			DPO, 
							SCSICmdField1Bit 			EBP, 
							SCSICmdField1Bit 			RELADR, 
							SCSICmdField4Byte 			LOGICAL_BLOCK_ADDRESS, 
							SCSICmdField4Byte 			TRANSFER_LENGTH );

	virtual bool 	WRITE_AND_VERIFY(
							SCSITaskIdentifier			request,
			    			IOMemoryDescriptor *		dataBuffer, 
			    			UInt32						blockSize,
			    			SCSICmdField1Bit 			DPO,
			    			SCSICmdField1Bit 			BYTCHK, 
			    			SCSICmdField1Bit 			RELADR, 
			    			SCSICmdField4Byte			LOGICAL_BLOCK_ADDRESS, 
			    			SCSICmdField2Byte 			TRANSFER_LENGTH );
};


#pragma mark -
#pragma mark IOUSBMassStorageUFISubclass declaration

class IOUSBMassStorageUFISubclass : public IOUSBMassStorageClass
{
    OSDeclareDefaultStructors(IOUSBMassStorageUFISubclass)

protected:
	virtual	bool		BeginProvidedServices( void );
	virtual	bool		EndProvidedServices( void );
};

#endif _IOKIT_IOUSBMASSSTORAGEUFISUBCLASS_H
