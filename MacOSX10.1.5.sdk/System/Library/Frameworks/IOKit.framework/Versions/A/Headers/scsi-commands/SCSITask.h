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

#ifndef _IOKIT_SCSI_TASK_H_
#define _IOKIT_SCSI_TASK_H_

#if KERNEL
#include <IOKit/IOTypes.h>
#else
#include <CoreFoundation/CoreFoundation.h>
#endif

// SCSI Service Repsonse values
typedef enum SCSIServiceResponse
{
	// This is not one of the standard service responses defined by
	// SAM, but is necessary for asynchronous commands that are not 
	// yet completed.
	kSCSIServiceResponse_Request_In_Process					= 0,

	// General Service Response
	kSCSIServiceResponse_SERVICE_DELIVERY_OR_TARGET_FAILURE	= 1,

	// Service Responses for Execute Command
	kSCSIServiceResponse_TASK_COMPLETE 						= 2,
	kSCSIServiceResponse_LINK_COMMAND_COMPLETE				= 3,
	
	// Service Responses used for Task Management Functions
	kSCSIServiceResponse_FUNCTION_COMPLETE					= 4,
	kSCSIServiceResponse_FUNCTION_REJECTED					= 5
} SCSIServiceResponse;


/* Task Attribute and constants
 * The Task Attribute defines how this task should be managed
 * when determing order for queueing and submission to the 
 * appropriate device server.
 *
 * The Task Attribute is set by the SCSI Application Layer and cannot be
 * modified by the SCSI Protocol Layer.
 */
typedef enum SCSITaskAttribute
{
	kSCSITask_SIMPLE			= 0,
	kSCSITask_ORDERED			= 1,
	kSCSITask_HEAD_OF_QUEUE		= 2,
	kSCSITask_ACA				= 3
} SCSITaskAttribute;

/* Task State Constants
 * The Task State represents the current state of the task.  The state is set
 * to NEW_TASK when the task is created.  The SCSI Protocol Layer will then
 * adjust the state as the task is queued and during execution.  The SCSI
 * Application Layer can examine the state to monitor the progress of a task.
 * 
 * The Task State can only be modified by the SCSI Protocol Layer.  The SCSI
 * Application Layer can only read the state.
 */
typedef enum SCSITaskState
{
	kSCSITaskState_NEW_TASK		= 0,
	kSCSITaskState_ENABLED		= 1,
	kSCSITaskState_BLOCKED		= 2,
	kSCSITaskState_DORMANT		= 3,
	kSCSITaskState_ENDED		= 4
} SCSITaskState;


/* Task Status Constants
 * The Task Status represents the completion status of the task. Only when a 
 * task completes with a service response of either TASK_COMPLETED or 
 * LINK_COMMAND_COMPLETE,
 * the status will be considered valid.
 * 
 * The Task Status can only be modified by the SCSI Protocol Layer.  The SCSI
 * Application Layer can only read the status.
 */
typedef enum SCSITaskStatus
{
	kSCSITaskStatus_GOOD						= 0x00,
	kSCSITaskStatus_CHECK_CONDITION				= 0x02,
	kSCSITaskStatus_CONDITION_MET				= 0x04,
	kSCSITaskStatus_BUSY						= 0x08,
	kSCSITaskStatus_INTERMEDIATE				= 0x10,
	kSCSITaskStatus_INTERMEDIATE_CONDITION_MET	= 0x14,
	kSCSITaskStatus_RESERVATION_CONFLICT		= 0x18,
	kSCSITaskStatus_TASK_SET_FULL				= 0x28,
	kSCSITaskStatus_ACA_ACTIVE					= 0x30,
	
	// This status is not defined by the SCSI specifications,
	// but is here to provide a status that can be returned in
	// cases where there is not status available from the device
	// server, for example, when the service response is neither
	// TASK_COMPLETED nor LINK_COMMAND_COMPLETE.
	kSCSITaskStatus_No_Status					= 0xFF
} SCSITaskStatus;

