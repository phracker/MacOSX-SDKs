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


#ifndef _IOKIT_SCSI_TASK_H_
#define _IOKIT_SCSI_TASK_H_

#if KERNEL
#include <IOKit/IOTypes.h>
#else
#include <CoreFoundation/CoreFoundation.h>
#endif


//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Constants used inside the kernel and user space
//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ

// The usage of these should be as follows:
// - if the identifier can either be that of an initiator or a target,
//	SCSIDeviceIdentifier should be used.
// - if the identifier is for a target only and not an initiator, then
// 	SCSITargetIdentifier should be used.
// - if the identifier is for an initiator only and not a target, then
//	SCSIInitiatorIdentifier should be used.

typedef UInt64 					SCSIDeviceIdentifier;
typedef SCSIDeviceIdentifier 	SCSITargetIdentifier;
typedef SCSIDeviceIdentifier 	SCSIInitiatorIdentifier;

typedef UInt64 					SCSILogicalUnitNumber;


/* Tagged Task Identifier
 * The Tagged Task Identifier is used when a Task has a Task Attribute other
 * than SIMPLE.  The SCSI Application Layer client that controls the Logical
 * Unit for which a Task is intended is required to guarantee that the Task
 * Tag Identifier is unique.  Zero cannot be used a a Tag value as this is used
 * to when a Tagged Task Identifier value is needed for a Task with a SIMPLE 
 * attribute.
 */ 
typedef UInt64 SCSITaggedTaskIdentifier;

/* Untagged Task Identifier
 * The Untagged Task Identifier is used when asked a Tag value is required for
 * a Task with a simple attribute.
 */
enum
{
	kSCSIUntaggedTaskIdentifier = 0
};

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

/* Service Response
 * The Service Response represents the execution status of a service request
 * made to a Protocol Services Driver.  
 
 * The Service Response can only be modified by the SCSI Protocol Layer.  The 
 * SCSI Application Layer can only read the state.
 */ 
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


/* Task Status Constants
 * The Task Status represents the completion status of the task. Only when a 
 * task completes with a service response of either TASK_COMPLETED or 
 * LINK_COMMAND_COMPLETE, will the status be considered valid.
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


//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Includes
//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ

// Libkern includes
#include <libkern/c++/OSObject.h>

// Generic IOKit related headers
#include <IOKit/IOCommand.h>
#include <IOKit/IOReturn.h>
#include <IOKit/IOMemoryDescriptor.h>

// SCSI Architecture Model Family includes
#include <IOKit/scsi-commands/SCSICmds_REQUEST_SENSE_Defs.h>


//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Constants used inside the kernel only
//ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ

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

#endif	/* defined(KERNEL) && defined(__cplusplus) */

#endif /* _IOKIT_SCSI_TASK_H_ */