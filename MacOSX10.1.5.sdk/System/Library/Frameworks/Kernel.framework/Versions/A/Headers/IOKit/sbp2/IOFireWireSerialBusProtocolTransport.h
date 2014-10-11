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

#ifndef _OPEN_SOURCE_

/*
 * Copyright (c) 2000 Apple Computer, Inc.  All rights reserved.
 *
 * HISTORY
 *
 *		2001.08.14	CM	header doc'ed
 *		2001.08.13	CM	added binary compatibility padding
 *		2001.02.05	CM	migrated to latest SAM changes
 *		2001.01.27	CM	migrated to tim's latest SAM changes
 *		2001.01.27	CM	migrated to collin's latest SBP-2 changes
 *		2001.01.19	CM	removed handleOpen handleClose methods
 *		2001.01.17	CM	cleaned up some lint
 *		2001.01.16	CM	turned off hot plugging hack 
 *		2001.01.07	CM	adapted new CommandCompleted APIs 
 *		2001.01.04	CM	added SetCommandBuffers for subclassing 
 *		2000.10.26	CM	made changes to sync up with SBP-2 API changes
 *		2000.10.15	CM	complete rewrite
 *		2000.08.18	CM	added support to set busy timeout register
 *		2000.07.14	CM	added more error handling support
 *		2000.07.13	CM	clean up and fixed header dependencies
 *		2000.07.10	CM	second pass rewrite
 *		2000.06.15	CM	started FireWire Mass Storage Transport
 *
 */

#endif

/*!
  @header IOFireWireSerialBusProtocolTransport
  Contains the class definition for IOFireWireSerialBusProtocolTransport.
*/

#ifndef _IOFireWireSerialBusProtocolTransport_
#define _IOFireWireSerialBusProtocolTransport_

#include <IOKit/IOBufferMemoryDescriptor.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOMessage.h>
#include <IOKit/IOService.h>
#include <IOKit/IOSyncer.h>

#include <IOKit/firewire/IOFireWireUnit.h>
#include <IOKit/sbp2/IOFireWireSBP2LUN.h>

#include <IOKit/scsi-commands/IOSCSIProtocolServices.h>

/*!
    @class IOFireWireSerialBusProtocolTransport
    @abstract SCSI Protocol Driver Family for FireWire SBP2 Devices. 
    @discussion IOFireWireSerialBusProtocolTransport contains all the bus specific support for FireWire
	SBP2 compliant devices. To add vendor specific features or workarounds you will sub-class the appropriate
	methods of this family. 
*/

class IOFireWireSerialBusProtocolTransport : public IOSCSIProtocolServices
{
	OSDeclareDefaultStructors(IOFireWireSerialBusProtocolTransport)

private:

	IOFireWireUnit *fUnit;
	IOFireWireSBP2LUN *fSBPTarget;
	IOFireWireSBP2Login *fLogin;
	IOFireWireSBP2ORB *fORB;
	IOFireWireSBP2ManagementORB * fLUNResetORB;
    IOSimpleLock *fQueueLock;
	UInt32 fLoginRetryCount;
	bool fDeferRegisterService;
	bool fNeedLogin;
	bool fPhysicallyConnected;

	static void
	StatusNotifyStatic ( void * refCon, FWSBP2NotifyParamsPtr params );

	static void
	UnsolicitedStatusNotifyStatic (	void * refCon,
									FWSBP2NotifyParamsPtr params );

	static void
	LunResetCompleteStatic (	void * refCon,
								IOReturn status,
								IOFireWireSBP2ManagementORB *orb);

	static void
	FetchAgentResetCompleteStatic (	void *refcon,
									IOReturn status );

	virtual void
	FetchAgentResetComplete ( IOReturn status );

	static void
	LoginCompletionStatic ( void *refCon, FWSBP2LoginCompleteParams *params );

	static void
	LogoutCompletionStatic ( void *refCon, FWSBP2LogoutCompleteParams *params );

    /*!
		@function CoalesceSenseData
		@abstract CoalesceSenseData convert a SBP-2 status block into a SPC-2 sense block.
		@discussion	CoalesceSenseData pulls the appropriate bits out of the SBP2 sense block
		as defined in SBP-2 Annex B section B.2 and dynamically builds a sense data block as
		defined in SPC-2 section 7.23.2.
	*/
	