// Command Descriptor Block Size constants
enum
{
#ifndef _OPEN_SOURCE_
	// -->What about the variable Byte 7F command?
#endif
	// This is the largest size a Command Descriptor
	// Block can be as specified in SPC-2
	kSCSICDBSize_Maximum 	= 16,
	kSCSICDBSize_6Byte 		= 6,
	kSCSICDBSize_10Byte 	= 10,
	kSCSICDBSize_12Byte 	= 12,
	kSCSICDBSize_16Byte 	= 16
};

typedef UInt8 SCSICommandDescriptorBlock[kSCSICDBSize_Maximum];

// Constants for the DataTransferDirection field
enum
{
	kSCSIDataTransfer_NoDataTransfer		= 0x00,
	kSCSIDataTransfer_FromInitiatorToTarget	= 0x01,
	kSCSIDataTransfer_FromTargetToInitiator	= 0x02
};


#if defined(KERNEL) && defined(__cplusplus)


// Basic MacOS X Headers
#include <libkern/c++/OSObject.h>

// IOKit Headers
#include <IOKit/IOCommand.h>
#include <IOKit/IOReturn.h>
#include <IOKit/IOMemoryDescriptor.h>

#include <IOKit/scsi-commands/SCSICmds_REQUEST_SENSE_Defs.h>

/* The SCSI Task mode is used by the SCSI Protocol Layer to 
 * indicate what mode the task is executing, the command or
 * the AutoSense command.
 */
typedef enum SCSITaskMode
{
	kSCSITaskMode_CommandExecution	= 1,
	kSCSITaskMode_Autosense			= 2
} SCSITaskMode;

/* This is an opaque object that represents a task.  This is used
 * so that driver for both the SCSI Protocol Layer and the SCSI 
 * Application Layer cannot modify the SCSITask object directly but must
 * instead use the inherited methods to do so.  This prevents changing
 * of properties that are not allowed to be changed by a given layer.
 */
typedef OSObject *	SCSITaskIdentifier;

typedef void ( *SCSITaskCompletion )( SCSITaskIdentifier completedTask );

class SCSITask : public IOCommand
{
	
	OSDeclareDefaultStructors ( SCSITask )
	
private:
	
	// Object that owns the instantiation of the SCSI Task object.
	OSObject *					fOwner;
	
    // The member variables that represent each part of the Task
    // Task Management members
    SCSITaskAttribute			fTaskAttribute;
    SCSITaskState				fTaskState;
	SCSITaskStatus				fTaskStatus;
	
    // The intended Logical Unit Number for this Task.  Currently only single
    // level LUN values are supported.
    UInt8						fLogicalUnitNumber;
	
    SCSICommandDescriptorBlock	fCommandDescriptorBlock;
    UInt8						fCommandSize;
    UInt8						fTransferDirection;
    IOMemoryDescriptor *		fDataBuffer;
    UInt64						fDataBufferOffset;
    UInt64						fRequestedByteCountOfTransfer;
    UInt64						fRealizedByteCountOfTransfer;
	
#ifndef _OPEN_SOURCE_
    // --> Either system wide or SCSITask object specific constants need to 
    // --> be defined.
#endif
	// Specifies the amount of time in milliseconds to wait for a task to
	// complete.  A zero value indicates that the task should be given the
	// longest duration possible by the Protocol Services Driver to complete.
    UInt32						fTimeoutDuration;

	SCSIServiceResponse			fServiceResponse;    
    
    SCSITaskCompletion			fCompletionCallback;

    // Autosense related members
    // This member indicates whether the client wants the SCSI Protocol
    // Layer to request autosense data if the command completes with a
    // CHECK_CONDITION status.
    bool						fAutosenseDataRequested;

    SCSICommandDescriptorBlock	fAutosenseCDB;
    UInt8						fAutosenseCDBSize;

