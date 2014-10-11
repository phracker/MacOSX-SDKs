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

#ifndef _IOKIT_IO_SCSI_PROTOCOL_SERVICES_H_
#define _IOKIT_IO_SCSI_PROTOCOL_SERVICES_H_

#if defined(KERNEL) && defined(__cplusplus)

#include <IOKit/IOLib.h>
#include <IOKit/IOCommandGate.h>

#include <IOKit/scsi-commands/IOSCSIProtocolInterface.h>

// Power Management values
enum
{
	kSCSIProtocolLayerPowerStateOff				= 0,
	kSCSIProtocolLayerPowerStateOn				= 1,
	kSCSIProtocolLayerNumDefaultStates			= 2
};

class IOSCSIProtocolServices : public IOSCSIProtocolInterface
{
	
	OSDeclareAbstractStructors ( IOSCSIProtocolServices )
	
private:
	
	// The head pointer for the queue of waiting SCSI Tasks.
	SCSITask *		fSCSITaskQueueHead;
	
	// This is the lock for preventing multiple access while
	// manipulating the SCSI Task queue.
	IOSimpleLock *	fQueueLock;
	
	// The internal flag to indicate whether service requests should be
	// executed or immediately errored, such as when a device is removed.
	bool			fAllowServiceRequests;
	
protected:

    // Reserve space for future expansion.
    struct IOSCSIProtocolServicesExpansionData { };
    IOSCSIProtocolServicesExpansionData *fIOSCSIProtocolServicesReserved;
	
	// ---- Protocol transport methods overridden by each subclass ----
	
	// Send a SCSI Command to the device.  If the command was sent to the
	// device and is pending completion, the subclass should return true and
	// return back the kSCSIServiceResponse_Request_In_Process response. 
	// If the command completes immediately with an error, the subclass will
	// return true and return back the appropriate status.
	// if the subclass is currently processing all the commands it can, the
	// subclass will return false and the command will be resent next time
	// CommandCompleted is called.  
	virtual bool		SendSCSICommand ( 	SCSITaskIdentifier 		request, 
											SCSIServiceResponse *	serviceResponse,
											SCSITaskStatus *		taskStatus ) = 0;
	
	virtual SCSIServiceResponse	AbortSCSICommand ( SCSITaskIdentifier request ) = 0;
	
	// ---- Command completion notification method ---------
	// Subclasses will call this inherited method when the command
	// executed by SendSCSICommand has completed.
	// The subclasses will return a service response that is derived
	// from protocol specific status information and as specified in 
	// the specification for that protocol.
	// If the service response is kSCSIServiceResponse_TASK_COMPLETE,
	// the subclass will also return a SCSI status value.
	void	CommandCompleted ( 	SCSITaskIdentifier 	request, 
								SCSIServiceResponse serviceResponse,
								SCSITaskStatus		taskStatus );
	
	// ---- Utility methods for accessing SCSITask attributes ----
	// Method for retreiving the attribute for a task.
	SCSITaskAttribute	GetTaskAttribute ( SCSITaskIdentifier request );
	
	bool			SetTaskState ( 	SCSITaskIdentifier request, 
									SCSITaskState newTaskState );
	SCSITaskState	GetTaskState ( 	SCSITaskIdentifier request );
	
	UInt8			GetLogicalUnitNumber( SCSITaskIdentifier request );

	// Method to determine the size of the command descriptor block.
	UInt8	GetCommandDescriptorBlockSize ( SCSITaskIdentifier request );
	
	// This will always return the define max CDB size.  If the Protocol Layer
	// driver only supports a smaller size CDB, it will have to create a local
	// SCSICommandDescriptorBlock variable to get the CDB data and then 
	// transfer the needed bytes from there.
	bool	GetCommandDescriptorBlock ( SCSITaskIdentifier 				request, 
										SCSICommandDescriptorBlock * 	cdbData );
	
	// Get the transfer direction for the request.
	UInt8	GetDataTransferDirection ( SCSITaskIdentifier request );
	
	UInt64	GetRequestedDataTransferCount ( SCSITaskIdentifier request );
	
	bool	SetRealizedDataTransferCount ( SCSITaskIdentifier request,
										   UInt64 newRealizedDataCount );
	
	UInt64	GetRealizedDataTransferCount ( SCSITaskIdentifier request );
	
	IOMemoryDescriptor *	GetDataBuffer ( SCSITaskIdentifier request );
	
	UInt64	GetDataBufferOffset ( SCSITaskIdentifier request );

	UInt32	GetTimeoutDuration ( SCSITaskIdentifier request );
	
	// Set the auto sense data that was returned for the SCSI Task.
	// A return value of true indicates that the data was copied to the member 
	// sense data structure, false indicates that the data could not be copied.
	bool	SetAutoSenseData ( SCSITaskIdentifier request, SCSI_Sense_Data * senseData );
	
	bool	SetProtocolLayerReference ( 
				SCSITaskIdentifier 		request, 
				void *					newReferenceValue );
	void *	GetProtocolLayerReference ( SCSITaskIdentifier request );
	
	
	bool	SetTaskExecutionMode (
				SCSITaskIdentifier 		request, 
				SCSITaskMode 			newTaskMode );
	SCSITaskMode	GetTaskExecutionMode ( SCSITaskIdentifier request );
	
