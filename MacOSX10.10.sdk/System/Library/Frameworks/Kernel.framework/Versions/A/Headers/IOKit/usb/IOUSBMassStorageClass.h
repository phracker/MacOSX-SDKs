/*
 * Copyright (c) 1998-2014 Apple Inc. All rights reserved.
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
 

#ifndef _IOKIT_IOUSBMASSSTORAGECLASS_H
#define _IOKIT_IOUSBMASSSTORAGECLASS_H

// Headers for general IOKit definitions
#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>
#include <IOKit/IOMemoryDescriptor.h>
#include <IOKit/IOMessage.h>

// Headers for USB specific definitions
#include <IOKit/usb/IOUSBInterface.h>
#include <IOKit/usb/IOUSBPipe.h>
#include <IOKit/usb/USBSpec.h>
#include <IOKit/usb/USB.h>

// Headers for SCSI Protocol support definitions
#include <IOKit/scsi/IOSCSIProtocolServices.h>

// BSD includes
#include <sys/sysctl.h>

#define UNUSED(x) ((void)x)

#pragma mark -
#pragma mark Vendor Specific Device Support
#define kIOUSBMassStorageCharacteristics		"USB Mass Storage Characteristics"
#define kIOUSBMassStoragePreferredSubclass		"Preferred Subclass"
#define kIOUSBMassStoragePreferredProtocol		"Preferred Protocol"
#define kIOUSBMassStorageUseStandardUSBReset	"Use Standard USB Reset"
#define kIOUSBKnownCSWTagIssues					"Known CSW Tag Issues"
#define kIOUSBMassStorageMaxLogicalUnitNumber	"Max Logical Unit Number"
#define kIOPropertyIOUnitKey					"IOUnit"
#define kIOUSBMassStorageDoNotMatch				"Do Not Match MSC"
#define kIOUSBMassStorageDoNotOperate			"Do Not Operate"
#define kIOUSBMassStorageEnableSuspendResumePM	"Enable Port Suspend-Resume PM"
#define kIOUSBMassStoragePostResetCoolDown		"Reset Recovery Time"

#ifndef EMBEDDED
#define kIOUSBMassStorageSuspendOnReboot        "Suspend On Reboot"
#define kIOUSBMassStorageResetOnResume			"Reset On Resume"
#endif // EMBEDDED

enum 
{
	kUSBDAddressLength = 10
};

enum 
{
	kIOUSBMassStorageReconfigurationTimeoutMS = 5000
};


#pragma mark -
#pragma mark CBI Protocol Strutures
// Structure for the global PB's
struct CBIRequestBlock
{
	SCSITaskIdentifier			request;
	IOUSBDevRequest				cbiDevRequest;
	SCSICommandDescriptorBlock	cbiCDB;
	IOUSBCompletion				cbiCompletion;
	UInt32						currentState;
	IOMemoryDescriptor *		cbiPhaseDesc;
	UInt8						cbiGetStatusBuffer[2];	// 2 bytes as specified in the USB spec
};

typedef struct CBIRequestBlock	CBIRequestBlock;

#pragma mark -
#pragma mark Bulk Only Protocol Structures

struct StorageBulkOnlyCBW
{
	UInt32		cbwSignature;
	UInt32		cbwTag;
	UInt32		cbwTransferLength;
	UInt8		cbwFlags;
	UInt8		cbwLUN;					// Bits 0-3: LUN, 4-7: Reserved
	UInt8		cbwCDBLength;			// Bits 0-4: CDB Length, 5-7: Reserved
	UInt8		cbwCDB[16];
};

typedef struct StorageBulkOnlyCBW	StorageBulkOnlyCBW;

struct	StorageBulkOnlyCSW
{
	UInt32		cswSignature;
	UInt32		cswTag;
	UInt32		cswDataResidue;
	UInt8		cswStatus;
};

typedef struct StorageBulkOnlyCSW	StorageBulkOnlyCSW;

struct	BulkOnlyRequestBlock
{
	SCSITaskIdentifier		request;
	IOUSBCompletion			boCompletion;
	UInt32					currentState;
	StorageBulkOnlyCBW		boCBW;
	StorageBulkOnlyCSW		boCSW;
	IOMemoryDescriptor *	boPhaseDesc;
	UInt8					boGetStatusBuffer[2];	// 2 bytes as specified in the USB spec
};

typedef struct BulkOnlyRequestBlock		BulkOnlyRequestBlock;


#pragma mark -
#pragma mark IOUSBMassStorageClass definition

class IOUSBMassStorageClass : public IOSCSIProtocolServices
{
    OSDeclareDefaultStructors(IOUSBMassStorageClass)

private:
	// ---- Member variables used by all protocols ----
	// The interface object that provides the driver with access to the 
	// USB so that it may talk to its device.
    IOUSBInterface *			fInterface;

	// The pipe objects that the driver uses to transport data through a
	// pipe to the appropriate endpoint.
    IOUSBPipe *					fBulkInPipe;
    IOUSBPipe *					fBulkOutPipe;
    IOUSBPipe *					fInterruptPipe;
    
	IOUSBDevRequest				fUSBDeviceRequest;
	UInt8						fPreferredSubclass;
	UInt8						fPreferredProtocol;
	
  	// The maximum Logical Unit Number.  This is the highest valid LUN
  	// that the USB device supports, so if the device only supports one
  	// LUN, such as CBI and CB, this number will be zero.
  	UInt8						fMaxLogicalUnitNumber;

	// ---- Member variables used by CBI protocol ----
	bool						fCBICommandStructInUse; 

	CBIRequestBlock				fCBICommandRequestBlock;
    
	// ---- Member variables used by Bulk Only protocol ----
 	// Command tag, this driver just uses a sequential counter that is
 	// incremented for each CBW that is sent to the device.
 	UInt32 						fBulkOnlyCommandTag;

	bool						fBulkOnlyCommandStructInUse; 
    
    // Dedicated CBW and CSW IOMemoryDescriptors are listed in the ExpansionData struct.
		
 	// The Request block that contains all the necessary data for 
 	// transporting a Bulk Only request across the USB.
 	BulkOnlyRequestBlock		fBulkOnlyCommandRequestBlock;

protected:
    // Reserve space for future expansion.
    
    // We flatten the ExpansionData for iOS since we're relieved of the burden binary compatibility.
#ifndef EMBEDDED
    struct ExpansionData
	{
#endif // EMBEDDED
		bool					fResetInProgress;
		OSSet *					fClients;
		IOUSBPipe *				fPotentiallyStalledPipe;
		bool					fUseUSBResetNotBOReset;
		bool					fAbortCurrentSCSITaskInProgress;
		IOMemoryDescriptor *	fCBIMemoryDescriptor;
		IOMemoryDescriptor *	fBulkOnlyCBWMemoryDescriptor;
		IOMemoryDescriptor *	fBulkOnlyCSWMemoryDescriptor;
        bool                    fDeviceAttached;
		bool                    fWaitingForReconfigurationMessage;
		bool					fTerminating;
        bool                    fKnownCSWTagMismatchIssues;
        bool                    fPortSuspendResumeForPMEnabled;
        bool                    fPortIsSuspended;
#ifndef EMBEDDED
		bool					fRequiresResetOnResume;
		bool					fAutonomousSpinDownWorkAround;
#endif // EMBEDDED
		UInt8					fConsecutiveResetCount;
#ifndef EMBEDDED
		bool					fClearStallInProgress;				/* OBSOLETE */
