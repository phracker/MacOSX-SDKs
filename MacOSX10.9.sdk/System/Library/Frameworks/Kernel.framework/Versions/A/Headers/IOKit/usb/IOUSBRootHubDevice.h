/*
 * Copyright © 1998-2012 Apple Inc. All rights reserved.
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

#include <IOKit/usb/IOUSBHubDevice.h>

typedef struct 
{
	UInt32 request;
	void   *data;
}RHCommandHeader;

typedef RHCommandHeader*	RHCommandHeaderPtr;

/*
 class IOUSBRootHubDevice
 The object representing the Root Hub simulation.
 */
class IOUSBRootHubDevice : public IOUSBHubDevice
{
    OSDeclareDefaultStructors(IOUSBRootHubDevice)

private:
    UInt16				configuration;
	IOCommandGate		*_commandGate;

	// private method which overrides the same method in IOUSBHubDevice
	virtual bool			InitializeCharacteristics(void);					// used at start
	
    struct ExpansionData 
	{
		IOService *		X_IOResourcesEntry;						// deprecated
		UInt8			_myControllerSpeed;
		bool			_builtInController;						// Actually used to indicate whether the controller support the extra current APIs
		bool			_hasBuiltInProperty;
		bool			_hasTunnelledProperty;
	};
    ExpansionData *_expansionData;

public:
	// static methods
    static IOUSBRootHubDevice	*NewRootHubDevice(void);
    static IOReturn				GatedDeviceRequest (OSObject *	owner, 
												void *		arg0, 
												void *		arg1, 
												void *		arg2, 
												void *		arg3 );
    
	// IOKit methods
    virtual bool 	init();
	virtual bool 	start( IOService * provider );
    virtual void 	stop( IOService *provider );
    virtual void	free();

	// IOUSBHubDevice methods
	virtual bool			IsRootHub(void);

	// 
	virtual UInt32			RequestSleepPower(UInt32 requestedPower);
	virtual void			ReturnSleepPower(UInt32 returnedPower);
	
	// a non static but non-virtual function
	IOReturn 				DeviceRequestWorker(IOUSBDevRequest *request, UInt32 noDataTimeout, UInt32 completionTimeout, IOUSBCompletion *completion);
	UInt32					RequestExtraWakePower(UInt32 wakeType, UInt32 requestedPower, bool *retry);
	void					ReturnExtraWakePower(UInt32 wakeType, UInt32 requestedPower);
   
	// IOUSBDevice methods overriden here
	virtual UInt32			RequestExtraPower(UInt32 type, UInt32 requestedPower);
	virtual IOReturn		ReturnExtraPower(UInt32 type, UInt32 returnedPower);
    virtual IOReturn 		DeviceRequest(IOUSBDevRequest *request, IOUSBCompletion *completion = 0);
    virtual IOReturn 		DeviceRequest(IOUSBDevRequest *request, UInt32 noDataTimeout, UInt32 completionTimeout, IOUSBCompletion *completion = 0);

    OSMetaClassDeclareReservedUsed(IOUSBRootHubDevice,  0);
	virtual IOReturn		GetDeviceInformation(UInt32 *info);
	
    OSMetaClassDeclareReservedUsed(IOUSBRootHubDevice,  1);
	virtual void			InitializeExtraPower(UInt32 maxPortCurrent, UInt32 totalExtraCurrent);
	
    OSMetaClassDeclareReservedUsed(IOUSBRootHubDevice,  2);
	virtual void			SetSleepCurrent(UInt32 sleepCurrent);
	
    OSMetaClassDeclareReservedUsed(IOUSBRootHubDevice,  3);
	virtual UInt32			GetSleepCurrent();

    OSMetaClassDeclareReservedUsed(IOUSBRootHubDevice,  4);
	virtual void			SendExtraPowerMessage(UInt32 type, UInt32 returnedPower);
};

#endif