    bool						fAutoSenseDataIsValid;
    SCSI_Sense_Data				fAutoSenseData;
    UInt64						fAutoSenseRealizedByteCountOfTransfer;

	IOMemoryDescriptor *		fAutosenseDescriptor;
	
    // Reference members for each layer.  Since these may contain a memory address, they
    // are declared as void * so that they will scale to a 64-bit system.
    void *						fProtocolLayerReference;
    void *						fApplicationLayerReference;
    
    // Pointer to the next SCSI Task in the queue.  This can only be used by the SCSI
    // Protocol Layer
    SCSITask *					fNextTaskInQueue;

	// The Task Execution mode is only used by the SCSI Protocol Layer for 
	// indicating whether the command currently being executed is the client's
	// command or the AutoSense RequestSense command.
	SCSITaskMode				fTaskExecutionMode;
	
    // Reserve space for future expansion.
    struct SCSITaskExpansionData { };
    SCSITaskExpansionData *		fSCSITaskReserved;

public:
    virtual bool		init( void );
	virtual void		free( void );


	// Utility methods for setting and retreiving the Object that owns the
	// instantiation of the SCSI Task
	bool				SetTaskOwner( OSObject	*taskOwner );
	OSObject *			GetTaskOwner( void );
	
    // Utility method to reset the object so that it may be used for a new
	// Task.  This method will return true if the reset was successful
	// and false if it failed because it represents an active task.
	bool				ResetForNewTask( void );
	
	// Utility method to check if this task represents an active.
	bool				IsTaskActive( void );

	// Utility Methods for managing the Logical Unit Number for which this Task 
	// is intended.
	bool				SetLogicalUnitNumber( UInt8 newLUN );
	UInt8				GetLogicalUnitNumber( void );
	
	// The following methods are used to set and to get the value of the
	// task's attributes.  The set methods all return a bool which indicates
	// whether the attribute was successfully set.  The set methods will return
	// true if the attribute was updated to the new value and false if it was
	// not.  A false return value usually indicates that the task is active
	// and the attribute that was requested to be changed, can not be changed
	// once a task is active.
	// The get methods will always return the current value of the attribute
	// regardless of whether it has been previously set and regardless of
	// whether or not the task is active.	
	bool				SetTaskAttribute( 
							SCSITaskAttribute newAttributeValue );
	SCSITaskAttribute	GetTaskAttribute( void );

	bool				SetTaskState( SCSITaskState newTaskState );
	SCSITaskState		GetTaskState( void );

	// Accessor methods for getting and setting that status of the Task.	
	bool				SetTaskStatus( SCSITaskStatus newTaskStatus );
	SCSITaskStatus		GetTaskStatus( void );
	
    // Accessor functions for setting the properties of the Task
    
    // Methods for populating the Command Descriptor Block.  Individual methods
    // are used instead of having a single method so that the CDB size is
    // automatically known.
	// Populate the 6 Byte Command Descriptor Block
	bool 	SetCommandDescriptorBlock( 
							UInt8			cdbByte0,
							UInt8			cdbByte1,
							UInt8			cdbByte2,
							UInt8			cdbByte3,
							UInt8			cdbByte4,
							UInt8			cdbByte5 );

	// Populate the 10 Byte Command Descriptor Block
	bool 	SetCommandDescriptorBlock( 
							UInt8			cdbByte0,
							UInt8			cdbByte1,
							UInt8			cdbByte2,
							UInt8			cdbByte3,
							UInt8			cdbByte4,
							UInt8			cdbByte5,
							UInt8			cdbByte6,
							UInt8			cdbByte7,
							UInt8			cdbByte8,
							UInt8			cdbByte9 );