#endif // EMBEDDED
		bool					fTerminationDeferred;
#ifndef EMBEDDED
		UInt32					fRequiredMaxBusStall;
#endif // EMBEDDED
		bool					fBlockOnResetThread;
#ifndef EMBEDDED
        UInt32					fPostDeviceResetCoolDownInterval;
		bool					fSuspendOnReboot;
#endif // EMBEDDED
		UInt8					fResetStatus;
        
#ifndef EMBEDDED
	};
    ExpansionData *				reserved;
#endif // EMBEDDED
	
#ifndef EMBEDDED
	#define fResetInProgress					reserved->fResetInProgress
	#define fClients							reserved->fClients
	#define fPotentiallyStalledPipe				reserved->fPotentiallyStalledPipe
    #define fUseUSBResetNotBOReset				reserved->fUseUSBResetNotBOReset
	#define fAbortCurrentSCSITaskInProgress		reserved->fAbortCurrentSCSITaskInProgress
    #define fCBIMemoryDescriptor                reserved->fCBIMemoryDescriptor
	#define	fBulkOnlyCBWMemoryDescriptor		reserved->fBulkOnlyCBWMemoryDescriptor
	#define	fBulkOnlyCSWMemoryDescriptor		reserved->fBulkOnlyCSWMemoryDescriptor
    #define fDeviceAttached                     reserved->fDeviceAttached
	#define fWaitingForReconfigurationMessage	reserved->fWaitingForReconfigurationMessage
	#define fTerminating						reserved->fTerminating
    #define fKnownCSWTagMismatchIssues          reserved->fKnownCSWTagMismatchIssues
    #define fPortSuspendResumeForPMEnabled      reserved->fPortSuspendResumeForPMEnabled
    #define fPortIsSuspended                    reserved->fPortIsSuspended
    #define fRequiresResetOnResume				reserved->fRequiresResetOnResume
    #define fAutonomousSpinDownWorkAround		reserved->fAutonomousSpinDownWorkAround
    #define fConsecutiveResetCount				reserved->fConsecutiveResetCount
    #define fClearStallInProgress				reserved->fClearStallInProgress
    #define fTerminationDeferred				reserved->fTerminationDeferred
    #define fRequiredMaxBusStall				reserved->fRequiredMaxBusStall
    #define fBlockOnResetThread					reserved->fBlockOnResetThread
    #define fPostDeviceResetCoolDownInterval	reserved->fPostDeviceResetCoolDownInterval
    #define fSuspendOnReboot					reserved->fSuspendOnReboot
    #define fResetStatus						reserved->fResetStatus	
