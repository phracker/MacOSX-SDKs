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
	Currently UFI devices are treated as SCSI Primary Command devices.  Since UFI
	is a unique non-SCSI defined command set, in a future release, UFI device 
	support will be migrated to using a driver stack better suited to the 
	specification.
*/

#ifndef _IOKIT_IOUSBMASSSTORAGEUFISUBCLASS_H
#define _IOKIT_IOUSBMASSSTORAGEUFISUBCLASS_H

// This class' header file
#include <IOKit/usb/IOUSBMassStorageClass.h>
#include <IOKit/scsi-commands/SCSICommandDefinitions.h>

#pragma mark -
#pragma mark IOUSBMassStorageUFISubclass definition

class IOUSBMassStorageUFISubclass : public IOUSBMassStorageClass
{
    OSDeclareDefaultStructors(IOUSBMassStorageUFISubclass)

private:
	static void			AsyncReadWriteComplete( SCSITaskIdentifier	completedTask );

protected:
    // Reserve space for future expansion.
    struct IOUSBMassStorageUFISubclassExpansionData { };
    IOUSBMassStorageUFISubclassExpansionData *fIOUSBMassStorageUFISubclassReserved;

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

	OSDictionary * 		fDeviceCharacteristicsDictionary;

	virtual	bool		BeginProvidedServices( void );
	virtual	bool		EndProvidedServices( void );

	// ---- Methods for controlling the current state of device support ----
	virtual bool		InitializeDeviceSupport( void );
	virtual void		SuspendDeviceSupport( void );
	virtual void		ResumeDeviceSupport( void );
	virtual void		TerminateDeviceSupport( void );

	// ---- Methods used for   ----
	virtual bool		ClearNotReadyStatus( void );
	virtual void 		CreateStorageServiceNub( void );
	virtual bool		DetermineDeviceCharacteristics( void );

	// ---- Methods used for controlling the polling thread ----
	virtual void		ProcessPoll( void );
	virtual void		EnablePolling( void );
	virtual void		DisablePolling( void );

	// Main and support methods for polling for new Media
	virtual void		PollForNewMedia( void );
	virtual bool		DetermineMediaPresence( void );
	virtual bool		DetermineMediumCapacity( 
							UInt64 * 				blockSize, 
							UInt64 * 				blockCount );
	virtual bool		DetermineMediumWriteProtectState( void );

	// Main and support methods for polling for Media removal
	virtual void		PollForMediaRemoval( void );

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

	// This will get a new SCSITask for the caller
	virtual SCSITaskIdentifier		GetSCSITask ( void );
	
	// This will release a SCSITask (eventually return it to a pool)
	virtual void					ReleaseSCSITask ( SCSITaskIdentifier request );

	// Call for executing the command synchronously	
	SCSIServiceResponse 			SendCommand ( 	
										SCSITaskIdentifier 	request,
										UInt32 				timeoutDuration );
														
	static void		TaskCallback ( SCSITaskIdentifier completedTask );
	
	// Call for executing the command asycnchronously	
	void 							SendCommand ( 
										SCSITaskIdentifier 	request,
										UInt32 				timeoutDuration,
										SCSITaskCompletion 	taskCompletion );