	// Populate the 12 Byte Command Descriptor Block
	bool 	SetCommandDescriptorBlock( 
							UInt8			cdbByte0,
							UInt8			cdbByte1,
							UInt8			cdbByte2,
							UInt8			cdbByte3,
							UInt8			cdbByte4,
							UInt8			cdbByte5,
							UInt8			cdbByte6,
							UInt8			cdbByte7,
							UInt8			cdbByte8,
							UInt8			cdbByte9,
							UInt8			cdbByte10,
							UInt8			cdbByte11 );

	// Populate the 16 Byte Command Descriptor Block
	bool 	SetCommandDescriptorBlock( 
							UInt8			cdbByte0,
							UInt8			cdbByte1,
							UInt8			cdbByte2,
							UInt8			cdbByte3,
							UInt8			cdbByte4,
							UInt8			cdbByte5,
							UInt8			cdbByte6,
							UInt8			cdbByte7,
							UInt8			cdbByte8,
							UInt8			cdbByte9,
							UInt8			cdbByte10,
							UInt8			cdbByte11,
							UInt8			cdbByte12,
							UInt8			cdbByte13,
							UInt8			cdbByte14,
							UInt8			cdbByte15 );

	UInt8	GetCommandDescriptorBlockSize( void );

	// This will always return a 16 Byte CDB.  If the Protocol Layer driver
	// does not support 16 Byte CDBs, it will have to create a local 
	// SCSICommandDescriptorBlock variable to get the CDB data and then
	// transfer the needed bytes from there.
	bool	GetCommandDescriptorBlock( 
        					SCSICommandDescriptorBlock * cdbData);
	
	// Set up the control information for the transfer, including
	// the transfer direction and the number of bytes to transfer.
	bool	SetDataTransferDirection( UInt8 newDataTransferDirection );
	UInt8	GetDataTransferDirection( void );

	bool	SetRequestedDataTransferCount( UInt64 requestedTransferCountInBytes );
	UInt64	GetRequestedDataTransferCount( void );

	bool	SetRealizedDataTransferCount( UInt64 realizedTransferCountInBytes );
	UInt64	GetRealizedDataTransferCount( void );

	bool	SetDataBuffer( IOMemoryDescriptor * newDataBuffer);
	IOMemoryDescriptor * GetDataBuffer( void );

	bool	SetDataBufferOffset( UInt64 newDataBufferOffset );
	UInt64	GetDataBufferOffset( void );

	bool	SetTimeoutDuration( UInt32 timeoutValue );
	UInt32	GetTimeoutDuration( void );

	bool	SetTaskCompletionCallback( SCSITaskCompletion newCallback );
	void	TaskCompletedNotification ( void );

	bool	SetServiceResponse( SCSIServiceResponse serviceResponse );
	SCSIServiceResponse GetServiceResponse( void );
	
	// Set the auto sense data that was returned for the SCSI Task.  According
	// to the SAM-2 rev 13 specification section 5.6.4.1 "Autosense", if the
	// protocol and logical unit support autosense, a device server will only 
	// return autosense data in response to command completion with a CHECK 
	// CONDITION status.
	// A return value of true indicates that the data was copied to the member 
	// sense data structure, false indicates that the data could not be saved.
	bool	SetAutoSenseData( SCSI_Sense_Data * senseData );
	
	// Get the auto sense data that was returned for the SCSI Task.  A return 
	// value of true indicates that valid auto sense data has been returned in 
	// the receivingBuffer.
	// A return value of false indicates that there is no auto sense data for 
	// this SCSI Task, and the receivingBuffer does not have valid data.
	// Since the SAM-2 specification only requires autosense data to be returned 
	// when a command completes with a CHECK CONDITION status, the autosense
	// data should only retrieved when the task status is 
	// kSCSITaskStatus_CHECK_CONDITION.
	// If the receivingBuffer is NULL, this routine will return whether the 
	// autosense data is valid without copying it to the receivingBuffer.
	bool	GetAutoSenseData( SCSI_Sense_Data * receivingBuffer );
	