#endif // EMBEDDED
    
	// Enumerated constants used to control various aspects of this
	// driver.

	// Enumerates the fResetStatus
	enum
	{
		kUSBResetStatusSuccess				= 0,
		kUSBResetStatusFailure				= 1
	};
	
	// Enumerations for Mass Storage Class Subclass types
	enum
	{
		kUSBStorageRBCSubclass 				= 1,
		kUSBStorageSFF8020iSubclass 		= 2,
		kUSBStorageQIC157Subclass			= 3,
		kUSBStorageUFISubclass				= 4,
		kUSBStorageSFF8070iSubclass			= 5,
		kUSBStorageSCSITransparentSubclass	= 6
	};

	// The supported USB Mass Storage Class transport protocols.
	enum
	{
		kProtocolControlBulkInterrupt	= 0x00,
		kProtocolControlBulk			= 0x01,
		kProtocolBulkOnly				= 0x50
	};

	// ------- Protocol support functions ------------
	// The SendSCSICommand function will take a SCSITask Object and transport
	// it across the physical wire(s) to the device
	virtual bool    		SendSCSICommand( 	
								SCSITaskIdentifier 		request, 
								SCSIServiceResponse *	serviceResponse,
								SCSITaskStatus		*	taskStatus );

	// The AbortSCSICommand function will abort the indicated SCSITask object,
	// if it is possible and the SCSITask has not already completed.
    virtual SCSIServiceResponse    	AbortSCSICommand( SCSITaskIdentifier abortTask );

	virtual bool					IsProtocolServiceSupported( 
										SCSIProtocolFeature 	feature, 
										void * 					serviceValue );

	virtual bool					HandleProtocolServiceFeature( 
										SCSIProtocolFeature 	feature, 
										void * 					serviceValue );
 
	// Methods for retrieving and setting the object for the Interface
	IOUSBInterface *		GetInterfaceReference( void );
	void					SetInterfaceReference( IOUSBInterface * newInterface );
	
	UInt8					GetInterfaceSubclass( void );
	UInt8					GetInterfaceProtocol( void );
	
	// Methods for retrieving an object for a Pipe.
	IOUSBPipe *				GetControlPipe( void );
	IOUSBPipe *				GetBulkInPipe( void );
	IOUSBPipe *				GetBulkOutPipe( void );
	IOUSBPipe *				GetInterruptPipe( void );
    
	// Methods for getting and setting the maximum LUN of a device.
	UInt8					GetMaxLogicalUnitNumber( void ) const;
	void					SetMaxLogicalUnitNumber( UInt8 maxLUN );
	
	virtual void 			CompleteSCSICommand( 
								SCSITaskIdentifier request, 
								IOReturn status );

	virtual	bool			BeginProvidedServices( void );
	virtual	bool			EndProvidedServices( void );
	
	// The Protocol specific helper methods for SendSCSICommand	
	virtual IOReturn		SendSCSICommandForCBIProtocol(
                                                          SCSITaskIdentifier request );
	
	virtual IOReturn		SendSCSICommandForBulkOnlyProtocol(
                                                               SCSITaskIdentifier request );
    
	// The Protocol specific helper methods for AbortSCSICommand	
	virtual IOReturn		AbortSCSICommandForCBIProtocol(
                                                           SCSITaskIdentifier abortTask );
	
	virtual IOReturn		AbortSCSICommandForBulkOnlyProtocol(
                                                                SCSITaskIdentifier abortTask );

	// Helper methods for performing general USB device requests
	virtual IOReturn		ClearFeatureEndpointStall( 
								IOUSBPipe *			thePipe,
								IOUSBCompletion	*	completion );
	virtual IOReturn 		GetStatusEndpointStatus(
								IOUSBPipe *			thePipe,
								void *				endpointStatus,
								IOUSBCompletion	*	completion );
	
 	/* All CBI transport related methods.
 	 */
	// All definitions and structures for the CBI Protocol
	enum
	{
 		kUSBStorageAutoStatusSize	= 2		// Per the USB CBI Protocol
 	};

 	// Methods for accessing Bulk Only specific member variables.
	CBIRequestBlock *		GetCBIRequestBlock( void );

	void 					ReleaseCBIRequestBlock( 
								CBIRequestBlock *	cbiRequestBlock );

	// Methods used for CBI/CB command transportation.
	static void		CBIProtocolUSBCompletionAction(
						void *					target,
		                void *					parameter,
		                IOReturn				status,
		                UInt32					bufferSizeRemaining);

	IOReturn		CBIProtocolTransferData( 
						CBIRequestBlock *		cbiRequestBlock,
						UInt32					nextExecutionState );
		                
	IOReturn		CBIProtocolReadInterrupt( 
						CBIRequestBlock *		cbiRequestBlock,
						UInt32					nextExecutionState );

	IOReturn		CBIGetStatusEndpointStatus( 
						IOUSBPipe *				targetPipe,
						CBIRequestBlock *		cbiRequestBlock,
						UInt32					nextExecutionState );

	IOReturn		CBIClearFeatureEndpointStall( 
						IOUSBPipe *				targetPipe,
						CBIRequestBlock *		cbiRequestBlock,
						UInt32					nextExecutionState );
						
	void 			CBIProtocolCommandCompletion(
						CBIRequestBlock *		cbiRequestBlock,
		                IOReturn				resultingStatus,
		                UInt32					bufferSizeRemaining );
		                
 	/* All Bulk Only transport related methods, structures and enums.
 	 */
 	// All Bulk Only specific structures and enums.
	
	// All definitions and structures for the Bulk Only Protocol
	// Command Block Wrapper (CBW)
	enum
	{
		// CBW general struture definitions
		kCommandBlockWrapperSignature	= OSSwapHostToBigConstInt32 ( 'USBC' ),
		kByteCountOfCBW					= 31,

		// CBW LUN related definitions
		kCBWLUNMask						= 0x0F,

		kCBWFlagsDataOut				= 0x00,
		kCBWFlagsDataIn					= 0x80
	};
	
	// All definitions and structures for the Bulk Only Protocol
	// Command Status Wrapper (CSW)
	enum
	{
		// CSW general struture definitions
		kCommandStatusWrapperSignature	= OSSwapHostToBigConstInt32 ( 'USBS' ),
		kByteCountOfCSW					= 13,

		// CSW status definitions
		kCSWCommandPassedError 			= 0x00,	// No error occurred
		kCSWCommandFailedError			= 0x01,	/* An error occurred (probably a 
											 	 * bad command or parameter ) */
		kCSWPhaseError					= 0x02	/* A transfer was performed in 
											 	 * the wrong sequence */
	};

 	// Methods for accessing Bulk Only specific member variables.
	BulkOnlyRequestBlock *	GetBulkOnlyRequestBlock( void );

	void 			ReleaseBulkOnlyRequestBlock( 
						BulkOnlyRequestBlock * 		boRequestBlock );

	UInt32			GetNextBulkOnlyCommandTag( void );

	// Methods for Bulk Only specific utility commands
	IOReturn		BulkDeviceResetDevice(
						BulkOnlyRequestBlock *		boRequestBlock,
						UInt32						nextExecutionState );
						
	// Methods used for Bulk Only command transportation.
	IOReturn		BulkOnlySendCBWPacket(
						BulkOnlyRequestBlock *		boRequestBlock,
						UInt32						nextExecutionState );
	
	IOReturn		BulkOnlyTransferData( 
						BulkOnlyRequestBlock *		boRequestBlock,
						UInt32						nextExecutionState );
	
	IOReturn		BulkOnlyReceiveCSWPacket(
						BulkOnlyRequestBlock *		boRequestBlock,
						UInt32						nextExecutionState );
	
	void			BulkOnlyExecuteCommandCompletion (
						BulkOnlyRequestBlock *		boRequestBlock,
		                IOReturn					resultingStatus,
		                UInt32						bufferSizeRemaining );

	static void		BulkOnlyUSBCompletionAction (
		                void *			target,
		                void *			parameter,
		                IOReturn		status,
		                UInt32			bufferSizeRemaining );
	