	// ---- Method calls for messaging device connectedness ----
	void 	SendNotification_DeviceRemoved ( void );
	
	void 	SendNotification_VerifyDeviceState ( void );   
	
	// -- SCSI Task Queue Management Methods --
	// Following are the commands used to manipulate the queue of pending SCSI Tasks.
	
	// Add the SCSI Task to the queue.  The Task's Attribute determines where in
	// the queue the Task is placed.
	void 	AddSCSITaskToQueue ( SCSITaskIdentifier request );
	
	// Add the SCSI Task to the head of the queue.  This is used when the task
	// has been removed from the head of the queue, but the subclass indicates
	// that it can not yet process this task.
	void 	AddSCSITaskToHeadOfQueue ( SCSITask * request );
	
	// Remove the next SCSI Task for the queue and return it.
	SCSITask * RetrieveNextSCSITaskFromQueue ( void );
	
	// Check to see if the SCSI Task resides in the queue and abort it if it does.
	bool 	AbortSCSITaskFromQueue ( SCSITask * request );
	
	// Methods for sending and completing SCSI tasks
	void	SendSCSITasksFromQueue ( void );
	
	void	RejectSCSITasksCurrentlyQueued ( void );
	
	void	ProcessCompletedTask ( 	SCSITaskIdentifier 	request, 
									SCSIServiceResponse serviceResponse,
									SCSITaskStatus		taskStatus );
	void	RejectTask ( SCSITaskIdentifier 	request );
	
	// ------ Power Management Support ------
	
	// The InitializePowerManagement method is called to initialize power management.
	// In the protocol services layer, this method calls the protocol interface layer
	// to initialize power management state variables and then registers the protocol
	// layer driver with the power manager with two(2) states, ON and OFF.	
	virtual void		InitializePowerManagement ( IOService * provider );

	// The GetInitialPowerState method is called once, right after InitializePowerManagement()
	// in order to determine what state the device is initially in at startup time (usually
	// the highest power mode).
	virtual UInt32		GetInitialPowerState ( void );
	
	// The HandlePowerChange method is pure virtual and is left to each protocol or
	// application layer driver to implement. It is guaranteed to be called on its
	// own thread of execution and can make synchronous or asynchronous calls.
	virtual void		HandlePowerChange ( void );
	
	// The HandleCheckPowerState (void) method is on the serialized side of the command
	// gate and can change member variables safely without multi-threading issues.
	// It's main purpose is to call the superclass' HandleCheckPowerState ( UInt32 maxPowerState )
	// with the max power state the class registered with.
	virtual void		HandleCheckPowerState ( void );
	
	// The TicklePowerManager ( void ) method is called by CheckPowerState and
	// sends an activity tickle to the power manager so that the idle timer is
	// reset.
	virtual void		TicklePowerManager ( void );
	
	// The HandlePowerOff method is called to do any bus specific activity
	// necessary before shutting down and going to sleep.
	virtual IOReturn	HandlePowerOff ( void );
	
	// The HandlePowerOn method is called to do any bus specific activity
	// necessary to recover from power-on/wake from sleep (e.g. bus reset on ATAPI)
	virtual IOReturn	HandlePowerOn ( void );
	
public:
	
	bool			init	( OSDictionary * propTable );
	virtual bool	start	( IOService * provider );
	virtual void	stop	( IOService *  provider );
	
	// -- The SCSI Protocol Interface methods	--
	// The ExecuteCommand method will take a SCSI Task and transport
	// it across the physical wire(s) to the device
	virtual void	ExecuteCommand ( SCSITaskIdentifier	request );
	
	// The AbortCommand method will abort the indicated SCSI Task,
	// if it is possible and the task has not already completed.
	virtual SCSIServiceResponse		AbortCommand ( SCSITaskIdentifier	request );
	
	// ---- Method used for determining protocol or physical interconnect characteristics. ----
	// The IsProtocolServiceSupported will return true if the specified
	// feature is supported by the protocol layer.  If the service has a value that must be
	// returned, it will be returned in the serviceValue output parameter.
	virtual bool	IsProtocolServiceSupported( SCSIProtocolFeature feature, void * serviceValue ) = 0;

	// The HandleProtocolServiceFeature instructs the Protocol Services driver to perform the necessary 
	// tasks for the indicated p
	virtual bool	HandleProtocolServiceFeature( SCSIProtocolFeature feature, void * serviceValue ) = 0;
	
private:
	// Space reserved for future expansion.
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 1 );
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 2 );
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 3 );
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 4 );
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 5 );
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 6 );
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 7 );
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 8 );
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 9 );
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 10 );
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 11 );
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 12 );
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 13 );
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 14 );
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 15 );
    OSMetaClassDeclareReservedUnused( IOSCSIProtocolServices, 16 );
};

#endif	/* defined(KERNEL) && defined(__cplusplus) */

#endif	/* _IOKIT_IO_SCSI_PROTOCOL_SERVICES_H_ */