	bool							SetTaskAttribute ( 
										SCSITaskIdentifier 		request, 
										SCSITaskAttribute 		newAttribute );
	SCSITaskAttribute				GetTaskAttribute ( 
										SCSITaskIdentifier 		request );
	bool							SetTaskState ( 	
										SCSITaskIdentifier 		request,
										SCSITaskState 			newTaskState );
	SCSITaskState					GetTaskState ( 
										SCSITaskIdentifier 		request );
	bool							SetTaskStatus ( 
										SCSITaskIdentifier 		request, 
										SCSITaskStatus 			newStatus );
	SCSITaskStatus					GetTaskStatus ( 
										SCSITaskIdentifier 		request );
	bool							SetDataTransferDirection ( 
										SCSITaskIdentifier 		request, 
										UInt8 					newDirection );
	UInt8							GetDataTransferDirection ( 
										SCSITaskIdentifier 		request );
	bool							SetRequestedDataTransferCount (
										SCSITaskIdentifier 		request, 
										UInt64 					newRequestedCount );
	UInt64							GetRequestedDataTransferCount (
										SCSITaskIdentifier 		request );
	bool							SetRealizedDataTransferCount (
										SCSITaskIdentifier 		request,
										UInt64 					newRealizedDataCount );
	UInt64							GetRealizedDataTransferCount( 
										SCSITaskIdentifier 		request );
	bool							SetDataBuffer( 
										SCSITaskIdentifier 		request, 
										IOMemoryDescriptor * 	newBuffer );
	IOMemoryDescriptor *			GetDataBuffer( 
										SCSITaskIdentifier 		request );
	bool							SetTimeoutDuration( 
										SCSITaskIdentifier 		request, 
										UInt32 					newTimeout );
	UInt32							GetTimeoutDuration( 
										SCSITaskIdentifier 		request );
	bool							SetTaskCompletionCallback( 
										SCSITaskIdentifier 		request,
										SCSITaskCompletion 		newCallback );
	void							TaskCompletedNotification ( 
										SCSITaskIdentifier 		request );

	bool							SetServiceResponse( 
										SCSITaskIdentifier 		request,
										SCSIServiceResponse 	serviceResponse );
	SCSIServiceResponse 			GetServiceResponse( 
										SCSITaskIdentifier 		request );
	bool							SetAutosenseCommand(
										SCSITaskIdentifier 		request,
										UInt8					cdbByte0,
										UInt8					cdbByte1,
										UInt8					cdbByte2,
										UInt8					cdbByte3,
										UInt8					cdbByte4,
										UInt8					cdbByte5 );
	bool							GetAutoSenseData( 	
										SCSITaskIdentifier 		request,
										SCSI_Sense_Data * 		senseData );
	bool							SetApplicationLayerReference( 
										SCSITaskIdentifier 		request,
										void * 					newReferenceValue );
	void *							GetApplicationLayerReference( 
										SCSITaskIdentifier 		request );
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
	
	// isParameterValid are used to validate that the parameter passed into
	// the command methods are of the correct value.
	
	// Validate Parameter used for 1 bit to 1 byte paramaters
    inline bool 	IsParameterValid( 
							SCSICmdField1Byte 			param,
							SCSICmdField1Byte 			mask );
	
	// Validate Parameter used for 9 bit to 2 byte paramaters
	inline bool 	IsParameterValid( 
							SCSICmdField2Byte 			param,
							SCSICmdField2Byte 			mask );
	
	// Validate Parameter used for 17 bit to 4 byte paramaters
	inline bool 	IsParameterValid( 
							SCSICmdField4Byte 			param,
							SCSICmdField4Byte 			mask );
	
	inline bool 	IsBufferAndCapacityValid(
							IOMemoryDescriptor *		dataBuffer,
							UInt32 						requiredSize );
	
	// ----- Methods for accessing the SCSITask ----------
	// Populate the 12 Byte Command Descriptor Block
	bool 	SetCommandDescriptorBlock (
							SCSITask *					request,
							UInt8						cdbByte0,
							UInt8						cdbByte1,
							UInt8						cdbByte2,
							UInt8						cdbByte3,
							UInt8						cdbByte4,
							UInt8						cdbByte5,
							UInt8						cdbByte6 = 0,
							UInt8						cdbByte7 = 0,
							UInt8						cdbByte8 = 0,
							UInt8						cdbByte9 = 0,
							UInt8						cdbByte10 = 0,
							UInt8						cdbByte11 = 0 );

	// Set up the control information for the transfer, including
	// the transfer direction and the number of bytes to transfer.
	// Need to add new version of method and remove the default values
	// from this one.
	bool	SetDataTransferControl(
							SCSITask *					request,
							UInt8						dataTransferDirection,
							IOMemoryDescriptor *		dataBuffer = NULL,
							UInt64						transferCountInBytes = 0 );

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

#endif _IOKIT_IOUSBMASSSTORAGEUFISUBCLASS_H