public:

    bool				init( OSDictionary * 	propTable );
    virtual bool		start( IOService *	 	provider );
    virtual void 		stop( IOService * 		provider );
	virtual void		free( void );
	virtual	IOReturn	message( UInt32 type, IOService * provider, void * argument = 0 );
	
	virtual bool        willTerminate(  IOService *     provider, 
                                        IOOptionBits    options );
										
	virtual bool        didTerminate(	IOService *     provider, 
                                        IOOptionBits    options, 
										bool *			defer );
                                        
	virtual bool		handleOpen( IOService *		client,
									IOOptionBits	options,
									void *			arg );
	
	virtual void		handleClose( IOService *	client,
									 IOOptionBits	options );
	
	virtual bool		handleIsOpen(  const IOService * client ) const;
	
	virtual IOReturn	HandlePowerOn( void );
	
#ifndef EMBEDDED
	virtual void		systemWillShutdown ( IOOptionBits specifier );
#endif // EMBEDDED
	
protected:

	static IOReturn		sWaitForReset( void * refcon );
	IOReturn			GatedWaitForReset( void );
	
#ifndef EMBEDDED
	static IOReturn		sWaitForTaskAbort( void * refcon );			/* OBSOLETE */
	IOReturn			GatedWaitForTaskAbort( void );				/* OBSOLETE */
