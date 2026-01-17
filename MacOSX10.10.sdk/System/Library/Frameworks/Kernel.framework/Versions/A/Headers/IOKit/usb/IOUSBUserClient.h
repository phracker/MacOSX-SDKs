/*
 * Copyright © 1998-2014 Apple Inc. All rights reserved.
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
    kUSBDeviceUserClientCreateInterfaceIterator,
    kUSBDeviceUserClientResetDevice,
    kUSBDeviceUserClientSuspend,
    kUSBDeviceUserClientAbortPipeZero,
    kUSBDeviceUserClientReEnumerateDevice,
    kUSBDeviceUserClientGetMicroFrameNumber,
    kUSBDeviceUserClientGetFrameNumberWithTime,
    kUSBDeviceUserClientSetAsyncPort,
	kUSBDeviceUserClientGetDeviceInformation,
	kUSBDeviceUserClientRequestExtraPower,
	kUSBDeviceUserClientReturnExtraPower,
	kUSBDeviceUserClientGetExtraPowerAllocated,
	kUSBDeviceUserClientGetBandwidthAvailableForDevice,
    kUSBDeviceUserClientSetConfigurationV2,
    kUSBDeviceUserClientRegisterForNotification,
    kUSBDeviceUserClientUnregisterNotification,
    kUSBDeviceUserClientAcknowledgeNotification,
    kIOUSBLibDeviceUserClientNumCommands
    };

enum {
    kUSBInterfaceUserClientOpen,
    kUSBInterfaceUserClientClose,
    kUSBInterfaceUserClientGetDevice,
    kUSBInterfaceUserClientSetAlternateInterface,
    kUSBInterfaceUserClientGetFrameNumber,
    kUSBInterfaceUserClientGetPipeProperties,
    kUSBInterfaceUserClientReadPipe,
    kUSBInterfaceUserClientWritePipe,
    kUSBInterfaceUserClientGetPipeStatus,
    kUSBInterfaceUserClientAbortPipe,
    kUSBInterfaceUserClientResetPipe,
    kUSBInterfaceUserClientClearPipeStall,
    kUSBInterfaceUserClientControlRequestOut,
    kUSBInterfaceUserClientControlRequestIn,
    kUSBInterfaceUserClientSetPipePolicy,
    kUSBInterfaceUserClientGetBandwidthAvailable,
    kUSBInterfaceUserClientGetEndpointProperties,
    kUSBInterfaceUserClientLowLatencyPrepareBuffer,
    kUSBInterfaceUserClientLowLatencyReleaseBuffer,
    kUSBInterfaceUserClientGetMicroFrameNumber,
    kUSBInterfaceUserClientGetFrameListTime,
    kUSBInterfaceUserClientGetFrameNumberWithTime,
    kUSBInterfaceUserClientSetAsyncPort,
    kUSBInterfaceUserClientReadIsochPipe,
    kUSBInterfaceUserClientWriteIsochPipe,
    kUSBInterfaceUserClientLowLatencyReadIsochPipe,
    kUSBInterfaceUserClientLowLatencyWriteIsochPipe,
	kUSBInterfaceUserClientGetConfigDescriptor,
	kUSBInterfaceUserClientGetPipePropertiesV2,
	kUSBInterfaceUserClientGetPipePropertiesV3,
	kUSBInterfaceUserClientGetEndpointPropertiesV3,
    kIOUSBLibInterfaceUserClientNumCommands,
	kUSBInterfaceUserClientSupportsStreams = kIOUSBLibInterfaceUserClientNumCommands,
	kUSBInterfaceUserClientCreateStreams,
	kUSBInterfaceUserClientGetConfiguredStreams,
	kUSBInterfaceUserClientReadStreamsPipe,
	kUSBInterfaceUserClientWriteStreamsPipe,
	kUSBInterfaceUserClientAbortStreamsPipe,
    kUSBInterfaceUserClientRegisterForNotification,
    kUSBInterfaceUserClientUnregisterNotification,
    kUSBInterfaceUserClientAcknowledgeNotification,
    kUSBInterfaceUserClientRegisterDriver,
	kIOUSBLibInterfaceUserClientV3NumCommands
   };

// this constant is used by both IOUSBDevice and IOUSBInterface to define the location of the IOUSBLib bundle
#define kIOUSBLibBundleName                 "IOUSBFamily.kext/Contents/PlugIns/IOUSBLib.bundle"

// this is a string representation of the UUID known as kIOUSBDeviceUserClientTypeID in IOUSBLib.h
// it should never have to change, even as we add new functions to the IOUSBDeviceInterface
#define kIOUSBDeviceUserClientTypeIDKey     "9dc7b780-9ec0-11d4-a54f-000a27052861"

// this is a string representation of the UUID known as kIOUSBInterfaceUserClientTypeID in IOUSBLib.h
// it should never have to change, even as we add new functions to the IOUSBInterfaceInterface
#define kIOUSBInterfaceUserClientTypeIDKey     "2d9786c6-9ef3-11d4-ad51-000a27052861"

// this is the class name of the IOUSBInterfaceUserClient in the kernel
// if we ever have to go to IOUSBInterfaceeUserClientV4, this will need to change
#define kIOUSBInterfaceUserClientClassNameStr     "IOUSBInterfaceUserClientV3"


// this is the class name of the IOUSBDeviceUserClient in the kernel
// if we ever have to go to IOUSBDeviceUserClientV3, this will need to change
#define kIOUSBDeviceUserClientClassNameStr     "IOUSBDeviceUserClientV2"

#define kNeedsDeviceAccessEntitlement   "NeedsDeviceAccessEntitlement"

#if KERNEL
#include <IOKit/IOService.h>
#include <IOKit/IOUserClient.h>
#include <IOKit/usb/USB.h>
#include <IOKit/usb/IOUSBDevice.h>
#include <IOKit/usb/IOUSBInterface.h>

//================================================================================================
//
//   Structure declarations
//
//================================================================================================
//
typedef struct IOUSBUserClientAsyncParamBlock IOUSBUserClientAsyncParamBlock;

struct IOUSBUserClientAsyncParamBlock 
{
    OSAsyncReference64			fAsyncRef;
    uint32_t					fAsyncCount;
    uint32_t					fMax;
    IOMemoryDescriptor *		fMem;
    IOUSBDevRequestDesc			req;
};

typedef struct IOUSBInterfaceUserClientISOAsyncParamBlock IOUSBInterfaceUserClientISOAsyncParamBlock;
struct IOUSBInterfaceUserClientISOAsyncParamBlock 
{
    OSAsyncReference64			fAsyncRef;
	uint32_t					fAsyncCount;
    mach_vm_size_t				frameLen;	// In bytes
    mach_vm_address_t           frameBase;	// In user task
    IOMemoryDescriptor *        dataMem;
    IOMemoryDescriptor *        countMem;
	uint64_t					numFrames;
	uint64_t					startFrame;
	uint64_t					options;
    IOUSBIsocFrame              frames[0];  // Must be the last one
};


// this class declaration may want to move to another header file (and maybe not)
class IOUSBNotification : public OSObject
{
    OSDeclareDefaultStructors(IOUSBNotification);

    IOUserClient *              fpIOUserClient;              // the IOUserClient object which created this IOUSBNotification
    IOUSBDevice *               fpIOUSBDevice;               // the device whose user client created this note (or the parent of the interface user client)
    IOUSBInterface *            fpIOUSBInterface;            // the interface whose user client create this note (could be NULL)
    UInt64                      fbmNotificationMask;         // a bitmask of the desired bits for this notification
    OSAsyncReference64          fAsyncRef;                   // this contains the callback routine and the refCon in user space
    UInt64                      fToken;                      // this token is unique for each user client
    
public:
    static IOUSBNotification*   withUserClient(IOUserClient *pIOUserClient);

    // Accessors
    inline IOUserClient *              GetIOUserClient(void)                                        {return fpIOUserClient;}
    inline IOUSBDevice *               GetIOUSBDevice(void)                                         {return fpIOUSBDevice;}
    inline IOUSBInterface *            GetIOUSBInterface(void)                                      {return fpIOUSBInterface;}
    inline UInt64                      GetNotificationMask(void)                                    {return fbmNotificationMask;}
    inline OSAsyncReference64 *        GetAsyncRefPtr(void)                                         {return &fAsyncRef;}
    inline UInt64                      GetToken(void)                                               {return fToken;}
    
    inline void                        SetIOUSBDevice(IOUSBDevice *iousbdevice)                     {fpIOUSBDevice = iousbdevice;}
    inline void                        SetIOUSBInterface(IOUSBInterface *iousbinterface)            {fpIOUSBInterface = iousbinterface;}
    inline void                        SetNotificationMask(UInt64 notificationmask)                 {fbmNotificationMask = notificationmask;}
    inline void                        SetAsyncRef(OSAsyncReference64 *pAsyncRef)                   {bcopy(pAsyncRef, &fAsyncRef, sizeof(OSAsyncReference64));}
    inline void                        SetToken(UInt64 token)                                       {fToken = token;}
    
    // public methods
    IOReturn                            SendNotification(UInt64 notificationmask, void* pToken);
};

enum {
    // values used to talk between the UserClient KEXT and a device or interface
    kUSBProcessNotificationRegisterNotification      = 1,
    kUSBProcessNotificationUnregisterNotification    = 2,
    kUSBProcessNotificationAcknowledgeNotification   = 3
};

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

#endif

#endif