	SCSITaskStatus
	CoalesceSenseData (	FWSBP2StatusBlock *sourceData,
						UInt8 quadletCount,
						SCSI_Sense_Data *targetData );

	virtual void 
	ConnectToDevice ( void );

	virtual void
	DisconnectFromDevice ( void );

	virtual bool
	IsDeviceCPUInDiskMode ( void );

	virtual IOReturn
	AllocateResources ( void );

	virtual void
	DeallocateResources ( void );

protected:

	/*! 
		@typedef SBP2ClientOrbData
		@param orb IOFireWireSBP2ORB for request.
		@param scsiTask SCSITaskIdentifier of request. 
		@param serviceResponse SCSIServiceResponse of request.
		@param taskStatus SCSITaskStatus of request.
		@discussion This structure is stuffed into the refcon so we can associate which
		IOFireWireSBP2ORB and SCSITaskIdentifier is completing.
	*/

	typedef struct {
		IOFireWireSBP2ORB *orb;
		SCSITaskIdentifier scsiTask;
		SCSIServiceResponse serviceResponse;
		SCSITaskStatus taskStatus;
	} SBP2ClientOrbData;
	
    static const UInt32 kDefaultBusyTimeoutValue = 0x0000000F;
	static const UInt64 kMaxFireWireLUN = 0xFFFF;
	static const UInt32 kMaxFireWirePayload = 2048;
	static const UInt32 kMaxLoginRetryCount = 8;
	static const UInt32 kMaxReconnectCount = 128;
	static const UInt32 kCSRModelInfoKey = 0x17;

	UInt32 fReconnectCount;
	bool fLoggedIn;
	
    // binary compatibility instance variable expansion
    struct ExpansionData { };
    ExpansionData *reserved;
	
	bool fObjectIsOpen;

    /*!
		@function CommandORBAccessor
		@abstract accessor function for fORB.
		@discussion	xxx.
	*/

	IOFireWireSBP2ORB * CommandORBAccessor ( void );
   
	/*!
		@function SBP2LoginAccessor
		@abstract accessor function for fLogin.
		@discussion	xxx.
	*/

	IOFireWireSBP2Login * SBP2LoginAccessor ( void );

	virtual IOReturn
	message ( UInt32 type, IOService * provider, void * argument = 0 );

    /*!
		@function SendSCSICommand
		@abstract Prepare and send a SCSI command to the device.
		@discussion	The incoming SCSITaskIdentifier gets turned into a IOFireWireSBP2ORB
		and is submitted to the SBP2 layer. See IOSCSIProtocolServices.h for more details
		regarding SendSCSICommand. Also see IOFireWireSBP2Lib.h for details regarding the
		IOFireWireSBP2ORB structure and the submitORB method.
		@result If the command was sent to the device and is pending completion, the
		subclass should return true and return back the kSCSIServiceResponse_Request_In_Process response.
		If the command completes immediately with an error, the subclass will return true
		and return back the appropriate status. If the subclass is currently processing all the
		commands it can, the subclass will return false and the command will be resent next time
		CommandCompleted is called.
	*/

	virtual bool 
	SendSCSICommand (	SCSITaskIdentifier request,
						SCSIServiceResponse *serviceResponse,
						SCSITaskStatus *taskStatus );

    /*!
		@function SetCommandBuffers
		@abstract Method to set orb's buffers.
		@discussion	This method was added so that subclasses can override and massage buffers as
		needed. The default simply calls setCommandBuffers. See IOFireWireSBP2Lib.h for details
		regarding the setCommandBuffers method.
		@result xxx.
	*/
	
	virtual IOReturn
	SetCommandBuffers (	IOFireWireSBP2ORB *orb, SCSITaskIdentifier request );

    /*!
		@function CompleteSCSITask
		@abstract This qualifies and sets appropriate data then calls CommandCompleted.
		@discussion	See IOSCSIProtocolServices.h for more details
		regarding CommandCompleted.
	*/
	
	virtual void 
	CompleteSCSITask ( IOFireWireSBP2ORB *orb );

    /*!
		@function AbortSCSICommand
		@abstract This method is intended to abort an in progress SCSI Task.
		@discussion	Currently not implemented in super class. This is a stub method for adding
		the abort command in the near future.
		@result See SCSITask.h for SCSIServiceResponse codes.
	*/
	
	virtual SCSIServiceResponse 
	AbortSCSICommand ( SCSITaskIdentifier request );

