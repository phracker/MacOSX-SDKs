/*
 * Copyright (c) 2000-2001 Apple Computer, Inc. All rights reserved.
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
 * Copyright (c) 2000 Apple Computer, Inc.  All rights reserved.
 *
 * HISTORY
 *
 *		06.07.2001	CJS		Merged SCSI Parallel Interface Protocol Transport into
 *							IOSCSIFamily.
 *		12.21.2000	CJS 	Started SCSI Parallel Interface Transport Layer
 *
 */

#ifndef _IO_SCSI_PARALLEL_INTERFACE_PROTOCOL_TRANSPORT_H_
#define _IO_SCSI_PARALLEL_INTERFACE_PROTOCOL_TRANSPORT_H_


/* General IOKit includes */
#include <IOKit/IOLib.h>
#include <IOKit/IOMessage.h>
#include <IOKit/IOService.h>
#include <IOKit/IOCommandPool.h>

/* SCSI includes */
#include <IOKit/scsi/IOSCSIDeviceInterface.h>

/* SCSI Architecture Model Family includes */
#include <IOKit/scsi-commands/IOSCSIProtocolServices.h>

// Forward class declaration
class IOSCSIParallelInterfaceProtocolTransport;

struct SCSIClientData
{
    IOSCSICommand *								cmd;
    SCSITaskIdentifier							scsiTask;
    SCSISenseData								senseBytes;
    IOMemoryDescriptor *						senseBuffer;
};
typedef struct SCSIClientData SCSIClientData;


class IOSCSIParallelInterfaceProtocolTransport : public IOSCSIProtocolServices
{
	
	OSDeclareDefaultStructors ( IOSCSIParallelInterfaceProtocolTransport )
	
public:
	
	virtual IOService *		probe	( IOService *  provider, SInt32 * score );	
	virtual bool 			start 	( IOService * provider );
	virtual void 			stop 	( IOService *  provider );
	
	
protected:
	
	IOSCSIDevice *			fSCSIDevice;
	IOCommandGate *			fCommandGate;
	IOCommandPool *			fCommandPool;
	bool					fBusResetInProgress;
	
	virtual IOReturn message ( UInt32 type, IOService * provider, void * argument = 0 );
	
	// return false when we are busy and command can't be taken
	virtual bool SendSCSICommand ( 	SCSITaskIdentifier request,
									SCSIServiceResponse * serviceResponse,
									SCSITaskStatus * taskStatus );
	
	// fired off to notify command completed
	virtual void CompleteSCSITask ( SCSITaskIdentifier scsiTask,
									SCSIServiceResponse serviceResponse,
									SCSITaskStatus taskStatus );
	
	// this is a stub - not implemented in upper layer yet
	virtual SCSIServiceResponse AbortSCSICommand ( SCSITaskIdentifier request );
	
	virtual bool IsProtocolServiceSupported ( SCSIProtocolFeature feature,
											  void * serviceValue );

	virtual bool HandleProtocolServiceFeature ( SCSIProtocolFeature feature, 
												void * serviceValue );
	
	// This is the callback that subclasses can override.
	virtual void SCSICallbackFunction ( IOSCSICommand * cmd, SCSIClientData * clientData );
	
	virtual bool	InspectDevice ( IOSCSIDevice * scsiDevice );
	
private:
	
	static void 		sSCSICallbackProc ( void * target, void * refCon );
	
	void 				AllocateSCSICommandObjects ( void );
	void 				DeallocateSCSICommandObjects ( void );
	IOSCSICommand *		GetSCSICommandObject	( bool okToSleep = true );
	void				ReturnSCSICommandObject	( IOSCSICommand * cmd );
	
};


#endif	/* _IO_SCSI_PARALLEL_INTERFACE_PROTOCOL_TRANSPORT_H_ */