	// These are used by the SCSI Protocol Layer object for storing and
	// retrieving a reference number that is specific to that protocol such
	// as a Task Tag.
	bool	SetProtocolLayerReference( void * newReferenceValue );
	void 	*GetProtocolLayerReference( void );

	// These are used by the SCSI Application Layer object for storing and
	// retrieving a reference number that is specific to that client.
	bool	SetApplicationLayerReference( void * newReferenceValue );
	void	*GetApplicationLayerReference( void );
	
	// These methods are only for the SCSI Protocol Layer to set the command
	// execution mode of the command.  There currently are two modes, standard
	// command execution for executing the command for which the task was 
	// created, and the autosense command execution mode for executing the 
	// Request Sense command for retrieving sense data.
	bool				SetTaskExecutionMode( SCSITaskMode newTaskMode );
	SCSITaskMode		GetTaskExecutionMode( void );

	bool				IsAutosenseRequested( void );

	// This method is used only by the SCSI Protocol Layer to set the
	// state of the auto sense data when the REQUEST SENSE command is
	// explicitly sent to the device.	
	bool				SetAutosenseIsValid( bool newAutosenseState );
	
	UInt8				GetAutosenseCommandDescriptorBlockSize( void );

	bool				GetAutosenseCommandDescriptorBlock( 
        					SCSICommandDescriptorBlock * cdbData);
	
	UInt8				GetAutosenseDataTransferDirection( void );
        					
	UInt64				GetAutosenseRequestedDataTransferCount( void );

	bool				SetAutosenseRealizedDataCount( 
							UInt64 realizedTransferCountInBytes );
	UInt64				GetAutosenseRealizedDataCount( void );
	
	IOMemoryDescriptor	*GetAutosenseDataBuffer( void );

	bool				SetAutosenseCommand(
							UInt8			cdbByte0,
							UInt8			cdbByte1,
							UInt8			cdbByte2,
							UInt8			cdbByte3,
							UInt8			cdbByte4,
							UInt8			cdbByte5 );
							
	// These are the methods used for adding and removing the SCSI Task object
	// to a queue.  These are mainly for use by the SCSI Protocol Layer, but can
	// be used by the SCSI Application Layer if the task is currently not active
	// (Not active meaing that the Task state is either kSCSITaskState_NEW_TASK
	// or kSCSITaskState_ENDED).
	
	// This method queues the specified Task after this one
	void	EnqueueFollowingSCSITask( SCSITask * followingTask );

	// Returns the pointer to the SCSI Task that is queued after
	// this one.  Returns NULL if one is not currently queued.
	SCSITask * GetFollowingSCSITask( void );

	// Returns the pointer to the SCSI Task that is queued after
	// this one and removes it from the queue.  Returns NULL if 
	// one is not currently queued.
	SCSITask * DequeueFollowingSCSITask( void );

	// Returns the pointer to the SCSI Task that is queued after
	// this one and removes it from the queue.  Returns NULL if 
	// one is not currently queued.  After dequeueing the following
	// Task, the specified newFollowingTask will be enqueued after this
	// task.
	SCSITask * ReplaceFollowingSCSITask( SCSITask * newFollowingTask );

private:
	// Space reserved for future expansion.
    OSMetaClassDeclareReservedUnused( SCSITask, 1 );
    OSMetaClassDeclareReservedUnused( SCSITask, 2 );
    OSMetaClassDeclareReservedUnused( SCSITask, 3 );
    OSMetaClassDeclareReservedUnused( SCSITask, 4 );
    OSMetaClassDeclareReservedUnused( SCSITask, 5 );
    OSMetaClassDeclareReservedUnused( SCSITask, 6 );
    OSMetaClassDeclareReservedUnused( SCSITask, 7 );
    OSMetaClassDeclareReservedUnused( SCSITask, 8 );

};

#endif	/* defined(KERNEL) && defined(__cplusplus) */

#endif /* _IOKIT_SCSI_TASK_H_ */