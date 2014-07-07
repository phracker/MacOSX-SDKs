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
#include <IOKit/scsi-commands/IOSCSIProtocolServices.h>

// Flag to turn debugging for the USB Mass Storage class on and off
#define USB_MASS_STORAGE_DEBUG	0

#pragma mark -
#pragma mark Vendor Specific Device Support
#define kIOUSBMassStorageCharacteristics	"USB Mass Storage Characteristics"
#define kIOUSBMassStoragePreferredSubclass	"Preferred Subclass"
#define kIOUSBMassStoragePreferredProtocol	"Preferred Protocol"

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

	// The manufacturer and product name strings that are retrieved from
	// the device's string descriptors.
	// Currently, the driver only supports English.  At a later time
	// support for other languages should be added and these should be
	// changed to support Unicode.    
  	//char						fManufacturerString[255];
  	//char						fProductString[255];
  	
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
		
 	// The Request block that contains all the necessary data for 
 	// transporting a Bulk Only request across the USB.
 	BulkOnlyRequestBlock		fBulkOnlyCommandRequestBlock;

protected:
    // Reserve space for future expansion.
    struct ExpansionData { };
    ExpansionData *				reserved;

	// Enumerated constants used to control various aspects of this
	// driver.
	enum
	{
		kUSBMaxBulkTransfer		= 0x200000	// Max transfer is 2MB
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
	inline IOUSBInterface *	GetInterfaceReference( void );
	inline void				SetInterfaceReference( IOUSBInterface * newInterface );
	
	inline UInt8			GetInterfaceSubclass( void );
	inline UInt8			GetInterfaceProtocol( void );
	
	// Methods for retrieving an object for a Pipe.
	inline IOUSBPipe *		GetControlPipe( void );
	inline IOUSBPipe *		GetBulkInPipe( void );
	inline IOUSBPipe *		GetBulkOutPipe( void );
	inline IOUSBPipe *		GetInterruptPipe( void );

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
		kCommandBlockWrapperSignature	= 'USBC',
		kByteCountOfCBW					= 31,

		// CBW LUN related definitions
		kCBWLUNMask						= 0x07,

		kCBWFlagsDataOut				= 0x00,
		kCBWFlagsDataIn					= 0x80
	};
	
	// All definitions and structures for the Bulk Only Protocol
	// Command Status Wrapper (CSW)
	enum
	{
		// CSW general struture definitions
		kCommandStatusWrapperSingature	= 'USBS',
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
	virtual	IOReturn	message( UInt32 type, IOService * provider, void * argument = 0 );

	virtual IOReturn	HandlePowerOn( void );

	// Space reserved for future expansion.
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 1 );
    OSMetaClassDeclareReservedUnused( IOUSBMassStorageClass, 2 );
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

#endif _IOKIT_IOUSBMASSSTORAGECLASS_H