#endif // EMBEDDED
    
	static void			sResetDevice( void * refcon );

#ifndef EMBEDDED
	static void			sAbortCurrentSCSITask( void * refcon );		/* OBSOLETE */
	
    OSMetaClassDeclareReservedUsed( IOUSBMassStorageClass, 1 );
	virtual IOReturn	StartDeviceRecovery( void );				/* OBSOLETE */

    OSMetaClassDeclareReservedUsed( IOUSBMassStorageClass, 2 );
	virtual void		FinishDeviceRecovery( IOReturn	status );	/* OBSOLETE */

	static void			DeviceRecoveryCompletionAction(
		                	void *			target,
		                	void *			parameter,
		                	IOReturn		status,
		                	UInt32			bufferSizeRemaining );	/* OBSOLETE */
#endif // EMBEDDED
    
	IOReturn       ResetDeviceNow( bool waitForReset );
	
	void                AbortCurrentSCSITask( void );
	
	bool                IsPhysicalInterconnectLocationInternal ( void );
	    
	IOReturn            SuspendPort ( bool suspend );
	
private:
	
	void				ClearPipeStall ( void );
	
	IOReturn			AcceptSCSITask ( SCSITaskIdentifier scsiTask, bool * pAccepted );
	
	void				CheckDeferredTermination ( void );
	
	void				GatedCompleteSCSICommand ( SCSITaskIdentifier request, SCSIServiceResponse * serviceResponse, SCSITaskStatus * taskStatus );
	
	// Space reserved for future expansion.
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 3 );
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 4 );
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 5 );
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 6 );
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 7 );
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 8 );
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 9 );
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 10 );
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 11 );
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 12 );
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 13 );
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 14 );
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 15 );
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 16 );
	
};


#endif //_IOKIT_IOUSBMASSSTORAGECLASS_H
