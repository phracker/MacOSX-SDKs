/*
 * Copyright (c) 1998-2002 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights Reserved.
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
#ifndef _IOKIT_IOUSBCONTROLLERV2_H
#define _IOKIT_IOUSBCONTROLLERV2_H

#include <IOKit/usb/IOUSBController.h>

enum
{
    kUSBHSHubCommandAddHub	= 1,
    kUSBHSHubCommandRemoveHub	= 2,
    
    kUSBHSHubFlagsMultiTT	= 1
};


/*!
    @class IOUSBControllerV2
    @abstract subclass of the IOUSBController to provide support for high speed 
                devices and split transactions.
    @discussion The IOUSBController class provide sufficient functionality to 
                work with full (12Mb/s) and low (1.5Mb/s) devices. IOUSBControllerV2
                introduces the support for high (480Mb/s) speed devices from the
                USB 2.0 spec. In particular IOUSBControllerV2 indicates the high
                speed hub a full or low speed device is attached to so that split
                transactions can be directed to the hub at high speed to be forwarded
                to the full or low speed device by the hub.
                It also gives support for bulk endoints of greater than 256 bytes.
*/

class IOUSBControllerV2 : public IOUSBController
{
    OSDeclareAbstractStructors(IOUSBControllerV2)

private:
    
    // These for keeping track of high speed ancestor to allow controller to do splits.
    //
    UInt8 _highSpeedHub[128];
    UInt8 _highSpeedPort[128];

    struct V2ExpansionData { /* */ };
    V2ExpansionData * _v2ExpansionData;

    // Super's expansion data
    #define _freeUSBCommandPool		_expansionData->freeUSBCommandPool
    #define _freeUSBIsocCommandPool	_expansionData->freeUSBIsocCommandPool
    #define _watchdogUSBTimer		_expansionData->watchdogUSBTimer
    #define _controllerTerminating	_expansionData->_terminating
    #define _watchdogTimerActive	_expansionData->_watchdogTimerActive
    #define _pcCardEjected		_expansionData->_pcCardEjected
    #define _busNumber			_expansionData->_busNumber
    #define _currentSizeOfCommandPool	_expansionData->_currentSizeOfCommandPool
    #define _currentSizeOfIsocCommandPool	_expansionData->_currentSizeOfIsocCommandPool
    #define _controllerSpeed		_expansionData->_controllerSpeed


    /*!
	@function openPipe
        Open a pipe to the specified device endpoint
        @param address Address of the device on the USB bus
        @param speed of the device: kUSBDeviceSpeedLow, kUSBDeviceSpeedFull or kUSBDeviceSpeedHigh
        @param endpoint description of endpoint to connect to
    */
    virtual IOReturn 		OpenPipe(   USBDeviceAddress 	address, 
                                            UInt8 		speed,
                                            Endpoint *		endpoint );
    