    /*!
		@function StatusNotify
		@abstract This is our handler for status.
		@discussion See IOFireWireSBP2Lib.h for details regarding the FWSBP2NotifyParams
		structure that is passed in to the completion..
	*/
	
	virtual void
	StatusNotify ( FWSBP2NotifyParams *params );

    /*!
		@function SetValidAutoSenseData
		@abstract Set the auto sense data that was returned for a given SCSI Task.
		@discussion	SetValidAutoSenseData is called to qualify sense data that is copied to the
		client via the SetAutoSenseData method. See IOSCSIProtocolServices.h for more details
		regarding SetAutoSenseData.
	*/
	
	void
	SetValidAutoSenseData (	SBP2ClientOrbData *clientData,
							FWSBP2StatusBlock *statusBlock,
							SCSI_Sense_Data *targetData );
	
    /*!
		@function UnsolicitedStatusNotify
		@abstract This is our handler for unsolicited status.
		@discussion	After we have parsed and handled the unsolicited status we call 
		enableUnsolicitedStatus. See IOFireWireSBP2Lib.h for details regarding the
		enableUnsolicitedStatus method.
	*/
	
	virtual void
	UnsolicitedStatusNotify ( FWSBP2NotifyParamsPtr params );

    /*!
		@function LoginCompletion
		@abstract Completion routine for login complete.
		@discussion	See IOFireWireSBP2Lib.h for details regarding the FWSBP2LogoutCompleteParams
		structure that is passed in to the completion.
	*/
	
	virtual void 
	LoginCompletion ( FWSBP2LoginCompleteParams *params );

    /*!
		@function LogoutCompletion
		@abstract Completion routine for logout complete.
		@discussion	See IOFireWireSBP2Lib.h for details regarding the FWSBP2LogoutCompleteParams
		structure that is passed in to the completion.
	*/
	
	virtual void 
	LogoutCompletion ( FWSBP2LogoutCompleteParams *params );

    /*!
		@function IsProtocolServiceSupported
		@abstract Determine is specified feature is supported by the protocol layer.
		@discussion	If the service has a value that must be returned, it will be returned in the
		serviceValue output parameter. See IOSCSIProtocolServices.h for more details regarding
		IsProtocolServiceSupported.
		@result Will return true if the specified feature is supported by the protocol layer.
	*/

	virtual bool
    IsProtocolServiceSupported ( SCSIProtocolFeature feature, void *serviceValue );

    /*!
		@function HandleProtocolServiceFeature
		@abstract Handle specified feature supported by the protocol layer.
		@discussion	See IOSCSIProtocolServices.h for more details regarding HandleProtocolServiceFeature.
		@result Will return true if the specified feature is supported by the protocol layer.
	*/

	virtual bool
	HandleProtocolServiceFeature( SCSIProtocolFeature feature, void *serviceValue );
   
    /*!
		@function LunResetComplete
		@abstract Callback to submit Fetch Agent Reset.
		@discussion	See IOFireWireSBP2Lib.h for details regarding the submitFetchAgentReset
		method.
	*/
	
	virtual void
	LunResetComplete ( IOReturn status, IOFireWireSBP2ManagementORB * orb);

public:

    /*!
		@function init
		@abstract See IOService for discussion.
		@discussion	Setup and prime class into known state.
	*/
	
	bool init ( OSDictionary * propTable );

	/*! 
		@function start
		@abstract During an IOService instantiation, the start method is called when the
		IOService has been selected to run on the provider.
		@discussion See IOService for discussion.
		@result Return true if the start was successful, false otherwise ( which will
		cause the instance to be detached and usually freed ).
	*/

	virtual bool start ( IOService * provider );

    /*!
	 *	@function cleanUp
		@abstract cleanUp is called to tear down IOFireWireSerialBusProtocolTransport.
		@discussion	cleanUp is called when we receive a kIOFWMessageServiceIsRequestingClose
		message or if we fail our initialization.
	*/
	
	virtual void cleanUp ( );

private:
	
	// binary compatibility reserved method space
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 1 );
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 2 );
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 3 );
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 4 );
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 5 );
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 6 );
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 7 );
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 8 );
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 9 );
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 10 );
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 11 );
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 12 );
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 13 );
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 14 );
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 15 );
    OSMetaClassDeclareReservedUnused ( IOFireWireSerialBusProtocolTransport, 16 );
	
};

#endif _IOFireWireSerialBusProtocolTransport_

//------------------------------------------------------------------------------