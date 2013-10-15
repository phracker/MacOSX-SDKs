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

#ifndef _IOKIT_IOUSBUSERCLIENT_H
#define _IOKIT_IOUSBUSERCLIENT_H

// these are the new User Client method names    
enum {
    kUSBDeviceUserClientOpen,
    kUSBDeviceUserClientClose,
    kUSBDeviceUserClientSetConfig,
    kUSBDeviceUserClientGetConfig,
    kUSBDeviceUserClientGetConfigDescriptor,
    kUSBDeviceUserClientGetFrameNumber,
    kUSBDeviceUserClientDeviceRequestOut,
    kUSBDeviceUserClientDeviceRequestIn,
    kUSBDeviceUserClientDeviceRequestOutOOL,
    kUSBDeviceUserClientDeviceRequestInOOL,
    kUSBDeviceUserClientCreateInterfaceIterator,
    kUSBDeviceUserClientResetDevice,
    // new with 1.8.2
    kUSBDeviceUserClientSuspend,
    kUSBDeviceUserClientAbortPipeZero,
    // new with 1.8.7
    kUSBDeviceUserClientReEnumerateDevice,
    // new with 1.9.7
    kUSBDeviceUserClientGetMicroFrameNumber,
    kNumUSBDeviceMethods
    };

enum {
    kUSBDeviceUserClientSetAsyncPort,
    kUSBDeviceUserClientDeviceAsyncRequestOut,
    kUSBDeviceUserClientDeviceAsyncRequestIn,
    kNumUSBDeviceAsyncMethods
    };

enum {
    kUSBInterfaceUserClientOpen,
    kUSBInterfaceUserClientClose,
    kUSBInterfaceUserClientGetDevice,
    kUSBInterfaceUserClientSetAlternateInterface,
    kUSBInterfaceUserClientGetFrameNumber,
    kUSBInterfaceUserClientGetPipeProperties,
    kUSBInterfaceUserClientReadPipe,
    kUSBInterfaceUserClientReadPipeOOL,
    kUSBInterfaceUserClientWritePipe,
    kUSBInterfaceUserClientWritePipeOOL,
    kUSBInterfaceUserClientGetPipeStatus,
    kUSBInterfaceUserClientAbortPipe,
    kUSBInterfaceUserClientResetPipe,
    kUSBInterfaceUserClientSetPipeIdle,
    kUSBInterfaceUserClientSetPipeActive,
    kUSBInterfaceUserClientClearPipeStall,
    kUSBInterfaceUserClientControlRequestOut,
    kUSBInterfaceUserClientControlRequestIn,
    kUSBInterfaceUserClientControlRequestOutOOL,
    kUSBInterfaceUserClientControlRequestInOOL,
    // new with 1.9.0
    kUSBInterfaceUserClientSetPipePolicy,
    kUSBInterfaceUserClientGetBandwidthAvailable,
    kUSBInterfaceUserClientGetEndpointProperties,
    // new with 1.9.2
    kUSBInterfaceUserClientLowLatencyPrepareBuffer,
    kUSBInterfaceUserClientLowLatencyReleaseBuffer,
    // new with 1.9.7
    kUSBInterfaceUserClientGetMicroFrameNumber,
    kUSBInterfaceUserClientGetFrameListTime,
    kNumUSBInterfaceMethods
    };


enum {
    kUSBInterfaceUserClientSetAsyncPort,
    kUSBInterfaceUserClientControlAsyncRequestOut,
    kUSBInterfaceUserClientControlAsyncRequestIn,
    kUSBInterfaceUserClientAsyncReadPipe,
    kUSBInterfaceUserClientAsyncWritePipe,
    kUSBInterfaceUserClientReadIsochPipe,
    kUSBInterfaceUserClientWriteIsochPipe,
    // new with 1.9.2
    kUSBInterfaceUserClientLowLatencyReadIsochPipe,
    kUSBInterfaceUserClientLowLatencyWriteIsochPipe,
    kNumUSBInterfaceAsyncMethods
    };

#if KERNEL
#include <IOKit/IOService.h>

//================================================================================================
//
// This class is used to add an IOProviderMergeProperties dictionary entry to a provider's
// property list, thus providing a tie between hardware and a CFBundle at hardware
// load time.  This property usually contains the user client class name and the CFPlugInTypes UUID's
// but it can contain other properties.
//
//================================================================================================
//
class IOUSBUserClientInit : public IOService 
{
    OSDeclareDefaultStructors(IOUSBUserClientInit);

public:
    
    virtual bool		start(IOService *  provider) ;
    virtual bool 		MergeDictionaryIntoProvider(IOService *  provider, OSDictionary *  mergeDict);
    virtual bool		MergeDictionaryIntoDictionary(OSDictionary *  sourceDictionary,  OSDictionary *  targetDictionary);
};

#endif // KERNEL

#endif /* ! _IOKIT_IOUSBUSERCLIENT_H */