    static IOReturn  DoCreateEP(OSObject *owner,
                           void *arg0, void *arg1,
                           void *arg2, void *arg3);

public:

/*!
    @function CreateDevice
    @abstract Create a new device as IOUSBController, making a note of the
                high speed hub device ID and port number the full/low speed
                device is attached to.
    @param newDevice       new device object to work with
    @param deviceAddress   USB device ID
    @param maxPacketSize   max packet size of endpoint zero
    @param speed           speed of the device kUSBDeviceSpeedLow, kUSBDeviceSpeedFull, kUSBDeviceSpeedHigh
    @param powerAvailable  power available to the device 
    @param hub             USB ID of hub the device is immediatly attached to. (Not necessarily high speed)
    @param port            port number of port the device is attached to.
*/
    virtual  IOReturn CreateDevice(	IOUSBDevice 		*newDevice,
                                    USBDeviceAddress	deviceAddress,
                                    UInt8		 	maxPacketSize,
                                    UInt8			speed,
                                    UInt32			powerAvailable,
                                    USBDeviceAddress		hub,
                                    int      port);

/*!
	@function ConfigureDeviceZero
    @abstract configure pipe zero of device zero, as IOUSBController, but also keeping 
                 note of high speed hub device is attached to.
    @param maxPacketSize  max packet size for the pipe
    @param speed           speed of the device kUSBDeviceSpeedLow, kUSBDeviceSpeedFull, kUSBDeviceSpeedHigh
    @param hub            USB ID of hub the device is immediatly attached to.  (Not necessarily high speed)
    @param port           port number of port the device is attached to.
*/
    virtual  IOReturn ConfigureDeviceZero(UInt8 maxPacketSize, UInt8 speed, USBDeviceAddress hub, int port);

/*!
	@function UIMCreateControlEndpoint
    @abstract Create an endpoint in the controller to do control transactions.
    @param functionNumber  USB device ID of device
    @param endpointNumber  endpoint address of the endpoint in the device
    @param maxPacketSize   maximum packet size of this endpoint
    @param speed           speed of the device kUSBDeviceSpeedLow, kUSBDeviceSpeedFull, kUSBDeviceSpeedHigh
    @param highSpeedHub    If speed is not kUSBDeviceSpeedHigh, the address of the high speed hub to
                           address split transactions to.
    @param highSpeedPort   If speed is not kUSBDeviceSpeedHigh, the hub port to address split transactions to
*/
    virtual IOReturn 		UIMCreateControlEndpoint(
                                                            UInt8	functionNumber,
                                                            UInt8	endpointNumber,
                                                            UInt16	maxPacketSize,
                                                            UInt8	speed,
                                                            USBDeviceAddress highSpeedHub,
                                                            int      highSpeedPort) = 0;

/*!
	@function UIMCreateBulkEndpoint
    @abstract Create an endpoint in the controller to do bulk transactions.
    @param functionNumber  USB device ID of device
    @param endpointNumber  endpoint address of the endpoint in the device
    @param direction       Direction of data flow. kUSBIn or kUSBOut
    @param maxPacketSize   maximum packet size of this endpoint
    @param speed           speed of the device kUSBDeviceSpeedFull, kUSBDeviceSpeedHigh
    @param highSpeedHub    If speed is not kUSBDeviceSpeedHigh, the address of the high speed hub to
                           address split transactions to.
    @param highSpeedPort   If speed is not kUSBDeviceSpeedHigh, the hub port to address split transactions to
*/
    virtual IOReturn 		UIMCreateBulkEndpoint(
                                                        UInt8		functionNumber,
                                                        UInt8		endpointNumber,
                                                        UInt8		direction,
                                                        UInt8		speed,
                                                        UInt16		maxPacketSize,
                                                        USBDeviceAddress highSpeedHub,
                                                        int      highSpeedPort) = 0;

/*!
	@function UIMCreateInterruptEndpoint
    @abstract Create an endpoint in the controller to do interrupt transactions.
    @param functionAddress USB device ID of device
    @param endpointNumber  endpoint address of the endpoint in the device
    @param direction       Direction of data flow. kUSBIn or kUSBOut
    @param speed           speed of the device kUSBDeviceSpeedLow, kUSBDeviceSpeedFull, kUSBDeviceSpeedHigh
    @param maxPacketSize   maximum packet size of this endpoint
    @param pollingRate     The maximum polling interval from the endpoint descriptor.
    @param highSpeedHub    If speed is not kUSBDeviceSpeedHigh, the address of the high speed hub to
                           address split transactions to.
    @param highSpeedPort   If speed is not kUSBDeviceSpeedHigh, the hub port to address split transactions to
*/
    virtual IOReturn		UIMCreateInterruptEndpoint(
                                                                short		functionAddress,
                                                                short		endpointNumber,
                                                                UInt8		direction,
                                                                short		speed,
                                                                UInt16		maxPacketSize,
                                                                short		pollingRate,
                                                                USBDeviceAddress highSpeedHub,
                                                                int      highSpeedPort) = 0;

/*!
	@function UIMCreateIsochEndpoint
    @abstract Create an endpoint in the controller to do Isochronous transactions.
    @param functionAddress USB device ID of device
    @param endpointNumber  endpoint address of the endpoint in the device
    @param maxPacketSize   maximum packet size of this endpoint
    @param highSpeedHub    If non zero, this is a full speed device, the address of the high speed hub to
                           address split transactions to.
    @param highSpeedPort   If highSpeedHub is non zero, the hub port to address split transactions to
*/
    virtual IOReturn 		UIMCreateIsochEndpoint(
                                                        short		functionAddress,
                                                        short		endpointNumber,
                                                        UInt32		maxPacketSize,
                                                        UInt8		direction,
                                                        USBDeviceAddress highSpeedHub,
                                                        int      highSpeedPort) = 0;

    OSMetaClassDeclareReservedUsed(IOUSBControllerV2,  0);
    virtual IOReturn		AddHSHub(USBDeviceAddress highSpeedHub, UInt32 flags);
    
    static IOReturn DOHSHubMaintenance(OSObject *owner, void *arg0, void *arg1, void *arg2, void *arg3);
    
    OSMetaClassDeclareReservedUsed(IOUSBControllerV2,  1);
    virtual IOReturn 		UIMHubMaintenance(USBDeviceAddress highSpeedHub, UInt32 highSpeedPort, UInt32 command, UInt32 flags);
    
    OSMetaClassDeclareReservedUsed(IOUSBControllerV2,  2);
    virtual IOReturn		RemoveHSHub(USBDeviceAddress highSpeedHub);
    
    static IOReturn DOSetTestMode(OSObject *owner, void *arg0, void *arg1, void *arg2, void *arg3);

    OSMetaClassDeclareReservedUsed(IOUSBControllerV2,  3);
    virtual IOReturn		SetTestMode(UInt32 mode, UInt32 port);
    
    OSMetaClassDeclareReservedUsed(IOUSBControllerV2,  4);
    virtual IOReturn		UIMSetTestMode(UInt32 mode, UInt32 port);
    
    OSMetaClassDeclareReservedUsed(IOUSBControllerV2,  5);
    virtual UInt64		GetMicroFrameNumber( void );
    
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  6);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  7);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  8);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  9);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  10);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  11);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  12);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  13);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  14);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  15);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  16);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  17);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  18);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  19);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  20);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  21);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  22);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  23);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  24);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  25);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  26);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  27);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  28);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  29);
    
};


#endif /* ! _IOKIT_IOUSBCONTROLLERV2_H */
