/*
 * Copyright (c) 1998-2003 Apple Computer, Inc. All rights reserved.
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

#ifndef __OPEN_SOURCE__
/*
 *
 *	$Id: IOUSBRootHubDevice.h,v 1.9 2003/08/20 19:41:40 nano Exp $
 *
 *	$Log: IOUSBRootHubDevice.h,v $
 *	Revision 1.9  2003/08/20 19:41:40  nano
 *	
 *	Bug #:
 *	New version's of Nima's USB Prober (2.2b17)
 *	3382540  Panther: Ejecting a USB CardBus card can freeze a machine
 *	3358482  Device Busy message with Modems and IOUSBFamily 201.2.14 after sleep
 *	3385948  Need to implement device recovery on High Speed Transaction errors to full speed devices
 *	3377037  USB EHCI: returnTransactions can cause unstable queue if transactions are aborted
 *	
 *	Also, updated most files to use the id/log functions of cvs
 *	
 *	Submitted by: nano
 *	Reviewed by: rhoads/barryt/nano
 *	
 */
#endif
#ifndef _IOKIT_IOUSBROOTHUBDEVICE_H
#define _IOKIT_IOUSBROOTHUBDEVICE_H

#include <IOKit/usb/IOUSBDevice.h>
#include <IOKit/usb/IOUSBController.h>
#include <IOKit/usb/USBHub.h>

class IOUSBRootHubDevice : public IOUSBDevice
{
    OSDeclareDefaultStructors(IOUSBRootHubDevice)

    UInt16 	configuration;

    struct ExpansionData { /* */ };
    ExpansionData * _expansionData;

public:
    static IOUSBRootHubDevice *NewRootHubDevice(void);
    
    virtual IOReturn DeviceRequest(IOUSBDevRequest *request, IOUSBCompletion *completion = 0);

    OSMetaClassDeclareReservedUsed(IOUSBRootHubDevice,  0);
    virtual IOReturn DeviceRequest(IOUSBDevRequest *request, UInt32 noDataTimeout, UInt32 completionTimeout, IOUSBCompletion *completion = 0);

    OSMetaClassDeclareReservedUnused(IOUSBRootHubDevice,  1);
    OSMetaClassDeclareReservedUnused(IOUSBRootHubDevice,  2);
    OSMetaClassDeclareReservedUnused(IOUSBRootHubDevice,  3);
    OSMetaClassDeclareReservedUnused(IOUSBRootHubDevice,  4);
};

#endif /* _IOKIT_IOUSBROOTHUBDEVICE_H */

