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

#ifndef _IOKIT_IOUSBROOTHUBDEVICE_H
#define _IOKIT_IOUSBROOTHUBDEVICE_H

#include <IOKit/usb/IOUSBDevice.h>
#include <IOKit/usb/IOUSBController.h>
#include <IOKit/usb/USBHub.h>

// this is a legacy name for a property that was available on some very old machines
#define kAppleCurrentAvailable	"AAPL,current-available"

typedef struct AppleRootHubExtraPowerRequest
{
	SInt32			requestedExtraPower;					// total "extra" power requested on my port - above and beyond the 500ms available on a root hub (negative to give it back)
	UInt32			extraPowerAvailable;					// total "extra" power available after returning from the call - should be zero on the call in
} AppleRootHubExtraPowerRequest;

class IOUSBRootHubDevice : public IOUSBDevice
{
    OSDeclareDefaultStructors(IOUSBRootHubDevice)

    UInt16 	configuration;

    struct ExpansionData { 
		IOCommandGate		*_commandGate;
	  };
    ExpansionData *_expansionData;

public:
	// static methods
    static IOUSBRootHubDevice *NewRootHubDevice(void);
    static IOReturn 		GatedDeviceRequest (OSObject *	owner, 
												void *		arg0, 
												void *		arg1, 
												void *		arg2, 
												void *		arg3 );
    
	// IOKit methods
    virtual bool		init();
	virtual bool		start( IOService * provider );
    virtual void		stop( IOService *provider );
    virtual void		free();
    virtual IOReturn 	message( UInt32 type, IOService * provider,  void * argument = 0 );
	
	// a non static but non-virtual function
	IOReturn DeviceRequestWorker(IOUSBDevRequest *request, UInt32 noDataTimeout, UInt32 completionTimeout, IOUSBCompletion *completion);
    
    virtual IOReturn DeviceRequest(IOUSBDevRequest *request, IOUSBCompletion *completion = 0);

    OSMetaClassDeclareReservedUsed(IOUSBRootHubDevice,  0);
    virtual IOReturn DeviceRequest(IOUSBDevRequest *request, UInt32 noDataTimeout, UInt32 completionTimeout, IOUSBCompletion *completion = 0);

    OSMetaClassDeclareReservedUnused(IOUSBRootHubDevice,  1);
    OSMetaClassDeclareReservedUnused(IOUSBRootHubDevice,  2);
    OSMetaClassDeclareReservedUnused(IOUSBRootHubDevice,  3);
    OSMetaClassDeclareReservedUnused(IOUSBRootHubDevice,  4);
};

#endif /* _IOKIT_IOUSBROOTHUBDEVICE_H */

